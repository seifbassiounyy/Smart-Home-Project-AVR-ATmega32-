////Author: Seif Bassiouny
////Date: 8/9/2022
////Version: 1.2
////Module: LCD

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include<string.h>
#include "DIO_Int.h" 
#include "LCD_Int.h"
#include "LCD_Priv.h"
#include "LCD_Config.h"

#define F_CPU 16000000UL
#include<util/delay.h>

//Initialization
void LCD_void_Init(void)
{
	 _delay_ms(35);
	 LCD_void_SetCommand(0x33);
	 _delay_ms(2);
	 LCD_void_SetCommand(0x32);
	 _delay_ms(2);
	 LCD_void_SetCommand(0x28);
	 _delay_ms(2);
	 LCD_void_SetCommand(0x0c);
	 _delay_ms(2);
	 LCD_void_SetCommand(0x06);//0x7 to enable shift
	 _delay_ms(2);
	 LCD_void_SetCommand(0x01);
	 _delay_ms(2);
}

//Setters
void LCD_void_SetData(Uint8 Copy_data)
{
	DIO_void_SetPinValue(LCD_Uint8_RS, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(LCD_Uint8_RW, DIO_Uint8_LOW);
	
	#if LCD_Uint8_DL == LCD_Uint8_4_BIT
	//Write upper nibble pins
	if(GET_BIT(Copy_data, 4) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 5) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 6) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 7) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);
	//Write upper nibble
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);
	//Write lower nibble pins
	if(GET_BIT(Copy_data, 0) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 1) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 2) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 3) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);
	//Write lower nibble
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);

	
	#elif LCD_Uint8_DL == LCD_Uint8_8_BIT
	//
	if(GET_BIT(Copy_data, 0) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D0, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D0, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 1) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D1, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D1, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 2) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D2, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D2, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 3) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D3, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D3, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 4) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 5) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 6) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_data, 7) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);
	//
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);	
	#endif
	

}

void LCD_void_SetCommand(Uint8 Copy_command)
{
	DIO_void_SetPinValue(LCD_Uint8_RS, DIO_Uint8_LOW);
	DIO_void_SetPinValue(LCD_Uint8_RW, DIO_Uint8_LOW);  
	
	#if LCD_Uint8_DL == LCD_Uint8_4_BIT
	//Write upper nibble pins
	if(GET_BIT(Copy_command, 4) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 5) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 6) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 7) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);	
	//Write upper nibble
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);
	//Write lower nibble pins
	if(GET_BIT(Copy_command, 0) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 1) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 2) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 3) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);
	//Write lower nibble
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);

	#elif LCD_Uint8_DL == LCD_Uint8_8_BIT
	//Write every pin
	if(GET_BIT(Copy_command, 0) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D0, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D0, DIO_Uint8_LOW);  
	if(GET_BIT(Copy_command, 1) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D1, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D1, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 2) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D2, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D2, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 3) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D3, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D3, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 4) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D4, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 5) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D5, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 6) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D6, DIO_Uint8_LOW);
	if(GET_BIT(Copy_command, 7) == 1)
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_HIGH);
	else
	DIO_void_SetPinValue(LCD_Uint8_D7, DIO_Uint8_LOW);
	//Write data
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_HIGH);
	_delay_ms(1);
	DIO_void_SetPinValue(LCD_Uint8_E, DIO_Uint8_LOW);
	_delay_ms(1);
	#endif
	
}

void LCD_void_SetString(Sint8* P_string)
{
	Uint8 i = 0;
	while(P_string[i] != '\0')
	{
		LCD_void_SetData(P_string[i]);
		i++;
	}
	
}

void LCD_void_SetCursor(Uint8 Copy_row, Uint8 Copy_column)
{
	Uint8 address = 0;
	switch(Copy_row)
	{
		case 0:
			address = 0x80 + Copy_column;
			break;
		case 1:
			address = 0x80 + 0x40 + Copy_column;	
			break;
	}
	LCD_void_SetCommand(address);
	_delay_ms(1);
}

void LCD_void_ClearScreen(void)
{
	LCD_void_SetCommand(0b00000001);
}