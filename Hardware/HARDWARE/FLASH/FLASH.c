#include "FLASH.h"
#include "delay.h"

u16 W25QXX_TYPE=W25Q16;	//ƒ¨»œ «W25Q16

void W25QXX_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);// πƒ‹GPIOB ±÷”
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;// ‰≥ˆ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//Õ∆ÕÏ ‰≥ˆ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//…œ¿≠
  GPIO_Init(GPIOB, &GPIO_InitStructure);//≥ı ºªØ

	W25QXX_CS=1;			//SPI FLASH≤ª—°÷–
	W25QXX_SPI_Init();		   			//≥ı ºªØSPI
	W25QXX_SPI_SetSpeed(SPI_BaudRatePrescaler_2);		//…Ë÷√Œ™42M ±÷”,∏ﬂÀŸƒ£ Ω 
	W25QXX_TYPE=W25QXX_ReadID();	//∂¡»°FLASH ID.
}

//∂¡»°FLASH ID
u16  W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	W25QXX_CS=0;				    
	W25QXX_SPI_ReadWriteByte(0x90);//∑¢ÀÕ∂¡»°ID√¸¡Ó	    
	W25QXX_SPI_ReadWriteByte(0x00); 	    
	W25QXX_SPI_ReadWriteByte(0x00); 	    
	W25QXX_SPI_ReadWriteByte(0x00); 	 			   
	Temp|=W25QXX_SPI_ReadWriteByte(0xFF)<<8;  
	Temp|=W25QXX_SPI_ReadWriteByte(0xFF);	 
	W25QXX_CS=1;				    
	return Temp;
}	



//∂¡»°W25QXXµƒ◊¥Ã¨ºƒ¥Ê∆˜
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:ƒ¨»œ0,◊¥Ã¨ºƒ¥Ê∆˜±£ª§Œª,≈‰∫œWP π”√
//TB,BP2,BP1,BP0:FLASH«¯”Ú–¥±£ª§…Ë÷√
//WEL:–¥ πƒ‹À¯∂®
//BUSY:√¶±Íº«Œª(1,√¶;0,ø’œ–)
//ƒ¨»œ:0x00
u8	 W25QXX_ReadSR(void)
{
	u8 byte=0;   
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
	W25QXX_SPI_ReadWriteByte(W25X_ReadStatusReg);    //∑¢ÀÕ∂¡»°◊¥Ã¨ºƒ¥Ê∆˜√¸¡Ó    
	byte=W25QXX_SPI_ReadWriteByte(0Xff);             //∂¡»°“ª∏ˆ◊÷Ω⁄  
	W25QXX_CS=1;                            //»°œ˚∆¨—°     
	return byte;   
}

//–¥◊¥Ã¨ºƒ¥Ê∆˜
void W25QXX_Write_SR(u8 sr)
{
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
	W25QXX_SPI_ReadWriteByte(W25X_WriteStatusReg);   //∑¢ÀÕ–¥»°◊¥Ã¨ºƒ¥Ê∆˜√¸¡Ó    
	W25QXX_SPI_ReadWriteByte(sr);               //–¥»Î“ª∏ˆ◊÷Ω⁄  
	W25QXX_CS=1;   
}

//–¥ πƒ‹ 
void W25QXX_Write_Enable(void)
{
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
	W25QXX_SPI_ReadWriteByte(W25X_WriteEnable);      //∑¢ÀÕ–¥ πƒ‹  
	W25QXX_CS=1;   
}

//–¥±£ª§
void W25QXX_Write_Disable(void)
{
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
  W25QXX_SPI_ReadWriteByte(W25X_WriteDisable);     //∑¢ÀÕ–¥Ω˚÷π÷∏¡Ó    
	W25QXX_CS=1;   
}

