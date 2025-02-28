#include "sys_include.h"



/****************************************************************************************************************/
SysPar_t gSysPar;
SysPar_t gSysParBk;
SysParRT_t gSysPar_RT;
SysParRT_t gSysPar_RT_Bk;
/****************************************************************************************************************/





/****************************************************************************************************************/
const ParSInitVar_t Par_S_InitVar[sizeof(SysPar_t)>>1]=
{
/*P0-00*/	{1,  999,    0, 	EEPROM_INIT_VAL,		0},	//EEPROM状态 0X100 0X101
/*P1-01*/	{1,      255,    1, 			1,		0},	//SysID
/*P1-02*/	{1,      2,    0, 			0,		0},	//电角度初始化
/*P1-03*/	{1,      3,    0, 			0,		1},	//// 0-位置模式  1-速度模式
/*P1-04*/	{1,   4000,   20, 		  1500,		1},	//位置控制比例增益
/*P1-05*/	{1,   4000,   20, 		 1000,		1},	//速度控制增益
/*P1-06*/	{1,    200,    1, 		   100,		1},	//速度积分补偿
/*P1-07*/	{1,   10000,    100, 		 3000,		1},	//最大扭矩限制1ma
/*P1-08*/	{1,   20000,  100, 		 9500,		1},	//横动电机盘直径	0.01mm	

/*P1-09*/	{1,   1000,  -1000, 	 0,		3},	//中心点偏移0.1mm
/*P1-10*/	{1,   10000,  0, 		 2500,		1},	//总行程0.1mm
/*P1-11*/	{1,   1000,  0, 		 30,		1},	 // //行程停机补偿量0.1mm  停机缩进
/*P1-12*/	{1,   1000,  0, 		 150,		1},	//导纱频次每分钟往返数     次/min
/*P1-13*/	{1,   200,  0, 		 100,		1},	 //导频变化系数0.01 
/*P1-14*/	{1,   1000,  0, 		 50,		1},	//导频防叠比例 0.1%
/*P1-15*/	{1,   1000,  0, 		 20,		1},	//导频防叠最低持续时间0.1s
/*P1-16*/	{1,   10000,  0, 		 1000,		1},	//运行时间 1min
/*P1-17*/	{1,   5000,  0, 		 50,		1},	//启动时间   0.1s
/*P1-18*/	{1,   5000,  0, 		 50,		1},	//停机时间   0.1s
/*P1-19*/	{1,   1000,  0, 		 300,		1},	//收边宽度0.1mm
/*P1-20*/	{1,   2000,  0, 		 45,		1},	//收边系数
/*P1-21*/	{1,   7,  0, 		 4,		1},  //软边模式
/*P1-22*/	{1,   1000,  0, 		 200,		1},	//软边1宽度0.1mm
/*P1-23*/	{1,   250,  0, 		 10,		1},	//软边1短行程次数
/*P1-24*/	{1,   250,  0, 		 20,		1},	//软边1长行程次数
/*P1-25*/	{1,   1000,  0, 		 60,		1},	//软边2宽度0.1mm
/*P1-26*/	{1,   250,  0, 		 6,		1},	//软边2短行程次数
/*P1-27*/	{1,   10000,  0, 		 5,		1},	//软边2周期
/*P1-28*/	{1,   100,  1, 		 10,		1},	//打结移动速度1-100档
/*P1-29*/	{1,   127,  -128, 	0,		3},	//结点偏移量0.1mm
/*P1-30*/	{1,   127,  -128, 	0,		3},	//结点偏移量0.1mm
/*P1-31*/	{1,   255,  0, 		 10,		1},	//打结位置偏移量1mm
/*P1-32*/	{1,   255,  0, 		 10,		1},	//打结时间1S
/*P1-33*/	{1,   255,  0, 		 10,		1},	//留头偏移量1mm
/*P1-34*/	{1,   255,  0, 		 10,		1},	//留头时间1S
/*P1-35*/	{1,      1,    0, 		 0,	 1},	////0-设定模式  1-跟随模式
/*P1-20*/	{1,   10000,  0, 	100,		1},	//移丝速度    每1ms移丝电机移动脉冲数
/*P1-20*/	{1,   1,  0, 		 1,		1},	//移丝坐标方向  
};
/****************************************************************************************************************/
#if EEPROM_TYPE == EEPROM_USE_FRAM
u16 api_read_sys_par_rt(void)
{
	u16 EpromSts = 0;
	memset(&gSysPar_RT, 0, sizeof(SysParRT_t));
	memset(&gSysPar_RT_Bk, 0, sizeof(SysParRT_t));
	EpromSts = E2Prom(EEPROM_READ, (u16*)&gSysPar_RT, 16, (sizeof(SysParRT_t)>>1)); //ads = 16  偏移16个page
	gSysPar_RT_Bk = gSysPar_RT;
	return EpromSts;

}

