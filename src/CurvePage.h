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
#ifndef CURVE_PAGE_H
#define CURVE_PAGE_H

#define ZOOM_BUFF_SIZE                          2
#define START_CURSOR                            1
#define END_CURSOR                              2
#define	LCDCURVELLIMIT				54
#define	LCDCURVEHIGH				47.0

extern uchar ShowDataBuffe[20];
extern uchar DecimalP;
extern bool8 G_IsCurveZoom;
extern uchar G_ShowCurveData[100];
extern uchar G_ShowFakeCurveData[100];

void CursorParamInit(ParamTableDef Flag);
void CurvePageShow();
void CurvePageHandle(KeyValueDef KeyMode);
void CurveOperationPageShow();
void CurveOperationPageHandle(KeyValueDef KeyMode);
void CurveNoZoomHandle();
void CurveFakeNhlEndHandle();
void CurveFakeEchoReloadFlagHandle();
#endif