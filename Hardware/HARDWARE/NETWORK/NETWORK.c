#include "NETWORK.h"
#include "UART.h"
#include "delay.h"

/**************************************************************************************************/
/*******************************                              *************************************/
/*******************************           基础配置           *************************************/
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
	GPIO_SetBits(GPIOB,GPIO_Pin_10);	//红色 PB10 复位
	GPIO_SetBits(GPIOB,GPIO_Pin_11);	//紫色 PB11 片选
	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  //?????????
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2); 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);  //??
	//SPI初始化
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
/*******************************         发包基础信息         *************************************/
/*******************************                              *************************************/
/**************************************************************************************************/
//W5500SPI发送 ByteArray
void NETWORK_SPI_Send_ByteArray(u16 address,u8 control,u8 dat[],u8 length)
{
	int i;
	
	CS_Low();									//片选拉低
	
	SPI_Write_Byte(address/256);	//发送地址帧
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//发送控制帧
	
	for(i=0;i<length;i++)
	{
		SPI_Write_Byte( *(dat+i) );
	}
	
	CS_High();									//片选拉高
}
//SPI 接受W5500的ByteArray
void NETWORK_SPI_Read_ByteArray(u16 address,u8 control,u8 dat[],u8 length)
{
	int i;
	
	CS_Low();									//片选拉低
	
	SPI_Write_Byte(address/256);	//发送地址帧
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//发送控制帧
	
	for(i=0;i<length;i++)
	{
		dat[i] = SPI_Read_Byte();
	}
	
	CS_High();									//片选拉高
}
//W5500SPI发送 Byte
void NETWORK_SPI_Send_Byte(u16 address,u8 control,u8 dat)
{
	CS_Low();									//片选拉低
	
	SPI_Write_Byte(address/256);	//发送地址帧
	SPI_Write_Byte(address);
	
	SPI_Write_Byte(control);			//发送控制帧
	
	SPI_Write_Byte(dat);
	
	CS_High();									//片选拉高
}
//SPI 接受W5500的Byte
u8 NETWORK_SPI_Read_Byte(u16 address,u8 control)
{
	u8 i[1];
	
	NETWORK_SPI_Read_ByteArray(address,control,i,1);
	
//	CS_Low();									//片选拉低
//	
//	SPI_Write_Byte(address/256);	//发送地址帧
//	SPI_Write_Byte(address);
//	
//	SPI_Write_Byte(control);			//发送控制帧
//	
//	
//	i = SPI_Read_Byte();
	
	CS_High();									//片选拉高
	
	return i[0];
}






/**************************************************************************************************/
/*******************************                              *************************************/
/*******************************        通用寄存器部分        *************************************/
/*******************************                              *************************************/
/**************************************************************************************************/
//硬件设置函数
//软件复位
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
u8 retryTimes[] = {0x07,0xd0};//2000(200ms)  单位是100us
u8 retryCounts = 4;
static void NETWORK_Init_Params(void)
{
	NETWORK_Software_Reset();//软件复位
	NETWORK_Set_MR();//设置模式
	NETWORK_Set_Gateway_Address(gatewayIP);
	NETWORK_Set_Sub_Mask(subMask);
	NETWORK_Set_Sorce_Mac_Address(macAddress);
	NETWORK_Set_Sorce_IP_Address(ipAddress);
//	NETWORK_Set_Socket0_Src_Port(srcPort);
	NETWORK_Set_Buffer_Size();
	
	NETWORK_Set_Sn_MR();
	NETWORK_Set_Sn_Port();
}




