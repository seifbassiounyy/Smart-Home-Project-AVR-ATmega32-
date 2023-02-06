////Author: Seif Bassiouny
////Date: 4/9/2022
////Version: 1.1
////Module: DIO

#ifndef DIO_INT_H_
#define DIO_INT_H_

//Pins of micro controller
//PORTA
#define DIO_Uint8_PIN0		0
#define DIO_Uint8_PIN1		1
#define DIO_Uint8_PIN2		2
#define DIO_Uint8_PIN3		3
#define DIO_Uint8_PIN4		4
#define DIO_Uint8_PIN5		5
#define DIO_Uint8_PIN6		6
#define DIO_Uint8_PIN7		7
//PORTB
#define DIO_Uint8_PIN8		8
#define DIO_Uint8_PIN9		9
#define DIO_Uint8_PIN10		10
#define DIO_Uint8_PIN11	    11
#define DIO_Uint8_PIN12		12
#define DIO_Uint8_PIN13		13
#define DIO_Uint8_PIN14		14
#define DIO_Uint8_PIN15		15
//PORTC
#define DIO_Uint8_PIN16		16
#define DIO_Uint8_PIN17		17
#define DIO_Uint8_PIN18		18
#define DIO_Uint8_PIN19		19
#define DIO_Uint8_PIN20		20
#define DIO_Uint8_PIN21		21
#define DIO_Uint8_PIN22		22
#define DIO_Uint8_PIN23		23
//PORTD
#define DIO_Uint8_PIN24		24
#define DIO_Uint8_PIN25		25
#define DIO_Uint8_PIN26		26
#define DIO_Uint8_PIN27		27
#define DIO_Uint8_PIN28		28
#define DIO_Uint8_PIN29		29
#define DIO_Uint8_PIN30		30
#define DIO_Uint8_PIN31		31
//Values
#define DIO_Uint8_HIGH		1
#define DIO_Uint8_LOW		0
//Functions of DIO
//1-Initialization
void DIO_void_Init(void);
//2-Setter: Pins (0 -> 31), value (HIGH - LOW)
void DIO_void_SetPinValue(Uint8 Copy_pin, Uint8 Copy_value);
//3-Getter: Pin (0 -> 31) , returns value.
Uint8 DIO_Uint8_GetPinValue(Uint8 Copy_pin);
//4-Update: Pin (0 -> 31)
void DIO_void_TogglePinValue(Uint8 Copy_pin);

#endif // DIO_INT_H_