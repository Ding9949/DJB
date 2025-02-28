#ifndef __buffer_h
#define __buffer_h

#include "queue.h"
#include "can.h"

#define MAX_CAN_BUFFER 20



typedef struct _can_buffer_s
{
	queue_t q;
	CanMsg_t msg[MAX_CAN_BUFFER];
}can_buffer_t;

extern can_buffer_t g_can1_buffer;

void can_buffer_init(void);
int can1_buffer_add_msg(CanMsg_t* msg);
CanMsg_t* can1_buffer_get_msg(void);


#endif