//设置Socket0 的源端口
void NETWORK_Set_Sn_Port()
{
	NETWORK_SPI_Send_ByteArray(0x0004,0x0c,srcPort,1);
}
//设置Socket0 的模式寄存器
void NETWORK_Set_Sn_MR()
{
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x20);//设置为UDP模式
}
//设置模式寄存器MR
void NETWORK_Set_MR()
{
	NETWORK_SPI_Send_Byte(0x0000,0x04,0x80);
}
//设置网关IP地址寄存器
void NETWORK_Set_Gateway_Address(u8 gatewayIP[])
{
	NETWORK_SPI_Send_ByteArray(0x0001,0x04,gatewayIP,4);
}	
//设置子网掩码
void NETWORK_Set_Sub_Mask(u8 subMask[])
{
	NETWORK_SPI_Send_ByteArray(0x0005,0x04,subMask,4);
}	
//设置源Mac地址
void NETWORK_Set_Sorce_Mac_Address(u8 macAddress[])
{
	NETWORK_SPI_Send_ByteArray(0x0009,0x04,macAddress,6);
}
//设置源IP地址
void NETWORK_Set_Sorce_IP_Address(u8 ipAddress[])
{
	NETWORK_SPI_Send_ByteArray(0x000f,0x04,ipAddress,4);
}	
//设置源端口
void NETWORK_Set_Socket0_Src_Port(u8 srcPort[])
{
	NETWORK_SPI_Send_ByteArray(0x0004,0x0c,srcPort,2);
}
//设置工作模式协议
void NETWORK_Set_Socket0_UDP()
{
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x02);	//设置为UDP模式，关闭多播，关闭广播阻塞,关闭多播阻塞，设置为UIDP协议
}
//设置缓冲区大小为2K
void NETWORK_Set_Buffer_Size()
{
	NETWORK_SPI_Send_Byte(0x001e,0x0c,0x02);//接受缓冲区大小为2kb
	NETWORK_SPI_Send_Byte(0x001f,0x0c,0x02);//发送缓冲区大小为2kb
}
//设置重试时间
void NETWORK_Set_Retry_Time(u8 retryTimes[])
{
	NETWORK_SPI_Send_ByteArray(0x0019,0x04,retryTimes,2);
}
//设置重试次数
void NETWORK_Set_Retry_Count(u8 retryCounts)
{
	NETWORK_SPI_Send_Byte(0x001b,0x04,retryCounts);
}
//初始化Socket
u8   NETWORK_Set_Socket_Open(void)
{
	u8 state;
	NETWORK_SPI_Send_Byte(0x0000,0x0c,0x02);//设置为UDP模式
	NETWORK_SPI_Send_Byte(0x0001,0x0c,0x01);//打开Socket
	delay_ms(5);//延时5MS
	state = NETWORK_SPI_Read_Byte(0x0003,0x08);
	printf("state : %d\n",state);
	if(state != 0x22)//是否打开成功,如果不是UDP
	{
		NETWORK_SPI_Send_Byte(0x0001,0x04,0x10);//关闭Socket
		return 0;	//不成功返回0
	}
	else
	{
		return 1;	//成功返回1
	}
	
}











//获取网关IP地址寄存器
void NETWORK_Get_Gateway_Address(u8 gatewayIP[])
{
	NETWORK_SPI_Read_ByteArray(0x0001,0x00,gatewayIP,4);
}	
//获取子网掩码
void NETWORK_Get_Sub_Mask(u8 subMask[])
{
	NETWORK_SPI_Read_ByteArray(0x0005,0x00,subMask,4);
}	
//获取源Mac地址
void NETWORK_Get_Sorce_Mac_Address(u8 macAddress[])
{
	NETWORK_SPI_Read_ByteArray(0x0009,0x00,macAddress,6);
}	
//获取源IP地址
void NETWORK_Get_Sorce_IP_Address(u8 ipAddress[])
{
	NETWORK_SPI_Read_ByteArray(0x000f,0x00,ipAddress,4);
}	
//获取源端口
void NETWORK_Get_Socket0_Src_Port(u8 srcPort[])
{
	NETWORK_SPI_Read_ByteArray(0x0004,0x08,srcPort,2);
}
//获取重试时间
void NETWORK_Get_Retry_Time(u8 retryTimes[])
{
	NETWORK_SPI_Read_ByteArray(0x0019,0x00,retryTimes,2);
}
//获取重试次数
u8   NETWORK_Get_Retry_Count()
{
	return NETWORK_SPI_Read_Byte(0x001b,0x00);
}



