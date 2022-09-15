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

#ifndef HARDWARE_SET_H
#define HARDWARE_SET_H
#include "io430f5418a.h"
#include "DataType.h"

#define	LCDREVERES			
#define	uchar			unsigned char 
#define	uint			unsigned int
#define	uint32			unsigned long int
//Lcd6029 Pin define
#define	READLCDDATA		P2IN
#define	WRITELCDDATA	        P2OUT
#define	LCD_DI_0		P1OUT_bit.P1OUT4 = 0
#define	LCD_DI_1		P1OUT_bit.P1OUT4 = 1
#define	LCD_WR_0		P1OUT_bit.P1OUT5 = 0
#define	LCD_WR_1		P1OUT_bit.P1OUT5 = 1
#define	LCD_E_0		        P1OUT_bit.P1OUT6 = 0
#define	LCD_E_1		        P1OUT_bit.P1OUT6 = 1
#define	LCD_RES_0		P1OUT_bit.P1OUT0 = 0
#define	LCD_RES_1		P1OUT_bit.P1OUT0 = 1
#define	LCDCS1_0		P1OUT_bit.P1OUT2 = 0
#define	LCDCS1_1		P1OUT_bit.P1OUT2 = 1
#define	LCDCS2_0		P1OUT_bit.P1OUT3 = 0
#define	LCDCS2_1		P1OUT_bit.P1OUT3 = 1
#define	LCDVCC_OFF		P1OUT_bit.P1OUT1 = 0
#define	LCDVCC_ON		P1OUT_bit.P1OUT1 = 1
#define	BACKLIGHT_OFF	        P1OUT_bit.P1OUT7 = 0
#define	BACKLIGHT_ON	        P1OUT_bit.P1OUT7 = 1
#define	LCDDATADIRWRITE	        P2DIR = 0xFF
#define	LCDDATADIRREAD	        P2DIR = 0
#define	LCD_CL_OUT		P1DIR = P1DIR|0xFC

#define	EnableTxHart	        P5OUT_bit.P5OUT5 = 0
#define	CLR_HartRest	        P7OUT_bit.P7OUT3 = 0
#define	SET_HartRest	        P7OUT_bit.P7OUT3 = 1

#define	EnaleSWReset	        UCB0CTL1_bit.UCSWRST = 1
#define	EnaleSWReset1	        UCB1CTL1_bit.UCSWRST = 1

#define	EnalePower		P5OUT_bit.P5OUT4 = 1
#define	DisablePower	        P5OUT_bit.P5OUT4 = 0

//#define ADSDI_0		        P6OUT_bit.P6OUT4 = 0
//#define ADSDI_1		        P6OUT_bit.P6OUT4 = 1
//#define ADCS_0		        P6OUT_bit.P6OUT5 = 0
//#define ADCS_1		        P6OUT_bit.P6OUT5 = 1
//#define ADSCK_0		        P6OUT_bit.P6OUT6 = 0
//#define ADSCK_1		        P6OUT_bit.P6OUT6 = 1
//#define ADSDO		        P6OUT_bit.P6OUT6 
#define FEED_DOG                P6OUT_bit.P6OUT0


#define RECEIVE_SEND_EN         P5OUT_bit.P5OUT5
#define HART_BUS_START          P7OUT_bit.P7OUT3
#define NULL                    (void*)0x00

#define LEAD_CODE_NUM 5
#define MAX_MIN_NUM 2
#define SAMPLE_NUM 5


 
// bit3~bit1为A2/A1/A0为设备地址位，A2~A0电平高低由相应的硬件输入脚决定
														// bit0 为R/W选择位，1代表读，0代表写
															// Bits A0, A1 and A2 are “don’t cares” for the 24AA02E48/24AA02E64.
// 以下为加密芯片IIC硬件接口定义，调用时可根据具体I/O接口进行更改
#define  IICROM_SDA_DIR_IN           		 P6DIR_bit.P6DIR4 = 0       // set direction of I2C_SDA sinal in
#define  IICROM_SDAIN			         P6IN_bit.P6IN4		    // "输入"

#define  IICROM_SDA_DIR_OUT                      P6DIR_bit.P6DIR4 = 1		// set direction of I2C_SDA signal out
#define  IICROM_SDA_H			         P6OUT_bit.P6OUT4 = 1		// set I2C_SDA signal 1
#define  IICROM_SDA_L			         P6OUT_bit.P6OUT4 = 0  		// reset I2C_SDA signal 0

