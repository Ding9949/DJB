#ifndef __sys_main_h
#define __sys_main_h

#include "sys_bsp.h"

//ϵͳ���궨��
extern u16 gPwmIsrTacker;
extern u16 ISR_FREQUENCY; 				// Define the ISR frequency (kHz)
extern u16 SPEED_LOOP_PSR;				//�ٶȻ�λ�û� ��Ƶ��
extern u16 POS_LOOP_FRE;			//�ٶȻ�Ƶ��KHZ
extern float  T_PWM;//(0.001/ISR_FREQUENCY)    // Samping period (sec), see parameter.h
extern u16 Can_Err_Cnt;
extern Filter32ID FilterID;
extern Filter32Mask FilterMask;
extern u32 SysUID;

void can_reset(void);
void main_init(void);
void main_ticker(void);
void main_isr(void);
void main_task(void);

#endif
