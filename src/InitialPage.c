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

#include "InitialPage.h"
bool8 G_IsInitVariable = FALSE;
uchar G_PV_UnitTemp[UCHAR] = {0};
//川仪PDS 5系高低端微调补丁判定
#define IS_CY_PDS6_PATCH_UST       (MENU_CurrentPageNumGet() == CY_PAGE_INDEX_14)\
     &&(MENU_CurrentPageTypeGet() == MENU_BAR)&&(MENU_GetMenuTreeIndex() == CHUAN_YI)
//川仪PDS 8系高低端微调补丁判定
#define IS_CY_PDS7_PATCH_UST       (MENU_CurrentPageNumGet() == CY7_PAGE_INDEX_41)\
     &&(MENU_CurrentPageTypeGet() == MENU_BAR)&&(MENU_GetMenuTreeIndex() == CY_HART7_PDS)

/*
void HART_SuccessRatioHandle(void )
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  成功率计算处理函数，将计算变量清零，然后开启新一轮计算。
*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static void HART_SuccessRatioHandle()
{
  G_SuccessNum = 0;
  G_FailureStatistics = 0;
  G_Denominator = 0;
  //开启成功率计算处理功能
  G_ComPCT_SWITCH = TRUE;
  MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
  MENU_PageTypeSetHandle(DYNAMIC_PAGE);
  MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_102);
}
/*
static void InitialPageVariableInit();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信变量初始化函数，
不同产品需要进行不同的变量初始化，所以可通过本函数分别进行处理。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void InitialPageVariableInit()
{
  uchar i;

  if(IS_CY_PDS6_PATCH_UST || IS_CY_PDS7_PATCH_UST)
  {
    for(i = 0;i < 4;i++)
    {
      G_SIEMENS_UpSnsrTrim[i] = G_PV_USL[i];
      G_SIEMENS_LoSnsrTrim[i] = G_PV_LSL[i];
    }
    G_IsInitVariable = TRUE;
    G_PV_UnitTemp[0] = G_PV_Unit[0];
  }
}
/*
static void InitialPageVariableInit();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信变量初始化函数，
不同产品需要进行不同的变量初始化，所以可通过本函数分别进行处理。
*
* 关键备注：
* - 

  
* 未来提高:




*/
bool8 InitialPageRangeCompare()
{
  uchar i;
  for(i = 0;i < 4;i++)
  {
    if((G_SIEMENS_UpSnsrTrim[i] != G_PV_USL[i])
       ||(G_SIEMENS_LoSnsrTrim[i] != G_PV_LSL[i]))
    {
      return FALSE;
    }
  }
  return TRUE;
}
/*
void HART_DeviceTypeHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  设备类型解析处理函数，根据设备唯一码，区分具体为哪种设备。
    版本界面执行完毕，调用设备类型处理函数进行菜单入口选择
*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static void HART_DeviceTypeHandle()
{
  ProductTypeAndID_Def   ProductType;
  ProductType = HART_GetProductTypeAndID();
  switch (ProductType)
  {
      case  SIEMENS_TYPE1:
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(SIEMENS);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(SMS_PAGE_INDEX_149);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  HW_TYPE1:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(HW);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(HW_PAGE_INDEX_0);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  EJA530_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(EJA530E);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(EJA_PAGE_INDEX_0);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  EJA_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(EJA);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(EA_PAGE_INDEX_0);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  LM_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(LM);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(LM_PAGE_INDEX_0);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  CHUAN_YI_TYPE1://川仪PDS
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(CHUAN_YI);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_PAGE_INDEX_109);
      }
      else if(HART_VersionGet() == HART_VERSION_7)
      {
        //测试，后续修改
        MENU_PageIndexSetHandle(CY_HART7_PDS);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY7_PAGE_INDEX_171);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  RADAR_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(RADAR);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(RADAR_PAGE_INDEX_85);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//TTS
      case  CHUAN_YI_TYPE2:
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_T1);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_T1_PAGE_INDEX_109);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//HVP
      case  CHUAN_YI_HVPID:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_HVP);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_HVP_PAGE_INDEX_129);
      }
      else if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_HVP5);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_HVP5_PAGE_INDEX_129);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//
      case  RAYDAR_80G:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(RAYDAR80G1_0);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(RAYDAR80G1_0_PAGE_INDEX_0);
      }
      else
      {
        //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      default:
             //跳转到初始化处理成功后的主界面
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      break;
  }
  
}
/*
void HART_InitialpageHandle(void )
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
初始化页面处理函数，
该函数功能是，确定初始化页面命令链接成功或失败后将执行哪些操作以及显示哪些页面。
*
* 关键备注：
* - 

  
* 未来提高:
如果添加多菜单树，可能还要补充其他的跳转界面。
  uint CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;

*/ 
void InitialpageHandle(void )
{
  if(G_HART_HandleFlag == HART_INIT_COMPLETE)     
  {
    //成功率界面确认判断，如果是成功率操作，则连接成功后进行页面切换操作
    if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_101)
       &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
    {
      HART_SuccessRatioHandle();
    }
    else if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_102)
       &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
    {
    
    }
    else
    {
      //关闭成功率计算处理功能
      G_ComPCT_SWITCH = FALSE;
      //版本界面执行完毕，调用设备类型处理函数进行菜单入口选择
      HART_DeviceTypeHandle();
    }    
  }//通信未连接切换界面
  else if(G_HART_HandleFlag == HART_INIT_ERR)  
  {
    //跳转到初始化处理失败的警告界面
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_39);
  }
  MENU_PageShowSwitch(TRUE);
  G_SingleCommandLoad = TRUE;
}

/*
void InitialPageShow()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
初始化页面显示函数，
该函数的作用是手操器刚刚上电启动时显示初始化界面，一般只有在设备未连接成功或
重新连接设备时会调用。
*
* 关键备注：
* - 
在手操器标准化之前，该函数是可以根据客户需要的显示形式进行改动的。
  
* 未来提高:

3.03版本，当前版本屏蔽了TTS的所有菜单，新增了锐达仪表80G和26G。
StringIndex_870
*/ 
void InitialPageShow()
{
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE] = {0};
  PageDef *PagePtr = NULL;
  MENU_PageShowSwitch(FALSE);

  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();

  G_ConnectWay = PagePtr->ConnectWay;
  //页面命令组加载函数
  MENU_PageCommandGroupLoad(PagePtr);
  //初始化显示界面为英文界面，如果后期需要改成中文的，可以进行程序升级
  StrStruct[0] = MENU_GetStrStruct(STR_INDEX_0);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX,ENGLISH,REVERSE_DISPLAY,StringCodeBuff[0]);
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_81);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX+2*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_82);  
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX+24,
       START_Y_INDEX+4*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]);
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_898); 
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX+6,
       START_Y_INDEX+6*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_899);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX+7*(ITEM_HIGHT),ENGLISH,REVERSE_DISPLAY,StringCodeBuff[0]);     
}
/*
void InitialPageRangeHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
初始页面范围处理模块函数，用来处理一些特殊参数。
*
* 关键备注：
* - 
  
* 未来提高:

*/ 
void InitialPageRangeHandle()
{
  if(G_IsInitVariable == FALSE)
  {
    InitialPageVariableInit();
  }
  else
  {
    if((G_PV_UnitTemp[0] != G_PV_Unit[0])
    ||(InitialPageRangeCompare() == FALSE))
    {
      G_IsInitVariable = FALSE;
    }
  }
}

