#ifndef __LedDis_h
#define __LedDis_h


#include "sys_bsp.h"



#define LEDCH1_RCU RCU_GPIOB
#define LEDCH1_PORT GPIOB
#define LEDCH1_PIN GPIO_PIN_15
#define LEDCH1_OUT(c)  gpio_bit_write(LEDCH1_PORT, LEDCH1_PIN, (c)?RESET:SET)
#define LEDCH2_RCU RCU_GPIOB
#define LEDCH2_PORT GPIOB
#define LEDCH2_PIN GPIO_PIN_13
#define LEDCH2_OUT(c)  gpio_bit_write(LEDCH2_PORT, LEDCH2_PIN, (c)?RESET:SET)
#define LEDA_RCU RCU_GPIOA
#define LEDA_PORT GPIOA
#define LEDA_PIN GPIO_PIN_0
#define LEDA_OUT(c)  gpio_bit_write(LEDA_PORT, LEDA_PIN, (c)?RESET:SET)
#define LEDB_RCU RCU_GPIOA
#define LEDB_PORT GPIOA
#define LEDB_PIN GPIO_PIN_1
#define LEDB_OUT(c)  gpio_bit_write(LEDB_PORT, LEDB_PIN, (c)?RESET:SET)
#define LEDC_RCU RCU_GPIOA
#define LEDC_PORT GPIOA
#define LEDC_PIN GPIO_PIN_2
#define LEDC_OUT(c)  gpio_bit_write(LEDC_PORT, LEDC_PIN, (c)?RESET:SET)
#define LEDD_RCU RCU_GPIOA
#define LEDD_PORT GPIOA
#define LEDD_PIN GPIO_PIN_3
#define LEDD_OUT(c)  gpio_bit_write(LEDD_PORT, LEDD_PIN, (c)?RESET:SET)
#define LEDE_RCU RCU_GPIOA
#define LEDE_PORT GPIOA
#define LEDE_PIN GPIO_PIN_4
#define LEDE_OUT(c)  gpio_bit_write(LEDE_PORT, LEDE_PIN, (c)?RESET:SET)
#define LEDF_RCU RCU_GPIOA
#define LEDF_PORT GPIOA
#define LEDF_PIN GPIO_PIN_5
#define LEDF_OUT(c)  gpio_bit_write(LEDF_PORT, LEDF_PIN, (c)?RESET:SET)
#define LEDG_RCU RCU_GPIOA
#define LEDG_PORT GPIOA
#define LEDG_PIN GPIO_PIN_6
#define LEDG_OUT(c)  gpio_bit_write(LEDG_PORT, LEDG_PIN, (c)?RESET:SET)
#define LEDDP_RCU RCU_GPIOA
#define LEDDP_PORT GPIOA
#define LEDDP_PIN GPIO_PIN_7
#define LEDDP_OUT(c)  gpio_bit_write(LEDDP_PORT, LEDDP_PIN, (c)?RESET:SET)




/*************************************************************************/
#define LED_NUM 2
#define DIS_FLASH_TIME 250


#define CHR_0 0
#define CHR_1 1
#define CHR_2 2
#define CHR_3 3
#define CHR_4 4
#define CHR_5 5
#define CHR_6 6
#define CHR_7 7
#define CHR_8 8
#define CHR_9 9
#define CHR_ 10
#define CHR_E 11
#define CHR_P 12


struct LED_BIT
{
	unsigned char a:1;
	unsigned char b:1;
	unsigned char c:1;
	unsigned char d:1;
	unsigned char e:1;
	unsigned char f:1;
	unsigned char g:1;
	unsigned char h:1;
};

union LED_CHR
{
	unsigned char all;
	struct LED_BIT bit;
};

typedef struct _LedDis_s
{
	
	// dis buf
	union LED_CHR Buf[LED_NUM];
	union LED_CHR Chr[LED_NUM];
	unsigned char PT[LED_NUM];
	unsigned char CF[LED_NUM]; //×Ö·ûÉÁË¸
	unsigned char PtF[LED_NUM];//Ð¡ÊýµãÉÁË¸


	//scan 
	unsigned char Pos; 
	unsigned int Ticker;

}LedDis_t;


/*************************************************************************/






/*************************************************************************/
extern LedDis_t gLed;
/*************************************************************************/

/*************************************************************************/
void Led_Init(void);
void Led_Clr(void);
void Led_Dis_Chr(unsigned char pos,unsigned char data,unsigned char point) ;     
void Led_Set_U8(unsigned char pos,unsigned char data);
void Led_Set_Uint(unsigned long dat, unsigned char type, unsigned char len);
void Led_Set_PT(unsigned char pos, unsigned char p);
void Led_Set_Flash(unsigned char pos, unsigned char type, unsigned char f);
void Led_Dis_Task(void);

/*************************************************************************/

#endif
