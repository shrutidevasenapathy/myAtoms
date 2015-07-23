/*
 * commHandler.c
 *
 *  Created on: 1 lip 2015
 *      Author: kuba
 */

#include <project.h>

/*
Extern declarations to avoid 'implicit declaration' errors
TODO find better fix, because when for some reason prototype will change,
here also neeed to be changed
*/
extern void sleepMgr_requestSleep(void);
extern void sleepMgr_releaseSleep(void);
extern uint32_t SysTimer_GetTicks(void);

comm_t comm;

char respBuff[RESP_BUFF_LEN];
char *respEnd = respBuff;
int respFreeSpace = RESP_BUFF_LEN;


#define MSG_SOURCE_HOLDER "{\"atomType\":\"" MY_ATOM_TYPE "\",\"atomId\":" MY_ATOM_ID "}"

char msgDestinationHolder[] = "{\"atomType\":\"X\",\"atomId\":0}";
char *msgDestinationHolderAtomType = msgDestinationHolder + 13;
char *msgDestinationHolderAtomId = msgDestinationHolder + 25;

/*
 * Converts FLAG passed in string to ENUM
 */
static comm_flags_t str2flag(const char *str, int len) {
  if(strncmp(str, "REQ", len) == 0) return COMM_FLAG_REQ;
  if(strncmp(str, "REQ_ACK", len) == 0) return COMM_FLAG_REQ_ACK;
  if(strncmp(str, "ACK", len) == 0) return COMM_FLAG_ACK;
  if(strncmp(str, "NACK", len) == 0) return COMM_FLAG_NACK;
  if(strncmp(str, "PUSH", len) == 0) return COMM_FLAG_PUSH;
  return COMM_FLAG_UNKNOWN;
}
/*
 * Converts ENUM Flag to string, length checking, returns bytes written to string
 */
static int flag2str(char *str, int len, comm_flags_t flag) {
  switch(flag) {
    case COMM_FLAG_REQ: memcpy(str, "REQ", len < 3 ? len : 3); return len < 3 ? len : 3;
    case COMM_FLAG_REQ_ACK: memcpy(str, "REQ_ACK", len < 7 ? len : 7); return len < 7 ? len : 7;
    case COMM_FLAG_ACK: memcpy(str, "ACK", len <  3 ? len : 3); return len <  3 ? len : 3;
    case COMM_FLAG_NACK: memcpy(str, "NACK", len < 4 ? len : 4); return len < 4 ? len : 4;
    case COMM_FLAG_PUSH: memcpy(str, "PUSH", len < 4 ? len : 4); return len < 4 ? len : 4;
    case COMM_FLAG_UNKNOWN: //no break on purpose
    default: memcpy(str, "ERR", len < 3 ? len : 3); return len < 3 ? len : 3;
  }
}

/*
 * ATOM ORDERs prototypes
 */
#define X(order) extern comm_flags_t comm_handle_##order(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);
  ATOM_ORDERS
#undef X
comm_flags_t comm_handle_Set(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);
comm_flags_t comm_handle_Get(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);
comm_flags_t comm_handle_Info(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);
comm_flags_t comm_handle_Status(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);
comm_flags_t comm_handle_Mode(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen);



/*
 * ATOM VARIABLES section
 */
typedef enum {
#define X(name, vtype, jtype) ATOM_VARIABLE_##name,
  ATOM_VARIABLES
#undef X
  NUM_OF_ATOM_VARIABLES,
  INVALID_ATOM_VARIABLE
} atom_variables_id_t;

static const char * atom_variables_id_strings[NUM_OF_ATOM_VARIABLES] = {
#define X(name, vtype, jtype) [ATOM_VARIABLE_##name] = #name,
    ATOM_VARIABLES
#undef X
};
static atom_variables_id_t get_atom_variable_id_from_string(const char * str, int len) {
#define X(name, vtype, jtype) if(strncmp(str, atom_variables_id_strings[ATOM_VARIABLE_##name], len) == 0) return ATOM_VARIABLE_##name; else
  ATOM_VARIABLES
#undef X
  return INVALID_ATOM_VARIABLE;
}

