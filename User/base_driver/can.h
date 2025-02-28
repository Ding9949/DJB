#ifndef __CAN_H
#define __CAN_H	 

#include "gd32f30x.h"

//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    
enum {
	CAN_BAUDRATE_1M = 0,
	CAN_BAUDRATE_800K,
	CAN_BAUDRATE_500K,
	CAN_BAUDRATE_250K,
	CAN_BAUDRATE_100K,
	CAN_BAUDRATE_10K,
};


struct Filter32Bit{
	u32 	RES:1;
	u32 RTR:1;
	u32 IDE:1;
	u32 EXID0:1;
	u32 EXID1:1;
	u32 EXID2:1;
	u32 EXID3:1;
	u32 EXID4:1;
	u32 EXID5:1;
	u32 EXID6:1;
	u32 EXID7:1;
	u32 EXID8:1;
	u32 EXID9:1;
	u32 EXID10:1;
	u32 EXID11:1;
	u32 EXID12:1;
	u32 EXID13:1;
	u32 EXID14:1;
	u32 EXID15:1;
	u32 EXID16:1;
	u32 EXID17:1;
	u32 STID0:1;
	u32 STID1:1;
	u32 STID2:1;
	u32 STID3:1;
	u32 STID4:1;
	u32 STID5:1;
	u32 STID6:1;
	u32 STID7:1;
	u32 STID8:1;
	u32 STID9:1;
	u32 STID10:1;
};

typedef union _Filter32ID
{
	u32 all;
	struct Filter32Bit bit;
}Filter32ID;

typedef union _Filter32Mask
{
	u32 all;
	struct Filter32Bit bit;
}Filter32Mask;

typedef struct _CanMsg_s
{
	u32 StdId;
	u32 ExtId;
	u8 IDE;
	u8 RTR;
	u8 DLC; 
	u8 Data[8]; 
	u8 FMI;
}CanMsg_t;
										 							 				    
u8 can_conf(unsigned char baudrate);
void can_set_filter32(u8 num, Filter32ID id, Filter32Mask mask);
u8 can_send_msg(CanMsg_t* msg);						//发送数据
u8 can1_send_msg(CanMsg_t* msg);
u8 can_receive_msg(u8 *buf);							//接收数据
#endif

















