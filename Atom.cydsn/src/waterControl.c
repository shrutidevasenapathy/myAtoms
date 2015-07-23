#include <stdio.h>
#include "waterControl.h"
#include "hwInterface.h"

#define OFF 0
#define ON 1

clock currentTime;
clock expTime;


//int currentVolume;
//int maxVolume;


//struct source: https://docs.google.com/document/d/1WrIqsW1SgbLmcNN1VXvH0uA1hI1NaXTKU7qD_cBLoLY/edit#
struct {
	int InnerPressure;
	int OuterPressure;
	int CurrentFlow;
	int TotalVolume;
	int ValveStatus;
	int LastStartNumber;
	int LastStartVolume;
	int LastStartFlow;
	int StartTime;
	int StopTime;
	int NumStarts;
	int VolPerStart;
	int MaxVol;
	int MinVol;

	int fertigationTable[10][4];

	int NotBefore;
	int NotAfter;
	int DilutionFactorA;
	int DilutionFactorB;
	int VenturiSuctionA;
	int VenturiSuctionB;
	int SquareMeters;
	int LperSqMeterPerDay;
	int CropType;
} water_data;


void waterControl_Init(){
     hwInterface_Init();
}

void setvar_fertigationTable0(int * val) {
	memcpy(water_data.fertigationTable[0], val, 4 * sizeof(int));
}
void setvar_fertigationTable1(int * val) {
	memcpy(water_data.fertigationTable[1], val, 4 * sizeof(int));
}
void setvar_fertigationTable2(int * val) {
	memcpy(water_data.fertigationTable[2], val, 4 * sizeof(int));
}
void setvar_fertigationTable3(int * val) {
	memcpy(water_data.fertigationTable[3], val, 4 * sizeof(int));
}
void setvar_fertigationTable4(int * val) {
	memcpy(water_data.fertigationTable[4], val, 4 * sizeof(int));
}
void setvar_fertigationTable5(int * val) {
	memcpy(water_data.fertigationTable[5], val, 4 * sizeof(int));
}
void setvar_fertigationTable6(int * val) {
	memcpy(water_data.fertigationTable[6], val, 4 * sizeof(int));
}
void setvar_fertigationTable7(int * val) {
	memcpy(water_data.fertigationTable[7], val, 4 * sizeof(int));
}
void setvar_fertigationTable8(int * val) {
	memcpy(water_data.fertigationTable[8], val, 4 * sizeof(int));
}
void setvar_fertigationTable9(int * val) {
	memcpy(water_data.fertigationTable[9], val, 4 * sizeof(int));
}

int * getvar_fertigationTable0(void) { return water_data.fertigationTable[0]; }
int * getvar_fertigationTable1(void) { return water_data.fertigationTable[1]; }
int * getvar_fertigationTable2(void) { return water_data.fertigationTable[2]; }
int * getvar_fertigationTable3(void) { return water_data.fertigationTable[3]; }
int * getvar_fertigationTable4(void) { return water_data.fertigationTable[4]; }
int * getvar_fertigationTable5(void) { return water_data.fertigationTable[5]; }
int * getvar_fertigationTable6(void) { return water_data.fertigationTable[6]; }
int * getvar_fertigationTable7(void) { return water_data.fertigationTable[7]; }
int * getvar_fertigationTable8(void) { return water_data.fertigationTable[8]; }
int * getvar_fertigationTable9(void) { return water_data.fertigationTable[9]; }

int conv_ia2str(char *str, int len, int * val) {
	//this function is tailored for fertigation table, so int* size if equal 4!
	int ret = 0;
	*str = '['; ret++;
	int i = 0;
	for(; i < 4; i++) {
		if(len - ret == 0) return ret;
		ret += conv_i2str(str + ret, len - ret, val[i]);
		if(len - ret == 0) return ret;
		*(str + ret++) = ',';
	}
	*(str + ret - 1) = ']'; //change comma to ]
	return ret;
}
static int fttmparr[4];
int * conv_str2ia(const char *str, int len) {
	//this function is tailored for fertigation table, so int* size if equal 4!
	str++; len -= 2; //skip first and last char (its [ and ]); now we have ints separated by commas
	int i = 0;
	for(; i < 4; i++) {
		int lentocomma = 0;
		while(str[lentocomma] != ',' && lentocomma != len) {
			lentocomma++;
		}
		fttmparr[i] = conv_str2i(str, lentocomma);
		lentocomma++;
		str += lentocomma;
		len -= lentocomma;
	}
	return fttmparr;
}

