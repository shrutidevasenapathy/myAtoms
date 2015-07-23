/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#define SENSOR_ATOM     0      //1=connected 0=not connected
#define LORA_ATOM       0       //1=connected 0=not connected
#define POWER_ATOM      0       //1=connected 0=not connected
#define CO2_SENSOR      0       //1-connected 0=not connected
#define SOIL_SENSOR     0       //1-connected 0=not connected

#ifndef MAIN_H_
#define MAIN_H_

#include <project.h>
#include "src-fsm/Fsm.h"
#include "src-fsm/FsmRequired.h"


#if(SENSOR_ATOM == 1)    
    #include "climate.h"
#endif
#if(LORA_ATOM == 1)    
    #include "lora.h"
#endif
#if(CO2_SENSOR == 1)    
    #include "co2.h"
#endif

#define POR_FLAG        0x01
#define SLEEP_FLAG      0x02
#define DEEP_SLEEP_FLAG 0x03
#define ADC_FLAG        0x04
#define SW_FLAG         0x08
#define SPI_FLAG        0x10
#define WAKE_MASK       0xFC
#define WAKE_FLAG_MASK  0x03
#define SPI_FLAG_MASK   0xEF
#define ADC_FLAG_MASK   0xFB    
    
#define INIT            0u
#define DAY             1u
#define NIGHT           2u
//#define NIGHT           20u
#define LOWPWR          3u

#define CR              0x0D    
#define LF              0x09
#define ESC             0x1B
#define NewLine() COMM_UartPutChar(CR); COMM_UartPutChar(LF);
#define ClearScreen() COMM_UartPutChar(ESC); COMM_UartPutString("[2J"); COMM_UartPutChar(ESC); COMM_UartPutString("[2H");
 
/*Time is (VALUE0*VALUE1)/32kHz in seconds*/    
#define WDT_MATCH_VALUE0			0x7CFF 
//#define WDT_MATCH_VALUE1_DAY        0x0A//0x0A   
#define WDT_MATCH_VALUE1_DAY        0x01// 1 second
#define WDT_MATCH_VALUE1_NIGHT      0x3C//0x3C 
//#define WDT_MATCH_VALUE1_NIGHT      0x0A// 10 seconds
    
CY_ISR_PROTO(WDT_ISR_Handler);
CY_ISR_PROTO(SPI_ISR_Handler);
    
typedef struct rdbuf{
    unsigned char val[5];
}rdbuf;

typedef struct clock{
    uint8 secs;
    uint8 mins;
    uint8 hours;
    uint8 mode;
    uint8 omode;
}clock;

void PrintFloat(char str1[],char str2[],float value);
void SetUpWDT(uint8 md);
void f_putc (void* p, char c);
void CheckTime();
clock getTime();


#endif /* MAIN_H_ */
