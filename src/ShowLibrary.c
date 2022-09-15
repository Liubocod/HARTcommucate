#include "SystemInclude.h"
uchar ShowDataBuffe[20],DecimalP,CursorMoveH,MenuSelection,Processed_DataType;
uchar	MenuMark[5],ShowCurveData[100];
//float StartDistance,EndDistance;

union
{
	unsigned char MenuIndexC[4];
	unsigned long MenuIndex_short;
}MenuIndex;

void	ClearLcdScreen(void)
{
	unsigned char Tmpi,Tmpj;
	Tmpi = 8;
	do
	{
		Tmpi--;
		LcdSetPage(Tmpi);
		LcdSetColumn(4);
		for(Tmpj = 4; Tmpj < 132; Tmpj++)
		{
			LcdWriteData(0);
		}
	}while(Tmpi != 0);
}

void	ShowString(uchar LibraryIndex,const uchar* String,uchar HorizontalPostion,uchar VerticalPostion)
{
	unsigned char Tmpi,Tmpj,CharacterHorizontalLine,CharacterVerticalLine,TempN;
	unsigned int IntTemp;
	const unsigned char *TempLibrary;
	TempN = 0;

	switch(LibraryIndex)
	{
		case ASCII_6X16:
			CharacterHorizontalLine = 6;
			CharacterVerticalLine = 2;		//12/8
			TempLibrary = Ascii_6x16;
			break;
		case ASCII_18X48:
			CharacterHorizontalLine = 18;
			CharacterVerticalLine = 6;		//24/8
			TempLibrary = Ascii_18x48;
			break;
		case ASCII_5X8:
			CharacterHorizontalLine = 5;
			CharacterVerticalLine = 1;		//12/8
			TempLibrary = Ascii_5x8;
			break;
		case ASCII_11X16:
			CharacterHorizontalLine = 11;
			CharacterVerticalLine = 2;		//24/8
			TempLibrary = MainPageUnit;
			break;
		case ASCII_25X48:
			CharacterHorizontalLine = 25;
			CharacterVerticalLine = 6;		//24/8
			TempLibrary = Ascii_25x48;
			break;
		default:break; 
	}		

	while(String[TempN] != '\0')
	{
		IntTemp = CharacterVerticalLine*CharacterHorizontalLine;
		IntTemp = (String[TempN]-0x2D)*IntTemp;
		for(Tmpi = 0; Tmpi < CharacterVerticalLine; Tmpi++)
		{
			LcdSetPage(VerticalPostion+Tmpi);
			LcdSetColumn(CharacterHorizontalLine*TempN+HorizontalPostion);
			for(Tmpj = 0; Tmpj < CharacterHorizontalLine; Tmpj++)
			{
				if((TempN == CursorMoveH)||(Processed_DataType == BOOLTYPE))
				{
					LcdWriteData(~TempLibrary[IntTemp+Tmpj+Tmpi*CharacterHorizontalLine]);
				}
				else
				{
					LcdWriteData(TempLibrary[IntTemp+Tmpj+Tmpi*CharacterHorizontalLine]);
				}
			}
		}
		TempN++;
		if(TempN > 21)break;
	}
}

void	CharToAssII(uchar CharValure)
{
	uchar TempC;
	if(CharValure > 100)
		CharValure = 99;
//	ShowDataBuffe[0] = CharValure/100;								//分解得到百位数
//	TempC = CharValure-ShowDataBuffe[0]*100;
	ShowDataBuffe[0] = CharValure/10;									//分解得到十位数
	ShowDataBuffe[1] = CharValure%10;									//分解得到个位数
	for(TempC = 0; TempC < 2; TempC++)
	{
		ShowDataBuffe[TempC] = ShowDataBuffe[TempC]+0x30;			//转换成字符串
	}
	ShowDataBuffe[2] =  '\0';
}

void	DisplayMenuMark(void)
{
	signed char TempC;
	for(TempC = 2; TempC >= 0; TempC--)
	{
		if(MenuIndex.MenuIndexC[TempC] != 0)
		{
			MenuMark[TempC] = 0x31+MenuSelection;
			break;
		}
		else
		{
			MenuMark[TempC] = 0x30;
		}
	}
	MenuMark[3] = '\0';
	ShowString(ASCII_5X8,MenuMark,116,0);
}

