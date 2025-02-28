/*
 *
 *  Created on: 2017��8��16��
 *      Author: Wuych
 */

 #ifndef __api_excom_task_h
#define __api_excom_task_h

#include "sys_bsp.h"



#define EXCMD_F0 0xf0 // ��ȡ����UID
#define EXCMD_F1 0xf1 // UID  ƥ��
#define EXCMD_F2 0xf2 // ���õ�ַ
#define EXCMD_F3 0xf3 // �˳����õ�ַ
#define EXCMD_D0 0xD0 // ���õ�������
#define EXCMD_D1 0xD1 //�ϵ��ʼ������
#define EXCMD_E0 0xE0 // ��ȡ��������
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
#define EXCMD_C0 0xC0 // ��ѯ����״̬



typedef struct _DisCom_s
{

	u16 RxdIndex;
	u16 RxdFlag; // ������ɱ�־
	u16 RxdTicker;
	u16 RxdLen;
	
	u16 TxdSts;
	u16 TxdFlag;//ͨ�ŷ���ʹ�ܱ�־
	u16 TxdLen;//���͵��ֽ���
	u16 TxdCnt;
	u16 TxdErr;
	u16 TxdDly;

	
	u32 ConnectTicker;	//Ⱥͨ�������жϼ�����
	u8 ConnectFlag;//Ⱥͨ�������жϱ�־

	u8 ParOk ;//Ⱥͨ�Ų����Ѹ��±�־
	u16 ParRequestFlag; //���������־
	u16 ParRxFlag; //������־��־
	u16 ParTransDlyCnt;
	

	u8 ADS;  //��ַ
	u8 ADS_Bk;
	u8 ParSave;
	u32 ParSaveDlyCnt;

	//ID����
	u8 UID_ReadFlag;//0-û�ж�ȡ  1-���ڶ�ȡ
	u16 UID_ReadDlyCnt;//UID ��ȡ�ظ��ӳ�
	u32 UID;//ѡ�е�UID
	u8 ID;
	//�ض���������
	u8 PAR_ReadFlag;// 0-��ʼ״̬ 1-����CAN  2-�ض���  3 �ض�����
	u8 PAR_ID;//�ض��������
	u16 PAR_ReadDlyCnt;//��ʱ


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
