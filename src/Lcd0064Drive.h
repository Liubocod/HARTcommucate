/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */

#ifndef LCD0064DRIVE_H
#define LCD0064DRIVE_H

#define LCD_CS_BOUNDARY 64
#define LCD_MAX_BOUNDARY 128
void	LcdSetPage(unsigned char Page);
void	LcdSetColumn(unsigned char Column);
void	LcdWriteData(unsigned char data);
void	LcdDisplayInit(void);
void	DelayTime(unsigned char TimeValure);
unsigned char LcdReadCommand(void);
void	LcdWriteCommand(unsigned char command);

unsigned char LcdReadData(void);
void LCD_CS_Switch(uchar Column,uchar Page);

#endif