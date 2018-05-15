#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f4xx.h"
#include "sys.h"

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17

extern u16 W25QXX_TYPE;					//����W25QXXоƬ�ͺ�		 

#define	W25QXX_CS 		PBout(0)  		//W25QXX��Ƭѡ�ź�

#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

#define FLASH_Size     						1

// FLASH ��־λ
#define FLASH_Air_Temp_Upper    			0x0000	// �¶�����
#define FALSH_Air_Temp_Upper_Action			0x0001	// �¶�����ִ�ж���
#define FLASH_Air_Temp_Lower				0x0002	// �¶�����
#define FLASH_Air_Temp_Lower_Action			0x0003

#define FLASH_Air_Humidity_Upper			0x0004
#define FLASH_Air_Humidity_Upper_Action		0x0005
#define FLASH_Air_Humidity_Lower			0x0006
#define FLASH_Air_Humidity_Lower_Action		0x0007

#define FLASH_Dirt_Temp_Upper				0x0010
#define FLASH_Dirt_Temp_Upper_Action		0x0011
#define FLASH_Dirt_Temp_Lower				0x0012
#define FLASH_Dirt_Temp_Lower_Action		0x0013

#define FLASH_Dirt_Humidity_Upper			0x0014
#define FLASH_Dirt_Humidity_Upper_Action	0x0015
#define FLASH_Dirt_Humidity_Lower			0x0016
#define FLASH_Dirt_Humidity_Lower_Action	0x0017

#define FLASH_Light_Color					0x0020
#define FLASH_Light_Brightness				0x0021

#define FLASH_Device_1						0x0024
#define FLASH_Device_2						0x0025
#define FLASH_Device_3						0x0026
#define FLASH_Device_4						0x0027

#define FLASH_Fan							0x0030

#define FLASH_Heat							0x0031

#define FLASH_Light							0x0032

#define FLASH_Air_Auto            			0x0040	// �¶��Զ�����
#define FLASH_Air_Humidity_Auto				0x0041
#define FLASH_Dirt_Humidity_Auto			0x0042
#define FLASH_Fertilized_Auto				0x0043
#define FLASH_Water_Auto					0x0050

void W25QXX_Init(void);
u16  W25QXX_ReadID(void);  	    		//��ȡFLASH ID
u8	 W25QXX_ReadSR(void);        		//��ȡ״̬�Ĵ��� 
void W25QXX_Write_SR(u8 sr);  			//д״̬�Ĵ���
void W25QXX_Write_Enable(void);  		//дʹ�� 
void W25QXX_Write_Disable(void);		//д����
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
void W25QXX_Erase_Sector(u32 Dst_Addr);	//��������
void W25QXX_Wait_Busy(void);           	//�ȴ�����
void W25QXX_PowerDown(void);        	//�������ģʽ
void W25QXX_WAKEUP(void);				//����

u8   FLASH_Read(u32 address);
void FLASH_Write(u32 address,u8 value);



void W25QXX_SPI_Init(void);
void W25QXX_SPI_SetSpeed(u8 SpeedSet);
u8 	 W25QXX_SPI_ReadWriteByte(u8 TxData);

#endif