void setvar_notBefore(int val) {
	water_data.NotBefore = val;
}
void setvar_notAfter(int val) {
	water_data.NotAfter = val;
}
void setvar_dilutionFactorA(int val) {
	water_data.DilutionFactorA = val;
}
void setvar_dilutionFactorB(int val) {
	water_data.DilutionFactorB = val;
}
void setvar_venturiSuctionA(int val) {
	water_data.VenturiSuctionA = val;
}
void setvar_venturiSuctionB(int val) {
	water_data.VenturiSuctionB = val;
}
void setvar_squareMeters(int val) {
	water_data.SquareMeters = val;
}
void setvar_lPerSqMeterPerDay(int val) {
	water_data.LperSqMeterPerDay = val;
}
void setvar_cropType(int val) { /*read only*/ }

void setvar_innerPressure(int val) { /*read only*/ }
void setvar_outerPressure(int val) { /*read only*/ }
void setvar_currentFlow(int val) { /*read only*/ }
void setvar_totalVolume(int val) { /*read only*/ }
void setvar_valveStatus(int val) { /*read only*/ }
void setvar_lastStartNumber(int val) { /*read only*/ }
void setvar_lastStartVolume(int val) { /*read only*/ }
void setvar_lastStartFlow(int val) { /*read only*/ }
void setvar_startTime(int val) {
	water_data.StartTime = val;
}
void setvar_stopTime(int val) {
	water_data.StopTime = val;
}
void setvar_numStarts(int val) {
	water_data.NumStarts = val;
}
void setvar_volPerStart(int val) {
	water_data.VolPerStart = val;
}
void setvar_maxVol(int val) {
	water_data.MaxVol = val;
}
void setvar_minVol(int val) {
	water_data.MinVol = val;
}

int getvar_notBefore(void) { return water_data.NotBefore; }
int getvar_notAfter(void) { return water_data.NotAfter; }
int getvar_dilutionFactorA(void) { return water_data.DilutionFactorA; }
int getvar_dilutionFactorB(void) { return water_data.DilutionFactorB; }
int getvar_venturiSuctionA(void) { return water_data.VenturiSuctionA; }
int getvar_venturiSuctionB(void) { return water_data.VenturiSuctionB; }
int getvar_squareMeters(void) { return water_data.SquareMeters; }
int getvar_lPerSqMeterPerDay(void) { return water_data.LperSqMeterPerDay; }
int getvar_cropType(void) { return water_data.CropType; }

int getvar_innerPressure(void) { return water_data.InnerPressure; }
int getvar_outerPressure(void) { return water_data.OuterPressure; }
int getvar_currentFlow(void) { return water_data.CurrentFlow; }
int getvar_totalVolume(void) { return water_data.TotalVolume; }
int getvar_valveStatus(void) { return water_data.ValveStatus; }
int getvar_lastStartNumber(void) { return water_data.LastStartNumber; }
int getvar_lastStartVolume(void) { return water_data.LastStartVolume; }
int getvar_lastStartFlow(void) { return water_data.LastStartFlow; }
int getvar_startTime(void) { return water_data.StartTime; }
int getvar_stopTime(void) { return water_data.StopTime; }
int getvar_numStarts(void) { return water_data.NumStarts; }
int getvar_volPerStart(void) { return water_data.VolPerStart; }
int getvar_maxVol(void) { return water_data.MaxVol; }
int getvar_minVol(void) { return water_data.MinVol; }

