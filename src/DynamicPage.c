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

#include "DynamicPage.h"


#define DYNAMIC_VARIABLE_BIT_NUM 25
static void DynamicPackageHandle(uchar j);
static void DynamicPV_Type1ShowHandle(uchar ShowLineIndex);
static void DynamicPV_Type2ShowHandle(uchar ShowLineIndex);
static void DynamicAlarmCodeShowHandle();
static void SucRateShow(const PageDef* CurrentPage,uchar ShowLineIndex);
static void DynamicDescriptionDisplay(const PageDef*const CurrentPage,uint MenuItemOffset,
             uchar StructIndex,uchar LineTemp,uchar ShowLineIndex,uchar ItemHighFactor,uchar LineOffset);
/*
//函数名称和参量和返回值类型。
void DynamicPageHandle(KeyValueDef KeyMode)
* 变量范围:
KeyValueDef KeyMode:按键种类，区分是哪一个按键。
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;

* 返回值说明:void 
* 功能介绍:   
  动态信息页面切换处理函数，
  根据按键切换，或后台处理时来调用，主要用于确定下一个显示的页面。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void DynamicPageHandle(KeyValueDef KeyMode)
{
  PageDef *PagePtr = NULL;

  PagePtr = MENU_GetCurrentMenuPage();
   if(MENU_CurrentPageTypeGet() == DYNAMIC_PAGE)
   {
     if(KeyMode == LEFT)
     {
      Menu_BackupPageLinkHandle(PagePtr);
      FlashReadLockHandle(FALSE);
     }
   }
   else
   {
     //Page error
   }
}
/*
//函数名称和参量和返回值类型。
static void DynamicDescriptionDisplay(const PageDef*const PagePtr,MenuTreeIndexDef MenuTreeIndex,uint MenuItemOffset
               uchar StructIndex,uchar LineTemp,uchar ShowLineIndex,uchar ItemHighFactor,uchar LineOffset)

* 变量范围:
PagePtr：页面信息指针。
MenuTreeIndex：菜单树索引。
MenuItemOffset：菜单项索引
StructIndex：字串结构全局数组序号，要来在固定数组中的固定位置保存固定信息。
LineTemp：变量显示时的行号。
ShowLineIndex：液晶对应显示行号。
ItemHighFactor：项高因子，汉字和英文有所区别。
LineOffset：行间距偏移，汉字英文不同。

* 返回值说明:void 
* 功能介绍: 动态显示报警码函数。HVP报警码显示函数  
*
* 关键备注：
* - 

  
* 未来提高:
*/ 

