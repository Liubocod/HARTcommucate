void	HandlePage();

uchar FactoryPassword[5] = {0x31,0x38,0x30,0x31,0x36};
uchar IfFactoryOrUserPassword,IfFactoryPasswordRightErro,IfUserPasswordRightErro;
uchar MaxMenuLine,ModifyParaStatus,FrontOrBack;
BOOL NextMenuYesOrNo = TRUE;
float	RealityDistance[2],MeasureDistance[2];//系统设置参数

uchar DisplayParaMax[4] = {5,4,0x35,2};	//显示设置参数
uchar DLineS;

//ParameterQuickSetupPage	ParameterQuickSetup; 

uchar Linear_Para_Del_Flag,ArrayLinearMP;
float EditValueFront,EditValueBack;
unsigned int DisplayMulti;
unsigned char DisplayDecimal;//,SensorDisWay,SensorUnit;

void	DisplayParaChar(uchar *ParaModfied,uchar ParaAddress,uchar MaxV, uchar MinV)
{
	uchar TempC;
	if(CursorMoveH == VISBLEEDITCURSOR)
	{
		Processed_DataType = CHARTYPE;
		CharToAssII(*ParaModfied);
		CursorMoveH = 0;
	}
	ShowDataBuffe[2] =  '\0';
	if(ModifyParaStatus == 1)
	{
		TempC = AssIICToChar();
		if( (TempC <= MaxV)&&(TempC >= MinV) )
		{
			*ParaModfied = TempC;
			TXByteCtr = 1;
			HartModfiyPara(ParaAddress);
			WriteParaToEEprom(OTHERPARAADDRESS+ParaAddress-10,ParaModfied);
		}
		CharToAssII(*ParaModfied);
	}
}
//显示单选
void	DisplayParaSingleS(uchar *SinglePara,uchar ParaAddress)
{
	if(CursorMoveH == VISBLEEDITCURSOR)
	{
		Processed_DataType = BOOLTYPE;
		ShowDataBuffe[0] = *SinglePara;
		CursorMoveH = 0;
	}
	if(ModifyParaStatus == 1)
	{
		*SinglePara = ShowDataBuffe[0];
		if(ParaAddress != 0)
		{
			if( (ParaAddress < 14)||(ParaAddress > 16) )
			{
				if(ParaAddress < 55)
				{
					HartModfiyPara(ParaAddress);
				}
			}
			TXByteCtr = 1;
			WriteParaToEEprom(OTHERPARAADDRESS+ParaAddress-10,SinglePara);
		}
	}
}

void	DisplayParaFloat(float *ParaModfiyF,uchar ParaAddress,float MaxV,float MinV)
{
	uint	TempI;
	float TempF;
	if(CursorMoveH == VISBLEEDITCURSOR)
	{
		FloatToChar(*ParaModfiyF,4);
		Processed_DataType = FLOATTYPE;
		CursorMoveH = 0;
	}
	if(ModifyParaStatus == 1)
	{
		TempF = CharToFloat();
		if((TempF >= MinV)&&(TempF <= MaxV))
		{
			*ParaModfiyF = TempF;
			if(ParaAddress >= 34)
			{
				HartModfiyPara(ParaAddress);
				TempI = (ParaAddress-34)*4;
				TXByteCtr = 4;
				WriteParaToEEprom(SYSTEMPARAADDRESS+TempI,&SystemParaU.SystemParaC[TempI]);
			}
		}
		FloatToChar(*ParaModfiyF,4);
	}
}

void	DisplayDisplayQuicksetupPage_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
	for(TempC = 0; TempC < (MaxMenuLine-1); TempC++)
	{
		if(MenuSelection == TempC)
		{
			switch(MenuSelection)
			{
				case 0:
					MaxLimit = MaxRange;
					MinLimit = SystemParaU.SystemPara.QuickSetupPage_para[1]+0.3;
				break;
				case 1:
					MaxLimit = SystemParaU.SystemPara.QuickSetupPage_para[0]-0.3;
					MinLimit = 0;
				break;
//				case 2:
//					MaxLimit = 1;
//					MinLimit = 0.02;
//				break;
				case 2:
					MaxLimit = 70;
					MinLimit = 0;
				break;
				default:break;
			}
			DisplayParaFloat(&SystemParaU.SystemPara.QuickSetupPage_para[TempC],34+TempC,MaxLimit,MinLimit);
			ShowDataBuffe[6] = '\0';
			ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
//			if(MenuSelection != 3)
//			{
				ShowString(ASCII_6X16,":",58,TempC*2);
				ShowString(ASCII_6X16,"m",100,TempC*2);
				FloatToChar(SystemParaU.SystemPara.QuickSetupPage_para[TempC],4);
				ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
//			}
			if((SystemParaU.SystemPara.QuickSetupPage_para[2] > 0))
				MaxMenuLine = 4;
			else if((SystemParaU.SystemPara.QuickSetupPage_para[2] == 10)||(SystemParaU.SystemPara.QuickSetupPage_para[2] == 0))
				MaxMenuLine = 3;
			else
				MaxMenuLine = 4;
		}
	}
}

void	DisplayFakeEchoVModify_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit,TempF;
	for(TempC = 0; TempC < 3; TempC++)
	{
		if(MenuSelection == TempC)
		{
			switch(MenuSelection)
			{
				case 2:
					MaxLimit = 3.3;
					MinLimit = 0;
				break;
				case 1:
				case 0:
					MaxLimit = 70;
					MinLimit = 0;
				break;
				default:break;
			}
			
			if(CursorMoveH == VISBLEEDITCURSOR)
			{
				FloatToChar(MasterVariableU.MasterVariableF[TempC+3],4);
				Processed_DataType = FLOATTYPE;
				CursorMoveH = 0;
			}
			if(ModifyParaStatus == 1)
			{
				TempF = CharToFloat();
				if((TempF >= MinLimit)&&(TempF <= MaxLimit))
				{
					MasterVariableU.MasterVariableF[TempC+3] = TempF;
				}
				FloatToChar(MasterVariableU.MasterVariableF[TempC+3],4);
			}
			ShowDataBuffe[6] = '\0';
			ShowString(ASCII_6X16,ShowDataBuffe,44,TempC*2);
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
			ShowString(ASCII_6X16,":",38,TempC*2);
			if(TempC == 2)
				ShowString(ASCII_6X16,"v",80,TempC*2);
			else
				ShowString(ASCII_6X16,"m",80,TempC*2);
			FloatToChar(MasterVariableU.MasterVariableF[TempC+3],4);												//把浮点数转成字符数组
			ShowDataBuffe[6] = '\0';
			ShowString(ASCII_6X16,ShowDataBuffe,44,TempC*2);
			MaxMenuLine = 4;
		}
	}
}

void	DisplayDisplayViewCurveMPage_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit,TempF;
	for(TempC = 0; TempC < 2; TempC++)
	{
		if(MenuSelection == TempC)
		{
			switch(MenuSelection)
			{
				case 0:
					MaxLimit = SystemParaU.SystemPara.ReceordCurvePage_para[1];
					MinLimit = 0;
				break;
				case 1:
					MaxLimit = 70;
					MinLimit = SystemParaU.SystemPara.ReceordCurvePage_para[0];
				break;
				default:break;
			}
			
			if(CursorMoveH == VISBLEEDITCURSOR)
			{
				FloatToChar(SystemParaU.SystemPara.ReceordCurvePage_para[TempC],4);
				Processed_DataType = FLOATTYPE;
				CursorMoveH = 0;
			}
			if(ModifyParaStatus == 1)
			{
				TempF = CharToFloat();
				if((TempF >= MinLimit)&&(TempF <= MaxLimit))
				{
					SystemParaU.SystemPara.ReceordCurvePage_para[TempC] = TempF;
					TXByteCtr = 4;
					WriteParaToEEprom(SYSTEMPARAADDRESS+88+TempC*4,&SystemParaU.SystemParaC[88]);
				}
				FloatToChar(SystemParaU.SystemPara.ReceordCurvePage_para[TempC],4);
			}
			ShowDataBuffe[6] = '\0';
			ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
//			if(MenuSelection < 3)
//			{
				ShowString(ASCII_6X16,":",58,TempC*2);
				if(TempC == 1)
					ShowString(ASCII_6X16,"m",100,2);
				else
					ShowString(ASCII_6X16,"s",100,0);
				FloatToChar(SystemParaU.SystemPara.ReceordCurvePage_para[TempC],4);												//把浮点数转成字符数组
				ShowDataBuffe[6] = '\0';
				ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
//			}
			MaxMenuLine = 4;
		}
	}
}

void	DisplayDisplayQuicksetupPage_Para_en(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
	for(TempC = 0; TempC < (MaxMenuLine-1); TempC++)
	{
		switch(MenuSelection)
		{
			case 0:
				MaxLimit = MaxRange;
				MinLimit = SystemParaU.SystemPara.QuickSetupPage_para[1]+0.3;
			break;
			case 1:
				MaxLimit = SystemParaU.SystemPara.QuickSetupPage_para[0]-0.3;
				MinLimit = 0;
			break;
			case 2:
				MaxLimit = 70;
				MinLimit = 0;
			break;
			case 3:
				MaxLimit = 20;
				MinLimit = 0.5;
			break;
			default:break;
		}
		if(MenuSelection == TempC)
		{
			if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
			{
				ClearLcdScreen();
				switch(MenuSelection)
				{
					case 0:
						ShowString(ASCII_6X16,"Min//0@:",44,0);
						DisplayChart(chart_Min0);
					break;
					case 1:
						ShowString(ASCII_6X16,"Max/100@:",41,0);
						DisplayChart(chart_Max100);
					break;
//					case 2:
//						ShowString(ASCII_6X16,"Standpipe/length:",16,0);
//					break;
					case 3:
						ShowString(ASCII_6X16,"Cable/length:",26,0);
					break;
					default:break;
				}
				FloatToChar(SystemParaU.SystemPara.QuickSetupPage_para[TempC],4);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
				if((SystemParaU.SystemPara.QuickSetupPage_para[2] > 0)&&(SystemParaU.SystemPara.QuickSetupPage_para[3] > 0))
					MaxMenuLine = 4;
				else if((SystemParaU.SystemPara.QuickSetupPage_para[2] == 10)||(SystemParaU.SystemPara.QuickSetupPage_para[2] == 0))
					MaxMenuLine = 3;
				else
					MaxMenuLine = 4;
				ShowString(ASCII_6X16,"m",83,3);
			}
			else
			{
				DisplayParaFloat(&SystemParaU.SystemPara.QuickSetupPage_para[TempC],34+TempC,MaxLimit,MinLimit);
				ShowDataBuffe[6] = '\0';
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
			}
		}
	}
	if(MenuSelection == (MaxMenuLine-1))
	{
		ClearLcdScreen();
		ShowString(ASCII_6X16,"Level/confirm",30,0);
		ShowString(ASCII_6X16,"echo/curve",38,2);
	}
}

