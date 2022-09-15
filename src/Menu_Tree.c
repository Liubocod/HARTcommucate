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

#include "MenuInit.c"
#include "Flash.h"
#include "AT24C64.h"
#include "System.h"
#define EFFECTIVE_STR_LENGTH 20

#define IS_HANDLE_FLAG(INSTANCE)  ((INSTANCE == OptionsLeft)\
  ||(INSTANCE == EndingOption)||(INSTANCE == InputCursor))
#define IS_DISPLAY_MODE(INSTANCE)  ((INSTANCE == NORMAL)\
  ||(INSTANCE == REVERSE_DISPLAY))
#define IS_VALID_FONT(INSTANCE)    ((INSTANCE == ASCII_6X16)\
  ||(INSTANCE == GB_12X16)||(INSTANCE == ASCII_5X8)||(INSTANCE == ASCII_6X8))


uchar G_CursorNumH = 0,G_CursorNumV = 0;
uchar G_PageChangeFlag = 0;
//单次执行命令发送变量，TRUE是单次发送，FALSE不是单次发送
bool8 G_SingleCommandLoad = TRUE;
PollingTypeDef G_ConnectWay = POLLING_STANDBY;
//区分编辑界面的自动加载和命令设定值
bool8 G_ParamLoadLock = TRUE;
//光标保护变量
uchar G_CursorTempV = 0;

void MENU_TimingIntervalSelect();
bool8 MENU_ItemParamLoad(const ItemDef* CurrentItemV);
//如果多菜单模式下，需要获取设备号，进行当前界面显示
#ifndef MULTIPLE_MENU_TREE
//起始通用初始化界面
CurrentPageDef  G_CurrentPage = {GENERAL_MENU_TREE,GENERAL_PAGE_INDEX_12,INITIAL_PAGE,ENGLISH};
//起始通用初始化界面
CurrentPageDef  G_CurrentPageTemp = {GENERAL_MENU_TREE,GENERAL_PAGE_INDEX_42,MENU_BAR,ENGLISH};
CurrentPageDef G_PreviousShowPage = {GENERAL_MENU_TREE,GENERAL_PAGE_INDEX_42,MENU_BAR,ENGLISH};

CurrentPageStructDef G_CurrentPageStruct = {0};
CurrentItemStructDef G_CurrentItemStruct = {0};
StringStructDef G_StringStruct = {0};
StringDef G_StrStruct[SHOW_STRING_BUFF_SIZE] = {0};
uchar G_StringCodeBuff[SHOW_STRING_BUFF_SIZE][COMMON_STRING_SIZE] = {0};
uchar G_WordLibrary[WORD_LIBRARY_BUFF_SIZE] = {0};

#endif
AdditionalInfoDef G_WarningPageRefreshFlag = ADDITION_STANDBY;
AdditionalInfoDef G_WaitingPageRefreshFlag = ADDITION_STANDBY;

//变量设定到仪表之前需要进行特殊运算的变量，是否开启本地计算特殊
bool8 G_IsSpecificHandle = FALSE;

bool8 MENU_PageRefreshIntervalHandle(void);
MenuTreeIndexDef MENU_GetMenuTreeIndex();
static void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage);
static void MENU_SiementsReturnPageSave(const PageDef* CurrentPage);
static uchar MENU_ContentLinePrint(const PageDef *const CurrentPage,uchar ShowLineIndex,LanguageTypeDef Language);
static void MENU_NoUnitVariableShow(uchar ShowVariableIndex,uchar line
                             ,CursorShowModeDef CursorShowMode,StringDef StrStruct,uchar* StrCodeBuff);
static void MENU_ItemVDisplay(FontDef IndexFront,const PageDef* const PagePtr,
           uchar j,uchar StructIndex,LanguageTypeDef Language,uchar LineOffset,
                                CursorShowModeDef CursorShowMode,uchar ItemHigh,uchar i,uchar *LineNum);
/**
 //函数名称和参量和返回值类型。
void  MENU_KeySwitchPageHandle()
* 变量范围:

* 返回值说明:void 
* 功能介绍:   
按键切换页面处理函数，
根据当前页面对应的有效按键，改变显示状态。
*
* 关键备注：
* - 
页面切换函数的主要功能是在当前页面的一些按键操作被触发后，
形成的一些画面改动，比如说菜单页面中菜单项的上下选择，
或者选中菜单项跳转到其他界面，或者在操作界面处理完任务后，
确认返回上一级页面等，这个函数主要应用到对当前显示界面全局变量的操作，
先判断当前页面的类型，判断出页面类型就会知道应该如何处理这个页面，
比如菜单翻页，参数修改，或者退出信息提示页面等。

  
* 未来提高:



* 
*/ 
void  MENU_KeySwitchPageHandle()
{
  MENU_PageTypeSelect(G_KeyValue);
  PageDef *PagePtr = NULL;
  if(G_KeyValue != NO_KEY_STATUS)
  {
   PagePtr = MENU_GetCurrentMenuPage();
   if(PagePtr->ConnectWay == REFRESH)
   {
     if((PagePtr->AdditionalInfo == PV_SHOW)
        ||(PagePtr->AdditionalInfo == FIVE_HUNDRED_MS))
     {
        if(G_KeyValue == LEFT)
          MENU_PageShowSwitch(TRUE);
     }
     else if(PagePtr->AdditionalInfo == CURVE_HANDLE)
     {
        MENU_PageShowSwitch(TRUE);
     }
     else
     {
        if(G_KeyValue == OK)
            MENU_PageShowSwitch(TRUE);
     }
   }
   else
   {
     MENU_PageShowSwitch(TRUE);
   }
   G_PowerOffCounter = 0;
  }
  //按键处理完毕之后，要将状态修改成空闲。要将处理状态改为完成处理。
  G_KeyValue =  NO_KEY_STATUS;
}
/**
 //函数名称和参量和返回值类型。
void MENU_PageTypeSelect(KeyValueDef Key);
* 变量范围:
KeyValueDef Key，按键类型。

* 返回值说明:void 
* 功能介绍:   
页面处理类型选择函数，
判断当前显示界面的类型，调用相应的页面处理函数。
*
* 关键备注：
* - 

  
* 未来提高:
会添加事件处理函数。


*/
void MENU_PageTypeSelect(KeyValueDef Key)
{
    if(MENU_CurrentPageTypeGet() == EXPLANATION_PAGE)
    {
        EXP_PageHandle(Key);
    }
    else if(MENU_CurrentPageTypeGet() == DYNAMIC_PAGE)
    {
       DynamicPageHandle(Key);
    }
    else if(MENU_CurrentPageTypeGet() == MENU_BAR)
    {
       MenuCurrentPageHandle(Key);
    } 
    else if(MENU_CurrentPageTypeGet() == INFO_PAGE)
    {
       InfoPageHandle(Key);      
    }
    else if(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE)
    {
       ParamSetPageHandle(Key);
    } 
    else if(MENU_CurrentPageTypeGet() == EDIT_PAGE)
    {
       EditPageHandle(Key);
    }
    else if(MENU_CurrentPageTypeGet() == PASWD_PAGE)
    {
       PasswordMatchingHandle(Key);
    }
    else if((MENU_CurrentPageTypeGet() == WAITING_PAGE)||(MENU_CurrentPageTypeGet() == WARNING_PAGE))
    {
      WarningPageHandle();
    }
    else if(MENU_CurrentPageTypeGet() == CURVE_PAGE)
    {
      CurvePageHandle(Key);
    }
    else if(MENU_CurrentPageTypeGet() == CURVE_OPT_PAGE)
    {
      CurveOperationPageHandle(Key);
    }
}

/*
 //函数名称和参量和返回值类型。
void MENU_PageShow()
* 变量范围:
PageDef   G_CurrentPage：
取值范围参见PageDef定义。

* 返回值说明:void 
* 功能介绍:   
根据当前页面结构体提供的页面信息，显示当前的页面。
*
* 关键备注：
* - 
首先，获得菜单树的编号，找到了菜单树的编号就找到了对应产品的菜单信息了，
包括菜单项，系统字符串等数组的首地址。
然后获得当前页面的类型，根据类型，调用不同的页面显示函数，比如菜单页面显示函数，
编辑页面显示函数等，调用不同的函数是因为各类页面的显示都有所差异。 
* 未来提高:
会添加其他页面类型的显示函数。
*/ 
void MENU_PageShow()
{ 
  //如果上一个页面与当前的页面不相同，调用清屏函数，再将当前页面赋给先前页面变量
  if((G_PreviousShowPage.CurrentMenuTreeIndex != MENU_GetMenuTreeIndex())||(G_PreviousShowPage.CurrentPageNum != MENU_CurrentPageNumGet())
     ||(G_PreviousShowPage.PageType != MENU_CurrentPageTypeGet())||(G_PreviousShowPage.Language != MENU_LanguageTypeGet()))
  {
    MENU_ClearLcdScreen();
    G_PreviousShowPage = G_CurrentPage;
  }
  if(MENU_CurrentPageTypeGet() == MENU_BAR)
  {
      MenuPageShow(); 
  }
  else if(MENU_CurrentPageTypeGet() == DYNAMIC_PAGE)
  {
      DynamicPageShow();
  }
  else if(MENU_CurrentPageTypeGet() == PASWD_PAGE)
  {
      PassWordMatchingShow();
  }
  else if(MENU_CurrentPageTypeGet() == INITIAL_PAGE)
  {
      InitialPageShow();
      //MENU_TimingIntervalSelect();
      //手操器版本显示界面，需要停顿3秒，便于观察
      while(1)
      {
        if(G_WarningTimeStamp == 0)
        {
          break;
        }
        //看门狗喂狗       
        FEED_DOG = ~FEED_DOG;
      }
  }
  else if(MENU_CurrentPageTypeGet() == EXPLANATION_PAGE)
  {
      EXP_PageShow();
  }
  else if(MENU_CurrentPageTypeGet() == INFO_PAGE)
  {
      InfoPageShow();   
  }
  else if(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE)
  {
      ParamSetPageShow();
  }
  else if(MENU_CurrentPageTypeGet() == WARNING_PAGE)
  {
      WarningPageShow();
      //需要在警告界面停留1秒,如果需要其他时间间隔数值，可以switch语句
      G_WarningPageRefreshFlag = WARNING_START;
      MENU_TimingIntervalSelect();
  }
  else if(MENU_CurrentPageTypeGet() == POLLING_PAGE)
  {
      PollingPageShow();
  }
  else if(MENU_CurrentPageTypeGet() == EDIT_PAGE)
  {
     EditPageShow();
  }
  else if(MENU_CurrentPageTypeGet() == CURVE_PAGE)
  {
     CurvePageShow();
  }
  else if(MENU_CurrentPageTypeGet() == CURVE_OPT_PAGE)
  {
     CurveOperationPageShow();
  }
  else if(MENU_CurrentPageTypeGet() == WAITING_PAGE)
  {
    WarningPageShow();
    G_WaitingPageRefreshFlag = WARNING_START;
  }
  
}
/**
 //函数名称和参量和返回值类型。
uchar MENU_HeadlineShow(const StringDef* StrStruct,const PageDef* Page,CursorShowModeDef CursorMode);
* 变量范围:
const StringDef* StrStruct：字符串结构体
const PageDef* Page：页面指针。
CursorShowModeDef CursorMode：光标显示方式。
* 返回值说明:返回标题行所占行数，为后面要显示内容提供坐标指示。 
* 功能介绍:   
显示标题行。
*
* 关键备注：
* - 

  
* 未来提高:
会添加事件处理函数。
会添加其他类型界面。
*/

