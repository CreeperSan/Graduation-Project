
#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx.h"
#include "sys.h"

#define DS18B20_GPIO_PORT   GPIOC
#define DS18B20_GPIO_PIN		GPIO_Pin_0
#define DS18B20_RCC_PORT		RCC_AHB1Periph_GPIOC

//IO方向设置
#define DS18B20_IO_IN()  {GPIOC->MODER&=~(3<<(0*2));GPIOC->MODER|=0<<0*2;}	//PG0输入模式
#define DS18B20_IO_OUT() {GPIOC->MODER&=~(3<<(0*2));GPIOC->MODER|=1<<0*2;} 	//PG0输出模式
 
////IO操作函数											   
#define	DS18B20_DQ_OUT PCout(0) //数据端口	PG0
#define	DS18B20_DQ_IN  PCin(0)  //数据端口	PG0

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


