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


#include "Uart.h"
#include "CopyRightActivate.h"

//����-�ӻ���ȡ�Ĵ�����ַ�궨��
#define IS_UNIQUE_CODE_GENERATE         2030
#define READ_UNIQUE_CODE                2031
#define IS_ACT_CODE_CORRECT             2038

//����-�ӻ�д��Ĵ�����ַ�궨��
#define SEND_CALC_CODE                  2034


unsigned char G_TxBuf[100]={0};   //UART��������
unsigned char G_RxBuf[100]={0};   //UART��������
unsigned char G_TxByteNum = 0;    //UART�����ֽ���
unsigned char G_RxByteNum = 0;    //UART�����ֽ���
bool8  G_TxStartFlag = FALSE;  //���Ϳ�ʼ��־λ
bool8  G_RxFinishFlag = FALSE; //���ս�����־λ
bool8  G_ReceiveReadUniqueCodeFlag = FALSE; //���յ���ȡΨһ�������־λ
bool8  G_ReceiveCalcCodeFlag = FALSE; //���յ������������־λ
bool8  G_ReceiveActivateCodeGenerateFlag = FALSE; //���յ����������������־λ
bool8  G_ReceiveActivateCodeCorrectFlag = FALSE;  //���յ�ѯ�ʼ������Ƿ���ȷ�����־λ
bool8  G_ActivateSuccess = FALSE; //�����Ǳ�����TRUE��ʾ����ɹ���FALSE��ʾ����ʧ��

void  COPY_FrameSend(uchar ByteNum,uchar *TxBuf);
 
/** 
* �������ƺͲ����ͷ���ֵ���͡�
* uint16_t	crc_check(uint8_t pack_byte)
* ������Χ: 
* pack_byte:У���ֽڸ�����
* ����ֵ˵��: uint16_t       
*       ����CRCУ����
* ���ܽ���: ����ElectrodePaste����֡У����
* 
* �ؼ���ע��
*
* δ�����:
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
/** void  COPY_FrameSend(uchar ByteNum,uchar *TxBuf)    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��:  
*
* ���ܽ���: ��Һ��������������ͨ�ŷ�����Ӧ֡������         
*
* �ؼ���ע��
*
* δ�����:
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
/** void  TransmitUniqueCodeToActivator(void)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��:  
*
* ���ܽ���: ����Ψһ�����������         
*
* �ؼ���ע�����յ��������Ķ�ȡΨһ������(01 03 00 00 00 06 B4 CB)ʱ������Ψһ��(0xAA + 6byteΨһ�� + 0xCC)����λ����
*
* δ�����:
* 
*/
void  TransmitUniqueCodeToActivator(void)
{
    unsigned char i;  // ѭ������    
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
/** void TransmitActivateCodeGenerateResultToActivator()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���: �����Ǽ��������ɽ����������
*
* �ؼ���ע��
* 
* δ�����:
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


/** void TransmitGenerateActivateCodeOrNotToActivator()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���: �����Ƿ����ɼ������������
*
* �ؼ���ע��
* 
* δ�����:
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


/** void ActivateMeterThroughUartActivator()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���: ͨ��UART�ͼ����������Ǳ�
*
* �ؼ���ע��
* 
* δ�����:
* 
*/ 
void  ActivateMeterThroughUartActivator()
{    
     unsigned char i;  // ѭ������ 
  
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
/** void ActivateReceiveFrameHandle()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���: �������ӻ�����֡����
*
* �ؼ���ע��
* 
* δ�����:
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

/** void TransmitActivateCodeCorrectOrNotToActivator()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���: ���ͼ�������ȷ����������
*
* �ؼ���ע��
* 
* δ�����:
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


/** void ActivationRequestHandle()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���:�������˼������������
*
* �ؼ���ע��
* 
* δ�����:
         

* 
*/ 
void  ActivationRequestHandle()
{ 
  static unsigned char FrameLength = 0xff;
  unsigned int CrcReceive = 0,CrcCalculate = 0;
  if ((G_TxStartFlag == FALSE )&&(G_RxFinishFlag == FALSE))   //�Ǳ�
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

/** void ActivationRespondHandle()  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ��
*
* ����ֵ˵��: void 
*
* ���ܽ���:�������˼�����������Ӧ����Ӧ����
*
* �ؼ���ע��
* 
* δ�����:
* 
*/ 
void  ActivationRespondHandle()
{ 
      if (G_TxStartFlag == TRUE)
      {                             
          UCA0TXBUF = G_TxBuf[G_TxByteNum];                                
          G_TxByteNum++; 
          if (G_TxByteNum >= 8)  //������8�ֽڸ���λ��
          {                               
              G_TxStartFlag = FALSE;
              DisableUartTxInterrupt(); 
              G_TxByteNum = 0;
          } 
      }       
}