void	DisplayDielectricConstant(uchar PassParameter)
{
	switch(PassParameter)
	{
		case 0:
			ShowString(ASCII_6X16,"1.4-1.6",47,3);
		break;
		case 1:
			ShowString(ASCII_6X16,"1.6-1.9",47,3);
		break;
		case 2:
			ShowString(ASCII_6X16,"1.9-2.5",47,3);
		break;
		case 3:
			ShowString(ASCII_6X16,"2.5-4//",47,3);
		break;
		case 4:
			ShowString(ASCII_6X16,"//4-7//",47,3);
		break;
		case 5:
			ShowString(ASCII_6X16,"//>/7//",47,3);
		break;
		default:
			ShowString(ASCII_6X16,"1.4-1.6",47,3);
		break;
	}
}

void	DisplayBasicSetupPage_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		MaxMenuLine = 6;
		switch(MenuSelection)
		{
			case 0:
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Damping:",44,0);
				CharToAssII(OtherParaU.OtherPara.DampingTime);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
				ShowString(ASCII_6X16,"s",72,3);
			break;
			case 1:
				MaxMenuLine = 6;
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Dielectric/constant:",8,0);
				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
				DisplayDielectricConstant(OtherParaU.OtherPara.DielectricConstant);
			break;
			case 2:
			case 3:
				ShowString(ASCII_6X16,"m",83,3);
				FloatToChar(SystemParaU.SystemPara.DeadZone[MenuSelection-2],4);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
				if(MenuSelection == 2)
				{
					if(OtherParaU.OtherPara.Language == 0)
						ShowString(ASCII_6X16,"Min.Dead/zone:",26,0);
				}
				else
				{
					if(OtherParaU.OtherPara.Language == 0)
						ShowString(ASCII_6X16,"Max.Dead/zone:",26,0);
				}
			break;
			case 4:
				ShowString(ASCII_6X16,"m=s",83,3);
				FloatToChar(SystemParaU.SystemPara.ObjectChangSpeed,4);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Change/speed:",26,0);
			break;
			case 5:
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"False/echo/Inc.:",26,0);
				CharToAssII(OtherParaU.OtherPara.FakeWaveGain);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
//				ShowString(ASCII_6X16,"s",72,3);
			break;
			default:break;
		}
		if(OtherParaU.OtherPara.Language == 1)
		{
			if(MenuSelection < 5)
			{
				for(TempC = 0; TempC < 4; TempC++)
				{
					DisplayChinese16X12(Page_BasicSetup[MenuSelection*4+TempC],TempC*12+44,0);			//显示汉字（16*12）
				}
				ShowString(ASCII_6X16,":",92,0);
			}
			else
			{
				for(TempC = 0; TempC < 6; TempC++)
				{
					DisplayChinese16X12(Page_FakeWaveGain[TempC],TempC*12+32,0);			//显示汉字（16*12）
				}
				ShowString(ASCII_6X16,":",104,0);
			}
		}
	}
	else
	{
		switch(MenuSelection)
		{
			case 0:
				DisplayParaChar(&OtherParaU.OtherPara.DampingTime,11,99,0);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
			break;
			case 1:
				MaxMenuLine = 6;
				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
				DisplayDielectricConstant(ShowDataBuffe[0]);
			break;
			case 2:
			case 3:
				if(MenuSelection == 2)
				{
					MaxLimit = SystemParaU.SystemPara.DeadZone[1]-0.5;
					MinLimit = 0;
					if(MinLimit < 0)
						MinLimit = 0;
				}
				else
				{
					MaxLimit = 72;
					MinLimit = SystemParaU.SystemPara.DeadZone[0]+0.5;
				}
				DisplayParaFloat(&SystemParaU.SystemPara.DeadZone[MenuSelection-2],38+MenuSelection,MaxLimit,MinLimit);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
			break;
			case 4:
				MaxLimit = 70;
				MinLimit = 0.1;
				DisplayParaFloat(&SystemParaU.SystemPara.ObjectChangSpeed,42,MaxLimit,MinLimit);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
			break;
			case 5:
				DisplayParaChar(&OtherParaU.OtherPara.FakeWaveGain,10,99,0);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
			break;
			default:break;
		}
	}
}

void	DisplayBasicSetupPage_Para_G(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		MaxMenuLine = 6;
		switch(MenuSelection)
		{
			case 0:
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Damping:",44,0);
				CharToAssII(OtherParaU.OtherPara.DampingTime);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
				ShowString(ASCII_6X16,"s",72,3);
			break;
			case 1:
				MaxMenuLine = 6;
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Dielectric/constant:",8,0);
				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
				DisplayDielectricConstant(OtherParaU.OtherPara.DielectricConstant);
			break;
			case 2:
			case 3:
				ShowString(ASCII_6X16,"m",83,3);
				FloatToChar(SystemParaU.SystemPara.DeadZone[MenuSelection-2],4);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
				if(MenuSelection == 2)
				{
					if(OtherParaU.OtherPara.Language == 0)
						ShowString(ASCII_6X16,"Min.Dead/zone:",26,0);
				}
				else
				{
					if(OtherParaU.OtherPara.Language == 0)
						ShowString(ASCII_6X16,"Max.Dead/zone:",26,0);
				}
			break;
			case 4:
				ShowString(ASCII_6X16,"m=s",83,3);
				FloatToChar(SystemParaU.SystemPara.ObjectChangSpeed,4);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Chang/speed:",26,0);
			break;
			case 5:
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Magnification/times:",44,0);
				CharToAssII(OtherParaU.OtherPara.FakeWaveGain);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
//				ShowString(ASCII_6X16,"s",72,3);
			break;
			case 6:
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Probe/type:",44,0);
//				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
//				DisplayProbetype(OtherParaU.OtherPara.DielectricConstant);
			break;
			default:break;
		}
		if(OtherParaU.OtherPara.Language == 1)
		{
//			if(MenuSelection < 5)
//			{
				for(TempC = 0; TempC < 4; TempC++)
				{
					DisplayChinese16X12(Page_BasicSetup_G[MenuSelection*4+TempC],TempC*12+44,0);			//显示汉字（16*12）
				}
				ShowString(ASCII_6X16,":",92,0);
//			}
		}
	}
	else
	{
		switch(MenuSelection)
		{
			case 0:
				DisplayParaChar(&OtherParaU.OtherPara.DampingTime,11,99,0);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
			break;
			case 1:
				MaxMenuLine = 6;
				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
				DisplayDielectricConstant(ShowDataBuffe[0]);
			break;
			case 2:
			case 3:
				if(MenuSelection == 2)
				{
					MaxLimit = SystemParaU.SystemPara.DeadZone[1]-0.5;
					MinLimit = 0;
					if(MinLimit < 0)
						MinLimit = 0;
				}
				else
				{
					MaxLimit = 72;
					MinLimit = SystemParaU.SystemPara.DeadZone[0]+0.5;
				}
				DisplayParaFloat(&SystemParaU.SystemPara.DeadZone[MenuSelection-2],38+MenuSelection,MaxLimit,MinLimit);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
			break;
			case 4:
				MaxLimit = 70;
				MinLimit = 0.1;
				DisplayParaFloat(&SystemParaU.SystemPara.ObjectChangSpeed,42,MaxLimit,MinLimit);
				ShowString(ASCII_6X16,ShowDataBuffe,47,3);
			break;
			case 5:
				DisplayParaChar(&OtherParaU.OtherPara.FakeWaveGain,10,80,0);
				ShowString(ASCII_6X16,ShowDataBuffe,56,3);
			break;
			case 6:
//				DisplayParaSingleS(&OtherParaU.OtherPara.DielectricConstant,12);
//				DisplayProbetype(ShowDataBuffe[0]);
			break;
			default:break;
		}
	}
}

void	DisplayContrast_Para(unsigned char BarValure)
{
	unsigned char TempChar;
	if(MenuSelection == 2)
	{
		if((BarValure > 0x15)&&(BarValure < 0x40))
		{
			LcdWriteCommand(0x81);
			LcdWriteCommand(BarValure);
		}

		BarValure = (BarValure-0x18)*3;
		LcdSetPage(4);
		for(TempChar = 10; TempChar < 98; TempChar++)
		{
			LcdSetColumn(TempChar);
			LcdWriteData(0);
		}

		LcdSetPage(3);
		LcdSetColumn(31);
		LcdWriteData(0xFF);
		
		for(TempChar = 10; TempChar < 87; TempChar++)
		{
			if(TempChar < BarValure)
				LcdWriteData(0xFF);
			else
				LcdWriteData(0x81);
		}
		LcdWriteData(0xFF);
	}
}

