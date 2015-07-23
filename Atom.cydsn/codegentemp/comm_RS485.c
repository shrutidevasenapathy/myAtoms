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
//#include "comm_RS485_Atom.h"
#include <project.h>


typedef enum {
	comm_RS485_SLEEPING,
#if comm_RS485_IS_ARBITER
  comm_RS485_ARBITRING,
#else
  comm_RS485_MASTER_RELEASING_BUS,
#endif

	comm_RS485_LISTENING,
	comm_RS485_SELECTING_AS_SLAVE,
	comm_RS485_SLAVE_OP,

	comm_RS485_MASTER_CHOOSING_SLAVE,
	comm_RS485_MASTER_OP,
	comm_RS485_MASTER_RELEASING_SLAVE,



} comm_RS485_state;


#define comm_RS485_ASSERT_WAKE() CyPins_ClearPin(comm_RS485_WAKE_0)
#define comm_RS485_RELEASE_WAKE() CyPins_SetPin(comm_RS485_WAKE_0)
#define comm_RS485_IS_WAKE_ASSERTED() (!comm_RS485_WAKE_ReadDataReg())

#define comm_RS485_TRANSCEIVER_TX_EN() \
  do { CyPins_SetPin(comm_RS485_DE_0); \
       CyPins_SetPin(comm_RS485_nRE_0); \
       comm_RS485_UART_DISABLE_INTR_RX(comm_RS485_UART_INTR_RX_NOT_EMPTY); } while(0)

#define comm_RS485_TRANSCEIVER_RX_EN() \
  do { CyPins_ClearPin(comm_RS485_DE_0); \
       CyPins_ClearPin(comm_RS485_nRE_0); \
       comm_RS485_UART_SpiUartClearRxBuffer(); \
       comm_RS485_UART_ENABLE_INTR_RX(comm_RS485_UART_INTR_RX_NOT_EMPTY); } while(0)

#define comm_RS485_TRANSCEIVER_SHUTDOWN() \
  do { CyPins_ClearPin(comm_RS485_DE_0); \
       CyPins_SetPin(comm_RS485_nRE_0); \
       comm_RS485_UART_SpiUartClearRxBuffer(); \
       comm_RS485_UART_DISABLE_INTR_RX(comm_RS485_UART_INTR_RX_NOT_EMPTY);} while(0)
      
#define comm_RS485_START_TIMEOUT() \
  do { comm_RS485_Timeout_WriteCounter(100); \
       comm_RS485_Timeout_Enable(); } while(0)
#define comm_RS485_STOP_TIMEOUT() \
  do { comm_RS485_Timeout_Stop(); } while(0)

static struct {
  comm_RS485_selected_as_slave selectedAsSlave;
  comm_RS485_released_as_slave releasedAsSlave;
  comm_RS485_receive_callback slaveReceive;
  comm_RS485_receive_callback masterReceive;
  //
  comm_RS485_bus_granted_callback busGranted;
  comm_RS485_bus_released_callback busReleased;
  comm_RS485_frame_sent_callback frameSent;
  comm_RS485_slave_selected_callback slaveSelected;
  comm_RS485_slave_released_callback slaveReleased;
  //
  comm_RS485_error_callback error;
  comm_RS485_wake_callback wake;
} callbacks = {
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL
};

#define ERROR_CB() do {if(callbacks.error) callbacks.error(__LINE__);}while(0)

static struct {
	char * buff;
	uint32 pos;
	uint32 size;
} slaveBuff, masterBuff, txBuff;

#if comm_RS485_IS_ARBITER
#define comm_RS485_OWN_ADDRESS comm_RS485_Protocol_ARB_ADDRESS
#define comm_RS485_MAX_NODEDB_SIZE 8
#else
#define comm_RS485_OWN_ADDRESS 176
#endif

static comm_RS485_state state = comm_RS485_SLEEPING;
static volatile comm_RS485_address otherEndAddress;




