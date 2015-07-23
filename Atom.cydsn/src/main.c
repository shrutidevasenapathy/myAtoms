#include <project.h>
#include "main.h"

   
#include "sysTimer.h"
#include "sleepMgr.h"



#include "waterControl.h"


volatile uint8 Flag = 0;
clock time;
//int voltage = 0;
int voltage = 4200;

char str_mode[4][15]={{"Init"},{"Day"},{"Night"},{"LowPower"}};
Fsm modelHandle;


static void communicationHandler(Fsm* handle) {
	comm_Handler();
}


void setvar_updateRate(int val) {

}


void setvar_test(char * val) {
  LED_Write(*val-0x30);
}
char * getvar_test(void) {
    return LED_Read() ? "0" : "1";
}

int getvar_sleepPeriod(void) {
	return CySysWdtReadMatch(CY_SYS_WDT_COUNTER1);
}
void setvar_sleepPeriod(int val) {
	CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
	CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
	CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1, val);
	CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
}

int getvar_shutdownTime(void) {
	return 1;
}
void setvar_shutdownTime(int val) {}



void comm_ModeChange(atom_modes_t mode) {
	switch(mode) {
	case ATOM_MODE_Idle: 	fsmIfacePlatform_raise_idle(&modelHandle); break;
	case ATOM_MODE_Start: 	fsmIfacePlatform_raise_start(&modelHandle); break;
	case ATOM_MODE_Test: 	fsmIfacePlatform_raise_test(&modelHandle); break;
	case ATOM_MODE_Shutdown: /*TODO do something here!*/ break;
	default: break;
	}
}

/*****************************************************************************************
* PLATFORM FUNCTIONS
*****************************************************************************************/
clock getTime(){
    return time;
}

CY_ISR(WDT_ISR_Handler){
	/* Clear the WDT interrupt */
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT|CY_SYS_WDT_COUNTER0_INT);

    fsmIfacePlatform_raise_timer(&modelHandle);
    Flag = Flag|DEEP_SLEEP_FLAG; //??
}
void preset(void){
   	time.secs = 00;
   	time.mins = 43;
   	time.hours = 10;
   	time.mode = DAY;
   	time.omode = time.mode;
   	Flag = Flag|POR_FLAG;
}
void init(void){
	Flag = Flag & WAKE_MASK;


    //UART Initialization
    UART_Init();
    UART_Enable();
    UART_Start();


    //Communication Initialization
    comm_Init();

    SysTimer_Init();
      
    /*Watchdog timer initilization*/
    SetUpWDT(INIT);
    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
    isr_WDT_StartEx(WDT_ISR_Handler);
	CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
    CyGlobalIntEnable;
    
    /*sensor and valve control initialization*/
    waterControl_Init();
  
}

static void ResumePeripherals(void){
    UART_Start();
}
static void StorePeripherals(void){
    UART_Stop();
}


void CheckTime(){
    /*Update time*/
    if(time.mode == DAY){
		time.secs +=1;
        if(time.secs >= 60){
			time.mins++;
			time.secs -= 60;
		}
    }
    else{
		time.mins++;
	}
    if(time.mins >= 60){
        time.hours++;
        time.mins -= 60;
        if(time.hours >= 24){
			time.hours = 0; 
		}
    }
    if(time.hours > 9 && time.hours < 17){
		time.mode = DAY;
	}
    else{
		time.mode = NIGHT;
	}
}
void check_duty_cycle(void){
        CheckTime();
}
void SetUpWDT(uint8 md){
    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
    switch(md){
    case INIT:
        /* Configure for Free Running mode for WDT 0 */
        CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_NONE);
        /* Configure for Interrupt mode for WDT 1 */
        CySysWdtWriteMode(CY_SYS_WDT_COUNTER1, CY_SYS_WDT_MODE_INT);
        /* Configure for Cascade WDT 0 & 1 */
        CySysWdtWriteCascade(CY_SYS_WDT_CASCADE_01);
        /* Let the timers clear when it reaches period */
        CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);
        CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
        /* Set the period for the WDT0 to 1 second */
        CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0,WDT_MATCH_VALUE0);
        CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1, 10);
        break;
    /*Set sleep time for modes, add case for new modes*/    
    case DAY:
        CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1,WDT_MATCH_VALUE1_DAY);
        break;
    case NIGHT:
        CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1,WDT_MATCH_VALUE1_NIGHT);
        break;
    case LOWPWR:
        CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1,WDT_MATCH_VALUE1_NIGHT);
        break;
    default:
        break;
    }
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK|CY_SYS_WDT_COUNTER1_MASK);
}

/*****************************************************************************************
* FSM OPERATION FUNCTIONS
*****************************************************************************************/
void fsmIfacePlatform_sleep(void){
	/* 
	* This state should decide weather we go on HW sleep or HW DeepSleep and resume accordingly
	*/
	check_duty_cycle();
	if (time.omode != time.mode){
		SetUpWDT(time.mode);
	}
    time.omode = time.mode; 
    StorePeripherals();

    sleepMgr_requestDeepSleep();
}
void fsmIfacePlatform_resume(void){
	sleepMgr_releaseDeepSleep();
	/* this function will resume any peripherals */
    Flag = Flag & WAKE_MASK;
    ResumePeripherals();

}

void fsmIfacePlatform_send_msg() {
	comm_ScheduleMessage("Info", 4, 'X', '0');
}

/*****************************************************************************************
* MAIN
*****************************************************************************************/
int main(){
	preset();
	init();

    fsm_init(&modelHandle);
    fsm_enter(&modelHandle);
    setValve1ON(true);
    CyDelay(1000);
    setValve1ON(false);
    for(;;){
        SysTimer_FsmHandler(&modelHandle);
    	communicationHandler(&modelHandle);
        fsm_runCycle(&modelHandle);
        sleepMgr_sleep();
    }
}