uchar MENU_HeadlineShow(StringDef* const StrStruct,
                        const PageDef* const CurrentPage,
                        CursorShowModeDef CursorMode,uchar* StringCodeArr)
{
    uchar i = 0,j;
    uchar Headline[] = {0x28,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00};//Tag，待续
    FontMatrixDef FontMatrix; 
    FlashStringCodeGet(StrStruct,StringCodeArr,ENGLISH);
    MENU_StaticStringShow(StrStruct,START_X_INDEX,
             START_Y_INDEX,ENGLISH,NORMAL,StringCodeArr);
    //如果标题行为Online时的标题行显示处理
    if(StrStruct->StructNum == 0x01) 
    {
      j = HART_ASCII_Decode(Headline+1,ASCII_6,ASCII_8,G_Tag);
      Headline[j+1] = 0x29;//右括号
      MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[ENGLISH]);
      MENU_DynamicStringShow(ASCII_6X8,Headline,
                    START_X_INDEX+(StrStruct->CharacterNumber[ENGLISH])*FontMatrix.HorizontalLine, 
                                     START_Y_INDEX,NORMAL,ENGLISH);
    }
    i++; 
    return  i;  
}
/**
 //函数名称和参量和返回值类型。
static void MENU_DisplayWords();
* 变量范围:
const StringDef* StrStruct：字符串结构体
const PageDef* Page：页面指针。
CursorShowModeDef CursorMode：光标显示方式。
* 返回值说明:返回标题行所占行数，为后面要显示内容提供坐标指示。 
* 功能介绍:   
显示标题行。
*
* 关键备注：
* - 

  
* 未来提高:
会添加事件处理函数。
会添加其他类型界面。
*/
static void MENU_DisplayWords(uchar CharacterHorizontalLine,uchar CharacterVerticalLine
                              ,uchar VerticalPostion,uchar TempN,uchar HorizontalPostion,CursorShowModeDef CursorShowMode
                                ,long unsigned int TempLibrary,unsigned int IntTemp)
{
  unsigned char Tmpi,Tmpj;
  uchar ColumnSetIndex = 0,PageSetIndex = 0;
  uint DataNumber = CharacterHorizontalLine*CharacterVerticalLine;
  
  FlashWordLibInfoGet(TempLibrary+IntTemp,DataNumber,G_WordLibrary);
  //开始刷点，自上而下，自左而右
  for(Tmpi = 0; Tmpi < CharacterVerticalLine; Tmpi++)
  {
      //设定纵坐标
      LcdSetPage(VerticalPostion+Tmpi);
      //设定横坐标                   
      LcdSetColumn(CharacterHorizontalLine*TempN+HorizontalPostion);

      //按行，逐列刷满
      for(Tmpj = 0; Tmpj < CharacterHorizontalLine; Tmpj++)
      {
          ColumnSetIndex = CharacterHorizontalLine*TempN+HorizontalPostion + Tmpj;
          PageSetIndex = VerticalPostion+Tmpi;
          if(ColumnSetIndex >= LCD_MAX_BOUNDARY)
            break;
          LCD_CS_Switch(ColumnSetIndex,PageSetIndex);

          if(CursorShowMode == REVERSE_DISPLAY)
          {
            //反显
            LcdWriteData(~G_WordLibrary[Tmpj+Tmpi*CharacterHorizontalLine]);
          }
          else if(CursorShowMode == NORMAL)
          {
            LcdWriteData(G_WordLibrary[Tmpj+Tmpi*CharacterHorizontalLine]);
          }
      }
  }
}
/*
 //函数名称和参量和返回值类型。
void	MENU_StaticStringShow(StringDef StrStructure,uchar HorizontalPostion,uchar VerticalPostion
                                                            CursorShowModeDef CursorShowMode)
* 变量范围:
StringDef StrStructure：
//字符串结构体定义
typedef struct 
{
  uint StructNum;                              //字符串编号
  FontDef FontNum[LANGUAGE_NUMBER];            //字库编号
  uchar CharacterNumber;                       //字符个数 
  const uint *LanguageTypeNum[LANGUAGE_NUMBER];//语种指针数组 
}StringDef;
HorizontalPostion：水平位置
VerticalPostion：垂直位置

CursorShowModeDef CursorShowMode：光标模式
typedef enum
{
  HIDE,
  REVERSE_DISPLAY,
  FLASH
}CursorShowModeDef;


* 返回值说明:void 
* 功能介绍:   
  显示静态字符串，比如标题，菜单项等。
*
* 关键备注：
* - 
  CharacterHorizontalLine：水平方向列的个数。
  CharacterVerticalLine：垂直方向字节的个数。

  const uint *LanguageTypeNum[LANGUAGE_NUMBER];//语种指针数组 
  FontDef FontNum[LANGUAGE_NUMBER];          //字库编号
  上面的两项是为了确定语言的，显示什么语言要利用
  typedef enum
  {
    ENGLISH = 0,
    CHINESE
  }LanguageTypeDef;
  在显示页面变量G_CurrentPage中有一个语言类型的定义，可以根据这个序号来
  确定当前显示的语言。
  每种字体的字串都会被存放到独立的数组中，索引的序号都是字符串结构体的序号。

* 未来提高:
字符串或汉字显示函数,要分到显示.c文件中


*/ 


void MENU_StaticStringShow(const StringDef* const StrStruct,uchar HorizontalPostion,uchar VerticalPostion,
                                        LanguageTypeDef Language,CursorShowModeDef CursorShowMode,const uchar *StructE)
{
	unsigned char CharacterHorizontalLine,CharacterVerticalLine,TempN;
        FontMatrixDef FontMatrix;
        FontDef Font;
	unsigned int IntTemp = 0;
        union 
        {
          uint iStructData;
          uchar cStructData[sizeof(uint)];
        }DataConvert;
	long unsigned int TempLibrary;
        
	TempN = 0;
        Font = StrStruct->FontNum[Language];
        MENU_FontMatrixGet(&FontMatrix,Font);
        CharacterHorizontalLine = FontMatrix.HorizontalLine;
        CharacterVerticalLine = FontMatrix.VerticalLine;
        TempLibrary = FontMatrix.Library;
	
        
	for(TempN = 0; TempN < StrStruct->CharacterNumber[Language];TempN++)
	{
                //字库中显示一个字符的总点数，每一个点为一个字节
		IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
                //根据字符在字库的哪一行，乘以这一行刷屏的字节个数，计算出字符在字库中的具体序号
                if(Font == ASCII_6X8)
                {
                    if(TempN >= StrStruct->RealCharacterNumber[Language])
                    {
                      IntTemp = 0;
                    }
                    else
                      IntTemp = (StructE[TempN]-' ')*IntTemp;
                }
                else if(Font == GB_12X16)
                {
                  DataConvert.cStructData[0] = StructE[TempN*2];
                  DataConvert.cStructData[1] = StructE[TempN*2+1];
                  IntTemp = DataConvert.iStructData*IntTemp;
                }
                //开始刷点，自上而下，自左而右
		MENU_DisplayWords(CharacterHorizontalLine,CharacterVerticalLine,
                              VerticalPostion,TempN,HorizontalPostion,CursorShowMode,TempLibrary,IntTemp);

	}
}
/*
 //函数名称和参量和返回值类型。
void MENU_FontMatrixGet(FontMatrixDef *FontMatrix,FontDef Font)
* 变量范围:
FontMatrixDef *FontMatrix：
typedef struct 
{
  uchar HorizontalLine;
  uchar VerticalLine;
  const uchar *Library;
}FontMatrixDef;

FontDef Font：
typedef enum 
{
  ASCII_6X16,
  GB_12X16,
  ASCII_5X8
}FontDef;

* 返回值说明:void 
* 功能介绍:  
  字库矩阵信息获取函数，获取当前字库的点阵信息，横纵点数。

*
* 关键备注：
* - 
本函数主要是为了获取每个字的横向占用宽度以及纵向占用宽度，用来计算字符串
间间隔的。 
* 未来提高:
会添加新的字库
*/ 
void MENU_FontMatrixGet(FontMatrixDef *const FontMatrix,FontDef Font)
{
  long uint addr = 0;
    switch(Font)
    {
            case ASCII_6X16:
                    FontMatrix->HorizontalLine = 6;
                    FontMatrix->VerticalLine = 2;		//12/8
                    GET_DATASHEET_ADDR(ASCII_6X16_LIB_,(uchar*)&addr);
                    FontMatrix->Library = addr;
                    break;
            case ASCII_5X8:
                    FontMatrix->HorizontalLine = 5;
                    FontMatrix->VerticalLine = 1;		//12/8
                    GET_DATASHEET_ADDR(ASCII_6X8_LIB_,(uchar*)&addr);
                    FontMatrix->Library = addr;
                    break;  
            case GB_12X16:
                    FontMatrix->HorizontalLine = 12;
                    FontMatrix->VerticalLine = 2;		//12/8
                    GET_DATASHEET_ADDR(ASCII_12X16_LIB_,(uchar*)&addr);
                    FontMatrix->Library = addr;
                    break;
            case ASCII_6X8:
                    FontMatrix->HorizontalLine = 6;
                    FontMatrix->VerticalLine = 1;		//12/8
                    GET_DATASHEET_ADDR(ASCII_6X8_LIB_,(uchar*)&addr);
                    FontMatrix->Library = addr;
            default:break; 
    }
}

/*
 //函数名称和参量和返回值类型。
void MENU_DynamicStringShow(FontDef LibraryIndex,uchar *String,uchar HorizontalPostion,uchar VerticalPostion,
                                                                            CursorShowModeDef CursorShowMode);
* 变量范围:
FontDef LibraryIndex:字库索引，用来确定显示的字属于哪个字库
uchar *String：要显示的字串内容。
uchar HorizontalPostion：水平坐标。
uchar VerticalPostion：垂直坐标。
CursorShowModeDef CursorShowMode：光标显示模式。
* 返回值说明:void 
* 功能介绍:   
* 用于显示非常规字符串的函数，比如动态变化的数据。
* 关键备注：
* - 
* 未来提高:
*/ 

void MENU_DynamicStringShow(FontDef LibraryIndex,uchar *const String,uchar HorizontalPostion,uchar VerticalPostion,
                                                                            CursorShowModeDef CursorShowMode,LanguageTypeDef Language)
{
    unsigned char CharacterHorizontalLine,CharacterVerticalLine,TempN;
    FontMatrixDef FontMatrix;
    uint *StringCH = NULL;
    unsigned int IntTemp = 0;
    long unsigned int TempLibrary;
    TempN = 0;

    MENU_FontMatrixGet(&FontMatrix,LibraryIndex);
    CharacterHorizontalLine = FontMatrix.HorizontalLine;
    CharacterVerticalLine = FontMatrix.VerticalLine;
    TempLibrary = FontMatrix.Library;
    if((LibraryIndex == ASCII_6X16)||(LibraryIndex == ASCII_6X8))
    {
      while(String[TempN] != '\0')
      {
          if(TempN >= 21)break;
          //字库中显示一个字符的总字节个数数
          IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
          //计算出字符串中字符在字库的哪一行，字库一行是一个字符。
          IntTemp = (String[TempN]-0x20)*IntTemp;
          //开始刷点，自上而下，自左而右
          MENU_DisplayWords(CharacterHorizontalLine,CharacterVerticalLine,
                        VerticalPostion,TempN,HorizontalPostion,CursorShowMode,TempLibrary,IntTemp);
          TempN++;
      }
    }
    else if(LibraryIndex == GB_12X16)
    {
      StringCH = (uint*)String;
      while(StringCH[TempN] != '\0')
      {
          if(TempN >= 11)break;
          //字库中显示一个字符的总字节个数数
          IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
          //计算出字符串中字符在字库的哪一行，字库一行是一个字符。
          IntTemp = StringCH[TempN]*IntTemp;
          //开始刷点，自上而下，自左而右
          MENU_DisplayWords(CharacterHorizontalLine,CharacterVerticalLine,
                        VerticalPostion,TempN,HorizontalPostion,CursorShowMode,TempLibrary,IntTemp);
          TempN++;
      }
    }
}

