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

#ifndef HANDLE_KEY_H
#define HANDLE_KEY_H

#define	PRESS_KEY_COUNT		3





#define KEY3_3		P3OUT_bit.P3OUT7
#define KEY3_2		P3OUT_bit.P3OUT6
#define KEY3_1		P8OUT_bit.P8OUT0

typedef enum 
{
//第一行
    FOUR,//4键
    FIVE,//5键
    SIX,//6键   
//第二行 
    SEVEN,//7键
    EIGHT,//8键
    NINE,//9键
//第三行 
    LEFT,//向左移动键
    DOWN,//向下移动键
    RIGHT,//向右键
//第四行
    I_O,//开关，此按键是由硬件实现逻辑，没有挂在排线纵向排线上，是独立走线
    UP,//向上移动键
    OK,//确认键
//第五行
    ONE,//1键
    TWO,//2键
    THREE,//3键 
//第六行
    ZERO,//0键
    POINT,//小数点
    MINUS,//负号键
//第七行
    LEFT_UP_SELECT,//左上选择键
    UP_SELECT,//向上选择键
    RIGHT_UP_SELECT,//右上选择键
//其他
    NO_KEY_STATUS,//无按键状态
}KeyValueDef;

typedef enum
{
    FIRST_COLUMN = 0x3f,
    SECOND_COLUMN = 0x5f,
    THIRD_COLUMN = 0x6f,
    FOURTH_COLUMN = 0x77,
    FIFTH_COLUMN = 0x7B,
    SIXTH_COLUMN = 0x7D,
    SEVENTH_COLUMN = 0x7E,
    NO_LEVEL = 0x7F,
}KeyColumnDef;
typedef enum
{
    LINE1,
    LINE2,
    LINE3,
}KeyLineDef;


typedef enum
{
  HANDLE_FINISH_KEY = 0,
  WAIT_HANDLE_KEY = 1,
  CONTINUED_PRESS,
  SINGLE_PRESS,
  RELEASE_KEY = 0x5A,
}KeyStatusHandleDef;

void KeyLineLevelSwitch(KeyLineDef KeyLine);
void KeyLineValueSwitch(KeyLineDef KeyLine);
void KeyScanHandleModule();

extern KeyStatusHandleDef G_KeyTask;
extern KeyValueDef G_PreviousKeyValure;
extern uchar G_PressKeyCount;
extern KeyValueDef G_KeyValue;
#endif