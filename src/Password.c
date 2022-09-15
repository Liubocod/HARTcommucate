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
#include "Password.h"
//密码18016
const uchar G_Password[ASCII_5] = "18016";
bool8 PasswordArraryCompare(uchar* ShowData,const uchar* Password,DataLengthDef DataLength);

/*
//函数名称和参量和返回值类型。
bool8 PasswordArraryCompare(uchar* ShowData,uchar* Password,DataLengthDef DataLength)

* 变量范围:
uchar* ShowData:输入数据数组指针。
uchar* Password：密码保存数组指针。
DataLength：被比较的数据个数。
* 返回值说明:TRUE,两个数组相同，FALSE，两个数组不相同。
* 功能介绍:   
密码数组比较函数，
密码输入数组和密码保存数组进行比较，相同返回TRUE,不同返回FALSE.

*
* 关键备注：
* - 

  
* 未来提高:

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
//函数名称和参量和返回值类型。
void PasswordMatchingHandle(KeyValueDef KeyMode)

* 变量范围:
KeyValueDef KeyMode：按键名称，用于区分当前触发的按键。
* 返回值说明:
* 功能介绍:   
密码匹配界面按键处理函数。

*
* 关键备注：
* - 

  
* 未来提高:

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
    //防止输入变量数组访问越界
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
              //输入值有效
              if(G_VariableArrIndex == ASCII_5)
              {
                //数组比较函数
                if(PasswordArraryCompare(G_ShowData,G_Password,ASCII_5) == TRUE)
                {
                  MENU_GeneralItemLinkHandle(CurrentItemH);
                }
                else
                {
                  //页面链接切换
                  MENU_PageLinkHandle(PagePtr);
                }          
              }
              else      
              {         
                //页面链接切换
                MENU_PageLinkHandle(PagePtr);
              }
              //临时缓冲数组清空
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0;
              FlashReadLockHandle(FALSE);
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_SECOND_ITEM)
            {
              //临时缓冲数组清空
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0; 
              //页面链接切换
              MENU_GeneralItemLinkHandle(CurrentItemH);
              FlashReadLockHandle(FALSE);
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_THIRD_ITEM)
            {  
              if(G_VariableArrIndex != 0)
              {                
                G_VariableArrIndex--;
              }
              //退格
              G_ShowData[G_VariableArrIndex] = 0x20;
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_FOURTH_ITEM)
            {
              //临时缓冲数组清空
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
//函数名称和参量和返回值类型。
void PassWordMatchingShow()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
密码匹配界面显示函数。

*
* 关键备注：
* - 

  
* 未来提高:



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
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  
  
  //页面停止刷新
  MENU_PageShowSwitch(FALSE);
  StrStruct[0] = MENU_GetStrStruct(PagePtr->TitleLineStringNum);
  MENU_FontMatrixGet(&FontMatrix,StrStruct->FontNum[MENU_LanguageTypeGet()]);
  //菜单页面上端的两行说明标题
  ShowLineIndex = MENU_HeadlineShow(G_StrStruct,(const void*)PagePtr,NORMAL,G_StringCodeBuff[ShowLineIndex]); 
  ShowLineIndex = MENU_ContentLineShow(PagePtr,ShowLineIndex,ENGLISH);
  //Input the password指示信息显示i++
  MENU_DynamicStringShow(ASCII_6X8,MarkedWord,0,ShowLineIndex,NORMAL,ENGLISH);
  ShowLineIndex++;
  //输入信息显示
  ShowLineIndex = MENU_VariableShow(ASCII_5,G_ShowData,ShowLineIndex,PagePtr,0,NORMAL);
  //横向菜单项显示。
  MENU_HorizontalItemShow(PagePtr,4,MENU_LanguageTypeGet());
  FlashReadLockHandle(TRUE);
}