void	DisplayDisplaySetupPage_Para_en(void)
{
	uchar TempC,Adjust_ch[] = {160,161};
	MaxMenuLine = DisplayParaMax[MenuSelection];
	switch(MenuSelection)
	{
		case 0:
			DisplayParaSingleS(&OtherParaU.OtherPara.DisplayPage_Para[0],14);
		break;
		case 1:
			DisplayParaSingleS(&OtherParaU.OtherPara.DisplayPage_Para[1],15);
		break;
		case 2:
			DisplayParaSingleS(&OtherParaU.OtherPara.DisplayPage_Para[2],16);
			if(ShowDataBuffe[0] <= 0x18)
				ShowDataBuffe[0] = 0x18;
			if(ShowDataBuffe[0] >= 0x35)
				ShowDataBuffe[0] = 0x35;
			if(CursorMoveH == 0)
				DisplayContrast_Para(ShowDataBuffe[0]);
		break;
		case 3:
			DisplayParaSingleS(&OtherParaU.OtherPara.Language,66);
		break;
		default:break;
	}
	if(CursorMoveH > 0xFD)
	{
		ClearLcdScreen();
		if(OtherParaU.OtherPara.Language != 0)
		{
			for(TempC = 0; TempC < 5; TempC++)
				DisplayChinese16X12(Page_DisplaySetup[MenuSelection*5+TempC],TempC*12+38,0);
			if(MenuSelection == 2)
			{
				ShowString(ASCII_6X16,":",98,0);
				for(TempC = 0; TempC < 2; TempC++)
					DisplayChinese16X12(Adjust_ch[TempC],TempC*12+53,3);
				ShowString(ASCII_6X16,"?",77,3);
			}
			else
				ShowString(ASCII_6X16,":",86,0);
		}
		else
		{
			switch(MenuSelection)
			{
				case 0:
					ShowString(ASCII_6X16,"Displayed/Value:",20,0);
				break;
				case 1:
					ShowString(ASCII_6X16,"Unit:",53,0);
				break;
				case 2:
					ShowString(ASCII_6X16,"LCD/Contrast:",30,0);
					ShowString(ASCII_6X16,"Do/you/adjust?",30,3);
				break;
				case 3:
					ShowString(ASCII_6X16,"Language:",40,0);
				break;
				default:break;
			}
		}
//		if(MenuSelection == 2)
//			DisplayContrast_Para(0);
		if(ModifyParaStatus == 0)
		{
			switch(MenuSelection)
			{
				case 0:
				case 1:
				case 2:
					ShowDataBuffe[0] = OtherParaU.OtherPara.DisplayPage_Para[MenuSelection];
				break;
				case 3:
					ShowDataBuffe[0] = OtherParaU.OtherPara.Language;
				break;
				default:break;
			}
		}
		MaxMenuLine = 4;
	}
		if(OtherParaU.OtherPara.Language != 0)
		{
			switch(MenuSelection)
			{
				case 0:
					Display_MenuSingleSelectionPage(Displaycontent_Item,ShowDataBuffe[0],5,3,50,3);
				break;
				case 1:
					Display_MenuSingleSelectionPage(DisplayUnit_Item,ShowDataBuffe[0],4,2,56,3);
				break;
				case 3:
					Display_MenuSingleSelectionPage(DisplayLanguage_Item,ShowDataBuffe[0],2,2,56,3);
				break;
				default:break;
			}
		}
		else
		{
			switch(MenuSelection)
			{
				case 0:
					Display_MenuSingleSelectionPage(&Displaycontent_Item_en[0][0],ShowDataBuffe[0],5,9,44,3);
				break;
				case 1:
					Display_MenuSingleSelectionPage(&DisplayUnit_Item_en[0][0],ShowDataBuffe[0],4,11,38,3);
				break;
				case 3:
					Display_MenuSingleSelectionPage(&DisplayLanguage_Item_en[0][0],ShowDataBuffe[0],2,8,47,3);
				break;
				default:break;
			}
		}
}

void	DisplayHartC_Para(void)
{
	uchar TempC;
	switch(MenuSelection)
	{
		case 0:
			DisplayParaChar(&OtherParaU.OtherPara.HartAddress,17,99,0);
			ShowString(ASCII_6X16,ShowDataBuffe,64,0);
		break;
		case 1:
			MaxMenuLine = 2;
			DisplayParaSingleS(&OtherParaU.OtherPara.HartCStype,18);
			if(OtherParaU.OtherPara.Language == 0)
				Display_MenuSingleSelectionPage(&HartStype_Item_en[0][0],ShowDataBuffe[0],2,9,64,2);
			else
				Display_MenuSingleSelectionPage(HartStype_Item,ShowDataBuffe[0],2,2,64,2);
		break;
		default:break;
	}

	if(CursorMoveH > 0xFD)
	{
		for(TempC = 0; TempC < 2; TempC++)
		{
			ShowString(ASCII_6X16,":",58,TempC*2);
		}
		CharToAssII(OtherParaU.OtherPara.HartAddress);
		ShowString(ASCII_6X16,ShowDataBuffe,64,0);
		if(OtherParaU.OtherPara.Language == 0)
			Display_MenuSingleSelectionPage(&HartStype_Item_en[0][0],OtherParaU.OtherPara.HartCStype,2,9,64,2);
		else
			Display_MenuSingleSelectionPage(HartStype_Item,OtherParaU.OtherPara.HartCStype,2,2,64,2);
		MaxMenuLine = 2;
	}
}

void	DisplayEchoAdjudgePage_Para(void)
{
	unsigned char TempC;
	float MaxLimit,MinLimit;
	switch(MenuSelection)
	{
		case 0:
			DisplayParaSingleS(&OtherParaU.OtherPara.EchoAdjudge,26);
			MaxMenuLine = 4;
			Display_MenuSingleSelectionPage(EchoAdjudgeItem,ShowDataBuffe[0],4,4,64,0);
		break;
		case 1:
			MaxLimit = 3;
			MinLimit = -3;
			DisplayParaFloat(&SystemParaU.SystemPara.EchoAdjudgeV,52,MaxLimit,MinLimit);
			ShowString(ASCII_6X16,ShowDataBuffe,64,2);
		break;
		case 2:
			DisplayParaFloat(&SystemParaU.SystemPara.ConfirmEchoDelay,53,9000,1);
			ShowString(ASCII_6X16,ShowDataBuffe,64,4);
		break;
		case 3:
			DisplayParaFloat(&SystemParaU.SystemPara.MinDistinctiveness,54,2,0);
			ShowString(ASCII_6X16,ShowDataBuffe,76,6);
			break;
		default:break;
	}
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		for(TempC = 0; TempC < 3; TempC++)
		{
			ShowString(ASCII_6X16,":",58,TempC*2);
		}
			
		FloatToChar(SystemParaU.SystemPara.EchoAdjudgeV,4);
		ShowString(ASCII_6X16,"V",100,2);//'v'
		ShowString(ASCII_6X16,ShowDataBuffe,64,2);

		FloatToChar(SystemParaU.SystemPara.ConfirmEchoDelay,4);
		ShowString(ASCII_6X16,ShowDataBuffe,64,4);
		ShowString(ASCII_6X16,"S",100,4);//'S'

		Display_MenuSingleSelectionPage(EchoAdjudgeItem,OtherParaU.OtherPara.EchoAdjudge,4,4,64,0);

		FloatToChar(SystemParaU.SystemPara.MinDistinctiveness,4);
		ShowString(ASCII_6X16,ShowDataBuffe,76,6);
		ShowString(ASCII_6X16,":",70,6);
		ShowString(ASCII_6X16,"V",112,6);//'v'
		MaxMenuLine = 4;
	}
}

void	DisplayEchoAdjudgePage_Para_en(void)
{
	float MaxLimit,MinLimit;
	if(MenuSelection != 0)
	{
		MaxLimit = 3;
		MinLimit = -3;
		DisplayParaFloat(&SystemParaU.SystemPara.EchoAdjudgeV,52,MaxLimit,MinLimit);
		ShowString(ASCII_6X16,ShowDataBuffe,47,3);
	}
	else
	{
		DisplayParaSingleS(&OtherParaU.OtherPara.EchoAdjudge,26);
		MaxMenuLine = 4;
		Display_MenuSingleSelectionPage(&EchoAdjudgeItem_en[0][0],ShowDataBuffe[0],3,7,50,3);
	}
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		if(MenuSelection != 0)
		{
			ShowString(ASCII_6X16,"Superiority:",32,0);
			FloatToChar(SystemParaU.SystemPara.EchoAdjudgeV,4);
			ShowString(ASCII_6X16,"V",83,3);//'v'
			ShowString(ASCII_6X16,ShowDataBuffe,47,3);
		}
		else
		{
			ShowString(ASCII_6X16,"Logic/select:",30,0);
			Display_MenuSingleSelectionPage(&EchoAdjudgeItem_en[0][0],OtherParaU.OtherPara.EchoAdjudge,4,11,38,3);
		}
		MaxMenuLine = 2;
	}
}

void	DisplayCurrentSetupPage_Para(void)
{
	uchar TempC;
	for(TempC = 0; TempC < 3; TempC++)
	{
		if(MenuSelection == TempC)
		{
			DisplayParaFloat(&SystemParaU.SystemPara.CurrentSetup[TempC],I2CURRENTADDRESS+TempC,24,1);
			ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
		}
	}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
			if(G_KeyValue == NO_KEY_STATUS)
				ClearLcdScreen();
			for(TempC = 0; TempC < 4; TempC++)
				ShowString(ASCII_6X16,"/",4,TempC*2);										//被选项后面显示“<-”
			ShowString(ASCII_6X16,"<",4,MenuSelection*2);										//被选项后面显示“<-”
			if(MenuSelection == 0)
			{
				ShowString(ASCII_6X16,":",58,0);
			}
			for(TempC = 0; TempC < 3; TempC++)
			{
				ShowString(ASCII_6X16,"mA",108,TempC*2);
				FloatToChar(SystemParaU.SystemPara.CurrentSetup[TempC],4);
				ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
			}
			ShowString(ASCII_6X16,"4mA->",31,2);			//4mA
			ShowString(ASCII_6X16,"18mA->",26,4);			//18mA
			if(OtherParaU.OtherPara.Language == 0)
			{
				ShowString(ASCII_6X16,"Calibration/confirm",10,6);
				ShowString(ASCII_6X16,"Setup/out:",10,0);
			}
			else
			{
				for(TempC = 0; TempC < 4; TempC++)
					DisplayChinese16X12(Page_CurrentSetup[TempC],TempC*12+10,0);
				for(TempC = 0; TempC < 4; TempC++)
					DisplayChinese16X12(Page_CurrentSetup[12+TempC],TempC*12+10,6);
			}
			MaxMenuLine = 4;
		}
	if((MenuSelection == 3)&&(ModifyParaStatus == 1))
	{
		if((SystemParaU.SystemPara.CurrentSetup[1] != 4)||(SystemParaU.SystemPara.CurrentSetup[2] != 18))
		{
			SystemParaU.SystemPara.CurrentSetup[0] = 1;
			HartModfiyPara(I2CURRENTADDRESS);
		}
		CursorMoveH = 0xFE;
		SystemParaU.SystemPara.CurrentSetup[1] = 4;
		SystemParaU.SystemPara.CurrentSetup[2] = 18;
		FloatToChar(4,4);
		ShowString(ASCII_6X16,ShowDataBuffe,70,2);
		FloatToChar(18,4);
		ShowString(ASCII_6X16,ShowDataBuffe,70,4);
	}
}

