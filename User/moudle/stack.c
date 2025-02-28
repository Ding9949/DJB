#include "stack.h"
#include "stdlib.h"
#include "string.h"

int create_stack( unsigned short size,  stack_t* s_handle)
{
	int err = 1;
	
	if( size<=0||s_handle==NULL)
		return err;

	s_handle->buf = (void**)malloc(sizeof(void*)*size);
	if(s_handle->buf!=NULL)
	{
		s_handle->bottom    = 0;
		s_handle->top       = size-1;
		s_handle->interator = 0;
		s_handle->size      = size;

		err = 0;
	}
	
	return err;

}

int delete_stack(stack_t* s_handle)
{
	if(s_handle == NULL)
		return 1;
	if(s_handle->buf)
		free(s_handle->buf);
	memset(s_handle, 0, sizeof(stack_t));
	return 0;	
}
void* pop_stack( stack_t* s_handle )
{
	int  i       = 0;
	void *result = NULL;

	if( s_handle==NULL )
		return result;

	if( s_handle->interator > 0 )
	{
		i = (--s_handle->interator)+s_handle->bottom;

		result = (void*)(s_handle->buf[i]);
	}
	return result;
}

int push_stack( stack_t * s_handle, void* buf )
{
	int i   = 0;
	int err = 1;

	
	if(s_handle==NULL || buf==NULL)
		return err;

	if( s_handle->interator < s_handle->size )
	{
	    	i = (s_handle->interator++)+s_handle->bottom;
	    	s_handle->buf[i] = buf;
	    	err = 0;
	}
	
	return err;
}
