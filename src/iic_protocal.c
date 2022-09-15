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



/****************************iic_protocal.c�ļ�˵��***************************/
//���ļ�Ϊ�洢оƬAT24CXX�ĵײ���������
/*****************************************************************************/



#include "iic_protocal.h"




unsigned char Ack;  //Ӧ���־λ��0��ʾ��Ӧ��1��ʾ��Ӧ��




/** void  Delay(unsigned int Time)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:TimeΪ��ʱʱ�������0 �� Time �� 65535
*
* ����ֵ˵��: void
*
* ���ܽ���: ��ʱ����
*
* �ؼ���ע��TimeΪ1ʱ��ʱԼ2.25us
*
* δ�����:
* 
*/
void  Delay(unsigned int Time)
{ 
	unsigned int i;
	
    for (i = 0;i < Time;i++);
}



/********************************����Ϊ�洢оƬAT24CXX�ײ���������**********************************/

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
	I2C_SCLOUT;
	I2C_SDAOUT;
  	I2C_SDA_0;
	I2C_SCL_0;
	Delay(DELAYSTAY);
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
	Delay(DELAYSTAY);
	I2C_SDA_1; 
	Delay(DELAYSTAY);
	I2C_SCL_1;
	Delay(DELAY_VALUE_10);
    I2C_SDA_0; 
    Delay(DELAYUP);
    I2C_SCL_0;   
    Delay(DELAYSTAY);
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
  I2C_SDAOUT;
  Delay(DELAYSTAY);
  I2C_SDA_0;  
  Delay(DELAYSTAY);
  I2C_SCL_1;   
  Delay(DELAY_VALUE_10);
  I2C_SDA_1;  
  Delay(DELAYSTAY);
}

/**unsigned char Wait_Ack_I2C()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: unsigned char��0����Ӧ��ʧ�ܣ�1����Ӧ��ɹ�
*
* ���ܽ���: I2C�ȴ�Ӧ���źŵ����������豸�ڵھŸ�ʱ�����ڻᷢ���͵�ƽӦ���źţ��Ա��������յ���ַ�����ݡ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char Wait_Ack_I2C()
{
    I2C_SDA_1;         
    I2C_SDAIN;
    Delay(DELAYSTAY);
    I2C_SCL_1;
    Delay(DELAY_VALUE_16);
    if (I2C_DATAIN == I2C_DATAIN_1)
    {
      I2C_SCL_0;
      I2C_SDAOUT;
      return I2C_ACK_FAIL;
    }
    else
    {
      I2C_SCL_0;
      I2C_SDAOUT;
      return I2C_ACK_SUCCESS;
    }      
}


/**void  SendByte(unsigned char Data)    //�������ƺͲ����ͷ���ֵ���͡�
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
void  SendByte(unsigned char Data)
{
  unsigned char BitCnt;
  
  I2C_SDAOUT;
  I2C_SCLOUT;
  for (BitCnt = 0;BitCnt < 8;BitCnt++)
  { 
    if ((Data<<BitCnt)&0x80)
	    I2C_SDA_1;  
    else  
	    I2C_SDA_0;
    Delay(DELAYUP);   
    I2C_SCL_1;         
    Delay(DELAYSTAY);       
    I2C_SCL_0;
    Delay(DELAYSTAY); 
  }
  Ack =  Wait_Ack_I2C();
}


/**unsigned char RcvByte()   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: �� 
*
* ����ֵ˵��: unsigned char����Χ0 �� Retc �� 255 
*
* ���ܽ���:����һ���ֽ�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char  RcvByte()
{
  unsigned char  Retc = 0;
  unsigned char  BitCnt; 
	  
  I2C_SDA_1;         
  I2C_SDAIN;
  for (BitCnt = 0;BitCnt < 8;BitCnt++)
  {
    I2C_SCL_0;     
    Delay(DELAYSTAY); 
    I2C_SCL_1;     
    Delay(DELAYSTAY);
    Retc = Retc<<1;
    if (I2C_DATAIN == I2C_DATAIN_1)
	    Retc += 1; 
    Delay(DELAYSTAY);
  }
  I2C_SCL_0;
  Delay(DELAYSTAY);
  return(Retc);
}


/**void Ack_I2C(unsigned char  Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  DataΪѡ���źţ�0 �� Data �� 1��DataΪ1ʱ������ACKӦ��Ϊ0ʱ����ACKӦ��
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
void  Ack_I2c(unsigned char  Data)
{
  I2C_SDAOUT;
  if (Data)
      I2C_SDA_1;      
  else
      I2C_SDA_0;
  Delay(DELAYSTAY);
  I2C_SCL_1;
  Delay(DELAYSTAY);             
  I2C_SCL_0;              
  Delay(DELAYSTAY);
}


/**unsigned char  ISendStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SlaveAddressΪ�ӻ��豸��ַ��1 0 1 0 A2 A1 A0 R/W ��0xA0 �� SlaveAddress �� 0xAE ,�����ֻ��һ��AT24C64�����ַ��Ϊ0xA0
*           SaveAddressΪ���ݴ��洢�ĵ�ַ��0 �� SaveAddress �� 8192
*           StrΪָ���ַ������ݵĵ�ַ�������Ŵ��洢���ݵ����ֽ�
*           StringLengthΪ���洢���ݵ��ֽ�����0 �� StringLength �� 255
*
* ����ֵ˵��: unsigned char���洢�ɹ�����1���洢ʧ�ܷ���0
*
* ���ܽ���: �ڴӻ���ַΪSlaveAddress��AT24CXXָ����ַSaveAddressд��StringLength���ֽ�����
*
* �ؼ���ע��AT24C64֧��32�ֽ�ҳдģʽ�����洢��ַ��31��������ʱ�����з�ҳ����
*           n���ֽڷ���ʱ��Ҫ���͵�һ���ֽڵĵ�ַ��Ȼ��һ���Է���n�ֽڵ�д�����ݺ��ٷ���ֹͣλ��
*           д�����������ĵ�ַ�����Լ���оƬ�ڲ���ɡ�
*
* δ�����:
* 
*/ 
unsigned char  ISendStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)
{
	unsigned char  i;
	
	Start_I2c();             
	SendByte(SlaveAddress);           
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	SendByte(SaveAddress>>8);          // send the first address
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	SendByte(SaveAddress & 0xff);        // send second address
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	i = 0;
	do
	{
		SendByte(*Str);           
		if (Ack == I2C_ACK_FAIL)
	        return FAIL;
		Str++;
		i++;
		SaveAddress++;
		if (((SaveAddress&0x1F) == 0)&&(i< StringLength)) //The 64K EEPROM is capable of 32-byte Page Writes
		{
			Stop_I2c();
			Delay(DELAYSTAYL);
  			Delay(DELAYSTAYL);             
			Delay(DELAYSTAYL);
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
			Start_I2c();             
			SendByte(SlaveAddress);           
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;
			SendByte(SaveAddress>>8);          // send the first address
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;
			SendByte(SaveAddress & 0xff);      // send second address
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;			
		}
	}
	while(i< StringLength);
	Stop_I2c();              
	return OK;
}


