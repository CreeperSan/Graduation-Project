#include "DHT11.h"
#include "delay.h"
#include "UART.h"

void DHT11_Init_Rcc(void)
{
	RCC_AHB1PeriphClockCmd(DHT11_RCC_PORT,ENABLE);
}

void DHT11_Init_As_Output(void)
{
	GPIO_InitTypeDef gpio_stucture;
	gpio_stucture.GPIO_Mode = GPIO_Mode_OUT;
	gpio_stucture.GPIO_OType = GPIO_OType_PP;
	gpio_stucture.GPIO_Pin = DHT11_GPIO_PIN;
	gpio_stucture.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_stucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&gpio_stucture);
	GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
}


void DHT11_Init_As_Input(void)
{
	GPIO_InitTypeDef gpio_stucture;
	gpio_stucture.GPIO_Mode = GPIO_Mode_IN;
	gpio_stucture.GPIO_Pin = DHT11_GPIO_PIN;
	gpio_stucture.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_stucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&gpio_stucture);
	GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
}



static u8 DHT11_Get_Pin_Status(void)
{
	return GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
}


static u8 DHT11_Read_Byte(void)
{
	unsigned char i,result = 0;
	for(i = 0;i<8;i++)
	{
		while(DHT11_Get_Pin_Status() == 0);
		delay_us(40);
		if(DHT11_Get_Pin_Status() == 1)
		{
			while(DHT11_Get_Pin_Status() == 1);
			result |= (uint8_t)(0x01 << (7-i));
		}
	}
	return result;
}


u8 DHT11_Read_Humiture(unsigned char humitureDat[5])
{
	unsigned int tempCount;
	
	DHT11_Init_As_Output();
	GPIO_ResetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
	delay_us(20000);
	GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
	delay_us(30);
	DHT11_Init_As_Input();
	if(DHT11_Get_Pin_Status() == 0)
	{
		tempCount = 0;
		while(DHT11_Get_Pin_Status() == 0)
		{
			tempCount++;
			if(tempCount > 100)
			{
				return 0;
			}
			delay_us(10);
		}
		tempCount = 0;
		while(DHT11_Get_Pin_Status() == 1)
		{
			tempCount++;
			if(tempCount>100)
			{
				return 0;
			}
			delay_us(10);
		}
		humitureDat[0] = DHT11_Read_Byte();
		humitureDat[1] = DHT11_Read_Byte();
		humitureDat[2] = DHT11_Read_Byte();
		humitureDat[3] = DHT11_Read_Byte();
		humitureDat[4] = DHT11_Read_Byte();
		DHT11_Init_As_Output();
		GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);
		if(humitureDat[4] == humitureDat[0] + humitureDat[1] + humitureDat[2] + humitureDat[3] )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