#if comm_RS485_IS_ARBITER
  
static struct {
	comm_RS485_address list[comm_RS485_MAX_NODEDB_SIZE];
	uint8 size;
} nodeDB = {.size = 0}; 
  
static void nextArbitrationStep(void) {
	static uint8 currentNodeDBIndex = 0;
	if(currentNodeDBIndex == nodeDB.size)
		currentNodeDBIndex = 0;

	//check if we want the bus
	if(comm_RS485_IS_WAKE_ASSERTED()) {
		//we want it!
		state = comm_RS485_MASTER_CHOOSING_SLAVE;
		if(callbacks.busGranted)
			callbacks.busGranted();

		return;
	}

  CyGlobalIntDisable;
	comm_RS485_TRANSCEIVER_TX_EN();
	//prepare ARB_REQ packet
	comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | nodeDB.list[currentNodeDBIndex];
	comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_ARB_REQ;
	comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
  CyGlobalIntEnable;


	currentNodeDBIndex++;
}
#endif

//TODO two dispatch functions may be merged?
static void dispatchReceivedByteInMasterOp(uint32 byte) {
	static enum {
		RECV_MARK_BYTE,
		RECV_NORMAL
	} internalState = RECV_NORMAL;
	if(byte & comm_RS485_UART_UART_MP_MARK) {
		internalState = RECV_MARK_BYTE;
		return;
	}
	switch(internalState) {
	case RECV_NORMAL:
		if(masterBuff.pos == masterBuff.size) {
			//TODO error report!
      ERROR_CB();
		} else {
      masterBuff.buff[masterBuff.pos++] = byte;
    }
	break;
	case RECV_MARK_BYTE:
		internalState = RECV_NORMAL;
		switch( (comm_RS485_Protocol_frame_type) byte) {
		case comm_RS485_Protocol_EOF:
			callbacks.masterReceive(masterBuff.buff, masterBuff.pos);
			masterBuff.pos = 0;
		break;
    default:
        //TODO error report?
        ERROR_CB();
    break;
		}
	break;
	}
}

static void dispatchReceivedByteInSlaveOp(uint32 byte) {
	static enum {
		RECV_MARK_BYTE,
		RECV_NORMAL
	} internalState = RECV_NORMAL;
	if(byte & comm_RS485_UART_UART_MP_MARK) {
		internalState = RECV_MARK_BYTE;
		return;
	}
	switch(internalState) {
	case RECV_NORMAL:
		if(slaveBuff.pos == slaveBuff.size) {
			//TODO error report
      ERROR_CB();
		} else {
      slaveBuff.buff[slaveBuff.pos++] = byte;
    }
	break;
	case RECV_MARK_BYTE:
		internalState = RECV_NORMAL;
		switch( (comm_RS485_Protocol_frame_type) byte) {
		case comm_RS485_Protocol_EOF:
			//TODO check if callback is set
			callbacks.slaveReceive(slaveBuff.buff, slaveBuff.pos);
			slaveBuff.pos = 0;
		break;
		case comm_RS485_Protocol_DONE:
			state = comm_RS485_LISTENING;
			if(callbacks.releasedAsSlave)
				callbacks.releasedAsSlave();
		break;
        default:
            //TODO error report?
            ERROR_CB();
        break;
		}
	break;
	}
}


static uint32_t rx_counter_helper = 0;
static comm_RS485_Protocol_frame_type rx_frame_type_helper;