void	DisplayMappingParaPage_Para(void)
{
	uchar TempC;
	for(TempC = 0; TempC < 2; TempC++)
	{
		if(MenuSelection == TempC)
		{
			DisplayParaFloat(&SystemParaU.SystemPara.MappingPara[TempC],46+TempC,70,0);
			ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
			ShowString(ASCII_6X16,":",64,TempC*2);
			ShowString(ASCII_6X16,"m",106,TempC*2);
			FloatToChar(SystemParaU.SystemPara.MappingPara[TempC],4);
			ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
			MaxMenuLine = 2;
		}
	}
}

void	DisplayCurveRangePage_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
//			ModfiyPara(5,2);
	for(TempC = 0; TempC < 2; TempC++)
	{
		if(TempC == 0)
		{
			MaxLimit = CurveStartEnd[1];
			MinLimit = -0.5;
		}
		else
		{
			MaxLimit = 70;
			MinLimit = CurveStartEnd[0];
		}
		if(MenuSelection == TempC)
		{
			DisplayParaFloat(&CurveStartEnd[TempC],46+TempC,MaxLimit,MinLimit);
			ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
			ShowString(ASCII_6X16,":",64,TempC*2);
			ShowString(ASCII_6X16,"m",106,TempC*2);
			FloatToChar(CurveStartEnd[TempC],4);
			ShowString(ASCII_6X16,ShowDataBuffe,70,TempC*2);
			MaxMenuLine = 3;
		}
	}
}

void	DisplayCoefficientPage_Para(void)
{
	uchar TempC;
	float MaxLimit,MinLimit;
	for(TempC = 0; TempC < 2; TempC++)
	{
		switch(MenuSelection)
		{
			case 0:
				MaxLimit = 20;
				MinLimit = -20;
			break;
			case 1:
				MaxLimit = 10;
				MinLimit = 0.5;
			break;
			default:break;
		}
		if(MenuSelection == TempC)
		{
			if(MenuSelection < 2)
			{
				DisplayParaFloat(&SystemParaU.SystemPara.SystemCoefficient[TempC],38+TempC,MaxLimit,MinLimit);
				ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
			}
		}
		if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
		{
			ShowString(ASCII_6X16,":",58,TempC*2);
			if(TempC == 0)
				ShowString(ASCII_6X16,"m",100,TempC*2);
			FloatToChar(SystemParaU.SystemPara.SystemCoefficient[TempC],4);
			ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
			MaxMenuLine = 2;
		}
	}
}

void	InitLinePoint(uchar LineSItem,float *EditPointsArrayFB)
{
	unsigned char  StringTempMark[3];
	StringTempMark[2] = '\0';
	FrontOrBack = FRONT;
	StringTempMark[0] = LineSItem/10+0x30;
	StringTempMark[1] = LineSItem%10+0x30;
	ShowString(ASCII_5X8,StringTempMark,10,ArrayLinearMP);
	ShowString(ASCII_6X16,":",20,ArrayLinearMP);										//显示":"
	ShowString(ASCII_6X16,UnitString,62,ArrayLinearMP);
	ShowString(ASCII_6X16,"->",68,ArrayLinearMP);										//显示":"
	ShowString(ASCII_6X16,UnitString,116,ArrayLinearMP);
	if(EditPointsArrayFB[LineSItem*2] > 70)
		EditPointsArrayFB[LineSItem*2] = 70;
	if(EditPointsArrayFB[LineSItem*2] < 0)
		EditPointsArrayFB[LineSItem*2] = 0;
	if(EditPointsArrayFB[LineSItem*2+1] > 70)
		EditPointsArrayFB[LineSItem*2+1] = 70;
	if(EditPointsArrayFB[LineSItem*2+1] < 0)
		EditPointsArrayFB[LineSItem*2+1] = 0;
	EditValueFront = EditPointsArrayFB[LineSItem*2];
	EditValueBack = EditPointsArrayFB[LineSItem*2+1];
	FloatToChar(EditValueBack,4);													//把浮点数转成字符数组
	ShowString(ASCII_6X16,ShowDataBuffe,80,ArrayLinearMP);								//显示浮点数字符串
	FloatToChar(EditValueFront,4);												//把浮点数转成字符数组
	ShowString(ASCII_6X16,ShowDataBuffe,26,ArrayLinearMP);								//显示浮点数字符串
}

//显示线性化数组
//输入参数：被选数据项、线性化浮点数组
void	Display_Linear_Array(uchar ArrayItemSelected,float *EditPointsArrayFB)
{
	uchar TempC,Tempi,TempM,StringTempMark[3];
	uchar StartItem,EndItem;

	StringTempMark[2] = '\0';
	CursorMoveH = VISBLEMENUCURSOR;
	TempM = ArrayItemSelected/4;
	StartItem = TempM*4;
	EndItem = StartItem+4;
	if(EndItem > LinearParaU.LinearPara.LinePointsNum)
	{
		EndItem = LinearParaU.LinearPara.LinePointsNum;									
	}
	if( (ArrayItemSelected%4) == 0)
	{
		ClearLcdScreen();
	}
		
//	SendFrameHeader(StartItem+55,2);
	TempC = G_KeyValue;
	for(Tempi = StartItem; Tempi < EndItem; Tempi++)
	{
		if((MenuSelection == 0)||((MenuSelection == 4)&&(TempC == DOWN))||((MenuSelection == 4)&&(TempC == UP)))
		{
//			ClearLcdScreen();
			G_KeyValue = NO_KEY_STATUS;
		}
		TempM = Tempi-StartItem;													//行号
		ArrayLinearMP = TempM*2;
		InitLinePoint(Tempi,EditPointsArrayFB);
		if(ArrayItemSelected == Tempi)
		{
			if(Linear_Para_Del_Flag == 1)
			{//选中要删除的显性化数组
				CursorMoveH = 0;													//出现光标，使后面的字符反显
				StringTempMark[0] = Tempi/10+0x30;
				StringTempMark[1] = Tempi%10+0x30;
				ShowString(ASCII_5X8,StringTempMark,10,ArrayLinearMP);
				ShowString(ASCII_5X8,&StringTempMark[1],15,ArrayLinearMP);
				ShowString(ASCII_6X16,":",20,TempM*2);
			}

			CursorMoveH = VISBLEMENUCURSOR;											//不出现光标，使后面的显示正常显示
			ShowString(ASCII_6X16,"<",4,TempM*2);
		}
		else
		{
			ShowString(ASCII_6X16,"/",4,TempM*2);
		}
	}
}

void	Show_Add_Linear_Para(float *EditPointsArrayFB)
{
	const uchar LDataFull[] = {49,164,165};
	uchar TempC,TempM;
	switch(G_KeyValue)
	{
		case NO_KEY_STATUS:
//			SendFrameHeader(LinearParaU.LinearPara.LinePointsNum+55,2);
			if(LinearParaU.LinearPara.LinePointsNum > 20)
			{
				LinearParaU.LinearPara.LinePointsNum = 0;
			}
			ClearLcdScreen();
			if(OtherParaU.OtherPara.Language == 0)
			{
				ShowString(ASCII_6X16,"Reality//Measure",22,0);
			}
			else
			{
				Display_MenuSingleSelectionPage(Page_CalibrationD,0,1,9,14,0);
			}
//			Display_MenuSingleSelectionPage(Page_CalibrationDEnter,0,1,4,10,6);				
			ArrayLinearMP = 2;
			InitLinePoint(LinearParaU.LinearPara.LinePointsNum,EditPointsArrayFB);
			CursorMoveH = 0;
			ShowString(ASCII_6X16,ShowDataBuffe,26,2);
		break;
		case DOWN:
			if(CursorMoveH < 0xFD)
			{
				CursorMoveH++;
				if(CursorMoveH == 6)
				{
					if(FrontOrBack)
					{
						EditValueFront = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,26,2);									//显示浮点数字符串
						FrontOrBack = 0;

						FloatToChar(EditValueBack,4);											//把浮点数转成字符数组
					}
					else
					{
						EditValueBack = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,80,2);									//显示浮点数字符串
						FrontOrBack = 1;

						FloatToChar(EditValueFront,4);											//把浮点数转成字符数组
					}
					CursorMoveH = 0;
				}
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,26,2);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,80,2);										//显示浮点数字符串
				}
			}
		break;
		case UP:
			if(CursorMoveH < 0xFD)
			{
				EditDataAdd1();
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,26,2);										//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,80,2);										//显示浮点数字符串
				}
			}
		break;
		case OK:
			if(CursorMoveH > 0xFD)
			{
//				DisplayChinese16X12(0,116,0);				//'√'
				InitLinePoint(LinearParaU.LinearPara.LinePointsNum,EditPointsArrayFB);
				CursorMoveH = 0;
				ShowString(ASCII_6X16,ShowDataBuffe,26,2);
			}
			else
			{
				if(FrontOrBack)
				{
					EditValueFront = CharToFloat();
				}
				else
				{
					 EditValueBack = CharToFloat();
				}
				TempC = LinearParaU.LinearPara.LinePointsNum*2;
				EditPointsArrayFB[TempC] = EditValueFront;
				EditPointsArrayFB[TempC+1] = EditValueBack;
				LinearParaU.LinearPara.LinePointsNum++;

//				ModfiyPara(LinearParaU.LinearPara.LinePointsNum+55,2);
//				TXByteCtr = 8;
//				WriteParaToEEprom(LINEARPARAADDRESS+LinearParaU.LinearPara.LinePointsNum*8,&LinearParaU.LinearParaC[LinearParaU.LinearPara.LinePointsNum*8]);
				CursorMoveH = VISBLEMENUCURSOR;
				if(LinearParaU.LinearPara.LinePointsNum > 20)
				{
					LinearParaU.LinearPara.LinePointsNum = 20;
					for(TempC = 0; TempC < 3; TempC++)
					{
						DisplayChinese16X12(LDataFull[TempC],TempC*12+52,2);			//显示汉字（16*12）
					}
				}
				else
				{
//					SendFrameHeader(LinearParaU.LinearPara.LinePointsNum+55,2);
					InitLinePoint(LinearParaU.LinearPara.LinePointsNum,EditPointsArrayFB);
					CursorMoveH = 0;//VISBLEMENUCURSOR;
				}
				TXByteCtr = 1;
				WriteParaToEEprom(LINEARPARAADDRESS+160,&LinearParaU.LinearPara.LinePointsNum);

			for(TempC = 0; TempC < LinearParaU.LinearPara.LinePointsNum; TempC++)
			{
				for(TempM = TempC+1; TempM < LinearParaU.LinearPara.LinePointsNum; TempM++)
				{
					if(EditPointsArrayFB[TempC*2] > EditPointsArrayFB[TempM*2] )
					{
						EditValueFront = EditPointsArrayFB[TempC*2];
						EditPointsArrayFB[TempC*2] = EditPointsArrayFB[TempM*2];
						EditPointsArrayFB[TempM*2] = EditValueFront;
						
						EditValueBack = EditPointsArrayFB[TempC*2+1];
						EditPointsArrayFB[TempC*2+1] = EditPointsArrayFB[TempM*2+1];
						EditPointsArrayFB[TempM*2+1] = EditValueBack;
//						ModfiyPara(TempC+55,2);
					}
				}
				TXByteCtr = 8;
				WriteParaToEEprom(LINEARPARAADDRESS+TempM*8,&LinearParaU.LinearParaC[TempM*8]);
			}
//				DisplayChinese16X12(279,116,0);				//'X'
			}
			if(FrontOrBack)
			{
				ShowString(ASCII_6X16,ShowDataBuffe,26,2);						//显示浮点数字符串
			}
			else
			{
				ShowString(ASCII_6X16,ShowDataBuffe,80,2);						//显示浮点数字符串
			}
		break;
		case LEFT:
			CursorMoveH = VISBLEMENUCURSOR;
			MenuIndex.MenuIndexC[2] = 0;
			MenuSelection = 0;
			G_KeyValue = NO_KEY_STATUS;
			HandlePage();
		break;
		default:
		break;
	}
}

