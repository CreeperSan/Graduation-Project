#include "FAN.h"

/**
	*	风扇的初始化
	*/
void FAN_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	RCC_AHB1PeriphClockCmd(FAN_PORT_RCC,ENABLE);
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = FAN_PIN;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(FAN_PORT,&gpio_structure);
}

/**
	*	打开风扇
	*/
void FAN_On(void)
{
	GPIO_SetBits(FAN_PORT,FAN_PIN);
}

/**
	*	关闭风扇
	*/
void FAN_Off(void)
{
	GPIO_ResetBits(FAN_PORT,FAN_PIN);
}

