/*
 * sysTimer.c
 *
 *  Created on: 29 kwi 2015
 *      Author: jakub.piskorz@thaumatec.com
 */

#include <CyLib.h>
#include <core_cm0_psoc4.h>
#include "sysTimer.h"

#define TIME_EVENTS_COUNT (sizeof(FsmTimeEvents)/sizeof(sc_boolean))

static struct _Timers {
	sc_eventid evid;
	uint32_t time_ms;
	uint32_t start;
	sc_boolean periodic;
} timers[TIME_EVENTS_COUNT];

static volatile uint32_t msTicks = 0;

CY_ISR(sys_tick_isr) {
	msTicks++;
}


void SysTimer_Init(void) {
	CyIntSetSysVector( CY_INT_SYSTICK_IRQN, sys_tick_isr );
	SysTick_Config(CYDEV_BCLK__SYSCLK__KHZ);
}

uint32_t SysTimer_GetTicks(void) {
	//this has to be atomic, however 32bit access is atomic
	return msTicks;
}

void fsm_setTimer(Fsm* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic) {
	timers[(((intptr_t)evid) - ((intptr_t)&(handle->timeEvents)))] = (struct _Timers) {
		.evid = evid,
		.time_ms = time_ms,
		.start = msTicks,
		.periodic = periodic
	};
}

void fsm_unsetTimer(Fsm* handle, const sc_eventid evid) {
	timers[(((intptr_t)evid) - ((intptr_t)&(handle->timeEvents)))].evid = 0;
}

void SysTimer_FsmHandler(Fsm* handle) {
	int i;
	uint32 now = msTicks;
	for(i = 0; i < TIME_EVENTS_COUNT; i++) {
		if(timers[i].evid != 0) {
			if(now - timers[i].start >= timers[i].time_ms) {
				//timer fired
				fsm_raiseTimeEvent(handle, timers[i].evid);
				if(timers[i].periodic) {
					timers[i].start = now;
				} else {
					timers[i].evid = 0;
				}
			}
		}
	}
}
