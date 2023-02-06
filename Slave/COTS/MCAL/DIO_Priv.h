////Author: Seif Bassiouny
////Date: 4/9/2022
////Version: 1.1
////Module: DIO

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

//Ports' addresses
#define PINA  (*(volatile char*)(0x39))
#define DDRA  (*(volatile char*)(0x3A))
#define PORTA (*(volatile char*)(0x3B))

#define PINB  (*(volatile char*)(0x36))
#define DDRB  (*(volatile char*)(0x37))
#define PORTB (*(volatile char*)(0x38))

#define PINC  (*(volatile char*)(0x33))
#define DDRC  (*(volatile char*)(0x34))
#define PORTC (*(volatile char*)(0x35))

#define PIND  (*(volatile char*)(0x30))
#define DDRD  (*(volatile char*)(0x31))
#define PORTD (*(volatile char*)(0x32))

//Direction options: INPUT - OUTPUT
#define DIO_Uint8_INPUT 0
#define DIO_Uint8_OUTPUT 1

//Limit of each port
#define DIO_Uint8_LIMITA	8
#define DIO_Uint8_LIMITB	16
#define DIO_Uint8_LIMITC	24
#define DIO_Uint8_LIMITD	32

//Direction registers
#define DIO_Uint8_DIRA	CONCATENATE_BITS(DIO_Uint8_PIN_DIR7, DIO_Uint8_PIN_DIR6, DIO_Uint8_PIN_DIR5, DIO_Uint8_PIN_DIR4, DIO_Uint8_PIN_DIR3, DIO_Uint8_PIN_DIR2, DIO_Uint8_PIN_DIR1, DIO_Uint8_PIN_DIR0)
#define DIO_Uint8_DIRB	CONCATENATE_BITS(DIO_Uint8_PIN_DIR15, DIO_Uint8_PIN_DIR14, DIO_Uint8_PIN_DIR13, DIO_Uint8_PIN_DIR12, DIO_Uint8_PIN_DIR11, DIO_Uint8_PIN_DIR10, DIO_Uint8_PIN_DIR9, DIO_Uint8_PIN_DIR8)
#define DIO_Uint8_DIRC	CONCATENATE_BITS(DIO_Uint8_PIN_DIR23, DIO_Uint8_PIN_DIR22, DIO_Uint8_PIN_DIR21, DIO_Uint8_PIN_DIR20, DIO_Uint8_PIN_DIR19, DIO_Uint8_PIN_DIR18, DIO_Uint8_PIN_DIR17, DIO_Uint8_PIN_DIR16)
#define DIO_Uint8_DIRD	CONCATENATE_BITS(DIO_Uint8_PIN_DIR31, DIO_Uint8_PIN_DIR30, DIO_Uint8_PIN_DIR29, DIO_Uint8_PIN_DIR28, DIO_Uint8_PIN_DIR27, DIO_Uint8_PIN_DIR26, DIO_Uint8_PIN_DIR25, DIO_Uint8_PIN_DIR24)


#endif // DIO_PRIV_H_