//∂¡»°–æ∆¨ID
//∑µªÿ÷µ»Áœ¬:				   
//0XEF13,±Ì æ–æ∆¨–Õ∫≈Œ™W25Q80  
//0XEF14,±Ì æ–æ∆¨–Õ∫≈Œ™W25Q16    
//0XEF15,±Ì æ–æ∆¨–Õ∫≈Œ™W25Q32  
//0XEF16,±Ì æ–æ∆¨–Õ∫≈Œ™W25Q64 
//0XEF17,±Ì æ–æ∆¨–Õ∫≈Œ™W25Q128 	  
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //µ•“≥ £”‡µƒ◊÷Ω⁄ ˝		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//≤ª¥Û”⁄256∏ˆ◊÷Ω⁄
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//–¥»ÎΩ· ¯¡À
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //ºı»•“—æ≠–¥»Î¡Àµƒ◊÷Ω⁄ ˝
			if(NumByteToWrite>256)pageremain=256; //“ª¥Œø…“‘–¥»Î256∏ˆ◊÷Ω⁄
			else pageremain=NumByteToWrite; 	  //≤ªπª256∏ˆ◊÷Ω⁄¡À
		}
	};	
}

//∂¡»°flash
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)
{
 	u16 i;   										    
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
	W25QXX_SPI_ReadWriteByte(W25X_ReadData);         //∑¢ÀÕ∂¡»°√¸¡Ó   
	W25QXX_SPI_ReadWriteByte((u8)((ReadAddr)>>16));  //∑¢ÀÕ24bitµÿ÷∑    
	W25QXX_SPI_ReadWriteByte((u8)((ReadAddr)>>8));   
	W25QXX_SPI_ReadWriteByte((u8)ReadAddr);   
	for(i=0;i<NumByteToRead;i++)
	{ 
		pBuffer[i]=W25QXX_SPI_ReadWriteByte(0XFF);   //—≠ª∑∂¡ ˝  
  }
	W25QXX_CS=1; 
}

void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    W25QXX_Write_Enable();                  //SET WEL 
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
    W25QXX_SPI_ReadWriteByte(W25X_PageProgram);      //∑¢ÀÕ–¥“≥√¸¡Ó   
    W25QXX_SPI_ReadWriteByte((u8)((WriteAddr)>>16)); //∑¢ÀÕ24bitµÿ÷∑    
    W25QXX_SPI_ReadWriteByte((u8)((WriteAddr)>>8));   
    W25QXX_SPI_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)W25QXX_SPI_ReadWriteByte(pBuffer[i]);//—≠ª∑–¥ ˝  
	W25QXX_CS=1;                            //»°œ˚∆¨—° 
	W25QXX_Wait_Busy();					   //µ»¥˝–¥»ÎΩ· ¯
} 

//–¥»Îflash
u8 W25QXX_BUFFER[4096];
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 * W25QXX_BUF;	  
   	W25QXX_BUF=W25QXX_BUFFER;	     
 	secpos=WriteAddr/4096;//…»«¯µÿ÷∑  
	secoff=WriteAddr%4096;//‘⁄…»«¯ƒ⁄µƒ∆´“∆
	secremain=4096-secoff;//…»«¯ £”‡ø’º‰¥Û–°   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//≤‚ ‘”√
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//≤ª¥Û”⁄4096∏ˆ◊÷Ω⁄
	while(1) 
	{	
		W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//∂¡≥ˆ’˚∏ˆ…»«¯µƒƒ⁄»›
		for(i=0;i<secremain;i++)//–£—È ˝æ›
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//–Ë“™≤¡≥˝  	  
		}
		if(i<secremain)//–Ë“™≤¡≥˝
		{
			W25QXX_Erase_Sector(secpos);//≤¡≥˝’‚∏ˆ…»«¯
			for(i=0;i<secremain;i++)	   //∏¥÷∆
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
			W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//–¥»Î’˚∏ˆ…»«¯  

		}else W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//–¥“—æ≠≤¡≥˝¡Àµƒ,÷±Ω”–¥»Î…»«¯ £”‡«¯º‰. 				   
		if(NumByteToWrite==secremain)break;//–¥»ÎΩ· ¯¡À
		else//–¥»ÎŒ¥Ω· ¯
		{
			secpos++;//…»«¯µÿ÷∑‘ˆ1
			secoff=0;//∆´“∆Œª÷√Œ™0 	 

		   	pBuffer+=secremain;  //÷∏’Î∆´“∆
			WriteAddr+=secremain;//–¥µÿ÷∑∆´“∆	   
		   	NumByteToWrite-=secremain;				//◊÷Ω⁄ ˝µ›ºı
			if(NumByteToWrite>4096)secremain=4096;	//œ¬“ª∏ˆ…»«¯ªπ «–¥≤ªÕÍ
			else secremain=NumByteToWrite;			//œ¬“ª∏ˆ…»«¯ø…“‘–¥ÕÍ¡À
		}	 
	};
}

