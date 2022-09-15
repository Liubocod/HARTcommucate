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

#include "Menu.h"



#define IS_SYSTEM_DEVICE  ((MENU_CurrentPageNumGet() == CY_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == CHUAN_YI))\
   ||((MENU_CurrentPageNumGet() == CY_HVP_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == CHUAN_YI_HVP))\
    ||((MENU_CurrentPageNumGet() == CY_HVP5_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == CHUAN_YI_HVP5))\
     ||((MENU_CurrentPageNumGet() == CY_T1_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == CHUAN_YI_T1))\
      ||((MENU_CurrentPageNumGet() == RADAR_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == RADAR))\
       ||((MENU_CurrentPageNumGet() == SMS_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == SIEMENS))\
        ||((MENU_CurrentPageNumGet() == EA_PAGE_INDEX_1)&&(MENU_GetMenuTreeIndex() == EJA))\
         ||((MENU_CurrentPageNumGet() == LM_PAGE_INDEX_1)&&(MENU_GetMenuTreeIndex() == LM))\
          ||((MENU_CurrentPageNumGet() == HW_PAGE_INDEX_1)&&(MENU_GetMenuTreeIndex() == HW))\
           ||((MENU_CurrentPageNumGet() == EJA_PAGE_INDEX_1)&&(MENU_GetMenuTreeIndex() == EJA530E))\
            ||((MENU_CurrentPageNumGet() == CY7_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == CY_HART7_PDS))\
              ||((MENU_CurrentPageNumGet() == RAYDAR80G1_0_PAGE_INDEX_0)&&(MENU_GetMenuTreeIndex() == RAYDAR80G1_0))


//�˵�������ö��
//�˵��к�����
//�˵��к�����


static void MenuVersionShowDownHandle(PageDef *PagePtr);
static void MenuVersionShowUpHandle(PageDef *PagePtr);
static void MenuItemShowUpHandle(PageDef *PagePtr);
static void MenuFlipOverDisplay(HandleFlagDef HandleFlag);
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void MenuVersionShowDownHandle(PageDef *PagePtr);
* ������Χ:
PagePtr ��ҳ����Ϣָ��


* ����ֵ˵��:void 
* ���ܽ���:   
*       �汾��ʾ�������¼�����������ҳ�л���
* �ؼ���ע��
* - 
* δ�����:



