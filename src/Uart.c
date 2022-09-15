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


#include "Uart.h"
#include "CopyRightActivate.h"

//主机-从机读取寄存器地址宏定义
#define IS_UNIQUE_CODE_GENERATE         2030
#define READ_UNIQUE_CODE                2031
#define IS_ACT_CODE_CORRECT             2038

//主机-从机写入寄存器地址宏定义
#define SEND_CALC_CODE                  2034


unsigned char G_TxBuf[100]={0};   //UART发送数组
unsigned char G_RxBuf[100]={0};   //UART接收数组
unsigned char G_TxByteNum = 0;    //UART发送字节数
unsigned char G_RxByteNum = 0;    //UART接收字节数
bool8  G_TxStartFlag = FALSE;  //发送开始标志位
bool8  G_RxFinishFlag = FALSE; //接收结束标志位
bool8  G_ReceiveReadUniqueCodeFlag = FALSE; //接收到读取唯一码命令标志位
bool8  G_ReceiveCalcCodeFlag = FALSE; //接收到计算码命令标志位
bool8  G_ReceiveActivateCodeGenerateFlag = FALSE; //接收到激活码生成命令标志位
bool8  G_ReceiveActivateCodeCorrectFlag = FALSE;  //接收到询问激活码是否正确命令标志位
bool8  G_ActivateSuccess = FALSE; //激活仪表结果，TRUE表示激活成功，FALSE表示激活失败

void  COPY_FrameSend(uchar ByteNum,uchar *TxBuf);
 
