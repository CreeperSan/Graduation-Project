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
#include "DEVICE.h"
#include "MOTOR.h"
#include "WARM.h"
#include <string.h>

void initBuffer(void);
void sendDataBack(void);
void initConfig(void); // 从FLASH中读取配置
void refreshLightState(void);


const unsigned int FLASH_BASE_ADDRESS =  0;
#define ADDR_DEVICE1 		FLASH_BASE_ADDRESS+1 	// 自定义设备1
#define ADDR_DEVICE2 		FLASH_BASE_ADDRESS+2 	// 自定义设备2
#define ADDR_DEVICE3 		FLASH_BASE_ADDRESS+3 	// 自定义设备3
#define ADDR_DEVICE4 		FLASH_BASE_ADDRESS+4 	// 自定义设备4
#define ADDR_FAN			FLASH_BASE_ADDRESS+5	// 风扇
#define ADDR_WARM			FLASH_BASE_ADDRESS+6	// 加热膜
#define ADDR_FERTILIZATION	FLASH_BASE_ADDRESS+7	// 施肥
#define ADDR_WATERING		FLASH_BASE_ADDRESS+8	// 浇水
#define ADDR_LIGHT			FLASH_BASE_ADDRESS+9	// 灯光开关
#define ADDR_LIGHT_COLOR	FLASH_BASE_ADDRESS+10	// 灯光颜色
#define ADDR_LIGHT_LEVEL	FLASH_BASE_ADDRESS+11	// 灯光亮度

#define ADDR_AIR_TEMP_UP			FLASH_BASE_ADDRESS+0x10		// 空气温度上限
#define ADDR_AIR_TEMP_DOWN			FLASH_BASE_ADDRESS+0x12		// 空气湿度上限
#define ADDR_AIR_HUMIDITY_UP		FLASH_BASE_ADDRESS+0x14		// 空气温度上限
#define ADDR_AIR_HUMIDITY_DOWN		FLASH_BASE_ADDRESS+0x16		// 空气湿度上限
#define ADDR_DIRT_TEMP_UP			FLASH_BASE_ADDRESS+0x18		// 湿度温度上限
#define ADDR_DIRT_TEMP_DOWN			FLASH_BASE_ADDRESS+0x1a		// 湿度湿度上限
#define ADDR_DIRT_HUMIDITY_UP		FLASH_BASE_ADDRESS+0x1c		// 湿度温度上限
#define ADDR_DIRT_HUMIDITY_DOWN		FLASH_BASE_ADDRESS+0x1e		// 湿度湿度上限

unsigned char i = 0;

volatile char val_device1 = 0;		// 自定义设备1
volatile char val_device2 = 0;		// 自定义设备2
volatile char val_device3 = 0; 	// 自定义设备3
volatile char val_device4 = 0; 	// 自定义设备4
volatile char val_fan = 0; 		// 风扇
volatile char val_warm = 0; 		// 加热
volatile char val_fertiliozation = 0;	// 施肥
volatile char val_water = 0;				// 浇水
volatile char val_buzzer = 0;			// 蜂鸣器
volatile char val_light = 0;				// 灯光开关
volatile char val_light_color = 0;		// 灯光颜色
volatile char val_light_level = 0;		// 灯光亮度
volatile u16	 val_air_temp_up = 0;			// 气温上限
volatile u16	 val_air_temp_low = 0;			// 气湿下限
volatile u16	 val_air_humidity_up = 0;		// 气温上限
volatile u16	 val_air_humidity_low = 0;		// 气湿下限
volatile u16	 val_dirt_temp_up = 0;			// 土温上限
volatile u16	 val_dirt_temp_low = 0;			// 土湿下限
volatile u16	 val_dirt_humidity_up = 0;		// 土温上限
volatile u16	 val_dirt_humidity_low = 0;		// 土湿下限

u8 val_dht11[5];			// 空气温度空气湿度
short val_18b20;			// 土壤温度,2个Byte
u16 val_ad_dirt_humidity;	// 土壤湿度
u16 val_ad_light;			// 亮度AD

