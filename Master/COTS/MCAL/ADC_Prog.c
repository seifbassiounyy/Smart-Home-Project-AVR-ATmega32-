////Author: Seif Bassiouny
////Date: 16/9/2022
////Version: 1.5
////Module: ADC

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "ADC_Int.h"
#include "ADC_Priv.h"
#include "ADC_Config.h"

void ADC_void_Init(void)
{
	#if ADC_Uint8_VREF  == ADC_Uint8_AREF
	CLEAR_BIT(ADMUX , 6);
	CLEAR_BIT(ADMUX , 7);
	#elif ADC_Uint8_VREF  == ADC_Uint8_AVCC
	SET_BIT(ADMUX , 6);
	CLEAR_BIT(ADMUX , 7);
	#elif ADC_Uint8_VREF  == ADC_Uint8_INTERNAL
	SET_BIT(ADMUX , 6);
	SET_BIT(ADMUX , 7);
	#endif
	
	#if ADC_Uint8_ADLAR	== ADC_Uint8_LEFTADJUSTMENT
	SET_BIT(ADMUX , 5);
	#elif ADC_Uint8_ADLAR	== ADC_Uint8_RIGHTADJUSTMENT
	CLEAR_BIT(ADMUX , 5);
	#endif
	
	#if ADC_Uint8_PRESCALER == ADC_Uint8_2_DIVFACTOR
	CLEAR_BIT(ADCSRA, 0);
	CLEAR_BIT(ADCSRA, 1);
	CLEAR_BIT(ADCSRA, 2);
	#elif ADC_Uint8_PRESCALER == ADC_Uint8_4_DIVFACTOR
	CLEAR_BIT(ADCSRA, 0);
	SET_BIT(ADCSRA, 1);
	CLEAR_BIT(ADCSRA, 2);
	#elif ADC_Uint8_PRESCALER == ADC_Uint8_8_DIVFACTOR
	SET_BIT(ADCSRA, 0);
	SET_BIT(ADCSRA, 1);
	CLEAR_BIT(ADCSRA, 2);
	#elif ADC_Uint8_PRESCALER == ADC_Uint8_128_DIVFACTOR
	SET_BIT(ADCSRA, 0);
	SET_BIT(ADCSRA, 1);
	SET_BIT(ADCSRA, 2);
	#endif
	ADC_void_Enable();	
}

Uint8 ADC_Uint8_GetConversionSingleEndded(Uint8 Copy_Channel)
{
	ADMUX = ADMUX & 0b11100000;
	ADMUX = ADMUX | Copy_Channel;
	SET_BIT(ADCSRA, 6);
	while(GET_BIT(ADCSRA, 6) == 1)
	{
		
	}
	return ADCH;
}

Uint16 ADC_Uint16_GetConversionSingleEndded(Uint8 Copy_Channel)
{
	Uint16 result = 0;
	Uint8 *p = &result;
	ADMUX &= 0b11100000;
	ADMUX |= Copy_Channel;
	SET_BIT(ADCSRA, 6);
	while(GET_BIT(ADCSRA, 6))
	{
			
	}
	*p = ADCL;
	p++;
	*p = ADCH;	
	return result;
}

void ADC_void_Enable(void)
{
	SET_BIT(ADCSRA, 7);
}

void ADC_void_Disable(void)
{
	CLEAR_BIT(ADCSRA, 7);
}
