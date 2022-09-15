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

#include "HART_Init.c"
#include "CurvePage.h"
#define IS_SINGLE_ERROR_RANGE   ((RecondCode > 0)&&(RecondCode <= 7))||\
    ((RecondCode >= 16)&&(RecondCode <= 23))||((RecondCode >= 32)&&(RecondCode <= 64))
#define IS_MULTIPLE_ERROR_RANGE ((RecondCode >= 9)&&(RecondCode <= 13))||\
      ((RecondCode >= 65)&&(RecondCode <= 95))||(RecondCode == 15)||(RecondCode == 28)||(RecondCode == 29)
#define IS_SINGLE_WARNING_RANGE         ((RecondCode >= 24)&&(RecondCode <= 27))||((RecondCode >= 96)&&(RecondCode <= 111))
#define IS_MULTIPLE_WARNING_RANGE ((RecondCode >= 112)&&(RecondCode <= 127))||\
      (RecondCode == 8)||(RecondCode == 14)||(RecondCode == 30)||(RecondCode == 31)
#define IS_CY_PROCESS_HIGH  ((ProductTypeAndID == CHUAN_YI_TYPE1)&&((ExecutingCommand == PV_ZERO_SET)\
        ||(ExecutingCommand == SET_LSL)||(ExecutingCommand == SET_LUL)))
        
#define RESEND_TIMES                     2
#define ADDR_14                          14
#define ADDR_31                          31
#define ADDR_63                          63
#define ADDR_6                           6
#define ADDR_8                           8
#define LONG_FRAME_DATA_NUM_INDEX        0x07
#define SHORT_FRAME_DATA_NUM_INDEX       0x03

//如果超过这个时间没有接收到回应帧，既定为超时一次
#define RECEIVE_TIME_INTERVAL 800

void HART_ReceiveStateReset();
//接收帧长度运算变量
unsigned char FrameLength = MAX_FRAME_LENGTH;
//接收帧分段处理变量
HART_ReceiveFlag FrameHandle = REC_STANDBY;

typedef enum 
{
SHORT_FRAME_ERR,
LONG_FRAME_ERR,
VALID_FRAME,
RESPOND_CODE_ERR,
CRC_ERR,
}RecHandleDef;

void HART_FrameSend(void);
void HART_AbnormalStatusHandleModule();
void HART_SendLeadCodeLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex);
void HART_SendDelimiterLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex);
void HART_SendSlaveAddrLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex);
void HART_SendCommandLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex);
void HART_SendDataLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex);
uchar HART_CRC(uchar *const FrameBuff,uchar FrameBuffLength,bool8 IsSendFrame);
void HART_SendFrameStructureInit(CommandDef Command);
void HART_StartConnect(PollingTypeDef ConnetectWay,uchar StartAddr);
void HART_FrameStringSend(uchar *const FrameBuff,uchar const FrameBuffLength);
void HART_InfoBuffPtrInit(void);
RecHandleDef HART_ReceiveFrameHandle();
void HART_ReceiveCheckoutLoad(uchar ReceiveIndex );
void HART_ReceiveCommandLoad(uchar *const ReceiveIndex );
void HART_ReceiveAddrBuffLoad();
void HART_ReceiveDataBuffLoad(uchar *const ReceiveIndex);
void HART_ReceiveDataByteNumberLoad(uchar *const ReceiveIndex);
void HART_ReceiveDelimiterLoad(uchar *const ReceiveIndex);
void HART_SingleAddrConnect();
uchar HART_IntToString(long unsigned int Data,uchar *const DeviceStr);
void HART_IdentifyReceiveFrameAnalysis(void );
PageCommandNumDef HART_CommandSend();
void HART_BusStart(void);
void HART_CommandInitHandle();
void HART_ReceiveErrHandle();
void HART_InitCompleteHandle(void );
void HART_ReceiveSuccessHandle();
void HART_CommunicateHandle();
void HART_CommandSendIndexReset();
void InitialpageHandle();
void HART_ReceiveFrameAnalysis();
bool8 HART_AddrCompare();

uchar HART_ReceiveStructVariableAssign(uint VariableIndex,uchar ValueAddr);
bool8 HART_MonthHandle(uchar *constMonth);
bool8 HART_DayHandle(uchar *const Day);
uchar HART_FunctionAndUnitArrIndexGet(const HART_UnitDef* UnitOrFunctionPtr,uchar Code);
bool8 HART_CommandSendTableInfoGet(CommandDef CommandID);
bool8 HART_CommandReceiveTableInfoGet(CommandDef CommandID);


CommandDef HART_CommandGet(CommandDef Command,MenuTreeIndexDef MenuTreeIndex);
void HART_RespondCodeLoad(HART_ReceiveFlag FrameType);
void HART_PercentileRatio(uchar length,uchar *const Temp);
void HART_ReceiveSendEN(HART_RS_Flag Flag);
static AbnormalStatusDef HART_ErrCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value);
static AbnormalStatusDef HART_ErrCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value);
static AbnormalStatusDef HART_WarningCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value);
static AbnormalStatusDef HART_WarningCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value);
static void HART_CommunicatorBuffClear(uchar FrameBuffIndex);
static void HART_ReceiveFrameVerify(void );
static void HART_RespondFrameTimeoutVerify(void );
static void HART_RespondFrameReceiveCpltVerify(void );
/*
void HART_SendLeadCodeLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧前导码加载函数，
根据发送帧结构体变量中的前导码个数，将前导码加载到发送帧数组当中。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 

void HART_SendLeadCodeLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  uchar i;
  for(i = *FrameBuffIndex; i < G_SendFrameStructure.LeadCodeNumber;i++)
  {
    *(FrameBuff + i) = LEAD_CODE_VAL;
  }
  *FrameBuffIndex = i;
}
/*
//函数名称和参量和返回值类型。
void HART_SendDelimiterLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧定界符加载函数，
将发送帧结构体变量中的定界符元素加载到发送帧数组当中。
*
* 关键备注：
* - 


* 未来提高:



*/ 

void HART_SendDelimiterLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff + *FrameBuffIndex) = G_SendFrameStructure.Delimiter;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//函数名称和参量和返回值类型。
void HART_SendSlaveAddrLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧从设备地址加载函数，
将从设备的地址加载到发送帧数组中。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_SendSlaveAddrLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  uchar i;
  for(i = 0;i < G_SendFrameStructure.AddrByteNumber;i++)
  {
    *(FrameBuff +*FrameBuffIndex + i) = *(G_SendFrameStructure.AddrBuff+i);
  }
  *FrameBuffIndex = i+*FrameBuffIndex;
}
/*
//函数名称和参量和返回值类型。
void HART_SendCommandLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧命令加载函数，
将发送帧的命令号加载到发送帧数组当中。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_SendCommandLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff+*FrameBuffIndex) = G_SendFrameStructure.Command;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//函数名称和参量和返回值类型。
void HART_SendDataLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送数据加载函数，
将发送帧中的数据从发送帧结构体变量中加载到发送帧数组中。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_SendDataLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  uchar i;
  for(i = 0;i < G_SendFrameStructure.DataByteNumber;i++)
  {
    *(FrameBuff + i + *FrameBuffIndex) = G_SendFrameStructure.DataBuff[i];
  }
  *FrameBuffIndex = i+*FrameBuffIndex;
}
/*
//函数名称和参量和返回值类型。
void HART_SendDataByteNumberLoad(uchar *FrameBuff,uchar *FrameBuffIndex)
* 变量范围:
FrameBuff：发送帧数组首地址。
FrameBuffIndex：被校验数组序号。

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧数据字节个数加载函数，
将要发送数据的字节个数从发送帧结构体变量中提取出来，并保存到发送帧数组当中。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_SendDataByteNumberLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff + *FrameBuffIndex) = G_SendFrameStructure.DataByteNumber;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//函数名称和参量和返回值类型。
uchar HART_CRC(uchar *const FrameBuff,uchar FrameBuffLength,bool8 IsSendFrame)
* 变量范围:
FrameBuff：被校验数组首地址。
FrameBuffIndex：被校验数组序号。
* 返回值说明:void 
* 功能介绍:   
HART通信CRC校验函数。

*
* 关键备注：
* - 
接收帧和发送帧的CRC校验不一样，接收帧中没有前导码
而发送帧有前导码。
  
* 未来提高:



*/ 

uchar HART_CRC(uchar *const FrameBuff,uchar FrameBuffLength,bool8 IsSendFrame)
{
  uchar TempC = 0,i;
  uchar CheckCode = 0xFF;
  if(IsSendFrame == FALSE)
    TempC = 0;
  else if(IsSendFrame == TRUE)
    TempC = G_SendFrameStructure.LeadCodeNumber;
  for(i = TempC ;i < FrameBuffLength; i++)
  {
          CheckCode ^= FrameBuff[i];
  }
  CheckCode =  ~CheckCode;
  return CheckCode;
}

/*
//函数名称和参量和返回值类型。
void HART_SendFrameStructureInit(CommandDef Command,
                        const HART_SendStructDef *const HART_SendVersionStruct)
* 变量范围:
typedef struct
{
  uchar LeadCodeNumber;         //前导码字节个数
  uchar Delimiter;              //定界符
  uchar AddrByteNumber;         //地址字节个数
  uchar *AddrBuff;              //地址数组首地址指针
  uchar Command;                //命令
  uchar DataByteNumber;      //内容字节个数
  uchar *DataBuff;           //内容数组收地址
}HART_FrameDef;

* 返回值说明:void 
* 功能介绍:   
HART通信发送帧结构体变量初始化函数，
通过本函数，将对应的参数赋给对应的结构体提成员。
* 关键备注：
* - 如果发送的命令帧是写命令
* 未来提高:
*/ 

void HART_SendFrameStructureInit(CommandDef CommandID)
{
  uchar i,j,VariableIndexNumber,ByteNumber=0;
  MenuTreeIndexDef MenuTreeIndex;
  DataLengthDef DataLength;
  uint VariableIndex;
  ArrIndexDef Temp;
  uchar *ShowData;
  PageVariableTableDef PageVariableTable = {0,0};
  VariableGroupDef VariableGroupTable = {0};

  //获取菜单树序号
  MenuTreeIndex = MENU_GetMenuTreeIndex();  
  if(HART_CommandSendTableInfoGet(CommandID) ==  TRUE)
  {
    //加载前导码
    G_SendFrameStructure.LeadCodeNumber = G_NumRegPreams[0]; 
    G_SendFrameStructure.Delimiter = G_SendStructure.SendStructInfo.Delimiter;
    G_SendFrameStructure.AddrByteNumber = G_SendStructure.SendStructInfo.AddrByteNumber;
    //接收表真实命令ID，因为有些命令号兼容多个功能，因此以此变量来作为接收命令解析的索引
    G_HART_ReceiveTableRealCommandID = G_SendStructure.SendStructInfo.Command;
    G_SendFrameStructure.Command = HART_CommandGet(G_SendStructure.SendStructInfo.Command,MenuTreeIndex);
    G_SendFrameStructure.DataByteNumber = G_SendStructure.SendStructInfo.VariableByteNumber;
    VariableIndexNumber = G_SendStructure.SendStructInfo.VariableIndexNumber;
    G_SendFrameStructure.W_R_Flag = G_SendStructure.SendStructInfo.W_R_Flag;
    //加载写数据变量
    if(G_SendFrameStructure.W_R_Flag == WRITE)
    {
      Temp = G_SendStructure.SendStructInfo.VariableIndex;
      if(FlashReadLockStatusGet() == TRUE)
      {
        FlashReadLockHandle(FALSE);
        //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
        FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
        FlashReadLockHandle(TRUE);
      }
      else
      {
       //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
        FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
      }

      for(i = 0;i < VariableIndexNumber;i++)
      {
        VariableIndex = MENU_VariableIndexInfoGet(i,VariableGroupTable);
        //获取HART变量的数据长度
        DataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);
        //获取HART变量数组指针
        ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
        for(j = 0;j < DataLength;j++)
        {
          G_SendFrameStructure.DataBuff[ByteNumber+j] = *(ShowData+j);
        }
        ByteNumber += DataLength;
      }
    }
  }
  else
  {
    //非法命令
  }
}

/*
//函数名称和参量和返回值类型。
void HART_AddrConnect(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信地址连接函数。
地址连接指的是主设备通过00命令向对应地址的从设备获取基本信息，地址匹配后即建立连接。
*
* 关键备注：
* - 

  
* 未来提高:



*/

