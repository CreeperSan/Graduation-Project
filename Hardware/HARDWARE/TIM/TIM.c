#include "TIM.h"

void TIM_Twinkle_Init(void)
{
	TIM_TimeBaseInitTypeDef tim_structure;
	NVIC_InitTypeDef nvic_structure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹŜTIM3ʱד
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//测试定时器2
	
	tim_structure.TIM_Period = 5000-1;	//�Զ���װ��ֵ
	tim_structure.TIM_Prescaler = 8400-1;	//��ʱ����Ƶ
	tim_structure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	tim_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3,&tim_structure);//ԵʼۯTIM3
	TIM_TimeBaseInit(TIM2,&tim_structure);//测试定时器2
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//Պѭ֨ʱǷ3ټтא׏
	TIM_Cmd(TIM3,ENABLE); //ʹŜ֨ʱǷ3
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//测试定时器2
	TIM_Cmd(TIM2,ENABLE); //测试定时器2
	
	nvic_structure.NVIC_IRQChannel = TIM3_IRQn;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	nvic_structure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�3
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
	NVIC_Init(&nvic_structure);
	
	nvic_structure.NVIC_IRQChannel = TIM2_IRQn;//测试定时器2
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;//测试定时器2
	nvic_structure.NVIC_IRQChannelSubPriority = 0x03;//测试定时器2
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 0x01;//测试定时器2
	NVIC_Init(&nvic_structure);//测试定时器2
	
}

