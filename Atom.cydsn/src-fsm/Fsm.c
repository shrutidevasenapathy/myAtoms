
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "Fsm.h"
#include "FsmRequired.h"
/*! \file Implementation of the state machine 'fsm'
*/

// prototypes of all internal functions

static void fsm_enact_SequenceImpl(Fsm* handle);
static void fsm_exact_SequenceImpl(Fsm* handle);
static void fsm_react_main_region_Sleep(Fsm* handle);
static void fsm_react_main_region_Operation_op_Decide(Fsm* handle);
static void fsm_react_main_region_Operation_op_ValveOn(Fsm* handle);
static void fsm_react_main_region_Operation_op_ValveOff(Fsm* handle);
static void fsm_react_main_region_Operation_op_VolumeCheck(Fsm* handle);
static void fsm_react_main_region_Operation_op_SendStats(Fsm* handle);
static void fsm_react_main_region_TestState_test__final_(Fsm* handle);
static void fsm_react_main_region_Idle(Fsm* handle);
static void fsm_clearInEvents(Fsm* handle);
static void fsm_clearOutEvents(Fsm* handle);


void fsm_init(Fsm* handle)
{
	int i;

	for (i = 0; i < FSM_MAX_ORTHOGONAL_STATES; ++i)
		handle->stateConfVector[i] = Fsm_last_state;
	
	
	handle->stateConfVectorPosition = 0;

	fsm_clearInEvents(handle);
	fsm_clearOutEvents(handle);

	/* Default init sequence for statechart fsm */
	handle->ifaceWaterControl.maxVolume = 0;
	handle->ifaceWaterControl.currentVolume = 0;
	handle->ifaceWaterControl.opMode = 0;

}

void fsm_enter(Fsm* handle)
{
	/* Default enter sequence for statechart fsm */
	fsm_enact_SequenceImpl(handle);
	/* 'default' enter sequence for region main region */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Operation */
	/* Entry action for state 'Operation'. */
	fsmIfaceWaterControl_setExpTime();
	/* 'default' enter sequence for region op */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Decide */
	/* Entry action for state 'Decide'. */
	handle->ifaceWaterControl.opMode = fsmIfaceWaterControl_getOpMode();
	handle->stateConfVector[0] = Fsm_main_region_Operation_op_Decide;
	handle->stateConfVectorPosition = 0;
}

