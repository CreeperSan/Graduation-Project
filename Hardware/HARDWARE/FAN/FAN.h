#ifndef __FAN_H
#define __FAN_H

#include "stm32f4xx.h"

#define FAN_PORT 					GPIOA
#define FAN_PORT_RCC 			RCC_AHB1Periph_GPIOA
#define FAN_PIN						GPIO_Pin_1

void FAN_Init(void);
void FAN_On(void);
void FAN_Off(void);

#endif