u16 api_save_sys_par_rt(void)
{
	u16 EpromSts = 0;

	if(0 != memcmp(&gSysPar_RT, &gSysPar_RT_Bk, sizeof(SysParRT_t)))
	{
		gSysPar_RT_Bk = gSysPar_RT;
		EpromSts = E2Prom(EEPROM_WRITE, (u16*)&gSysPar_RT_Bk, 16, (sizeof(SysParRT_t)>>1)); //ads = 16  偏移16个page

		return EpromSts;
	}
}
#endif



/****************************************************************************************************************/
//参数读取
u16 api_read_sys_par(void)
{
	u16 EpromSts = 0;
	memset(&gSysPar, 0, sizeof(SysPar_t));
	memset(&gSysParBk, 0, sizeof(SysPar_t));
	gSysPar.Index = EEPROM_INIT_VAL + 1;
	EpromSts = sys_par_read((u16*)&gSysPar, 2);
	if(EpromSts != SYSPAR_OK)
	{
		gSysPar.Index = EEPROM_INIT_VAL;
		gSysPar.SysAds = 1;
		sys_par_init((u16*)&gSysPar);
		EpromSts = sys_par_write((u16*)&gSysPar, (sizeof(SysPar_t)>>1));
		return EPROM_ERR;

	}

	if(gSysPar.Index != EEPROM_INIT_VAL)// 
	{
		gSysPar.Index = EEPROM_INIT_VAL;
		sys_par_init((u16*)&gSysPar);
		EpromSts = sys_par_write((u16*)&gSysPar, (sizeof(SysPar_t)>>1));
		if(EpromSts != SYSPAR_OK)
		{
			return EPROM_ERR;
		}
	}
	else
	{
		
		EpromSts = sys_par_read((u16*)&gSysPar, (sizeof(SysPar_t)>>1));
		sys_par_check((u16*)&gSysPar);
	}

	gSysParBk = gSysPar;
	return TRUE;	
}


u16 api_save_sys_par(void)
{
	u16 EpromSts = 0;

	sys_par_check((u16*)&gSysPar);
	if(0 != memcmp(&gSysPar, &gSysParBk, sizeof(SysPar_t)))
	{
		EpromSts = sys_par_write((u16*)&gSysPar, (sizeof(SysPar_t)>>1));
		gSysParBk = gSysPar;
	}
	return EpromSts;

}

u16 api_init_sys_par(void)
{
	u16 EpromSts = 0;
	
	gSysPar.Index = EEPROM_INIT_VAL;
	sys_par_init((u16*)&gSysPar);
	EpromSts = sys_par_write((u16*)&gSysPar, (sizeof(SysPar_t)>>1));
	if(EpromSts != SYSPAR_OK)
	{
		return EPROM_ERR;
	}
	else
		return EpromSts;

}

/****************************************************************************************************************/




/****************************************************************************************************************/
//读取部分系统参数
u16 sys_par_read(u16 *pbf, u16 len)
{

	#if EEPROM_TYPE ==EEPROM_USE_FLASH
	FLASH_Read(FLASH_PARAM_ADDR, pbf, len);	
	return SYSPAR_OK;
	#else
	u16 EpromSts = FALSE,times = 0;

	do{
		EpromSts = E2Prom(EEPROM_READ,pbf,0, len);
		times++;
	}while((EpromSts == FALSE) && (times < 5));
	if(times >= 5) return SYSPAR_READ_ERR;//
	return SYSPAR_OK;
	#endif

}
/****************************************************************************************************************/

/******************************************************************************************************/
//保存系统参数
u16 sys_par_write(u16 *pbf, u16 len)
{
	#if EEPROM_TYPE ==EEPROM_USE_FLASH
	FLASH_Write(FLASH_ZOOM_PARAM, FLASH_PARAM_ADDR, pbf, len);	
	return SYSPAR_OK;
	#else
	u16 EpromSts = FALSE,times = 0;

	do{
		EpromSts = E2Prom(EEPROM_WRITE,pbf,0, len);
		times++;
	}while((EpromSts == FALSE) && (times < 5));
	if(times >= 5) return SYSPAR_WRITE_ERR;// 
	return SYSPAR_OK;
	#endif
}
/******************************************************************************************************/



