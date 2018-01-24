#include "AD.h"
#include "delay.h"

void AD_Light_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	ADC_CommonInitTypeDef adc_common_structure;
	ADC_InitTypeDef adc_structure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC1时钟
	
	//先初始化ADC1通道5 IO口
	gpio_structure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_3;//PA5 通道5,PA3 通道3
	gpio_structure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	gpio_structure.GPIO_PuPd = GPIO_PuPd_NOPULL;//不带上下拉
	GPIO_Init(GPIOA,&gpio_structure);//初始化  
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);//复位结束	
	
	adc_common_structure.ADC_Mode = ADC_Mode_Independent;//独立模式
	adc_common_structure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	adc_common_structure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//DMA失能
	adc_common_structure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&adc_common_structure);//初始化
	
	adc_structure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	adc_structure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	adc_structure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	adc_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	adc_structure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	adc_structure.ADC_NbrOfConversion = 2;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1,&adc_structure);//ADC初始化
	
	ADC_Cmd(ADC1,ENABLE);//开启AD转换器	
}

//获得ADC值
u16	 AD_Light_Get_Adc(u8 channel)
{
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度		`

	ADC_SoftwareStartConv(ADC1);	//使能指定的ADC1的软件转换启动功能	
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
	
	return ADC_GetConversionValue(ADC1);//返回最近一次ADC1规则组的转换结果
}

//获取通道ch的转换值，取times次,然后平均 
u16	 AD_Light_Get_Adc_Result(u8 channel,u8 times)
{
	u32 temp_value = 0;
	u8 i = 0;
	for(i = 0;i < times;i++)
	{
		temp_value += AD_Light_Get_Adc(channel);
		delay_ms(5);
	}
	return temp_value / times;
}

void AD_Dirt_Humidity_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
}

u16	 AD_Dirt_Get_Adc(u8 channel)
{
		//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度		`

	ADC_SoftwareStartConv(ADC1);	//使能指定的ADC1的软件转换启动功能	
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
	
	return ADC_GetConversionValue(ADC1);//返回最近一次ADC1规则组的转换结果
}

u16	 AD_Dirt_Get_Adc_Result(u8 channel,u8 times)
{
	return 0;
}


