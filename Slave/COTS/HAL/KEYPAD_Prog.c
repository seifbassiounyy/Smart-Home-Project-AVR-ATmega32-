////Author: Seif Bassiouny
////Date: 9/9/2022
////Version: 1.3
////Module: KEYPAD

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "DIO_Int.h"
#include "KEYPAD_Int.h"
#include "KEYPAD_Priv.h"
#include "KEYPAD_Config.h"


void KEYPAD_void_Init(void)
{
	#if KEYPAD_Uint8_MODE == KEYPAD_Uint8_INTERNAL_RES
	DIO_void_SetPinValue(KEYPAD_Uint8_COL_1, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_COL_2, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_COL_3, DIO_Uint8_HIGH);
	//DIO_void_SetPinValue(KEYPAD_Uint8_COL_4, DIO_Uint8_HIGH);
	
	#elif KEYPAD_Uint8_MODE == KEYPAD_Uint8_INTERNAL_RES
	
	#endif
}

Uint8 KEYPAD_Uint8_GetPressedNumber(void)
{
	Uint8 Pressed = '\0';
	
	//row1
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_1, DIO_Uint8_LOW);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_2, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_3, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_4, DIO_Uint8_HIGH);
	
	if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_1))
		return KEYPAD_Uint8_R1C1;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_2))
		return KEYPAD_Uint8_R1C2;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_3))
		return KEYPAD_Uint8_R1C3;
		
	//row2
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_1, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_2, DIO_Uint8_LOW);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_3, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_4, DIO_Uint8_HIGH);
	
	if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_1))
		return KEYPAD_Uint8_R2C1;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_2))
		return KEYPAD_Uint8_R2C2;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_3))
		return KEYPAD_Uint8_R2C3;
	
	//row3
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_1, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_2, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_3, DIO_Uint8_LOW);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_4, DIO_Uint8_HIGH);
	
	if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_1))
		return KEYPAD_Uint8_R3C1;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_2))
		return KEYPAD_Uint8_R3C2;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_3))
		return KEYPAD_Uint8_R3C3;
	
	//row4
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_1, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_2, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_3, DIO_Uint8_HIGH);
	DIO_void_SetPinValue(KEYPAD_Uint8_ROW_4, DIO_Uint8_LOW);
	
	if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_1))
		return KEYPAD_Uint8_R4C1;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_2))
		return KEYPAD_Uint8_R4C2;
	else if(!DIO_Uint8_GetPinValue(KEYPAD_Uint8_COL_3))
		return KEYPAD_Uint8_R4C3;
	
	return Pressed;
}