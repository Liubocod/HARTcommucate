/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd，BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd，BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */

#include "Lcd0064Drive.h"
#include "System.h"

/**
 //函数名称和参量和返回值类型。
void	DelayTime(unsigned char TimeValure)
* 变量范围:
TimeValure：延时时间值

* 返回值说明:void 
* 功能介绍:   
延时函数。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	DelayTime(unsigned char TimeValure)
{
  	unsigned char TempC;
	while(TimeValure)
	{
		for(TempC = 0; TempC < 10; TempC++){;}
		TimeValure--;
	}
}
/**
 //函数名称和参量和返回值类型。
unsigned char LcdStatusRead(void)  
* 变量范围:


* 返回值说明:
读取的液晶显示状态，将这个状态值返回。
* 功能介绍:   
读取LCD状态函数，读取液晶的显示状态。
*
* 关键备注：
* - 

  
* 未来提高:



*/
unsigned char LcdStatusRead(void)         //
{
  unsigned char ReadStatus = 0;
  LCDDATADIRREAD;
  LCD_E_0;
  asm("NOP");  
  LCD_WR_1;
  LCD_DI_0;
  asm("NOP");
  LCD_E_1;
  ReadStatus = READLCDDATA;
  asm("NOP");
  return ReadStatus;
}
/**
 //函数名称和参量和返回值类型。
void	LcdWriteCommand(unsigned char command)  
* 变量范围:
command：要写入液晶的命令。

* 返回值说明:
void
* 功能介绍:   
向液晶模块发送控制命令。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	LcdWriteCommand(unsigned char command)   
{
  while(LcdStatusRead() & 0x80);
  LCDDATADIRWRITE;
  
  LCD_E_0;
  asm("NOP");
  LCD_WR_0;
  LCD_DI_0;
  asm("NOP");
  LCD_E_1;
  asm("NOP");
  WRITELCDDATA = command;
  asm("NOP");
  LCD_E_0;
}
/**
 //函数名称和参量和返回值类型。
void	LcdWriteData(unsigned char data)  
* 变量范围:
data：要写入液晶模块的显示数据。。

* 返回值说明:
* 功能介绍:   
向液晶模块发送显示数据。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	LcdWriteData(unsigned char data)      
{
  while(LcdStatusRead() & 0x80);
  LCDDATADIRWRITE;
  
  LCD_E_0;
  asm("NOP");
  LCD_WR_0;
  LCD_DI_1;
  asm("NOP");
  LCD_E_1;
  asm("NOP");
  WRITELCDDATA = data;
  asm("NOP");
  LCD_E_0;	
}
/**
 //函数名称和参量和返回值类型。
unsigned char LcdReadData(void) 
* 变量范围:
。

* 返回值说明:
在液晶模块读取的显示数据。
* 功能介绍:   
从液晶模块发读取显示数据。
*
* 关键备注：
* - 

  
* 未来提高:



*/
unsigned char LcdReadData(void)         //
{
  unsigned char ReadData = 0;
  LCDDATADIRREAD;
  LCD_E_0;
  asm("NOP");  
  LCD_WR_1;
  LCD_DI_1;
  asm("NOP");
  LCD_E_1;
  ReadData = READLCDDATA;
  asm("NOP");
  return ReadData;
}
/**
 //函数名称和参量和返回值类型。
void	LcdDisplayInit(void)   
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
液晶显示模块初始化函数。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	LcdDisplayInit(void)        //
{
  LCD_RES_1;
  LCD_E_1;
  BACKLIGHT_OFF;
  DelayTime(100);
  LCD_RES_0;
  DelayTime(100);
  LCD_RES_1;
  BACKLIGHT_ON;
  LCDCS1_0;
  LCDCS2_1;
  LcdWriteCommand(0xc0);
  LcdWriteCommand(0xb8);
  LcdWriteCommand(0x40);
  LcdWriteCommand(0x3f);
}
/**
 //函数名称和参量和返回值类型。
void	LcdSetPage(unsigned char Page)  
* 变量范围:
。Page：设置液晶模块的页，
液晶模块显示部分自上而下的将64行分成8份，分成的每一份就是一页。
Page取值为0-7，该字节只有0-2比特有效。
* 返回值说明:
* 功能介绍:   
液晶显示模块页设置函数，设定显示点的纵坐标。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	LcdSetPage(unsigned char Page)
{
	Page = Page&0x07;
	Page = Page|0xB8;
	LcdWriteCommand(Page);
}
/**
 //函数名称和参量和返回值类型。
void	LcdSetColumn(unsigned char Column) 
* 变量范围:
。Column：设置液晶模块的列，
液晶模块分为两个芯片负责显示驱动，每一个芯片驱动64列点阵的显示。
Column取值为0-63，该字节只有0-5比特有效。
* 返回值说明:
* 功能介绍:   
液晶显示模块列设置函数，设定显示点的横坐标坐标。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	LcdSetColumn(unsigned char Column)
{
    //unsigned char temp;
    Column = Column&0x7f;
    Column |= 0x40;         
    LcdWriteCommand(Column);
}
 /**
//函数名称和参量和返回值类型。
void LCD_CS_Switch(uchar Column,uchar Page)
* 变量范围:
。Page：设置液晶模块的页，
液晶模块显示部分自上而下的将64行分成8份，分成的每一份就是一页。
Page取值为0-7，该字节只有0-2比特有效。
。Column：设置液晶模块的列，
液晶模块分为两个芯片负责显示驱动，每一个芯片驱动64列点阵的显示。
Column取值为0-63，该字节只有0-5比特有效。
* 返回值说明:
* 功能介绍:   
液晶显示模块的驱动芯片切换函数，当column值大于63，可以将点刷在另一个芯片的
驱动显示范围内。
*
* 关键备注：
* - 

  
* 未来提高:



*/

void LCD_CS_Switch(uchar Column,uchar Page)
{
  if((Column >= LCD_CS_BOUNDARY)&&(Column < LCD_MAX_BOUNDARY))
  {
    LCDCS1_1;
    LCDCS2_0;
    //LcdWriteCommand(0xc0);
    //设定纵坐标
    LcdSetPage(Page);
    //设定横坐标
    LcdWriteCommand(0x3f);
    LcdSetColumn(Column - LCD_CS_BOUNDARY);
  }
  else if(Column < LCD_CS_BOUNDARY)
  {
    LCDCS1_0;
    LCDCS2_1;
    LcdSetPage(Page);
    LcdSetColumn(Column);
  }
}