void	Show_Edit_Linear_Para(float *DisplayPointsArrayFB)
{
	float Min=0,Max=80;
	unsigned char  TempC;//,TempM;
	const uchar LDataEmpty[] = {49,164,58}; 
	switch(G_KeyValue)
	{
		case NO_KEY_STATUS:
			ClearLcdScreen();
			MenuSelection = 0;
			if(LinearParaU.LinearPara.LinePointsNum > 20)
			{
				LinearParaU.LinearPara.LinePointsNum = 0;
			}
			if(LinearParaU.LinearPara.LinePointsNum != 0)
			{
				Display_Linear_Array(0,DisplayPointsArrayFB);							//数据不为空时，显示线性化数组
			}
			else
			{
				for(TempC = 0; TempC < 3; TempC++)
				{
					DisplayChinese16X12(LDataEmpty[TempC],TempC*12+52,0);			//显示汉字（16*12）
				}
			}
		break;
		case DOWN:
		if(LinearParaU.LinearPara.LinePointsNum != 0)
		{//数据不为空时才可以判断是否移动光标
			Linear_Para_Del_Flag = 0;
			if(CursorMoveH < 0xFD)
			{//光标能使时，才能移动光标
				CursorMoveH++;
				if(CursorMoveH == 6)
				{
					if(FrontOrBack)
					{
						EditValueFront = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,26,ArrayLinearMP);									//显示浮点数字符串
						FrontOrBack = 0;

						FloatToChar(EditValueBack,4);											//把浮点数转成字符数组
					}
					else
					{
						EditValueBack = CharToFloat();
						ShowString(ASCII_6X16,ShowDataBuffe,80,ArrayLinearMP);									//显示浮点数字符串
						FrontOrBack = 1;

						FloatToChar(EditValueFront,4);											//把浮点数转成字符数组
					}
					CursorMoveH = 0;
				}
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,26,ArrayLinearMP);							//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,80,ArrayLinearMP);							//显示浮点数字符串
				}
			}
			else
			{//选择被编辑的数据组（移动箭头）
				MenuSelection++;
				if(MenuSelection == LinearParaU.LinearPara.LinePointsNum)
				{
					MenuSelection = 0;
				}
//				G_KeyValue = NO_KEY_STATUS;
				Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
			}
		}
		break;
		case UP:
		if(LinearParaU.LinearPara.LinePointsNum != 0)
		{//数据不为空时才可以判断是否可以编辑数据
			Linear_Para_Del_Flag = 0;
			if( CursorMoveH > 0xF0 )
			{//选择被编辑的数据组（移动箭头）
				if(MenuSelection == 0)
				{
					MenuSelection = LinearParaU.LinearPara.LinePointsNum;
				}
				MenuSelection--;
				Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
			}
			else
			{//编辑数据
				EditDataAdd1();
				if(FrontOrBack)
				{
					ShowString(ASCII_6X16,ShowDataBuffe,26,ArrayLinearMP);							//显示浮点数字符串
				}
				else
				{
					ShowString(ASCII_6X16,ShowDataBuffe,80,ArrayLinearMP);							//显示浮点数字符串
				}
			}
		}
		break;
		case OK:
			if(LinearParaU.LinearPara.LinePointsNum != 0)
			{
				if(DLineS == 1)
				{
					if(Linear_Para_Del_Flag == 1)
					{//删除被选中的数据组合，序号反显表示被选中
						Linear_Para_Del_Flag = 0;
						for(;  MenuSelection < LinearParaU.LinearPara.LinePointsNum; MenuSelection++)
						{
							DisplayPointsArrayFB[MenuSelection*2] = DisplayPointsArrayFB[MenuSelection*2+2];
							DisplayPointsArrayFB[MenuSelection*2+1] = DisplayPointsArrayFB[MenuSelection*2+3];
						}
						DisplayPointsArrayFB[MenuSelection*2] = 0;
						DisplayPointsArrayFB[MenuSelection*2+1] = 0; 
						MenuSelection = 0;
						LinearParaU.LinearPara.LinePointsNum--;
						if(LinearParaU.LinearPara.LinePointsNum != 0)
						{
							Display_Linear_Array(0,DisplayPointsArrayFB);
						}
//						else
//						{
//							Display_MenuePage(ShuJuKuYiKong,2,1,5);
//							ShowString(ASCII_6X12,"      ",100,0);
//						}
//						*(*EditPointsArray).PChangeFlag = PARA_CHANGED;
//						HART_Variables.IfDataChanged = PARA_CHANGED;
					}
					else
					{//选中要删除的数据组合，使得该数据组合序号反显
						Linear_Para_Del_Flag = 1;
						Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
					}
				} 
				else if(DLineS == 2)
				{
					if(CursorMoveH > 0xFD)
					{//进入编辑数据状态，出现光标在第一位数据上
						FrontOrBack = 1;
						ArrayLinearMP = MenuSelection%4*2;						//行号
						InitLinePoint(MenuSelection,DisplayPointsArrayFB);
						CursorMoveH = 0;
						ShowString(ASCII_6X16,ShowDataBuffe,26,ArrayLinearMP);
					}
					else
					{//保存编辑的数据
						if(FrontOrBack)
						{
							EditValueFront = CharToFloat();
						}
						else
						{
							 EditValueBack = CharToFloat();
						}
//						DisplayChinese16X12(279,116,ArrayLinearMP);				//'X'
						if( (EditValueFront >= Min) &&(EditValueFront <= Max))				//判断前面一点编辑的数据是否超出范围
						{
							if( (EditValueBack >= Min) &&(EditValueBack <= Max))			//判断后面一点编辑的数据是否超出范围
							{
								DisplayPointsArrayFB[MenuSelection*2] = EditValueFront;
								DisplayPointsArrayFB[MenuSelection*2+1] = EditValueBack;
								TXByteCtr = 8;
								WriteParaToEEprom(LINEARPARAADDRESS+MenuSelection*8,&LinearParaU.LinearParaC[MenuSelection*8]);
//								DisplayChinese16X12(278,116,ArrayLinearMP);				//'√'
//								*(*EditPointsArray).PChangeFlag = PARA_CHANGED;
//								HART_Variables.IfDataChanged = PARA_CHANGED;
							}
							else
							{
								EditValueFront = DisplayPointsArrayFB[MenuSelection*2];
								EditValueBack = DisplayPointsArrayFB[MenuSelection*2+1];
							}
						}
						else
						{
							EditValueFront = DisplayPointsArrayFB[MenuSelection*2];
							EditValueBack = DisplayPointsArrayFB[MenuSelection*2+1];
						}
						CursorMoveH = VISBLEMENUCURSOR;
						Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
					}
				}
			}
		break;
		case LEFT:
			if(Linear_Para_Del_Flag == 1)
			{//退出删除状态
				Linear_Para_Del_Flag = 0;
				Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
				break;
			}
			if(CursorMoveH < 0xF0)
			{//退出编辑状态
				CursorMoveH = VISBLEMENUCURSOR;
				Display_Linear_Array(MenuSelection,DisplayPointsArrayFB);
			}
			else
			{//返回上一次菜单
				CursorMoveH = VISBLEMENUCURSOR;
				MenuIndex.MenuIndexC[2] = 0;
				G_KeyValue = NO_KEY_STATUS;
				MenuSelection = 0;
				HandlePage();
			}
			//线性化数组由大到小排序
		break;
		default:
		break;
	}
}

