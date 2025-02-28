#include "drv_pwm.h"



void drv_pwm_init(void)
{
	timer_parameter_struct  TIM_Structure;	
	

	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_TIMER0);


	
	TIM_Structure.prescaler         = 0U;
	TIM_Structure.alignedmode       = TIMER_COUNTER_CENTER_DOWN;
	TIM_Structure.counterdirection  = TIMER_COUNTER_UP;
	TIM_Structure.period            = PWM_PERIOD;
	TIM_Structure.clockdivision     = TIMER_CKDIV_DIV1;
	TIM_Structure.repetitioncounter = REP_RATE;
	timer_init(TIMER0, &TIM_Structure);



	timer_flag_clear(TIMER0,TIMER_FLAG_UP);
	timer_interrupt_enable(TIMER0, TIMER_INT_UP);

	timer_disable(TIMER0);

	nvic_irq_enable(TIMER0_UP_IRQn, 1, 0);


}




