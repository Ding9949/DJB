#include "buffer.h"
#include "queue.h"
#include "string.h"

can_buffer_t g_can1_buffer;

void can_buffer_init(void)
{
	unsigned char i;
	if(0 == create_queue(MAX_CAN_BUFFER, &g_can1_buffer.q))
	{
		for(i=0; i<MAX_CAN_BUFFER; i++)
		{
			g_can1_buffer.q.buf[i] = (void*)&g_can1_buffer.msg[i];
		}
	}

}

int can1_buffer_add_msg(CanMsg_t* msg)
{
	CanMsg_t* pbuf = NULL;
	if(msg == NULL)
		return 1;

	pbuf  = (CanMsg_t*)queue_join(&g_can1_buffer.q);
	if(pbuf == NULL)
		return 1;

	*pbuf = *msg;
	return 0;
}

CanMsg_t* can1_buffer_get_msg(void)
{
	CanMsg_t* pbuf = NULL;
	int ret = 1;
	ret = queue_quit(&g_can1_buffer.q, (void*)&pbuf);
	if(ret == 1 || pbuf == NULL)
		return (CanMsg_t*)pbuf;

	return (CanMsg_t*)pbuf;
	
}



