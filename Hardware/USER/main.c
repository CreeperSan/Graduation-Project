#include "stm32f4xx.h"
#include "LED.h"
#include "FAN.h"
#include "BUZZER.h"
#include "UART.h"
#include "sys.h"
#include "delay.h"
#include "FLASH.h"
#include "TIM.h"
#include "AD.h"
//#include "usart.h"

//	!!!  注意 stm32f4xx.h 89行被我注释了，因为他老是弹出重定义的警告
//往下是函数声明


//往下是主要逻辑

u16 val_ad1;
u16 val_ad2;

int main(void)
{
//	unsigned char i = 0;
//	u32 FLASH_SIZE;
//	unsigned char SIZE = 1;
//	u8 datatemp[1] = {0};
//	LED_Init();		//LED的初始化
//	FAN_Init();		//风扇初始化
//	BUZZER_Init();	//蜂鸣器初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	UART_Init();	//串口初始化
	delay_init(168);  //初始化延时函数
//	W25QXX_Init();	//外部Flash准备
	//TIM_Twinkle_Init();//定时器初始化
	AD_Light_Init();	//AD 初始化
	delay_ms(300);//延时300ms
	while(1)
	{
//		W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);
//		i = datatemp[0];
//		i++ ;
//		datatemp[0] = i;
//		W25QXX_Write(datatemp,FLASH_SIZE-100,SIZE);
//		printf("Hello World!  %d \r\n",i);
		delay_ms(500);
		val_ad1 = AD_Light_Get_Adc_Result(ADC_Channel_5,5);
		val_ad2 = AD_Light_Get_Adc_Result(ADC_Channel_3,5);
		printf("AD1 => %d ,AD2 => %d\r\n",val_ad1,val_ad2);
	}
}

// 往下是中断的处理句柄

void USART1_IRQHandler(void)
{
	u8 rec;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)	//接收到数据了
	{
		rec = USART_ReceiveData(USART1);
		
		UART_Send_Byte(rec);
	}
}



void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		printf("定时中断！ \r\n");
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}






