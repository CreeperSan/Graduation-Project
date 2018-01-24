#include "LED.h"


/**
	*		LED�ĳ�ʼ��
	*/
void LED_Init()
{
	GPIO_InitTypeDef gpio_structure;
	RCC_AHB1PeriphClockCmd(LED_RCC_PORT,ENABLE);	//ʹ��ʱ��
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = LED_PIN_RED | LED_PIN_GREEN | LED_PIN_BLUE;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_PORT,&gpio_structure);
	
}

/**
	*		�򿪺��
	*/
void LED_Set_Red()
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		���̵�
	*/
void LED_Set_Blue()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		������
	*/
void LED_Set_Green()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
}
/**
	*		�ص�
	*/
void LED_Set_Off()
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
}

