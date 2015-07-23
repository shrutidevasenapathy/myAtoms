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
#if !defined(CY_RS485_Atom_comm_RS485_H)
#define CY_RS485_Atom_comm_RS485_H

#include <cytypes.h>
#include <cydevice_trm.h>
#include <cyfitter.h>
#include <CyLib.h>
  
#define comm_RS485_IS_ARBITER 0
  
typedef void (* comm_RS485_error_callback) ( int line );
void comm_RS485_SetCallbackOnError(
    comm_RS485_error_callback callback
);

typedef void (* comm_RS485_wake_callback) (uint8 isWake);
void comm_RS485_SetCallbackOnWake(
    comm_RS485_wake_callback callback
);


  /* comm_RS485_return code enum
   *
   *  SUCCESS - returned when call finished with success
   *  FAIL - returned when call failed 
   *  FORBIDDEN - returned when function called in invalid internal state,
   *      user should not seen this error if API is used correctly
   */
typedef enum {
    comm_RS485_SUCCESS = 0,
    comm_RS485_FAIL,
    comm_RS485_FORBIDDEN,

#if comm_RS485_IS_ARBITER
    comm_RS485_OUT_OF_SPACE
#endif
} comm_RS485_return_code;
   
  /* comm_RS485_address typedef, special typedef for Atom address
   *
   *
   */
typedef uint32 comm_RS485_address;

  /* comm_RS485_receive_callback typedef callback
   */
typedef void (* comm_RS485_receive_callback) (
    char * buffer,
    uint32 len
);

  /*
   * comm_RS485_frame_sent typedef callback
   * called after sending frame
   */
typedef void (* comm_RS485_frame_sent_callback) (
	char * buff,
	uint32 len
);

  /* comm_RS485_bus_granted_callback
   * called when Atom receives ARB_GRANTED packet
   *
   * After this callback SelectSlave i ReleaseBus calls are allowed
   */
typedef void (* comm_RS485_bus_granted_callback) (void);

  /* comm_RS485_bus_released_callback
   * called when Atom released bus and is back in listening state
   *
   * After this callback RequestBus
   */
typedef void (* comm_RS485_bus_released_callback) (void);

  /* comm_RS485_slave_selected_callback
   *  called when slave_selecting process is completed
   *
   * After this callback SendFrame and ReleaseSlave calls are allowed
   */
typedef void (* comm_RS485_slave_selected_callback) (void);

  /* comm_RS485_slave_relseased_callback
   *  called when slave_releasing process is completed
   *
   * After this callback SelectSlave and ReleaseBus calls are allowed
   */
typedef void (* comm_RS485_slave_released_callback) (void);

  /* comm_RS485_selected_as_slave
   * called when current master selects this device as its slave
   * 
   * from this moment only SendFrame as reaction to SlaveReceiveCallback
   * is allowed until released as slave callback
   */
typedef void (* comm_RS485_selected_as_slave) (
    comm_RS485_address byWhoAddress
);

/* comm_RS485_released_as_slave
   * called when current master releases this device as its slave
   */
typedef void (* comm_RS485_released_as_slave) (void);

/***********************************************************
 * FUNCTIONS API
 ***********************************************************/

  /* comm_RS485_Init
   * Initializes component
   */
void comm_RS485_Init(void);


  /* Set Callback functions set */

void comm_RS485_SetCallbackOnSelectedAsSlave(
    comm_RS485_selected_as_slave callback
);


void comm_RS485_SetCallbackOnReleasedAsSlave(
    comm_RS485_released_as_slave callback
);

void comm_RS485_SetCallbackOnSlaveReceive(
    comm_RS485_receive_callback callback,
    char *receiveBuffer,
    uint32 receiveBufferSize
);

void comm_RS485_SetCallbackOnMasterReceive(
    comm_RS485_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
);

  /* comm_RS485_SendFrame
   * Sends bufer over bus, other device is set by previous actions
   * and depends on internal state
   *
   * As master, this function can be called after slave_selected_callback,
   * as slave this function can be called after selected_as_slave callbac,
   * and it should only be called in response to OnSlaveReceive
   */
comm_RS485_return_code comm_RS485_SendFrame(
    char * buffer,
    uint32 len,
    comm_RS485_frame_sent_callback callback
);

  /* comm_RS485_RequestBus
   * call this function to aquire bus as master,
   * until receiving bus_granted_callback, atom is listening on all events
   * and can be selected as slave by other atom
   */
comm_RS485_return_code comm_RS485_RequestBus(
    comm_RS485_bus_granted_callback callback
);

  /* comm_RS485_SelectSlave
   * call this function to select slave, call only after bus_granted callback
   */
comm_RS485_return_code comm_RS485_SelectSlave(
    comm_RS485_address slaveAddress,
    comm_RS485_slave_selected_callback callback
);

  /* comm_RS485_ReleaseSlave
   * call when communication with slave is finished, after this call, SendFrame
   * function is forbidden, select another slave, or release bus
   */
comm_RS485_return_code comm_RS485_ReleaseSlave(
  comm_RS485_slave_released_callback callback
);

  /* comm_RS485_ReleaseBus
   * call when finished all communication as Master
   */
comm_RS485_return_code comm_RS485_ReleaseBus(
  comm_RS485_bus_released_callback callback
);


#if comm_RS485_IS_ARBITER
/*
 * Strict Arbiter functions
 */

comm_RS485_return_code comm_RS485_AddNode(comm_RS485_address address);

#endif

#endif /* (CY_RS485_Atom_comm_RS485_H) */
/* [] END OF FILE */
