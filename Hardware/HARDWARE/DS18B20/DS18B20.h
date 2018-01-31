
#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx.h"
#include "sys.h"

#define DS18B20_GPIO_PORT   GPIOC
#define DS18B20_GPIO_PIN		GPIO_Pin_0
#define DS18B20_RCC_PORT		RCC_AHB1Periph_GPIOC

//IO��������
#define DS18B20_IO_IN()  {GPIOC->MODER&=~(3<<(0*2));GPIOC->MODER|=0<<0*2;}	//PG0����ģʽ
#define DS18B20_IO_OUT() {GPIOC->MODER&=~(3<<(0*2));GPIOC->MODER|=1<<0*2;} 	//PG0���ģʽ
 
////IO��������											   
#define	DS18B20_DQ_OUT PCout(0) //���ݶ˿�	PG0
#define	DS18B20_DQ_IN  PCin(0)  //���ݶ˿�	PG0

u8    DS18B20_Init(void);
short DS18B20_Get_Temp(void);
void  DS18B20_Start(void);
void  DS18B20_Write_Byte(u8 dat);
u8    DS18B20_Read_Byte(void);
u8    DS18B20_Read_Bit(void);
u8    DS18B20_Check(void);
void  DS18B20_Reset(void);

void  DS18B20_Set_Input(void);
void  DS18B20_Set_Output(void);

void  DS18B20_Set_High(void);
void  DS18B20_Set_Low(void);

#endif


