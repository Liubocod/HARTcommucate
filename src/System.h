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

#ifndef SYSTEM_H
#define SYSTEM_H

#define TEST
#define IS_BOOL_TYPE(INSTANCE)  ((INSTANCE == TRUE)||(INSTANCE == FALSE))
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */

#define AssertParam(expr) ((expr) ? (void)0U : SystemErrorHandle())

void NOP(uint Time);
void SystemTimingRefreshHandle();
void SystemPageRefresh();
void SystemBatteryModule();
void SystemErrorHandle();
//成功率功能函数定义
void SystemSucRateResultStatistis(bool8 IsSuccess);
void SystemSendStatistics();
void SystemSucRateRegularHandle();

extern uint G_TimeStamp;
extern uint G_WarningTimeStamp;
extern bool8 G_ClearScreenFlag;

extern  float G_Denominator;
extern  float G_SuccessNum;
extern  bool8 G_ComPCT_Flag;
extern  bool8 G_ComPCT_SWITCH;
extern  float G_ComPCT_Temp;
extern  float G_FailureStatistics;
#endif
