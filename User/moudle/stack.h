#ifndef __stack_h
#define __stack_h


typedef struct _stack_s
{
	unsigned short     bottom;
	unsigned short     top;
	unsigned short     interator;
	unsigned short     size;
	void**  buf;
}stack_t;

int create_stack( unsigned short size,  stack_t* s_handle);
int delete_stack(stack_t* s_handle);
void* pop_stack( stack_t* s_handle );
int push_stack( stack_t * s_handle, void* buf );



#endif
