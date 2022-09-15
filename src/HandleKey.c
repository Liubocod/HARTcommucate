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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
������������ֵ��ȡ������
��ȡ��ǰ���µİ����ڵڼ��С�
*
* �ؼ���ע��
* - 
�������ʱ����Ҫ��⿪�عܽŵ��ź����룬���õ�ع����Ǿ���Ҫ��⿪�عܽš�
  
* δ�����:




*/ 
void KeyInputValueGet() 
{
  G_KeyColumn = KEY_INPUT_PIN_SELECT(0x7f);
}

/*
KeyValueDef  KeyBoardScan(KeyLineDef KeyLine)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ɨ�躯����
ͨ�����������̵ı���������һ�������ֵĴ�������ֵ���ء�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
KeyValueDef  KeyBoardScan(KeyLineDef KeyLine)
{
  KeyValueDef KeyValue;
  //��ȡ�������е������źţ�ȷ��������������һ�С�
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ֵ��ȡ������
ͨ����������Ĺܽ�״̬���Ե�ǰ�����İ�������������������ֵ���ء�
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��λ�������������ܽ�״̬������
�������ĺ������������ܽŵĵ�ƽȫ�����ߡ�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void PullUpAllKeyLine()
{
    KEY3_1 = 1;
    KEY3_2 = 1;
    KEY3_3 = 1;  
}

/*
void KeyLineLevelSwitch()
* ������Χ:
KeyLineDef KeyLine����Ҫ�����͵Ķ�Ӧ�ܽš�

* ����ֵ˵��:void 
* ���ܽ���:   
�����йܽŵ�ƽ�л�������
���ݰ�����ɨ�����ڣ����ڽ������������ܽŵĵ�ƽ�л���
*
* �ؼ���ע��
* - 
����G_KeyLine��ֵ�԰����������������ĹܽŽ��е�ƽ�л���������Ҫɨ��Ĺܽ�
֮ǰ����Ҫ�Ƚ����йܽ����ߣ�������Ϊ�˸�λһ�¹ܽŵ�״̬��������һ�α�����
�Ĺܽ�û�б��øߡ�
  
* δ�����:




*/ 
void KeyLineLevelSwitch(KeyLineDef KeyLine)
{
  //������ǵ��δ�����Ч�����߸��������ߵ����״̬����Ϊ�ߵ�ƽ���
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
* ������Χ:
KeyLineDef KeyLine����Ҫ�����͵Ķ�Ӧ�ܽš�

* ����ֵ˵��:void 
* ���ܽ���:   
������ֵ�л�������
���ݰ�����ɨ�����ڣ����ڽ�����ֵ�л���
*
* �ؼ���ע��
* - 
��������ɨ�裬��7�У���Ӧ7���ܽţ���һ��ɨ��������ֻ��һ���ܽ��ǵ͵�ƽ
�����ܽž�Ϊ�ߵ�ƽ��������ֻ���LINE7֮���ֻ���������趨��LINE1��
������ɨ���л����֮����Ҫ�л������ܽŵĵ�ƽ��ͨ��KeyLineLevelSwitch();
��������
  
* δ�����:




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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ʶ��������

*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
G_PressKeyCount:������Чɨ�����������󲻳���PRESS_KEY_COUNT

* ����ֵ˵��:void 
* ���ܽ���:   
����ɨ�躯����
�����趨�õİ���ɨ�����ڵ��øú�������ɶԼ��̵�ʵʱ��⡣
*
* �ؼ���ע��
* - 
��ӷ���
  
* δ�����:




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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ɨ�账��ģ�顣

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void KeyScanHandleModule()
{
  if(G_KeyScanFlag == TRUE)
  {
    ScanKey();
    G_KeyScanFlag = FALSE;
  }
}