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
#include "Password.h"
//����18016
const uchar G_Password[ASCII_5] = "18016";
bool8 PasswordArraryCompare(uchar* ShowData,const uchar* Password,DataLengthDef DataLength);

/*
//�������ƺͲ����ͷ���ֵ���͡�
bool8 PasswordArraryCompare(uchar* ShowData,uchar* Password,DataLengthDef DataLength)

* ������Χ:
uchar* ShowData:������������ָ�롣
uchar* Password�����뱣������ָ�롣
DataLength�����Ƚϵ����ݸ�����
* ����ֵ˵��:TRUE,����������ͬ��FALSE���������鲻��ͬ��
* ���ܽ���:   
��������ȽϺ�����
����������������뱣��������бȽϣ���ͬ����TRUE,��ͬ����FALSE.

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 

bool8 PasswordArraryCompare(uchar* ShowData,const uchar* Password,DataLengthDef DataLength)
{
  uchar i = 0;
  for(i = 0; i < DataLength; i++)
  {
    if(*(ShowData+i) != *(Password+i))
    {
      return FALSE;
    }
  }
  return TRUE;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void PasswordMatchingHandle(KeyValueDef KeyMode)

* ������Χ:
KeyValueDef KeyMode���������ƣ��������ֵ�ǰ�����İ�����
* ����ֵ˵��:
* ���ܽ���:   
����ƥ����水����������

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void PasswordMatchingHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemH;

  AdditionalInfoDef AdditionFlog = ADDITION_STANDBY;
  PageDef *PagePtr = NULL;
  static KeyValueDef CharPositionSelectFlag = NO_KEY_STATUS;
  
  
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,G_CursorNumH);
  
  AdditionFlog = PagePtr->AdditionalInfo;
  
  if(MENU_CurrentPageTypeGet() == PASWD_PAGE)
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
              //����ֵ��Ч
              if(G_VariableArrIndex == ASCII_5)
              {
                //����ȽϺ���
                if(PasswordArraryCompare(G_ShowData,G_Password,ASCII_5) == TRUE)
                {
                  MENU_GeneralItemLinkHandle(CurrentItemH);
                }
                else
                {
                  //ҳ�������л�
                  MENU_PageLinkHandle(PagePtr);
                }          
              }
              else      
              {         
                //ҳ�������л�
                MENU_PageLinkHandle(PagePtr);
              }
              //��ʱ�����������
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0;
              FlashReadLockHandle(FALSE);
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_SECOND_ITEM)
            {
              //��ʱ�����������
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0; 
              //ҳ�������л�
              MENU_GeneralItemLinkHandle(CurrentItemH);
              FlashReadLockHandle(FALSE);
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
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ONE,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case TWO:          
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,TWO,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag); 
           break;
          case THREE:
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,THREE,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case FOUR:          
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FOUR,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case FIVE:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FIVE,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case SIX:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SIX,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case SEVEN:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SEVEN,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case EIGHT:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,EIGHT,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case NINE:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,NINE,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case ZERO:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ZERO,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case POINT:          
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,POINT,ASCII_5);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case MINUS:           
           if(G_VariableArrIndex < ASCII_5)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,MINUS,ASCII_5);
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
void PassWordMatchingShow()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ƥ�������ʾ������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void PassWordMatchingShow()
{
  FontMatrixDef FontMatrix = {0};
  PageDef *PagePtr = NULL;
  uchar ShowLineIndex = 0;
  StringDef StrStruct[1] = {0};
  //Input the password
  uchar MarkedWord[] = 
  {0x49,0x6E,0x70,0x75,0x74,0x20,
    0x74,0x68,0x65,0x20,0x70,0x61,
      0x73,0x73,0x77,0x6F,0x72,0x64,0x00};
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  
  
  //ҳ��ֹͣˢ��
  MENU_PageShowSwitch(FALSE);
  StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
  MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[MENU_LanguageTypeGet()]);
  //�˵�ҳ���϶˵�����˵������
  ShowLineIndex = MENU_HeadlineShow(G_StrStruct,(const void*)PagePtr,NORMAL,G_StringCodeBuff[ShowLineIndex]); 
  ShowLineIndex = MENU_ContentLineShow(PagePtr,ShowLineIndex,ENGLISH);
  //Input the passwordָʾ��Ϣ��ʾi++
  MENU_DynamicStringShow(ASCII_6X8,MarkedWord,0,ShowLineIndex,NORMAL,ENGLISH);
  ShowLineIndex++;
  //������Ϣ��ʾ
  ShowLineIndex = MENU_VariableShow(ASCII_5,G_ShowData,ShowLineIndex,PagePtr,0,NORMAL);
  //����˵�����ʾ��
  MENU_HorizontalItemShow(PagePtr,4,MENU_LanguageTypeGet());
  FlashReadLockHandle(TRUE);
}
