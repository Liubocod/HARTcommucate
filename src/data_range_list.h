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
#ifndef DATA_RANGE_LIST_H
#define DATA_RANGE_LIST_H
#include "data_management.h"//管理 
//RAM区装载被保护参数的个数，根据情况而定，STM32F103C8T6选择不超过65535
#define RAM_DATA_SIZE 200

//装载参数组码的数组大小，一般不超过3
#define PARAM_GROUP_BUFF_SIZE 3
#define RANGE_BUFF_SIZE 5
#define ACCESS_PROPERTY_BUFF_SIZE 2

extern const float FloatDataRangeListBuff[RAM_DATA_SIZE][RANGE_BUFF_SIZE];
extern const uint32 IntDataRangeListBuff[RAM_DATA_SIZE][RANGE_BUFF_SIZE];
extern const uchar CharDataRangeListBuff[RAM_DATA_SIZE][RANGE_BUFF_SIZE];
extern const uchar CharDataAccessProperty[RAM_DATA_SIZE][ACCESS_PROPERTY_BUFF_SIZE];
extern const uchar IntDataAccessProperty[RAM_DATA_SIZE][ACCESS_PROPERTY_BUFF_SIZE];
extern const uchar FloatDataAccessProperty[RAM_DATA_SIZE][ACCESS_PROPERTY_BUFF_SIZE];

extern uchar G_PROTECT_CharParamBuff[RAM_DATA_SIZE][PARAM_GROUP_BUFF_SIZE];
extern uint32 G_PROTECT_IntParamBuff[RAM_DATA_SIZE][PARAM_GROUP_BUFF_SIZE];
extern uint32 G_PROTECT_FloatParamBuff[RAM_DATA_SIZE][PARAM_GROUP_BUFF_SIZE];

#endif