CY_ISR(comm_RS485_Uart_isr) {
	uint32 tmp;
  if(comm_RS485_UART_CHECK_INTR_RX_MASKED(comm_RS485_UART_INTR_RX_NOT_EMPTY)) {
    switch(state) {
#if comm_RS485_IS_ARBITER
    case comm_RS485_ARBITRING:
    	//in this state i can receive only ARB_ACK or ARB_NACK
		tmp = comm_RS485_UART_RX_FIFO_RD_REG;
		if(tmp == (comm_RS485_UART_UART_MP_MARK | comm_RS485_OWN_ADDRESS)) {
			//start of frame!
			rx_counter_helper = 1;
			break;
		}
		if(rx_counter_helper == 1) {
			rx_frame_type_helper = tmp;
			rx_counter_helper = 2;
			break;
		}
		if(rx_counter_helper == 2) {
			otherEndAddress = tmp;
			rx_counter_helper = 0;

            comm_RS485_STOP_TIMEOUT();

            comm_RS485_UART_SpiUartClearRxBuffer();

            switch(rx_frame_type_helper) {
      				case comm_RS485_Protocol_ARB_ACK:
      					//we have device interested in mastering
      					//soo send GRANTED
              
              
      		      
      		            
      		      state = comm_RS485_LISTENING;
              
                CyGlobalIntDisable;
                comm_RS485_TRANSCEIVER_TX_EN();

                comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
                comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_ARB_GRANTED;
                comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
                CyGlobalIntEnable;

      					break;
      				case comm_RS485_Protocol_ARB_NACK:
      					//device is not interested in mastering
      					//next
      					nextArbitrationStep();
      				default:
                ERROR_CB();
      					break;
      			}
        }
    	break;
#endif
#if comm_RS485_IS_ARBITER
    case comm_RS485_LISTENING:
    	//here i can receive NORMAL frame when selected as slave, or ARB_DONE as bus relesae indicator
		tmp = comm_RS485_UART_RX_FIFO_RD_REG;
		if(tmp == (comm_RS485_UART_UART_MP_MARK | comm_RS485_OWN_ADDRESS)) {
			//start of frame!
			rx_counter_helper = 1;
			break;
		}
		if(rx_counter_helper == 1) {
			rx_frame_type_helper = tmp;
			rx_counter_helper = 2;
			break;
		}
		if(rx_counter_helper == 2) {
			otherEndAddress = tmp;
			rx_counter_helper = 0;


			comm_RS485_UART_SpiUartClearRxBuffer();

			switch (rx_frame_type_helper) {
				case comm_RS485_Protocol_ARB_DONE:
					//is wake asserted? it should be if we still here...
					state = comm_RS485_ARBITRING;
					nextArbitrationStep();
					break;
				case comm_RS485_Protocol_NORMAL:
					//if we receivied this message, we were selected as slave
		        	
		            //we were selected as slave device!
		            state = comm_RS485_SELECTING_AS_SLAVE;

                CyGlobalIntDisable;
                comm_RS485_TRANSCEIVER_TX_EN();
		            comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
		            comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_NORMAL;
		            comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
                CyGlobalIntEnable;
					break;
				default:
					break;
			}
    	}
    break;
#else
    case comm_RS485_LISTENING:
        //in this state i can receive only control message ARG_REQ or NORMAL,
    	// or for master arb ARB_GRANTED
		tmp = comm_RS485_UART_RX_FIFO_RD_REG;
		if(tmp == (comm_RS485_UART_UART_MP_MARK | comm_RS485_OWN_ADDRESS)) {
			//start of frame!
			rx_counter_helper = 1;
			break;
		}
		if(rx_counter_helper == 1) {
			rx_frame_type_helper = tmp;
			rx_counter_helper = 2;
			break;
		}
		if(rx_counter_helper == 2) {
			otherEndAddress = tmp;
			rx_counter_helper = 0;


        comm_RS485_UART_SpiUartClearRxBuffer();
        
        switch(rx_frame_type_helper) {
          case comm_RS485_Protocol_ARB_REQ:
          
            CyGlobalIntDisable;
        	  comm_RS485_TRANSCEIVER_TX_EN();

            comm_RS485_UART_TX_FIFO_WR_REG =
              comm_RS485_UART_UART_MP_MARK | otherEndAddress;
            comm_RS485_UART_TX_FIFO_WR_REG =
               comm_RS485_IS_WAKE_ASSERTED() ? comm_RS485_Protocol_ARB_ACK : comm_RS485_Protocol_ARB_NACK;
            comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
            CyGlobalIntEnable;
          break;
          case comm_RS485_Protocol_ARB_GRANTED:
        	  state = comm_RS485_MASTER_CHOOSING_SLAVE;
        	  if(callbacks.busGranted)
        		  callbacks.busGranted();
          break;
          case comm_RS485_Protocol_NORMAL:
        	
            //we were selected as slave device!
            state = comm_RS485_SELECTING_AS_SLAVE;
          
            CyGlobalIntDisable;
            comm_RS485_TRANSCEIVER_TX_EN();
            comm_RS485_UART_TX_FIFO_WR_REG =
              comm_RS485_UART_UART_MP_MARK | otherEndAddress;
            comm_RS485_UART_TX_FIFO_WR_REG =
              comm_RS485_Protocol_NORMAL;
            comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
            CyGlobalIntEnable;
          break;
          default:
            //this should not happen...
          break;
        }
        
      }
    break;
#endif
    case comm_RS485_MASTER_CHOOSING_SLAVE:
  	  //wait for enough data in RX fifo
		tmp = comm_RS485_UART_RX_FIFO_RD_REG;
		if(tmp == (comm_RS485_UART_UART_MP_MARK | comm_RS485_OWN_ADDRESS)) {
			//start of frame!
			rx_counter_helper = 1;
			break;
		}
		if(rx_counter_helper == 1) {
			rx_frame_type_helper = tmp;
			rx_counter_helper = 2;
			break;
		}
		if(rx_counter_helper == 2) {
			otherEndAddress = tmp;
			rx_counter_helper = 0;

			comm_RS485_STOP_TIMEOUT();

			comm_RS485_UART_SpiUartClearRxBuffer();

			switch(rx_frame_type_helper) {
			case comm_RS485_Protocol_NORMAL:
			  //slave selected sucessfully
			  state = comm_RS485_MASTER_OP;
			  if(callbacks.slaveSelected)
				  callbacks.slaveSelected();
			break;
			default:
			  //TODO should never happen!
			ERROR_CB();
			break;
			}
  	  }
  	  break;
    case comm_RS485_SLAVE_OP:
		while(0 != comm_RS485_UART_GET_RX_FIFO_ENTRIES) {
			dispatchReceivedByteInSlaveOp(comm_RS485_UART_RX_FIFO_RD_REG);
		}
		break;
    case comm_RS485_MASTER_OP:
		while(0 != comm_RS485_UART_GET_RX_FIFO_ENTRIES) {
		  dispatchReceivedByteInMasterOp(comm_RS485_UART_RX_FIFO_RD_REG);
		}
		break;
    default:
        //TODO error report?
        ERROR_CB();
        //clear wrong received bytes, this somehow happen when we are in
        //TX mode
        //TODO find out why!
        comm_RS485_UART_SpiUartClearRxBuffer();
    break;
    }

    comm_RS485_UART_ClearRxInterruptSource(comm_RS485_UART_INTR_RX_NOT_EMPTY);
  }

  if(comm_RS485_UART_CHECK_INTR_TX_MASKED(comm_RS485_UART_INTR_TX_UART_DONE)) {
    comm_RS485_TRANSCEIVER_RX_EN();

    switch(state) {
#if comm_RS485_IS_ARBITER
    case comm_RS485_ARBITRING:
    	//nothing special, we sent ARB_REQ
      comm_RS485_START_TIMEOUT();
  	break;
#else 
    case comm_RS485_MASTER_RELEASING_BUS:
  	  //we sent release bus, change state
  	  state = comm_RS485_LISTENING;
  	  comm_RS485_RELEASE_WAKE();
      if(callbacks.busReleased)
        callbacks.busReleased();
    break; 
#endif
    case comm_RS485_LISTENING:
#if comm_RS485_IS_ARBITER
    	//nothing special, we sent ARB_GRANTED
#else
      //nothing special happnd, we sent ARB_NACK or ARB_ACK successfuly
#endif
    break;
    case comm_RS485_MASTER_CHOOSING_SLAVE:
		//we sent selectSlave request, work is done here
      comm_RS485_START_TIMEOUT();
		break;
    case comm_RS485_SELECTING_AS_SLAVE:
		state = comm_RS485_SLAVE_OP;
		  //sent response for being selected as slave, time for callback
		  if(callbacks.selectedAsSlave)
			callbacks.selectedAsSlave(otherEndAddress);
		break;
    case comm_RS485_MASTER_RELEASING_SLAVE:
  		//we sent release req, change state
  		state = comm_RS485_MASTER_CHOOSING_SLAVE;
      if(callbacks.slaveReleased)
        callbacks.slaveReleased();
		break;
    case comm_RS485_MASTER_OP:
    case comm_RS485_SLAVE_OP:
  		//send frame transfer is over, inform about it
  		if(callbacks.frameSent)
  			callbacks.frameSent(txBuff.buff, txBuff.size);
		break;

    default:
        //TODO error report?
        ERROR_CB();
    break;
    }

    comm_RS485_UART_ClearTxInterruptSource(comm_RS485_UART_INTR_TX_UART_DONE);
  }

  if(comm_RS485_UART_CHECK_INTR_TX_MASKED(comm_RS485_UART_INTR_TX_NOT_FULL)) {
	  while(comm_RS485_UART_SPI_UART_FIFO_SIZE != comm_RS485_UART_GET_TX_FIFO_ENTRIES) {
		  if(txBuff.pos == txBuff.size) {
			  //end of message, add EOF mark
			  while((comm_RS485_UART_SPI_UART_FIFO_SIZE - comm_RS485_UART_GET_TX_FIFO_ENTRIES) < 2) {
				  //wait until there is 2 byte space in tx fifo (shouldnt take long!)
			  }
			  //add EOF mark
			  comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
			  comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_EOF;
			  //disable TX_NOT_FULL IRQ
			  comm_RS485_UART_DISABLE_INTR_TX(comm_RS485_UART_INTR_TX_NOT_FULL);
			  break;
		  } else {
			  comm_RS485_UART_TX_FIFO_WR_REG = txBuff.buff[txBuff.pos++];
		  }
	  }

	  comm_RS485_UART_ClearTxInterruptSource(comm_RS485_UART_INTR_TX_NOT_FULL);
  }

}

