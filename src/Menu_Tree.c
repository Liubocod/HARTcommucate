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
//����ִ������ͱ�����TRUE�ǵ��η��ͣ�FALSE���ǵ��η���
bool8 G_SingleCommandLoad = TRUE;
PollingTypeDef G_ConnectWay = POLLING_STANDBY;
//���ֱ༭������Զ����غ������趨ֵ
bool8 G_ParamLoadLock = TRUE;
//��걣������
uchar G_CursorTempV = 0;

void MENU_TimingIntervalSelect();
bool8 MENU_ItemParamLoad(const ItemDef* CurrentItemV);
//�����˵�ģʽ�£���Ҫ��ȡ�豸�ţ����е�ǰ������ʾ
#ifndef MULTIPLE_MENU_TREE
//��ʼͨ�ó�ʼ������
CurrentPageDef  G_CurrentPage = {GENERAL_MENU_TREE,GENERAL_PAGE_INDEX_12,INITIAL_PAGE,ENGLISH};
//��ʼͨ�ó�ʼ������
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

//�����趨���Ǳ�֮ǰ��Ҫ������������ı������Ƿ������ؼ�������
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
 //�������ƺͲ����ͷ���ֵ���͡�
void  MENU_KeySwitchPageHandle()
* ������Χ:

* ����ֵ˵��:void 
* ���ܽ���:   
�����л�ҳ�洦������
���ݵ�ǰҳ���Ӧ����Ч�������ı���ʾ״̬��
*
* �ؼ���ע��
* - 
ҳ���л���������Ҫ�������ڵ�ǰҳ���һЩ����������������
�γɵ�һЩ����Ķ�������˵�˵�ҳ���в˵��������ѡ��
����ѡ�в˵�����ת���������棬�����ڲ������洦���������
ȷ�Ϸ�����һ��ҳ��ȣ����������ҪӦ�õ��Ե�ǰ��ʾ����ȫ�ֱ����Ĳ�����
���жϵ�ǰҳ������ͣ��жϳ�ҳ�����;ͻ�֪��Ӧ����δ������ҳ�棬
����˵���ҳ�������޸ģ������˳���Ϣ��ʾҳ��ȡ�

  
* δ�����:



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
  //�����������֮��Ҫ��״̬�޸ĳɿ��С�Ҫ������״̬��Ϊ��ɴ���
  G_KeyValue =  NO_KEY_STATUS;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_PageTypeSelect(KeyValueDef Key);
* ������Χ:
KeyValueDef Key���������͡�

* ����ֵ˵��:void 
* ���ܽ���:   
ҳ�洦������ѡ������
�жϵ�ǰ��ʾ��������ͣ�������Ӧ��ҳ�洦������
*
* �ؼ���ע��
* - 

  
* δ�����:
������¼���������


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
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_PageShow()
* ������Χ:
PageDef   G_CurrentPage��
ȡֵ��Χ�μ�PageDef���塣

