/* ========================================
 *
 * Copyright Thaumatec, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Thaumatec.
 *
 * ========================================
*/
#if !defined(CY_RS485_Atom_`$INSTANCE_NAME`_H)
#define CY_RS485_Atom_`$INSTANCE_NAME`_H

#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
  
#define `$INSTANCE_NAME`_IS_ARBITER `$IsArbiter`
  
typedef void (* `$INSTANCE_NAME`_error_callback) ( int line );
void `$INSTANCE_NAME`_SetCallbackOnError(
    `$INSTANCE_NAME`_error_callback callback
);

typedef void (* `$INSTANCE_NAME`_wake_callback) (uint8 isWake);
void `$INSTANCE_NAME`_SetCallbackOnWake(
    `$INSTANCE_NAME`_wake_callback callback
);


  /* `$INSTANCE_NAME`_return code enum
   *
   *  SUCCESS - returned when call finished with success
   *  FAIL - returned when call failed 
   *  FORBIDDEN - returned when function called in invalid internal state,
   *      user should not seen this error if API is used correctly
   */
typedef enum {
    `$INSTANCE_NAME`_SUCCESS = 0,
    `$INSTANCE_NAME`_FAIL,
    `$INSTANCE_NAME`_FORBIDDEN,

#if `$INSTANCE_NAME`_IS_ARBITER
    `$INSTANCE_NAME`_OUT_OF_SPACE
#endif
} `$INSTANCE_NAME`_return_code;
   
  /* `$INSTANCE_NAME`_address typedef, special typedef for Atom address
   *
   *
   */
typedef uint32 `$INSTANCE_NAME`_address;

  /* `$INSTANCE_NAME`_receive_callback typedef callback
   */
typedef void (* `$INSTANCE_NAME`_receive_callback) (
    char * buffer,
    uint32 len
);

  /*
   * `$INSTANCE_NAME`_frame_sent typedef callback
   * called after sending frame
   */
typedef void (* `$INSTANCE_NAME`_frame_sent_callback) (
	char * buff,
	uint32 len
);

  /* `$INSTANCE_NAME`_bus_granted_callback
   * called when Atom receives ARB_GRANTED packet
   *
   * After this callback SelectSlave i ReleaseBus calls are allowed
   */
typedef void (* `$INSTANCE_NAME`_bus_granted_callback) (void);

  /* `$INSTANCE_NAME`_bus_released_callback
   * called when Atom released bus and is back in listening state
   *
   * After this callback RequestBus
   */
typedef void (* `$INSTANCE_NAME`_bus_released_callback) (void);

  /* `$INSTANCE_NAME`_slave_selected_callback
   *  called when slave_selecting process is completed
   *
   * After this callback SendFrame and ReleaseSlave calls are allowed
   */
typedef void (* `$INSTANCE_NAME`_slave_selected_callback) (void);

  /* `$INSTANCE_NAME`_slave_relseased_callback
   *  called when slave_releasing process is completed
   *
   * After this callback SelectSlave and ReleaseBus calls are allowed
   */
typedef void (* `$INSTANCE_NAME`_slave_released_callback) (void);

  /* `$INSTANCE_NAME`_selected_as_slave
   * called when current master selects this device as its slave
   * 
   * from this moment only SendFrame as reaction to SlaveReceiveCallback
   * is allowed until released as slave callback
   */
typedef void (* `$INSTANCE_NAME`_selected_as_slave) (
    `$INSTANCE_NAME`_address byWhoAddress
);

/* `$INSTANCE_NAME`_released_as_slave
   * called when current master releases this device as its slave
   */
typedef void (* `$INSTANCE_NAME`_released_as_slave) (void);

/***********************************************************
 * FUNCTIONS API
 ***********************************************************/

  /* `$INSTANCE_NAME`_Init
   * Initializes component
   */
void `$INSTANCE_NAME`_Init(void);


  /* Set Callback functions set */

void `$INSTANCE_NAME`_SetCallbackOnSelectedAsSlave(
    `$INSTANCE_NAME`_selected_as_slave callback
);


void `$INSTANCE_NAME`_SetCallbackOnReleasedAsSlave(
    `$INSTANCE_NAME`_released_as_slave callback
);

void `$INSTANCE_NAME`_SetCallbackOnSlaveReceive(
    `$INSTANCE_NAME`_receive_callback callback,
    char *receiveBuffer,
    uint32 receiveBufferSize
);

void `$INSTANCE_NAME`_SetCallbackOnMasterReceive(
    `$INSTANCE_NAME`_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
);

  /* `$INSTANCE_NAME`_SendFrame
   * Sends bufer over bus, other device is set by previous actions
   * and depends on internal state
   *
   * As master, this function can be called after slave_selected_callback,
   * as slave this function can be called after selected_as_slave callbac,
   * and it should only be called in response to OnSlaveReceive
   */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_SendFrame(
    char * buffer,
    uint32 len,
    `$INSTANCE_NAME`_frame_sent_callback callback
);

  /* `$INSTANCE_NAME`_RequestBus
   * call this function to aquire bus as master,
   * until receiving bus_granted_callback, atom is listening on all events
   * and can be selected as slave by other atom
   */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_RequestBus(
    `$INSTANCE_NAME`_bus_granted_callback callback
);

  /* `$INSTANCE_NAME`_SelectSlave
   * call this function to select slave, call only after bus_granted callback
   */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_SelectSlave(
    `$INSTANCE_NAME`_address slaveAddress,
    `$INSTANCE_NAME`_slave_selected_callback callback
);

  /* `$INSTANCE_NAME`_ReleaseSlave
   * call when communication with slave is finished, after this call, SendFrame
   * function is forbidden, select another slave, or release bus
   */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_ReleaseSlave(
  `$INSTANCE_NAME`_slave_released_callback callback
);

  /* `$INSTANCE_NAME`_ReleaseBus
   * call when finished all communication as Master
   */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_ReleaseBus(
  `$INSTANCE_NAME`_bus_released_callback callback
);


#if `$INSTANCE_NAME`_IS_ARBITER
/*
 * Strict Arbiter functions
 */

`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_AddNode(`$INSTANCE_NAME`_address address);

#endif

#endif /* (CY_RS485_Atom_`$INSTANCE_NAME`_H) */
/* [] END OF FILE */