static void DynamicDescriptionDisplay(const PageDef*const PagePtr,uint MenuItemOffset,
               uchar StructIndex,uchar LineTemp,uchar ShowLineIndex,uchar ItemHighFactor,uchar LineOffset)
{
  const ItemDef* CurrentItem = NULL;
  FontDef FontType;
  uchar LineNum[5] = {0};
  CurrentItem = MENU_GetVarticalItem(PagePtr,MenuItemOffset);
  //flash字符串读取锁处理
  FlashStringReadLockHandle(StructIndex,CurrentItem->StringNum,MENU_LanguageTypeGet());
  if(MENU_LanguageTypeGet() == ENGLISH)
  {
    FontType = ASCII_6X8;
  }
  else
  {
    FontType = ASCII_6X16;
  }
  MENU_LineNumEdit(LineNum,LineTemp); 
  MENU_DynamicStringShow(FontType,LineNum,
        START_X_INDEX,START_Y_INDEX+ShowLineIndex*(ItemHighFactor),NORMAL,ENGLISH);     
  MENU_StaticStringShow(G_StrStruct+StructIndex,START_X_INDEX+LineOffset,
    START_Y_INDEX+ShowLineIndex*(ItemHighFactor),
        MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[StructIndex]);
}
/*
//函数名称和参量和返回值类型。
static void DynamicAlarmCodeShowHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍: 动态显示报警码函数。HVP报警码显示函数  
*
* 关键备注：
* - 

  
* 未来提高:
*/ 
static void DynamicAlarmCodeShowHandle()
{
  if(G_PublicVC8[0] == 0)
  {
    MENU_DynamicStringShow(ASCII_6X8,"No Alarm",24,7,NORMAL,ENGLISH);
  }
  else if(G_PublicVC8[0] == 1)
  {
    MENU_DynamicStringShow(ASCII_6X8,"No Snsr sigl",24,7,NORMAL,ENGLISH);
  }
  else if(G_PublicVC8[0] == 2)
  {
    MENU_DynamicStringShow(ASCII_6X8,"Over sigl span",24,7,NORMAL,ENGLISH);
  }
  else if(G_PublicVC8[0] == 3)
  {
    MENU_DynamicStringShow(ASCII_6X8,"Install error",24,7,NORMAL,ENGLISH);
  }
  else if(G_PublicVC8[0] == 4)
  {
    MENU_DynamicStringShow(ASCII_6X8,"EEP error",24,7,NORMAL,ENGLISH);
  }
  else if(G_PublicVC8[0] == 5)
  {
    MENU_DynamicStringShow(ASCII_6X8,"Tmp high or low",24,7,NORMAL,ENGLISH);
  }
}
/*
//函数名称和参量和返回值类型。
void DynamicPV_Type2ShowHandle()
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍: 主变量类型2显示函数
  显示四个变量。  
*
* 关键备注：
* - 

  
* 未来提高:
*/ 
static void DynamicPV_Type2ShowHandle(uchar ShowLineIndex)
{
  uchar LineNum[5] = {0};
  uchar LengthInter;
  uchar Temp[SHOW_DATA_BUF_SIZE];
  const HART_UnitDef* UnitTable = NULL;
  uint StrNum;
  
  FlashReadLockHandle(FALSE);
  union FloatToChar
  {
    uchar Char[4];
    float Float;
  }F_C;
  //PV
  MENU_LineNumEdit(LineNum,1);
  MENU_DynamicStringShow(ASCII_6X8,LineNum,0,2,NORMAL,ENGLISH); 	
  MENU_DynamicStringShow(ASCII_6X8,"PV",18,2,NORMAL,ENGLISH);
  BufReverseCopy(F_C.Char,G_PV,FLOAT_T);
  LengthInter = ModbusFloatToASCIIConvert(F_C.Float,3,Temp);
  LengthInter += 4;
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter] = 0x00;
  UnitTable = MENU_GetHartUnitTable(0XE7); 

  StrNum = HART_UnitShowHandle(UnitTable,G_PV_Unit);
  FlashStringReadLockHandle(ShowLineIndex,StrNum,ENGLISH);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
    (21-LengthInter-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,NORMAL,ENGLISH);
  MENU_StaticStringShow(G_StrStruct+ShowLineIndex,
    (21-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,
          MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[ShowLineIndex]);  
  ShowLineIndex++;
  //SV
  //编辑序号
  MENU_LineNumEdit(LineNum,2);
  MENU_DynamicStringShow(ASCII_6X8,LineNum,0,ShowLineIndex,NORMAL,ENGLISH);
  BufReverseCopy(F_C.Char,G_SV,FLOAT_T);
  if(HART_VersionGet() == HART_VERSION_5)
  {
    MENU_DynamicStringShow(ASCII_6X8,"AO%",18,ShowLineIndex,NORMAL,ENGLISH);
    LengthInter = ModbusFloatToASCIIConvert(F_C.Float*100,1,Temp);
  }
  else if(HART_VersionGet() == HART_VERSION_7)
  {
    MENU_DynamicStringShow(ASCII_6X8,"SV",18,ShowLineIndex,NORMAL,ENGLISH);
    LengthInter = ModbusFloatToASCIIConvert(F_C.Float,1,Temp);
    //如果是HART7，只发送03命令读取4个主变量
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = 0;
  }


  LengthInter += 4;
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter] = 0x00;
  StrNum = HART_UnitShowHandle(UnitTable,G_SV_Unit);
  FlashStringReadLockHandle(ShowLineIndex,StrNum,ENGLISH);
  MENU_DynamicStringShow(ASCII_6X8,Temp,(23-LengthInter-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,NORMAL,ENGLISH);
  MENU_StaticStringShow(G_StrStruct+ShowLineIndex,(21-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,
          MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[ShowLineIndex]); 
  ShowLineIndex++ ;
  //TV
  //编辑序号
  MENU_LineNumEdit(LineNum,3);
  MENU_DynamicStringShow(ASCII_6X8,LineNum,0,ShowLineIndex,NORMAL,ENGLISH); 	
  MENU_DynamicStringShow(ASCII_6X8,"TV",18,ShowLineIndex,NORMAL,ENGLISH);
  BufReverseCopy(F_C.Char,G_TV,FLOAT_T);
  if(HART_VersionGet() == HART_VERSION_5)
  {
    LengthInter = ModbusFloatToASCIIConvert(F_C.Float,1,Temp);
  }
  else if(HART_VersionGet() == HART_VERSION_7)
  {
    LengthInter = ModbusFloatToASCIIConvert(F_C.Float*100,1,Temp);
  }

  LengthInter += 4;
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter] = 0x00;
  StrNum = HART_UnitShowHandle(UnitTable,G_TV_Unit);
  FlashStringReadLockHandle(ShowLineIndex,StrNum,ENGLISH);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
      (23-LengthInter-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,NORMAL,ENGLISH);
  MENU_StaticStringShow(G_StrStruct+ShowLineIndex,
      (21-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,
          MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[ShowLineIndex]);  
  ShowLineIndex++;
  //QV
  //编辑序号
  MENU_LineNumEdit(LineNum,4);
  MENU_DynamicStringShow(ASCII_6X8,LineNum,0,ShowLineIndex,NORMAL,ENGLISH);
  if(HART_VersionGet() == HART_VERSION_5)
  {
    MENU_DynamicStringShow(ASCII_6X8,"AO",18,ShowLineIndex,NORMAL,ENGLISH);
    BufReverseCopy(F_C.Char,G_PV_Current,FLOAT_T);
    StrNum = STR_INDEX_255;//模拟电流单位mA
  } 
  else if(HART_VersionGet() == HART_VERSION_7)
  {
    MENU_DynamicStringShow(ASCII_6X8,"QV",18,ShowLineIndex,NORMAL,ENGLISH);
    BufReverseCopy(F_C.Char,G_QV,FLOAT_T);
    StrNum = HART_UnitShowHandle(UnitTable,G_QV_Unit);
  }	
  LengthInter = ModbusFloatToASCIIConvert(F_C.Float,1,Temp);
  FlashStringReadLockHandle(ShowLineIndex,StrNum,ENGLISH);
  LengthInter += 4;
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter] = 0x00;

  MENU_DynamicStringShow(ASCII_6X8,Temp,
      (23-LengthInter-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,NORMAL,ENGLISH);
  MENU_StaticStringShow(G_StrStruct+ShowLineIndex,
      (21-(G_StrStruct+ShowLineIndex)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,ShowLineIndex,
          MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[ShowLineIndex]); 
  ShowLineIndex++; 
  MENU_CommandAdd(SECOND_VARIABLE);
  //编辑序号
  MENU_LineNumEdit(LineNum,5);
  MENU_DynamicStringShow(ASCII_6X8,LineNum,0,ShowLineIndex,NORMAL,ENGLISH); 	
  MENU_DynamicStringShow(ASCII_6X8,"AlmCode",18,ShowLineIndex,NORMAL,ENGLISH);
  //如果有些产品需要显示其他内容，可以在这里进行做分支处理，进行特殊显示
  DynamicAlarmCodeShowHandle();
  MENU_CommandAdd(ReadAlarmStatus);
  FlashReadLockHandle(TRUE);
}
/*
//函数名称和参量和返回值类型。
void DynamicPV_Type1ShowHandle()
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍: 著变量类型1显示函数
  应用在PDS等单主变量或双主变量界面。  
*
* 关键备注：
* - 

  
* 未来提高:
*/ 
static void DynamicPV_Type1ShowHandle(uchar ShowLineIndex)
{
  uint StrNum;
  uchar LineOffset = 0,j = ShowLineIndex,ItemHighFactor = 0;
  uchar StartY = 0;
  uint VariableIndex = 0;
  FontMatrixDef FontMatrix = {0};
  
  uchar *ShowData = NULL,Temp[SHOW_DATA_BUF_SIZE] = {0},LengthInter = 0;
  uchar ShowWordsNumber = 0;
  const HART_UnitDef* UnitTable = NULL;
  PageDef *PagePtr = NULL;
  union FloatToChar
  {
          uchar Char[4];
          float Float;
  }F_C;

  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  //页面命令组加载函数
  MENU_PageCommandGroupLoad(PagePtr);
  MENU_PageShowSwitch(FALSE);

  MENU_FontMatrixGet(&FontMatrix,(G_StrStruct+j)->FontNum[MENU_LanguageTypeGet()]);
  ShowWordsNumber = COMMON_STRING_SIZE-1;
  if(MENU_LanguageTypeGet() == ENGLISH)
  {
    StartY =  START_Y_INDEX;
    ItemHighFactor = ITEM_HIGHT;
    LineOffset = FontMatrix.HorizontalLine*3;
  }
  else if(MENU_LanguageTypeGet() == CHINESE)
  {
    StartY =  START_Y_INDEX+1;
    ItemHighFactor = ITEM_HIGHT*2;
    LineOffset = FontMatrix.HorizontalLine;
  }
  //PV动态变量说明显示
  DynamicDescriptionDisplay(PagePtr,0,j,1,ShowLineIndex,ItemHighFactor,LineOffset);
  j++;
  //动态变量显示
  VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
  //加载动态显示变量
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  //获取HART变量功能码对照表数组指针
  UnitTable = MENU_GetHartUnitTable(VariableIndex); 

  if(MENU_GetMenuTreeIndex() == RADAR)
  {
    //锐达仪表雷达设备，单位m
    StrNum = STR_INDEX_201;
  }
  else
  {
    StrNum = HART_UnitShowHandle(UnitTable,ShowData);
  }
  //动态变量显示
  VariableIndex = MENU_VariableIndexInfoGet(1,G_VariableGroupTable);
  //加载动态显示变量
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  BufReverseCopy(F_C.Char,ShowData,FLOAT_T);
  LengthInter = ModbusFloatToASCIIConvert(F_C.Float,3,Temp);
  LengthInter += 4;


  //后续需要补充单位代码对应表
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter] = 0x00; 
  FlashStringReadLockHandle(j,StrNum,ENGLISH);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
    START_X_INDEX+(ShowWordsNumber-LengthInter-(G_StrStruct+j-1)->RealCharacterNumber[MENU_LanguageTypeGet()])*6,
      StartY+ShowLineIndex*(ItemHighFactor),NORMAL,ENGLISH); 
  MENU_StaticStringShow(G_StrStruct+j,
    START_X_INDEX+(ShowWordsNumber-(G_StrStruct+j)->RealCharacterNumber[ENGLISH])*6,
      StartY+ShowLineIndex*(ItemHighFactor),ENGLISH,NORMAL,G_StringCodeBuff[j]);  
  ShowLineIndex++;
  j++;
  F_C.Float = 0;
  //SV
  DynamicDescriptionDisplay(PagePtr,1,j,2,ShowLineIndex,ItemHighFactor,LineOffset);
  j++;
   //动态变量显示
  VariableIndex = MENU_VariableIndexInfoGet(3,G_VariableGroupTable);
  //加载动态显示变量
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  BufReverseCopy(F_C.Char,ShowData,FLOAT_T);
  LengthInter = ModbusFloatToASCIIConvert(F_C.Float,3,Temp);
  LengthInter += 4;
  //后续需要补充单位代码对应表
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter++] = 0x25;
  Temp[LengthInter] = 0x00;

  MENU_DynamicStringShow(ASCII_6X8,Temp,
            START_X_INDEX+(ShowWordsNumber-LengthInter)*6,
                                    StartY+ShowLineIndex*(ItemHighFactor),NORMAL,ENGLISH);  
  ShowLineIndex++;
  F_C.Float = 0;
  //TV
  DynamicDescriptionDisplay(PagePtr,2,j,3,ShowLineIndex,ItemHighFactor,LineOffset);
  j++;
   //动态变量显示
  VariableIndex = MENU_VariableIndexInfoGet(2,G_VariableGroupTable);  //加载动态显示变量
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  BufReverseCopy(F_C.Char,ShowData,FLOAT_T);
  LengthInter = ModbusFloatToASCIIConvert(F_C.Float,3,Temp);
  LengthInter += 4;
  //后续需要补充单位代码对应表
  Temp[LengthInter++] = 0x20;
  Temp[LengthInter++] = 0x6d;
  Temp[LengthInter++] = 0x41;
  Temp[LengthInter] = 0x00;

  //经过FloatToAscii之后FontMatrix被莫名改动
  MENU_DynamicStringShow(ASCII_6X8,Temp,
      START_X_INDEX+(ShowWordsNumber-LengthInter)*6,
           StartY+ShowLineIndex*(ItemHighFactor),NORMAL,ENGLISH);  
  DynamicPackageHandle(j);
}
/*
//函数名称和参量和返回值类型。
static void SucRateShow(const PageDef* CurrentPage,uchar ShowLineIndex);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
成功率显示函数
*
* 关键备注：
* - 

  
* 未来提高:
*/
static void SucRateShow(const PageDef* CurrentPage,uchar ShowLineIndex)
{
  uchar Temp[SHOW_DATA_BUF_SIZE] = {0};
  //成功率界面
  if(G_ComPCT_Temp <= 1.0)
    G_ComPCT_Temp = G_ComPCT_Temp*100;
  ModbusFloatToASCIIConvert(G_ComPCT_Temp,3,Temp);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
            42,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),NORMAL,ENGLISH); 
  MENU_DynamicStringShow(ASCII_6X8,"FN",
            0,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+1,NORMAL,ENGLISH); 
  ModbusFloatToASCIIConvert(G_FailureStatistics,0,Temp);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
            24,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+1,NORMAL,ENGLISH); 
  MENU_DynamicStringShow(ASCII_6X8,"SN",
            0,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+2,NORMAL,ENGLISH); 
  ModbusFloatToASCIIConvert(G_SuccessNum,0,Temp);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
            24,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+2,NORMAL,ENGLISH); 
  MENU_DynamicStringShow(ASCII_6X8,"DN",
            0,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+3,NORMAL,ENGLISH); 
  ModbusFloatToASCIIConvert(G_Denominator,0,Temp);
  MENU_DynamicStringShow(ASCII_6X8,Temp,
            24,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+3,NORMAL,ENGLISH); 
  if(G_ComPCT_SWITCH == FALSE)
  {
          MENU_DynamicStringShow(ASCII_6X8,"COMPLETE",
                                0,START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT)+4,NORMAL,ENGLISH); 
  }
}
/*
//函数名称和参量和返回值类型。
void GeneralLineShow(uchar StartItem,uchar EndItem,uchar ShowLineIndex,
                            const PageDef* CurrentPage,MenuTreeIndexDef MenuTreeIndex);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  通用行信息显示界面
*
* 关键备注：
* - 

  
* 未来提高:
*/ 
void GeneralLineShow(uchar StartItem,uchar EndItem,uchar ShowLineIndex,
                     const PageDef* PagePtr,uchar LineOffset)
{
  uchar *ShowData = NULL,Temp[SHOW_DATA_BUF_SIZE] = {0};
  uchar ItemHighFactor = 0,StartY = 0;
  DataTypeDef DataType = UCHAR_T;
  DataLengthDef DataLength = UCHAR;
  uchar j = 0;
  uint VariableIndex = 0;
  if(MENU_LanguageTypeGet() == ENGLISH)
  {
    ItemHighFactor = ITEM_HIGHT;
    StartY = START_Y_INDEX;
  }
  else if(MENU_LanguageTypeGet() == CHINESE)
  {
    ItemHighFactor = ITEM_HIGHT*2;
    StartY = START_Y_INDEX+1;
  }
  //行显示参数
  for(j = StartItem; j < EndItem;j++,ShowLineIndex++)
  {
    DynamicDescriptionDisplay(PagePtr,j,j+ShowLineIndex,j+1,ShowLineIndex,ItemHighFactor,LineOffset);
    //动态变量显示
    VariableIndex = MENU_VariableIndexInfoGet(j,G_VariableGroupTable);
    //加载动态显示变量
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
    DataType = MENU_GetHartVariableDataType(VariableIndex);
    DataLength = MENU_GetHartVariableDataLength(VariableIndex);

    HART_TypeConvert(ShowData,Temp,DataType,DataLength,ASCII_T);
    MENU_DynamicStringShow(ASCII_6X8,Temp,
            108,StartY+ShowLineIndex*(ItemHighFactor),NORMAL,ENGLISH);
  }
}
/*
//函数名称和参量和返回值类型。
void DynamicPV_Type2ShowHandle()
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍: 著变量类型2显示函数
  显示四个变量。  
*
* 关键备注：
* - 

  
* 未来提高:
*/ 
static void DynamicStatusGroupShowHandle(uchar ShowLineIndex)
{

	uchar LineNum[5] = {0};
	uchar Temp[SHOW_DATA_BUF_SIZE];

        HART_TypeConvert(G_PublicVC9,Temp,UCHAR_T,UCHAR,ASCII_T);
        //PV
	MENU_LineNumEdit(LineNum,1);
	MENU_DynamicStringShow(ASCII_6X8,LineNum,0,2,NORMAL,ENGLISH); 	
	MENU_DynamicStringShow(ASCII_6X8,"Group0",18,2,NORMAL,ENGLISH);

	MENU_DynamicStringShow(ASCII_6X8,Temp,108,2,NORMAL,ENGLISH);
}
/*
//函数名称和参量和返回值类型。
void DynamicPageShow(uint MenuTreeIndex)
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍:   
  动态信息页面显示函数，
  该页面下一般挂载需要实时监测的变量。
*
* 关键备注：
* - 

  
* 未来提高:
显示部分需要改进，因为数据部分保存方式都修改为字符类型，显示需要ASCII，所以
需要转换工作。
*/ 


