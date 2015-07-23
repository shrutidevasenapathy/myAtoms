/*
 * commHandler.h
 *
 *  Created on: 1 lip 2015
 *      Author: kuba
 */

#if !defined(CY_comm_comm_H)
#define CY_comm_comm_H

#include <project.h>
  
#define comm__C 67
#define comm__D 68
#define comm__G 71
#define comm__K 75
#define comm__S 83
#define comm__L 76
#define comm__W 87

  
#if   87 == comm__C
  #define MY_ATOM_TYPE "C"
#elif 87 == comm__D
  #define MY_ATOM_TYPE "D"
#elif 87 == comm__G
  #define MY_ATOM_TYPE "G"
#elif 87 == comm__K
  #define MY_ATOM_TYPE "K"
#elif 87 == comm__S
  #define MY_ATOM_TYPE "S"
#elif 87 == comm__L
  #define MY_ATOM_TYPE "L"
#elif 87 == comm__W
  #define MY_ATOM_TYPE "W"
#else
  #error "Invalid or not supported Atom type"
#endif


//TODO this shoyld be in different FILE

#define MY_ATOM_ID "0"

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
	comm_RS485_address schedAddr;
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
    X(sleepPeriod, int, i)   X(shutdownTime, int, i)   X(test, char *, s)    X(innerPressure, int, i)   X(outerPressure, int, i)   X(currentFlow, int, i)     X(totalVolume, int, i)    X(valveStatus, int, i)    X(lastStartNumber, int, i)     X(lastStartVolume, int, i)     X(lastStartFlow, int, i)     X(startTime, int, i)   X(stopTime, int, i)      X(numStarts, int, i)     X(volPerStart, int, i)    X(maxVol, int, i)    X(minVol, int, i)     X(fertigationTable0, int *, ia)     X(fertigationTable1, int *, ia)      X(fertigationTable2, int *, ia)     X(fertigationTable3, int *, ia)     X(fertigationTable4, int *, ia)     X(fertigationTable5, int *, ia)     X(fertigationTable6, int *, ia)     X(fertigationTable7, int *, ia)     X(fertigationTable8, int *, ia)     X(fertigationTable9, int *, ia)   X(notBefore, int, i)   X(notAfter, int, i)   X(dilutionFactorA, int, i)   X(dilutionFactorB, int, i)   X(venturiSuctionA, int, i)   X(venturiSuctionB, int, i)   X(squareMeters, int, i)   X(lPerSqMeterPerDay, int, i)   X(cropType, int, i)

/*
 * Here define ATOM MODES, this will create proper enum, and string to enum conversion
 */
#define ATOM_MODES \
		X(Start)  	X(Test) 	X(Idle) 	X(Shutdown)

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

#endif /* CY_comm_comm_H */
