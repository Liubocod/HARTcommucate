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



/****************************eeprom.c�ļ�˵��*************************************/
//���ļ�Ϊ����iic_protocal.c�ļ��еĵײ������ļ�����д���йز�����д�ĺ���������
// 1�������ַ��Ͳ����Ĵ洢��������ȡ����
// 2�������������ݵĴ洢��������ȡ����
// 3���������������ݵĴ洢��������ȡ����
// 4���ַ�����Ĵ洢��������ȡ����
// 5����������Ĵ洢��������ȡ����
// 6������������Ĵ洢��������ȡ����
//���Ϻ����ɱ������ļ�����
/********************************************************************************/

/***************************************************************************
���ļ���Ҫ��eeprom�Ķ�д���������ṩ��eeprom��д��������ĺ���



******************************************************************************/

/**********************eeprom�ĵײ����������ϵ************************************


ISendStr  IRcvStr  �ֱ��õ�Ƭ������ͨ����ģ��iic�ķ���һ���ַ����ͽ���һ���ַ����Ĺ��ܡ�

Ȼ������������������ ʵ���� ReadEEPChar WriteEEPChar �Ⱥ��������������εĺ������Ƕ�дһ�εľ������͵ı�������û�н���У��ͼ�顣

Ȼ���һ���� read��write���� ������ LoadChar ��SaveChar�Ⱥ�����Load��Save�о��ǽ���У���ˡ� ������Ҳֻ�Ǿ��м��Ķ�д�������������͡�

�ڶ�д�����������͵�Load  �� Write  �����ϡ���һ��д�˸���������Load��Write



***********************************************************/





/**********************�������ĺʹ洢�ķ�ʱ�����߼�************************************

Ϊ���еı������ṩ��һ����־λ������FlagOfChange_PVUnit ���ڸ����˱���֮��Ҳ��������־λ�����ġ��ⲿ��һ����ͨѶ������ɡ�
Ȼ��ϵͳ��ʱ���ˣ��Ͷ������־λ����飬���ֱ�־λ�����ģ���ô�ͰѶ�Ӧ�ı������棬Ȼ��������־λ���ָ���

���Ĳ����뱣������Ƿ�ʱ�����ġ���Ҫ��ԭ���Ǵ洢eeprom���ٶ�̫��������ŵ��ж����������ᵢ��ܶ��ʱ�䡣
���Ĳ���֮������һ���ò�����Ӧ�ı�־λ��Ȼ��洢������������־λ���д洢������洢�������ã��ָ��������ã��������������ȵȡ�
�ͺ����Ǹ��Ĳ����ĳ�����洢�����ĳ�����һ��ָ����ָ��������ڸ��ٴ洢�����ĳ�����κ����顣

�������Ƿ���ĵı�־λ(��Ӧ���Ĳ����������ݹ�����ָ��)�����Ҷ���Ӧ�Ĳ������д洢���߽������������ĺ�������Save_All_Para() 
��Ϊ���������߼��ϣ��洢�ϣ��ṹ�� ���źܴ�Ĳ�ͬ����Щ��һ��char ��Щ�����char ����int�ȵȡ�
��������Ϊÿһ��������������������������д��

***********************************************************/







#include "eeprom.h"
#include "iic_protocal.h"







/** void  Delay5ms(unsigned int DelayTime)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:DelayTimeΪ��ʱʱ�������0 �� DelayTime �� 65535
*
* ����ֵ˵��: void
*
* ���ܽ���: ��ʱ����
*
* �ؼ���ע��for mem write  , the at24c64 has this problem need 5ms to save data into eeprom
*
* δ�����:
* 
*/
void  Delay5ms(unsigned int DelayTime)   
{
	unsigned int i;
	
    for (i = 0;i < DelayTime;i++)
  	{;}
}