void fsm_exit(Fsm* handle)
{
	/* Default exit sequence for statechart fsm */
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of main region) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case Fsm_main_region_Sleep : {
			/* Default exit sequence for state Sleep */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			/* Exit action for state 'Sleep'. */
			fsmIfacePlatform_resume();
			break;
		}
		case Fsm_main_region_Operation_op_Decide : {
			/* Default exit sequence for state Decide */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case Fsm_main_region_Operation_op_ValveOn : {
			/* Default exit sequence for state ValveOn */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case Fsm_main_region_Operation_op_ValveOff : {
			/* Default exit sequence for state ValveOff */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case Fsm_main_region_Operation_op_VolumeCheck : {
			/* Default exit sequence for state VolumeCheck */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case Fsm_main_region_Operation_op_SendStats : {
			/* Default exit sequence for state SendStats */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			/* Exit action for state 'SendStats'. */
			fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
			break;
		}
		case Fsm_main_region_TestState_test__final_ : {
			/* Default exit sequence for final state. */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case Fsm_main_region_Idle : {
			/* Default exit sequence for state Idle */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	fsm_exact_SequenceImpl(handle);
}

static void fsm_clearInEvents(Fsm* handle) {
	handle->ifacePlatform.start_raised = bool_false;
	handle->ifacePlatform.test_raised = bool_false;
	handle->ifacePlatform.idle_raised = bool_false;
	handle->ifacePlatform.timer_raised = bool_false;
	handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised = bool_false; 
}

static void fsm_clearOutEvents(Fsm* handle) {
}

void fsm_runCycle(Fsm* handle) {
	
	fsm_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < FSM_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case Fsm_main_region_Sleep : {
			fsm_react_main_region_Sleep(handle);
			break;
		}
		case Fsm_main_region_Operation_op_Decide : {
			fsm_react_main_region_Operation_op_Decide(handle);
			break;
		}
		case Fsm_main_region_Operation_op_ValveOn : {
			fsm_react_main_region_Operation_op_ValveOn(handle);
			break;
		}
		case Fsm_main_region_Operation_op_ValveOff : {
			fsm_react_main_region_Operation_op_ValveOff(handle);
			break;
		}
		case Fsm_main_region_Operation_op_VolumeCheck : {
			fsm_react_main_region_Operation_op_VolumeCheck(handle);
			break;
		}
		case Fsm_main_region_Operation_op_SendStats : {
			fsm_react_main_region_Operation_op_SendStats(handle);
			break;
		}
		case Fsm_main_region_TestState_test__final_ : {
			fsm_react_main_region_TestState_test__final_(handle);
			break;
		}
		case Fsm_main_region_Idle : {
			fsm_react_main_region_Idle(handle);
			break;
		}
		default:
			break;
		}
	}
	
	fsm_clearInEvents(handle);
}

void fsm_raiseTimeEvent(Fsm* handle, sc_eventid evid) {
	if ( ((intptr_t)evid) >= ((intptr_t)&(handle->timeEvents))
		&&  ((intptr_t)evid) < ((intptr_t)&(handle->timeEvents)) + sizeof(FsmTimeEvents)) {
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean fsm_isActive(Fsm* handle, FsmStates state) {
	switch (state) {
		case Fsm_main_region_Sleep : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Sleep
			);
		case Fsm_main_region_Operation : 
			return (sc_boolean) (handle->stateConfVector[0] >= Fsm_main_region_Operation
				&& handle->stateConfVector[0] <= Fsm_main_region_Operation_op_SendStats);
		case Fsm_main_region_Operation_op_Decide : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Operation_op_Decide
			);
		case Fsm_main_region_Operation_op_ValveOn : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Operation_op_ValveOn
			);
		case Fsm_main_region_Operation_op_ValveOff : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Operation_op_ValveOff
			);
		case Fsm_main_region_Operation_op_VolumeCheck : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Operation_op_VolumeCheck
			);
		case Fsm_main_region_Operation_op_SendStats : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Operation_op_SendStats
			);
		case Fsm_main_region_TestState : 
			return (sc_boolean) (handle->stateConfVector[0] >= Fsm_main_region_TestState
				&& handle->stateConfVector[0] <= Fsm_main_region_TestState_test__final_);
		case Fsm_main_region_TestState_test__final_ : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_TestState_test__final_
			);
		case Fsm_main_region_Idle : 
			return (sc_boolean) (handle->stateConfVector[0] == Fsm_main_region_Idle
			);
		default: return bool_false;
	}
}

void fsmIfacePlatform_raise_start(Fsm* handle) {
	handle->ifacePlatform.start_raised = bool_true;
}
void fsmIfacePlatform_raise_test(Fsm* handle) {
	handle->ifacePlatform.test_raised = bool_true;
}
void fsmIfacePlatform_raise_idle(Fsm* handle) {
	handle->ifacePlatform.idle_raised = bool_true;
}
void fsmIfacePlatform_raise_timer(Fsm* handle) {
	handle->ifacePlatform.timer_raised = bool_true;
}






sc_integer fsmIfaceWaterControl_get_maxVolume(Fsm* handle) {
	return handle->ifaceWaterControl.maxVolume;
}
void fsmIfaceWaterControl_set_maxVolume(Fsm* handle, sc_integer value) {
	handle->ifaceWaterControl.maxVolume = value;
}
sc_integer fsmIfaceWaterControl_get_currentVolume(Fsm* handle) {
	return handle->ifaceWaterControl.currentVolume;
}
void fsmIfaceWaterControl_set_currentVolume(Fsm* handle, sc_integer value) {
	handle->ifaceWaterControl.currentVolume = value;
}
sc_integer fsmIfaceWaterControl_get_opMode(Fsm* handle) {
	return handle->ifaceWaterControl.opMode;
}
void fsmIfaceWaterControl_set_opMode(Fsm* handle, sc_integer value) {
	handle->ifaceWaterControl.opMode = value;
}

// implementations of all internal functions

/* Entry action for statechart 'fsm'. */
static void fsm_enact_SequenceImpl(Fsm* handle) {
}

/* Exit action for state 'fsm'. */
static void fsm_exact_SequenceImpl(Fsm* handle) {
}

