#include "ShowLibrary.c"
#include "EEprom24CXX.c"
#include "HandleUserPara.c"

uchar CurveSwitch,XZoom_Flag,YZoom_Flag,Zoom_X[2],Zoom_Y[2],FakeWaveCurve[100],YZoom_Valure,DeadSetFlag,ZoomMainDisplay,CurveSwitchDoubleCurve,RecordEchoFlag;
uchar RecordCount,ViewCount,RangeReceordFlag[11],RecordEcohEnd,MasterVFlag;
float	Page_One_M;//,MeasurePV[10];
unsigned long MenuIndexBackup;
typedef struct
{
	uchar CurveDataV[100];
	uchar BestEchoP,BestEchoSignalR,BestEchoA;
	float Distance;
}CurvePageI;
CurvePageI InitEchoInformation[1],RangeEchoInformation[11];
CurvePageI SuddenChangeEchoInformation[8];
void	HandlePage();

void	DisplaySensorUnit(void)
{
	DisplayMulti = 1;
	switch(OtherParaU.OtherPara.DisplayPage_Para[0])
	{
		case	MEANING_SENSOR_DISWAY_LIAOGAO:
		case	MEANING_SENSOR_DISWAY_KONGGAO:
			switch(OtherParaU.OtherPara.DisplayPage_Para[1])
			{
				case	MEANING_SENSOR_UNIT_MI:
					ShowString(ASCII_11X16, "/",95,6);//m
					DisplayMulti = 1;
					DisplayDecimal = 3;
				break;
				case	MEANING_SENSOR_UNIT_FENMI:
					ShowString(ASCII_11X16, "./",95,6);//dm
					DisplayMulti = 10;
					DisplayDecimal = 2;
				break;
				case	MEANING_SENSOR_UNIT_LIMI:
					ShowString(ASCII_11X16, "-/",95,6);//cm
					DisplayMulti = 100;
					DisplayDecimal = 1;
				break;
				case	MEANING_SENSOR_UNIT_HAOMI:
					ShowString(ASCII_11X16, "//",95,6);//mm
					DisplayMulti = 1000;
					DisplayDecimal = 0;
				break;
				default:break;
			}
		break;
		case	MEANING_SENSOR_DISWAY_BILI:
			ShowString(ASCII_11X16, "1",95,6);
			DisplayDecimal = 3;
		break;
		case	MEANING_SENSOR_DISWAY_DIANLIU:
			ShowString(ASCII_11X16, "/0",95,6);
			DisplayDecimal = 3;
		break;
		case	MEANING_SENSOR_DISWAY_PERSENT:
			ShowString(ASCII_11X16, "1",95,6);
			DisplayDecimal = 2;
		break;
		default:break;
	}
}

void	DisplayMeasurePageBackground(void)
{
	unsigned char MeauseValues[3]={1,2,3};
	Processed_DataType = NOTYPE;
	CursorMoveH = HIDECURSOR;
	ClearLcdScreen( );
	if(OtherParaU.OtherPara.Language == 0)
		ShowString(ASCII_6X16,"Measure/Values",4,0);
	else
		Display_MenuPage(MeauseValues,0,1,3,4);
	MenuIndex.MenuIndex_short = 0;
	if(ZoomMainDisplay == 0)
	{
		DisplaySensorUnit();
		DrawBar();
		DisplayBarPercentage_v(0);
	//	DisplayMenuMark();
	//	ShowString(ASCII_5X8,MenuMark,111,0);
		UpdateMainInterface();
	}
	if(RecordEchoFlag == 1)
		ShowString(ASCII_6X16, "R",95,4);//R
	UpdateCurveFlag = 8;
}

void	HandleOptionShift(void)
{
	if(CursorMoveH > 0xF0)
	{
		MenuSelection++;
		if(MenuSelection >= MaxMenuLine)
		{
			MenuSelection = 0;
		}
	}
	else
	{
		CursorMoveH++;
		if(CursorMoveH > Processed_DataType)
		{
			CursorMoveH = 0;
			if(Processed_DataType == BOOLTYPE)
			{
				if(ShowDataBuffe[0] == 0 )
					ShowDataBuffe[0] = MaxMenuLine;
				ShowDataBuffe[0]--;
			}
		}
	}
}

void	HandleDataInc(void)
{
 	if(CursorMoveH > 0xF0)
	{
		if(MenuSelection == 0)
		{
			MenuSelection = MaxMenuLine;
		}
		MenuSelection--;
	}
	else
	{
		switch(Processed_DataType)
		{
			case BOOLTYPE:
				ShowDataBuffe[0]++;
				if(ShowDataBuffe[0] >= MaxMenuLine)
					ShowDataBuffe[0] = 0;
			break;
			case FLOATTYPE:
				EditDataAdd1();											//被编辑的数字加一
			break;
			case ASCIITYPE:
				ShowDataBuffe[CursorMoveH]++;
				if(ShowDataBuffe[CursorMoveH] > 'Z')
				{
					ShowDataBuffe[CursorMoveH] = '0';
				}
			break;
			default:
				ShowDataBuffe[CursorMoveH]++;
				if(ShowDataBuffe[CursorMoveH] >= ':')
				{
					ShowDataBuffe[CursorMoveH] = '0';
				}
			break;
		}
	}
}
void	ReturnDoubleCurve(void)
{
	DelayCount = 0;
	XZoom_Flag = 0;
	CurveSwitch = 1;
	MenuIndex.MenuIndex_short = MenuIndexBackup;
	G_KeyValue = NO_KEY_STATUS;
	HandlePage();
	UpdateCurveFlag = 8;
	CurveSwitchDoubleCurve = 0;
	MasterVariableU.MasterVariableF[3] = 0;//MasterVariableU.MasterVariableF[5];
	MasterVariableU.MasterVariableF[4] = 0;//MasterVariableU.MasterVariableF[6];
	while(DelayCount < 50)
	{
		;
	}
}

//显示菜单界面
//输入参数：按键值、当前选择的菜单行号、菜单汉字数组、菜单总行数、一行汉字的字数
void HandleMenuPage(const uchar *MunuWords,uchar NumMenuMax, uchar LengthMenu)
{
	uchar TempC,TempP;
	switch(G_KeyValue)
	{
		case	NO_KEY_STATUS:
			ClearLcdScreen();											//清屏
			CursorMoveH = VISBLEMENUCURSOR;
//			MenuSelection = 0;
			Display_MenuPage(MunuWords,MenuSelection,NumMenuMax,LengthMenu,10);		//显示菜单
			break;
		case	DOWN:
			HandleOptionShift();
 			if(CursorMoveH > 0xFD)
				Display_MenuPage(MunuWords,MenuSelection,NumMenuMax,LengthMenu,10);
			break;
		case	UP:
			HandleDataInc();
 			if(CursorMoveH > 0xFD)
				Display_MenuPage(MunuWords,MenuSelection,NumMenuMax,LengthMenu,10);
			break;
		case	OK:												//进入下一级菜单
			if(NextMenuYesOrNo == TRUE)
			{
				for(TempC = 0; TempC < 4; TempC++)
				{
					if(MenuIndex.MenuIndexC[TempC] == 0)
					{
						MenuIndex.MenuIndexC[TempC] = MenuSelection+1;
						break;
					}
				}
				G_KeyValue = NO_KEY_STATUS;
				MenuSelection = 0;
				HandlePage();
			}
			else
			{
				if(CursorMoveH < 0xF0)
				{
					Processed_DataType = NOTYPE;
					CursorMoveH = VISBLEMENUCURSOR;
					ModifyParaStatus = 1;
				}
				else
				{
					CursorMoveH = VISBLEEDITCURSOR;
					if((MenuSelection >= (MaxMenuLine-1))&&(MenuIndex.MenuIndex_short == QUICKSETUPINTERFACE))
					{
						MenuIndex.MenuIndexC[2] = 3;//MenuSelection+1;
						MenuSelection = MaxMenuLine-1;//MenuIndex.MenuIndexC[1];
//						MenuIndex.MenuIndex_short = ECHOENTERPAGE;
						CursorMoveH = HIDECURSOR;
						G_KeyValue = NO_KEY_STATUS;
						HandlePage();
					}
					
					if((MenuSelection >= 3)&&(MenuIndex.MenuIndex_short == MODFYMCURVEPAGE))
					{
						HartModfiyPara(189);
						MasterVariableU.MasterVariableF[5] = MasterVariableU.MasterVariableF[2];
						ReturnDoubleCurve();
					}

					if((MenuSelection >= 4)&&(MenuIndex.MenuIndex_short == BASICSETUPINTERFACE))
					{
						SendHartReadCmd(14);
						MenuIndex.MenuIndexC[2] = MenuSelection+1;
						MenuSelection = MenuIndex.MenuIndexC[1];
						G_KeyValue = NO_KEY_STATUS;
						HandlePage();
					}

					if((MenuSelection == 3)&&(MenuIndex.MenuIndex_short == CURRENTPARAPAGE))
						ModifyParaStatus = 1;
					if((MenuSelection == 0)&&(MenuIndex.MenuIndex_short == SYSTEMDISPAGE))
						ModifyParaStatus = 1;
					if((MenuSelection == 2)&&(MenuIndex.MenuIndex_short == SETCURVERANGEPAGE))
					{
						MasterVariableU.MasterVariableF[5] = CurveStartEnd[0];
						MasterVariableU.MasterVariableF[6] = CurveStartEnd[1];
						Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
						MenuIndex.MenuIndex_short = MenuIndexBackup;
						G_KeyValue = NO_KEY_STATUS;
						HandlePage();
					}
					if(MenuIndex.MenuIndex_short == VIEWCURVEECHO)
					{
						if((MenuSelection == 2)||(MenuSelection == 0))
						{
							Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
							MenuIndexBackup = MenuIndex.MenuIndex_short;
							MenuIndex.MenuIndex_short = VIEWRECORDCURVEECHO;
							G_KeyValue = NO_KEY_STATUS;
							HandlePage();
						}
						else
						{
							CursorMoveH = 0xFE;
							if(MenuSelection == 1)
							{
								for(TempP = 0; TempP < 8; TempP++)
								{
									for(TempC = 0; TempC < 100; TempC++)
										SuddenChangeEchoInformation[TempP].CurveDataV[TempC] = 0;
									SuddenChangeEchoInformation[TempP].Distance = 0;
									SuddenChangeEchoInformation[TempP].BestEchoA = 0;
									SuddenChangeEchoInformation[TempP].BestEchoSignalR = 0;
									SuddenChangeEchoInformation[TempP].BestEchoP = 0;
								}
								for(TempP = 0; TempP < 4; TempP++)
									EchoPostionV[TempP] = 0;
								MarkBestWavePostionBackup = MarkBestWavePostion;
								ShowString(ASCII_6X16,"OK",88,2);
							}
							else if(MenuSelection == 3)
							{
								for(TempP = 0; TempP < 11; TempP++)
								{
									for(TempC = 0; TempC < 100; TempC++)
										RangeEchoInformation[TempP].CurveDataV[TempC] = 0;
									RangeEchoInformation[TempP].Distance = 0;
									RangeEchoInformation[TempP].BestEchoA = 0;
									RangeEchoInformation[TempP].BestEchoSignalR = 0;
									RangeEchoInformation[TempP].BestEchoP = 0;
									RangeReceordFlag[TempP] = 0;
								}
								ShowString(ASCII_6X16,"OK",88,6);
							}
						}
					}
				}
			}
		break;
		case LEFT:						//退到上一级菜单
 			if(CursorMoveH > 0xF0)
			{
				if(MenuIndex.MenuIndex_short != ZOOMCURVEPAGE)
				{
					TempC = 4;
					do
					{
						TempC--;
						if(MenuIndex.MenuIndexC[TempC] != 0)
						{
							MenuSelection = MenuIndex.MenuIndexC[TempC]-1;
							MenuIndex.MenuIndexC[TempC] = 0;
							break;
						}
					}while(TempC != 0);
				}
				else
				{
					MenuIndex.MenuIndex_short = MenuIndexBackup;
				}
				G_KeyValue = NO_KEY_STATUS;
				MenuSelection = 0;
				HandlePage();
			}
			else
			{
				Processed_DataType = NOTYPE;
				ModifyParaStatus = 0;
				CursorMoveH = VISBLEMENUCURSOR;
			}
			break;
		default:
		break;
	}
}

