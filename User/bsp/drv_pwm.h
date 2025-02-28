#ifndef __drv_pwm_h
#define __drv_pwm_h

#include "sys_bsp.h"



#define PWM_TIMER_EN() {timer_enable(TIMER0);}

void drv_pwm_init(void);
#endif
