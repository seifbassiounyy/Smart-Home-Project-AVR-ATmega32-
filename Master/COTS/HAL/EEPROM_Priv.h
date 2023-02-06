////Author: Seif Bassiouny
////Date: 10/10/2022
////Version: 2.2
////Module: EEPROM

#ifndef EEPROM_Priv_h__
#define EEPROM_Priv_h__

//Registers
#define TWBR  (*(volatile char*)(0x20))
#define TWSR  (*(volatile char*)(0x21))
#define TWAR  (*(volatile char*)(0x22))
#define TWDR  (*(volatile char*)(0x23))
#define TWCR  (*(volatile char*)(0x56))
//Modes
#define EEPROM_Uint8_NACK					0
#define EEPROM_Uint8_ACK					1
#define EEPROM_Uint8_INT_DISABLE			0
#define EEPROM_Uint8_INT_ENABLE			1
#define EEPROM_Uint8_DISABLE_GENERAL_CALL	0
#define EEPROM_Uint8_ENABLE_GENERAL_CALL	1
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
#define EEPROM_Uint8_STA_TRANSMITTED		0x08
#define EEPROM_Uint8_SLA_W_NACK				0x20
#define EEPROM_Uint8_SLA_W_ACK				0x18
#define EEPROM_Uint8_SLA_R_NACK				0x48
#define EEPROM_Uint8_SLA_R_ACK				0x40
#define EEPROM_Uint8_DATA_TRANSMITTED_NACK	0x30
#define EEPROM_Uint8_DATA_TRANSMITTED_ACK	0x28
#define EEPROM_Uint8_DATA_RECEIVED_NACK		0x58
#define EEPROM_Uint8_DATA_RECEIVED_ACK		0x50
#define EEPROM_Uint8_RSTA_TRANSMITTED		0x10


#endif // EEPROM_Priv_h__