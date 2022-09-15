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



/****************************24AA02E48T.c�ļ�˵��*************************************************/
//���ļ�Ϊ����оƬ24AA02E48T�����������
/*************************************************************************************************/


#include "IICROM24AA02E48T.h"
#include "DataType.h"  
#include "HardwareSet.h"



#define  IICROM_SDAIN_H	             1

#define	 IICROM_DELAY_6US		20
#define  IICROM_DELAY_350US          50000
#define  IICROM_DELAY_4MS            36000
#define  IICROM_DELAY_5MS            10000

#define  IICROM_TRY_TIME             3

#define  IICROM_GENERATE_ACK         0
#define  IICROM_UNGENERATE_ACK       1


bool8   G_IICROMDeviceAck = FALSE;   // �豸Ӧ��FALSE������Ӧ��TRUE������Ӧ��





/** void  IICRomDelay(uint16  DelayTime)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:TimeΪ��ʱʱ�������0 �� DelayTime �� 65535
*
* ����ֵ˵��: void
*
* ���ܽ���: ��ʱ����
*
* �ؼ���ע��
*
* δ�����:
* 
*/
void  IICRomDelay(uint16  DelayTime)
{ 
      uint16 i;  // ѭ������
    
      for (i = 0; i < DelayTime; i++);
}


/**void  IICROM_Inital(void)    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void
*
* ���ܽ���: I2C��ʼ������P0.4(SCK)��P0.5(SDA)����Ϊ��ͨ���ģʽ�����õ͵�ƽ
*
* �ؼ���ע��
*
* δ�����:
* 
*/
void  IICROM_Inital(void)
{
      IICROM_SDA_DIR_OUT;
      IICROM_SCL_DIR_OUT;
      IICROM_SCL_L;
      IICROM_SDA_L;
      IICRomDelay(IICROM_DELAY_6US);
}


/**void  Start_IICROM(void)    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void
*
* ���ܽ���: ����I2C��ʼ�źţ�SCLΪ�ߵ�ƽʱ��SDA�ɸߵ�ƽ��͵�ƽ���䣬��ʼ��������
*
* �ؼ���ע��
*
* δ�����:
* 
*/
void  Start_IICROM(void)
{
      IICROM_Inital();
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SDA_H;
      IICRomDelay(IICROM_DELAY_6US); 
      IICROM_SCL_H;
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SDA_L; 
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SCL_L;   
      IICRomDelay(IICROM_DELAY_6US);
}


/**void  Stop_IICROM()    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void
*
* ���ܽ���:����I2Cֹͣ�źţ�SCLΪ�ߵ�ƽʱ��SDA�ɵ͵�ƽ��ߵ�ƽ���䣬������������
*
* �ؼ���ע��
*
* δ�����:
* 
*/
void  Stop_IICROM()
{
      IICROM_SDA_DIR_OUT;
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SDA_L;  
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SCL_H;   
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SDA_H;  
      IICRomDelay(IICROM_DELAY_6US);
}


