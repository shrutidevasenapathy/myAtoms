/*
 * sysTimer.h
 *
 *  Created on: 29 kwi 2015
 *      Author: jakub.piskorz@thaumatec.com
 */

#ifndef SRC_SYSTIMER_H_
#define SRC_SYSTIMER_H_

#include "src-fsm/Fsm.h"

void SysTimer_Init(void);

void SysTimer_FsmHandler(Fsm* handle);


uint32_t SysTimer_GetTicks(void);

#endif /* SRC_SYSTIMER_H_ */
