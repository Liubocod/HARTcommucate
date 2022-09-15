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
//����ִ����
bool8 G_SingleExcutionLock = FALSE;

/*
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamCY_TTSPatch1(const HART_UnitDef* UnitTable);
* ������Χ:
UnitTable:��λ��ָ�롣

* ����ֵ˵��:void 
* ���ܽ���:   
  ����TTS����1����������ҳ����������л���λ��

*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
static uchar* ParamCY_HVPPatch1(uchar* FunCodeTemp,uchar* ShowData,uint ContentStrIndex)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����HVP����1������
  ҳ����ر�����Ҫ����λ������вü�����������ʾ

*
* �ؼ���ע��
* - 

  
* δ�����:



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
    //����RISE �� LIN�Ĺ�����ֵ��ͬ��Ϊ��������ʾ�����ｫ����������Զ���
    if(*FunCodeTemp == 0)
    {
      *FunCodeTemp = 3;
    }
    break;
  case STR_INDEX_1075:
    *FunCodeTemp = (*FunCodeTemp)&0x04;
    //�ַ���1074��ͬ
    (*FunCodeTemp) = (*FunCodeTemp)>>1;
    //����RISE �� LIN�Ĺ�����ֵ��ͬ��Ϊ��������ʾ�����ｫ����������Զ���
    if(*FunCodeTemp == 0)
    {
      *FunCodeTemp = 3;
    }
    break;
  default:break;
  }
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	ParamSetPageHandle(KeyValueDef KeyMode);
* ������Χ:
KeyValueDef KeyMode:�������࣬��������һ��������

* ����ֵ˵��:void 
* ���ܽ���:   
  �����趨ҳ���л�������

*
* �ؼ���ע��
* - 
�����л�������ҳ��Ĵ�����
  
* δ�����:
��Ҫ������ʾ�ļ��С�


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
  //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
  CurrentItemV = MENU_GetVarticalItem(PagePtr,G_CursorNumV);
  if(PagePtr->VariableIndex != VARIABLE_ARR_0)
  {
    //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
    VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
    //��ȡHART��������ָ��
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
    //��ȡHART��������������
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
            //У׼������;�����˳�����ģʽ��ʱ�򣬲���Ҫ��ԭ�������ֳ�����Ϊ��Ҫ����0����ֵ
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
 //�������ƺͲ����ͷ���ֵ���͡�
void ParamSetPageShow(uint MenuTreeIndex);
* ������Χ:
MenuTreeIndex���˵�����ţ�����ͨ���������ҵ��˵���Ӧ����Ϣ��

* ����ֵ˵��:void 
* ���ܽ���:   
  �����趨ҳ����ʾ������

*
* �ؼ���ע��
* - 

  
* δ�����:



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
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  //�쳣��������ֳ���������
  MENU_ReturnPageSave(PagePtr);

  ShowLineNum = PagePtr->SinglePageItemNumberV; 
  ItemNumber = PagePtr->ItemNumberV;
  MENU_CursorOverrunHandle(ItemNumber-1);
  //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
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


  //������ʾ������ȡ����ȡ��ǰҳ�����ʼ��ż��������
  HandleFlag = MENU_VerticalItemSwitchParamGet(&StartItem,
                &EndItem,ShowLineNum,ItemNumber);
  //����˵�����ʾ����
  ShowLineIndex = MENU_VerticalItemShow(StartItem,EndItem,ShowLineIndex,LanguageTemp,PagePtr,LineOffset);
  if(MENU_LanguageTypeGet() == CHINESE)
  {
    ShowLineIndex = 6;
  }
  else
  {
    ShowLineIndex = 7;
  }
  //����˵�����ʾ
  MENU_HorizontalItemShow(PagePtr,ShowLineIndex,MENU_LanguageTypeGet());
  
  ParamHandleFlagDisplay(HandleFlag,LanguageTemp);
  FlashReadLockHandle(TRUE);
}
/*
void ParamSetPageSingleExcutionLockHandle(bool8 IsSingleExcution);
* ������Χ:
  IsSingleExcution:����ִ������ͨ���ò�������ִ����

* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ�����ר�еĵ���ִ�������������ٶ��ν���˵���

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void ParamSetPageSingleExcutionLockHandle(bool8 IsSingleExcution)
{
  G_SingleExcutionLock = IsSingleExcution;
}
  
/*
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamHandleFlagDisplay(HandleFlagDef HandleFlag,LanguageTypeDef Language);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  �������洦������ʾ������������ʱ����ѡ����������ѡ������޷���һҳ��
  ��ʾȫ��ѡ������Ҫ��ҳ��ʾ��ǡ�

*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamChineseShowLineHandle(PageDef* const PagePtr,uchar *const ShowLineNum);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ��������ʾ�б괦��������������������ʾʱ�����Բ���ʾ���㡣

*
* �ؼ���ע��
* - 

  
* δ�����:



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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamShowLineCalculation(uchar ShowLineIndex,
       PageDef* const PagePtr,LanguageTypeDef Language,uchar* const LineOffset,uchar *const ShowLineNum);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ����ʾ�б괦����������������ʾʱ�����Բ���ʾ���㡣

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
static void ParamShowLineCalculation(PageDef* const PagePtr,uchar *const ShowLineNum,LanguageTypeDef Language)
{
  if(Language == CHINESE)
  {
    ParamChineseShowLineHandle(PagePtr,ShowLineNum);
  }
  else if((MENU_LanguageTypeGet() == CHINESE)&&(Language == ENGLISH))
  {
    //���ֽ����е�Ӣ������ʾ���Ը�������
    *ShowLineNum = 3;
  }
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamVariableDisplay(PageDef* const PagePtr,DataType,
              uint *VariableIndex,uchar* ShowData,LanguageTypeDef Language,uchar* ShowLineIndex,DataLengthDef* DataLength);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ�������ʾ,�е�ҳ����Ҫ��ʾ�������еĲ���Ҫ��ʾ��
  �е���ʾ���֣��е���ʾ���֣��еĴ���λ���еĲ�����λ��

*
* �ؼ���ע��
* - 

  
* δ�����:



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
    //�ò�����Ҫ��Լ�����ֵ���������е�λ�����Ĳ���ѡ����档
    if(PagePtr->AdditionalInfo == NUM_VARIABLE_BOTH)
    {
      ParamVariableNumberDisplay(Language,FloatStrTemp,Length,PagePtr,ShowLineIndex,DataLength);
      //��ʾ�������������ʾ������
      if(VariableNumber == 0x02)
      {
        ParamVariableUnitDisplay(Language,FloatStrTemp,PagePtr,ShowLineIndex);
      }
    }
    else 
    {
      if(PagePtr->AdditionalInfo == VARIABLE_WITHOUT_NUM)//��Թ������������ʾ
      {
        ParamFunctionCodeDisplay(PagePtr,ShowLineIndex,DataType,FloatStrTemp,DataLength,Language);
      }
      else if(PagePtr->AdditionalInfo == NUM_WITHOUT_VARIABLE)//��Թ�������������ʽ��ʾ��ҳ��
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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamVariableNumberDisplay(MenuTreeIndexDef MenuTreeIndex,
              LanguageTypeDef Language,uchar *const FloatStrTemp,uchar Length,
              PageDef* const PagePtr,uchar* ShowLineIndex);

* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ�����ֱ�����ʾ����,������ʾ���ֱ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
static void ParamVariableNumberDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,uchar Length,
              PageDef* const PagePtr,uchar* ShowLineIndex,DataLengthDef DataLength)
{
  uchar StartX,StartY;
  FontMatrixDef FontMatrix;
  if(Language == ENGLISH)
  {
    //��ȡ������Ϣ
    MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[Language]);
    //ȷ����ʾ��������
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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamVariableUnitDisplay(LanguageTypeDef Language,uchar *const FloatStrTemp,
                                      PageDef* const PagePtr,uchar* ShowLineIndex);

* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ�����ֱ�����ʾ����,������ʾ���ֱ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



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
  //��ȡHART��������ָ��
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    //��ȡHART������������ձ�����ָ��
    UnitTable = MENU_GetHartUnitTable(VariableIndex); 
    if(UnitTable != NULL)
    {
      //��ָֹ�붪ʧ�����»�ȡһ��������Ϣ
      MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[ENGLISH]);
      IntegerLength = MENU_AsciiLengthGet(FloatStrTemp,ASCII_9,0x20);
      if(Language == ENGLISH)
      {
        //ȷ����ʾ��������
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
 //�������ƺͲ����ͷ���ֵ���͡�
static void ParamFunctionCodeDisplay(PageDef* const PagePtr,uchar* ShowLineIndex);

* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ�湦���������ʾ����,������ʾ���������ֱ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
static void ParamFunctionCodeDisplay(PageDef* const PagePtr,uchar* ShowLineIndex,DataTypeDef DataType,
            uchar *FloatStrTemp,DataLengthDef DataLength,LanguageTypeDef Language)
{
  const HART_UnitDef* UnitTable = NULL;
  uchar FunCodeTemp = 0;
  uint VariableIndex = 0;
  uchar* ShowData;
  //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
  VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
  //��ȡHART��������ָ��
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    //��ȡHART������������ձ�����ָ��
    UnitTable = MENU_GetHartUnitTable(VariableIndex);
    //����TTS������Snsr type��ʾ����
    if(PagePtr->ContentStrIndex == STR_INDEX_916)
    {
      UnitTable = ParamCY_TTSPatch1();
    }
    //����HVP������YFCT SDIR YDIR
    if((PagePtr->ContentStrIndex == STR_INDEX_1073)
        ||(PagePtr->ContentStrIndex == STR_INDEX_1074)
          ||(PagePtr->ContentStrIndex == STR_INDEX_1075))
    {
        ParamCY_HVPPatch1(&FunCodeTemp,*ShowData,PagePtr->ContentStrIndex);
        //������ʾ���ı�ָ��ָ��
        ShowData = &FunCodeTemp;
    }
    //����ѡ�����ı���׷�ٹ��ܡ�
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
    //������ǹ��������������ʾ��ֵ
    *ShowLineIndex = MENU_VariableShow(DataLength,FloatStrTemp,*ShowLineIndex,PagePtr,0,NORMAL);
  }
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
static uint ParamVariableTrace(const HART_UnitDef* UnitTable,uchar* ShowData,
      PageDef* const PagePtr,MenuTreeIndexDef MenuTreeIndex,uchar* ShowLineIndex);

* ����ֵ˵��:void 
* ���ܽ���:   
  ����ѡ��ҳ����׷�ٺ���,����������ǰ������ѡ���б��е�λ�ã�
  �ù������ʾʱֱ����ת����������λ�á�

*
* �ؼ���ע��
* - 

  
* δ�����:



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