void HART_AddrConnect(void)
{
    G_SendFrameStructure.AddrBuff[0] = G_PollingAddress[0];
    HART_SingleAddrConnect();
}
/*
//函数名称和参量和返回值类型。
void HART_StartConnect(PollingTypeDef ConnetectWay,uchar StartAddr)
* 变量范围:
ConnetectWay:
//HART轮询链接方式定义
typedef enum 
{
  ALL_CONNECT,
  HALF_CONNECT,
  SINGLE_CONNECT
}HART_PollingConnectWayDef;

StartAddr：轮询链接的起始地址。

* 返回值说明:void 
* 功能介绍:
HART通信开始链接变量设置函数。
根据链接方式设置G_PollingConnectGroupIndex的起始值，
前三种均是从地址0开始轮询，而HALF_CONNECT_8是从地址8开始的。
*
* 关键备注：
* - 
G_PollingConnectGroupIndex
  
* 未来提高:



*/

void HART_StartConnect(PollingTypeDef ConnetectWay,uchar StartAddr)
{
  if( (ConnetectWay == ALL_CONNECT_31)||(ConnetectWay == ALL_CONNECT_63)||(ConnetectWay == ALL_CONNECT)||(ConnetectWay == INIT_CONNECT )||((ConnetectWay == HALF_CONNECT_0)))
  {
    if(G_PollingAddress[0] <= StartAddr)
    {
      G_PollingAddress[0] = StartAddr;
    }
  }
  else if((ConnetectWay == HALF_CONNECT_8))
  {
    if(G_PollingAddress[0] <= ADDR_8)
    {
      G_PollingAddress[0] = ADDR_8;
    }
  }
}
/*
//函数名称和参量和返回值类型。
void HART_SingleAddrConnect()
* 变量范围:

* 返回值说明:void 
* 功能介绍:   
HART单地址链接函数，
每次只针对一个地址进行连接

*
* 关键备注：
* - 
NOP(30);
此处延时是为了串口助手中发送命令与上一次接收帧分开，方便查看.

G_TimeStamp = 600;
设定计时参数，大概2s 
设置这个计时参数是为了确定

* 未来提高:



*/

void HART_SingleAddrConnect()
{  
  //开启发送模式
  HART_ReceiveSendEN(SEND_START);
  HART_FrameSend();
  HART_ReceiveSendEN(RECEIVE_START);
}
/*
//函数名称和参量和返回值类型。
void HART_ReceiveSendEN(HartRS_Flag Flag)
* 变量范围:
Flag
typedef enum
{
  SEND_START = 0,
  RECEIVE_START = 1
}HART_RS_Flag;
Flag = SEND_START：开始发送。
Flag = RECEIVE_START：开始接收。
* 返回值说明:void 
* 功能介绍:   
HART发送接收总线使能函数
负责控制总线的主动权归主机发送还是回应帧接收。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveSendEN(HART_RS_Flag Flag)
{
  //稍作延时，保证发送帧完整 
  //NOP(50);
  RECEIVE_SEND_EN = Flag;
  G_HART_ReceiveEN = Flag;
  //稍作延时，保证发送帧完整 
  NOP(50);
}

/*
//函数名称和参量和返回值类型。
void HART_FrameStringSend(uchar *const FrameBuff,uchar FrameBuffLength)
* 变量范围:
FrameBuff[]:装在HART命令帧的数组。
FrameBuffLength:发送帧数组的字符个数。
* 返回值说明:void 
* 功能介绍:   
HART帧字符串发送函数，将要发送出去的命令帧字符串发送到HART总线上。

*
* 关键备注：
* -
HART_ReceiveSendEN(SEND_START);是总线控制函数，
而G_HART_ReceiveEN = SEND_START; 
是程序运行标志，负责区分接收帧及发送命令处理的标志性变量。
  
* 未来提高:



*/ 



void HART_FrameStringSend(uchar *const FrameBuff,uchar FrameBuffLength)
{
  uchar i;
  for(i = 0; i < FrameBuffLength;i++)
  {
    UsartFrameCharSend(*(FrameBuff+i));
  }
}
static void HART_CommunicatorBuffClear(uchar FrameBuffIndex)
{
  uchar i = 0;
  for(i = 0;i < FrameBuffIndex;i++)
  {
    G_FrameReceiveBuff[i] = 0;
  }
}
/*
//函数名称和参量和返回值类型。
void HART_FrameSend(void)
* 变量范围:
FrameBuff[]:装在HART命令帧的数组。
FrameBuffIndex:发送帧数组的序号。

* 返回值说明:void 
* 功能介绍:   
HART帧发送函数，本函数包含了命令帧发送的全部过程，包括帧打包以及帧发送。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_FrameSend(void)
{
  uchar FrameBuff[HART_FRAME_BUFF_SIZE] = {0};
  uchar FrameBuffIndex = 0;
  HART_SendLeadCodeLoad(FrameBuff,&FrameBuffIndex); 
  HART_SendDelimiterLoad(FrameBuff,&FrameBuffIndex);
  HART_SendSlaveAddrLoad(FrameBuff,&FrameBuffIndex);
  HART_SendCommandLoad(FrameBuff,&FrameBuffIndex);
  HART_SendDataByteNumberLoad(FrameBuff,&FrameBuffIndex);
  if(G_SendFrameStructure.DataByteNumber != 0x00)
  {
    HART_SendDataLoad(FrameBuff,&FrameBuffIndex);
  }
  FrameBuff[FrameBuffIndex] = HART_CRC(FrameBuff,FrameBuffIndex,TRUE);
  FrameBuffIndex++;
  HART_FrameStringSend(FrameBuff,FrameBuffIndex);
  
  HART_CommunicatorBuffClear(HART_FRAME_BUFF_SIZE);
}
/*
void HART_ReceiveCheckoutLoad(uchar ReceiveIndex )
* 变量范围:
G_FrameReceiveBuff[]:接收帧保存数组。
ReceiveIndex：接收帧保存数组序号。
G_ReceiveFrameStructure：接收帧结构体变量。

* 返回值说明:void 
* 功能介绍:   
HART接收帧校验码加载函数，负责将接收帧中的校验码部分提取出来，并转存到接收帧
结构体变量中

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveCheckoutLoad(uchar ReceiveIndex )
{
  G_ReceiveFrameStructure.Checkout = G_FrameReceiveBuff[ReceiveIndex];
}

/*
void HART_ReceiveCommandLoad(uchar *const ReceiveIndex)
* 变量范围:
G_FrameReceiveBuff[]:接收帧保存数组。
ReceiveIndex：接收帧保存数组序号。
G_ReceiveFrameStructure：接收帧结构体变量。

* 返回值说明:void 
* 功能介绍:   
接收帧命令号加载函数
每一个正确的接收帧中都会包含他回应命令的命令号，本函数负责将这个命令号
保存到接收帧结构体变量中。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveCommandLoad(uchar *const ReceiveIndex )
{
  G_ReceiveFrameStructure.Command = (CommandDef)G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
void HART_LoadExpandedDeviceType()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
扩展设备类型获取函数，
因为很多操作都需要根据设备产生以及设备型号来做区分处理，
因此在通信帧接收完成，马上获取厂商以及型号，但是需要注意条件，
只有短帧，00命令，定界符为02，并且符合手操器兼容的HART版本才会执行本函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
void HART_LoadExpandedDeviceType()
{
  //需要在第一时间获取制造商以及设备型号
  if((G_SendFrameStructure.Command == IDENTIFY)
            &&(G_SendFrameStructure.Delimiter == 0x02)
              &&(G_HART_ReceiveFrameType == SHORT_FRAME))
  {
    G_ManufacturerID[0] = G_FrameReceiveBuff[7];
    G_DeviceType[0] = G_FrameReceiveBuff[8];
  }
}
/*
void HART_ReceiveAddrBuffLoad()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART接收帧地址数组加载函数
负责将接收帧中的地址提取出来并保存到接收帧结构体变量当中。

*
* 关键备注：
* - 
本函数分别对长帧型和短帧型的地址进行提取保存

除了加载地址信息，同时也将生产商ID以及产品类型提取出来，方便菜单树索引
  
* 未来提高:


*/ 

void HART_ReceiveAddrBuffLoad()
{
  uchar i = 0;
#ifndef SAVE_MAMORY
  //锐达仪表短帧定制
  if(HART_GetProductTypeAndID() == RADAR_TYPE1)
  {
    G_SendFrameStructure.AddrBuff[0] = 0x80+G_PollingAddress[0];
  }
  else
#endif
  {
    G_SendFrameStructure.AddrBuff[i++] = G_FrameReceiveBuff[7]&0x3f;
    G_SendFrameStructure.AddrBuff[i++] = G_FrameReceiveBuff[8];
    G_SendFrameStructure.AddrBuff[i++] = G_FrameReceiveBuff[15];
    G_SendFrameStructure.AddrBuff[i++] = G_FrameReceiveBuff[16];
    G_SendFrameStructure.AddrBuff[i++] = G_FrameReceiveBuff[17]; 

  }
}
/*
void HART_ReceiveDataBuffLoad(uchar *ReceiveIndex )
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART接收帧数据加载函数
将接收帧中的数据部分保存到接收帧结构体变量当中。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveDataBuffLoad(uchar *const ReceiveIndex)
{
  uchar i;
  for(i = 0; i < G_ReceiveFrameStructure.DataByteNumber;i++)
  {
    G_ReceiveFrameStructure.DataBuff[i] = G_FrameReceiveBuff[*ReceiveIndex + i];    
  }
  *ReceiveIndex = *ReceiveIndex + i;
}
/*
void HART_ReceiveDataByteNumberLoad(uchar *const ReceiveIndex )
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART接收帧数据字节个数加载函数
将接收帧中数据的字节个数保存的接收帧结构体变量中

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveDataByteNumberLoad(uchar *const ReceiveIndex)
{
  G_ReceiveFrameStructure.DataByteNumber = G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
void HART_ReceiveDelimiterLoad(uchar *const ReceiveIndex)
* 变量范围:
uchar *const ReceiveIndex：接收帧序号

* 返回值说明:void 
* 功能介绍:   
HART接收定界符加载函数
将接收帧中的定界符保存到接收帧结构体变量中。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveDelimiterLoad(uchar *const ReceiveIndex)
{
  G_ReceiveFrameStructure.Delimiter = G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
uchar HART_VersionGet()
* 变量范围:

* 返回值说明:HART协议版本 
* 功能介绍:   
HART版本分析函数，
使用的是哪一个版本的HART协议。

*
* 关键备注：
* - 

  
* 未来提高:
加入其他版本后，会更新分支语句


*/ 
uchar HART_VersionGet()
{
  return G_UniversalRev[0];
}
/*
void HART_WriteProtectHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
变送器写保护判断函数
通过接收帧分析，返回的数据是否为写保护反馈码。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
AbnormalStatusDef HART_AbnormalStatusHandle()
{
  AbnormalStatusDef Value = ABNORMAL_STANDBY;
  uchar DataByteNumber = G_ReceiveFrameStructure.DataByteNumber;
  uchar RecondCode = G_RecondCode[0];
  CommandDef ExecutingCommand = G_SendFrameStructure.Command;
  //错误响应码处理

  if(DataByteNumber == 0x02)
  {
    Value = HART_ErrCodeWithSingleDefinitions(RecondCode,Value);
    Value = HART_ErrCodeWithMultipleDefinitions(RecondCode,ExecutingCommand,Value);
  }
  //警告响应码处理
  Value = HART_WarningCodeWithSingleDefinitions(RecondCode,Value);
  Value = HART_WarningCodeWithMultipleDefinitions(RecondCode,ExecutingCommand,Value);
  return Value;
}
/*
void HART_AbnormalPageHandle(AbnormalStatusDef AbnormalStatus)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
异常页面处理函数
通信或系统发生异常时，需要切换到警告或通知页面

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_AbnormalPageHandle(AbnormalStatusDef AbnormalStatus)
{    
  if(AbnormalStatus == WRITE_PROTECT)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_115);
    MENU_PageShowSwitch(TRUE);
  }
  if(AbnormalStatus == POSSIBLE_VALUE)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_116);
    MENU_PageShowSwitch(TRUE);
  }
  if(AbnormalStatus == COMMUNICATION_ERR)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_105);
    MENU_PageShowSwitch(TRUE);
  }
  else if(AbnormalStatus == VALUE_SMALL)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_117);
    MENU_PageShowSwitch(TRUE);
  }
  else if(AbnormalStatus == VALUE_LARGE)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_118);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == SPAN_SMALL)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_119);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == UPPER_HIGH)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_120);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == UPPER_LOW)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_121);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == ABORTING_STATUS)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_104);
    MENU_PageShowSwitch(TRUE);    
  }
  else if(AbnormalStatus == NOT_IMPLEMENTED)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_103);
    MENU_PageShowSwitch(TRUE);    
  }
  else if(AbnormalStatus == LOWER_HIGH)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_122);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == LOWER_LOW)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_123);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == INVALID_SELECTION)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_124);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == EXC_CORRECTION)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_125);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == INVALID_FUNCTION)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_126);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == INVALID_TRIM_TYPE)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_127);
    MENU_PageShowSwitch(TRUE);  
  }//待定异常处理   
  else if(AbnormalStatus == MULTIDROP_MODE)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_111);
    MENU_PageShowSwitch(TRUE);  
  } 
  else if(AbnormalStatus == PROCESS_HIGH)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_112);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == PROCESS_LOW)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_112);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == NEW_LRV_PUSHED)
  {
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_129);
    MENU_PageShowSwitch(TRUE);  
  }
  else if(AbnormalStatus == OTHER_ANOMALY)
  {
  
  }//目前未知异常不做处理，所以不加警告界面切换，后续需要进行完善。
  else
  {
  
  }
  //显示当前警告页面
  G_RxFrameVerifyFlag = RESPOND_CODE_EXPRESSION;
  //需要设置警告界面切换参数，设置页面显示时间
  G_WarningPageRefreshFlag = WARNING_START;
  FlashReadLockHandle(FALSE);
  MENU_TimingIntervalSelect();
  FlashReadLockHandle(TRUE); 
}
/*
RecHandleDef HART_ReceiveFrameHandle(void)
* 变量范围:
typedef enum 
{
SHORT_FRAME_ERR,
LONG_FRAME_ERR,
VALID_FRAME,
RESPOND_CODE_ERR,
CRC_ERR,
}RecHandleDef;

* 返回值说明:void 
* 功能介绍:   
HART接收帧处理函数，将接到的数据帧进行校验码核对，通过审核后进行接收帧拆分，并对号加载
到接收帧结构体中。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 

RecHandleDef HART_ReceiveFrameHandle()
{ 
  uchar ReceiveIndex = 2,CRC_LocalCalculate,FrameReceiveBuffIndex;
  //将接收到的字节个数加载到临时变量中，并且将全局计数变量清零
  FrameReceiveBuffIndex = FrameLength;
  G_FrameReceiveBuffIndex = 0;
  CRC_LocalCalculate = HART_CRC(G_FrameReceiveBuff,FrameReceiveBuffIndex,FALSE);
  HART_ReceiveCheckoutLoad(FrameReceiveBuffIndex);
  //校验码匹配
  if(CRC_LocalCalculate == G_ReceiveFrameStructure.Checkout)
  {
    if(G_HART_ReceiveFrameType == SHORT_FRAME)
    {
      if(G_SendFrameStructure.Delimiter == 0x02)
      {
        HART_RespondCodeLoad(SHORT_FRAME);
        HART_ReceiveAddrBuffLoad();  
      }
      else
      {
        /* Report short frame event end */
        return SHORT_FRAME_ERR;
      }
    }
    else
    {
      if(G_SendFrameStructure.Delimiter == 0x82)
      {
        ReceiveIndex = 6;
        HART_RespondCodeLoad(LONG_FRAME);
      }
      else
      {
        /* Report long frame event end */
        return LONG_FRAME_ERR;
      }
    } 
    HART_ReceiveCommandLoad(&ReceiveIndex);
    if(G_ReceiveFrameStructure.Command == G_SendFrameStructure.Command)
    {
      HART_ReceiveDataByteNumberLoad(&ReceiveIndex);
      //如果接受的字节个数大于两个，说明是正常接收帧，否则是异常状态或单纯的状态反馈。
      if(G_ReceiveFrameStructure.DataByteNumber > 0x02)
      { 
        HART_ReceiveDataBuffLoad(&ReceiveIndex);
        G_RxFrameVerifyFlag = REC_STANDBY;
        return VALID_FRAME;
      }
      else//响应码异常
      {
        return RESPOND_CODE_ERR;        
      }
    }
    else
    {
      return RESPOND_CODE_ERR;   
    }
  }
  else
  {
    //校验错误返回校验错误码
    FrameLength = MAX_FRAME_LENGTH;
    /* Report CRC event end */
    return CRC_ERR;
  }
}