#define  IICROM_SCL_DIR_OUT          		 P6DIR_bit.P6DIR5 = 1 		// set direction of I2C_SCL signal out
#define  IICROM_SCL_H			         P6OUT_bit.P6OUT5 = 1		// set I2C_SCL signal 1
#define  IICROM_SCL_L			         P6OUT_bit.P6OUT5 = 0		// reset I2C_SCL signal 0


#define  IICROM_DEVICE_ADDRESS        		 0xA0           // I2C设备地址(加密芯片24AA02E48T的设备地址)，bit7~bit4固定为1010b
                                                      // 24AA02E48T引脚只有VCC,VSS,SCL,SDA

/*
// 以下为加密芯片IIC硬件接口定义，调用时可根据具体I/O接口进行更改
#define  IICROM_SDA_DIR_IN           		 P8DIR_bit.P8DIR2 = 0       // set direction of I2C_SDA sinal in
#define  IICROM_SDAIN			         P8IN_bit.P8IN2		    // "输入"

#define  IICROM_SDA_DIR_OUT                      P8DIR_bit.P8DIR2 = 1		// set direction of I2C_SDA signal out
#define  IICROM_SDA_H			         P8OUT_bit.P8OUT2 = 1		// set I2C_SDA signal 1
#define  IICROM_SDA_L			         P8OUT_bit.P8OUT2 = 0  		// reset I2C_SDA signal 0

#define  IICROM_SCL_DIR_OUT          		 P6DIR_bit.P6DIR5 = 1 		// set direction of I2C_SCL signal out
#define  IICROM_SCL_H			         P6OUT_bit.P6OUT5 = 1		// set I2C_SCL signal 1
#define  IICROM_SCL_L			         P6OUT_bit.P6OUT5 = 0		// reset I2C_SCL signal 0


#define  IICROM_DEVICE_ADDRESS        		 0xA0           // I2C设备地址(加密芯片24AA02E48T的设备地址)，bit7~bit4固定为1010b

*/

// 以下为AT24C64硬件接口定义，调用时可根据具体I/O接口进行更改
#define EEPROM_SDA_DIR_IN              P6DIR_bit.P6DIR6 = 0            // set direction of I2C_SDA signal in
#define EEPROM_SDAIN                   P6IN_bit.P6IN6                  // "输入"

#define EEPROM_SDA_DIR_OUT	       P6DIR_bit.P6DIR6 = 1             // set direction of I2C_SDA signal out
#define EEPROM_SDA_H                   P6OUT_bit.P6OUT6 = 1             // set I2C_SDA signal 1
#define EEPROM_SDA_L                   P6OUT_bit.P6OUT6 = 0             // reset I2C_SDA signal 0

#define EEPROM_SCL_DIR_OUT             P6DIR_bit.P6DIR7 = 1             // set direction of I2C_SCL signal out
#define EEPROM_SCL_H                   P6OUT_bit.P6OUT7 = 1             // set I2C_SCL signal 1
#define EEPROM_SCL_L                   P6OUT_bit.P6OUT7 = 0             // reset I2C_SCL signal 0

#define EEPROM_WP_OUT	       P7DIR_bit.P7DIR5 = 1             // set direction of I2C_SDA signal out
#define EEPROM_WP_H                   P7OUT_bit.P7OUT5 = 1             // set I2C_SDA signal 1
#define EEPROM_WP_L                   P7OUT_bit.P7OUT5 = 0             // reset I2C_SDA signal 0


#define EEPROM_DEVICE_ADDRESS          0xA0                 // I2C设备地址(存储芯片AT24CXX的设备地址)，bit7~bit4固定为1010b
                                                            // bit3~bit1为A2/A1/A0为设备地址位，A2~A0电平高低由相应的硬件输入脚决定
							    // bit0 为R/W选择位，1代表读，0代表写


typedef enum{CLEAR,SET}PinLevelDef;
typedef enum
{
  DYNAMIC_SCAN,
  COMMON_SCAN
}PageKeyScanDef;

void	InitAD(void);
uint GetAverageOfAD(uint *AD_data);
void	UCSInit(void);

extern uchar	G_SampleCount; 
extern bool8	G_SampleEndFlag;
extern uint    G_ADResults[2][SAMPLE_NUM];
extern bool8 G_KeyScanFlag;
extern uint G_PowerOffCounter;
extern uint G_AD_TimingStamp;
extern bool8 G_RxFlag;
extern bool8 G_TxFlag;
void KeyPinInit(PageKeyScanDef PageKeyScanFlag);
void UsartFrameCharSend(uchar FrameBuffDataChar);
void EnableUartTxInterrupt();  
void  ReadDataFromUartRxBuf();
void  WriteDataToUartTxBuf();
void  DisableUartTxInterrupt();
#endif