/*
 //函数名称和参量和返回值类型。
void	MENU_ClearLcdScreen(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  清屏函数。

*
* 关键备注：
* - 

  
* 未来提高:
需要移至显示文件中。


*/ 
void	MENU_ClearLcdScreen(void)
{
	unsigned char Tmpi,Tmpj;
	Tmpi = 8;
	do
	{
		Tmpi--;
		LcdSetPage(Tmpi);
		LcdSetColumn(0);
		for(Tmpj = 0; Tmpj < LED_LINE_PIXEL_NUM; Tmpj++)
		{
                  LCD_CS_Switch(Tmpj,Tmpi);
                  LcdWriteData(0);
		}
	}while(Tmpi != 0);
}
/*
 //函数名称和参量和返回值类型。
void MenuPageRefrashTimeLoad(const PageDef *CurrentPage);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  菜单页面命令组加载函数，
  负责将当前显示页面中挂载的变量的命令号提取出来，经过消除重复项后保存到命令
  执行数组当中（目前只挂载HART变量）。

*
* 关键备注：
* - 
 页面的链接方式有多种，POLLING_STANDBY表示无轮询状态，也就是非特殊链接方式。
  
* 未来提高:



*/ 
void MENU_PageCommandGroupLoad(const PageDef *const CurrentPage)
{
  uint i=0,VariableIndex;
  uchar CommandIndexCount = 0;
  
  //如果链接方式是不轮询，不做处理，否则需要进行命令执行数组加载操作
  G_ConnectWay = CurrentPage->ConnectWay;
  //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
  FlashVariableGroupLoad(CurrentPage->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);

  //如果当前页面为无命令页面
  if(CurrentPage->ConnectWay == POLLING_STANDBY)
  {
  
  }
  else
  {
    //根据当前页面挂载的变量个数对命令进行整理，将重复的命令号去掉
    for(i = 0;i < MENU_PageVariableNumber(G_PageVariableTable);i++)
    {
      //提取变量在变量当前页面变量数组中的序号
      VariableIndex = MENU_VariableIndexInfoGet(i,G_VariableGroupTable);
      //HART命令执行数组加载函数，更具变量索引在变量数组中找到对应的命令编号，并将计数变量通过实参形式返回
      FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
      HART_CommandExecuteArrLoad(G_VariableStructureInfo.VariableStructureInfo.CommandIndex,
                                 &CommandIndexCount);
    }
    if((CurrentPage->ConnectWay == INIT_CONNECT)||(CurrentPage->ConnectWay == HALF_CONNECT_0)
       ||(CurrentPage->ConnectWay == HALF_CONNECT_8)||(CurrentPage->ConnectWay == ALL_CONNECT)
            ||(CurrentPage->ConnectWay == ALL_CONNECT_31)||(CurrentPage->ConnectWay == ALL_CONNECT_63)
                                                          ||(CurrentPage->ConnectWay == SINGLE_CONNECT))
    {
      //与初始化命令组相关的，需要将HART操作标志设定为HART初始化命令操作。
      G_HART_HandleFlag = HART_INIT_COMMAND_HANDLE;
    }
    else if((CurrentPage->ConnectWay == REFRESH)||(CurrentPage->ConnectWay == WAITING_CONNECT)
            ||(CurrentPage->ConnectWay == COMMON_PAGE_CONNECT))
    {
      //如果是非初始化链接方式，将HART处理标志变量赋值为通用命令处理。
      G_HART_HandleFlag = HART_COMMON_COMMAND_HANDLE;
    }
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = CommandIndexCount;
    G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
  }
}
/*
 //函数名称和参量和返回值类型。
void MENU_PageShowSwitch()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
页面显示切换函数。
需要改变屏显内容时将Flag设置成TRUE,不需要改变屏显内容时，将其关闭，Flag设置成FALSE
*
* 关键备注：
* - 
  
* 未来提高:


函数名Update修改

*/ 
void MENU_PageShowSwitch(bool8 Flag)
{
   G_PageChangeFlag = Flag;
}

 /*/函数名称和参量和返回值类型。
void MENU_LineNumEdit(uchar *const LineNum,uchar LineTemp)
* 变量范围:
     LineNum:行号数组。
     LineTemp：行号参考变量。
* 返回值说明:void 
* 功能介绍:   
  行号编辑函数，将菜单的序号有序的制作成数组，为显示提供条件。
*
* 关键备注：
* - 
本函数也可用于编辑有序递增的序号。
注意，本函数只适合255以内的序号编辑，若超过这个范围需要修改参数数据类型。
* 未来提高:



*/
uchar MENU_LineNumEdit(uchar *const LineNum,uchar LineTemp)
{
  uchar LineIndex = 0;
  uchar Scaleplate = 100;
  if(LineTemp != 0)
  {
     while(((LineTemp/Scaleplate) == 0)&&(LineTemp > 0))
     {
        Scaleplate /=10;
     }
     while(Scaleplate != 1)
     {
        LineNum[LineIndex++] = LineTemp/Scaleplate+0x30;
        LineTemp %= Scaleplate;
        Scaleplate /=10;
     }
     if(Scaleplate == 1)
     {
        LineNum[LineIndex++] = LineTemp+0x30;
     }
     LineNum[LineIndex] = 0x20;
     LineNum[LineIndex+1] = 0x20;
     LineNum[LineIndex+2] = 0x00;
  }
  else
  {
    LineNum[0] = 0x30;
    LineNum[1] = 0x20;
    LineNum[2] = 0x20;
    LineNum[3] = 0x00;
  }
  return LineIndex;
}
 /*/函数名称和参量和返回值类型。
void MENU_HorizontalItemShow(const PageDef* CurrentPage,const StringDef* StrStruct,
                                                const ItemDef* CurrentItemH,FontMatrixDef FontMatrix)

* 变量范围:
const PageDef* Page：页面指针。
const StringDef* StrStruct：字符串结构体指针。
* 返回值说明:void 
* 功能介绍:   
  水平菜单项
*
* 关键备注：
* - 

* 未来提高:



*/
void MENU_HorizontalItemShow(const PageDef* const CurrentPage,uchar BuffIndex,LanguageTypeDef Language)
{
   uchar j = 0,StartX = 0,StartY = 0;
   FontMatrixDef FontMatrix;
   const ItemDef* CurrentItemH;
   if(Language == ENGLISH)
   {
    StartY = 7;
   }
   else if(Language == CHINESE)
   {
    StartY = 6;
   }
   for(j = 0;j < CurrentPage->ItemNumberH;j++)
   {
     CurrentItemH = MENU_GetHorizontalItem(CurrentPage,j);
     FlashStringReadLockHandle(BuffIndex+j,CurrentItemH->StringNum,Language);
     MENU_FontMatrixGet(&FontMatrix,(G_StrStruct+BuffIndex+j)->FontNum[Language]);
     if(Language == ENGLISH)
     {
       if((G_StrStruct+j+BuffIndex)->RealCharacterNumber[MENU_LanguageTypeGet()] == 5)
       {
        //将横向菜单分配后剩余的像素给每一个横向菜单项，便于区分横向菜单项
        StartX = START_X_INDEX+(FontMatrix.HorizontalLine)*HORIZONTAL_ITEMS_BYTE_NUM*(HORIZONTAL_ITEMS_NUM-j-1);
       }
       else if((G_StrStruct+j+BuffIndex)->RealCharacterNumber[MENU_LanguageTypeGet()] < 5)
       {
        StartX = START_X_INDEX+(FontMatrix.HorizontalLine)*HORIZONTAL_ITEMS_BYTE_NUM*(HORIZONTAL_ITEMS_NUM-j-1)+FontMatrix.HorizontalLine;
       }
     }
     else
     {
      StartX = LCD_MAX_BOUNDARY-FontMatrix.HorizontalLine*2*(j+1)-8*j;
     }
     if(j == G_CursorNumH)
     {
       MENU_StaticStringShow(G_StrStruct+BuffIndex+j,StartX,StartY,MENU_LanguageTypeGet(),REVERSE_DISPLAY,G_StringCodeBuff[j+BuffIndex]); 
       if((CurrentItemH->ParamValue != NO_PARAM)&&(MENU_CurrentPageTypeGet() != PARAM_SET_PAGE))
       {
         if(CurrentPage->ContentStrIndex == STR_INDEX_105)
         {
         
         }
         else
          G_ParamLoadLock = MENU_ItemParamLoad(CurrentItemH);
       }
       else
        G_ParamLoadLock = MENU_ItemParamLoad(CurrentItemH);
     }
     else 
     {
        MENU_StaticStringShow(G_StrStruct+j+BuffIndex,StartX,StartY,MENU_LanguageTypeGet(),NORMAL,G_StringCodeBuff[j+BuffIndex]);             
     }
   }
}


/*/函数名称和参量和返回值类型。
const PageDef* MENU_GetCurrentMenuPage()
* 变量范围:
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:const PageDef* 返回页面结构体指针，及当前执行页面。 
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到当前显示页面的序号，并获得
当前页面的基本信息
*
* 关键备注：
* - 

* 未来提高:



*/
PageDef* MENU_GetCurrentMenuPage()
{
  MenuTreeIndexDef MenuTreeIndex = MENU_GetMenuTreeIndex();
  if(FlashReadLockStatusGet() == FALSE)
  {
    FlashCurrentPageInfoGet(MenuTreeIndex,
         G_CurrentPage.CurrentPageNum,G_CurrentPageStruct.CurrentPageInfoArr);
  }
  return &G_CurrentPageStruct.CurrentPageInfo;
}
/*/函数名称和参量和返回值类型。
PageDef* MENU_GetCurrentMenuPageTemporary()
* 变量范围:
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:const PageDef* 返回页面结构体指针，及当前执行页面。 
* 功能介绍:   
  为了减少读取FLASH的次数，增设了本函数，因为页面信息读取一遍就可以，
  数据已经保留在本地，因此直接获取数据指针进行访问即可。
*
* 关键备注：
* - 

* 未来提高:



*/

PageDef* MENU_GetCurrentMenuPageTemporary()
{
  return &G_CurrentPageStruct.CurrentPageInfo;
}
/*/函数名称和参量和返回值类型。
uint MENU_CurrentPageNumGet()
* 功能介绍:   
  备份页面序号返回函数
*
* 关键备注：
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* 未来提高:



*/
uint MENU_CurrentPageTempNumGet()
{
  return G_CurrentPageTemp.CurrentPageNum;
}
/**
 //函数名称和参量和返回值类型。
uchar MENU_GetMenuTreeIndexTemp()
* 变量范围:


* 返回值说明:菜单树序号 
* 功能介绍:   
备份页面菜单树序号获取函数
*
* 关键备注：
* - 

  
* 未来提高:
会添加事件处理函数。


*/
MenuTreeIndexDef MENU_GetMenuTreeIndexTemp()
{
  return G_CurrentPageTemp.CurrentMenuTreeIndex;
}
/*/函数名称和参量和返回值类型。
PageTypeDef MENU_CurrentPageTempTypeGet()
* 功能介绍:   
  备份页面类型返回函数
*
* 关键备注：
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* 未来提高:



*/
PageTypeDef MENU_CurrentPageTempTypeGet()
{
  return G_CurrentPageTemp.PageType;
}
/*
LanguageTypeDef MENU_TempLanguageTypeGet(void );
* 变量范围:


* 返回值说明:LanguageTypeDef,返回当前语言类型
* 功能介绍:   
*       备份页面语言种类读取函数，获取当前显示语言种类。
* 关键备注：
* - 

  
* 未来提高:




*/
LanguageTypeDef MENU_TempLanguageTypeGet(void )
{
  return G_CurrentPageTemp.Language;
}
/*/函数名称和参量和返回值类型。
uint MENU_CurrentPageNumGet()
* 功能介绍:   
  当前页面序号返回函数
*
* 关键备注：
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* 未来提高:



*/
uint MENU_CurrentPageNumGet()
{
  return G_CurrentPage.CurrentPageNum;
}
/**
 //函数名称和参量和返回值类型。
uchar MENU_GetMenuTreeIndex()
* 变量范围:


* 返回值说明:菜单树序号 
* 功能介绍:   
菜单树序号获取函数
*
* 关键备注：
* - 

  
* 未来提高:
会添加事件处理函数。


*/
MenuTreeIndexDef MENU_GetMenuTreeIndex()
{
  return G_CurrentPage.CurrentMenuTreeIndex;
}
/*/函数名称和参量和返回值类型。
PageTypeDef MENU_CurrentPageTypeGet()
* 功能介绍:   
  当前页面类型返回函数
*
* 关键备注：
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* 未来提高:



*/
PageTypeDef MENU_CurrentPageTypeGet()
{
  return G_CurrentPage.PageType;
}
/*
LanguageTypeDef MENU_LanguageTypeGet(void );
* 变量范围:


* 返回值说明:LanguageTypeDef,返回当前语言类型
* 功能介绍:   
*       语言种类读取函数，获取当前显示语言种类。
* 关键备注：
* - 

  
* 未来提高:




*/
LanguageTypeDef MENU_LanguageTypeGet(void )
{
  return G_CurrentPage.Language;
}
 /*/函数名称和参量和返回值类型。
const StringDef* MENU_GetStrStruct(uint MenuTreeIndex)
* 变量范围:
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:const StringDef* 返回字符串结构体指针。 
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到当前显示时需要用到的字符串库。
*
* 关键备注：
* - 

* 未来提高:



*/
StringDef MENU_GetStrStruct(uint StructNum)
{
  FlashStringInfoGet(StructNum,G_StringStruct.StringInfoArr);
  return G_StringStruct.StringInfo;
}
 /*/函数名称和参量和返回值类型。
uint MENU_VariableIndexInfoGet(uchar OffSet);
* 变量范围:
uint OffSet:变量组中的索引序号，找到指定变量，默认0为数组首个数值。
* 返回值说明:uint参数，在变量组中找到对应的变量表序号，可以访问变量信息。 
* 功能介绍:   
*       变量序号获取函数，通过偏移参数，
  在变量组中的找到对应的变量索引，通过该索引序号可以访问变量表中的变量信息。
* 关键备注：
* - 

* 未来提高:



*/
uint MENU_VariableIndexInfoGet(uchar OffSet,VariableGroupDef GroupTable)
{
  return GroupTable.VariableGroupI[OffSet];
}
/*/函数名称和参量和返回值类型。
uchar MENU_PageVariableNumber();
* 变量范围:
* 返回值说明:uchar 参数，当前页面变量组中的变量个数。 
* 功能介绍:   
*       页面变量个数获取函数，获取当前页面变量组中保存的变量总个数。
* 关键备注：
* - 

* 未来提高:



*/
uchar MENU_PageVariableNumber(PageVariableTableDef PageVariableTable)
{
  return PageVariableTable.PageVariableInfo.CurrentPageVariableNumber;
}
/*/函数名称和参量和返回值类型。
uchar* MENU_GetHartVariableDataType(uint VariableIndex,uint MenuTreeIndex)
* 变量范围:
uint VariableIndex:变量解析表的索引序号。
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:HART_DataTypeDef  返回HART变量的数据类型。
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到HART变量的数据类型。
*
* 关键备注：
* - 

* 未来提高:



*/
DataTypeDef MENU_GetHartVariableDataType(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.DataType; 
}
/*/函数名称和参量和返回值类型。
DataLengthDef MENU_GetHartVariableDataLength(uint VariableIndex,uint MenuTreeIndex)
* 变量范围:
uint VariableIndex:变量解析表的索引序号。
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:HART_DataTypeDef  返回HART变量的数据类型。
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到HART变量的数据类型。
*
* 关键备注：
* - 

* 未来提高:
*/
DataLengthDef MENU_GetHartVariableDataLength(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.DataLength; 
}
/*/函数名称和参量和返回值类型。
DataLengthDef MENU_GetHartVariableAnalysisLength(uint VariableIndex,uint MenuTreeIndex)
* 变量范围:
uint VariableIndex:变量解析表的索引序号。
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:HART_DataTypeDef  返回HART变量的数据类型。
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到HART变量的数据类型。
*
* 关键备注：
* - 

* 未来提高:



*/
DataLengthDef MENU_GetHartVariableAnalysisLength(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.AnalysisLength; 
}
/*/函数名称和参量和返回值类型。
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex,uint MenuTreeIndex)
* 变量范围:
uint VariableIndex:变量解析表的索引序号。
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:uchar * 返回HART变量字符串数组指针。
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到HART变量值的保存数组。
*
* 关键备注：
* - 

* 未来提高:



*/
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableTablePtr[G_VariableStructureInfo.VariableStructureInfo.VariablePtr]; 
}
/*/函数名称和参量和返回值类型。
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex)
* 变量范围:
uint VariableIndex:变量解析表的索引序号。
uint MenuTreeIndex:菜单树索引，确定当前显示的是哪一种产品的菜单树。
* 返回值说明:uchar * 返回HART变量字符串数组指针。
* 功能介绍:   
通过本函数，可以根据当前产品菜单树，找到HART变量值的保存数组。
*
* 关键备注：
* - 

* 未来提高:



*/
const HART_UnitDef* MENU_GetHartUnitTable(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return (G_UnitTableIndexPtr[G_VariableStructureInfo.VariableStructureInfo.Table]);
}
/*/函数名称和参量和返回值类型。
static void MENU_NoUnitVariableShow(uchar ShowVariableIndex,uchar line
                             ,CursorShowModeDef CursorShowMode)
* 变量范围:

* 返回值说明:void
* 功能介绍:   
菜单页面无单位行参数显示函数，
可以将有些没有单位的参数，直接显示在菜单页面的行后面。
*
* 关键备注：
* - 

* 未来提高:

后续可能会增加带有非标的单位参数显示程序，目前暂时没有此类界面。

*/
static void MENU_NoUnitVariableShow(uchar ShowVariableIndex,uchar line
                             ,CursorShowModeDef CursorShowMode,StringDef StrStruct,uchar* StrCodeBuff)
{
  uchar FloatStrTemp[ASCII_15] = {0},Length = 0,UnitLength = 0;
  DataLengthDef ReceiveDataLength = UCHAR;
  DataTypeDef DataType = UCHAR_T;
  uint VariableIndex = 0;
  const uchar* ShowData = NULL;
  uchar* StrTemp = NULL,StrCode[1] = {0X25};
  PageDef *PagePtr = NULL;


  
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  StrTemp = StrCodeBuff;
  //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
  VariableIndex = MENU_VariableIndexInfoGet(ShowVariableIndex,G_VariableGroupTable);
  ReceiveDataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);  
  DataType = MENU_GetHartVariableDataType(VariableIndex);
  //获取HART变量数组指针
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);

  Length = MENU_DataToASCII(ShowData,FloatStrTemp,DataType);
  if(PagePtr->AdditionalInfo == FIXED_UNIT_VSHOW)
  {
    //川仪HVP SL页面固定单位显示补丁
    if(PagePtr->ContentStrIndex == STR_INDEX_1042)
    {
      StrStruct = MENU_GetStrStruct(STR_INDEX_275);
      UnitLength = StrStruct.RealCharacterNumber[MENU_LanguageTypeGet()]+1;
      Length += UnitLength;
      StrTemp = StrCode;
    }
  }
  MENU_VariableShow(ReceiveDataLength,FloatStrTemp,line,PagePtr,(21-Length)*6,CursorShowMode);
  if((PagePtr->AdditionalInfo == FIXED_UNIT_VSHOW)
     ||(PagePtr->AdditionalInfo == UNIT_VSHOW))
  {
    MENU_StaticStringShow(&StrStruct,(21-UnitLength)*6,line,MENU_LanguageTypeGet(),CursorShowMode,StrTemp);  
  }
}
/*/函数名称和参量和返回值类型。
void MENU_VerticalItemShow(uchar StartItem,uchar EndItem,uchar i,
                           const PageDef* const CurrentPage,uchar LineOffset,
                           const StringDef*const StrStruct,const ItemDef*const CurrentItemV)
* 变量范围:

* 返回值说明:void
* 功能介绍:   
纵向菜单项显示函数
*
* 关键备注：
* - 

* 未来提高:



*/
uchar MENU_VerticalItemShow(uchar StartItem,uchar EndItem,uchar i,LanguageTypeDef Language,
                           const PageDef* const PagePtr,uchar LineOffset)
{
   uchar LineNum[5] = {0},j = 0;
   FontDef IndexFront;
   uchar ItemHigh;
   CursorShowModeDef CursorShowMode;
   uchar StructIndex = i;
   if(Language == CHINESE)
   {
     if(i > 0)
     {
      i--;
     }
     ItemHigh = ITEM_HIGHT+1;
     IndexFront = ASCII_6X16;
   }
   else if(Language == ENGLISH)
   {
     ItemHigh = ITEM_HIGHT;
     IndexFront = ASCII_6X8;
   }
   //纵向菜单项显示
   for(j = StartItem; j < EndItem;j++,i++,StructIndex++)
   {
     //行号偏移计算。
      LineOffset = MENU_LineNumEdit(LineNum,j+1); 
      LineOffset++;
      LineOffset = LineOffset*6;
      if(j == G_CursorNumV)
      {
       MENU_ItemVDisplay(IndexFront,PagePtr,j,StructIndex,Language,LineOffset,REVERSE_DISPLAY,ItemHigh,i,LineNum);
       CursorShowMode = REVERSE_DISPLAY;
      }
      else
      {
       MENU_ItemVDisplay(IndexFront,PagePtr,j,StructIndex,Language,LineOffset,NORMAL,ItemHigh,i,LineNum);
       CursorShowMode = NORMAL; 
      }
      //利用附加信息，在菜单项后对无单位参数进行末显示
      if((PagePtr->AdditionalInfo == NO_UNIT_VSHOW)
         ||(PagePtr->AdditionalInfo == FIXED_UNIT_VSHOW))
      {
        MENU_NoUnitVariableShow(j,i,CursorShowMode,G_StrStruct[StructIndex],G_StringCodeBuff[StructIndex]);
      }
      else if(PagePtr->AdditionalInfo == UNIT_VSHOW)
      {
        MENU_NoUnitVariableShow(j*2,i,CursorShowMode,G_StrStruct[StructIndex],G_StringCodeBuff[StructIndex]);
      }
   }
  return i;
}

