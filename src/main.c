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

#include "HardwareInit.c"

const unsigned char CopyrightCheck[] = {"All datas in this eeprom,flash or mcu is the important property of CONNETECH(BeijingRuiDaYiBiaoYouXianGongSi).The copyrights belong to connetech (BeijingRuiDaYiBiaoYouXianGongSi),and All rights reserved.To read out or copy these datas in eeprom,flash or mcu without permission of CONNETECH is Copyright infringement."};

const unsigned char  CompanyNameCheck[]={"CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)"};

const unsigned char DeclarationCheck[] = {"The All copyrights belong to connetech (BeijingRuiDaYiBiaoYouXianGongSi)"};
#define EEPROM_FLASH_ERASE_FLAG         0

#if (EEPROM_FLASH_ERASE_FLAG == 1)
  #define IS_SINGLE_WRITE         0xA5
#else
  #define IS_SINGLE_WRITE         0x5A
#endif

/**
 //�������ƺͲ����ͷ���ֵ���͡�
void PatchHandle()
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
������������������Ҫϵͳ��ѯ����Ĳ�����
*
* �ؼ���ע��
* - 

  
* δ�����:

  �������������������������Ҫ���䡣

*/
void PatchHandle()
{
  InitialPageRangeHandle();
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void PageRefreshModule()
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
ҳ��ˢ�´���ģ�飬��ʱˢ�»�ϵͳˢ�´���
*
* �ؼ���ע��
* - 

  
* δ�����:

  �������������������������Ҫ���䡣

*/
void PageRefreshModule()
{
  //�ظ����������ˢ�½���ʱ�䴦��ģ��
  if((G_WarningTimeStamp == 0)&&(MENU_PageRefreshIntervalHandle() == TRUE))
  {
    MENU_PageShow();
  }
  else
  {
    //ҳ��ˢ��
    SystemPageRefresh();
  }
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void EEP_ParamHandle()
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
���α�̴���������������������дFLASH��EEPROM��
*
* �ؼ���ע��
* - 

  
* δ�����:

  �������������������������Ҫ���䡣

*/
void SingleProgramHandle()
{
  uchar PowerUpFlag = 0,language = 0;
  LoadChar(1,&PowerUpFlag);
  if(PowerUpFlag != IS_SINGLE_WRITE)
  {
    PowerUpFlag = IS_SINGLE_WRITE;
    SaveChar(1,PowerUpFlag);
    SaveChar(0,CHINESE);
#ifdef ENABLE_FLASH_WRITE
    FlashMenuWriteModule(FALSE);
#endif
  }
  else
  {
#ifdef ENABLE_FLASH_WRITE
    FlashMenuWriteModule(TRUE);
#endif
    //FlashMenuWriteModule(TRUE);
    LoadChar(0,&language);
    MENU_LanguageSetHandle((LanguageTypeDef)language);
  }
}
void	main()
{
  HardwareInit();
  LcdDisplayInit();
  //eeromд�����ܽţ���Ҫ���ݼ���ģ��ķ�������д����
  EEPROM_WP_OUT;
  EEPROM_WP_L;
  SingleProgramHandle();
  MENU_ClearLcdScreen();
  MENU_PageShow();
  HART_InfoInit();


  InitAD(); 
  G_SampleEndFlag = TRUE;
  G_VariableProtect.LoadLock = FALSE;
  //�������Ǳ�˵����棬���³�ֵ���㡣
  HART_CableLengthReset();
  
  G_WarningTimeStamp = 2000;
  MENU_PageShow();
  HART_ReceiveSendEN(RECEIVE_START);
  while(1)
  {
  //������  
  SystemKeyHandle();
  //ҳ����´���
  PageRefreshModule();
  //HARTͨ�Ŵ�����
  HART_CommunicateHandle();
  //��ʱˢ��
  SystemTimingRefreshHandle();
  //BATTERY Module
  SystemBatteryModule();
  //����ɨ�账��
  KeyScanHandleModule();
  //����
  PatchHandle();
  //����ģ�鴦����
  COPY_EncryptionHandle();
  } 
}