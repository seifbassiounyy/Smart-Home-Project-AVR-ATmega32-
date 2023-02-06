////Author: Seif Bassiouny
////Date: 21/9/2022
////Version: 1.6
////Module: TIMER0

#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_

//Timer registers
#define TCNT0  (*(volatile char*)(0x52))
#define TCCR0  (*(volatile char*)(0x53))
#define TIFR   (*(volatile char*)(0x58))
#define TIMSK  (*(volatile char*)(0x59))
#define OCR0   (*(volatile char*)(0x5C))
//Used bits
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define TOV0	0
#define OCF0	1
#define TOIE0	0
#define OCIE0	1
//Timer mode select.
#define	TIMER0_Uint8_NORMAL								0
#define	TIMER0_Uint8_PWM_PHASE_CORRECT					1
#define	TIMER0_Uint8_CTC								2
#define	TIMER0_Uint8_FAST_PWM							3
//OC0 mode select.
#define TIMER0_Uint8_NORMAL_PORT						0
#define TIMER0_Uint8_TOGGLE								1
#define TIMER0_Uint8_CLEAR								2
#define TIMER0_Uint8_SET								3
#define TIMER0_Uint8_NON_INVERTING						4
#define TIMER0_Uint8_INVERTING							5
//Clock select.
#define TIMER0_Uint8_NO_CLOCK_SOURCE					0
#define TIMER0_Uint8_INTERNAL_CLOCK_1					1
#define TIMER0_Uint8_INTERNAL_CLOCK_8					2
#define TIMER0_Uint8_INTERNAL_CLOCK_64					3
#define TIMER0_Uint8_INTERNAL_CLOCK_256					4
#define TIMER0_Uint8_INTERNAL_CLOCK_1024				5
#define TIMER0_Uint8_EXTERNAL_CLOCK_T0_FALLING_EDGE		6
#define TIMER0_Uint8_EXTERNAL_CLOCK_T0_RISING_EDGE		7

#endif // TIMER0_PRIV_H_