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
//������ʾ��Χ����
uchar G_CurveLimitH = 255;
//������ʾ��Χ����
uchar G_CurveLimitL = 0;
//Y�����ű�������
float G_Curve_One_H = 5.4;
//X�����ű�������
float G_Page_One_M;
uchar ShowDataBuffe[20] = {0};
uchar G_ShowCurveData[100];
uchar G_ShowFakeCurveData[100];
uchar DecimalP = 0;
//��ǰ��ʾ�����Ƿ��ڷŴ�״̬
bool8 G_IsCurveZoom = FALSE;
//
bool8 G_VariableSingleDisFlag = FALSE;
//��ٻز����±�־
bool8 G_IsFakeCurveUpdateFlag = FALSE;
//��ٻز����ؼ���
uchar G_FakeCurveLoadCount = 0;
//��ٻز���ʾ���Ʊ�־
bool8 G_IsFakeCurveDisplay = FALSE;

//�������߲�����������������
uchar G_ZoomX[ZOOM_BUFF_SIZE] = {0};
uchar G_ZoomY[ZOOM_BUFF_SIZE] = {0};
//�������߲���������ݹ�괦���־����
uchar G_ZoomX_Flag = 0;
uchar G_ZoomY_Flag = 0;
/*
//�������ƺͲ����ͷ���ֵ���͡�
void	DrawChart(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
���߱����ƺ�����������ʾ��ʵ�ߺ����߱���
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void	DrawChart(void)
{
	unsigned char TempC,TempL,TempD;
        bool8 ClearFlag = FALSE;
        //����
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
			LcdWriteData(0);		//������������Ա�ˢ������
		}
	}
 
        //���߽���
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
//�������ƺͲ����ͷ���ֵ���͡�
void	DiplayCureXY(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����X���Y��༭�������̶���ʾ
*
* �ؼ���ע��
* - 

  
* δ�����:



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
                  //�������ᵼ�����°�����
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
//�������ƺͲ����ͷ���ֵ���͡�
void	DrawCurve()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
���߻��ƺ�������100�����ߵ㡣
*
* �ؼ���ע��
* - 

  
* δ�����:



*/

