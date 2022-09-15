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

#include "InfoPage.h"


static uchar PageUnitShow(const PageDef* CurrentPage,uchar ShowLineIndex);
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	InfoPageHandle(KeyValueDef KeyMode);
* ������Χ:
KeyValueDef KeyMode������ֵ

* ����ֵ˵��:void 
* ���ܽ���:   
  ״̬��Ϣҳ���л�������

*
* �ؼ���ע��
* - 
�����л�������ҳ��Ĵ�����
  
* δ�����:
��Ҫ������ʾ�ļ��С�


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
 //�������ƺͲ����ͷ���ֵ���͡�
void PageUnitShow();
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ҳ�浥λ��ʾ������

*
* �ؼ���ע��
* - 


  
* δ�����:

     ע�⣺

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
  //��λ�ֽڸ���
  StrStruct[0] = MENU_GetStrStruct(StrNum);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  UnitLength = StrStruct->RealCharacterNumber[0];
  MENU_StaticStringShow(StrStruct,(21-UnitLength)*6,
    START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  return UnitLength;
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void InfoPageShow();
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  ״̬��Ϣ��ʾ������

*
* �ؼ���ע��
* - 


  
* δ�����:

     ע�⣺
���ڱ������������̻������������ͬ��ID�������豸�ͺ�ID���ܳ�����ͬ��
Ŀǰ�Ľ�������ǣ���������豸����code�ٱ��뺯�����Ե�ǰ��ʾ���豸���ͽ�����Ϊ����
��֧�����������ظ���������ID���Ͷ�Ӧ���豸����code���ر�ָ��StrNum.
���磺
if((G_ManufacturerID == LM_MANUFACTURER_ID)&&(G_DeviceType == 0x06))//��Ϊ�������������豸����Ϊ0x06���豸���ͺ�
{
  return STR_INDEX_885;
}
Ȼ���ñ���StrNum�������������ķ���ֵ������if(DataType == FUNC_CODE_T){}��
     MENU_StaticStringShow(StrStruct+StrNum,CurrentPage->StartX,
            START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),NORMAL);
�Ĳ�����

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
  //��ȡ�˵������
  MENU_PageShowSwitch(FALSE);

  PagePtr = MENU_GetCurrentMenuPage();
  //ҳ����������غ���
  MENU_PageCommandGroupLoad(PagePtr);
  ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);

  //�����ǰҳ��û�й��ڱ������飬����Ҫ������ʾ�������ء�
  if(PagePtr->VariableIndex != 0x00)
  {
    VariableNumber = MENU_PageVariableNumber(G_PageVariableTable);
    //��д��λ
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
      //����TTS������Snsr type��ʾ����
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
      //�����Tag�༭���棬��Ҫ����ASCII����
      j = HART_ASCII_Decode(Tagline,ReceiveDataLength,DataLength,ShowData);
      if(j != 0)
      {
         ShowLineIndex = MENU_VariableShow(DataLength,Tagline,ShowLineIndex,PagePtr,0,NORMAL);
      }
    }
    else if(DataType == L_ASCII_T)
    {
      //ͨ��8λASCII�봦��
      ShowLineIndex = MENU_VariableShow(DataLength,ShowData,ShowLineIndex,PagePtr,0,NORMAL);
    }
    else
    {
      ShowLength = HART_TypeConvert(ShowData,Temp,DataType,DataLength,ASCII_T);
      //�����ʾ��λ����Ҫ��������ʾ�����������һ���ֽڸ�ֵΪ/0������Ḳ�ǵ�λ
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
  //����˵�����ʾ
  MENU_HorizontalItemShow(PagePtr,6,MENU_LanguageTypeGet());
}

