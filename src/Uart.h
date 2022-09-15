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



extern unsigned char G_TxBuf[100];   //UART��������
extern unsigned char G_RxBuf[100];   //UART��������
extern unsigned char G_TxByteNum;    //UART�����ֽ���
extern unsigned char G_RxByteNum;    //UART�����ֽ���
extern bool8  G_TxStartFlag;  //���Ϳ�ʼ��־λ
extern bool8  G_RxFinishFlag; //���ս�����־λ
extern bool8  G_ReceiveReadUniqueCodeFlag; //���յ���ȡΨһ���־λ
extern bool8  G_ReceiveCalcCodeFlag; //���յ��������־λ
extern bool8  G_ReceiveActivateCodeGenerateFlag; //���յ����������������־λ
extern bool8  G_ReceiveActivateCodeCorrectFlag;  //���յ�ѯ�ʼ������Ƿ���ȷ�����־λ
extern bool8  G_ActivateSuccess;



#endif