#ifndef __drv_sci_h
#define __drv_sci_h

#include "sys_bsp.h"

#define USART_BUS_TXD 1
#define USART_BUS_RXD 0




#define SCI_B_RCC_Periph   		RCU_USART0
#define SCI_B_USART						USART0
#define SCI_B_TXD_RCU RCU_GPIOA
#define SCI_B_TXD_GPIO_PORT 	GPIOA
#define SCI_B_TXD_GPIO_PIN 		GPIO_PIN_9
#define SCI_B_RXD_RCU RCU_GPIOA
#define SCI_B_RXD_GPIO_PORT 	GPIOA
#define SCI_B_RXD_GPIO_PIN 		GPIO_PIN_10
#define SCI_B_DE_RCU RCU_GPIOA
#define SCI_B_DE_GPIO_PORT		GPIOA
#define SCI_B_DE_GPIO_PIN			GPIO_PIN_8
#define SCI_B_BaudRate 				9600
#define SCI_B_DE_CTL(c) 			gpio_bit_write(SCI_B_DE_GPIO_PORT, SCI_B_DE_GPIO_PIN, ((c)?SET:RESET))

#define USARTB_TXD_OK() 			usart_flag_get(SCI_B_USART,USART_FLAG_TBE)&&usart_flag_get(SCI_B_USART,USART_FLAG_TC) 
#define USARTB_RXD_OK() 			usart_flag_get(SCI_B_USART,USART_FLAG_RBNE) 
#define USARTB_DISABLE() 			usart_disable(SCI_B_USART)
#define USARTB_ENABLE() 			usart_enable(SCI_B_USART)
#define USARTB_TXD(c) 				usart_data_transmit(SCI_B_USART,c)
#define USARTB_RXD() 				usart_data_receive(SCI_B_USART)
#define USARTB_STS()  				SCI_B_USART->SR
#define USARTB_TC_CLR()   			usart_flag_clear(SCI_B_USART, USART_FLAG_TC)


void drv_sci_init(void);

#endif


