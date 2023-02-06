////Author: Seif Bassiouny
////Date: 16/9/2022
////Version: 1.5
////Module: ADC

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

//Registers used in ADC
#define ADCL   (*(volatile char*)(0x24))
#define ADCH   (*(volatile char*)(0x25))
#define ADCSRA (*(volatile char*)(0x26))
#define ADMUX (*(volatile char*)(0x27))
#define SFIOR  (*(volatile char*)(0x50))
//Adjustment of data
#define ADC_Uint8_RIGHTADJUSTMENT	0
#define ADC_Uint8_LEFTADJUSTMENT	1
//Mode of receiving data
#define ADC_Uint8_POLLING	0
#define ADC_Uint8_INTERRUPT	1
//Types of VREF
#define ADC_Uint8_AREF		0
#define ADC_Uint8_AVCC		1
#define ADC_Uint8_INTERNAL	2
//Division factors of ADC
#define ADC_Uint8_2_DIVFACTOR		0
//#define ADC_Uint8_2_DIVFACTOR		1
#define ADC_Uint8_4_DIVFACTOR		2
#define ADC_Uint8_8_DIVFACTOR		3
#define ADC_Uint8_16_DIVFACTOR		4
#define ADC_Uint8_32_DIVFACTOR		5
#define ADC_Uint8_64_DIVFACTOR		6
#define ADC_Uint8_128_DIVFACTOR		7
//Modes of ADC
#define ADC_Uint8_SINGLECONVERSION	0
#define ADC_Uint8_FREERUNNING		1
#define ADC_Uint8_AUTOTRIGGER		2

#endif // ADC_PRIV_H_