/**bool8 Wait_Ack_IICROM()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: bool8��FALSE��ʾ�豸������оƬ����Ӧ��TRUE��ʾ�豸������оƬ����Ӧ��
*
* ���ܽ���: Wait_Ack_IIROM�ȴ�Ӧ���źŵ����������豸�ڵھŸ�ʱ�����ڻᷢ���͵�ƽӦ���źţ��Ա��������յ���ַ�����ݡ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8 Wait_Ack_IICROM()
{
     IICROM_SDA_H;         
     IICROM_SDA_DIR_IN;
     IICRomDelay(IICROM_DELAY_6US);
     IICROM_SCL_H;
     IICRomDelay(IICROM_DELAY_6US);
     if (IICROM_SDAIN == IICROM_SDAIN_H)
     {
         IICROM_SCL_L;
         IICROM_SDA_DIR_OUT; 
         return FALSE;
     }
     else
     {
         IICROM_SCL_L;
         IICROM_SDA_DIR_OUT; 
         return TRUE; 
     }        
}


/**void  IIROMSendByte(uchar8 Data)    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:DataΪ���͵��ֽ����ݣ�0 �� Data �� 255 
*
* ����ֵ˵��: void
*
* ���ܽ���: ����һ���ֽڣ����شӻ�����Ӧ���źţ�Ack = 1��Ӧ��Ack = 0��Ӧ��
*
* �ؼ���ע����������ʱ��ֻ����SCLΪ�ߵ�ƽʱ��SDA�ϵĵ�ƽΪ��Ч���ݡ�
*           ��д��Ƭ�������������ݳ���ʱ�������SCL���ڵ͵�ƽʱ�������ݵ�ƽ�͵�SDA��
*           Ȼ������SCL����ʱSDA��Ӧ�е�ƽ���䣬��ʱ������SCL���ٽ�����һλ�����ݴ���ֱ����ɡ�
*
* δ�����:
* 
*/
void  IIROMSendByte(uchar8 Data)
{
      uchar8 i;  // ѭ������
      
      IICROM_SDA_DIR_OUT;
      IICROM_SCL_DIR_OUT;
      for (i = 0; i < BYTELENGTH; i++)
      { 
          if ( (Data & 0x80) == 0 )
          {
              IICROM_SDA_L;
          }
          else
          {
              IICROM_SDA_H;
          }
          IICRomDelay(IICROM_DELAY_6US);   
          IICROM_SCL_H;         
          Data <<= 1;
          IICRomDelay(IICROM_DELAY_6US);       
          IICROM_SCL_L;
          IICRomDelay(IICROM_DELAY_6US); 
      }     
      G_IICROMDeviceAck = Wait_Ack_IICROM();
}


/**uchar8 IIROMRcvByte()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: �� 
*
* ����ֵ˵��: uchar8����Χ0 �� ReceivedData �� 255 
*
* ���ܽ���:��24AA02E48T���գ���ȡ��һ���ֽ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 	
uchar8  IIROMRcvByte()
{
      uchar8  ReceivedData = 0;  // ���յ�������
      uchar8  i;                 // ѭ������
      
      IICROM_SDA_H;         
      IICROM_SDA_DIR_IN;
      for (i = 0; i < BYTELENGTH; i++)
      {
           IICROM_SCL_L;     
           IICRomDelay(IICROM_DELAY_6US); 
           IICROM_SCL_H;     
           IICRomDelay(IICROM_DELAY_6US);
           ReceivedData = ReceivedData << 1;
           if (IICROM_SDAIN == IICROM_SDAIN_H)
           {
               ReceivedData += 1; 
           }
           IICRomDelay(IICROM_DELAY_6US);
      }
      IICROM_SCL_L;
      IICRomDelay(IICROM_DELAY_6US);
      return(ReceivedData);
}


/**void  Ack_Out(uchar8 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  DataΪѡ���źţ�0 �� Data �� 1��DataΪ1ʱ������ACKӦ��Ϊ0ʱ����ACKӦ��
*
* ����ֵ˵��: void
*
* ���ܽ���: I2CӦ��TempDataΪ1ʱ������ACKӦ��Ϊ0ʱ����ACKӦ��
*
* �ؼ���ע��1���������ݵ�IC�ڽ��յ�8bit���ݺ��������ݵ�IC�����ض��ĵ͵�ƽ�źţ���ʾ�Ѿ��յ����ݡ�
*           2���豸��д�����ڼ䲻������Ӧ����˿ɸ���Ӧ��������д���ڵ����
*
* δ�����:
* 
*/ 
void  Ack_Out(uchar8 Data)
{
      IICROM_SDA_DIR_OUT;
      if (Data == IICROM_UNGENERATE_ACK)
      {
          IICROM_SDA_H;
      }
      else
      {
          IICROM_SDA_L;
      }
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SCL_H;
      IICRomDelay(IICROM_DELAY_6US);
      IICROM_SCL_L;
}