void HandleMenuPage_en()
{
	uchar TempC;
	switch(G_KeyValue)
	{
		case	DOWN:
			HandleOptionShift();
			break;
		case	UP:
			HandleDataInc();
			break;
		case	OK:												//进入下一级菜单
			if(NextMenuYesOrNo == TRUE)
			{
				for(TempC = 0; TempC < 4; TempC++)
				{
					if(MenuIndex.MenuIndexC[TempC] == 0)
					{
						MenuIndex.MenuIndexC[TempC] = MenuSelection+1;
						break;
					}
				}
				G_KeyValue = NO_KEY_STATUS;
				MenuSelection = 0;
				HandlePage();
			}
			else
			{
				if(CursorMoveH < 0xF0)
				{
					Processed_DataType = NOTYPE;
					CursorMoveH = VISBLEMENUCURSOR;
					ModifyParaStatus = 1;
				}
				else
				{
					CursorMoveH = VISBLEEDITCURSOR;
					if((MenuSelection >= (MaxMenuLine-1))&&(MenuIndex.MenuIndex_short == QUICKSETUPINTERFACE))
					{
						MenuIndex.MenuIndexC[2] = 3;//MenuSelection+1;
						MenuSelection = MaxMenuLine-1;//MenuIndex.MenuIndexC[1];
//						MenuIndex.MenuIndex_short = ECHOENTERPAGE;
						CursorMoveH = HIDECURSOR;
						G_KeyValue = NO_KEY_STATUS;
						HandlePage();
					}
					
					if((MenuSelection > 5)&&(MenuIndex.MenuIndex_short == BASICSETUPINTERFACE))
					{
						SendHartReadCmd(14);
						MenuIndex.MenuIndexC[2] = MenuSelection+1;
						MenuSelection = MenuIndex.MenuIndexC[1];
						G_KeyValue = NO_KEY_STATUS;
						HandlePage();
					}

					if((MenuSelection == 3)&&(MenuIndex.MenuIndex_short == CURRENTPARAPAGE))
						ModifyParaStatus = 1;
					if((MenuSelection == 0)&&(MenuIndex.MenuIndex_short == SYSTEMDISPAGE))
						ModifyParaStatus = 1;
				}
			}
		break;
		case LEFT:						//退到上一级菜单
 			if(CursorMoveH > 0xF0)
			{
				if(MenuIndex.MenuIndex_short != ZOOMCURVEPAGE)
				{
					TempC = 4;
					do
					{
						TempC--;
						if(MenuIndex.MenuIndexC[TempC] != 0)
						{
							MenuSelection = MenuIndex.MenuIndexC[TempC]-1;
							MenuIndex.MenuIndexC[TempC] = 0;
							break;
						}
					}while(TempC != 0);
				}
				else
				{
					MenuIndex.MenuIndex_short = MenuIndexBackup;
				}
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
			else
			{
				Processed_DataType = NOTYPE;
				ModifyParaStatus = 0;
				CursorMoveH = VISBLEMENUCURSOR;
			}
			break;
		default:
		break;
	}
}

void	DisplayPasswordInputPage(void)
{
	uchar TempC;
	CursorMoveH = HIDECURSOR;
	if(OtherParaU.OtherPara.Language == 0)
	{
		ClearLcdScreen( );
		ShowString(ASCII_6X16,"Please/input",28,0);
		ShowString(ASCII_6X16,"Password:",4,3);
	}
	else
		Display_MenuPage(Page_Password,0,1,5,38);
	for(TempC = 0; TempC < 5; TempC++)
	{
		ShowDataBuffe[TempC] = '0';								//初始化输入的密码值
	}
	ShowDataBuffe[5] = '\0';									//字符串结束符号
	CursorMoveH = 0;
	Processed_DataType = PASSWORDTYPE;
	ShowString(ASCII_6X16,ShowDataBuffe,55,3);						//显示字符串
	MenuIndex.MenuIndexC[0] = 2;									//当前显示界面为密码输入界面
}
void	JudgePasswordRightOrErro()
{
	uchar TempC;
	const uchar PasswordEerro[]={	7,8,9,10};						//密码错误
	IfFactoryPasswordRightErro = PasswordErro;
	IfUserPasswordRightErro = PasswordErro;
	for(TempC = 0; TempC < 5; TempC++)
	{
		if(ShowDataBuffe[TempC] != OtherParaU.OtherPara.UserPassword[TempC])	//输入的密码值与用户密码值比较
		{
			break;
		}
	}
	if((IfFactoryOrUserPassword) || (TempC != 5))						//如果要求输入出厂密码或者用户密码不对的话，再判断是否跟出厂密码一致
	{
		for(TempC = 0; TempC < 5; TempC++)
		{
			if(ShowDataBuffe[TempC] != FactoryPassword[TempC])			//输入的密码值与厂家密码值比较
			{
				break;
			}
		}
	}
	if(TempC == 5)
	{
		if(IfFactoryOrUserPassword)
		{
			IfFactoryPasswordRightErro = PasswordRight;				//输入的密码值与厂家密码值一致
		}
		else
		{
			IfUserPasswordRightErro = PasswordRight;					//输入的密码值与用户密码值一致
		}
	}
	else
	{//输入密码值错误时
//		ClearPasswordErrorInformation = 1;
		CursorMoveH = HIDECURSOR;
		if(IfFactoryOrUserPassword)
		{
			IfFactoryPasswordRightErro = PasswordErro;
//			Display_MenuPage(Page_FactoryPassword,0,1,7,22);
		}
		else
		{
			IfUserPasswordRightErro = PasswordErro;
		}
		if(OtherParaU.OtherPara.Language == 0)
			ShowString(ASCII_6X16,"Password/is/wrong",14,6);
		else
		{
			for(TempC = 0; TempC < 4; TempC++)
				DisplayChinese16X12(PasswordEerro[TempC],TempC*12+45,6);
		}
		CursorMoveH = 0;
	}
}
void	ReadMeterLimit(void)
{
	if(ReadUpperFlag == 0)
	{
		SendHartReadCmd(15);
		ReadUpperFlag = 1;
		MasterVariableU.MasterVariableF[6] = SystemParaU.SystemPara.QuickSetupPage_para[0]+2;//曲线不放大
		MasterVariableU.MasterVariableF[5] = 0;
		CurveLimitL = 0;
		CurveLimitH = 255;
		Curve_One_H = 255/LCDCURVEHIGH;
		CurveSwitch = 0;
		Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
	}
	if(MasterVariableU.MasterVariableF[6] > (SystemParaU.SystemPara.QuickSetupPage_para[0]+2))
	{
		MasterVariableU.MasterVariableF[6] = SystemParaU.SystemPara.QuickSetupPage_para[0]+2;
		Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
	}
	if(CurveSwitch != 1)
	{
		HartModfiyPara(188);
	}
	else
	{
		HartModfiyPara(189);
	}
}
void	HandleMainPage()
{
	unsigned char TempC;
	switch(G_KeyValue)
	{
		case	NO_KEY_STATUS:
			DisplayMeasurePageBackground();
			break;
		case	DOWN:
		  	if(OtherParaU.OtherPara.DisplayPage_Para[2] < 0x35)
				OtherParaU.OtherPara.DisplayPage_Para[2]++;
			else
				OtherParaU.OtherPara.DisplayPage_Para[2] = 0x35;
			LcdWriteCommand(0x81);
			LcdWriteCommand(OtherParaU.OtherPara.DisplayPage_Para[2]);
			DisplayMeasurePageBackground();
			if(RecordEchoFlag == 0)
			{
				RecordEchoFlag = 1;
				ShowString(ASCII_6X16, "R",95,4);//R
			}
			else
			{
				RecordEchoFlag = 0;
				ShowString(ASCII_6X16, "/",95,4);//
			}
			break;
		case	UP:
		  	if(OtherParaU.OtherPara.DisplayPage_Para[2] > 0x15)
				OtherParaU.OtherPara.DisplayPage_Para[2]--;
			else
				OtherParaU.OtherPara.DisplayPage_Para[2] = 0x15;
			LcdWriteCommand(0x81);
			LcdWriteCommand(OtherParaU.OtherPara.DisplayPage_Para[2]);
			if(ZoomMainDisplay == 0)
			{
				ClearLcdScreen();
				ZoomMainDisplay = 1;
			}
			else
			{
				ZoomMainDisplay = 0;
				DisplayMeasurePageBackground();
			}
			break;
		case	OK:						//进入下一级菜单
			for(TempC = 0; TempC < 5; TempC++)
			{
				if(OtherParaU.OtherPara.UserPassword[TempC] != 0x30)
					TempC = 10;
			}
			if(TempC == 11)
				DisplayPasswordInputPage();
			else
			{
				G_KeyValue = NO_KEY_STATUS;
				MenuIndex.MenuIndexC[0] = 1;
				HandlePage();
			}
		break;
		case LEFT:						//退到上一级菜单
			MenuIndex.MenuIndex_short = QUICKVIEWCURVE;
			G_KeyValue = NO_KEY_STATUS;
			HandlePage();
			break;
		default:
		break;
	}
}

void	HandlePasswordPage()
{
//	const uchar ClearPasswordEerro[]={0,0,0,0,0,0,0};						//清除密码错误信息
	uchar	TempC;
	switch(G_KeyValue)
	{
		case	DOWN:
			HandleOptionShift();
			ShowString(ASCII_6X16,ShowDataBuffe,55,3);						//显示字符串
			for(TempC = 0; TempC < 9; TempC++)
				DisplayChinese16X12(0,TempC*12+14,6);
			break;
		case	UP:
			HandleDataInc();
			ShowString(ASCII_6X16,ShowDataBuffe,55,3);						//显示字符串
			for(TempC = 0; TempC < 9; TempC++)
				DisplayChinese16X12(0,TempC*12+14,6);
			break;
		case	OK:						//进入下一级菜单
			JudgePasswordRightOrErro();
			if((IfFactoryPasswordRightErro == PasswordRight)||(IfUserPasswordRightErro == PasswordRight))
			{
				G_KeyValue = NO_KEY_STATUS;
				MenuIndex.MenuIndexC[0] = 1;
				HandlePage();
			}
		break;
		case LEFT:						//退到上一级菜单
			DisplayMeasurePageBackground();
			MenuIndex.MenuIndexC[0] = 0;
			break;
		default:
		break;
	}
}
//距离校正画面
void DisplayCDistancePage()
{
	float tempa=0;//,PreZero,PreRadio;
	unsigned char TempC;
	
	switch(G_KeyValue)
	{
		case NO_KEY_STATUS:
			ClearLcdScreen();
			if(OtherParaU.OtherPara.Language == 0)
			{
				ShowString(ASCII_6X16,"Reality//Measure",22,0);
				ShowString(ASCII_6X16,"Calibration/confirm",10,6);
			}
			else
			{
				Display_MenuSingleSelectionPage(Page_CalibrationD,0,1,9,10,0);
				Display_MenuSingleSelectionPage(Page_CalibrationDEnter,0,1,4,10,6);
			}
			for(TempC = 1; TempC < 3; TempC++)
			{
				ShowString(ASCII_6X16,":",16,2*TempC);
				ShowString(ASCII_6X16,"m",59,2*TempC);		//单位"m"
				ShowString(ASCII_6X16,"->",65,2*TempC);														//清除右上角的显示标示
				ShowString(ASCII_6X16,"m",116,2*TempC);		//单位"m"

				FloatToChar(RealityDistance[TempC-1],4);					//把浮点数转成字符数组
				ShowString(ASCII_6X16,ShowDataBuffe,22,2*TempC);					//显示浮点数字符串
				FloatToChar(MeasureDistance[TempC-1],4);					//把浮点数转成字符数组
				ShowString(ASCII_6X16,ShowDataBuffe,77,2*TempC);					//显示浮点数字符串
			}

			ShowString(ASCII_6X16,"1",10,2);
			ShowString(ASCII_6X16,"2",10,4);
			ShowString(ASCII_6X16,"<",4,2);														
			MenuSelection = 1;
			FrontOrBack = FRONT;
		break;
		case DOWN:
			if(CursorMoveH < 0xFD)
			{
				CursorMoveH++;
				if(CursorMoveH == 6)
				{
					if(FrontOrBack)
					{
						RealityDistance[MenuSelection-1] = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,22,2*MenuSelection);									//显示浮点数字符串
						FrontOrBack = 0;

						FloatToChar(MeasureDistance[MenuSelection-1],4);											//把浮点数转成字符数组
					}
					else
					{
						MeasureDistance[MenuSelection-1] = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,77,2*MenuSelection);									//显示浮点数字符串
						FrontOrBack = 1;

						FloatToChar(RealityDistance[MenuSelection-1],4);											//把浮点数转成字符数组
					}
					CursorMoveH = 0;
				}
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,22,2*MenuSelection);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,77,2*MenuSelection);										//显示浮点数字符串
				}
			}
			else
			{
				ShowString(ASCII_6X16,"/",4,MenuSelection*2);
				if(MenuSelection >= 3)
				{
					MenuSelection = 0;
				}
				MenuSelection++;
				ShowString(ASCII_6X16,"<",4,MenuSelection*2);														//清除右上角的显示标示
			}
		break;
		case UP:
			if(CursorMoveH < 0xFD)
			{//光标可以使用时
				EditDataAdd1();									//被编辑的数字加一
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,22,2*MenuSelection);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,77,2*MenuSelection);										//显示浮点数字符串
				}
			}
			else
			{
				ShowString(ASCII_6X16,"/",4,MenuSelection*2);
				if(MenuSelection <= 1)
				{
					MenuSelection = 4;
				}
				MenuSelection--;
				ShowString(ASCII_6X16,"<",4,MenuSelection*2);														//清除右上角的显示标示
			}
		break;
		case OK:
			if(CursorMoveH > 0xFD)
			{
				if(MenuSelection != 3)
				{
//					if(CurrentSlect_Current = 1)
					FrontOrBack = FRONT;
					FloatToChar(RealityDistance[MenuSelection-1],4);			//把浮点数转成字符数组
					CursorMoveH = 0;										//初始化光标位置，
					ShowString(ASCII_6X16,ShowDataBuffe,22,MenuSelection*2);		//显示浮点数字符串
				}
				else
				{
					if( ( (RealityDistance[1] > RealityDistance[0])&&(MeasureDistance[1] > MeasureDistance[0]) ) 
					|| ( (RealityDistance[1] < RealityDistance[0])&&(MeasureDistance[1] < MeasureDistance[0]) ))
					{
//						PreZero = SystemParaU.SystemPara.SystemZero;
//						PreRadio = SystemParaU.SystemPara.SystemRatio;
						
						MeasureDistance[0] = (MeasureDistance[0]+SystemParaU.SystemPara.SystemCoefficient[0]+MasterVariableU.MasterVariableF[0])/SystemParaU.SystemPara.SystemCoefficient[1];
						MeasureDistance[1] = (MeasureDistance[1]+SystemParaU.SystemPara.SystemCoefficient[0]+MasterVariableU.MasterVariableF[0])/SystemParaU.SystemPara.SystemCoefficient[1];
						MeasureDistance[0] = MeasureDistance[0]/MasterVariableU.MasterVariableF[1];
						MeasureDistance[1] = MeasureDistance[1]/MasterVariableU.MasterVariableF[1];
						SystemParaU.SystemPara.SystemCoefficient[1] =  (RealityDistance[1]-RealityDistance[0])/(MeasureDistance[1]-MeasureDistance[0]);
						SystemParaU.SystemPara.SystemCoefficient[1] = SystemParaU.SystemPara.SystemCoefficient[1]/MasterVariableU.MasterVariableF[1];
						if((SystemParaU.SystemPara.SystemCoefficient[1] < 0.5)||(SystemParaU.SystemPara.SystemCoefficient[1] > 5))
							SystemParaU.SystemPara.SystemCoefficient[1] = 1;
						HartModfiyPara(39);
						SystemParaU.SystemPara.SystemCoefficient[0] = MeasureDistance[0]*SystemParaU.SystemPara.SystemCoefficient[1]*MasterVariableU.MasterVariableF[1]-RealityDistance[0]-MasterVariableU.MasterVariableF[0];
						if((SystemParaU.SystemPara.SystemCoefficient[0] < -2)||(SystemParaU.SystemPara.SystemCoefficient[0] > 2))
							SystemParaU.SystemPara.SystemCoefficient[0] = 0;
						HartModfiyPara(39);
						
						RealityDistance[0] = 0;
						RealityDistance[1] = 0;
						MeasureDistance[0] = 0;
						MeasureDistance[1] = 0;
						for(TempC = 1; TempC < 3; TempC++)
						{
							FloatToChar(RealityDistance[TempC-1],4);					//把浮点数转成字符数组
							ShowString(ASCII_6X16,ShowDataBuffe,22,2*TempC);					//显示浮点数字符串
							FloatToChar(MeasureDistance[TempC-1],4);					//把浮点数转成字符数组
							ShowString(ASCII_6X16,ShowDataBuffe,77,2*TempC);					//显示浮点数字符串
						}
//						DisplayChinese16X12(278,60,6);				//'√'
					}
//					else
//						DisplayChinese16X12(279,60,6);				//'X'
				}
			}
			else
			{
				tempa = CharToFloat();
				CursorMoveH = VISBLEMENUCURSOR;
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,22,2*MenuSelection);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,77,2*MenuSelection);										//显示浮点数字符串
				}
				if( (tempa <= 40) && (tempa > 0) )							//判断数值是否在允许范围里
				{
					if(FrontOrBack)
					{
						RealityDistance[MenuSelection-1] = tempa;
					}
					else
					{
						 MeasureDistance[MenuSelection-1] = tempa;
					}
				}
			}
		break;
		case LEFT:
