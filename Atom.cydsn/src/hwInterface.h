#ifndef HW_INTERFACE_H
#define HW_INTERFACE_H

#include <project.h>
#include "main.h"

    void hwInterface_Init(void);
    void setValve1ON(bool);
    void setValve2ON(bool);
    void setValve3ON(bool);
    void setValve4ON(bool);
    void setValve5ON(bool);
    void setValve6ON(bool);

    void setValve1OFF(void);
    void setValve2OFF(void);
    void setValve3OFF(void);
    void setValve4OFF(void);
    void setValve5OFF(void);
    void setValve6OFF(void);
    
    sc_integer PressureSensor1_Read(void);
    sc_integer PressureSensor2_Read(void);
    
    sc_integer FlowSensor1_Read(void);
   // sc_integer readflowSensor2(void);
    

#endif