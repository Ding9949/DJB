#include "nvic.h" 

 //ϵͳ��λ   
void sys_soft_reset(void)
{  
	 NVIC_SystemReset();	  
}    

 void nvic_init(void)
{
	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
}



