/**bool8  IICROM_BufferWrite(uchar8 *Buffer, uchar8 WriteAddr, uchar8 NumByteToWrite)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: WriteAddrΪ���ݴ��洢�ĵ�ַ��0x00 �� WriteAddr �� 0x80��24AA02E48T�ڴ�ռ�Ϊ2Kbit��256Byte��,0x80~0xFFΪд�����������������Ψһ��ʶ��
*           BufferΪָ���ַ������ݵĵ�ַ�������Ŵ��洢���ݵ����ֽ�
*           NumByteToWriteΪ���洢���ݵ��ֽ�����0 �� NumByteToWrite �� 255
*           Page Write Time 3 ms, typical, Page Write Buffer:8-byte page (24AA02E48/24AA02E64)
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE���洢ʧ�ܷ���FALSE
*
* ���ܽ���: ��24AA02E48Tָ����ַWriteAddrд��NumByteToWrite���ֽ�����
*
* �ؼ���ע��1������ڲ���STOP����֮ǰ�������8�ֽڣ���ô��ַ���������ᷭת��֮ǰ���յ������ݽ��ᱻ���ǵ�
*           2��once the Stop condition is received ,an internal write cycle�����5ms�� will begin
*           3��ÿ��д���1���ֽں���Ҫ��ʱ����Լ1��IICRomDelay(IICROM_DELAY_5MS)��IICROM_DELAY_5MS=2500;���ſ��Դ�24AA02E48T�ж�ȡ�˴�д�������
*
* δ�����:
* 
*/ 
bool8  IICROM_BufferWrite(uchar8 *Buffer, uchar8 WriteAddr, uchar8 NumByteToWrite)
{	
       uchar8  WrittedByteNum = 0;             // д����ֽڸ���  
	  
       Start_IICROM();                          // Send START condition 	 
       IIROMSendByte(IICROM_DEVICE_ADDRESS);   // Send EEPROM address for write
       if (G_IICROMDeviceAck == FALSE)
       {
           return FALSE;
       } 
       IIROMSendByte(WriteAddr);               // Send the EEPROM's internal address to write to 
       if (G_IICROMDeviceAck == FALSE)
       {
           return FALSE;
       }
  
       WrittedByteNum = 0;	  
	  
       do
       {		
           IIROMSendByte(*Buffer);             // Send the current byte 	
           if (G_IICROMDeviceAck == FALSE)
           {
               return FALSE;
           } 
           WrittedByteNum++;
           WriteAddr++;
           Buffer++;                   // Point to the next byte to be written
           if ( ((WriteAddr & 0x07) == 0) && (WrittedByteNum < NumByteToWrite) ) //The 2K EEPROM is capable of 8-byte Page Writes
           {
                 Stop_IICROM(); 		 
                 IICRomDelay(IICROM_DELAY_5MS);   // һ���յ�stop conditionʱ���ڲ�д���ڿ�ʼ��д�������5ms      
                 //IICRomDelay(IICROM_DELAY_4MS); // Ŀǰ��һ��д127���ֽ�ʱ����оƬ��д���ֽ���Ϊ128����������Ҫ4ms��	   
                 Start_IICROM();                          // Send START condition 	 
                 IIROMSendByte(IICROM_DEVICE_ADDRESS);   // Send EEPROM address for write
                 if (G_IICROMDeviceAck == FALSE)
                 {
                     return FALSE;	
                 }
                 IIROMSendByte(WriteAddr);               // Send the EEPROM's internal address to write to 
                 if (G_IICROMDeviceAck == FALSE)
                 {
                     return FALSE;
                 }
          }		                   
      }	while (WrittedByteNum < NumByteToWrite);         // While there is data to be written 
      Stop_IICROM();                    //Send STOP condition 
      return TRUE;
}