* 
*/ 
static void MenuVersionShowDownHandle(PageDef *PagePtr)
{
  uchar SinglePageItemNumberV = PagePtr->SinglePageItemNumberV;
  uchar  ItemNumberV = PagePtr->ItemNumberV;
  if(MENU_LanguageTypeGet() == CHINESE)
  {
    SinglePageItemNumberV = 4;
  }
  if(ItemNumberV > SinglePageItemNumberV)
  {
    G_CursorNumV = G_CursorNumV/SinglePageItemNumberV*SinglePageItemNumberV;
    G_CursorNumV += SinglePageItemNumberV;
    if(G_CursorNumV > ItemNumberV)
    {
      G_CursorNumV = 0;
    }
  }
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void MenuVersionShowUpHandle(PageDef *PagePtr);
* ������Χ:
PagePtr ��ҳ����Ϣָ��


* ����ֵ˵��:void 
* ���ܽ���:   
*       �汾��ʾ�������ϼ�����������ҳ�л���
* �ؼ���ע��
* - 
* δ�����:



* 
*/ 
static void MenuVersionShowUpHandle(PageDef *PagePtr)
{
  uchar SinglePageItemNumberV = PagePtr->SinglePageItemNumberV;
  uchar  ItemNumberV = PagePtr->ItemNumberV;
  if(MENU_LanguageTypeGet() == CHINESE)
  {
    SinglePageItemNumberV = 4;
  }
  if(ItemNumberV > SinglePageItemNumberV)
  {
    G_CursorNumV = G_CursorNumV/SinglePageItemNumberV*SinglePageItemNumberV;
    if(G_CursorNumV >= SinglePageItemNumberV)
    {
      G_CursorNumV -= SinglePageItemNumberV;
    }
    else
    {
      G_CursorNumV = ItemNumberV/SinglePageItemNumberV*SinglePageItemNumberV;
    }
  }
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void MenuItemShowUpHandle(PageDef *PagePtr);
* ������Χ:
PagePtr ��ҳ����Ϣָ��


* ����ֵ˵��:void 
* ���ܽ���:   
*       �˵�����˵������ϼ����������л���
* �ؼ���ע��
* - 
* δ�����:



* 
*/ 
static void MenuItemShowUpHandle(PageDef *PagePtr)
{
  if(G_CursorNumV == 0)
  {
    G_CursorNumV = PagePtr->ItemNumberV-1;
  }
  else
  {
    G_CursorNumV--;
  }       
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void MenuItemShowDownHandle(PageDef *PagePtr);
* ������Χ:
PagePtr ��ҳ����Ϣָ��


* ����ֵ˵��:void 
* ���ܽ���:   
*       �˵�����˵������¼����������л���
* �ؼ���ע��
* - 
* δ�����:



* 
*/ 
static void MenuItemShowDownHandle(PageDef *PagePtr)
{
  if(G_CursorNumV >= PagePtr->ItemNumberV-1)
  {
    G_CursorNumV = 0;
  }
  else
  { 
      G_CursorNumV++;
  }            
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void MenuCurrentPageHandle(KeyValueDef KeyMode);
* ������Χ:
 KeyValueDef HandleFlag��
 typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;
�ǲ�ͬ�İ������ƣ�Ҳ���ܻ��и���İ�����

* ����ֵ˵��:void 
* ���ܽ���:   
  ��ǰ�˵�ҳ�洦��������ͬ��������������������ñ����������ݲ�ͬ�İ�����ִ�в�ͬ��
  ҳ���޸Ļ�ҳ���л���
*
* �ؼ���ע��
* - 
  1 �������°�����ҳ�治��Ҫ�л���ֻ�ǹ�������ƶ������ǹ�����Ҫȷ������Ϊ������
  ��ȷ����ǰִ�в˵������Ҫ��־��
  2 �������"OK"��BACK������������Ҫ��ʾ�µ�ҳ�棬����Ҫ���ʵ�ǰ�˵����а�������һ��
 ������һ����ҳ���ź����ͣ�����������µ���ǰ��ʾҳ��ṹ�����G_CurrentPage�У�
  ��ô��ִ����ʾ����ʱ�ͻ������������Ϣȷ����ǰҳ�沢����ҳ����ʾ��
  ���⣬������ʹ���˲˵������ͺͲ˵������͵Ľṹ��ָ�롣
* δ�����:



* 
*/ 

void MenuCurrentPageHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemV = NULL;
  PageDef *PagePtr = NULL;
  
  PagePtr = MENU_GetCurrentMenuPage();  
  CurrentItemV = MENU_GetVarticalItem(PagePtr,G_CursorNumV);
  
  if(MENU_CurrentPageTypeGet() == MENU_BAR)
  {
     switch(KeyMode)
     {
        case DOWN:
            if(PagePtr->AdditionalInfo == VERSION_SHOW)
            {
              MenuVersionShowDownHandle(PagePtr);
            }
            else
            {
              MenuItemShowDownHandle(PagePtr);
            }            
          break;
        case UP:
            if(PagePtr->AdditionalInfo == VERSION_SHOW)
            {
              MenuVersionShowUpHandle(PagePtr);
            }
            else
            {
              MenuItemShowUpHandle(PagePtr);
            }
          break;
        case RIGHT:
        case OK:
          if(PagePtr->AdditionalInfo != VERSION_SHOW)
              MENU_GeneralItemLinkHandle(CurrentItemV);
          break;
        case LEFT:
               if(IS_SYSTEM_DEVICE)          
               {
                  MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
                  MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_42);
                  //�������Ǳ�˵����棬���³�ֵ���㡣
                  HART_CableLengthReset();
               }
               else
               {
                 Menu_BackupPageLinkHandle(PagePtr);
               }
               //��������������˵�������ֵ,��ԭ���������ʼֵ��
               if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_42)
                 &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
               {
                  MENU_CursorNumReset();
                  MENU_VeriableReset();
               }
               FlashReadLockHandle(FALSE);
          break;  
          //��ݼ����
        case ONE:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x01))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,0);
            MENU_GeneralItemLinkHandle(CurrentItemV);
            G_CursorTempV = 0;
          }
          break;
        case TWO:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x02))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,1);
            MENU_GeneralItemLinkHandle(CurrentItemV);
            G_CursorTempV = 1;
          }
          break;
        case THREE:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x03))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,2);
            MENU_GeneralItemLinkHandle(CurrentItemV);          
            G_CursorTempV = 2;
          }
          break;
        case FOUR:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x04))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,3);
            MENU_GeneralItemLinkHandle(CurrentItemV);
            G_CursorTempV = 3;          
          }
          break;
        case FIVE:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x05))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,4);
            MENU_GeneralItemLinkHandle(CurrentItemV); 
            G_CursorTempV = 4;
          }
          break;
        case SIX:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x06))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,5);
            MENU_GeneralItemLinkHandle(CurrentItemV);   
            G_CursorTempV = 5;       
          }
          break;
        case SEVEN:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x07))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,6);
            MENU_GeneralItemLinkHandle(CurrentItemV); 
            G_CursorTempV = 6;    
          }
          break;
        case EIGHT:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x08))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,7);
            MENU_GeneralItemLinkHandle(CurrentItemV);
            G_CursorTempV = 7;            
          }          
          break;
        case NINE:
          if((PagePtr->AdditionalInfo != VERSION_SHOW)
             &&(PagePtr->ItemNumberV >= 0x09))
          {
            CurrentItemV = MENU_GetVarticalItem(PagePtr,8);
            MENU_GeneralItemLinkHandle(CurrentItemV);  
            G_CursorTempV = 8;         
          }
          break;
     default :break;
     }
  }
  else
  {
    //Page error
  }
}

 








 /*/�������ƺͲ����ͷ���ֵ���͡�
void MenuPageShow(MenuBarDef MenuTreeIndex);
* ������Χ:
MenuTreeIndex���˵�����ţ�����ͨ���������ҵ��˵���Ӧ����Ϣ��

* ����ֵ˵��:void 
* ���ܽ���:   
  �˵�ҳ����ʾ��
*
* �ؼ���ע��
* - 
��һ�б������һ��Tag��Ŀǰ�������һ�����ֲ������޸ģ�
���Ը��µ���Ʒ�豸�ϵ�һ�����ƣ�����ɸ��ĺ󣬻�ͨ��HARTЭ���ٴ��豸��ȡ��
��д���˵������ϣ���������ҳ�����Ҳ���ڣ���
  
* δ�����:
�ڵ�һ�к���һ���豸Tag������ͨ���༭ҳ���޸ģ�������δʵ��


*/
void MenuPageShow()
{ 
  HandleFlagDef HandleFlag;
   uchar ShowLineIndex = 0,ShowLineNum,ItemNumber; 
   uchar StartItem,EndItem,LineOffset = 0;
   FontMatrixDef FontMatrix;
   PageDef *PagePtr = NULL;
   StringDef StrStruct[1] = {0};
   LanguageTypeDef Language = MENU_LanguageTypeGet();
   PagePtr = MENU_GetCurrentMenuPage();
   
   MENU_CursorOverrunHandle(PagePtr->ItemNumberV-1);
                                                                                                      
   ShowLineNum = PagePtr->SinglePageItemNumberV; 
   if(Language == CHINESE)
   {
      ShowLineNum = 4;
   } 
   ItemNumber = PagePtr->ItemNumberV;
   //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
   FlashVariableGroupLoad(PagePtr->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);

   //ҳ�����������
   //�˵�ҳ���ֳ�����
   MENU_CurrentPageTempSave();
   MENU_ReturnPageSave(PagePtr);
   MENU_CursorSaveHand(TRUE);
   MENU_PageShowSwitch(FALSE);
   MENU_IS_SingleCommandLoad(TRUE,PagePtr);
   StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
   MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[MENU_LanguageTypeGet()]);
   LineOffset = FontMatrix.HorizontalLine*LINE_MARK_INTERVAL;
   MENU_VerticalItemRefreshHandle(ShowLineNum,PagePtr);
   //�˵�ҳ���϶˵�����˵������
   ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);
   //������ʾ������ȡ����ȡ��ǰҳ�����ʼ��ż��������
   HandleFlag = MENU_VerticalItemSwitchParamGet(&StartItem,
                    &EndItem,ShowLineNum,ItemNumber);
   if(PagePtr->AdditionalInfo == VERSION_SHOW)
   {
     if(ShowLineIndex < 1)
     {
      ShowLineIndex = 1;
     }
     GeneralLineShow(StartItem,EndItem,ShowLineIndex-1,
                     PagePtr,LineOffset);
   }
   else
   {
      MENU_VerticalItemShow(StartItem,EndItem,ShowLineIndex,Language,PagePtr,LineOffset);
      MenuFlipOverDisplay(HandleFlag);
   }
   FlashReadLockHandle(TRUE);
}
 /*/�������ƺͲ����ͷ���ֵ���͡�
void MenuFlipOverDisplay(HandleFlagDef HandleFlag);
* ������Χ:
HandleFlag:������

* ����ֵ˵��:void 
* ���ܽ���:   
  ��ҳ�����ʾ������������ָʾ��һҳ�Ƿ��в˵��
*
* �ؼ���ע��
* - 
��
  
* δ�����:



*/
static void MenuFlipOverDisplay(HandleFlagDef HandleFlag)
{
  CursorShowModeDef CursorShowMode;
  if((G_CursorNumV == 0)&&(MENU_LanguageTypeGet() == CHINESE))
  {
    CursorShowMode = REVERSE_DISPLAY;
  }
  else
  {
    CursorShowMode = NORMAL;
  }
  if(HandleFlag == EndingOption)
  {
  MENU_HandleFlagDisplay(EndingOption,CursorShowMode,116,0,MENU_LanguageTypeGet()); 
  }
  else if(HandleFlag == OptionsLeft)
  {
  MENU_HandleFlagDisplay(OptionsLeft,CursorShowMode,116,0,MENU_LanguageTypeGet());
  }
}



