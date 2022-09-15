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
 //函数名称和参量和返回值类型。
void PatchHandle()
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
补丁处理函数，处理需要系统轮询处理的补丁。
*
* 关键备注：
* - 

  
* 未来提高:

  数据输入界面闪动的输入光标需要补充。

*/
void PatchHandle()
{
  InitialPageRangeHandle();
}
/**
 //函数名称和参量和返回值类型。
void PageRefreshModule()
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
页面刷新处理模块，定时刷新或系统刷新处理。
*
* 关键备注：
* - 

  
* 未来提高:

  数据输入界面闪动的输入光标需要补充。

*/
void PageRefreshModule()
{
  //重复发送命令的刷新界面时间处理模块
  if((G_WarningTimeStamp == 0)&&(MENU_PageRefreshIntervalHandle() == TRUE))
  {
    MENU_PageShow();
  }
  else
  {
    //页面刷新
    SystemPageRefresh();
  }
}
/**
 //函数名称和参量和返回值类型。
void EEP_ParamHandle()
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
单次编程处理函数，可以用来单次烧写FLASH和EEPROM。
*
* 关键备注：
* - 

  
* 未来提高:

  数据输入界面闪动的输入光标需要补充。

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
  //eerom写保护管脚，需要根据加密模块的反馈进行写保护
  EEPROM_WP_OUT;
  EEPROM_WP_L;
  SingleProgramHandle();
  MENU_ClearLcdScreen();
  MENU_PageShow();
  HART_InfoInit();


  InitAD(); 
  G_SampleEndFlag = TRUE;
  G_VariableProtect.LoadLock = FALSE;
  //针对锐达仪表菜单界面，将缆长值归零。
  HART_CableLengthReset();
  
  G_WarningTimeStamp = 2000;
  MENU_PageShow();
  HART_ReceiveSendEN(RECEIVE_START);
  while(1)
  {
  //处理按键  
  SystemKeyHandle();
  //页面更新处理
  PageRefreshModule();
  //HART通信处理函数
  HART_CommunicateHandle();
  //定时刷新
  SystemTimingRefreshHandle();
  //BATTERY Module
  SystemBatteryModule();
  //按键扫描处理
  KeyScanHandleModule();
  //补丁
  PatchHandle();
  //加密模块处理函数
  COPY_EncryptionHandle();
  } 
}