/*
void HART_InfoBuffPtrInit()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信信息数组指针初始化函数，将收发帧结构体的地址及数据加载数组绑定到结构体
变量上。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_InfoBuffPtrInit()
{
  G_ReceiveFrameStructure.DataBuff = G_SendReceiveDataBuff;
  G_SendFrameStructure.DataBuff = G_SendReceiveDataBuff;
}


/*
void HART_ReceiveFrameAnalysis(const HART_ReceiveStructDef *const HART_ReceiveStruct)
* 变量范围:
const HART_ReceiveStructDef *const HART_ReceiveStruct：
HART接收帧结构体。
* 返回值说明:void 
* 功能介绍:   
HART接收帧解析函数，
将接收到的HART接收帧拆分到对应的变量上。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_ReceiveFrameAnalysis()
{
  CommandDef CommandID = IDENTIFY;
  uchar DataByteNumber = 2;
  uint VariableIndexNumber = 0,i = 0,VariableIndex = 0;
  ArrIndexDef Temp;
  CommandID = G_HART_ReceiveTableRealCommandID; 
  PageVariableTableDef PageVariableTable = {0,0};
  VariableGroupDef VariableGroupTable = {0};

  //根据命令ID--CommandID找到对应命令接收表的索引序号CommandIndex
  if(HART_CommandReceiveTableInfoGet(CommandID) ==  TRUE)
  {
   Temp = G_ReceiveStructure.ReceiveStructInfo.VariableIndex;
   if(FlashReadLockStatusGet() == TRUE)
   {
     FlashReadLockHandle(FALSE);
     //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
     FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
     FlashReadLockHandle(TRUE);
   }
   else
   {
      FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
   }
   
   VariableIndexNumber = MENU_PageVariableNumber(PageVariableTable);
    for(i = 0;i < VariableIndexNumber;i++)
    {
      VariableIndex = MENU_VariableIndexInfoGet(i,VariableGroupTable);
      //结构表中对应HART变量赋值
      DataByteNumber += HART_ReceiveStructVariableAssign(VariableIndex,DataByteNumber);
    }
  }
}
/*
void HART_ReceiveSuccessHandle()
* 变量范围:
HART_CommandSendTimes:HART通信命令失败后重发的次数，用来保证通信成功率。

HART_CommandIndex：HART通信的命令序号，
可根据该序号确定当前发送的命令在命令执行数组的哪一位。

* 返回值说明:void 
* 功能介绍:   
HART通信接收成功处理函数，
成功发送请求报文后，从机会回复主机一条相应报文，主机确定完全接收之后
进入接收成功处理函数进行命令解析。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 


void HART_ReceiveSuccessHandle()
{
    RecHandleDef Result;
    HART_ResendFlagReset();

    //建立连接地址匹配
    if(HART_AddrCompare() == TRUE)
    {
        //接收帧处理 
        Result = HART_ReceiveFrameHandle();
        if((Result == VALID_FRAME)||(Result == RESPOND_CODE_ERR))
        {
          HART_AbnormalStatusHandleModule();
        }
        //如果接收帧异常
        if((Result == SHORT_FRAME_ERR)
                ||(Result == LONG_FRAME_ERR)
                  ||(Result == CRC_ERR))
        {
          //成功率失败次数统计
          SystemSucRateResultStatistis(FALSE);
          G_RxFrameVerifyFlag = REC_INCORRECT;
        }
        else
        {
          if(G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber == 0)
          {
            G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = 1;
          }
          //如果命令执行数组序号变量值已经达到了命令执行数组的装载量时。
          if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex
             >= G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber-1)
          {
            G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
            G_CurrentPageCommandExecuteStructure.ResendCounter = 0;
            if(G_HART_HandleFlag == HART_START_INIT)
            {
              G_HART_HandleFlag = HART_INIT_COMPLETE;
              //硬件版本号为该字节高5位，这里后续最好添加一个处理函数，用来处理生产商信息
              G_HardwareRev[0] >>= 3;
            }
            else if(G_HART_HandleFlag == HART_START_COMMON)
            {
               G_HART_HandleFlag = HART_COMMON_COMPLETE;
            }
            //当一个命令组完成，需要对特定的编辑界面进行变量更新
            G_ParamLoadLock = FALSE;
            //此时要关闭HART通信通道，以免出现误发数据
            RECEIVE_SEND_EN = RECEIVE_START;
            /*命令组中的所有命令执行完毕后，
              SINGLE_C类型页面需要二次刷新，更新读数*/
            if((MENU_CurrentPageTypeGet() == EDIT_PAGE)
               ||(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE))
            {
              MENU_PageShowSwitch(TRUE);
              //由于变量读取完毕之后需要在页面更新显示内容，因此除了清屏以外，还需解开flash锁
              MENU_ClearLcdScreen();
              FlashReadLockHandle(FALSE);
              //参数选择页面涉及到光标追踪问题，因此需要开启单次执行锁，可以在第二次刷新页面时索引选项
              if(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE)
              {
                G_SingleExcutionLock = FALSE;
              }
            }
            if(MENU_CurrentPageTypeGet() == WAITING_PAGE)
            {
              G_WarningPageRefreshFlag = ADDITION_STANDBY;
              WarningPageHandle();
            }
          }
          else
          {
            if(G_HART_HandleFlag == HART_START_INIT)
            {
              G_HART_HandleFlag = HART_INIT_COMPLETE;
            }
            else
            {
              G_HART_HandleFlag = HART_COMMON_COMMAND_HANDLE;
              //防止执行数组索引变量超过命令总个数
              if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex
                 >= G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber)
              {
                G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 
                  G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber-1;
              }
              else if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex
                 < G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber)
              {
                G_CurrentPageCommandExecuteStructure.CurrentCommandIndex++;
              }
            }
          }
          //如果不存在报文接收失真或响应码异常现象，将接收标志设置成空闲
          if((G_RxFrameVerifyFlag != REC_INCORRECT)
             &&(G_RxFrameVerifyFlag != RESPOND_CODE_EXPRESSION))
          {
              //通信成功匹配一次
              SystemSucRateResultStatistis(TRUE);
              G_RxFrameVerifyFlag = REC_STANDBY;
          }
      }
    }
    else//地址不匹配
    {
      /* Report invalid frame event end */
      G_FrameReceiveBuffIndex = 0;
      G_RxFrameVerifyFlag = REC_INCORRECT;
    }
}

