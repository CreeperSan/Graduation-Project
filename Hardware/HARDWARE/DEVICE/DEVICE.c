#include "DEVICE.h"

void DEVICE_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOD,&gpio_structure);
	
}

void DEVICE_1_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
}
void DEVICE_1_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
}

void DEVICE_2_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_1);
}
void DEVICE_2_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_1);
}

void DEVICE_3_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
}
void DEVICE_3_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void DEVICE_4_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_3);
}
void DEVICE_4_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
}