char val_send_buffer[33]; 
u8 val_dht11_result;	//DHT11的读取结果

u16 tempData = 0;
u8 isError = 0;

/**
 *	Main 函数
 */ 

const unsigned int TIME_SEND = 5;
const unsigned int TIME_FERTILIZED = 100;
const unsigned int TIME_WATRER = 100;

unsigned int count_send = TIME_SEND;
unsigned int count_feterlized = 0;
unsigned int count_water = 0;

int main(void)
{
	delay_init(168); 
	DEVICE_Init(); 
	FAN_Init();
	WARM_Init();
	MOTOR_Init();
	BUZZER_Init();
	BUZZER_Off();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	UART_Init();
	TIM_Twinkle_Init();// 定时器初始化
	AD_Light_Init();	// AD 初始化
	while(DS18B20_Init())
	{
		BUZZER_On();
		delay_ms(1000);
	}
	DHT11_Init_Rcc();
	DHT11_Init_As_Output();
	// printf("Running...\r\n\r\n");
	
	MOTOR_Fertilized_Off();
	MOTOR_Water_Off();
	FAN_Off();
	WARM_Off();
	DEVICE_1_Off();
	DEVICE_2_Off();
	DEVICE_3_Off();
	DEVICE_4_Off();
	W25QXX_Init();
	initBuffer();	// 初始化发送的缓冲区
	initConfig();	// 从Flash中读取数据
	
	LED_Init();
	LED_Set_Off();
	while(1)
	{
		
		// USART_Cmd(USART1, DISABLE);
		val_18b20 = DS18B20_Get_Temp(); // 读取土壤温度
		val_dht11_result = DHT11_Read_Humiture(val_dht11); // 读取空气温湿度
		val_ad_light = AD_Light_Get_Adc_Result(ADC_Channel_0,5); // 读取光敏电阻
		val_ad_dirt_humidity = AD_Light_Get_Adc_Result(ADC_Channel_3,5); // 读取土壤湿度
		// USART_Cmd(USART1, ENABLE);

		// 数值做放大缩小处理
		val_18b20 /= 10;
		if(val_ad_dirt_humidity > 62000 ){
			val_ad_dirt_humidity = 62000;
		}else if(val_ad_dirt_humidity < 33000){
			val_ad_dirt_humidity = 33000;
		}
		val_ad_dirt_humidity = 100 - ((val_ad_dirt_humidity - 33000) / 290);
		if(val_ad_light > 54000 ){
			val_ad_light = 54000;
		}else if(val_ad_light < 1000){
			val_ad_light = 1000;
		}
		val_ad_light = 100 - ((val_ad_light - 1000) / 530);
		
		// 初始化发送缓存并且发送数据
		sendDataBack();
		val_send_buffer[4] = val_fan;
		val_send_buffer[5] = val_warm;
		val_send_buffer[6] = val_fertiliozation;
		val_send_buffer[7] = val_water;
		val_send_buffer[8] = val_buzzer;
		val_send_buffer[9] = val_light;
		val_send_buffer[10] = val_light_color;
		val_send_buffer[11] = val_light_level;
		val_send_buffer[12] = 0; // 空气温度
		val_send_buffer[13] = val_dht11[2];
		val_send_buffer[14] = 0; // 空气湿度
		val_send_buffer[15] = val_dht11[0];
		val_send_buffer[16] = val_18b20 >> 8; // 土壤温度
		val_send_buffer[17] = val_18b20 & 0x00ff;
		val_send_buffer[18] = val_ad_dirt_humidity >> 8; // 土壤湿度
		val_send_buffer[19] = val_ad_dirt_humidity & 0x00ff;
		val_send_buffer[20] = val_ad_light >> 8;
		val_send_buffer[21] = val_ad_light & 0x00ff;
		val_send_buffer[22] = val_air_temp_up & 0x00ff;
		val_send_buffer[23] = val_air_temp_low & 0x00ff;
		val_send_buffer[24] = val_air_humidity_up & 0x00ff;
		val_send_buffer[25] = val_air_humidity_low & 0x00ff;
		val_send_buffer[26] = val_dirt_temp_up & 0x00ff;
		val_send_buffer[27] = val_dirt_temp_low & 0x00ff;
		val_send_buffer[28] = val_dirt_humidity_up & 0x00ff;
		val_send_buffer[29] = val_dirt_humidity_low & 0x00ff;
		
		// printf("\nair  %d,%d    %d,%d\n",val_air_temp_low,val_air_temp_up,val_air_humidity_low,val_air_humidity_up);
		// printf("dirt %d,%d    %d,%d\n\n",val_dirt_temp_low,val_dirt_temp_up,val_dirt_humidity_low,val_dirt_humidity_up);

		// 判断和报警
		isError = 0;
		if(val_dht11[2] > val_air_temp_up){
			isError |= 0x01;
		}else if(val_dht11[2] < val_air_temp_low){
			isError |= 0x01;
		}
		// printf("\nair_temp => %d , %d , %d",val_air_temp_low, val_dht11[2],val_air_temp_up);
		if(val_dht11[0] > val_air_humidity_up){
			isError |= 0x01;
		}else if(val_dht11[0] < val_air_humidity_low){
			isError |= 0x01;
		}
		// printf("\nair_humi => %d , %d , %d",val_air_humidity_low, val_dht11[0],val_air_humidity_up);
		if(val_18b20 > val_dirt_temp_up){
			isError |= 0x01;
		}else if(val_18b20 < val_dirt_temp_low){
			isError |= 0x01;
		}
		// printf("\ndirt_temp => %d , %d , %d",val_dirt_temp_low, val_18b20,val_dirt_temp_up);
		if(val_ad_dirt_humidity > val_dirt_humidity_up){
			isError |= 0x01;
		}else if(val_ad_dirt_humidity < val_dirt_humidity_low){
			isError |= 0x01;
		}
		// printf("\ndirt_humi => %d , %d , %d",val_dirt_humidity_low, val_ad_dirt_humidity,val_dirt_humidity_up);

		// printf("\nisError => %d",isError);

		if(isError == 0x00){
			val_buzzer = 0;
		}else{
			val_buzzer = 1;
		}

		// printf("\ntemperature => %d",val_18b20);
		// printf("\ndirt => %d",val_ad_dirt_humidity);
		// printf("\nlight => %d",val_ad_light);

		// 是否应该发送的判断

		if(count_feterlized > 0){
			count_feterlized --;
			MOTOR_Fertilized_On();
		}else{
			MOTOR_Fertilized_Off();
		}

		if(count_water > 0){
			count_water --;
			MOTOR_Water_On();
		}else{
			MOTOR_Water_Off();
		}

		// 发送数据

		if(count_send > 0){
			count_send--;
			if(count_send > TIME_SEND){
				count_send = TIME_SEND;
			}
		}else{
			for(i = 0;i < 33;i++)
			{
				UART_Send_Byte(val_send_buffer[i]);
			}
			count_send = TIME_SEND;
		}
		
			// for(i = 0;i < 33;i++)
			// {
			// 	UART_Send_Byte(val_send_buffer[i]);
			// }
	}
	
}