/**unsigned char IRcvStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SlaveAddressΪ�ӻ��豸��ַ��1 0 1 0 A2 A1 A0 R/W, 0xA0 �� SlaveAddress �� 0xAE ,�����ֻ��һ��AT24C64�����ַ��Ϊ0xA0
*           SaveAddressΪ���ݴ洢�ĵ�ַ��0 �� SaveAddress �� 8192
*           StrΪָ���ַ������ݵĵ�ַ�������������ȡ���ݵ����ֽ�
*           StringLengthΪ����ȡ���ݵ��ֽ�����0 �� StringLength �� 255
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����1����ȡʧ�ܷ���0
*
* ���ܽ���: �ڴӻ���ַΪSlaveAddress��AT24CXXָ����ַSaveAddress��ȡStringLength���ֽ�����
*
* �ؼ���ע��������ȡ����ʱ��ÿ��ȡһ���ֽڣ�������ӦоƬһ���͵�ƽ��ACKӦ��
*           ����ȡ�����һ���ֽ�ʱ��������Ӧ��
*
* δ�����:
* 
*/ 
unsigned char  IRcvStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)
{
  unsigned char  i;
  
  Start_I2c();            
  SendByte(SlaveAddress);        
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  SendByte(SaveAddress>>8);          //send first address 
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  SendByte(SaveAddress & 0xff);        
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;       //sebd second address
  Start_I2c();
  SendByte(SlaveAddress + 1);
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  for (i=0;i < StringLength - 1;i++)
  {
    *Str = RcvByte();         
    Ack_I2c(I2C_GENERATE_ACK);         
    Str++;
  }
  *Str = RcvByte();
  Ack_I2c(I2C_UNGENERATE_ACK);       
  Stop_I2c();                  
  return OK;
}