/*/函数名称和参量和返回值类型。
void MENU_CursorTrace(const PageDef* CurrentPage)
* 变量范围:
CurrentPage：当前页面指针。
* 返回值说明:void
* 功能介绍:   
光标追踪函数
*
* 关键备注：
* - 

* 未来提高:



*/
void MENU_CursorTrace(const PageDef*const CurrentPage)
{
   if((MENU_CurrentPageTypeGet() == PARAM_SET_PAGE)||(MENU_CurrentPageTypeGet() == WAITING_PAGE)||
      (MENU_CurrentPageTypeGet() == EXPLANATION_PAGE)||(MENU_CurrentPageTypeGet() == MENU_BAR)
        ||(MENU_CurrentPageTypeGet() == WARNING_PAGE))
   {
      G_CursorNumV = CurrentPage->PreviousOrNextItemLine-1;
   }
   else
    G_CursorNumV = 0;
   G_CursorNumH = 0;
}

/*/函数名称和参量和返回值类型。
static void MENU_ContentLinePrint(const PageDef *const CurrentPage,uchar ShowLineIndex)
* 变量范围:
CurrentPage：当前页面指针。
ShowLineIndex：当前打印行序号

* 返回值说明:void
* 功能介绍:   
面说明信息打印函数，根据行标逐行打印。

*
* 关键备注：
* - 

* 未来提高:



*/
static uchar MENU_ContentLinePrint(const PageDef *const CurrentPage,uchar ShowLineIndex,LanguageTypeDef Language)
{
  uchar j = 0,StartY = 1,LineIndex = ShowLineIndex;
  if(Language == ENGLISH)
  {
    StartY = ITEM_HIGHT;
  }
  else if(Language == CHINESE)
  {
    StartY = (ITEM_HIGHT)*2;
  }
  for(j = 0;j < CurrentPage->ContentLineNumber[Language];j++,ShowLineIndex++)
  {
    FlashStringReadLockHandle(ShowLineIndex,CurrentPage->ContentStrIndex +j,Language);
    MENU_StaticStringShow((G_StrStruct+ShowLineIndex),START_X_INDEX,
                                          LineIndex+StartY*j,Language,NORMAL,G_StringCodeBuff[ShowLineIndex]);
  }
  if( (CurrentPage->ContentLineNumber[Language] == 2) 
     && (Language == CHINESE))
  {
    ShowLineIndex++;
  }
  return ShowLineIndex;
}

/*/函数名称和参量和返回值类型。
uchar MENU_ContentLineShow(const PageDef *CurrentPage,uchar i,const StringDef* StrStruct)
* 变量范围:
CurrentPage：当前页面指针。
StrStruct：字符串库指针
i:内容显示的起始行，
* 返回值说明:void
* 功能介绍:   
面说明信息显示函数，

*
* 关键备注：
* - 

* 未来提高:



*/
uchar MENU_ContentLineShow(const PageDef *const CurrentPage,uchar ShowLineIndex,LanguageTypeDef Language)
{
  uchar i = 0;
  //汉字界面需要保留标题和英文父菜单名称
  if(Language == CHINESE)
  {
    i = MENU_ContentLinePrint(CurrentPage,ShowLineIndex,CHINESE);
  }
  else if(Language == ENGLISH)
  {
    i = MENU_ContentLinePrint(CurrentPage,ShowLineIndex,ENGLISH);
  }
  return i;
}
/*/函数名称和参量和返回值类型。
void MENU_GetVarticalItem(const PageDef* CurrentPage,uint MenuTreeIndex)
* 变量范围:
CurrentPage：当前页面指针。
MenuTreeIndex:菜单树编号，用来确定哪种产品的菜单结构。
* 返回值说明:const ItemDef* 菜单项类型指针
* 功能介绍:   
获取当前页面纵向菜单项指针，

*
* 关键备注：
* - 

* 未来提高:



*/
const ItemDef* MENU_GetVarticalItem(const PageDef*const CurrentPage,uint  MenuItemOffset)
{
  MenuTreeIndexDef MenuTreeIndex = MENU_GetMenuTreeIndex();
  FlashCurrentItemInfoGet(MenuTreeIndex,
                          CurrentPage->ItemArrIndexV+MenuItemOffset,G_CurrentItemStruct.CurrentItemInfoArr);
 return &G_CurrentItemStruct.CurrentItemInfo;
}
/*/函数名称和参量和返回值类型。
const ItemDef* MENU_GetHorizontalItem(const PageDef* CurrentPage,uint MenuTreeIndex)
* 变量范围:
CurrentPage：当前页面指针。
MenuTreeIndex:菜单树编号，用来确定哪种产品的菜单结构。
* 返回值说明:const ItemDef* 菜单项类型指针
* 功能介绍:   
获取当前页面横向菜单项指针，

*
* 关键备注：
* - 

* 未来提高:



*/
const ItemDef* MENU_GetHorizontalItem(const PageDef*const CurrentPage,uint  MenuItemOffset)
{
  MenuTreeIndexDef MenuTreeIndex = MENU_GetMenuTreeIndex();
  FlashCurrentItemInfoGet(MenuTreeIndex,
                          CurrentPage->ItemArrIndexH+MenuItemOffset,G_CurrentItemStruct.CurrentItemInfoArr);
  return &G_CurrentItemStruct.CurrentItemInfo;
}

/*
 //函数名称和参量和返回值类型。
void MENU_HorizontalItemLinkHandle(const ItemDef* CurrentItem,const PageDef* CurrentPage)
* 变量范围:
CurrentPage：当前页面指针。
const ItemDef* CurrentItem：纵向菜单项指针。

* 返回值说明:void 
* 功能介绍:   
  横向项链接切换处理函数。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void MENU_HorizontalItemLinkHandle(const ItemDef*const CurrentItem,const PageDef*const CurrentPage)
{
   MENU_CursorTrace(CurrentPage);
   MENU_PageNumSetHandle(CurrentItem->NextLayerNum);
   MENU_PageTypeSetHandle(CurrentItem->NextLayerType);
}
/*
 //函数名称和参量和返回值类型。
void Menu_BackupPageLinkHandle(const PageDef*const CurrentPage);
* 变量范围:
CurrentPage：当前页面指针。

* 返回值说明:void 
* 功能介绍:   
  返回上级页面链接处理函数，通过本函数可以返回当前页面绑定的父级菜单。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void Menu_BackupPageLinkHandle(const PageDef*const CurrentPage)
{
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  G_CursorNumV = CurrentPage->PreviousOrNextItemLine-1; 
}
/*
 //函数名称和参量和返回值类型。
void MENU_ItemLinkHandle(const ItemDef* CurrentItem,const PageDef* CurrentPage)
* 变量范围:
CurrentPage：当前页面指针。
const ItemDef* CurrentItem：纵向菜单项指针。

* 返回值说明:void 
* 功能介绍:   
  通用菜单项链接切换处理函数。

*
* 关键备注：
* - 

  
* 未来提高:



*/
void MENU_GeneralItemLinkHandle(const ItemDef*const CurrentItem)
{
  //缆长为0是脉冲，脉冲无法进入缆长设置
   if((CurrentItem->ParamValue == TDR)
      &&(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0.00))
   {
     
   }
   else
   {
     //单命令处理
     if(CurrentItem->ParamValue == SINGLE_C)
     {
        G_SingleCommandLoad = TRUE;
     }
     //锐达仪表特有处理，不放大时需要将曲线还原成量程加2
     if(CurrentItem->ParamValue == NO_ZOOM)
     {
        G_IsCurveZoom = FALSE;
     }
     //曲线界面初始化
     if(CurrentItem->ParamValue == CURVE_INIT)
     {
       G_IsCurveZoom = FALSE;
       CurveNoZoomHandle();
     }
     //切换英文处理
     if(CurrentItem->ParamValue == LANGUAGE_ENGLISH)
     {
        MENU_LanguageSetHandle(ENGLISH);
        MENU_TempLanguageSetHandle(ENGLISH);
        G_PreviousShowPage.Language = ENGLISH;
        SaveChar(0,ENGLISH);
     }
     //切换英文处理
     if(CurrentItem->ParamValue == LANGUAGE_CHINESE)
     {
        MENU_LanguageSetHandle(CHINESE);
        MENU_TempLanguageSetHandle(CHINESE);
        G_PreviousShowPage.Language = CHINESE;
        SaveChar(0,CHINESE);
     }
     //曲线界面初始化
     if(CurrentItem->ParamValue == FAKE_END)
     {
        CurveFakeNhlEndHandle();
     }
     if(CurrentItem->ParamValue == DIST_CALI_HANDLE)
     {
        G_IsSpecificHandle = TRUE;
     }
     //单位页面切换处理
     if(((MENU_GetMenuTreeIndex() == EJA)
        &&(MENU_CurrentPageNumGet() == EA_PAGE_INDEX_154))
        ||((MENU_GetMenuTreeIndex() == EJA)
          &&(MENU_CurrentPageNumGet() == EA_PAGE_INDEX_157)))
     {
       MENU_PageNumSetHandle(EA_PAGE_INDEX_159);
       MENU_PageTypeSetHandle(WAITING_PAGE);
     }
     else
     {
       MENU_PageNumSetHandle(CurrentItem->NextLayerNum);
       MENU_PageTypeSetHandle(CurrentItem->NextLayerType);
     }
     MENU_CursorNumReset();
     //解锁flash读取
     FlashReadLockHandle(FALSE);
   }
}

