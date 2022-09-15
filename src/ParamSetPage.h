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

#ifndef PARAMSETPAGE_H
#define PARAMSETPAGE_H
void	ParamSetPageHandle(KeyValueDef KeyMode);
void ParamSetPageShow();
#define IS_PARAM_DISPLAY (PagePtr->AdditionalInfo == VARIABLE_WITHOUT_NUM)\
                ||(PagePtr->AdditionalInfo == NUM_VARIABLE_BOTH)||(PagePtr->AdditionalInfo == NUM_WITHOUT_VARIABLE)
#endif