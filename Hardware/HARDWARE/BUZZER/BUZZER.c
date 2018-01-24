#include "BUZZER.h"

/**
	*	�������ĳ�ʼ��
	*/
void BUZZER_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	RCC_AHB1PeriphClockCmd(BUZZER_PORT_RCC,ENABLE);	//ʹ��ʱ��
	gpio_structure.GPIO_Mode = GPIO_Mode_OUT;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = BUZZER_PIN ;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUZZER_PORT,&gpio_structure);
}

/**
	*	�������ĳ�ʼ��
	*/
void BUZZER_On(void)
{
	GPIO_SetBits(BUZZER_PORT,BUZZER_PIN);
}

/**
	*	�������ĳ�ʼ��
	*/
void BUZZER_Off(void)
{
	GPIO_ResetBits(BUZZER_PORT,BUZZER_PIN);
}

