#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx.h"

#define DHT11_GPIO_PORT		GPIOC
#define DHT11_GPIO_PIN   	GPIO_Pin_1
#define DHT11_RCC_PORT 		RCC_AHB1Periph_GPIOC

void DHT11_Init_Rcc(void);
void DHT11_Init_As_Output(void);
void DHT11_Init_As_Input(void);

static u8 DHT11_Get_Pin_Status(void);
static u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Humiture(unsigned char humitureDat[5]);

#endif