/* The reactions of state Sleep. */
static void fsm_react_main_region_Sleep(Fsm* handle) {
	/* The reactions of state Sleep. */
	if (handle->ifacePlatform.timer_raised) { 
		/* Default exit sequence for state Sleep */
		handle->stateConfVector[0] = Fsm_last_state;
		handle->stateConfVectorPosition = 0;
		/* Exit action for state 'Sleep'. */
		fsmIfacePlatform_resume();
		/* 'default' enter sequence for state Operation */
		/* Entry action for state 'Operation'. */
		fsmIfaceWaterControl_setExpTime();
		/* 'default' enter sequence for region op */
		/* Default react sequence for initial entry  */
		/* 'default' enter sequence for state Decide */
		/* Entry action for state 'Decide'. */
		handle->ifaceWaterControl.opMode = fsmIfaceWaterControl_getOpMode();
		handle->stateConfVector[0] = Fsm_main_region_Operation_op_Decide;
		handle->stateConfVectorPosition = 0;
	}  else {
		if (handle->ifacePlatform.idle_raised) { 
			/* Default exit sequence for state Sleep */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			/* Exit action for state 'Sleep'. */
			fsmIfacePlatform_resume();
			/* 'default' enter sequence for state Idle */
			handle->stateConfVector[0] = Fsm_main_region_Idle;
			handle->stateConfVectorPosition = 0;
		} 
	}
}

/* The reactions of state Decide. */
static void fsm_react_main_region_Operation_op_Decide(Fsm* handle) {
	/* The reactions of state Decide. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
		/* Default exit sequence for state Decide */
		handle->stateConfVector[0] = Fsm_last_state;
		handle->stateConfVectorPosition = 0;
		/* The reactions of state null. */
		if (handle->ifaceWaterControl.opMode > 0) { 
			/* 'default' enter sequence for state VolumeCheck */
			/* Entry action for state 'VolumeCheck'. */
			handle->ifaceWaterControl.maxVolume = fsmIfaceWaterControl_getMaxVolume();
			handle->ifaceWaterControl.currentVolume = fsmIfaceWaterControl_getCurrentVolume();
			handle->stateConfVector[0] = Fsm_main_region_Operation_op_VolumeCheck;
			handle->stateConfVectorPosition = 0;
		}  else {
			if (handle->ifaceWaterControl.opMode == 0) { 
				/* 'default' enter sequence for state ValveOff */
				/* Entry action for state 'ValveOff'. */
				fsmIfaceWaterControl_valveOff();
				handle->stateConfVector[0] = Fsm_main_region_Operation_op_ValveOff;
				handle->stateConfVectorPosition = 0;
			}  else {
				/* Default exit sequence for state Operation */
				/* Default exit sequence for region op */
				/* Handle exit of all possible states (of op) at position 0... */
				switch(handle->stateConfVector[ 0 ]) {
					case Fsm_main_region_Operation_op_Decide : {
						/* Default exit sequence for state Decide */
						handle->stateConfVector[0] = Fsm_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case Fsm_main_region_Operation_op_ValveOn : {
						/* Default exit sequence for state ValveOn */
						handle->stateConfVector[0] = Fsm_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case Fsm_main_region_Operation_op_ValveOff : {
						/* Default exit sequence for state ValveOff */
						handle->stateConfVector[0] = Fsm_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case Fsm_main_region_Operation_op_VolumeCheck : {
						/* Default exit sequence for state VolumeCheck */
						handle->stateConfVector[0] = Fsm_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case Fsm_main_region_Operation_op_SendStats : {
						/* Default exit sequence for state SendStats */
						handle->stateConfVector[0] = Fsm_last_state;
						handle->stateConfVectorPosition = 0;
						/* Exit action for state 'SendStats'. */
						fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
						break;
					}
					default: break;
				}
				/* 'default' enter sequence for state Sleep */
				/* Entry action for state 'Sleep'. */
				fsmIfacePlatform_sleep();
				handle->stateConfVector[0] = Fsm_main_region_Sleep;
				handle->stateConfVectorPosition = 0;
			}
		}
	}
}

/* The reactions of state ValveOn. */
static void fsm_react_main_region_Operation_op_ValveOn(Fsm* handle) {
	/* The reactions of state ValveOn. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
		/* Default exit sequence for state ValveOn */
		handle->stateConfVector[0] = Fsm_last_state;
		handle->stateConfVectorPosition = 0;
		/* 'default' enter sequence for state SendStats */
		/* Entry action for state 'SendStats'. */
		fsm_setTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) , 2 * 1000, bool_false);
		fsmIfaceWaterControl_sendStats();
		handle->stateConfVector[0] = Fsm_main_region_Operation_op_SendStats;
		handle->stateConfVectorPosition = 0;
	}
}

/* The reactions of state ValveOff. */
static void fsm_react_main_region_Operation_op_ValveOff(Fsm* handle) {
	/* The reactions of state ValveOff. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Sleep */
		/* Entry action for state 'Sleep'. */
		fsmIfacePlatform_sleep();
		handle->stateConfVector[0] = Fsm_main_region_Sleep;
		handle->stateConfVectorPosition = 0;
	}
}