/**void WriteEEPChar(unsigned int SaveAddress,unsigned char Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255 
*
* ����ֵ˵��: void
*
* ���ܽ���:дһ���ֽ��ַ�������Data��EEProm��SaveAddress��ַ
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  WriteEEPChar(unsigned int SaveAddress, unsigned char Data)
{
	ISendStr(I2C_ADDRESS,SaveAddress,&Data,BYTE_NUM_1);
	Delay5ms(EEPROM_5MS);
}


/**void ReadByte(unsigned int SaveAddress, unsigned char * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: void
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�һ���ֽ��ַ������ݣ����ڵ�ַData��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  ReadEEPChar(unsigned int SaveAddress, unsigned char * Data)
{
	IRcvStr(I2C_ADDRESS,SaveAddress,Data,BYTE_NUM_1);
}


/**unsigned char SaveChar(unsigned int SaveAddress, unsigned char Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*
* ����ֵ˵��: unsigned char���洢�ɹ�����OK���洢ʧ�ܷ���FAIL

* ���ܽ���: �����ַ�������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����SUCCESS�����򷵻�FAIL
*
* �ؼ���ע�����һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char  SaveChar(unsigned int SaveAddress, unsigned char  Data)
{
	unsigned char EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		WriteEEPChar(SaveAddress, Data);
		ReadEEPChar(SaveAddress,&EEPTemp);
		if (EEPTemp == Data) 
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char LoadChar(unsigned int SaveAddress, unsigned char * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�һ���ֽ����ݣ����ڵ�ַData��
*
* �ؼ���ע�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char  LoadChar(unsigned int SaveAddress, unsigned char* Data)
{
	unsigned char EEPTemp;
	unsigned char i;
	
	ReadEEPChar(SaveAddress,Data);
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		ReadEEPChar(SaveAddress,&EEPTemp);
		if(EEPTemp == *Data) 
		{
		   //RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		   return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**void  WriteEEPInt(unsigned int SaveAddress,unsigned int Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 65535  
*
* ����ֵ˵��: void
*
* ���ܽ���:д��������Data��EEProm�����ֽڴ洢��EEProm�ĵ�ַSaveAddress�У���ռSaveAddress��SaveAddress+1�����ֽڵ�ַ
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  WriteEEPInt(unsigned int SaveAddress,unsigned int Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress = (unsigned char*)&Data;
	ISendStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_2);
	Delay5ms(EEPROM_5MS);
}

/**void  ReadEEPInt(unsigned int SaveAddress,unsigned int Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 65535  
*
* ����ֵ˵��: void
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+1�ж������ֽ��������ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  ReadEEPInt(unsigned int SaveAddress, unsigned int * Data)
{
	unsigned char * ByteAddress;

	ByteAddress = (unsigned char*)Data;
	IRcvStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_2);
}


/**unsigned char SaveInt(unsigned int SaveAddress,unsigned int  Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪ���洢�����ݣ�0 �� Data �� 65535 
*
* ����ֵ˵��: unsigned char���洢�ɹ�����OK���洢ʧ�ܷ���FAIL
*
* ���ܽ���:������������Data��EEProm�ĵ�ַSaveAddress~SaveAddress+1�У�,������ٶ������������ֵ�ͱ����ֵһ�£�����SUCCESS�����򷵻�FAIL
*
* �ؼ���ע�����һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char SaveInt(unsigned int SaveAddress, unsigned int  Data)
{
	unsigned int EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		WriteEEPInt(SaveAddress,Data);
		ReadEEPInt(SaveAddress, &EEPTemp);
		if (EEPTemp == Data)
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}

/**unsigned char LoadInt(unsigned int SaveAddress,unsigned int * Data)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*
* ����ֵ˵��: unsigned char,��ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+1�ж������ֽ��������ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char  LoadInt(unsigned int SaveAddress,  unsigned int * Data)
{
	unsigned int EEPTemp;
	unsigned char i;
	
	ReadEEPInt(SaveAddress,Data);
	for (i=0;i<EEP_TRY_TIME;i++)
	{	
		ReadEEPInt(SaveAddress,&EEPTemp);
		if (EEPTemp == *Data)
		{ 
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**void  WriteEEPFloat(unsigned int SaveAddress, float  Data)  //�������ƺͲ����ͷ���ֵ���͡�
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
void  WriteEEPFloat(unsigned int SaveAddress, float Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress = (unsigned char*)&Data;
	ISendStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_4);
	Delay5ms(EEPROM_5MS);
}


/**void ReadEEPFloat (unsigned int SaveAddress, float * Data)  //�������ƺͲ����ͷ���ֵ���͡�
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
void  ReadEEPFloat (unsigned int SaveAddress, float * Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress=(unsigned char*)Data;
	IRcvStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_4);	
}


/**unsigned char SaveFloat(unsigned int SaveAddress, float  Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪ���洢�����ݣ�3.4e-38 �� Data �� 3.4e38 
*
* ����ֵ˵��: unsigned char,д��ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���: д����������Data��EEProm�����ֽڴ洢��EEProm�ĵ�ַSaveAddress�У���ռSaveAddress~SaveAddress+3�ĸ��ֽڵ�ַ
*
* �ؼ���ע�����һ�δ洢���ɹ������ٴ洢һ�Σ����洢3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char SaveFloat(unsigned int SaveAddress, float Data)
{
	float EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{		
		WriteEEPFloat(SaveAddress,Data);
		ReadEEPFloat(SaveAddress, &EEPTemp);
		if (EEPTemp == Data) 
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char ReadEEPFloat (unsigned int SaveAddress, float * Data)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*            DataΪָ�򸡵������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ� 
*  
* ����ֵ˵��: unsigned char����ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���:��EEProm�ĵ�ַSaveAddress~SaveAddress+3�ж��ĸ��ֽ����ݣ��������Data��ͷ�ĵ�ַ��
*
* �ؼ���ע�����һ�ζ�ȡ���ɹ������ٶ�ȡһ�Σ�����ȡ3�ξ����ɹ����򷵻�0��FAIL��
*
* δ�����:
* 
*/ 
unsigned char LoadFloat(unsigned int SaveAddress, float * Data)
{
	float EEPTemp;
	unsigned char i;
	
	ReadEEPFloat(SaveAddress,Data);
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		ReadEEPFloat(SaveAddress,&EEPTemp);
		if (EEPTemp == *Data)
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char  LoadCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ���ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength���ֽ����ݣ����ڵ�ַData~Data+ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char  LoadCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadChar(SaveAddress+i, (Data+i)) != OK)
			return FAIL;		
	}
	return OK;
}


