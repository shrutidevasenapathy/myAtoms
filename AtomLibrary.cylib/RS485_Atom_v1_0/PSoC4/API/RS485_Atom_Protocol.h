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

#if !defined(CY_RS485_Protocol_`$INSTANCE_NAME`_H)
#define CY_RS485_Protocol_`$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_Protocol_ARB_ADDRESS (0x01)

typedef enum {
  `$INSTANCE_NAME`_Protocol_ARB_REQ = 0x01,
  `$INSTANCE_NAME`_Protocol_ARB_NACK,
  `$INSTANCE_NAME`_Protocol_ARB_ACK,
  `$INSTANCE_NAME`_Protocol_ARB_GRANTED,
  `$INSTANCE_NAME`_Protocol_ARB_DONE,
  
  `$INSTANCE_NAME`_Protocol_NORMAL = 0x10,
  `$INSTANCE_NAME`_Protocol_EOF, //end of frame
  `$INSTANCE_NAME`_Protocol_DONE
} `$INSTANCE_NAME`_Protocol_frame_type;
  
#endif
/* [] END OF FILE */
