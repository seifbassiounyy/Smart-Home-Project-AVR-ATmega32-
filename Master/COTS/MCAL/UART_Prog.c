////Author: Seif Bassiouny
////Date: 5/10/2022
////Version: 2.0
////Module: UART

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "UART_Priv.h"
#include "UART_Config.h"
#include "UART_Int.h"


void UART_void_Init(void)
{
	
	//UBRRH = 0;		// write zero on the last bit to choose UBRRH
	//UBRRL = 103;
	
	//SET_BIT(UCSRC, 7);
	
	#if UART_Uint8_CLK_MODE == UART_Uint8_ASYNCHRONOUS
	CLEAR_BIT(UCSRC, 6);
	#elif UART_Uint8_CLK_MODE == UART_Uint8_SYNCHRONOUS
	SET_BIT(UCSRC, 6);	
	#endif
	
	#if UART_Uint8_PARITY_MODE == UART_Uint8_NO_PARITY
	CLEAR_BIT(UCSRC, 4);
	CLEAR_BIT(UCSRC, 5);
	#elif UART_Uint8_PARITY_MODE == UART_Uint8_EVEN_PARITY
	CLEAR_BIT(UCSRC, 4);
	SET_BIT(UCSRC, 5);
	#elif UART_Uint8_PARITY_MODE == UART_Uint8_ODD_PARITY
	SET_BIT(UCSRC, 4);
	SET_BIT(UCSRC, 5);
	#endif
	
	#if UART_Uint8_STOP_BIT == UART_Uint8_1_STOP_BIT
	CLEAR_BIT(UCSRC, 3);
	#elif UART_Uint8_STOP_BIT == UART_Uint8_2_STOP_BIT
	SET_BIT(UCSRC, 3);
	#endif
	
	#if UART_Uint8_DATA_BITS == UART_Uint8_5_DATA_BITS
	CLEAR_BIT(UCSRC, 1);
	CLEAR_BIT(UCSRC, 2);
	CLEAR_BIT(UCSRB, 2);
	#elif UART_Uint8_DATA_BITS == UART_Uint8_6_DATA_BITS
	SET_BIT(UCSRC, 1);
	CLEAR_BIT(UCSRC, 2);
	CLEAR_BIT(UCSRB, 2);
	#elif UART_Uint8_DATA_BITS == UART_Uint8_7_DATA_BITS
	CLEAR_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	CLEAR_BIT(UCSRB, 2);
	#elif UART_Uint8_DATA_BITS == UART_Uint8_8_DATA_BITS
	SET_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	CLEAR_BIT(UCSRB, 2);
	#elif UART_Uint8_DATA_BITS == UART_Uint8_9_DATA_BITS
	SET_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	SET_BIT(UCSRB, 2);
	#endif
	
	UBRRH = 0; // write zero on the last bit to choose UBRRH
	UBRRL = 25; //103 odfmim
	
	CLEAR_BIT(UCSRB, 5);
	CLEAR_BIT(UCSRB, 6);
	CLEAR_BIT(UCSRB, 7);
	
	SET_BIT(UCSRB, 3);
	SET_BIT(UCSRB, 4);

}

void UART_void_Transmit(Uint8 Copy_Data)
{
	while(!GET_BIT(UCSRA, 5));
	SET_REG_VALUE(UDR, Copy_Data);
}

Uint8 UART_Uint8_Receive(void)
{
	while(!GET_BIT(UCSRA, 7));
	return UDR;
}

Uint8 UART_Uint8_Receive2(void)
{
	if(GET_BIT(UCSRA, 7))
	return UDR;
	else
	return '\0';
}

void UART_void_Transmit_String(Uint8 *Copy_String)
{
	Uint8 i = 0;
	while(Copy_String[i]!='\0')
	{
	while(!GET_BIT(UCSRA, 5));
	SET_REG_VALUE(UDR, Copy_String[i]);
	i++;
	}
}