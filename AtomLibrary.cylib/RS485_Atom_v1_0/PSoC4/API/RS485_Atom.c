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
//#include "`$INSTANCE_NAME`_Atom.h"
#include <project.h>


typedef enum {
	`$INSTANCE_NAME`_SLEEPING,
#if `$INSTANCE_NAME`_IS_ARBITER
  `$INSTANCE_NAME`_ARBITRING,
#else
  `$INSTANCE_NAME`_MASTER_RELEASING_BUS,
#endif

	`$INSTANCE_NAME`_LISTENING,
	`$INSTANCE_NAME`_SELECTING_AS_SLAVE,
	`$INSTANCE_NAME`_SLAVE_OP,

	`$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE,
	`$INSTANCE_NAME`_MASTER_OP,
	`$INSTANCE_NAME`_MASTER_RELEASING_SLAVE,



} `$INSTANCE_NAME`_state;


#define `$INSTANCE_NAME`_ASSERT_WAKE() CyPins_ClearPin(`$INSTANCE_NAME`_WAKE_0)
#define `$INSTANCE_NAME`_RELEASE_WAKE() CyPins_SetPin(`$INSTANCE_NAME`_WAKE_0)
#define `$INSTANCE_NAME`_IS_WAKE_ASSERTED() (!`$INSTANCE_NAME`_WAKE_ReadDataReg())

#define `$INSTANCE_NAME`_TRANSCEIVER_TX_EN() \
  do { CyPins_SetPin(`$INSTANCE_NAME`_DE_0); \
       CyPins_SetPin(`$INSTANCE_NAME`_nRE_0); \
       `$INSTANCE_NAME`_UART_DISABLE_INTR_RX(`$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY); } while(0)

#define `$INSTANCE_NAME`_TRANSCEIVER_RX_EN() \
  do { CyPins_ClearPin(`$INSTANCE_NAME`_DE_0); \
       CyPins_ClearPin(`$INSTANCE_NAME`_nRE_0); \
       `$INSTANCE_NAME`_UART_SpiUartClearRxBuffer(); \
       `$INSTANCE_NAME`_UART_ENABLE_INTR_RX(`$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY); } while(0)

#define `$INSTANCE_NAME`_TRANSCEIVER_SHUTDOWN() \
  do { CyPins_ClearPin(`$INSTANCE_NAME`_DE_0); \
       CyPins_SetPin(`$INSTANCE_NAME`_nRE_0); \
       `$INSTANCE_NAME`_UART_SpiUartClearRxBuffer(); \
       `$INSTANCE_NAME`_UART_DISABLE_INTR_RX(`$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY);} while(0)
      
#define `$INSTANCE_NAME`_START_TIMEOUT() \
  do { `$INSTANCE_NAME`_Timeout_WriteCounter(100); \
       `$INSTANCE_NAME`_Timeout_Enable(); } while(0)
#define `$INSTANCE_NAME`_STOP_TIMEOUT() \
  do { `$INSTANCE_NAME`_Timeout_Stop(); } while(0)