uchar	AssIICToChar()
{
	return((ShowDataBuffe[0]-0x30)*10+ShowDataBuffe[1]-0x30);//字符串转成数值
}

void	DisplayChinese16X12(uint DisplayedChinese,uchar HorizontalPostion,uchar VerticalPostion)
{
	uchar Tmpi,Tmpj;
	uint IntTemp;
	IntTemp = DisplayedChinese*24;													//ChineseVerticalLine*ChineseHorizontalLine = 2*16
	for(Tmpi = 0; Tmpi < 2; Tmpi++)
	{
		LcdSetPage(VerticalPostion+Tmpi);
		LcdSetColumn(HorizontalPostion);
		for(Tmpj = 0; Tmpj < 12; Tmpj++)
		{
			if(Processed_DataType != BOOLTYPE)
				LcdWriteData(GB_12x16[IntTemp+Tmpj+Tmpi*12]);
			else
				LcdWriteData(~GB_12x16[IntTemp+Tmpj+Tmpi*12]);
		}
	}
}

//显示菜单
//输入参数：汉字数组、被选择的菜单行号、菜单总行数、每行汉字的字数
void	Display_MenuPage(const uchar *Menucontent, uchar MenuItemSelected,uchar MenuLineNumber,uchar EachLineWordNumber,uchar StartH)
{
	uchar Tempi,Tempj,TempM;
	uchar StartItem,EndItem;
	
	TempM = MenuItemSelected/4;
	StartItem = TempM*4;				//确定菜单起始行
	EndItem = StartItem+4;				//确定菜单结束行
	if(EndItem > MenuLineNumber)
	{
		EndItem = MenuLineNumber;
	}
	
	TempM = MenuLineNumber-1;
	if(( (MenuItemSelected%4) == 0)||(MenuItemSelected == TempM))
	{
		ClearLcdScreen();
	}
		
	for(Tempi = StartItem; Tempi < EndItem; Tempi++)
	{
		TempM = Tempi-StartItem;
		TempM = TempM*2;
		if(OtherParaU.OtherPara.Language == 0)
			ShowString(ASCII_6X16,&Menucontent[Tempi*EachLineWordNumber],StartH,TempM);
		else
		{
			for(Tempj = 0; Tempj < EachLineWordNumber; Tempj++)
			{
				DisplayChinese16X12(Menucontent[Tempi*EachLineWordNumber+Tempj],Tempj*12+StartH,TempM);			//显示汉字（16*12）
			}
		}
		if(CursorMoveH != HIDECURSOR)
		{
			if(MenuItemSelected == Tempi)
			{
				ShowString(ASCII_6X16,"<",4,TempM);										//被选项后面显示“<-”
			}
			else
			{
				ShowString(ASCII_6X16,"/",4,TempM);										//非被选项后面显示“ ”
			}
		}
	}
	//显示右上角菜单号
//	if(NextMenuYesOrNo == YES)
		DisplayMenuMark();
}

void	Display_MenuSingleSelectionPage(const uchar *Menucontent,uchar ItemSelected,uchar SelectionNumber,uchar EachLineWordNumber,uchar StartH,uchar StartV)
{
	uchar Tempi,Tempj;
	
	for(Tempi = 0; Tempi < SelectionNumber; Tempi++)
	{
		if(Tempi == ItemSelected)
		{
			if(OtherParaU.OtherPara.Language == 0)
				ShowString(ASCII_6X16,&Menucontent[Tempi*EachLineWordNumber],StartH,StartV);
			else
			{
				for(Tempj = 0; Tempj < EachLineWordNumber; Tempj++)
				{
					DisplayChinese16X12(Menucontent[Tempi*EachLineWordNumber+Tempj],Tempj*12+StartH,StartV);			//显示汉字（16*12）
				}
			}
		}
	}
}