/****************************************************************************************************************/
//初始化系统参数
void sys_par_init(u16* pbf)
{	
	u16 i=0;
	u16 num = 0;

	while(num < MAX_PAR_NUM)
	{
		if(Par_S_InitVar[num].size == 1)
		{
			if(Par_S_InitVar[num].RstFlag & 0x1)
				*(pbf+i) = Par_S_InitVar[num].Default;
			i++;
		}
		else if(Par_S_InitVar[num].size == 2)
		{	
			
			if(Par_S_InitVar[num].RstFlag & 0x1)
				*(pbf+i) = Par_S_InitVar[num].Default&0xFFFF;
			i++;
			
			if(Par_S_InitVar[num].RstFlag & 0x1)
				*(pbf+i) = Par_S_InitVar[num].Default>>16;
			i++;
		}
			
		num++;
	}

	
}/****************************************************************************************************************/



/****************************************************************************************************************/
u8 sys_par_check(u16* pbf)
{
	u16 i=0;
	u16 num = 0;
	u16 temp = 0;
	s32 temp32 = 0;

	while(num < MAX_PAR_NUM)
	{
		if(Par_S_InitVar[num].size == 1)
		{
			if((Par_S_InitVar[num].RstFlag & 0x2)== 0)
			{
				if(*(pbf+i) > Par_S_InitVar[num].Max)
				{
					*(pbf+i) = Par_S_InitVar[num].Max;
					temp = TRUE;
				}
				else if((*(pbf+i) < Par_S_InitVar[num].Min))
				{
					*(pbf+i) = Par_S_InitVar[num].Min;
					temp = TRUE;
				}
			}
			else
			{
				if((s16)*(pbf+i) > Par_S_InitVar[num].Max)
				{
					*(pbf+i) = (s16)Par_S_InitVar[num].Max;
					temp = TRUE;
				}
				else if((s16)(*(pbf+i) < Par_S_InitVar[num].Min))
				{
					*(pbf+i) = (s16)Par_S_InitVar[num].Min;
					temp = TRUE;
				}

			}
			i++;
		}
		else if(Par_S_InitVar[num].size == 2)
		{			
			if((Par_S_InitVar[num].RstFlag & 0x2)== 0)
			{
				temp32 = (*(pbf+i+1)<<16) + *(pbf+i);
				if(temp32 > Par_S_InitVar[num].Max)
				{
					*(pbf+i) = Par_S_InitVar[num].Max&0xFFFF;
					*(pbf+i+1) = Par_S_InitVar[num].Max>>16;

					temp = TRUE;
				}
				else if(temp32 < Par_S_InitVar[num].Min)
				{
					*(pbf+i) = Par_S_InitVar[num].Min &0xFFFF;
					*(pbf+i+1) = Par_S_InitVar[num].Min>>16;
					
					temp = TRUE;
				}
			}
			else
			{
				temp32 =(s32)( (*(pbf+i+1)<<16) + *(pbf+i));
				if(temp32 > Par_S_InitVar[num].Max)
				{
					*(pbf+i) = Par_S_InitVar[num].Max&0xFFFF;
					*(pbf+i+1) = Par_S_InitVar[num].Max>>16;

					temp = TRUE;
				}
				else if(temp32 < Par_S_InitVar[num].Min)
				{
					*(pbf+i) = Par_S_InitVar[num].Min &0xFFFF;
					*(pbf+i+1) = Par_S_InitVar[num].Min>>16;
					
					temp = TRUE;
				}

			}

			i+=2;
		}
			
		num++;
	}

	return temp;
}/****************************************************************************************************************/

/****************************************************************************************************************/
u16 gSysParLoadAll(void)
{
	u16 sts = 0;

	memset(&gSysPar, 0, sizeof(SysPar_t));
	
	gSysPar.CTL = 0;
	gSysPar.KPP = 1500;
	gSysPar.KVP = 1000;
	gSysPar.KVI = 100;

	gSysPar.HHD = 9500;
	gSysPar.LEN_StopSB = 30;
	gSysPar.SB_W = 0;
	gSysPar.SB_Rto = 45;

	
	gSysPar.ZT_MidOfs = 0;
	gSysPar.LEN = 2000;
	gSysPar.DSPC = 300;
	gSysPar.RunTime = 1000;
	gSysPar.ACC = 50;
	gSysPar.DEC = 50;
	gSysPar.RB_Mode = 7;
	gSysPar.RB1_W = 120;
	gSysPar.RB1_S = 10;
	gSysPar.RB1_L = 8;


	return sts;
}
/****************************************************************************************************************/