CY_ISR(comm_RS485_Wake_isr) {
  if(comm_RS485_WAKE_ClearInterrupt()) { //checks irq status
    if(CyPins_ReadPin(comm_RS485_WAKE_0)) {
      //was rising edge
/*      switch(state) {
#if comm_RS485_IS_ARBITER
        case comm_RS485_ARBITRING:
#endif
        case comm_RS485_LISTENING: //is rising edge possible in this state? */
          comm_RS485_Timeout_Sleep();
          comm_RS485_UART_Sleep();
          comm_RS485_TRANSCEIVER_SHUTDOWN();
          state = comm_RS485_SLEEPING;
          if(callbacks.wake)
            callbacks.wake(0);
/*        break;
        default:
            //TODO error report?
            ERROR_CB();
        break;
      }*/
    } else {
      //was falling edge
/*      switch(state) {
        case comm_RS485_SLEEPING:*/
          comm_RS485_TRANSCEIVER_RX_EN();
          comm_RS485_UART_Wakeup();
          comm_RS485_Timeout_Wakeup();
#if comm_RS485_IS_ARBITER
          state = comm_RS485_ARBITRING;
          nextArbitrationStep();
#else
          state = comm_RS485_LISTENING;
#endif
          if(callbacks.wake)
            callbacks.wake(1);
/*        break;
        default:
            //TODO error report?
            ERROR_CB();
        break;
      }*/
    }
  }
}

