/*
 * commHandler.h
 *
 *  Created on: 1 lip 2015
 *      Author: kuba
 */

#if !defined(CY_comm_`$INSTANCE_NAME`_H)
#define CY_comm_`$INSTANCE_NAME`_H

#include <project.h>
  
`#declare_enum JSON_Comm_Atom_type`
  
#if   `$Atom_Type` == `$INSTANCE_NAME`__C
  #define MY_ATOM_TYPE "C"
#elif `$Atom_Type` == `$INSTANCE_NAME`__D
  #define MY_ATOM_TYPE "D"
#elif `$Atom_Type` == `$INSTANCE_NAME`__G
  #define MY_ATOM_TYPE "G"
#elif `$Atom_Type` == `$INSTANCE_NAME`__K
  #define MY_ATOM_TYPE "K"
#elif `$Atom_Type` == `$INSTANCE_NAME`__S
  #define MY_ATOM_TYPE "S"
#elif `$Atom_Type` == `$INSTANCE_NAME`__L
  #define MY_ATOM_TYPE "L"
#elif `$Atom_Type` == `$INSTANCE_NAME`__W
  #define MY_ATOM_TYPE "W"
#else
  #error "Invalid or not supported Atom type"
#endif


//TODO this shoyld be in different FILE

#define MY_ATOM_ID "`$Atom_ID`"

#define RECV_BUFF_LEN 300
typedef struct {
	char recvBuff[RECV_BUFF_LEN];
	uint32 len;
	struct {
		uint32 RECV : 1;
		uint32 SENT : 1;
		uint32 SLAVE: 1;
		uint32 LAST_MSG: 1;
	} flags;
	enum {
		COMM_STATE_IDLE,
		COMM_STATE_BUS_GRANTED,
		COMM_STATE_SLAVE_SELECTED,
		COMM_STATE_SLAVE_RELEASED,
		COMM_STATE_BUS_RELEASED
	} state;
	const char *schedOrder;
	int schedOrderLen;
	`$INSTANCE_NAME`_RS485_address schedAddr;
} comm_t;
extern comm_t comm;

typedef enum {
  COMM_FLAG_UNKNOWN = 0x00,
  COMM_FLAG_REQ = 0x01,
  COMM_FLAG_ACK = 0x02,
  COMM_FLAG_REQ_ACK = 0x03, //this is REQ | ACK also!
  COMM_FLAG_NACK = 0x04,
  COMM_FLAG_PUSH = 0x08,
} comm_flags_t;

/* Here define ATOM ORDERS, which it can handle, Set and Get, Info, Status and Mode are defaults
 * EXAMPLE:
 * #define ATOM_ORDERS \
 * X(xsms) \
 * X(OtherOrder)
 */
#define ATOM_ORDERS \
  `$Atom_Orders`

/* Here define ATOM VARIABLES, first name of variable, then C type,
 * then JSON comm protocol type (without C string quotes!)
 *
 * EXAMPLE:
 * #define ATOM_VARIABLES \
 * X(intVar, int, i) \
 * X(stringVar, char *, s) \
 * X(doubleVar, double, d) \
 * X(booleanVar, unsigned int, b)
 *
 * IMPORTANT NOTICE: if using stringVar, remember that pointer is only valid on setvar callback!
 */
#define ATOM_VARIABLES \
  `$Atom_Variables`

/*
 * Here define ATOM MODES, this will create proper enum, and string to enum conversion
 */
#define ATOM_MODES \
	`$Atom_Modes`

typedef enum {
#define X(mode) ATOM_MODE_##mode,
	ATOM_MODES
#undef X
	NUM_OF_ATOM_MODES,
	INVALID_ATOM_MODE
} atom_modes_t;

/*
 * Response buffer
 */
#define RESP_BUFF_LEN 300
extern char respBuff[RESP_BUFF_LEN];
extern char *respEnd;
extern int respFreeSpace;

#define ADD_STATIC_STRING_TO_RESP(x) do {\
  memcpy(respEnd, x, sizeof(x)); \
  respEnd += sizeof(x) -1; \
  respFreeSpace -= sizeof(x) -1; }while(0)
   //This -1 for null byte
#define ADD_CHAR_TO_RESP(x) do {*respEnd++ = x;respFreeSpace--;} while(0)


void comm_Init(void);
void comm_Handler(void);

void comm_ScheduleMessage(const char *order, int orderLen, char atomType, char atomID);

/*
 * Functions which Atom implementer has to provide, along with seters, getters and order handles
 */

extern void comm_GenerateInfo(void);
extern void comm_ModeChange(atom_modes_t mode);

#endif /* CY_comm_`$INSTANCE_NAME`_H */
