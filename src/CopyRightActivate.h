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



#ifndef __COPYRIGHTACTIVATE_H
#define __COPYRIGHTACTIVATE_H


#include "DataType.h"


/****************************CopyRightActivate.h�ļ�˵��********************************************/
// ���ļ�ΪCopyRightActivate.c����һЩ���⿪�ŵĽӿ�
/***************************************************************************************************/

#define  CHECK_ACTIVATIONCODE_FAIL_NUM      3                           // ��ʱ�������롢��˾���ơ���Ȩ����ʧ�ܴ���CHECK_ACTIVATIONCODE_FAIL_NUM�Σ��ﵽ�˴������б�����Ϊ
#define  CHECK_ACTIVATIONCODE_TIME          1                        // ��λ���֣���ʱʱ��������ʱ�������롢��˾���ơ���Ȩ��������ʱ���ʵ��ֵΪ�ú궨����ֵ�붨ʱ����ʱ����ĳ˻�����

#define  UNIQUE_CODE_BYTE_NUM       	    6                          // Ψһ���ֽ���
#define  CALC_CODE_BYTE_NUM       	    8                          // �������ֽ���



extern uint16  G_CheckActivateCodeTimer;         // ���ڼ�鼤����(�����롢��˾���ơ���Ȩ����)�õļ�ʱ����,���ø��ļ�ʱ���ñ������ڶ�ʱ���ж��н���++
                                                 // �� >= CHECK_ACTIVATIONCODE_TIME ʱ����һ�μ�������

extern uchar8  G_UniqueCode[UNIQUE_CODE_BYTE_NUM];         // ����оƬΨһ��������
extern uchar8  G_CalcSourceCode[CALC_CODE_BYTE_NUM];       // ����оƬ������ԭ��������
extern bool8   G_ActivatorAskStateEnable;  // ������ѯ�ʼ���״̬ʹ�ܣ���鼤����ʱ�����֣�һ����ϵͳ��ʱ��飬��������Ĺ�����ƽ�����䵽ÿһ�γ��������
                                          // ����һ���ǵ�������ѯ���Ǳ�ļ���״̬ʱ�������м�����Ϣ���һ��

extern bool8   G_IfRevenge;
extern uchar8 G_ActivateCheckCounter;

bool8   ReadUniqueCode(uchar8 UniqueCodeArray[]);
bool8   ActivateMeter(void);
bool8   CheckActivationCode(void);
bool8   IfRevengeOrNot(void);



#endif