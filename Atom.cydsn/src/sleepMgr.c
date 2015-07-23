/*
 * sleepMgr.c
 *
 *      Author: jakub.piskorz@thaumatec.com
 */

#include "sleepMgr.h"
#include <CyLib.h>
#include <cyPm.h>
#include <core_cm0_psoc4.h>

static volatile uint32 deepSleepRequests = 0;
static volatile uint32 sleepRequests = 0;

void sleepMgr_sleep(void) {
	if(deepSleepRequests != 0 && sleepRequests == 0) {
		CySysPmDeepSleep();
	} else {
		CySysPmSleep();
	}
}

void sleepMgr_requestDeepSleep(void) {
	uint8 interruptState = CyEnterCriticalSection();

	deepSleepRequests++;

	CyExitCriticalSection(interruptState);
}
void sleepMgr_releaseDeepSleep(void) {
	uint8 interruptState = CyEnterCriticalSection();

	if(deepSleepRequests)
		deepSleepRequests--;

	CyExitCriticalSection(interruptState);
}

void sleepMgr_requestSleep(void) {
	uint8 interruptState = CyEnterCriticalSection();

	sleepRequests++;

	CyExitCriticalSection(interruptState);
}
void sleepMgr_releaseSleep(void) {
	uint8 interruptState = CyEnterCriticalSection();

	if(sleepRequests)
		sleepRequests--;

	CyExitCriticalSection(interruptState);
}