float	CharToFloat( void )
{
	signed char Temp;
//	unsigned int TempI = 1;
	float	TranResult = 0,TempF = 1;
	for(Temp = DecimalP-1; Temp > 0; Temp--)
	{
		TranResult = TempF*(ShowDataBuffe[Temp]-0x30)+TranResult;
		TempF = TempF*10;
	}
	if(ShowDataBuffe[0] != '-')
	{
		TranResult = TranResult+(ShowDataBuffe[0]-0x30)*TempF;
	}
	TempF = 10;
	for(Temp = DecimalP+1; Temp < 6; Temp++)
	{
		TranResult = (ShowDataBuffe[Temp]-0x30)/TempF+TranResult;
		TempF = TempF*10;
	}
	if(ShowDataBuffe[0] == '-')
	{
		TranResult = 0-TranResult;
	}
	return(TranResult);
}
//把浮点数转成字符串
//输入参数：浮点数、要显示小数位
//输出参数：存放在数组ShowDataBuffe里
void	FloatToChar(float TranFloat,unsigned char DecimalN)
{
	unsigned char j = 0;
	unsigned char i = 0;
	unsigned char TempC,CarryFlag = 0;
	unsigned long preValue,currValue;
//	ShowDataBuffe[0]=0;
	if(TranFloat < 0)
	{//浮点数是负数时
		TranFloat = 0-TranFloat;
		ShowDataBuffe[0] = '-';
		i++;
	}
	TranFloat = TranFloat+0.000008;
	preValue = (unsigned long)TranFloat;
	TranFloat = TranFloat-preValue;
	//处理整数部分
	do
	{
		currValue = preValue/10;
		ShowDataBuffe[i] = preValue-currValue*10+0x30;
		preValue = currValue;
		i++;
	}
	while( (preValue != 0) && (i < 5) );

	if(DecimalN != 0)
		ShowDataBuffe[i] = '.';
	else
		ShowDataBuffe[i] = '/';
	DecimalP = i;
	//处理小数部分
	while(i < 6)
	{
		i++ ;	
		ShowDataBuffe[i] = (uchar) (TranFloat*10);
		TranFloat = TranFloat*10-ShowDataBuffe[i];
		ShowDataBuffe[i] = ShowDataBuffe[i]+0x30;
		if( j >= DecimalN )
		{
			if(ShowDataBuffe[i] >= '5')
			{
				if(ShowDataBuffe[i-1] != '/')
				{
					TempC = i-1;
					do
					{
						if(ShowDataBuffe[TempC] != '9')
						{
							ShowDataBuffe[TempC]++;
							TempC = 0;
						}
						else
						{
							ShowDataBuffe[TempC] = '0';
							TempC--;
							if(TempC == DecimalP)
								CarryFlag = 1;
						}
					}
					while(TempC > DecimalP);
				}
			}
			ShowDataBuffe[i] = '/';
//			break;
		}
		j++;
	}
	j = DecimalP-1;
	if(ShowDataBuffe[0] == '-')
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	//调整顺序,高位在前
	while(i < j)
	{
		TempC = ShowDataBuffe[j];
		ShowDataBuffe[j] = ShowDataBuffe[i];
		ShowDataBuffe[i] = TempC;
		i++;
		j--;
	}
	if(CarryFlag == 1)
	{
		TempC = DecimalP-1;
		do
		{
			if(ShowDataBuffe[TempC] != '9')
			{
				ShowDataBuffe[TempC]++;
				TempC = 0;
			}
			else
			{
				ShowDataBuffe[TempC] = '0';
				TempC--;
				if(TempC == 0)
				{
					if(ShowDataBuffe[0] == '9')
					{
						ShowDataBuffe[0] = '1';
						for(i = 5; i > 1; i--)
							ShowDataBuffe[i] = ShowDataBuffe[i-1] ;
						ShowDataBuffe[1] = '0';
					}
					else
						ShowDataBuffe[0]++;
				}
			}
		}
		while(TempC > 0);
	}
	ShowDataBuffe[6] = '\0';//字符串结束符
}

