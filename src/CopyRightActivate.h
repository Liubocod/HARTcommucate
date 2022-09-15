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



#ifndef __COPYRIGHTACTIVATE_H
#define __COPYRIGHTACTIVATE_H


#include "DataType.h"


/****************************CopyRightActivate.h文件说明********************************************/
// 该文件为CopyRightActivate.c声明一些对外开放的接口
/***************************************************************************************************/

#define  CHECK_ACTIVATIONCODE_FAIL_NUM      3                           // 定时检查计算码、公司名称、版权声明失败次数CHECK_ACTIVATIONCODE_FAIL_NUM次，达到此次数进行报复行为
#define  CHECK_ACTIVATIONCODE_TIME          1                        // 单位：分，定时时间间隔，定时检查计算码、公司名称、版权声明（定时间隔实际值为该宏定义数值与定时器定时间隔的乘积），

#define  UNIQUE_CODE_BYTE_NUM       	    6                          // 唯一码字节数
#define  CALC_CODE_BYTE_NUM       	    8                          // 计算码字节数



extern uint16  G_CheckActivateCodeTimer;         // 定期检查激活码(计算码、公司名称、版权声明)用的计时变量,调用该文件时将该变量放在定时器中断中进行++
                                                 // 当 >= CHECK_ACTIVATIONCODE_TIME 时进行一次激活码检查

extern uchar8  G_UniqueCode[UNIQUE_CODE_BYTE_NUM];         // 加密芯片唯一码存放数组
extern uchar8  G_CalcSourceCode[CALC_CODE_BYTE_NUM];       // 加密芯片计算码原码存放数组
extern bool8   G_ActivatorAskStateEnable;  // 激活器询问激活状态使能，检查激活码时分两种，一种是系统定时检查，把整体检查的工作量平均分配到每一次程序调用中
                                          // 另外一种是当激活器询问仪表的激活状态时，把所有激活信息检查一下

extern bool8   G_IfRevenge;
extern uchar8 G_ActivateCheckCounter;

bool8   ReadUniqueCode(uchar8 UniqueCodeArray[]);
bool8   ActivateMeter(void);
bool8   CheckActivationCode(void);
bool8   IfRevengeOrNot(void);



#endif