#include "sys_include.h"


#define SCL_H          SCL_OUT (1)
#define SCL_L        SCL_OUT(0)

#define SDA_H         SDA_OUT (1)
#define SDA_L         SDA_OUT (0)

#define SDA_read      SDA_VAL




//#define LINE_I2C_DAT_OUT() gpio_config(SDA_PORT, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_OD, GPIO_PuPd_NOPULL, 0)


//#define LINE_I2C_DAT_IN()  gpio_config(SDA_PORT, GPIO_Mode_IN, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP, 0)

void LINE_I2C_DAT_OUT(void)
{
	rcu_periph_clock_enable(SDA_RCU);	gpio_init(SDA_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,SDA_PIN);
}

void LINE_I2C_DAT_IN(void)
{
	rcu_periph_clock_enable(SDA_RCU);	gpio_init(SDA_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SDA_PIN);
}


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
vu8 FRAM_ADDRESS;
u8 FRAM_Buff[I2C_PageSize];
/* Private function prototypes -----------------------------------------------*/

/**/
#define I2CF_delay(t)	delay_us(t)
#define I2C_FRE_TIME 2


u16 E2PromWaitCnt = 0;
#define WAIT_TIME 5 //MS

void I2CF_Start(void)
{
	//LINE_I2C_DAT_OUT();
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
	SDA_H;
	I2CF_delay(I2C_FRE_TIME);
	SCL_H;
	I2CF_delay(I2C_FRE_TIME);
	SDA_L;
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
}

void I2CF_Stop(void)
{

	//LINE_I2C_DAT_OUT();
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
	SDA_L;
	I2CF_delay(I2C_FRE_TIME);
	SCL_H;
	I2CF_delay(I2C_FRE_TIME);
	SDA_H;
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
	SDA_L;

}

u16 I2CF_RX_Ack(void)
{
	u16 temp;
	LINE_I2C_DAT_IN();
	I2CF_delay(I2C_FRE_TIME);
	SCL_H;
	I2CF_delay(I2C_FRE_TIME);
	temp = SDA_read;
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
	LINE_I2C_DAT_OUT();
	return temp;
}

void I2CF_TX_Ack(void)
{

	SDA_L;
	I2CF_delay(I2C_FRE_TIME);
	SCL_H;
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
}

void I2CF_NoAck(void)
{

	SDA_H;
	I2CF_delay(I2C_FRE_TIME);
	SCL_H;
	I2CF_delay(I2C_FRE_TIME);
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
}


void I2CF_SendByte(u8 SendByte) //数据从高位到低位//
{
	u8 i=8;
	LINE_I2C_DAT_OUT();
	I2CF_delay(I2C_FRE_TIME);
	while(i--)
	{
		SCL_L;
		I2CF_delay(I2C_FRE_TIME);
		if(SendByte&0x80){
			SDA_H;}
		else{
			SDA_L;}
		SendByte<<=1;
		I2CF_delay(I2C_FRE_TIME);
		SCL_H;
		I2CF_delay(I2C_FRE_TIME);
	}
	SCL_L;
	I2CF_delay(I2C_FRE_TIME);
	SDA_L;
}

u8 I2CF_ReceiveByte(void)  //数据从高位到低位//
{
	u8 i=8;
	u8 ReceiveByte=0;
	LINE_I2C_DAT_IN();
	I2CF_delay(I2C_FRE_TIME);
	while(i--)
	{
		ReceiveByte<<=1;
		SCL_L;
		I2CF_delay(I2C_FRE_TIME);
		SCL_H;
		I2CF_delay(I2C_FRE_TIME);
		if(SDA_read)
		{
			ReceiveByte|=0x01;
		}
	}
	SCL_L;

	I2CF_delay(I2C_FRE_TIME);
	LINE_I2C_DAT_OUT();
	return ReceiveByte;
}