/* The reactions of state VolumeCheck. */
static void fsm_react_main_region_Operation_op_VolumeCheck(Fsm* handle) {
	/* The reactions of state VolumeCheck. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
		/* Default exit sequence for state VolumeCheck */
		handle->stateConfVector[0] = Fsm_last_state;
		handle->stateConfVectorPosition = 0;
		/* The reactions of state null. */
		if (handle->ifaceWaterControl.currentVolume >= handle->ifaceWaterControl.maxVolume) { 
			/* 'default' enter sequence for state ValveOff */
			/* Entry action for state 'ValveOff'. */
			fsmIfaceWaterControl_valveOff();
			handle->stateConfVector[0] = Fsm_main_region_Operation_op_ValveOff;
			handle->stateConfVectorPosition = 0;
		}  else {
			if (handle->ifaceWaterControl.currentVolume < handle->ifaceWaterControl.maxVolume) { 
				/* 'default' enter sequence for state ValveOn */
				/* Entry action for state 'ValveOn'. */
				fsmIfaceWaterControl_valveOn();
				handle->stateConfVector[0] = Fsm_main_region_Operation_op_ValveOn;
				handle->stateConfVectorPosition = 0;
			}  else {
				/* 'default' enter sequence for state SendStats */
				/* Entry action for state 'SendStats'. */
				fsm_setTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) , 2 * 1000, bool_false);
				fsmIfaceWaterControl_sendStats();
				handle->stateConfVector[0] = Fsm_main_region_Operation_op_SendStats;
				handle->stateConfVectorPosition = 0;
			}
		}
	}
}

/* The reactions of state SendStats. */
static void fsm_react_main_region_Operation_op_SendStats(Fsm* handle) {
	/* The reactions of state SendStats. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state Operation */
		/* Default exit sequence for region op */
		/* Handle exit of all possible states (of op) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_Operation_op_Decide : {
				/* Default exit sequence for state Decide */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOn : {
				/* Default exit sequence for state ValveOn */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_ValveOff : {
				/* Default exit sequence for state ValveOff */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_VolumeCheck : {
				/* Default exit sequence for state VolumeCheck */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case Fsm_main_region_Operation_op_SendStats : {
				/* Default exit sequence for state SendStats */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				/* Exit action for state 'SendStats'. */
				fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
		if (handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) { 
			/* Default exit sequence for state SendStats */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			/* Exit action for state 'SendStats'. */
			fsm_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.fsm_main_region_Operation_op_SendStats_tev0_raised) );		
			/* 'default' enter sequence for state Decide */
			/* Entry action for state 'Decide'. */
			handle->ifaceWaterControl.opMode = fsmIfaceWaterControl_getOpMode();
			handle->stateConfVector[0] = Fsm_main_region_Operation_op_Decide;
			handle->stateConfVectorPosition = 0;
		} 
	}
}

/* The reactions of state null. */
static void fsm_react_main_region_TestState_test__final_(Fsm* handle) {
	/* The reactions of state null. */
	if (handle->ifacePlatform.idle_raised) { 
		/* Default exit sequence for state TestState */
		/* Default exit sequence for region test */
		/* Handle exit of all possible states (of test) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case Fsm_main_region_TestState_test__final_ : {
				/* Default exit sequence for final state. */
				handle->stateConfVector[0] = Fsm_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Idle */
		handle->stateConfVector[0] = Fsm_main_region_Idle;
		handle->stateConfVectorPosition = 0;
	}  else {
	}
}

/* The reactions of state Idle. */
static void fsm_react_main_region_Idle(Fsm* handle) {
	/* The reactions of state Idle. */
	if (handle->ifacePlatform.test_raised) { 
		/* Default exit sequence for state Idle */
		handle->stateConfVector[0] = Fsm_last_state;
		handle->stateConfVectorPosition = 0;
		/* 'default' enter sequence for state TestState */
		/* 'default' enter sequence for region test */
		/* Default react sequence for initial entry  */
		/* Default enter sequence for state null */
		handle->stateConfVector[0] = Fsm_main_region_TestState_test__final_;
		handle->stateConfVectorPosition = 0;
	}  else {
		if (handle->ifacePlatform.start_raised) { 
			/* Default exit sequence for state Idle */
			handle->stateConfVector[0] = Fsm_last_state;
			handle->stateConfVectorPosition = 0;
			/* 'default' enter sequence for state Sleep */
			/* Entry action for state 'Sleep'. */
			fsmIfacePlatform_sleep();
			handle->stateConfVector[0] = Fsm_main_region_Sleep;
			handle->stateConfVectorPosition = 0;
		} 
	}
}


