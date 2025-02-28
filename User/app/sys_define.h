#ifndef __sys_define_h
#define __sys_define_h


/****************************************************************************/
 //版本号、发布时间
#define CODE_VER 101
#define CODE_DATE 20241210
/****************************************************************************/

/****************************************************************************/
#define CKTIM	((u32)120000000uL) 	
#define CKTIMx	((u32)120000000uL) 	
#define PWM_PRSC ((u8)0)
#define PWM_FREQ ((u16) 5000) // in Hz  (N.b.: pattern type is center aligned)
#define PWM_PERIOD ((u16) (CKTIM / (u32)(2*PWM_FREQ *(PWM_PRSC+1)))) 
#define PWM_PERIODx ((u16) (CKTIMx / (u32)(PWM_FREQ *(PWM_PRSC+1)))) 
/****	ADC IRQ-HANDLER frequency, related to PWM  ****/
#define REP_RATE (1)  // (N.b): Internal current loop is performed every 
                      //             (REP_RATE + 1)/(2*PWM_FREQ) seconds.
                      // REP_RATE has to be an odd number in case of three-shunt
                      // current reading; this limitation doesn't apply to ICS

          
#define SYS_ISR_PSC 5
#define LED_ON_DLY_MS 2500 //500ms
/****************************************************************************/





#endif
