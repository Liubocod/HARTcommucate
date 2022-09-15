/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */
#ifndef EDIT_PAGE_H
#define EDIT_PAGE_H
void EditPageHandle(KeyValueDef KeyMode);
void EditPageShow();

typedef struct 
{
  KeyValueDef KeyValue;
  uchar UpValue;
  uchar LeftValue;
  uchar RightValue;
  uchar NumberValue;
}KeyCharDef;

extern KeyValueDef  EditPageCharPositionSelect(AdditionalInfoDef AdditionFlog,
                                               KeyValueDef Position);
extern void EditPageDataInput(uchar G_VariableArrIndex,
                       AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue,DataLengthDef ShowDataLength);
extern void CharPositionSeletFlagReset(KeyValueDef *CharPositionSelectFlag);
#endif