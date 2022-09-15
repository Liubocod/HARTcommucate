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

#include "System.h"
#include "WarningPage.h"
#include "HandleKey.h"
#include "HART.h"

#define STATIC_PERCENT 3501
#define MAX_RANGE_BATTERY 3686
#define MIN_RANGE_BATTERY 2380


uint G_FrameGap = 0;
uint G_BytesGap = 0;
uint G_WarningTimeStamp = 0;
uchar G_DelayStamp = 0;
bool8 G_BackLightFlag = FALSE;
uchar G_BackLightCount = 0;

//成功率统计参数定义
//运算分母
float G_Denominator = 0.0;
//测试命令成功接收次数
float G_SuccessNum = 0.0;
//测试命令成功次数
float G_FailureStatistics = 0.0;

float G_ComPCT_Temp = 1.0;
bool8 G_ComPCT_Flag = FALSE;
//成功率处理操作功能变量
bool8 G_ComPCT_SWITCH = TRUE;


/*
void NOP(uint Time)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
延时函数，程序中不影响执行的前提下进行短暂延时。

*
* 关键备注：
* - 
本函数只适合极短的延时，例如通信总线的启动电平置高拉低的短暂延时。
  
* 未来提高:

*/

 
void NOP(uint Time)
{
  G_DelayStamp = Time;
  while(G_DelayStamp);
}
/*
void System_TimingRefreshHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
系统定时刷新函数。
为了解决卡在警告或报警界面
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemTimingRefreshHandle()
{
  if((G_WarningPageRefreshFlag == WARNING_START)
     &&(G_WarningTimeStamp == 0)&&(MENU_CurrentPageTypeGet() == WARNING_PAGE))
  {
    G_WarningPageRefreshFlag = ADDITION_STANDBY;
    WarningPageHandle();
  }
}
/*
void SystemPageRefresh()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
系统页面刷新函数，重新刷新液晶显示。

*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemPageRefresh()
{
  PageDef *PagePtr = NULL;
  //获取菜单树序号
  PagePtr = MENU_GetCurrentMenuPage();
  //如果刷新开启，则调用页面显示函数。
  if((G_PageChangeFlag == TRUE)&&
     ((PagePtr->ConnectWay == ALL_CONNECT_63)||(PagePtr->ConnectWay == ALL_CONNECT_31)
      ||(PagePtr->ConnectWay == ALL_CONNECT)||(PagePtr->ConnectWay == HALF_CONNECT_0)||(PagePtr->ConnectWay == HALF_CONNECT_8)
        ||(G_HART_HandleFlag == HART_STANDBY)||(G_HART_HandleFlag == HART_INIT_ERR)||(G_HART_HandleFlag == HART_COMMON_ERR)
          ||(G_HART_HandleFlag == HART_INIT_COMPLETE)||(G_HART_HandleFlag == HART_COMMON_COMPLETE)||(G_HART_HandleFlag == HART_POLL_ERR)))
  { 
    //排除了PV刷新界面，因为复用会导致第一次加载刷新时间间隔不准确，所以将PV刷新界面独立显示
    //当PV_SHOW处于通信错误时，依然需要显示界面，在通信成功刷新页面部分显示会出现命令错误，所以在此处刷新界面显示
    if(G_ConnectWay != REFRESH)
    {
      MENU_PageShow();
    }  
    if(G_HART_HandleFlag == HART_POLL_ERR)
    {
      G_HART_HandleFlag = HART_STANDBY;
    }
  }
  /*Patch PV显示失联返回无法刷新补丁 */
  if((G_PageChangeFlag == TRUE)
     &&(G_PreviousShowPage.PageType == DYNAMIC_PAGE))
  {
    G_ConnectWay = POLLING_STANDBY;
    G_HART_HandleFlag = HART_STANDBY;
    MENU_PageShow();
  }
}
/*
void SystemKeyHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
系统按键处理函数，
如果发现按键被处发，即进入按键切换页面处理函数，并重置按键状态机。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemKeyHandle()
{
  if(G_KeyTask == SINGLE_PRESS)
  {
    MENU_KeySwitchPageHandle();
    G_KeyTask = WAIT_HANDLE_KEY;
  }
}
/*
void SystemBatteryPercentDetectModule();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
电量监测模块函数
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemBatteryPercentDetectModule()
{
  uint AD_DataValue = 0;
  uint  Power;
  uchar Percent;
  AD_DataValue = GetAverageOfAD(G_ADResults[0]);
  if((AD_DataValue <= MAX_RANGE_BATTERY)&&(AD_DataValue > MIN_RANGE_BATTERY))
  {
    if(AD_DataValue > STATIC_PERCENT)
    {
      Percent = 100;
    }
    else
    {
      Power = (MAX_RANGE_BATTERY-MIN_RANGE_BATTERY)/100;
      Percent = (AD_DataValue-MIN_RANGE_BATTERY)/Power;
    }
  }
  else if(AD_DataValue > MAX_RANGE_BATTERY)
  {
    Percent = 100;
  }
  else if(AD_DataValue <= MIN_RANGE_BATTERY)
  {
    Percent = 0;
  }
  G_BatteryPercent[0] = Percent;
}

/*
void SystemComPCT_FailureStatistis();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
	成功率失败次数统计函数，
	如果发生数据帧校验错误或设备未回应情况，记为一次通信失败
*
* 关键备注：
* - 

  
* 未来提高:

*/

