#include "NETWORK.h"
#include "UART.h"
#include "delay.h"

/**************************************************************************************************/
/*******************************                              *************************************/
/*******************************           ��������           *************************************/
/*******************************                              *************************************/
/**************************************************************************************************/

void NETWORK_Init(void)
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
	
	NETWORK_Init_Params();
}

void CS_High(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
}


void CS_Low(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
}


u8   SPI_Read_Byte(void)
{
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);			  
	SPI2->DR=0xFF;	 	  										
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); 
	return SPI2->DR; 
}


void SPI_Write_Byte(u8 dat)
{
	while((SPI2->SR&SPI_I2S_FLAG_TXE)==0);			  
	SPI2->DR=dat;	 	  									
	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==0); 
	SPI2->DR;	
}




/**************************************************************************************************/
/*******************************                              *************************************/
/*******************************         ����������Ϣ         *************************************/
/*******************************                              *************************************/
/**************************************************************************************************/
//W5500SPI���� ByteArray
void NETWORK_SPI_Send_ByteArray(u16 address,u8 control,u8 dat[],u8 length)
{
	int i;
	
	CS_Low();									//Ƭѡ����
	
	SPI_Write_Byte(address/256);	//���͵�ַ֡
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//���Ϳ���֡
	
	for(i=0;i<length;i++)
	{
		SPI_Write_Byte( *(dat+i) );
	}
	
	CS_High();									//Ƭѡ����
}
//SPI ����W5500��ByteArray
void NETWORK_SPI_Read_ByteArray(u16 address,u8 control,u8 dat[],u8 length)
{
	int i;
	
	CS_Low();									//Ƭѡ����
	
	SPI_Write_Byte(address/256);	//���͵�ַ֡
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//���Ϳ���֡
	
	for(i=0;i<length;i++)
	{
		dat[i] = SPI_Read_Byte();
	}
	
	CS_High();									//Ƭѡ����
}
//W5500SPI���� Byte
void NETWORK_SPI_Send_Byte(u16 address,u8 control,u8 dat)
{
	CS_Low();									//Ƭѡ����
	
	SPI_Write_Byte(address/256);	//���͵�ַ֡
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//���Ϳ���֡
	
	SPI_Write_Byte(dat);
	
	CS_High();									//Ƭѡ����
}
//SPI ����W5500��Byte
u8 NETWORK_SPI_Read_Byte(u16 address,u8 control)
{
	u8 i[1];
	
	NETWORK_SPI_Read_ByteArray(address,control,i,1);
	
//	CS_Low();									//Ƭѡ����
//	
//	SPI_Write_Byte(address/256);	//���͵�ַ֡
//	SPI_Write_Byte(address);
//	
//	SPI_Write_Byte(control);			//���Ϳ���֡
//	
//	
//	i = SPI_Read_Byte();
	
	CS_High();									//Ƭѡ����
	
	return i[0];
}






/**************************************************************************************************/
/*******************************                              *************************************/
/*******************************        ͨ�üĴ�������        *************************************/
/*******************************                              *************************************/
/**************************************************************************************************/
//Ӳ�����ú���
//�����λ
void NETWORK_Software_Reset()
{
	NETWORK_SPI_Send_Byte(0x0000,0x04,0x80);
	delay_ms(10);
}



u8 gatewayIP[] = {192,168,31,1};
u8 subMask[] = {255,255,255,0};
u8 macAddress[] = {0x00, 0x08, 0xdc,0x00, 0xab, 0xcd};
u8 ipAddress[] = {192,168,31,199};
u8 srcPort[] = {0x1F,0x40};	//8000
u8 retryTimes[] = {0x07,0xd0};//2000(200ms)  ��λ��100us
u8 retryCounts = 4;
static void NETWORK_Init_Params(void)
{
	NETWORK_Software_Reset();//�����λ
	NETWORK_Set_MR();//����ģʽ
	NETWORK_Set_Gateway_Address(gatewayIP);
	NETWORK_Set_Sub_Mask(subMask);
	NETWORK_Set_Sorce_Mac_Address(macAddress);
	NETWORK_Set_Sorce_IP_Address(ipAddress);
//	NETWORK_Set_Socket0_Src_Port(srcPort);
	NETWORK_Set_Buffer_Size();
	
	NETWORK_Set_Sn_MR();
	NETWORK_Set_Sn_Port();
}




