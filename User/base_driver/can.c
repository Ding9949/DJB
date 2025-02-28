#include <string.h>
#include "can.h"
#include "delay.h"

//CAN初始化
//tsjw:重新同步跳跃时间单元.范围:1~3; CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
//tbs2:时间段2的时间单元.范围:1~8;
//tbs1:时间段1的时间单元.范围:1~16;	  CAN_BS1_1tq ~CAN_BS1_16tq
//brp :波特率分频器.范围:1~1024;(实际要加1,也就是1~1024) tq=(brp)*tpclk1
typedef struct _can_baudrate_s
{
	unsigned char tsjw;
	unsigned char tbs1;
	unsigned char tbs2;
	unsigned short brp;
}can_baudrate_t;

//波特率=Fpclk1/((tsjw+tbs1+tbs2)*brp);
/* 1MBps   主频120M   波特率 = 60M  / (prescaler*(CAN_BT_SJW_1TQ+CAN_BT_BS1_5TQ+CAN_BT_BS2_4TQ))  = 60M /(6*(1+5+4))  = 1M*/

static void _get_baud_rate(unsigned char baudrate, can_baudrate_t* p)
{
	switch(baudrate)
	{
	case CAN_BAUDRATE_1M:
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_5TQ;
		p->tbs2 = CAN_BT_BS2_4TQ;
		p->brp = 6;
		break;
	case CAN_BAUDRATE_800K: 
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_8TQ;
		p->tbs2 = CAN_BT_BS2_6TQ;
		p->brp = 5;
		break;
	case CAN_BAUDRATE_500K: 
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_5TQ;
		p->tbs2 = CAN_BT_BS2_4TQ;
		p->brp = 12;
		break;
	case CAN_BAUDRATE_250K: 
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_5TQ;
		p->tbs2 = CAN_BT_BS2_4TQ;
		p->brp = 24;
		break;
	case CAN_BAUDRATE_100K: 
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_5TQ;
		p->tbs2 = CAN_BT_BS2_4TQ;
		p->brp = 60;
		break;
	case CAN_BAUDRATE_10K: 
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_5TQ;
		p->tbs2 = CAN_BT_BS2_4TQ;
		p->brp = 600;
		break;
	default:
		p->tsjw = CAN_BT_SJW_1TQ;
		p->tbs1 = CAN_BT_BS1_6TQ;
		p->tbs2 = CAN_BT_BS2_5TQ;
		p->brp = 6;
		break;
	}
}
//CAN初始化
//注意以上参数任何一个都不能设为0,否则会乱.
//mode:0,普通模式;1,回环模式;
//返回值:0,初始化OK;
//    其他,初始化失败;

u8 can_conf(unsigned char baudrate)
{


	can_parameter_struct can_parameter;
	can_baudrate_t p;

	_get_baud_rate(baudrate, &p);
            											 

	rcu_periph_clock_enable(RCU_CAN0);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_AF);

	gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_12);

	can_struct_para_init(CAN_INIT_STRUCT, &can_parameter);
	/* initialize CAN register */
	can_deinit(CAN0);

	/* initialize CAN parameters */
	can_parameter.time_triggered = DISABLE;
	can_parameter.auto_bus_off_recovery = DISABLE;
	can_parameter.auto_wake_up = DISABLE;
	can_parameter.no_auto_retrans = DISABLE;
	can_parameter.rec_fifo_overwrite = DISABLE;
	can_parameter.trans_fifo_order = DISABLE;
	can_parameter.working_mode = CAN_NORMAL_MODE;
	can_parameter.resync_jump_width = p.tsjw;;
	can_parameter.time_segment_1 = p.tbs1;
	can_parameter.time_segment_2 = p.tbs2;
	can_parameter.prescaler = p.brp;



		
	/* initialize CAN */
	can_init(CAN0, &can_parameter);




	
    can_interrupt_enable(CAN0, CAN_INT_RFNE0);

#if CAN_RX0_INT_ENABLE
	nvic_irq_enable(USBD_LP_CAN0_RX0_IRQn,1,0);
#endif

	return 0;
}   

