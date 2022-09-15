//#define	LCDFORWARDDIRECTION
#define	MAININTERFACE		0
#define	MAINMENUPAGE		1
#define	INPUTPASSWORDINTERFACE	2
#define	READINGPARAPAGE		3
#define	WRITINGPARAPAGE		4
#define	QUICKVIEWCURVE		6
#define	VIEWRECORDCURVEECHO	10
#define	QUICKSETUPINTERFACE	257
#define	BASICSETUPINTERFACE	513
#define	DISPLAYSETUPPAGE		769
#define	SYSTEMSETUPPAGE		1025
#define	LINEARIZATIONPAGE		1281
#define	SECURESETUPPAGE		1537
#define	HARTCPAGE			1793
#define	SYSTEMDISPAGE		2049
#define	SYSTEMINFORMATION		2305
#define	SYSTEMRECORDCURVE		2561

#define	ZOOMCURVERPAGE		262401

#define	ZOOMCURVEPAGE		8
#define	FAKEENTERPAGE		196865
#define	FZOOMCURVERPAGE		262401

#define	XZOOMCURVEPAGE		264
#define	YZOOMCURVEPAGE		520
#define	NOZOOMCURVEPAGE		776
#define	SETCURVERANGEPAGE		1032
#define	FAKEMODIFYPAGE		1288
#define	HIGHDEADSETPAGE		1544
#define	LOWERDEADSETPAGE		1800
#define	THRESHOLDSETPAGE		2056

#define	MODFYNCURVEPAGE		66824
#define	MODFYHCURVEPAGE		132360
#define	MODFYLCURVEPAGE		197896
#define	MODFYPCURVEPAGE		263432
#define	MODFYMCURVEPAGE		328968
#define	MODFYDCURVEPAGE		394504

#define	ECHOADJUDGEPAGE		66561
#define	CURRENTPARAPAGE		132097
#define	DISTANCEPARAPAGE		197633
#define	DISTANCECOEFFICIENTPAGE		263169
#define	MAPPINGPARAPAGE		328705

#define	SECUREUNECHOPAGE		67073
#define	SECUREJUMPPAGE		132609
#define	SECUREOTHER			198145
#define	PARASAFEPAGE		263681

#define	DLINEARPAGE			66817
#define	SLINEARPAGE			132353

#define	ECHOPARAPAGE		67585
#define	ECHOENTERPAGE		133121
#define	MAXMINRECORDPAGE		67585
#define	MAXDEADCURVE		328193
#define	MINDEADCURVE		393729
#define	THRESHOLDCURVE		459265

#define	VIEWCURVEECHO		68097
#define	VIEWCURVEMEASURED		133633

#define	MEANING_SENSOR_DISWAY_LIAOGAO		0
#define	MEANING_SENSOR_DISWAY_KONGGAO		1
#define	MEANING_SENSOR_DISWAY_BILI		2
#define	MEANING_SENSOR_DISWAY_DIANLIU		3
#define	MEANING_SENSOR_DISWAY_PERSENT		4

#define	MEANING_SENSOR_UNIT_MI			0
#define	MEANING_SENSOR_UNIT_FENMI		1
#define	MEANING_SENSOR_UNIT_LIMI		2
#define	MEANING_SENSOR_UNIT_HAOMI		3

#define	LCDCURVEHIGH				47.0
#define	LCDCURVELLIMIT				54
#define	LCDCURVEHLIMIT				7

#define	LCDCURVESTARTPAGE				1
#define	LCDCURVEENDPAGE				7

#define	LCDCURVESTARTCOLUMN			20
#define	LCDCURVEENDCOLUMN				121

#define	BarPostionY					6
#define	BarPostionX_Start				18
#define	BarPostionX_End				119

#define	ASCII_6X16					0x00
#define	ASCII_18X48					0x01
#define	ASCII_5X8					0x02
#define	ASCII_11X16					0x03
#define	ASCII_25X48					0x04

#define	PAGE00_DISPLAYVALUE_FONT		ASCII_18X48

#define	PasswordRight				1
#define	PasswordErro				0

#define	HIDECURSOR					0xFF
#define	VISBLEMENUCURSOR				0xFE
#define	VISBLEEDITCURSOR				0XFD
#define	VISIBLECURSOR				0

#define	UNMODIFIED					0
#define	MODIFYING					1

#define	NO						0
#define	YES						1

#define	FRONT						1
#define	BACK						0

