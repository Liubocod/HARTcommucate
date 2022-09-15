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

#include "ParamSetPage.h"
#include "HART.h"
#include "InfoPage.h"
#define IS_NOT_CHINESE_DISPLAY (PagePtr->ContentStrIndex == STR_INDEX_29)||(PagePtr->ContentStrIndex == STR_INDEX_316)||(PagePtr->ContentStrIndex == STR_INDEX_371)\
||(PagePtr->ContentStrIndex == STR_INDEX_33)||(PagePtr->ContentStrIndex == STR_INDEX_310)||(PagePtr->ContentStrIndex == STR_INDEX_368)||(PagePtr->ContentStrIndex == STR_INDEX_88)\
  ||(PagePtr->ContentStrIndex == STR_INDEX_1106)||(PagePtr->ContentStrIndex == STR_INDEX_911)||(PagePtr->ContentStrIndex == STR_INDEX_107)||(PagePtr->ContentStrIndex == STR_INDEX_906)\
    ||(PagePtr->ContentStrIndex == STR_INDEX_914)||(PagePtr->ContentStrIndex == STR_INDEX_915)||(PagePtr->ContentStrIndex == STR_INDEX_916)||(PagePtr->ContentStrIndex == STR_INDEX_917)||(PagePtr->ContentStrIndex == STR_INDEX_918)\
      ||(PagePtr->ContentStrIndex == STR_INDEX_939)
      
static void ParamChineseShowLineHandle(PageDef* const PagePtr,uchar *const ShowLineNum);
static void ParamShowLineCalculation(PageDef* const PagePtr,uchar *const ShowLineNum,LanguageTypeDef Language);
static void ParamVariableDisplay(PageDef* const PagePtr,DataTypeDef DataType,uint *VariableIndex,uchar* ShowData,
                       LanguageTypeDef Language,uchar* ShowLineIndex,DataLengthDef DataLength);
static void ParamVariableNumberDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,uchar Length,
                  PageDef* const PagePtr,uchar* ShowLineIndex,DataLengthDef DataLength);
static void ParamVariableUnitDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,
                                      PageDef* const PagePtr,uchar* ShowLineIndex);
static void ParamFunctionCodeDisplay(PageDef* const PagePtr,uchar* ShowLineIndex,DataTypeDef DataType
                            ,uchar *FloatStrTemp,DataLengthDef DataLength,LanguageTypeDef Language);
static void ParamVariableTrace(const HART_UnitDef* UnitTable,uchar* ShowData,
      PageDef* const PagePtr,uchar* ShowLineIndex,LanguageTypeDef Language);
static void ParamHandleFlagDisplay(HandleFlagDef HandleFlag,LanguageTypeDef Language);
//单次执行锁
bool8 G_SingleExcutionLock = FALSE;

