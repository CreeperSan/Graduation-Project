#include "WARM.h"

void WARM_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = GPIO_Pin_4;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOD,&gpio_structure);
}


void WARM_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_4);
}

void WARM_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
}