void initBuffer()
{
	val_send_buffer[0] = 0x11;
	val_send_buffer[1] = 0x99;
	val_send_buffer[2] = 0xff;
	val_send_buffer[30] = 0xf0;
	val_send_buffer[31] = 0x90;
	val_send_buffer[32] = 0x10;
}
void sendDataBack()
{
	u8 tempByte = 0;
	if(val_device1 > 0)
	{
		tempByte = tempByte | 0x01;
	}
	if(val_device2 > 0)
	{
		tempByte = tempByte | 0x02;
	}
	if(val_device3 > 0)
	{
		tempByte = tempByte | 0x04;
	}
	if(val_device4 > 0)
	{
		tempByte = tempByte | 0x08;
	}
	val_send_buffer[3] = tempByte;
}

u8 flash_buffer[2];
void initConfig()
{
	W25QXX_Read(flash_buffer, ADDR_DEVICE1, 1);	// 自定义设备 1
	val_device1 = flash_buffer[0];
	if(val_device1 == 0){
		DEVICE_1_Off();
	}else{
		DEVICE_1_On();
	}
	W25QXX_Read(flash_buffer, ADDR_DEVICE2, 1);	// 自定义设备 2
	val_device2 = flash_buffer[0];
	if(val_device2 == 0){
		DEVICE_2_Off();
	}else{
		DEVICE_2_On();
	}
	W25QXX_Read(flash_buffer, ADDR_DEVICE3, 1);	// 自定义设备 3
	val_device3 = flash_buffer[0];
	if(val_device3 == 0){
		DEVICE_3_Off();
	}else{
		DEVICE_3_On();
	}
	W25QXX_Read(flash_buffer, ADDR_DEVICE4, 1);	// 自定义设备 4
	val_device4 = flash_buffer[0];
	if(val_device4 == 0){
		DEVICE_4_Off();
	}else{
		DEVICE_4_On();
	}
	W25QXX_Read(flash_buffer, ADDR_FAN, 1);	// 风扇
	val_fan = flash_buffer[0];
	if(val_fan == 0){
		FAN_Off();
	}else{
		FAN_On();
	}
	W25QXX_Read(flash_buffer, ADDR_WARM, 1);	// 加热
	val_warm = flash_buffer[0];
	if(val_warm == 0){
		WARM_Off();
	}else{
		WARM_On();
	}
	W25QXX_Read(flash_buffer, ADDR_FERTILIZATION, 1);	// 施肥
	val_fertiliozation = flash_buffer[0];
	if(val_fertiliozation == 0){
		MOTOR_Fertilized_Off();
	}else{
		MOTOR_Fertilized_On();
	}
	W25QXX_Read(flash_buffer, ADDR_WATERING, 1);	// 浇水
	val_water = flash_buffer[0];
	if(val_water == 0){
		MOTOR_Water_Off();
	}else{
		MOTOR_Water_On();
	}
	W25QXX_Read(flash_buffer, ADDR_LIGHT, 1);	// 灯光亮度
	val_light = flash_buffer[0];
	W25QXX_Read(flash_buffer, ADDR_LIGHT_COLOR, 1);	// 灯光颜色
	val_light_color = flash_buffer[0];
	W25QXX_Read(flash_buffer, ADDR_LIGHT_LEVEL, 1);	// 灯光亮度
	val_light_level = flash_buffer[0];
	refreshLightState();

	W25QXX_Read(flash_buffer, ADDR_AIR_TEMP_UP, 2);	// 气温上限
	val_air_temp_up = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_AIR_TEMP_DOWN, 2);	// 气温下限
	val_air_temp_low = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_AIR_HUMIDITY_UP, 2);	// 气湿上限
	val_air_humidity_up = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_AIR_HUMIDITY_DOWN, 2);	// 气湿下限
	val_air_humidity_low = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_DIRT_TEMP_UP, 2);	// 土温上限
	val_dirt_temp_up = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_DIRT_TEMP_DOWN, 2);	// 土温下限
	val_dirt_temp_low = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_DIRT_HUMIDITY_UP, 2);	// 土湿上限
	val_dirt_humidity_up = flash_buffer[0]*256 + flash_buffer[1];
	W25QXX_Read(flash_buffer, ADDR_DIRT_HUMIDITY_DOWN, 2);	// 土湿下限
	val_dirt_humidity_low = flash_buffer[0]*256 + flash_buffer[1];

	// printf("air  %d,%d    %d,%d",val_air_temp_low,val_air_temp_up,val_air_humidity_low,val_air_humidity_up);
	// printf("dirt %d,%d    %d,%d",val_dirt_temp_low,val_dirt_temp_up,val_dirt_humidity_low,val_dirt_humidity_up);
}

