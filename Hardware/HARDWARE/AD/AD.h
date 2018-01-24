#ifndef __AD_H
#define __AD_H

#include "stm32f4xx.h"

void AD_Light_Init(void);
u16	 AD_Light_Get_Adc(u8 channel);
u16	 AD_Light_Get_Adc_Result(u8 channel,u8 times);
void AD_Dirt_Humidity_Init(void);
u16	 AD_Dirt_Get_Adc(u8 channel);
u16	 AD_Dirt_Get_Adc_Result(u8 channel,u8 times);

#endif


