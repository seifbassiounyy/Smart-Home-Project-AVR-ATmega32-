////Author: Seif Bassiouny
////Date: 10/10/2022
////Version: 2.2
////Module: EEPROM

#ifndef EEPROM_Int_h__
#define EEPROM_Int_h__

void EEPROM_void_Init(void);
void EEPROM_void_Write(Uint16 Copy_Address, Uint8 Copy_Data);
Uint8 EEPROM_Uint8_Read(Uint16 Copy_Address);
void EEPROM_void_Write_Successive(Uint16 Copy_Address, Uint8 *Copy_Data);
void EEPROM_Uint8_Read_Successive(Uint16 Copy_Address, Uint8 *Ptr_Data, Uint8 Counter, Uint8 *p);

#endif // EEPROM_Int_h__