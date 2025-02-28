#include <string.h>
#include "can.h"
#include "delay.h"

//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:1~3; CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.��Χ:1~8;
//tbs1:ʱ���1��ʱ�䵥Ԫ.��Χ:1~16;	  CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024;(ʵ��Ҫ��1,Ҳ����1~1024) tq=(brp)*tpclk1
typedef struct _can_baudrate_s
{
	unsigned char tsjw;
	unsigned char tbs1;
	unsigned char tbs2;
	unsigned short brp;
}can_baudrate_t;

//������=Fpclk1/((tsjw+tbs1+tbs2)*brp);
/* 1MBps   ��Ƶ120M   ������ = 60M  / (prescaler*(CAN_BT_SJW_1TQ+CAN_BT_BS1_5TQ+CAN_BT_BS2_4TQ))  = 60M /(6*(1+5+4))  = 1M*/

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
//CAN��ʼ��
//ע�����ϲ����κ�һ����������Ϊ0,�������.
//mode:0,��ͨģʽ;1,�ػ�ģʽ;
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��;

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


	can_filter.filter_number=num; //��������
	can_filter.filter_mode = CAN_FILTERMODE_MASK;
	can_filter.filter_bits = CAN_FILTERBITS_32BIT; //32λ 
	can_filter.filter_list_high = (id.all>>16)&0xFFFF;////32λID
	can_filter.filter_list_low = id.all&0xFFFF;
	can_filter.filter_mask_high = (mask.all>>16)&0xFFFF;//32λMASK
	can_filter.filter_mask_low = mask.all&0xFFFF;
	can_filter.filter_fifo_number = CAN_FIFO0;//������0������FIFO0
	can_filter.filter_enable = ENABLE;

	can_filter_init(&can_filter);

}

 
#if CAN_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����	
void can_msg_parse(CanMsg_t* pMsg);
void USBD_LP_CAN0_RX0_IRQHandler(void)
{
		
	can_receive_message_struct RxMessage1;
	CanMsg_t RxMessage2;	
	u8 i=0;
	can_message_receive(CAN0, CAN_FIFO0, &RxMessage1);
	// ��Ҫ��һЩid������������
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

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 can_send_msg(CanMsg_t* msg)
{	
	u8 mbox;
	u16 i=0;
	can_trasnmit_message_struct TxMessage;
	
	TxMessage.tx_sfid=msg->StdId;					 // ��׼��ʶ��Ϊ0
	TxMessage.tx_efid=msg->ExtId;				 // ������չ��ʾ����29λ��
	TxMessage.tx_ff=CAN_FF_EXTENDED;//msg->IDE;			 // ʹ����չ��ʶ��
	TxMessage.tx_ft=CAN_FT_DATA;		 // ��Ϣ����Ϊ����֡��һ֡8λ
	TxMessage.tx_dlen=msg->DLC;							 // ������֡��Ϣ
	for(i=0;i<8;i++)
		TxMessage.tx_data[i]=msg->Data[i];				 // ��һ֡��Ϣ      
		
	mbox= can_message_transmit(CAN0, &TxMessage);   
	
	i=0;
	while((can_transmit_states(CAN0, mbox)==CAN_TRANSMIT_FAILED)&&(i<0XFFF))//�ȴ����ͽ���
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
	
	TxMessage.tx_sfid=msg->StdId;					 // ��׼��ʶ��Ϊ0
	TxMessage.tx_efid=msg->ExtId;				 // ������չ��ʾ����29λ��
	TxMessage.tx_ff=CAN_FF_EXTENDED;//msg->IDE;			 // ʹ����չ��ʶ��
	TxMessage.tx_ft=CAN_FT_DATA;		 // ��Ϣ����Ϊ����֡��һ֡8λ
	TxMessage.tx_dlen=msg->DLC;							 // ������֡��Ϣ
	for(i=0;i<8;i++)
		TxMessage.tx_data[i]=msg->Data[i];				 // ��һ֡��Ϣ      
		
	mbox= can_message_transmit(CAN0, &TxMessage);   
	
	//i=0;
	//while((can_transmit_states(CAN0, mbox)==CAN_TRANSMIT_FAILED)&&(i<0XFFF))//�ȴ����ͽ���
	//	i++;	
		
	//if(i>=0XFFF)
	//	return 1;
		
	return 0;		

}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 can_receive_msg(u8 *buf)
{		   		   
	u32 i;
	can_receive_message_struct RxMessage;
	
	//û�н��յ�����,ֱ���˳� 	
	if( (CAN_RFIFO0(CAN0))  & CAN_RFIFO0_RFL0  == 0)
		return 0;		
		
	//��ȡ����			
	can_message_receive(CAN0, CAN_FIFO0, &RxMessage);
		
	for(i=0;i<8;i++)
		buf[i]=RxMessage.rx_data[i];  
	
	return RxMessage.rx_dlen;	
}



