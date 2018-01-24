#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h" 

#define LED_PORT 				GPIOA
#define LED_RCC_PORT			RCC_AHB1Periph_GPIOA
#define LED_PIN_RED 			GPIO_Pin_6
#define LED_PIN_GREEN 			GPIO_Pin_7
#define LED_PIN_BLUE 			GPIO_Pin_12

void LED_Init(void);
void LED_Set_Red(void);
void LED_Set_Blue(void);
void LED_Set_Green(void);
void LED_Set_Off(void);

#endif
