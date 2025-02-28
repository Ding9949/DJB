#include "nvic.h" 

 //系统软复位   
void sys_soft_reset(void)
{  
	 NVIC_SystemReset();	  
}    

 void nvic_init(void)
{
	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
}



























