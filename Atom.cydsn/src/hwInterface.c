#include "hwInterface.h"



void hwInterface_Init(void){
    
    Ctrl_12V_Write(1u);
    Ctrl_5V_Write(1u);
    
    Counter_Start();
    
    ADC_Start();
    ADC_StartConvert();


}
/*******************************************************************************
* Function Name: setValve1ON
********************************************************************************
*
* Summary:
*  Turns on valve 1 (connector J9 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
void setValve1ON(bool direction){
    if (direction==true){ //Direction 1
         ON1_DIR1_Write(0u);
         ON2_DIR2_Write(1u);
    }
    else{
        ON1_DIR1_Write(1u);
        ON2_DIR2_Write(0u);
    }
}
/*******************************************************************************
* Function Name: setValve2ON
********************************************************************************
*
* Summary:
*  Turns on valve 2 (connector J11 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
void setValve2ON(bool direction){
    if (direction==true){ //Direction 1
        ON1_DIR2_Write(0u);
        ON2_DIR1_Write(1u);
    }
    else{
       ON1_DIR2_Write(1u);
       ON2_DIR1_Write(0u);
    }
}
/*******************************************************************************
* Function Name: setValve3ON
********************************************************************************
*
* Summary:
*  Turns on valve 3 (connector J8 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
void setValve3ON(bool direction){
    if (direction==true){ //Direction 1
        ON3_DIR1_Write(0u);
        ON4_DIR2_Write(1u);
    }
    else{
        ON3_DIR1_Write(1u);
        ON4_DIR2_Write(0u);
    }
}
/*******************************************************************************
* Function Name: setValve4ON
********************************************************************************
*
* Summary:
*  Turns on valve 4 (connector J10 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
void setValve4ON(bool direction){
    if (direction==true){ //Direction 1
        ON3_DIR2_Write(0u);
        ON4_DIR1_Write(1u);
    }
    else{
        ON3_DIR2_Write(1u);
        ON4_DIR1_Write(0u);
    }
}
/*******************************************************************************
* Function Name: setValve5ON
********************************************************************************
*
* Summary:
*  Turns on valve 5 (connector J6 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
/*void setValve5ON(bool direction){
    if (direction==true){ //Direction 1
        ON5_DIR1_Write(0u);
        ON6_DIR2_Write(1u);
    }
    else{
        ON5_DIR1_Write(1u);
        ON6_DIR2_Write(0u);
    }
}*/
/*******************************************************************************
* Function Name: setValve6ON
********************************************************************************
*
* Summary:
*  Turns on valve 6 (connector J7 on Water Control Atom.)
*
* Parameters:
*  direction: The direction in which to turn the valve ON.
*  TRUE		1 to set pin 2 high and pin 1 low
*  FALSE	0 to set pin 1 high and pin 2 low
*
* Return:
*  None.
*
*******************************************************************************/
/*void setValve6ON(bool direction){
    if (direction==true){ //Direction 1
         ON5_DIR2_Write(0u);
         ON6_DIR1_Write(1u);
    }
    else{
          ON5_DIR2_Write(1u);
         ON6_DIR1_Write(0u);
    }
}
*/
/*******************************************************************************
* Function Name: setValve1OFF
********************************************************************************
*
* Summary:
*  Turns off valve 1 (connector J9 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/

void setValve1OFF(void){
    ON1_DIR1_Write(0u);
    ON2_DIR2_Write(0u);
}

/*******************************************************************************
* Function Name: setValve2OFF
********************************************************************************
*
* Summary:
*  Turns off valve 2 (connector J10 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/
void setValve2OFF(void){
	ON1_DIR2_Write(0u);
	ON2_DIR1_Write(0u);
}

/*******************************************************************************
* Function Name: setValve3OFF
********************************************************************************
*
* Summary:
*  Turns off valve 3 (connector J8 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/
void setValve3OFF(void){
    ON3_DIR1_Write(0u);
    ON4_DIR2_Write(0u);
}
/*******************************************************************************
* Function Name: setValve4OFF
********************************************************************************
*
* Summary:
*  Turns off valve 4 (connector J10 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/
void setValve4OFF(void){
    ON3_DIR2_Write(0u);
    ON4_DIR1_Write(0u);
}
/*******************************************************************************
* Function Name: setValve5OFF
********************************************************************************
*
* Summary:
*  Turns off valve 1 (connector J6 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/
/*void setValve5OFF(void){
    ON5_DIR1_Write(0u);
    ON6_DIR2_Write(0u);
}*/
/*******************************************************************************
* Function Name: setValve6OFF
********************************************************************************
*
* Summary:
*  Turns off valve 1 (connector J7 on Water Control Atom.)
*
* Parameters:
* None
*
* Return:
*  None.
*
*******************************************************************************/
/*void setValve6OFF(void){
    ON5_DIR2_Write(0u);
    ON6_DIR1_Write(0u);
}*/


    sc_integer PressureSensor1_Read(void){
        int ADC_Val=0;
        if((ADC_IsEndConversion(ADC_RETURN_STATUS)!=0)){
            ADC_Val = ADC_GetResult16(0);
        }
       return ADC_Val; 
    }
    sc_integer PressureSensor2_Read(void){
         int ADC_Val=0;
        if((ADC_IsEndConversion(ADC_RETURN_STATUS)!=0)){
            ADC_Val = ADC_GetResult16(1);
        }
       return ADC_Val; 
    }
    
    sc_integer FlowSensor1_Read(void){
        int flowSensor1 = Counter_ReadCounter();
        Counter_WriteCounter(0);
        return flowSensor1;
    }



/* [] END OF FILE */

