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
#include "EditPage.h"
//�������������о���������
#define IS_SPECIAL_DATA_TYPE_HANDLE (DataType == CURVE_START_T)||(DataType == FLOAT_T)\
  ||(DataType == FLOAT1_T)||(DataType == CURVE_END_T)||(DataType == FAKE_RANGE_T)||(DataType == FAKE_AMP_T)\
                        ||(DataType == PVL_T)||(DataType == PVU_T)||(DataType == MAX_ZOON_T)||(DataType == MIN_ZOON_T)\
                                ||(DataType == LEVEL_SPD_T)||(DataType == SUPRITY_T)||(DataType == MIN_RESOL_T)
//����������ֵ�о���������
#define IS_FIXED_CURRENT_HANDLE (PagePtr->ContentStrIndex == STR_INDEX_105)||(PagePtr->ContentStrIndex == STR_INDEX_99)\
                                  ||(PagePtr->ContentStrIndex == STR_INDEX_902)

#define IS_EDIT_PAGE_INPUT_SPECIAL_DISPLAY      ((PagePtr->ContentStrIndex == STR_INDEX_324)||(PagePtr->ContentStrIndex == STR_INDEX_325)\
                ||(PagePtr->ContentStrIndex == STR_INDEX_364)||(PagePtr->ContentStrIndex == STR_INDEX_365)\
                    ||(PagePtr->ContentStrIndex == STR_INDEX_105))&&(G_EditPageInputSpecialShowFlag == TRUE)
#define IS_CY_PDS6_PATCH_1 (PagePtr->ContentStrIndex == STR_INDEX_590)\
                ||(PagePtr->ContentStrIndex == STR_INDEX_370)
#define IS_SPECIAL_RANGE (DataType == CURVE_START_T)||(DataType == CURVE_END_T)||(DataType == FAKE_RANGE_T)\
          ||(DataType == FAKE_AMP_T)||(DataType == PVL_T)||(DataType == PVU_T)||(DataType == HANDRED_T)||(DataType == BYTE_VALUE_T)\
                   ||(DataType == MAX_ZOON_T)||(DataType == MIN_ZOON_T)||(DataType == LEVEL_SPD_T)||(DataType == SUPRITY_T)||(DataType == MIN_RESOL_T)||(DataType == INT_VALUE_T)

static uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue);
static uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue);
static uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue);
static DataTypeDef EditVariableRangeConfirm(uchar *ShowData,
                              DataTypeDef DataType,const PageDef *CurrentPage);
static void EditInvalidInputReset(void);
static uchar EditDateDisplay(DataLengthDef DataLength,uchar ShowLineTemp);
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,uchar *ShowData,uchar ShowLineIndex);
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,uchar ShowLineIndex,uchar *ShowData,DataLengthDef ReceiveDataLength,uchar *UnitStartPosition);
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
        DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                        uchar ShowLineIndex,uchar *UnitStartPosition);
static uchar EditIntDataHandle(uchar *ShowData,
        DataTypeDef DataType,DataLengthDef DataLength,
          uchar ShowLineIndex,uchar *UnitStartPosition);
static void EditFunctionCodeHandle(uint VariableIndex,DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex);
static void EditUnitDisplay(uint VariableIndex,uchar ShowLineIndex,const PageDef *const PagePtr,uchar UnitStartPosition);

//��20���ֽ�ԭ��Ϊ0x00
uchar G_ShowData[ASCII_42] = 
{
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
};

uchar G_VariableArrIndex = 0;
//�༭��������������ʾ״̬��־��
bool8 G_EditPageInputSpecialShowFlag = TRUE;
/*


typedef struct 
{
  KeyValueDef KeyValue;
  uchar UpValue;
  uchar LeftValue;
  uchar RightValue;
  uchar NumberValue;
}KeyCharDef;


*/ 