/*
 //函数名称和参量和返回值类型。
static void ParamCY_TTSPatch1(const HART_UnitDef* UnitTable);
* 变量范围:
UnitTable:单位表指针。

* 返回值说明:void 
* 功能介绍:   
  川仪TTS补丁1函数，根据页面标题自行切换单位表

*
* 关键备注：
* - 

  
* 未来提高:



*/
static const HART_UnitDef* ParamCY_TTSPatch1()
{
  const HART_UnitDef* UnitTable = NULL;
  if((G_PublicVC0[0] == 0)||(G_PublicVC0[0] == 1))
  {
    UnitTable = G_CY_TTS_SnsrModel_1Table; 
  }
  else if((G_PublicVC0[0] == 2)||(G_PublicVC0[0] == 3))
  {
    UnitTable = G_CY_TTS_SnsrModelTable;
  }
  return UnitTable;
}
/*
 //函数名称和参量和返回值类型。
static uchar* ParamCY_HVPPatch1(uchar* FunCodeTemp,uchar* ShowData,uint ContentStrIndex)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  川仪HVP补丁1函数，
  页面挂载变量需要进行位运算进行裁剪才能正常显示

*
* 关键备注：
* - 

  
* 未来提高:



*/
static void ParamCY_HVPPatch1(uchar* FunCodeTemp,uchar ShowData,uint ContentStrIndex)
{
  *FunCodeTemp = ShowData;
  switch(ContentStrIndex)
  {
  case STR_INDEX_1073:
    *FunCodeTemp = (*FunCodeTemp)&0x01;
    break;
  case STR_INDEX_1074:
    *FunCodeTemp = (*FunCodeTemp)&0x02;
    //由于RISE 和 LIN的功能码值相同，为了区分显示，这里将功能码进行自定义
    if(*FunCodeTemp == 0)
    {
      *FunCodeTemp = 3;
    }
    break;
  case STR_INDEX_1075:
    *FunCodeTemp = (*FunCodeTemp)&0x04;
    //字符与1074相同
    (*FunCodeTemp) = (*FunCodeTemp)>>1;
    //由于RISE 和 LIN的功能码值相同，为了区分显示，这里将功能码进行自定义
    if(*FunCodeTemp == 0)
    {
      *FunCodeTemp = 3;
    }
    break;
  default:break;
  }
}
/*
 //函数名称和参量和返回值类型。
void	ParamSetPageHandle(KeyValueDef KeyMode);
* 变量范围:
KeyValueDef KeyMode:按键种类，区分是哪一个按键。

* 返回值说明:void 
* 功能介绍:   
  参数设定页面切换处理函数

*
* 关键备注：
* - 
用于切换到其他页面的处理函数
  
* 未来提高:
需要移至显示文件中。


*/ 
void	ParamSetPageHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemV;
  uint VariableIndex;
  uchar *ShowData = NULL;
  PageDef *PagePtr = NULL;
  DataTypeDef DataType;
  bool8 IsVariableHandle = FALSE;

  
  PagePtr = MENU_GetCurrentMenuPage();
  //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
  CurrentItemV = MENU_GetVarticalItem(PagePtr,G_CursorNumV);
  if(PagePtr->VariableIndex != VARIABLE_ARR_0)
  {
    //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
    VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
    //获取HART变量数组指针
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
    //获取HART变量的数据类型
    DataType = MENU_GetHartVariableDataType(VariableIndex);
    IsVariableHandle = TRUE;
  }

  
  if(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE)
  {
     switch(KeyMode)
     {
        case DOWN:
            if(G_CursorNumV >= PagePtr->ItemNumberV-1)
            {
              G_CursorNumV = 0;
            }
            else
            {
              G_CursorNumV++;
            }
          break;
        case UP:
            if(G_CursorNumV == 0)
            {
              G_CursorNumV = PagePtr->ItemNumberV-1;
            }
            else
            {
              G_CursorNumV--;
            }
          break;
        case RIGHT:
            if(G_CursorNumH >= PagePtr->ItemNumberH-1)
            {
              G_CursorNumH = 0;
            }
            else
            {
              G_CursorNumH++;
            }
          break;
        case LEFT:
            if(G_CursorNumH == 0)
            {
              G_CursorNumH = PagePtr->ItemNumberH-1;
            }
            else
            {
              G_CursorNumH--;
            }
          break;
        case OK:
          if(G_CursorNumH == HORIZONTAL_RIGHT_FIRST_ITEM)
          {
            MENU_GeneralItemLinkHandle(CurrentItemV);
            HART_UnitTempLoad(DataType,IsVariableHandle,ShowData);
          }
          if(G_CursorNumH == HORIZONTAL_RIGHT_SECOND_ITEM)
          {
            MENU_PageLinkHandle(PagePtr); 
            //校准电流中途放弃退出电流模式的时候，不需要还原被保护现场，因为需要发送0电流值
            if((PagePtr->ContentStrIndex != STR_INDEX_310)
              &&(PagePtr->ContentStrIndex != STR_INDEX_316)
                &&(PagePtr->ContentStrIndex != STR_INDEX_73))
            {
              HART_ProtectedVariableGet(); 
            }
          }
          G_VariableProtect.LoadLock = FALSE;
          G_SingleExcutionLock = FALSE;
          FlashReadLockHandle(FALSE);
          MENU_IS_SingleCommandLoad(FALSE,PagePtr);
          break;
     }
  }
  else
  {
    //Page error
  }
}
/*
 //函数名称和参量和返回值类型。
void ParamSetPageShow(uint MenuTreeIndex);
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍:   
  参数设定页面显示函数。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void ParamSetPageShow()
{
  uchar ShowLineIndex = 0,ShowLineNum,ItemNumber; 
  uchar StartItem,EndItem,LineOffset = 0;
  HandleFlagDef HandleFlag;

  DataLengthDef DataLength,ReceiveDataLength;
  uint VariableIndex;
  uchar *ShowData = NULL;
  PageDef *PagePtr = NULL;
  DataTypeDef DataType;
  LanguageTypeDef LanguageTemp;
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  //异常情况返回现场保护函数
  MENU_ReturnPageSave(PagePtr);

  ShowLineNum = PagePtr->SinglePageItemNumberV; 
  ItemNumber = PagePtr->ItemNumberV;
  MENU_CursorOverrunHandle(ItemNumber-1);
  //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
  FlashVariableGroupLoad(PagePtr->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);
  ShowData = MENU_VariableInfoGet(&VariableIndex,&DataType,&DataLength,&ReceiveDataLength);
  MENU_IS_SingleCommandLoad(TRUE,PagePtr);
  MENU_PageShowSwitch(FALSE);
  if(IS_NOT_CHINESE_DISPLAY)
  {
    LanguageTemp = ENGLISH;
  }
  else
  {
    LanguageTemp = MENU_LanguageTypeGet();
  }
  ParamShowLineCalculation(PagePtr,&ShowLineNum,LanguageTemp); 
  MENU_VerticalItemRefreshHandle(ShowLineNum,PagePtr);

  ShowLineIndex = MENU_ExplainInfoDisplayHandle(MENU_LanguageTypeGet(),ShowLineIndex,PagePtr);

  ParamVariableDisplay(PagePtr,DataType,&VariableIndex,ShowData,LanguageTemp,&ShowLineIndex,DataLength);


  //纵向显示参数获取，获取当前页面的起始项号及最终项号
  HandleFlag = MENU_VerticalItemSwitchParamGet(&StartItem,
                &EndItem,ShowLineNum,ItemNumber);
  //纵向菜单项显示函数
  ShowLineIndex = MENU_VerticalItemShow(StartItem,EndItem,ShowLineIndex,LanguageTemp,PagePtr,LineOffset);
  if(MENU_LanguageTypeGet() == CHINESE)
  {
    ShowLineIndex = 6;
  }
  else
  {
    ShowLineIndex = 7;
  }
  //横向菜单项显示
  MENU_HorizontalItemShow(PagePtr,ShowLineIndex,MENU_LanguageTypeGet());
  
  ParamHandleFlagDisplay(HandleFlag,LanguageTemp);
  FlashReadLockHandle(TRUE);
}
/*
void ParamSetPageSingleExcutionLockHandle(bool8 IsSingleExcution);
* 变量范围:
  IsSingleExcution:单次执行锁，通过该参数设置执行锁

* 返回值说明:void 
* 功能介绍:   
  参数选择界面专有的单次执行锁，用来减少二次进入菜单后。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void ParamSetPageSingleExcutionLockHandle(bool8 IsSingleExcution)
{
  G_SingleExcutionLock = IsSingleExcution;
}
  
/*
 //函数名称和参量和返回值类型。
static void ParamHandleFlagDisplay(HandleFlagDef HandleFlag,LanguageTypeDef Language);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  参数界面处理标记显示函数，由于有时参数选择界面后续有选项，但是无法在一页中
  显示全部选项，因此需要翻页提示标记。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamHandleFlagDisplay(HandleFlagDef HandleFlag,LanguageTypeDef Language)
{
  uchar StartX = 0,StartY = 0;
  AssertParam(IS_HANDLE_FLAG(HandleFlag));
  if(Language == ENGLISH)
  {
    StartX = 0;
    StartY = 7;
  }
  else if(Language == CHINESE)
  {
    StartX = 0;
    StartY = 6;
  }

  if(HandleFlag == EndingOption)
  {
  MENU_HandleFlagDisplay(EndingOption,NORMAL,StartX,StartY,Language); 
  }
  else if(HandleFlag == OptionsLeft)
  {
  MENU_HandleFlagDisplay(OptionsLeft,NORMAL,StartX,StartY,Language);
  }
}

/*
 //函数名称和参量和返回值类型。
static void ParamChineseShowLineHandle(PageDef* const PagePtr,uchar *const ShowLineNum);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  参数选择页面中文显示行标处理函数，用来计算中文显示时的行显参数示运算。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamChineseShowLineHandle(PageDef* const PagePtr,uchar *const ShowLineNum)
{
  if(PagePtr->AdditionalInfo == ONLY_SHOW)
  {
   *ShowLineNum = 4;
  }
  else if(PagePtr->AdditionalInfo ==  NO_VARIABLE_NUM)
  {
    *ShowLineNum = 2;
  }
  else
  {
    *ShowLineNum = 1;
  }
}
/*
 //函数名称和参量和返回值类型。
static void ParamShowLineCalculation(uchar ShowLineIndex,
       PageDef* const PagePtr,LanguageTypeDef Language,uchar* const LineOffset,uchar *const ShowLineNum);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  参数选择页面显示行标处理函数，用来计算显示时的行显参数示运算。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamShowLineCalculation(PageDef* const PagePtr,uchar *const ShowLineNum,LanguageTypeDef Language)
{
  if(Language == CHINESE)
  {
    ParamChineseShowLineHandle(PagePtr,ShowLineNum);
  }
  else if((MENU_LanguageTypeGet() == CHINESE)&&(Language == ENGLISH))
  {
    //汉字界面中的英文项显示行显个数计算
    *ShowLineNum = 3;
  }
}
/*
 //函数名称和参量和返回值类型。
static void ParamVariableDisplay(PageDef* const PagePtr,DataType,
              uint *VariableIndex,uchar* ShowData,LanguageTypeDef Language,uchar* ShowLineIndex,DataLengthDef* DataLength);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  参数选择页面变量显示,有的页面需要显示变量，有的不需要显示，
  有的显示数字，有的显示文字，有的带单位，有的不带单位。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamVariableDisplay(PageDef* const PagePtr,DataTypeDef DataType,
              uint *VariableIndex,uchar* ShowData,LanguageTypeDef Language,uchar* ShowLineIndex,DataLengthDef DataLength)
{
  uchar FloatStrTemp[ASCII_9] = {0},VariableNumber = 0;
  uchar Length;

  
  if(IS_PARAM_DISPLAY)
  {
    VariableNumber = MENU_PageVariableNumber(G_PageVariableTable);
    Length = MENU_DataToASCII(G_VariableProtect.Buff,FloatStrTemp,DataType);
    //该部分主要针对既有数值变量，又有单位变量的参数选择界面。
    if(PagePtr->AdditionalInfo == NUM_VARIABLE_BOTH)
    {
      ParamVariableNumberDisplay(Language,FloatStrTemp,Length,PagePtr,ShowLineIndex,DataLength);
      //显示界面包括两个显示变量的
      if(VariableNumber == 0x02)
      {
        ParamVariableUnitDisplay(Language,FloatStrTemp,PagePtr,ShowLineIndex);
      }
    }
    else 
    {
      if(PagePtr->AdditionalInfo == VARIABLE_WITHOUT_NUM)//针对功能码变量的显示
      {
        ParamFunctionCodeDisplay(PagePtr,ShowLineIndex,DataType,FloatStrTemp,DataLength,Language);
      }
      else if(PagePtr->AdditionalInfo == NUM_WITHOUT_VARIABLE)//针对功能码以数字形式显示的页面
      {
        ParamFunctionCodeDisplay(PagePtr,ShowLineIndex,DataType,FloatStrTemp,DataLength,Language);
        if(*ShowLineIndex > 3)
        {
          *ShowLineIndex = *ShowLineIndex-1;
        }
      }
    }
  }
}
/*
 //函数名称和参量和返回值类型。
static void ParamVariableNumberDisplay(MenuTreeIndexDef MenuTreeIndex,
              LanguageTypeDef Language,uchar *const FloatStrTemp,uchar Length,
              PageDef* const PagePtr,uchar* ShowLineIndex);

* 返回值说明:void 
* 功能介绍:   
  参数选择页面数字变量显示函数,用来显示数字变量。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamVariableNumberDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,uchar Length,
              PageDef* const PagePtr,uchar* ShowLineIndex,DataLengthDef DataLength)
{
  uchar StartX,StartY;
  FontMatrixDef FontMatrix;
  if(Language == ENGLISH)
  {
    //获取字体信息
    MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[Language]);
    //确定显示横向坐标
    StartX = 
      (G_StrStruct[*ShowLineIndex-1].CharacterNumber[Language])*(FontMatrix.HorizontalLine);
    StartY = *ShowLineIndex-1;
  }
  else if(Language == CHINESE)
  {
    StartX = 0;
    StartY = *ShowLineIndex;
  }
  MENU_TemporaryVariableReset(FloatStrTemp,LINE_LENGTH,Length);
  *ShowLineIndex = MENU_VariableShow(DataLength,FloatStrTemp,StartY,PagePtr,StartX,NORMAL);
}
/*
 //函数名称和参量和返回值类型。
static void ParamVariableUnitDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,
                                      PageDef* const PagePtr,uchar* ShowLineIndex);

* 返回值说明:void 
* 功能介绍:   
  参数选择页面数字变量显示函数,用来显示数字变量。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamVariableUnitDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,
                                      PageDef* const PagePtr,uchar* ShowLineIndex)
{
  uint VariableIndex = 0;
  DataTypeDef DataType;
  uchar* ShowData,IntegerLength = 0;
  uchar StartX,StartY;
  FontMatrixDef FontMatrix;
  const HART_UnitDef* UnitTable = NULL;
  uint StrNum = 0;
  StringDef StrUnitStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE] = {0};
  
  VariableIndex = MENU_VariableIndexInfoGet(1,G_VariableGroupTable);        
  DataType = MENU_GetHartVariableDataType(VariableIndex);
  //获取HART变量数组指针
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    //获取HART变量功能码对照表数组指针
    UnitTable = MENU_GetHartUnitTable(VariableIndex); 
    if(UnitTable != NULL)
    {
      //防止指针丢失，重新获取一次字体信息
      MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[ENGLISH]);
      IntegerLength = MENU_AsciiLengthGet(FloatStrTemp,ASCII_9,0x20);
      if(Language == ENGLISH)
      {
        //确定显示横向坐标
        StartX = (G_StrStruct[*ShowLineIndex-1].CharacterNumber[Language])*(FontMatrix.HorizontalLine);
        StartX += IntegerLength*(FontMatrix.HorizontalLine);
        StartY = START_Y_INDEX+(*ShowLineIndex-2)*(ITEM_HIGHT)+1;
      }
      else if(Language == CHINESE)
      {
        StartX = IntegerLength*(FontMatrix.HorizontalLine);
        StartY = *ShowLineIndex-1;
      }
      StrNum = HART_UnitShowHandle(UnitTable,ShowData);
      StrUnitStruct[0] = MENU_GetStrStruct(StrNum);
      FlashStringCodeGet(StrUnitStruct,StringCodeBuff[0],ENGLISH);
      MENU_StaticStringShow(StrUnitStruct,StartX,
              StartY,ENGLISH,NORMAL,StringCodeBuff[0]); 
    }
  }
}
/*
 //函数名称和参量和返回值类型。
static void ParamFunctionCodeDisplay(PageDef* const PagePtr,uchar* ShowLineIndex);

* 返回值说明:void 
* 功能介绍:   
  参数选择页面功能码变量显示函数,用来显示功能码文字变量。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamFunctionCodeDisplay(PageDef* const PagePtr,uchar* ShowLineIndex,DataTypeDef DataType,
            uchar *FloatStrTemp,DataLengthDef DataLength,LanguageTypeDef Language)
{
  const HART_UnitDef* UnitTable = NULL;
  uchar FunCodeTemp = 0;
  uint VariableIndex = 0;
  uchar* ShowData;
  //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
  VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
  //获取HART变量数组指针
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    //获取HART变量功能码对照表数组指针
    UnitTable = MENU_GetHartUnitTable(VariableIndex);
    //川仪TTS补丁，Snsr type显示问题
    if(PagePtr->ContentStrIndex == STR_INDEX_916)
    {
      UnitTable = ParamCY_TTSPatch1();
    }
    //川仪HVP补丁，YFCT SDIR YDIR
    if((PagePtr->ContentStrIndex == STR_INDEX_1073)
        ||(PagePtr->ContentStrIndex == STR_INDEX_1074)
          ||(PagePtr->ContentStrIndex == STR_INDEX_1075))
    {
        ParamCY_HVPPatch1(&FunCodeTemp,*ShowData,PagePtr->ContentStrIndex);
        //便于显示，改变指针指向
        ShowData = &FunCodeTemp;
    }
    //参数选择界面的变量追踪功能。
    if(UnitTable != NULL)
    {
      ParamVariableTrace(UnitTable,ShowData,PagePtr,ShowLineIndex,Language);

      MENU_StaticStringShow(G_StrStruct+*ShowLineIndex,START_X_INDEX,
        START_Y_INDEX+*ShowLineIndex*(ITEM_HIGHT),Language,NORMAL,G_StringCodeBuff[*ShowLineIndex]); 
      *ShowLineIndex += 1;
    }
  }
  else
  {
    //如果不是功能码变量，则显示数值
    *ShowLineIndex = MENU_VariableShow(DataLength,FloatStrTemp,*ShowLineIndex,PagePtr,0,NORMAL);
  }
}
/*
 //函数名称和参量和返回值类型。
static uint ParamVariableTrace(const HART_UnitDef* UnitTable,uchar* ShowData,
      PageDef* const PagePtr,MenuTreeIndexDef MenuTreeIndex,uchar* ShowLineIndex);

* 返回值说明:void 
* 功能介绍:   
  参数选择页面光标追踪函数,用来锁定当前变量在选项列表中的位置，
  让光标在显示时直接跳转到变量所在位置。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
static void ParamVariableTrace(const HART_UnitDef* UnitTable,uchar* ShowData,
      PageDef* const PagePtr,uchar* ShowLineIndex,LanguageTypeDef Language)
{
  const ItemDef* CurrentItemV = NULL;
  uchar CursorIndex = 0;
  uint StrNum = 0;
  StrNum = HART_UnitShowHandle(UnitTable,ShowData);
  if(G_SingleExcutionLock == FALSE)
  {
    for(CursorIndex = 0;CursorIndex < PagePtr->ItemNumberV;CursorIndex++ )
    {
      CurrentItemV = MENU_GetVarticalItem(PagePtr,CursorIndex); 
      if(CurrentItemV->StringNum == StrNum)
      {
        G_CursorNumV = CursorIndex;
        break;
      }
    }
    G_SingleExcutionLock = TRUE;
  }      
  FlashStringReadLockHandle(*ShowLineIndex,StrNum,Language);
}
