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



#ifndef _IICROM24AA02E48T_H
#define _IICROM24AA02E48T_H


#include "DataType.h"

/****************************24AA02E48T.h文件说明********************************************/
//该文件24AA02E48T.c文件对外的接口声明
/*******************************************************************************************/






bool8  IICROM_SaveCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength);
bool8  IICROM_LoadCharArrayData(uchar8 SaveAddress, uchar8 * Data, uint16 ArrayLength);
bool8  IICROM_SaveCharData(uchar8 SaveAddress, uchar8  Data);
bool8  IICROM_LoadCharData(uchar8 SaveAddress, uchar8* Data);





#endif