u16 I2C_FRAM_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
	u8 Addr = 0;
	u16 count = 0;
	u16 t = I2C_Dedey;



	#if E2PROM_DEV <= E2PROM16
	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	Addr = Addr << 1;

	Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7 | Addr;
	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}
	I2CF_SendByte(count&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	#else

	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	//Addr = Addr << 1;

	//Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7 ;
	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(Addr&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(count&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}


	#endif

	
	while(NumByteToWrite--)
	{
		I2CF_SendByte(* pBuffer);
		if(I2CF_RX_Ack() != 0){
			I2CF_Stop();
			return FALSE;
		}
		pBuffer++;
	}
	I2CF_Stop(); 	//注意：因为这里要等待EEPROM写完(5ms)
	while(t--) 	I2CF_delay(50);
	return TRUE;
}


u16 I2C_FRAM_BufferWriteBNoDly(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
	u8 Addr = 0;
	u16 count = 0;
	u16 t = I2C_Dedey;

	#if E2PROM_DEV <= E2PROM16
	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	Addr = Addr << 1;

	Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7 | Addr;
	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}
	I2CF_SendByte(count&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	#else

	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	//Addr = Addr << 1;

	//Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7 ;
	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(Addr&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(count&0x00ff);   //设置段内地址
	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}


	#endif
	while(NumByteToWrite--)
	{
		I2CF_SendByte(* pBuffer);
		if(I2CF_RX_Ack() != 0){
			I2CF_Stop();
			return FALSE;
		}
		pBuffer++;
	}
	I2CF_Stop(); 	//注意：因为这里要等待EEPROM写完(5ms)
	while(t--) 	I2CF_delay(50);
	return TRUE;
}

//读出1串数据
u16 I2C_FRAM_BufferRead(u8* pBuffer, u16 WriteAddr, u16 NumByteToRead)
{
	u8 Addr = 0;
	u16 count = 0;
	u16 t = I2C_Dedey;



	#if E2PROM_DEV <= E2PROM16
	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	Addr = Addr << 1;

	Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7 | Addr;

	I2CF_Start();

	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(count&0x00ff);   //设置低起始地址

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}


	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS | 0x01);

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}
	#else

	Addr = WriteAddr / I2C_ChapterSize;

	count = WriteAddr % I2C_ChapterSize;

	//Addr = Addr << 1;

	//Addr = Addr & 0x0F;

	FRAM_ADDRESS = I2C1_SLAVE_ADDRESS7;

	I2CF_Start();

	I2CF_SendByte(FRAM_ADDRESS);//设置器件地址+段地址

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}

	I2CF_SendByte(Addr&0x00ff);   //设置低起始地址

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}




	I2CF_SendByte(count&0x00ff);   //设置低起始地址

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}




	
	I2CF_Start();
	I2CF_SendByte(FRAM_ADDRESS | 0x01);

	if(I2CF_RX_Ack() != 0){
		I2CF_Stop();
		return FALSE;
	}
	#endif


	while(NumByteToRead)
	{
		*pBuffer = I2CF_ReceiveByte();

		if(NumByteToRead == 1)
			I2CF_NoAck();
		else
			I2CF_TX_Ack();
		pBuffer++;
		NumByteToRead--;
	}
	I2CF_Stop();
	while(t--) 	I2CF_delay(1);
	return TRUE;
}


