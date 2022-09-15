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

#include "PollingPage.h"

/*
void PollingPageHandle(void )
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ַ��ѯҳ�洦������
������ѯ��ɺ��л�����Ӧ���档
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void PollingPageHandle(void )
{
  PageDef *PagePtr = NULL;
  
  PagePtr = MENU_GetCurrentMenuPage();
  MENU_PageNumSetHandle(PagePtr->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(PagePtr->PreviousOrNextPageType);

  MENU_CursorNumReset();
  FlashReadLockHandle(FALSE);
}
/*
void PointFill(void )
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ѯ����ʡ�Ժ���Ӻ���������ҳ����ʾ��һ���Ӻ�����
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

void PointFill(uchar *Addr,uchar Index)
{
    Addr[Index++] = 0x2E;
    Addr[Index++] = 0x2E;
    Addr[Index++] = 0x2E;
    Addr[Index++] = 0x00;
}
/*
void PollingPageShow(uint MenuTreeIndex)
* ������Χ:
uint MenuTreeIndex���˵�����ţ���ͨ��������ҵ���ǰҪ��ʾ�Ĳ˵���

* ����ֵ˵��:void 
* ���ܽ���:   
��ַ��ѯ����ҳ����ʾ������
�ڵ�ַ��ѯ���ӵĹ����У���������Ϣ��ʾ������ͬʱ�����ӵĵ�ַҲҪ��ʾ������
*
* �ؼ���ע��
* - 
���ֲ�����׼��֮ǰ���ú����ǿ��Ը��ݿͻ���Ҫ����ʾ��ʽ���иĶ��ġ�
  
* δ�����:
//�˵���ṹ�嶨��
typedef struct 
{
  uint  MenuItemNum;              //�˵�����
  uint  StringNum;                //�˵���Ӣ���ַ������
  PageTypeDef  NextLayerType;     //��һ����������
  uint  NextLayerNum;             //��һ�����ӱ��
  uint  ParamValue;               //�����趨ֵ
}ItemDef;

*/ 
void PollingPageShow()
{
   uchar Addr[6] = {0},Index = 0;
   uchar IndexV = 0,IndexH = 0;
   FontMatrixDef FontMatrix;
   PageDef *PagePtr = NULL;
   
   MENU_PageShowSwitch(FALSE);
   //��ʼ��������Ҫ����ַ����
   
   //��ȡ�˵������
   PagePtr = MENU_GetCurrentMenuPage();
   
   
   //���ص�ַ��ѯ��ʽ
   G_ConnectWay = PagePtr->ConnectWay;
   HART_StartConnect(G_ConnectWay,0);
   //ҳ����������غ���
   MENU_PageCommandGroupLoad(PagePtr);
   G_StrStruct[IndexV] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
   MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[MENU_LanguageTypeGet()]);  
   IndexV = MENU_HeadlineShow(G_StrStruct,PagePtr,NORMAL,G_StringCodeBuff[IndexV]); 
   IndexV++;
   IndexV = MENU_ContentLineShow(PagePtr,IndexV,ENGLISH);
   MENU_CursorOverrunHandle(PagePtr->ItemNumberV-1);
   //�����ѯ���������
   if(G_PollingAddress[0] >= 0x0a)
   {
      Addr[Index++] = G_PollingAddress[0]/10 + 0x30;
      Addr[Index++] = G_PollingAddress[0]%10 + 0x30;
   }
   else
   {
      Addr[Index++] = G_PollingAddress[0] + 0x30;
   }
   PointFill(Addr,Index);
   IndexH = (G_StrStruct+IndexV-1)->CharacterNumber[MENU_LanguageTypeGet()] + 1;
   MENU_DynamicStringShow(ASCII_6X8,Addr,
          START_X_INDEX+IndexH*(FontMatrix.HorizontalLine),START_Y_INDEX+(IndexV-1)*(ITEM_HIGHT),NORMAL,ENGLISH);
   FlashReadLockHandle(TRUE);
}