//’˚∆¨≤¡≥˝
void W25QXX_Erase_Chip(void)
{
	W25QXX_Write_Enable();                  //SET WEL 
	W25QXX_Wait_Busy();   
	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
	W25QXX_SPI_ReadWriteByte(W25X_ChipErase);        //∑¢ÀÕ∆¨≤¡≥˝√¸¡Ó  
	W25QXX_CS=1;                            //»°œ˚∆¨—°     	      
	W25QXX_Wait_Busy();   				   //µ»¥˝–æ∆¨≤¡≥˝Ω· ¯
}

//…»«¯≤¡≥˝
void W25QXX_Erase_Sector(u32 Dst_Addr)
{
	//º‡ ”falsh≤¡≥˝«Èøˆ,≤‚ ‘”√   
// 	printf("fe:%x\r\n",Dst_Addr);	  
 	Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
    W25QXX_SPI_ReadWriteByte(W25X_SectorErase);      //∑¢ÀÕ…»«¯≤¡≥˝÷∏¡Ó 
    W25QXX_SPI_ReadWriteByte((u8)((Dst_Addr)>>16));  //∑¢ÀÕ24bitµÿ÷∑    
    W25QXX_SPI_ReadWriteByte((u8)((Dst_Addr)>>8));   
    W25QXX_SPI_ReadWriteByte((u8)Dst_Addr);  
	W25QXX_CS=1;                            //»°œ˚∆¨—°     	      
    W25QXX_Wait_Busy();   				   //µ»¥˝≤¡≥˝ÕÍ≥…
}

//µ»¥˝ø’œ–
void W25QXX_Wait_Busy(void)
{
		while((W25QXX_ReadSR()&0x01)==0x01);   // µ»¥˝BUSYŒª«Âø’
}

//Ω¯»ÎµÙµÁƒ£ Ω
void W25QXX_PowerDown(void)
{
	  	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
    W25QXX_SPI_ReadWriteByte(W25X_PowerDown);        //∑¢ÀÕµÙµÁ√¸¡Ó  
	W25QXX_CS=1;                            //»°œ˚∆¨—°     	      
    delay_us(3);  
}

//ªΩ–—
void W25QXX_WAKEUP(void)
{
	  	W25QXX_CS=0;                            // πƒ‹∆˜º˛   
    W25QXX_SPI_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	W25QXX_CS=1;                            //»°œ˚∆¨—°     	      
    delay_us(3);                               //µ»¥˝TRES1
}

