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

#include "InfoPage.h"


static uchar PageUnitShow(const PageDef* CurrentPage,uchar ShowLineIndex);
/*
 //函数名称和参量和返回值类型。
void	InfoPageHandle(KeyValueDef KeyMode);
* 变量范围:
KeyValueDef KeyMode：按键值

* 返回值说明:void 
* 功能介绍:   
  状态信息页面切换处理函数

*
* 关键备注：
* - 
用于切换到其他页面的处理函数
  
* 未来提高:
需要移至显示文件中。


*/ 
void	InfoPageHandle(KeyValueDef KeyMode)
{
  PageDef *PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPage();  

  if(MENU_CurrentPageTypeGet() == INFO_PAGE)
  {
   if(KeyMode == OK)
   {
      MENU_PageLinkHandle(PagePtr);
   }
  }
  else
  {
   //Page error
  }
}
/*
 //函数名称和参量和返回值类型。
void PageUnitShow();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  页面单位显示函数。

*
* 关键备注：
* - 


  
* 未来提高:

     注意：

*/
static uchar PageUnitShow(const PageDef* CurrentPage,uchar ShowLineIndex)
{
  uint VariableIndex;
  uchar *ShowData;
  const HART_UnitDef* UnitTable = NULL;
  uint StrNum = 0,UnitLength=0;
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE] = {0};
  VariableIndex = MENU_VariableIndexInfoGet(1,G_VariableGroupTable);
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  UnitTable = MENU_GetHartUnitTable(VariableIndex);
  StrNum = HART_UnitShowHandle(UnitTable,ShowData);
  //单位字节个数
  StrStruct[0] = MENU_GetStrStruct(StrNum);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  UnitLength = StrStruct->RealCharacterNumber[0];
  MENU_StaticStringShow(StrStruct,(21-UnitLength)*6,
    START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  return UnitLength;
}
/*
 //函数名称和参量和返回值类型。
void InfoPageShow();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  状态信息显示函数。

*
* 关键备注：
* - 


  
* 未来提高:

     注意：
关于变送器的生产商基本不会出现相同的ID，但是设备型号ID可能出现相同的
目前的解决方法是，后期添加设备类型code再编码函数，以当前显示的设备类型界面作为函数
分支条件，根据重复生产厂商ID，和对应的设备类型code，特别指定StrNum.
例如：
if((G_ManufacturerID == LM_MANUFACTURER_ID)&&(G_DeviceType == 0x06))//因为其他生产商有设备类型为0x06的设备类型号
{
  return STR_INDEX_885;
}
然后用变量StrNum接收上述函数的返回值，继续if(DataType == FUNC_CODE_T){}中
     MENU_StaticStringShow(StrStruct+StrNum,CurrentPage->StartX,
            START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),NORMAL);
的操作。

*/ 

void InfoPageShow()
{
  uint StrNum = 0;
  uchar *ShowData,VariableNumber = 0;
  uint VariableIndex;
  PageDef *PagePtr = NULL;
  FontMatrixDef FontMatrix;
  const HART_UnitDef* UnitTable = NULL;
  uchar ShowLineIndex=0,j,ShowLength = 0,UnitLength=0;
  uchar Temp[SHOW_DATA_BUF_SIZE] = {0};
  DataTypeDef DataType = UCHAR_T;
  DataLengthDef DataLength = UCHAR,ReceiveDataLength = UCHAR;
  LanguageTypeDef Language = MENU_LanguageTypeGet();
  uchar Tagline[]  = 
  {
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x00,
  };
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE] = {0};
  //获取菜单树序号
  MENU_PageShowSwitch(FALSE);

  PagePtr = MENU_GetCurrentMenuPage();
  //页面命令组加载函数
  MENU_PageCommandGroupLoad(PagePtr);
  ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);

  //如果当前页面没有挂在变量数组，则不需要进行显示变量加载。
  if(PagePtr->VariableIndex != 0x00)
  {
    VariableNumber = MENU_PageVariableNumber(G_PageVariableTable);
    //先写单位
    if(VariableNumber == 0x02)
    {
      UnitLength = PageUnitShow(PagePtr,ShowLineIndex);
    }
    VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
    UnitTable = MENU_GetHartUnitTable(VariableIndex);
    DataType = MENU_GetHartVariableDataType(VariableIndex);
    DataLength = MENU_GetHartVariableDataLength(VariableIndex);
    ReceiveDataLength = MENU_GetHartVariableAnalysisLength(VariableIndex); 

    if(DataType == FUNC_CODE_T)
    {
      //川仪TTS补丁，Snsr type显示问题
      if(PagePtr->ContentStrIndex == STR_INDEX_912)
      {
        if((G_PublicVC0[0] == 0)||(G_PublicVC0[0] == 1))
        {
          UnitTable = G_CY_TTS_SnsrModel_1Table; 
        }
        else if((G_PublicVC0[0] == 2)||(G_PublicVC0[0] == 3))
        {
          UnitTable = G_CY_TTS_SnsrModelTable;
        }
      }
      StrNum = HART_UnitShowHandle(UnitTable,ShowData); 
      StrStruct[0] = MENU_GetStrStruct(StrNum);
      FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);  
      MENU_StaticStringShow(StrStruct,START_X_INDEX,
            START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]);
    }
    else if(DataType == ASCII_T)
    {
      //如果是Tag编辑界面，需要进行ASCII解码
      j = HART_ASCII_Decode(Tagline,ReceiveDataLength,DataLength,ShowData);
      if(j != 0)
      {
         ShowLineIndex = MENU_VariableShow(DataLength,Tagline,ShowLineIndex,PagePtr,0,NORMAL);
      }
    }
    else if(DataType == L_ASCII_T)
    {
      //通用8位ASCII码处理。
      ShowLineIndex = MENU_VariableShow(DataLength,ShowData,ShowLineIndex,PagePtr,0,NORMAL);
    }
    else
    {
      ShowLength = HART_TypeConvert(ShowData,Temp,DataType,DataLength,ASCII_T);
      //如果显示单位，需要将变量显示缓冲数组最后一个字节赋值为/0，否则会覆盖单位
      if(VariableNumber == 2)
      {
        Temp[ShowLength] = 0;
      }
      MENU_DynamicStringShow(ASCII_6X8,Temp,
          (21-UnitLength-ShowLength-1)*6,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),NORMAL,ENGLISH);
    }
    if((PagePtr->ContentStrIndex == STR_INDEX_417)||(PagePtr->ContentStrIndex == STR_INDEX_418)
      ||(PagePtr->ContentStrIndex == STR_INDEX_419)||(PagePtr->ContentStrIndex == STR_INDEX_420))
    {
      StrStruct[0] = MENU_GetStrStruct(STR_INDEX_255);
      FlashStringCodeGet(StrStruct,StringCodeBuff[0],MENU_LanguageTypeGet());  
      MENU_StaticStringShow(StrStruct,START_X_INDEX+42,
        START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),MENU_LanguageTypeGet(),NORMAL,StringCodeBuff[0]);  
    }
  }
  MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[MENU_LanguageTypeGet()]);
  //横向菜单项显示
  MENU_HorizontalItemShow(PagePtr,6,MENU_LanguageTypeGet());
}