void can_set_filter32(u8 num, Filter32ID id, Filter32Mask mask)
{

	can_filter_parameter_struct can_filter;


	can_filter.filter_number=num; //过滤器号
	can_filter.filter_mode = CAN_FILTERMODE_MASK;
	can_filter.filter_bits = CAN_FILTERBITS_32BIT; //32位 
	can_filter.filter_list_high = (id.all>>16)&0xFFFF;////32位ID
	can_filter.filter_list_low = id.all&0xFFFF;
	can_filter.filter_mask_high = (mask.all>>16)&0xFFFF;//32位MASK
	can_filter.filter_mask_low = mask.all&0xFFFF;
	can_filter.filter_fifo_number = CAN_FIFO0;//过滤器0关联到FIFO0
	can_filter.filter_enable = ENABLE;

	can_filter_init(&can_filter);

}

 
#if CAN_RX0_INT_ENABLE	//使能RX0中断
//中断服务函数	
void can_msg_parse(CanMsg_t* pMsg);
void USBD_LP_CAN0_RX0_IRQHandler(void)
{
		
	can_receive_message_struct RxMessage1;
	CanMsg_t RxMessage2;	
	u8 i=0;
	can_message_receive(CAN0, CAN_FIFO0, &RxMessage1);
	// 需要做一些id、过滤器处理
	RxMessage2.StdId=RxMessage1.rx_sfid;				
	RxMessage2.ExtId=RxMessage1.rx_efid;				
	RxMessage2.IDE=RxMessage1.rx_ff;			
	RxMessage2.RTR=RxMessage1.rx_ft;		
	RxMessage2.DLC=RxMessage1.rx_dlen;						
	for(i=0;i<8;i++)
		RxMessage2.Data[i]=RxMessage1.rx_data[i];				
	can_msg_parse(&RxMessage2);

}
#endif

//can发送一组数据(固定格式:ID为0X12,标准帧,数据帧)	
//len:数据长度(最大为8)				     
//msg:数据指针,最大为8个字节.
//返回值:0,成功;
//		 其他,失败;
u8 can_send_msg(CanMsg_t* msg)
{	
	u8 mbox;
	u16 i=0;
	can_trasnmit_message_struct TxMessage;
	
	TxMessage.tx_sfid=msg->StdId;					 // 标准标识符为0
	TxMessage.tx_efid=msg->ExtId;				 // 设置扩展标示符（29位）
	TxMessage.tx_ff=CAN_FF_EXTENDED;//msg->IDE;			 // 使用扩展标识符
	TxMessage.tx_ft=CAN_FT_DATA;		 // 消息类型为数据帧，一帧8位
	TxMessage.tx_dlen=msg->DLC;							 // 发送两帧信息
	for(i=0;i<8;i++)
		TxMessage.tx_data[i]=msg->Data[i];				 // 第一帧信息      
		
	mbox= can_message_transmit(CAN0, &TxMessage);   
	
	i=0;
	while((can_transmit_states(CAN0, mbox)==CAN_TRANSMIT_FAILED)&&(i<0XFFF))//等待发送结束
		i++;	
		
	if(i>=0XFFF)
		return 1;
		
	return 0;		

}


u8 can1_send_msg(CanMsg_t* msg)
{	
	u8 mbox;
	u16 i=0;
	can_trasnmit_message_struct TxMessage;
	
	TxMessage.tx_sfid=msg->StdId;					 // 标准标识符为0
	TxMessage.tx_efid=msg->ExtId;				 // 设置扩展标示符（29位）
	TxMessage.tx_ff=CAN_FF_EXTENDED;//msg->IDE;			 // 使用扩展标识符
	TxMessage.tx_ft=CAN_FT_DATA;		 // 消息类型为数据帧，一帧8位
	TxMessage.tx_dlen=msg->DLC;							 // 发送两帧信息
	for(i=0;i<8;i++)
		TxMessage.tx_data[i]=msg->Data[i];				 // 第一帧信息      
		
	mbox= can_message_transmit(CAN0, &TxMessage);   
	
	//i=0;
	//while((can_transmit_states(CAN0, mbox)==CAN_TRANSMIT_FAILED)&&(i<0XFFF))//等待发送结束
	//	i++;	
		
	//if(i>=0XFFF)
	//	return 1;
		
	return 0;		

}

//can口接收数据查询
//buf:数据缓存区;	 
//返回值:0,无数据被收到;
//		 其他,接收的数据长度;
u8 can_receive_msg(u8 *buf)
{		   		   
	u32 i;
	can_receive_message_struct RxMessage;
	
	//没有接收到数据,直接退出 	
	if( (CAN_RFIFO0(CAN0))  & CAN_RFIFO0_RFL0  == 0)
		return 0;		
		
	//读取数据			
	can_message_receive(CAN0, CAN_FIFO0, &RxMessage);
		
	for(i=0;i<8;i++)
		buf[i]=RxMessage.rx_data[i];  
	
	return RxMessage.rx_dlen;	
}



