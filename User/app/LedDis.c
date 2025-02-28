#include "sys_include.h"



LedDis_t gLed;

const unsigned char LED_CODE[13]={
0x3F,/*0*/
0x06,/*1*/
0x5b,/*2*/
0x4f,/*3*/
0x66,/*4*/
0x6d,/*5*/
0x7d,/*6*/
0x07,/*7*/
0x7f,/*8*/
0x6f,/*9*/
0x00,/* */
0x79,/*E*/
0x73 /*P*/
};        //0~9显示代码


void Led_Init(void)
{
	rcu_periph_clock_enable(LEDCH1_RCU);	gpio_init(LEDCH1_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDCH1_PIN);
	rcu_periph_clock_enable(LEDCH2_RCU);	gpio_init(LEDCH2_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDCH2_PIN);
	rcu_periph_clock_enable(LEDA_RCU);	gpio_init(LEDA_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDA_PIN);
	rcu_periph_clock_enable(LEDB_RCU);	gpio_init(LEDB_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDB_PIN);
	rcu_periph_clock_enable(LEDC_RCU);	gpio_init(LEDC_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDC_PIN);
	rcu_periph_clock_enable(LEDD_RCU);	gpio_init(LEDD_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDD_PIN);
	rcu_periph_clock_enable(LEDE_RCU);	gpio_init(LEDE_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDE_PIN);
	rcu_periph_clock_enable(LEDF_RCU);	gpio_init(LEDF_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDF_PIN);
	rcu_periph_clock_enable(LEDG_RCU);	gpio_init(LEDG_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDG_PIN);
	rcu_periph_clock_enable(LEDDP_RCU);	gpio_init(LEDDP_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LEDDP_PIN);

	memset(&gLed, 0, sizeof(LedDis_t));

}





 //显示设定数据：位，数据，是否小数点
void Led_Dis_Chr(unsigned char pos,unsigned char data,unsigned char point)                  
{

	if(pos >= LED_NUM)
		return;
	gLed.Buf[pos].all = LED_CODE[data]|(point<<7);

	if(pos == 0)
	{
		LEDCH1_OUT(0);
		LEDCH2_OUT(0);

		LEDA_OUT(gLed.Buf[pos].bit.a);
		LEDB_OUT(gLed.Buf[pos].bit.b);
		LEDC_OUT(gLed.Buf[pos].bit.c);
		LEDD_OUT(gLed.Buf[pos].bit.d);
		LEDE_OUT(gLed.Buf[pos].bit.e);
		LEDF_OUT(gLed.Buf[pos].bit.f);
		LEDG_OUT(gLed.Buf[pos].bit.g);
		LEDDP_OUT(gLed.Buf[pos].bit.h);
	
		LEDCH2_OUT(0);
		LEDCH1_OUT(1);
		

	}
	else if(pos == 1)
	{
		LEDCH1_OUT(0);
		LEDCH2_OUT(0);
		
		LEDA_OUT(gLed.Buf[pos].bit.a);
		LEDB_OUT(gLed.Buf[pos].bit.b);
		LEDC_OUT(gLed.Buf[pos].bit.c);
		LEDD_OUT(gLed.Buf[pos].bit.d);
		LEDE_OUT(gLed.Buf[pos].bit.e);
		LEDF_OUT(gLed.Buf[pos].bit.f);
		LEDG_OUT(gLed.Buf[pos].bit.g);
		LEDDP_OUT(gLed.Buf[pos].bit.h);
	
		LEDCH1_OUT(0);
		LEDCH2_OUT(1);


	}

	
}


void Led_Clr(void)
{
	unsigned char i = LED_NUM;
	while(i--)
	{
		gLed.Chr[i].all = CHR_;	
		gLed.PT[i] = 0;
		gLed.CF[i] = 0;
		gLed.PtF[i] = 0;
	}
}


void Led_Set_U8(unsigned char pos,unsigned char data)
{
	if(pos >= LED_NUM)
		return;
	gLed.Chr[pos].all = data;
}


//type = 0 高位0显示  type = 1 高位0不显示
void Led_Set_Uint(unsigned long dat, unsigned char type, unsigned char len)
{
	unsigned char bit;
	unsigned long tmp;
	unsigned char i =0;

	tmp = dat;
	while(len)
	{
		bit = tmp%10;
		tmp = tmp/10;

		if(i == 0)
		{
			gLed.Chr[i].all = bit;

		}
		else if(type == 1 && bit==0 && tmp ==0)
		{
			gLed.Chr[i].all = CHR_;

		}
		else
		{
			gLed.Chr[i].all = bit;
		}
		


		len--;
		i++;
	}


	
}


void Led_Set_PT(unsigned char pos, unsigned char p)
{
	if(pos >= LED_NUM)
		return;
	gLed.PT[pos] = p;
	
}

void Led_Set_Flash(unsigned char pos, unsigned char type, unsigned char f)
{
	if(pos >= LED_NUM)
		return;
	
	if(type == 0)
		gLed.CF[pos]= f;
	else
		gLed.PtF[pos]= f;

}



void Led_Dis_Update(void)
{
	unsigned char Chr[LED_NUM] = {0,};
	unsigned char Pt[LED_NUM] = {0,};

	gLed.Ticker++;
	if(gLed.Ticker > DIS_FLASH_TIME+DIS_FLASH_TIME)
		gLed.Ticker -= DIS_FLASH_TIME+DIS_FLASH_TIME;

	gLed.Pos++;
	if(gLed.Pos == LED_NUM)
		gLed.Pos = 0;
		

	if(gLed.CF[gLed.Pos])
	{
		if(gLed.Ticker < DIS_FLASH_TIME)
			Chr[gLed.Pos] = gLed.Chr[gLed.Pos].all;
		else 
			Chr[gLed.Pos] = CHR_;
	}
	else
	{
		Chr[gLed.Pos] = gLed.Chr[gLed.Pos].all;
	}


	if(gLed.PtF[gLed.Pos])
	{
		if(gLed.Ticker < DIS_FLASH_TIME)
			Pt[gLed.Pos] = gLed.PT[gLed.Pos];
		else 
			Pt[gLed.Pos] =  0;
	}
	else
	{
		Pt[gLed.Pos] = gLed.PT[gLed.Pos];
	}


	Led_Dis_Chr(gLed.Pos, Chr[gLed.Pos], Pt[gLed.Pos]);

}


void Led_Dis_Task(void)
{

	Led_Dis_Update();
}