/** 
* 函数名称和参量和返回值类型。
* uint16_t	crc_check(uint8_t pack_byte)
* 变量范围: 
* pack_byte:校验字节个数。
* 返回值说明: uint16_t       
*       返回CRC校验码
* 功能介绍: 计算ElectrodePaste数据帧校验码
* 
* 关键备注：
*
* 未来提高:
* 
*/
unsigned int crc_check(unsigned char pack_byte,const unsigned char * const Ptr)
{
	unsigned int polyn_m = 0xA001;
	unsigned char crc_i,crc_j;
	unsigned int crc = 0xFFFF;
	for(crc_i=0;crc_i<pack_byte;crc_i++)
	{
		crc ^= Ptr[crc_i];
		for(crc_j=0;crc_j<8;crc_j++)
		{
			if((crc&0x01)==0x01)
			{
				crc>>=1;
				crc^=polyn_m;
			}
			else
				crc>>=1;
		}
	}
	return( crc );
}
/** void  COPY_FrameSend(uchar ByteNum,uchar *TxBuf)    //函数名称和参量和返回值类型。
* 变量范围: 
*
* 返回值说明:  
*
* 功能介绍: 与液晶（加密主机）通信发送响应帧函数。         
*
* 关键备注：
*
* 未来提高:
* 
*/
void  COPY_FrameSend(uchar ByteNum,uchar *TxBuf)
{
  uchar i = 0;
    for(i = 0;i < ByteNum;i++)
    {
      UCA0TXBUF = TxBuf[i];
      while(UCA0STAT&UCBUSY);
    }
}
/** void  TransmitUniqueCodeToActivator(void)     //函数名称和参量和返回值类型。
* 变量范围: 
*
* 返回值说明:  
*
* 功能介绍: 发送唯一码给激活器。         
*
* 关键备注：在收到激活器的读取唯一码命令(01 03 00 00 00 06 B4 CB)时，发送唯一码(0xAA + 6byte唯一码 + 0xCC)到上位机。
*
* 未来提高:
* 
*/
void  TransmitUniqueCodeToActivator(void)
{
    unsigned char i;  // 循环变量    
    unsigned int CrcValue = 0;
           
    ReadUniqueCode(G_UniqueCode);
    G_TxBuf[0] = DEVICE_ADDRESS;
    G_TxBuf[1] = 0x03;
    G_TxBuf[2] = UNIQUE_CODE_BYTE_NUM;
    for (i = 0; i < UNIQUE_CODE_BYTE_NUM; i++) 
    {
         G_TxBuf[i+3] = G_UniqueCode[i];
    }
    CrcValue = crc_check(UNIQUE_CODE_BYTE_NUM+3,G_TxBuf);
    G_TxBuf[9] = CrcValue;
    G_TxBuf[10] = CrcValue>>8;
    G_TxStartFlag = TRUE;       
    COPY_FrameSend(11,G_TxBuf);
    G_TxStartFlag = FALSE;
}                                                               
/** void TransmitActivateCodeGenerateResultToActivator()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍: 发送是激活码生成结果给激活器
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  TransmitActivateCodeGenerateResultToActivator()
{    
  unsigned int CrcValue = 0;
      if (G_ActivateSuccess == TRUE)
      {
           G_TxBuf[0] = DEVICE_ADDRESS;
           G_TxBuf[1] = 0x03;
           G_TxBuf[2] = 0x02;
           G_TxBuf[3] = 0xA5;
           G_TxBuf[4] = 0x01;     
           CrcValue = crc_check(5,G_TxBuf);
           G_TxBuf[5] = CrcValue;
           G_TxBuf[6] = CrcValue>>8;
      }
      else
      {
           G_TxBuf[0] = DEVICE_ADDRESS;
           G_TxBuf[1] = 0x03;
           G_TxBuf[2] = 0x02;
           G_TxBuf[3] = 0xA5;
           G_TxBuf[4] = 0x00;     
           CrcValue = crc_check(5,G_TxBuf);
           G_TxBuf[5] = CrcValue;
           G_TxBuf[6] = CrcValue>>8;           
      }
      G_TxStartFlag = TRUE;       
      COPY_FrameSend(7,G_TxBuf);  
      G_TxStartFlag = FALSE;
}


/** void TransmitGenerateActivateCodeOrNotToActivator()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍: 发送是否生成激活码给激活器
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  TransmitGenerateActivateCodeOrNotToActivator()
{ 
     if ( (G_RxFinishFlag == TRUE) && (G_ReceiveActivateCodeGenerateFlag == TRUE) )	
     { 
            G_ReceiveActivateCodeGenerateFlag = FALSE; 
            G_RxFinishFlag = FALSE;  
            TransmitActivateCodeGenerateResultToActivator();     
     }
}


/** void ActivateMeterThroughUartActivator()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍: 通过UART型激活器激活仪表
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  ActivateMeterThroughUartActivator()
{    
     unsigned char i;  // 循环变量 
  
     if ( (G_RxFinishFlag == TRUE) && (G_ReceiveReadUniqueCodeFlag == TRUE) )	
     { 
            G_ReceiveReadUniqueCodeFlag = FALSE; 
            G_RxFinishFlag = FALSE;  
            TransmitUniqueCodeToActivator();            
     }
     else if ( (G_ReceiveCalcCodeFlag == TRUE)&&(G_RxFinishFlag == TRUE) )
     {
         G_ReceiveCalcCodeFlag = FALSE;
         G_RxFinishFlag = FALSE;  
         for (i = 0; i < CALC_CODE_BYTE_NUM; i++) 
         {
              G_CalcSourceCode[i] = G_RxBuf[i+7];  
         }
         
         G_ActivateSuccess =  ActivateMeter();               
         TransmitActivateCodeGenerateResultToActivator();              
     }     
}
/** void ActivateReceiveFrameHandle()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍: 激活器从机接收帧处理
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  ActivateReceiveFrameHandle()
{    
  unsigned int RegAdd = 0;
  if(G_RxFinishFlag == TRUE)
  {
    RegAdd = G_RxBuf[REG_BYTEH_INDEX];
    RegAdd <<= 8;
    RegAdd += G_RxBuf[REG_BYTEL_INDEX];
    if(G_RxBuf[FUNCTION_INDEX] == 0x03)
    {
      switch(RegAdd)
      {
      case READ_UNIQUE_CODE:
        G_ReceiveReadUniqueCodeFlag = TRUE;
        break;
      case IS_UNIQUE_CODE_GENERATE:
        G_ReceiveActivateCodeGenerateFlag = TRUE;
        break;
      case IS_ACT_CODE_CORRECT:
        G_ReceiveActivateCodeCorrectFlag = TRUE;
        break;
      default:break;
      }
    }
    else if(G_RxBuf[FUNCTION_INDEX] == 0x10)
    {
      switch(RegAdd)
      {
      case SEND_CALC_CODE:
        G_ReceiveCalcCodeFlag = TRUE;
        break;
      default:break;
      }
    }
  }
}

/** void TransmitActivateCodeCorrectOrNotToActivator()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍: 发送激活码正确与否给激活器
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  TransmitActivateCodeCorrectOrNotToActivator()
{ 
      bool8  ActivateCodeCorrect = FALSE;
      unsigned int CrcValue = 0;
      if ( (G_RxFinishFlag == TRUE) && (G_ReceiveActivateCodeCorrectFlag == TRUE) )	
      { 
            G_ReceiveActivateCodeGenerateFlag = FALSE; 
            G_RxFinishFlag = FALSE;  
            
            G_ActivatorAskStateEnable = TRUE;
            ActivateCodeCorrect = CheckActivationCode();
            if (ActivateCodeCorrect == TRUE)
            {
               G_TxBuf[0] = DEVICE_ADDRESS;
               G_TxBuf[1] = 0x03;
               G_TxBuf[2] = 0x02;
               G_TxBuf[3] = 0xA5;
               G_TxBuf[4] = 0x01;     
               CrcValue = crc_check(5,G_TxBuf);
               G_TxBuf[5] = CrcValue;
               G_TxBuf[6] = CrcValue>>8;             
            }
            else
            {
               G_TxBuf[0] = DEVICE_ADDRESS;
               G_TxBuf[1] = 0x03;
               G_TxBuf[2] = 0x02;
               G_TxBuf[3] = 0xA5;
               G_TxBuf[4] = 0x00;     
               CrcValue = crc_check(5,G_TxBuf);
               G_TxBuf[5] = CrcValue;
               G_TxBuf[6] = CrcValue>>8;              
            }
            G_TxStartFlag = TRUE;       
            COPY_FrameSend(7,G_TxBuf);  
            G_TxStartFlag = FALSE;       
      }
}


/** void ActivationRequestHandle()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍:激活器端激活相关请求处理
*
* 关键备注：
* 
* 未来提高:
         

* 
*/ 
void  ActivationRequestHandle()
{ 
  static unsigned char FrameLength = 0xff;
  unsigned int CrcReceive = 0,CrcCalculate = 0;
  if ((G_TxStartFlag == FALSE )&&(G_RxFinishFlag == FALSE))   //仪表
  {	
    ReadDataFromUartRxBuf(); 
    if(G_RxByteNum == 0)
    {                                                             
        if(G_RxBuf[G_RxByteNum] == DEVICE_ADDRESS)
        {
           G_RxByteNum++;  
        }   
        else
        {
           G_RxByteNum = 0; 
        }  
    }
    else  
    {                      
         G_RxByteNum++;
         if (G_RxByteNum > UART_RXBYTENUM_MAX)
         {
             G_RxByteNum = 0; 
             FrameLength = 0xff;
         }
    }     
    if(G_RxByteNum == REG_NUM_INDEX+1)  
    {
      if(G_RxBuf[FUNCTION_INDEX] == 0x03)
      {
        FrameLength = REG_NUM_INDEX+2;
      }
      else if(G_RxBuf[FUNCTION_INDEX] == 0x10)
      {
        FrameLength = REG_NUM_INDEX+G_RxBuf[REG_NUM_INDEX]*2+3;
      }
      if (FrameLength > UART_RXBYTENUM_MAX)
      {
        G_RxByteNum = 0; 
        FrameLength = 0xff;
      }
    }
  }
  if(G_RxByteNum > FrameLength)
  {
    CrcReceive = G_RxBuf[FrameLength];
    CrcReceive <<= 8;
    CrcReceive += G_RxBuf[FrameLength-1];
    CrcCalculate = crc_check(FrameLength-1,G_RxBuf);
    if(CrcCalculate == CrcReceive)
    {
      FrameLength = 0xff;
      G_RxByteNum = 0;
      G_RxFinishFlag = TRUE;
    }
    else
    {
      G_RxByteNum = 0; 
      FrameLength = 0xff;
    }
  }
}

/** void ActivationRespondHandle()  //函数名称和参量和返回值类型。
* 变量范围: 无
*
* 返回值说明: void 
*
* 功能介绍:激活器端激活相关请求对应的响应处理
*
* 关键备注：
* 
* 未来提高:
* 
*/ 
void  ActivationRespondHandle()
{ 
      if (G_TxStartFlag == TRUE)
      {                             
          UCA0TXBUF = G_TxBuf[G_TxByteNum];                                
          G_TxByteNum++; 
          if (G_TxByteNum >= 8)  //共发送8字节给上位机
          {                               
              G_TxStartFlag = FALSE;
              DisableUartTxInterrupt(); 
              G_TxByteNum = 0;
          } 
      }       
}







