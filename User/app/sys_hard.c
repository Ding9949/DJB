#include "sys_include.h"

SysHart_t gSysHard;


void sys_hard_init(void)
{
	memset(&gSysHard, 0, sizeof(SysHart_t));
}

// 5K, 200us
void sys_hard_read_port(void)
{


	gExCom.ADS = (SW5_VAL<<4) + (SW4_VAL<<3) + (SW3_VAL<<2) + (SW2_VAL<<1) + SW1_VAL + 1;
	if(gExCom.ADS != gExCom.ADS_Bk)
	{
		gExCom.ADS_Bk = gExCom.ADS;
		
		Led_Set_Uint(gExCom.ADS, 1, 2);
	}


}
void sys_hard_load_port(void)
{
	//Êä³ö¿Ú

	LED_OUT(gSysHard.Led);

}



