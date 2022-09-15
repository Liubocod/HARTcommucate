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

#include "WarningPage.h"


/*
void WaitingErrPageHandle(bool8 Flag )
* 变量范围:
bool8 Flag：用来判断当前界面是否为有错误跳转界面。

* 返回值说明:void 
* 功能介绍:
警告界面后台处理函数。
例如在通信过程中，有些界面在三次链接未果后，需要跳转到对应的错误提示界面，
可以通过本函数实现。

*
* 关键备注：
* - 

  
* 未来提高:


*/

void WaitingErrPageHandle(bool8 Flag )
{
  PageDef *PagePtr = NULL;
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();

  //解除单次加载命令锁定，否则进入下一个等待界面时不会发送命令
  MENU_IS_SingleCommandLoad(FALSE,PagePtr);
  MENU_PageShowSwitch(TRUE);
}
/*
void WarningPageHandle(void )
* 变量范围:


* 返回值说明:void 
* 功能介绍:
警告界面后台处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/

void WarningPageHandle(void )
{
  PageDef *PagePtr = NULL;
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  MENU_PageLinkHandle(PagePtr);
  if(PagePtr->AdditionalInfo == ABNORMAL_MODE)
  {
    MENU_CurrentPageRestore();
    //将缓冲页面变量复位
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
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍:   
警告界面显示函数。

*
* 关键备注：
* - 

  
* 未来提高:

*/

void WarningPageShow()
{
  const ItemDef* CurrentItemH;
  uchar i = 0;
  PageDef *PagePtr = NULL;
  LanguageTypeDef Language = MENU_LanguageTypeGet();
  FontMatrixDef FontMatrix;
  //warning界面一般为命令发送页面或提示说明界面，没有反复操作情况，因此无需FLASH读取锁
  FlashReadLockHandle(FALSE);
  MENU_PageShowSwitch(FALSE);
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  G_StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);
  MENU_ItemParamLoad(CurrentItemH);
  //如果开启特殊操作，可以调用特殊操作函数
  if(G_IsSpecificHandle == TRUE)
  {
    MENU_SpecificOperation(PagePtr->AdditionalInfo);
    //处理完毕以后，需要还原处理标志变量
    G_IsSpecificHandle = FALSE;
  }
  //页面命令组加载函数
  MENU_PageCommandGroupLoad(PagePtr);

  MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[Language]);
  i = MENU_HeadlineShow(G_StrStruct,(void*)PagePtr,NORMAL,G_StringCodeBuff[i]); 
  i = MENU_ContentLineShow(PagePtr,i,Language); 
}