/*
void HART_IntToString(unsigned long int  Data,uchar *const DeviceStr)
* 变量范围:
DeviceStr：保存ASCII码的字符串数组。
Data:长整型数据。
* 返回值说明:void 
* 功能介绍:   
将长整型数据转换成ASCII码字符串。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
uchar HART_IntToString(unsigned long int  Data,uchar *const DeviceStr)
{
  unsigned long int TempData = 0;
  char i=0;
  uchar TempArr[INFO_BUFF_SIZE] = {0},DataLength = 0;
  TempData = Data;
  while(TempData)
  {
    TempData = TempData/10;
    i++;
  }
  DataLength = i;
  TempData = Data;
  
  for( i = DataLength-1 ;i > 0;i--)
  {
    TempArr[i] = TempData%10+0x30;
    TempData = TempData/10;
  }
  TempArr[i] = TempData%10+0x30;
  for(i = 0;i < INFO_BUFF_SIZE;i++)
  {
    DeviceStr[i] = TempArr[i];
  }
  return DataLength;
}

/*
void HART_CharToString(uchar  Data,uchar *const DeviceStr)
* 变量范围:
DeviceStr：保存ASCII码的字符指针。
Data:字符型数据。
* 返回值说明:void 
* 功能介绍:   
将字符型数据转换成ASCII码字符串。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_CharToString(uchar  Data,uchar *const DeviceStr)
{
  uchar i = 0,j = 0,flag = 0;
  uchar Scale = 100;

  
  for( i = 0;i < 3; i++)
  { 
    //信息界面数字显示需要左对齐
    if(MENU_CurrentPageTypeGet() == INFO_PAGE)
    {
      if(Data/Scale != 0)
      {
        *(DeviceStr + j) = Data/Scale+0x30;
        j++;
      }
    }
    else if(MENU_CurrentPageTypeGet() == DYNAMIC_PAGE)
    {
      *(DeviceStr + i) = Data/Scale+0x30;
      //Revision 0显示为空格处理
      if((*(DeviceStr + i) == 0x30)&&(flag == 0))
      {
        *(DeviceStr + i) = 0x20;
      }
      else
      {
        flag = 1;
      }
    }
    else
    {
      *(DeviceStr + i) = Data/Scale+0x30;
    }
    Data %= Scale;
    Scale /= 10;
  }
}

/*
PageCommandNumDef HART_CommandSend()
* 变量范围:
HART_CommandIndex：HART通信的命令序号，
可根据该序号确定当前发送的命令在命令执行数组的哪一位。

* 返回值说明:void 
* 功能介绍:   
HART命令发送函数，
根据命令序号在命令执行数组中找到对应执行的序号。

*
* 关键备注：
* - 

  
* 未来提高:

如果页面没有挂载命令，需要通过命令个数来屏蔽掉命令发送。

命令发送函数需要加入返回值，以此来区分页面的命令挂载情况，是有指令还是没指令，是
一个指令还是多个指令等情况

如果建立连接之后，需要发送IDENTIFY命令，可以在发送命令结构表中添加一条新的命令结构
，标识要区别于IDENTIFY。
*/ 
PageCommandNumDef HART_CommandSend()
{
  PageCommandNumDef CommandNum = NO_COMMAND;
  CommandDef CommandID;
  CommandID = 
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[G_CurrentPageCommandExecuteStructure.CurrentCommandIndex];

  //页面挂载变量个数大于0
  if(G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber > 0)
  {
    CommandNum = MORE_COMMAND;
    if((MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE)&&
       			(MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_101))
    {
      //测成功率界面处理
      CommandNum = TEST_COMMAND;
    }
    //成功率运算发送统计
    SystemSendStatistics();
    //建立连接发送的命令
    if(CommandID == IDENTIFY)
    {
      HART_SendFrameStructureInit(CommandID);
      HART_StartConnect(G_ConnectWay,0);
      HART_AddrConnect();
    }
    else
    {
      HART_SendFrameStructureInit(CommandID);
      HART_SingleAddrConnect(); 
    }          
  }
  //只要存在命令发送，就不可以定时关机
  G_PowerOffCounter = 0;
  return CommandNum;
}


/*
void HART_BusStart(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART总线启动函数，在开始HART通信前需要对总线进行拉低一段时间后拉高的操作。

*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_BusStart()
{  
  HART_BUS_START = 0;
  NOP(5);
  HART_BUS_START = 1;
}
/*
void HART_InfoInit(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信信息初始设定函数，
HART总线设置以及一些初始状态设定。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
void HART_InfoInit(void)
{
  HART_BusStart();
  //Set Polling mode
  G_ConnectWay = INIT_CONNECT;
  HART_InfoBuffPtrInit();
  //开启发送模式
  RECEIVE_SEND_EN = RECEIVE_START;
}
/*
void HART_CommandExecuteArrLoad(CommandDef Command,uchar *const CommandIndexCount);
* 变量范围:
Command：HART命令号。
CommandIndexCount：命令个数记录变量，负责记录执行数组的有效命令个数。
* 返回值说明:void 
* 功能介绍:   
HART通信命令执行数组加载函数，
在命令执行数组中加入当前页面需要发送的命令号，同时确定当前页面发送的命令个数。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_CommandExecuteArrLoad(CommandDef Command,uchar *const CommandIndexCount)
{
  uint i = 0,Count = 0;
  //若命令索引统计个数为零，说明是对第一个命令进行加载操作。
  Count = *CommandIndexCount;
  if(Count == 0)
  {
    Count++;
    //将第一个命令加载到当前页面命令执行结构体的命令数组中
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[0] = Command;
  }
  else//将重复的命令号覆盖掉
  {
    for( i = 0;i < Count; i++)
    {
       if( Command == G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[i] )
       {
          break;
       }
    }
    if(i == Count)
    {
      G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[i] = Command;
      Count++;
    }
  }
  *CommandIndexCount = Count;
}
/*
void HART_ResendFlagReset();
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART重发状态机重置函数，
本函数主要作用是将HART的定时变量，以及重发状态机变量恢复到初始状态。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_ResendFlagReset()
{
    G_FrameGap = 0;
}


/*
void HART_SingleConnectHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART单次链接处理函数，功能是将轮询链接地址序号进行自加，然后开启页面变换标志变量，
对页面进行更新。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_SingleConnectHandle()
{
   G_PollingAddress[0]++;
   MENU_PageShowSwitch(TRUE);
}
/*
void HART_SingleConnectFailHandle()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信单次地址链接失败处理函数。
如果单次地址链接失败，清零轮询链接数组索引，同时将调用轮询页面处理函数，返回
前一个页面。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_SingleConnectFailHandle()
{
   G_PollingAddress[0] = 0;
   G_HART_HandleFlag = HART_POLL_ERR;
   PollingPageHandle();
   MENU_PageShowSwitch(TRUE);
}
/*
void HART_TopAddrPollingHandle(uchar TopAddr)
* 变量范围:
uchar TopAddr：轮询地址上限。

* 返回值说明:void 
* 功能介绍:   
轮询上限地址处理函数。
如果轮询链接数组索引变量值超过了参数TopAddr，需要调用
担此链接失败处理函数，返回轮询页面的前一级页面。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_TopAddrPollingHandle(uchar TopAddr)
{
   if(G_PollingAddress[0] > TopAddr)
   {
      HART_SingleConnectFailHandle();
   }
   else
   {       
     HART_SingleConnectHandle();
   } 
   G_ConnectWay = POLLING_STANDBY;
}
/*
void HART_ReceiveErrHandle()
* 变量范围:
HART_CommandSendTimes:HART通信命令失败后重发的次数，用来保证通信成功率。

HART_CommandIndex：HART通信的命令序号，
可根据该序号确定当前发送的命令在命令执行数组的哪一位。

* 返回值说明:void 
* 功能介绍:   
  HART通信接收帧错误处理函数，
  负责防止校验错误或通信过程中漏发丢发造成的通信错误，将失败的命令重新发送最多两次。
  如果两次均为接收到正确回应，即判断本次通信失败。
*
* 关键备注：
* - 

  
* 未来提高:




*/


void HART_ReceiveErrHandle()
{     
  //重发次数大于规定值，需要提交错误，并做错误界面切换准备
    if(G_CurrentPageCommandExecuteStructure.ResendCounter >= RESEND_TIMES)
    {
       if((G_ConnectWay == ALL_CONNECT)||(G_ConnectWay == HALF_CONNECT_8))
       {      
          HART_TopAddrPollingHandle(ADDR_14);
       }
       else if(G_ConnectWay == ALL_CONNECT_31)
       {
          HART_TopAddrPollingHandle(ADDR_31);
       }
       else if(G_ConnectWay == ALL_CONNECT_63)
       {
          HART_TopAddrPollingHandle(ADDR_63);
       }
       else if(G_ConnectWay == HALF_CONNECT_0)
       {
          HART_TopAddrPollingHandle(ADDR_6);
       }
       else if(G_ConnectWay == SINGLE_CONNECT)
       {
         HART_SingleConnectFailHandle();
       }
       else if(G_ConnectWay == INIT_CONNECT)
       {
         //初始连接失败状态机  
         G_HART_HandleFlag = HART_INIT_ERR;
         MENU_CursorNumReset();
         MENU_VeriableReset();
       }
       else if((G_ConnectWay == COMMON_PAGE_CONNECT)||(G_ConnectWay == WAITING_CONNECT)
               ||(G_ConnectWay == REFRESH))
       {
         G_HART_HandleFlag = HART_COMMON_ERR;
       }
       //轮询超过3次仍未链接到设备，需要重置链接次数和命令索引序号
       HART_CommandSendIndexReset();
       G_RxFrameVerifyFlag =  REC_ERR;
    }
    else
    { 
      if(G_HART_HandleFlag == HART_START_INIT)
      {
            G_HART_HandleFlag = HART_INIT_COMMAND_HANDLE;
      }
      else if(G_HART_HandleFlag == HART_START_COMMON)
      {
            G_HART_HandleFlag = HART_COMMON_COMMAND_HANDLE;
      }
      G_CurrentPageCommandExecuteStructure.ResendCounter++;
      G_RxFrameVerifyFlag =  REC_STANDBY;
    }       
    
}

/*
void HART_CommandInitHandle();
* 变量范围:
HART_CommandIndex：HART通信的命令序号，

* 返回值说明:void 
* 功能介绍:   
HART命令初始化处理函数，
该函数作用是，当显示页面上挂载的HART变量已经整理完毕，并且生成了HART命令执行数组，
通过本函数来发送执行数组的初始命令组。
*
* 关键备注：
* - 
特别强调一下，初始命令组一般是在初始链接界面以及Polling界面才会使用到。
  
* 未来提高:

命令发送函数需要加入返回值，以此来区分页面的命令挂载情况，是有指令还是没指令，是
一个指令还是多个指令等情况



*/ 


void HART_CommandInitHandle()
{
  PageCommandNumDef CommandNum = NO_COMMAND;

  if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex <
   G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber)
  {
    CommandNum = HART_CommandSend(); 
  }
  //是指不只发送一个命令的页面。
  if(CommandNum == MORE_COMMAND)
  {
    if(G_HART_HandleFlag == HART_INIT_COMMAND_HANDLE)
    {
      G_HART_HandleFlag = HART_START_INIT;
    }
    else if(G_HART_HandleFlag == HART_COMMON_COMMAND_HANDLE)
    {
      G_HART_HandleFlag = HART_START_COMMON;
    }
    G_FrameGap = RECEIVE_TIME_INTERVAL;
  }
  else if(CommandNum == TEST_COMMAND)
  {
    //启动成功率连接
    G_HART_HandleFlag = HART_START_INIT;
    G_FrameGap = RECEIVE_TIME_INTERVAL;
  }
  else
    G_HART_HandleFlag = HART_STANDBY;      
}
/*
void HART_InitCompleteHandle(void );
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信初始化成功处理函数，
该函数的作用是在主设备与从设备完成通信连接后，
从初始化界面转换到主菜单页面的处理过程。

*
* 关键备注：
* - 

  
* 未来提高:




*/