CY_ISR(comm_RS485_Timeout_isr) {
  comm_RS485_STOP_TIMEOUT();
  ERROR_CB();
  
  switch(state) {
#if comm_RS485_IS_ARBITER
    case comm_RS485_ARBITRING:
      nextArbitrationStep();
    break;
#endif
    case comm_RS485_MASTER_CHOOSING_SLAVE:
      //resend choosing call!
      
      CyGlobalIntDisable;
      comm_RS485_TRANSCEIVER_TX_EN();
  		//send request
  		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
  		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_NORMAL;
  		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
      CyGlobalIntEnable;
		break;
    default:
      ERROR_CB();
    break;
  }
}


#if comm_RS485_IS_ARBITER
comm_RS485_return_code comm_RS485_AddNode(comm_RS485_address address) {
	if(nodeDB.size == comm_RS485_MAX_NODEDB_SIZE)
		return comm_RS485_OUT_OF_SPACE;
	nodeDB.list[nodeDB.size++] = address;
	return comm_RS485_SUCCESS;
}
#endif

void comm_RS485_Init(void) {

  comm_RS485_UART_Start();
  comm_RS485_UART_SetCustomInterruptHandler(comm_RS485_Uart_isr);

  comm_RS485_UART_UartSetRxAddressMask(0xFF);
  comm_RS485_UART_UartSetRxAddress(comm_RS485_OWN_ADDRESS);


  comm_RS485_isr_WAKE_StartEx(comm_RS485_Wake_isr);
  comm_RS485_isr_Timeout_StartEx(comm_RS485_Timeout_isr);
  
  comm_RS485_Timeout_Start();
  comm_RS485_Timeout_Stop();
  comm_RS485_Timeout_Sleep();

  comm_RS485_TRANSCEIVER_SHUTDOWN();
  comm_RS485_UART_Sleep();
}