void SystemSucRateResultStatistis(bool8 IsSuccess)
{
  long uint CPT_PERIOD = 0;
  CPT_PERIOD = HART_DataToLongInt(G_PublicVLI2,LONG_UINT_T);
  if(G_ComPCT_SWITCH == TRUE)
  {
    if(G_Denominator > CPT_PERIOD)
    {
          G_ComPCT_SWITCH = FALSE;
          G_Denominator = CPT_PERIOD;
    }
    else
    {
          //开启成功率运算变量
          G_ComPCT_Flag = TRUE;
    }
    if(IsSuccess == TRUE)
    {
          //成功完成一次成功率测试匹配，改变标志变量，更新参数值。
      G_SuccessNum++; 
    }
    else
    {
          G_FailureStatistics++;
    }
  }
}
/*
void SystemSucRateRegularHandle();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
	成功率定期运算函数，
	没完成一次发收处理后，便进入该函数计算一次成功率。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemSucRateRegularHandle()
{
  long uint CPT_PERIOD = 0;
  CPT_PERIOD = HART_DataToLongInt(G_PublicVLI2,LONG_UINT_T);
  if((G_ComPCT_Flag == TRUE)&&(G_ComPCT_SWITCH == TRUE))
  {
        if(G_Denominator > CPT_PERIOD)
        {
          G_ComPCT_SWITCH = FALSE;
          G_Denominator = CPT_PERIOD;
        }
        else
        {
          G_ComPCT_Temp = G_SuccessNum/G_Denominator;
          G_ComPCT_Flag = FALSE;
        }
  }
}

/*
void SystemSendStatistics();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
	成功率命令发送次数统计函数，
	数据帧发送一次，进行统计一次。
*
* 关键备注：
* - 

  
* 未来提高:

*/

void SystemSendStatistics()
{
  long uint CPT_PERIOD = 0;
  CPT_PERIOD = HART_DataToLongInt(G_PublicVLI2,LONG_UINT_T);
  if(G_ComPCT_SWITCH == TRUE)
  {
         //如果接收命令时间未超时，但刷新界面重新发布了命令，导致了命令接收失败，
         if(G_FrameGap != 0)
         {
              G_FailureStatistics++;
         }
         if(G_Denominator > CPT_PERIOD)
         {
                 G_ComPCT_SWITCH = FALSE;
                 G_Denominator = CPT_PERIOD;
         }
         else
         {
               G_Denominator++;
         }
  }	
}
/*
void SystemBatteryModule()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
系统电池电量检测模块。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemBatteryModule()
{
  if(G_SampleEndFlag == TRUE)
  { 
    SystemBatteryPercentDetectModule();
    G_SampleEndFlag = FALSE;
  }
}

/*
void SystemErrorHandle();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
错误调试点，调用call stack找到问题
*
* 关键备注：
* - 

  
* 未来提高:

*/
void SystemErrorHandle()
{
#ifdef TEST
  while(1)
  {
    /*error call stack*/
  }
#endif
}
