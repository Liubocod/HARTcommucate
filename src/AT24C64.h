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



/****************************AT24CXX.h文件说明*******************************************/
//该文件声明了AT24CXX.c中对外开放的接口
/****************************************************************************************/

#ifndef _AT24C64_H
#define _AT24C64_H

#include "DataType.h"




uchar8 IRcvStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength);
bool8  SaveFloat(uint16 SaveAddress, float Data);
bool8  LoadFloat(uint16 SaveAddress, float * Data);
bool8  SaveCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength);
bool8  LoadCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength);
bool8  LoadChar(uint16 SaveAddress, uchar8* Data);
bool8  SaveChar(uint16 SaveAddress, uchar8  Data);

void   EEPROMReadAndWriteTest();




#endif