////Author: Seif Bassiouny
////Date: 5/10/2022
////Version: 2.0
////Module: UART

#ifndef UART_Priv_h__
#define UART_Priv_h__


#define UDR		(*(volatile char*)(0x2C))
#define UCSRA	(*(volatile char*)(0x2B))
#define UCSRB	(*(volatile char*)(0x2A))
#define UCSRC	(*(volatile char*)(0x40))
#define UBRRL	(*(volatile char*)(0x29))
#define UBRRH	(*(volatile char*)(0x40))

#define UART_Uint8_ASYNCHRONOUS		0
#define UART_Uint8_SYNCHRONOUS		1

#define UART_Uint8_NO_PARITY		0
#define UART_Uint8_EVEN_PARITY		1
#define UART_Uint8_ODD_PARITY		2

#define UART_Uint8_1_STOP_BIT		0
#define UART_Uint8_2_STOP_BIT		1

#define UART_Uint8_5_DATA_BITS		0
#define UART_Uint8_6_DATA_BITS		1
#define UART_Uint8_7_DATA_BITS		2
#define UART_Uint8_8_DATA_BITS		3
#define UART_Uint8_9_DATA_BITS		4

#define UART_Uint8_RISINGTRANSMIT_FALLINGRECEIVE	0
#define UART_Uint8_RISINGRECEIVE_FALLINGTRANSMIT	1

#endif // UART_Priv_h__