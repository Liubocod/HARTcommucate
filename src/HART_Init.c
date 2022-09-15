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

#include "HART.h"
#include "System.c"


VariableStructureDef G_VariableStructureInfo = 
{
  /*0*/	IDENTIFY,	UCHAR,	UCHAR,	UCHAR_T,	  VariablePtrIndex1,	UnitTableIndex0,
};

ReceiveStructureDef G_ReceiveStructure = 
{
  0,	IDENTIFY,	 READ,	VARIABLE_ARR_0,
};
SendStructureDef G_SendStructure = 
{
  0x00,	IDENTIFY,	 SHORT_FRAME_REQUEST,	 READ,	 INIT_ADDR_BYTE_NUMBER,	0x00,	 0x00,	VARIABLE_ARR_0,
};
PageVariableTableDef G_PageVariableTable = {0,0};
VariableGroupDef G_VariableGroupTable = {0};
//命令执行数组
CommandDef G_CommandBuff[COMMAND_BUFF_SIZE] = {IDENTIFY};
/*
//当前页命令执行顺序表
//用来定义当前页面的命令执行数组结构
typedef struct
{
  uchar CurrentPageCommandNumber;
  uchar *CurrentPageCommandBuff;
}HART_CommandIndexDef;
//命令执行结构体变量*/
CommandExecuteBuffDef G_CurrentPageCommandExecuteStructure = 
{
  0,0,0,G_CommandBuff
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_GeneralFunctionTable[] =
{
  0X00,0X00,STR_INDEX_120,//linear  
  0X01,0X01,STR_INDEX_121,//square root  
  0X02,0X02,STR_INDEX_122,//cube root  
  0X03,0X03,STR_INDEX_123,//fifth root  
  0X04,0X04,STR_INDEX_124,//Special Curve  
  0X05,0X05,STR_INDEX_125,//square  
  0xFA,0x06,STR_INDEX_126,//Not Used
  0xFB,0x07,STR_INDEX_127,//None
  0xFC,0x08,STR_INDEX_128,//Unknown
  0xFD,0x09,STR_INDEX_129,//Special
  0xEF,0x0a,STR_INDEX_340,//SQROFF
  0xF0,0x0b,STR_INDEX_341,//SQRLI2/*
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_DispOutTable[] =
{
  0X00,	0X00,	STR_INDEX_829,	//PRES
  0X01,	0X01,	STR_INDEX_830,	//PRES %
  0X02,	0X02,	STR_INDEX_831,	//ENGR. PRES
  0X03,	0X03,	STR_INDEX_832,	//SP
  0X04,	0X04,	STR_INDEX_833,	//SP %
  0xFA,	0X05,	STR_INDEX_126,	//Not Used
  0xff,0xff,STR_INDEX_0,//结束符
};
const HART_UnitDef G_SquawkControlCodes[] = 
{
  0X00,0X00,STR_INDEX_616,//Off
  0X01,0X01,STR_INDEX_617,//On
  0X02,0X02,STR_INDEX_1103,//squawk once
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_ResponsModeCodes[] = 
{
  0X00,0X00,STR_INDEX_1112,//Filtering
  0X01,0X01,STR_INDEX_1113,//Quick
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_AddrTable[] =
{
  0X00,0X00,STR_INDEX_118,//Addr 0  
  0X01,0X01,STR_INDEX_380,//Addr 1  
  0X02,0X02,STR_INDEX_381,//Addr 2   
  0X03,0X03,STR_INDEX_382,//Addr 3   
  0X04,0X04,STR_INDEX_383,//Addr 4   
  0X05,0X05,STR_INDEX_384,//Addr 5   
  0x06,0x06,STR_INDEX_385,//Addr 6 
  0x07,0x07,STR_INDEX_386,//Addr 7 
  0x08,0x08,STR_INDEX_387,//Addr 8 
  0x09,0x09,STR_INDEX_388,//Addr 9 
  0x0a,0x0a,STR_INDEX_389,//Addr 10 
  0x0b,0x0b,STR_INDEX_390,//Addr 11
  0x0c,0x0c,STR_INDEX_391,//Addr 12 
  0x0d,0x0d,STR_INDEX_392,//Addr 13 
  0x0e,0x0e,STR_INDEX_393,//Addr 14 
  0x0f,0x0f,STR_INDEX_394,//Addr 15 
  0x10,0x10,STR_INDEX_940,//Addr 16
  0x11,0x11,STR_INDEX_941,//Addr 17
  0x12,0x12,STR_INDEX_942,//Addr 18
  0x13,0x13,STR_INDEX_943,//Addr 19
  0x14,0x14,STR_INDEX_944,//Addr 20
  0x15,0x15,STR_INDEX_945,//Addr 21
  0x16,0x16,STR_INDEX_946,//Addr 22
  0x17,0x17,STR_INDEX_947,//Addr 23
  0x18,0x18,STR_INDEX_948,//Addr 24
  0x19,0x19,STR_INDEX_949,//Addr 25
  0x1a,0x1a,STR_INDEX_950,//Addr 26
  0x1b,0x1b,STR_INDEX_951,//Addr 27
  0x1c,0x1c,STR_INDEX_952,//Addr 28
  0x1d,0x1d,STR_INDEX_953,//Addr 29
  0x1e,0x1e,STR_INDEX_954,//Addr 30
  0x1f,0x1f,STR_INDEX_955,//Addr 31
  0x20,0x20,STR_INDEX_956,//Addr 32
  0x21,0x21,STR_INDEX_957,//Addr 33
  0x22,0x22,STR_INDEX_958,//Addr 34
  0x23,0x23,STR_INDEX_959,//Addr 35
  0x24,0x24,STR_INDEX_960,//Addr 36
  0x25,0x25,STR_INDEX_961,//Addr 37
  0x26,0x26,STR_INDEX_962,//Addr 38
  0x27,0x27,STR_INDEX_963,//Addr 39
  0x28,0x28,STR_INDEX_964,//Addr 40
  0x29,0x29,STR_INDEX_965,//Addr 41
  0x2a,0x2a,STR_INDEX_966,//Addr 42
  0x2b,0x2b,STR_INDEX_967,//Addr 43
  0x2c,0x2c,STR_INDEX_968,//Addr 44
  0x2d,0x2d,STR_INDEX_969,//Addr 45
  0x2e,0x2e,STR_INDEX_970,//Addr 46
  0x2f,0x2f,STR_INDEX_971,//Addr 47
  0x30,0x30,STR_INDEX_972,//Addr 48
  0x31,0x31,STR_INDEX_973,//Addr 49
  0x32,0x32,STR_INDEX_974,//Addr 50
  0x33,0x33,STR_INDEX_975,//Addr 51
  0x34,0x34,STR_INDEX_976,//Addr 52
  0x35,0x35,STR_INDEX_977,//Addr 53
  0x36,0x36,STR_INDEX_978,//Addr 54
  0x37,0x37,STR_INDEX_979,//Addr 55
  0x38,0x38,STR_INDEX_980,//Addr 56
  0x39,0x39,STR_INDEX_981,//Addr 57
  0x3a,0x3a,STR_INDEX_982,//Addr 58
  0x3b,0x3b,STR_INDEX_983,//Addr 59
  0x3c,0x3c,STR_INDEX_984,//Addr 60
  0x3d,0x3d,STR_INDEX_985,//Addr 61
  0x3e,0x3e,STR_INDEX_986,//Addr 62
  0x3f,0x3f,STR_INDEX_987,//Addr 63
  0xff,0xff,STR_INDEX_0,//结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_DisplayPressTypeTable[] =
{
  0X00,0X00,STR_INDEX_377,//Nomal  
  0X01,0X01,STR_INDEX_378,//Device Pressure
  0X02,0X02,STR_INDEX_379,//absolute Pressure  
  0xff,0xff,STR_INDEX_0,//结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_ManufacturerCodeTable[] =
{
  0Xd4,0X00,STR_INDEX_579,//SIC 
  0X37,0X01,STR_INDEX_789,//YOKOGAWA
  0X26,0X02,STR_INDEX_884,//ROSEMOUNT
  0X2a,0X03,STR_INDEX_891,//SIEMENS
  0X17,0X04,STR_INDEX_888,//H
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_DeviceTypeTable[] =
{
  0X81,0X00,STR_INDEX_580,//_PDS4**H 
  0X04,0X01,STR_INDEX_788,//_EJA
  0X06,0X02,STR_INDEX_885,//_PRS_3051C
  0x0b,0X03,STR_INDEX_892,//_STN_P_DS
  0x21,0X04,STR_INDEX_889,//ST700
  0x87,0X05,STR_INDEX_989,//TTS
  0x82,0X06,STR_INDEX_1100,//HVP
  0x5C,0X07,STR_INDEX_1148,//HVP
  0xff,0xff,STR_INDEX_0,//结束符
};


/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_GeneralWriteProtectTable[] = 
{
  0X00,0X00,STR_INDEX_104,//NO
  0X01,0X01,STR_INDEX_103,//YES
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_TTS_SnsrTypeTable[] = 
{
  0X00,0X00,STR_INDEX_914,//RTD
  0X01,0X01,STR_INDEX_915,//OHM
  0X02,0X02,STR_INDEX_916,//TC
  0X03,0X03,STR_INDEX_917,//MV
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_TTS_SnsrModelTable[] = 
{
  0X00,0X00,STR_INDEX_927,//TC_B  
  0X01,0X01,STR_INDEX_928,//TC_E 
  0X02,0X02,STR_INDEX_929,//TC_J   
  0X03,0X03,STR_INDEX_930,//TC_K  
  0X04,0X04,STR_INDEX_931,//TC_N 
  0X05,0X05,STR_INDEX_932,//TC_R  
  0x06,0x06,STR_INDEX_933,//TC_S
  0x07,0x07,STR_INDEX_934,//TC_T
  0x08,0x08,STR_INDEX_253,//mV
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_TTS_SnsrModel_1Table[] = 
{
  0X00,0X00,STR_INDEX_918,//Cu50  
  0X01,0X01,STR_INDEX_919,//Cu100 
  0X02,0X02,STR_INDEX_920,//Pt10   
  0X03,0X03,STR_INDEX_921,//Pt100  
  0X04,0X04,STR_INDEX_922,//Pt1000 
  0X05,0X05,STR_INDEX_926,//OHM1
  //为了显示当前模式，附加的
  0x06,0x06,STR_INDEX_933,//TC_S
  0x07,0x07,STR_INDEX_934,//TC_T
  0x08,0x08,STR_INDEX_253,//mV
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_TTS_SnsrWiresTable[] = 
{
  0X00,0X00,STR_INDEX_923,//2 wires
  0X01,0X01,STR_INDEX_925,//4 wires
  0X02,0X02,STR_INDEX_924,//3 wires 
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_A0_AlarmTypeTable[] = 
{
  0X00,0X00,STR_INDEX_375,//high
  0X01,0X01,STR_INDEX_376,//low
  0xff,0xff,STR_INDEX_0,//结束符
};
/*				
typedef struct				
{				
  uchar UnitCode;//单位编码				
  uchar ArrIndex;//单位数组序号				
  uint StrIndex; //单位字符串序号				
}HART_UnitDef;				
*/				
const HART_UnitDef G_Eja530EngrUnitTable[] =				
{				
  0X00,	0X00,	STR_INDEX_852,		//NULL
  0X01,	0X01,	STR_INDEX_145,		//KPa
  0X02,	0X02,	STR_INDEX_149,		//MPa
  0X03,	0X03,	STR_INDEX_141,		//mbar
  0X04,	0X04,	STR_INDEX_140,		//bar
  0X05,	0X05,	STR_INDEX_139,		//psi
  0X06,	0X06,	STR_INDEX_853,		//psia
  0X07,	0X07,	STR_INDEX_137,		//mmH20
  0X08,	0X08,	STR_INDEX_138,		//mmHg
  0X09,	0X09,	STR_INDEX_854,		//mmHgA
  0X0a,	0X0a,	STR_INDEX_855,		//mmAq
  0X0b,	0X0b,	STR_INDEX_856,		//mmWG
  0X0c,	0X0c,	STR_INDEX_146,		//Torr
  0X0d,	0X0d,	STR_INDEX_134,		//inH20
  0X0e,	0X0e,	STR_INDEX_135,		//inHg
  0x0f,	0x0f,	STR_INDEX_857,		//inHgA
  0X10,	0X10,	STR_INDEX_858,		//ftH20
  0X11,	0X11,	STR_INDEX_859,		//gf/cm2
  0X12,	0X12,	STR_INDEX_860,		//kgf/cm2
  0X13,	0X13,	STR_INDEX_861,		//kgf/cm2G
  0X14,	0X14,	STR_INDEX_862,		//kg/cm2A
  0X15,	0X15,	STR_INDEX_147,		//atm
  0X16,	0X16,	STR_INDEX_221,		//Kg/h
  0X17,	0X17,	STR_INDEX_863,		//t/h
  0X18,	0X18,	STR_INDEX_864,		//m3/h
  0X19,	0X19,	STR_INDEX_865,		//m3/min
  0X1a,	0X1a,	STR_INDEX_178,		//l/h
  0X1b,	0X1b,	STR_INDEX_866,		//l/min
  0X1c,	0X1c,	STR_INDEX_867,		//kl/h
  0X1d,	0X1d,	STR_INDEX_868,		//kl/min
  0X1e,	0X1e,	STR_INDEX_869,		//Nl/h
  0X1f,	0X1f,	STR_INDEX_870,		//Nl/min
  0X20,	0X20,	STR_INDEX_871,		//Nm3/h
  0X21,	0X21,	STR_INDEX_872,		//Nm3/min
  0X22,	0X22,	STR_INDEX_873,		//ACFH
  0X23,	0X23,	STR_INDEX_874,		//ACFM
  0X24,	0X24,	STR_INDEX_875,		//SCFH
  0X25,	0X25,	STR_INDEX_876,		//SCFM
  0X26,	0X26,	STR_INDEX_877,		//GPH
  0X27,	0X27,	STR_INDEX_878,		//GPM 
  0X28,	0X28,	STR_INDEX_201,		//m
  0X29,	0X29,	STR_INDEX_204,		//mm
  0X2a,	0X2a,	STR_INDEX_202,		//in
  0X2b,	0X2b,	STR_INDEX_200,		//ft
  0X2c,	0X2c,	STR_INDEX_237,		//kg/m3
  0X2d,	0X2d,	STR_INDEX_879,		//g/cm3
  0xff,0xff,STR_INDEX_0,//结束符
};				


/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_GeneralUnitTable[] =
{
  0x00,0x00,STR_INDEX_128,
  0x01,0x01,STR_INDEX_134,//inH20
  0x02,0x02,STR_INDEX_135,//inHg
  0x03,0x03,STR_INDEX_136,//FtH20
  0x04,0x04,STR_INDEX_137,//mmH20
  0x05,0x05,STR_INDEX_138,//mmHg
  0x06,0x06,STR_INDEX_139,//psi
  0x07,0x07,STR_INDEX_140,//bar
  0x08,0x08,STR_INDEX_141,//mbar
  0x09,0x09,STR_INDEX_142,//g/Sqcm
  0x0a,0x0a,STR_INDEX_143,//kg/Sqcm
  0x0b,0x0b,STR_INDEX_144,//Pa
  0x0c,0x0c,STR_INDEX_145,//kPa
  0x0d,0x0d,STR_INDEX_146,//torr
  0x0e,0x0e,STR_INDEX_147,//atm
  0x0f,0x0f,STR_INDEX_152,//Cuft/min
  0x10,0x10,STR_INDEX_153,//gal/min
  0x11,0x11,STR_INDEX_154,//L/min
  0x12,0x12,STR_INDEX_155,//Impgal/min
  0x13,0x13,STR_INDEX_156,//Cum/h
  0x14,0x14,STR_INDEX_180,//ft/s
  0x15,0x15,STR_INDEX_181,//m/s
  0x16,0x16,STR_INDEX_157,//gal/s
  0x17,0x17,STR_INDEX_158,//MMgal/d
  0x18,0x18,STR_INDEX_159,//L/s
  0x19,0x19,STR_INDEX_160,//ML/d
  0x1a,0x1a,STR_INDEX_161,//Cuft/s
  0x1b,0x1b,STR_INDEX_162,//Cuft/d
  0x1c,0x1c,STR_INDEX_163,//Cum/s
  0x1d,0x1d,STR_INDEX_164,//Cum/d
  0x1e,0x1e,STR_INDEX_165,//Impgal/h
  0x1f,0x1f,STR_INDEX_166,//Impgal/d
  0x20,0x20,STR_INDEX_130,//degC
  0x21,0x21,STR_INDEX_131,//degF
  0x22,0x22,STR_INDEX_132,//degR
  0x23,0x23,STR_INDEX_133,//Kelvin
  0x24,0x24,STR_INDEX_253,//mV
  0x25,0x25,STR_INDEX_256,//ohm
  0x26,0x25,STR_INDEX_273,//Hz
  0x27,0x27,STR_INDEX_255,//mA
  0x28,0x28,STR_INDEX_186,//gal
  0x29,0x29,STR_INDEX_187,//L
  0x2a,0x2a,STR_INDEX_188,//Impgal
  0x2b,0x2b,STR_INDEX_189,//Cum
  0x2c,0x2c,STR_INDEX_200,//ft
  0x2d,0x2d,STR_INDEX_201,//m
  0x2e,0x2e,STR_INDEX_190,//bbl
  0x2f,0x2f,STR_INDEX_202,//in
  0x30,0x30,STR_INDEX_203,//cm 
  0x31,0x31,STR_INDEX_204,//mm
  0x32,0x32,STR_INDEX_205,//min
  0x33,0x33,STR_INDEX_206,//s
  0x34,0x34,STR_INDEX_207,//h
  0x35,0x35,STR_INDEX_208,//d
  0x36,0x36,STR_INDEX_251,//cST
  0x37,0x37,STR_INDEX_252,//cP
  0x38,0x38,STR_INDEX_274,//uMho
  0x39,0x39,STR_INDEX_275,//%
  0x3a,0x3a,STR_INDEX_254,//v
  0x3b,0x3b,STR_INDEX_276,//pH
  0x3c,0x3c,STR_INDEX_209,//g
  0x3d,0x3d,STR_INDEX_210,//kg
  0x3e,0x3e,STR_INDEX_211,//MetTon
  0x3f,0x3f,STR_INDEX_212,//lb
  0x40,0x40,STR_INDEX_213,//STon
  0x41,0x41,STR_INDEX_214,//LTon
  0x42,0x42,STR_INDEX_277,//mS/cm
  0x43,0x43,STR_INDEX_278,//uS/cm
  0x44,0x44,STR_INDEX_279,//N
  0x45,0x45,STR_INDEX_258,//Nm
  0x46,0x46,STR_INDEX_216,//g/s
  0x47,0x47,STR_INDEX_217,//g/min
  0x48,0x48,STR_INDEX_218,//g/h
  0x49,0x49,STR_INDEX_219,//kg/s
  0x4a,0x4a,STR_INDEX_220,//kg/m
  0x4b,0x4b,STR_INDEX_221,//kg/h
  0x4c,0x4c,STR_INDEX_222,//kg/d
  0x4d,0x4d,STR_INDEX_223,//MetTon/min
  0x4e,0x4e,STR_INDEX_224,//MetTon/h
  0x4f,0x4f,STR_INDEX_225,//MetTon/d
  0x50,0x50,STR_INDEX_226,//lb/s
  0x51,0x51,STR_INDEX_227,//lb/ min
  0x52,0x52,STR_INDEX_228,//lb/h
  0x53,0x53,STR_INDEX_229,//lb/d
  0x54,0x54,STR_INDEX_230,//STon/min
  0x55,0x55,STR_INDEX_231,//STon/h
  0x56,0x56,STR_INDEX_232,//STon/d
  0x57,0x57,STR_INDEX_233,//LTon/h
  0x58,0x58,STR_INDEX_234,//LTon/d
  0x59,0x59,STR_INDEX_259,//datherm
  0x5a,0x5a,STR_INDEX_235,//SGU
  0x5b,0x5b,STR_INDEX_236,//g/CuCm
  0x5c,0x5c,STR_INDEX_237,//kg/m3
  0x5d,0x5d,STR_INDEX_238,//lb/gal
  0x5e,0x5e,STR_INDEX_239,//lb/Cuft
  0x5f,0x5f,STR_INDEX_240,//g/mL
  0x60,0x60,STR_INDEX_241,//kg/L
  0x61,0x61,STR_INDEX_242,//g/L
  0x62,0x62,STR_INDEX_243,//lb/Cuin
  0x63,0x63,STR_INDEX_244,//STon/ Cuyd
  0x64,0x64,STR_INDEX_245,//degTwad
  0x65,0x65,STR_INDEX_280,//degBrix
  0x66,0x66,STR_INDEX_246,//degBaum hv
  0x67,0x67,STR_INDEX_247,//degBaum lt
  0x68,0x68,STR_INDEX_248,//degAPI
  0x69,0x69,STR_INDEX_281,//% sol-wt 
  0x6a,0x6a,STR_INDEX_282,//% sol-vol
  0x6b,0x6b,STR_INDEX_283,//degBall
  0x6c,0x6c,STR_INDEX_284,//proof/vol
  0x6d,0x6d,STR_INDEX_285,//proof/mass
  0x6e,0x6e,STR_INDEX_191,//bush
  0x6f,0x6f,STR_INDEX_192,//Cuyd
  0x70,0x70,STR_INDEX_193,//Cuft
  0x71,0x71,STR_INDEX_194,//Cuin
  0x72,0x72,STR_INDEX_182,//in/s
  0x73,0x73,STR_INDEX_183,//in/min
  0x74,0x74,STR_INDEX_184,//ft/min
  0x75,0x75,STR_INDEX_270,//deg/s
  0x76,0x76,STR_INDEX_271,//rev/s
  0x77,0x77,STR_INDEX_272,//rpm
  0x78,0x78,STR_INDEX_185,//m/h
  0x79,0x79,STR_INDEX_167,//Nm3/h
  0x7a,0x7a,STR_INDEX_168,//nl/h
  0x7b,0x7b,STR_INDEX_169,//StdCuft/min
  0x7c,0x7c,STR_INDEX_195,//bbl（liq）
  0x7d,0x7d,STR_INDEX_215,//ounce
  0x7e,0x7e,STR_INDEX_260,//ft lbf
  0x7f,0x7f,STR_INDEX_265,//kW
  0x80,0x80,STR_INDEX_261,//kWh
  0x81,0x81,STR_INDEX_266,//hp
  0x82,0x82,STR_INDEX_170,//Cuft/h
  0x83,0x83,STR_INDEX_171,//Cum/min
  0x84,0x84,STR_INDEX_172,//bbl/s
  0x85,0x85,STR_INDEX_173,//bbl/min
  0x86,0x86,STR_INDEX_174,//bbl/h
  0x87,0x87,STR_INDEX_175,//bbl/d
  0x88,0x88,STR_INDEX_176,//gal/h
  0x89,0x89,STR_INDEX_177,//Impgal/s
  0x8a,0x8a,STR_INDEX_178,//l/h
  0x8b,0x8b,STR_INDEX_286,//ppm
  0x8c,0x8c,STR_INDEX_267,//Mcal/h
  0x8d,0x8d,STR_INDEX_268,//MJ/h
  0x8e,0x8e,STR_INDEX_269,//Btu/h
  0x8f,0x8f,STR_INDEX_287,//deg
  0x90,0x90,STR_INDEX_288,//rad
  0x91,0x91,STR_INDEX_148,//inH20_60DegF
  0x92,0x92,STR_INDEX_249,//ug/L
  0x93,0x93,STR_INDEX_250,//ug/m3
  0x94,0x94,STR_INDEX_289,//%Cs
  0x95,0x95,STR_INDEX_290,//Vol% 
  0x96,0x96,STR_INDEX_295,//% Stm Qual
  0x97,0x97,STR_INDEX_296,//ftin16
  0x98,0x98,STR_INDEX_297,//Cuft/lb
  0x99,0x99,STR_INDEX_298,//pF
  0x9a,0x9a,STR_INDEX_291,//mL/L
  0x9b,0x9b,STR_INDEX_292,//uL/L
  0xa0,0x9c,STR_INDEX_299,//% plato
  0xa1,0x9d,STR_INDEX_293,//%LEL
  0xa2,0x9e,STR_INDEX_264,//Mcal
  0xa3,0x9f,STR_INDEX_257,//kO
  0xa4,0xa0,STR_INDEX_262,//MJ
  0xa5,0xa1,STR_INDEX_263,//Btu
  0xa6,0xa2,STR_INDEX_196,//NmlCum
  0xa7,0xa3,STR_INDEX_197,//NmlL
  0xa8,0xa4,STR_INDEX_198,//StdCuft
  0xa9,0xa5,STR_INDEX_294,//ppb
  0xeb,0xa6,STR_INDEX_179,//gal/d
  0xec,0xa7,STR_INDEX_199,//hL
  0xed,0xa8,STR_INDEX_149,//MPa
  0xee,0xa9,STR_INDEX_150,//in4H20
  0xef,0xaa,STR_INDEX_151,//mm4H20
  0xf0,0xab,STR_INDEX_300,//mh20
  0xf1,0xac,STR_INDEX_301,//mHg
  0xfa,0xad,STR_INDEX_302,//Not Used
  0xfb,0xae,STR_INDEX_127,//None
  0xfc,0xaf,STR_INDEX_128,//Unknown
  0xfd,0xb0,STR_INDEX_305,//Spcl
  0xff,0xff,STR_INDEX_0,//结束符
};


/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_Eja530UnitTable[] =
{
  0x00,0x00,STR_INDEX_128,
  0x01,0x01,STR_INDEX_880,//inH20@68degF
  0x02,0x02,STR_INDEX_135,//inHg
  0x03,0x03,STR_INDEX_881,//ftH20@68degF
  0x04,0x04,STR_INDEX_882,//mmH20@68degF
  0x05,0x05,STR_INDEX_138,//mmHg
  0x06,0x06,STR_INDEX_139,//psi
  0x07,0x07,STR_INDEX_140,//bar
  0x08,0x08,STR_INDEX_141,//mbar
  0x09,0x09,STR_INDEX_142,//g/Sqcm
  0x0a,0x0a,STR_INDEX_143,//kg/Sqcm
  0x0b,0x0b,STR_INDEX_144,//Pa
  0x0c,0x0c,STR_INDEX_145,//kPa
  0x0d,0x0d,STR_INDEX_146,//torr
  0x0e,0x0e,STR_INDEX_147,//atm
  0xed,0x0f,STR_INDEX_149,//MPa
  0xee,0x10,STR_INDEX_134,//in4H20
  0xef,0x11,STR_INDEX_137,//mm4H20
  0xf0,0x12,STR_INDEX_136,//mh20
  0xf1,0x13,STR_INDEX_883,//mHg
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CutModeFunctionTable[] =
{
  0X00,0X00,STR_INDEX_120,//linear
  0X01,0X01,STR_INDEX_615,//Zero    
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CutMode530FunctionTable[] =
{
  0X00,0X00,STR_INDEX_615,//Zero
  0X01,0X01,STR_INDEX_120,//linear
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_BiDirModeTable[] =
{
  0X00,0X00,STR_INDEX_616,//Off
  0X01,0X01,STR_INDEX_617,//On    
  0xff,0xff,STR_INDEX_0,//结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_H20UnitTable[] =
{
  0X00,0X00,STR_INDEX_618,//@4C
  0X01,0X01,STR_INDEX_619,//@20C(68F)
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_FlangeTypeTable[] =
{
  0X00,0X00,STR_INDEX_475,//Conventional
  0X01,0X01,STR_INDEX_477,//Remote~Seal
  0X02,0X02,STR_INDEX_74,//level
  0X03,0X03,STR_INDEX_620,//Thread
  0Xfc,0X04,STR_INDEX_128,//Unknown
  0Xfd,0X05,STR_INDEX_129,//Special
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_LM_FlangeTypeTable[] =
{
  0X0C,	0X00,	STR_INDEX_475,	//Conventional
  0X0D,	0X01,	STR_INDEX_476,	//Coplanar
  0X0E,	0X02,	STR_INDEX_477,	//Remote~Seal
  0X0F,	0X03,	STR_INDEX_478,	//Level_3_150
  0X10,	0X04,	STR_INDEX_479,	//Level_4_150
  0X11,	0X05,	STR_INDEX_480,	//Level_3_300
  0X12,	0X06,	STR_INDEX_481,	//Level_4_300
  0X13,	0X07,	STR_INDEX_482,	//Level_80_40
  0X14,	0X08,	STR_INDEX_483,	//Level_100_40
  0X15,	0X09,	STR_INDEX_484,	//Level_100_10_16
  0X16,	0X0A,	STR_INDEX_485,	//Level_2_150
  0X17,	0X0B,	STR_INDEX_486,	//Level_2_300
  0X18,	0X0C,	STR_INDEX_487,	//Level_50_6
  0X19,	0X0D,	STR_INDEX_488,	//Level_50_40
  0X2C,	0X0E,	STR_INDEX_489,	//1/2in~pipe_female
  0X2D,	0X0F,	STR_INDEX_490,	//DIN16288G~1/2~A~male
  0X2E,	0X10,	STR_INDEX_491,	//1/4in,~NPTF
  0XFC,	0X11,	STR_INDEX_128,	//Unknown
  0XFD,	0X12,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_RemoteSealTable[] =
{
  0X00,0X00,STR_INDEX_621,      //Wafer
  0X01,0X01,STR_INDEX_622,	//Nozzle
  0X02,0X02,STR_INDEX_623,	//HTV-W
  0X03,0X03,STR_INDEX_624,	//HTV-N
  0XFB,0X04,STR_INDEX_127,	//None
  0XFC,0X05,STR_INDEX_128,	//Unknown
  0Xfd,0X06,STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_SealFillFluidTable[] =
{
  0X00,0X00,STR_INDEX_557,	//silicone_oil
  0X01,0X01,STR_INDEX_625,	//SH704
  0X02,0X02,STR_INDEX_626,	//SH705
  0X03,0X03,STR_INDEX_627,	//Ethy~Gly/H20
  0X04,0X04,STR_INDEX_628,	//Prop~Gly/H20
  0Xfb,0X05,STR_INDEX_127,	//None
  0Xfc,0X06,STR_INDEX_128,	//Unknown
  0Xfd,0X07,STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};


/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_NumOfRmtSealTable[] =
{
  0X01,0X00,STR_INDEX_569,	//one_seal
  0X02,0X01,STR_INDEX_570,	//two_seals
  0Xfa,0X02,STR_INDEX_126,	//Not~Used
  0Xfb,0X03,STR_INDEX_127,	//None
  0Xfc,0X04,STR_INDEX_128,	//Unknown
  0Xfd,0X05,STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_FlangeMaterialTable[] =
{
  0X00,0X00,STR_INDEX_492,//carbon_steel
  0X01,0X01,STR_INDEX_493,//stainless_steel_304
  0X02,0X02,STR_INDEX_494,//stainless_steel_316
  0X03,0X03,STR_INDEX_495,	//hastelloy_c
  0X04,0X04,STR_INDEX_496,	//monel
  0X05,0X05,STR_INDEX_497,	//tantalum
  0X06,0X06,STR_INDEX_498,	//titanium
  0X07,0X07,STR_INDEX_499,	//pt_ir
  0X08,0X08,STR_INDEX_500,	//alloy_20
  0X09,0X09,STR_INDEX_501,	//co_cr_ni
  0X0A,0X0A,STR_INDEX_502,	//ptfe
  0X0B,0X0B,STR_INDEX_503,	//vito
  0X0C,0X0C,STR_INDEX_504,	//buna_n
  0X0D,0X0D,STR_INDEX_505,	//ethyl_prop
  0X0E,0X0E,STR_INDEX_506,	//urethane
  0X0F,0X0F,STR_INDEX_507,	//gold_monel
  0X10,0X10,STR_INDEX_508,	//tefzel
  0X11,0X11,STR_INDEX_509,	//ryton
  0X12,0X12,STR_INDEX_510,	//ceramic
  0X13,0X13,STR_INDEX_511,	//stainless_steel_3161s
  0X14,0X14,STR_INDEX_512,	//pvc
  0X15,0X15,STR_INDEX_513,	//nitrile_rubber
  0X16,0X16,STR_INDEX_514,	//kalrez
  0X17,0X17,STR_INDEX_515,	//inconel
  0X18,0X18,STR_INDEX_516,	//kynar
  0X19,0X19,STR_INDEX_517,	//aluminium
  0X1A,0X1A,STR_INDEX_518,	//nickel
  0X1B,0X1B,STR_INDEX_519,	//fep
  0X1C,0X1C,STR_INDEX_520,	//stainless_steel_316_t
  0X1D,0X1D,STR_INDEX_521,	//ICr18Ni9Ti
  0X1E,0X1E,STR_INDEX_522,	//hastelloy_c276
  0X1F,0X1F,STR_INDEX_523,	//klinger_c4401
  0X20,0X20,STR_INDEX_524,	//thermotork
  0X21,0X21,STR_INDEX_525,	//grafoil
  0X22,0X22,STR_INDEX_526,	//ptfe_coated_3161_sst
  0X23,0X23,STR_INDEX_527,	//gold_hastelloy_c276
  0X24,0X24,STR_INDEX_528,	//ptfe_glass
  0X25,0X25,STR_INDEX_529,	//ptfe_graphite
  0XEA,0X26,STR_INDEX_530,	//PTFE_hastelloy
  0XEB,0X27,STR_INDEX_531,	//stainless_steel_CF_8M
  0XEC,0X28,STR_INDEX_532,	//hastelloy_sst
  0XED,0X29,STR_INDEX_533,	//gold_plated_sst
  0XEF,0X2A,STR_INDEX_534,	//monel_400
  0XFA,0X2B,STR_INDEX_126,	//Not~Used
  0XFB,0X2C,STR_INDEX_127,	//None
  0XFC,0X2D,STR_INDEX_128,	//Unknown
  0Xfd,0X2E,STR_INDEX_129,      //Special
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_ModuleFillFluidTable[] =
{
  0X00,0X00,STR_INDEX_557,	//silicone_oil
  0X01,0X01,STR_INDEX_629,	//F~oil
  0Xfc,0X02,STR_INDEX_128,	//Unknown
  0Xfd,0X03,STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,        //结束符
};




/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_DisplayModeTable[] =
{
  0X00,0X00,STR_INDEX_630,	//Normal~%
  0X01,0X01,STR_INDEX_631,	//User~set
  0X02,0X02,STR_INDEX_632,	//User~set~&~%
  0X03,0X03,STR_INDEX_633,	//Input~press
  0X04,0X04,STR_INDEX_634,	//Input~press~&~%
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_EngrDispPointTable[] =
{
  0X00,0X00,STR_INDEX_635,	//0
  0X01,0X01,STR_INDEX_636,	//1
  0X02,0X02,STR_INDEX_637,	//2
  0X03,0X03,STR_INDEX_638,	//3
  0X04,0X04,STR_INDEX_843,	//4
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_SoftwareSealTable[] =
{
  0X01,0X00,STR_INDEX_790,	//keep
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_ExtSWTable[] =
{
  0X00,0X00,STR_INDEX_613,//Enable
  0X01,0X01,STR_INDEX_614,//Inhibit
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_ResoTable[] =
{
  0X00,0X00,STR_INDEX_840,//Normal
  0X01,0X01,STR_INDEX_841,//High Resolution
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_NoneTable[] =
{
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_LocalKeysTable[] =
{
  0X02,0X00,STR_INDEX_613,//Enable
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_AlarmSatTable[] =
{
  0X00,0X00,STR_INDEX_886,//Standard
  0X01,0X01,STR_INDEX_887,//User
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_EngrExpTable[] =
{
  0X00,	0X00,	STR_INDEX_848,	//*1
  0X01,	0X01,	STR_INDEX_849,	//*10
  0X02,	0X02,	STR_INDEX_850,	//*100
  0X03,	0X03,	STR_INDEX_851,	//*1000
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_SngrTrimCalTypeTable[] =
{
  0x00,	0x00,	STR_INDEX_581,	//DP
  0x01,	0x01,	STR_INDEX_446,	//GP
  0x02,	0x02,	STR_INDEX_447,	//AP
  0x03,	0x03,	STR_INDEX_448,	//HP
  0x04,	0x04,	STR_INDEX_449,	//LL
  0x05,	0x05,	STR_INDEX_450,	//DR
  0x06,	0x06,	STR_INDEX_451,	//DP/GP
  0xfa,	0x07,	STR_INDEX_452,	//Not_used
  0xfb,	0x08,	STR_INDEX_127,	//None
  0xfc,	0x09,	STR_INDEX_128,	//Unknown
  0xfd,	0x0a,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_MeterTypeTable[] =
{
  0x01,	0x00,	STR_INDEX_461,	//Installed
  0x02,	0x01,	STR_INDEX_462,	//Eng~unit
  0x03,	0x02,	STR_INDEX_463,	//%~rnge
  0x04,	0x03,	STR_INDEX_464,	//Alt~%~rnge|Eng~unit//用冒号代替了原两个竖的符号
  0x05,	0x04,	STR_INDEX_465,	//Custom~Meter~display
  0x06,	0x05,	STR_INDEX_466,	//Alt~custom|Eng~unit//用冒号代替了原两个竖的符号
  0x07,	0x06,	STR_INDEX_467,	//Alt~custom|%~rng//用冒号代替了原两个竖的符号
  0xfb,	0x07,	STR_INDEX_127,	//None
  0xfc,	0x08,	STR_INDEX_128,	//Unknown
  0xfd,	0x09,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_SelDecPtPosTable[] =
{
  0X00,	0X00,	STR_INDEX_468,	//XXXXX
  0X01,	0X01,	STR_INDEX_469,	//XXXX.X
  0X02,	0X02,	STR_INDEX_470,	//XXX.XX
  0X03,	0X03,	STR_INDEX_471,	//XX.XXX
  0X04,	0X04,	STR_INDEX_472,	//X.XXXX
  0xff,0xff,STR_INDEX_0,//结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_OringMaterialTable[] =
{
  0X0A,	0X00,	STR_INDEX_535,	//Teflow
  0X0B,	0X01,	STR_INDEX_536,	//Vition
  0X0C,	0X02,	STR_INDEX_537,	//Buna-n
  0X0D,	0X03,	STR_INDEX_538,	//Ethy-prop
  0X1F,	0X04,	STR_INDEX_523,	//klinger_c4401
  0X20,	0X05,	STR_INDEX_524,	//thermotork
  0X16,	0X06,	STR_INDEX_539,	//Kalrez
  0X21,	0X07,	STR_INDEX_540,	//Grafoil
  0X24,	0X08,	STR_INDEX_541,	//PEFE~Glass
  0X25,	0X09,	STR_INDEX_542,	//PEFE~Graphite
  0XFB,	0X0A,	STR_INDEX_127,	//None
  0XFC,	0X0B,	STR_INDEX_128,	//Unknown
  0XFD,	0X0C,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_LM_RemoteSealTable[] =
{
  0X02,	0X00,	STR_INDEX_543,	//CTW
  0X03,	0X01,	STR_INDEX_544,	//EFW
  0X04,	0X02,	STR_INDEX_545,	//PFW
  0X05,	0X03,	STR_INDEX_546,	//RFW
  0X06,	0X04,	STR_INDEX_547,	//RTW
  0X07,	0X05,	STR_INDEX_548,	//SCW
  0X08,	0X06,	STR_INDEX_549,	//SSW
  0X09,	0X07,	STR_INDEX_550,	//high_temperature
  0X0A,	0X08,	STR_INDEX_551,	//ffw
  0X0B,	0X09,	STR_INDEX_552,	//ucw
  0X0C,	0X0A,	STR_INDEX_553,	//tsw
  0X0D,	0X0B,	STR_INDEX_554,	//nwsp
  0X0E,	0X0C,	STR_INDEX_555,	//ssap
  0X0F,	0X0D,	STR_INDEX_556,	//sshp
  0XFB,	0X0E,	STR_INDEX_127,	//None
  0XFC,	0X0F,	STR_INDEX_128,	//Unknown
  0XFD,	0X10,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,//结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_LM_SealFillFluidTable[] =
{
  0X02,	0X00,	STR_INDEX_557,	//silicone_oil
  0X03,	0X01,	STR_INDEX_558,	//sytherm_800
  0X04,	0X02,	STR_INDEX_559,	//inert
  0X05,	0X03,	STR_INDEX_560,	//glycerin_h20
  0X06,	0X04,	STR_INDEX_561,	//prop_gly_h20
  0X07,	0X05,	STR_INDEX_562,	//neobee_m20
  0X08,	0X06,	STR_INDEX_563,	//syltherm~XLT
  0X09,	0X07,	STR_INDEX_564,	//Dioctyl~phthalate
  0X0A,	0X08,	STR_INDEX_565,	//D.~C.~704
  0X0B,	0X09,	STR_INDEX_566,	//Therminol~66
  0X0C,	0X0A,	STR_INDEX_567,	//D.~C.~210H
  0X0D,	0X0B,	STR_INDEX_568,	//Distilled~water
  0XFB,	0X0C,	STR_INDEX_127,	//None
  0XFC,	0X0d,	STR_INDEX_128,	//Unknown
  0XFD,	0X0e,	STR_INDEX_129,	//Special
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_HW_DisplaySetupTable[] =
{
  0x01,	0x00,	STR_INDEX_801,	//Differ.Press
  0x03,	0x01,	STR_INDEX_802,	//Loop~Output
  0x04,	0x02,	STR_INDEX_803,	//Percent~Output
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_HW_DisplayUnitTable[] =
{
  0xee,	0x00,	STR_INDEX_804,	//inH20@39F
  0x91,	0x01,	STR_INDEX_805,	//inH20@60F
  0x01,	0x02,	STR_INDEX_806,	//inH20@68F
  0x02,	0x03,	STR_INDEX_807,	//inH20@0C
  0x0a,	0x04,	STR_INDEX_812,	//kfg/cm2
  0x0c,	0x05,	STR_INDEX_145,	//kPa
  0x08,	0x06,	STR_INDEX_141,	//mbar
  0xef,	0x07,	STR_INDEX_808,	//mmH20@4C
  0x04,	0x08,	STR_INDEX_809,	//mmH20@68F
  0x05,	0x09,	STR_INDEX_810,	//mmHg@0C
  0xed,	0x0a,	STR_INDEX_149,	//Mpa
  0x0b,	0x0b,	STR_INDEX_144,	//Pa
  0x06,	0x0c,	STR_INDEX_139,	//psi
  0x0d,	0x0d,	STR_INDEX_146,	//torr
  0x0e,	0x0e,	STR_INDEX_147,	//atm
  0x07,	0x0f,	STR_INDEX_140,	//bar
  0x03,	0x10,	STR_INDEX_811,	//ftH20@68F
  0x09,	0x11,	STR_INDEX_813,	//gf/cm2
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_HW_DisplayPointTable[] =
{
  0x00,	0x00,	STR_INDEX_127,	//None
  0x01,	0x01,	STR_INDEX_814,	//.X
  0x02,	0x02,	STR_INDEX_815,	//.XX
  0x03,	0x03,	STR_INDEX_816,	//.XXX
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
锐达仪表介电常数功能码表
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;	
*/
const HART_UnitDef G_RADAR_DielTable[] =
{
  0x00,	0x00,	STR_INDEX_663,	//1.4-1.6
  0x01,	0x01,	STR_INDEX_664,	//1.6-1.9
  0x02,	0x02,	STR_INDEX_665,	//1.9-2.5
  0x03,	0x03,	STR_INDEX_669,	//2.5-4
  0x04,	0x04,	STR_INDEX_670,	//4-7
  0x05,	0x05,	STR_INDEX_673,	//>7	
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
锐达仪表介电常数功能码表
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;	
*/
const HART_UnitDef G_RADAR_LogicSelectTable[] =
{
  0x00,	0x00,	STR_INDEX_702,	//Largest	
  0x01,	0x01,	STR_INDEX_704,	//Foremost
  0x02,	0x02,	STR_INDEX_705,	//Successional
  0x03,	0x03,	STR_INDEX_703,	//Resolution
  0xff,0xff,STR_INDEX_0,        //结束符
};

/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///失波操作功能码表
const HART_UnitDef G_RadarELOTable[] =
{
  0X00,0X00,STR_INDEX_683,	//Hold
  0X01,0X01,STR_INDEX_737,	//Appoint
  0X02,0X02,STR_INDEX_736,	//Trend
  0X03,0X03,STR_INDEX_735,	//Alarm
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///跳变方式功能码表
const HART_UnitDef G_RadarJumpModeTable[] =
{
  0X00,0X00,STR_INDEX_741,	//Direct 
  0X01,0X01,STR_INDEX_743,	///Wait
  0X02,0X02,STR_INDEX_742,	//Speed
  0X03,0X03,STR_INDEX_736,	//Trend
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///启动电流和电流报警功能码表
const HART_UnitDef G_RadarCurrentOptTable[] =
{
  0X00,0X00,STR_INDEX_683,	//Hold	 
  0X01,0X01,STR_INDEX_686,	//3.5mA
  0X02,0X02,STR_INDEX_685,	//20.5mA
  0X03,0X03,STR_INDEX_684,	//22mA
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
//报警选择功能码表
const HART_UnitDef G_AlarmSelectionCodesTable[] =
{
  0,0,STR_INDEX_1117,	        //High alert
  1,1,STR_INDEX_1118,	        //Low alert
  239,2,STR_INDEX_1119,         //Hold last value
  240,3,STR_INDEX_1119,         //Hold last value
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///启动电流和电流报警功能码表
const HART_UnitDef G_CY_T1_CurrentTable[] =
{
  0X00,0X00,STR_INDEX_818,	//Disable
  0X01,0X01,STR_INDEX_613,	//Enable
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///轮询模式能码表
const HART_UnitDef G_RadarCurrentDirTable[] =
{
  0X00,0X00,STR_INDEX_681,	//4-20mA
  0X01,0X01,STR_INDEX_682,	//20-4mA
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///电流方向功能码表
const HART_UnitDef G_RadarPollModeTable[] =
{
  0X00,0X00,STR_INDEX_886,	//Standard
  0X01,0X01,STR_INDEX_92,	//Polling
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*///电流方向功能码表
const HART_UnitDef G_DispPresResoTable[] =
{
  1,0X00,STR_INDEX_1130,	//one digit
  2,0X01,STR_INDEX_1129,	//two digit 
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_HVP_YFCT_Table[] =
{
  0X00,0X00,STR_INDEX_1071,	//LIN
  0X01,0X01,STR_INDEX_1072,	//NLIN
  0X03,0X02,STR_INDEX_1076,	//RISE
  0X02,0X03,STR_INDEX_1077,	//FALL
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_HVP_SFCT_Table[] =
{
  0X00,0X00,STR_INDEX_1078,	//LIN linear
  240,0X01,STR_INDEX_1079,	//1:50 logarithm
  241,0X02,STR_INDEX_1080,	//50:1 quick open
  242,0X03,STR_INDEX_1081,	//FREE
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_HVP_AFCT_Table[] =
{
  0X00,0X00,STR_INDEX_1093,	//OFF
  1,1,STR_INDEX_1094,	//ON
  2,2,STR_INDEX_1095,	//LAST
  3,3,STR_INDEX_1096,	//POS
  0xff,0xff,STR_INDEX_0,        //结束符
};
/*
typedef struct
{
  uchar UnitCode;//单位编码
  uchar ArrIndex;//单位数组序号
  uint StrIndex; //单位字符串序号
}HART_UnitDef;
*/
const HART_UnitDef G_CY_HVP_YCLS_Table[] =
{
  0X00,0X00,STR_INDEX_1097,	//ALL
  1,1,STR_INDEX_1098,	//UP
  2,2,STR_INDEX_1099,	//DOWN
  3,3,STR_INDEX_104,	//NO
  0xff,0xff,STR_INDEX_0,        //结束符
};
const HART_UnitDef G_CY_PDS7DispValueTable[] = 
{
  0X00,0X00,STR_INDEX_1140,//Pressure / 压力
  0X01,0X01,STR_INDEX_1141,//percent / 百分比
  0X02,0X02,STR_INDEX_1142,//Loop current / 电流  
  0X03,0X03,STR_INDEX_1143,//pres/percent / 压力与百分比
  0X04,0X04,STR_INDEX_1144,//pres/temperature / 压力与温度
  0X05,0X05,STR_INDEX_1145,//pres/Loop C / 压力与电流
  0xff,0xff,STR_INDEX_0,//结束符
};

//G_VariableGroupAddress+159
//空子节，存储非定义字节
uchar G_None[LONG_UINT] = {0};

//HART变量#0
uchar G_254[UCHAR] = {0};
uchar G_ManufacturerID[UCHAR] = {0};
uchar G_DeviceType[UCHAR] = {0};
uchar G_NumRegPreams[UCHAR] = {LEAD_CODE_NUM};
uchar G_UniversalRev[UCHAR] = {0};
uchar G_FldDevRev[UCHAR] = {0};
uchar G_SoftwareRev[UCHAR] = {0};
uchar G_HardwareRev[UCHAR] = {0};
uchar G_DeviceMark[UCHAR] = {0};
uchar G_DeviceID[THREE_BYTES] = {0};
uchar G_NumRegPreamsSM[UCHAR] = {0};


//HART变量#1
uchar G_PV_Unit[UCHAR] = {0};
uchar G_UnitTemp[UCHAR] = {0};
uchar G_DampUnit[UCHAR] = {0x33};
uchar G_PV[FLOAT] = {0};
//HART变量#2
uchar G_PV_Current[FLOAT] = {0};
uchar G_PercentOfPV[FLOAT] = {0};
//HART命令变量#3
uchar G_SV_Unit[UCHAR] = {0};
uchar G_SV[FLOAT] = {0};
//HART命令变量#3
uchar G_TV_Unit[UCHAR] = {0};
uchar G_TV[FLOAT] = {0};
//HART命令变量#3
uchar G_QV_Unit[UCHAR] = {0};
uchar G_QV[FLOAT] = {0};
//HART变量#12
uchar G_Message[ASCII_24] = {0};
//HART变量#13
uchar G_Tag[ASCII_6] = {0};
uchar G_Description[ASCII_12] = {0};
uchar G_Date[THREE_BYTES] = {0};
//HART变量#14
uchar G_PV_SnsrSN[THREE_BYTES] = {0};
uchar G_PV_SnsrUNIT[UCHAR] = {0};
uchar G_PV_SnsrUSL[FLOAT] = {0};
uchar G_PV_SnsrLSL[FLOAT] = {0};
uchar G_PV_MinSpan[FLOAT] = {0};
//HART变量#15
uchar G_PV_AlarmSelectCode[UCHAR] = {0};
uchar G_PV_TransferCode[UCHAR] = {0};
uchar G_PV_RangeUnit[UCHAR] = {0};
uchar G_PV_USL[FLOAT] = {0};
uchar G_PV_LSL[FLOAT] = {0};
uchar G_PV_DampValue[FLOAT] = {0};
uchar G_WriteProtect[UCHAR] = {0};
//命令00 Private Label Distributor Code.
uchar G_PrivateLabelDistributorCode[UINT] = {0};
//HART变量#16
uchar G_AssemblyNum[THREE_BYTES] = {0};
uchar G_OutputLevel[FLOAT] = {0};

//HART变量#41
uchar G_BatteryPercent[UCHAR] = {0};
//HART变量保护数组
VariableProtectDef G_VariableProtect = {FLOAT,0,0,FALSE};



//写保护设置变量
uchar G_WriteProtectSet[UCHAR] = {0x05};
uchar G_WriteProtectCancel[UCHAR] = {0};

uchar G_MeterValue[ASCII_7] = 
{
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x00,
};

//uchar G_LeadCodeNumber = LEAD_CODE_NUM;
uchar G_XferFnctn[UCHAR] = {0};

//0x80命令未知变量1  
uchar G_SIEMENS_UpSnsrTrim[FLOAT] = {0};
uchar G_SIEMENS_LoSnsrTrim[FLOAT] = {0};
//0x80命令未知变量2
uchar G_SIEMENS_RootingCode[UCHAR] = {0x33};
//0x96命令未知变量
uchar G_SIEMENS_RootingWriteCode[UINT] = {0x33,0x39};
//响应码数组定义
uchar G_RecondCode[UINT] = {0};   

//数组大小定义成ASCII_33是因为显示该变量时使用了动态变量显示函数
//需要将数组最后一个元素初始化为0才能找到最后一个显示字节。
uchar G_LongTag[ASCII_33] = {0};
uchar G_CHUAN_YI_VariableDisMode[UINT] = {0x16,0xfa};
uchar G_CHUAN_YI_RootCutoffPt[UINT] = {0x33,0xfa};
uchar G_CHUAN_YI_TransmitterType[UINT] = {0x52,0xfa};

uchar G_CHUAN_YI_DisplayPressType[UINT] = {0x18,0xfa};
uchar G_PollingAddress[UCHAR] = {0};
uchar G_CurrentMode[UCHAR] = {0};



















//锐达仪表变量定义
//曲线终点定义
uchar G_RadarCurveEndP[FLOAT] = {0x40,0x80,0x00,0x00};
//曲线描点信息数组1
uchar G_RadarCurvePoint1[ASCII_20] = {0};
//曲线描点信息数组2
uchar G_RadarCurvePoint2[ASCII_20] = {0};
//曲线描点信息数组3
uchar G_RadarCurvePoint3[ASCII_20] = {0};
//曲线描点信息数组4
uchar G_RadarCurvePoint4[ASCII_20] = {0};
//曲线描点信息数组5
uchar G_RadarCurvePoint5[ASCII_20] = {0};
//命令00 Last Device Variable code.
uchar G_LastDeviceVariableCode[UCHAR] = {0};
//命令00 Configuration Change Counter.
uchar G_CnfChangeCounter[UINT] = {0};
//命令00 Extended Field Device Status
uchar G_ExtendedFieldDeviceStatus[UCHAR] = {0};
//命令00 Manufacturer Identification Code.
uchar G_ManufacturerIdentificationCode[UINT] = {0};
//命令00 Device Profile
uchar G_DeviceProfile[UCHAR] = {0};







/* Public variable float */

//SIEMENS Rootingvalue
//CHUAN_YI_RootCutoffPtValue
//RadarCableLength 锐达缆长变量定义
//G_EngrDispLRV  EJA 
//G_BoardTemperature[FLOAT] HVP
//80G雷达 Change speed
uchar G_PublicVF0[FLOAT] = {0};

//G_CYT1_CurrentAlm 报警电流值
//RadarCurveStartP 锐达曲线起点定义
//G_EngrDispURV EJA
//G_MinnmumTemperature[FLOAT] HVP
//CY_PDS7Simulate-----value
//80G雷达 Wave superiority.
uchar G_PublicVF1[FLOAT] = {0};

//RadarValue//当前测量值，空高
//G_LowCut//EJA
//G_MaximumTemperature[FLOAT] HVP
//CY_PDS7 AO upper limit value
//80G雷达 Wave Confirm Time.
uchar G_PublicVF2[FLOAT] = {0};

//RadarCR//控制频率
//G_FixPercentValue[FLOAT] HVP
//CY_PDS7 AO lower limit value
//80G雷达 Wave Min Resolution.
uchar G_PublicVF3[FLOAT] = {0};

//RadarFakeStart//虚假回波起点
//G_ValvePositionVercentage[FLOAT] HVP
//CY_PDS7 Temperature High alert value
//80G雷达 Appoint Dist.
uchar G_PublicVF4[FLOAT] = {0};

//RadarFakeEnd//虚假回波终点
//G_SL0[FLOAT] HVP;
//CY_PDS7 Temperature low alert value
//80G雷达 Jump Dist.
uchar G_PublicVF5[FLOAT] = {0};

//RadarLevelSpeed//物位速度
//G_SL1[FLOAT] HVP
//CY_PDS7 Pressure High alert value
//80G雷达 Waiting Time.
uchar G_PublicVF6[FLOAT] = {0};

//RadarSuperiority
//G_SL2[FLOAT] HVP
//CY_PDS7 Pressure low alert value
//80G雷达 Jump Speed.
uchar G_PublicVF7[FLOAT] = {0};

//RadarConfirmTime
//G_SL3[FLOAT] HVP
//CY_PDS7 Zero Value
//80G雷达 Distance zero point trim value.
uchar G_PublicVF8[FLOAT] = {0};

//RadarMinResolution//液晶端回波判决中设定的最小分辨率
//G_SL4[FLOAT] HVP
//80G雷达 Distance scale factor trim value.
uchar G_PublicVF9[FLOAT] = {0};

//G_RadarMeasure2
//G_SL5[FLOAT] HVP
//80G雷达 性能变量1
uchar G_PublicVF10[FLOAT] = {0};

//G_RadarMeasure1
//G_SL6[FLOAT] HVP
//80G雷达 性能变量2
uchar G_PublicVF11[FLOAT] = {0};

//G_RadarReality2
//G_SL7[FLOAT] HVP
//80G雷达 性能变量3
uchar G_PublicVF12[FLOAT] = {0};

//G_RadarReality1
//G_SL8[FLOAT] HVP
//80G雷达 性能变量4
uchar G_PublicVF13[FLOAT] = {0};

//G_RadarRatioCorrect
//G_SL9[FLOAT] HVP
//80G雷达 浮点型扩展变量
uchar G_PublicVF14[FLOAT] = {0};

//G_RadarZeroCorrect
//G_SL10[FLOAT] HVP
uchar G_PublicVF15[FLOAT] = {0};

//G_RadarFakeAmp
//G_SL11[FLOAT] HVP
uchar G_PublicVF16[FLOAT] = {0};

//G_RadarJumpSpeed
//G_SL12[FLOAT] HVP
uchar G_PublicVF17[FLOAT] = {0};

//G_RadarWaitTime
//G_SL13[FLOAT] HVP
uchar G_PublicVF18[FLOAT] = {0};

//G_RadarJumpDist
//G_SL14[FLOAT] HVP
uchar G_PublicVF19[FLOAT] = {0};

//G_RadarAppointDist
//G_SL15[FLOAT] HVP
uchar G_PublicVF20[FLOAT] = {0};

//G_SL16[FLOAT] HVP;
uchar G_PublicVF21[FLOAT] = {0};

//G_SL17[FLOAT] HVP
uchar G_PublicVF22[FLOAT] = {0};

//G_SL18[FLOAT] HVP
uchar G_PublicVF23[FLOAT] = {0};

//G_SL19[FLOAT] HVP
uchar G_PublicVF24[FLOAT] = {0};

//G_SL20[FLOAT] HVP
uchar G_PublicVF25[FLOAT] = {0};

//G_P1[FLOAT] HVP
uchar G_PublicVF26[FLOAT] = {0};

//G_I1[FLOAT] HVP
uchar G_PublicVF27[FLOAT] = {0};

//G_D1[FLOAT] HVP
uchar G_PublicVF28[FLOAT] = {0};

//G_P2[FLOAT] HVP
uchar G_PublicVF29[FLOAT] = {0};

//G_I2[FLOAT] HVP
uchar G_PublicVF30[FLOAT] = {0};

//G_D2[FLOAT] HVP
uchar G_PublicVF31[FLOAT] = {0};

//G_MA4[FLOAT] HVP
uchar G_PublicVF32[FLOAT] = {0};

//G_MA20[FLOAT] HVP
uchar G_PublicVF33[FLOAT] = {0};

//G_DEAD[FLOAT] HVP
uchar G_PublicVF34[FLOAT] = {0};

//uchar G_SPRA[FLOAT] HVP
uchar G_PublicVF35[FLOAT] = {0};

//uchar G_SPRE[FLOAT] HVP
uchar G_PublicVF36[FLOAT] = {0};

//uchar G_SCUA[FLOAT] HVP
uchar G_PublicVF37[FLOAT] = {0};

//uchar G_SCUE[FLOAT] HVP
uchar G_PublicVF38[FLOAT] = {0};

//G_SHUT[FLOAT] HVP
uchar G_PublicVF39[FLOAT] = {0};


/* public variable uchar */

//G_CYT1_SensorType//TTS
//G_RadarSNR//信噪比锐达
//G_CutMode//EJA EJA530
//G_OringMatl[UCHAR]//LM
//G_DisplaySetup[UCHAR]//Honeywell
//G_BoardTemperatureUnit HVP
//80G雷达 False Echo Inc
uchar G_PublicVC0[UCHAR] = {0};

//G_CHUAN_YI_Variable_Unit
//G_CYT1_SensorModel//TTS
//G_RadarPositionMark//最优波位置锐达
//G_DisplayMode//EJA
//G_DispOut1[UCHAR]//EJA530E
//G_MeterType[UCHAR]//LM
//G_DisplayUnit[UCHAR]//Honeywell
//G_MinnmumTemperatureUnit[UCHAR] HVP
//80G雷达 Dielectric Constant 
uchar G_PublicVC1[UCHAR] = {0};

//G_CHUAN_YI_DisplayPressTypeValue
//G_CYT1_SensorWires//TTS
//G_RadarAmplitude//最优波幅度锐达
//G_DisplayFnctn//EJA
//G_DispOut2[UCHAR]//EJA530E
//G_AlarmSatType[UCHAR]//LM
//G_DisplayPoint[UCHAR]//Honeywell
//G_MaximumTemperatureUnit HVP
//80G雷达 Logic Select
uchar G_PublicVC2[UCHAR] = {0};
//G_CHUAN_YI_TransmitterValue
//G_CYT1_DisplayCode1_M//TTS
//G_RadarDamp//锐达
//G_IsolMatl//EJA
//G_DispOut3[UCHAR]//EJA530E
//G_LocalKeys[UCHAR]//LM
//G_CA_1[UCHAR]//Honeywell
//G_RunningTimeUnit[UCHAR] HVP
//80G雷达 Echo Lost Operate 
uchar G_PublicVC3[UCHAR] = {0};

//G_CYT1_DisplayCode2_P//TTS
//G_RadarFakeInc//锐达
//G_FillFluid//EJA
//G_DispOut4[UCHAR]//EJA530E
//G_ModCfgType[UCHAR]//LM
//G_CA_2[UCHAR]//Honeywell
//G_ValveSegmentUnit[UCHAR] HVP
//CY_PDS7_SquawkRead/write
//80G雷达 Jump Way
uchar G_PublicVC4[UCHAR] = {0};

//G_CYT1_DisplayCode3_O//TTS
//G_RadarDieConstant//锐达介电常数
//G_GasketMatl//EJA
//G_DispReso[UCHAR]//EJA530E
//G_CMXfFnct[UCHAR]//LM
//G_CA_4[UCHAR]//Honeywell
//G_TempSegmentUnit[UCHAR] HVP
//CY_PDS7EnterExitSimulateMode
//80G雷达 Current Direction
uchar G_PublicVC5[UCHAR] = {0};

//G_CYT1_DisplayCode4_L//TTS
//G_RadarResolution//锐达
//G_FlangeMatl//EJA  LM
//G_PresDispPoint[UCHAR]//EJA530E
//G_CA_7[UCHAR]//Honeywell
//G_TotalTravelUnit[UCHAR] HVP
//CY_PDS7Simulate------unit
//80G雷达 Alarm Output 
uchar G_PublicVC6[UCHAR] = {0};

//G_RadarLogicSelect//锐达
//G_DV_Matl//EJA
//G_SpDispPoint[UCHAR]//EJA530E
//G_CMSelDecPtPos[UCHAR]//LM
//G_CA_8[UCHAR]//Honeywell
//G_TravelSegmentUnit[UCHAR] HVP
//CY_PDS7 error log,Error log information selection
//80G雷达 Boot Current
uchar G_PublicVC7[UCHAR] = {0};

//G_RadarParamSave//锐达
//G_FlangeType//EJA LM
//G_EngrExp[UCHAR]//EJA530E
//G_AlarmStatusCode[UCHAR] HVP
//CY_PDS7 Bi-dir Mode      
//80G雷达 Write protection
uchar G_PublicVC8[UCHAR] = {0};

//G_RadarRepeatCounter//锐达
//G_RS_IsolMatl//EJA
//G_BarIndicator[UCHAR]//EJA530E
//G_TrimToRecall[UCHAR]//LM
//G_StatusGroup0[UCHAR] HVP
//CY_PDS7 Response Mode  
//80G雷达 Parameter setting code.
uchar G_PublicVC9[UCHAR] = {0};

//G_RadarParaProtect//锐达
//G_NumRmtSeal//EJA
//G_EngrUnitCode[UCHAR]//EJA530E
//G_SnsrTrimCalType[UCHAR]//LM
//CY_PDS7 Temperature alerm Mode  
//80G雷达  Device Variable Code 1
uchar G_PublicVC10[UCHAR] = {0};

//G_RadarMinAmp//信号阈值锐达
//G_SealFillFluid//EJA LM
//G_FixControlMode[UCHAR] HVP
//CY_PDS7 Display Pressure % Resolution
//80G雷达  Device Variable Code 2
uchar G_PublicVC11[UCHAR] = {0};

//G_RadarBootCurrent//启动输出电流锐达
//G_RS_Type//EJA LM
//G_PST[UCHAR] HVP
//CY_PDS7 bar indicator display 
//80G雷达  Device Variable Code 3
uchar G_PublicVC12[UCHAR] = {0};

//G_RadarCurrentAlm//报警输出电流锐达
//G_ExtSM//EJA
//G_SP[UCHAR] HVP
//CY_PDS7 Write protect
//80G雷达  Device Variable Code 4
uchar G_PublicVC13[UCHAR] = {0};

//G_RadarCurrentDir//锐达
//G_SnsrTempUnit//EJA EJA530
//G_DiagnosticDataReset[UCHAR] HVP
//CY_PDS7 Transmitter Display Variable
//80G雷达  字符型扩展变量
uchar G_PublicVC14[UCHAR] = {0};

//G_RadarJumpMode//锐达
//G_StaticPresUnit//EJA
//G_YsyInfo[UCHAR] YFCT, SDIR, YDIR HVP 
//80G雷达  扩展变量序号
uchar G_PublicVC15[UCHAR] = {0};

//G_RadarELO//电流方向 锐达
//G_H20_Unit[UCHAR]//EJA
//G_SFCT[UCHAR] HVP
uchar G_PublicVC16[UCHAR] = {0};

//G_RadarPollMode//锐达
//G_SI_Option[UCHAR]//EJA
//G_AFCT[UCHAR] HVP
uchar G_PublicVC17[UCHAR] = {0};

//G_SoftwareSeal[UCHAR]//EJA
//G_YCLS [UCHAR] HVP
uchar G_PublicVC18[UCHAR] = {0};

//G_BiDirMode[UCHAR]//EJA
uchar G_PublicVC19[UCHAR] = {0};

//G_MeasType[UCHAR]//EJA
uchar G_PublicVC20[UCHAR] = {0};

//G_ModuleRange[UCHAR]//EJA//Honeywell
uchar G_PublicVC21[UCHAR] = {0};

//G_EngrDispPoint[UCHAR]//EJA
uchar G_PublicVC22[UCHAR] = {0};



//public variable uint
//G_SIEMENS_Unknown2[UINT]//SIEMENS//EJA
//G_HighAlarm[UINT]//LM
//G_ValveSegment1[UINT] HVP
uchar G_PublicVI0[UINT] = {0};

//G_SIEMENS_Unknown3[UINT]//SIEMENS
//G_LowAlarm[UINT]//LM
//G_ValveSegment2[UINT] HVP
uchar G_PublicVI1[UINT] = {0};

//G_HighSat[UINT]//LM
//G_ValveSegment3[UINT] HVP
uchar G_PublicVI2[UINT] = {0};

//G_LowSat[UINT]//LM
//G_ValveSegment4[UINT] HVP
uchar G_PublicVI3[UINT] = {0};

//G_ValveSegment5[UINT] HVP
uchar G_PublicVI4[UINT] = {0};

//G_TempSegment1[UINT] HVP
uchar G_PublicVI5[UINT] = {0};

//G_TempSegment2[UINT] HVP
uchar G_PublicVI6[UINT] = {0};

//G_TempSegment3[UINT] HVP
uchar G_PublicVI7[UINT] = {0};

//G_TempSegment4[UINT] HVP
uchar G_PublicVI8[UINT] = {0};

//G_TempSegment5[UINT] HVP
uchar G_PublicVI9[UINT] = {0};

//G_TempSegment6[UINT] HVP
uchar G_PublicVI10[UINT] = {0};

//G_TempSegment7[UINT] HVP
uchar G_PublicVI11[UINT] = {0};

//G_TempSegment8[UINT] HVP
uchar G_PublicVI12[UINT] = {0};

//G_ST[UINT] HVP
uchar G_PublicVI13[UINT] = {0};








//public variable long uint
//G_RadarVersion[LONG_UINT] Radar
//G_RunningTime[LONG_UINT] HVP
//CY_PDS7 Device style number 
//80G雷达  Device bariable code
uchar G_PublicVLI0[LONG_UINT] = {0};

//G_TotalTravel[LONG_UINT] HVP
//CY_PDS7 Customization number
uchar G_PublicVLI1[LONG_UINT] = {0};

//G_TravelSegment1[LONG_UINT] HVP
//通信成功率次数
uchar G_PublicVLI2[LONG_UINT] = {0xff};

//G_TravelSegment2[LONG_UINT] HVP
uchar G_PublicVLI3[LONG_UINT] = {0};

//G_TravelSegment3[LONG_UINT] = HVP
uchar G_PublicVLI4[LONG_UINT] = {0};

//G_TravelSegment4[LONG_UINT] HVP
uchar G_PublicVLI5[LONG_UINT] = {0};

//G_TravelSegment5[LONG_UINT] HVP
uchar G_PublicVLI6[LONG_UINT] = {0};


//public variable Unknown

//G_RadarPartNo[ASCII_16] Radar
//G_SIEMENS_Unknown1[ASCII_13]SIEMENS
//G_EngrUnit[ASCII_8] EJA
//G_EngrShortUnitCode[ASCII_12] EJA530E
//G_CMUpperValue[THREE_BYTES] LM
//G_LCD_Display[ASCII_14] Honeywell
//CY_PDS7 the Board Code
uchar G_PublicVUnknowA0[ASCII_16] = {0};

//G_RadarSerialNo[ASCII_11] Radar
//G_EnableWrt[ASCII_8] EJA
//G_EngrlongUnitCode[ASCII_8] EJA530E
//G_CMLowerValue[THREE_BYTES] LM
//CY_PDS7 Manufactured date
uchar G_PublicVUnknowA1[ASCII_11] = {0};

//G_RadarDate[ASCII_9] Radar
//G_NewPWD[ASCII_8] EJA
//G_CMUnits[ASCII_5] LM
uchar G_PublicVUnknowA2[ASCII_9] = {0};

//G_Model[ASCII_16] EJA
//G_CA_15[ASCII_16] Honeywell
uchar G_PublicVUnknowA3[ASCII_16] = {0};

//G_SerialNo[ASCII_16] EJA
uchar G_PublicVUnknowA4[ASCII_16] = {0};
//变量指针表
uchar* const G_VariableTablePtr[] = 
{
  G_None,	//VariablePtrIndex0
  G_254,	//VariablePtrIndex1
  G_ManufacturerID,	//VariablePtrIndex2
  G_DeviceType,	//VariablePtrIndex3
  G_NumRegPreams,	//VariablePtrIndex4
  G_UniversalRev,	//VariablePtrIndex5
  G_FldDevRev,	//VariablePtrIndex6
  G_SoftwareRev,	//VariablePtrIndex7
  G_HardwareRev,	//VariablePtrIndex8
  G_DeviceMark,	//VariablePtrIndex9
  G_DeviceID,	//VariablePtrIndex10
  G_NumRegPreamsSM,	//VariablePtrIndex11
  G_PV_Unit,	//VariablePtrIndex12
  G_UnitTemp,	//VariablePtrIndex13
  G_DampUnit,	//VariablePtrIndex14
  G_PV,	//VariablePtrIndex15
  G_PV_Current,	//VariablePtrIndex16
  G_PercentOfPV,	//VariablePtrIndex17
  G_SV_Unit,	//VariablePtrIndex18
  G_SV,	//VariablePtrIndex19
  G_TV_Unit,	//VariablePtrIndex20
  G_TV,	//VariablePtrIndex21
  G_QV_Unit,	//VariablePtrIndex22
  G_QV,	//VariablePtrIndex23
  G_Message,	//VariablePtrIndex24
  G_Tag,	//VariablePtrIndex25
  G_Description,	//VariablePtrIndex26
  G_Date,	//VariablePtrIndex27
  G_PV_SnsrSN,	//VariablePtrIndex28
  G_PV_SnsrUNIT,	//VariablePtrIndex29
  G_PV_SnsrUSL,	//VariablePtrIndex30
  G_PV_SnsrLSL,	//VariablePtrIndex31
  G_PV_MinSpan,	//VariablePtrIndex32
  G_PV_AlarmSelectCode,	//VariablePtrIndex33
  G_PV_TransferCode,	//VariablePtrIndex34
  G_PV_RangeUnit,	//VariablePtrIndex35
  G_PV_USL,	//VariablePtrIndex36
  G_PV_LSL,	//VariablePtrIndex37
  G_PV_DampValue,	//VariablePtrIndex38
  G_WriteProtect,	//VariablePtrIndex39
  G_PrivateLabelDistributorCode,	//VariablePtrIndex40
  G_AssemblyNum,	//VariablePtrIndex41
  G_OutputLevel,	//VariablePtrIndex42
  G_BatteryPercent,	//VariablePtrIndex43
  G_WriteProtectSet,	//VariablePtrIndex44
  G_WriteProtectCancel,	//VariablePtrIndex45
  G_MeterValue,	//VariablePtrIndex46
  G_XferFnctn,	//VariablePtrIndex47
  G_SIEMENS_UpSnsrTrim,	//VariablePtrIndex48
  G_SIEMENS_LoSnsrTrim,	//VariablePtrIndex49
  G_SIEMENS_RootingCode,	//VariablePtrIndex50
  G_SIEMENS_RootingWriteCode,	//VariablePtrIndex51
  G_RecondCode,	//VariablePtrIndex52
  G_LongTag,	//VariablePtrIndex53
  G_CHUAN_YI_VariableDisMode,	//VariablePtrIndex54
  G_CHUAN_YI_RootCutoffPt,	//VariablePtrIndex55
  G_CHUAN_YI_TransmitterType,	//VariablePtrIndex56
  G_CHUAN_YI_DisplayPressType,	//VariablePtrIndex57
  G_PollingAddress,	//VariablePtrIndex58
  G_CurrentMode,	//VariablePtrIndex59
  G_RadarCurveEndP,	//VariablePtrIndex60
  G_RadarCurvePoint1,	//VariablePtrIndex61
  G_RadarCurvePoint2,	//VariablePtrIndex62
  G_RadarCurvePoint3,	//VariablePtrIndex63
  G_RadarCurvePoint4,	//VariablePtrIndex64
  G_RadarCurvePoint5,	//VariablePtrIndex65
  G_PublicVF0,	//VariablePtrIndex66
  G_PublicVF1,	//VariablePtrIndex67
  G_PublicVF2,	//VariablePtrIndex68
  G_PublicVF3,	//VariablePtrIndex69
  G_PublicVF4,	//VariablePtrIndex70
  G_PublicVF5,	//VariablePtrIndex71
  G_PublicVF6,	//VariablePtrIndex72
  G_PublicVF7,	//VariablePtrIndex73
  G_PublicVF8,	//VariablePtrIndex74
  G_PublicVF9,	//VariablePtrIndex75
  G_PublicVF10,	//VariablePtrIndex76
  G_PublicVF11,	//VariablePtrIndex77
  G_PublicVF12,	//VariablePtrIndex78
  G_PublicVF13,	//VariablePtrIndex79
  G_PublicVF14,	//VariablePtrIndex80
  G_PublicVF15,	//VariablePtrIndex81
  G_PublicVF16,	//VariablePtrIndex82
  G_PublicVF17,	//VariablePtrIndex83
  G_PublicVF18,	//VariablePtrIndex84
  G_PublicVF19,	//VariablePtrIndex85
  G_PublicVF20,	//VariablePtrIndex86
  G_PublicVF21,	//VariablePtrIndex87
  G_PublicVF22,	//VariablePtrIndex88
  G_PublicVF23,	//VariablePtrIndex89
  G_PublicVF24,	//VariablePtrIndex90
  G_PublicVF25,	//VariablePtrIndex91
  G_PublicVF26,	//VariablePtrIndex92
  G_PublicVF27,	//VariablePtrIndex93
  G_PublicVF28,	//VariablePtrIndex94
  G_PublicVF29,	//VariablePtrIndex95
  G_PublicVF30,	//VariablePtrIndex96
  G_PublicVF31,	//VariablePtrIndex97
  G_PublicVF32,	//VariablePtrIndex98
  G_PublicVF33,	//VariablePtrIndex99
  G_PublicVF34,	//VariablePtrIndex100
  G_PublicVF35,	//VariablePtrIndex101
  G_PublicVF36,	//VariablePtrIndex102
  G_PublicVF37,	//VariablePtrIndex103
  G_PublicVF38,	//VariablePtrIndex104
  G_PublicVF39,	//VariablePtrIndex105
  G_PublicVC0,	//VariablePtrIndex106
  G_PublicVC1,	//VariablePtrIndex107
  G_PublicVC2,	//VariablePtrIndex108
  G_PublicVC3,	//VariablePtrIndex109
  G_PublicVC4,	//VariablePtrIndex110
  G_PublicVC5,	//VariablePtrIndex111
  G_PublicVC6,	//VariablePtrIndex112
  G_PublicVC7,	//VariablePtrIndex113
  G_PublicVC8,	//VariablePtrIndex114
  G_PublicVC9,	//VariablePtrIndex115
  G_PublicVC10,	//VariablePtrIndex116
  G_PublicVC11,	//VariablePtrIndex117
  G_PublicVC12,	//VariablePtrIndex118
  G_PublicVC13,	//VariablePtrIndex119
  G_PublicVC14,	//VariablePtrIndex120
  G_PublicVC15,	//VariablePtrIndex121
  G_PublicVC16,	//VariablePtrIndex122
  G_PublicVC17,	//VariablePtrIndex123
  G_PublicVC18,	//VariablePtrIndex124
  G_PublicVC19,	//VariablePtrIndex125
  G_PublicVC20,	//VariablePtrIndex126
  G_PublicVC21,	//VariablePtrIndex127
  G_PublicVC22,	//VariablePtrIndex128
  G_PublicVI0,	//VariablePtrIndex129
  G_PublicVI1,	//VariablePtrIndex130
  G_PublicVI2,	//VariablePtrIndex131
  G_PublicVI3,	//VariablePtrIndex132
  G_PublicVI4,	//VariablePtrIndex133
  G_PublicVI5,	//VariablePtrIndex134
  G_PublicVI6,	//VariablePtrIndex135
  G_PublicVI7,	//VariablePtrIndex136
  G_PublicVI8,	//VariablePtrIndex137
  G_PublicVI9,	//VariablePtrIndex138
  G_PublicVI10,	//VariablePtrIndex139
  G_PublicVI11,	//VariablePtrIndex140
  G_PublicVI12,	//VariablePtrIndex141
  G_PublicVI13,	//VariablePtrIndex142
  G_PublicVLI0,	//VariablePtrIndex143
  G_PublicVLI1,	//VariablePtrIndex144
  G_PublicVLI2,	//VariablePtrIndex145
  G_PublicVLI3,	//VariablePtrIndex146
  G_PublicVLI4,	//VariablePtrIndex147
  G_PublicVLI5,	//VariablePtrIndex148
  G_PublicVLI6,	//VariablePtrIndex149
  G_PublicVUnknowA0,	//VariablePtrIndex150
  G_PublicVUnknowA1,	//VariablePtrIndex151
  G_PublicVUnknowA2,	//VariablePtrIndex152
  G_PublicVUnknowA3,	//VariablePtrIndex153
  G_PublicVUnknowA4,	//VariablePtrIndex154
  G_LastDeviceVariableCode,             //VariablePtrIndex155
  G_CnfChangeCounter,                   //VariablePtrIndex156
  G_ExtendedFieldDeviceStatus,          //VariablePtrIndex157
  G_ManufacturerIdentificationCode,     //VariablePtrIndex158
  G_DeviceProfile,                      //VariablePtrIndex159
  G_ShowCurveData,                      //VariablePtrIndex160
  G_ShowFakeCurveData,                      //VariablePtrIndex161
};

/* 单位码表数组 */
const HART_UnitDef* const G_UnitTableIndexPtr[] = 
{
  NULL,	//UnitTableIndex0
  G_GeneralUnitTable,	//UnitTableIndex1
  G_GeneralFunctionTable,	//UnitTableIndex2
  G_GeneralWriteProtectTable,	//UnitTableIndex3
  G_A0_AlarmTypeTable,	//UnitTableIndex4
  G_CY_TTS_SnsrTypeTable,	//UnitTableIndex5
  G_CY_TTS_SnsrModelTable,	//UnitTableIndex6
  G_CY_TTS_SnsrWiresTable,	//UnitTableIndex7
  G_CY_TTS_SnsrModel_1Table,	//UnitTableIndex8
  G_DisplayPressTypeTable,	//UnitTableIndex9
  G_ManufacturerCodeTable,	//UnitTableIndex10
  G_DeviceTypeTable,	//UnitTableIndex11
  G_CutModeFunctionTable,	//UnitTableIndex12
  G_CutMode530FunctionTable,	//UnitTableIndex13
  G_BiDirModeTable,	//UnitTableIndex14
  G_H20UnitTable,	//UnitTableIndex15
  G_RemoteSealTable,	//UnitTableIndex16
  G_FlangeTypeTable,	//UnitTableIndex17
  G_SealFillFluidTable,	//UnitTableIndex18
  G_NumOfRmtSealTable,	//UnitTableIndex19
  G_ModuleFillFluidTable,	//UnitTableIndex20
  G_DisplayModeTable,	//UnitTableIndex21
  G_EngrDispPointTable,	//UnitTableIndex22
  G_FlangeMaterialTable,	//UnitTableIndex23
  G_SoftwareSealTable,	//UnitTableIndex24
  G_ExtSWTable,	//UnitTableIndex25
  G_Eja530UnitTable,	//UnitTableIndex26
  G_Eja530EngrUnitTable,	//UnitTableIndex27
  G_DispOutTable,	//UnitTableIndex28
  G_ResoTable,	//UnitTableIndex29
  G_EngrExpTable,	//UnitTableIndex30
  G_OringMaterialTable,	//UnitTableIndex31
  G_MeterTypeTable,	//UnitTableIndex32
  G_LocalKeysTable,	//UnitTableIndex33
  G_NoneTable,	//UnitTableIndex34
  G_SngrTrimCalTypeTable,	//UnitTableIndex35
  G_SelDecPtPosTable,	//UnitTableIndex36
  G_LM_FlangeTypeTable,	//UnitTableIndex37
  G_OringMaterialTable,	//UnitTableIndex38
  G_LM_RemoteSealTable,	//UnitTableIndex39
  G_LM_SealFillFluidTable,	//UnitTableIndex40
  G_AlarmSatTable,	//UnitTableIndex41
  G_RADAR_DielTable,	//UnitTableIndex42
  G_RADAR_LogicSelectTable,	//UnitTableIndex43
  G_RadarELOTable,	//UnitTableIndex44
  G_RadarCurrentDirTable,	//UnitTableIndex45
  G_RadarJumpModeTable,	//UnitTableIndex46
  G_RadarCurrentOptTable,	//UnitTableIndex47
  G_RadarPollModeTable,	//UnitTableIndex48
  G_CY_T1_CurrentTable,	//UnitTableIndex49
  G_CY_HVP_YFCT_Table,	//UnitTableIndex50
  G_CY_HVP_SFCT_Table,	//UnitTableIndex51
  G_CY_HVP_AFCT_Table,	//UnitTableIndex52
  G_CY_HVP_YCLS_Table,	//UnitTableIndex53
  G_HW_DisplayPointTable,	//UnitTableIndex54
  G_HW_DisplayUnitTable,	//UnitTableIndex55
  G_HW_DisplaySetupTable,	//UnitTableIndex56
  G_AddrTable,          //UnitTableIndex57
  G_SquawkControlCodes,	//UnitTableIndex58
  G_ResponsModeCodes,//UnitTableIndex59
  G_AlarmSelectionCodesTable,//UnitTableIndex60
  G_DispPresResoTable,//UnitTableIndex61
  G_CY_PDS7DispValueTable,//UnitTableIndex62
};
//Revision
//HART_VersionDef G_HART_VersionFlag = HART_VERSION_5;


HART_SendFrameDef  G_SendFrameStructure;
HART_ReceiveFrameDef G_ReceiveFrameStructure;
uchar G_SendReceiveDataBuff[SEND_DATA_BUFF_SIZE] = {0};

uchar G_FrameReceiveBuff[HART_FRAME_BUFF_SIZE];
uchar G_FrameReceiveBuffIndex = 0;
//HART通信帧接收处理状态变量，描述接收帧处理
HART_ReceiveFlag G_RxFrameVerifyFlag = REC_STANDBY;
HART_RS_Flag G_HART_ReceiveEN = SEND_START;
uchar G_HART_ReceiveFrameType = REC_STANDBY;


HART_HandleFlagDef G_HART_HandleFlag = HART_STANDBY;

uchar G_CommandVariableNum[COMMAND_BUFF_SIZE] = {0};
bool8 G_CommunicationStatus = TRUE;
CommandDef G_HART_ReceiveTableRealCommandID = IDENTIFY;









