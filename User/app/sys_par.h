#ifndef __sys_par_h
#define __sys_par_h

#include "sys_bsp.h"



enum{
	PAR_OK=0,
	PAR_OVR1 = 0x01,
	PAR_OVR2 = 0x02,
	EPROM_ERR = 0x04
};

enum{
	SYSPAR_OK = 0,		//
	SYSPAR_READ_ERR,	//
	SYSPAR_WRITE_ERR,	//
	SYSPAR_CHECK_ERR	//
};

//---------------------------------------------------------------------------------------//
#define EEPROM_INIT_VAL 0x0303
#define MAX_PAR_NUM (sizeof(SysPar_t)>>1)
#define EEPROM_USE_FLASH 0
#define EEPROM_USE_FRAM 1
#define EEPROM_TYPE EEPROM_USE_FRAM
//---------------------------------------------------------------------------------------//


//------------------------------P1--------------------------------------------------------//
typedef struct{
	u16 Index;	//EEPROM״̬ 0X100 0X101
	u16 SysAds;  
	u16 INIT;// 0-��ͨģʽ1-������ģʽ2-��Ƕȳ�ʼ��
	u16 CTL;// 0-λ��ģʽ  1-�ٶ�ģʽ2 -λ��ģʽ2
	u16 KPP;	//λ�ÿ��Ʊ�������								PS:OK
	u16 KVP;	//�ٶȿ�������									PS:OK
	u16 KVI;	//�ٶȻ��ֲ���									PS:OK
	u16 MTOR;	//���Ť������	1ma								PS:OK
	u16 HHD;		//�ᶯ�����ֱ��	0.01mm						PS:OK

	//���ղ���
	s16 ZT_MidOfs;//���ĵ�ƫ��0.1mm
	u16 LEN;//���г�0.1mm
	u16 LEN_StopSB; //�г�ͣ��������0.1mm  ͣ������
	u16 DSPC;//��ɴƵ��ÿ����������     ��/min
	u16 DSPC_Rto; //��Ƶ������ʱ��仯ϵ��0.01 
	u16 DSPC_FD_RTO;//��Ƶ�������� 0.1%
	u16 DSPC_FD_Period;//��Ƶ��������0.1s
	u16 RunTime;//����ʱ�� 1min
	u16 ACC; //����ʱ��   0.1s
	u16 DEC; //ͣ��ʱ��   0.1s
	u16 SB_W;//�ձ߿��0.1mm
	u16 SB_Rto;// �ձ�ϵ��0.01
	u16 RB_Mode;//���ģʽ
	u16 RB1_W;//���1���0.1mm
	u16 RB1_S;//���1���г̴���
	u16 RB1_L;//���1���г̴���
	u16 RB2_W;//���2���0.1mm
	u16 RB2_S;//���2���г̴���
	u16 RB2_T;//���2����
	u16 DJ_Spd;//����ƶ��ٶ�1-100��
	s16 DJ_Ofs;//���ƫ����0.1mm
	s16 DJ_Ofs_BC;//���ƫ����0.1mm  ����ֵ
	u16 DJ_Ofs_O;//���λ��ƫ����1mm
	u16 DJ_Time;//���ʱ��1S
	u16 LT_Ofs;//��ͷƫ��1mm
	u16 LT_Time;//��ͷʱ��1S
	u16 DSPC_Mode;//��Ƶ����ģʽ 0-�趨ģʽ  1-����ģʽ
	u16 YS_Spd;//��˿�ٶ�    ÿ1ms��˿����ƶ�������
	u16 YS_Dir;//��˿���귽��  
	


}SysPar_t;
//---------------------------------------------------------------------------------------//
typedef struct{
	u32 RunTimeCur;
	u32 RunTimeGvn;
	u16 SB_W;
	u16 SB_Rto;
	float SB_L;
	u16 Flag;//  = 0xA54B Ϊ��Ч
}SysParRT_t;



extern SysPar_t gSysPar;
extern SysPar_t gSysParBk;
extern SysParRT_t gSysPar_RT;
extern SysParRT_t gSysPar_RT_Bk;

//---------------------------------------------------------------------------------------//
//�������ͼ�������ֵ�ṹ��
typedef struct{
	u32 size;
	s32 Max;
	s32 Min;
	s32 Default;
	u32 RstFlag;//bit0 - �Ƿ�����λ   bit1-�Ƿ�Ϊ�з�����
}ParSInitVar_t;
//---------------------------------------------------------------------------------------//


#if EEPROM_TYPE == EEPROM_USE_FRAM
u16 api_read_sys_par_rt(void);
u16 api_save_sys_par_rt(void);
#endif
u16 api_read_sys_par(void);
u16 api_save_sys_par(void);
u16 api_init_sys_par(void);

u16 sys_par_read(u16 *pbf, u16 len);
u16 sys_par_write(u16 *pbf, u16 len);
void sys_par_init(u16* pbf);
u8 sys_par_check(u16* pbf);

#endif