void DynamicPageShow()
{ 
   uchar ShowLineIndex = 0,ShowLineNum = 0,ItemNumber = 0; 
   uchar StartItem = 0,EndItem,LineOffset = 0;
   FontMatrixDef FontMatrix = {0};
   PageDef *PagePtr = NULL;


   
   //获取菜单树序号
   PagePtr = MENU_GetCurrentMenuPage();
      
   ShowLineNum = PagePtr->SinglePageItemNumberV; 
   ItemNumber = PagePtr->ItemNumberV;
   
   //页面命令组加载函数
   MENU_PageCommandGroupLoad(PagePtr);
   MENU_PageShowSwitch(FALSE);
   MENU_TimingIntervalSelect();
    
   if(MENU_LanguageTypeGet() == ENGLISH)
   {
     FlashStringReadLockHandle(ShowLineIndex,PagePtr->TitleLineStringNum,ENGLISH);
     MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[MENU_LanguageTypeGet()]);
     LineOffset = FontMatrix.HorizontalLine*3;
     //菜单页面上端的两行说明标题
     ShowLineIndex = MENU_HeadlineShow(G_StrStruct+ShowLineIndex,(const void*)PagePtr,NORMAL,G_StringCodeBuff[ShowLineIndex]);     
     ShowLineIndex = MENU_ContentLineShow(PagePtr,ShowLineIndex,ENGLISH); 
   }
   //PV界面比较特殊，所以单独处理一下
   if(PagePtr->AdditionalInfo == PV_SHOW)
   {
      //HVP特殊处理
      if(HART_GetProductTypeAndID() == CHUAN_YI_HVPID)
      {
        DynamicPV_Type2ShowHandle(ShowLineIndex);
      }
      else
      {
        //通用情况下
        DynamicPV_Type1ShowHandle(ShowLineIndex);
      }
   }
   else if(PagePtr->AdditionalInfo == TRACK_SHOW)
   {
       //HVP特殊处理
      if(HART_GetProductTypeAndID() == CHUAN_YI_HVPID)
      {
        DynamicStatusGroupShowHandle(ShowLineIndex);
      }
   }
   else  if((MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE)&&
                            (MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_102))
   {
     //成功率显示
      SystemSucRateRegularHandle();
      SucRateShow(PagePtr,ShowLineIndex);
   } 
   else
   {
     //纵向显示参数获取，获取当前页面的起始项号及最终项号
     MENU_VerticalItemSwitchParamGet(&StartItem,
                    &EndItem,ShowLineNum,ItemNumber);     //通用信息行显示
     GeneralLineShow(StartItem,EndItem,ShowLineIndex,PagePtr,LineOffset);
   }
   //执行一次flash读取后，上锁
   FlashReadLockHandle(TRUE);
}
/*
//函数名称和参量和返回值类型。
static void DynamicPackageHandle();
* 变量范围:
j:锁定读取显存数组序号。
* 返回值说明:void 
* 功能介绍:   
  动态变量界面补丁处理函数，处理一些特殊显示的信息，比如第二主变量，需要区分产品类型
*
* 关键备注：
* - 

  
* 未来提高:

*/ 
static void DynamicPackageHandle(uchar j)
{
  uchar LineNum[5] = {0};
  uchar LengthInter,ShowWordsNumber;
  uchar Temp[SHOW_DATA_BUF_SIZE];
  uchar *StringE = "SV",*pStr = NULL;
  uchar StartY = 0,StartX = 0,StartV_Y = 0;
  FontDef FontType = ASCII_6X8;
  FontDef FontTypeStr = ASCII_6X8;
  //温度
  uint StringCH[] = {0x8d,0x8E,0x00};
  ShowWordsNumber = COMMON_STRING_SIZE-1;
  const HART_UnitDef* UnitTable = NULL;
  uint StrNum;

  union FloatToChar
  {
    uchar Char[4];
    float Float;
  }F_C;
  //川仪温度版PDS补丁，添加了第二主变量
  if((G_ManufacturerID[0] == 0xd4)
     &&((G_DeviceType[0] == 0x81)))
  {
    if(MENU_LanguageTypeGet() == ENGLISH)
    {
      StartY = 5;
      StartX = 18;
      FontType = ASCII_6X8;
      FontTypeStr = ASCII_6X8;
      pStr = StringE;
      StartV_Y = StartY;
    }
    else if(MENU_LanguageTypeGet() == CHINESE)
    {
      pStr = (uchar*)StringCH;
      FontType = ASCII_6X16;
      FontTypeStr = GB_12X16;
      StartY = 7;
      StartX = 12;
      StartV_Y = 6;
    }
    //编辑序号
    MENU_LineNumEdit(LineNum,4);
    MENU_DynamicStringShow(FontType,LineNum,0,StartV_Y,NORMAL,ENGLISH);     
    MENU_DynamicStringShow(FontTypeStr,pStr,StartX,StartV_Y,NORMAL,MENU_LanguageTypeGet());
    BufReverseCopy(F_C.Char,G_SV,FLOAT_T);
    LengthInter = ModbusFloatToASCIIConvert(F_C.Float,3,Temp);
    
    LengthInter += 4;
    Temp[LengthInter++] = 0x20;
    Temp[LengthInter] = 0x00;
    UnitTable = MENU_GetHartUnitTable(0XE7); 
    //川仪第二主变量是强制设定为温度的。
    G_SV_Unit[0] = 0X20;
    StrNum = HART_UnitShowHandle(UnitTable,G_SV_Unit);
    FlashStringReadLockHandle(j,StrNum,ENGLISH);
    MENU_DynamicStringShow(ASCII_6X8,Temp,
     (ShowWordsNumber-LengthInter-(G_StrStruct+j)->RealCharacterNumber[ENGLISH])*6,
          StartY,NORMAL,ENGLISH);
    MENU_StaticStringShow(G_StrStruct+j,
      (ShowWordsNumber-(G_StrStruct+j)->RealCharacterNumber[ENGLISH])*6,StartY,ENGLISH,NORMAL,G_StringCodeBuff[j]);  
    MENU_CommandAdd(SECOND_VARIABLE);
  }
}
