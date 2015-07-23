
#ifndef FSM_H_
#define FSM_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'fsm'.
*/

//! enumeration of all states 
typedef enum {
	Fsm_main_region_Sleep,
	Fsm_main_region_Operation,
	Fsm_main_region_Operation_op_Decide,
	Fsm_main_region_Operation_op_ValveOn,
	Fsm_main_region_Operation_op_ValveOff,
	Fsm_main_region_Operation_op_VolumeCheck,
	Fsm_main_region_Operation_op_SendStats,
	Fsm_main_region_TestState,
	Fsm_main_region_TestState_test__final_,
	Fsm_main_region_Idle,
	Fsm_last_state
} FsmStates;

//! Type definition of the data structure for the FsmIfacePlatform interface scope.
typedef struct {
	sc_boolean start_raised;
	sc_boolean test_raised;
	sc_boolean idle_raised;
	sc_boolean timer_raised;
} FsmIfacePlatform;

//! Type definition of the data structure for the FsmIfaceAtom interface scope.
typedef struct {
} FsmIfaceAtom;

//! Type definition of the data structure for the FsmIfaceWaterControl interface scope.
typedef struct {
	sc_integer maxVolume;
	sc_integer currentVolume;
	sc_integer opMode;
} FsmIfaceWaterControl;

//! Type definition of the data structure for the FsmTimeEvents interface scope.
typedef struct {
	sc_boolean fsm_main_region_Operation_op_SendStats_tev0_raised;
} FsmTimeEvents;


//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
#define FSM_MAX_ORTHOGONAL_STATES 1

/*! Type definition of the data structure for the Fsm state machine.
This data structure has to be allocated by the client code. */
typedef struct {
	FsmStates stateConfVector[FSM_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	FsmIfacePlatform ifacePlatform;
	FsmIfaceAtom ifaceAtom;
	FsmIfaceWaterControl ifaceWaterControl;
	FsmTimeEvents timeEvents;
} Fsm;

/*! Initializes the Fsm state machine data structures. Must be called before first usage.*/
extern void fsm_init(Fsm* handle);

/*! Activates the state machine */
extern void fsm_enter(Fsm* handle);

/*! Deactivates the state machine */
extern void fsm_exit(Fsm* handle);

/*! Performs a 'run to completion' step. */
extern void fsm_runCycle(Fsm* handle);

/*! Raises a time event. */
extern void fsm_raiseTimeEvent(Fsm* handle, sc_eventid evid);

/*! Raises the in event 'start' that is defined in the interface scope 'Platform'. */ 
extern void fsmIfacePlatform_raise_start(Fsm* handle);

/*! Raises the in event 'test' that is defined in the interface scope 'Platform'. */ 
extern void fsmIfacePlatform_raise_test(Fsm* handle);

/*! Raises the in event 'idle' that is defined in the interface scope 'Platform'. */ 
extern void fsmIfacePlatform_raise_idle(Fsm* handle);

/*! Raises the in event 'timer' that is defined in the interface scope 'Platform'. */ 
extern void fsmIfacePlatform_raise_timer(Fsm* handle);



/*! Gets the value of the variable 'maxVolume' that is defined in the interface scope 'waterControl'. */ 
extern sc_integer fsmIfaceWaterControl_get_maxVolume(Fsm* handle);
/*! Sets the value of the variable 'maxVolume' that is defined in the interface scope 'waterControl'. */ 
extern void fsmIfaceWaterControl_set_maxVolume(Fsm* handle, sc_integer value);
/*! Gets the value of the variable 'currentVolume' that is defined in the interface scope 'waterControl'. */ 
extern sc_integer fsmIfaceWaterControl_get_currentVolume(Fsm* handle);
/*! Sets the value of the variable 'currentVolume' that is defined in the interface scope 'waterControl'. */ 
extern void fsmIfaceWaterControl_set_currentVolume(Fsm* handle, sc_integer value);
/*! Gets the value of the variable 'opMode' that is defined in the interface scope 'waterControl'. */ 
extern sc_integer fsmIfaceWaterControl_get_opMode(Fsm* handle);
/*! Sets the value of the variable 'opMode' that is defined in the interface scope 'waterControl'. */ 
extern void fsmIfaceWaterControl_set_opMode(Fsm* handle, sc_integer value);


/*! Checks if the specified state is active. */
extern sc_boolean fsm_isActive(Fsm* handle, FsmStates state);

#ifdef __cplusplus
}
#endif 

#endif /* FSM_H_ */
