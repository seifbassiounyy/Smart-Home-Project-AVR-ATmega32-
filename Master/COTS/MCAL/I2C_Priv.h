////Author: Seif Bassiouny
////Date: 7/10/2022
////Version: 2.1
////Module: I2C

#ifndef I2C_Priv_h__
#define I2C_Priv_h__
//Registers
#define TWBR  (*(volatile char*)(0x20))
#define TWSR  (*(volatile char*)(0x21))
#define TWAR  (*(volatile char*)(0x22))
#define TWDR  (*(volatile char*)(0x23))
#define TWCR  (*(volatile char*)(0x56))
//Modes
#define I2C_Uint8_NACK					0
#define I2C_Uint8_ACK					1
#define I2C_Uint8_INT_DISABLE			0
#define I2C_Uint8_INT_ENABLE			1
#define I2C_Uint8_DISABLE_GENERAL_CALL	0
#define I2C_Uint8_ENABLE_GENERAL_CALL	1
//Bits
#define TWGCE	0
#define TWIE	0
#define TWEN	2
#define TWWC	3
#define TWSTO	4
#define TWSTA	5
#define TWEA	6
#define TWINT	7
//TWSR modes
#define I2C_Uint8_STA_TRANSMITTED		0x08
#define I2C_Uint8_SLA_W_NACK			0x20		
#define I2C_Uint8_SLA_W_ACK				0x18
#define I2C_Uint8_SLA_R_NACK			0x48
#define I2C_Uint8_SLA_R_ACK				0x40
#define I2C_Uint8_DATA_TRANSMITTED_NACK	0x30
#define I2C_Uint8_DATA_TRANSMITTED_ACK	0x28
#define I2C_Uint8_DATA_RECEIVED_NACK	0x58
#define I2C_Uint8_DATA_RECEIVED_ACK		0x50

#endif // I2C_Priv_h__