//			退到上一级菜单
//			LcdFlash=LCD_FLASH_YES;
 			if(CursorMoveH < 0xF0)
			{
				CursorMoveH = VISBLEMENUCURSOR;
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,22,2*MenuSelection);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,77,2*MenuSelection);										//显示浮点数字符串
				}
			}
			else
			{
//				CalculatePara(KeyValue);
				MenuIndex.MenuIndexC[2] = 0;
				MenuSelection = 2;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		default:
		break;
	}
}
void	DisplayDead(void)
{
	FloatToChar(SystemParaU.SystemPara.DeadZone[0],3);
	ShowDataBuffe[5] = '\0';
	ShowString(ASCII_5X8,ShowDataBuffe,25,0);
	FloatToChar(SystemParaU.SystemPara.DeadZone[1],3);
	ShowDataBuffe[5] = '\0';
	ShowString(ASCII_5X8,ShowDataBuffe,100,0);
}

void	DisplayZoomSart_End(void)
{
	float	TempF;
	if(MenuIndex.MenuIndex_short != MINDEADCURVE)
	{
		TempF = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
		FloatToChar(TempF,3);
		ShowDataBuffe[5] = '\0';
		ShowString(ASCII_5X8,ShowDataBuffe,25,0);
	}
	if(XZoom_Flag == 2)
	{
		TempF = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
		FloatToChar(TempF,3);
		ShowDataBuffe[5] = '\0';
		ShowString(ASCII_5X8,ShowDataBuffe,100,0);
	}
}

