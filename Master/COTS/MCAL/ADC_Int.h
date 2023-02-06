////Author: Seif Bassiouny
////Date: 16/9/2022
////Version: 1.5
////Module: ADC

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#define ADC_Uint8_CHANNEL_0		0
#define ADC_Uint8_CHANNEL_1		1
#define ADC_Uint8_CHANNEL_2		2
#define ADC_Uint8_CHANNEL_3		3
#define ADC_Uint8_CHANNEL_4		4
#define ADC_Uint8_CHANNEL_5		5
#define ADC_Uint8_CHANNEL_6		6
#define ADC_Uint8_CHANNEL_7		7

void   ADC_void_Init(void);
void   ADC_void_Enable(void);
void   ADC_void_Disable(void);
Uint8  ADC_Uint8_GetConversionSingleEndded(Uint8 Copy_Channel);
Uint16 ADC_Uint16_GetConversionSingleEndded(Uint8 Copy_Channel);

#endif // ADC_INIT_H_