#define	BOOLTYPE					0
#define	LCDCONTRASTTYPE				1
#define	CHARTYPE					1
#define	INTTYPE					3
#define	PASSWORDTYPE				4
#define	FLOATTYPE					5
#define	DATETYPE					7
#define	SNTYPE					9
#define	ASCIITYPE					14
#define	NOTYPE					0xFF

#define	NODATAWRITE					0
#define	WRINTINGPARA				1
#define	NEXTPAGE					2
#define	PAGESTARTWRITE				3
#define	WRITEPARAEND				0xFF
//参数结构定义
#define	INITFLAGADDRESS				0
#define	OTHERPARAADDRESS				INITFLAGADDRESS+2
#define	SYSTEMPARAADDRESS				OTHERPARAADDRESS+60
#define	LINEARPARAADDRESS				SYSTEMPARAADDRESS+150
#define	EMPTYCURVEADDRESS				LINEARPARAADDRESS+400

#define	DAMPINGTIMEADDRESS			INITFLAGADDRESS+2
#define	DIELECTRICCONSTANTADDRESS		DAMPINGTIMEADDRESS+1

#define	CURVEUPDATE					10
//
#define	DEFAULTDAMPINGTIME			5

#define	MaxRange					70
#define	MenueStartH					10

#define	I2CURRENTADDRESS				43

#define	SystemZeroDist				0.6662
#define	SystemProportion				1.0501
typedef struct                     
{
	float	QuickSetupPage_para[4];			//
	float SystemCoefficient[2];
	float DeadZone[2];
	float ObjectChangSpeed;
	float	CurrentSetup[3];
	float	MappingPara[2];
	float AppointDistance,JumpPara[3];
	float	EchoAdjudgeV;
	float ConfirmEchoDelay;
	float MinDistinctiveness;
	float ReceordCurvePage_para[2];
	uint	SystemParaCRCcode;
}SystemParaStruct;

typedef struct                     
{
	float LinearParaFB[20][2],ScaleParaFB[20][2];
	uchar LinePointsNum,ScalePointsNum;
	uint	LinearCRCcode;
}LinearStruct;

typedef struct                     
{
	uchar FakeWaveGain,DampingTime,DielectricConstant,CurrentDirection;			//基本设置参数
	uchar DisplayPage_Para[3];												//显示设置参数
	uchar HartAddress,HartCStype;												//Hart通信设置参数
	uchar	UnechoMode,JumpMode;								//跳变、失波操作
	uchar	DLineUseorUnuse,RLineUseorUnuse;
	uchar	Alarm_OutCurrent;
	uchar	Boot_OutCurrent;
	uchar EchoMinAmplitude;
	uchar EchoAdjudge;
	uchar SuccessionDistance;
	uchar PDate[8];
	uchar PSN[10];
	uchar PDescriptor[15];
	uchar UserPassword[5];
	uchar Language;
	uint	OtherParaCRCcode;
}OtherParaStruct;

union
{
	SystemParaStruct SystemPara;
	uchar SystemParaC[sizeof(SystemPara)];
}SystemParaU;

union
{
	LinearStruct LinearPara;
	uchar	LinearParaC[sizeof(LinearPara)];
}LinearParaU;

union
{
	OtherParaStruct	OtherPara;
	uchar	OtherParaC[sizeof(OtherPara)];
}OtherParaU;
union
{
	float	MasterVariableF[8];
	uchar	MasterVariableC[32];
}MasterVariableU;
float SysRecordMaxMin[2],Curve_One_H,CurveStartEnd[2];
uchar	UpdateLcdFlag,Sencond,ChangeStartAddress,MarkBestWavePostion,MarkBestWaveAmplitude,SignalNoiseRadio,Distinctiveness,UpdateCurveFlag,ReadUpperFlag,DelayCount;
uchar ParaAddressCopying,WriteParaProgress,LanguageSlect,MarkBestWavePostionBackup,RecordFlag,EchoPostionV[4];
uchar	CurveLimitH,CurveLimitL,Reboot_NoE_Hop_Count[3],MeterStatus,ResumeParameterType,Key_P_Count,UnKey_P_Count,HartDeviceId[3][7];
uchar CpuVison[3];
uchar	HartSendCount,HartSendMaxN,IIcOrHart,HartReceiveBuffer[30],HartTRFlag,HartTxEnd,HartRxFlag,CurveData[100],ReHartSendCount;
uchar *UnitString,LineOrScale,Wait_Off_Power;
uint	BVSample;
void	WriteParaDefaultVToEEprom(void);
void	UpdateMainInterface(void);
void	DisplayMeasurePageBackground(void);

