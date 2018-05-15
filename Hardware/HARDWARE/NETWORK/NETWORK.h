#ifndef __NETWORK_H
#define __NETWORK_H

#include "stm32f4xx.h"

#define u8 			unsigned char
#define u16 		unsigned int
	
#define SOCKET_STATE_SOCK_CLOSED = 0x00;
#define SOCKET_STATE_SOCK_INIT = 0x13;
#define SOCKET_STATE_SOCK_LISTEN = 0x14;
#define SOCKET_STATE_SOCK_ESTABLISHED  = 0x17;
#define SOCKET_STATE_SOCK_CLOSE_WAIT = 0x1c;
#define SOCKET_STATE_SOCK_UDP = 0x22;
#define SOCKET_STATE_SOCK_MACRAW = 0X42;
#define SOCKET_STATE_SOCK_SYNSENT = 0x15;
#define SOCKET_STATE_SOCK_SYNRECV = 0x16;
#define SOCKET_STATE_SOCK_FIN_WAIT = 0x18;
#define SOCKET_STATE_SOCK_CLOSING = 0x1A;
#define SOCKET_STATE_SOCK_TIME_WAIT = 0x1B;
#define SOCKET_STATE_SOCK_LAST_ACK = 0x1B;


void NETWORK_Init(void);	//��ʼ��
static void CS_High(void);	//Ƭѡ����
static void CS_Low(void);	//Ƭѡ���� 
static u8   SPI_Read_Byte(void);	//SPI��ȡһ��Byte
static void SPI_Write_Byte(u8 dat);	//SPIд��һ��Byte

/** ����������Ϣ **/
//Ӳ������
void NETWORK_Software_Reset(void);

//��ʼ��
static void NETWORK_Init_Params(void);

//����
void NETWORK_Set_Sn_CR_Open(void);
void NETWORK_Set_Sn_Port(void);
void NETWORK_Set_Sn_MR(void);
void NETWORK_Set_MR(void);
void NETWORK_Set_Gateway_Address(u8 gatewayIP[]);
void NETWORK_Set_Sub_Mask(u8 subMask[]);
void NETWORK_Set_Sorce_Mac_Address(u8 macAddress[]);
void NETWORK_Set_Sorce_IP_Address(u8 ipAddress[]);
void NETWORK_Set_Socket0_Src_Port(u8 srcPort[]);
void NETWORK_Set_Buffer_Size(void);
void NETWORK_Set_Retry_Time(u8 retryTimes[]);
void NETWORK_Set_Retry_Count(u8 retryCounts);
u8   NETWORK_Set_Socket_Open(void);

//��ȡ
void NETWORK_Get_Gateway_Address(u8 gatewayIP[]);
void NETWORK_Get_Sub_Mask(u8 subMask[]);
void NETWORK_Get_Sorce_Mac_Address(u8 macAddress[]);
void NETWORK_Get_Sorce_IP_Address(u8 ipAddress[]);
void NETWORK_Get_Socket0_Src_Port(u8 srcPort[]);
void NETWORK_Get_Retry_Time(u8 retryTimes[]);
u8   NETWORK_Get_Retry_Count(void);

#endif