/*
 //函数名称和参量和返回值类型。
void MENU_PageLinkHandle(const PageDef* CurrentPage);
* 变量范围:
CurrentPage：当前页面指针。

* 返回值说明:void 
* 功能介绍:   
  页面方式切换处理函数，
  针对水平取消菜单项进行链路处理。

*
* 关键备注：
* - 

  
* 未来提高:
需要移至显示文件中。


*/ 
void MENU_PageLinkHandle(const PageDef*const CurrentPage)
{
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  MENU_CursorTrace(CurrentPage);
}

/*
//函数名称和参量和返回值类型。
uchar MENU_VariableShow(DataLengthDef DataLength,uchar *ShowData,uchar StartY,
                       const PageDef *CurrentPage,uchar StartX)* 变量范围:
DataTypeDef DataType:变量的数据类型，在这里可以理解为变量的长度，即字节个数。
uchar *ShowData：要被显示的字符串数组首地址。
uchar i：当前显示所在行行标。
const PageDef *CurrentPage：指向当前显示页面的指针。
* 返回值说明:uchar 将显示完变量后的行标返回，便于下一行显示找到位置。 
* 功能介绍:   
编辑变量显示函数，本函数主要作用是将编辑页面上挂载的变量以及挂载变量的副本变量
显示在编辑界面的对应位置。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
uchar MENU_VariableShow(DataLengthDef DataLength,uchar *const ShowData,uchar StartY,
                       const PageDef *const CurrentPage,uchar StartX,CursorShowModeDef CursorShowMode)
{
  uchar j = 0,ShowLineNum = 0;
  if(DataLength/MESSAGE_BOUNDARY == 0)
  {
    MENU_DynamicStringShow(ASCII_6X8,ShowData,
          START_X_INDEX+StartX,START_Y_INDEX+StartY*(ITEM_HIGHT),CursorShowMode,ENGLISH);
    StartY++;
  }
  else
  {
    if(DataLength%MESSAGE_BOUNDARY != 0)
      ShowLineNum = DataLength/MESSAGE_BOUNDARY + 1;
    else
      ShowLineNum = DataLength/MESSAGE_BOUNDARY;
      
    for(j = 0;j < ShowLineNum;j++,StartY++)
    {
      MENU_DynamicStringShow(ASCII_6X8,&ShowData[j*MESSAGE_BOUNDARY],
              START_X_INDEX+StartX,START_Y_INDEX+StartY*(ITEM_HIGHT),CursorShowMode,ENGLISH);
    }
  }
  return StartY;
}
/*
//函数名称和参量和返回值类型。
bool8 MENU_PageRefreshIntervalHandle(void)
* 变量范围:

* 返回值说明:
返回TRUE说明当前页面属于刷新类界面，返回FALSE说明不属于。
* 功能介绍:   
页面刷新间隔处理函数
用来判断刷新类性界面的刷新时间间隔。

*
* 关键备注：
* - 

  
* 未来提高:
*/
 
bool8 MENU_PageRefreshIntervalHandle(void)
{
  PageDef *PagePtr = NULL;
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  if(PagePtr->ConnectWay == REFRESH)
  {
    //如果当前页面仍属于刷新类界面，并且时间计数已经完成一个周期，则重新加载周期计数值。
    if(G_WarningTimeStamp == 0)
    {
      MENU_TimingIntervalSelect();
      if(G_HART_HandleFlag == HART_STANDBY)
      {        
        MENU_ClearLcdScreen();
        return TRUE;
      }
      if(MENU_CurrentPageTypeGet() == CURVE_PAGE)
      {        
        MENU_ClearLcdScreen();
        return TRUE;
      }
    }
  }
  return FALSE;
}
/*
//函数名称和参量和返回值类型。
void MENU_TimingIntervalSelect()
* 变量范围:

* 功能介绍:   


*
* 关键备注：
* - 

  
* 未来提高:
*/
 

void MENU_TimingIntervalSelect()
{
  PageDef *PagePtr = NULL;
    //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  if((PagePtr->AdditionalInfo == ONE_THOUSAND_MS)||(PagePtr->AdditionalInfo == ABNORMAL_MODE))
  {
    G_WarningTimeStamp = 1300;
  }
  else if(PagePtr->AdditionalInfo == ONE_HALF_THOUSAND_MS)
  {
	G_WarningTimeStamp = 1500;
  }
  else if((PagePtr->AdditionalInfo == THREE_THOUSAND_MS)
            ||(PagePtr->AdditionalInfo == PV_SHOW)||(PagePtr->AdditionalInfo == TRACK_SHOW))     
  {
    G_WarningTimeStamp = 3000;
  }
  else if(PagePtr->AdditionalInfo == CURVE_HANDLE)
  {
    G_WarningTimeStamp = 5500;
  }
  else if(PagePtr->AdditionalInfo == ONE_HUNDRED_MS)
  {
    G_WarningTimeStamp = 100;
  }
  else if(PagePtr->AdditionalInfo == SIX_THOUSAND_MS)
  {
    G_WarningTimeStamp = 6000;
  }
  else if(PagePtr->AdditionalInfo == SIX_HUNDRED_MS)
  {
    G_WarningTimeStamp = 600;
  }
}
/*
//函数名称和参量和返回值类型。
float	MENU_CharToFloat( uchar DecimalP,uchar *ShowDataBuffe,uchar Length )
* 变量范围:

* 功能介绍:   
显示字符串转换为float数值。

*
* 关键备注：
* - 

  
* 未来提高:
*/
float	MENU_StrToFloat( uchar DecimalP,uchar *const ShowDataBuffe,uchar Length )
{
	signed char Temp;
//	unsigned int TempI = 1;
	float	TranResult = 0,TempF = 1;
	for(Temp = DecimalP-1; Temp > 0; Temp--)
	{
		TranResult = TempF*(ShowDataBuffe[Temp]-0x30)+TranResult;
		TempF = TempF*10;
	}
	if(ShowDataBuffe[0] != '-')
	{
		TranResult = TranResult+(ShowDataBuffe[0]-0x30)*TempF;
	}
	TempF = 10;
        //字符串字符个数精确到第十个字节
        if(Length >= EFFECTIVE_STR_LENGTH)
        {
          Length = EFFECTIVE_STR_LENGTH;
        }
	for(Temp = DecimalP+1; Temp < Length; Temp++)
	{
		TranResult = (ShowDataBuffe[Temp]-0x30)/TempF+TranResult;
		TempF = TempF*10;
	}
	if(ShowDataBuffe[0] == '-')
	{
		TranResult = 0-TranResult;
	}
	return(TranResult);
}
/*
//函数名称和参量和返回值类型。
uchar MENU_DataToASCII(uchar *ShowData,uchar *Temp,DataTypeDef DataType)
* 变量范围:

* 功能介绍:   
float数据转换成ASCII函数，
数据的保存类型均以char类型为准，float类型数据也保存在字符串当中，本函数的功能
就是将float字符串数组转换成可以显示的ASCII数据流。
*
* 关键备注：
* - 

  
* 未来提高:
小数点位数可能会作为参数传入。
*/
uchar MENU_DataToASCII(const uchar *const ShowData,uchar *const Temp,DataTypeDef DataType)
{
  uchar TempLength,DecimalN = 0;
  float FloatTemp = 0;
  FloatTemp = MENU_DataToFloat(ShowData,DataType);
  if(DataType == FLOAT_T)
  {
    DecimalN = 3;
  }
  else if(DataType == FLOAT1_T)
  {
    DecimalN = 1;
  }
  TempLength = ModbusFloatToASCIIConvert(FloatTemp,DecimalN,Temp);
  //返回值是整数位加小数点加小数位
  return TempLength+DecimalN+2;
}

/**  static void BufReverseCopy(void* Destination,void* Source,uchar8 Length)//函数名称和参量和返回值类型。
* 变量范围: 
Destination：目的数组。
Source：源数组
Length：复制成员个数

* 返回值说明: 
* 功能介绍:   
   将源数组的内容反向拷贝到目的数组
*
* 关键备注：
* - 关于复制个数，是调用该函数时严格判断，本函数不做判断
* 未来提高: 
* 
*/
void BufReverseCopy(uchar *const Destination,const uchar*const Source,DataTypeDef DataType)
{
   uchar i = 0;
   uchar *p1 = (uchar*)Destination,*p2 = (uchar*)Source;
   if((DataType == CURVE_START_T)
               ||(DataType == FLOAT_T)
                 ||(DataType == FLOAT1_T)
                  ||(DataType == CURVE_END_T)
                    ||(DataType == FAKE_RANGE_T)
                      ||(DataType == FAKE_AMP_T)
                        ||(DataType == PVL_T)
                          ||(DataType == PVU_T)
                            ||(DataType == MAX_ZOON_T)
                              ||(DataType == MIN_ZOON_T)
                                ||(DataType == LEVEL_SPD_T)
                                  ||(DataType == SUPRITY_T)
                                    ||(DataType == MIN_RESOL_T))
   {
     for(i = 0;i < FLOAT ;i++)
     {
       *(p1+(FLOAT-i-1)) = *(p2+i);
     }    
   }
   else if(DataType == LONG_UINT_T)
   {
     for(i = 0;i < THREE_BYTES ;i++)
     {
       *(p1+(THREE_BYTES-i-1)) = *(p2+i);
     } 
   }
   else if((DataType == UINT_T)||(DataType == INT_VALUE_T))
   {
     for(i = 0;i < UINT ;i++)
     {
       *(p1+(UINT-i-1)) = *(p2+i);
     } 
   }
}

/*
//函数名称和参量和返回值类型。
float MENU_DataToFloat(uchar *ShowData,DataTypeDef FLOAT_T)
* 变量范围:

* 功能介绍:   
将四个字节的数据帧数组转换成float数据

*
* 关键备注：
* - 

  
* 未来提高:
*/

float MENU_DataToFloat(const uchar *const ShowData,DataTypeDef Type)
{
  union FloatToStr
  {
    uchar Char[FLOAT];
    float Float;
  }Data;
  BufReverseCopy(Data.Char,ShowData,Type);
  return Data.Float;
}
/*
//函数名称和参量和返回值类型。
void MENU_FloatToData(uchar *const ShowData,float FloatV,DataTypeDef Type);
* 变量范围:

* 功能介绍:   
将浮点数数据转换成四个字节的变量数组。

*
* 关键备注：
* - 

  
* 未来提高:
*/