#define X(name, vtype, jtype) \
extern void setvar_##name(vtype);\
extern vtype getvar_##name(void);
ATOM_VARIABLES
#undef X
/*
 * End of ATOM VARIABLES section
 */

/*
 * ATOM MODES section
 */
static const char * atom_modes_strings[NUM_OF_ATOM_MODES] = {
#define X(mode) [ATOM_MODE_##mode] = #mode,
	ATOM_MODES
#undef X
};
static atom_modes_t get_atom_mode_from_string(const char *str, int len) {
#define X(mode) if(strncmp(str, atom_modes_strings[ATOM_MODE_##mode], len) == 0) return ATOM_MODE_##mode;
	ATOM_MODES
#undef X
	return INVALID_ATOM_MODE;
}

/*
 * END OF ATOM MODES
 */

//JSON/JSMN helpers
static int compKey(const char *json, jsmntok_t *t, const char *key) {
  if(t->type == JSMN_STRING && strncmp(json + t->start, key, t->end - t->start) == 0) {
    return 0;
  }
  return -1;
}
static int skipToNextTokenInLevel(jsmntok_t *tokens, int current) {
  if(tokens[current].type == JSMN_OBJECT ||
     tokens[current].type == JSMN_ARRAY) {
    int expectedEnd = tokens[current].end;
    while(expectedEnd > tokens[++current].start);
  } else {
    //normal, just skip token
    current++;
  }
  return current;
}

// Functions for JSON protocol creating
static inline void resp_GenDestSrcOrder(
  const char *dest, int destLen,
  const char *src, int srcLen,
  const char *order, int orderLen) {

  respEnd = respBuff;
  respFreeSpace = RESP_BUFF_LEN;

  ADD_STATIC_STRING_TO_RESP("{\"destination\":");

  memcpy(respEnd, dest, destLen);
  respEnd += destLen;
  respFreeSpace -= destLen;

  ADD_STATIC_STRING_TO_RESP(",\"source\":");

  memcpy(respEnd, src, srcLen);
  respEnd += srcLen;
  respFreeSpace -= srcLen;

  // memcpy(respEnd, ",\"source\":" ATOM_SOURCE_FIELD, sizeof(",\"source\":" ATOM_SOURCE_FIELD));
  // respEnd += sizeof(",\"source\":" ATOM_SOURCE_FIELD) -1;
  // respFreeSpace -= sizeof(",\"source\":" ATOM_SOURCE_FIELD) -1;

  ADD_STATIC_STRING_TO_RESP(",\"order\":\"");

  memcpy(respEnd, order, orderLen);
  respEnd += orderLen;
  respFreeSpace -= orderLen;

  ADD_CHAR_TO_RESP('\"');
}

void resp_AddFlags(comm_flags_t flag) {
  ADD_STATIC_STRING_TO_RESP(",\"flags\":\"");

  int r = flag2str(respEnd, respFreeSpace, flag);
  respEnd += r;
  respFreeSpace -= r;

  ADD_CHAR_TO_RESP('\"');
}

typedef enum {
  JSON_MSG_PARSE_OK = 0,
  JSON_MSG_PARSE_FAILED,
  JSON_MSG_INVALID_DESTINATION,
  JSON_MSG_INVALID_FIELDS,
  JSON_MSG_GETSET_INVALID_VARIABLE
} JSON_MSG_return_t;

static comm_flags_t flags = COMM_FLAG_UNKNOWN;
static const char *order = NULL;
static int orderLen = 0;
static const char *payload = NULL;
static int payloadLen = 0;

static const char *msgSource = NULL;
static int msgSourceLen = 0;
static const char *msgDest = NULL;
static int msgDestLen = 0;

#define JSMN_TOKENS_SIZE 60
static jsmn_parser parser;
jsmntok_t tokens[JSMN_TOKENS_SIZE];

/* This function tests if recived JSON msg was addressed correctly,
 * it sets flags, order, payload and msgSource variables
 */
