#include "MOTOR.h"

void MOTOR_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOC,&gpio_structure);
	
}

void MOTOR_Water_On(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
}

void MOTOR_Water_Off(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
}

void MOTOR_Fertilized_On(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
}

void MOTOR_Fertilized_Off(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
}

