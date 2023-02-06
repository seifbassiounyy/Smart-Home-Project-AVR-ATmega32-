////Author: Seif Bassiouny
////Date: 7/10/2022
////Version: 2.1
////Module: I2C

#ifndef I2C_Int_h__
#define I2C_Int_h__

void I2C_void_Init(void);
void I2C_void_Transmit(Uint8 Copy_Data, Uint8 Copy_Address);
Uint8 I2C_Uint8_Receive(Uint8 Copy_Address);
void I2C_void_Set_SLAVE_ADDRESS(Uint8 Copy_Address);
void I2C_void_Send_Byte(Uint8 Copy_Byte);
void I2C_void_Send_Start(void);
void I2C_void_Send_Stop(void);

#endif // I2C_Int_h__