void refreshLightState(){
	u8 tempLightLevel = 0;
	if(val_light != 0){
		// 获取亮度等级
		if(val_light > 10){
			val_light_level = 10;
		}
		tempLightLevel = 83 - (8 * (10-val_light_level)) - 3 ;
		// 设置颜色
		switch(val_light_color){
			case 0:	//红色
				LED_Set_Red(tempLightLevel);
				break;
			case 1:	//绿色
				LED_Set_Green(tempLightLevel);
				break;
			case 2:	//蓝色
				LED_Set_Blue(tempLightLevel);
				break;
			case 3:	//黄色
				LED_Set_Yellow(tempLightLevel);
				break;
			case 4:	//紫色
				LED_Set_Purple(tempLightLevel);
				break;
			case 5:	//青色
				LED_Set_Cyan(tempLightLevel);
				break;
			case 6:	//白色
				LED_Set_White(tempLightLevel);
				break;
		}
	}else{
		LED_Set_Off();
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, 0);
		TIM_SetCompare3(TIM3, 0);
	}
	
}

char rec_buffer[100];
char rec_buffer_count = 0;
void USART1_IRQHandler(void)
{
	u8 rec;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)	//���յ�������
	{
		rec = USART_ReceiveData(USART1);
		UART_Send_Byte(rec);
		if(rec_buffer_count == 0 && rec == 0x00)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 1;
		}
		else if(rec_buffer_count == 1 && rec == 0xaa)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 2;
		}
		else if(rec_buffer_count == 2 && rec == 0xee)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 3;
		}
		else if(rec_buffer_count == 3 && rec <= 0x14)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 4;
		}
		else if(rec_buffer_count == 4)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 5;
		}
		else if(rec_buffer_count == 5)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 6;
		}
		else if(rec_buffer_count == 6 && rec == 0xef)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 7;
		}
		else if(rec_buffer_count == 7 && rec == 0xab)
		{
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 8;
		}
		else if(rec_buffer_count == 8 && rec == 0x01) // 校验通过！！！！
		{
			printf(" OK! ");
			rec_buffer[rec_buffer_count] = rec;
			rec_buffer_count = 0;
			switch(rec_buffer[3])
			{
				case 0x00:	 /**  设置自定义设备1的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						DEVICE_1_Off();
						val_device1 = 0;
					}else{
						flash_buffer[0] = 1;
						val_device1 = 1;
						DEVICE_1_On();
					}
					W25QXX_Write(flash_buffer, ADDR_DEVICE1, 1);
					break;
				case 0x01:	 /**  设置自定义设备2的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						DEVICE_2_Off();
						val_device2 = 0;
					}else{
						flash_buffer[0] = 1;
						DEVICE_2_On();
						val_device2 = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_DEVICE2, 1);
					break;
				case 0x02:	 /**  设置自定义设备3的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						DEVICE_3_Off();
						val_device3 = 0;
					}else{
						flash_buffer[0] = 1;
						DEVICE_3_On();
						val_device3 = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_DEVICE3, 1);
					break;
				case 0x03:	 /**  设置自定义设备4的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						DEVICE_4_Off();
						val_device4 = 0;
					}else{
						flash_buffer[0] = 1;
						DEVICE_4_On();
						val_device4 = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_DEVICE4, 1);					
					break;
				case 0x04:	 /**  设置风扇的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						FAN_Off();
						val_fan = 0;
					}else{
						flash_buffer[0] = 1;
						FAN_On();
						val_fan = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_FAN, 1);
					break;
				case 0x05:	 /**  设置加热的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						WARM_Off();
						val_warm = 0;
					}else{
						flash_buffer[0] = 1;
						WARM_On();
						val_warm = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_WARM, 1);
					break;
				case 0x06:	 /**  设置施肥的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						// MOTOR_Fertilized_Off();
						count_feterlized = 0;
					}else{
						flash_buffer[0] = 1;
						// MOTOR_Fertilized_On();
						count_feterlized = TIME_FERTILIZED;
					}
					// W25QXX_Write(flash_buffer, ADDR_FERTILIZATION, 1);
					break;
				case 0x07:	 /**  设置浇水的状态  **/
					if(rec_buffer[5] == 0){
						count_water = 0;
					}else{
						flash_buffer[0] = 1;
						count_water = TIME_WATRER;
					}
					break;
				case 0x08:	 /**  设置灯光的状态  **/
					if(rec_buffer[5] == 0){
						flash_buffer[0] = 0;
						val_light = 0;
					}else{
						flash_buffer[0] = 1;
						val_light = 1;
					}
					W25QXX_Write(flash_buffer, ADDR_LIGHT, 1);
					refreshLightState();
					break;
				case 0x09:	/**  设置灯光颜色的状态  **/
					flash_buffer[0] = rec_buffer[5];
					val_light_color = flash_buffer[0];
					W25QXX_Write(flash_buffer, ADDR_LIGHT_COLOR, 1);
					refreshLightState();
					break;
				case 0x0a:	/**  设置灯光亮度的状态  **/
					flash_buffer[0] = rec_buffer[5];
					val_light_level = flash_buffer[0];
					W25QXX_Write(flash_buffer, ADDR_LIGHT_LEVEL, 1);
					refreshLightState();
					break;
				case 0x0b:	/**  设置空气温度上限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_air_temp_up = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_air_temp_up);
					W25QXX_Write(flash_buffer, ADDR_AIR_TEMP_UP, 2);
					break;
				case 0x0c:	/**  设置空气湿度下限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_air_temp_low = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_air_temp_low);
					W25QXX_Write(flash_buffer, ADDR_AIR_TEMP_DOWN, 2);
					break;
				case 0x0d:	/**  设置空气湿度上限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_air_humidity_up = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_air_humidity_up);
					W25QXX_Write(flash_buffer, ADDR_AIR_HUMIDITY_UP, 2);
					break;
				case 0x0e:	/**  设置空气湿度下限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_air_humidity_low = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_air_humidity_low);
					W25QXX_Write(flash_buffer, ADDR_AIR_HUMIDITY_DOWN, 2);
					break;
				case 0x10:	 /**  设置土壤温度上限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_dirt_temp_up = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_dirt_temp_up);
					W25QXX_Write(flash_buffer, ADDR_DIRT_TEMP_UP ,2);
					break;
				case 0x11:	 /**  设置土壤温度下限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_dirt_temp_low = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_dirt_temp_low);
					W25QXX_Write(flash_buffer, ADDR_DIRT_TEMP_DOWN ,2);
					break;
				case 0x12:	 /**  设置土壤湿度上限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_dirt_humidity_up = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_dirt_humidity_up);
					W25QXX_Write(flash_buffer, ADDR_DIRT_HUMIDITY_UP ,2);
					break;
				case 0x13:	 /**  设置土壤湿度下限的状态  **/
					flash_buffer[0] = rec_buffer[4];
					flash_buffer[1] = rec_buffer[5];
					val_dirt_humidity_low = flash_buffer[0]*256 + flash_buffer[1];
					printf("%d, %d => %d",flash_buffer[0],flash_buffer[1],val_dirt_humidity_low);
					W25QXX_Write(flash_buffer, ADDR_DIRT_HUMIDITY_DOWN ,2);
					break;
				case 0x14:
					UART_Reset();
					break;
			}
		}
		else
		{
			rec_buffer_count = 0;
		}
	}
}


u8 is_twinkle_active = 0;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		// 逆转twinkle状态
		// 逆转twinkle状态
		if(is_twinkle_active == 0){
			is_twinkle_active = 1;
			if(val_buzzer != 0){ //蜂鸣器
				BUZZER_On();
				// LED_Set_White(10);
			}
		}else{
			is_twinkle_active = 0;
			BUZZER_Off();
			// LED_Set_Off();

		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}





