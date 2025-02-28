#ifndef __drv_eprom_h
#define __drv_eprom_h

#include "sys_bsp.h"

#define SDA_RCU RCU_GPIOB
#define SDA_PORT GPIOB
#define SDA_PIN GPIO_PIN_7
#define SDA_OUT(c)  gpio_bit_write(SDA_PORT, SDA_PIN, (c)?SET:RESET)
#define SDA_VAL  (gpio_input_bit_get(SDA_PORT, SDA_PIN)== 1)? 1:0


#define SCL_RCU RCU_GPIOB
#define SCL_PORT GPIOB
#define SCL_PIN GPIO_PIN_6
#define SCL_OUT(c)  gpio_bit_write(SCL_PORT, SCL_PIN, (c)?SET:RESET)

#define E2PROM01 0 
#define E2PROM02 1 
#define E2PROM04 2 
#define E2PROM08 3 
#define E2PROM16 4 
#define E2PROM64 5
#define E2PROM_DEV E2PROM04




#define I2C_Speed              100000
#define I2C1_SLAVE_ADDRESS7    0xA0
#define I2C_PageNum            128
#define I2C_PageSize           16
#define I2C_ChapterSize		   256
#define I2C_Dedey 			  100// 0//EEPROM保存需要等待较长时间。如果是FRAM则不需要等待

#define EEPROM_READ 0
#define EEPROM_WRITE 1

enum{
	EEPROM_IDEL = 0,
	EEPROM_GOING,
	EEPROM_WR_ERR,
	EEPROM_RD_ERR
};


/* Exported functions ------------------------------------------------------- */ 

u16 I2C_FRAM_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
u16 I2C_FRAM_BufferRead(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead);
u16 E2Prom(u16 cmd,u16 *dp,u16 ads,u16 len);


extern u16 E2PromWaitCnt;
u16 E2PromLogic(u16 cmd,u16 *dp,u16 ads,u16 len,u16 *Endp);//状态机保存
void drv_eprom_init(void);

#endif
