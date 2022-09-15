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
#include "CurvePage.h"
#include "HART.h"

#define	LCDCURVESTARTPAGE				1
#define	LCDCURVEENDPAGE				7
#define	LCDCURVESTARTCOLUMN			20
#define	LCDCURVEENDCOLUMN				121

void	DisplayMeasureV_Amplitude(void);
void	DrawChart(void);
void	DiplayCureXY(void);
void	DrawCurve();
void	DrawHLine(uchar HPostion);
void    CurveLowDeadZoneHandle(const ItemDef* CurrentItemH);
void    CurveHighDeadZoneHandle(const ItemDef* CurrentItemH);
void    CurveXZoomHandle(const PageDef *CurrentPage);
void    CurveYZoomHandle(const PageDef *CurrentPage);
void    CurveFakePartHandle(const ItemDef* CurrentItemH);
void    CurveFakeNhlHandle(const PageDef *CurrentPage,const ItemDef* CurrentItemH);
void    CurveGeneralHandle();
void    CurveKeyDownHandle(const PageDef *CurrentPage);
void    CurveKeyUpHandle(const PageDef *CurrentPage);
void    CurveThresholdHandle(const ItemDef* CurrentItemH);
void	CurveZoomSart_End(void);
void	CurveDeadZoneSpanDisplay(void);
//曲线显示范围上限
uchar G_CurveLimitH = 255;
//曲线显示范围下限
uchar G_CurveLimitL = 0;
//Y轴缩放比例变量
float G_Curve_One_H = 5.4;
//X轴缩放比例变量
float G_Page_One_M;
uchar ShowDataBuffe[20] = {0};
uchar G_ShowCurveData[100];
uchar G_ShowFakeCurveData[100];
uchar DecimalP = 0;
//当前显示曲线是否处于放大状态
bool8 G_IsCurveZoom = FALSE;
//
bool8 G_VariableSingleDisFlag = FALSE;
//虚假回波更新标志
bool8 G_IsFakeCurveUpdateFlag = FALSE;
//虚假回波加载计数
uchar G_FakeCurveLoadCount = 0;
//虚假回波显示控制标志
bool8 G_IsFakeCurveDisplay = FALSE;

//定义曲线操作界面光标坐标数组
uchar G_ZoomX[ZOOM_BUFF_SIZE] = {0};
uchar G_ZoomY[ZOOM_BUFF_SIZE] = {0};
//定义曲线操作界面横纵光标处理标志变量
uchar G_ZoomX_Flag = 0;
uchar G_ZoomY_Flag = 0;
/*
//函数名称和参量和返回值类型。
void	DrawChart(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线表格绘制函数，曲线显示的实线和虚线背景
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	DrawChart(void)
{
	unsigned char TempC,TempL,TempD;
        bool8 ClearFlag = FALSE;
        //清屏
	for(TempL = LCDCURVESTARTPAGE; TempL < LCDCURVEENDPAGE; TempL++)
	{
                LCD_CS_Switch(LCDCURVESTARTCOLUMN,TempL);
                ClearFlag = FALSE;
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; TempC++)
		{
                  if((ClearFlag==FALSE)&&
                     ((TempC >= LCD_CS_BOUNDARY)&&(TempC < LCD_MAX_BOUNDARY)))
                  {
                    LCD_CS_Switch(LCD_CS_BOUNDARY,TempL);
                    ClearFlag = TRUE;
                  }
			LcdWriteData(0);		//清除曲线区，以备刷新曲线
		}
	}
 
        //曲线界面
	for(TempL = LCDCURVESTARTPAGE; TempL < LCDCURVEENDPAGE; )
	{
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; )
		{
                        LCD_CS_Switch(TempC,TempL);
			LcdWriteData(0x01);
			if(TempL == 1)
				TempC++;
			else
				TempC = TempC+2;
		}
		TempL = TempL+2;
	}

	for(TempL = LCDCURVESTARTPAGE; TempL < LCDCURVEENDPAGE; TempL++)
	{
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; )
		{
			if(TempC == 120)
				TempC = LCDCURVEENDCOLUMN;
                        LCD_CS_Switch(TempC,TempL);
			if((TempC == LCDCURVESTARTCOLUMN)||(TempC == LCDCURVEENDCOLUMN))
				LcdWriteData(0xFF);
			else
				LcdWriteData(0x55);
			TempC = TempC+25;
		}
	}

	for(TempC = LCDCURVESTARTCOLUMN; TempC <= LCDCURVEENDCOLUMN; TempC++)
	{
          TempD = 0x80;
          if((TempC == LCDCURVESTARTCOLUMN)||(TempC == LCDCURVEENDCOLUMN))
                  TempD = 0xFF;
          else if((TempC-LCDCURVESTARTCOLUMN)%25 == 0)
                  TempD = 0xD5;
          if((TempC == 43)||(TempC == 120))
          {
            TempD = 0x80;
          }
          LCD_CS_Switch(TempC,6);
          LcdWriteData(TempD);
	}
}


/*
//函数名称和参量和返回值类型。
void	DiplayCureXY(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线X轴和Y轴编辑函数，刻度显示
*
* 关键备注：
* - 

  
* 未来提高:



*/


