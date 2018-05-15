#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h" 

#define LED_PORT 				GPIOC
#define LED_RCC_PORT			RCC_AHB1Periph_GPIOC
#define LED_PIN_RED 			GPIO_Pin_6
#define LED_PIN_GREEN 			GPIO_Pin_7
#define LED_PIN_BLUE 			GPIO_Pin_8

void LED_Init(void);
void LED_Set_Red(int lightLevel);
void LED_Set_Blue(int lightLevel);
void LED_Set_Green(int lightLevel);
void LED_Set_Cyan(int lightLevel);
void LED_Set_Purple(int lightLevel);
void LED_Set_Yellow(int lightLevel);
void LED_Set_White(int lightLevel);
void LED_Set_Off(void);
void LED_Set_Level(int level);
static void initTim(void);

#endif