JSON_MSG_return_t validateDestinationAndParse(const char* json, int json_len) {
	//reset globals
	order = payload = msgSource = msgDest = NULL;
	flags = COMM_FLAG_UNKNOWN;
  jsmn_init(&parser);
  int r = jsmn_parse(&parser, json, json_len, tokens, JSMN_TOKENS_SIZE);
  if(r <= 0)
    return JSON_MSG_PARSE_FAILED;
  // for(int i = 0; i < r; i++) {
  //   printf("[%2d]Type: %3d, size: %3d, start: %3d, end: %3d", i, tokens[i].type,
  //   tokens[i].size, tokens[i].start, tokens[i].end);
  //   printf(", value: %.*s", tokens[i].end - tokens[i].start, json + tokens[i].start);
  //   printf("\n");
  // }
  // return 0;
  if(tokens[0].type != JSMN_OBJECT)
    return JSON_MSG_PARSE_FAILED;

  int t = 1;
  int i = 0;
  for(; i < tokens[0].size; i++) {
    if(tokens[t].type != JSMN_STRING) //it should point to key
      return JSON_MSG_PARSE_FAILED;
    //printf("!value: %.*s\n", tokens[t].end - tokens[t].start, argv[1] + tokens[t].start);
    if(compKey(json, &tokens[t], "destination") == 0) {
      if(tokens[t+1].type != JSMN_OBJECT)//it should be OBJECT
        return JSON_MSG_PARSE_FAILED;
      int y = t+2;
      int j = 0;
      for(; j < tokens[t+1].size; j++) {
        //were in destination object
        if(tokens[y].type != JSMN_STRING) //it should point to key
          return JSON_MSG_PARSE_FAILED;
        //printf("-!value: %.*s\n", tokens[y].end - tokens[y].start, argv[1] + tokens[y].start);
        if(compKey(json, &tokens[y], "atomType") == 0) {
          //woot atom type
          if(strncmp(json + tokens[y+1].start, MY_ATOM_TYPE, tokens[y+1].end - tokens[y+1].start) != 0) {
            return JSON_MSG_INVALID_DESTINATION;
          }
        } else if(compKey(json, &tokens[y], "atomId") == 0) {
          //woot atomId
          if(strncmp(json + tokens[y+1].start, MY_ATOM_ID, tokens[y+1].end - tokens[y+1].start) != 0) {
            return JSON_MSG_INVALID_DESTINATION;
          }
        }
        y = skipToNextTokenInLevel(tokens, ++y);
      }
      msgDest = json + tokens[t+1].start;
      msgDestLen = tokens[t+1].end - tokens[t+1].start;
    } else if(compKey(json, &tokens[t], "source") == 0) {
      if(tokens[t+1].type != JSMN_OBJECT)//it should be OBJECT
        return JSON_MSG_PARSE_FAILED;
      msgSource = json + tokens[t+1].start;
      msgSourceLen = tokens[t+1].end - tokens[t+1].start;
    } else if(compKey(json, &tokens[t], "flags") == 0) {
      flags = str2flag(json + tokens[t+1].start, tokens[t+1].end - tokens[t+1].start);
    } else if(compKey(json, &tokens[t], "order") == 0) {
      order = json + tokens[t+1].start;
      orderLen = tokens[t+1].end - tokens[t+1].start;
    } else if(compKey(json, &tokens[t], "payload") == 0) {
      payload = json + tokens[t+1].start;
      payloadLen = tokens[t+1].end - tokens[t+1].start;
    }
    t = skipToNextTokenInLevel(tokens, ++t);
  }
  if(msgSource == NULL || msgDest == NULL || order == NULL || flags == COMM_FLAG_UNKNOWN || payload == NULL) {
    return JSON_MSG_INVALID_FIELDS;
  }
  return JSON_MSG_PARSE_OK;
}

