#include "sys_include.h"

/******************************************************************************/


u16 Can_Err_Cnt = 0;
Filter32ID FilterID;
Filter32Mask FilterMask;
/******************************************************************************/


void can_filter_config(void)
{

	FilterID.all = 0;
	FilterID.bit.IDE = 1;
	FilterID.bit.EXID0 = 0;
	FilterID.bit.EXID1 = 0;
	FilterID.bit.EXID2 = 0;
	FilterID.bit.EXID3 = 0;
	FilterID.bit.EXID4 = 0;
	FilterID.bit.EXID5 = 0;
	FilterID.bit.EXID6 = 0;
	FilterID.bit.EXID7 = 0;//0x00
	
	FilterID.bit.EXID8 = 0;
	FilterID.bit.EXID9 = 0;
	FilterID.bit.EXID10 = 0;
	FilterID.bit.EXID11 = 0;
	FilterID.bit.EXID12 = 0;
	FilterID.bit.EXID13 = 0;
	FilterID.bit.EXID14 = 0;
	FilterID.bit.EXID15 = 0;//0x00
	FilterMask.all = 0;
	FilterMask.bit.IDE = 1;
	FilterMask.bit.EXID0 = 0;
	FilterMask.bit.EXID1 = 0;
	FilterMask.bit.EXID2 = 0;
	FilterMask.bit.EXID3 = 0;
	FilterMask.bit.EXID4 = 0;
	FilterMask.bit.EXID5 = 0;
	FilterMask.bit.EXID6 = 0;
	FilterMask.bit.EXID7 = 0;//0x00
	
	FilterMask.bit.EXID8 = 0;
	FilterMask.bit.EXID9 = 0;
	FilterMask.bit.EXID10 = 0;
	FilterMask.bit.EXID11 = 0;
	FilterMask.bit.EXID12 = 0;
	FilterMask.bit.EXID13 = 0;
	FilterMask.bit.EXID14 = 0;
	FilterMask.bit.EXID15 = 0;//0x00
	can_set_filter32(0, FilterID, FilterMask);


}
void can_reset(void)
{
	#ifdef STM32F10X_MD
	CAN_CancelTransmit(CAN1, 0);
	CAN_CancelTransmit(CAN1, 1);
	CAN_CancelTransmit(CAN1, 2);
	#endif
	#ifdef GD32F30X_HD
	can_transmission_stop(CAN0, 0);
	can_transmission_stop(CAN0, 1);
	can_transmission_stop(CAN0, 2);
	#endif

	can_conf(CAN_BAUDRATE_250K);

	can_filter_config();
}


// 0-秒闪
// 1-快闪
// 2-慢闪
void led_flash(u8 type)
{
	static u32 Ticker = 0;
	u32 Time = LED_ON_DLY_MS;


	if(type == 0)
	{
		Time = LED_ON_DLY_MS;
	}
	else if(type == 1)
	{
		Time = (LED_ON_DLY_MS)>>2;
	}
	else if(type == 2)
	{
		Time = (LED_ON_DLY_MS)<<2;
	}
	
	Ticker++;
	if(Ticker < Time)
		gSysHard.Led = 0;
	else if(Ticker < (Time<<1))		
		gSysHard.Led = 1;
	else 
		Ticker = 0;



}


void main_init(void)
{


}



void main_ticker(void)
{
	static u16 psr = 0;
	led_flash(0);

	gSysCtlVar.Ticker++;
	if(gExCom.RxdTicker)gExCom.RxdTicker--;
	E2PromWaitCnt++;
	if(gExCom.TxdDly)gExCom.TxdDly--;


	psr++;
	if(psr >= SYS_ISR_PSC*100)// 0.1s
	{
		psr = 0;


		if(can_flag_get(CAN0, CAN_FLAG_BOERR))
		{
			Can_Err_Cnt++;
		}
		else
		{
			Can_Err_Cnt = 0;
		}

		
	}
	//----------------------------------------------------------------//

	
}

//5K  
void main_isr(void)
{
	/*******************************************************************************/
	main_ticker();		//系统计时器使用
	/*******************************************************************************/
	
	
	/*******************************************************************************/
	sys_hard_read_port();			//读取硬件接口数据值到相关的寄存器
	/*******************************************************************************/

		

	/*******************************************************************************/
	can1_task();
	/*******************************************************************************/


	
	/*******************************************************************************/
	sys_hard_load_port();			//加载系统变量到相应的硬件接口
	/*******************************************************************************/
}

void main_task(void)
{
	main_init();
	drv_io_init();
	drv_pwm_init();
	#if EEPROM_TYPE == EEPROM_USE_FRAM
	drv_eprom_init();
	#endif
	sys_hard_init();


	delay_ms(100);
	api_read_sys_par();

	can_conf(CAN_BAUDRATE_250K);
	can_filter_config();
	can_buffer_init();
	
	drv_sci_init();
	excom_init();
	sys_task_init();
	Led_Init();



	
	PWM_TIMER_EN(); 
	
	while(1)
	{
		/*******************************************************************************/
		sys_task();		
		/*******************************************************************************/
		


	}
}
