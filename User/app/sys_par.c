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
/*P0-00*/	{1,  999,    0, 	EEPROM_INIT_VAL,		0},	//EEPROM״̬ 0X100 0X101
/*P1-01*/	{1,      255,    1, 			1,		0},	//SysID
/*P1-02*/	{1,      2,    0, 			0,		0},	//��Ƕȳ�ʼ��
/*P1-03*/	{1,      3,    0, 			0,		1},	//// 0-λ��ģʽ  1-�ٶ�ģʽ
/*P1-04*/	{1,   4000,   20, 		  1500,		1},	//λ�ÿ��Ʊ�������
/*P1-05*/	{1,   4000,   20, 		 1000,		1},	//�ٶȿ�������
/*P1-06*/	{1,    200,    1, 		   100,		1},	//�ٶȻ��ֲ���
/*P1-07*/	{1,   10000,    100, 		 3000,		1},	//���Ť������1ma
/*P1-08*/	{1,   20000,  100, 		 9500,		1},	//�ᶯ�����ֱ��	0.01mm	

/*P1-09*/	{1,   1000,  -1000, 	 0,		3},	//���ĵ�ƫ��0.1mm
/*P1-10*/	{1,   10000,  0, 		 2500,		1},	//���г�0.1mm
/*P1-11*/	{1,   1000,  0, 		 30,		1},	 // //�г�ͣ��������0.1mm  ͣ������
/*P1-12*/	{1,   1000,  0, 		 150,		1},	//��ɴƵ��ÿ����������     ��/min
/*P1-13*/	{1,   200,  0, 		 100,		1},	 //��Ƶ�仯ϵ��0.01 
/*P1-14*/	{1,   1000,  0, 		 50,		1},	//��Ƶ�������� 0.1%
/*P1-15*/	{1,   1000,  0, 		 20,		1},	//��Ƶ������ͳ���ʱ��0.1s
/*P1-16*/	{1,   10000,  0, 		 1000,		1},	//����ʱ�� 1min
/*P1-17*/	{1,   5000,  0, 		 50,		1},	//����ʱ��   0.1s
/*P1-18*/	{1,   5000,  0, 		 50,		1},	//ͣ��ʱ��   0.1s
/*P1-19*/	{1,   1000,  0, 		 300,		1},	//�ձ߿��0.1mm
/*P1-20*/	{1,   2000,  0, 		 45,		1},	//�ձ�ϵ��
/*P1-21*/	{1,   7,  0, 		 4,		1},  //���ģʽ
/*P1-22*/	{1,   1000,  0, 		 200,		1},	//���1���0.1mm
/*P1-23*/	{1,   250,  0, 		 10,		1},	//���1���г̴���
/*P1-24*/	{1,   250,  0, 		 20,		1},	//���1���г̴���
/*P1-25*/	{1,   1000,  0, 		 60,		1},	//���2���0.1mm
/*P1-26*/	{1,   250,  0, 		 6,		1},	//���2���г̴���
/*P1-27*/	{1,   10000,  0, 		 5,		1},	//���2����
/*P1-28*/	{1,   100,  1, 		 10,		1},	//����ƶ��ٶ�1-100��
/*P1-29*/	{1,   127,  -128, 	0,		3},	//���ƫ����0.1mm
/*P1-30*/	{1,   127,  -128, 	0,		3},	//���ƫ����0.1mm
/*P1-31*/	{1,   255,  0, 		 10,		1},	//���λ��ƫ����1mm
/*P1-32*/	{1,   255,  0, 		 10,		1},	//���ʱ��1S
/*P1-33*/	{1,   255,  0, 		 10,		1},	//��ͷƫ����1mm
/*P1-34*/	{1,   255,  0, 		 10,		1},	//��ͷʱ��1S
/*P1-35*/	{1,      1,    0, 		 0,	 1},	////0-�趨ģʽ  1-����ģʽ
/*P1-20*/	{1,   10000,  0, 	100,		1},	//��˿�ٶ�    ÿ1ms��˿����ƶ�������
/*P1-20*/	{1,   1,  0, 		 1,		1},	//��˿���귽��  
};
/****************************************************************************************************************/
#if EEPROM_TYPE == EEPROM_USE_FRAM
u16 api_read_sys_par_rt(void)
{
	u16 EpromSts = 0;
	memset(&gSysPar_RT, 0, sizeof(SysParRT_t));
	memset(&gSysPar_RT_Bk, 0, sizeof(SysParRT_t));
	EpromSts = E2Prom(EEPROM_READ, (u16*)&gSysPar_RT, 16, (sizeof(SysParRT_t)>>1)); //ads = 16  ƫ��16��page
	gSysPar_RT_Bk = gSysPar_RT;
	return EpromSts;

}

u16 api_save_sys_par_rt(void)
{
	u16 EpromSts = 0;

	if(0 != memcmp(&gSysPar_RT, &gSysPar_RT_Bk, sizeof(SysParRT_t)))
	{
		gSysPar_RT_Bk = gSysPar_RT;
		EpromSts = E2Prom(EEPROM_WRITE, (u16*)&gSysPar_RT_Bk, 16, (sizeof(SysParRT_t)>>1)); //ads = 16  ƫ��16��page

		return EpromSts;
	}
}
#endif



/****************************************************************************************************************/
//������ȡ
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
//��ȡ����ϵͳ����
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
//����ϵͳ����
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
//��ʼ��ϵͳ����
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