void	DiplayCureXY(void)
{
	unsigned char TempC,TempL,TempD;
	float TempF,TempK;
        float CurveEndP = 0.0,CurveStartP = 0.0;
        MENU_DynamicStringShow(ASCII_5X8,"V",20,0,NORMAL,ENGLISH);
	TempF = 3.3/255*G_CurveLimitH;
//	TempF1 = 3.3/255*CurveLimitL;
	TempK = 1.1*(G_CurveLimitH-G_CurveLimitL)/255;
	for(TempC = 0; TempC < 7; )
	{
		if(TempF < 0)
			TempF = 0;
		HART_FloatToChar(TempF,1);
		ShowDataBuffe[3] = '\0';
                MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,0,TempC,NORMAL,ENGLISH);
		TempF = TempF-TempK;
		TempC = TempC+2;
	}
	
	for(TempC = 0; TempC < 7; )
	{
		for(TempL = 0; TempL < 20; TempL++)
		{
                  //坐标错误会导致向下半格错误
                        LCD_CS_Switch(TempL,TempC);
			TempD = LcdReadData();
                        NOP(1);
			LCD_CS_Switch(TempL,TempC);
			TempD = LcdReadData();
                        LCD_CS_Switch(TempL,TempC);
			LcdWriteData(TempD<<4);

                        LCD_CS_Switch(TempL,TempC+1);
			LcdWriteData(TempD>>4);
		}
		TempC = TempC+2;
	}
        CurveEndP = HART_DataToFloat(G_RadarCurveEndP,FLOAT_T);
	HART_FloatToChar(CurveEndP,2);
        ShowDataBuffe[4] = '\0';
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,95,7,NORMAL,ENGLISH); 
        CurveStartP = HART_DataToFloat(G_PublicVF1,FLOAT_T);
	HART_FloatToChar(CurveStartP,2);
        ShowDataBuffe[4] = '\0';
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,20,7,NORMAL,ENGLISH);
	TempF = CurveStartP+(CurveEndP-CurveStartP)/2;
	HART_FloatToChar(TempF,2);
        ShowDataBuffe[4] = '\0';
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,61,7,NORMAL,ENGLISH);
        MENU_DynamicStringShow(ASCII_5X8,"m",121,7,NORMAL,ENGLISH);
        MENU_DynamicStringShow(ASCII_5X8,"m",121,0,NORMAL,ENGLISH);
}
/*
//函数名称和参量和返回值类型。
void	DrawCurve()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线绘制函数，苗100个曲线点。
*
* 关键备注：
* - 

  
* 未来提高:



*/

void	DrawCurve(uchar *ShowCurveData)
{
	uchar TempC,PreByte,PreDot,CurrentDot,CurrentByte,TempData,InitDotValure;
	float TempF;
	PreDot = 1;
        
	for(TempC = 0; TempC < 100; TempC++)
	{
          //超出了显示范围的点需要定格在显示范围内。
		if(ShowCurveData[TempC] < G_CurveLimitL)
			ShowCurveData[TempC] = G_CurveLimitL;
		if(ShowCurveData[TempC] > G_CurveLimitH)
			ShowCurveData[TempC] = G_CurveLimitH;
                
		TempF = ShowCurveData[TempC]-G_CurveLimitL;
                if(TempF != 0)
                  TempF = TempF/G_Curve_One_H;
                else
                  TempF = 0;
		TempData = (unsigned char)TempF;
                //纵向余数点坐标
		CurrentDot = TempData%8;
		CurrentDot = 7-CurrentDot;
                //纵向行数坐标
		CurrentByte = 6-TempData/8;
		
		if(TempC != 0)
		{
                  //在同一行
                  if(CurrentByte == PreByte)
                  {
                          InitDotValure = 0xFF;                    
                          TempData = 0xFF;
                          //余数点位置与历史点进行比较
                          //历史点在高处，将描点数据进行移位运算，便于将历史点和当前点进行连线
                          if(CurrentDot < PreDot)
                          {
                                  InitDotValure >>= (7-PreDot);
                                  TempData <<= CurrentDot;
                          }
                          else
                          {
                                  InitDotValure >>= (7-CurrentDot);
                                  TempData <<= PreDot;
                          }
                          //得到两点进行描线连接的数据
                          TempData = InitDotValure&TempData;
                  }
                  //当前行数高于历史行数（向下）
                  else	if(CurrentByte > PreByte)
                  {
                          InitDotValure = 0xFF;                    
                          InitDotValure <<= PreDot;
                          
                          //设置读取位置坐标
                          //读取命令需要发两遍，因为第一遍液晶需要将显示内容锁存在输出寄存器，第二遍才会正常读取
                          LCD_CS_Switch(TempC+21,PreByte);
                          TempData = LcdReadData();
                          NOP(1);
                          LCD_CS_Switch(TempC+21,PreByte);
                          TempData = LcdReadData();
                          TempData = TempData|InitDotValure;
                          LCD_CS_Switch(TempC+21,PreByte);
                          LcdWriteData(TempData);
                          PreByte++;
                          while(CurrentByte > PreByte)
                          {
                                  LCD_CS_Switch(TempC+21,PreByte);
                                  LcdWriteData(0xFF);
                                  PreByte++;
                          }
                          TempData = 0xFF;
                          TempData >>= (7-CurrentDot);
                  }
                  else 
                  {
                          InitDotValure = 0xFF;
                          InitDotValure >>= (7-PreDot);
                          //读取命令需要发两遍，因为第一遍液晶需要将显示内容锁存在输出寄存器，第二遍才会正常读取
                          LCD_CS_Switch(TempC+21,PreByte);
                          TempData = LcdReadData();
                          NOP(1);
                          LCD_CS_Switch(TempC+21,PreByte);
                          TempData = LcdReadData();
                          TempData = TempData|InitDotValure;
                          LCD_CS_Switch(TempC+21,PreByte);
                          LcdWriteData(TempData);
                          PreByte--;
                          while(CurrentByte < PreByte)
                          {
                                  LCD_CS_Switch(TempC+21,PreByte);
                                  LcdWriteData(0xFF);
                                  PreByte--;
                          }
                          TempData = 0xFF;
                          TempData <<= CurrentDot;
                  }
                  //读取命令需要发两遍，因为第一遍液晶需要将显示内容锁存在输出寄存器，第二遍才会正常读取
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  InitDotValure = LcdReadData();
                  NOP(1);
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  InitDotValure = LcdReadData();

                  TempData = TempData|InitDotValure;
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  LcdWriteData(TempData);
		}
                //读取命令需要发两遍，因为第一遍液晶需要将显示内容锁存在输出寄存器，第二遍才会正常读取
                LCD_CS_Switch(TempC+21,CurrentByte);
                InitDotValure = LcdReadData();
                NOP(1);
                LCD_CS_Switch(TempC+21,CurrentByte);
                InitDotValure = LcdReadData();

                TempData = TempData|InitDotValure;
                LCD_CS_Switch(TempC+21,CurrentByte);
                LcdWriteData(TempData);
		PreDot = CurrentDot;
		PreByte = CurrentByte;
	}
}