void HART_InitCompleteHandle(void )
{
  if(G_HART_HandleFlag == HART_INIT_COMPLETE)
  {
    InitialpageHandle();
  }
  if(MENU_CurrentPageTypeGet() == WAITING_PAGE)
  {
    WaitingErrPageHandle(TRUE);
  }    
  G_HART_HandleFlag = HART_STANDBY;
  G_ConnectWay = CONNECTED;
}
/*
void HART_InitErrHandle(void );
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
HART通信初始化错误处理函数，
该函数的作用是在主设备与从设备未完成通信连接的情况下，
从初始化界面转换到错误提示页面的处理过程。

*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_InitErrHandle()
{
  InitialpageHandle();
  MENU_PageShowSwitch(TRUE);
  //G_HART_ResendFlag = HART_STANDBY;
}
/*
static void HART_ReceiveFrameVerify(void );
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  HART接收从机响应报文核实函数，
  接收报文时可能出现三种情况：接收成功，接收不成功但可以补发，三次补发均不成功。
  系统需要根据这三种情况分别处理。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void HART_ReceiveFrameVerify(void )
{
  if(G_RxFrameVerifyFlag == REC_INCORRECT)
  {
    //接收帧不正确的理解是单次通信出现异常，并没有完成三次补发操作
    HART_ReceiveErrHandle();
  }
  if(G_RxFrameVerifyFlag == REC_STANDBY)
  {
    //初始化HART发送命令
    if((G_HART_HandleFlag == HART_INIT_COMMAND_HANDLE)||(G_HART_HandleFlag == HART_COMMON_COMMAND_HANDLE))
    {
      //命令组命令发送
      HART_CommandInitHandle();
    }
    if((G_HART_HandleFlag == HART_INIT_COMPLETE)||(G_HART_HandleFlag == HART_COMMON_COMPLETE))
    {  
      //命令组命令发送完成
      HART_InitCompleteHandle();      
      HART_CommandSendIndexReset();
    }
  }
  if(G_RxFrameVerifyFlag == REC_ERR)
  {
    //通过三次补发仍然未能建立连接
    if(G_HART_HandleFlag == HART_INIT_ERR)
    {
      HART_InitErrHandle();
      HART_CommandSendIndexReset();
    }
    else if(G_HART_HandleFlag == HART_COMMON_ERR)
    {
       //有些菜单界面需要单次发送读取命令，利用本段代码屏蔽掉菜单界面多次刷新命令发送
       if(MENU_CurrentPageTypeGet() == MENU_BAR)
       {
       
       }
       else if(G_ConnectWay == REFRESH)
       {
          WaitingErrPageHandle(FALSE);  
       }
       else
       {
          /* 跳转到通信错误提示界面*/
          HART_AbnormalPageHandle(COMMUNICATION_ERR); 
       }
    }
    G_RxFrameVerifyFlag =  REC_STANDBY;
    //此时要关闭HART通信发送通道，以免出现误发数据
    RECEIVE_SEND_EN = RECEIVE_START;
  }
  if(G_RxFrameVerifyFlag == RESPOND_CODE_EXPRESSION)
  {
    MENU_PageShow();
    G_RxFrameVerifyFlag = REC_STANDBY;
  }
}
/*
static void HART_RespondFrameTimeoutVerify(void );
* 变量范围:

* 返回值说明:void 
* 功能介绍:   
  HART响应帧接收超时判断函数，规定时间内没有收到从机响应报文，会记一次通信错误。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void HART_RespondFrameTimeoutVerify(void )
{
  if((G_FrameGap == 0)&&
       ((G_HART_HandleFlag == HART_START_INIT)
        ||(G_HART_HandleFlag == HART_START_COMMON)))
  {
    /* Report receive incorrect event end */
    //成功率失败次数统计
    SystemSucRateResultStatistis(FALSE);
    //超时引起的通信错误
    G_RxFrameVerifyFlag = REC_INCORRECT;
  }
}
/*
static void HART_RespondFrameReceiveCpltVerify(void );
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
  从机响应报文接收完成判断函数，
  通过串口中断接收从机发来的报文，当字节与字节之间的时间间隔大于50（HART协议规定10ms）毫秒时，
  判断当前报文接收完成。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void HART_RespondFrameReceiveCpltVerify(void )
{
  //帧接收结束处理
  if((G_BytesGap == 0)&&(FrameHandle == INFO_CODE))
  {
    HART_ReceiveStateReset();
    //加载厂商及设备型号
    HART_LoadExpandedDeviceType();
    HART_ReceiveSuccessHandle();
  }
}
/*
void HART_CommunicateHandle(uchar *const HART_CommandSendTimes,uchar *const HART_CommandIndex)
* 变量范围:
HART_CommandSendTimes:HART通信命令失败后重发的次数，用来保证通信成功率。

HART_CommandIndex：HART通信的命令序号，
可根据该序号确定当前发送的命令在命令执行数组的哪一位。

* 返回值说明:void 
* 功能介绍:   
HART通信处理函数，
本函数基本包含了HART通信模块的所有处理过程，是HART通信函数的主干，
一般会在主函数中调用。

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_CommunicateHandle()
{
  HART_ReceiveFrameVerify();
  HART_RespondFrameTimeoutVerify();
  HART_RespondFrameReceiveCpltVerify();
}
/*
void HART_CommandSendIndexReset(uchar *const HART_CommandSendTimes,uchar *const HART_CommandIndex)
* 变量范围:
HART_CommandSendTimes:HART通信命令失败后重发的次数，用来保证通信成功率。
HART_CommandIndex：HART通信的命令序号，
可根据该序号确定当前发送的命令在命令执行数组的哪一位。

* 返回值说明:void 
* 功能介绍:   
//命令执行数组索引标号需清零。 

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_CommandSendIndexReset()
{
   G_CurrentPageCommandExecuteStructure.ResendCounter = 0;
   G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
}

/*
//函数名称和参量和返回值类型。
bool8 HART_AddrCompare()
* 变量范围:


* 返回值说明:bool8 
* 功能介绍:   
匹配发送帧和接收帧的地址，保证通信的准确性。
*
* 关键备注：
* - 

  
* 未来提高:



*/ 
bool8 HART_AddrCompare()
{
  uchar i = 0;
  bool8 CompareResult = TRUE;
  //锐达仪表定制
  if(HART_GetProductTypeAndID() == RADAR_TYPE1)
  {
    if((G_SendFrameStructure.AddrBuff[0] == (0x80+G_PollingAddress[0]))
       ||(G_SendFrameStructure.AddrBuff[0] == (0x00+G_PollingAddress[0])))
    {
      CompareResult = TRUE;
    }
  }
  else
  {
    for(i = 0;i < G_SendFrameStructure.AddrByteNumber;i++)
    {
      if(G_SendFrameStructure.AddrBuff[i] != G_FrameReceiveBuff[i+1])
      {
       return FALSE; 
      }
    }
    if(i == G_SendFrameStructure.AddrByteNumber)
    {
      CompareResult = TRUE;
    }
  }
  return CompareResult;
}


/** static signed char ModbusFloatToASCIIConvert(float TranFloat,
                                  unsigned char DecimalN,uchar8* ShowDataBuffe)
//函数名称和参量和返回值类型。
* 变量范围: 
TranFloat：要转换的浮点数
DecimalN：精确到小数点后的位数
ShowDataBuffe：装载转换好的浮点数的字符数组
* 返回值说明:返回值返回数据中整数部分的字节个数 
* 功能介绍:   
   把浮点数转成ASCII
   输入参数：浮点数、要显示小数位
   输出参数：存放在数组ShowDataBuffe里
*
* 关键备注：
* -
* 未来提高: 
* 
*/
static signed char ModbusFloatToASCIIConvert(float TranFloat,
                                  unsigned char DecimalN,uchar*const ShowDataBuffe)
{
	uchar j = 0;
	uchar i = 0;
	uchar TempC,CarryFlag = 0;
	long uint preValue,currValue;
        uchar DecimalP  = 0;
//	ShowDataBuffe[0]=0;
	if(TranFloat < 0)
	{//浮点数是负数时
            TranFloat = 0-TranFloat;
            ShowDataBuffe[0] = '-';
            i++;
	}
	preValue = (long uint)TranFloat;
	TranFloat = TranFloat-preValue;
	//处理整数部分
	do
	{
            currValue = preValue/10;
            ShowDataBuffe[i] = preValue-currValue*10+0x30;
            preValue = currValue;
            i++;
	}
	while( (preValue != 0) && (i < SHOW_DATA_BUF_SIZE-1) );

	if(DecimalN != 0)
		ShowDataBuffe[i] = '.';
	else
		ShowDataBuffe[i] = ' ';
	DecimalP = i;
	//处理小数部分
	while(i < SHOW_DATA_BUF_SIZE)
	{
		i++ ;	
		ShowDataBuffe[i] = (uchar) (TranFloat*10);
		TranFloat = TranFloat*10-ShowDataBuffe[i];
		ShowDataBuffe[i] = ShowDataBuffe[i]+0x30;
		if( j >= DecimalN )
		{
                    if(ShowDataBuffe[i] >= '5')
                    {
                      if(ShowDataBuffe[i-1] != ' ')
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
			ShowDataBuffe[i] = ' ';
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
              //小数点前如果不是9，那么直接进位，跳出循环
              if(ShowDataBuffe[TempC] != '9')
              {
                ShowDataBuffe[TempC]++;
                TempC = 0;
              }
              else
              {
                  //如果小数点前是9，需要进位，把当前的位赋值为0
                  if(TempC > 0)
                  {
                    ShowDataBuffe[TempC--] = '0';  
                  }	
                  //判断当前是否为数据最高位，如果是，进行进位移位处理，否则进行下一轮进位处理。
                  if(TempC == 0)
                  {
                    if(ShowDataBuffe[0] == '-')
                    {
                        if(ShowDataBuffe[1] == '0')
                        {
                                ShowDataBuffe[1] = '1';
                                for(i = DecimalP+DecimalN+2; i > 2; i--)
                                  ShowDataBuffe[i] = ShowDataBuffe[i-1] ;
                                ShowDataBuffe[2] = '0';
                        }
                        else
                                ShowDataBuffe[1]++;
                 
                      }
                      else
                      {
                        if(ShowDataBuffe[0] == '9')
                        {
                                ShowDataBuffe[0] = '1';
                                for(i = DecimalP+DecimalN+2; i > 1; i--)
                                  ShowDataBuffe[i] = ShowDataBuffe[i-1] ;
                                ShowDataBuffe[1] = '0';
                        }
                        else
                                ShowDataBuffe[0]++;
                      }
                    }                                 
              }
          }
          while(TempC > 0);
	}
	ShowDataBuffe[SHOW_DATA_BUF_SIZE] = '\0';//字符串结束符
     return  DecimalP;
}

/*
uchar HART_ReceiveStructVariableAssign(uchar VariableIndex,uchar ValueAddr)
* 变量范围:
VariableIndex：HART变量在变量解析表中的序号。
uchar ValueAddr：变量坐标


* 返回值说明:变量所占字节个数
* 功能介绍:   
接收结构变量对应赋值函数。
将接收帧中的数值赋给HART变量解析表的对应变量中。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
uchar HART_ReceiveStructVariableAssign(uint VariableIndex,uchar ValueAddr)
{
   uchar *VariableArr = NULL;
   uchar i = 0,j;
   DataLengthDef ByteLength;
   ByteLength = MENU_GetHartVariableAnalysisLength(VariableIndex);
   VariableArr = MENU_GetHartVariablePtrIndex(VariableIndex);
   for(i = 0,j = ValueAddr;i < ByteLength;i++)
   {
     VariableArr[i] = G_ReceiveFrameStructure.DataBuff[j++];
   }
   return (uchar)ByteLength;
}
/*
uchar HART_ASCII_Decode(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,
                                  DataLengthDef ShowDataLength,uchar *const DataRam)
* 变量范围:
ASCII_Tag:数组指针，指向保存解码后的Tag数组。
DataLengthDef ReceiveLength：
DataLengthDef ShowDataLength：
uchar *const DataRam：

* 返回值说明:void
* 功能介绍:   
HART变量Tag解码函数，
  因为Tag的传输格式与ASCII相差两个bit位,所以需要通过该函数将6位ASCII转换为8位ASCII。
*
* 关键备注：
* - 
6位ASCII码转8位ASCII码，取公倍数48，也是6位ASCII的总字bit数
，当i%6为0时（i！=0），8位ASCII数组角标加1，6位ASCII码数组移位标度
用i%8来控制，这样就可以把6位数组中的bit流顺序保存到8位ASCII数组中。
  
* 未来提高:




*/ 
uchar HART_ASCII_Decode(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,
                                  DataLengthDef ShowDataLength,uchar *const DataRam)
{

  uchar i = 0,j = 0,k = 0,m = 0;
  for(i = 0;i < ReceiveLength*8;i++)
  {
    if((i%6 == 0)&&(i!=0))
    {
      k++;
    }
    if((i%8 == 0)&&(i!=0))
    {
      m++;
    }
    if(DataRam[m]&(0x80>>(i%8)))
    {
      ASCII_Tag[k] |= (0x80>>(i%6));
    }
    else
    {
      ASCII_Tag[k] &= ~((0x80>>(i%6)));
    }
  }
  //将拆分好的数组整理成8bitASCII
  for(i = 0;i < ShowDataLength;i++)
  {
    ASCII_Tag[i] >>=2;
    //将@去掉
    if(ASCII_Tag[i] == 0x00)
    {
      ASCII_Tag[i] = 0x20;
    }
    //判断#5bit（解包后），
    if((ASCII_Tag[i]&0x20) == 0x00)
    {
      ASCII_Tag[i] |=0x40;
    }
    else if((ASCII_Tag[i]&0x20) == 0x20)
    {
      //不处理
    }
    if(ASCII_Tag[i] != 0x20)
    {
      j++;
    }
  }
  return j;
}

/*
bool8 HART_TypeConvert(uchar *const ShowData,uchar *const Temp,DataTypeDef DataType,DataLengthDef DataLength,DataTypeDef ToType)
* 变量范围:




* 返回值说明:变量所占字节个数
* 功能介绍:   
HART变量数据类型的转换
*
* 关键备注：
* - 

  
* 未来提高:

void HART_IntToString(unsigned long int  Data,uchar *const DeviceStr)


*/ 
uchar HART_TypeConvert(uchar *const ShowData,uchar *const Temp,
                      DataTypeDef DataType,DataLengthDef DataLength,DataTypeDef ToType)
{
  uchar length = 0;
  union DataToInt
  {
    long uint Int;
    uchar Char[4];
  }C_I;
  uchar Length = 0,i;
  if(ToType == ASCII_T)
  {
    switch(DataType)
    {
      case HANDRED_T:
      case BYTE_VALUE_T:
      case UCHAR_T:
        HART_CharToString(*ShowData,Temp);
        Length = 1;
        break;
      case UINT_PERCENTILE_T:
      case INT_VALUE_T:
      case UINT_T:
        if(DataType == INT_VALUE_T)
        {
          DataLength = UINT;
        }
        for(i = 0;i < UINT;i++)
        {
          if(DataLength == UINT)
          {
            C_I.Char[i] = *(ShowData+1-i);
          }
        }
        C_I.Char[2] = 0x00;
        C_I.Char[3] = 0x00;
        if(C_I.Int == 0x00)
        {
          Temp[0] = 0x30;
          Length = 1;
        }
        else
        {
          length = HART_IntToString(C_I.Int,Temp);
          if(DataType == UINT_PERCENTILE_T)
            HART_PercentileRatio(length,Temp);
        }                 
        break;
      case FLOAT_T: 
      case FLOAT1_T:
        Length = MENU_DataToASCII(ShowData,Temp,DataType);
        MENU_TemporaryVariableReset(Temp,21,Length);        
        break;
      case LONG_UINT_T:
        for(i = 0;i < LONG_UINT;i++)
        {
          if(DataLength == LONG_UINT)
          {
            C_I.Char[i] = *(ShowData+3-i);
          }
          if(DataLength == THREE_BYTES)
          {
            if(i == 3)
            {
              C_I.Char[i] = 0;
            }
            else
              C_I.Char[i] = *(ShowData+2-i);
          }
        }
        if(C_I.Int == 0x00)
        {
          Temp[0] = 0x30;
          Length = 1;
        }
        else
          Length = HART_IntToString(C_I.Int,Temp);        
        break;
      default:
        
        break;
    }
  }
  return Length;
}
/*
void HART_PercentileRatio(uchar length,uchar *const Temp);* 变量范围:


* 返回值说明:void
* 功能介绍:   

*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_PercentileRatio(uchar length,uchar *const Temp)
{
  uchar i;
  if((length > 3)&&(length < SHOW_DATA_BUF_SIZE))
  {
    for(i = 0; i < 3;i++)
    {
      Temp[length - i] = Temp[length - i - 1];
    }
  }
  Temp[length - 3] = 0x2e;
}
/*
void HART_ASCII_Code(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,DataLengthDef ShowDataLength,uchar *const DataRam)
* 变量范围:
uchar *const ASCII_Tag：
DataLengthDef ReceiveLength：
DataLengthDef ShowDataLength：
uchar *const DataRam：

* 返回值说明:void
* 功能介绍:   
HART TAG编码函数，将8位ASCII码转换成6位ASCII码。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
void HART_ASCII_Code(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,DataLengthDef ShowDataLength,uchar *const DataRam)
{
  uchar i,j = 0,k = 0;
  
  for(i = 0 ; i < ShowDataLength;i++)
  {
    ASCII_Tag[i] &= 0x3f;
    ASCII_Tag[i] <<= 2;
  }
  for(i = 0;i < ReceiveLength*8;i++)
  {
    if((i%6 == 0)&&(i!=0))
    {
      j++;
    }
    if((i%8 == 0)&&(i!=0))
    {
      k++;
    }
    if(ASCII_Tag[j]&(0x80>>(i%6)))
    {
      DataRam[k] |= 0x80>>(i%8);
    }
    else
    {
      DataRam[k] &= ~(0x80>>(i%8));
    }
  }  
}
/*
bool8 HART_DataHandle(uchar *const DateStr)
* 变量范围:

uchar *const DateStr：日期缓冲数组指针。


* 返回值说明:void
* 功能介绍:   
HART日期处理函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
bool8 HART_DateHandle(uchar *const DateStr)
{
  
  uchar Month[2] = {0};
  uchar Day[2] = {0};
  uchar Year[4] = {0};
  uchar *Str[3] = {Month,Day,Year};
  uchar i = 0,j = 0,k = 0;
  if((DateStr[2] != 0x2d)||(DateStr[5] != 0x2d))
  {
    /* Report date event begin */
#ifndef TEST
        SystemErrorHandle();
#endif
    /* Report date event end */
    return FALSE;
  }
  else
  {
    for(i = 0;i < 10;i++)
    {
       if(DateStr[i] == 0x2d)
       {
          j++;
          k = 0;
       }
       else
       {
        Str[j][k++] = DateStr[i];
       }
    }
  }
  if(HART_MonthHandle(Month) == FALSE)
  {
    return FALSE;
  }
  if(HART_DayHandle(Day) == FALSE)
  {
    return FALSE;
  }
  if(HART_YearHandle(Year) == FALSE)
  {
    return FALSE;
  }
  
  return TRUE;
}

