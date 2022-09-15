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

#include "PollingPage.h"

/*
void PollingPageHandle(void )
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
地址轮询页面处理函数，
负责轮询完成后切换到相应界面。
*
* 关键备注：
* - 

  
* 未来提高:



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
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
轮询界面省略号添加函数，属于页面显示的一个子函数。
*
* 关键备注：
* - 

  
* 未来提高:



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
* 变量范围:
uint MenuTreeIndex：菜单树序号，可通过改序号找到当前要显示的菜单树

* 返回值说明:void 
* 功能介绍:   
地址轮询链接页面显示函数，
在地址轮询链接的过程中，将基本信息显示出来，同时将链接的地址也要显示出来。
*
* 关键备注：
* - 
在手操器标准化之前，该函数是可以根据客户需要的显示形式进行改动的。
  
* 未来提高:
//菜单项结构体定义
typedef struct 
{
  uint  MenuItemNum;              //菜单项编号
  uint  StringNum;                //菜单项英文字符串编号
  PageTypeDef  NextLayerType;     //下一层连接类型
  uint  NextLayerNum;             //下一层连接编号
  uint  ParamValue;               //参数设定值
}ItemDef;

*/ 
void PollingPageShow()
{
   uchar Addr[6] = {0},Index = 0;
   uchar IndexV = 0,IndexH = 0;
   FontMatrixDef FontMatrix;
   PageDef *PagePtr = NULL;
   
   MENU_PageShowSwitch(FALSE);
   //初始化界面需要单地址链接
   
   //获取菜单树序号
   PagePtr = MENU_GetCurrentMenuPage();
   
   
   //加载地址轮询方式
   G_ConnectWay = PagePtr->ConnectWay;
   HART_StartConnect(G_ConnectWay,0);
   //页面命令组加载函数
   MENU_PageCommandGroupLoad(PagePtr);
   G_StrStruct[IndexV] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
   MENU_FontMatrixGet(&FontMatrix,G_StrStruct->FontNum[MENU_LanguageTypeGet()]);  
   IndexV = MENU_HeadlineShow(G_StrStruct,PagePtr,NORMAL,G_StringCodeBuff[IndexV]); 
   IndexV++;
   IndexV = MENU_ContentLineShow(PagePtr,IndexV,ENGLISH);
   MENU_CursorOverrunHandle(PagePtr->ItemNumberV-1);
   //如果轮询链接组序号
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












