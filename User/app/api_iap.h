#ifndef __api_iap_h
#define __api_iap_h


#include "sys_bsp.h"
#include "drv_flash.h"


#define RS485_TX_MAX              20
#define RS485_RX_MAX             1034// (1024+10)


#define USART_BUS_TXD 1
#define USART_BUS_RXD 0


#define RS485_TX_HEAD1      0xA6
#define RS485_RX_HEAD1      0xA5

#define RS485_CMD_IAP_UPDATE			0x24	// App data
#define RS485_CMD_IAP_EXIT			0x25	// 退出升级


#define CAN_CMD_IAP_UPDATE 0x4f
#define CAN_CMD_IAP_READY 0x4e
#define CAN_CMD_IAP_TRANS 0x4d
#define CAN_CMD_IAP_FINISH_SECTOR 0x4c
#define CAN_CMD_IAP_FINISH_ALL 0x4b




#define IAP_SECTOR_SIZE 1024

enum {
	STS_INIT = 0,
	STS_UPDATE, 
	STS_FINISH,
	STS_START_APP
};



typedef  void (*iapfun)(void);				//定义一个函数类型的参数.

typedef struct _IapMarkInfo_s
{
	u16 IapMarkWord; // 0-正常启动  1 2 CAN 升级  3 4 485升级
	u16 BootVer;
	u16 AppVer;
	u16 BaudRate;
	u16 ID;
}IapMarkInfo_t;

typedef struct _IapSectorBuf_s
{
	u8 data[IAP_SECTOR_SIZE];
	u8 idxflag[IAP_SECTOR_SIZE>>3];
	u8 sector;
	u8 errflag;
	u16 len;
}IapSectorBuf_t;


typedef struct
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

	

	u8 RecBuf[RS485_RX_MAX];
	u8 TxdBuf[RS485_TX_MAX];
}
RS485_T;
				
extern RS485_T RS485;

typedef struct _Iap_s
{

	u8 Sts;   


	u8 CmdUpdate;
	u8 CmdReady;
	u8 CmdFinishSector;
	u8 CmdFinishAll;

	
	u8 UpErr; 



	u32 TimeOutCnt;


}Iap_t;

extern Iap_t IapCtl;
extern IapMarkInfo_t IapMarkInfo;


void iap_init(void);
void iap_get_mark(void);
void iap_save_mark(void);
void iap_write_sector(u8 sector,  u8 *appbuf,u32 appsize);
void iap_load_app(u32 appxaddr);
void iap_trans_app(u8 sector,  u8 idx, u8* data);
void iap_parse_can_msg(CanMsg_t* pMsg);
void iap_process(void);
void iap_485_rx(void);
void iap_485_tx(u16 len);
void iap_485_process(void);





#endif
