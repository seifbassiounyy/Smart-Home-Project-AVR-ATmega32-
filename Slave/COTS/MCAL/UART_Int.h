////Author: Seif Bassiouny
////Date: 5/10/2022
////Version: 2.0
////Module: UART

#ifndef UART_Int_h__
#define UART_Int_h__

void UART_void_Init(void);
void UART_void_Transmit(Uint8 Copy_Data);
Uint8 UART_Uint8_Receive(void);
Uint8 UART_Uint8_Receive2(void);
void UART_void_Transmit_String(Uint8 *Copy_String);

#endif // UART_Int_h__