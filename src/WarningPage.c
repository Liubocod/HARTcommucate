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

#include "WarningPage.h"


/*
void WaitingErrPageHandle(bool8 Flag )
* ������Χ:
bool8 Flag�������жϵ�ǰ�����Ƿ�Ϊ�д�����ת���档

* ����ֵ˵��:void 
* ���ܽ���:
��������̨��������
������ͨ�Ź����У���Щ��������������δ������Ҫ��ת����Ӧ�Ĵ�����ʾ���棬
����ͨ��������ʵ�֡�

*
* �ؼ���ע��
* - 

  
* δ�����:


*/

void WaitingErrPageHandle(bool8 Flag )
{
  PageDef *PagePtr = NULL;
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();

  //������μ����������������������һ���ȴ�����ʱ���ᷢ������
  MENU_IS_SingleCommandLoad(FALSE,PagePtr);
  MENU_PageShowSwitch(TRUE);
}
/*
void WarningPageHandle(void )
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:
��������̨��������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/

void WarningPageHandle(void )
{
  PageDef *PagePtr = NULL;
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  MENU_PageLinkHandle(PagePtr);
  if(PagePtr->AdditionalInfo == ABNORMAL_MODE)
  {
    MENU_CurrentPageRestore();
    //������ҳ�������λ
    MENU_TempPageTypeSetHandle(EXPLANATION_PAGE);
    MENU_TempPageNumSetHandle(GENERAL_PAGE_INDEX_40);
    MENU_TempPageIndexSetHandle(GENERAL_MENU_TREE);
    HART_ProtectedVariableGet(); 
  }
  MENU_CursorSaveHand(FALSE);
  //MENU_PageCommandGroupLoad(PagePtr);
  MENU_PageShowSwitch(TRUE);
}
/*
void WarningPageShow(uint MenuTreeIndex)
* ������Χ:
MenuTreeIndex���˵�����ţ�����ͨ���������ҵ��˵���Ӧ����Ϣ��

* ����ֵ˵��:void 
* ���ܽ���:   
���������ʾ������

*
* �ؼ���ע��
* - 

  
* δ�����:

*/

void WarningPageShow()
{
  const ItemDef* CurrentItemH;
  uchar i = 0;
  PageDef *PagePtr = NULL;
  LanguageTypeDef Language = MENU_LanguageTypeGet();
  FontMatrixDef FontMatrix;
  //warning����һ��Ϊ�����ҳ�����ʾ˵�����棬û�з�������������������FLASH��ȡ��
  FlashReadLockHandle(FALSE);
  MENU_PageShowSwitch(FALSE);
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  G_StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);
  MENU_ItemParamLoad(CurrentItemH);
  //�������������������Ե��������������
  if(G_IsSpecificHandle == TRUE)
  {
    MENU_SpecificOperation(PagePtr->AdditionalInfo);
    //��������Ժ���Ҫ��ԭ�����־����
    G_IsSpecificHandle = FALSE;
  }
  //ҳ����������غ���
  MENU_PageCommandGroupLoad(PagePtr);

  MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[Language]);
  i = MENU_HeadlineShow(G_StrStruct,(void*)PagePtr,NORMAL,G_StringCodeBuff[i]); 
  i = MENU_ContentLineShow(PagePtr,i,Language); 
}