void	DisplayLine_Para(void)
{
	uchar TempC;
	switch(MenuSelection)
	{
		case 0:
			MaxMenuLine = 2;
			DisplayParaSingleS(&OtherParaU.OtherPara.DLineUseorUnuse,21);
			Display_MenuSingleSelectionPage(Page_LineItem,ShowDataBuffe[0],2,3,64,0);
		break;
		case 1:
			MaxMenuLine = 3;
			DisplayParaSingleS(&DLineS,0);
			Display_MenuSingleSelectionPage(Page_LineSItem,ShowDataBuffe[0],3,2,64,2);
			if(ModifyParaStatus == 1)
			{
				MenuIndex.MenuIndexC[2] = 1;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		case 2:
			MaxMenuLine = 2;
			DisplayParaSingleS(&OtherParaU.OtherPara.RLineUseorUnuse,22);
			Display_MenuSingleSelectionPage(Page_LineItem,ShowDataBuffe[0],2,3,64,4);
		break;
		case 3:
			MaxMenuLine = 3;
			DisplayParaSingleS(&DLineS,0);
			Display_MenuSingleSelectionPage(Page_LineSItem,ShowDataBuffe[0],3,2,64,6);
			if(ModifyParaStatus == 1)
			{
				MenuIndex.MenuIndexC[2] = 2;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		default:break;
	}

	if((CursorMoveH > 0xFD)&&(MenuIndex.MenuIndexC[2] == 0))
	{
		for(TempC = 0; TempC < 4; TempC++)
		{
			ShowString(ASCII_6X16,":",58,TempC*2);
		}
		Display_MenuSingleSelectionPage(Page_LineItem,OtherParaU.OtherPara.DLineUseorUnuse,2,3,64,0);
		Display_MenuSingleSelectionPage(Page_LineSItem,DLineS,3,2,64,2);
		Display_MenuSingleSelectionPage(Page_LineItem,OtherParaU.OtherPara.RLineUseorUnuse,2,3,64,4);
		Display_MenuSingleSelectionPage(Page_LineSItem,DLineS,3,2,64,6);
		MaxMenuLine = 4;
	}
}

void	DisplayLine_Para_en(void)
{
//	uchar TempC;
	switch(MenuSelection)
	{
		case 0:
			MaxMenuLine = 2;
			DisplayParaSingleS(&OtherParaU.OtherPara.DLineUseorUnuse,21);
			Display_MenuSingleSelectionPage(&Page_LineItem_en[0][0],ShowDataBuffe[0],2,4,58,3);
		break;
		case 1:
			MaxMenuLine = 3;
			DisplayParaSingleS(&DLineS,0);
			Display_MenuSingleSelectionPage(&Page_LineSItem_en[0][0],ShowDataBuffe[0],3,7,50,3);
			if(ModifyParaStatus == 1)
			{
				MenuIndex.MenuIndexC[2] = 1;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		case 2:
			MaxMenuLine = 2;
			DisplayParaSingleS(&OtherParaU.OtherPara.RLineUseorUnuse,22);
			Display_MenuSingleSelectionPage(&Page_LineItem_en[0][0],ShowDataBuffe[0],2,4,58,3);
		break;
		case 3:
			MaxMenuLine = 3;
			DisplayParaSingleS(&DLineS,0);
			Display_MenuSingleSelectionPage(&Page_LineSItem_en[0][0],ShowDataBuffe[0],3,7,50,3);
			if(ModifyParaStatus == 1)
			{
				MenuIndex.MenuIndexC[2] = 2;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
			}
		break;
		default:break;
	}

	if((CursorMoveH > 0xFD)&&(MenuIndex.MenuIndexC[2] == 0))
	{
		ClearLcdScreen();
		switch(MenuSelection)
		{
			case 0:
				ShowString(ASCII_6X16,"Dist/linearization",16,0);
				Display_MenuSingleSelectionPage(&Page_LineItem_en[0][0],OtherParaU.OtherPara.DLineUseorUnuse,2,4,58,3);
			break;
			case 1:
				ShowString(ASCII_6X16,"Dist/Lin/Edit",26,0);
				Display_MenuSingleSelectionPage(&Page_LineSItem_en[0][0],DLineS,3,7,50,3);
			break;
			case 2:
				ShowString(ASCII_6X16,"percent/linearization",5,0);
				Display_MenuSingleSelectionPage(&Page_LineItem_en[0][0],OtherParaU.OtherPara.RLineUseorUnuse,2,4,58,3);
			break;
			case 3:
				ShowString(ASCII_6X16,"percent/lin/Edit",20,0);
				Display_MenuSingleSelectionPage(&Page_LineSItem_en[0][0],DLineS,3,7,50,3);
			break;
			default:break;
		}
		MaxMenuLine = 4;
	}
}

void	DisplayJumpPage_Para(void)
{
	uchar TempC;
	float MaxLimit;
	if(MenuSelection != 0)
	{
		switch(MenuSelection)
		{
			case 1:
			case 3:
				MaxLimit = SystemParaU.SystemPara.QuickSetupPage_para[0];
			break;
			case 2:
				MaxLimit = 9000;
			break;
			default:break;
		}
		DisplayParaFloat(&SystemParaU.SystemPara.JumpPara[MenuSelection-1],48+MenuSelection,MaxLimit,0);
		ShowString(ASCII_6X16,ShowDataBuffe,64,MenuSelection*2);
	}
	else
	{
		DisplayParaSingleS(&OtherParaU.OtherPara.JumpMode,20);
		MaxMenuLine = 4;
		Display_MenuSingleSelectionPage(JumpSetupItem,ShowDataBuffe[0],4,4,64,0);
	}
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		for(TempC = 1; TempC < 4; TempC++)
		{
			ShowString(ASCII_6X16,":",58,TempC*2);
			FloatToChar(SystemParaU.SystemPara.JumpPara[TempC-1],4);
			ShowString(ASCII_6X16,ShowDataBuffe,64,TempC*2);
		}
		ShowString(ASCII_6X16,"m",100,2);
		ShowString(ASCII_6X16,"s",100,4);
		ShowString(ASCII_6X16,"m=s",100,6);//m/s
		ShowString(ASCII_6X16,":",58,0);
		Display_MenuSingleSelectionPage(JumpSetupItem,OtherParaU.OtherPara.JumpMode,4,4,64,0);
		MaxMenuLine = 4;
	}
}

void	DisplayJumpPage_Para_en(void)
{
//	uchar TempC;
	float MaxLimit;
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		if(MenuSelection > 0)	
			FloatToChar(SystemParaU.SystemPara.JumpPara[MenuSelection-1],4);
			switch(MenuSelection)
			{
				case 0:
					ShowString(ASCII_6X16,"Way/of/jump:",29,0);
					ShowDataBuffe[0] = OtherParaU.OtherPara.JumpMode;
				break;
				case 1:
					ShowString(ASCII_6X16,"Gap/distance:",29,0);
					ShowString(ASCII_6X16,"m",83,3);
				break;
				case 2:
					ShowString(ASCII_6X16,"Waitting/time:",26,0);
					ShowString(ASCII_6X16,"s",83,3);
				break;
				case 3:
					ShowString(ASCII_6X16,"Speed:",50,0);
					ShowString(ASCII_6X16,"m=s",83,3);
				break;
				default:break;
			}
		MaxMenuLine = 4;
	}
	if(MenuSelection != 0)
	{
		switch(MenuSelection)
		{
			case 1:
			case 3:
				MaxLimit = SystemParaU.SystemPara.QuickSetupPage_para[0];
			break;
			case 2:
				MaxLimit = 9000;
			break;
			default:break;
		}
		DisplayParaFloat(&SystemParaU.SystemPara.JumpPara[MenuSelection-1],48+MenuSelection,MaxLimit,0);
		ShowString(ASCII_6X16,ShowDataBuffe,47,3);
	}
	else
	{
		DisplayParaSingleS(&OtherParaU.OtherPara.JumpMode,20);
		MaxMenuLine = 4;
		Display_MenuSingleSelectionPage(&JumpSetupItem_en[0][0],ShowDataBuffe[0],4,11,37,3);
	}
}

void	DisplayUnechoPage_Para(void)
{
	if(MenuSelection != 0)
	{
		DisplayParaFloat(&SystemParaU.SystemPara.AppointDistance,48,SystemParaU.SystemPara.QuickSetupPage_para[0],0);
		ShowString(ASCII_6X16,ShowDataBuffe,64,2);
	}
	else
	{
		DisplayParaSingleS(&OtherParaU.OtherPara.UnechoMode,19);
		MaxMenuLine = 4;
		Display_MenuSingleSelectionPage(UnechoItem,ShowDataBuffe[0],4,4,64,0);
	}
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ShowString(ASCII_6X16,":",58,2);
		FloatToChar(SystemParaU.SystemPara.AppointDistance,4);
		ShowString(ASCII_6X16,"m",100,2);
		ShowString(ASCII_6X16,ShowDataBuffe,64,2);
		ShowString(ASCII_6X16,":",58,0);
		Display_MenuSingleSelectionPage(UnechoItem,OtherParaU.OtherPara.UnechoMode,4,4,64,0);
		MaxMenuLine = 2;
	}
}

void	DisplayUnechoPage_Para_en(void)
{
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		if(MenuSelection != 0)
		{
			ShowString(ASCII_6X16,"Assign/place:",29,0);
			FloatToChar(SystemParaU.SystemPara.AppointDistance,4);
			ShowString(ASCII_6X16,"m",83,3);
			ShowString(ASCII_6X16,ShowDataBuffe,47,3);
		}
		else
		{
			ShowString(ASCII_6X16,"Echo/lost/action:",17,0);
			Display_MenuSingleSelectionPage(&UnechoItem_en[0][0],OtherParaU.OtherPara.UnechoMode,4,6,53,3);
		}
		MaxMenuLine = 2;
	}
	else
	{
		if(MenuSelection != 0)
		{
			DisplayParaFloat(&SystemParaU.SystemPara.AppointDistance,48,SystemParaU.SystemPara.QuickSetupPage_para[0],0);
			ShowString(ASCII_6X16,ShowDataBuffe,47,3);
		}
		else
		{
			DisplayParaSingleS(&OtherParaU.OtherPara.UnechoMode,19);
			MaxMenuLine = 4;
			Display_MenuSingleSelectionPage(&UnechoItem_en[0][0],ShowDataBuffe[0],4,6,53,3);
		}
	}
}

