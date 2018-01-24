#include "LED.h"


/**
	*		LED的初始化
	*/
void LED_Init()
{
	GPIO_InitTypeDef gpio_structure;
	RCC_AHB1PeriphClockCmd(LED_RCC_PORT,ENABLE);	//使能时钟
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = LED_PIN_RED | LED_PIN_GREEN | LED_PIN_BLUE;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_PORT,&gpio_structure);
	
}

/**
	*		打开红灯
	*/
void LED_Set_Red()
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		打开绿灯
	*/
void LED_Set_Blue()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		打开蓝灯
	*/
void LED_Set_Green()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		关灯
	*/
void LED_Set_Off()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}

