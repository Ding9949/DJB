#include "Gpio.h"

const static uint32_t gpio_rcc_periph[8] = {
	RCC_AHB1Periph_GPIOA,
	RCC_AHB1Periph_GPIOB,
	RCC_AHB1Periph_GPIOC,
	RCC_AHB1Periph_GPIOD,
	RCC_AHB1Periph_GPIOE,
	RCC_AHB1Periph_GPIOF,
	RCC_AHB1Periph_GPIOG,
	RCC_AHB1Periph_GPIOH
};

static GPIO_TypeDef* gpio_x[8] = {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH
};

const static uint8_t gpio_pin_source[16] = 
{
	GPIO_PinSource0,
	GPIO_PinSource1,
	GPIO_PinSource2,
	GPIO_PinSource3,
	GPIO_PinSource4,
	GPIO_PinSource5,
	GPIO_PinSource6,
	GPIO_PinSource7,
	GPIO_PinSource8,
	GPIO_PinSource9,
	GPIO_PinSource10,
	GPIO_PinSource11,
	GPIO_PinSource12,
	GPIO_PinSource13,
	GPIO_PinSource14,
	GPIO_PinSource15
};

const static uint16_t gpio_pin[16] = 
{
	GPIO_Pin_0,
	GPIO_Pin_1,
	GPIO_Pin_2,
	GPIO_Pin_3,
	GPIO_Pin_4,
	GPIO_Pin_5,
	GPIO_Pin_6,
	GPIO_Pin_7,
	GPIO_Pin_8,
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11,
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15
};

void gpio_config(uint8_t PTx, 
			GPIOMode_TypeDef Mode, 
			GPIOSpeed_TypeDef Speed, 
			GPIOOType_TypeDef OType,  
			GPIOPuPd_TypeDef PuPd,
			uint8_t AFType)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	uint8_t Port = PTx>>4;
	uint8_t Pin = PTx & 0xF;

	// config rcc
	RCC_AHB1PeriphClockCmd(gpio_rcc_periph[Port], ENABLE);

	//config af
	if(Mode == GPIO_Mode_AF)
		GPIO_PinAFConfig(gpio_x[Port], gpio_pin_source[Pin], AFType);

	//init
	GPIO_InitStructure.GPIO_Pin = gpio_pin[Pin];
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_InitStructure.GPIO_Speed = Speed;
	GPIO_InitStructure.GPIO_OType = OType;
	GPIO_InitStructure.GPIO_PuPd  = PuPd;

	GPIO_Init(gpio_x[Port], &GPIO_InitStructure);

	

}