void	DisplayAsciiInformation(uchar *AsciiInformation,uchar ParaAddress)
{
	uchar TempC;
	if(CursorMoveH == VISBLEEDITCURSOR)
	{
		for(TempC = 0; TempC <= Processed_DataType; TempC++)
			ShowDataBuffe[TempC] = AsciiInformation[TempC];
		CursorMoveH = 0;
	}
	ShowDataBuffe[Processed_DataType+1] =  '\0';
	
	if(ModifyParaStatus == 1)
	{
		for(TempC = 0; TempC <= Processed_DataType; TempC++)
			AsciiInformation[TempC] = ShowDataBuffe[TempC];
		if((ParaAddress != 0)||(ParaAddress != 1))
		{
			HartModfiyPara(ParaAddress);
		}
		TXByteCtr = Processed_DataType+1;
		switch(ParaAddress)
		{
			case 0:
				WriteParaToEEprom(OTHERPARAADDRESS+51,AsciiInformation);
			break;
			case 28:
				WriteParaToEEprom(OTHERPARAADDRESS+18,AsciiInformation);
			break;
			case 29:
				WriteParaToEEprom(OTHERPARAADDRESS+26,AsciiInformation);
			break;
			case 30:
				WriteParaToEEprom(OTHERPARAADDRESS+36,AsciiInformation);
			break;
//			case 31:
//				ResumeParameterType = 0x5A;
//			break;
			default:break;
		}
	}
}

void	DisplayStringBuffer(uchar *AsciiInformation)
{
	uchar TempC;
	for(TempC = 0; TempC <= Processed_DataType; TempC++)
	{
		if((AsciiInformation[TempC] < 0x30)||(AsciiInformation[TempC] > 0x5A))
			AsciiInformation[TempC] = 0x30;
		ShowDataBuffe[TempC] = AsciiInformation[TempC];
	}
	ShowDataBuffe[Processed_DataType+1] =  '\0';
}

void	DisplaySystemInformation(void)
{
	uchar TempC;
	switch(MenuSelection)
	{
		case 0:
			Processed_DataType = DATETYPE;
			DisplayAsciiInformation(OtherParaU.OtherPara.PDate,28);
			ShowString(ASCII_6X16,ShowDataBuffe,44,3);
		break;
		case 1:
			Processed_DataType = SNTYPE;
			DisplayAsciiInformation(OtherParaU.OtherPara.PSN,29);
			ShowString(ASCII_6X16,ShowDataBuffe,39,3);
		break;
		case 2:
			Processed_DataType = ASCIITYPE;
			DisplayAsciiInformation(OtherParaU.OtherPara.PDescriptor,30);
			ShowString(ASCII_6X16,ShowDataBuffe,23,3);
		break;
		case 3:
//			Processed_DataType = ASCIITYPE;
			CursorMoveH = HIDECURSOR;
			for(TempC = 0; TempC < 3; TempC++)
				ShowDataBuffe[TempC] = CpuVison[TempC];
			ShowDataBuffe[3] = '.';
			ShowDataBuffe[4] = '2';
			ShowDataBuffe[5] = '0';
			ShowDataBuffe[6] = '0';
			ShowDataBuffe[7] = '\0';
//			DisplayAsciiInformation(OtherParaU.OtherPara.CpuVison,29);
			ShowString(ASCII_6X16,ShowDataBuffe,44,3);
		break;
		default:break;
	}
	if(CursorMoveH > 0xFD)
	{
		ClearLcdScreen();
		switch(MenuSelection)
		{
			case 0:
				Processed_DataType = DATETYPE;
//				if(NextMenuYesOrNo == YES)
				SendHartReadCmd(251);
				DisplayStringBuffer(OtherParaU.OtherPara.PDate);
				ShowString(ASCII_6X16,ShowDataBuffe,44,3);
				
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Date/of/manufacture:",6,0);
			break;
			case 1:
				Processed_DataType = SNTYPE;
				SendHartReadCmd(252);
				DisplayStringBuffer(OtherParaU.OtherPara.PSN);
				ShowString(ASCII_6X16,ShowDataBuffe,39,3);
				
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Serial/number:",29,0);
			break;
			case 2:
				Processed_DataType = ASCIITYPE;
/*				if(OtherParaU.OtherPara.PDescriptor[0] != 'M')
				{
				  OtherParaU.OtherPara.PDescriptor[0] = 'M';
				  OtherParaU.OtherPara.PDescriptor[1] = 'P';
				  OtherParaU.OtherPara.PDescriptor[2] = 'S';
				  OtherParaU.OtherPara.PDescriptor[3] = '1';
				  OtherParaU.OtherPara.PDescriptor[4] = '3';
				  OtherParaU.OtherPara.PDescriptor[5] = '0';
				  OtherParaU.OtherPara.PDescriptor[6] = '0';
				  OtherParaU.OtherPara.PDescriptor[7] = 'P';
				  OtherParaU.OtherPara.PDescriptor[8] = '4';
				  OtherParaU.OtherPara.PDescriptor[9] = 'X';
				  OtherParaU.OtherPara.PDescriptor[10] = 'X';
				  OtherParaU.OtherPara.PDescriptor[11] = 'K';
				  OtherParaU.OtherPara.PDescriptor[12] = 'T';
				  OtherParaU.OtherPara.PDescriptor[13] = 'P';
				  OtherParaU.OtherPara.PDescriptor[14] = 'M';
				}*/
				SendHartReadCmd(253);
				DisplayStringBuffer(OtherParaU.OtherPara.PDescriptor);
				ShowString(ASCII_6X16,ShowDataBuffe,23,3);
				
				if(OtherParaU.OtherPara.Language == 0)
					ShowString(ASCII_6X16,"Part/number:",35,0);
			break;
		case 3://LCD Version
			CursorMoveH = HIDECURSOR;
			SendHartReadCmd(254);
			for(TempC = 0; TempC < 3; TempC++)
				ShowDataBuffe[TempC] = CpuVison[TempC];
			ShowDataBuffe[3] = '.';
			ShowDataBuffe[4] = '2';
			ShowDataBuffe[5] = '0';
			ShowDataBuffe[6] = '9';
			ShowDataBuffe[7] = '\0';
//			DisplayAsciiInformation(OtherParaU.OtherPara.CpuVison,29);
			ShowString(ASCII_6X16,ShowDataBuffe,44,3);
			if(OtherParaU.OtherPara.Language == 0)
				ShowString(ASCII_6X16,"Version/number:",26,0);
			break;
		case 4://LCD Version
//			SendHartReadCmd(255);
//			DisplayMeterStatus();
			break;
			default:break;
		}
		if(OtherParaU.OtherPara.Language == 1)
		{
			for(TempC = 0; TempC < 5; TempC++)
			{
				DisplayChinese16X12(Page_SystemInformation[MenuSelection*5+TempC],TempC*12+38,0);			//显示汉字（16*12）
			}
			if((MenuSelection== 1)||(MenuSelection == 2))
				ShowString(ASCII_6X16,":",98,0);
			else
				ShowString(ASCII_6X16,":",92,0);
		}
		MaxMenuLine = 4;
	}
}

void	DisplayCurrentAlarm(uchar PassParameter)
{
	uchar TempC;
	const char CurrentAlarmRetain[] ={53,101,0};
	switch(PassParameter)
	{
		case 0:
			if(OtherParaU.OtherPara.Language == 0)
			{
				ShowString(ASCII_6X16,"/Hold/",50,3);
			}
			else
			{
				for(TempC = 0; TempC < 3; TempC++)
				{
					DisplayChinese16X12(CurrentAlarmRetain[TempC],TempC*12+50,3);			//显示汉字（16*12）
				}
			}
		break;
		case 1:
			ShowString(ASCII_6X16,"3.5mA/",50,3);
		break;
		case 2:
			ShowString(ASCII_6X16,"20.5mA",50,3);
		break;
		case 3:
			ShowString(ASCII_6X16,"/22mA/",50,3);
		break;
		default:break;
	}
}

void	DisplayCurrentAlarmDirection(uchar TempParameter)
{
//	uchar TempC;
	if(TempParameter == 0)
		ShowString(ASCII_6X16,"4-20mA",50,3);
	else
		ShowString(ASCII_6X16,"20-4mA",50,3);
}
void	DisplayOtherSecure_Para(void)
{
	uchar TempC;
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		if(OtherParaU.OtherPara.Language != 0)
		{
			for(TempC = 0; TempC < 4; TempC++)
				DisplayChinese16X12(Page_OtherSecureSetup[MenuSelection*4+TempC],TempC*12+38,0);
			ShowString(ASCII_6X16,":",86,0);
		}
		else
		{
			switch(MenuSelection)
			{
				case 0:
					ShowString(ASCII_6X16,"Current/direction:",14,0);
				break;
				case 1:
					ShowString(ASCII_6X16,"Alarm/output:",29,0);
				break;
				case 2:
					ShowString(ASCII_6X16,"Boot/current:",16,0);
				break;
				default:break;
			}
		}

		switch(MenuSelection)
		{
			case 0:
				ShowDataBuffe[0] = OtherParaU.OtherPara.CurrentDirection;
			break;
			case 1:
				ShowDataBuffe[0] = OtherParaU.OtherPara.Alarm_OutCurrent;
			break;
			case 2:
				ShowDataBuffe[0] = OtherParaU.OtherPara.Boot_OutCurrent;
			break;
			default:break;
		}
		MaxMenuLine = 3;
	}
	switch(MenuSelection)
	{
		case 0:
			DisplayParaSingleS(&OtherParaU.OtherPara.CurrentDirection,13);
			if(CursorMoveH < 0xFD)
				MaxMenuLine = 2;
			else
				MaxMenuLine = 3;
			DisplayCurrentAlarmDirection(ShowDataBuffe[0]);
		break;
		case 1:
			DisplayParaSingleS(&OtherParaU.OtherPara.Alarm_OutCurrent,23);
			if(CursorMoveH < 0xFD)
				MaxMenuLine = 4;
			else
				MaxMenuLine = 3;
			DisplayCurrentAlarm(ShowDataBuffe[0]);
		break;
		case 2:
			DisplayParaSingleS(&OtherParaU.OtherPara.Boot_OutCurrent,24);
			if(CursorMoveH < 0xFD)
				MaxMenuLine = 4;
			else
				MaxMenuLine = 3;
			DisplayCurrentAlarm(ShowDataBuffe[0]);
		break;
		default:break;
	}
}

