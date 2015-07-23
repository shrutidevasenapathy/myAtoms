/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#if !defined(CY_RS485_Protocol_comm_RS485_H)
#define CY_RS485_Protocol_comm_RS485_H
#define comm_RS485_Protocol_ARB_ADDRESS (0x01)

typedef enum {
  comm_RS485_Protocol_ARB_REQ = 0x01,
  comm_RS485_Protocol_ARB_NACK,
  comm_RS485_Protocol_ARB_ACK,
  comm_RS485_Protocol_ARB_GRANTED,
  comm_RS485_Protocol_ARB_DONE,
  
  comm_RS485_Protocol_NORMAL = 0x10,
  comm_RS485_Protocol_EOF, //end of frame
  comm_RS485_Protocol_DONE
} comm_RS485_Protocol_frame_type;
  
#endif
/* [] END OF FILE */