void MENU_FloatToData(uchar *const ShowData,float FloatV,DataTypeDef Type)
{
  union FloatToStr
  {
    uchar Char[FLOAT];
    float Float;
  }Data;
  Data.Float = FloatV;
  BufReverseCopy(ShowData,Data.Char,Type);
}
/*
//函数名称和参量和返回值类型。
void MENU_FloatToData(float FloatData,uchar *ShowData,DataTypeDef FLOAT_T)
* 变量范围:

* 功能介绍:   


*
* 关键备注：
* - 

  
* 未来提高:
*/
void MENU_TemporaryVariableReset(uchar *const ShowData,uchar Length,uchar StartIndex)
{
  uchar i = StartIndex;
  for(i = StartIndex;i < Length;i++)
  {
    ShowData[i] = 0x20;
  }
}
/*
//函数名称和参量和返回值类型。
void MENU_DataCopy(uchar *G_OutputLevel,const uchar *FourMA,DataTypeDef FLOAT_T);

* 变量范围:

* 功能介绍:   


*
* 关键备注：
* - 

  
* 未来提高:
*/
void MENU_DataCopy(uchar *const Destination,const uchar *const Source,DataLengthDef Length)
{
  uchar i = 0;
  for(i = 0; i < Length;i++)
  {
    *(Destination+i) = *(Source+i);
  }
}
/*
//函数名称和参量和返回值类型。
bool8 MENU_ItemParamLoad(const ItemDef* CurrentItemV)
* 变量范围:

* 功能介绍:   
菜单项参数处理函数，
界面的一些初始信息需要预加载，可以通过本函数，单位变量也可以通过本函数进行处理。

*
* 关键备注：
* - 

  
* 未来提高:
*/
bool8 MENU_ItemParamLoad(const ItemDef*const CurrentItemV)
{
  const uchar FourMA[] = {0x40,0x80,0x00,0x00};
  const uchar TwentyMA[] = {0x41,0xa0,0x00,0x00};
  const uchar EighteenMA[] = {0x41,0x90,0x00,0x00};
  const uchar OneMA[] = {0x3F,0x80,0x00,0x00};
  const uchar ZeroMA[] = {0x00,0x00,0x00,0x00};
  const uchar ThreePointEightMA[] = {0x40,0x73,0x33,0x33};
  const uchar TwentyOneMA[] = {0x41,0xA8,0x00,0x00};
  switch(CurrentItemV->ParamValue)
  {
    case ZERO_MA:
      MENU_DataCopy(G_OutputLevel,ZeroMA,FLOAT);
    break;
    case FOUR_MA:
      MENU_DataCopy(G_OutputLevel,FourMA,FLOAT);
      break;
    case EIGHTEEN_MA:
      MENU_DataCopy(G_OutputLevel,EighteenMA,FLOAT);
      break;
    case TWENTY_MA:
      MENU_DataCopy(G_OutputLevel,TwentyMA,FLOAT);
      break;
    case ONE_MA:
      MENU_DataCopy(G_OutputLevel,OneMA,FLOAT);
      break;
    case ALARM3_8:
      MENU_DataCopy(G_PublicVF1,ThreePointEightMA,FLOAT);
      break;
    case ALARM21:
      MENU_DataCopy(G_PublicVF1,TwentyOneMA,FLOAT);
      break;
    case CURSORY_PARAM:
    case CURSORX_PARAM://曲线光标界面变量初始化
    case CURSOR_NEW:
    case CURSOR_MHIGH:
    case CURSOR_MLOW:
    case CURSOR_MPART:
    case CURSOR_DZH:
    case CURSOR_DZL:
    case CURSOR_SGT:
    case NO_ZOOM:
      CursorParamInit(CurrentItemV->ParamValue);
      CurveFakeEchoReloadFlagHandle();
      break;
    case Bit0Set: G_UnitTemp[0] |= 0x01;break;
    case Bit0Reset: G_UnitTemp[0] &= (~0x01);break;
    case Bit1Set: G_UnitTemp[0] |= 0x02;break;
    case Bit1Reset: G_UnitTemp[0] &= (~0x02);break;
    case Bit2Set: G_UnitTemp[0] |= 0x04;break;
    case Bit2Reset: G_UnitTemp[0] &= (~0x04);break;
    case VALUE_0: G_UnitTemp[0] = 0x00;break;
    case VALUE_1: G_UnitTemp[0] = 0x01;break;
    case VALUE_2: G_UnitTemp[0] = 0x02;break;
    case VALUE_3: G_UnitTemp[0] = 0x03;break;
    case VALUE_4: G_UnitTemp[0] = 0x04;break;
    case VALUE_5: G_UnitTemp[0] = 0x05;break;
    case VALUE_6: G_UnitTemp[0] = 0x06;break;
    case VALUE_7: G_UnitTemp[0] = 0x07;break;
    case VALUE_8: G_UnitTemp[0] = 0x08;break;
    case VALUE_9: G_UnitTemp[0] = 0x09;break;
    case VALUE_10: G_UnitTemp[0] = 0x0a;break;
    case VALUE_11: G_UnitTemp[0] = 0x0b;break;
    case VALUE_12: G_UnitTemp[0] = 0x0c;break;
    case VALUE_13: G_UnitTemp[0] = 0x0d;break;
    case VALUE_14: G_UnitTemp[0] = 0x0e;break;
    case VALUE_15: G_UnitTemp[0] = 0x0f;break;
    case VALUE_16: G_UnitTemp[0] = 0x20; break;
    case VALUE_17: G_UnitTemp[0] = 0x21; break;
    case VALUE_18: G_UnitTemp[0] = 0x22; break;
    case VALUE_19: G_UnitTemp[0] = 0x23; break;      
    case VALUE_20: G_UnitTemp[0] = 0x91; break;
    case VALUE_21: G_UnitTemp[0] = 0xed; break;
    case VALUE_22: G_UnitTemp[0] = 0xee; break;
    case VALUE_23: G_UnitTemp[0] = 0xef; break;
    case VALUE_24: G_UnitTemp[0] = 0x10; break;
    case VALUE_25: G_UnitTemp[0] = 0x11; break;
    case VALUE_26: G_UnitTemp[0] = 0x12; break;
    case VALUE_27: G_UnitTemp[0] = 0x13; break;
    case VALUE_28: G_UnitTemp[0] = 0x16; break;
    case VALUE_29: G_UnitTemp[0] = 0x17; break;
    case VALUE_30: G_UnitTemp[0] = 0x18; break;
    case VALUE_31: G_UnitTemp[0] = 0x19; break;
    case VALUE_32: G_UnitTemp[0] = 0x1a; break;
    case VALUE_33: G_UnitTemp[0] = 0x1d; break;
    case VALUE_34: G_UnitTemp[0] = 0x1c; break;
    case VALUE_35: G_UnitTemp[0] = 0x1e; break;
    case VALUE_36: G_UnitTemp[0] = 0x1f; break;
    case VALUE_37: G_UnitTemp[0] = 0x79; break;
    case VALUE_38: G_UnitTemp[0] = 0x7a; break;
    case VALUE_39: G_UnitTemp[0] = 0x7b; break;
    case VALUE_40: G_UnitTemp[0] = 0x82; break;
    case VALUE_41: G_UnitTemp[0] = 0x83; break;
    case VALUE_42: G_UnitTemp[0] = 0x84; break;
    case VALUE_43: G_UnitTemp[0] = 0x85; break;
    case VALUE_44: G_UnitTemp[0] = 0x86; break;
    case VALUE_45: G_UnitTemp[0] = 0x87; break;
    case VALUE_46: G_UnitTemp[0] = 0x88; break;
    case VALUE_47: G_UnitTemp[0] = 0x89; break;
    case VALUE_48: G_UnitTemp[0] = 0x8a; break;
    case VALUE_49: G_UnitTemp[0] = 0xeb; break;
    case VALUE_50: G_UnitTemp[0] = 0x14; break;
    case VALUE_51: G_UnitTemp[0] = 0x15; break;
    case VALUE_52: G_UnitTemp[0] = 0x72; break;
    case VALUE_53: G_UnitTemp[0] = 0x73; break;
    case VALUE_54: G_UnitTemp[0] = 0x74; break;
    case VALUE_55: G_UnitTemp[0] = 0x78; break;
    case VALUE_56: G_UnitTemp[0] = 0x28; break;
    case VALUE_57: G_UnitTemp[0] = 0x29; break;
    case VALUE_58: G_UnitTemp[0] = 0x2A; break;
    case VALUE_59: G_UnitTemp[0] = 0x2B; break;
    case VALUE_60: G_UnitTemp[0] = 0x2E; break;
    case VALUE_61: G_UnitTemp[0] = 0x6e; break;
    case VALUE_62: G_UnitTemp[0] = 0x6f; break;
    case VALUE_63: G_UnitTemp[0] = 0x70; break;
    case VALUE_64: G_UnitTemp[0] = 0x71; break;
    case VALUE_65: G_UnitTemp[0] = 0x7c; break;
    case VALUE_66: G_UnitTemp[0] = 0xa6; break;
    case VALUE_67: G_UnitTemp[0] = 0xa7; break;
    case VALUE_68: G_UnitTemp[0] = 0xa8; break;
    case VALUE_69: G_UnitTemp[0] = 0xec; break;
    case VALUE_70: G_UnitTemp[0] = 0x2C; break;
    case VALUE_71: G_UnitTemp[0] = 0x2D; break;
    case VALUE_72: G_UnitTemp[0] = 0x2F; break;
    case VALUE_73: G_UnitTemp[0] = 0x30; break;
    case VALUE_74: G_UnitTemp[0] = 0x31; break;
    case VALUE_75: G_UnitTemp[0] = 0x32; break;
    case VALUE_76: G_UnitTemp[0] = 0x33; break;
    case VALUE_77: G_UnitTemp[0] = 0x34; break;
    case VALUE_78: G_UnitTemp[0] = 0x35; break;
    case VALUE_79: G_UnitTemp[0] = 0x3c; break;
    case VALUE_80: G_UnitTemp[0] = 0x3d; break;
    case VALUE_81: G_UnitTemp[0] = 0x3e; break;
    case VALUE_82: G_UnitTemp[0] = 0x3f; break;
    case VALUE_83: G_UnitTemp[0] = 0x40; break;
    case VALUE_84: G_UnitTemp[0] = 0x41; break;
    case VALUE_85: G_UnitTemp[0] = 0x7d; break;
    case VALUE_86: G_UnitTemp[0] = 0x46; break;
    case VALUE_87: G_UnitTemp[0] = 0x47; break;
    case VALUE_88: G_UnitTemp[0] = 0x48; break;
    case VALUE_89: G_UnitTemp[0] = 0x49; break;
    case VALUE_90: G_UnitTemp[0] = 0x4A; break;
    case VALUE_91: G_UnitTemp[0] = 0x4B; break;
    case VALUE_92: G_UnitTemp[0] = 0x4C; break;
    case VALUE_93: G_UnitTemp[0] = 0x4d; break;
    case VALUE_94: G_UnitTemp[0] = 0x4e; break;
    case VALUE_95: G_UnitTemp[0] = 0x4f; break;
    case VALUE_96: G_UnitTemp[0] = 0x50; break;
    case VALUE_97: G_UnitTemp[0] = 0x51; break;
    case VALUE_98: G_UnitTemp[0] = 0x52; break;
    case VALUE_99: G_UnitTemp[0] = 0x53; break;
    case VALUE_100: G_UnitTemp[0] = 0x54; break;
    case VALUE_101: G_UnitTemp[0] = 0x55; break;
    case VALUE_102: G_UnitTemp[0] = 0x56; break;
    case VALUE_103: G_UnitTemp[0] = 0x57; break;
    case VALUE_104: G_UnitTemp[0] = 0x58; break;
    case VALUE_105: G_UnitTemp[0] = 0x5a; break;
    case VALUE_106: G_UnitTemp[0] = 0x5b; break;
    case VALUE_107: G_UnitTemp[0] = 0x5c; break;
    case VALUE_108: G_UnitTemp[0] = 0x5d; break;
    case VALUE_109: G_UnitTemp[0] = 0x5e; break;
    case VALUE_110: G_UnitTemp[0] = 0x5f; break;
    case VALUE_111: G_UnitTemp[0] = 0x60; break;
    case VALUE_112: G_UnitTemp[0] = 0x61; break;
    case VALUE_113: G_UnitTemp[0] = 0x62; break;
    case VALUE_114: G_UnitTemp[0] = 0x63; break;
    case VALUE_115: G_UnitTemp[0] = 0x64; break;
    case VALUE_116: G_UnitTemp[0] = 0x66; break;
    case VALUE_117: G_UnitTemp[0] = 0x67; break;
    case VALUE_118: G_UnitTemp[0] = 0x68; break;
    case VALUE_119: G_UnitTemp[0] = 0x92; break;
    case VALUE_120: G_UnitTemp[0] = 0x93; break;
    case VALUE_121: G_UnitTemp[0] = 0x24; break;
    case VALUE_122: G_UnitTemp[0] = 0x27; break;
    case VALUE_123: G_UnitTemp[0] = 0x25; break;
    case VALUE_124: G_UnitTemp[0] = 0xa3; break;
    case VALUE_125: G_UnitTemp[0] = 0x45; break;
    case VALUE_126: G_UnitTemp[0] = 0x59; break;
    case VALUE_127: G_UnitTemp[0] = 0x7e; break;
    case VALUE_128: G_UnitTemp[0] = 0x80; break;
    case VALUE_129: G_UnitTemp[0] = 0xa4; break;
    case VALUE_130: G_UnitTemp[0] = 0xa5; break;
    case VALUE_131: G_UnitTemp[0] = 0xa2; break;
    case VALUE_132: G_UnitTemp[0] = 0x7f; break;
    case VALUE_133: G_UnitTemp[0] = 0x81; break;
    case VALUE_134: G_UnitTemp[0] = 0x8c; break;
    case VALUE_135: G_UnitTemp[0] = 0x8d; break;
    case VALUE_136: G_UnitTemp[0] = 0x8e; break;
    case VALUE_137: G_UnitTemp[0] = 0x75; break;
    case VALUE_138: G_UnitTemp[0] = 0x76; break;
    case VALUE_139: G_UnitTemp[0] = 0x77; break;
    case VALUE_140: G_UnitTemp[0] = 0x26; break;
    case VALUE_141: G_UnitTemp[0] = 0x39; break;
    case VALUE_142: G_UnitTemp[0] = 0x42; break;
    case VALUE_143: G_UnitTemp[0] = 0x43; break;
    case VALUE_144: G_UnitTemp[0] = 0x44; break;
    case VALUE_145: G_UnitTemp[0] = 0x69; break;
    case VALUE_146: G_UnitTemp[0] = 0x6a; break;
    case VALUE_147: G_UnitTemp[0] = 0x6b; break;
    case VALUE_148: G_UnitTemp[0] = 0x6c; break;
    case VALUE_149: G_UnitTemp[0] = 0x6d; break;
    case VALUE_150: G_UnitTemp[0] = 0x8b; break;
    case VALUE_151: G_UnitTemp[0] = 0x8f; break;
    case VALUE_152: G_UnitTemp[0] = 0x90; break;
    case VALUE_153: G_UnitTemp[0] = 0x94; break;
    case VALUE_154: G_UnitTemp[0] = 0x95; break;
    case VALUE_155: G_UnitTemp[0] = 0x9a; break;
    case VALUE_156: G_UnitTemp[0] = 0x9b; break;
    case VALUE_157: G_UnitTemp[0] = 0xa1; break;
    case VALUE_158: G_UnitTemp[0] = 0xa9; break;
    case VALUE_159: G_UnitTemp[0] = 0x96; break;
    case VALUE_160: G_UnitTemp[0] = 0x97; break;
    case VALUE_161: G_UnitTemp[0] = 0x98; break;
    case VALUE_162: G_UnitTemp[0] = 0x99; break;
    case VALUE_163: G_UnitTemp[0] = 0xa0; break;
    case VALUE_164: G_UnitTemp[0] = 0xf0; break;
    case VALUE_165: G_UnitTemp[0] = 0xf1; break;
    case VALUE_166: G_UnitTemp[0] = 0xfa; break;
    case VALUE_167: G_UnitTemp[0] = 0xfb; break;
    case VALUE_168: G_UnitTemp[0] = 0xfc; break;
    case VALUE_169: G_UnitTemp[0] = 0xfd; break;
    case VALUE_170: G_UnitTemp[0] = 0x1b; break;        
    case VALUE_172: G_UnitTemp[0] = 0xea; break;
    case VALUE_173: G_UnitTemp[0] = 0x36; break;
    case VALUE_174: G_UnitTemp[0] = 0x37; break;
    case VALUE_175: G_UnitTemp[0] = 0x3a; break;
    case VALUE_176: G_UnitTemp[0] = 0x38; break;
    case VALUE_177: G_UnitTemp[0] = 0x3b; break;        
    case VALUE_178: G_UnitTemp[0] = 0x65; break;   
    case VALUE_179: G_UnitTemp[0] = 0xaa; break;   
    case VALUE_180: G_UnitTemp[0] = 0xf2; break;
    case VALUE_181: G_UnitTemp[0] = 0xad; break;  
    case VALUE_182: G_UnitTemp[0] = 0xae; break;  
    case VALUE_183: G_UnitTemp[0] = 0xaf; break;
    case VALUE_184: G_UnitTemp[0] = 0xb0; break;
    case VALUE_185: G_UnitTemp[0] = 0xb1; break;
    case VALUE_186: G_UnitTemp[0] = 0xb2; break;
    case VALUE_187: G_UnitTemp[0] = 0xb3; break;
    case VALUE_188: G_UnitTemp[0] = 0xab; break;
    case VALUE_189: G_UnitTemp[0] = 0xac; break;
    case RENEW: HART_ProtectedVariableGet(); break;  
    default:
      break;
  }
  return TRUE;
}

