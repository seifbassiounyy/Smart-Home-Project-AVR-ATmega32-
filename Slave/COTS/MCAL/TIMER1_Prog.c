////Author: Seif Bassiouny
////Date: 21/9/2022
////Version: 1.6
////Module: TIMER1

#include "BIT_MATHS.h"
#include "STD_TYPES.h"
#include "DIO_Int.h"
#include "TIMER1_Int.h"
#include "TIMER1_Priv.h"
#include <avr/io.h>

void TIMER1_void_Init(void)
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
	
	//TCCR1A=0x0000;
	//TCCR1B=0x0000;
	
	//TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	//TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11);		//PRESCALER=64 MODE 8(FAST PWM)

	//ICR1=19999;  //fPWM=50Hz (Period = 20ms Standard).
	//TCNT1=0x0000;
	//OCR1A=0x0000;
	
	//
	
	CLEAR_REG(TCCR1A);
	CLEAR_REG(TCCR1B);
	
	
	
	
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1A, COM1A1);
	//SET_BIT(TCCR1A, COM1B1);
	
	SET_BIT(TCCR1B, WGM13);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, CS11);
	//SET_BIT(TCCR1B, CS10);
	
	ICR1=19999;
	CLEAR_REG(TCNT1);
	CLEAR_REG(OCR1A);
	
	TIMER1_void_SetTimer1CompareMatchReg(125);
	
	//SET_REG_VALUE(ICR1H,0x13);
	//SET_REG_VALUE(ICR1H,0x87);
	//TCNT1=4999;
	
	//TIMER1_void_SetTimer1CompareMatchReg(316);
	
}

void TIMER1_void_SetTimer1CompareMatchReg(Uint16 Copy_value)
{
	OCR1A=Copy_value;
}

/*void TIMER0_void_SetTimer0Reg(Uint8 Copy_value)
{
	SET_REG_VALUE(TCNT0, Copy_value);
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