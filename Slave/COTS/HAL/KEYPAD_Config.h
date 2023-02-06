////Author: Seif Bassiouny
////Date: 9/9/2022
////Version: 1.3
////Module: KEYPAD

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

//Rows are output
#define KEYPAD_Uint8_ROW_1		DIO_Uint8_PIN26
#define KEYPAD_Uint8_ROW_2		DIO_Uint8_PIN27
#define KEYPAD_Uint8_ROW_3		DIO_Uint8_PIN28
#define KEYPAD_Uint8_ROW_4		DIO_Uint8_PIN30
//Columns are input
#define KEYPAD_Uint8_COL_1		DIO_Uint8_PIN18
#define KEYPAD_Uint8_COL_2		DIO_Uint8_PIN19
#define KEYPAD_Uint8_COL_3		DIO_Uint8_PIN20
//#define KEYPAD_Uint8_COL_4		DIO_Uint8_PIN22

#define KEYPAD_Uint8_R1C1		'1'
#define KEYPAD_Uint8_R1C2		'2' 
#define KEYPAD_Uint8_R1C3		'3' 
//#define KEYPAD_Uint8_R1C4		'A' 
#define KEYPAD_Uint8_R2C1		'4' 
#define KEYPAD_Uint8_R2C2		'5' 
#define KEYPAD_Uint8_R2C3		'6' 
//#define KEYPAD_Uint8_R2C4		'B' 
#define KEYPAD_Uint8_R3C1		'7' 
#define KEYPAD_Uint8_R3C2		'8' 
#define KEYPAD_Uint8_R3C3		'9' 
//#define KEYPAD_Uint8_R3C4		'C' 
#define KEYPAD_Uint8_R4C1		'*' 
#define KEYPAD_Uint8_R4C2		'0'
#define KEYPAD_Uint8_R4C3		'#'
//#define KEYPAD_Uint8_R4C4		'D'

/*
Options:	DIO_Uint8_INTERNAL_RES	-	DIO_Uint8_EXTERNAL_RES
*/

#define KEYPAD_Uint8_MODE		DIO_Uint8_INTERNAL_RES


#endif // KEYPAD_CONFIG_H_