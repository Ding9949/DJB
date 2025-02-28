#include "drv_sci.h"



void drv_sci_b_init(void)
{


	rcu_periph_clock_enable(RCU_AF);	
	rcu_periph_clock_enable(SCI_B_RCC_Periph);

	//config GPIO	
	rcu_periph_clock_enable(SCI_B_TXD_RCU);
	gpio_init(SCI_B_TXD_GPIO_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,SCI_B_TXD_GPIO_PIN);
	rcu_periph_clock_enable(SCI_B_RXD_RCU);
	gpio_init(SCI_B_RXD_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,SCI_B_RXD_GPIO_PIN);
	rcu_periph_clock_enable(SCI_B_DE_RCU);
	gpio_init(SCI_B_DE_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,SCI_B_DE_GPIO_PIN);

	
	SCI_B_DE_CTL(USART_BUS_RXD);

	

	usart_deinit(SCI_B_USART);
	usart_baudrate_set(SCI_B_USART, SCI_B_BaudRate);
	usart_parity_config(SCI_B_USART, USART_PM_NONE);
	usart_word_length_set(SCI_B_USART, USART_WL_8BIT);
	usart_stop_bit_set(SCI_B_USART, USART_STB_1BIT);

	usart_transmit_config(SCI_B_USART, USART_TRANSMIT_ENABLE);
	usart_receive_config(SCI_B_USART, USART_RECEIVE_ENABLE);

	usart_interrupt_enable(SCI_B_USART, USART_INT_RBNE);
	usart_interrupt_enable(SCI_B_USART, USART_INT_TC);

	usart_enable(SCI_B_USART);

	nvic_irq_enable(USART0_IRQn, 1, 2);


}


void drv_sci_init(void)
{
	drv_sci_b_init();
}





