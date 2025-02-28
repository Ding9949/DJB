#ifndef __drv_io_h
#define __drv_io_h

#include "sys_bsp.h"

#define LED_RCU RCU_GPIOB
#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_5
#define LED_OUT(c)  gpio_bit_write(LED_PORT, LED_PIN, (c)?RESET:SET)


#define OUT1_RCU RCU_GPIOB
#define OUT1_PORT GPIOB
#define OUT1_PIN GPIO_PIN_2
#define OUT1_OUT(c)  gpio_bit_write(OUT1_PORT, OUT1_PIN, (c)?SET:RESET)
#define OUT2_RCU RCU_GPIOB
#define OUT2_PORT GPIOB
#define OUT2_PIN GPIO_PIN_10
#define OUT2_OUT(c)  gpio_bit_write(OUT2_PORT, OUT2_PIN, (c)?SET:RESET)



#define IN1_RCU RCU_GPIOB
#define IN1_PORT GPIOB
#define IN1_PIN GPIO_PIN_11
#define IN1_VAL  (gpio_input_bit_get(IN1_PORT, IN1_PIN)== 0)? 1:0
#define IN2_RCU RCU_GPIOB
#define IN2_PORT GPIOB
#define IN2_PIN GPIO_PIN_12
#define IN2_VAL  (gpio_input_bit_get(IN2_PORT, IN2_PIN)== 0)? 1:0

#define SW1_RCU RCU_GPIOB
#define SW1_PORT GPIOB
#define SW1_PIN GPIO_PIN_8
#define SW1_VAL  ((gpio_input_bit_get(SW1_PORT, SW1_PIN)== 0)? 0:1)
#define SW2_RCU RCU_GPIOB
#define SW2_PORT GPIOB
#define SW2_PIN GPIO_PIN_9
#define SW2_VAL  ((gpio_input_bit_get(SW2_PORT, SW2_PIN)== 0)? 0:1)
#define SW3_RCU RCU_GPIOC
#define SW3_PORT GPIOC
#define SW3_PIN GPIO_PIN_13
#define SW3_VAL  ((gpio_input_bit_get(SW3_PORT, SW3_PIN)== 0)? 0:1)
#define SW4_RCU RCU_GPIOC
#define SW4_PORT GPIOC
#define SW4_PIN GPIO_PIN_14
#define SW4_VAL  ((gpio_input_bit_get(SW4_PORT, SW4_PIN)== 0)? 0:1)
#define SW5_RCU RCU_GPIOC
#define SW5_PORT GPIOC
#define SW5_PIN GPIO_PIN_15
#define SW5_VAL  ((gpio_input_bit_get(SW5_PORT, SW5_PIN)== 0)? 0:1)


void drv_io_init(void);

#endif