/*
//函数名称和参量和返回值类型。
void	DrawCurve()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
峰值显示函数，包括测量值，信噪比或控制频率，峰值，以及波形位置。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	DisplayMeasureV_Amplitude(void)
{
	uchar TempC,TempP,TempD,TempData[5] = {0xC0,0xE0,0xF0,0xE0,0xC0};
	float	SNR_CR_Float,ValueFloat,AmplitudeFloat;
        //当前测量值，空高,数据转换，float转换成可以显示的字符序列。
        ValueFloat = HART_DataToFloat(G_PublicVF2,FLOAT_T);
	HART_FloatToChar(ValueFloat,3);
	ShowDataBuffe[5] = '\0';		
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,85,0,NORMAL,ENGLISH);//测量距离
        
        
        //脉冲和导波的区分
        if(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0)
        {
          //信噪比
          SNR_CR_Float = G_PublicVC0[0];
          SNR_CR_Float = SNR_CR_Float*0.0129;
        }
        else
        {
          //控制频率
          SNR_CR_Float = HART_DataToFloat(G_PublicVF3,FLOAT_T);
        }

	HART_FloatToChar(SNR_CR_Float,2);					//回波信噪比或控制频率（导波）
	ShowDataBuffe[4] = '\0';
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,56,0,NORMAL,ENGLISH);//测量距离
	//最优波幅度换算
	AmplitudeFloat = G_PublicVC2[0]*0.0129;
	HART_FloatToChar(AmplitudeFloat,2);					//回波分辨率
	ShowDataBuffe[4] = '\0';
	MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,26,0,NORMAL,ENGLISH);//测量距离

	if(G_PublicVC1[0] >= 2)
	{
          //最优波位置
          TempP = G_PublicVC1[0]-2+LCDCURVESTARTCOLUMN;
          for(TempC = 0; TempC < 5; TempC++)
          {
            LCD_CS_Switch(TempC+TempP,6);
            TempD = LcdReadData()|TempData[TempC];
            NOP(1);
            LCD_CS_Switch(TempC+TempP,6);
            TempD = LcdReadData()|TempData[TempC];
            LCD_CS_Switch(TempC+TempP,6);
            LcdWriteData(TempD);
          }
	}
}
/*
//函数名称和参量和返回值类型。
void CurvePointLoad()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
加载曲线绘制的100个点，放置在显示数组中。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void CurvePointLoad(uchar *const ShowCurveData)
{
  uchar i = 0;
  
  for(i = 0;i < 100; i++)
  {
    if(i < 20)
    {
      ShowCurveData[i] = G_RadarCurvePoint1[i];
    }
    else if((i >= 20)&&(i < 40))
    {
      ShowCurveData[i] = G_RadarCurvePoint2[i-20];
    }
    else if((i >= 40)&&(i < 60))
    {
      ShowCurveData[i] = G_RadarCurvePoint3[i-40];
    }
    else if((i >= 60)&&(i < 80))
    {
      ShowCurveData[i] = G_RadarCurvePoint4[i-60];
    }
    else if((i >= 80)&&(i < 100))
    {
      ShowCurveData[i] = G_RadarCurvePoint5[i-80];
    }
  }
  
}
/*
//函数名称和参量和返回值类型。
void CurveNoZoomHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线不放大处理函数，将放大的曲线还原成量程低位加2.
*
* 关键备注：
* - 

  
* 未来提高:



*/
void CurveNoZoomHandle()
{
   float CurveXEndP;
   //加载曲线起始点信息
   if(G_IsCurveZoom == FALSE)
   {
     //根据量程计算曲线起始点数值
     CurveXEndP = MENU_DataToFloat(G_PV_LSL,FLOAT_T);
     if(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0)
     {
       //脉冲雷达+2
       CurveXEndP += 0.5;
     }
     else
     {
       //导波雷达+0.2
       CurveXEndP += 0.2;
     }
     //将起始点浮点数据转换成帧格式数组
     MENU_FloatToData(G_RadarCurveEndP,CurveXEndP,FLOAT_T);
     MENU_FloatToData(G_PublicVF1,0,FLOAT_T);
     G_Page_One_M = CurveXEndP/100;
     G_CurveLimitL = 0;
     G_CurveLimitH = 255;
     G_Curve_One_H = 255/LCDCURVEHIGH;
     G_IsCurveZoom = TRUE;
   }
}
/*
//函数名称和参量和返回值类型。
void FakeCurveGroupLoad()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
借用回波曲线界面发送虚假回波获取命令
*
* 关键备注：
* - 

  
* 未来提高:



*/

