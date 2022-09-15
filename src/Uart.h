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


#ifndef UART_H
#define UART_H


#include "HardwareSet.h"




#define  DEVICE_ADDRESS         0xAA
#define  COMMAND_READ           0x03
#define  CRC_L                  0xB4
#define  CRC_H                  0xCB

#define PACKAGE_TAIL            0xCC

#define	UART_RXBYTENUM_MAX	50

#define  FUNCTION_INDEX                               1     
#define  REG_BYTEH_INDEX                              2  
#define  REG_BYTEL_INDEX                              3  
#define  REG_NUM_INDEX                                5  





void  TransmitUniqueCodeToActivator(void);
void  ActivateMeterThroughUartActivator();
void  ActivateReceiveFrameHandle();

void  TransmitGenerateActivateCodeOrNotToActivator();
void  TransmitActivateCodeCorrectOrNotToActivator();


void  ActivationRequestHandle();
void  ActivationRespondHandle(); 



extern unsigned char G_TxBuf[100];   //UART发送数组
extern unsigned char G_RxBuf[100];   //UART接收数组
extern unsigned char G_TxByteNum;    //UART发送字节数
extern unsigned char G_RxByteNum;    //UART接收字节数
extern bool8  G_TxStartFlag;  //发送开始标志位
extern bool8  G_RxFinishFlag; //接收结束标志位
extern bool8  G_ReceiveReadUniqueCodeFlag; //接收到读取唯一码标志位
extern bool8  G_ReceiveCalcCodeFlag; //接收到计算码标志位
extern bool8  G_ReceiveActivateCodeGenerateFlag; //接收到激活码生成命令标志位
extern bool8  G_ReceiveActivateCodeCorrectFlag;  //接收到询问激活码是否正确命令标志位
extern bool8  G_ActivateSuccess;



#endif