//ƒ⁄¥Ê–æ∆¨µƒSPI≥ı ºªØ
void W25QXX_SPI_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);// πƒ‹GPIOA ±÷”
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);// πƒ‹SPI1 ±÷”
 
  //GPIOFB3,4,5≥ı ºªØ…Ë÷√
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5∏¥”√π¶ƒ‹ ‰≥ˆ	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//∏¥”√π¶ƒ‹
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//Õ∆ÕÏ ‰≥ˆ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//…œ¿≠
  GPIO_Init(GPIOB, &GPIO_InitStructure);//≥ı ºªØ
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PB3∏¥”√Œ™ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PB4∏¥”√Œ™ SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5∏¥”√Œ™ SPI1
 
	//’‚¿Ô÷ª’Î∂‘SPIø⁄≥ı ºªØ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//∏¥ŒªSPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//Õ£÷π∏¥ŒªSPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //…Ë÷√SPIµ•œÚªÚ’ﬂÀ´œÚµƒ ˝æ›ƒ£ Ω:SPI…Ë÷√Œ™À´œﬂÀ´œÚ»´À´π§
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//…Ë÷√SPIπ§◊˜ƒ£ Ω:…Ë÷√Œ™÷˜SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//…Ë÷√SPIµƒ ˝æ›¥Û–°:SPI∑¢ÀÕΩ” ’8Œª÷°Ω·ππ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//¥Æ––Õ¨≤Ω ±÷”µƒø’œ–◊¥Ã¨Œ™∏ﬂµÁ∆Ω
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//¥Æ––Õ¨≤Ω ±÷”µƒµ⁄∂˛∏ˆÃ¯±‰—ÿ£®…œ…˝ªÚœ¬Ωµ£© ˝æ›±ª≤…—˘
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS–≈∫≈”…”≤º˛£®NSSπ‹Ω≈£©ªπ «»Ìº˛£® π”√SSIŒª£©π‹¿Ì:ƒ⁄≤øNSS–≈∫≈”–SSIŒªøÿ÷∆
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//∂®“Â≤®Ãÿ¬ ‘§∑÷∆µµƒ÷µ:≤®Ãÿ¬ ‘§∑÷∆µ÷µŒ™256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//÷∏∂® ˝æ›¥´ ‰¥”MSBŒªªπ «LSBŒªø™ º: ˝æ›¥´ ‰¥”MSBŒªø™ º
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC÷µº∆À„µƒ∂‡œÓ Ω
	SPI_Init(SPI1, &SPI_InitStructure);  //∏˘æ›SPI_InitStruct÷–÷∏∂®µƒ≤Œ ˝≥ı ºªØÕ‚…ËSPIxºƒ¥Ê∆˜
 
	SPI_Cmd(SPI1, ENABLE); // πƒ‹SPIÕ‚…Ë

	W25QXX_SPI_ReadWriteByte(0xff);//∆Ù∂Ø¥´ ‰		
}

//ƒ⁄¥Ê–æ∆¨µƒSPI…Ë÷√ÀŸ∂»
void W25QXX_SPI_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//≈–∂œ”––ß–‘
	SPI1->CR1&=0XFFC7;//Œª3-5«Â¡„£¨”√¿¥…Ë÷√≤®Ãÿ¬ 
	SPI1->CR1|=SPI_BaudRatePrescaler;	//…Ë÷√SPI1ÀŸ∂» 
	SPI_Cmd(SPI1,ENABLE); // πƒ‹SPI1
}

//ƒ⁄¥Ê–æ∆¨µƒSPI∂¡–¥“ª∏ˆ◊÷Ω⁄
u8 	 W25QXX_SPI_ReadWriteByte(u8 TxData)
{
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//µ»¥˝∑¢ÀÕ«¯ø’  
	
	SPI_I2S_SendData(SPI1, TxData); //Õ®π˝Õ‚…ËSPIx∑¢ÀÕ“ª∏ˆbyte   ˝æ›
		
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //÷à’ΩﬁìÀïŒ™“ªŸ∂byte  
 
	return SPI_I2S_ReceiveData(SPI1); //∑µªÿÕ®π˝SPIx◊ÓΩ¸Ω” ’µƒ ˝æ›	
	
//	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//Á≠âÂæÖÂèëÈÄÅÂå∫Á©∫			  
//	SPI1->DR=TxData;	 	  										//ÂèëÈÄÅ‰∏Ä‰∏™Á©∫Êï∞ÊçÆ‰∫ßÁîüËæìÂÖ•Êï∞ÊçÆÁöÑÊó∂Èíü 
//	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //Á≠âÂæÖÊé•Êî∂ÂÆå‰∏Ä‰∏™byte  
//	return SPI1->DR;  		
}

static u8 flash_buffer[1];

u8   FLASH_Read(u32 address)
{
	W25QXX_Read(flash_buffer,address,FLASH_Size);
	return flash_buffer[0];
}
void FLASH_Write(u32 address,u8 value)
{
	flash_buffer[0] = value;
	W25QXX_Write(flash_buffer,address,FLASH_Size);
}