/*
//函数名称和参量和返回值类型。
void MENU_IS_SingleCommandLoad(bool8 LoadStatus,const PageDef CurrentPage)
* 变量范围:

* 功能介绍:   


*
* 关键备注：
* - 

  
* 未来提高:
*/
void MENU_IS_SingleCommandLoad(bool8 LoadStatus,const PageDef *const CurrentPage)
{
  if((LoadStatus == TRUE)&&(G_SingleCommandLoad == TRUE))
  {
    MENU_PageCommandGroupLoad(CurrentPage);
    G_SingleCommandLoad = FALSE;
  }
  if(G_SingleCommandLoad == LoadStatus)
  {
    G_SingleCommandLoad = TRUE;
  }
}

/*
//函数名称和参量和返回值类型。
bool8 MENU_ParamReset()
* 变量范围:

* 功能介绍:   
参数变量复位函数，
因为有些界面需要发送0值的参数，通过本函数来处理。

*
* 关键备注：
* - 

  
* 未来提高:
*/
bool8 MENU_ParamReset()
{
  uchar ZeroParam[] = {0x00,0x00,0x00,0x00};
  //后期会根据不同分支进行不同处理
  MENU_DataCopy(G_OutputLevel,ZeroParam,FLOAT);
  return TRUE;
}

/*
void MENU_DateShow()
* 变量范围:

ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void MENU_DateShowHandle(uchar *const Temp)
{
  uchar Buff = 0;
  //M
  Temp[0] = G_Date[1]/10+0x30;
  Temp[1] = G_Date[1]%10+0x30;

  Temp[2] = 0x2d;
  //D
  Temp[3] = G_Date[0]/10+0x30;
  Temp[4] = G_Date[0]%10+0x30;
  
  Temp[5] = 0x2d;
  //Y
  if(G_Date[2] < 100)
  {
    Temp[6] = 0x31;
    Temp[7] = 0x39;
  }
  else if(G_Date[2] < 200)
  {
    Temp[6] = 0x32;
    Temp[7] = 0x30;
    Buff  = G_Date[2] -100;
  }
  else 
  {
    Temp[6] = 0x32;
    Temp[7] = 0x31; 
    Buff  = G_Date[2] -200;
  }
    
  Temp[8] = G_Date[2]/10+0x30;
  if(Temp[8]>0x39)
  {
    Temp[8] = 0x30+Buff/10;
  }
  Temp[9] = G_Date[2]%10+0x30;
}

/*
long uint MENU_StrToInt(uchar *const ShowData,uchar VariableArrIndex)
* 变量范围:

ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   
字符串ASCII转换成整型数据函数
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
long uint MENU_StrToInt(uchar *const ShowData,uchar VariableArrIndex)
{
  uchar i = 0;
  long uint UintData = 0,Scale = 1;
  for(i = 1;i <= VariableArrIndex;i++)
  {
    UintData += (ShowData[VariableArrIndex-i]-0x30)*Scale;
    Scale *= 10;
  }
  return UintData;
}
/*
void MENU_CursorNumReset()
* 变量范围:

ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   
光标复位函数
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_CursorNumReset()
{
   G_CursorNumV = 0;
   G_CursorNumH = 0;
}
/*
void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage)

* 变量范围:
CurrentPage，当前显示界面类型结构体指针
ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   
针对西门子菜单的异常处理返回现场保护函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_SiementsReturnPageSave(const PageDef* CurrentPage)
{

}
/*
void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage)

* 变量范围:
CurrentPage，当前显示界面类型结构体指针
ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   
针对川仪菜单的异常处理返回现场保护函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage)
{
    switch(CurrentPage->ContentStrIndex)
    {
    case STR_INDEX_65:
      MENU_TempPageNumSetHandle(CY_PAGE_INDEX_9);
      MENU_TempPageTypeSetHandle(EXPLANATION_PAGE);
      break;
    case STR_INDEX_69:
      MENU_TempPageNumSetHandle(CY_PAGE_INDEX_151);
      MENU_TempPageTypeSetHandle(PARAM_SET_PAGE);
      break;
    case STR_INDEX_105:
      if(CurrentPage->PageNum == CY_PAGE_INDEX_25)
      {
        MENU_TempPageNumSetHandle(CY_PAGE_INDEX_27);
        MENU_TempPageTypeSetHandle(PARAM_SET_PAGE);
      }
      else if(CurrentPage->PageNum == CY_PAGE_INDEX_115)
      {
        MENU_TempPageNumSetHandle(CY_PAGE_INDEX_32);
        MENU_TempPageTypeSetHandle(PARAM_SET_PAGE);
      }
      break;
    default:break;
    }
}
/*
void MENU_ReturnPageSave(const PageDef* CurrentPage)

* 变量范围:
CurrentPage，当前显示界面类型结构体指针
ASCII_Tag
G_Tag


* 返回值说明:void
* 功能介绍:   
异常处理返回现场保护函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_ReturnPageSave(const PageDef* CurrentPage)
{
  //川仪的特殊异常返回加载
  if(MENU_GetMenuTreeIndex() == CHUAN_YI)
  {
    MENU_ChuanYiReturnPageSave(CurrentPage);
  }//西门子的特殊异常加载
  else if(MENU_GetMenuTreeIndex() == SIEMENS)
  {
    MENU_SiementsReturnPageSave(CurrentPage);
  }
  //通用异常返回页面加载
  switch(CurrentPage->ContentStrIndex)
  {
    case STR_INDEX_2://Device Setup
    case STR_INDEX_4://Diag/Service
    case STR_INDEX_9://Calibration
    case STR_INDEX_5://Basio setup
    case STR_INDEX_6://Detailed setup
    case STR_INDEX_7://Test device
    case STR_INDEX_995://Review
    case STR_INDEX_105://Enter~meter~value （EditPage）  
    case STR_INDEX_23://Sensor trim
    case STR_INDEX_73://Choose analog output
    case STR_INDEX_20://Signal condition
    case STR_INDEX_107: //Set~the:
    case STR_INDEX_339://keypad~Input
    case STR_INDEX_332://HART~output
    case STR_INDEX_333://Device~Info
    case STR_INDEX_409://VALUE_73~setup
    case STR_INDEX_575://Wrt~protet~menu
    case STR_INDEX_910://DisplayCode
    case STR_INDEX_1116: //菜单列--Process Alerts
    MENU_CurrentPageTempSave();
    break;
  default:break;
  }  
}
/*
void MENU_CursorSaveHand(bool8 flag)

* 变量范围:
flag:TRUE,FALSE;


* 返回值说明:void
* 功能介绍:   
光标保存处理函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/

void MENU_CursorSaveHand(bool8 flag)
{
  if(flag == TRUE)
  {
    G_CursorTempV = G_CursorNumV;
  }
  else if(flag == FALSE)
  {
    G_CursorNumV = G_CursorTempV;
  }
}
/*
void MENU_CursorOverrunHandle(uchar CursorMaxVal)

* 变量范围:
CursorMaxVal:纵向菜单个数最大值


* 返回值说明:void
* 功能介绍:   
异常光标处理函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_CursorOverrunHandle(uchar CursorMaxVal)
{
  if(G_CursorNumV > CursorMaxVal)
  {
    G_CursorNumV = 0;
  }
}
/*
void MENU_VeriableReset()

* 变量范围:



* 返回值说明:void
* 功能介绍:   
返回到未连接界面时，需要对一些变量进行处理，本函数就是复原
个别变量设计的。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_VeriableReset()
{
  G_PollingAddress[0] = 0;
}
/*
void MENU_SpecificOperation(AdditionalInfoDef Operation)

* 变量范围:
AdditionalInfoDef Operation:页面附加信息变量


* 返回值说明:void
* 功能介绍:   
  菜单特殊处理函数，用来执行菜单页面中必须执行的特定运算，
  根据菜单结构的附加功能项，采取特定的运算，使用情况较少，
  多用于定制产品（目前用于锐达仪表的距离系数校准）
个别变量设计的。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_SpecificOperation(AdditionalInfoDef Operation)
{
  switch(Operation)
  {
    case DIST_CALI:
      HART_DistCalibrateHandle();
      break;
    default:break;
  }
}
/*
void MENU_CommandAdd(CommandDef Command)

* 变量范围:



* 返回值说明:void
* 功能介绍:   
附加命令添加函数，当特定界面需要添加附加命令时，可通过本函数进行命令添加
*
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_CommandAdd(CommandDef Command)
{
  uchar Index = G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber;
  G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[Index] = Command;
  G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber++;
}

/*
void MENU_VerticalItemSwitchParamGet(uchar *StartItem,uchar *EndItem,
                                 uchar ShowLineNum,uchar ItemNumber);
* 变量范围:



* 返回值说明:void
* 功能介绍:   
  纵向菜单切换刷屏参数获取，将计算好的菜单显示起始和终点作为实际参数返回
*
* 关键备注：
* - 

  
* 未来提高:




*/
HandleFlagDef MENU_VerticalItemSwitchParamGet(uchar *StartItem,uchar *EndItem,
                                 uchar ShowLineNum,uchar ItemNumber)
{
  uchar CurrentPageNum = 0;
  //计算一下光标在菜单列的第几页。
  CurrentPageNum = G_CursorNumV/ShowLineNum;
  //计算本页起始行菜单项行号
  StartItem[0] =  CurrentPageNum*ShowLineNum;
  //计算本页末尾菜单项行号
  EndItem[0] = StartItem[0] + ShowLineNum;
  //如果末尾菜单项行号比菜单项个数还要大，说明已经到了菜单列最后一页，那么就以菜单项个数为准
  if(EndItem[0] >= ItemNumber)
  {
    EndItem[0] = ItemNumber;  
    return EndingOption;
  }
  else
  {
    return OptionsLeft;
  }
}