* ����ֵ˵��:void 
* ���ܽ���:   
���ݵ�ǰҳ��ṹ���ṩ��ҳ����Ϣ����ʾ��ǰ��ҳ�档
*
* �ؼ���ע��
* - 
���ȣ���ò˵����ı�ţ��ҵ��˲˵����ı�ž��ҵ��˶�Ӧ��Ʒ�Ĳ˵���Ϣ�ˣ�
�����˵��ϵͳ�ַ�����������׵�ַ��
Ȼ���õ�ǰҳ������ͣ��������ͣ����ò�ͬ��ҳ����ʾ����������˵�ҳ����ʾ������
�༭ҳ����ʾ�����ȣ����ò�ͬ�ĺ�������Ϊ����ҳ�����ʾ���������졣 
* δ�����:
���������ҳ�����͵���ʾ������
*/ 
void MENU_PageShow()
{ 
  //�����һ��ҳ���뵱ǰ��ҳ�治��ͬ�����������������ٽ���ǰҳ�渳����ǰҳ�����
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
      //�ֲ����汾��ʾ���棬��Ҫͣ��3�룬���ڹ۲�
      while(1)
      {
        if(G_WarningTimeStamp == 0)
        {
          break;
        }
        //���Ź�ι��       
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
      //��Ҫ�ھ������ͣ��1��,�����Ҫ����ʱ������ֵ������switch���
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
 //�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_HeadlineShow(const StringDef* StrStruct,const PageDef* Page,CursorShowModeDef CursorMode);
* ������Χ:
const StringDef* StrStruct���ַ����ṹ��
const PageDef* Page��ҳ��ָ�롣
CursorShowModeDef CursorMode�������ʾ��ʽ��
* ����ֵ˵��:���ر�������ռ������Ϊ����Ҫ��ʾ�����ṩ����ָʾ�� 
* ���ܽ���:   
��ʾ�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:
������¼���������
������������ͽ��档
*/

uchar MENU_HeadlineShow(StringDef* const StrStruct,
                        const PageDef* const CurrentPage,
                        CursorShowModeDef CursorMode,uchar* StringCodeArr)
{
    uchar i = 0,j;
    uchar Headline[] = {0x28,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00};//Tag������
    FontMatrixDef FontMatrix; 
    FlashStringCodeGet(StrStruct,StringCodeArr,ENGLISH);
    MENU_StaticStringShow(StrStruct,START_X_INDEX,
             START_Y_INDEX,ENGLISH,NORMAL,StringCodeArr);
    //���������ΪOnlineʱ�ı�������ʾ����
    if(StrStruct->StructNum == 0x01) 
    {
      j = HART_ASCII_Decode(Headline+1,ASCII_6,ASCII_8,G_Tag);
      Headline[j+1] = 0x29;//������
      MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[ENGLISH]);
      MENU_DynamicStringShow(ASCII_6X8,Headline,
                    START_X_INDEX+(StrStruct->CharacterNumber[ENGLISH])*FontMatrix.HorizontalLine, 
                                     START_Y_INDEX,NORMAL,ENGLISH);
    }
    i++; 
    return  i;  
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void MENU_DisplayWords();
* ������Χ:
const StringDef* StrStruct���ַ����ṹ��
const PageDef* Page��ҳ��ָ�롣
CursorShowModeDef CursorMode�������ʾ��ʽ��
* ����ֵ˵��:���ر�������ռ������Ϊ����Ҫ��ʾ�����ṩ����ָʾ�� 
* ���ܽ���:   
��ʾ�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:
������¼���������
������������ͽ��档
*/
static void MENU_DisplayWords(uchar CharacterHorizontalLine,uchar CharacterVerticalLine
                              ,uchar VerticalPostion,uchar TempN,uchar HorizontalPostion,CursorShowModeDef CursorShowMode
                                ,long unsigned int TempLibrary,unsigned int IntTemp)
{
  unsigned char Tmpi,Tmpj;
  uchar ColumnSetIndex = 0,PageSetIndex = 0;
  uint DataNumber = CharacterHorizontalLine*CharacterVerticalLine;
  
  FlashWordLibInfoGet(TempLibrary+IntTemp,DataNumber,G_WordLibrary);
  //��ʼˢ�㣬���϶��£��������
  for(Tmpi = 0; Tmpi < CharacterVerticalLine; Tmpi++)
  {
      //�趨������
      LcdSetPage(VerticalPostion+Tmpi);
      //�趨������                   
      LcdSetColumn(CharacterHorizontalLine*TempN+HorizontalPostion);

      //���У�����ˢ��
      for(Tmpj = 0; Tmpj < CharacterHorizontalLine; Tmpj++)
      {
          ColumnSetIndex = CharacterHorizontalLine*TempN+HorizontalPostion + Tmpj;
          PageSetIndex = VerticalPostion+Tmpi;
          if(ColumnSetIndex >= LCD_MAX_BOUNDARY)
            break;
          LCD_CS_Switch(ColumnSetIndex,PageSetIndex);

          if(CursorShowMode == REVERSE_DISPLAY)
          {
            //����
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
 //�������ƺͲ����ͷ���ֵ���͡�
void	MENU_StaticStringShow(StringDef StrStructure,uchar HorizontalPostion,uchar VerticalPostion
                                                            CursorShowModeDef CursorShowMode)
* ������Χ:
StringDef StrStructure��
//�ַ����ṹ�嶨��
typedef struct 
{
  uint StructNum;                              //�ַ������
  FontDef FontNum[LANGUAGE_NUMBER];            //�ֿ���
  uchar CharacterNumber;                       //�ַ����� 
  const uint *LanguageTypeNum[LANGUAGE_NUMBER];//����ָ������ 
}StringDef;
HorizontalPostion��ˮƽλ��
VerticalPostion����ֱλ��

CursorShowModeDef CursorShowMode�����ģʽ
typedef enum
{
  HIDE,
  REVERSE_DISPLAY,
  FLASH
}CursorShowModeDef;


* ����ֵ˵��:void 
* ���ܽ���:   
  ��ʾ��̬�ַ�����������⣬�˵���ȡ�
*
* �ؼ���ע��
* - 
  CharacterHorizontalLine��ˮƽ�����еĸ�����
  CharacterVerticalLine����ֱ�����ֽڵĸ�����

  const uint *LanguageTypeNum[LANGUAGE_NUMBER];//����ָ������ 
  FontDef FontNum[LANGUAGE_NUMBER];          //�ֿ���
  �����������Ϊ��ȷ�����Եģ���ʾʲô����Ҫ����
  typedef enum
  {
    ENGLISH = 0,
    CHINESE
  }LanguageTypeDef;
  ����ʾҳ�����G_CurrentPage����һ���������͵Ķ��壬���Ը�����������
  ȷ����ǰ��ʾ�����ԡ�
  ÿ��������ִ����ᱻ��ŵ������������У���������Ŷ����ַ����ṹ�����š�

* δ�����:
�ַ���������ʾ����,Ҫ�ֵ���ʾ.c�ļ���


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
                //�ֿ�����ʾһ���ַ����ܵ�����ÿһ����Ϊһ���ֽ�
		IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
                //�����ַ����ֿ����һ�У�������һ��ˢ�����ֽڸ�����������ַ����ֿ��еľ������
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
                //��ʼˢ�㣬���϶��£��������
		MENU_DisplayWords(CharacterHorizontalLine,CharacterVerticalLine,
                              VerticalPostion,TempN,HorizontalPostion,CursorShowMode,TempLibrary,IntTemp);

	}
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_FontMatrixGet(FontMatrixDef *FontMatrix,FontDef Font)
* ������Χ:
FontMatrixDef *FontMatrix��
typedef struct 
{
  uchar HorizontalLine;
  uchar VerticalLine;
  const uchar *Library;
}FontMatrixDef;

FontDef Font��
typedef enum 
{
  ASCII_6X16,
  GB_12X16,
  ASCII_5X8
}FontDef;

* ����ֵ˵��:void 
* ���ܽ���:  
  �ֿ������Ϣ��ȡ��������ȡ��ǰ�ֿ�ĵ�����Ϣ�����ݵ�����

*
* �ؼ���ע��
* - 
��������Ҫ��Ϊ�˻�ȡÿ���ֵĺ���ռ�ÿ���Լ�����ռ�ÿ�ȣ����������ַ���
�����ġ� 
* δ�����:
������µ��ֿ�
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
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_DynamicStringShow(FontDef LibraryIndex,uchar *String,uchar HorizontalPostion,uchar VerticalPostion,
                                                                            CursorShowModeDef CursorShowMode);
* ������Χ:
FontDef LibraryIndex:�ֿ�����������ȷ����ʾ���������ĸ��ֿ�
uchar *String��Ҫ��ʾ���ִ����ݡ�
uchar HorizontalPostion��ˮƽ���ꡣ
uchar VerticalPostion����ֱ���ꡣ
CursorShowModeDef CursorShowMode�������ʾģʽ��
* ����ֵ˵��:void 
* ���ܽ���:   
* ������ʾ�ǳ����ַ����ĺ��������綯̬�仯�����ݡ�
* �ؼ���ע��
* - 
* δ�����:
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
          //�ֿ�����ʾһ���ַ������ֽڸ�����
          IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
          //������ַ������ַ����ֿ����һ�У��ֿ�һ����һ���ַ���
          IntTemp = (String[TempN]-0x20)*IntTemp;
          //��ʼˢ�㣬���϶��£��������
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
          //�ֿ�����ʾһ���ַ������ֽڸ�����
          IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
          //������ַ������ַ����ֿ����һ�У��ֿ�һ����һ���ַ���
          IntTemp = StringCH[TempN]*IntTemp;
          //��ʼˢ�㣬���϶��£��������
          MENU_DisplayWords(CharacterHorizontalLine,CharacterVerticalLine,
                        VerticalPostion,TempN,HorizontalPostion,CursorShowMode,TempLibrary,IntTemp);
          TempN++;
      }
    }
}

/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	MENU_ClearLcdScreen(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����������

*
* �ؼ���ע��
* - 

  
* δ�����:
��Ҫ������ʾ�ļ��С�


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
 //�������ƺͲ����ͷ���ֵ���͡�
void MenuPageRefrashTimeLoad(const PageDef *CurrentPage);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  �˵�ҳ����������غ�����
  ���𽫵�ǰ��ʾҳ���й��صı������������ȡ���������������ظ���󱣴浽����
  ִ�����鵱�У�Ŀǰֻ����HART��������

*
* �ؼ���ע��
* - 
 ҳ������ӷ�ʽ�ж��֣�POLLING_STANDBY��ʾ����ѯ״̬��Ҳ���Ƿ��������ӷ�ʽ��
  
* δ�����:



*/ 
void MENU_PageCommandGroupLoad(const PageDef *const CurrentPage)
{
  uint i=0,VariableIndex;
  uchar CommandIndexCount = 0;
  
  //������ӷ�ʽ�ǲ���ѯ����������������Ҫ��������ִ��������ز���
  G_ConnectWay = CurrentPage->ConnectWay;
  //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
  FlashVariableGroupLoad(CurrentPage->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);

  //�����ǰҳ��Ϊ������ҳ��
  if(CurrentPage->ConnectWay == POLLING_STANDBY)
  {
  
  }
  else
  {
    //���ݵ�ǰҳ����صı�����������������������ظ��������ȥ��
    for(i = 0;i < MENU_PageVariableNumber(G_PageVariableTable);i++)
    {
      //��ȡ�����ڱ�����ǰҳ����������е����
      VariableIndex = MENU_VariableIndexInfoGet(i,G_VariableGroupTable);
      //HART����ִ��������غ��������߱��������ڱ����������ҵ���Ӧ�������ţ�������������ͨ��ʵ����ʽ����
      FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
      HART_CommandExecuteArrLoad(G_VariableStructureInfo.VariableStructureInfo.CommandIndex,
                                 &CommandIndexCount);
    }
    if((CurrentPage->ConnectWay == INIT_CONNECT)||(CurrentPage->ConnectWay == HALF_CONNECT_0)
       ||(CurrentPage->ConnectWay == HALF_CONNECT_8)||(CurrentPage->ConnectWay == ALL_CONNECT)
            ||(CurrentPage->ConnectWay == ALL_CONNECT_31)||(CurrentPage->ConnectWay == ALL_CONNECT_63)
                                                          ||(CurrentPage->ConnectWay == SINGLE_CONNECT))
    {
      //���ʼ����������صģ���Ҫ��HART������־�趨ΪHART��ʼ�����������
      G_HART_HandleFlag = HART_INIT_COMMAND_HANDLE;
    }
    else if((CurrentPage->ConnectWay == REFRESH)||(CurrentPage->ConnectWay == WAITING_CONNECT)
            ||(CurrentPage->ConnectWay == COMMON_PAGE_CONNECT))
    {
      //����Ƿǳ�ʼ�����ӷ�ʽ����HART�����־������ֵΪͨ�������
      G_HART_HandleFlag = HART_COMMON_COMMAND_HANDLE;
    }
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = CommandIndexCount;
    G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
  }
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_PageShowSwitch()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ҳ����ʾ�л�������
��Ҫ�ı���������ʱ��Flag���ó�TRUE,����Ҫ�ı���������ʱ������رգ�Flag���ó�FALSE
*
* �ؼ���ע��
* - 
  
* δ�����:


������Update�޸�

*/ 
void MENU_PageShowSwitch(bool8 Flag)
{
   G_PageChangeFlag = Flag;
}

 /*/�������ƺͲ����ͷ���ֵ���͡�
void MENU_LineNumEdit(uchar *const LineNum,uchar LineTemp)
* ������Χ:
     LineNum:�к����顣
     LineTemp���кŲο�������
* ����ֵ˵��:void 
* ���ܽ���:   
  �кű༭���������˵��������������������飬Ϊ��ʾ�ṩ������
*
* �ؼ���ע��
* - 
������Ҳ�����ڱ༭�����������š�
ע�⣬������ֻ�ʺ�255���ڵ���ű༭�������������Χ��Ҫ�޸Ĳ����������͡�
* δ�����:



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
 /*/�������ƺͲ����ͷ���ֵ���͡�
void MENU_HorizontalItemShow(const PageDef* CurrentPage,const StringDef* StrStruct,
                                                const ItemDef* CurrentItemH,FontMatrixDef FontMatrix)

* ������Χ:
const PageDef* Page��ҳ��ָ�롣
const StringDef* StrStruct���ַ����ṹ��ָ�롣
* ����ֵ˵��:void 
* ���ܽ���:   
  ˮƽ�˵���
*
* �ؼ���ע��
* - 

* δ�����:



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
        //������˵������ʣ������ظ�ÿһ������˵���������ֺ���˵���
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


/*/�������ƺͲ����ͷ���ֵ���͡�
const PageDef* MENU_GetCurrentMenuPage()
* ������Χ:
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:const PageDef* ����ҳ��ṹ��ָ�룬����ǰִ��ҳ�档 
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ���ǰ��ʾҳ�����ţ������
��ǰҳ��Ļ�����Ϣ
*
* �ؼ���ע��
* - 

* δ�����:



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
/*/�������ƺͲ����ͷ���ֵ���͡�
PageDef* MENU_GetCurrentMenuPageTemporary()
* ������Χ:
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:const PageDef* ����ҳ��ṹ��ָ�룬����ǰִ��ҳ�档 
* ���ܽ���:   
  Ϊ�˼��ٶ�ȡFLASH�Ĵ����������˱���������Ϊҳ����Ϣ��ȡһ��Ϳ��ԣ�
  �����Ѿ������ڱ��أ����ֱ�ӻ�ȡ����ָ����з��ʼ��ɡ�
*
* �ؼ���ע��
* - 

* δ�����:



*/

PageDef* MENU_GetCurrentMenuPageTemporary()
{
  return &G_CurrentPageStruct.CurrentPageInfo;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uint MENU_CurrentPageNumGet()
* ���ܽ���:   
  ����ҳ����ŷ��غ���
*
* �ؼ���ע��
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* δ�����:



*/
uint MENU_CurrentPageTempNumGet()
{
  return G_CurrentPageTemp.CurrentPageNum;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_GetMenuTreeIndexTemp()
* ������Χ:


* ����ֵ˵��:�˵������ 
* ���ܽ���:   
����ҳ��˵�����Ż�ȡ����
*
* �ؼ���ע��
* - 

  
* δ�����:
������¼���������


*/
MenuTreeIndexDef MENU_GetMenuTreeIndexTemp()
{
  return G_CurrentPageTemp.CurrentMenuTreeIndex;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
PageTypeDef MENU_CurrentPageTempTypeGet()
* ���ܽ���:   
  ����ҳ�����ͷ��غ���
*
* �ؼ���ע��
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* δ�����:



*/
PageTypeDef MENU_CurrentPageTempTypeGet()
{
  return G_CurrentPageTemp.PageType;
}
/*
LanguageTypeDef MENU_TempLanguageTypeGet(void );
* ������Χ:


* ����ֵ˵��:LanguageTypeDef,���ص�ǰ��������
* ���ܽ���:   
*       ����ҳ�����������ȡ��������ȡ��ǰ��ʾ�������ࡣ
* �ؼ���ע��
* - 

  
* δ�����:




*/
LanguageTypeDef MENU_TempLanguageTypeGet(void )
{
  return G_CurrentPageTemp.Language;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uint MENU_CurrentPageNumGet()
* ���ܽ���:   
  ��ǰҳ����ŷ��غ���
*
* �ؼ���ע��
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* δ�����:



*/
uint MENU_CurrentPageNumGet()
{
  return G_CurrentPage.CurrentPageNum;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_GetMenuTreeIndex()
* ������Χ:


* ����ֵ˵��:�˵������ 
* ���ܽ���:   
�˵�����Ż�ȡ����
*
* �ؼ���ע��
* - 

  
* δ�����:
������¼���������


*/
MenuTreeIndexDef MENU_GetMenuTreeIndex()
{
  return G_CurrentPage.CurrentMenuTreeIndex;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
PageTypeDef MENU_CurrentPageTypeGet()
* ���ܽ���:   
  ��ǰҳ�����ͷ��غ���
*
* �ؼ���ע��
* - 
  MenuTreeIndexDef CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;
* δ�����:



*/
PageTypeDef MENU_CurrentPageTypeGet()
{
  return G_CurrentPage.PageType;
}
/*
LanguageTypeDef MENU_LanguageTypeGet(void );
* ������Χ:


* ����ֵ˵��:LanguageTypeDef,���ص�ǰ��������
* ���ܽ���:   
*       ���������ȡ��������ȡ��ǰ��ʾ�������ࡣ
* �ؼ���ע��
* - 

  
* δ�����:




*/
LanguageTypeDef MENU_LanguageTypeGet(void )
{
  return G_CurrentPage.Language;
}
 /*/�������ƺͲ����ͷ���ֵ���͡�
const StringDef* MENU_GetStrStruct(uint MenuTreeIndex)
* ������Χ:
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:const StringDef* �����ַ����ṹ��ָ�롣 
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ���ǰ��ʾʱ��Ҫ�õ����ַ����⡣
*
* �ؼ���ע��
* - 

* δ�����:



*/
StringDef MENU_GetStrStruct(uint StructNum)
{
  FlashStringInfoGet(StructNum,G_StringStruct.StringInfoArr);
  return G_StringStruct.StringInfo;
}
 /*/�������ƺͲ����ͷ���ֵ���͡�
uint MENU_VariableIndexInfoGet(uchar OffSet);
* ������Χ:
uint OffSet:�������е�������ţ��ҵ�ָ��������Ĭ��0Ϊ�����׸���ֵ��
* ����ֵ˵��:uint�������ڱ��������ҵ���Ӧ�ı�������ţ����Է��ʱ�����Ϣ�� 
* ���ܽ���:   
*       ������Ż�ȡ������ͨ��ƫ�Ʋ�����
  �ڱ������е��ҵ���Ӧ�ı���������ͨ����������ſ��Է��ʱ������еı�����Ϣ��
* �ؼ���ע��
* - 

* δ�����:



*/
uint MENU_VariableIndexInfoGet(uchar OffSet,VariableGroupDef GroupTable)
{
  return GroupTable.VariableGroupI[OffSet];
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_PageVariableNumber();
* ������Χ:
* ����ֵ˵��:uchar ��������ǰҳ��������еı��������� 
* ���ܽ���:   
*       ҳ�����������ȡ��������ȡ��ǰҳ��������б���ı����ܸ�����
* �ؼ���ע��
* - 

* δ�����:



*/
uchar MENU_PageVariableNumber(PageVariableTableDef PageVariableTable)
{
  return PageVariableTable.PageVariableInfo.CurrentPageVariableNumber;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uchar* MENU_GetHartVariableDataType(uint VariableIndex,uint MenuTreeIndex)
* ������Χ:
uint VariableIndex:�����������������š�
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:HART_DataTypeDef  ����HART�������������͡�
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ�HART�������������͡�
*
* �ؼ���ע��
* - 

* δ�����:



*/
DataTypeDef MENU_GetHartVariableDataType(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.DataType; 
}
/*/�������ƺͲ����ͷ���ֵ���͡�
DataLengthDef MENU_GetHartVariableDataLength(uint VariableIndex,uint MenuTreeIndex)
* ������Χ:
uint VariableIndex:�����������������š�
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:HART_DataTypeDef  ����HART�������������͡�
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ�HART�������������͡�
*
* �ؼ���ע��
* - 

* δ�����:
*/
DataLengthDef MENU_GetHartVariableDataLength(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.DataLength; 
}
/*/�������ƺͲ����ͷ���ֵ���͡�
DataLengthDef MENU_GetHartVariableAnalysisLength(uint VariableIndex,uint MenuTreeIndex)
* ������Χ:
uint VariableIndex:�����������������š�
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:HART_DataTypeDef  ����HART�������������͡�
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ�HART�������������͡�
*
* �ؼ���ע��
* - 

* δ�����:



*/
DataLengthDef MENU_GetHartVariableAnalysisLength(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableStructureInfo.VariableStructureInfo.AnalysisLength; 
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex,uint MenuTreeIndex)
* ������Χ:
uint VariableIndex:�����������������š�
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:uchar * ����HART�����ַ�������ָ�롣
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ�HART����ֵ�ı������顣
*
* �ؼ���ע��
* - 

* δ�����:



*/
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return G_VariableTablePtr[G_VariableStructureInfo.VariableStructureInfo.VariablePtr]; 
}
/*/�������ƺͲ����ͷ���ֵ���͡�
uchar* MENU_GetHartVariablePtrIndex(uint VariableIndex)
* ������Χ:
uint VariableIndex:�����������������š�
uint MenuTreeIndex:�˵���������ȷ����ǰ��ʾ������һ�ֲ�Ʒ�Ĳ˵�����
* ����ֵ˵��:uchar * ����HART�����ַ�������ָ�롣
* ���ܽ���:   
ͨ�������������Ը��ݵ�ǰ��Ʒ�˵������ҵ�HART����ֵ�ı������顣
*
* �ؼ���ע��
* - 

* δ�����:



*/
const HART_UnitDef* MENU_GetHartUnitTable(uint VariableIndex)
{
  FlashVariableInfoGet(VariableIndex,G_VariableStructureInfo.VariableStructure);
  return (G_UnitTableIndexPtr[G_VariableStructureInfo.VariableStructureInfo.Table]);
}
/*/�������ƺͲ����ͷ���ֵ���͡�
static void MENU_NoUnitVariableShow(uchar ShowVariableIndex,uchar line
                             ,CursorShowModeDef CursorShowMode)
* ������Χ:

* ����ֵ˵��:void
* ���ܽ���:   
�˵�ҳ���޵�λ�в�����ʾ������
���Խ���Щû�е�λ�Ĳ�����ֱ����ʾ�ڲ˵�ҳ����к��档
*
* �ؼ���ע��
* - 

* δ�����:

�������ܻ����Ӵ��зǱ�ĵ�λ������ʾ����Ŀǰ��ʱû�д�����档

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


  
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  StrTemp = StrCodeBuff;
  //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
  VariableIndex = MENU_VariableIndexInfoGet(ShowVariableIndex,G_VariableGroupTable);
  ReceiveDataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);  
  DataType = MENU_GetHartVariableDataType(VariableIndex);
  //��ȡHART��������ָ��
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);

  Length = MENU_DataToASCII(ShowData,FloatStrTemp,DataType);
  if(PagePtr->AdditionalInfo == FIXED_UNIT_VSHOW)
  {
    //����HVP SLҳ��̶���λ��ʾ����
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
/*/�������ƺͲ����ͷ���ֵ���͡�
void MENU_VerticalItemShow(uchar StartItem,uchar EndItem,uchar i,
                           const PageDef* const CurrentPage,uchar LineOffset,
                           const StringDef*const StrStruct,const ItemDef*const CurrentItemV)
* ������Χ:

* ����ֵ˵��:void
* ���ܽ���:   
����˵�����ʾ����
*
* �ؼ���ע��
* - 

* δ�����:



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
   //����˵�����ʾ
   for(j = StartItem; j < EndItem;j++,i++,StructIndex++)
   {
     //�к�ƫ�Ƽ��㡣
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
      //���ø�����Ϣ���ڲ˵������޵�λ��������ĩ��ʾ
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

/*/�������ƺͲ����ͷ���ֵ���͡�
void MENU_CursorTrace(const PageDef* CurrentPage)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
* ����ֵ˵��:void
* ���ܽ���:   
���׷�ٺ���
*
* �ؼ���ע��
* - 

* δ�����:



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

/*/�������ƺͲ����ͷ���ֵ���͡�
static void MENU_ContentLinePrint(const PageDef *const CurrentPage,uchar ShowLineIndex)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
ShowLineIndex����ǰ��ӡ�����

* ����ֵ˵��:void
* ���ܽ���:   
��˵����Ϣ��ӡ�����������б����д�ӡ��

*
* �ؼ���ע��
* - 

* δ�����:



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

/*/�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_ContentLineShow(const PageDef *CurrentPage,uchar i,const StringDef* StrStruct)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
StrStruct���ַ�����ָ��
i:������ʾ����ʼ�У�
* ����ֵ˵��:void
* ���ܽ���:   
��˵����Ϣ��ʾ������

*
* �ؼ���ע��
* - 

* δ�����:



*/
uchar MENU_ContentLineShow(const PageDef *const CurrentPage,uchar ShowLineIndex,LanguageTypeDef Language)
{
  uchar i = 0;
  //���ֽ�����Ҫ���������Ӣ�ĸ��˵�����
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
/*/�������ƺͲ����ͷ���ֵ���͡�
void MENU_GetVarticalItem(const PageDef* CurrentPage,uint MenuTreeIndex)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
MenuTreeIndex:�˵�����ţ�����ȷ�����ֲ�Ʒ�Ĳ˵��ṹ��
* ����ֵ˵��:const ItemDef* �˵�������ָ��
* ���ܽ���:   
��ȡ��ǰҳ������˵���ָ�룬

*
* �ؼ���ע��
* - 

* δ�����:



*/
const ItemDef* MENU_GetVarticalItem(const PageDef*const CurrentPage,uint  MenuItemOffset)
{
  MenuTreeIndexDef MenuTreeIndex = MENU_GetMenuTreeIndex();
  FlashCurrentItemInfoGet(MenuTreeIndex,
                          CurrentPage->ItemArrIndexV+MenuItemOffset,G_CurrentItemStruct.CurrentItemInfoArr);
 return &G_CurrentItemStruct.CurrentItemInfo;
}
/*/�������ƺͲ����ͷ���ֵ���͡�
const ItemDef* MENU_GetHorizontalItem(const PageDef* CurrentPage,uint MenuTreeIndex)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
MenuTreeIndex:�˵�����ţ�����ȷ�����ֲ�Ʒ�Ĳ˵��ṹ��
* ����ֵ˵��:const ItemDef* �˵�������ָ��
* ���ܽ���:   
��ȡ��ǰҳ�����˵���ָ�룬

*
* �ؼ���ע��
* - 

* δ�����:



*/
const ItemDef* MENU_GetHorizontalItem(const PageDef*const CurrentPage,uint  MenuItemOffset)
{
  MenuTreeIndexDef MenuTreeIndex = MENU_GetMenuTreeIndex();
  FlashCurrentItemInfoGet(MenuTreeIndex,
                          CurrentPage->ItemArrIndexH+MenuItemOffset,G_CurrentItemStruct.CurrentItemInfoArr);
  return &G_CurrentItemStruct.CurrentItemInfo;
}

/*
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_HorizontalItemLinkHandle(const ItemDef* CurrentItem,const PageDef* CurrentPage)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
const ItemDef* CurrentItem������˵���ָ�롣

* ����ֵ˵��:void 
* ���ܽ���:   
  �����������л���������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void MENU_HorizontalItemLinkHandle(const ItemDef*const CurrentItem,const PageDef*const CurrentPage)
{
   MENU_CursorTrace(CurrentPage);
   MENU_PageNumSetHandle(CurrentItem->NextLayerNum);
   MENU_PageTypeSetHandle(CurrentItem->NextLayerType);
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void Menu_BackupPageLinkHandle(const PageDef*const CurrentPage);
* ������Χ:
CurrentPage����ǰҳ��ָ�롣

* ����ֵ˵��:void 
* ���ܽ���:   
  �����ϼ�ҳ�����Ӵ�������ͨ�����������Է��ص�ǰҳ��󶨵ĸ����˵���
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void Menu_BackupPageLinkHandle(const PageDef*const CurrentPage)
{
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  G_CursorNumV = CurrentPage->PreviousOrNextItemLine-1; 
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_ItemLinkHandle(const ItemDef* CurrentItem,const PageDef* CurrentPage)
* ������Χ:
CurrentPage����ǰҳ��ָ�롣
const ItemDef* CurrentItem������˵���ָ�롣

* ����ֵ˵��:void 
* ���ܽ���:   
  ͨ�ò˵��������л���������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void MENU_GeneralItemLinkHandle(const ItemDef*const CurrentItem)
{
  //�³�Ϊ0�����壬�����޷������³�����
   if((CurrentItem->ParamValue == TDR)
      &&(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0.00))
   {
     
   }
   else
   {
     //�������
     if(CurrentItem->ParamValue == SINGLE_C)
     {
        G_SingleCommandLoad = TRUE;
     }
     //����Ǳ����д������Ŵ�ʱ��Ҫ�����߻�ԭ�����̼�2
     if(CurrentItem->ParamValue == NO_ZOOM)
     {
        G_IsCurveZoom = FALSE;
     }
     //���߽����ʼ��
     if(CurrentItem->ParamValue == CURVE_INIT)
     {
       G_IsCurveZoom = FALSE;
       CurveNoZoomHandle();
     }
     //�л�Ӣ�Ĵ���
     if(CurrentItem->ParamValue == LANGUAGE_ENGLISH)
     {
        MENU_LanguageSetHandle(ENGLISH);
        MENU_TempLanguageSetHandle(ENGLISH);
        G_PreviousShowPage.Language = ENGLISH;
        SaveChar(0,ENGLISH);
     }
     //�л�Ӣ�Ĵ���
     if(CurrentItem->ParamValue == LANGUAGE_CHINESE)
     {
        MENU_LanguageSetHandle(CHINESE);
        MENU_TempLanguageSetHandle(CHINESE);
        G_PreviousShowPage.Language = CHINESE;
        SaveChar(0,CHINESE);
     }
     //���߽����ʼ��
     if(CurrentItem->ParamValue == FAKE_END)
     {
        CurveFakeNhlEndHandle();
     }
     if(CurrentItem->ParamValue == DIST_CALI_HANDLE)
     {
        G_IsSpecificHandle = TRUE;
     }
     //��λҳ���л�����
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
     //����flash��ȡ
     FlashReadLockHandle(FALSE);
   }
}

/*
 //�������ƺͲ����ͷ���ֵ���͡�
void MENU_PageLinkHandle(const PageDef* CurrentPage);
* ������Χ:
CurrentPage����ǰҳ��ָ�롣

* ����ֵ˵��:void 
* ���ܽ���:   
  ҳ�淽ʽ�л���������
  ���ˮƽȡ���˵��������·����

*
* �ؼ���ע��
* - 

  
* δ�����:
��Ҫ������ʾ�ļ��С�


*/ 
void MENU_PageLinkHandle(const PageDef*const CurrentPage)
{
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  MENU_CursorTrace(CurrentPage);
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_VariableShow(DataLengthDef DataLength,uchar *ShowData,uchar StartY,
                       const PageDef *CurrentPage,uchar StartX)* ������Χ:
DataTypeDef DataType:�������������ͣ�������������Ϊ�����ĳ��ȣ����ֽڸ�����
uchar *ShowData��Ҫ����ʾ���ַ��������׵�ַ��
uchar i����ǰ��ʾ�������бꡣ
const PageDef *CurrentPage��ָ��ǰ��ʾҳ���ָ�롣
* ����ֵ˵��:uchar ����ʾ���������б귵�أ�������һ����ʾ�ҵ�λ�á� 
* ���ܽ���:   
�༭������ʾ��������������Ҫ�����ǽ��༭ҳ���Ϲ��صı����Լ����ر����ĸ�������
��ʾ�ڱ༭����Ķ�Ӧλ�á�

*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
bool8 MENU_PageRefreshIntervalHandle(void)
* ������Χ:

* ����ֵ˵��:
����TRUE˵����ǰҳ������ˢ������棬����FALSE˵�������ڡ�
* ���ܽ���:   
ҳ��ˢ�¼��������
�����ж�ˢ�����Խ����ˢ��ʱ������

*
* �ؼ���ע��
* - 

  
* δ�����:
*/
 
bool8 MENU_PageRefreshIntervalHandle(void)
{
  PageDef *PagePtr = NULL;
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  if(PagePtr->ConnectWay == REFRESH)
  {
    //�����ǰҳ��������ˢ������棬����ʱ������Ѿ����һ�����ڣ������¼������ڼ���ֵ��
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_TimingIntervalSelect()
* ������Χ:

* ���ܽ���:   


*
* �ؼ���ע��
* - 

  
* δ�����:
*/
 

void MENU_TimingIntervalSelect()
{
  PageDef *PagePtr = NULL;
    //��ȡ�˵������
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
//�������ƺͲ����ͷ���ֵ���͡�
float	MENU_CharToFloat( uchar DecimalP,uchar *ShowDataBuffe,uchar Length )
* ������Χ:

* ���ܽ���:   
��ʾ�ַ���ת��Ϊfloat��ֵ��

*
* �ؼ���ע��
* - 

  
* δ�����:
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
        //�ַ����ַ�������ȷ����ʮ���ֽ�
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
//�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_DataToASCII(uchar *ShowData,uchar *Temp,DataTypeDef DataType)
* ������Χ:

* ���ܽ���:   
float����ת����ASCII������
���ݵı������;���char����Ϊ׼��float��������Ҳ�������ַ������У��������Ĺ���
���ǽ�float�ַ�������ת���ɿ�����ʾ��ASCII��������
*
* �ؼ���ע��
* - 

  
* δ�����:
С����λ�����ܻ���Ϊ�������롣
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
  //����ֵ������λ��С�����С��λ
  return TempLength+DecimalN+2;
}

/**  static void BufReverseCopy(void* Destination,void* Source,uchar8 Length)//�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
Destination��Ŀ�����顣
Source��Դ����
Length�����Ƴ�Ա����

* ����ֵ˵��: 
* ���ܽ���:   
   ��Դ��������ݷ��򿽱���Ŀ������
*
* �ؼ���ע��
* - ���ڸ��Ƹ������ǵ��øú���ʱ�ϸ��жϣ������������ж�
* δ�����: 
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
//�������ƺͲ����ͷ���ֵ���͡�
float MENU_DataToFloat(uchar *ShowData,DataTypeDef FLOAT_T)
* ������Χ:

* ���ܽ���:   
���ĸ��ֽڵ�����֡����ת����float����

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_FloatToData(uchar *const ShowData,float FloatV,DataTypeDef Type);
* ������Χ:

* ���ܽ���:   
������������ת�����ĸ��ֽڵı������顣

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_FloatToData(float FloatData,uchar *ShowData,DataTypeDef FLOAT_T)
* ������Χ:

* ���ܽ���:   


*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_DataCopy(uchar *G_OutputLevel,const uchar *FourMA,DataTypeDef FLOAT_T);

* ������Χ:

* ���ܽ���:   


*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
bool8 MENU_ItemParamLoad(const ItemDef* CurrentItemV)
* ������Χ:

* ���ܽ���:   
�˵��������������
�����һЩ��ʼ��Ϣ��ҪԤ���أ�����ͨ������������λ����Ҳ����ͨ�����������д���

*
* �ؼ���ע��
* - 

  
* δ�����:
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
    case CURSORX_PARAM://���߹����������ʼ��
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_IS_SingleCommandLoad(bool8 LoadStatus,const PageDef CurrentPage)
* ������Χ:

* ���ܽ���:   


*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
bool8 MENU_ParamReset()
* ������Χ:

* ���ܽ���:   
����������λ������
��Ϊ��Щ������Ҫ����0ֵ�Ĳ�����ͨ��������������

*
* �ؼ���ע��
* - 

  
* δ�����:
*/
bool8 MENU_ParamReset()
{
  uchar ZeroParam[] = {0x00,0x00,0x00,0x00};
  //���ڻ���ݲ�ͬ��֧���в�ͬ����
  MENU_DataCopy(G_OutputLevel,ZeroParam,FLOAT);
  return TRUE;
}

/*
void MENU_DateShow()
* ������Χ:

ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   

*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:

ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   
�ַ���ASCIIת�����������ݺ���
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:

ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   
��긴λ����
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_CursorNumReset()
{
   G_CursorNumV = 0;
   G_CursorNumH = 0;
}
/*
void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage)

* ������Χ:
CurrentPage����ǰ��ʾ�������ͽṹ��ָ��
ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   
��������Ӳ˵����쳣�������ֳ�����������
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_SiementsReturnPageSave(const PageDef* CurrentPage)
{

}
/*
void MENU_ChuanYiReturnPageSave(const PageDef* CurrentPage)

* ������Χ:
CurrentPage����ǰ��ʾ�������ͽṹ��ָ��
ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   
��Դ��ǲ˵����쳣�������ֳ�����������
*
* �ؼ���ע��
* - 

  
* δ�����:




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

* ������Χ:
CurrentPage����ǰ��ʾ�������ͽṹ��ָ��
ASCII_Tag
G_Tag


* ����ֵ˵��:void
* ���ܽ���:   
�쳣�������ֳ�����������
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_ReturnPageSave(const PageDef* CurrentPage)
{
  //���ǵ������쳣���ؼ���
  if(MENU_GetMenuTreeIndex() == CHUAN_YI)
  {
    MENU_ChuanYiReturnPageSave(CurrentPage);
  }//�����ӵ������쳣����
  else if(MENU_GetMenuTreeIndex() == SIEMENS)
  {
    MENU_SiementsReturnPageSave(CurrentPage);
  }
  //ͨ���쳣����ҳ�����
  switch(CurrentPage->ContentStrIndex)
  {
    case STR_INDEX_2://Device Setup
    case STR_INDEX_4://Diag/Service
    case STR_INDEX_9://Calibration
    case STR_INDEX_5://Basio setup
    case STR_INDEX_6://Detailed setup
    case STR_INDEX_7://Test device
    case STR_INDEX_995://Review
    case STR_INDEX_105://Enter~meter~value ��EditPage��  
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
    case STR_INDEX_1116: //�˵���--Process Alerts
    MENU_CurrentPageTempSave();
    break;
  default:break;
  }  
}
/*
void MENU_CursorSaveHand(bool8 flag)

* ������Χ:
flag:TRUE,FALSE;


* ����ֵ˵��:void
* ���ܽ���:   
��걣�洦������
*
* �ؼ���ע��
* - 

  
* δ�����:




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

* ������Χ:
CursorMaxVal:����˵��������ֵ


* ����ֵ˵��:void
* ���ܽ���:   
�쳣��괦������
*
* �ؼ���ע��
* - 

  
* δ�����:




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

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
���ص�δ���ӽ���ʱ����Ҫ��һЩ�������д������������Ǹ�ԭ
���������Ƶġ�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_VeriableReset()
{
  G_PollingAddress[0] = 0;
}
/*
void MENU_SpecificOperation(AdditionalInfoDef Operation)

* ������Χ:
AdditionalInfoDef Operation:ҳ�渽����Ϣ����


* ����ֵ˵��:void
* ���ܽ���:   
  �˵����⴦����������ִ�в˵�ҳ���б���ִ�е��ض����㣬
  ���ݲ˵��ṹ�ĸ��ӹ������ȡ�ض������㣬ʹ��������٣�
  �����ڶ��Ʋ�Ʒ��Ŀǰ��������Ǳ�ľ���ϵ��У׼��
���������Ƶġ�
*
* �ؼ���ע��
* - 

  
* δ�����:




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

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
����������Ӻ��������ض�������Ҫ��Ӹ�������ʱ����ͨ�������������������
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
  ����˵��л�ˢ��������ȡ��������õĲ˵���ʾ��ʼ���յ���Ϊʵ�ʲ�������
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
HandleFlagDef MENU_VerticalItemSwitchParamGet(uchar *StartItem,uchar *EndItem,
                                 uchar ShowLineNum,uchar ItemNumber)
{
  uchar CurrentPageNum = 0;
  //����һ�¹���ڲ˵��еĵڼ�ҳ��
  CurrentPageNum = G_CursorNumV/ShowLineNum;
  //���㱾ҳ��ʼ�в˵����к�
  StartItem[0] =  CurrentPageNum*ShowLineNum;
  //���㱾ҳĩβ�˵����к�
  EndItem[0] = StartItem[0] + ShowLineNum;
  //���ĩβ�˵����кűȲ˵��������Ҫ��˵���Ѿ����˲˵������һҳ����ô���Բ˵������Ϊ׼
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
* ������Χ:
  ShowLineNum����ǰҳ����ʾ���������


* ����ֵ˵��:void
* ���ܽ���:   
*       ����ˢ�´�������
    �˵�ҳ������ѡ����������ﵽ��ҳ��׼ʱ������ˢ�����´���
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_VerticalItemRefreshHandle(uchar ShowLineNum,PageDef *PagePtr)
{
  //�����߼��뱾�ز���������ˣ�������ÿ��һ��ѡ�����Ҫ����ˢ��һ��ҳ�档
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
* ������Χ:
  Language����Ҫ�趨�����ԡ�


* ����ֵ˵��:void
* ���ܽ���:   
*       ����ҳ���������ú������޸ı���ҳ����Ϣ�е����ԡ�
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_TempLanguageSetHandle(LanguageTypeDef Language)
{
  G_CurrentPageTemp.Language = Language;
}
/*
void MENU_TempPageNumSetHandle(uint CurrentPageNum)
* ������Χ:
CurrentPageNum:Ҫ�趨��ҳ����


* ����ֵ˵��:void
* ���ܽ���:   
*       ����ҳ�������ú�����������ҳ���Ž����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:
PageType:Ҫ�趨��ҳ������


* ����ֵ˵��:void
* ���ܽ���:   
*       ����ҳ���������ú�����������ҳ�����ͽ����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:
PageType:Ҫ�趨�Ĳ˵����������


* ����ֵ˵��:void
* ���ܽ���:   
*       ����ҳ��˵�������������ú�����������ҳ��˵���������Ž����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:
  Language����Ҫ�趨�����ԡ�


* ����ֵ˵��:void
* ���ܽ���:   
*       �������ú���������ǰҳ����ʾ���Խ����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:




*/
void MENU_LanguageSetHandle(LanguageTypeDef Language)
{
  G_CurrentPage.Language = Language;
}
/*
void MENU_PageNumSetHandle(uint CurrentPageNum)
* ������Χ:
CurrentPageNum:Ҫ�趨��ҳ����


* ����ֵ˵��:void
* ���ܽ���:   
*       ҳ�������ú���������ǰҳ���Ž����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:
PageType:Ҫ�趨��ҳ������


* ����ֵ˵��:void
* ���ܽ���:   
*       ҳ���������ú���������ǰҳ�����ͽ����޸ġ�
  �������ͨ������Ҫ��ʱ��ʾ����ʾʱ����ҳ����Ϣ���еĸ��Ӳ������þ���
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:
PageType:Ҫ�趨�Ĳ˵����������


* ����ֵ˵��:void
* ���ܽ���:   
*       �˵�������������ú���������ǰҳ��˵���������Ž����޸ġ�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void
* ���ܽ���:   
*       ��ǰҳ�滹ԭ���������־����֪ͨ�������Ҫ����ǰҳ��ָ�����ʷ�˵��С�
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void
* ���ܽ���:   
*       ��ǰҳ�汣�溯����Ԥ��ҳ����ת���ң����ͽ��Լ��˵��б��浽ҳ����Ϣ��������
* �ؼ���ע��
* - 

  
* δ�����:

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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamVariableInfoGet(uint*const VariableIndex,DataTypeDef*const DataType,
        DataLengthDef*const DataLength,MenuTreeIndexDef MenuTreeIndex,uchar* ShowData);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ�������Ϣ��ȡ������ͨ�����������Ի�ȡ������������ţ�
  �������ͣ����ݳ��ȵ���Ϣ��

*
* �ؼ���ע��
* - 

  
* δ�����:



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
  //�����ǰҳ��û�й��ڱ������飬����Ҫ������ʾ�������ء�
  if(PagePtr->VariableIndex != 0x00)
  {
    //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
    *VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
    //��ȡHART���������ݳ���
    *DataLength = MENU_GetHartVariableDataLength(*VariableIndex);
    //��ȡHART��������������
    *DataType = MENU_GetHartVariableDataType(*VariableIndex);
    *ReceiveDataLength = MENU_GetHartVariableAnalysisLength(*VariableIndex); 
    //��ȡHART��������ָ��
    ShowData = MENU_GetHartVariablePtrIndex(*VariableIndex); 
    
    MENU_ShowVariableProtection(ShowData,*ReceiveDataLength);
  }
  return ShowData;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_ShowVariableProtection(uchar *ShowData,DataLengthDef DataLength);
* ������Χ:
uchar *ShowData������HART����ָ��
DataLengthDef DataLength�� 
* ���ܽ���:   
HART��ʾ����������������ʱͨ�Ż�����쳣����ӻ���Ӧ�쳣�����Ǳ��ز��������Ա��쳣
�������ģ���ˣ���Ҫ���б�����ʾ��������������
* ����ֵ˵��:void 
*
* �ؼ���ע��
* - 

  
* δ�����:
*/
void MENU_ShowVariableProtection(uchar *ShowData,DataLengthDef DataLength)
{
  //����������ڷǱ���״̬�����Ҳ��ǵ��μ������
  //��Ϊ��Щҳ����Ҫˢ����ʾ��ǰҳ���ȡ�ı�����
  if((G_VariableProtect.LoadLock == FALSE)
              &&(G_SingleCommandLoad == FALSE))
  {
   HART_VariableProtect(ShowData,DataLength);
   G_VariableProtect.LoadLock = TRUE;
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_ExplainInfoDisplayHandle(LanguageTypeDef Language,uchar *ShowLineIndex,PageDef *const PagePtr);
      * ������Χ:

* ���ܽ���:   
�˵�˵����Ϣ��ʾ����������Ҫ������ʾ�����Լ�ҳ��˵���������Դ���
* ����ֵ˵��:void 
*
* �ؼ���ע��
* - 

  
* δ�����:
*/
uchar MENU_ExplainInfoDisplayHandle(LanguageTypeDef Language,uchar ShowLineIndex,PageDef *const PagePtr)
{
  //������ʾ�ռ�ԭ�����Ĳ˵��Ĳ���ѡ�����ʡ�Ա����У�ֱ����ʾ����˵��
  if(Language == ENGLISH)
  {
    //��ȡ�����ֺ�
    FlashStringReadLockHandle(ShowLineIndex,PagePtr->TitleLineStringNum,Language);
    //�˵�ҳ���϶˵�����˵������
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
//�������ƺͲ����ͷ���ֵ���͡�
uchar MENU_AsciiLengthGet(uchar const *const FloatStrTemp,DataLengthDef LimitLength);
* ������Χ:

* ���ܽ���:   
ASCII��ʾ���������ݵĳ��Ȼ�ȡ,ͨ������ʶ�ֽ���Ϊ�����ж����ݣ�Ȼ�󷵻س��ȡ�
* ����ֵ˵��:void 
*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void MENU_HandleFlagDisplay(bool8 IsExecutingState)
* ������Χ:
HandleState:
* ���ܽ���:   
  ��ҳ��ʾ��������ʾ�������в˵�������ѵ������ѡ�
*
* ����ֵ˵��:void 
* �ؼ���ע��
* - 

  
* δ�����:
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
      TempCH[0] = 0xd4;//ʣ��ѡ����ʾ���
      MENU_DynamicStringShow(GB_12X16,(uchar*)TempCH,StartX,StartY,CursorShowMode,Language);
    }
    else if(Language == ENGLISH)
    {
      TempEN[0] = 96+0X20;//ʣ��ѡ����ʾ���
      MENU_DynamicStringShow(ASCII_6X8,(uchar*)TempEN,StartX,StartY,CursorShowMode,Language);
    }
  break;
  case EndingOption:
    if(Language == CHINESE)
    {
      TempCH[0] = 0xd5;//����ҳ��ʾ���
      MENU_DynamicStringShow(GB_12X16,(uchar*)TempCH,StartX,StartY,CursorShowMode,CHINESE);
    }
    else if(Language == ENGLISH)
    {
      TempEN[0] = 97+0X20;//ʣ��ѡ����ʾ���
      MENU_DynamicStringShow(ASCII_6X8,(uchar*)TempEN,StartX,StartY,CursorShowMode,Language);
    }
  break;
  case InputCursor:break;
  default:break;
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static void MENU_ItemVDisplay(FontDef IndexFront,const PageDef* const PagePtr,
           uchar j,uchar StructIndex,LanguageTypeDef Language,uchar LineOffset,
                                CursorShowModeDef CursorShowMode,uchar ItemHigh);
* ������Χ:
HandleState:
* ���ܽ���:   
  �˵�������ʾ������
*
* ����ֵ˵��:void 
* �ؼ���ע��
* - 

  
* δ�����:
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
  //�˵�������ʾ
  MENU_DynamicStringShow(IndexFront,LineNum,
   0,StartY,CursorShowMode,ENGLISH); 
  CurrentItemV = MENU_GetVarticalItem(PagePtr,j); 
  //�˵����ַ���ʾ
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
