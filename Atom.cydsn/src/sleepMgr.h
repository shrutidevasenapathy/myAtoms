/*
 * sleepMgr.h
 *
 *      Author: jakub.piskorz@thaumatec.com
 */

#ifndef SRC_SLEEPMGR_H_
#define SRC_SLEEPMGR_H_

/*
 * sleep function will go to DeepSleep mode only of DeepSleep was requested, and all Sleep was released,
 * otherwise, it will go to normal Sleep mode
 */

void sleepMgr_sleep(void);

void sleepMgr_requestDeepSleep(void);
void sleepMgr_releaseDeepSleep(void);

void sleepMgr_requestSleep(void);
void sleepMgr_releaseSleep(void);

#endif /* SRC_SLEEPMGR_H_ */
