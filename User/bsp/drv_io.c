#include "drv_io.h"




void drv_io_init(void)
{


	rcu_periph_clock_enable(RCU_AF);	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

	rcu_periph_clock_enable(LED_RCU);	gpio_init(LED_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,LED_PIN);
	rcu_periph_clock_enable(OUT1_RCU);	gpio_init(OUT1_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,OUT1_PIN);
	rcu_periph_clock_enable(OUT2_RCU);	gpio_init(OUT2_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,OUT2_PIN);
	
	rcu_periph_clock_enable(IN1_RCU);	gpio_init(IN1_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,IN1_PIN);
	rcu_periph_clock_enable(IN2_RCU);	gpio_init(IN2_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,IN2_PIN);
	rcu_periph_clock_enable(SW1_RCU);gpio_init(SW1_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SW1_PIN);
 	rcu_periph_clock_enable(SW2_RCU);gpio_init(SW2_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SW2_PIN);
	rcu_periph_clock_enable(SW3_RCU);gpio_init(SW3_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SW3_PIN);
	rcu_periph_clock_enable(SW4_RCU);gpio_init(SW4_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SW4_PIN);
	rcu_periph_clock_enable(SW5_RCU);gpio_init(SW5_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,SW5_PIN);


}