static struct {
  `$INSTANCE_NAME`_selected_as_slave selectedAsSlave;
  `$INSTANCE_NAME`_released_as_slave releasedAsSlave;
  `$INSTANCE_NAME`_receive_callback slaveReceive;
  `$INSTANCE_NAME`_receive_callback masterReceive;
  //
  `$INSTANCE_NAME`_bus_granted_callback busGranted;
  `$INSTANCE_NAME`_bus_released_callback busReleased;
  `$INSTANCE_NAME`_frame_sent_callback frameSent;
  `$INSTANCE_NAME`_slave_selected_callback slaveSelected;
  `$INSTANCE_NAME`_slave_released_callback slaveReleased;
  //
  `$INSTANCE_NAME`_error_callback error;
  `$INSTANCE_NAME`_wake_callback wake;
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

#if `$INSTANCE_NAME`_IS_ARBITER
#define `$INSTANCE_NAME`_OWN_ADDRESS `$INSTANCE_NAME`_Protocol_ARB_ADDRESS
#define `$INSTANCE_NAME`_MAX_NODEDB_SIZE `$NodeDBSize`
#else
#define `$INSTANCE_NAME`_OWN_ADDRESS `$Address`
#endif

static `$INSTANCE_NAME`_state state = `$INSTANCE_NAME`_SLEEPING;
static volatile `$INSTANCE_NAME`_address otherEndAddress;




#if `$INSTANCE_NAME`_IS_ARBITER
  
static struct {
	`$INSTANCE_NAME`_address list[`$INSTANCE_NAME`_MAX_NODEDB_SIZE];
	uint8 size;
} nodeDB = {.size = 0}; 
  
static void nextArbitrationStep(void) {
	static uint8 currentNodeDBIndex = 0;
	if(currentNodeDBIndex == nodeDB.size)
		currentNodeDBIndex = 0;

	//check if we want the bus
	if(`$INSTANCE_NAME`_IS_WAKE_ASSERTED()) {
		//we want it!
		state = `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE;
		if(callbacks.busGranted)
			callbacks.busGranted();

		return;
	}

  CyGlobalIntDisable;
	`$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
	//prepare ARB_REQ packet
	`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | nodeDB.list[currentNodeDBIndex];
	`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_ARB_REQ;
	`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
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
	if(byte & `$INSTANCE_NAME`_UART_UART_MP_MARK) {
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
		switch( (`$INSTANCE_NAME`_Protocol_frame_type) byte) {
		case `$INSTANCE_NAME`_Protocol_EOF:
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
	if(byte & `$INSTANCE_NAME`_UART_UART_MP_MARK) {
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
		switch( (`$INSTANCE_NAME`_Protocol_frame_type) byte) {
		case `$INSTANCE_NAME`_Protocol_EOF:
			//TODO check if callback is set
			callbacks.slaveReceive(slaveBuff.buff, slaveBuff.pos);
			slaveBuff.pos = 0;
		break;
		case `$INSTANCE_NAME`_Protocol_DONE:
			state = `$INSTANCE_NAME`_LISTENING;
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
static `$INSTANCE_NAME`_Protocol_frame_type rx_frame_type_helper;

CY_ISR(`$INSTANCE_NAME`_Uart_isr) {
	uint32 tmp;
  if(`$INSTANCE_NAME`_UART_CHECK_INTR_RX_MASKED(`$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY)) {
    switch(state) {
#if `$INSTANCE_NAME`_IS_ARBITER
    case `$INSTANCE_NAME`_ARBITRING:
    	//in this state i can receive only ARB_ACK or ARB_NACK
		tmp = `$INSTANCE_NAME`_UART_RX_FIFO_RD_REG;
		if(tmp == (`$INSTANCE_NAME`_UART_UART_MP_MARK | `$INSTANCE_NAME`_OWN_ADDRESS)) {
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

            `$INSTANCE_NAME`_STOP_TIMEOUT();

            `$INSTANCE_NAME`_UART_SpiUartClearRxBuffer();

            switch(rx_frame_type_helper) {
      				case `$INSTANCE_NAME`_Protocol_ARB_ACK:
      					//we have device interested in mastering
      					//soo send GRANTED
              
              
      		      
      		            
      		      state = `$INSTANCE_NAME`_LISTENING;
              
                CyGlobalIntDisable;
                `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();

                `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
                `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_ARB_GRANTED;
                `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
                CyGlobalIntEnable;

      					break;
      				case `$INSTANCE_NAME`_Protocol_ARB_NACK:
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
#if `$INSTANCE_NAME`_IS_ARBITER
    case `$INSTANCE_NAME`_LISTENING:
    	//here i can receive NORMAL frame when selected as slave, or ARB_DONE as bus relesae indicator
		tmp = `$INSTANCE_NAME`_UART_RX_FIFO_RD_REG;
		if(tmp == (`$INSTANCE_NAME`_UART_UART_MP_MARK | `$INSTANCE_NAME`_OWN_ADDRESS)) {
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


			`$INSTANCE_NAME`_UART_SpiUartClearRxBuffer();

			switch (rx_frame_type_helper) {
				case `$INSTANCE_NAME`_Protocol_ARB_DONE:
					//is wake asserted? it should be if we still here...
					state = `$INSTANCE_NAME`_ARBITRING;
					nextArbitrationStep();
					break;
				case `$INSTANCE_NAME`_Protocol_NORMAL:
					//if we receivied this message, we were selected as slave
		        	
		            //we were selected as slave device!
		            state = `$INSTANCE_NAME`_SELECTING_AS_SLAVE;

                CyGlobalIntDisable;
                `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
		            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
		            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_NORMAL;
		            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
                CyGlobalIntEnable;
					break;
				default:
					break;
			}
    	}
    break;
#else
    case `$INSTANCE_NAME`_LISTENING:
        //in this state i can receive only control message ARG_REQ or NORMAL,
    	// or for master arb ARB_GRANTED
		tmp = `$INSTANCE_NAME`_UART_RX_FIFO_RD_REG;
		if(tmp == (`$INSTANCE_NAME`_UART_UART_MP_MARK | `$INSTANCE_NAME`_OWN_ADDRESS)) {
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


        `$INSTANCE_NAME`_UART_SpiUartClearRxBuffer();
        
        switch(rx_frame_type_helper) {
          case `$INSTANCE_NAME`_Protocol_ARB_REQ:
          
            CyGlobalIntDisable;
        	  `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();

            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG =
              `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG =
               `$INSTANCE_NAME`_IS_WAKE_ASSERTED() ? `$INSTANCE_NAME`_Protocol_ARB_ACK : `$INSTANCE_NAME`_Protocol_ARB_NACK;
            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
            CyGlobalIntEnable;
          break;
          case `$INSTANCE_NAME`_Protocol_ARB_GRANTED:
        	  state = `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE;
        	  if(callbacks.busGranted)
        		  callbacks.busGranted();
          break;
          case `$INSTANCE_NAME`_Protocol_NORMAL:
        	
            //we were selected as slave device!
            state = `$INSTANCE_NAME`_SELECTING_AS_SLAVE;
          
            CyGlobalIntDisable;
            `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG =
              `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG =
              `$INSTANCE_NAME`_Protocol_NORMAL;
            `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
            CyGlobalIntEnable;
          break;
          default:
            //this should not happen...
          break;
        }
        
      }
    break;
#endif
    case `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE:
  	  //wait for enough data in RX fifo
		tmp = `$INSTANCE_NAME`_UART_RX_FIFO_RD_REG;
		if(tmp == (`$INSTANCE_NAME`_UART_UART_MP_MARK | `$INSTANCE_NAME`_OWN_ADDRESS)) {
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

			`$INSTANCE_NAME`_STOP_TIMEOUT();

			`$INSTANCE_NAME`_UART_SpiUartClearRxBuffer();

			switch(rx_frame_type_helper) {
			case `$INSTANCE_NAME`_Protocol_NORMAL:
			  //slave selected sucessfully
			  state = `$INSTANCE_NAME`_MASTER_OP;
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
    case `$INSTANCE_NAME`_SLAVE_OP:
		while(0 != `$INSTANCE_NAME`_UART_GET_RX_FIFO_ENTRIES) {
			dispatchReceivedByteInSlaveOp(`$INSTANCE_NAME`_UART_RX_FIFO_RD_REG);
		}
		break;
    case `$INSTANCE_NAME`_MASTER_OP:
		while(0 != `$INSTANCE_NAME`_UART_GET_RX_FIFO_ENTRIES) {
		  dispatchReceivedByteInMasterOp(`$INSTANCE_NAME`_UART_RX_FIFO_RD_REG);
		}
		break;
    default:
        //TODO error report?
        ERROR_CB();
        //clear wrong received bytes, this somehow happen when we are in
        //TX mode
        //TODO find out why!
        `$INSTANCE_NAME`_UART_SpiUartClearRxBuffer();
    break;
    }

    `$INSTANCE_NAME`_UART_ClearRxInterruptSource(`$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY);
  }

  if(`$INSTANCE_NAME`_UART_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_UART_INTR_TX_UART_DONE)) {
    `$INSTANCE_NAME`_TRANSCEIVER_RX_EN();

    switch(state) {
#if `$INSTANCE_NAME`_IS_ARBITER
    case `$INSTANCE_NAME`_ARBITRING:
    	//nothing special, we sent ARB_REQ
      `$INSTANCE_NAME`_START_TIMEOUT();
  	break;
#else 
    case `$INSTANCE_NAME`_MASTER_RELEASING_BUS:
  	  //we sent release bus, change state
  	  state = `$INSTANCE_NAME`_LISTENING;
  	  `$INSTANCE_NAME`_RELEASE_WAKE();
      if(callbacks.busReleased)
        callbacks.busReleased();
    break; 
#endif
    case `$INSTANCE_NAME`_LISTENING:
#if `$INSTANCE_NAME`_IS_ARBITER
    	//nothing special, we sent ARB_GRANTED
#else
      //nothing special happnd, we sent ARB_NACK or ARB_ACK successfuly
#endif
    break;
    case `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE:
		//we sent selectSlave request, work is done here
      `$INSTANCE_NAME`_START_TIMEOUT();
		break;
    case `$INSTANCE_NAME`_SELECTING_AS_SLAVE:
		state = `$INSTANCE_NAME`_SLAVE_OP;
		  //sent response for being selected as slave, time for callback
		  if(callbacks.selectedAsSlave)
			callbacks.selectedAsSlave(otherEndAddress);
		break;
    case `$INSTANCE_NAME`_MASTER_RELEASING_SLAVE:
  		//we sent release req, change state
  		state = `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE;
      if(callbacks.slaveReleased)
        callbacks.slaveReleased();
		break;
    case `$INSTANCE_NAME`_MASTER_OP:
    case `$INSTANCE_NAME`_SLAVE_OP:
  		//send frame transfer is over, inform about it
  		if(callbacks.frameSent)
  			callbacks.frameSent(txBuff.buff, txBuff.size);
		break;

    default:
        //TODO error report?
        ERROR_CB();
    break;
    }

    `$INSTANCE_NAME`_UART_ClearTxInterruptSource(`$INSTANCE_NAME`_UART_INTR_TX_UART_DONE);
  }

  if(`$INSTANCE_NAME`_UART_CHECK_INTR_TX_MASKED(`$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL)) {
	  while(`$INSTANCE_NAME`_UART_SPI_UART_FIFO_SIZE != `$INSTANCE_NAME`_UART_GET_TX_FIFO_ENTRIES) {
		  if(txBuff.pos == txBuff.size) {
			  //end of message, add EOF mark
			  while((`$INSTANCE_NAME`_UART_SPI_UART_FIFO_SIZE - `$INSTANCE_NAME`_UART_GET_TX_FIFO_ENTRIES) < 2) {
				  //wait until there is 2 byte space in tx fifo (shouldnt take long!)
			  }
			  //add EOF mark
			  `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
			  `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_EOF;
			  //disable TX_NOT_FULL IRQ
			  `$INSTANCE_NAME`_UART_DISABLE_INTR_TX(`$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL);
			  break;
		  } else {
			  `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = txBuff.buff[txBuff.pos++];
		  }
	  }

	  `$INSTANCE_NAME`_UART_ClearTxInterruptSource(`$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL);
  }

}

CY_ISR(`$INSTANCE_NAME`_Wake_isr) {
  if(`$INSTANCE_NAME`_WAKE_ClearInterrupt()) { //checks irq status
    if(CyPins_ReadPin(`$INSTANCE_NAME`_WAKE_0)) {
      //was rising edge
/*      switch(state) {
#if `$INSTANCE_NAME`_IS_ARBITER
        case `$INSTANCE_NAME`_ARBITRING:
#endif
        case `$INSTANCE_NAME`_LISTENING: //is rising edge possible in this state? */
          `$INSTANCE_NAME`_Timeout_Sleep();
          `$INSTANCE_NAME`_UART_Sleep();
          `$INSTANCE_NAME`_TRANSCEIVER_SHUTDOWN();
          state = `$INSTANCE_NAME`_SLEEPING;
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
        case `$INSTANCE_NAME`_SLEEPING:*/
          `$INSTANCE_NAME`_TRANSCEIVER_RX_EN();
          `$INSTANCE_NAME`_UART_Wakeup();
          `$INSTANCE_NAME`_Timeout_Wakeup();
#if `$INSTANCE_NAME`_IS_ARBITER
          state = `$INSTANCE_NAME`_ARBITRING;
          nextArbitrationStep();
#else
          state = `$INSTANCE_NAME`_LISTENING;
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

CY_ISR(`$INSTANCE_NAME`_Timeout_isr) {
  `$INSTANCE_NAME`_STOP_TIMEOUT();
  ERROR_CB();
  
  switch(state) {
#if `$INSTANCE_NAME`_IS_ARBITER
    case `$INSTANCE_NAME`_ARBITRING:
      nextArbitrationStep();
    break;
#endif
    case `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE:
      //resend choosing call!
      
      CyGlobalIntDisable;
      `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
  		//send request
  		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
  		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_NORMAL;
  		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
      CyGlobalIntEnable;
		break;
    default:
      ERROR_CB();
    break;
  }
}


#if `$INSTANCE_NAME`_IS_ARBITER
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_AddNode(`$INSTANCE_NAME`_address address) {
	if(nodeDB.size == `$INSTANCE_NAME`_MAX_NODEDB_SIZE)
		return `$INSTANCE_NAME`_OUT_OF_SPACE;
	nodeDB.list[nodeDB.size++] = address;
	return `$INSTANCE_NAME`_SUCCESS;
}
#endif

void `$INSTANCE_NAME`_Init(void) {

  `$INSTANCE_NAME`_UART_Start();
  `$INSTANCE_NAME`_UART_SetCustomInterruptHandler(`$INSTANCE_NAME`_Uart_isr);

  `$INSTANCE_NAME`_UART_UartSetRxAddressMask(0xFF);
  `$INSTANCE_NAME`_UART_UartSetRxAddress(`$INSTANCE_NAME`_OWN_ADDRESS);


  `$INSTANCE_NAME`_isr_WAKE_StartEx(`$INSTANCE_NAME`_Wake_isr);
  `$INSTANCE_NAME`_isr_Timeout_StartEx(`$INSTANCE_NAME`_Timeout_isr);
  
  `$INSTANCE_NAME`_Timeout_Start();
  `$INSTANCE_NAME`_Timeout_Stop();
  `$INSTANCE_NAME`_Timeout_Sleep();

  `$INSTANCE_NAME`_TRANSCEIVER_SHUTDOWN();
  `$INSTANCE_NAME`_UART_Sleep();
}

void `$INSTANCE_NAME`_SetCallbackOnWake(
    `$INSTANCE_NAME`_wake_callback callback
) {
  callbacks.wake = callback;  
}

void `$INSTANCE_NAME`_SetCallbackOnError(
    `$INSTANCE_NAME`_error_callback callback
) {
  callbacks.error = callback;  
}

void `$INSTANCE_NAME`_SetCallbackOnSelectedAsSlave(
    `$INSTANCE_NAME`_selected_as_slave callback
) {
  callbacks.selectedAsSlave = callback;
}

void `$INSTANCE_NAME`_SetCallbackOnReleasedAsSlave(
    `$INSTANCE_NAME`_released_as_slave callback
) {
  callbacks.releasedAsSlave = callback;
}

void `$INSTANCE_NAME`_SetCallbackOnSlaveReceive(
    `$INSTANCE_NAME`_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
) {
  callbacks.slaveReceive = callback;
  slaveBuff.buff = receiveBuffer;
  slaveBuff.size = receiveBufferSize;
  slaveBuff.pos = 0;
}

void `$INSTANCE_NAME`_SetCallbackOnMasterReceive(
    `$INSTANCE_NAME`_receive_callback callback,
    char *receiveBuffer,
	uint32 receiveBufferSize
) {
  callbacks.masterReceive = callback;
  masterBuff.buff = receiveBuffer;
  masterBuff.size = receiveBufferSize;
  masterBuff.pos = 0;
}

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
) {
  switch(state) {
  case `$INSTANCE_NAME`_MASTER_OP:
  case `$INSTANCE_NAME`_SLAVE_OP:
    `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
	  txBuff.buff = buffer;
	  txBuff.size = len;
	  txBuff.pos = 0;

	  callbacks.frameSent = callback;

	  //enable TX_FIFO_NOTFULL IRQ
	  `$INSTANCE_NAME`_UART_ClearTxInterruptSource(`$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL);
	  `$INSTANCE_NAME`_UART_SpiUartEnableIntTx(
			  `$INSTANCE_NAME`_UART_GetTxInterruptMode() | `$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL);

	  return `$INSTANCE_NAME`_SUCCESS;
  break;
  default:
	  return `$INSTANCE_NAME`_FORBIDDEN;
  break;
  }
  return `$INSTANCE_NAME`_FAIL; //shouldnt happen, but suppress warning
}
/* `$INSTANCE_NAME`_RequestBus
 * call this function to aquire bus as master,
 * until receiving bus_granted_callback, atom is listening on all events
 * and can be selected as slave by other atom
 */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_RequestBus(
  `$INSTANCE_NAME`_bus_granted_callback callback
) {
	callbacks.busGranted = callback;
	`$INSTANCE_NAME`_ASSERT_WAKE(); //this should wake up UART if it was sleeping, or do nothing if was
	//already asserted
	return `$INSTANCE_NAME`_SUCCESS;
}
/* `$INSTANCE_NAME`_SelectSlave
 * call this function to select slave, call only after bus_granted callback
 */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_SelectSlave(
  `$INSTANCE_NAME`_address slaveAddress,
  `$INSTANCE_NAME`_slave_selected_callback callback
) {
	switch(state) {
	case `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE:
		

		callbacks.slaveSelected = callback;
		otherEndAddress = slaveAddress;

    CyGlobalIntDisable;
    `$INSTANCE_NAME`_TRANSCEIVER_TX_EN();
		//send request
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_NORMAL;
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
    CyGlobalIntEnable;

		return `$INSTANCE_NAME`_SUCCESS;
	break;
	default:
		return `$INSTANCE_NAME`_FORBIDDEN;
	break;
	}
	return `$INSTANCE_NAME`_FAIL;
}

/* `$INSTANCE_NAME`_ReleaseSlave
 * call when communication with slave is finished, after this call, SendFrame
 * function is forbidden, select another slave, or release bus
 */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_ReleaseSlave(
  `$INSTANCE_NAME`_slave_released_callback callback
) {
	switch(state) {
	case `$INSTANCE_NAME`_MASTER_OP:
    callbacks.slaveReleased = callback;
		state = `$INSTANCE_NAME`_MASTER_RELEASING_SLAVE;
    
    CyGlobalIntDisable;
		`$INSTANCE_NAME`_TRANSCEIVER_TX_EN();

		//send request
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | otherEndAddress;
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_DONE;
    CyGlobalIntEnable;

		return `$INSTANCE_NAME`_SUCCESS;
	break;
	default:
		return `$INSTANCE_NAME`_FORBIDDEN;
	break;
	}
	return `$INSTANCE_NAME`_FAIL;
}

/* `$INSTANCE_NAME`_ReleaseBus
 * call when finished all communication as Master
 */
`$INSTANCE_NAME`_return_code `$INSTANCE_NAME`_ReleaseBus(
  `$INSTANCE_NAME`_bus_released_callback callback
) {
	switch(state) {
	case `$INSTANCE_NAME`_MASTER_CHOOSING_SLAVE:
    callbacks.busReleased = callback;
#if `$INSTANCE_NAME`_IS_ARBITER
		state = `$INSTANCE_NAME`_ARBITRING;
		`$INSTANCE_NAME`_isr_WAKE_Disable();

		`$INSTANCE_NAME`_RELEASE_WAKE();
    if(callbacks.busReleased)
      callbacks.busReleased();

	    if(CyPins_ReadPin(`$INSTANCE_NAME`_WAKE_0)) {
	    	//rising
	    	`$INSTANCE_NAME`_isr_WAKE_SetPending();
	    	`$INSTANCE_NAME`_isr_WAKE_Enable();
	    } else {
	    	//low level, someone is still holding bus
	    	`$INSTANCE_NAME`_isr_WAKE_Enable();
	    	nextArbitrationStep();
	    }
#else
    state = `$INSTANCE_NAME`_MASTER_RELEASING_BUS;
  
    CyGlobalIntDisable;
		`$INSTANCE_NAME`_TRANSCEIVER_TX_EN();

		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_UART_UART_MP_MARK | `$INSTANCE_NAME`_Protocol_ARB_ADDRESS;
		`$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_Protocol_ARB_DONE;
    `$INSTANCE_NAME`_UART_TX_FIFO_WR_REG = `$INSTANCE_NAME`_OWN_ADDRESS;
    CyGlobalIntEnable;

#endif
		return `$INSTANCE_NAME`_SUCCESS;
	break;
	default:
		return `$INSTANCE_NAME`_FORBIDDEN;
	break;
	}
	return `$INSTANCE_NAME`_FAIL;
}

/* [] END OF FILE */
