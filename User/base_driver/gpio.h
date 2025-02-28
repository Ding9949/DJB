#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f4xx.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40011E08 

#define GPIOx_ODR_Addr(n)	(GPIOA_BASE + 0x400*n + 20)
#define GPIOx_IDR_Addr(n)	(GPIOA_BASE + 0x400*n + 16)


//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PORTout(PTx) BIT_ADDR(GPIOx_ODR_Addr((PTx>>4)), (PTx&0xF)) 
#define PORTin(PTx) BIT_ADDR(GPIOx_IDR_Addr((PTx>>4)), (PTx&0xF)) 

#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5
#define PG 6
#define PH 7


#define Pin0 0
#define Pin1 1
#define Pin2 2
#define Pin3 3
#define Pin4 4
#define Pin5 5
#define Pin6 6
#define Pin7 7
#define Pin8 8
#define Pin9 9
#define Pin10 10
#define Pin11 11
#define Pin12 12
#define Pin13 13
#define Pin14 14
#define Pin15 15

#define PTx(n,x) ((uint8_t)((n<<4) | (x & 0xf))) 

#define PA0 PTx(PA, Pin0)
#define PA1 PTx(PA, Pin1)
#define PA2 PTx(PA, Pin2)
#define PA3 PTx(PA, Pin3)
#define PA4 PTx(PA, Pin4)
#define PA5 PTx(PA, Pin5)
#define PA6 PTx(PA, Pin6)
#define PA7 PTx(PA, Pin7)
#define PA8 PTx(PA, Pin8)
#define PA9 PTx(PA, Pin9)
#define PA10 PTx(PA, Pin10)
#define PA11 PTx(PA, Pin11)
#define PA12 PTx(PA, Pin12)
#define PA13 PTx(PA, Pin13)
#define PA14 PTx(PA, Pin14)
#define PA15 PTx(PA, Pin15)

#define PB0 PTx(PB, Pin0)
#define PB1 PTx(PB, Pin1)
#define PB2 PTx(PB, Pin2)
#define PB3 PTx(PB, Pin3)
#define PB4 PTx(PB, Pin4)
#define PB5 PTx(PB, Pin5)
#define PB6 PTx(PB, Pin6)
#define PB7 PTx(PB, Pin7)
#define PB8 PTx(PB, Pin8)
#define PB9 PTx(PB, Pin9)
#define PB10 PTx(PB, Pin10)
#define PB11 PTx(PB, Pin11)
#define PB12 PTx(PB, Pin12)
#define PB13 PTx(PB, Pin13)
#define PB14 PTx(PB, Pin14)
#define PB15 PTx(PB, Pin15)

#define PC0 PTx(PC, Pin0)
#define PC1 PTx(PC, Pin1)
#define PC2 PTx(PC, Pin2)
#define PC3 PTx(PC, Pin3)
#define PC4 PTx(PC, Pin4)
#define PC5 PTx(PC, Pin5)
#define PC6 PTx(PC, Pin6)
#define PC7 PTx(PC, Pin7)
#define PC8 PTx(PC, Pin8)
#define PC9 PTx(PC, Pin9)
#define PC10 PTx(PC, Pin10)
#define PC11 PTx(PC, Pin11)
#define PC12 PTx(PC, Pin12)
#define PC13 PTx(PC, Pin13)
#define PC14 PTx(PC, Pin14)
#define PC15 PTx(PC, Pin15)

#define PD0 PTx(PD, Pin0)
#define PD1 PTx(PD, Pin1)
#define PD2 PTx(PD, Pin2)
#define PD3 PTx(PD, Pin3)
#define PD4 PTx(PD, Pin4)
#define PD5 PTx(PD, Pin5)
#define PD6 PTx(PD, Pin6)
#define PD7 PTx(PD, Pin7)
#define PD8 PTx(PD, Pin8)
#define PD9 PTx(PD, Pin9)
#define PD10 PTx(PD, Pin10)
#define PD11 PTx(PD, Pin11)
#define PD12 PTx(PD, Pin12)
#define PD13 PTx(PD, Pin13)
#define PD14 PTx(PD, Pin14)
#define PD15 PTx(PD, Pin15)

#define PE0 PTx(PE, Pin0)
#define PE1 PTx(PE, Pin1)
#define PE2 PTx(PE, Pin2)
#define PE3 PTx(PE, Pin3)
#define PE4 PTx(PE, Pin4)
#define PE5 PTx(PE, Pin5)
#define PE6 PTx(PE, Pin6)
#define PE7 PTx(PE, Pin7)
#define PE8 PTx(PE, Pin8)
#define PE9 PTx(PE, Pin9)
#define PE10 PTx(PE, Pin10)
#define PE11 PTx(PE, Pin11)
#define PE12 PTx(PE, Pin12)
#define PE13 PTx(PE, Pin13)
#define PE14 PTx(PE, Pin14)
#define PE15 PTx(PE, Pin15)

#define PF0 PTx(PF, Pin0)
#define PF1 PTx(PF, Pin1)
#define PF2 PTx(PF, Pin2)
#define PF3 PTx(PF, Pin3)
#define PF4 PTx(PF, Pin4)
#define PF5 PTx(PF, Pin5)
#define PF6 PTx(PF, Pin6)
#define PF7 PTx(PF, Pin7)
#define PF8 PTx(PF, Pin8)
#define PF9 PTx(PF, Pin9)
#define PF10 PTx(PF, Pin10)
#define PF11 PTx(PF, Pin11)
#define PF12 PTx(PF, Pin12)
#define PF13 PTx(PF, Pin13)
#define PF14 PTx(PF, Pin14)
#define PF15 PTx(PF, Pin15)

#define PG0 PTx(PG, Pin0)
#define PG1 PTx(PG, Pin1)
#define PG2 PTx(PG, Pin2)
#define PG3 PTx(PG, Pin3)
#define PG4 PTx(PG, Pin4)
#define PG5 PTx(PG, Pin5)
#define PG6 PTx(PG, Pin6)
#define PG7 PTx(PG, Pin7)
#define PG8 PTx(PG, Pin8)
#define PG9 PTx(PG, Pin9)
#define PG10 PTx(PG, Pin10)
#define PG11 PTx(PG, Pin11)
#define PG12 PTx(PG, Pin12)
#define PG13 PTx(PG, Pin13)
#define PG14 PTx(PG, Pin14)
#define PG15 PTx(PG, Pin15)

#define PH0 PTx(PH, Pin0)
#define PH1 PTx(PH, Pin1)
#define PH2 PTx(PH, Pin2)
#define PH3 PTx(PH, Pin3)
#define PH4 PTx(PH, Pin4)
#define PH5 PTx(PH, Pin5)
#define PH6 PTx(PH, Pin6)
#define PH7 PTx(PH, Pin7)
#define PH8 PTx(PH, Pin8)
#define PH9 PTx(PH, Pin9)
#define PH10 PTx(PH, Pin10)
#define PH11 PTx(PH, Pin11)
#define PH12 PTx(PH, Pin12)
#define PH13 PTx(PH, Pin13)
#define PH14 PTx(PH, Pin14)
#define PH15 PTx(PH, Pin15)

#define gpio_set(PTx) PORTout(PTx) = 1
#define gpio_reset(PTx) PORTout(PTx) = 0
#define gpio_get(PTx) PORTin(PTx)


void gpio_config(uint8_t PTx,
			GPIOMode_TypeDef Mode, 
			GPIOSpeed_TypeDef Speed, 
			GPIOOType_TypeDef OType,  
			GPIOPuPd_TypeDef PuPd,
			uint8_t AFType);




#endif
