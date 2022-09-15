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



/****************************AT24CXX.c�ļ�˵��********************************/
// ���ļ�Ϊ�洢оƬAT24CXX�ĵײ�����������΢������ʹ�õ���AT24C64�洢оƬ
// AT24C64 Ϊ64k bit,�� 8192�ֽ�
/*****************************************************************************/


#include "AT24C64.h"
#include "DataType.h" 
#include "HardwareSet.h"
  



#define  EEPROM_SDAIN_H	             1

#define	 DELAY_6US		  	     50          
#define	 DELAY_350US		  	     2000
#define	 DELAY_1400US		  	     8000
#define	 DELAY_1800US		  	     10000
#define  DELAY_5MS                           10000

#define  EEPROM_TRY_TIME             3

#define  EEPROM_GENERATE_ACK         0
#define  EEPROM_UNGENERATE_ACK       1


bool8   G_EepromDeviceAck = FALSE;   // EEPROMӦ�������FALSE��ʾ��Ӧ��TRUE��ʾ��Ӧ��




/** void  AT24CxxDelay(uint16  DelayTime)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: DelayTimeΪ��ʱʱ�������0 �� DelayTime �� 65535
*
* ����ֵ˵��: void
*
* ���ܽ���: ��ʱ����
*
* �ؼ���ע������ʱ������������ʱʱ��϶̵ĳ��ϣ�ʱ��ϳ�����ʱӦ�ڶ�ʱ���ж���ʵ��
*
* δ�����:
* 
*/
void  AT24CxxDelay(uint16  DelayTime)
{ 
      uint16  i;  // ѭ������
	
      for (i = 0; i < DelayTime; i++);
}


/**void  I2c_initial()    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void
*
* ���ܽ���: I2C��ʼ��
*
* �ؼ���ע��
*
* δ�����:
* 
*/
void  I2c_initial()
{
      EEPROM_SCL_DIR_OUT;
      EEPROM_SDA_DIR_OUT;
      EEPROM_SDA_L;
      EEPROM_SCL_L;
      AT24CxxDelay(DELAY_6US);
}


/**void  Start_I2c()    //�������ƺͲ����ͷ���ֵ���͡�
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
void  Start_I2c()
{
      I2c_initial();
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_H; 
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_L; 
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_L;   
      AT24CxxDelay(DELAY_6US);
}


/**void  Stop_I2c()    //�������ƺͲ����ͷ���ֵ���͡�
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
void  Stop_I2c()
{
      EEPROM_SDA_DIR_OUT;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_L;  
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;   
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_H;  
      AT24CxxDelay(DELAY_6US);
}

/**bool8 Wait_Ack_I2C()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: bool8��FALSE��ʾ��Ӧ��TRUE��ʾ��Ӧ��
*
* ���ܽ���: I2C�ȴ�Ӧ���źŵ����������豸�ڵھŸ�ʱ�����ڻᷢ���͵�ƽӦ���źţ��Ա��������յ���ַ�����ݡ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  Wait_Ack_I2C()
{
      EEPROM_SDA_H;         
      EEPROM_SDA_DIR_IN;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);
      if (EEPROM_SDAIN == EEPROM_SDAIN_H)
      { 
          EEPROM_SCL_L;
          EEPROM_SDA_DIR_OUT;
          return FALSE;
      }
      else
      {
         EEPROM_SCL_L;
         EEPROM_SDA_DIR_OUT;
         return TRUE;
      }      
}


/**void  SendByte(uchar8  Data)    //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:DataΪ���͵��ֽ����ݣ�0 �� Data �� 255 
*
* ����ֵ˵��: void
*
* ���ܽ���: ����һ���ֽ�
*
* �ؼ���ע����������ʱ��ֻ����SCLΪ�ߵ�ƽʱ��SDA�ϵĵ�ƽΪ��Ч���ݡ�
*           ��д��Ƭ�������������ݳ���ʱ�������SCL���ڵ͵�ƽʱ�������ݵ�ƽ�͵�SDA��
*           Ȼ������SCL����ʱSDA��Ӧ�е�ƽ���䣬��ʱ������SCL���ٽ�����һλ�����ݴ���ֱ����ɡ�
*
* δ�����: 
* 
*/
void  SendByte(uchar8  Data)
{
      uchar8  i;  // ѭ������

      EEPROM_SDA_DIR_OUT;
      EEPROM_SCL_DIR_OUT;
      for (i = 0; i < 8; i++)
      { 
          if ( (Data << i) & 0x80 )
          {
                EEPROM_SDA_H;  
          }
          else 
          { 
                EEPROM_SDA_L;
          }
          AT24CxxDelay(DELAY_6US);   
          EEPROM_SCL_H;         
          AT24CxxDelay(DELAY_6US);       
          EEPROM_SCL_L;
          AT24CxxDelay(DELAY_6US); 
     }
     G_EepromDeviceAck = Wait_Ack_I2C();
}


