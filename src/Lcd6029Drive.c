#include "Lcd6029Drive.h"
void	DelayTeime(unsigned char TimeValure)
{
  	unsigned char TempC;
	while(TimeValure)
	{
		for(TempC = 0; TempC < 10; TempC++){;}
		TimeValure--;
	}
}
 
unsigned char LcdReadCommand(void)         //
{
	unsigned char ReadLcdData;
	LCDDATADIRREAD;
	LCDRS_0;
	LCDWR_1;
	asm("NOP");asm("NOP");asm("NOP");
	LCDRD_0;
	asm("NOP");asm("NOP");asm("NOP");
	ReadLcdData = READLCDDATA;
	LCDRD_1;
	LCDDATADIRWRITE;  
	return(ReadLcdData);
}

void	LcdWriteCommand(unsigned char command)   
{
	while(LcdReadCommand() & 0x80)
	{
		DelayTeime(1);
	}
	LCDRS_0;
	LCDRD_1;
	WRITELCDDATA = command;
	asm("NOP");asm("NOP");asm("NOP");
	LCDWR_0;
	asm("NOP");asm("NOP");asm("NOP");
	LCDWR_1;  
}

void	LcdWriteData(unsigned char data)      
{
	while(LcdReadCommand() & 0x80)
	{
		DelayTeime(1);
	}
	LCDRS_1;
	LCDRD_1;
	WRITELCDDATA = data;
	asm("NOP");asm("NOP");asm("NOP");
	LCDWR_0;
	asm("NOP");asm("NOP");asm("NOP");
	LCDWR_1;
}

unsigned char LcdReadData(void)         //
{
	unsigned char ReadLcdData;
	LCDDATADIRREAD;
//	WRITELCDDATA = 0xFF;
	LCDRS_1;
	LCDWR_1;
	LCDRD_0;
//	asm("NOP");asm("NOP");asm("NOP");
//	ReadLcdData = READLCDDATA;
	LCDRD_1;
//	asm("NOP");asm("NOP");asm("NOP");
	LCDRD_0;
	asm("NOP");asm("NOP");asm("NOP");
	ReadLcdData = READLCDDATA;
//	LCDDATADIRWRITE;  
	return(ReadLcdData);
}

void	LcdDisplayInit(void)        //
{
	LCDCS_0;
	LCDRES_0;
	DelayTeime(100);
	LCDRES_1;
	#ifdef LCDREVERES
		LcdWriteCommand(0xA0);         //adc=0 normal
		LcdWriteCommand(0xC8);         //
	#else
		LcdWriteCommand(0xA1);         //adc=1 reveres
		LcdWriteCommand(0xC0);         //
	#endif

	LcdWriteCommand(0xA2);         //
	LcdWriteCommand(0x2F);         //
	LcdWriteCommand(0x81);         //
	LcdWriteCommand(0x30);//
	LcdWriteCommand(0x40);         //display start line 0
	LcdWriteCommand(0xAF);         //display on
}

void	LcdSetPage(unsigned char Page)
{
	Page = Page&0x0F;
	Page = Page|0xB0;
	LcdWriteCommand(Page);
}

void	LcdSetColumn(unsigned char Column)
{
	unsigned char temp;
	#ifdef LCDREVERES
		Column = Column-4;			//ดจาว
	#endif
	temp = Column;
	Column = Column&0x0F;
	Column = Column|0x00;
	LcdWriteCommand(Column);
	temp = temp>>4;
	Column = temp&0x0F;
	Column = Column|0x10;
	LcdWriteCommand(Column);
}
