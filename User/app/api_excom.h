/*
 *
 *  Created on: 2017年8月16日
 *      Author: Wuych
 */

 #ifndef __api_excom_task_h
#define __api_excom_task_h

#include "sys_bsp.h"



#define EXCMD_F0 0xf0 // 读取单锭UID
#define EXCMD_F1 0xf1 // UID  匹配
#define EXCMD_F2 0xf2 // 设置地址
#define EXCMD_F3 0xf3 // 退出设置地址
#define EXCMD_D0 0xD0 // 设置单锭参数
#define EXCMD_D1 0xD1 //上电初始化参数
#define EXCMD_E0 0xE0 // 读取单锭参数
#define EXCMD_E1 0xE1
#define EXCMD_E2 0xE2
#define EXCMD_E3 0xE3
#define EXCMD_E4 0xE4
#define EXCMD_E5 0xE5
#define EXCMD_E6 0xE6
#define EXCMD_E7 0xE7
#define EXCMD_E8 0xE8
#define EXCMD_E9 0xE9
#define EXCMD_EA 0xEA
#define EXCMD_EB 0xEB
#define EXCMD_C0 0xC0 // 查询单锭状态



typedef struct _DisCom_s
{

	u16 RxdIndex;
	u16 RxdFlag; // 接收完成标志
	u16 RxdTicker;
	u16 RxdLen;
	
	u16 TxdSts;
	u16 TxdFlag;//通信发送使能标志
	u16 TxdLen;//发送的字节数
	u16 TxdCnt;
	u16 TxdErr;
	u16 TxdDly;

	
	u32 ConnectTicker;	//群通信连接判断计数器
	u8 ConnectFlag;//群通信连接判断标志

	u8 ParOk ;//群通信参数已更新标志
	u16 ParRequestFlag; //参数请求标志
	u16 ParRxFlag; //参数标志标志
	u16 ParTransDlyCnt;
	

	u8 ADS;  //地址
	u8 ADS_Bk;
	u8 ParSave;
	u32 ParSaveDlyCnt;

	//ID配置
	u8 UID_ReadFlag;//0-没有读取  1-正在读取
	u16 UID_ReadDlyCnt;//UID 读取回复延迟
	u32 UID;//选中的UID
	u8 ID;
	//回读单锭参数
	u8 PAR_ReadFlag;// 0-初始状态 1-发送CAN  2-回读中  3 回读结束
	u8 PAR_ID;//回读参数标号
	u16 PAR_ReadDlyCnt;//超时


	u32 rx_ok;
	u32 chk_ok;
	u32 tx_ok;

	u8 RecBuf[100];
	u8 TxdBuf[100];

}ExCom_t;




extern ExCom_t gExCom;



void excom_init(void);
void excom_rx(u8 temp);
void excom_tx(u16 len);
void excom_task(void);

#endif
