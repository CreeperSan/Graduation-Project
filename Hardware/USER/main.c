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

//	!!!  ע�� stm32f4xx.h 89�б���ע���ˣ���Ϊ�����ǵ����ض���ľ���
//�����Ǻ�������


//��������Ҫ�߼�

u16 val_ad1;
u16 val_ad2;

int main(void)
{
//	unsigned char i = 0;
//	u32 FLASH_SIZE;
//	unsigned char SIZE = 1;
//	u8 datatemp[1] = {0};
//	LED_Init();		//LED�ĳ�ʼ��
//	FAN_Init();		//���ȳ�ʼ��
//	BUZZER_Init();	//��������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	UART_Init();	//���ڳ�ʼ��
	delay_init(168);  //��ʼ����ʱ����
//	W25QXX_Init();	//�ⲿFlash׼��
	//TIM_Twinkle_Init();//��ʱ����ʼ��
	AD_Light_Init();	//AD ��ʼ��
	delay_ms(300);//��ʱ300ms
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

// �������жϵĴ�����

void USART1_IRQHandler(void)
{
	u8 rec;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)	//���յ�������
	{
		rec = USART_ReceiveData(USART1);
		
		UART_Send_Byte(rec);
	}
}



void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		printf("��ʱ�жϣ� \r\n");
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}






