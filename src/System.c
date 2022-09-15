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

//�ɹ���ͳ�Ʋ�������
//�����ĸ
float G_Denominator = 0.0;
//��������ɹ����մ���
float G_SuccessNum = 0.0;
//��������ɹ�����
float G_FailureStatistics = 0.0;

float G_ComPCT_Temp = 1.0;
bool8 G_ComPCT_Flag = FALSE;
//�ɹ��ʴ���������ܱ���
bool8 G_ComPCT_SWITCH = TRUE;


/*
void NOP(uint Time)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ʱ�����������в�Ӱ��ִ�е�ǰ���½��ж�����ʱ��

*
* �ؼ���ע��
* - 
������ֻ�ʺϼ��̵���ʱ������ͨ�����ߵ�������ƽ�ø����͵Ķ�����ʱ��
  
* δ�����:

*/

 
void NOP(uint Time)
{
  G_DelayStamp = Time;
  while(G_DelayStamp);
}
/*
void System_TimingRefreshHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ϵͳ��ʱˢ�º�����
Ϊ�˽�����ھ���򱨾�����
*
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ϵͳҳ��ˢ�º���������ˢ��Һ����ʾ��

*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void SystemPageRefresh()
{
  PageDef *PagePtr = NULL;
  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();
  //���ˢ�¿����������ҳ����ʾ������
  if((G_PageChangeFlag == TRUE)&&
     ((PagePtr->ConnectWay == ALL_CONNECT_63)||(PagePtr->ConnectWay == ALL_CONNECT_31)
      ||(PagePtr->ConnectWay == ALL_CONNECT)||(PagePtr->ConnectWay == HALF_CONNECT_0)||(PagePtr->ConnectWay == HALF_CONNECT_8)
        ||(G_HART_HandleFlag == HART_STANDBY)||(G_HART_HandleFlag == HART_INIT_ERR)||(G_HART_HandleFlag == HART_COMMON_ERR)
          ||(G_HART_HandleFlag == HART_INIT_COMPLETE)||(G_HART_HandleFlag == HART_COMMON_COMPLETE)||(G_HART_HandleFlag == HART_POLL_ERR)))
  { 
    //�ų���PVˢ�½��棬��Ϊ���ûᵼ�µ�һ�μ���ˢ��ʱ������׼ȷ�����Խ�PVˢ�½��������ʾ
    //��PV_SHOW����ͨ�Ŵ���ʱ����Ȼ��Ҫ��ʾ���棬��ͨ�ųɹ�ˢ��ҳ�沿����ʾ�����������������ڴ˴�ˢ�½�����ʾ
    if(G_ConnectWay != REFRESH)
    {
      MENU_PageShow();
    }  
    if(G_HART_HandleFlag == HART_POLL_ERR)
    {
      G_HART_HandleFlag = HART_STANDBY;
    }
  }
  /*Patch PV��ʾʧ�������޷�ˢ�²��� */
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ϵͳ������������
������ְ����������������밴���л�ҳ�洦�����������ð���״̬����
*
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�������ģ�麯��
*
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
	�ɹ���ʧ�ܴ���ͳ�ƺ�����
	�����������֡У�������豸δ��Ӧ�������Ϊһ��ͨ��ʧ��
*
* �ؼ���ע��
* - 

  
* δ�����:

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
          //�����ɹ����������
          G_ComPCT_Flag = TRUE;
    }
    if(IsSuccess == TRUE)
    {
          //�ɹ����һ�γɹ��ʲ���ƥ�䣬�ı��־���������²���ֵ��
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
	�ɹ��ʶ������㺯����
	û���һ�η��մ���󣬱����ú�������һ�γɹ��ʡ�
*
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
	�ɹ�������ʹ���ͳ�ƺ�����
	����֡����һ�Σ�����ͳ��һ�Ρ�
*
* �ؼ���ע��
* - 

  
* δ�����:

*/

void SystemSendStatistics()
{
  long uint CPT_PERIOD = 0;
  CPT_PERIOD = HART_DataToLongInt(G_PublicVLI2,LONG_UINT_T);
  if(G_ComPCT_SWITCH == TRUE)
  {
         //�����������ʱ��δ��ʱ����ˢ�½������·���������������������ʧ�ܣ�
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ϵͳ��ص������ģ�顣
*
* �ؼ���ע��
* - 

  
* δ�����:

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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
������Ե㣬����call stack�ҵ�����
*
* �ؼ���ע��
* - 

  
* δ�����:

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