u16 E2Prom(u16 cmd,u16 *dp,u16 ads,u16 len)
{
	u16 page_id = 0;
	u16 page_ads = 0;
	u16 page_offset = 0;
	u16 page_ofs_dp = 0;
	u16 i = 0,j = 0;

	if(cmd == EEPROM_READ){//read
		page_id = (len<<1) / I2C_PageSize;
		page_ads = (len<<1) % I2C_PageSize;
		for(i =0;i<page_id;i++ ){
			page_offset = (i+ads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			if(I2C_FRAM_BufferRead(FRAM_Buff,page_offset,I2C_PageSize) == FALSE) return FALSE;
			for(j=0;j<I2C_PageSize/2;j++){
				*(dp+(page_ofs_dp/2)+j) = (u16)(FRAM_Buff[2*j+1]<<8) | (u16)(FRAM_Buff[2*j]);
			}
		}
		if(page_ads != 0){
			page_offset = (i+ads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			if(I2C_FRAM_BufferRead(FRAM_Buff,page_offset,page_ads)== FALSE) return FALSE;
			for(j=0;j<page_ads/2;j++){
				*(dp+(page_ofs_dp/2)+j) = (u16)(FRAM_Buff[2*j+1]<<8) | (u16)(FRAM_Buff[2*j]);
			}
		}
	}else if(cmd == EEPROM_WRITE){
		page_id = (len<<1) / I2C_PageSize;
		page_ads = (len<<1) % I2C_PageSize;
		for(i =0;i<page_id;i++ ){
			page_offset = (i+ads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			for(j=0;j<I2C_PageSize/2;j++){
				FRAM_Buff[2*j] = *(dp+(page_ofs_dp/2)+j) & 0xff;
				FRAM_Buff[2*j+1] = (*(dp+(page_ofs_dp/2)+j)>>8) & 0xff;
			}

			if(I2C_FRAM_BufferWrite(FRAM_Buff,page_offset,I2C_PageSize)== FALSE) return FALSE;
		}
		if(page_ads != 0){
			page_offset = (i+ads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			for(j=0;j<page_ads/2;j++){
				FRAM_Buff[2*j] = *(dp+(page_ofs_dp/2)+j) & 0xff;
				FRAM_Buff[2*j+1] = (*(dp+(page_ofs_dp/2)+j)>>8) & 0xff;
			}
			if(I2C_FRAM_BufferWrite(FRAM_Buff,page_offset,page_ads) == FALSE) return FALSE;
		}

	}
	return TRUE;

}


u16 E2PromLogic(u16 cmd,u16 *dp,u16 ads,u16 len,u16 *Endp)//状态机保存
{
	static u16 sts = 0, uads = 0;
	static u16 ulen;

	static u16 page_id = 0;
	static u16 page_ads = 0;
	static u16 page_offset = 0;
	static u16 page_ofs_dp = 0;
	static u16 i = 0;
	static u16 *dpi ;
	u16 j = 0;


	switch(sts)
	{

	case 0:
		if(*Endp)
		{
			*Endp = 0;
			ulen = len;
			uads = ads;
			dpi = dp;
			i = 0;
			page_id = (ulen<<1) / I2C_PageSize;
			page_ads = (ulen<<1) % I2C_PageSize;
			if(cmd == EEPROM_READ){
				sts = 1;
			}
			else{
				sts = 11;
			}
			return EEPROM_GOING;
		}else{
			return EEPROM_IDEL;
		}


	/***********************************************************************************************************/
	case 1://读操作-整页读取
		if(i < page_id)
		{
			page_offset = (i + uads) * I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			if(I2C_FRAM_BufferRead(FRAM_Buff,page_offset,I2C_PageSize) == FALSE) return EEPROM_RD_ERR;
			for(j=0;j<I2C_PageSize/2;j++){
				*(dpi+(page_ofs_dp/2)+j) = (u16)(FRAM_Buff[2*j+1]<<8) | (u16)(FRAM_Buff[2*j]);
			}
			i++;
		}else{
			sts = 2;
		}
		return EEPROM_GOING;
	case 2://读操作-小于整页读取
		if(page_ads != 0){
			page_offset = (i + uads) * I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			if(I2C_FRAM_BufferRead(FRAM_Buff,page_offset,page_ads)== FALSE) return EEPROM_RD_ERR;
			for(j=0;j<page_ads/2;j++){
				*(dpi+(page_ofs_dp/2)+j) = (u16)(FRAM_Buff[2*j+1]<<8) | (u16)(FRAM_Buff[2*j]);
			}
		}
		sts = 0;	//读操作完成
		return EEPROM_GOING;
	/***********************************************************************************************************/


	/***********************************************************************************************************/
	case 11://写整页
		if(i < page_id){
			page_offset = (i+uads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			for(j=0;j<I2C_PageSize/2;j++){
				FRAM_Buff[2*j] = *(dpi+(page_ofs_dp/2)+j) & 0xff;
				FRAM_Buff[2*j+1] = (*(dpi+(page_ofs_dp/2)+j)>>8) & 0xff;
			}
			if(I2C_FRAM_BufferWriteBNoDly(FRAM_Buff,page_offset,I2C_PageSize)== FALSE) return EEPROM_WR_ERR;
			i++;
			E2PromWaitCnt = 0;
			sts = 13;	//	进入等待程序
		}else{
			sts = 12;
		}
		return EEPROM_GOING;
	case 12://写非整页
		if(page_ads != 0){
			page_offset = (i+uads)*I2C_PageSize;
			page_ofs_dp =  i*I2C_PageSize;
			for(j=0;j<page_ads/2;j++){
				FRAM_Buff[2*j] = *(dpi+(page_ofs_dp/2)+j) & 0xff;
				FRAM_Buff[2*j+1] = (*(dpi+(page_ofs_dp/2)+j)>>8) & 0xff;
			}
			if(I2C_FRAM_BufferWriteBNoDly(FRAM_Buff,page_offset,page_ads) == FALSE) return EEPROM_WR_ERR;
			E2PromWaitCnt = 0;
			sts = 14;	//	进入等待程序
		}else{
			sts = 0;
		}
		return EEPROM_GOING;
	case 13://等待1
		if(E2PromWaitCnt > (WAIT_TIME * SYS_ISR_PSC))
		{
			sts = 11;
		}
		return EEPROM_GOING;
	case 14://等待2
		if(E2PromWaitCnt > (WAIT_TIME * SYS_ISR_PSC))
		{
			sts = 0;
		}
		return EEPROM_GOING;
	default:
		sts = 0;
		return EEPROM_GOING;
	/***********************************************************************************************************/
	}
}

//u8 test_rx[10] = {0,};
//u8 test_tx[10] = {2,2,3,4,5,6,7,8,9,10};

void drv_eprom_init(void)
{
	rcu_periph_clock_enable(SDA_RCU);	gpio_init(SDA_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,SDA_PIN);
	rcu_periph_clock_enable(SCL_RCU);	gpio_init(SCL_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,SCL_PIN);



//	I2C_FRAM_BufferWrite(test_tx, 0, 10);
//	I2C_FRAM_BufferRead(test_rx, 0, 10);
}