comm_flags_t comm_handle_Get(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen) {
  switch(flags) {
  case COMM_FLAG_REQ: //here is implementation of standard GET request, we are breaking case, so implementation can follow
	  break;
  case COMM_FLAG_ACK: //here can be implementation of GET ACK message, however, receiving ACK means it is ok, so we are ending handling by returning UNKNOWN flag;
  default: return COMM_FLAG_UNKNOWN;//we only handle REQ and ACK
  }

  if(tokens[0].type != JSMN_OBJECT) {
	  //invalid payload, it should be an object
	  goto error_exit;
  }

  int t = 1;
  atom_variables_id_t avid = INVALID_ATOM_VARIABLE;
  int i = 0;
  for(; i < tokens[0].size; i++) {
	if(tokens[t].type != JSMN_STRING) {//it should point to key
	  //something is wrong with payload
	  goto error_exit;
	}
    if(compKey(payload, &tokens[t], "n") == 0) {
      //printf("%.*s\n", tokens[t+1].end - tokens[t+1].start, payload + tokens[t+1].start);
      avid = get_atom_variable_id_from_string(payload + tokens[t+1].start,tokens[t+1].end - tokens[t+1].start);
      break;
    }
    t = skipToNextTokenInLevel(tokens, ++t);
  }
  if(avid == INVALID_ATOM_VARIABLE) {
	  //failed to properly parse Payload, not found variable or unknown
	  goto error_exit;
  }

  int tmp = 0;
  switch(avid) {
#define X(name, vtype, jtype) \
    case ATOM_VARIABLE_##name: { \
      ADD_STATIC_STRING_TO_RESP(",\"payload\":{\"n\":\"" #name "\",\"t\":\"" #jtype "\",\"v\":"); \
      tmp = conv_##jtype##2str(respEnd, respFreeSpace, getvar_##name()); \
    } break;
    ATOM_VARIABLES
#undef X
    default: goto error_exit;
    break;
  }
  respEnd += tmp;
  respFreeSpace -= tmp;

  ADD_CHAR_TO_RESP('}');

  return COMM_FLAG_REQ_ACK;
error_exit:
	ADD_STATIC_STRING_TO_RESP(",\"payload\":null");
	return COMM_FLAG_NACK;
}