/*
void MENU_VerticalItemRefreshHandle(uchar ShowLineNum);
* 变量范围:
  ShowLineNum：当前页面显示纵项个数。


* 返回值说明:void
* 功能介绍:   
*       纵项刷新处理函数，
    菜单页面或参数选择界面的纵项达到翻页标准时，进行刷屏更新处理。
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_VerticalItemRefreshHandle(uchar ShowLineNum,PageDef *PagePtr)
{
  //这里逻辑与本地查表有区别了，现在是每换一批选项，就需要重新刷新一次页面。
  if((G_CursorNumV%ShowLineNum == 0)
     ||(G_CursorNumV%ShowLineNum == ShowLineNum-1)
       ||(G_CursorNumV == PagePtr->ItemNumberV-1))
  {
    MENU_ClearLcdScreen();
    FlashReadLockHandle(FALSE);
  }
}
/*
void MENU_TempLanguageSetHandle(LanguageTypeDef Language);
* 变量范围:
  Language：将要设定的语言。


* 返回值说明:void
* 功能介绍:   
*       备份页面语言设置函数，修改备份页面信息中的语言。
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_TempLanguageSetHandle(LanguageTypeDef Language)
{
  G_CurrentPageTemp.Language = Language;
}
/*
void MENU_TempPageNumSetHandle(uint CurrentPageNum)
* 变量范围:
CurrentPageNum:要设定的页面编号


* 返回值说明:void
* 功能介绍:   
*       备份页面编号设置函数，将备份页面编号进行修改。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_TempPageNumSetHandle(uint CurrentPageNum)
{
  G_CurrentPageTemp.CurrentPageNum = CurrentPageNum;
}
/*
void MENU_PageTypeSetHandle(uint CurrentPageNum)
* 变量范围:
PageType:要设定的页面类型


* 返回值说明:void
* 功能介绍:   
*       备份页面类型设置函数，将备份页面类型进行修改。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_TempPageTypeSetHandle(PageTypeDef PageType)
{
  G_CurrentPageTemp.PageType = PageType;
}
/*
void MENU_TempPageIndexSetHandle(uint CurrentPageNum)
* 变量范围:
PageType:要设定的菜单树索引序号


* 返回值说明:void
* 功能介绍:   
*       备份页面菜单树索引序号设置函数，将备份页面菜单树索引序号进行修改。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_TempPageIndexSetHandle(MenuTreeIndexDef Index)
{
  G_CurrentPageTemp.CurrentMenuTreeIndex = Index;
}
/*
void MENU_LanguageSetHandle(LanguageTypeDef Language);
* 变量范围:
  Language：将要设定的语言。


* 返回值说明:void
* 功能介绍:   
*       语言设置函数，将当前页面显示语言进行修改。
* 关键备注：
* - 

  
* 未来提高:




*/
void MENU_LanguageSetHandle(LanguageTypeDef Language)
{
  G_CurrentPage.Language = Language;
}
/*
void MENU_PageNumSetHandle(uint CurrentPageNum)
* 变量范围:
CurrentPageNum:要设定的页面编号


* 返回值说明:void
* 功能介绍:   
*       页面编号设置函数，将当前页面编号进行修改。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_PageNumSetHandle(uint CurrentPageNum)
{
  G_CurrentPage.CurrentPageNum = CurrentPageNum;
}
/*
void MENU_PageTypeSetHandle(uint CurrentPageNum)
* 变量范围:
PageType:要设定的页面类型


* 返回值说明:void
* 功能介绍:   
*       页面类型设置函数，将当前页面类型进行修改。
  警告界面通常都需要定时显示，显示时间有页面信息表中的附加参数设置决定
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_PageTypeSetHandle(PageTypeDef PageType)
{
  G_CurrentPage.PageType = PageType;
}
/*
void MENU_PageTypeSetHandle(uint CurrentPageNum)
* 变量范围:
PageType:要设定的菜单树索引序号


* 返回值说明:void
* 功能介绍:   
*       菜单树索引序号设置函数，将当前页面菜单树索引序号进行修改。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_PageIndexSetHandle(MenuTreeIndexDef Index)
{
  G_CurrentPage.CurrentMenuTreeIndex = Index;
}

/*
void MENU_CurrentPageRestore()
* 变量范围:


* 返回值说明:void
* 功能介绍:   
*       当前页面还原函数，出现警告或通知界面后，需要将当前页面恢复到历史菜单列。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_CurrentPageRestore()
{
  G_CurrentPage = G_CurrentPageTemp;
}
/*
void MENU_CurrentPageRestore()
* 变量范围:


* 返回值说明:void
* 功能介绍:   
*       当前页面保存函数，预防页面跳转紊乱，将就近以及菜单列保存到页面信息缓冲区。
* 关键备注：
* - 

  
* 未来提高:

  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;


*/
void MENU_CurrentPageTempSave()
{
  G_CurrentPageTemp = G_CurrentPage;
}

/*
 //函数名称和参量和返回值类型。
static void ParamVariableInfoGet(uint*const VariableIndex,DataTypeDef*const DataType,
        DataLengthDef*const DataLength,MenuTreeIndexDef MenuTreeIndex,uchar* ShowData);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  参数选择页面变量信息获取函数，通过本函数可以获取变量的索引序号，
  数据类型，数据长度等信息。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
uchar* MENU_VariableInfoGet(uint*const VariableIndex,DataTypeDef*const DataType,
        DataLengthDef*const DataLength,DataLengthDef *const ReceiveDataLength)
{
  uchar* ShowData = NULL;
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  if(PagePtr == NULL)
  {
    HART_AbnormalPageHandle(COMMUNICATION_ERR);
    return NULL;
  }
  //如果当前页面没有挂在变量数组，则不需要进行显示变量加载。
  if(PagePtr->VariableIndex != 0x00)
  {
    //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
    *VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
    //获取HART变量的数据长度
    *DataLength = MENU_GetHartVariableDataLength(*VariableIndex);
    //获取HART变量的数据类型
    *DataType = MENU_GetHartVariableDataType(*VariableIndex);
    *ReceiveDataLength = MENU_GetHartVariableAnalysisLength(*VariableIndex); 
    //获取HART变量数组指针
    ShowData = MENU_GetHartVariablePtrIndex(*VariableIndex); 
    
    MENU_ShowVariableProtection(ShowData,*ReceiveDataLength);
  }
  return ShowData;
}
/*
//函数名称和参量和返回值类型。
void MENU_ShowVariableProtection(uchar *ShowData,DataLengthDef DataLength);
* 变量范围:
uchar *ShowData：本地HART变量指针
DataLengthDef DataLength： 
* 功能介绍:   
HART显示变量保护函数，有时通信会出现异常，或从机响应异常，但是本地参数不可以被异常
变量更改，因此，需要进行本地显示参数保护操作。
* 返回值说明:void 
*
* 关键备注：
* - 

  
* 未来提高:
*/
void MENU_ShowVariableProtection(uchar *ShowData,DataLengthDef DataLength)
{
  //如果变量处于非保护状态，并且不是单次加载命令，
  //因为有些页面需要刷新显示当前页面读取的变量。
  if((G_VariableProtect.LoadLock == FALSE)
              &&(G_SingleCommandLoad == FALSE))
  {
   HART_VariableProtect(ShowData,DataLength);
   G_VariableProtect.LoadLock = TRUE;
  }
}
/*
//函数名称和参量和返回值类型。
void MENU_ExplainInfoDisplayHandle(LanguageTypeDef Language,uchar *ShowLineIndex,PageDef *const PagePtr);
      * 变量范围:

* 功能介绍:   
菜单说明信息显示处理函数，主要用来显示标题以及页面说明，分语言处理。
* 返回值说明:void 
*
* 关键备注：
* - 

  
* 未来提高:
*/
uchar MENU_ExplainInfoDisplayHandle(LanguageTypeDef Language,uchar ShowLineIndex,PageDef *const PagePtr)
{
  //由于显示空间原因，中文菜单的参数选择界面省略标题行，直接显示内容说明
  if(Language == ENGLISH)
  {
    //读取标题字号
    FlashStringReadLockHandle(ShowLineIndex,PagePtr->TitleLineStringNum,Language);
    //菜单页面上端的两行说明标题
    ShowLineIndex = MENU_HeadlineShow(G_StrStruct,(void*)PagePtr,NORMAL,G_StringCodeBuff[ShowLineIndex]); 
    ShowLineIndex = MENU_ContentLineShow(PagePtr,ShowLineIndex,Language); 
  }
  else
  {
    if(MENU_CurrentPageTypeGet() == MENU_BAR)
    {
      ShowLineIndex = 0;
    }
    else
    {
      ShowLineIndex = MENU_ContentLineShow(PagePtr,ShowLineIndex,Language);
      ShowLineIndex++;
    }
  }
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
uchar MENU_AsciiLengthGet(uchar const *const FloatStrTemp,DataLengthDef LimitLength);
* 变量范围:

* 功能介绍:   
ASCII显示数组中数据的长度获取,通过最后标识字节作为结束判断依据，然后返回长度。
* 返回值说明:void 
*
* 关键备注：
* - 

  
* 未来提高:
*/
uchar MENU_AsciiLengthGet(uchar const *const FloatStrTemp,DataLengthDef LimitLength,uchar EndIdentification)
{
  uchar i = 0;
  while(FloatStrTemp[i] != EndIdentification)
  {
    i++;
    if(i >= LimitLength)
    {
      //report
      i = LimitLength-1;
      break;
    }
  }
  return i;
}
/*
//函数名称和参量和返回值类型。
void MENU_HandleFlagDisplay(bool8 IsExecutingState)
* 变量范围:
HandleState:
* 功能介绍:   
  翻页提示函数，提示后续还有菜单项，或者已到达最后选项。
*
* 返回值说明:void 
* 关键备注：
* - 

  
* 未来提高:
*/
void MENU_HandleFlagDisplay(HandleFlagDef HandleFlag,
      CursorShowModeDef CursorShowMode,uchar StartX,uchar StartY,LanguageTypeDef Language)
{
  uint TempCH[] = {0,0};
  uchar TempEN[] = {0,0};
  
  AssertParam(IS_HANDLE_FLAG(HandleFlag));
  AssertParam(IS_DISPLAY_MODE(CursorShowMode));
  
  switch(HandleFlag)
  {  
  case OptionsLeft:
    if(Language == CHINESE)
    {
      TempCH[0] = 0xd4;//剩余选项提示标记
      MENU_DynamicStringShow(GB_12X16,(uchar*)TempCH,StartX,StartY,CursorShowMode,Language);
    }
    else if(Language == ENGLISH)
    {
      TempEN[0] = 96+0X20;//剩余选项提示标记
      MENU_DynamicStringShow(ASCII_6X8,(uchar*)TempEN,StartX,StartY,CursorShowMode,Language);
    }
  break;
  case EndingOption:
    if(Language == CHINESE)
    {
      TempCH[0] = 0xd5;//最终页提示标记
      MENU_DynamicStringShow(GB_12X16,(uchar*)TempCH,StartX,StartY,CursorShowMode,CHINESE);
    }
    else if(Language == ENGLISH)
    {
      TempEN[0] = 97+0X20;//剩余选项提示标记
      MENU_DynamicStringShow(ASCII_6X8,(uchar*)TempEN,StartX,StartY,CursorShowMode,Language);
    }
  break;
  case InputCursor:break;
  default:break;
  }
}
/*
//函数名称和参量和返回值类型。
static void MENU_ItemVDisplay(FontDef IndexFront,const PageDef* const PagePtr,
           uchar j,uchar StructIndex,LanguageTypeDef Language,uchar LineOffset,
                                CursorShowModeDef CursorShowMode,uchar ItemHigh);
* 变量范围:
HandleState:
* 功能介绍:   
  菜单项行显示函数。
*
* 返回值说明:void 
* 关键备注：
* - 

  
* 未来提高:
*/
static void MENU_ItemVDisplay(FontDef IndexFront,const PageDef* const PagePtr,
           uchar j,uchar StructIndex,LanguageTypeDef Language,uchar LineOffset,
               CursorShowModeDef CursorShowMode,uchar ItemHigh,uchar i,uchar *LineNum)
{
  const ItemDef* CurrentItemV;
  uchar StartY = 0;
  if((IS_PARAM_DISPLAY)&&(Language == CHINESE)
     &&(PagePtr->AdditionalInfo != VARIABLE_WITHOUT_NUM))
  {
    StartY = i*ItemHigh-1;
  }
  else
  {
    StartY = i*ItemHigh;
  }
  //菜单项标号显示
  MENU_DynamicStringShow(IndexFront,LineNum,
   0,StartY,CursorShowMode,ENGLISH); 
  CurrentItemV = MENU_GetVarticalItem(PagePtr,j); 
  //菜单项字符显示
  FlashStringReadLockHandle(StructIndex,CurrentItemV->StringNum,Language);
  MENU_StaticStringShow((G_StrStruct+StructIndex),LineOffset,
            StartY,Language,CursorShowMode,G_StringCodeBuff[StructIndex]);
  if(CursorShowMode == REVERSE_DISPLAY)
  {
    if(CurrentItemV->ParamValue != NO_PARAM)
    {
      G_ParamLoadLock = MENU_ItemParamLoad(CurrentItemV);
    }
  }
}
