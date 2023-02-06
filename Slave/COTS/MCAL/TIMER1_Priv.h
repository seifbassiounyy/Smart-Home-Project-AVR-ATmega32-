////Author: Seif Bassiouny
////Date: 21/9/2022
////Version: 1.6
////Module: TIMER1

#ifndef TIMER1_PRIV_H_
#define TIMER1_PRIV_H_

//Timer registers
#define TCNT1L  (*(volatile char*)(0x4C))
#define TCNT1H  (*(volatile char*)(0x4D))
#define TCCR1A  (*(volatile char*)(0x4F))
#define TCCR1B  (*(volatile char*)(0x4E))
#define TIFR    (*(volatile char*)(0x58))
#define TIMSK   (*(volatile char*)(0x59))
#define OCR1AL  (*(volatile char*)(0x4A))
#define OCR1AH  (*(volatile char*)(0x4B))
#define ICR1L   (*(volatile char*)(0x46))
#define ICR1H   (*(volatile char*)(0x47))
//Used bits
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM10	0
#define WGM11	1
#define WGM12	3
#define WGM13	4
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7
//#define TOV0	0
//#define OCF0	1
//#define TOIE0	0
//#define OCIE0	1
//Timer mode select.
/*#define	TIMER0_Uint8_NORMAL								0
#define	TIMER0_Uint8_PWM_PHASE_CORRECT					1
#define	TIMER0_Uint8_CTC								2
#define	TIMER0_Uint8_FAST_PWM							3
//OC1 mode select.
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
*/
#endif // TIMER1_PRIV_H_