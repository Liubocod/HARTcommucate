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



/****************************eeprom.h�ļ�˵��********************************************/
//���ļ�Ϊeeprom.c�ļ�������һЩ�궨�壬�Լ��Կɱ������ļ����õı����ͺ�����������
/****************************************************************************************/


#define EEPROM_5MS      5000
#define EEP_TRY_TIME 	3
#define OK 				1
#define FAIL 			0

#define BYTE_NUM_1      1
#define BYTE_NUM_2      2
#define BYTE_NUM_4      4



unsigned char LoadChar(unsigned int SaveAddress, unsigned char* Data);
unsigned char SaveChar(unsigned int SaveAaddress, unsigned char  Data);
unsigned char SaveCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength);
unsigned char  LoadCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength);


void  Delay5ms(unsigned int DelayTime);