/**bool8  IICROM_BufferRead(uchar8 *Buffer, uchar8 ReadAddr, uchar8 NumByteToRead)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: ReadAddrΪ����ȡ���ݵĴ洢��ַ��0x00 �� ReadAddr �� 0xff��24AA02E48T�ڴ�ռ�Ϊ2Kbit��256Byte��,0x80~0xFFΪд�����������������Ψһ��ʶ��
*           BufferΪָ���ַ������ݵĵ�ַ�������������ȡ���ݵ����ֽ�
*           NumByteToReadΪ����ȡ���ݵ��ֽ�����0 �� NumByteToRead�� 8��24AA02E48T��8Byteҳдģʽʹ����������д��8Byte���ݵ�24AA02E48T
*
* ����ֵ˵��: bool8,��ȡ�ɹ�����TRUE����ȡʧ�ܷ���FALSE
*
* ���ܽ���: ��24AA02E48Tָ����ַReadAddr��ȡNumByteToRead���ֽ�����
*
* �ؼ���ע��������ȡ����ʱ��ÿ��ȡһ���ֽڣ�������ӦоƬһ���͵�ƽ��ACKӦ��
*           ����ȡ�����һ���ֽ�ʱ��������Ӧ��
*
* δ�����:
* 
*/ 
bool8  IICROM_BufferRead(uchar8 *Buffer, uchar8 ReadAddr, uchar8 NumByteToRead)
{  	
      Start_IICROM();                            // Send START condition 	
      IIROMSendByte(IICROM_DEVICE_ADDRESS);            // Send EEPROM address for write 
      if (G_IICROMDeviceAck == FALSE)
      {
          return FALSE;	
      }
      IIROMSendByte(ReadAddr);                  // Send the EEPROM's internal address to Read From 
      if (G_IICROMDeviceAck == FALSE)
      {
          return FALSE;
      }
  
      Start_IICROM();                            // Send STRAT condition a second time  	 
      IIROMSendByte(IICROM_DEVICE_ADDRESS + 1);         // Send EEPROM address for read
      if (G_IICROMDeviceAck == FALSE)
      {
          return FALSE;
      }
       
      NumByteToRead--;        
      while (NumByteToRead)                     //While there is data to be read 
      {		
          *Buffer = IIROMRcvByte();             // Read a byte from the EEPROM 		
          Buffer++;                             // Point to the next location where the byte read will be saved 
          Ack_Out(IICROM_GENERATE_ACK);                //generate ack		
          NumByteToRead--;                      // Decrement the read bytes counter 
      }
      
      *Buffer = IIROMRcvByte();                 // Read the last byte from the EEPROM
      Ack_Out(IICROM_UNGENERATE_ACK);
      Stop_IICROM();
      return TRUE;
}


/**void IICROM_WriteCharData(uchar8 SaveAddress,uchar8 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0x80
*           DataΪ���洢�����ݣ�0 �� Data �� 255 
*
* ����ֵ˵��: void
*
* ���ܽ���: дһ���ֽ��ַ�������Data��24AA02E48T��SaveAddress��ַ
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  IICROM_WriteCharData(uchar8 SaveAddress, uchar8 Data)
{	
      IICROM_BufferWrite(&Data,SaveAddress,CHAR_BYTENUM);	
}


/**void IICROM_ReadCharData(uchar8 SaveAddress, uchar8 * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0xff
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: void
*
* ���ܽ���: ��24AA02E48T��SaveAddress��ַ�ж�һ���ֽ��ַ������ݣ����ڵ�ַData��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  IICROM_ReadCharData(uchar8 SaveAddress, uchar8 * Data)
{
      IICROM_BufferRead(Data,SaveAddress,CHAR_BYTENUM);
}


/**bool8 IICROM_SaveCharData(uchar8 SaveAddress, uchar8 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0x80
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*
* ����ֵ˵��:bool8���洢�ɹ�����TRUE���洢ʧ�ܷ���FALSE

* ���ܽ���: �����ַ�������Data��24AA02E48T��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����SUCCESS�����򷵻�FAIL
*
* �ؼ���ע��1�����һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FALSE��
*           2������ִ��һ�θú�����һ��д�ɹ���Լ6ms
*
* δ�����:
* 
*/ 
bool8  IICROM_SaveCharData(uchar8 SaveAddress, uchar8  Data)
{
      uchar8 EEPTemp;  // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
      uchar8 i;        // ѭ������

      for (i = 0; i < IICROM_TRY_TIME; i++)
      {	
          IICROM_WriteCharData(SaveAddress, Data);
          IICRomDelay(IICROM_DELAY_5MS);  // ÿ��д�����ݺ�����д����ʱ������ֹͣ����󣬻����һ���ڲ�д���ڣ��ڲ�д����(�ֽ�д��ҳд)���5ms
                                          // �����Ҫ��ʱһ����ٶ�ȡ�������Ըô�������ʱ5ms
                                         // The write cycle time tWR is the time from a valid stop condition 
                                         // of a write sequence to the end of the internal clear/write cycle.		
          IICROM_ReadCharData(SaveAddress,&EEPTemp);
          if (EEPTemp == Data) 
          {
//	      RecordEventFaultNumber(&EncryptPerfV,FAULT_UNHAPPEN);
              return TRUE;
          }
          else
          {					
//	      RecordEventFaultNumber(&EncryptPerfV,FAULT_HAPPEN);			 
          }
      }
//	HandleSystemFaultPara(ENCRYPTION_WRITE_FAULT);
      return FALSE;
}


