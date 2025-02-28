#include <stdlib.h>
#include "queue.h"

int create_queue( unsigned short size,  queue_t* s_handle)
{
	int err = 1;
	
	if( size<=0||s_handle==NULL)
		return err;
	s_handle->buf = (void**)malloc(sizeof(void*)*size);
	if(s_handle->buf!=NULL)
	{
		s_handle->head    = 0;
		s_handle->tail       = 0;
		s_handle->size      = size;

		err = 0;
	}
	
	return err;

}

int destroy_queue(queue_t* s_handle)
{
	if(s_handle == NULL)
		return 1;

	if(s_handle->buf)
	{
		free(s_handle->buf);
		s_handle->buf = NULL;
	}
	return 0;
}

// 出列
int queue_quit( queue_t* s_handle, void** buf )
{
	int  i = 0;
	if(s_handle == NULL || buf == NULL)
		return 1;

	//队列空
	if(s_handle->head == s_handle->tail)
		return 1;
		
	i = s_handle->tail + 1;
	if(i >= s_handle->size)
		i = 0;
		
	*buf = (void*)(s_handle->buf[i]);
	
	s_handle->tail = i;

	
	return 0;	
}

// 入列
void* queue_join( queue_t * s_handle)
{
	int  i = 0;
	void *result = NULL;
	if(s_handle == NULL)
		return result;

	i = s_handle->head+ 1;
	if(i >= s_handle->size)
		i = 0;

	// 队列满
	if(i == s_handle->tail)
		return result;

	result = (void*)(s_handle->buf[i]);
	s_handle->head  = i;

	return result;

	
}

