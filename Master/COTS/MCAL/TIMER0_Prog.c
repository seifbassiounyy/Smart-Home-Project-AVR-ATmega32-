////Author: Seif Bassiouny
////Date: 21/9/2022
////Version: 1.6
////Module: TIMER0

#include "BIT_MATHS.h"
#include "STD_TYPES.h"
#include "TIMER0_Int.h"
#include "TIMER0_Priv.h"

void TIMER0_void_Init(void)
{
	//Set timer mode
	/*#if TIMER0_Uint8_MODE == TIMER0_Uint8_NORMAL
	CLEAR_BIT(TCCR0, WGM00);
	CLEAR_BIT(TCCR0, WGM01);
	#elif TIMER0_Uint8_MODE == TIMER0_Uint8_PWM_PHASE_CORRECT
	SET_BIT(TCCR0, WGM00);
	CLEAR_BIT(TCCR0, WGM01);
	#elif TIMER0_Uint8_MODE == TIMER0_Uint8_FAST_PWM
	*/
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	/*#elif TIMER0_Uint8_MODE == TIMER0_Uint8_CTC
	CLEAR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	#endif
	*/
	//Set OC0 mode
	/*#if TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_NORMAL_PORT
	CLEAR_BIT(TCCR0, COM00);
	CLEAR_BIT(TCCR0, COM01);
	#elif TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_TOGGLE
	SET_BIT(TCCR0, COM00);
	CLEAR_BIT(TCCR0, COM01);
	#elif TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_CLEAR
	CLEAR_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
	#elif TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_SET
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
	#elif TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_NON_INVERTING
	*/
	CLEAR_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
	/*#elif TIMER0_Uint8_OC0_MODE == TIMER0_Uint8_INVERTING
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
	#endif
	*/
	//Clear TCNTO and OCR0 registers
	CLEAR_REG(TCNT0);
	CLEAR_REG(OCR0);
	//Setting clock along with its pre-scaler factor
	/*#if   TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_NO_CLOCK_SOURCE
	CLEAR_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
	*///#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_INTERNAL_CLOCK_1
	SET_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
	/*#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_INTERNAL_CLOCK_8
	CLEAR_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
	#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_INTERNAL_CLOCK_64
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
	#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_INTERNAL_CLOCK_256
	CLEAR_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_INTERNAL_CLOCK_1024
	SET_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_EXTERNAL_CLOCK_T0_FALLING_EDGE
	CLEAR_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	#elif TIMER0_Uint8_CLOCK_SELECT == TIMER0_Uint8_EXTERNAL_CLOCK_T0_RISING_EDGE
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	#endif
	*/
}

void TIMER0_void_SetTimer0Reg(Uint8 Copy_value)
{
	SET_REG_VALUE(TCNT0, Copy_value);
}

void TIMER0_void_SetTimer0CompareMatchReg(Uint8 Copy_value)
{
	SET_REG_VALUE(OCR0, Copy_value);
}

void TIMER0_void_EnableInterrupt(void)
{
	//#if TIMER0_Uint8_MODE == TIMER0_Uint8_NORMAL
	SET_BIT(TIMSK, TOIE0);
	//#elif TIMER0_Uint8_MODE == TIMER0_Uint8_CTC
	SET_BIT(TIMSK, OCIE0);
	//#endif
}

void TIMER0_void_DisableInterrupt(void)
{
	//#if TIMER0_Uint8_MODE == TIMER0_Uint8_NORMAL
	CLEAR_BIT(TIMSK, TOIE0);
	//#elif TIMER0_Uint8_MODE == TIMER0_Uint8_CTC
	CLEAR_BIT(TIMSK, OCIE0);
	//#endif
}

void Timer0_void_PWM_CTC(Uint8 Copy_OCR_Set, Uint8 Copy_OCR_Clear)
{
	//Set OCR0 with the value to set OC0 pin at
	TIMER0_void_SetTimer0CompareMatchReg(Copy_OCR_Set);
	//Set timer mode CTC
	CLEAR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	//Set on compare match
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
	//while TCNT0 has not reached OCR0 (compare match), do nothing
	while(GET_BIT(TIFR, 1) == 0)
	{
		
	}
	//clear compare flag
	SET_BIT(TIFR, 1);
	//Set OCR0 with the value to clear OC0 pin at
	TIMER0_void_SetTimer0CompareMatchReg(Copy_OCR_Clear);
	//Clear on compare match
	CLEAR_BIT(TCCR0, COM00);
	//while TCNT0 has not reached OCR0 (compare match), do nothing
	while(GET_BIT(TIFR, 1) == 0)
	{
	}
	//clear compare flag
	SET_BIT(TIFR, 1);
}

void Timer0_void_PWM_ADC(Uint8 Copy_channel)
{
	//Get reading from ADC through specified channel
	Uint8 conversion = ADC_Uint8_GetConversionSingleEndded(Copy_channel);
	//Set OCR0 with this conversion to generate corresponding PWM
	TIMER0_void_SetTimer0CompareMatchReg(conversion);
}
/*
void TIMER0_void_SetTimer0(Uint16 Copy_Millis)
{
	Uint8 preload = 0;
	Fint32 NOVFLS = 0;
	
	if(TIMER0_Uint8_MODE == TIMER0_Uint8_NORMAL)
	{
		if(Copy_Millis <= TIMER0_TOVF)
		{
			preload = (TIMER0_TOVF - Copy_Millis)/TIMER0_TICK_TIME; 
			SET_REG_VALUE(TCNT0, preload);
		}
		else if(Copy_Millis > TIMER0_TOVF)
		{
			
		}
	}
}
*/