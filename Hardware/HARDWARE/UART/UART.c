#include "UART.h"
#include "stdio.h"

/**
	* ���ڵĳ�ʼ��
	*/
void UART_Init(void)
{
	GPIO_InitTypeDef gpio_structure;	//GPIO��ʼ��
	USART_InitTypeDef uart_structure;	//UART��ʼ��
	NVIC_InitTypeDef nvic_structure;	//NVIC��ʼ��
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//GPIO��ʼ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	//���ø���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	gpio_structure.GPIO_Mode = GPIO_Mode_AF;	//��������
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_structure);
	
	//���ڳ�ʼ��
	
	uart_structure.USART_BaudRate = 115200;	//���ò�����
	uart_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//������Ӳ������������
	uart_structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//����Ϊ���ͺͽ���ģʽ
	uart_structure.USART_Parity = USART_Parity_No;	//����Ϊ����ż����
	uart_structure.USART_StopBits = USART_StopBits_1;	///����Ϊ1Ϊֹͣλ
	uart_structure.USART_WordLength = USART_WordLength_8b;	//�����ֳ�Ϊ8���ֽ�
	USART_Init(USART1,&uart_structure);
	
	USART_Cmd(USART1,ENABLE);	//ʹ�ܴ���
	
	USART_ClearFlag(USART1,USART_FLAG_TC);	//�����־λ
	
	//�����ǿ��������жϵ�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	nvic_structure.NVIC_IRQChannel = USART1_IRQn;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 3;
	nvic_structure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic_structure);
}

/**
	*	���ڷ���һ��Byte
	*/
void UART_Send_Byte(uint8_t dat)
{
	USART_SendData(USART1,dat);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
	*	���ڷ���һ���ַ���
	*/
void UART_Send_String(char *dat)
{
	unsigned char i = 0;
	while( *(dat + i) != '\0' )
	{
		UART_Send_Byte(*(dat+i));
		i++;
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET );
}

/**
	*	�ض���printf()
	*/
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}