void	DisplayMeasureV_Amplitude(void)
{
	uchar TempC,TempP,TempD,TempData[5] = {0xC0,0xE0,0xF0,0xE0,0xC0};
	float	TempFloat;
	FloatToChar(MasterVariableU.MasterVariableF[0],3);
	ShowDataBuffe[5] = '\0';
	ShowString(ASCII_5X8,ShowDataBuffe,100,0);		//测量距离

	#ifdef GUIDERADAR
		TempFloat = MasterVariableU.MasterVariableF[7];
	#else
		TempFloat = SignalNoiseRadio;
		TempFloat = TempFloat*0.0129;
	#endif

	if(MenuIndex.MenuIndex_short == FAKEENTERPAGE)
		TempFloat = MasterVariableU.MasterVariableF[7];
	FloatToChar(TempFloat,2);					//回波信噪比或控制频率（导波）
	ShowDataBuffe[5] = '\0';
	ShowString(ASCII_5X8,ShowDataBuffe,62,0);
	
	TempFloat = MarkBestWaveAmplitude*0.0129;
	FloatToChar(TempFloat,2);					//回波分辨率
	ShowDataBuffe[5] = '\0';
	ShowString(ASCII_5X8,ShowDataBuffe,25,0);
	
	if((MarkBestWavePostion >= 2)&&(CurveSwitch != 1))
	{
		TempP = MarkBestWavePostion-2+LCDCURVESTARTCOLUMN;
		LcdSetPage(6);
		for(TempC = 0; TempC < 5; TempC++)
		{
			LcdSetColumn(TempC+TempP);
			TempD = LcdReadData()|TempData[TempC];

			LcdSetColumn(TempC+TempP);
			LcdWriteData(TempD);
		}
	}
}
void	CopyCurvePageInformation(CurvePageI *TempCurvePageI)
{
	uchar TempC;
	for(TempC = 0; TempC < 100; TempC++)
		TempCurvePageI->CurveDataV[TempC] = CurveData[TempC];
	TempCurvePageI->Distance = MasterVariableU.MasterVariableF[0];
	TempCurvePageI->BestEchoA = MarkBestWaveAmplitude;
	TempCurvePageI->BestEchoSignalR = SignalNoiseRadio;
	TempCurvePageI->BestEchoP = MarkBestWavePostion;
}
void	UpdateCurve(void)
{
	uchar TempC,TempN,TempMin;
	float TempF;
//	G_KeyValue = NO_KEY_STATUS;
	if(UpdateCurveFlag > 8)
	{
		ReHartSendCount = 0;
		for(TempC = 80; TempC < 85; TempC++)
		{
//			ReHartSendCount = 30;
			if(ReHartSendCount < 3)
				SendHartReadCmd(TempC+110);
		}
		if(MenuIndex.MenuIndex_short == QUICKVIEWCURVE)
		{
			#ifdef GUIDERADAR
				//SendFrameHeader(85,0);
				SendHartReadCmd(186);
			#else
				SendHartReadCmd(187);
			#endif
		}
		else
		{
			SendHartReadCmd(186);
		}
		if(MenuIndex.MenuIndex_short != MAININTERFACE)
		{
			if(CurveSwitch == 1)
			{
				CurveSwitchDoubleCurve++;
				if(CurveSwitchDoubleCurve > 2)
				{
					for(TempC = 0; TempC < 100; TempC++)
						FakeWaveCurve[TempC] = CurveData[TempC];
					ShowString(ASCII_6X16,"D",122,2);
					CurveSwitch = 2;
					CurveSwitchDoubleCurve = 0;
					UpdateCurveFlag = 7;
				}
			}
		}
	}
	else
		ReadMeterLimit();
	UpdateCurveFlag++;
	if(UpdateCurveFlag > CURVEUPDATE)
	{
		if(MenuIndex.MenuIndex_short != MAININTERFACE)
		{
			DrawChart();
			DisplayMeasureV_Amplitude();
			for(TempC = 0; TempC < 100; TempC++)
				ShowCurveData[TempC] = CurveData[TempC];
			DrawCurve();
	//		TempC = (uchar)MasterVariableU.MasterVariableF[7];
			if((CurveSwitch != 1)&&((ShowCurveData[80] <= 8)||(ShowCurveData[80] > 250)))//&&(TempC == RF_FREQUENCY))
			{
				HartModfiyPara(188);
			}
			if((MenuIndex.MenuIndex_short == FAKEENTERPAGE)||(MenuIndex.MenuIndex_short == QUICKVIEWCURVE))
			{
				if(CurveSwitch == 2)
				{
					for(TempC = 0; TempC < 100; TempC++)
						ShowCurveData[TempC] = FakeWaveCurve[TempC];
					DrawCurve();
				}
			}
		}
		TempF = SystemParaU.SystemPara.QuickSetupPage_para[0]-SystemParaU.SystemPara.QuickSetupPage_para[1];
		TempF = (MasterVariableU.MasterVariableF[0]-SystemParaU.SystemPara.QuickSetupPage_para[1])/TempF;
		if(TempF > 1)
			TempF = 1;
		TempN = (uchar)(TempF*100);
		if((TempN > 0)&&(TempN < 5)&&(RangeReceordFlag[0] == 0))//&&(MarkBestWavePostion < 6)&&(MarkBestWavePostion > 0))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[0] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 8)&&(TempN < 12)&&(RangeReceordFlag[1] == 0))//&&(MarkBestWavePostion < 18)&&(MarkBestWavePostion > 8))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[1] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 18)&&(TempN < 22)&&(RangeReceordFlag[2] == 0))//&&(MarkBestWavePostion < 28)&&(MarkBestWavePostion > 18))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[2] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 28)&&(TempN < 32)&&(RangeReceordFlag[3] == 0))//&&(MarkBestWavePostion < 38)&&(MarkBestWavePostion > 28))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[3] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 38)&&(TempN < 42)&&(RangeReceordFlag[4] == 0))//&&(MarkBestWavePostion < 48)&&(MarkBestWavePostion > 38))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[4] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 48)&&(TempN < 52)&&(RangeReceordFlag[5] == 0))//&&(MarkBestWavePostion < 58)&&(MarkBestWavePostion > 48))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[5] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 58)&&(TempN < 62)&&(RangeReceordFlag[6] == 0))//&&(MarkBestWavePostion < 68)&&(MarkBestWavePostion > 58))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[6] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 68)&&(TempN < 72)&&(RangeReceordFlag[7] == 0))//&&(MarkBestWavePostion < 78)&&(MarkBestWavePostion > 68))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[7] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 78)&&(TempN < 82)&&(RangeReceordFlag[8] == 0))//&&(MarkBestWavePostion < 88)&&(MarkBestWavePostion > 78))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[8] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 88)&&(TempN < 92)&&(RangeReceordFlag[9] == 0))//&&(MarkBestWavePostion < 98)&&(MarkBestWavePostion > 88))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[9] = 1;
			RecordEcohEnd = 1;
		}
		if((TempN > 95)&&(RangeReceordFlag[10] == 0))//&&(MarkBestWavePostion > 90))
		{
			for(TempC = 0; TempC < 11; TempC++)
			{
				RangeReceordFlag[TempC] = 0;
			}
			RangeReceordFlag[10] = 1;
			RecordEcohEnd = 1;
		}
		for(TempC = 0; TempC < 11; TempC++)
		{
			if((RangeReceordFlag[TempC] == 1)&&(RecordEcohEnd == 1))
			{
				CopyCurvePageInformation(&RangeEchoInformation[TempC]);
				RecordEcohEnd = 0;
			}
		}
		//记录跳变信号曲线
		if(MarkBestWavePostion != 0)
		{
			//MarkBestWavePostion、SignalNoiseRadio、MarkBestWaveAmplitude、MasterVariableU.MasterVariableF[0]
			TempMin = 0xFF;
			for(TempC = 0; TempC < 4; TempC++)
			{
				if(EchoPostionV[TempC] < TempMin)
				{
					TempMin = EchoPostionV[TempC];
					TempN = TempC;
				}
			}
			TempMin = TempN;

			if(MarkBestWavePostionBackup == 0)
				MarkBestWavePostionBackup = MarkBestWavePostion;
			if(MarkBestWavePostion > MarkBestWavePostionBackup)
				TempN = MarkBestWavePostion-MarkBestWavePostionBackup;
			else
				TempN = MarkBestWavePostionBackup-MarkBestWavePostion;
						
			if(TempN > EchoPostionV[TempMin])
			{
				TempF = InitEchoInformation[0].Distance-MasterVariableU.MasterVariableF[0];
				if((TempF > 0.006)||(TempF < -0.006))//(0-SystemParaU.SystemPara.ReceordCurvePage_para[0])))
				{
					EchoPostionV[TempMin] = TempN;
					TempMin = TempMin*2;
					CopyCurvePageInformation(&SuddenChangeEchoInformation[TempMin+1]);
					for(TempC = 0; TempC < 100; TempC++)
						SuddenChangeEchoInformation[TempMin].CurveDataV[TempC] = InitEchoInformation[0].CurveDataV[TempC];
					SuddenChangeEchoInformation[TempMin].Distance = InitEchoInformation[0].Distance;
					SuddenChangeEchoInformation[TempMin].BestEchoA = InitEchoInformation[0].BestEchoA;
					SuddenChangeEchoInformation[TempMin].BestEchoSignalR = InitEchoInformation[0].BestEchoSignalR;
					SuddenChangeEchoInformation[TempMin].BestEchoP = InitEchoInformation[0].BestEchoP;
					MarkBestWavePostionBackup = MarkBestWavePostion;
				}
			}
			else
			{
				CopyCurvePageInformation(&InitEchoInformation[0]);
			}
		}
		UpdateCurveFlag = CURVEUPDATE;
	}
}