void comm_RS485_SetCallbackOnWake(
    comm_RS485_wake_callback callback
) {
  callbacks.wake = callback;  
}

void comm_RS485_SetCallbackOnError(
    comm_RS485_error_callback callback
) {
  callbacks.error = callback;  
}

void comm_RS485_SetCallbackOnSelectedAsSlave(
    comm_RS485_selected_as_slave callback
) {
  callbacks.selectedAsSlave = callback;
}

void comm_RS485_SetCallbackOnReleasedAsSlave(
    comm_RS485_released_as_slave callback
) {
  callbacks.releasedAsSlave = callback;
}

void comm_RS485_SetCallbackOnSlaveReceive(
    comm_RS485_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
) {
  callbacks.slaveReceive = callback;
  slaveBuff.buff = receiveBuffer;
  slaveBuff.size = receiveBufferSize;
  slaveBuff.pos = 0;
}

void comm_RS485_SetCallbackOnMasterReceive(
    comm_RS485_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
) {
  callbacks.masterReceive = callback;
  masterBuff.buff = receiveBuffer;
  masterBuff.size = receiveBufferSize;
  masterBuff.pos = 0;
}

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
) {
  switch(state) {
  case comm_RS485_MASTER_OP:
  case comm_RS485_SLAVE_OP:
    comm_RS485_TRANSCEIVER_TX_EN();
	  txBuff.buff = buffer;
	  txBuff.size = len;
	  txBuff.pos = 0;

	  callbacks.frameSent = callback;

	  //enable TX_FIFO_NOTFULL IRQ
	  comm_RS485_UART_ClearTxInterruptSource(comm_RS485_UART_INTR_TX_NOT_FULL);
	  comm_RS485_UART_SpiUartEnableIntTx(
			  comm_RS485_UART_GetTxInterruptMode() | comm_RS485_UART_INTR_TX_NOT_FULL);

	  return comm_RS485_SUCCESS;
  break;
  default:
	  return comm_RS485_FORBIDDEN;
  break;
  }
  return comm_RS485_FAIL; //shouldnt happen, but suppress warning
}
/* comm_RS485_RequestBus
 * call this function to aquire bus as master,
 * until receiving bus_granted_callback, atom is listening on all events
 * and can be selected as slave by other atom
 */
