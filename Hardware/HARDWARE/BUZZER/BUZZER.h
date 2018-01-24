#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f4xx.h"

#define BUZZER_PORT 					GPIOA
#define BUZZER_PORT_RCC 			RCC_AHB1Periph_GPIOA
#define BUZZER_PIN						GPIO_Pin_2

void BUZZER_Init(void);
void BUZZER_On(void);
void BUZZER_Off(void);


#endif