/**uchar8  RcvByte()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: �� 
*
* ����ֵ˵��: uchar8����Χ0x00 �� ReceivedData �� 0xFF 
*
* ���ܽ���:����һ���ֽ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
uchar8  RcvByte()
{
        uchar8  ReceivedData = 0;   // ���յ������� 
        uchar8  i;   // ѭ������
      
        EEPROM_SDA_H;         
        EEPROM_SDA_DIR_IN;
        for (i = 0; i < 8; i++)
        {
            EEPROM_SCL_L;     
            AT24CxxDelay(DELAY_6US); 
            EEPROM_SCL_H;     
            AT24CxxDelay(DELAY_6US);
            ReceivedData = ReceivedData << 1;
            if (EEPROM_SDAIN == EEPROM_SDAIN_H)
            {
                ReceivedData += 1; 
            }
            AT24CxxDelay(DELAY_6US);
        }
        EEPROM_SCL_L;
        AT24CxxDelay(DELAY_6US);
        return(ReceivedData);
}


/**void Ack_I2C(uchar8  Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  DataΪ�Ƿ�Ӧ���źţ�TRUEʱ������Ӧ��ΪFALSEʱ����Ӧ��
*
* ����ֵ˵��: void
*
* ���ܽ���: I2CӦ��DataΪ1ʱ������ACKӦ��Ϊ0ʱ����ACKӦ��
*
* �ؼ���ע���������ݵ�IC�ڽ��յ�8bit���ݺ��������ݵ�IC�����ض��ĵ͵�ƽ�źţ���ʾ�Ѿ��յ����ݡ�
*
* δ�����: 
* 
*/ 
void  Ack_I2c(uchar8  Data)
{
      EEPROM_SDA_DIR_OUT;
      if (Data)
      {
          EEPROM_SDA_H;  
      }    
      else
      {
          EEPROM_SDA_L;
      }
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);             
      EEPROM_SCL_L;              
      AT24CxxDelay(DELAY_6US);
}


