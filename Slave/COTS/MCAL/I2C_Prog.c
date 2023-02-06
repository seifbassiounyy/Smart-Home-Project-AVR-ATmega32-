////Author: Seif Bassiouny
////Date: 7/10/2022
////Version: 2.1
////Module: I2C

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "I2C_Priv.h"
#include "I2C_Config.h"
#include "I2C_Int.h"

void I2C_void_Init(void)
{
	/*#if I2C_Uint8_ACK_MODE == I2C_Uint8_NACK
	CLEAR_BIT(TWCR, TWEA);
	#elif I2C_Uint8_ACK_MODE == I2C_Uint8_ACK
	SET_BIT(TWCR, TWEA);
	#endif
	#if I2C_Uint8_INT_MODE == I2C_Uint8_INT_DISABLE
	CLEAR_BIT(TWCR, TWIE);
	#elif I2C_Uint8_INT_MODE == I2C_Uint8_INT_ENABLE
	SET_BIT(TWCR, TWIE);
	#endif
	#if I2C_Uint8_GENERAL_CALL_MODE == I2C_Uint8_DISABLE_GENERAL_CALL
	CLEAR_BIT(TWAR, TWGCE);
	#elif I2C_Uint8_GENERAL_CALL_MODE == I2C_Uint8_ENABLE_GENERAL_CALL
	SET_BIT(TWAR, TWGCE);
	#endif
	*/ 
	//Set our SCL frequency
	SET_BIT(TWCR, TWEA);
	SET_BIT(TWCR, TWEN);
	TWBR = 10;
	SET_BIT(TWSR,0);
	CLEAR_BIT(TWSR,1);
}

void I2C_void_Send_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while(!GET_BIT(TWCR, TWINT));
}

void I2C_void_Send_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_void_Send_Byte(Uint8 Copy_Byte)
{
	SET_REG_VALUE(TWDR, Copy_Byte);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!GET_BIT(TWCR, TWINT));
}

void I2C_void_Transmit(Uint8 Copy_Address, Uint8 Copy_Data)
{
	I2C_void_Send_Start();
	
	if((TWSR & 0xF8) == I2C_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(Copy_Address);
		
		if((TWSR & 0xF8) == I2C_Uint8_SLA_W_ACK)
		{
			I2C_void_Send_Byte(Copy_Data);
			if((TWSR & 0xF8) == I2C_Uint8_DATA_TRANSMITTED_NACK)
			{
				I2C_void_Send_Stop();
			}
		}
	}
}


Uint8 I2C_Uint8_Receive(Uint8 Copy_Address)
{
	Uint8 received_data = 0;
	I2C_void_Send_Start();
	if((TWSR & 0xF8) == I2C_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(Copy_Address);
		
		if((TWSR & 0xF8) == I2C_Uint8_SLA_R_NACK)
		{
			SET_BIT(TWCR, TWINT);
			SET_BIT(TWCR, TWEN);
			while(!GET_BIT(TWCR, TWINT));
			if((TWSR & 0xF8) == I2C_Uint8_DATA_RECEIVED_NACK)
			{
				received_data = TWDR;
				I2C_void_Send_Stop();
				return received_data;
			}	
		}	
	}
}

void I2C_void_Set_SLAVE_ADDRESS(Uint8 Copy_Address)
{
	SET_REG_VALUE(TWAR, Copy_Address<<1);
}