void	CurveSetKey()
{
	if((YZoom_Flag == 0)&&(XZoom_Flag == 0)&&(CurveSwitch == 0)&&(MenuIndex.MenuIndex_short != LOWERDEADSETPAGE)&&(MenuIndex.MenuIndex_short != HIGHDEADSETPAGE))
	{
		MenuIndexBackup = MenuIndex.MenuIndex_short;
		MenuIndex.MenuIndexC[0] = 8;
		MenuIndex.MenuIndexC[1] = 0;
		MenuIndex.MenuIndexC[2] = 0;
		MenuIndex.MenuIndexC[3] = 0;
		G_KeyValue = NO_KEY_STATUS;
		HandlePage();
	}
	if(XZoom_Flag == 2)
	{
		switch(MenuIndex.MenuIndex_short)
		{
			case	XZOOMCURVEPAGE:
				MasterVariableU.MasterVariableF[6] = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				MasterVariableU.MasterVariableF[5] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
//				ModfiyPara(7,2);
				Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
				MenuIndex.MenuIndex_short = MenuIndexBackup;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
				break;
			case	MODFYPCURVEPAGE:
				MasterVariableU.MasterVariableF[3] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				MasterVariableU.MasterVariableF[4] = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				MasterVariableU.MasterVariableF[2] = MasterVariableU.MasterVariableF[5];
				MasterVariableU.MasterVariableF[5] = 0;
				HartModfiyPara(189);
				MasterVariableU.MasterVariableF[5] = MasterVariableU.MasterVariableF[2];
				ReturnDoubleCurve();
				break;
			case	THRESHOLDCURVE:
				SystemParaU.SystemPara.DeadZone[1] = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				SystemParaU.SystemPara.DeadZone[0] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				HartModfiyPara(40);
				break;
//			case	MINDEADCURVE:
//			case	MAXDEADCURVE:
//			case	HIGHDEADSETPAGE:
			case	LOWERDEADSETPAGE:
//				if(DeadSetFlag == 0x5A)
//				{
					SystemParaU.SystemPara.DeadZone[1] = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
					XZoom_Flag = 0;
					HartModfiyPara(41);
//					DeadSetFlag = 0;
//				}
//				else
//				{
//					MasterVariableU.MasterVariableF[6] = (Zoom_X[1]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
//					MasterVariableU.MasterVariableF[5] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
//					ModfiyPara(7,2);
//					Page_One_M = (MasterVariableU.MasterVariableF[6]-MasterVariableU.MasterVariableF[5])/100;
//				}
				MenuIndex.MenuIndex_short = MenuIndexBackup;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
				break;
			default:break;
		}
		DiplayCureXY();
		XZoom_Flag = 0;
	}
	if((YZoom_Flag == 2)&&(MenuIndex.MenuIndex_short ==  YZOOMCURVEPAGE))
	{
		CurveLimitL = (uchar)((LCDCURVELLIMIT-Zoom_Y[0])*Curve_One_H)+CurveLimitL;
		CurveLimitH = (uchar)((LCDCURVELLIMIT-Zoom_Y[1])*Curve_One_H)+CurveLimitL;
		Curve_One_H = (float)(CurveLimitH-CurveLimitL);
		Curve_One_H = Curve_One_H/LCDCURVEHIGH;
//		ModfiyPara(7,2);
		YZoom_Flag = 0;
		MenuIndex.MenuIndex_short = MenuIndexBackup;
		G_KeyValue = NO_KEY_STATUS;
		HandlePage();
	}
	if(XZoom_Flag == 1)
	{
		if((MenuIndex.MenuIndex_short == MODFYNCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYHCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYLCURVEPAGE))
		{
			MasterVariableU.MasterVariableF[4] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
			MasterVariableU.MasterVariableF[3] = 70+MenuIndex.MenuIndexC[2];
			HartModfiyPara(189);
			ReturnDoubleCurve();
		}
		else
		{
			if(MenuIndex.MenuIndex_short == HIGHDEADSETPAGE)
			{
				SystemParaU.SystemPara.DeadZone[0] = (Zoom_X[0]-21)*Page_One_M+MasterVariableU.MasterVariableF[5];
				HartModfiyPara(40);
				XZoom_Flag = 0;
//				DeadSetFlag = 0;
				MenuIndex.MenuIndex_short = MenuIndexBackup;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
			else
			{
				XZoom_Flag = 2;
				Zoom_X[1] = Zoom_X[0]+30;
				DrawHLine(Zoom_X[1]);
				DisplayZoomSart_End();
			}
		}
	}
	if(YZoom_Flag == 1)
	{
		if(MenuIndex.MenuIndex_short == THRESHOLDSETPAGE)
		{
			OtherParaU.OtherPara.EchoMinAmplitude = (uchar)((LCDCURVELLIMIT-Zoom_Y[0])*Curve_One_H)+CurveLimitL;
			TXByteCtr = 1;
			HartModfiyPara(25);
			WriteParaToEEprom(OTHERPARAADDRESS+15,&OtherParaU.OtherPara.EchoMinAmplitude);
			YZoom_Flag = 0;
			MenuIndex.MenuIndex_short = MenuIndexBackup;
			G_KeyValue = NO_KEY_STATUS;
			HandlePage();
		}
		else
		{
			YZoom_Flag = 2;
			Zoom_Y[1] = Zoom_Y[0]-8;
			DrawVMoveLine(Zoom_Y[1]);
		}
	}
}

void	CurvePage(void)
{
	uchar TempC;
	switch(G_KeyValue)
	{
		case	NO_KEY_STATUS:
			ClearLcdScreen();											//清屏
			DrawChart();
			DisplayMeasureV_Amplitude();
			DiplayCureXY();
			DrawCurve();
			XZoom_Flag = 0;
			YZoom_Flag = 0;
			switch(MenuIndex.MenuIndex_short)
			{
//				case THRESHOLDCURVE:
//					SendFrameHeader(25,1);
//					Zoom_Y[0] = LCDCURVELLIMIT-(uchar)((OtherParaU.OtherPara.EchoMinAmplitude-CurveLimitL)/Curve_One_H);
//				break;
				case XZOOMCURVEPAGE:
				case MODFYNCURVEPAGE:
				case MODFYHCURVEPAGE:
				case MODFYLCURVEPAGE:
				case MODFYPCURVEPAGE:
					Zoom_X[0] = 21;
					if(MenuIndex.MenuIndex_short == MODFYHCURVEPAGE)
						Zoom_X[0] = 60;
					if(MenuIndex.MenuIndex_short == MODFYLCURVEPAGE)
						Zoom_X[0] = 90;
					XZoom_Flag = 1;
					DrawHLine(Zoom_X[0]);
					DisplayZoomSart_End();
				break;
				case YZOOMCURVEPAGE:
					Zoom_Y[0] = 54;
					YZoom_Flag = 1;
					DrawVMoveLine(Zoom_Y[0]);
				break;
				case HIGHDEADSETPAGE:
					SendHartReadCmd(14);
					if((SystemParaU.SystemPara.DeadZone[0] >= MasterVariableU.MasterVariableF[5])&&(SystemParaU.SystemPara.DeadZone[0] < MasterVariableU.MasterVariableF[6]))
					{
						Zoom_X[0] = (uchar)((SystemParaU.SystemPara.DeadZone[0]-MasterVariableU.MasterVariableF[5])/Page_One_M+21);
						DrawHLine(Zoom_X[0]);
//						DeadSetFlag = 0x5A;
						XZoom_Flag = 1;
					}
					if((SystemParaU.SystemPara.DeadZone[1] > MasterVariableU.MasterVariableF[5])&&(SystemParaU.SystemPara.DeadZone[1] < MasterVariableU.MasterVariableF[6]))
					{
						Zoom_X[1] = (uchar)((SystemParaU.SystemPara.DeadZone[1]-MasterVariableU.MasterVariableF[5])/Page_One_M+21);
					}
					else
						Zoom_X[1] = 120;
					DisplayDead();
				break;
				case LOWERDEADSETPAGE:
					SendHartReadCmd(14);
					if((SystemParaU.SystemPara.DeadZone[1] > MasterVariableU.MasterVariableF[5])&&(SystemParaU.SystemPara.DeadZone[1] < MasterVariableU.MasterVariableF[6]))
					{
						Zoom_X[1] = (uchar)((SystemParaU.SystemPara.DeadZone[1]-MasterVariableU.MasterVariableF[5])/Page_One_M+21);
						DrawHLine(Zoom_X[1]);
//						DeadSetFlag = 0x5A;
						XZoom_Flag = 2;
					}
					if((SystemParaU.SystemPara.DeadZone[0] > MasterVariableU.MasterVariableF[5])&&(SystemParaU.SystemPara.DeadZone[0] < MasterVariableU.MasterVariableF[6]))
					{
						Zoom_X[0] = (uchar)((SystemParaU.SystemPara.DeadZone[0]-MasterVariableU.MasterVariableF[5])/Page_One_M+21);
					}
					else
						Zoom_X[0] = 21;
					DisplayDead();
				break;
				case THRESHOLDSETPAGE:
					SendHartReadCmd(70);
					Zoom_Y[0] = LCDCURVELLIMIT-(uchar)((OtherParaU.OtherPara.EchoMinAmplitude-CurveLimitL)/Curve_One_H);
					DrawVMoveLine(Zoom_Y[0]);
					YZoom_Flag = 1;
				break;
				default:
					Zoom_X[0] = 21;
					Zoom_Y[0] = 55;
					XZoom_Flag = 0;
					YZoom_Flag = 0;
				break;
			}
			switch(CurveSwitch)
			{
				case 0:
					ShowString(ASCII_6X16,"E",122,2);
					break;
//				case 1:
//					ShowString(ASCII_6X16,"F",122,2);
//					break;
				case 2:
					ShowString(ASCII_6X16,"D",122,2);
					break;
				default:break;
			}
			break;
		case	DOWN:
			DrawChart();
			DrawCurve();
 			if(YZoom_Flag == 0)
			{
				if(XZoom_Flag > 0)
				{
					if(XZoom_Flag == 2)
					{
						TempC = 121;
						if(MenuIndex.MenuIndex_short != LOWERDEADSETPAGE)
							DrawHLine(Zoom_X[0]);
					}
					else 
					{
						if((MenuIndex.MenuIndex_short == MODFYNCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYHCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYLCURVEPAGE))
							TempC = 120;
						else
							TempC = 90;
					}
					if((XZoom_Flag == 0)&&((MenuIndex.MenuIndex_short == MODFYNCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYHCURVEPAGE)||(MenuIndex.MenuIndex_short == MODFYLCURVEPAGE)))
						XZoom_Flag = 1;
					Zoom_X[XZoom_Flag-1]++;
					if(Zoom_X[XZoom_Flag-1] > TempC)
						Zoom_X[XZoom_Flag-1] = TempC;
					DrawHLine(Zoom_X[XZoom_Flag-1]);
					DisplayZoomSart_End();
				}
			}
			else if(YZoom_Flag >= 1)
			{
				if(YZoom_Flag == 2)
				{
					TempC = Zoom_Y[0]-3;
					DrawVMoveLine(Zoom_Y[0]);
				}
				else
					TempC = 53;
				if(Zoom_Y[YZoom_Flag-1] == TempC)
					Zoom_Y[YZoom_Flag-1] = TempC+1;
				if(Zoom_Y[YZoom_Flag-1] > TempC)
					Zoom_Y[YZoom_Flag-1] = TempC;
				Zoom_Y[YZoom_Flag-1]++;
				DrawVMoveLine(Zoom_Y[YZoom_Flag-1]);
			}
			break;
		case	UP:
			DrawChart();
			DrawCurve();
 			if(XZoom_Flag == 0)
			{
				switch(MenuIndex.MenuIndex_short)
				{
					case YZOOMCURVEPAGE:
					case THRESHOLDSETPAGE:
						if(YZoom_Flag == 2)
						{
							TempC = 7;
							DrawVMoveLine(Zoom_Y[0]);
						}
						else
							TempC = 9;
						if(Zoom_Y[YZoom_Flag-1] <= TempC)
							Zoom_Y[YZoom_Flag-1] = TempC+1;
						Zoom_Y[YZoom_Flag-1]--;
						DrawVMoveLine(Zoom_Y[YZoom_Flag-1]);
					break;
					case FAKEENTERPAGE:
					case QUICKVIEWCURVE:
						UpdateCurveFlag = 8;
						CurveSwitch++;
						if(CurveSwitch >= 3)
							CurveSwitch = 0;
						switch(CurveSwitch)
						{
							case 0:
//								ModfiyPara(7,2);
								UpdateCurveFlag = CURVEUPDATE;
								ShowString(ASCII_6X16,"E",122,2);
								break;
							case 1:
								MasterVariableU.MasterVariableF[3] = 0;//MasterVariableU.MasterVariableF[5];
								MasterVariableU.MasterVariableF[4] = 0;//MasterVariableU.MasterVariableF[6];
//								ModfiyPara(5,2);
								CurveSwitchDoubleCurve = 0;
								ShowString(ASCII_6X16,"D",122,2);
								break;
							case 2:
//								for(TempC = 0; TempC < 100; TempC++)
//									FakeWaveCurve[TempC] = CurveData[TempC];
//								ModfiyPara(7,2);
//								ShowString(ASCII_6X16,"D",122,2);
								break;
							default:break;
						}
						DrawChart();
					break;
					default:break;
				}
			}
			else
			{
				if(XZoom_Flag == 2)
				{
					TempC = Zoom_X[0]+8;
					if(MenuIndex.MenuIndex_short != LOWERDEADSETPAGE)
						DrawHLine(Zoom_X[0]);
				}
				else
					TempC = 21;
				if(Zoom_X[XZoom_Flag-1] == TempC)
					Zoom_X[XZoom_Flag-1] = TempC+1;
				Zoom_X[XZoom_Flag-1]--;
				DrawHLine(Zoom_X[XZoom_Flag-1]);
				DisplayZoomSart_End();
			}
			break;
		case	OK:												//进入下一级菜单
			CurveSetKey();
		break;
		case LEFT:						//退到上一级菜单
			if((XZoom_Flag == 0)&&(YZoom_Flag == 0))
			{
				if(MenuIndex.MenuIndex_short != QUICKVIEWCURVE)
				{
					if(MenuIndex.MenuIndexC[2] == 0)
						MenuIndex.MenuIndexC[1] = 0;
					else
						MenuIndex.MenuIndexC[2] = 0;
//					MenuIndex.MenuIndexC[1] = MenuSelection;
//					MenuSelection = 0;
				}
				else
					MenuIndex.MenuIndex_short = MAININTERFACE;
				MenuSelection = 0;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
			else
			{
				if((MenuIndex.MenuIndex_short <= THRESHOLDSETPAGE))
				{
					MenuIndex.MenuIndex_short = 8;
					G_KeyValue = NO_KEY_STATUS;
					HandlePage();
				}
				else
				{
					DrawChart();
					DrawCurve();
					XZoom_Flag = 0;
					YZoom_Flag = 0;
				}
			}
//			DeadSetFlag = 0;
		default:
		break;
	}
}

void	ViewRecordCurvePage(void)
{
	uchar TempC,TempString[2];
	switch(G_KeyValue)
	{
		case	NO_KEY_STATUS:
			ViewCount = 0;
			ReadMeterLimit();
			ClearLcdScreen();											//清屏
			DiplayCureXY();
			break;
		case	DOWN:
			ViewCount++;
			if(MenuSelection == 0)
			{
				if(ViewCount >= 8)
					ViewCount = 0;
			}
			else if(MenuSelection == 2)
			{
				if(ViewCount >= 11)
					ViewCount = 0;
			}
			break;
		case	UP:
			if(MenuSelection == 0)
			{
				if(ViewCount == 0)
					ViewCount = 8;
			}
			else if(MenuSelection == 2)
			{
				if(ViewCount == 0)
					ViewCount = 12;
			}
			ViewCount--;
			break;
		case	OK:												//进入下一级菜单
//			CurveSetKey();
		break;
		case LEFT:						//退到上一级菜单
			MenuIndex.MenuIndex_short = MenuIndexBackup;
			MenuSelection = 0;
			G_KeyValue = NO_KEY_STATUS;
			HandlePage();
		default:
		break;
	}
	if(MenuIndex.MenuIndex_short == VIEWRECORDCURVEECHO)
	{
		if(MenuSelection == 0)
		{
			for(TempC = 0; TempC < 100; TempC++)
				ShowCurveData[TempC] = SuddenChangeEchoInformation[ViewCount].CurveDataV[TempC];
			MasterVariableU.MasterVariableF[0] = SuddenChangeEchoInformation[ViewCount].Distance;
			MarkBestWaveAmplitude = SuddenChangeEchoInformation[ViewCount].BestEchoA;
			SignalNoiseRadio = SuddenChangeEchoInformation[ViewCount].BestEchoSignalR;
			MarkBestWavePostion = SuddenChangeEchoInformation[ViewCount].BestEchoP;
		}
		else if(MenuSelection == 2)
		{
			for(TempC = 0; TempC < 100; TempC++)
				ShowCurveData[TempC] = RangeEchoInformation[ViewCount].CurveDataV[TempC];
			MasterVariableU.MasterVariableF[0] = RangeEchoInformation[ViewCount].Distance;
			MarkBestWaveAmplitude = RangeEchoInformation[ViewCount].BestEchoA;
			SignalNoiseRadio = RangeEchoInformation[ViewCount].BestEchoSignalR;
			MarkBestWavePostion = RangeEchoInformation[ViewCount].BestEchoP;
		}
		DrawChart();
		DrawCurve();
		DisplayMeasureV_Amplitude();
		TempString[0] = 0x30+ViewCount;
		TempString[1] = '\0';
		ShowString(ASCII_6X16,TempString,122,2);
	}
}

void	HandlePage()
{
	switch(MenuIndex.MenuIndex_short)
	{
		case	MAININTERFACE:
			SystemParaU.SystemPara.QuickSetupPage_para[3] = 0;
			HandleMainPage();
		break;
		case	MAINMENUPAGE:
			NextMenuYesOrNo = TRUE;
			MaxMenuLine = 10;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&MainMenuePage_en[0][0],10,14);
			else
				HandleMenuPage(Page_MainMenu,10,4);
//			SendHartReadCmd(247);
		break;
		case	INPUTPASSWORDINTERFACE:
			HandlePasswordPage();
		break;
		case	WRITINGPARAPAGE:
			if(G_KeyValue == LEFT)
			{
				MenuIndex.MenuIndex_short = PARASAFEPAGE;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		case	QUICKSETUPINTERFACE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(15);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if((MenuIndex.MenuIndexC[1] == 1)&&(MenuIndex.MenuIndexC[2] == 0))
					DisplayDisplayQuicksetupPage_Para_en();
			}
			else
			{
				if(SystemParaU.SystemPara.QuickSetupPage_para[2] > 0)
					HandleMenuPage(Page_QuickSetup_G,4,4);
				else
					HandleMenuPage(Page_QuickSetup,3,4);
				if((MenuIndex.MenuIndexC[1] == 1)&&(MenuIndex.MenuIndexC[2] == 0))
					DisplayDisplayQuicksetupPage_Para();
			}
		break;
		case	BASICSETUPINTERFACE:
			if(NextMenuYesOrNo == TRUE)
			{
//				SendHartReadCmd(14);
				SendHartReadCmd(80);
			}
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			CurveSwitch = 0;
//			SendFrameHeader(,2);
			HandleMenuPage_en();
			if(MenuIndex.MenuIndexC[1] == 2)
				DisplayBasicSetupPage_Para();
		break;
		case	DISPLAYSETUPPAGE:
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			HandleMenuPage_en();
			if(MenuIndex.MenuIndexC[1] == 3)
				DisplayDisplaySetupPage_Para_en();
		break;
		case	SYSTEMSETUPPAGE:
			SystemParaU.SystemPara.CurrentSetup[1] = 4;
			SystemParaU.SystemPara.CurrentSetup[2] = 18;
			MaxMenuLine = 5;
			NextMenuYesOrNo = TRUE;
//			ArrowPosition = 60;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&Page_SystemSetup_en[0][0],5,21);
			else
				HandleMenuPage(Page_SystemSetup,5,4);
		break;
		case	LINEARIZATIONPAGE:
//			ArrowPosition = 105;
			if(NextMenuYesOrNo == TRUE)
			{
				SendHartReadCmd(157);
			}
			NextMenuYesOrNo = FALSE;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if(MenuIndex.MenuIndexC[1] == 5)
					DisplayLine_Para_en();
			}
			else
			{
				HandleMenuPage(Page_Linearization,4,4);
				if(MenuIndex.MenuIndexC[1] == 5)
					DisplayLine_Para();
			}
		break;
		case	SECURESETUPPAGE:
			MaxMenuLine = 4;
			NextMenuYesOrNo = TRUE;
//			ArrowPosition = 60;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&Page_SecureSetup_en[0][0],4,18);
			else
				HandleMenuPage(Page_SecureSetup,4,4);
		break;
		case	HARTCPAGE:
			//SendFrameHeader(17,2);
			if(NextMenuYesOrNo == TRUE)
			{
				SendHartReadCmd(90);
			}
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage(&Page_HartCSetup_en[0][0],2,8);
			}
			else
				HandleMenuPage(Page_HartCSetup,2,4);
			if(MenuIndex.MenuIndexC[1] == 7)
				DisplayHartC_Para();
		break;
		case	SYSTEMDISPAGE:
			if(NextMenuYesOrNo == TRUE)
			{
				SendHartReadCmd(90);
			}
//			ArrowPosition = 80;
			//SendFrameHeader(31,2);
			NextMenuYesOrNo = FALSE;
			
			if((MenuSelection != 2)&&(G_KeyValue != UP))
				HandleMenuPage_en();
//			else
				
			if(MenuIndex.MenuIndexC[1] == 8)
				DisplayMaxMinPage();

//			MaxMenuLine = 1;
//			NextMenuYesOrNo = TRUE;
//			ArrowPosition = 60;
//			HandleMenuPage(Page_SystemDiagnosis,1,4);
		break;
		case	ECHOADJUDGEPAGE:
//			ArrowPosition = 105;
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(85);
			NextMenuYesOrNo = FALSE;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if(MenuIndex.MenuIndexC[2] == 1)
					DisplayEchoAdjudgePage_Para_en();
			}
			else
			{
				HandleMenuPage(Page_EchoAdjudge,4,5);
				if(MenuIndex.MenuIndexC[2] == 1)
					DisplayEchoAdjudgePage_Para();
			}
		break;
		case	CURRENTPARAPAGE:
			NextMenuYesOrNo = FALSE;
			HandleMenuPage_en();
			if(CursorMoveH >= 0xFD)
			{
				if(G_KeyValue != NO_KEY_STATUS)
				{
					switch(MenuSelection)
					{
						case	1:
							SystemParaU.SystemPara.CurrentSetup[0] = 4;
							HartModfiyPara(I2CURRENTADDRESS);
						break;
						case	2:
							SystemParaU.SystemPara.CurrentSetup[0] = 18;
							HartModfiyPara(I2CURRENTADDRESS);
						break;
						default:break;
					}
				}
				else
				{
					SystemParaU.SystemPara.CurrentSetup[0] = 0;
					HartModfiyPara(I2CURRENTADDRESS);
				}
			}
			if(MenuIndex.MenuIndexC[2] == 2)
				DisplayCurrentSetupPage_Para(); 
		break;
		case	DISTANCEPARAPAGE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(149);
			NextMenuYesOrNo = FALSE;