//����Socket0 ��Դ�˿�
void NETWORK_Set_Sn_Port()
{
	NETWORK_SPI_Send_ByteArray(0x0004,0x0c,srcPort,1);
}
//����Socket0 ��ģʽ�Ĵ���
void NETWORK_Set_Sn_MR()
{
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x20);//����ΪUDPģʽ
}
//����ģʽ�Ĵ���MR
void NETWORK_Set_MR()
{
	NETWORK_SPI_Send_Byte(0x0000,0x04,0x80);
}
//��������IP��ַ�Ĵ���
void NETWORK_Set_Gateway_Address(u8 gatewayIP[])
{
	NETWORK_SPI_Send_ByteArray(0x0001,0x04,gatewayIP,4);
}	
//������������
void NETWORK_Set_Sub_Mask(u8 subMask[])
{
	NETWORK_SPI_Send_ByteArray(0x0005,0x04,subMask,4);
}	
//����ԴMac��ַ
void NETWORK_Set_Sorce_Mac_Address(u8 macAddress[])
{
	NETWORK_SPI_Send_ByteArray(0x0009,0x04,macAddress,6);
}
//����ԴIP��ַ
void NETWORK_Set_Sorce_IP_Address(u8 ipAddress[])
{
	NETWORK_SPI_Send_ByteArray(0x000f,0x04,ipAddress,4);
}	
//����Դ�˿�
void NETWORK_Set_Socket0_Src_Port(u8 srcPort[])
{
	NETWORK_SPI_Send_ByteArray(0x0004,0x0c,srcPort,2);
}
//���ù���ģʽЭ��
void NETWORK_Set_Socket0_UDP()
{
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x02);	//����ΪUDPģʽ���رնಥ���رչ㲥����,�رնಥ����������ΪUIDPЭ��
}
//���û�������СΪ2K
void NETWORK_Set_Buffer_Size()
{
	NETWORK_SPI_Send_Byte(0x001e,0x0c,0x02);//���ܻ�������СΪ2kb
	NETWORK_SPI_Send_Byte(0x001f,0x0c,0x02);//���ͻ�������СΪ2kb
}
//��������ʱ��
void NETWORK_Set_Retry_Time(u8 retryTimes[])
{
	NETWORK_SPI_Send_ByteArray(0x0019,0x04,retryTimes,2);
}
//�������Դ���
void NETWORK_Set_Retry_Count(u8 retryCounts)
{
	NETWORK_SPI_Send_Byte(0x001b,0x04,retryCounts);
}
//��ʼ��Socket
u8   NETWORK_Set_Socket_Open(void)
{
	u8 state;
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x02);//����ΪUDPģʽ
	NETWORK_SPI_Send_Byte(0x0001,0x0c,0x01);//��Socket
	delay_ms(5);//��ʱ5MS
	state = NETWORK_SPI_Read_Byte(0x0003,0x08);
	printf("state : %d\n",state);
	if(state != 0x22)//�Ƿ�򿪳ɹ�,�������UDP
	{
		NETWORK_SPI_Send_Byte(0x0001,0x04,0x10);//�ر�Socket
		return 0;	//���ɹ�����0
	}
	else
	{
		return 1;	//�ɹ�����1
	}
	
}











//��ȡ����IP��ַ�Ĵ���
void NETWORK_Get_Gateway_Address(u8 gatewayIP[])
{
	NETWORK_SPI_Read_ByteArray(0x0001,0x00,gatewayIP,4);
}	
//��ȡ��������
void NETWORK_Get_Sub_Mask(u8 subMask[])
{
	NETWORK_SPI_Read_ByteArray(0x0005,0x00,subMask,4);
}	
//��ȡԴMac��ַ
void NETWORK_Get_Sorce_Mac_Address(u8 macAddress[])
{
	NETWORK_SPI_Read_ByteArray(0x0009,0x00,macAddress,6);
}	
//��ȡԴIP��ַ
void NETWORK_Get_Sorce_IP_Address(u8 ipAddress[])
{
	NETWORK_SPI_Read_ByteArray(0x000f,0x00,ipAddress,4);
}	
//��ȡԴ�˿�
void NETWORK_Get_Socket0_Src_Port(u8 srcPort[])
{
	NETWORK_SPI_Read_ByteArray(0x0004,0x08,srcPort,2);
}
//��ȡ����ʱ��
void NETWORK_Get_Retry_Time(u8 retryTimes[])
{
	NETWORK_SPI_Read_ByteArray(0x0019,0x00,retryTimes,2);
}
//��ȡ���Դ���
u8   NETWORK_Get_Retry_Count()
{
	return NETWORK_SPI_Read_Byte(0x001b,0x00);
}



