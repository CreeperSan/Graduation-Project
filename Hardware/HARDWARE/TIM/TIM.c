#include "TIM.h"

void TIM_Twinkle_Init(void)
{
	TIM_TimeBaseInitTypeDef tim_structure;
	NVIC_InitTypeDef nvic_structure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	
	tim_structure.TIM_Period = 5000-1;	//自动重装载值
	tim_structure.TIM_Prescaler = 8400-1;	//定时器分频
	tim_structure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	tim_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3,&tim_structure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	nvic_structure.NVIC_IRQChannel = TIM3_IRQn;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	nvic_structure.NVIC_IRQChannelSubPriority = 0x03;//子优先级3
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
	NVIC_Init(&nvic_structure);
	
}

