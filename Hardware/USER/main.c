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
#include "DHT11.h"
#include "DS18B20.h"
#include <string.h>

//	!!!  ע�� stm32f4xx.h 89�б���ע���ˣ���Ϊ�����ǵ����ض���ľ���
//�����Ǻ�������






void READ_GATEWAY_ADDRESS(u8 gatewayAddress[]);
void WRITE_GATEWAY_ADDRESS(void);

void NETWORK_RESET(void);

void CS_LOW(void);
void CS_HIGH(void);

void MySPI_SendData(char da);
uint8_t MySPI_ReceiveData(void);





void NETWORK_RESET()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);	
	delay_ms(50);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);	
	delay_ms(200);
}

void CS_LOW()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
}

void CS_HIGH()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
}

void MySPI_SendData(char da)
{
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);	//??????		  
	SPI2->DR=da;	 	  									//????byte 
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); //???????byte  
	SPI2->DR;	
}

uint8_t MySPI_ReceiveData(void)
{
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);	//??????			  
	SPI2->DR=0xFF;	 	  										//???????????????? 
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); //???????byte  
	return SPI2->DR; 
}

void READ_GATEWAY_ADDRESS(u8 gatewayAddress[])
{
	CS_LOW();
	MySPI_SendData(0x00);
	MySPI_SendData(0x01);
	
	MySPI_SendData(0x00);
	
	gatewayAddress[0] = MySPI_ReceiveData();
	gatewayAddress[1] = MySPI_ReceiveData();
	gatewayAddress[2] = MySPI_ReceiveData();
	gatewayAddress[3] = MySPI_ReceiveData();
	
	CS_HIGH();
}

void WRITE_GATEWAY_ADDRESS()
{
	CS_LOW();
	
	MySPI_SendData(0x00);
	MySPI_SendData(0x01);
	
	MySPI_SendData(0x04);
	
	MySPI_SendData(11);
	MySPI_SendData(22);
	MySPI_SendData(33);
	MySPI_SendData(44);
	
	
	CS_HIGH();
}

void TEST_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  //????
	SPI_InitTypeDef SPI_InitStructure;
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //?????
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //?????
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);	//��ɫ PB10 ��λ
	GPIO_SetBits(GPIOB,GPIO_Pin_11);	//��ɫ PB11 Ƭѡ
	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  //?????????
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2); 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);  //??
	//SPI��ʼ��
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //?????
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   //??????
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //????8
	SPI_InitStructure.SPI_CPOL  = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //????NSS??
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2,&SPI_InitStructure);
	SPI_Cmd(SPI2,ENABLE);
}

void test2()
{
	u8 gatewayAddr[10];
	printf("׼������...");
	TEST_GPIO_Init();
	NETWORK_RESET();
	printf("��ʼ����...");
	while(1)
	{
		delay_ms(500);
		WRITE_GATEWAY_ADDRESS();
		READ_GATEWAY_ADDRESS(gatewayAddr);
		printf("%d.%d.%d.%d",gatewayAddr[0],gatewayAddr[1],gatewayAddr[2],gatewayAddr[3]);
	}
}






//��������Ҫ�߼�

u16 val_ad1;
u16 val_ad2;

unsigned char val_humidity[5];
unsigned char val_humidity_result = 0;
short val_temperature;  

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
//	AD_Light_Init();	//AD ��ʼ��
//	DHT11_Init_Rcc();
//	DHT11_Init_As_Output();
	delay_ms(300);//��ʱ300ms
	
//	while(DS18B20_Init())
//	{
//		printf("Fail");
//		delay_ms(1000);
//	}
	
	//ר�����
	printf("start test 2\n");
	test2();
	//���Խ���
	
	printf("Application Running...");

	while(1)
	{
		delay_ms(500);

		printf("һ��ѭ��");
		
//		val_temperature = DS18B20_Get_Temp();
//		printf("�¶� %d",val_temperature);
		
		
//		USART_Cmd(USART1,DISABLE);
//		val_humidity_result = DHT11_Read_Humiture(val_humidity);
//		USART_Cmd(USART1,ENABLE);
//		printf("��� %d ʪ�� %d , �¶� %d , ȫ����� %d %d %d %d %d \r\n",val_humidity_result,val_humidity[0],val_humidity[2],val_humidity[0],val_humidity[1],val_humidity[2],val_humidity[3],val_humidity[4]);
		
		
		
//		W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);
//		i = datatemp[0];
//		i++ ;
//		datatemp[0] = i;
//		W25QXX_Write(datatemp,FLASH_SIZE-100,SIZE);
//		printf("Hello World!  %d \r\n",i);
		
//		val_ad1 = AD_Light_Get_Adc_Result(ADC_Channel_5,5);
//		val_ad2 = AD_Light_Get_Adc_Result(ADC_Channel_3,5);
//		printf("AD1 => %d ,AD2 => %d\r\n",val_ad1,val_ad2);
		
		
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





