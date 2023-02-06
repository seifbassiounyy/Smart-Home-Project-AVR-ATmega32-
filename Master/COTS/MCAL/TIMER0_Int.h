////Author: Seif Bassiouny
////Date: 21/9/2022
////Version: 1.6
////Module: TIMER0

#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

#define TIMER0_SYSTEM_CLOCK		16000000UL
#define TIMER0_TICK_TIME		1/TIMER0_Uint8_CLOCK_SELECT
#define TIMER0_TOVF				TIMER0_TICK_TIME*256

void TIMER0_void_Init(void);
void TIMER0_void_EnableInterrupt(void);
void TIMER0_void_DisableInterrupt(void);
void TIMER0_void_SetTimer0Reg(Uint8 Copy_value);
void TIMER0_void_SetTimer0CompareMatchReg(Uint8 Copy_value);
void Timer0_void_PWM_CTC(Uint8 Copy_OCR_Set, Uint8 Copy_OCR_Clear);
void Timer0_void_PWM_ADC(Uint8 Copy_channel);
//void TIMER0_void_SetTimer0(Uint16 Copy_Milliseconds);

#endif // TIMER0_INT_H_