/**bool8  ISendStr(uchar8 SlaveAddress, uint16 SaveAddress, ucha8r  *Str, uchar8 StringLength)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SlaveAddressΪ�ӻ��豸��ַ��1 0 1 0 A2 A1 A0 R/W ��0xA0 �� SlaveAddress �� 0xAE ,�����ֻ��һ��AT24C64�����ַ��Ϊ0xA0
*           SaveAddressΪ���ݴ��洢�ĵ�ַ��0 �� SaveAddress �� 8192
*           StrΪָ���ַ������ݵĵ�ַ�������Ŵ��洢���ݵ����ֽ�
*           StringLengthΪ���洢���ݵ��ֽ�����0 �� StringLength �� 255
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE���洢ʧ�ܷ���FALSE
*
* ���ܽ���: �ڴӻ���ַΪSlaveAddress��AT24CXXָ����ַSaveAddressд��StringLength���ֽ�����
*
* �ؼ���ע��1��AT24C64֧��32�ֽ�ҳдģʽ�����洢��ַ��32��������ʱ�����з�ҳ����
*              n���ֽڷ���ʱ��Ҫ���͵�һ���ֽڵĵ�ַ��Ȼ��һ���Է���n�ֽڵ�д�����ݺ��ٷ���ֹͣλ��
*              д�����������ĵ�ַ�����Լ���оƬ�ڲ���ɡ�
*           2������ҳдʱ�������ݵĴ洢��ַ�ﵽҳ�߽��ַ����ַΪ32����������ʱ����һ���ֽڽ�������ͬһҳ����ʼ��ַ��
*              Ϊ������������ĳ��֣����洢��ַ��32��������ʱ������ֹͣ��������ʱһ����ٴη�����ʼ������д����
*           3��ÿ��д��һ���ֽں���Ҫ��ʱ����Լ2��AT24CxxDelay(DELAY_350US);���ſ��Դ�EEPROM�ж�ȡ�˴�д�������
*              ÿ��д�곬��32���ֽں���Ҫ��ʱ����Լ4��AT24CxxDelay(DELAY_350US);���ſ��Դ�EEPROM�ж�ȡ�˴�д�������
*           4��дһ���ֽ�0.8ms
*           
* δ�����: 
* 
*/ 
bool8  ISendStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)
{
        uchar8  i;  // ѭ������

        Start_I2c();             
        SendByte(SlaveAddress);           
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        SendByte(SaveAddress>>8);            // send the first address
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        SendByte(SaveAddress & 0xFF);        // send second address
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        i = 0;
        do
        {
              SendByte(*Str);           
              if (G_EepromDeviceAck == FALSE)
              {
                  return FALSE;
              }
              Str++;
              i++;
              SaveAddress++;
              if ( ((SaveAddress & 0x1F) == 0) && (i < StringLength) ) //The 64K EEPROM is capable of 32-byte Page Writes
              {
                      Stop_I2c();
                      AT24CxxDelay(DELAY_1800US);    // ������д����32���ֽڣ��е�ַ��ҳʱ��AT24C64֧��32�ֽ�ҳд��
                                                     // ������ַ��ҳʱ��������ҪDELAY_1400US=800 ��Ϊ���ӿɿ��ͣ���ʱ1.8ms						       
                      Start_I2c();             
                      SendByte(SlaveAddress);           
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;
                      }
                      SendByte(SaveAddress>>8);          // send the first address
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;
                      }
                      SendByte(SaveAddress & 0xff);      // send second address
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;	
                      }  
              }
        }
        while(i < StringLength);
        Stop_I2c();              
        return TRUE;
}


/**uchar8  IRcvStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SlaveAddressΪ�ӻ��豸��ַ��1 0 1 0 A2 A1 A0 R/W, 0xA0 �� SlaveAddress �� 0xAE ,�����ֻ��һ��AT24C64�����ַ��Ϊ0xA0
*           SaveAddressΪ���ݴ洢�ĵ�ַ��0 �� SaveAddress �� 8192
*           StrΪָ���ַ������ݵĵ�ַ�������������ȡ���ݵ����ֽ�
*           StringLengthΪ����ȡ���ݵ��ֽ�����0 �� StringLength �� 255
*
* ����ֵ˵��: uchar8����ȡ�ɹ�����TRUE����ȡʧ�ܷ���FALSE
*
* ���ܽ���: �ڴӻ���ַΪSlaveAddress��AT24CXXָ����ַSaveAddress��ȡStringLength���ֽ�����
*
* �ؼ���ע: 1��������ȡ����ʱ��ÿ��ȡһ���ֽڣ�������ӦоƬһ���͵�ƽ��ACKӦ��
*              ����ȡ�����һ���ֽ�ʱ��������Ӧ��
*           2����ȡһ���ֽ�����ʱ��ʱ1.2ms
*
* δ�����: 
* 
*/ 
uchar8  IRcvStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)
{
        uchar8  i;  // ѭ������

        Start_I2c();            
        SendByte(SlaveAddress);        
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        SendByte(SaveAddress>>8);          //send first address 
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        SendByte(SaveAddress & 0xFF);     //send second address    
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;  
        } 
        Start_I2c();
        SendByte(SlaveAddress + 1);
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        for (i = 0; i < StringLength - 1; i++)
        {
            *Str = RcvByte();         
            Ack_I2c(EEPROM_GENERATE_ACK);         
            Str++;
        }
        *Str = RcvByte();
        Ack_I2c(EEPROM_UNGENERATE_ACK);       
        Stop_I2c();                  
        return TRUE;
}



