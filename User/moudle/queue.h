#ifndef __queue_h
#define __queue_h


typedef struct _queue_s
{
	unsigned short     head;
	unsigned short     tail;
	unsigned short     size;
	void**  buf;
}queue_t;

int create_queue( unsigned short size,  queue_t* s_handle);
int destroy_queue(queue_t* s_handle);
int queue_quit( queue_t* s_handle, void** buf );
void* queue_join( queue_t * s_handle);


#endif