/**bool8  IICROM_LoadCharData(uchar8 SaveAddress, uchar8 * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0xff
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��24AA02E48T��SaveAddress��ַ�ж�һ���ֽ����ݣ����ڵ�ַData��
*
* �ؼ���ע�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
bool8  IICROM_LoadCharData(uchar8 SaveAddress, uchar8* Data)
{
        uchar8 EEPTemp;  // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
        uchar8 i;        // ѭ������	
        
        for (i = 0;i < IICROM_TRY_TIME;i++)
        {
                IICROM_ReadCharData(SaveAddress,Data);	
                IICROM_ReadCharData(SaveAddress, &EEPTemp);
                if (EEPTemp == *Data) 
                {
//		   RecordEventFaultNumber(&EncryptPerfV,FAULT_UNHAPPEN);
                   return TRUE;
                }
                else
                {
//		   RecordEventFaultNumber(&EncryptPerfV,FAULT_HAPPEN);
                }
        }
//	HandleSystemFaultPara(ENCRYPTION_READ_FAULT);
        return FALSE;
}


/**bool8 IICROM_SaveCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0x80
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE���洢ʧ�ܷ���FALSE
*
* ���ܽ���: �����ַ�������Data��24AA02E48T��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  IICROM_SaveCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
	uint16 i;   // ѭ������
	
	for (i = 0; i < ArrayLength; i++)
	{
              if (IICROM_SaveCharData(SaveAddress + i, *(Data + i)) != TRUE)
              {			
                  return FALSE;		
              }
	}
	return TRUE;
}

/**bool8  IICROM_LoadCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 0xff
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ���ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��24AA02E48T��SaveAddress��ַ�ж�ArrayLength���ֽ����ݣ����ڵ�ַData~Data+ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  IICROM_LoadCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
	uint16 i;    // ѭ������
	
	for (i = 0; i < ArrayLength; i++)
	{
            if (IICROM_LoadCharData(SaveAddress + i, (Data + i)) != TRUE)
            {
                //HandleSystemFaultPara(ENCRYPTION_READ_FAULT);
                return FALSE;
            }		
	}
	return TRUE;
}



uchar8  AWriteData[130] = {0};
uchar8  AReadData[130] = {0};

/**void  IICROMReadAndWriteTest()//�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: �� 
*
* ����ֵ˵��: 
*
* ���ܽ���: IICROM��д����
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  IICROMReadAndWriteTest()
{	
      uchar8  i;
	
      for(i=0;i<130;i++)
      {
          AWriteData[i]=150-i;
          AReadData[i]=0;
      }
//	TEST_TIME_PIN_OUT_H;  // ����֮�䲻����ʱʱ���ߵ�ƽ����ʱ��Լ0.8us
	//IICRomDelay(IICROM_DELAY_5MS); 
	//IICROM_BufferWrite(AWriteData, 7,120);
//	IICRomDelay(2500);		
//	IICROM_BufferRead(AReadData, 7, 120);
//	IICROM_SaveCharData(1, 34);
//	IICROM_SaveCharArrayData(0xFA, AWriteData, 6);
//	IICROM_LoadCharArrayData(0xFA, AReadData, 6);
	//IICRomDelay(2500);
//	TEST_TIME_PIN_OUT_L;
}