//			if(MenuIndex.MenuIndexC[2] == 3)
			DisplayCDistancePage();
		break;
		case	MAPPINGPARAPAGE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(245);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage(&Page_Mapping_en[0][0],2,10);
			}
			else
				HandleMenuPage(Page_Mapping,2,4);
			if(MenuIndex.MenuIndexC[2] == 5)
				DisplayMappingParaPage_Para();
		break;
		case	DISTANCECOEFFICIENTPAGE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(153);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage(&Page_Coefficient_en[0][0],2,8);
			}
			else
				HandleMenuPage(Page_Coefficient,2,4);
			if(MenuIndex.MenuIndexC[2] == 4)
				DisplayCoefficientPage_Para();
		break;
//		case	FZOOMCURVERPAGE:
		case	ZOOMCURVEPAGE:
			if(MenuIndexBackup == FAKEENTERPAGE)
			{
				MaxMenuLine = 8;
				CurveStartEnd[0] = MasterVariableU.MasterVariableF[5];
				CurveStartEnd[1] = MasterVariableU.MasterVariableF[6];
			}
			else
				MaxMenuLine = 3;
			NextMenuYesOrNo = TRUE;
//			ArrowPosition = 80;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&CurveMenue_en[0][0],8,16);
			else
				HandleMenuPage(Page_ZoomCurvePage,8,6);
			if((MenuIndex.MenuIndexC[1] == 0)&&(MenuIndex.MenuIndexC[0] == 8)&&(MenuSelection < 4)&&(OtherParaU.OtherPara.Language == 1))
			{
				ShowString(ASCII_6X16, "X",15,0);
				ShowString(ASCII_6X16, "Y",15,2);
			}
			else if(MenuIndex.MenuIndex_short == NOZOOMCURVEPAGE)
			{
				ReadUpperFlag = 0;
				MenuIndex.MenuIndex_short = MenuIndexBackup;
				G_KeyValue = NO_KEY_STATUS;
				CurveSwitch = 0;
				HandlePage();
			}
		break;
		case	XZOOMCURVEPAGE:
		case	YZOOMCURVEPAGE:
		case	MODFYNCURVEPAGE:
		case	MODFYHCURVEPAGE:
		case	MODFYLCURVEPAGE:
		case	MODFYPCURVEPAGE:
		case	FAKEENTERPAGE:
		case	QUICKVIEWCURVE:
		case	HIGHDEADSETPAGE:
		case	LOWERDEADSETPAGE:
		case	THRESHOLDSETPAGE:
		case	MODFYDCURVEPAGE:
			UpdateCurveFlag = CURVEUPDATE;
			ReadMeterLimit();
			CurvePage();
		break;
		case	MAXMINRECORDPAGE:
