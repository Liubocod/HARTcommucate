/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd��BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd��BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */

#include "Lcd0064Drive.h"
#include "System.h"

/**
 //�������ƺͲ����ͷ���ֵ���͡�
void	DelayTime(unsigned char TimeValure)
* ������Χ:
TimeValure����ʱʱ��ֵ

* ����ֵ˵��:void 
* ���ܽ���:   
��ʱ������
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
unsigned char LcdStatusRead(void)  
* ������Χ:


* ����ֵ˵��:
��ȡ��Һ����ʾ״̬�������״ֵ̬���ء�
* ���ܽ���:   
��ȡLCD״̬��������ȡҺ������ʾ״̬��
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
void	LcdWriteCommand(unsigned char command)  
* ������Χ:
command��Ҫд��Һ�������

* ����ֵ˵��:
void
* ���ܽ���:   
��Һ��ģ�鷢�Ϳ������
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
void	LcdWriteData(unsigned char data)  
* ������Χ:
data��Ҫд��Һ��ģ�����ʾ���ݡ���

* ����ֵ˵��:
* ���ܽ���:   
��Һ��ģ�鷢����ʾ���ݡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
unsigned char LcdReadData(void) 
* ������Χ:
��

* ����ֵ˵��:
��Һ��ģ���ȡ����ʾ���ݡ�
* ���ܽ���:   
��Һ��ģ�鷢��ȡ��ʾ���ݡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
void	LcdDisplayInit(void)   
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Һ����ʾģ���ʼ��������
*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
void	LcdSetPage(unsigned char Page)  
* ������Χ:
��Page������Һ��ģ���ҳ��
Һ��ģ����ʾ�������϶��µĽ�64�зֳ�8�ݣ��ֳɵ�ÿһ�ݾ���һҳ��
PageȡֵΪ0-7�����ֽ�ֻ��0-2������Ч��
* ����ֵ˵��:
* ���ܽ���:   
Һ����ʾģ��ҳ���ú������趨��ʾ��������ꡣ
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void	LcdSetPage(unsigned char Page)
{
	Page = Page&0x07;
	Page = Page|0xB8;
	LcdWriteCommand(Page);
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void	LcdSetColumn(unsigned char Column) 
* ������Χ:
��Column������Һ��ģ����У�
Һ��ģ���Ϊ����оƬ������ʾ������ÿһ��оƬ����64�е������ʾ��
ColumnȡֵΪ0-63�����ֽ�ֻ��0-5������Ч��
* ����ֵ˵��:
* ���ܽ���:   
Һ����ʾģ�������ú������趨��ʾ��ĺ��������ꡣ
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void	LcdSetColumn(unsigned char Column)
{
    //unsigned char temp;
    Column = Column&0x7f;
    Column |= 0x40;         
    LcdWriteCommand(Column);
}
 /**
//�������ƺͲ����ͷ���ֵ���͡�
void LCD_CS_Switch(uchar Column,uchar Page)
* ������Χ:
��Page������Һ��ģ���ҳ��
Һ��ģ����ʾ�������϶��µĽ�64�зֳ�8�ݣ��ֳɵ�ÿһ�ݾ���һҳ��
PageȡֵΪ0-7�����ֽ�ֻ��0-2������Ч��
��Column������Һ��ģ����У�
Һ��ģ���Ϊ����оƬ������ʾ������ÿһ��оƬ����64�е������ʾ��
ColumnȡֵΪ0-63�����ֽ�ֻ��0-5������Ч��
* ����ֵ˵��:
* ���ܽ���:   
Һ����ʾģ�������оƬ�л���������columnֵ����63�����Խ���ˢ����һ��оƬ��
������ʾ��Χ�ڡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/

void LCD_CS_Switch(uchar Column,uchar Page)
{
  if((Column >= LCD_CS_BOUNDARY)&&(Column < LCD_MAX_BOUNDARY))
  {
    LCDCS1_1;
    LCDCS2_0;
    //LcdWriteCommand(0xc0);
    //�趨������
    LcdSetPage(Page);
    //�趨������
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
