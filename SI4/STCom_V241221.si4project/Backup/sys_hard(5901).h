#ifndef __sys_hard_h
#define __sys_hard_h

#include "sys_bsp.h"
          


typedef struct 
{
	u16 Led;





	
}SysHart_t;

extern SysHart_t gSysHard;


void sys_hard_init(void);
void sys_hard_read_port(void);
void sys_hard_load_port(void);


#endif
