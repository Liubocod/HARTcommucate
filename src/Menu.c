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


//菜单树索引枚举
//菜单行号数组
//菜单行号数组


static void MenuVersionShowDownHandle(PageDef *PagePtr);
static void MenuVersionShowUpHandle(PageDef *PagePtr);
static void MenuItemShowUpHandle(PageDef *PagePtr);
static void MenuFlipOverDisplay(HandleFlagDef HandleFlag);
/**
 //函数名称和参量和返回值类型。
static void MenuVersionShowDownHandle(PageDef *PagePtr);
* 变量范围:
PagePtr ：页面信息指针


* 返回值说明:void 
* 功能介绍:   
*       版本显示界面向下键处理，用于整页切换。
* 关键备注：
* - 
* 未来提高:



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
 //函数名称和参量和返回值类型。
static void MenuVersionShowUpHandle(PageDef *PagePtr);
* 变量范围:
PagePtr ：页面信息指针


* 返回值说明:void 
* 功能介绍:   
*       版本显示界面向上键处理，用于整页切换。
* 关键备注：
* - 
* 未来提高:



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
 //函数名称和参量和返回值类型。
static void MenuItemShowUpHandle(PageDef *PagePtr);
* 变量范围:
PagePtr ：页面信息指针


* 返回值说明:void 
* 功能介绍:   
*       菜单界面菜单项向上键处理，单项切换。
* 关键备注：
* - 
* 未来提高:



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
 //函数名称和参量和返回值类型。
static void MenuItemShowDownHandle(PageDef *PagePtr);
* 变量范围:
PagePtr ：页面信息指针


* 返回值说明:void 
* 功能介绍:   
*       菜单界面菜单项向下键处理，单项切换。
* 关键备注：
* - 
* 未来提高:



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
 //函数名称和参量和返回值类型。
void MenuCurrentPageHandle(KeyValueDef KeyMode);
* 变量范围:
 KeyValueDef HandleFlag：
 typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;
是不同的按键名称，也可能会有更多的按键。

* 返回值说明:void 
* 功能介绍:   
  当前菜单页面处理函数，不同的主按键触发，都会调用本函数，根据不同的按键，执行不同的
  页面修改或页面切换。
*
* 关键备注：
* - 
  1 触发上下按键，页面不需要切换，只是光标上下移动，但是光标序号要确定，因为光标序号
  是确定当前执行菜单项的重要标志。
  2 如果触发"OK"或”BACK”按键，就需要显示新的页面，就需要访问当前菜单项中包含的下一级
 （或上一级）页面编号和类型，将这两项更新到当前显示页面结构体变量G_CurrentPage中，
  那么当执行显示函数时就会根据这两个信息确定当前页面并进行页面显示。
  另外，程序中使用了菜单列类型和菜单项类型的结构体指针。
* 未来提高:



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
                  //针对锐达仪表菜单界面，将缆长值归零。
                  HART_CableLengthReset();
               }
               else
               {
                 Menu_BackupPageLinkHandle(PagePtr);
               }
               //如果返回连接主菜单，清光标值,还原个别变量初始值。
               if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_42)
                 &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
               {
                  MENU_CursorNumReset();
                  MENU_VeriableReset();
               }
               FlashReadLockHandle(FALSE);
          break;  
          //快捷键设计
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

 








 /*/函数名称和参量和返回值类型。
void MenuPageShow(MenuBarDef MenuTreeIndex);
* 变量范围:
MenuTreeIndex：菜单树编号，可以通过这个编号找到菜单对应的信息。

* 返回值说明:void 
* 功能介绍:   
  菜单页面显示。
*
* 关键备注：
* - 
第一行标题后有一个Tag，目前理解这是一个在手操器上修改，
可以更新到产品设备上的一个名称，当完成更改后，会通过HART协议再从设备读取，
并写到菜单标题上（其他类型页面或许也存在）。
  
* 未来提高:
在第一行后有一个设备Tag，可以通过编辑页面修改，这里暂未实现


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
   //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
   FlashVariableGroupLoad(PagePtr->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);

   //页面命令组加载
   //菜单页面现场保护
   MENU_CurrentPageTempSave();
   MENU_ReturnPageSave(PagePtr);
   MENU_CursorSaveHand(TRUE);
   MENU_PageShowSwitch(FALSE);
   MENU_IS_SingleCommandLoad(TRUE,PagePtr);
   StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
   MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[MENU_LanguageTypeGet()]);
   LineOffset = FontMatrix.HorizontalLine*LINE_MARK_INTERVAL;
   MENU_VerticalItemRefreshHandle(ShowLineNum,PagePtr);
   //菜单页面上端的两行说明标题
   ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);
   //纵向显示参数获取，获取当前页面的起始项号及最终项号
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
 /*/函数名称和参量和返回值类型。
void MenuFlipOverDisplay(HandleFlagDef HandleFlag);
* 变量范围:
HandleFlag:处理标记

* 返回值说明:void 
* 功能介绍:   
  翻页标记显示处理函数，用来指示下一页是否还有菜单项。
*
* 关键备注：
* - 
。
  
* 未来提高:



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