void FakeCurveGroupLoad()
{
  if(G_FakeCurveLoadCount < 5 )
  {
    CurveFakeNhlEndHandle();
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[0] = RADAR_PULSE_CURVE;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[1] = RADAR_CURVE_RANGE;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[2] = RADAR_FAKE_RANGE;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[3] = RADAR_CURVE_POINT1;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[4] = RADAR_CURVE_POINT2;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[5] = RADAR_CURVE_POINT2;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[6] = RADAR_CURVE_POINT2;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[7] = RADAR_CURVE_POINT5;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = 8;
    G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
  }
  /*else
  {
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[0] = RADAR_CURVE_RANGE;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[1] = RADAR_CURVE_POINT1;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[2] = RADAR_CURVE_POINT2;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[3] = RADAR_CURVE_POINT3;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[4] = RADAR_CURVE_POINT4;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[5] = RADAR_CURVE_POINT5;
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = 6;
  }*/
  
  G_HART_HandleFlag = HART_COMMON_COMMAND_HANDLE;
}
/*
//函数名称和参量和返回值类型。
void CurvePageShow()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线页面显示函数。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void CurvePageShow()
{
   const ItemDef* CurrentItemH;
   MENU_PageShowSwitch(FALSE);
   PageDef *PagePtr = NULL;
   
   //获取菜单树序号
   PagePtr = MENU_GetCurrentMenuPage();
   CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);
   MENU_ItemParamLoad(CurrentItemH);

    if(G_FakeCurveLoadCount >= 3)
    {
      //轮询获取曲线点阵
      CurvePointLoad(G_ShowCurveData);
      MENU_PageCommandGroupLoad(PagePtr);
    }
    else 
    {
      FakeCurveGroupLoad();
      G_ConnectWay = PagePtr->ConnectWay;
      //轮询获取曲线点阵
      CurvePointLoad(G_ShowFakeCurveData);
      G_FakeCurveLoadCount++;
    }
   CurveNoZoomHandle();
   DrawChart();
   DiplayCureXY();
   DisplayMeasureV_Amplitude();
   if(G_IsFakeCurveDisplay == FALSE)
   {
    DrawCurve(G_ShowFakeCurveData);
   }
   DrawCurve(G_ShowCurveData);
}
/*
//函数名称和参量和返回值类型。
void CurvePageHandle(KeyValueDef KeyMode);
* 变量范围:
KeyValueDef KeyMode:按键种类，区分是哪一个按键。
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* 返回值说明:void 
* 功能介绍:   
曲线操作界面处理函数，执行曲线界面与按键配合执行功能，
例如OK键可以切换到设置菜单。


*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurvePageHandle(KeyValueDef KeyMode)
{

  const ItemDef* CurrentItemH;
  PageDef *PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,G_CursorNumH);
  //以曲线终点-曲线起点，除以100，计算出水平放缩刻度单位
  G_Page_One_M = (MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T)-
                  MENU_DataToFloat(G_PublicVF1,FLOAT_T))/100;
  
  if(MENU_CurrentPageTypeGet() == CURVE_PAGE)
  {
     switch(KeyMode)
     {
        case LEFT:
                 MENU_PageNumSetHandle(PagePtr->PreviousOrNextPageNum);
                 MENU_PageTypeSetHandle(MENU_BAR);
                 G_CursorNumV = PagePtr->PreviousOrNextItemLine-1;  
                 G_FakeCurveLoadCount = 0;
                 MENU_PageShowSwitch(TRUE);
          break;
        case RIGHT:
                 if(G_IsFakeCurveDisplay == TRUE)
                 {
                    G_IsFakeCurveDisplay = FALSE;
                    G_IsFakeCurveUpdateFlag = FALSE;
                 }
                 else if(G_IsFakeCurveDisplay == FALSE)
                 {
                    G_IsFakeCurveDisplay = TRUE;
                    G_IsFakeCurveUpdateFlag = TRUE;
                    G_FakeCurveLoadCount = 0;
                 }
          break;
         case OK:
           //回波曲线界面切换处理
            MENU_GeneralItemLinkHandle(CurrentItemH);
            MENU_PageShowSwitch(TRUE);
            //将连接方式改为空闲，便于快速切换界面。
            G_ConnectWay = POLLING_STANDBY;
            //关闭HART操作，有利于快速从刷新界面中切换出去
            G_HART_HandleFlag = HART_STANDBY;
          break;
        default: break;
     }
  }
  else
  {
    //Page error
  }
}
/*
//函数名称和参量和返回值类型。
void	DrawHLine(uchar HPostion)
* 变量范围:
HPostion：竖线的起始横坐标。

* 返回值说明:void 
* 功能介绍:   
画曲线操作界面移动光标竖线函数
*
* 关键备注：
* - 

  
* 未来提高:

需要根据光标的移动范围进行变量范围判定。

*/
void	DrawHLine(uchar HPostion)
{
	uchar TempH;
	for(TempH = 2; TempH < 6; TempH++)
	{
                LCD_CS_Switch(HPostion,TempH);
		LcdWriteData(0xFF);
	}
}
/*
//函数名称和参量和返回值类型。
void	DrawVMoveLine(uchar VPostion)
* 变量范围:
VPostion：横线的起始纵坐标。

* 返回值说明:void 
* 功能介绍:   
画曲线操作界面移动光标横线函数
*
* 关键备注：
* - 

  
* 未来提高:

需要根据光标的移动范围进行变量范围判定。

*/
void	DrawVMoveLine(uchar VPostion)
{
	uchar TempH,TempDot,TempData,TempPage;
	TempPage = VPostion/8;
	TempDot = 7-VPostion%8;
	TempData = 0x80;
	TempDot = TempData>>TempDot;
	//LcdSetPage(TempPage);
	for(TempH = 21; TempH < 121; TempH++)
	{
		LCD_CS_Switch(TempH,TempPage);
		TempData = LcdReadData()|TempDot;
                NOP(1);
                LCD_CS_Switch(TempH,TempPage);
		TempData = LcdReadData()|TempDot;

		LCD_CS_Switch(TempH,TempPage);
		LcdWriteData(TempData);
	}
}
/*
//函数名称和参量和返回值类型。
void CurveOperationPageShow()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
曲线操作页面显示函数，设定曲线参数时，可通过当前函数设定。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void CurveOperationPageShow()
{
   const ItemDef* CurrentItemH;
   uchar ZoomX[ZOOM_BUFF_SIZE] = {0};
   uchar ZoomY[ZOOM_BUFF_SIZE] = {0};
   MENU_PageShowSwitch(FALSE);
   PageDef *PagePtr = NULL;
   
   //获取菜单树序号
   PagePtr = MENU_GetCurrentMenuPage();
   CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);
   MENU_ItemParamLoad(CurrentItemH);
   
   MENU_PageCommandGroupLoad(PagePtr);
   DrawChart();
   DiplayCureXY();
   if(G_VariableSingleDisFlag == FALSE)
   {
    DisplayMeasureV_Amplitude();
    G_VariableSingleDisFlag = TRUE;
   }
   DrawCurve(G_ShowCurveData);
   //轮询获取曲线点阵
   CurvePointLoad(G_ShowCurveData);
   if((PagePtr->AdditionalInfo == CURSOR_HANDLE_NEW)||
            (PagePtr->AdditionalInfo == CURSOR_HANDLE_MHIGH)||
              (PagePtr->AdditionalInfo == CURSOR_HANDLE_MLOW)||
                (PagePtr->AdditionalInfo == CURSOR_HANDLE_MPART)||
                  (PagePtr->AdditionalInfo == CURSOR_HANDLE_DZH)||
                    (PagePtr->AdditionalInfo == CURSOR_HANDLE_DZL)||
                        (PagePtr->AdditionalInfo == CURSOR_HANDLE_V))
   {
       if(((G_ZoomX_Flag >= 1)&&(G_ZoomY_Flag == 0))
          &&(PagePtr->AdditionalInfo != CURSOR_HANDLE_DZL))
       {
         //设置光标X轴的起始位置
         ZoomX[0] = G_ZoomX[0];
         //画移动光标竖线。
         DrawHLine(ZoomX[0]);
         //显示光标位置变量数值，曲线图中的变量。
       }
       if(((G_ZoomX_Flag == 2)&&(G_ZoomY_Flag == 0))
          &&((PagePtr->AdditionalInfo == CURSOR_HANDLE_V)
             ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_MPART)
               ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_DZL)))
       {
         //设置光标X轴的起始位置
         ZoomX[1] = G_ZoomX[1];
         //画移动光标竖线。
         DrawHLine(ZoomX[1]);
       }
     if((PagePtr->AdditionalInfo == CURSOR_HANDLE_DZL)
        ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_DZH))
     {
       //盲区刻度显示。
       CurveDeadZoneSpanDisplay();
     }
     else
     {
       //光标移动刻度显示。
       CurveZoomSart_End();
     }
   }
   else if((PagePtr->AdditionalInfo == CURSOR_HANDLE_H)
           ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_SGT))
   {
     if((G_ZoomX_Flag == 0)&&(G_ZoomY_Flag >= 1))
     {
       //设置光标Y轴的起始位置
       ZoomY[0] = G_ZoomY[0];
       //画移动光标横线。
       DrawVMoveLine(ZoomY[0]);
       //显示光标位置变量数值，曲线图中的变量。
     }
     if((G_ZoomX_Flag == 0)&&(G_ZoomY_Flag == 2))
     {
       //设置光标Y轴的起始位置
       ZoomY[1] = G_ZoomY[1];
       //画移动光标横线。
       DrawVMoveLine(ZoomY[1]);
       //显示光标位置变量数值，曲线图中的变量。
     }
   }
}
/*
//函数名称和参量和返回值类型。
void CurveBackLinkHandle(const PageDef *CurrentPage)
* 变量范围:

CurrentPage:返回界面信息

* 返回值说明:void 
* 功能介绍:   

根据页面信息返回上一级页面
*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveBackLinkHandle(const PageDef *CurrentPage)
{
  /*返回上一级菜单操作*/
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  G_CursorNumV = CurrentPage->PreviousOrNextItemLine-1;     
  G_ZoomY_Flag = 0;
  G_ZoomX_Flag = 0;
  G_VariableSingleDisFlag = FALSE;
  MENU_PageShowSwitch(TRUE);
}
/*
//函数名称和参量和返回值类型。
void CurveSetLinkHandle(const PageDef *CurrentPage)
* 变量范围:



* 返回值说明:void 
* 功能介绍:   
曲线界面确认键连接函数。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveSetLinkHandle(const ItemDef* CurrentItemH)
{
  /*返回上一级菜单操作*/
  MENU_PageNumSetHandle(CurrentItemH->NextLayerNum);
  MENU_PageTypeSetHandle(CurrentItemH->NextLayerType);
  G_ZoomY_Flag = 0;
  G_ZoomX_Flag = 0;
  G_VariableSingleDisFlag = FALSE;
  MENU_PageShowSwitch(TRUE);
}
/*
//函数名称和参量和返回值类型。
void CurveHighDeadZoneHandle(const ItemDef* CurrentItemH)
* 变量范围:
CurrentItemH:菜单项信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
高位盲区曲线处理函数，
当高位盲区曲线光标移动到准确位置，选定OK键，即执行本函数，本函数
功能是曲线位置转换成数据，赋值给对应的高位盲区变量。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveHighDeadZoneHandle(const ItemDef* CurrentItemH)
{
  float DeadZoneH = 0;
  float CurveXStartP = 0;
  
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  DeadZoneH = (G_ZoomX[0]-21)*G_Page_One_M+CurveXStartP;
  MENU_FloatToData(G_PV_SnsrLSL,DeadZoneH,FLOAT_T); 
  G_ZoomX_Flag = 0;
  CurveSetLinkHandle(CurrentItemH);
}
/*
//函数名称和参量和返回值类型。
void CurveLowDeadZoneHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
低位盲区曲线处理函数，
当高位盲区曲线光标移动到准确位置，选定OK键，即执行本函数，本函数
功能是曲线位置转换成数据，赋值给对应的低位盲区变量。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveLowDeadZoneHandle(const ItemDef* CurrentItemH)
{
  float DeadZoneL = 0;
  float CurveXStartP = 0;
  
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  DeadZoneL = (G_ZoomX[1]-21)*G_Page_One_M+CurveXStartP;
  MENU_FloatToData(G_PV_SnsrUSL,DeadZoneL,FLOAT_T); 
  G_ZoomX_Flag = 0;
  CurveSetLinkHandle(CurrentItemH);
}
/*
//函数名称和参量和返回值类型。
void CurveFakePartHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
虚假回波曲线局部设置，
在两个光标之间建立虚假回波。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveFakePartHandle(const ItemDef* CurrentItemH)
{
  float CurveXStartP,CurveXEndP;
  //将曲线起始点变量转换成float类型数据，方便计算
  CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  //重新计算光标移动后的曲线终点
  //这里先算终点是因为CurveXStartP变量此时没有因为参与计算而改变变量值
  CurveXEndP = G_Page_One_M*(G_ZoomX[1]-21)+CurveXStartP;
  //重新计算光标移动后的曲线起点
  CurveXStartP = G_Page_One_M*(G_ZoomX[0]-21)+CurveXStartP;
  //将起始点浮点数据转换成帧格式数组
  MENU_FloatToData(G_PublicVF5,CurveXEndP,FLOAT_T);
  MENU_FloatToData(G_PublicVF4,CurveXStartP,FLOAT_T);
  CurveSetLinkHandle(CurrentItemH);
}
/*
//函数名称和参量和返回值类型。
void CurveFakeNhlHandle(const PageDef *CurrentPage,const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
虚假回波曲线新建，高位更改，低位更改设置，
曲线起点到光标之间建立虚假回波。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveFakeNhlHandle(const PageDef *CurrentPage,const ItemDef* CurrentItemH)
{
  float CurveXStartP,CurveXEndP;
  uchar* StartPointPtr = NULL;
  uchar NewFakeStartArr[] = {0x42,0x8E,0x00,0x00};
  uchar HighFakeStartArr[] = {0x42,0x90,0x00,0x00};
  uchar LowFakeStartArr[] = {0x42,0x92,0x00,0x00};
  if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_NEW)
  {
    StartPointPtr = NewFakeStartArr;
  }
  else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MHIGH)
  {
    StartPointPtr = HighFakeStartArr;
  }
  else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MLOW)
  {
    StartPointPtr = LowFakeStartArr;
  }
  //计算获取虚假回波曲线起始点数据，以回波曲线起点为起点
  CurveXStartP = MENU_DataToFloat(StartPointPtr,FLOAT_T);
  MENU_FloatToData(G_PublicVF4,CurveXStartP,FLOAT_T);
  //重新计算光标移动后的曲线起点
  CurveXEndP = G_Page_One_M*(G_ZoomX[0]-21);
  //将起始点浮点数据转换成帧格式数组
  MENU_FloatToData(G_PublicVF5,CurveXEndP,FLOAT_T); 
  CurveSetLinkHandle(CurrentItemH); 
}
/*
//函数名称和参量和返回值类型。
void CurveFakeNhlEndHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
虚假回波曲线新建，高位更改，低位更改后续处理函数，
向雷达设备发送虚假回波指令。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveFakeNhlEndHandle()
{
  MENU_FloatToData(G_PublicVF4,0,FLOAT_T);
  MENU_FloatToData(G_PublicVF5,0,FLOAT_T); 
  MENU_FloatToData(G_PublicVF16,0,FLOAT_T); 
}
/*
//函数名称和参量和返回值类型。
void CurveXZoomHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
X轴放大变量设置函数，
选定OK键，将光标选定的范围转换成数据，赋值给曲线范围变量。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveXZoomHandle(const PageDef *CurrentPage)
{
  float CurveXStartP,CurveXEndP;
  //将曲线起始点变量转换成float类型数据，方便计算
  CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  //重新计算光标移动后的曲线起点
  CurveXStartP = G_Page_One_M*(G_ZoomX[0]-21)+CurveXStartP;
  //重新计算光标移动后的曲线终点
  CurveXEndP = G_Page_One_M*(G_ZoomX[1]-21)+CurveXStartP;
  //将起始点浮点数据转换成帧格式数组
  MENU_FloatToData(G_RadarCurveEndP,CurveXEndP,FLOAT_T);
  MENU_FloatToData(G_PublicVF1,CurveXStartP,FLOAT_T);
  //重新计算横坐标缩放比。
  G_Page_One_M = (CurveXEndP-CurveXStartP)/100;
  //曲线界面经过放大处理标志。
  G_IsCurveZoom = TRUE;
  CurveBackLinkHandle(CurrentPage);
}
/*
//函数名称和参量和返回值类型。
void CurveYZoomHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
Y轴放大变量设置函数，
选定OK键，将光标选定的范围转换成数据，赋值给曲线范围变量。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveYZoomHandle(const PageDef *CurrentPage)
{
  uchar CurveLimitTemp = 0;
  G_CurveLimitL = 
    (uchar)((LCDCURVELLIMIT-G_ZoomY[0])*G_Curve_One_H)+G_CurveLimitL;
  G_CurveLimitH = 
    (uchar)((LCDCURVELLIMIT-G_ZoomY[1])*G_Curve_One_H)+G_CurveLimitL;
  if(G_CurveLimitL  >= G_CurveLimitH)
  {
    CurveLimitTemp = G_CurveLimitL;
    G_CurveLimitL = G_CurveLimitH;
    G_CurveLimitH = CurveLimitTemp;
  }
  G_Curve_One_H = (float)(G_CurveLimitH-G_CurveLimitL);
  G_Curve_One_H /= LCDCURVEHIGH;
  //曲线界面经过放大处理标志。
  G_IsCurveZoom = TRUE;
  CurveBackLinkHandle(CurrentPage);
}
/*
//函数名称和参量和返回值类型。
void CurveGeneralHandle()
* 变量范围:

* 返回值说明:void 
* 功能介绍:   
通用光标处理函数，除了特殊光标处理以外，通过本函数处理
，包括XY轴放大，虚假回波局部更改的第一条光标处理
*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveGeneralHandle()
{
  if(G_ZoomX_Flag == 1)
  {
    G_ZoomX_Flag = 2;
    G_ZoomX[1] = G_ZoomX[0]+30;
  }
  if(G_ZoomY_Flag == 1)
  {
    G_ZoomY_Flag = 2;
    G_ZoomY[1] = G_ZoomY[0]-8;
  }
}
/*
//函数名称和参量和返回值类型。
void CurveKeyDownHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
光标递减移动处理函数，按键下触发后，对光标的处理。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveKeyDownHandle(const PageDef *CurrentPage)
{
  uchar TempC = 0;
  if(G_ZoomY_Flag == 0)
  {
        if(G_ZoomX_Flag > 0)
        {
                if(G_ZoomX_Flag == 2)
                {
                  TempC = 121;
                }
                else 
                {
                  if((CurrentPage->AdditionalInfo == CURSOR_HANDLE_NEW)
                    ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MHIGH)
                        ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MLOW))
                  {
                    TempC = 120;
                  }
                  else
                  {
                    TempC = 90;
                  }
                }
                //光标向右移动
                G_ZoomX[G_ZoomX_Flag-1]++;
                //不可以让光标移动出曲线框架
                if(G_ZoomX[G_ZoomX_Flag-1] > TempC)
                        G_ZoomX[G_ZoomX_Flag-1] = TempC;
        }
  }
  else if(G_ZoomY_Flag >= 1)
  {
          if(G_ZoomY_Flag == 2)
          {
                  TempC = G_ZoomY[0]-3;
          }
          else
                  TempC = 53;
          if(G_ZoomY[G_ZoomY_Flag-1] == TempC)
                  G_ZoomY[G_ZoomY_Flag-1] = TempC+1;
          //Y轴放大的上限是54，曲线图最下端
          if(G_ZoomY[G_ZoomY_Flag-1] > TempC)
                  G_ZoomY[G_ZoomY_Flag-1] = TempC;
          G_ZoomY[G_ZoomY_Flag-1]++;
  }
}
/*
//函数名称和参量和返回值类型。
void CurveKeyUpHandle(const PageDef *CurrentPage)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
光标递减增处理函数，按键上触发后，对光标的处理。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveKeyUpHandle(const PageDef *CurrentPage)
{
  uchar TempC = 0;
  if(G_ZoomX_Flag == 0)
  {
    if((CurrentPage->AdditionalInfo == CURSOR_HANDLE_H)
       ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_SGT))
    {
      if(G_ZoomY_Flag == 2)
      {
              TempC = 7;
              //DrawVMoveLine(G_ZoomY[0]);
      }
      else
              TempC = 9;
      if(G_ZoomY[G_ZoomY_Flag-1] <= TempC)
              G_ZoomY[G_ZoomY_Flag-1] = TempC+1;
      G_ZoomY[G_ZoomY_Flag-1]--;
    }
  }
  else
  {
      if(G_ZoomX_Flag == 2)
      {
              TempC = G_ZoomX[0]+8;
      }
      else
              TempC = 21;
      if(G_ZoomX[G_ZoomX_Flag-1] == TempC)
              G_ZoomX[G_ZoomX_Flag-1] = TempC+1;
      G_ZoomX[G_ZoomX_Flag-1]--;
  }
}
/*
//函数名称和参量和返回值类型。
void CurveThresholdHandle(const ItemDef* CurrentItemH)
* 变量范围:
CurrentPage:页面信息，在此用来完成页面切换。
* 返回值说明:void 
* 功能介绍:   
信号阈值确定处理函数，将光标位置转换为数据，保存到信号阈值变量中。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 

void CurveThresholdHandle(const ItemDef* CurrentItemH)
{  
  G_PublicVC11[0] = (uchar)((LCDCURVELLIMIT - G_ZoomY[0])*G_Curve_One_H)+G_CurveLimitL;
  G_ZoomY_Flag = 0;
  CurveSetLinkHandle(CurrentItemH);
}
/*
//函数名称和参量和返回值类型。
void CurveKeyOkHandle(CurrentPage)
* 变量范围:

* 返回值说明:void 
* 功能介绍:   
光标确定处理函数，按键确定触发后，对光标的处理。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveKeyOkHandle(const PageDef *CurrentPage,const ItemDef* CurrentItemH)
{
  if((G_ZoomX_Flag >= 2)||(G_ZoomY_Flag >= 2))
  {
    //X轴放大处理
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_V)
    {
      CurveXZoomHandle(CurrentPage);
      G_VariableSingleDisFlag = FALSE;
    }
    //Y轴放大处理
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_H)
    {
      CurveYZoomHandle(CurrentPage);
    }
    //局部虚假回波建立处理
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MPART)
    {
      CurveFakePartHandle(CurrentItemH);
      G_VariableSingleDisFlag = FALSE;
    }//低位盲区确定处理
    else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_DZL)
    {
      CurveLowDeadZoneHandle(CurrentItemH);
    }
  }
  else if((G_ZoomX_Flag == 1)||(G_ZoomY_Flag == 1))
  {
    //虚假回波设定，新建，更改高位，更改低位处理
    if((G_ZoomX_Flag == 1)&&(G_ZoomY_Flag == 0)
       &&((CurrentPage->AdditionalInfo == CURSOR_HANDLE_NEW)
        ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MHIGH)
          ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MLOW)))
    {
      CurveFakeNhlHandle(CurrentPage,CurrentItemH);
    }//高位盲区确定处理
    else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_DZH)
    {
      CurveHighDeadZoneHandle(CurrentItemH);
    }//信号阈值确定处理
    else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_SGT)
    {
      CurveThresholdHandle(CurrentItemH);
    }
    else 
    {
      CurveGeneralHandle();
    }
  }
}
/*
//函数名称和参量和返回值类型。
void CurveOperationPageHandle(KeyValueDef KeyMode);
* 变量范围:
KeyValueDef KeyMode:按键种类，区分是哪一个按键。
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* 返回值说明:void 
* 功能介绍:   
曲线操作界面处理函数，执行曲线界面与按键配合执行功能，
例如界面返回，光标移动等功能。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void CurveOperationPageHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemH;
  PageDef *PagePtr = NULL;
  
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);

  
  if(MENU_CurrentPageTypeGet() == CURVE_OPT_PAGE)
  {
     switch(KeyMode)
     {
        case LEFT:
          CurveBackLinkHandle(PagePtr);
          break;
        case DOWN:
          CurveKeyDownHandle(PagePtr);
          break;
        case UP:
          CurveKeyUpHandle(PagePtr);
          break;
        case OK:
          CurveKeyOkHandle(PagePtr,CurrentItemH);
          CurveFakeEchoReloadFlagHandle();
        default: break;
     }
  }
  else
  {
    //Page error
  }
}
/*
//函数名称和参量和返回值类型。
void CursorParamInit(ParamTableDef Flag)
* 变量范围:


* 返回值说明:void 
* 功能介绍:  
光标参数加载函数，
曲线界面光标需要设定初始坐标，以及其他的起始条件，需要通过本函数进行参数加载。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void CursorParamInit(ParamTableDef Flag)
{
  float DeadZoneH = 0;
  float DeadZoneL = 0;
  float CurveXStartP = 0;
  float CurveXEndP = 0;
  switch(Flag)
  {
    case CURSOR_MHIGH:
      G_ZoomX[0] = 60;
      G_ZoomY[0] = 0;
      G_ZoomX_Flag = START_CURSOR;
      G_ZoomY_Flag = 0;
      break;
    case CURSOR_MLOW:
      G_ZoomX[0] = 90;
      G_ZoomY[0] = 0;
      G_ZoomX_Flag = START_CURSOR;
      G_ZoomY_Flag = 0;
      break;
    case CURSOR_MPART:
    case CURSOR_NEW:
    case CURSORX_PARAM:
      G_ZoomX[0] = 21;
      G_ZoomY[0] = 0;
      G_ZoomX_Flag = START_CURSOR;
      G_ZoomY_Flag = 0;
      break;
    case CURSORY_PARAM:
      G_ZoomX[0] = 0;
      G_ZoomY[0] = 54;
      G_ZoomX_Flag = 0;
      G_ZoomY_Flag = START_CURSOR;
      break;
    case CURSOR_DZH:
      DeadZoneH = MENU_DataToFloat(G_PV_SnsrLSL,FLOAT_T);
      CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
      CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
      if((DeadZoneH >= CurveXStartP)&&(DeadZoneH <= CurveXEndP))
      {
        G_ZoomX[0] = (uchar)((DeadZoneH - CurveXStartP)/G_Page_One_M+21);
      }
      else
      {
        G_ZoomX[0] = 21;
      }
      G_ZoomX_Flag = START_CURSOR;
      break;
    case CURSOR_DZL:
      DeadZoneL = MENU_DataToFloat(G_PV_SnsrUSL,FLOAT_T);
      CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
      CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
      if((DeadZoneL >= CurveXStartP)&&(DeadZoneL <= CurveXEndP))
      {
        G_ZoomX[1] = (uchar)((DeadZoneL - CurveXStartP)/G_Page_One_M+21);
      }
      else
      {
        G_ZoomX[1] = 120;
      }
      G_ZoomX_Flag = END_CURSOR;
      break;
    case CURSOR_SGT:
      G_ZoomY[0] = 
        LCDCURVELLIMIT-(uchar)((G_PublicVC11[0]-G_CurveLimitL)/G_Curve_One_H);
      G_ZoomY_Flag = START_CURSOR;
      G_ZoomX_Flag = 0;
      break;
    default:
      G_ZoomX[0] = 21;
      G_ZoomY[0] = 55;
      G_ZoomX_Flag = 0;
      G_ZoomY_Flag = 0;
      break;
  }
}
/*
//函数名称和参量和返回值类型。
void	CurveZoomSart_End(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:  
曲线放大部分起始点变量数据显示处理函数，
将光标移动的步数转换成浮点型数据显示在曲线图对应位置。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	CurveZoomSart_End(void)
{
	float	ValueFloat,CurveXStartP;
        CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
	if(G_ZoomX_Flag == 1)
	{
          ValueFloat = (G_ZoomX[0]-21)*G_Page_One_M+CurveXStartP;
          HART_FloatToChar(ValueFloat,3);
          ShowDataBuffe[5] = '\0';		
          MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,25,0,NORMAL,ENGLISH);
	}
	if(G_ZoomX_Flag == 2)
	{
          ValueFloat = (G_ZoomX[1]-21)*G_Page_One_M+CurveXStartP;
          HART_FloatToChar(ValueFloat,3);
          ShowDataBuffe[5] = '\0';		
          MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,85,0,NORMAL,ENGLISH);
     	}
}
/*
//函数名称和参量和返回值类型。
void	CurveDeadZoneSpanDisplay(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:  
盲区刻度显示函数，将当前高低位盲区的数值显示在曲线界面。
*
* 关键备注：
* - 

  
* 未来提高:


*/
void	CurveDeadZoneSpanDisplay(void)
{
  float ValueFloat;
  ValueFloat = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  ValueFloat = (G_ZoomX[1]-21)*G_Page_One_M+ValueFloat;
  HART_FloatToChar(ValueFloat,3);
  ShowDataBuffe[5] = '\0';
  MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,85,0,NORMAL,ENGLISH);
  ValueFloat = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  ValueFloat = (G_ZoomX[0]-21)*G_Page_One_M+ValueFloat;
  HART_FloatToChar(ValueFloat,3);
  ShowDataBuffe[5] = '\0';
  MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,25,0,NORMAL,ENGLISH);
}
/*
//函数名称和参量和返回值类型。
void CurveFakeEchoReloadFlagHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:  

*
* 关键备注：
* - 

  
* 未来提高:


*/
void CurveFakeEchoReloadFlagHandle()
{  
  //如果虚假回波设置发生更改，需要在此处对虚假回波更新标志进行重置
  G_IsFakeCurveUpdateFlag = TRUE;
  G_IsFakeCurveDisplay = TRUE;
  G_FakeCurveLoadCount = 0;
}

