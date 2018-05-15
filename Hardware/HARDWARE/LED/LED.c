#include "LED.h"


/**
	*		LED�ĳ�ʼ��
	*/
void LED_Init()
{
	GPIO_InitTypeDef gpio_structure;
	
	RCC_AHB1PeriphClockCmd(LED_RCC_PORT,ENABLE);	//ʹ��ʱ��
	gpio_structure.GPIO_Mode = GPIO_Mode_AF;
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = LED_PIN_RED | LED_PIN_GREEN | LED_PIN_BLUE;
	// gpio_structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_structure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(LED_PORT,&gpio_structure);
	
	GPIO_PinAFConfig(LED_PORT, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(LED_PORT, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(LED_PORT, GPIO_PinSource8, GPIO_AF_TIM3);

	initTim();
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	
//	tim_structure.TIM_Period = 5000-1;	//自动重装载值
//	tim_structure.TIM_Prescaler = 8400-1;	// 定时器分频 
//	tim_structure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
//	tim_structure.TIM_ClockDivision = TIM_CKD_DIV1;
//	
//	TIM_TimeBaseInit(TIM3,&tim_structure);//初始化定时器3
//	
//	tim_oc_structure.TIM_OCMode = TIM_OCMode_PWM1;
//	tim_oc_structure.TIM_OutputState = TIM_OutputState_Enable;
//	tim_oc_structure.TIM_OCPolarity = TIM_OCPolarity_Low;
//	TIM_OC1Init(TIM3, &tim_oc_structure);
//	
//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//	
//	TIM_ARRPreloadConfig(TIM3,ENABLE);
//	
//	TIM_Cmd(TIM3,ENABLE); //ʹŜ֨ʱǷ3

}

static void initTim()
{
	TIM_TimeBaseInitTypeDef tim_structure;
	TIM_OCInitTypeDef tim_oc_structure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹŜTIM3ʱד

	tim_structure.TIM_Prescaler = 2999;
	tim_structure.TIM_CounterMode = TIM_CounterMode_Up;
	tim_structure.TIM_Period = 83;
	tim_structure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM3, &tim_structure);

	tim_oc_structure.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_structure.TIM_OutputState = TIM_OutputState_Enable;
	tim_oc_structure.TIM_OCPolarity = TIM_OCPolarity_Low;

	// tim_oc_structure.TIM_OutputNState = TIM_OutputNState_Enable;
	// tim_oc_structure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// tim_oc_structure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	

	TIM_OC1Init(TIM3,&tim_oc_structure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3,&tim_oc_structure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3,&tim_oc_structure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);


	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, 0);

	TIM_Cmd(TIM3, ENABLE);

}

/**
	*		�򿪺��
	*/
void LED_Set_Red(int lightLevel)
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, lightLevel);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, 0);
}
/**
	*		���̵�
	*/
void LED_Set_Blue(int lightLevel)
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, lightLevel);
}
/**
	*		������
	*/
void LED_Set_Green(int lightLevel)
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, lightLevel);
	TIM_SetCompare3(TIM3, 0);
}

/**
  *	������ɫΪ��ɫ
  */
void LED_Set_Cyan(int lightLevel)
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, lightLevel);
	TIM_SetCompare3(TIM3, lightLevel);
}

/**
  *	������ɫΪ��ɫ
  */
void LED_Set_Purple(int lightLevel)
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, lightLevel);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, lightLevel);
}

/**
  *	������ɫΪ��ɫ
  */
void LED_Set_Yellow(int lightLevel)
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, lightLevel);
	TIM_SetCompare2(TIM3, lightLevel);
	TIM_SetCompare3(TIM3, 0);
}

/**
  *	������ɫΪ��ɫ
  */
void LED_Set_White(int lightLevel)
{
	GPIO_ResetBits(LED_PORT,LED_PIN_RED);
	GPIO_ResetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_ResetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, lightLevel);
	TIM_SetCompare2(TIM3, lightLevel);
	TIM_SetCompare3(TIM3, lightLevel);
}

/**
	*		�ص�
	*/
void LED_Set_Off()
{
	GPIO_SetBits(LED_PORT,LED_PIN_RED);
	GPIO_SetBits(LED_PORT,LED_PIN_GREEN);
	GPIO_SetBits(LED_PORT,LED_PIN_BLUE);
	TIM_SetCompare1(TIM3, 0);
	TIM_SetCompare2(TIM3, 0);
	TIM_SetCompare3(TIM3, 0);
}

void LED_Set_Level(int level)
{
	
}