void	DisplayBarPercentage( unsigned char PerValure)
{
	unsigned char TempChar,TempJ,PercentNumber;

	PercentNumber = PerValure;

	if(PercentNumber <= 100) 
		PercentNumber = PercentNumber+BarPostionX_Start;
	else
		PercentNumber = 0;
	
	LcdSetPage(BarPostionY);
	LcdSetColumn(BarPostionX_Start);
	LcdWriteData(0xFF);
	
	for(TempChar = BarPostionX_Start+1; TempChar < BarPostionX_End; TempChar++)
	{
		TempJ = TempChar-BarPostionX_Start;
		TempJ = TempJ%10;
		if(TempJ)
		{
			if(TempChar < PercentNumber)
				LcdWriteData(0xFF);
			else
				LcdWriteData(0x81);
		}
		else
		{
			if(TempChar == PercentNumber)
				LcdWriteData(0xFF);
			else
				LcdWriteData(0xE7);
		}
	}
	LcdWriteData(0xFF);
}

//编辑数字加一
void	EditDataAdd1()
{
	if(ShowDataBuffe[CursorMoveH] != '.')
	{
		ShowDataBuffe[CursorMoveH]++;
		if(ShowDataBuffe[CursorMoveH] == '.')
		{
			ShowDataBuffe[CursorMoveH] = 0x30;
		}
		else	if(ShowDataBuffe[CursorMoveH] == ':')
		{
			if(CursorMoveH == 0)
			{
				ShowDataBuffe[CursorMoveH] = '-';
			}
			else
			{
				ShowDataBuffe[CursorMoveH] = 0x30;
			}
		}
	}
	else		//当前编辑位为小数点时
	{
		if(CursorMoveH != 5)
		{
			ShowDataBuffe[CursorMoveH] = ShowDataBuffe[CursorMoveH+1];
			ShowDataBuffe[CursorMoveH+1] = '.';
			DecimalP++;
		}
		else
		{
			ShowDataBuffe[5] = ShowDataBuffe[3];
			ShowDataBuffe[4] = ShowDataBuffe[2];
			ShowDataBuffe[3] = ShowDataBuffe[1];
			ShowDataBuffe[2] = ShowDataBuffe[0];
			ShowDataBuffe[0] = 0x30;
			ShowDataBuffe[1] = '.';
			DecimalP = 1;
		}
	}
}

void	DrawHLine(uchar HPostion)
{
	uchar TempH;
	for(TempH = 2; TempH < 6; TempH++)
	{
		LcdSetPage(TempH);
		LcdSetColumn(HPostion);
		LcdWriteData(0xFF);
	}
}

void	DrawVMoveLine(uchar VPostion)
{
	uchar TempH,TempDot,TempData,TempPage;
	TempPage = VPostion/8;
	TempDot = 7-VPostion%8;
	TempData = 0x80;
	TempDot = TempData>>TempDot;
	LcdSetPage(TempPage);
	for(TempH = 21; TempH < 120; TempH++)
	{
		LcdSetColumn(TempH);
		TempData = LcdReadData()|TempDot;

		LcdSetColumn(TempH);
		LcdWriteData(TempData);
	}
}

void	DrawChart(void)
{
	unsigned char TempC,TempL,TempD;

	for(TempL = LCDCURVESTARTPAGE; TempL < LCDCURVEENDPAGE; TempL++)
	{
		LcdSetPage(TempL);
		LcdSetColumn(LCDCURVESTARTCOLUMN);
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; TempC++)
		{
			LcdWriteData(0);		//清除曲线区，以备刷新曲线
		}
	}

	for(TempL = LCDCURVESTARTPAGE; TempL < LCDCURVEENDPAGE; )
	{
		LcdSetPage(TempL);
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; )
		{
			LcdSetColumn(TempC);
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
		LcdSetPage(TempL);
		for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; )
		{
			if(TempC == 120)
				TempC = LCDCURVEENDCOLUMN;
			LcdSetColumn(TempC);
			if((TempC == LCDCURVESTARTCOLUMN)||(TempC == LCDCURVEENDCOLUMN))
				LcdWriteData(0xFF);
			else
				LcdWriteData(0x55);
			TempC = TempC+25;
		}
	}

	LcdSetPage(6);
	for(TempC = LCDCURVESTARTCOLUMN; TempC < LCDCURVEENDCOLUMN; TempC++)
	{
		LcdSetColumn(TempC);
		TempD = LcdReadData();

		LcdSetColumn(TempC);
		LcdWriteData(0x80|TempD);
	}
}