comm_RS485_return_code comm_RS485_RequestBus(
  comm_RS485_bus_granted_callback callback
) {
	callbacks.busGranted = callback;
	comm_RS485_ASSERT_WAKE(); //this should wake up UART if it was sleeping, or do nothing if was
	//already asserted
	return comm_RS485_SUCCESS;
}
/* comm_RS485_SelectSlave
 * call this function to select slave, call only after bus_granted callback
 */
comm_RS485_return_code comm_RS485_SelectSlave(
  comm_RS485_address slaveAddress,
  comm_RS485_slave_selected_callback callback
) {
	switch(state) {
	case comm_RS485_MASTER_CHOOSING_SLAVE:
		

		callbacks.slaveSelected = callback;
		otherEndAddress = slaveAddress;

    CyGlobalIntDisable;
    comm_RS485_TRANSCEIVER_TX_EN();
		//send request
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_NORMAL;
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
    CyGlobalIntEnable;

		return comm_RS485_SUCCESS;
	break;
	default:
		return comm_RS485_FORBIDDEN;
	break;
	}
	return comm_RS485_FAIL;
}

/* comm_RS485_ReleaseSlave
 * call when communication with slave is finished, after this call, SendFrame
 * function is forbidden, select another slave, or release bus
 */
comm_RS485_return_code comm_RS485_ReleaseSlave(
  comm_RS485_slave_released_callback callback
) {
	switch(state) {
	case comm_RS485_MASTER_OP:
    callbacks.slaveReleased = callback;
		state = comm_RS485_MASTER_RELEASING_SLAVE;
    
    CyGlobalIntDisable;
		comm_RS485_TRANSCEIVER_TX_EN();

		//send request
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | otherEndAddress;
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_DONE;
    CyGlobalIntEnable;

		return comm_RS485_SUCCESS;
	break;
	default:
		return comm_RS485_FORBIDDEN;
	break;
	}
	return comm_RS485_FAIL;
}

/* comm_RS485_ReleaseBus
 * call when finished all communication as Master
 */
comm_RS485_return_code comm_RS485_ReleaseBus(
  comm_RS485_bus_released_callback callback
) {
	switch(state) {
	case comm_RS485_MASTER_CHOOSING_SLAVE:
    callbacks.busReleased = callback;
#if comm_RS485_IS_ARBITER
		state = comm_RS485_ARBITRING;
		comm_RS485_isr_WAKE_Disable();

		comm_RS485_RELEASE_WAKE();
    if(callbacks.busReleased)
      callbacks.busReleased();

	    if(CyPins_ReadPin(comm_RS485_WAKE_0)) {
	    	//rising
	    	comm_RS485_isr_WAKE_SetPending();
	    	comm_RS485_isr_WAKE_Enable();
	    } else {
	    	//low level, someone is still holding bus
	    	comm_RS485_isr_WAKE_Enable();
	    	nextArbitrationStep();
	    }
#else
    state = comm_RS485_MASTER_RELEASING_BUS;
  
    CyGlobalIntDisable;
		comm_RS485_TRANSCEIVER_TX_EN();

		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_UART_MP_MARK | comm_RS485_Protocol_ARB_ADDRESS;
		comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_Protocol_ARB_DONE;
    comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_OWN_ADDRESS;
    CyGlobalIntEnable;

#endif
		return comm_RS485_SUCCESS;
	break;
	default:
		return comm_RS485_FORBIDDEN;
	break;
	}
	return comm_RS485_FAIL;
}

/* [] END OF FILE */