void	DisplayParaSafe_Para(void)
{
	uchar TempC;
	uchar Resume_ch[2] = {118,119};
	if((CursorMoveH > 0xFD)&&(ModifyParaStatus == 0))
	{
		ClearLcdScreen();
		if(OtherParaU.OtherPara.Language != 0)
		{
			for(TempC = 0; TempC < 6; TempC++)
				DisplayChinese16X12(Page_ParaSafe[MenuSelection*6+TempC],TempC*12+26,0);
			ShowString(ASCII_6X16,":",98,0);
		}
		else
		{
			switch(MenuSelection)
			{
				case 0:
					ShowString(ASCII_6X16,"Password/set:",29,0);
				break;
				case 1:
					ShowString(ASCII_6X16,"Write/to/instrument:",8,0);
				break;
				case 2:
					ShowString(ASCII_6X16,"Write/factory/parameter:",8,0);
				break;
				case 3:
					ShowString(ASCII_6X16,"Save/factory/parameter:",8,0);
				break;
				case 4:
					ShowString(ASCII_6X16,"Write/Default/parameter:",8,0);
				break;
				default:break;
			}
		}

		switch(MenuSelection)
		{
			case 0:
				for(TempC = 0; TempC < 5; TempC++)
				{
					if( (OtherParaU.OtherPara.UserPassword[TempC]<0x30)||(OtherParaU.OtherPara.UserPassword[TempC]>0x39) )
						OtherParaU.OtherPara.UserPassword[TempC] = 0x30;
					ShowDataBuffe[TempC] = OtherParaU.OtherPara.UserPassword[TempC];
				}
				ShowDataBuffe[5] = '\0';
			break;
			case 1:
			case 3:
				for(TempC = 0; TempC < 5; TempC++)
				{
					ShowDataBuffe[TempC] =  0x30;
				}
			break;
			default:break;
		}
		if((MenuSelection != 2)||(MenuSelection != 4))
			ShowString(ASCII_6X16,ShowDataBuffe,53,3);
		MaxMenuLine = 5;
	}
	switch(MenuSelection)
	{
		case 0:
			Processed_DataType = PASSWORDTYPE;
			DisplayAsciiInformation(OtherParaU.OtherPara.UserPassword,0);
			ShowString(ASCII_6X16,ShowDataBuffe,53,3);
		break;
		case 1:
		case 3:
			Processed_DataType = PASSWORDTYPE;
			for(TempC = 0; TempC < 9; TempC++)
				DisplayChinese16X12(0,TempC*12+14,6);
			DisplayAsciiInformation(ShowDataBuffe,1);
			ShowString(ASCII_6X16,ShowDataBuffe,53,3);
		break;
		case 2:
		case 4:
			if(CursorMoveH == VISBLEEDITCURSOR)
			{
				CursorMoveH = 0;
				Processed_DataType = BOOLTYPE;
			}
			
			if(OtherParaU.OtherPara.Language == 0)
			{
				ShowString(ASCII_6X16,"resume?",46,3);
			}
			else
			{
				for(TempC = 0; TempC < 2; TempC++)
					DisplayChinese16X12(Resume_ch[TempC],TempC*12+53,3);
				ShowString(ASCII_6X16,"?",77,3);
			}
			
			if(ModifyParaStatus == 1)
			{
				if(MenuSelection == 2)
					ResumeParameterType = 0xA5;//factory para
				else
					ResumeParameterType = 0x55; //default para
				HartModfiyPara(31);
			}
		break;
		default:break;
	}
}

void	DisplayMaxMinPage(void)
{
	uchar TempC,Temp;
	if((MenuSelection == 0)&&(ModifyParaStatus == 1))
	{
		SysRecordMaxMin[0] = 0;
		SysRecordMaxMin[1] = 80;
		CursorMoveH = 0xFF;
	}
	if(CursorMoveH >= 0xFD)
	{
		ClearLcdScreen();
		
		switch(MenuSelection)
		{
			case 0:
				if(OtherParaU.OtherPara.Language == 0)
				{
					ShowString(ASCII_6X16,"Delete",12,0);
					ShowString(ASCII_6X16,"Maximum",12,2);
					ShowString(ASCII_6X16,"Minimum",12,4);
				}
				else
				{
					for(Temp = 0; Temp < 3; Temp++)
					{
						for(TempC = 0; TempC < 4; TempC++)
							DisplayChinese16X12(Page_DiagnosisRecond[Temp*4+TempC],TempC*12+10,Temp*2);
					}
				}
				for(TempC = 1; TempC < 3; TempC++)
				{
					ShowString(ASCII_6X16,":",60,TempC*2);
					ShowString(ASCII_6X16,"m",104,TempC*2);
				}
			break;
			case 1:
				if(OtherParaU.OtherPara.Language == 0)
				{
					ShowString(ASCII_6X16,"Reboot/count",12,0);
				}
				else
				{
					for(TempC = 0; TempC < 4; TempC++)
						DisplayChinese16X12(Page_Reboot[TempC],TempC*12+36,0);
				}
				CharToAssII(Reboot_NoE_Hop_Count[0]);
				ShowString(ASCII_6X16,ShowDataBuffe,60,3);
//				CharToAssII(HardWareFault_Count);
//				ShowString(ASCII_6X16,ShowDataBuffe,60,5);
			break;
			case 2:
//				ClearLcdScreen();											//清屏
//				DrawChart();
//				DisplayMeasureV_Amplitude();
//				DiplayCureXY();
//				DrawCurve();
				MenuIndex.MenuIndexC[2] = 1;
				G_KeyValue = NO_KEY_STATUS;
				HandlePage();
//				InitReadDubleCurve();
			break;
			default:break;
		}
//		ShowString(ASCII_6X16,"<",4,0);
		MaxMenuLine = 2;
	}
}

/*
void	ReadParaFormMeter(void)
{
	switch(ParaAddressCopying)
	{
		case	11:
			SendFrameHeader(11,3);
			ParaAddressCopying = 17;
		break;
		case	17:
			SendFrameHeader(17,2);
			ParaAddressCopying = 19;
		break;
		case	19:
			SendFrameHeader(19,1);
			ParaAddressCopying = 20;
		break;
		case	20:
			SendFrameHeader(20,1);
			ParaAddressCopying = 21;
		break;
		case	21:
			SendFrameHeader(21,2);
			ParaAddressCopying = 23;
		break;
		case	23:
			SendFrameHeader(23,1);
			ParaAddressCopying = 24;
		break;
		case	24:
			SendFrameHeader(24,1);
			ParaAddressCopying = 25;
		break;
		case	25:
			SendFrameHeader(25,1);
			ParaAddressCopying = 26;
		break;
		case	26:
			SendFrameHeader(24,1);
			ParaAddressCopying = 27;
		break;
		case	27:
			SendFrameHeader(27,1);
			ParaAddressCopying = 34;
		break;
		case	34:
			SendFrameHeader(34,4);
			ParaAddressCopying = 38;
		break;
		case	38:
			SendFrameHeader(38,2);
			ParaAddressCopying = 40;
		break;
		case	40:
			SendFrameHeader(40,2);
			ParaAddressCopying = 42;
		break;
		case	42:
			SendFrameHeader(42,3);
			ParaAddressCopying = 45;
		break;
		case	45:
			SendFrameHeader(45,2);
			ParaAddressCopying = 47;
		break;
		case	47:
			SendFrameHeader(47,1);
			ParaAddressCopying = 48;
		break;
		case	48:
			SendFrameHeader(48,3);
			ParaAddressCopying = 55;
		break;
		default:break;
	}
}
*/

void	WiteParaToMeterInformation(void)
{
	uchar	TempC;
	uchar	WritingParaInformation[7] = {84,173,163,157,158,156,49};
	for(TempC = 0; TempC < 7; TempC++)
	{
		DisplayChinese16X12(WritingParaInformation[TempC],TempC*12+25,2);			//12/8  16*12
	}
}

void	WiteParaToMeterEndInformation(void)
{
	uchar	TempC;
	uchar	WritingParaEndInformation[7] = {0,0,163,156,49,0,0};
	for(TempC = 0; TempC < 7; TempC++)
	{
		DisplayChinese16X12(WritingParaEndInformation[TempC],TempC*12+25,2);			//12/8  16*12
	}
	ShowString(ASCII_6X16,"OK",73,2);
}
void	WiteParaToMeter(void)
{
	switch(ParaAddressCopying)
	{
		case	14:
			ParaAddressCopying = 17;
		break;
//		case	24:
//			ParaAddressCopying = 25;
//		break;
		case	31:
			ParaAddressCopying = 34;
		break;
		case	43:
			ParaAddressCopying = 44;
		break;
//		case	54:
//			ParaAddressCopying = 55;
//		break;
		default:break;
	}
	if(ParaAddressCopying < 55)
	{
		HartModfiyPara(ParaAddressCopying);
		if(WriteParaProgress > 20)
		{
			ClearLcdScreen();
			WiteParaToMeterInformation();
			WriteParaProgress = 5;			
		}
		DisplayProgressBar(WriteParaProgress);
		WriteParaProgress++;
		ParaAddressCopying++;
	}
	else
	{
		ClearLcdScreen();
		WiteParaToMeterEndInformation();
	}
}

void	WriteParaDefaultVToEEprom(void)
{
	uint TempC;
	OtherParaU.OtherPara.DampingTime = 5;
	for(TempC = 1; TempC < sizeof(OtherParaU.OtherParaC); TempC++)
	{
		OtherParaU.OtherParaC[TempC] = 0;
	}
	for(TempC = 0; TempC < 5; TempC++)
	{
		OtherParaU.OtherPara.UserPassword[TempC] = 0x30;
	}
	OtherParaU.OtherPara.DisplayPage_Para[2] = 0x25;
	CRCINIRES = 0xFFFF;
	for(TempC = 0; TempC < sizeof(OtherParaU.OtherParaC); TempC++)
	{
		CRCDI = OtherParaU.OtherParaC[TempC];
	}
	OtherParaU.OtherPara.Language = 1;
	for(TempC = 0; TempC < sizeof(SystemParaU.SystemParaC);  TempC++)
	{
		SystemParaU.SystemParaC[TempC] = 0;
	}
	SystemParaU.SystemPara.SystemCoefficient[1] = 1;
	for(TempC = 0; TempC < sizeof(LinearParaU.LinearParaC);  TempC++)
	{
		LinearParaU.LinearParaC[TempC] = 0;
	}
	WaitWriteQuene |= 0x07;
}