void	DrawCurve(uchar *ShowCurveData)
{
	uchar TempC,PreByte,PreDot,CurrentDot,CurrentByte,TempData,InitDotValure;
	float TempF;
	PreDot = 1;
        
	for(TempC = 0; TempC < 100; TempC++)
	{
          //��������ʾ��Χ�ĵ���Ҫ��������ʾ��Χ�ڡ�
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
                //��������������
		CurrentDot = TempData%8;
		CurrentDot = 7-CurrentDot;
                //������������
		CurrentByte = 6-TempData/8;
		
		if(TempC != 0)
		{
                  //��ͬһ��
                  if(CurrentByte == PreByte)
                  {
                          InitDotValure = 0xFF;                    
                          TempData = 0xFF;
                          //������λ������ʷ����бȽ�
                          //��ʷ���ڸߴ�����������ݽ�����λ���㣬���ڽ���ʷ��͵�ǰ���������
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
                          //�õ���������������ӵ�����
                          TempData = InitDotValure&TempData;
                  }
                  //��ǰ����������ʷ���������£�
                  else	if(CurrentByte > PreByte)
                  {
                          InitDotValure = 0xFF;                    
                          InitDotValure <<= PreDot;
                          
                          //���ö�ȡλ������
                          //��ȡ������Ҫ�����飬��Ϊ��һ��Һ����Ҫ����ʾ��������������Ĵ������ڶ���Ż�������ȡ
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
                          //��ȡ������Ҫ�����飬��Ϊ��һ��Һ����Ҫ����ʾ��������������Ĵ������ڶ���Ż�������ȡ
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
                  //��ȡ������Ҫ�����飬��Ϊ��һ��Һ����Ҫ����ʾ��������������Ĵ������ڶ���Ż�������ȡ
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  InitDotValure = LcdReadData();
                  NOP(1);
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  InitDotValure = LcdReadData();

                  TempData = TempData|InitDotValure;
                  LCD_CS_Switch(TempC+21,CurrentByte);
                  LcdWriteData(TempData);
		}
                //��ȡ������Ҫ�����飬��Ϊ��һ��Һ����Ҫ����ʾ��������������Ĵ������ڶ���Ż�������ȡ
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
//�������ƺͲ����ͷ���ֵ���͡�
void	DrawCurve()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ֵ��ʾ��������������ֵ������Ȼ����Ƶ�ʣ���ֵ���Լ�����λ�á�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void	DisplayMeasureV_Amplitude(void)
{
	uchar TempC,TempP,TempD,TempData[5] = {0xC0,0xE0,0xF0,0xE0,0xC0};
	float	SNR_CR_Float,ValueFloat,AmplitudeFloat;
        //��ǰ����ֵ���ո�,����ת����floatת���ɿ�����ʾ���ַ����С�
        ValueFloat = HART_DataToFloat(G_PublicVF2,FLOAT_T);
	HART_FloatToChar(ValueFloat,3);
	ShowDataBuffe[5] = '\0';		
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,85,0,NORMAL,ENGLISH);//��������
        
        
        //����͵���������
        if(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0)
        {
          //�����
          SNR_CR_Float = G_PublicVC0[0];
          SNR_CR_Float = SNR_CR_Float*0.0129;
        }
        else
        {
          //����Ƶ��
          SNR_CR_Float = HART_DataToFloat(G_PublicVF3,FLOAT_T);
        }

	HART_FloatToChar(SNR_CR_Float,2);					//�ز�����Ȼ����Ƶ�ʣ�������
	ShowDataBuffe[4] = '\0';
        MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,56,0,NORMAL,ENGLISH);//��������
	//���Ų����Ȼ���
	AmplitudeFloat = G_PublicVC2[0]*0.0129;
	HART_FloatToChar(AmplitudeFloat,2);					//�ز��ֱ���
	ShowDataBuffe[4] = '\0';
	MENU_DynamicStringShow(ASCII_5X8,ShowDataBuffe,26,0,NORMAL,ENGLISH);//��������

	if(G_PublicVC1[0] >= 2)
	{
          //���Ų�λ��
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
//�������ƺͲ����ͷ���ֵ���͡�
void CurvePointLoad()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�������߻��Ƶ�100���㣬��������ʾ�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveNoZoomHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
���߲��Ŵ����������Ŵ�����߻�ԭ�����̵�λ��2.
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void CurveNoZoomHandle()
{
   float CurveXEndP;
   //����������ʼ����Ϣ
   if(G_IsCurveZoom == FALSE)
   {
     //�������̼���������ʼ����ֵ
     CurveXEndP = MENU_DataToFloat(G_PV_LSL,FLOAT_T);
     if(HART_DataToFloat(G_PublicVF0,FLOAT_T) == 0)
     {
       //�����״�+2
       CurveXEndP += 0.5;
     }
     else
     {
       //�����״�+0.2
       CurveXEndP += 0.2;
     }
     //����ʼ�㸡������ת����֡��ʽ����
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
//�������ƺͲ����ͷ���ֵ���͡�
void FakeCurveGroupLoad()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
���ûز����߽��淢����ٻز���ȡ����
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void CurvePageShow()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
����ҳ����ʾ������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void CurvePageShow()
{
   const ItemDef* CurrentItemH;
   MENU_PageShowSwitch(FALSE);
   PageDef *PagePtr = NULL;
   
   //��ȡ�˵������
   PagePtr = MENU_GetCurrentMenuPage();
   CurrentItemH = MENU_GetHorizontalItem(PagePtr,0);
   MENU_ItemParamLoad(CurrentItemH);

    if(G_FakeCurveLoadCount >= 3)
    {
      //��ѯ��ȡ���ߵ���
      CurvePointLoad(G_ShowCurveData);
      MENU_PageCommandGroupLoad(PagePtr);
    }
    else 
    {
      FakeCurveGroupLoad();
      G_ConnectWay = PagePtr->ConnectWay;
      //��ѯ��ȡ���ߵ���
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
//�������ƺͲ����ͷ���ֵ���͡�
void CurvePageHandle(KeyValueDef KeyMode);
* ������Χ:
KeyValueDef KeyMode:�������࣬��������һ��������
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* ����ֵ˵��:void 
* ���ܽ���:   
���߲������洦������ִ�����߽����밴�����ִ�й��ܣ�
����OK�������л������ò˵���


*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurvePageHandle(KeyValueDef KeyMode)
{

  const ItemDef* CurrentItemH;
  PageDef *PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,G_CursorNumH);
  //�������յ�-������㣬����100�������ˮƽ�����̶ȵ�λ
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
           //�ز����߽����л�����
            MENU_GeneralItemLinkHandle(CurrentItemH);
            MENU_PageShowSwitch(TRUE);
            //�����ӷ�ʽ��Ϊ���У����ڿ����л����档
            G_ConnectWay = POLLING_STANDBY;
            //�ر�HART�����������ڿ��ٴ�ˢ�½������л���ȥ
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
//�������ƺͲ����ͷ���ֵ���͡�
void	DrawHLine(uchar HPostion)
* ������Χ:
HPostion�����ߵ���ʼ�����ꡣ

* ����ֵ˵��:void 
* ���ܽ���:   
�����߲��������ƶ�������ߺ���
*
* �ؼ���ע��
* - 

  
* δ�����:

��Ҫ���ݹ����ƶ���Χ���б�����Χ�ж���

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
//�������ƺͲ����ͷ���ֵ���͡�
void	DrawVMoveLine(uchar VPostion)
* ������Χ:
VPostion�����ߵ���ʼ�����ꡣ

* ����ֵ˵��:void 
* ���ܽ���:   
�����߲��������ƶ������ߺ���
*
* �ؼ���ע��
* - 

  
* δ�����:

��Ҫ���ݹ����ƶ���Χ���б�����Χ�ж���

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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveOperationPageShow()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
���߲���ҳ����ʾ�������趨���߲���ʱ����ͨ����ǰ�����趨��
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void CurveOperationPageShow()
{
   const ItemDef* CurrentItemH;
   uchar ZoomX[ZOOM_BUFF_SIZE] = {0};
   uchar ZoomY[ZOOM_BUFF_SIZE] = {0};
   MENU_PageShowSwitch(FALSE);
   PageDef *PagePtr = NULL;
   
   //��ȡ�˵������
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
   //��ѯ��ȡ���ߵ���
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
         //���ù��X�����ʼλ��
         ZoomX[0] = G_ZoomX[0];
         //���ƶ�������ߡ�
         DrawHLine(ZoomX[0]);
         //��ʾ���λ�ñ�����ֵ������ͼ�еı�����
       }
       if(((G_ZoomX_Flag == 2)&&(G_ZoomY_Flag == 0))
          &&((PagePtr->AdditionalInfo == CURSOR_HANDLE_V)
             ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_MPART)
               ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_DZL)))
       {
         //���ù��X�����ʼλ��
         ZoomX[1] = G_ZoomX[1];
         //���ƶ�������ߡ�
         DrawHLine(ZoomX[1]);
       }
     if((PagePtr->AdditionalInfo == CURSOR_HANDLE_DZL)
        ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_DZH))
     {
       //ä���̶���ʾ��
       CurveDeadZoneSpanDisplay();
     }
     else
     {
       //����ƶ��̶���ʾ��
       CurveZoomSart_End();
     }
   }
   else if((PagePtr->AdditionalInfo == CURSOR_HANDLE_H)
           ||(PagePtr->AdditionalInfo == CURSOR_HANDLE_SGT))
   {
     if((G_ZoomX_Flag == 0)&&(G_ZoomY_Flag >= 1))
     {
       //���ù��Y�����ʼλ��
       ZoomY[0] = G_ZoomY[0];
       //���ƶ������ߡ�
       DrawVMoveLine(ZoomY[0]);
       //��ʾ���λ�ñ�����ֵ������ͼ�еı�����
     }
     if((G_ZoomX_Flag == 0)&&(G_ZoomY_Flag == 2))
     {
       //���ù��Y�����ʼλ��
       ZoomY[1] = G_ZoomY[1];
       //���ƶ������ߡ�
       DrawVMoveLine(ZoomY[1]);
       //��ʾ���λ�ñ�����ֵ������ͼ�еı�����
     }
   }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveBackLinkHandle(const PageDef *CurrentPage)
* ������Χ:

CurrentPage:���ؽ�����Ϣ

* ����ֵ˵��:void 
* ���ܽ���:   

����ҳ����Ϣ������һ��ҳ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveBackLinkHandle(const PageDef *CurrentPage)
{
  /*������һ���˵�����*/
  MENU_PageNumSetHandle(CurrentPage->PreviousOrNextPageNum);
  MENU_PageTypeSetHandle(CurrentPage->PreviousOrNextPageType);
  G_CursorNumV = CurrentPage->PreviousOrNextItemLine-1;     
  G_ZoomY_Flag = 0;
  G_ZoomX_Flag = 0;
  G_VariableSingleDisFlag = FALSE;
  MENU_PageShowSwitch(TRUE);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveSetLinkHandle(const PageDef *CurrentPage)
* ������Χ:



* ����ֵ˵��:void 
* ���ܽ���:   
���߽���ȷ�ϼ����Ӻ�����

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveSetLinkHandle(const ItemDef* CurrentItemH)
{
  /*������һ���˵�����*/
  MENU_PageNumSetHandle(CurrentItemH->NextLayerNum);
  MENU_PageTypeSetHandle(CurrentItemH->NextLayerType);
  G_ZoomY_Flag = 0;
  G_ZoomX_Flag = 0;
  G_VariableSingleDisFlag = FALSE;
  MENU_PageShowSwitch(TRUE);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveHighDeadZoneHandle(const ItemDef* CurrentItemH)
* ������Χ:
CurrentItemH:�˵�����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
��λä�����ߴ�������
����λä�����߹���ƶ���׼ȷλ�ã�ѡ��OK������ִ�б�������������
����������λ��ת�������ݣ���ֵ����Ӧ�ĸ�λä��������

*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveLowDeadZoneHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
��λä�����ߴ�������
����λä�����߹���ƶ���׼ȷλ�ã�ѡ��OK������ִ�б�������������
����������λ��ת�������ݣ���ֵ����Ӧ�ĵ�λä��������

*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveFakePartHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
��ٻز����߾ֲ����ã�
���������֮�佨����ٻز���

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveFakePartHandle(const ItemDef* CurrentItemH)
{
  float CurveXStartP,CurveXEndP;
  //��������ʼ�����ת����float�������ݣ��������
  CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  //���¼������ƶ���������յ�
  //���������յ�����ΪCurveXStartP������ʱû����Ϊ���������ı����ֵ
  CurveXEndP = G_Page_One_M*(G_ZoomX[1]-21)+CurveXStartP;
  //���¼������ƶ�����������
  CurveXStartP = G_Page_One_M*(G_ZoomX[0]-21)+CurveXStartP;
  //����ʼ�㸡������ת����֡��ʽ����
  MENU_FloatToData(G_PublicVF5,CurveXEndP,FLOAT_T);
  MENU_FloatToData(G_PublicVF4,CurveXStartP,FLOAT_T);
  CurveSetLinkHandle(CurrentItemH);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveFakeNhlHandle(const PageDef *CurrentPage,const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
��ٻز������½�����λ���ģ���λ�������ã�
������㵽���֮�佨����ٻز���

*
* �ؼ���ע��
* - 

  
* δ�����:

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
  //�����ȡ��ٻز�������ʼ�����ݣ��Իز��������Ϊ���
  CurveXStartP = MENU_DataToFloat(StartPointPtr,FLOAT_T);
  MENU_FloatToData(G_PublicVF4,CurveXStartP,FLOAT_T);
  //���¼������ƶ�����������
  CurveXEndP = G_Page_One_M*(G_ZoomX[0]-21);
  //����ʼ�㸡������ת����֡��ʽ����
  MENU_FloatToData(G_PublicVF5,CurveXEndP,FLOAT_T); 
  CurveSetLinkHandle(CurrentItemH); 
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveFakeNhlEndHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
��ٻز������½�����λ���ģ���λ���ĺ�����������
���״��豸������ٻز�ָ�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveFakeNhlEndHandle()
{
  MENU_FloatToData(G_PublicVF4,0,FLOAT_T);
  MENU_FloatToData(G_PublicVF5,0,FLOAT_T); 
  MENU_FloatToData(G_PublicVF16,0,FLOAT_T); 
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveXZoomHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
X��Ŵ�������ú�����
ѡ��OK���������ѡ���ķ�Χת�������ݣ���ֵ�����߷�Χ������

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveXZoomHandle(const PageDef *CurrentPage)
{
  float CurveXStartP,CurveXEndP;
  //��������ʼ�����ת����float�������ݣ��������
  CurveXEndP = MENU_DataToFloat(G_RadarCurveEndP,FLOAT_T);
  CurveXStartP = MENU_DataToFloat(G_PublicVF1,FLOAT_T);
  //���¼������ƶ�����������
  CurveXStartP = G_Page_One_M*(G_ZoomX[0]-21)+CurveXStartP;
  //���¼������ƶ���������յ�
  CurveXEndP = G_Page_One_M*(G_ZoomX[1]-21)+CurveXStartP;
  //����ʼ�㸡������ת����֡��ʽ����
  MENU_FloatToData(G_RadarCurveEndP,CurveXEndP,FLOAT_T);
  MENU_FloatToData(G_PublicVF1,CurveXStartP,FLOAT_T);
  //���¼�����������űȡ�
  G_Page_One_M = (CurveXEndP-CurveXStartP)/100;
  //���߽��澭���Ŵ����־��
  G_IsCurveZoom = TRUE;
  CurveBackLinkHandle(CurrentPage);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveYZoomHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
Y��Ŵ�������ú�����
ѡ��OK���������ѡ���ķ�Χת�������ݣ���ֵ�����߷�Χ������

*
* �ؼ���ע��
* - 

  
* δ�����:

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
  //���߽��澭���Ŵ����־��
  G_IsCurveZoom = TRUE;
  CurveBackLinkHandle(CurrentPage);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveGeneralHandle()
* ������Χ:

* ����ֵ˵��:void 
* ���ܽ���:   
ͨ�ù�괦���������������괦�����⣬ͨ������������
������XY��Ŵ���ٻز��ֲ����ĵĵ�һ����괦��
*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveKeyDownHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
���ݼ��ƶ��������������´����󣬶Թ��Ĵ���

*
* �ؼ���ע��
* - 

  
* δ�����:

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
                //��������ƶ�
                G_ZoomX[G_ZoomX_Flag-1]++;
                //�������ù���ƶ������߿��
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
          //Y��Ŵ��������54������ͼ���¶�
          if(G_ZoomY[G_ZoomY_Flag-1] > TempC)
                  G_ZoomY[G_ZoomY_Flag-1] = TempC;
          G_ZoomY[G_ZoomY_Flag-1]++;
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveKeyUpHandle(const PageDef *CurrentPage)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
���ݼ����������������ϴ����󣬶Թ��Ĵ���

*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveThresholdHandle(const ItemDef* CurrentItemH)
* ������Χ:
CurrentPage:ҳ����Ϣ���ڴ��������ҳ���л���
* ����ֵ˵��:void 
* ���ܽ���:   
�ź���ֵȷ���������������λ��ת��Ϊ���ݣ����浽�ź���ֵ�����С�

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 

void CurveThresholdHandle(const ItemDef* CurrentItemH)
{  
  G_PublicVC11[0] = (uchar)((LCDCURVELLIMIT - G_ZoomY[0])*G_Curve_One_H)+G_CurveLimitL;
  G_ZoomY_Flag = 0;
  CurveSetLinkHandle(CurrentItemH);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void CurveKeyOkHandle(CurrentPage)
* ������Χ:

* ����ֵ˵��:void 
* ���ܽ���:   
���ȷ��������������ȷ�������󣬶Թ��Ĵ���

*
* �ؼ���ע��
* - 

  
* δ�����:

*/ 
void CurveKeyOkHandle(const PageDef *CurrentPage,const ItemDef* CurrentItemH)
{
  if((G_ZoomX_Flag >= 2)||(G_ZoomY_Flag >= 2))
  {
    //X��Ŵ���
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_V)
    {
      CurveXZoomHandle(CurrentPage);
      G_VariableSingleDisFlag = FALSE;
    }
    //Y��Ŵ���
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_H)
    {
      CurveYZoomHandle(CurrentPage);
    }
    //�ֲ���ٻز���������
    if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MPART)
    {
      CurveFakePartHandle(CurrentItemH);
      G_VariableSingleDisFlag = FALSE;
    }//��λä��ȷ������
    else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_DZL)
    {
      CurveLowDeadZoneHandle(CurrentItemH);
    }
  }
  else if((G_ZoomX_Flag == 1)||(G_ZoomY_Flag == 1))
  {
    //��ٻز��趨���½������ĸ�λ�����ĵ�λ����
    if((G_ZoomX_Flag == 1)&&(G_ZoomY_Flag == 0)
       &&((CurrentPage->AdditionalInfo == CURSOR_HANDLE_NEW)
        ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MHIGH)
          ||(CurrentPage->AdditionalInfo == CURSOR_HANDLE_MLOW)))
    {
      CurveFakeNhlHandle(CurrentPage,CurrentItemH);
    }//��λä��ȷ������
    else if(CurrentPage->AdditionalInfo == CURSOR_HANDLE_DZH)
    {
      CurveHighDeadZoneHandle(CurrentItemH);
    }//�ź���ֵȷ������
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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveOperationPageHandle(KeyValueDef KeyMode);
* ������Χ:
KeyValueDef KeyMode:�������࣬��������һ��������
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* ����ֵ˵��:void 
* ���ܽ���:   
���߲������洦������ִ�����߽����밴�����ִ�й��ܣ�
������淵�أ�����ƶ��ȹ��ܡ�

*
* �ؼ���ע��
* - 

  
* δ�����:

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
//�������ƺͲ����ͷ���ֵ���͡�
void CursorParamInit(ParamTableDef Flag)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:  
���������غ�����
���߽�������Ҫ�趨��ʼ���꣬�Լ���������ʼ��������Ҫͨ�����������в������ء�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void	CurveZoomSart_End(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:  
���߷Ŵ󲿷���ʼ�����������ʾ��������
������ƶ��Ĳ���ת���ɸ�����������ʾ������ͼ��Ӧλ�á�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void	CurveDeadZoneSpanDisplay(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:  
ä���̶���ʾ����������ǰ�ߵ�λä������ֵ��ʾ�����߽��档
*
* �ؼ���ע��
* - 

  
* δ�����:


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
//�������ƺͲ����ͷ���ֵ���͡�
void CurveFakeEchoReloadFlagHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:  

*
* �ؼ���ע��
* - 

  
* δ�����:


*/
void CurveFakeEchoReloadFlagHandle()
{  
  //�����ٻز����÷������ģ���Ҫ�ڴ˴�����ٻز����±�־��������
  G_IsFakeCurveUpdateFlag = TRUE;
  G_IsFakeCurveDisplay = TRUE;
  G_FakeCurveLoadCount = 0;
}