const KeyCharDef KeyCharArr[] = 
{
  MINUS,0x3b,0x2a,0x2b,0x2d,
  POINT,0x20,0x3c,0x3e,0x2e,
  ZERO,0x25,0x23,0x26,0x30,
  THREE,0x5a,0x59,0x2f,0x33,
  TWO,0x57,0x56,0x58,0x32,
  ONE,0x54,0x53,0x55,0x31,
  SIX,0x51,0x50,0x52,0x36,
  FIVE,0x4e,0x4d,0x4f,0x35,
  FOUR,0x4b,0x4a,0x4c,0x34,
  NINE,0x48,0x47,0x49,0x39,
  EIGHT,0x45,0x44,0x46,0x38,
  SEVEN,0x42,0x41,0x43,0x37,
};
/*
//�������ƺͲ����ͷ���ֵ���͡�
KeyValueDef  EditPageCharPositionSelect(AdditionalInfoDef AdditionFlog,KeyValueDef Position)
* ������Χ:
AdditionFlog:ҳ��ĸ�����Ϣ����һЩ����������˵����
Position���ַ�λ��ѡ���־������ѡ�����ְ����Ϲ��ص��ַ���

* ����ֵ˵��:KeyValueDef �������ּ������ַ���λ�ã����ϣ��һ��ް������� 
* ���ܽ���:   
�༭ҳ���ַ�λ��ѡ������������������ѡ�����ּ����ص��ַ����ڵ�λ�á�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 

KeyValueDef  EditPageCharPositionSelect(AdditionalInfoDef AdditionFlog,KeyValueDef Position)
{
    if(AdditionFlog == CHAR_NUMBER_SHOW)
    {
      return Position;
    }
    return NO_KEY_STATUS;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue);
* ������Χ:
KeyValue���������밴��ֵ����Χ0-9�����ź�С���㡣


* ����ֵ˵��:uchar ���ذ���ֵ�ַ������Ӧ��������ţ�����ͨ�������Ż���ַ���
ASCII��ֵ��
* ���ܽ���:   
�༭�����ַ���ֵ��Ż�ȡ�����������������Ǹ��ݴ����İ���ֵ�����������Ӧ
�ļ�ֵ�ַ�������ţ�������ҵ����ּ����ص��ַ�ASCII��ֵ��

*
* �ؼ���ע��
* - 

* δ�����:

*/ 

uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue)
{
  switch(KeyValue)
  {
    case MINUS:
      return 0;
      break;
    case POINT:
      return 1;
      break;
    case ZERO:
      return 2;
      break;
    case THREE:
      return 3;
      break;
    case TWO:
      return 4;
      break;
    case ONE:
      return 5;
      break;
    case SIX:
      return 6;
      break;
    case FIVE:
      return 7;
      break;
    case FOUR:
      return 8;
      break;
    case NINE:
      return 9;
      break;
    case EIGHT:
      return 10;
      break;
    case SEVEN:
      return 11;
      break;
  default:break;
  }
  //���ش�����
  return 0xff;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
* ������Χ:
CharPositionSelectFlag:�ַ�λ��ѡ���־������ѡ�����ְ����Ϲ��ص��ַ���
KeyValue:�����µ����ְ���������ͨ���ñ���ȷ������һ�����ְ�������������Χ��0-9��ֵ�Լ����ţ���С���㡣

* ����ֵ˵��:uchar ��ȡ�����ڱ༭ҳ����ַ�ֵ�� 
* ���ܽ���:   
�༭ҳ���ַ�ֵ��ȡ�������жϵ�ǰҳ�����뵽�����е�ֵ���ַ���ֵ��ʱ��ͨ����
������ȡȷ�����ַ�ֵ��

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 

uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
{
  uchar KeyCharIndex = 0;
  
  KeyCharIndex = EditPageKeyCharIndexGet(KeyValue);
  
  switch(CharPositionSelectFlag)
  {
    case UP_SELECT:
      return KeyCharArr[KeyCharIndex].UpValue;
      break;
    case RIGHT_UP_SELECT:
      return KeyCharArr[KeyCharIndex].RightValue;
      break;
    case LEFT_UP_SELECT:
      return KeyCharArr[KeyCharIndex].LeftValue;
      break;
    case NO_KEY_STATUS:
      return KeyCharArr[KeyCharIndex].NumberValue;
    default :
      break;
  }
  //���ش�����
  return 0xff;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
* ������Χ:
AdditionFlog:ҳ��ĸ�����Ϣ����һЩ����������˵����
CharPositionSelectFlag:�ַ�λ��ѡ���־������ѡ�����ְ����Ϲ��ص��ַ���
KeyValue:�����µ����ְ���������ͨ���ñ���ȷ������һ�����ְ�������������Χ��0-9��ֵ�Լ����ţ���С���㡣

* ����ֵ˵��:uchar�����ص�����Ҫ�����༭����󶨱���������ֵ��
* ���ܽ���:   
�༭ҳ����ر���ֵ��ȡ�������������Ĺ����Ǹ���ҳ�渽����Ϣ���ַ�λ�ñ������Լ�
�����İ����������Ҫ������ҳ����ر�����Ӧλ���е�����ֵ��

*
* �ؼ���ע��
* - 

  
* δ�����:
����������ݸ�ʽ����ơ�
*/ 

uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
{
  return EditPageCharValueGet(CharPositionSelectFlag,KeyValue);
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditPageHandle(KeyValueDef KeyMode);
* ������Χ:
KeyValueDef KeyMode:�������࣬��������һ��������
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* ����ֵ˵��:void 
* ���ܽ���:   
  ˵��ҳ�洦��������ǰ��ʾҳ��Ϊ˵��ҳ��ʱ�������������������ʱ
  ͨ��������ȷ����һ����ʾҳ�棬��ִ��ʲô���Ĳ�����

*
* �ؼ���ע��
* - 
��Щ˵�������ִ��һЩ������������Թ��ܼ����һЩ���ܺ���ָ�룬
ִ��ʲô��������ʲô������
  
* δ�����:
������ȫ��Ҫ���а�������
*/ 

void CharPositionSeletFlagReset(KeyValueDef *CharPositionSelectFlag)
{
  *CharPositionSelectFlag = NO_KEY_STATUS;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditPageDataInput(uchar G_VariableArrIndex,AdditionalInfoDef AdditionFlog,
                       KeyValueDef CharPositionSelectFlag,KeyValueDef ONE,DataLengthDef ShowDataLength)
* ������Χ:
  uchar VariableArrIndex:��ʾ�����������š�
  AdditionalInfoDef AdditionFlog:ҳ��ĸ�����Ϣ����һЩ����������˵����
  KeyValueDef CharPositionSelectFlag:�ַ�λ��ѡ���־������ѡ�����ְ����Ϲ��ص��ַ���
  KeyValueDef ONE:�����µ����ְ���������ͨ���ñ���ȷ������һ�����ְ�������������Χ��0-9��ֵ�Լ����ţ���С���㡣
  DataLengthDef ShowDataLength:��ʾ�ַ����ĳ���


* ����ֵ˵��:void 
* ���ܽ���:
������������ַ����浽�༭ҳ����ʾ��ʱ�������鵱�С�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void EditPageDataInput(uchar VariableArrIndex,AdditionalInfoDef AdditionFlog,
                       KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue,DataLengthDef ShowDataLength)
{
  if((AdditionFlog == SPECIAL_NUMBER_SHOW)
     &&((KeyValue == POINT)||(KeyValue == MINUS)))
  {
    
  }
  else
  {
     G_ShowData[VariableArrIndex] = EditPageVariableValueGet(AdditionFlog,CharPositionSelectFlag,KeyValue);
     G_VariableArrIndex++;
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar GetPoint(uchar *ShowData,uchar Length)
* ������Χ:
uchar *ShowData��ʾ��������ָ�롣
uchar Length����ʾ�������鳤�ȡ�

* ����ֵ˵��:uchar��С�������ڵ�λ�á� 
* ���ܽ���:   
����ʾ�����������ҵ�С�����λ�ã���ͨ������ֵ�����λ�÷��ء�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
uchar GetPoint(uchar *ShowData,uchar Length)
{
  uchar i;
  for(i = 0;i < Length;i++)
  {
    if(ShowData[i] == 0x2e)
      break;
  }
  return i;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditPageVariableLoad(uchar *ShowData,DataLengthDef ShowDataLength,
DataTypeDef DataType,DataLengthDef ReceiveDataLength)

* ������Χ:
uchar *ShowData��ʾ��������ָ�롣
uchar Length����ʾ�������鳤�ȡ�

* ����ֵ˵��:
* ���ܽ���:   
�༭ҳ����ر������غ�����
���༭ҳ���е���ʱ������ʾ������Ϣͨ����������ת�������浽ҳ����ر����С�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void EditPageVariableLoad(uchar *ShowData,DataLengthDef ShowDataLength,
                          DataTypeDef DataType,DataLengthDef ReceiveDataLength)
{
  uchar i;
  float FloatData = 0.0;
  long uint LongIntData = 0;
  uint IntData = 0;
  
  if(G_VariableArrIndex > ShowDataLength)
  {
    //error
  }
  else if(G_VariableArrIndex != 0)
  {
    if((DataType == FLOAT_T)||(DataType == FLOAT1_T))
    {      
      FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
      HART_FloatToData(FloatData,ShowData,FLOAT_T);
    }
    else if(DataType == LONG_UINT_T)
    {
      LongIntData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
      if(ReceiveDataLength == THREE_BYTES)
      {
        if(LongIntData <= 16777215)
        {
          HART_LongIntToData(LongIntData,ShowData,DataType );
        }
        else
        {
          //
        }
      }
    }
    else if(DataType == L_ASCII_1_T)
    {//����ASCII��ʾ����������ո���Ҫ���ո��޸�Ϊ00�룬ֻ�ڸ����Ʒ������ʹ�á�
      for(i = 0; i < ShowDataLength;i++)
      {
        if(G_ShowData[i] != 0x20)
        {
          *(ShowData+i) = G_ShowData[i];
        }
        else
          *(ShowData+i) = 0;
      }
    }
    else if(DataType == L_ASCII_T)
    {//ͨ��8λASCII�봦��
      for(i = 0; i < ShowDataLength;i++)
      {
        *(ShowData+i) = G_ShowData[i];
      }
    }
    else if((DataType == UCHAR_T)||(DataType == FUNC_CODE_T))
    {
      *ShowData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
    }
    else if(DataType == UINT_T)
    {      
      IntData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
      HART_IntToData(IntData,ShowData,DataType);
    }
    else//test,��ʱʹ��
    {
      for(i = 0; i < ShowDataLength;i++)
      {
        *(ShowData+i) = G_ShowData[i];
      }
    }
  }
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditPageHandle(KeyValueDef KeyMode)

* ������Χ:
KeyValueDef KeyMode���������ƣ��������ֵ�ǰ�����İ�����
* ����ֵ˵��:
* ���ܽ���:   
�༭ҳ�洦������
���ݱ༭ҳ���д����İ�����ʵ�ֹ��ܣ�����������ʾ��ҳ���л��ȡ�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void EditPageHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemH;
  uchar *ShowData;
  DataLengthDef ShowDataLength = UCHAR,ReceiveDataLength = UCHAR;
  DataTypeDef DataType;
  uint VariableIndex;
  AdditionalInfoDef AdditionFlog = ADDITION_STANDBY;
  PageDef *PagePtr = NULL;
  
  static KeyValueDef CharPositionSelectFlag = NO_KEY_STATUS;
  
  
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,G_CursorNumH);
  
  AdditionFlog = PagePtr->AdditionalInfo;

  //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
  VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
  //��ȡHART��������ָ��
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  ShowDataLength = MENU_GetHartVariableDataLength(VariableIndex);
  ReceiveDataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);  
  DataType = MENU_GetHartVariableDataType(VariableIndex);
  if(MENU_CurrentPageTypeGet() == EDIT_PAGE)
  {
    //��ֹ��������������Խ��
       switch(KeyMode)
       {
          case LEFT:
              if(G_CursorNumH >= PagePtr->ItemNumberH-1)
              {
                G_CursorNumH = 0;
              }
              else
              {
                G_CursorNumH++;
              }            
            break;
          case RIGHT:
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
               //������Ч�Լ���
               DataType = EditVariableRangeConfirm(ShowData,DataType,PagePtr);
              //����������ⷶΧ����
              if(G_VariableArrIndex != 0)
              {
                //Tag
                if(DataType == ASCII_T)
                {
                  HART_ASCII_Code(G_ShowData,ReceiveDataLength,ShowDataLength,ShowData);
                }
                //Data
                else if(PagePtr->ContentStrIndex == STR_INDEX_35)
                {
                  HART_DateHandle(G_ShowData);
                }
                else
                {
                   //��ʱ����������ص�ҳ����ر���
                   EditPageVariableLoad(ShowData,ShowDataLength,DataType,ReceiveDataLength);
                }
                //��ʱ�����������
                MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
                MENU_GeneralItemLinkHandle(CurrentItemH);
              }
              else      
              {  
                //�ַ��ͺͰ����ͱ���ֵ������Ҫ���зǷ�ֵ��ʾ
                if((DataType == INT_VALUE_T)||(DataType == BYTE_VALUE_T))
                {
                  //����TTS��ʾ���趨��������ʾ����ֵ���ޣ�ϵͳ����ʹ�ø���ʾҳ��
                  MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
                  MENU_PageTypeSetHandle(WARNING_PAGE);
                  MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_113);
                }
                else
                {
                  //ҳ�������л�
                  MENU_PageLinkHandle(PagePtr);
                }
                //���������Ҫ�ָ�Ϊ0ֵ
                G_ParamLoadLock = MENU_ParamReset();
              }
              
              MENU_IS_SingleCommandLoad(FALSE,PagePtr);
              G_VariableArrIndex = 0;
              G_VariableProtect.LoadLock = FALSE;
              FlashReadLockHandle(FALSE);
              G_EditPageInputSpecialShowFlag = TRUE;
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_SECOND_ITEM)
            {
              //��ʱ�����������
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0; 
              //ҳ�������л�
              MENU_PageLinkHandle(PagePtr);  
              MENU_IS_SingleCommandLoad(FALSE,PagePtr);
              G_VariableProtect.LoadLock = FALSE;
              FlashReadLockHandle(FALSE);
              G_EditPageInputSpecialShowFlag = TRUE;
              if(PagePtr->ContentStrIndex == STR_INDEX_105)
              {
                MENU_ItemParamLoad(CurrentItemH);
              }
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_THIRD_ITEM)
            {  
              if(G_VariableArrIndex != 0)
              {                
                G_VariableArrIndex--;
              }
              //�˸�
              G_ShowData[G_VariableArrIndex] = 0x20;
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_FOURTH_ITEM)
            {
              //��ʱ�����������
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0;
            }
            break;
          case UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,UP_SELECT);        
            break;
          case LEFT_UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,LEFT_UP_SELECT);
            break;
          case RIGHT_UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,RIGHT_UP_SELECT);
            break;
          case ONE:
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ONE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case TWO:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,TWO,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag); 
           break;
          case THREE:
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,THREE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case FOUR:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FOUR,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case FIVE:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FIVE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case SIX:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SIX,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case SEVEN:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SEVEN,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case EIGHT:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,EIGHT,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case NINE:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,NINE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case ZERO:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ZERO,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case POINT:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,POINT,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case MINUS:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,MINUS,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
         default: break;
   
     }
  }
  else
  {
    //Page error
  }
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditPageShow()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭ҳ����ʾ���������ݱ༭ҳ��ĸ�ʽ�Լ���Ҫ���ݵ�
ҳ���ʽ��ʾ���༭ҳ����ʾ������

*
* �ؼ���ע��
* - 

  
* δ�����:
��Ҫ������ʾ�ļ��С�


*/ 
void EditPageShow()
{
  uchar ShowLineIndex = 0,VariableNumber = 0;
  
  DataLengthDef DataLength = UCHAR,ReceiveDataLength = UCHAR;
  DataTypeDef DataType = UCHAR_T;
  uint VariableIndex = {0};
  uchar *ShowData = NULL,UnitStartPosition = 0;
  PageDef *PagePtr = NULL;
  LanguageTypeDef Language = MENU_LanguageTypeGet();
  PagePtr = MENU_GetCurrentMenuPage();
  //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
  FlashVariableGroupLoad(PagePtr->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);
  ShowData = MENU_VariableInfoGet(&VariableIndex,&DataType,&DataLength,&ReceiveDataLength);
  if(ShowData == NULL)
  {
    HART_AbnormalPageHandle(COMMUNICATION_ERR); 
    return ;
  }
  //������淵�ػ�����������
  MENU_ReturnPageSave(PagePtr);
  //ҳ��ֹͣˢ��
  MENU_PageShowSwitch(FALSE);
  MENU_IS_SingleCommandLoad(TRUE,PagePtr);
  ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);
  //Date��ʾ
  /* ���ǵı���MM-DD-YY */
  if(PagePtr->ContentStrIndex == STR_INDEX_35)
  { 
    ShowLineIndex = EditDateDisplay(DataLength,ShowLineIndex);
    if(ShowLineIndex == SOFTWARE_ERR)
    {
      //�����������������
      HART_AbnormalPageHandle(COMMUNICATION_ERR); 
      return ;
    }
  }
  else
  {
    if(DataType == ASCII_T)
    {
      //�����Tag�༭���棬��Ҫ����ASCII����
      ShowLineIndex = EditTagDisplay(ReceiveDataLength,DataLength,ShowData,ShowLineIndex);
    }
    else if(IS_SPECIAL_DATA_TYPE_HANDLE)
    {
      ShowLineIndex = EditSpecialDataTypeHandle(DataType,ShowLineIndex,ShowData,ReceiveDataLength,&UnitStartPosition);
    }
    else if((DataType == LONG_UINT_T)||(DataType == HANDRED_T)||(DataType == BYTE_VALUE_T))
    {
      ShowLineIndex = EditLongIntDataHandle(ShowData,DataType,ReceiveDataLength,DataLength,ShowLineIndex,&UnitStartPosition);
    }
    else if((DataType == L_ASCII_T)||(DataType == L_ASCII_1_T))
    {
      ShowLineIndex = MENU_VariableShow(DataLength,ShowData,ShowLineIndex,PagePtr,0,NORMAL);
      UnitStartPosition = DataLength;
    }
    else if((DataType == UCHAR_T)||(DataType == UINT_T)||(DataType == INT_VALUE_T))
    {
      ShowLineIndex = EditIntDataHandle(ShowData,DataType,DataLength,ShowLineIndex,&UnitStartPosition);
    }
    else if(DataType == FUNC_CODE_T)
    {
      if(PagePtr->ContentStrIndex == STR_INDEX_337)
      {
        Language = ENGLISH;
      }
      EditFunctionCodeHandle(VariableIndex,DataType,ShowData,Language,ShowLineIndex);
    }
  }
  EditUnitDisplay(VariableNumber,ShowLineIndex,PagePtr,UnitStartPosition);
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  ShowLineIndex = MENU_VariableShow(DataLength,G_ShowData,4,PagePtr,0,NORMAL);
  MENU_HorizontalItemShow(PagePtr,4,MENU_LanguageTypeGet());
  FlashReadLockHandle(TRUE);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