/*
bool8 HART_MonthHandle(uchar *const Month)
* 变量范围:

uchar *const Month：


* 返回值说明:void
* 功能介绍:   
月份处理函数
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
bool8 HART_MonthHandle(uchar *const Month)
{
  if(Month[0] == 0x30)
  {
    if((Month[1] >= 0x31)&&(Month[1] <= 0x39))
    {
      G_Date[1] = Month[1]-0x30;
    }
    else
    {
      return FALSE;
    }
  }
  else if(Month[0] == 0x31)
  {
    if((Month[1] >= 0x30)&&(Month[1] <= 0x32))
    {
      G_Date[1] = Month[1]-0x30+0x0a;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
  return TRUE;
}
/*
bool8 HART_DayHandle(uchar *const Day)
* 变量范围:
uchar *const Day

* 返回值说明:void
* 功能介绍:   
天数处理函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
bool8 HART_DayHandle(uchar *const Day)
{
  if(Day[0] == 0x30)
  {
    if((Day[1] >= 0x31)&&(Day[1] <= 0x39))
    {
      G_Date[0] = Day[1]-0x30;
    }
    else
    {
      return FALSE;
    }
  }
  else if((Day[0] == 0x31)||(Day[0] == 0x32))
  {
    if((Day[0] == 0x31))
    {
      G_Date[0] = 0x0a;
    }
    else
      G_Date[0] = 0x14;
    if((Day[1] >= 0x30)&&(Day[1] <= 0x39))
    {
      G_Date[0] += Day[1]-0x30;
    }
    else
    {
      return FALSE;
    }
  }
  else if(Day[0] == 0x33)
  {
    if((Day[1] == 0x30)||(Day[1] == 0x31))
    {
      G_Date[0] = 0x1e + Day[1]-0x30;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
  return TRUE;
}
/*
bool8 HART_YearHandle(uchar *const Day)
* 变量范围:
uchar *const Day：



* 返回值说明:void
* 功能介绍:   
年份处理函数。
*
* 关键备注：
* - 

  
* 未来提高:




*/ 
bool8 HART_YearHandle(uchar *const Year)
{
  if((Year[0] == 0x31)&&(Year[1] == 0x39))
  {
    G_Date[2] = (Year[2]-0x30)*0x0a + Year[3]-0x30;
  }
  else if((Year[0] == 0x32)&&(Year[1] == 0x30))
  {
    G_Date[2] = (Year[2]-0x30)*0x0a + Year[3]-0x30+100;
  }
  else if((Year[0] == 0x32)&&(Year[1] == 0x31))
  {
    if(((Year[2]-0x30)*0x0a + Year[3]-0x30) <= 55)
    {
      G_Date[2] = (Year[2]-0x30)*0x0a + Year[3]-0x30+200;
    }
    else
    {
      return FALSE;
    }
  }
  else 
  {
    return FALSE;
  }
  return TRUE;
}



/*
//函数名称和参量和返回值类型。
void HART_FloatToData(float FloatData,uchar *const ShowData,DataTypeDef ShowDataType)
* 变量范围:
float FloatData
uchar *const ShowData
DataTypeDef ShowDataType
* 功能介绍:   
将float型数据转换成发送帧格式的四个字节的字符型数据。

*
* 关键备注：
* - 

  
* 未来提高:
*/

void HART_FloatToData(float FloatData,uchar *const ShowData,DataTypeDef ShowDataType)
{
  union FloatToStr
  {
    uchar Char[FLOAT];
    float Float;
  }Data;
  Data.Float = FloatData;
  BufReverseCopy(ShowData,Data.Char,ShowDataType);
}
/*
//函数名称和参量和返回值类型。
void HART_FloatToData(float FloatData,uchar *const ShowData,DataTypeDef ShowDataType)
* 变量范围:
float FloatData
uchar *const ShowData
DataTypeDef ShowDataType
* 功能介绍:   
将帧格式浮点型数据转化为浮点数计算变量

*
* 关键备注：
* - 

  
* 未来提高:
*/
float HART_DataToFloat(uchar *const ShowData,DataTypeDef ShowDataType)
{
  float FloatData = 0.0;
  union FloatToStr
  {
    uchar Char[FLOAT];
    float Float;
  }Data; 
  BufReverseCopy(Data.Char,ShowData,ShowDataType);
  FloatData = Data.Float;
  return FloatData;
}
/*
//函数名称和参量和返回值类型。
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* 变量范围:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* 功能介绍:   
  整型数据转换为发送数据

*
* 关键备注：
* - 

  
* 未来提高:
*/
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
{
  union IntToData
  {
    long uint Int;
    uchar Char[4];
  }I_C;
  
  I_C.Int = LongIntData;
  BufReverseCopy(ShowData,I_C.Char,ShowDataType);
}
/*
//函数名称和参量和返回值类型。
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* 变量范围:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* 功能介绍:   
  发送数据转换为整型数据

*
* 关键备注：
* - 

  
* 未来提高:
*/
long uint HART_DataToLongInt(uchar *const ShowData,DataTypeDef ShowDataType )
{
  union IntToData
  {
    long uint Int;
    uchar Char[4];
  }I_C;
  BufReverseCopy(I_C.Char,ShowData,ShowDataType);
  return I_C.Int;
}
/*
//函数名称和参量和返回值类型。
void HART_IntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* 变量范围:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* 功能介绍:   


*
* 关键备注：
* - 

  
* 未来提高:
*/
void HART_IntToData(uint IntData,uchar *const ShowData,DataTypeDef ShowDataType )
{
  union IntToData
  {
    uint Int;
    uchar Char[2];
  }I_C;
  
  I_C.Int = IntData;
  BufReverseCopy(ShowData,I_C.Char,ShowDataType);
}
/*
//函数名称和参量和返回值类型。
void HART_VariableProtect(ShowData,DataLength);
* 变量范围:
uchar *ShowData：本地HART变量指针
DataLengthDef DataLength： 
* 功能介绍:   
HART变量保护函数，在编辑参数发送命令后，需要将改变之前的变量保护起来，
防止命令发送失败本地变量显示错误。

*
* 关键备注：
* - 

  
* 未来提高:
*/
void HART_VariableProtect(uchar *ShowData,DataLengthDef DataLength)
{
  uchar i = 0;
  for(i = 0; i < DataLength;i++)
  {
    G_VariableProtect.Buff[i] = ShowData[i];
  }
  G_VariableProtect.DataLength = DataLength;
  G_VariableProtect.DataPtr = ShowData;
}


/*
//函数名称和参量和返回值类型。
void HART_ProtectedVariableGet();
* 变量范围:


* 功能介绍:   
HART保护变量提取函数，
在写保护模式下，进入编辑界面过程中会
*
* 关键备注：
* - 

  
* 未来提高:
*/
void HART_ProtectedVariableGet()
{
  uchar i = 0;
  for(i = 0; i < G_VariableProtect.DataLength;i++)
  {
    G_VariableProtect.DataPtr[i]= G_VariableProtect.Buff[i] ;
  }
  G_VariableProtect.LoadLock = TRUE;
}
/*
//函数名称和参量和返回值类型。
uchar HART_FunctionAndUnitArrIndexGet(HART_UnitDef* UnitOrFunctionPtr,uchar Code);
* 变量范围:

* 返回值说明:返回单位码或功能码对应的数组序号
* 功能介绍:   
功能码及单位数据表数组序号获取函数
通过本函数，可以根据单位或功能代码查询到字符对应表数组对应的序号，从而可以正确显示单位及功能码。
*
* 关键备注：
* - 

  
* 未来提高:
*/
uchar HART_FunctionAndUnitArrIndexGet(const HART_UnitDef* UnitOrFunctionPtr,uchar Code)
{
  uchar i,ReturnValue = 0xff;

  if(UnitOrFunctionPtr == NULL)
  {
    return 0xff;
  }
  for(i = 0;i < 0xff; i++)
  {
    if((UnitOrFunctionPtr[i].UnitCode == 0xff)&&(UnitOrFunctionPtr[i].ArrIndex == 0xff)&&
       (UnitOrFunctionPtr[i].StrIndex == STR_INDEX_0))
    {
      ReturnValue = 0xff;
      break;
    }
    else
    {
        if(UnitOrFunctionPtr[i].UnitCode == Code)
        {
          ReturnValue = UnitOrFunctionPtr[i].ArrIndex;
          break;
        }
    }
  }
  return ReturnValue;
}
/*
//函数名称和参量和返回值类型。
uint HART_UnitShowHandle(const HART_UnitDef *Table,char* Variable)
* 变量范围:

* 返回值说明:uint 返回单位的字串序号码
* 功能介绍:   
HART变量单位显示处理函数
通过查表方式，找到对应的单位显示代码
*
* 关键备注：
* - 

  
* 未来提高:
如果，在单位表或功能码表没有装满的前提下，UnintIndex=0xff,说明程序出错，
需要报警
*/
uint HART_UnitShowHandle(const HART_UnitDef *Table,uchar* Variable)
{
  uint StrNum = 0x00;
  uchar UnintIndex = 0;
  if(Table == NULL)
  {
    return STR_INDEX_128;
  }
  else
    UnintIndex = HART_FunctionAndUnitArrIndexGet(Table,Variable[0]);
  
  if(UnintIndex == 0xff)
  {
     StrNum = STR_INDEX_128;
  }
  else
  {
    StrNum = Table[UnintIndex].StrIndex;
  }
  return StrNum;
}



