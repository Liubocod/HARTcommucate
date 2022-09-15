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

#include "HandleKey.h"
#include "Menu_Tree.h"

//#define EMULATOR
#define KEY_INPUT_PIN_SELECT(SELECT_PINS_BIT) (KeyColumnDef)(P4IN&SELECT_PINS_BIT)
#define COLUMN_KEY_NUM 3

KeyStatusHandleDef G_KeyTask = HANDLE_FINISH_KEY;
KeyValueDef G_PreviousKeyValure = NO_KEY_STATUS;

uchar G_PressKeyCount = 0;
KeyValueDef G_KeyValue = NO_KEY_STATUS;
KeyColumnDef G_KeyColumn = NO_LEVEL;





/*
void KeyInputValueGet() 
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
按键纵向输入值获取函数。
获取当前按下的按键在第几列。
*
* 关键备注：
* - 
仿真调试时不需要检测开关管脚的信号输入，当用电池供电是就需要监测开关管脚。
  
* 未来提高:




*/ 
void KeyInputValueGet() 
{
  G_KeyColumn = KEY_INPUT_PIN_SELECT(0x7f);
}

/*
KeyValueDef  KeyBoardScan(KeyLineDef KeyLine)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
键盘扫描函数。
通过对整个键盘的遍历，将第一个被发现的触发按键值返回。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
KeyValueDef  KeyBoardScan(KeyLineDef KeyLine)
{
  KeyValueDef KeyValue;
  //获取三条纵列的输入信号，确定触发按键在那一列。
  KeyInputValueGet();
  switch(G_KeyColumn)
  {
      case FIRST_COLUMN: 
          KeyValue = (KeyValueDef)(KeyLine);
      break;
      case SECOND_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM + KeyLine);
      break;
      case THIRD_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM*2 + KeyLine);
      break;
      case FOURTH_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM*3 + KeyLine);
      break;
      case FIFTH_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM*4 + KeyLine);
      break;
      case SIXTH_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM*5 + KeyLine);
      break;
      case SEVENTH_COLUMN: 
          KeyValue = (KeyValueDef)(COLUMN_KEY_NUM*6 + KeyLine);
      break;
      case NO_LEVEL: 
          KeyValue = NO_KEY_STATUS;
      break;
      default:
      break;
  }
  return KeyValue;
}


/*
KeyValueDef  KeyValueGet()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
按键值获取函数。
通过横向纵向的管脚状态，对当前触发的按键进行锁定，并将键值返回。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 

KeyValueDef  KeyValueGet()
{
  KeyValueDef KeyValue;
  KeyLineDef KeyLine = LINE1;  

  for(KeyLine = LINE1;KeyLine <= LINE3;KeyLine++)
  {
      KeyLineValueSwitch(KeyLine);
      KeyValue = KeyBoardScan(KeyLine);
      if(KeyValue != NO_KEY_STATUS)
      break;
  }

  return KeyValue;
}
/*
void PullUpAllKeyLine()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
复位按键横向驱动管脚状态函数。
将按键的横向排线驱动管脚的电平全部拉高。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void PullUpAllKeyLine()
{
    KEY3_1 = 1;
    KEY3_2 = 1;
    KEY3_3 = 1;  
}

/*
void KeyLineLevelSwitch()
* 变量范围:
KeyLineDef KeyLine：需要被拉低的对应管脚。

* 返回值说明:void 
* 功能介绍:   
按键行管脚电平切换函数。
根据按键的扫描周期，定期进按键行驱动管脚的电平切换。
*
* 关键备注：
* - 
根据G_KeyLine的值对按键横向排线驱动的管脚进行电平切换，在拉低要扫描的管脚
之前，需要先将所有管脚拉高，这样是为了复位一下管脚的状态，以免上一次被拉低
的管脚没有被置高。
  
* 未来提高:




*/ 
void KeyLineLevelSwitch(KeyLineDef KeyLine)
{
  //如果不是单次触发有效，将七根横向排线的输出状态设置为高电平输出
  if(G_KeyTask != WAIT_HANDLE_KEY)
  PullUpAllKeyLine();
  switch(KeyLine)
  {
    case LINE1:
      KEY3_1 = 0;
      break;
    case LINE2:
      KEY3_2 = 0;
      break;
    case LINE3:
      KEY3_3 = 0;
      break;
  default:break;
  }
}
/*
void KeyLineValueSwitch()
* 变量范围:
KeyLineDef KeyLine：需要被拉低的对应管脚。

* 返回值说明:void 
* 功能介绍:   
按键行值切换函数。
根据按键的扫描周期，定期进行行值切换。
*
* 关键备注：
* - 
按键横向扫描，有7行，对应7根管脚，在一个扫描周期内只有一个管教是低电平
其他管脚均为高电平输出。当轮换到LINE7之后将轮换起点重新设定在LINE1。
将横向扫描切换完毕之后需要切换驱动管脚的电平，通过KeyLineLevelSwitch();
函数处理。
  
* 未来提高:




*/ 