/**void  WriteEEPChar(uint16 SaveAddress, uchar8 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255 
*
* ����ֵ˵��: void
*
* ���ܽ���: дһ���ֽ��ַ�������Data��EEProm��SaveAddress��ַ
*
* �ؼ���ע:
*
* δ�����:
* 
*/ 
void  WriteEEPChar(uint16 SaveAddress, uchar8 Data)
{
      ISendStr(EEPROM_DEVICE_ADDRESS, SaveAddress, &Data, CHAR_BYTENUM);	   
}


/**void ReadByte(uint16 SaveAddress, uchar8 * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: void
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�һ���ֽ��ַ������ݣ����ڵ�ַData��
*
* �ؼ���ע:
*
* δ�����:
* 
*/ 
void  ReadEEPChar(uint16 SaveAddress, uchar8 * Data)
{  
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, Data, CHAR_BYTENUM);   
}


/**bool8 SaveChar(uint16 SaveAddress, uchar8 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE���洢ʧ�ܷ���FALSE

* ���ܽ���: �����ַ�������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����SUCCESS�����򷵻�FAIL
*
* �ؼ���ע: ���һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*           ִ��һ�θú���Լ4ms
*
* δ�����:
* 
*/ 
bool8  SaveChar(uint16 SaveAddress, uchar8 Data)
{
        uchar8 EEPTemp;  // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
        uchar8 i;        // ѭ������

        for (i = 0; i < EEPROM_TRY_TIME; i++)
        {	
              WriteEEPChar(SaveAddress, Data);   	     
              AT24CxxDelay(DELAY_5MS);  // ÿ��д�����ݺ�����д����ʱ������ֹͣ����󣬻����һ���ڲ�д���ڣ��ڲ�д����(�ֽ�д��ҳд)���5ms
                                           // �����Ҫ��ʱһ����ٶ�ȡ
                                                                       // The write cycle time tWR is the time from a valid stop condition 
                                       // of a write sequence to the end of the internal clear/write cycle.
              ReadEEPChar(SaveAddress, &EEPTemp);
              if (EEPTemp == Data) 
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);  // ��¼�¼����ϴ�����������¼ĳ�������100������ͨѶ�������ϴ���������10000�εĹ��ϴ��������ϵ������Ĺ�������
                  return TRUE;
              }
              else
              {		
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**bool8  LoadChar(uint16 SaveAddress, uchar8 * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�һ���ֽ����ݣ����ڵ�ַData��
*
* �ؼ���ע: 1�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*           2��ִ��һ�θú���Լ2.2ms
*
* δ�����: 
* 
*/ 
bool8  LoadChar(uint16 SaveAddress, uchar8 *Data)
{
        uchar8 EEPTemp; // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
        uchar8 i;       // ѭ������	

        for (i = 0;i < EEPROM_TRY_TIME;i++)
        {	
              ReadEEPChar(SaveAddress, Data);
              ReadEEPChar(SaveAddress, &EEPTemp);
              if (EEPTemp == *Data) 
              {
//		   RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                 return TRUE;
              }
              else
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**void  WriteEEPInt(uint16 SaveAddress,uint16 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 65535  
*
* ����ֵ˵��: void
*
* ���ܽ���: д��������Data��EEProm�����ֽڴ洢��EEProm�ĵ�ַSaveAddress�У���ռSaveAddress��SaveAddress+1�����ֽڵ�ַ
*
* �ؼ���ע:
*
* δ�����:
* 
*/ 
void  WriteEEPInt(uint16 SaveAddress,uint16 Data)
{
      uchar8 * ByteAddress;  // ָ��Data���ֽ����ݵĵ�ָ��
    
      ByteAddress = (uchar8*)&Data;
      ISendStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, INT_BYTENUM);
}

/**void  ReadEEPInt(uint16 SaveAddress,uint16 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 65535  
*
* ����ֵ˵��: void
*
* ���ܽ���: ��EEProm�ĵ�ַSaveAddress~SaveAddress+1�ж������ֽ��������ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע:
*
* δ�����:
* 
*/ 
void  ReadEEPInt(uint16 SaveAddress, uint16 * Data)
{
      uchar8 * ByteAddress;  // ָ��Data���ֽ����ݵĵ�ָ��

      ByteAddress = (uchar8*)Data;
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, INT_BYTENUM);
}


/**bool8  SaveInt(uint16 SaveAddress,uint16 Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪ���洢�����ݣ�0 �� Data �� 65535 
*
* ����ֵ˵��: bool8 ���洢�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ������������Data��EEProm�ĵ�ַSaveAddress~SaveAddress+1�У�,������ٶ������������ֵ�ͱ����ֵһ�£�����SUCCESS�����򷵻�FAIL
*
* �ؼ���ע: ���һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
bool8  SaveInt(uint16 SaveAddress, uint16 Data)
{
      uint16 EEPTemp;  // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
      uchar8 i;       // ѭ������

      for (i = 0; i < EEPROM_TRY_TIME; i++)
      {	
            WriteEEPInt(SaveAddress,Data);
            AT24CxxDelay(DELAY_5MS);  // ÿ��д�����ݺ�����д����ʱ������ֹͣ����󣬻����һ���ڲ�д���ڣ��ڲ�д����(�ֽ�д��ҳд)���5ms
                                         // �����Ҫ��ʱһ����ٶ�ȡ
                                                                     // The write cycle time tWR is the time from a valid stop condition 
                                     // of a write sequence to the end of the internal clear/write cycle.
            ReadEEPInt(SaveAddress, &EEPTemp);
            if (EEPTemp == Data)
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {			
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
      }
      return FALSE;
}

/**bool8  LoadInt(uint16 SaveAddress,uint16 * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: bool8, ��ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+1�ж������ֽ��������ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע: ���һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
bool8  LoadInt(uint16 SaveAddress,  uint16 * Data)
{
      uint16 EEPTemp;  // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
      uchar8 i;       // ѭ������	

      for (i = 0; i < EEPROM_TRY_TIME; i++)
      {	
            ReadEEPInt(SaveAddress, Data);
            ReadEEPInt(SaveAddress, &EEPTemp);
            if (EEPTemp == *Data)
            { 
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
      }
      return FALSE;
}


/**void  WriteEEPFloat(uint16 SaveAddress, float  Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪ���洢�����ݣ�3.4e-38 �� Data �� 3.4e38 
*
* ����ֵ˵��:void
*
* ���ܽ���: д����������Data��EEProm�����ֽڴ洢��EEProm�ĵ�ַSaveAddress�У���ռSaveAddress~SaveAddress+3�ĸ��ֽڵ�ַ
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  WriteEEPFloat(uint16 SaveAddress, float Data)
{
      uchar8 * ByteAddress;  // ָ��Data���ֽ����ݵĵ�ָ��
    
      ByteAddress = (uchar8*)&Data;
      ISendStr(EEPROM_DEVICE_ADDRESS,SaveAddress,ByteAddress,FLOAT_BYTENUM);	
}


/**void ReadEEPFloat (uint16 SaveAddress, float * Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪָ�򸡵������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ� 
*  
* ����ֵ˵��: void
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+3�ж��ĸ��ֽ����ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  ReadEEPFloat (uint16 SaveAddress, float * Data)
{
      uchar8 * ByteAddress;  // ָ��Data���ֽ����ݵĵ�ָ��
	
      ByteAddress = (uchar8*)Data;
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, FLOAT_BYTENUM);	
}


/**bool8  SaveFloat(uint16 SaveAddress, float  Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪ���洢�����ݣ�3.4e-38 �� Data �� 3.4e38 
*
* ����ֵ˵��: bool8, д��ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: д����������Data��EEProm�����ֽڴ洢��EEProm�ĵ�ַSaveAddress�У���ռSaveAddress~SaveAddress+3�ĸ��ֽڵ�ַ
*
* �ؼ���ע�����һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
bool8  SaveFloat(uint16 SaveAddress, float Data)
{
        float EEPTemp;   // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
        uchar8 i; // ѭ������

        for (i = 0; i < EEPROM_TRY_TIME; i++)
        {		
              WriteEEPFloat(SaveAddress,Data);
              AT24CxxDelay(DELAY_5MS);  // ÿ��д�����ݺ�����д����ʱ������ֹͣ����󣬻����һ���ڲ�д���ڣ��ڲ�д����(�ֽ�д��ҳд)���5ms
                                           // �����Ҫ��ʱһ����ٶ�ȡ
                                           // The write cycle time tWR is the time from a valid stop condition 
                                           // of a write sequence to the end of the internal clear/write cycle.
              ReadEEPFloat(SaveAddress, &EEPTemp);
              if (EEPTemp == Data) 
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                  return TRUE;
              }
              else
              {			
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**bool8 ReadEEPFloat (uint16 SaveAddress, float * Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪָ�򸡵������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ� 
*  
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+3�ж��ĸ��ֽ����ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
bool8  LoadFloat(uint16 SaveAddress, float * Data)
{
       float EEPTemp;    // ��ʱ���������ڴ�Ŵ�AT24CXX�ж���������
       uchar8 i;  // ѭ������	

       for (i = 0; i < EEPROM_TRY_TIME; i++)
       {
            ReadEEPFloat(SaveAddress,Data);	
            ReadEEPFloat(SaveAddress,&EEPTemp);
            if (EEPTemp == *Data)
            {
//			    RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
       }
       return FALSE;
}


/**bool8  LoadCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ���ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength���ֽ����ݣ����ڵ�ַData~Data+ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  LoadCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadChar(SaveAddress + i, (Data + i)) != TRUE)
            {
                return FALSE;	
            } 
       }
       return TRUE;
}


/**bool8  LoadIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ����������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength���������ݣ����ڵ�ַData~Data+2*ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  LoadIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadInt(SaveAddress + i*INT_BYTENUM, (Data + i))!=TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  LoadFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ�ĸ���������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8����ȡ�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength�����������ݣ����ڵ�ַData~Data+4*ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  LoadFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadFloat(SaveAddress+i*FLOAT_BYTENUM, (Data+i))!=TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  SaveCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char���洢�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: �����ַ�������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  SaveCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveChar(SaveAddress + i, *(Data + i)) != TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8 SaveIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ������������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  SaveIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveInt(SaveAddress + i*INT_BYTENUM, *(Data+i)) != TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  SaveIntArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: bool8���洢�ɹ�����TRUE��ʧ�ܷ���FALSE
*
* ���ܽ���: ���渡��������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
bool8  SaveFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)
{
       uint16 i;  // ѭ������
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveFloat(SaveAddress + i * FLOAT_BYTENUM, *(Data + i)) != TRUE)
            {
                return FALSE;
            }
            else
            {
              ;
            }
       }
       return TRUE;
}