/*
//函数名称和参量和返回值类型。
bool8 HART_CommandTableIndexGet(CommandDef CommandID,
                   const HART_SendStructDef *const HART_SendVersionStruct,uchar *Command)
* 变量范围:

* 返回值说明:bool8 返回序号有效性，FALSE是非法序号，TRUE是合法序号。
* 功能介绍:   
命令表序号查询函数，
由于所有的HART命令不见得在每个版本的手操器上全部使用，所以设计了
这个函数，便于节省空间
*
* 关键备注：
* - 
      查询方式会略微占用计算资源，但全部命令也不过255个，所以影响不大。
  
* 未来提高:
   如果命令码为0xff,说明是非法指令
*/
bool8 HART_CommandSendTableInfoGet(CommandDef CommandID)
{
  uchar i;
  for(i = 0;i < 0xff;i++)
  {
    FlashCmdSendTableGet(MENU_GetMenuTreeIndex(),i,G_SendStructure.SendStruct);
    if(G_SendStructure.SendStructInfo.Command == CommandID)
    {
       return TRUE;
    }
  }
  return FALSE;
}
/*
//函数名称和参量和返回值类型。
bool8 HART_CommandTableIndexGet(CommandDef CommandID,
                   const HART_SendStructDef *const HART_SendVersionStruct,uchar *Command)
* 变量范围:

* 返回值说明:bool8 返回序号有效性，FALSE是非法序号，TRUE是合法序号。
* 功能介绍:   
命令表序号查询函数，
由于所有的HART命令不见得在每个版本的手操器上全部使用，所以设计了
这个函数，便于节省空间
*
* 关键备注：
* - 
      查询方式会略微占用计算资源，但全部命令也不过255个，所以影响不大。
  
* 未来提高:
   如果命令码为0xff,说明是非法指令
*/
bool8 HART_CommandReceiveTableInfoGet(CommandDef CommandID)
{
  uchar i;
  for(i = 0;i < 0xff;i++)
  {
    FlashCmdReceiveTableGet(MENU_GetMenuTreeIndex(),i,G_ReceiveStructure.ReceiveStruct);
    if(G_ReceiveStructure.ReceiveStructInfo.Command == CommandID)
    {
       return TRUE;
    }
  }
  return FALSE;
}
/*
//函数名称和参量和返回值类型。
ProductTypeAndID_Def HART_GetProductTypeAndID();
* 变量范围:

* 返回值说明:ProductTypeAndID_Def,产品识别枚举定义，因为不同的产品有不同的
生产商，相同的生产商有不同的产品类型。
* 功能介绍:   
本函数是用于确定当前通信设备的生产商以及设备型号，从而可以确定使用什么命令表。
*
* 关键备注：
* - 
  设备类型编号和菜单树编号会有所不同，因为同一个设备类型可能会拥有不同版本协议
  ，因此菜单树编号往往会比设备类型编号要多，因为不同协议版本的相同产品需要配置
  不同的菜单树。
  
* 未来提高:
*/

ProductTypeAndID_Def HART_GetProductTypeAndID()
{
  if(G_ManufacturerID[0] == 0x2a)
  {
    if(G_DeviceType[0] == 0x0b) 
    {
      return SIEMENS_TYPE1;
    }
  }
  if(G_ManufacturerID[0] == EJA_MANUFACTURER_ID)
  {
    if(G_DeviceType[0] == 0x04)
    {
      return EJA_TYPE1;
    }  
    else if(G_DeviceType[0] == 0x5C)
    {
      return EJA530_TYPE1;
    }  
  }
  if(G_ManufacturerID[0] == LM_MANUFACTURER_ID)
  {
    if(G_DeviceType[0] == 0x06)
    {
      return LM_TYPE1;
    }    
  }
  if(G_ManufacturerID[0] == HW_MANUFACTURER_ID)
  {
    if(G_DeviceType[0] == 0x21)
    {
      return HW_TYPE1;
    }    
  }
  if(G_ManufacturerID[0] == 0xd4)
  {
    if(G_DeviceType[0] == 0x81)
    {
      return CHUAN_YI_TYPE1;
    } 
    if(G_DeviceType[0] == 0x82)
    {
      return CHUAN_YI_HVPID;
    }  
    if(G_DeviceType[0] == 0x87)
    {
      return CHUAN_YI_TYPE2;
    }  
  } 
  if(G_ManufacturerID[0] == RAYDAR_MANUFACTURER_ID)
  {
    //锐达脉冲80G
    if(G_DeviceType[0] == 0x40)
    {
      return RAYDAR_80G;
    }    
  }
  if((G_ManufacturerID[0] == 0xFD)
   ||(G_ManufacturerID[0] == 0x11))
  {
    if((G_DeviceType[0] == 0xFD)
       ||(G_DeviceType[0] == 0x18)
         ||(G_DeviceType[0] == 0x10))
    {
      return RADAR_TYPE1;
    }      
  }
  return NOMEANS;
}

/*
//函数名称和参量和返回值类型。
CommandDef HART_CommandGet(CommandDef Command,MenuTreeIndexDef MenuTreeIndex)
* 变量范围:
参考
 CommandDef和 MenuTreeIndexDef定义。
* 返回值说明:
* 功能介绍:   
本函数是用于命令ID获取发送命令中的命令序号，因为有些自定义命令同一个命令号复用了
多个命令，所以不能采用一对一匹配，因此需要本函数来确认发送命令号。
*
* 关键备注：
* - 

  
* 未来提高:
  当前川仪菜单应用在西门子的pds上，所以西门子和川仪的命令表是调换的，有表之后需要
调换回来。
*/
CommandDef HART_CommandGet(CommandDef Command,MenuTreeIndexDef MenuTreeIndex)
{
  CommandDef CommandID;
  switch(MenuTreeIndex)
  {
  case GENERAL_MENU_TREE:
      CommandID = Command;
      break;
  case SIEMENS:
     switch (Command)
     {
       case CHUAN_YI_VARIABLE_DIS_MODE_SET:
        //由于一些写入命令写入的信息是固定的，因此需要在此进行发送命令预处理
        G_CHUAN_YI_VariableDisMode[0] = 0x16;
        CommandID = SIEMENS_WRITE_ROOTING;
        break;
       case CHUAN_YI_TRANSMITTER_TYPE:
        //由于一些写入命令写入的信息是固定的，因此需要在此进行发送命令预处理
        G_CHUAN_YI_TransmitterType[0] = 0x52;
        CommandID = SIEMENS_WRITE_ROOTING;
        break;
       case CHUAN_YI_CUTOFF_PT_SHOW:
         CommandID = SIEMENS_WRITE_ROOTING_VALUE;
         break;
        default:
        CommandID = Command;
        break;
     }
      break;
  case CHUAN_YI_HVP:
      switch(Command)
      {
        case WriteAdditionalDeviceStatus:
         CommandID = ReadAdditionalDeviceStatus;
         break;
         default:
        CommandID = Command;
        break;
      }
      break;
  case CHUAN_YI :
     switch (Command)
     {
       case CHUAN_YI_CUTOFF_PT_SHOW:
       case CHUAN_YI_DISPLAY_PRESS_TYPE:
       case CHUAN_YI_TRANSMITTER_TYPE:
        CommandID = CHUAN_YI_VARIABLE_DIS_MODE;
        break;
       case CHUAN_YI_WRITE_PRO_CANCEL:
        CommandID = CHUAN_YI_WRITE_PRO_SET;
        break;
       case CHUAN_YI_VARIABLE_DIS_MODE_SET:
       case CHUAN_YI_DISPLAY_PRESS_TYPE_SET: 
        CommandID = CHUAN_YI_CUTOFF_PT_SET;
        break;
       default:
         CommandID = Command;
       break;
     }
      break; 
  default:
      CommandID = Command;
      break;
  }
  return CommandID;
}

/*
//函数名称和参量和返回值类型。
HART_ReceiveFlag HART_RespondCodeLoad(HART_ReceiveFlag FrameType)
* 变量范围:
HART_ReceiveFlag:LONG_FRAME,SHORT_FRAME
* 返回值说明:
* 功能介绍:   
HART响应帧响应码加载函数，分长帧响应码和短帧响应码。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void HART_RespondCodeLoad(HART_ReceiveFlag FrameType)
{
  uchar i,StartIndex;
  if(FrameType == LONG_FRAME)
  {
    StartIndex = 8;
  }
  else if(FrameType == SHORT_FRAME)
  {
    StartIndex = 4;
  }
  for(i = 0;i < 2;i++)
  {
    G_RecondCode[i] = G_FrameReceiveBuff[i+StartIndex];
  }
}

//把浮点数转成字符串
//输入参数：浮点数、要显示小数位
//输出参数：存放在数组ShowDataBuffe里
void	HART_FloatToChar(float TranFloat,unsigned char DecimalN)
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

/*
//函数名称和参量和返回值类型。
void HART_FrameReceiveHandle()
* 变量范围:

* 返回值说明:
* 功能介绍:   
HART通信帧接收中断处理函数
*
* 关键备注：
* - 

  
* 未来提高:

*/
void HART_FrameReceiveHandle()
{
    if(G_HART_ReceiveEN == RECEIVE_START)	
    {                   
        G_FrameReceiveBuff[G_FrameReceiveBuffIndex] = UCA1RXBUF;
        if((G_FrameReceiveBuff[G_FrameReceiveBuffIndex] != LEAD_CODE_VAL)||(FrameHandle == INFO_CODE))
        {
          //屏蔽前导码
          if((FrameHandle == LEAD_CODE)
                  &&(G_FrameReceiveBuffIndex >= G_NumRegPreams[0]-1)
                     &&((G_FrameReceiveBuff[G_FrameReceiveBuffIndex] == 0x06)
                          ||(G_FrameReceiveBuff[G_FrameReceiveBuffIndex] == 0x86)))
          {
              FrameHandle = INFO_CODE;
              //加载定界符
              G_FrameReceiveBuff[0] = G_FrameReceiveBuff[G_FrameReceiveBuffIndex];
              //判断长短帧
              if(G_FrameReceiveBuff[0]&0x80)
              {
                G_HART_ReceiveFrameType = LONG_FRAME;
                G_SendFrameStructure.AddrByteNumber = 5;
              }
              else
              {
                G_HART_ReceiveFrameType = SHORT_FRAME;
                G_SendFrameStructure.AddrByteNumber = 1;
              }
              //将接收帧缓冲数组的序号清零，将前导码覆盖掉
              G_FrameReceiveBuffIndex = 0;
          }
          if(FrameHandle == INFO_CODE)
          {
            G_BytesGap = 50;
            if(G_HART_ReceiveFrameType == LONG_FRAME)
            {
              if(G_FrameReceiveBuffIndex == LONG_FRAME_DATA_NUM_INDEX)
              {
                //计算长帧帧长
                FrameLength = G_FrameReceiveBuff[G_FrameReceiveBuffIndex]+LONG_FRAME_DATA_NUM_INDEX +1;
              }
            }
            if(G_HART_ReceiveFrameType == SHORT_FRAME)
            {
              if(G_FrameReceiveBuffIndex == SHORT_FRAME_DATA_NUM_INDEX)
              {
                //计算短帧帧长
                FrameLength = G_FrameReceiveBuff[G_FrameReceiveBuffIndex]+SHORT_FRAME_DATA_NUM_INDEX +1;
              }
            }
            G_FrameReceiveBuffIndex++;  
          }
          else
            G_FrameReceiveBuffIndex = 0;
        }
        else if(G_FrameReceiveBuff[G_FrameReceiveBuffIndex] == LEAD_CODE_VAL)
        {
                G_FrameReceiveBuffIndex++;
                FrameHandle = LEAD_CODE;
        }
    }

}
//帧接收完成，修改状态机，复位帧长变量
void HART_ReceiveStateReset()
{
  G_RxFrameVerifyFlag = REC_COMPLETE;
  FrameHandle = REC_STANDBY;
}

