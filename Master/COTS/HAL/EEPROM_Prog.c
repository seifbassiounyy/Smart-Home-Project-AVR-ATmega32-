////Author: Seif Bassiouny
////Date: 10/10/2022
////Version: 2.2
////Module: EEPROM

#define  F_CPU 1000000UL
#include  "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "EEPROM_Priv.h"
#include "EEPROM_Config.h"
#include "EEPROM_Int.h"
#include "I2C_Int.h"

void EEPROM_void_Init(void)
{
	I2C_void_Init();
}

void EEPROM_void_Write(Uint16 Copy_Address, Uint8 Copy_Data)
{
	Uint8 SLA_W = 0b10100000;
	SLA_W |= ((GET_BIT(Copy_Address, 8)<<1) | (GET_BIT(Copy_Address, 9)<<2) | (GET_BIT(Copy_Address , 10)<<3));
	I2C_void_Send_Start();
	
	if((TWSR & 0xF8) == EEPROM_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(SLA_W);
		if((TWSR & 0xF8) == EEPROM_Uint8_SLA_W_ACK)
		{
			I2C_void_Send_Byte((Uint8)Copy_Address);
			if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
			{
				I2C_void_Send_Byte(Copy_Data);
				if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
				{
					I2C_void_Send_Stop();
				}
			}
		}
	}
}



Uint8 EEPROM_Uint8_Read(Uint16 Copy_Address)
{
	Uint8 received_data = 0;
	Uint8 SLA_W = 0b10100000;
	Uint8 SLA_R = 0;
	SLA_W |= ((GET_BIT(Copy_Address , 8)<<1) | (GET_BIT(Copy_Address , 9)<<2) | (GET_BIT(Copy_Address , 10)<<3));
	SLA_R = SLA_W + 1 ;
	I2C_void_Send_Start();
	if((TWSR & 0xF8) == EEPROM_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(SLA_W);
		if((TWSR & 0xF8) == EEPROM_Uint8_SLA_W_ACK)
		{
			I2C_void_Send_Byte((Uint8)Copy_Address);
			if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
			{
				I2C_void_Send_Start();
				if((TWSR & 0xF8) == EEPROM_Uint8_RSTA_TRANSMITTED)
				{
					I2C_void_Send_Byte(SLA_R);
					if((TWSR & 0xF8) == EEPROM_Uint8_SLA_R_ACK)
					{
						TWCR = (1<<TWINT) | (1<<TWEN);
						while(!GET_BIT(TWCR , TWINT));
						received_data = TWDR;
						I2C_void_Send_Stop();
						
					}
				}	
			}
		}
	}
	return received_data;
}


void EEPROM_void_Write_Successive(Uint16 Copy_Address, Uint8 *Copy_Data)
{
	Uint8 i = 0;
	while(Copy_Data[i] != '\0')
	{
		
	Uint8 SLA_W = 0b10100000;
	SLA_W |= ((GET_BIT(Copy_Address , 8)<<1) | (GET_BIT(Copy_Address , 9)<<2) | (GET_BIT(Copy_Address , 10)<<3));
	I2C_void_Send_Start();
	
	if((TWSR & 0xF8) == EEPROM_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(SLA_W);
		if((TWSR & 0xF8) == EEPROM_Uint8_SLA_W_ACK)
		{
			I2C_void_Send_Byte((Uint8)Copy_Address);
			if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
			{
				I2C_void_Send_Byte(Copy_Data[i]);
				if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
				{
					I2C_void_Send_Stop();
				}
			}
		}
	}
	Copy_Address++;
	i++;
	_delay_ms(5);
  }
}

void EEPROM_Uint8_Read_Successive(Uint16 Copy_Address, Uint8 *Ptr_Data, Uint8 Counter, Uint8 *p)
{
	Uint8 i = 0;
	while(i < Counter)
	{
	*p = *p + 1;
	Uint8 SLA_W = 0b10100000;
	Uint8 SLA_R = 0;
	SLA_W |= ((GET_BIT(Copy_Address , 8)<<1) | (GET_BIT(Copy_Address , 9)<<2) | (GET_BIT(Copy_Address , 10)<<3));
	SLA_R = SLA_W + 1 ;
	I2C_void_Send_Start();
	if((TWSR & 0xF8) == EEPROM_Uint8_STA_TRANSMITTED)
	{
		I2C_void_Send_Byte(SLA_W);
		if((TWSR & 0xF8) == EEPROM_Uint8_SLA_W_ACK)
		{
			I2C_void_Send_Byte((Uint8)Copy_Address);
			if((TWSR & 0xF8) == EEPROM_Uint8_DATA_TRANSMITTED_ACK)
			{
				I2C_void_Send_Start();
				if((TWSR & 0xF8) == EEPROM_Uint8_RSTA_TRANSMITTED)
				{
					I2C_void_Send_Byte(SLA_R);
					if((TWSR & 0xF8) == EEPROM_Uint8_SLA_R_ACK)
					{
						TWCR = (1<<TWINT) | (1<<TWEN);
						while(!GET_BIT(TWCR , TWINT));
						Ptr_Data[i] = TWDR;
						I2C_void_Send_Stop();
					}
				}
			}
		}
	}
	i++;
	Copy_Address++;
	_delay_ms(5);
	}
}