comm_flags_t comm_handle_Set(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen) {
	if(flags != COMM_FLAG_REQ) {
		//we only expect REQ flags, ignore otherwise (this is error?
		return COMM_FLAG_UNKNOWN;
	}
  if(tokens[0].type != JSMN_OBJECT) {
	  //invalid payload, it should be an object
	  goto error_exit;
  }

  int t = 1;
  atom_variables_id_t avid = INVALID_ATOM_VARIABLE;
  const char *value = NULL;
  int valueLen = 0;
  const char *type = NULL;
  int typeLen = 0;
  int i = 0;
  for(; i < tokens[0].size; i++) {
	  if(tokens[t].type != JSMN_STRING) {//it should point to key
		  //something is wrong with payload
		  goto error_exit;
	  }
    if(compKey(payload, &tokens[t], "n") == 0) {
      //printf("%.*s\n", tokens[t+1].end - tokens[t+1].start, payload + tokens[t+1].start);
      avid = get_atom_variable_id_from_string(payload + tokens[t+1].start,tokens[t+1].end - tokens[t+1].start);
    } else if(compKey(payload, &tokens[t], "t") == 0) {
      type = payload + tokens[t+1].start;
      typeLen = tokens[t+1].end - tokens[t+1].start;
    } else if(compKey(payload, &tokens[t], "v") == 0) {
      value = payload + tokens[t+1].start;
      valueLen = tokens[t+1].end - tokens[t+1].start;
    }
    t = skipToNextTokenInLevel(tokens, ++t);
  }

  if(value == NULL || type == NULL || avid == INVALID_ATOM_VARIABLE) {
	  //failed to properly parse Payload
	  goto error_exit;
  }

  switch(avid) {
#define X(name, vtype, jtype) \
    case ATOM_VARIABLE_##name: { \
      if(strncmp(type, #jtype, typeLen) == 0) \
        setvar_##name(conv_str2##jtype(value, valueLen)); \
    } break;
    ATOM_VARIABLES
#undef X
    default: goto error_exit;
    break;
  }

  ADD_STATIC_STRING_TO_RESP(",\"payload\":null");

  return COMM_FLAG_ACK;
error_exit:
	ADD_STATIC_STRING_TO_RESP(",\"payload\":null");
	return COMM_FLAG_NACK;
}

comm_flags_t comm_handle_Info(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen) {
	if(flags == COMM_FLAG_UNKNOWN) {
		//in this case we are preparing this message!
		ADD_STATIC_STRING_TO_RESP(",\"payload\":{\"oa\":[");
		comm_GenerateInfo();
		ADD_STATIC_STRING_TO_RESP("]}");
		return COMM_FLAG_PUSH;
	}
	return COMM_FLAG_UNKNOWN;
}
comm_flags_t comm_handle_Status(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen) {
	if(flags == COMM_FLAG_REQ) {
		//We are expecting only REQ here, according to protocol, payload array with Info block is expected, with REQ_ACK
		ADD_STATIC_STRING_TO_RESP(",\"payload\":{\"oa\":[");
		comm_GenerateInfo();
		ADD_STATIC_STRING_TO_RESP("]}");
		return COMM_FLAG_REQ_ACK;
	}
	//if we receive ACK, end of communication
	return COMM_FLAG_UNKNOWN;
}

comm_flags_t comm_handle_Mode(comm_flags_t flags, const char *payload, int payloadLen, jsmntok_t *tokens, int tokensLen) {
	if(flags == COMM_FLAG_REQ) {
		//We are expecting only REQ here, according to protocol, ACK or NACK is proper anserw

		atom_modes_t mode = get_atom_mode_from_string(payload, payloadLen);

		if(mode == INVALID_ATOM_MODE) {
			//invalid payload
			goto error_exit;
		}

		comm_ModeChange(mode);

		ADD_STATIC_STRING_TO_RESP(",\"payload\":null");
		return COMM_FLAG_ACK;
	error_exit:
		ADD_STATIC_STRING_TO_RESP(",\"payload\":null");
		return COMM_FLAG_NACK;
	}
	return COMM_FLAG_UNKNOWN;
}

static comm_RS485_address jsonAddressToRS(char atomType, char atomID) {
	return (((atomType - 'A')&0x1f) << 3) | ((atomID - '0')&0x07);
}

/*
 * ************************************
 * RS485 callbacks
 * ************************************
 */

void rs485_selected_as_slave_callback(comm_RS485_address byWho) {
	comm.flags.SLAVE = 1;
}
void rs485_released_as_slave_callback(void) {
	comm.flags.SLAVE = 0;
	//connection was broken, just to be sure stop sending
	comm.flags.SENT = 0;
}
void rs485_receive_callback(char * buff, uint32 len) {
	comm.len = len;
	comm.flags.RECV = 1;
}

void rs485_wake_callback(uint8 isWake) {
	isWake ? sleepMgr_requestSleep() : sleepMgr_releaseSleep();
}
//void rs485_error_callback(int line) {
//	if(line < 10000) {
//	  DEBUG_UartPutString("ERR ");
//	  DEBUG_UartPutChar("0123456789"[line/1000]);
//	  DEBUG_UartPutChar("0123456789"[(line%1000)/100]);
//	  DEBUG_UartPutChar("0123456789"[(line%100)/10]);
//	  DEBUG_UartPutChar("0123456789"[line%10]);
//	  DEBUG_UartPutString("\r\n");
//	}
//
//}
void rs485_bus_granted_callback(void) {
	comm.state = COMM_STATE_BUS_GRANTED;
}
void rs485_slave_selected_callback(void) {
	comm.state = COMM_STATE_SLAVE_SELECTED;
}
void rs485_slave_released_callback(void) {
	comm.state = COMM_STATE_SLAVE_RELEASED;
}
void rs485_bus_released_callback(void) {
	comm.state = COMM_STATE_BUS_RELEASED;
}

void comm_Init(void) {
	memset(&comm, 0, sizeof(comm));
	comm.state = COMM_STATE_IDLE;

    comm_RS485_SetCallbackOnSelectedAsSlave(rs485_selected_as_slave_callback);
    comm_RS485_SetCallbackOnReleasedAsSlave(rs485_released_as_slave_callback);
    comm_RS485_SetCallbackOnSlaveReceive(rs485_receive_callback, comm.recvBuff, RECV_BUFF_LEN);
    comm_RS485_SetCallbackOnMasterReceive(rs485_receive_callback, comm.recvBuff, RECV_BUFF_LEN);
    comm_RS485_SetCallbackOnWake(rs485_wake_callback);
//    comm_RS485_SetCallbackOnError(rs485_error_callback);
    comm_RS485_Init();
}

void comm_ScheduleMessage(const char *order, int orderLen, char atomType, char atomID) {
	comm.schedOrder = order;
	comm.schedOrderLen = orderLen;
	comm.schedAddr = atomType == 'X' ? comm_RS485_Protocol_ARB_ADDRESS : jsonAddressToRS(atomType, atomID);
	*msgDestinationHolderAtomType = atomType;
	*msgDestinationHolderAtomId = atomID;

	comm_RS485_RequestBus(rs485_bus_granted_callback);
}


static uint32_t sendingTicks = 0;
void rs485_frame_sent_callback(char * buff, uint32 len) {
	if(comm.flags.LAST_MSG) {
		comm.flags.LAST_MSG = 0;
		comm_RS485_ReleaseSlave(rs485_slave_released_callback);  //if we are slave, this will fail
	} else {
		sendingTicks = SysTimer_GetTicks();
		comm.flags.SENT = 1;
	}
}

void comm_Handler(void) {
	static int error_counter = 0;
	static int timeout_counter = 0;
	if(comm.flags.RECV) {
		//stop resending
		comm.flags.SENT = 0;
		//recv message
		if(validateDestinationAndParse(comm.recvBuff, comm.len) == JSON_MSG_PARSE_OK) {
			if(flags == COMM_FLAG_NACK) {
				//we are in session, but receivied NACK increease error counter
				if(error_counter++ < 3) {
					//resend message
					comm_RS485_SendFrame(respBuff, RESP_BUFF_LEN - respFreeSpace, rs485_frame_sent_callback);
				}
			} else {
				//reset error & timeout counter
				error_counter = 0;
				timeout_counter = 0;
				resp_GenDestSrcOrder(msgSource, msgSourceLen, msgDest, msgDestLen, order, orderLen);

				jsmn_init(&parser);
				int r = jsmn_parse(&parser, payload, payloadLen, tokens, JSMN_TOKENS_SIZE);
				if(r > 0) {
					comm_flags_t retflag = COMM_FLAG_UNKNOWN;

					if(strncmp(order, "Set", orderLen) == 0) {
						retflag = comm_handle_Set(flags, payload, payloadLen, tokens, r);
					} else if(strncmp(order, "Get", orderLen) == 0) {
						retflag = comm_handle_Get(flags, payload, payloadLen, tokens, r);
					} else if(strncmp(order, "Info", orderLen) == 0) {
						retflag = comm_handle_Info(flags, payload, payloadLen, tokens, r);
					} else if(strncmp(order, "Status", orderLen) == 0) {
						retflag = comm_handle_Status(flags, payload, payloadLen, tokens, r);
					} else if(strncmp(order, "Mode", orderLen) == 0) {
						retflag = comm_handle_Mode(flags, payload, payloadLen, tokens, r);
					}
					#define X(OrderName) else if(strncmp(order, #OrderName, orderLen) == 0) { \
						retflag = comm_handle_##OrderName(flags, payload, payloadLen, tokens, r); \
					}
					ATOM_ORDERS
					#undef X

					if(retflag != COMM_FLAG_UNKNOWN) {
						//handler returned flag that indicates communication, we are adding it to overall payload, and sending over bus
						resp_AddFlags(retflag);
						ADD_CHAR_TO_RESP('}');

						*respEnd = '\0';

						if(retflag == COMM_FLAG_ACK || retflag == COMM_FLAG_NACK) {
							//this is final message from this atom
							comm.flags.LAST_MSG = 1;
						}

						comm_RS485_SendFrame(respBuff, RESP_BUFF_LEN - respFreeSpace, rs485_frame_sent_callback);
					} else {
						//handler indicated that comm is over, if we are master, we should release the bus!
						if(comm.flags.SLAVE == 0) {
							comm_RS485_ReleaseSlave(rs485_slave_released_callback); //we can call this even if we are not master, it'll just fail
						}
					}
					//otherwise just wait for other events (another message or bus release?)
				}
			}
		}
		comm.flags.RECV = 0;
	}
	if(comm.flags.SENT) {
		//message was sent,
		if(timeout_counter > 2) {
			//we are 3x timeouted, stop sending...
			comm.flags.SENT = 0;
			//if we are MASTER here, well, release bus
			if(comm.flags.SLAVE == 0) {
				comm_RS485_ReleaseSlave(rs485_slave_released_callback);
			}
		} else if(SysTimer_GetTicks() - sendingTicks > 3000) {
			//we've got timeout, resend frame
			comm.flags.SENT = 0;
			timeout_counter++;
			comm_RS485_SendFrame(respBuff, RESP_BUFF_LEN - respFreeSpace, rs485_frame_sent_callback);
		}
	}
	switch(comm.state) {
	case COMM_STATE_BUS_GRANTED:
		comm_RS485_SelectSlave(comm.schedAddr, rs485_slave_selected_callback);
		break;
	case COMM_STATE_SLAVE_SELECTED:
		//reset error & timeout counter
		error_counter = 0;
		timeout_counter = 0;
		resp_GenDestSrcOrder(msgDestinationHolder, sizeof(msgDestinationHolder) - 1,
				MSG_SOURCE_HOLDER, sizeof(MSG_SOURCE_HOLDER) - 1,
				comm.schedOrder, comm.schedOrderLen);

		comm_flags_t retflag = COMM_FLAG_UNKNOWN;

		if(strncmp(comm.schedOrder, "Set", comm.schedOrderLen) == 0) {
			retflag = comm_handle_Set(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0);
		} else if(strncmp(comm.schedOrder, "Get", comm.schedOrderLen) == 0) {
			retflag = comm_handle_Get(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0);
		} else if(strncmp(comm.schedOrder, "Info", comm.schedOrderLen) == 0) {
			retflag = comm_handle_Info(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0);
		} else if(strncmp(comm.schedOrder, "Status", comm.schedOrderLen) == 0) {
			retflag = comm_handle_Info(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0);
		} else if(strncmp(comm.schedOrder, "Mode", comm.schedOrderLen) == 0) {
			retflag = comm_handle_Mode(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0);
		}
		#define X(OrderName) else if(strncmp(comm.schedOrder, #OrderName, comm.schedOrderLen) == 0) { \
			retflag = comm_handle_##OrderName(COMM_FLAG_UNKNOWN, NULL, 0, NULL, 0); \
		}
		ATOM_ORDERS
		#undef X

		if(retflag != COMM_FLAG_UNKNOWN) {
			//handler returned flag that indicates communication, we are adding it to overall payload, and sending over bus
			resp_AddFlags(retflag);
			ADD_CHAR_TO_RESP('}');

			*respEnd = '\0';

			if(retflag == COMM_FLAG_PUSH) {
				//we dont care about ACKs...
				comm.flags.LAST_MSG = 1;
			}
			comm_RS485_SendFrame(respBuff, RESP_BUFF_LEN - respFreeSpace, rs485_frame_sent_callback);
		} else {
			//this is defeneatly error, but release slave
			comm_RS485_ReleaseSlave(rs485_slave_released_callback);
		}

		break;
	case COMM_STATE_SLAVE_RELEASED:
		comm_RS485_ReleaseBus(rs485_bus_released_callback);
		break;
	case COMM_STATE_BUS_RELEASED:
	default:
		break;
	}
	comm.state = COMM_STATE_IDLE;
}