/**unsigned char  LoadIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ����������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength���������ݣ����ڵ�ַData~Data+2*ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char  LoadIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)
{
	unsigned int i;

	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadInt(SaveAddress+i*BYTE_NUM_2, (Data+i))!=OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char  LoadFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪָ���ַ������ݵ�ָ�룬�����Ŷ�ȡ�������������ֽ�  
*           ArrayLengthΪ����ȡ�ĸ���������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char����ȡ�ɹ�����OK��ʧ�ܷ���FAIL
*
* ���ܽ���: ��EEProm��SaveAddress��ַ�ж�ArrayLength�����������ݣ����ڵ�ַData~Data+4*ArrayLength-1��
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char LoadFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)
{
	int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadFloat(SaveAddress+i*BYTE_NUM_4, (Data+i))!=OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char���洢�ɹ�����OK���洢ʧ�ܷ���FAIL
*
* ���ܽ���: �����ַ�������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char SaveCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveChar(SaveAddress+i, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char���洢�ɹ�����OK���洢ʧ�ܷ���FAIL
*
* ���ܽ���: ������������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char SaveIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveInt(SaveAddress + i*BYTE_NUM_2, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveIntArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)   //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: SaveAddressΪ�洢��ַ��0 �� SaveAddress �� 8191
*           DataΪ���洢�����ݣ�0 �� Data �� 255   
*           ArrayLengthΪ��������ַ�������ĳ��ȣ�0 �� ArrayLength �� 65535
*
* ����ֵ˵��: unsigned char���洢�ɹ�����OK���洢ʧ�ܷ���FAIL
*
* ���ܽ���: ���渡��������Data��EEProm��SaveAddress��ַ��������ٶ������������ֵ�ͱ����ֵһ�£�����OK�����򷵻�FAIL
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
unsigned char SaveFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveFloat(SaveAddress + i*BYTE_NUM_4, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}