/*
//函数名称和参量和返回值类型。
void HART_AbnormalStatusHandleModule()
* 变量范围:

* 返回值说明:
* 功能介绍:   
HART通信异常状态处理模块，
如果通信帧正常，就进行正常解析，否则，进入异常处理函数。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void HART_AbnormalStatusHandleModule()
{
  AbnormalStatusDef AbnormalStatus = ABNORMAL_STANDBY;
  //获取异常状态码
  AbnormalStatus = HART_AbnormalStatusHandle();
  if(AbnormalStatus == ABNORMAL_STANDBY)
  {  
    //刷新数据关闭加载保护锁
    if((G_ReceiveFrameStructure.Command == PV_OUTPUT_INFO)
      ||(G_ReceiveFrameStructure.Command == PV)
        ||(G_ReceiveFrameStructure.Command == PV_CURRENT_PERCENT)
          ||(G_ReceiveFrameStructure.Command == ReadAdditionalDeviceStatus)) 
    {
      G_VariableProtect.LoadLock = FALSE;
    }  
    if(G_VariableProtect.LoadLock == FALSE)
      HART_ReceiveFrameAnalysis();
  }
  else if(AbnormalStatus != ABNORMAL_STANDBY)
  {
    //个别警告界面不需要保护变量值，所以需要在正常接收帧处理部分提出警告
    if((AbnormalStatus != POSSIBLE_VALUE)
       &&(AbnormalStatus != EXC_CORRECTION)
         &&(AbnormalStatus != OTHER_ANOMALY))
    {
      HART_ProtectedVariableGet();   
    }
    else
    {
      /* Patch begin */
      if(((MENU_CurrentPageNumGet() == EA_PAGE_INDEX_83)
          ||(MENU_CurrentPageNumGet() == EA_PAGE_INDEX_85))
            &&(MENU_GetMenuTreeIndex() == EJA))
      {
        HART_ProtectedVariableGet();   
      }
      else if(((MENU_CurrentPageNumGet() == SMS_PAGE_INDEX_48)
          ||(MENU_CurrentPageNumGet() == SMS_PAGE_INDEX_49))
            &&(MENU_GetMenuTreeIndex() == SIEMENS))
      {
        HART_ProtectedVariableGet();   
      }
      else if(((MENU_CurrentPageNumGet() == CY_PAGE_INDEX_154)
          ||(MENU_CurrentPageNumGet() == CY_PAGE_INDEX_156))
            &&(MENU_GetMenuTreeIndex() == CHUAN_YI))
      {
        HART_ProtectedVariableGet();   
      }
      /* Patch end */
    }
    //异常状态处理
    HART_AbnormalPageHandle(AbnormalStatus); 
  }
}

/*
//函数名称和参量和返回值类型。
void	HART_CableLengthReset(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:  
缆长值归零函数，
本函数只服务于锐达仪表菜单，用来给缆长变量赋值为0。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void	HART_CableLengthReset(void)
{
  MENU_FloatToData(G_PublicVF0,0,FLOAT_T);
}
/*
void HART_DistCalibrateHandle()

* 变量范围:



* 返回值说明:void
* 功能介绍:   
  菜单特殊处理函数，用来执行菜单页面中必须执行的特定运算，
  根据菜单结构的附加功能项，采取特定的运算，使用情况较少，
  多用于定制产品（目前用于锐达仪表的距离系数校准）
个别变量设计的。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_DistCalibrateHandle()
{
  //校准前距离1
  float HistoryCalibrateValue1;
  //校准前距离2
  float HistoryCalibrateValue2;
  //比例系数运算变量
  float RadarRatioCorrect;
  //零点系数运算变量
  float RadarZeroCorrect;
  //测量值1运算变量
  float RadarMeasure1;
  //测量值2运算变量
  float RadarMeasure2;
  //实际值1运算变量
  float RadarReality1;
  //实际值2运算变量
  float RadarReality2;
  
  RadarMeasure1 = HART_DataToFloat(G_PublicVF11,FLOAT_T);
  RadarMeasure2 = HART_DataToFloat(G_PublicVF10,FLOAT_T);
  RadarReality1 = HART_DataToFloat(G_PublicVF13,FLOAT_T);
  RadarReality2 = HART_DataToFloat(G_PublicVF12,FLOAT_T);
  RadarRatioCorrect = HART_DataToFloat(G_PublicVF14,FLOAT_T);
  RadarZeroCorrect = HART_DataToFloat(G_PublicVF15,FLOAT_T);
  
  if(RadarRatioCorrect == 0)
  {
    RadarRatioCorrect = 0;
    RadarZeroCorrect = 0;
  }
  else
  {
    HistoryCalibrateValue1 = 
      (RadarMeasure1 + RadarZeroCorrect)/RadarRatioCorrect;
    HistoryCalibrateValue2 = 
      (RadarMeasure2 + RadarZeroCorrect)/RadarRatioCorrect;
    if(HistoryCalibrateValue1 == HistoryCalibrateValue2)
    {
      RadarRatioCorrect = 0;
      RadarZeroCorrect = 0;
    }
    else
    {
      RadarRatioCorrect = 
        (RadarReality1-RadarReality2)/(HistoryCalibrateValue1-HistoryCalibrateValue2);
      RadarZeroCorrect = 
        (HistoryCalibrateValue2*RadarReality1-HistoryCalibrateValue1*RadarReality2)/(HistoryCalibrateValue1-HistoryCalibrateValue2);
    }
  }
  HART_FloatToData(RadarMeasure1,G_PublicVF11,FLOAT_T);
  HART_FloatToData(RadarMeasure2,G_PublicVF10,FLOAT_T);
  HART_FloatToData(RadarReality1,G_PublicVF13,FLOAT_T);
  HART_FloatToData(RadarReality2,G_PublicVF12,FLOAT_T);
  HART_FloatToData(RadarRatioCorrect,G_PublicVF14,FLOAT_T);
  HART_FloatToData(RadarZeroCorrect,G_PublicVF15,FLOAT_T);
}
/*
AbnormalStatusDef HART_ErrCodeWithSingleDefinition(uchar DataByteNumber,uchar RecondCode);
* 变量范围:



* 返回值说明:AbnormalStatusDef异常状态码。
* 功能介绍:   
  独有定义错误码确认函数，通过本函数，确认错误码类型。
*
* 关键备注：
* - 

  
* 未来提高:

遇到更多的应用独有错误定义 产品时，可以后续添加，目前用到什么就写什么。


*/
static AbnormalStatusDef HART_ErrCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value)
{
  if(IS_SINGLE_ERROR_RANGE)
  {
    //写保护反馈码判断
    if(RecondCode == 0x07)
    {
      Value = WRITE_PROTECT;
    }
    else if(RecondCode== 0x04)
    {
      Value = VALUE_SMALL;
    }
    else if(RecondCode== 0x03)
    {
      Value = VALUE_LARGE;
    }
    else if(RecondCode== 0x02)
    {
      Value = INVALID_SELECTION;
    }
    else if(G_RecondCode[0]== 0x40)
    {
      Value = NOT_IMPLEMENTED;
    }
  }
  return Value;
}
/*
static AbnormalStatusDef HART_ErrCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value);
* 变量范围:



* 返回值说明:AbnormalStatusDef异常状态码。
* 功能介绍:   
  复用定义错误码确认函数，通过本函数，确认错误码类型。
*
* 关键备注：
* - 

  
* 未来提高:

遇到更多的应用独有错误定义 产品时，可以后续添加，目前用到什么就写什么。


*/

static AbnormalStatusDef HART_ErrCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value)
{
  //后续复用错误判定都需要加上设备厂家及型号的判定，因为不同厂家有不同的复用错误判定。
  //目前程序的处理保留，后续升级或新增再做修改。
  ProductTypeAndID_Def ProductTypeAndID = HART_GetProductTypeAndID();
  if(IS_MULTIPLE_ERROR_RANGE)
  {
    if(RecondCode== 11)
    {
      if(ExecutingCommand == WRITE_PV_RANGE)
      {
        Value = UPPER_HIGH;
      }
      else
      {
        Value = EXC_CORRECTION;
      }
      if(G_RecondCode[1] == 72)
      {
        Value = MULTIDROP_MODE;
      }
    }
    else if(RecondCode== 9)
    {
      if((ExecutingCommand == WRITE_PV_RANGE)
         ||(ExecutingCommand == EJA530_LOW_CUT_W))
      {
        Value = LOWER_HIGH;
      }
      else if(IS_CY_PROCESS_HIGH)
      {
        Value = PROCESS_HIGH;
      }
      else if((ProductTypeAndID == CHUAN_YI_TYPE1)&&((ExecutingCommand == AO_MINIMUM)
                  ||(ExecutingCommand == AO_MAX)))
      {
        //Incorrect Loop Current Mode or Value,后续补充
        Value = OTHER_ANOMALY;
      }
      else
      {
        Value = OTHER_ANOMALY;
      }
    }
    else if(RecondCode == 10)
    {
      if(ExecutingCommand == WRITE_PV_RANGE)
      {
        Value = LOWER_LOW;
      }
      else if((ProductTypeAndID == CHUAN_YI_TYPE1)&&
              (ExecutingCommand == PV_ZERO_SET))
      {
        Value = PROCESS_HIGH;
      }
      else
      {
        Value = OTHER_ANOMALY;
      }
    }
    else if(RecondCode == 12)
    {
      if(ExecutingCommand == WRITE_PV_RANGE)
      {
        Value = UPPER_LOW;
      }
      else
      {
        Value = INVALID_TRIM_TYPE;
      }
    }
    else if(RecondCode == 15)
    {
      Value = INVALID_FUNCTION;
    }
  }
  return Value;
}
/*
static AbnormalStatusDef HART_WarningCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value);
* 变量范围:



* 返回值说明:AbnormalStatusDef异常状态码。
* 功能介绍:   
  独有定义警告码确认函数，通过本函数，确认警告码类型。
*
* 关键备注：
* - 

  
* 未来提高:

遇到更多的应用独有错误定义 产品时，可以后续添加，目前用到什么就写什么。


*/
static AbnormalStatusDef HART_WarningCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value)
{
  if(IS_SINGLE_WARNING_RANGE)
  {
  
  }
  return Value;
}
/*
static AbnormalStatusDef HART_ErrCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value);
* 变量范围:



* 返回值说明:AbnormalStatusDef异常状态码。
* 功能介绍:   
  复用定义警告码确认函数，通过本函数，确认警告码类型。
*
* 关键备注：
* - 

  
* 未来提高:

遇到更多的应用独有错误定义 产品时，可以后续添加，目前用到什么就写什么。


*/
static AbnormalStatusDef HART_WarningCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value)
{
  //后续复用错误判定都需要加上设备厂家及型号的判定，因为不同厂家有不同的复用错误判定。
  //目前程序的处理保留，后续升级或新增再做修改。
  ProductTypeAndID_Def ProductTypeAndID = HART_GetProductTypeAndID();

  if(IS_MULTIPLE_WARNING_RANGE)
  {
    if(RecondCode == 0x08)
    {
      Value = POSSIBLE_VALUE;
    }
    else if(RecondCode == 14)
    {
      if(ExecutingCommand == SET_LSL)
      {
        Value = NEW_LRV_PUSHED;
      }
      else if(ExecutingCommand == SET_LUL)
      {
        Value = SPAN_SMALL;
      }
      else
      {
        Value = PROCESS_HIGH;
      }
    }
  }
  return Value;
}
/*
void HART_UnitTempLoad(DataTypeDef DataType,bool8 IsVariableHandle,uchar *ShowData);
* 变量范围:



* 返回值说明:AbnormalStatusDef异常状态码。
* 功能介绍:   
  单位缓存更新处理，一些单位选择界面确认时可以通过本函数将变量值更新。
*
* 关键备注：
* - 

  
* 未来提高:




*/
void HART_UnitTempLoad(DataTypeDef DataType,bool8 IsVariableHandle,uchar *ShowData)
{
  if((DataType == FUNC_CODE_T)&&(IsVariableHandle == TRUE))
  {
    ShowData[0] = G_UnitTemp[0];
  }
}