void	DiplayCureXY(void)
{
	unsigned char TempC,TempL,TempD;
	float TempF,TempK;
	ShowString(ASCII_5X8,"=",20,0);
	TempF = 3.3/255*CurveLimitH;
//	TempF1 = 3.3/255*CurveLimitL;
	TempK = 1.1*(CurveLimitH-CurveLimitL)/255;
	for(TempC = 0; TempC < 7; )
	{
		if(TempF < 0)
			TempF = 0;
		FloatToChar(TempF,1);
		ShowDataBuffe[3] = '\0';
		ShowString(ASCII_5X8,ShowDataBuffe,4,TempC);
		TempF = TempF-TempK;
		TempC = TempC+2;
	}
	
	for(TempC = 0; TempC < 7; )
	{
		for(TempL = 4; TempL < 20; TempL++)
		{
			LcdSetPage(TempC);
			LcdSetColumn(TempL);
			TempD = LcdReadData();
			
			LcdSetPage(TempC);
			LcdSetColumn(TempL);
			LcdWriteData(TempD<<4);

			LcdSetPage(TempC+1);
			LcdSetColumn(TempL);
			LcdWriteData(TempD>>4);
		}
		TempC = TempC+2;
	}
	FloatToChar(MasterVariableU.MasterVariableF[6],2);
	ShowString(ASCII_5X8,ShowDataBuffe,104,7);
	FloatToChar(MasterVariableU.MasterVariableF[5],2);
	ShowString(ASCII_5X8,ShowDataBuffe,20,7);
	TempF = MasterVariableU.MasterVariableF[5]+(MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/2;
	FloatToChar(TempF,2);
	ShowString(ASCII_5X8,ShowDataBuffe,61,7);
	ShowString(ASCII_5X8,";",125,7);
	ShowString(ASCII_5X8,";",125,0);
}
void	DrawCurve()
{
	uchar TempC,PreByte,PreDot,CurrentDot,CurrentByte,TempData,InitDotValure;
	float TempF;
	PreDot = 1;
	for(TempC = 0; TempC < 100; TempC++)
	{
		if(ShowCurveData[TempC] < CurveLimitL)
			ShowCurveData[TempC] = CurveLimitL;
		if(ShowCurveData[TempC] > CurveLimitH)
			ShowCurveData[TempC] = CurveLimitH;
		TempF = ShowCurveData[TempC]-CurveLimitL;
		TempF = TempF/Curve_One_H;
		TempData = (unsigned char)TempF;
		CurrentDot = TempData%8;
		CurrentDot = 7-CurrentDot;
		CurrentByte = 6-TempData/8;
		
		if(TempC != 0)
		{
		if(CurrentByte == PreByte)
		{
			InitDotValure = 0xFF;                    
			TempData = 0xFF;
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
			TempData = InitDotValure&TempData;
		}
		else	if(CurrentByte > PreByte)
		{
			InitDotValure = 0xFF;                    
			InitDotValure <<= PreDot;

			LcdSetPage(PreByte);
			LcdSetColumn(TempC+21);
			TempData = LcdReadData();
			TempData = TempData|InitDotValure;
			LcdSetPage(PreByte);
			LcdSetColumn(TempC+21);
			LcdWriteData(TempData);
			PreByte++;
			while(CurrentByte > PreByte)
			{
				LcdSetPage(PreByte);
				LcdSetColumn(TempC+21);
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

			LcdSetPage(PreByte);
			LcdSetColumn(TempC+21);
			TempData = LcdReadData();
			TempData = TempData|InitDotValure;
			LcdSetPage(PreByte);
			LcdSetColumn(TempC+21);
			LcdWriteData(TempData);
			PreByte--;
			while(CurrentByte < PreByte)
			{
				LcdSetPage(PreByte);
				LcdSetColumn(TempC+21);
				LcdWriteData(0xFF);
				PreByte--;
			}
			TempData = 0xFF;
			TempData <<= CurrentDot;
		}
		}
		else
		{
			TempData = 0x01;
			TempData <<= CurrentDot;
		}
		
		LcdSetPage(CurrentByte);
		LcdSetColumn(TempC+21);
		InitDotValure = LcdReadData();
		TempData = TempData|InitDotValure;
		LcdSetPage(CurrentByte);
		LcdSetColumn(TempC+21);
		LcdWriteData(TempData);
		
		PreDot = CurrentDot;
		PreByte = CurrentByte;
	}
}

void	DisplayProgressBar(uchar PrograssNumber)
{
	uchar TempC;
	LcdSetPage(4);
	for(TempC = 0; TempC < 4; TempC++)
	{
		LcdSetColumn(TempC+PrograssNumber*5);
		LcdWriteData(0xC0);
	}
}

void	DisplayChart(const uchar *Libr)
{
	uchar TempC,Temp;
	for(Temp = 1; Temp < 7; Temp++)
	{
		LcdSetPage(Temp);
		for(TempC = 106; TempC < 130; TempC++)
		{
			LcdSetColumn(TempC);
			LcdWriteData(Libr[Temp*24+TempC-130]);
		}
	}
}
void	DrawBar(void)	
{
	unsigned char TempChar,TempJ;
	for(TempChar = 2; TempChar <7; TempChar++)
	{
		LcdSetPage(TempChar);
		for(TempJ = 118; TempJ < 120; TempJ++)
		{
			LcdSetColumn(TempJ);
			LcdWriteData(0xFF);
		}
		LcdSetPage(TempChar);
		for(TempJ = 130; TempJ < 132; TempJ++)
		{
			LcdSetColumn(TempJ);
			LcdWriteData(0xFF);
		}
	}
}

void	DisplayBarPercentage_v( unsigned char PerValure)
{
	unsigned char TempChar,TempJ,PercentNumber,TempData;//,Temp;

	for(TempChar = 1; TempChar < 8; TempChar = TempChar+6)
	{
		LcdSetPage(TempChar);
		TempData = TempChar/6;
		for(TempJ = 118; TempJ < 132; TempJ++)
		{
			LcdSetColumn(TempJ);
			LcdWriteData(chart_bar[TempData*14+TempJ-118]);
		}
	}

	if(PerValure <= 100) 
		PercentNumber = PerValure/2+2;
	else
		PercentNumber = 50;

	TempData = 0xFF;
	if(PercentNumber < 8)
	{
		TempChar = PercentNumber%8;
		TempChar = 7-TempChar;
		TempData = TempData <<TempChar;
		TempData = TempData&0x1F;
	}
	else
		TempData = 0x1F;

	for(TempJ = 120; TempJ < 130; TempJ++)
	{
		LcdSetPage(7);
		LcdSetColumn(TempJ);
		TempChar = TempData|LcdReadData();

		LcdSetPage(7);
		LcdSetColumn(TempJ);
		LcdWriteData(TempChar);
	}
	
	TempData = 0xFF;
	TempChar = PercentNumber%8;
	TempChar = 7-TempChar;
	TempData = TempData <<TempChar;
	TempJ = 7-PercentNumber/8;
		
	if((TempJ > 1)&&(TempJ < 7))
	{
		for(TempChar = 120; TempChar < 130; TempChar++)
		{
			LcdSetPage(TempJ);
			LcdSetColumn(TempChar);
			LcdWriteData(TempData);
		}				
	}
	for(TempData = 2; TempData < 7; TempData++)
	{
		LcdSetPage(TempData);
		for(TempChar = 120; TempChar < 130; TempChar++)
		{
			LcdSetColumn(TempChar);
			if(TempData > TempJ)
				LcdWriteData(0xFF);
			else if(TempData < TempJ)
				LcdWriteData(0);
		}
	}

	TempData = 0xFF;
	if(PercentNumber > 47)
	{
		TempChar = PercentNumber%8;
		TempChar = 7-TempChar;
		TempData = TempData <<TempChar;
		TempData = TempData&0xF8;
	}
	else
		TempData = 0;

	for(TempJ = 120; TempJ < 130; TempJ++)
	{
		LcdSetPage(1);
		LcdSetColumn(TempJ);
		TempChar = TempData|LcdReadData();

		LcdSetPage(1);
		LcdSetColumn(TempJ);
		LcdWriteData(TempChar);
	}
}
