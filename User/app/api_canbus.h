#ifndef __api_canbus_h
#define __api_canbus_h

#include "sys_bsp.h"
#include "sys_par.h"


#define MAX_NODE_NUM 12  //

#define MAX_RESEND_NUM 1




#define CAN_CMD_ID 0x00
#define CAN_CMD_SET_PAR 0x41 
#define CAN_CMD_CTL 0x42 
#define CAN_CMD_READ_PAR 0x43 
#define CAN_CMD_STATUS1 0x44 
#define CAN_CMD_SET_CURTIME 0x45 
#define CAN_CMD_POS 0x46

#define CAN_CMD_SET_PAR_ACK 0x51 
#define CAN_CMD_CTL_ACK 0x52 
#define CAN_CMD_READ_PAR_ACK 0x53 
#define CAN_CMD_STATUS1_ACK 0x54 
#define CAN_CMD_SET_CURTIME_ACK 0x55 
#define CAN_CMD_POS_ACK 0x56


enum {
	STS_INIT = 0,
	STS_WAIT_SEND,
	STS_WAIT_OVER_TIME,
	STS_LOAD,
	STS_SEND,
	STS_OVER_TIME,
	STS_PARSE,
};

enum {
	CMD_FLASH = 0x1,  
	CMD_SET1 = 0x2,
};




typedef struct _CanBusCtl_s
{
	//CAN1
	u8 State; // 0-��������  1-�·� 2-�ȴ�  3-��������
	u8 CurID;
	u8 CurCmd;
	u8 CurNode;
	u8 CurIndex;
	u16 MaxIndex;//���֡��
	u8 RxFlag;//0-δ�յ�  1-�����յ�2-ȫ���յ�   
	u8 FinalFrame;// 1-��ʾΪ���һ֡����
	u16 WaitCnt;//�ȴ�������


	u8 DataRequestMain[MAX_NODE_NUM];//��Ҫ�������󣬻�����߽���С��
	u8 ComErrCnt[MAX_NODE_NUM];//���ڵ�ͨ���쳣
	u8 ComErr[MAX_NODE_NUM];
	u16 Flg_StsReadMask[MAX_NODE_NUM];
	u16 Flg_ParReadMask;

	// ID����
	u8 UID_Idx;
	u8 UID_Sts;
	u32 UID[MAX_NODE_NUM];
	u8 ID[MAX_NODE_NUM];
	
	u8 ReSendCnt;

	CanMsg_t TxMsg; //�������ݻ���
	CanMsg_t RxMsg; //�������ݻ���
}CanBusCtl_t;


typedef struct{
	s16 HD_Spd;//��ɴ�ٶ�
	s32 HD_PosCur;//��ɴ��ǰλ��
	s32 SG_PosCur;//˿�˵�ǰλ��
	u32 RunTimeCur;// 1min
	u16 DSPC;
	u16 Verson_App;
	u16 Verson_Boot;
	u16 CurLEN;//0.1mm
	s8 ErrL;
	s8 ErrR;
	u8 Sts;//
	u8 Err;
}StsVal_t;

extern CanBusCtl_t gCanBusCtl1;
extern StsVal_t gStsVal[MAX_NODE_NUM];
extern SysPar_t gSysPar_RdBack;
void can1_parse_msg(CanMsg_t* pMsg);
void can_task_init(void);
void can1_task(void);

#endif
