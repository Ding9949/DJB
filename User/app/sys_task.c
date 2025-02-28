#include "sys_include.h"


SysCtlVar_t gSysCtlVar;



/**********************************************************************************************************************/


void sys_task_init(void)
{
	
	memset(&gSysCtlVar, 0, sizeof(SysCtlVar_t));

}


// 1ms
void sys_task(void)
{

	if(gSysCtlVar.Ticker < SYS_ISR_PSC)
		return;
	gSysCtlVar.Ticker = 0;


	excom_task();

	Led_Dis_Task();

	if(gSysCtlVar.ParSave_Flag)
	{
		gSysCtlVar.ParSave_Flag = 0;
		api_save_sys_par();
	}

	if(Can_Err_Cnt > 100)  // 100ms
	{
		can_reset();
		Can_Err_Cnt = 0;
	}

}


