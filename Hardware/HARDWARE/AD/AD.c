#include "AD.h"
#include "delay.h"

void AD_Light_Init(void)
{
	GPIO_InitTypeDef gpio_structure;
	ADC_CommonInitTypeDef adc_common_structure;
	ADC_InitTypeDef adc_structure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ʹ��ADC1ʱ��
	
	//�ȳ�ʼ��ADC1ͨ��5 IO��
	gpio_structure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_3;//PA5 ͨ��5,PA3 ͨ��3
	gpio_structure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	gpio_structure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����������
	GPIO_Init(GPIOA,&gpio_structure);//��ʼ��  
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);//��λ����	
	
	adc_common_structure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	adc_common_structure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	adc_common_structure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//DMAʧ��
	adc_common_structure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&adc_common_structure);//��ʼ��
	
	adc_structure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	adc_structure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	adc_structure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	adc_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	adc_structure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	adc_structure.ADC_NbrOfConversion = 2;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1,&adc_structure);//ADC��ʼ��
	
	ADC_Cmd(ADC1,ENABLE);//����ADת����	
}

//���ADCֵ
u16	 AD_Light_Get_Adc(u8 channel)
{
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��		`

	ADC_SoftwareStartConv(ADC1);	//ʹ��ָ����ADC1�����ת����������	
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
	
	return ADC_GetConversionValue(ADC1);//�������һ��ADC1�������ת�����
}

//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
}

u16	 AD_Dirt_Get_Adc(u8 channel)
{
		//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��		`

	ADC_SoftwareStartConv(ADC1);	//ʹ��ָ����ADC1�����ת����������	
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
	
	return ADC_GetConversionValue(ADC1);//�������һ��ADC1�������ת�����
}

u16	 AD_Dirt_Get_Adc_Result(u8 channel,u8 times)
{
	return 0;
}