//			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 80;
//			HandleMenuPage(Page_DiagnosisRecond,3,5);
//			if(MenuIndex.MenuIndexC[2] == 1)
//				DisplayMaxMinPage();
		break;
		case DLINEARPAGE:
			LineOrScale = 0;
			if(CursorMoveH > 0xFD)
			{
				SendHartReadCmd(150);
//				SendHartReadCmd151(LinearParaU.LinearPara.LinePointsNum,LinearParaU.LinearPara.LinePointsNum);
			}
			UnitString = "m";
			if(DLineS == 0)
			 	Show_Add_Linear_Para(&LinearParaU.LinearPara.LinearParaFB[0][0]);
			else
				Show_Edit_Linear_Para(&LinearParaU.LinearPara.LinearParaFB[0][0]);
		break;
		case SLINEARPAGE:
			UnitString = "@";//"%"
			LineOrScale = 1;
			if(CursorMoveH > 0xFD)
			{
				SendHartReadCmd(160);
			}
			if(DLineS == 0)
			 	Show_Add_Linear_Para(&LinearParaU.LinearPara.ScaleParaFB[0][0]);
			else
				Show_Edit_Linear_Para(&LinearParaU.LinearPara.ScaleParaFB[0][0]);
		break;
		case SECUREUNECHOPAGE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(83);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if(MenuIndex.MenuIndexC[2] == 1)
					DisplayUnechoPage_Para_en();
			}
			else
			{
				HandleMenuPage(Page_Unecho,2,4);
				if(MenuIndex.MenuIndexC[2] == 1)
					DisplayUnechoPage_Para();
			}
		break;
		case SECUREJUMPPAGE:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(84);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 112;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if(MenuIndex.MenuIndexC[2] == 2)
					DisplayJumpPage_Para_en();
			}
			else
			{
				HandleMenuPage(Page_JumpSetup,4,4);
				if(MenuIndex.MenuIndexC[2] == 2)
					DisplayJumpPage_Para();
			}
		break;
		case	SECUREOTHER:
			if(NextMenuYesOrNo == TRUE)
				SendHartReadCmd(70);
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			HandleMenuPage_en();
			if(MenuIndex.MenuIndexC[2] == 3)
			{
				DisplayOtherSecure_Para();
			}
		break;
		case	PARASAFEPAGE:
			NextMenuYesOrNo = FALSE;
