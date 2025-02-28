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
	u16 Index;	//EEPROM状态 0X100 0X101
	u16 SysAds;  
	u16 INIT;// 0-普通模式1-自启动模式2-电角度初始化
	u16 CTL;// 0-位置模式  1-速度模式2 -位置模式2
	u16 KPP;	//位置控制比例增益								PS:OK
	u16 KVP;	//速度控制增益									PS:OK
	u16 KVI;	//速度积分补偿									PS:OK
	u16 MTOR;	//最大扭矩限制	1ma								PS:OK
	u16 HHD;		//横动电机盘直径	0.01mm						PS:OK

	//工艺参数
	s16 ZT_MidOfs;//中心点偏移0.1mm
	u16 LEN;//总行程0.1mm
	u16 LEN_StopSB; //行程停机补偿量0.1mm  停机缩进
	u16 DSPC;//导纱频次每分钟往返数     次/min
	u16 DSPC_Rto; //导频随运行时间变化系数0.01 
	u16 DSPC_FD_RTO;//导频防叠比例 0.1%
	u16 DSPC_FD_Period;//导频防叠周期0.1s
	u16 RunTime;//运行时间 1min
	u16 ACC; //启动时间   0.1s
	u16 DEC; //停机时间   0.1s
	u16 SB_W;//收边宽度0.1mm
	u16 SB_Rto;// 收边系数0.01
	u16 RB_Mode;//软边模式
	u16 RB1_W;//软边1宽度0.1mm
	u16 RB1_S;//软边1短行程次数
	u16 RB1_L;//软边1长行程次数
	u16 RB2_W;//软边2宽度0.1mm
	u16 RB2_S;//软边2短行程次数
	u16 RB2_T;//软边2参数
	u16 DJ_Spd;//打结移动速度1-100档
	s16 DJ_Ofs;//结点偏移量0.1mm
	s16 DJ_Ofs_BC;//结点偏移量0.1mm  补偿值
	u16 DJ_Ofs_O;//打结位置偏移量1mm
	u16 DJ_Time;//打结时间1S
	u16 LT_Ofs;//留头偏移1mm
	u16 LT_Time;//留头时间1S
	u16 DSPC_Mode;//导频控制模式 0-设定模式  1-跟随模式
	u16 YS_Spd;//移丝速度    每1ms移丝电机移动脉冲数
	u16 YS_Dir;//移丝坐标方向  
	


}SysPar_t;
//---------------------------------------------------------------------------------------//
typedef struct{
	u32 RunTimeCur;
	u32 RunTimeGvn;
	u16 SB_W;
	u16 SB_Rto;
	float SB_L;
	u16 Flag;//  = 0xA54B 为有效
}SysParRT_t;



extern SysPar_t gSysPar;
extern SysPar_t gSysParBk;
extern SysParRT_t gSysPar_RT;
extern SysParRT_t gSysPar_RT_Bk;

//---------------------------------------------------------------------------------------//
//参数类型及参数初值结构体
typedef struct{
	u32 size;
	s32 Max;
	s32 Min;
	s32 Default;
	u32 RstFlag;//bit0 - 是否允许复位   bit1-是否为有符号数
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
