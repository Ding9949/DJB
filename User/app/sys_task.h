#ifndef __sys_task_h
#define __sys_task_h

#include "sys_bsp.h"



typedef struct{
	u8 ParSave_Flag;

	u16 Ticker;
}SysCtlVar_t;



extern SysCtlVar_t gSysCtlVar;



void sys_task_init(void);
void sys_task(void);

#endif