//			ArrowPosition = 105;
			HandleMenuPage_en();
			if(MenuIndex.MenuIndexC[2] == 4)
			{
				DisplayParaSafe_Para();
				if(ModifyParaStatus == 1)
				{
					if((MenuSelection == 1) || (MenuSelection == 3))
					{
						IfFactoryOrUserPassword = 1;
						JudgePasswordRightOrErro();
						if(IfFactoryPasswordRightErro == PasswordRight)
						{
							if(MenuSelection == 1)
							{
								MenuIndex.MenuIndex_short = WRITINGPARAPAGE;
								ResumeParameterType = 0xAA;
								ParaAddressCopying = 10;
								WriteParaProgress = 20;
							}
							else if(MenuSelection == 3)
							{
								ResumeParameterType = 0x5A;
								HartModfiyPara(31);
							}
						}
					}
				}
			}
		break;
		case SYSTEMINFORMATION:
//			ArrowPosition = 122;
			NextMenuYesOrNo = FALSE;
			//SendFrameHeader(30,0);
			HandleMenuPage_en();
			//SendFrameHeader(27,0);
			if(MenuIndex.MenuIndexC[1] == 9)
				DisplaySystemInformation();
		break;
		case	SETCURVERANGEPAGE:
			NextMenuYesOrNo = FALSE;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage(&Page_Mapping_en[0][0],2,10);
			}
			else
				HandleMenuPage(Page_CurveRange,3,4);
			if(MenuIndex.MenuIndexC[1] == 4)
				DisplayCurveRangePage_Para();
		break;
		case	SYSTEMRECORDCURVE:
			MaxMenuLine = 2;
			NextMenuYesOrNo = TRUE;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&Page_CurveView_en[0][0],2,20);
			else
				HandleMenuPage(Page_CurveView,2,5);
		break;
		case	VIEWCURVEMEASURED:
			NextMenuYesOrNo = FALSE;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage_en();
				if((MenuIndex.MenuIndexC[1] == 10)&&(MenuIndex.MenuIndexC[2] == 2))
					DisplayDisplayQuicksetupPage_Para_en();
			}
			else
			{
				HandleMenuPage(Page_ViewCurveM,4,4);
				if((MenuIndex.MenuIndexC[1] == 10)&&(MenuIndex.MenuIndexC[2] == 2))
					DisplayDisplayViewCurveMPage_Para();
			}
		break;
		case	VIEWCURVEECHO:
			MaxMenuLine = 4;
			NextMenuYesOrNo = FALSE;
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&Page_EchoCurveView_en[0][0],2,16);
			else
				HandleMenuPage(Page_EchoCurveView,4,4);
		break;
		case	VIEWRECORDCURVEECHO:
			ViewRecordCurvePage();
		break;
		case	FAKEMODIFYPAGE:
			MaxMenuLine = 5;
			NextMenuYesOrNo = TRUE;
			MasterVariableU.MasterVariableF[2] = MasterVariableU.MasterVariableF[5];
			if(OtherParaU.OtherPara.Language == 0)
				HandleMenuPage(&Page_FakeEchoCurveModify_en[0][0],6,10);
			else
				HandleMenuPage(Page_FakeEchoCurveModify,6,4);
		break;
		case MODFYMCURVEPAGE:
			NextMenuYesOrNo = FALSE;
			MaxMenuLine = 4;
			if(OtherParaU.OtherPara.Language == 0)
			{
				HandleMenuPage(&Page_Mapping_en[0][0],2,10);
			}
			else
				HandleMenuPage(Page_FakeEchoVModify,4,2);
			if(MenuIndex.MenuIndexC[2] == 5)
				DisplayFakeEchoVModify_Para();
		break;
		default:break;
	}
	ModifyParaStatus = 0;
}

void	PageStartInformation(void)
{
	uchar	TempC;
	uchar	const StartInformation[7] = {84,173,174,115,212,103,157};
//	uchar	const PInformation[4] = {};
	Processed_DataType = BOOLTYPE;
	if(OtherParaU.OtherPara.Language == 0)
		ShowString(ASCII_6X16,"Starting....",32,2);
	else
	{
            for(TempC = 0; TempC < 7; TempC++)
            {
                DisplayChinese16X12(StartInformation[TempC],TempC*12+28,2);			//12/8  16*12
            }
	}
	Processed_DataType = NOTYPE;
}

void	PageFailInformation(void)
{
	uchar	TempC;
	uchar	FailInformation[4] = {193,109,104,194};
	ClearLcdScreen();
	if(OtherParaU.OtherPara.Language == 0)
		ShowString(ASCII_6X16,"Connection/failed",12,2);
	else
	{
		for(TempC = 0; TempC < 4; TempC++)
		{
			DisplayChinese16X12(FailInformation[TempC],TempC*12+46,2);			//12/8  16*12
		}
	}
}
/*
void	PageReadParaFormMeter(void)
{
	uchar	TempC;
	uchar	ReadingParaInformation[7] = {84,173,162,157,158,156,49};
	for(TempC = 0; TempC < 7; TempC++)
	{
		DisplayChinese16X12(StartInformation[TempC],TempC*12+26,2);			//12/8  16*12
	}
}
*/

void	Page00DisplayValue()
{
	unsigned char TempC,TempCommand,Tempi;
	float temp = MasterVariableU.MasterVariableF[0];
	switch(OtherParaU.OtherPara.DisplayPage_Para[0])
	{
		case	MEANING_SENSOR_DISWAY_LIAOGAO:
			temp = SystemParaU.SystemPara.QuickSetupPage_para[0]-temp;
			TempC = 2;
		break;
		case	MEANING_SENSOR_DISWAY_KONGGAO:
			TempC = 2;
		break;
		case	MEANING_SENSOR_DISWAY_BILI:
			temp = MasterVariableU.MasterVariableF[1]*100;
			TempC = 2;
		break;
		case	MEANING_SENSOR_DISWAY_DIANLIU:
			temp = MasterVariableU.MasterVariableF[2];
			MasterVariableU.MasterVariableF[1] = (MasterVariableU.MasterVariableF[2]-4)/16;
			TempC = 4;
		break;
		case	MEANING_SENSOR_DISWAY_PERSENT:
			temp = MasterVariableU.MasterVariableF[1]*100;
			TempC = 2;
		break;
		default:break;
	}
	
	
        if(MasterVFlag == 0)
        {
                SendHartReadCmd(1);
                MasterVFlag = 1;
        }
        else
        {
                SendHartReadCmd(2);
                MasterVFlag = 0;
        }
	
	temp = temp*DisplayMulti;
	FloatToChar(temp, DisplayDecimal);
	ShowDataBuffe[5] = '\0';
	if(ZoomMainDisplay == 0)
		ShowString(ASCII_18X48,ShowDataBuffe,4,2);
	else if(ZoomMainDisplay == 1)
		ShowString(ASCII_25X48,ShowDataBuffe,5,2);

	if(MeterStatus != 0)
	{
		TempCommand = 0x01;
		for(TempC = 0; TempC < 6; TempC++)
		{
			if( (MeterStatus&TempCommand) != 0 )
			{
				if(OtherParaU.OtherPara.Language == 1)
				{
					for(Tempi = 0; Tempi < 4; Tempi++)
					{
	//					ShowString(ASCII_6X16,"!",44,0);
						DisplayChinese16X12(FaultInformation[TempC*4+Tempi],Tempi*12+52,0);			//12/8  16*12
					}
					break;
				}
				else
				{
				}
			}
			TempCommand <<= 1;
		}
	}
	else
	{
		for(Tempi = 0; Tempi < 5; Tempi++)
		{
			DisplayChinese16X12(0,Tempi*12+48,0);		
		}
	}
	if(RecordEchoFlag == 1)
		UpdateCurve();
}

void	RecondMaxMin(void)
{
	if(MasterVariableU.MasterVariableF[0] > SysRecordMaxMin[0])
	{
		SysRecordMaxMin[0] = MasterVariableU.MasterVariableF[0];
	}
	if(MasterVariableU.MasterVariableF[0] < SysRecordMaxMin[1])
	{
		SysRecordMaxMin[1] = MasterVariableU.MasterVariableF[0];
	}
}

void	UpdateMainInterface(void)
{
	uchar TempC;
	switch(MenuIndex.MenuIndex_short)
	{
		case MAININTERFACE:
			Page00DisplayValue();
			if(ZoomMainDisplay == 0)
			{
				TempC = (uchar)(MasterVariableU.MasterVariableF[1]*100);
//				DisplayBarPercentage(TempC);
				DisplayBarPercentage_v(TempC);
			}
			RecondMaxMin();
		break;
		case	SYSTEMDISPAGE://MAXMINRECORDPAGE:
			SendHartReadCmd(1);
			RecondMaxMin();
			if(MenuSelection == 0)
			{
				for(TempC = 1; TempC < 3; TempC++)
				{
					FloatToChar(SysRecordMaxMin[TempC-1],3);
					ShowString(ASCII_6X16,ShowDataBuffe,66,TempC*2);
				}
			}
		break;
		case	ZOOMCURVERPAGE:
		case	FAKEENTERPAGE:
//		case	THRESHOLDCURVE:
		case	QUICKVIEWCURVE:
//		case	MAXDEADCURVE:
//		case	MINDEADCURVE:
			if((XZoom_Flag == 0)&&(YZoom_Flag == 0))
			{
				UpdateCurve();
			}
		break;
//		case	READINGPARAPAGE:
//			ReadParaFormMeter();
//		break;
		case	WRITINGPARAPAGE:
			if(ResumeParameterType == 0xAA)
				WiteParaToMeter();
		break;
		default:break;
	}
}

void	OFF_Power(void)
{
	unsigned char TempC;
	ClearLcdScreen();
	for(TempC = 0; TempC < 6; TempC++)
	{
		DisplayChinese16X12(OFF_Power_Page[TempC],TempC*12+34,2);			//12/8  16*12
	}
}