void comm_GenerateInfo(void) {
	int tmp;

	ADD_STATIC_STRING_TO_RESP("{\"n\":\"InnerPressure\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.InnerPressure);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"OuterPressure\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.OuterPressure);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"CurrentFlow\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.CurrentFlow);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"TotalVolume\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.TotalVolume);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"ValveStatus\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.ValveStatus);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"LastStartNumber\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.LastStartNumber);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"LastStartVolume\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.LastStartVolume);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');

	ADD_STATIC_STRING_TO_RESP(",{\"n\":\"LastStartFlow\",\"t\":\"i\",\"v\":");
	tmp = conv_i2str(respEnd, respFreeSpace, water_data.LastStartFlow);
	respEnd += tmp;
	respFreeSpace -= tmp;
	ADD_CHAR_TO_RESP('}');
}


int opVals[24][4]=
{
    //At startup everything should be set to zero until vals are downloaded
    //{Time of day, valve mode, minutes on, total max vol}
    {0,OFF,0,0},
    {1,OFF,0,0},
    {2,OFF,0,0},
    {3,OFF,0,0},
    {4,OFF,0,0},
    {5,OFF,0,0},
    {6,OFF,0,0},
    {7,OFF,0,0},
    {8,ON,5,5},
    {9,ON,6,11},
    {10,ON,7,18},
    {11,ON,8,26},
    {12,ON,9,35},
    {13,ON,10,45},
    {14,ON,9,54},
    {15,ON,8,62},
    {16,ON,7,69},
    {17,ON,6,75},
    {18,OFF,0,75},
    {19,OFF,0,75},
    {20,OFF,0,75},
    {21,OFF,0,75},
    {22,OFF,0,75},
    {23,OFF,0,75}
};

void fsmIfaceWaterControl_updateOpVals(){
    //TODO
    //Update the operation vals based on Info coming from mc200
    UART_UartPutString("updateOpVals\n\r");
}

void fsmIfaceWaterControl_setExpTime(){
    currentTime = getTime();
    expTime = currentTime;
    int operationMins = opVals[currentTime.hours][1];
       
    expTime.mins += operationMins;
    if(expTime.mins >= 60){
        expTime.hours+=1;
        expTime.mins-=60;
    }
}

sc_integer fsmIfaceWaterControl_getOpMode(){
    currentTime = getTime();
    int mode = opVals[currentTime.hours][1];
    
    if(currentTime.hours > expTime.hours){
        mode=OFF;
    }
    if(currentTime.hours == expTime.hours && currentTime.mins >= expTime.mins){
        mode=OFF;
    }
        
//    UART_UartPutString("checkOpMode  : ");
//    UART_UartPutChar(mode);
//    UART_UartPutString("\r\n");
    
    //return mode;
    return 1;
}

sc_integer fsmIfaceWaterControl_getCurrentVolume(){
    //TODO
    //make sure that we are not exeeding the maximum volume
    
//    UART_UartPutString("checkVolume\n\r");
    return 1;
}

sc_integer fsmIfaceWaterControl_getMaxVolume(){
    //return opVals[getTime().hours][3];
    return 1000;
}    
void fsmIfaceWaterControl_valveOn(){
    //TODO
    //switch valve on
//	UART_UartPutString("valveOn\r\n");
}

void fsmIfaceWaterControl_valveOff(){
    //TODO
    //switch valve off
//    UART_UartPutString("valveOff\r\n");
	LED_Write(0u);
}

void fsmIfaceWaterControl_sendStats(){
	comm_ScheduleMessage("Info", 4, 'X', '0');
//    int temp;
    char tmpstr[25];
//    temp = PressureSensor1_Read();
    sprintf(tmpstr, "Pressure 1 = %d\r\n", PressureSensor1_Read());    
    UART_UartPutString(tmpstr);
    
    sprintf(tmpstr, "Pressure 2 = %d\r\n", PressureSensor2_Read());    
    UART_UartPutString(tmpstr);
    
    sprintf(tmpstr, "Flow = %d\r\n", FlowSensor1_Read());    
    UART_UartPutString(tmpstr);
    
}