void KeyLineValueSwitch(KeyLineDef KeyLine)
{
  KeyLineLevelSwitch(KeyLine);
  if(KeyLine >= LINE3)
  {
          KeyLine = LINE1;
  }
  else 
  {
          KeyLine++;
  }
}


/*
void KeyPressHandle(KeyStatusHandleDef Mode)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
按键识别处理函数。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 

void KeyPressHandle(KeyStatusHandleDef Mode)
{
  if(Mode == SINGLE_PRESS)
  {
     G_KeyTask = SINGLE_PRESS;  
  }
  else if(Mode == CONTINUED_PRESS)
  {
     G_KeyTask = CONTINUED_PRESS;
     G_PressKeyCount = 0;
  }
}


/*
void	ScanKey(void)
* 变量范围:
G_PressKeyCount:按键有效扫描计数器，最大不超过PRESS_KEY_COUNT

* 返回值说明:void 
* 功能介绍:   
按键扫描函数。
根据设定好的按键扫描周期调用该函数，完成对键盘的实时监测。
*
* 关键备注：
* - 
添加防抖
  
* 未来提高:




*/ 

void	ScanKey(void)
{
    KeyValueDef KeyValue;
    KeyValue = KeyValueGet();
    if(KeyValue != NO_KEY_STATUS)
    {
      if(G_PreviousKeyValure == KeyValue)
              G_PressKeyCount++;
      else
              G_PressKeyCount = 0;
      G_PreviousKeyValure = KeyValue;
      
      if((G_PressKeyCount > PRESS_KEY_COUNT)&&(G_KeyTask != WAIT_HANDLE_KEY))
      { 
          switch(G_PreviousKeyValure) 
          { 
            case OK:
            case RIGHT:
            case UP:
            case LEFT:
            case DOWN: 
            case ONE: 
            case TWO: 
            case THREE: 
            case FOUR: 
            case FIVE: 
            case SIX: 
            case SEVEN: 
            case EIGHT: 
            case NINE: 
            case ZERO: 
            case POINT: 
            case MINUS: 
            case LEFT_UP_SELECT: 
            case UP_SELECT: 
              G_KeyValue = G_PreviousKeyValure;
              KeyPressHandle(SINGLE_PRESS);
            break;
            case RIGHT_UP_SELECT: 
              G_KeyValue = RIGHT_UP_SELECT;
              if(MENU_CurrentPageTypeGet() == EDIT_PAGE)
                KeyPressHandle(SINGLE_PRESS);
              else 
                KeyPressHandle(CONTINUED_PRESS);
            break;
          default :break;
          }
      }
    }
    else 
    {
      
      //if(G_KeyTask != WAIT_HANDLE_KEY)
      G_KeyTask = RELEASE_KEY;
      G_PressKeyCount = 0;
    }
}
/*
void KeyScanHandleModule();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
按键扫描处理模块。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void KeyScanHandleModule()
{
  if(G_KeyScanFlag == TRUE)
  {
    ScanKey();
    G_KeyScanFlag = FALSE;
  }
}