DataTypeDef EditVariableRangeConfirm(uchar *ShowData,DataTypeDef DataType);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭���������Χȷ�Ϻ�����
��Ҫ���������������ݱ����涨�ķ�Χ��������ֵ��Ч��ȷ�ϡ�

*
* �ؼ���ע��
* - 

  
* δ�����:
��Ҫ������ʾ�ļ��С�


*/ 
DataTypeDef EditVariableRangeConfirm(uchar *ShowData,
                              DataTypeDef DataType,const PageDef *CurrentPage)
{
  float FloatData;
  uchar UcharData;
  uint32 UintData;
  
  //��������ⷶΧ����
  if(IS_SPECIAL_RANGE)
  {
    switch(DataType)
    {
      case CURVE_START_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 72))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case SUPRITY_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < -3)||(FloatData > 3))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MIN_RESOL_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 2))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MAX_ZOON_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.5)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MIN_ZOON_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 69.5))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case LEVEL_SPD_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.1)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case CURVE_END_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.1)||(FloatData > 72))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case FAKE_RANGE_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case FAKE_AMP_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 3.3))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case PVL_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.3)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case PVU_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 69.7))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case HANDRED_T:
        //�Ƚ���ʾ�ַ���ת���ɳ���������
        UcharData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UcharData >= 100)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UCHAR_T;
        }
        break;
      case BYTE_VALUE_T:
        //�Ƚ���ʾ�ַ���ת���ɳ���������
        UintData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UintData > 255)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UCHAR_T;
        }
        break;
      case INT_VALUE_T:
        //�Ƚ���ʾ�ַ���ת���ɳ���������
        UintData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UintData > 65535)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UINT_T;
        }
        break;
      default:
        
        break;
    }
  }
  return DataType;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void EditInvalidInputReset(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�Ƿ�������ʾ���鸴ԭ����

*
* �ؼ���ע��
* - 

  
* δ�����:
��Ҫ������ʾ�ļ��С�


*/ 
void EditInvalidInputReset(void)
{
  G_VariableArrIndex = 0;
  //��ʱ�����������
  MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static void EditDateDisplay(DataLengthDef DataLength,uchar *ShowLinePtr);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭������ʾ������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static uchar EditDateDisplay(DataLengthDef DataLength,uchar ShowLineIndex)
{
  uchar DateStrTemp[ASCII_10] = {0};
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  MENU_DateShowHandle(DateStrTemp);
  ShowLineIndex = MENU_VariableShow(DataLength,DateStrTemp,ShowLineIndex,PagePtr,0,NORMAL);
  //DD-MM-YY
  StrStruct[0] = MENU_GetStrStruct(STR_INDEX_320);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
             START_Y_INDEX+5,ENGLISH,NORMAL,StringCodeBuff[0]);  
  return ShowLineIndex;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                            uchar *ShowData,uchar ShowLineIndex,const PageDef *const PagePtr);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭Tag��ʾ����,���룬����ת������ʾ��

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,uchar *ShowData,uchar ShowLineIndex)
{
  uchar j = 0;
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();

  //��20���ֽ�ԭ��Ϊ0x00
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
  j = HART_ASCII_Decode(Tagline,ReceiveDataLength,DataLength,ShowData);
  if(j != 0)
  {
     ShowLineIndex = MENU_VariableShow(DataLength,Tagline,ShowLineIndex,PagePtr,0,NORMAL);
  }
  return ShowLineIndex;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,uchar ShowLineIndex,
        uchar *ShowData,DataLengthDef ReceiveDataLength,const PageDef *const PagePtr);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭���������������ʹ�������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,
  uchar ShowLineIndex,uchar *ShowData,DataLengthDef ReceiveDataLength,uchar *UnitStartPosition)
{
  uchar FloatStrTemp[ASCII_42] = {0};
  uchar Length = 0,j = 0;
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  if(IS_FIXED_CURRENT_HANDLE)
  {
    ShowData = G_PV_Current;
  }
  Length = MENU_DataToASCII(ShowData,FloatStrTemp,DataType);
  if(Length < ASCII_42)
  {
    MENU_TemporaryVariableReset(FloatStrTemp,ASCII_42,Length);
    ShowLineIndex = MENU_VariableShow(ReceiveDataLength,FloatStrTemp,ShowLineIndex,PagePtr,0,NORMAL);
    if(IS_EDIT_PAGE_INPUT_SPECIAL_DISPLAY)
    {  
      for(j = 0;j < Length;j++)
      {
        G_ShowData[j] = FloatStrTemp[j];
      }
      //ȷ������༭������������ַ�������,���������Ҫ���ֽڸ���-1
      G_VariableArrIndex = Length-1;
      G_EditPageInputSpecialShowFlag = FALSE;
    }
    else if(IS_CY_PDS6_PATCH_1)
    {
      //����PDS����
      StrStruct[0] = MENU_GetStrStruct(STR_INDEX_275);
      FlashStringCodeGet(StrStruct,StringCodeBuff[1],ENGLISH);
      MENU_StaticStringShow(StrStruct,START_X_INDEX+Length*6,
          START_Y_INDEX+(ShowLineIndex-1)*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[1]);        
    }
  }
  *UnitStartPosition = Length;
  ShowLineIndex++;
  return ShowLineIndex;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
                DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                  uchar ShowLineIndex,uchar *UnitStartPosition);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭���泤���������ʹ�������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
                DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                  uchar ShowLineIndex,uchar *UnitStartPosition)
{
  uchar Temp[ASCII_8] = {0};
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  *UnitStartPosition = HART_TypeConvert(ShowData,Temp,DataType,ReceiveDataLength,ASCII_T);
  ShowLineIndex = MENU_VariableShow(DataLength,Temp,ShowLineIndex,PagePtr,0,NORMAL);
  return ShowLineIndex;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static uchar EditIntDataHandle(uchar *ShowData,DataType,DataTypeDef DataLength,
       uchar ShowLineIndex,const PageDef *const PagePtr);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭�������������ʹ�������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static uchar EditIntDataHandle(uchar *ShowData,DataTypeDef DataType,
    DataLengthDef DataLength,uchar ShowLineIndex,uchar *UnitStartPosition)
{
  uchar Temp[ASCII_8] = {0};
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  *UnitStartPosition = HART_TypeConvert(ShowData,Temp,DataType,DataLength,ASCII_T);
  ShowLineIndex = MENU_VariableShow(DataLength,Temp,ShowLineIndex,PagePtr,0,NORMAL);
  return ShowLineIndex;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static void EditFunctionCodeHandle(uint VariableIndex,
            DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex);
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭���湦������ʾ��������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static void EditFunctionCodeHandle(uint VariableIndex,DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex)
{
  StringDef StrStruct[1] = {0};
  uint StrNum = 0;
  const HART_UnitDef* UnitTable = NULL;
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];

  //��ȡHART������������ձ�����ָ��
  UnitTable = MENU_GetHartUnitTable(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    StrNum = HART_UnitShowHandle(UnitTable,ShowData);
    StrStruct[0] = MENU_GetStrStruct(StrNum);
    FlashStringCodeGet(StrStruct,StringCodeBuff[0],Language);
    MENU_StaticStringShow(StrStruct,START_X_INDEX,
            START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),Language,NORMAL,StringCodeBuff[0]); 
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
static void EditUnitDisplay(uint VariableIndex,uchar ShowLineIndex,const PageDef *const PagePtr); 
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�༭���浥λ��ʾ��������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static void EditUnitDisplay(uint VariableIndex,
          uchar ShowLineIndex,const PageDef *const PagePtr,uchar UnitStartPosition)
{
  uint StrNum = 0;
  const HART_UnitDef* UnitTable = NULL;
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  uchar VariableNumber = 0,*ShowData = NULL;
  DataTypeDef DataType;
  //�������������������һ��������Ϊ��λ������ͨ�����з�������
  VariableNumber = MENU_PageVariableNumber(G_PageVariableTable);
  if(VariableNumber == 0x02)
  {
    //�༭ҳ����ص�HART����һ��ֻ��һ��������������0Ԫ��
    VariableIndex = MENU_VariableIndexInfoGet(1,G_VariableGroupTable);
    DataType = MENU_GetHartVariableDataType(VariableIndex);
    //��ȡHART��������ָ��
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
    //��ȡHART������������ձ�����ָ��
    UnitTable = MENU_GetHartUnitTable(VariableIndex); 
    if(DataType == FUNC_CODE_T)
    {

      StrNum = HART_UnitShowHandle(UnitTable,ShowData);
      StrStruct[0] = MENU_GetStrStruct(StrNum);
      FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
      MENU_StaticStringShow(StrStruct,START_X_INDEX+UnitStartPosition*6,
              START_Y_INDEX+(ShowLineIndex-2)*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
    }
  }
}

