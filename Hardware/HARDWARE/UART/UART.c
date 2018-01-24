#include "UART.h"
#include "stdio.h"

/**
	* 串口的初始化
	*/
void UART_Init(void)
{
	GPIO_InitTypeDef gpio_structure;	//GPIO初始化
	USART_InitTypeDef uart_structure;	//UART初始化
	NVIC_InitTypeDef nvic_structure;	//NVIC初始化
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//GPIO初始化
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	//设置复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	gpio_structure.GPIO_Mode = GPIO_Mode_AF;	//复用引脚
	gpio_structure.GPIO_OType = GPIO_OType_PP;
	gpio_structure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio_structure.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_structure);
	
	//串口初始化
	
	uart_structure.USART_BaudRate = 115200;	//设置波特率
	uart_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//设置无硬件数据流控制
	uart_structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//设置为发送和接受模式
	uart_structure.USART_Parity = USART_Parity_No;	//设置为无奇偶检验
	uart_structure.USART_StopBits = USART_StopBits_1;	///设置为1为停止位
	uart_structure.USART_WordLength = USART_WordLength_8b;	//设置字长为8个字节
	USART_Init(USART1,&uart_structure);
	
	USART_Cmd(USART1,ENABLE);	//使能串口
	
	USART_ClearFlag(USART1,USART_FLAG_TC);	//清楚标志位
	
	//往下是开启接受中断的
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	nvic_structure.NVIC_IRQChannel = USART1_IRQn;
	nvic_structure.NVIC_IRQChannelCmd = ENABLE;
	nvic_structure.NVIC_IRQChannelPreemptionPriority = 3;
	nvic_structure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic_structure);
}

/**
	*	串口发送一个Byte
	*/
void UART_Send_Byte(uint8_t dat)
{
	USART_SendData(USART1,dat);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
	*	串口发送一个字符串
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
	*	重定向printf()
	*/
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}

