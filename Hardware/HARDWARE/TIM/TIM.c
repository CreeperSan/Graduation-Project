#include "TIM.h"

void TIM_Twinkle_Init(void)
{
	TIM_TimeBaseInitTypeDef tim_structure;
	NVIC_InitTypeDef nvic_structure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3ʱ��
	
	tim_structure.TIM_Period = 5000-1;	//�Զ���װ��ֵ
	tim_structure.TIM_Prescaler = 8400-1;	//��ʱ����Ƶ
	tim_structure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	tim_structure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3,&tim_structure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	nvic_structure.NVIC_IRQChannel = TIM3_IRQn;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	nvic_structure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�3
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
	NVIC_Init(&nvic_structure);
	
}

