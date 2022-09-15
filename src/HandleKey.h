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

#ifndef HANDLE_KEY_H
#define HANDLE_KEY_H

#define	PRESS_KEY_COUNT		3





#define KEY3_3		P3OUT_bit.P3OUT7
#define KEY3_2		P3OUT_bit.P3OUT6
#define KEY3_1		P8OUT_bit.P8OUT0

typedef enum 
{
//��һ��
    FOUR,//4��
    FIVE,//5��
    SIX,//6��   
//�ڶ��� 
    SEVEN,//7��
    EIGHT,//8��
    NINE,//9��
//������ 
    LEFT,//�����ƶ���
    DOWN,//�����ƶ���
    RIGHT,//���Ҽ�
//������
    I_O,//���أ��˰�������Ӳ��ʵ���߼���û�й����������������ϣ��Ƕ�������
    UP,//�����ƶ���
    OK,//ȷ�ϼ�
//������
    ONE,//1��
    TWO,//2��
    THREE,//3�� 
//������
    ZERO,//0��
    POINT,//С����
    MINUS,//���ż�
//������
    LEFT_UP_SELECT,//����ѡ���
    UP_SELECT,//����ѡ���
    RIGHT_UP_SELECT,//����ѡ���
//����
    NO_KEY_STATUS,//�ް���״̬
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