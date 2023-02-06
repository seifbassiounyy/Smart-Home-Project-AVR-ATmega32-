////Author: Seif Bassiouny
////Date: 4/9/2022
////Version: 1.1
////Module: DIO

#include "STD_TYPES.h"
#include "DIO_Int.h"
#include "BIT_MATHS.h"
#include "DIO_Config.h"
#include "DIO_Priv.h"

//1-Initialization
void DIO_void_Init(void)
{
	DDRA = DIO_Uint8_DIRA;
	DDRB = DIO_Uint8_DIRB;
	DDRC = DIO_Uint8_DIRC;
	DDRD = DIO_Uint8_DIRD;
}

//2-Setter: Pins (0 -> 31), value (HIGH - LOW)
void DIO_void_SetPinValue(Uint8 Copy_pin, Uint8 Copy_value)
{
	if(Copy_pin < DIO_Uint8_LIMITA)
	{
		switch(Copy_value)
		{
			case DIO_Uint8_HIGH:	SET_BIT(PORTA, Copy_pin); break;
			case DIO_Uint8_LOW:		CLEAR_BIT(PORTA, Copy_pin); break;
			default: break;
		}	
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITB)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITA;
		switch(Copy_value)
		{
			case DIO_Uint8_HIGH:	SET_BIT(PORTB, Copy_pin); break;
			case DIO_Uint8_LOW:		CLEAR_BIT(PORTB, Copy_pin); break;
			default: break;
		}
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITC)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITB;
		switch(Copy_value)
		{
			case DIO_Uint8_HIGH:	SET_BIT(PORTC, Copy_pin); break;
			case DIO_Uint8_LOW:		CLEAR_BIT(PORTC, Copy_pin); break;
			default: break;
		}
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITD)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITC;
		switch(Copy_value)
		{
			case DIO_Uint8_HIGH:	SET_BIT(PORTD, Copy_pin); break;
			case DIO_Uint8_LOW:		CLEAR_BIT(PORTD, Copy_pin); break;
			default: break;
		}
	}
}

//3-Getter: Pin (0 -> 31) , returns value.
Uint8 DIO_Uint8_GetPinValue(Uint8 Copy_pin)
{
	Uint8 value = 0;
	
	if(Copy_pin < DIO_Uint8_LIMITA)
	{
		value = GET_BIT(PINA, Copy_pin);
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITB)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITA;
		value = GET_BIT(PINB, Copy_pin);
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITC)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITB;
		value = GET_BIT(PINC, Copy_pin);
	}
	
	else if(Copy_pin < DIO_Uint8_LIMITD)
	{
		Copy_pin = Copy_pin - DIO_Uint8_LIMITC;
		value = GET_BIT(PIND, Copy_pin);
	}
	
	return value;
}

void DIO_void_TogglePinValue(Uint8 Copy_pin)
{
	if(DIO_Uint8_GetPinValue(Copy_pin))
	DIO_void_SetPinValue(Copy_pin, DIO_Uint8_LOW);
	else if(!DIO_Uint8_GetPinValue(Copy_pin))
	DIO_void_SetPinValue(Copy_pin, DIO_Uint8_HIGH);
}