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

//����������ʱ��û�н��յ���Ӧ֡���ȶ�Ϊ��ʱһ��
#define RECEIVE_TIME_INTERVAL 800

void HART_ReceiveStateReset();
//����֡�����������
unsigned char FrameLength = MAX_FRAME_LENGTH;
//����֡�ֶδ������
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
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡ǰ������غ�����
���ݷ���֡�ṹ������е�ǰ�����������ǰ������ص�����֡���鵱�С�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendDelimiterLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡��������غ�����
������֡�ṹ������еĶ����Ԫ�ؼ��ص�����֡���鵱�С�
*
* �ؼ���ע��
* - 


* δ�����:



*/ 

void HART_SendDelimiterLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff + *FrameBuffIndex) = G_SendFrameStructure.Delimiter;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendSlaveAddrLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡���豸��ַ���غ�����
�����豸�ĵ�ַ���ص�����֡�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendCommandLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡������غ�����
������֡������ż��ص�����֡���鵱�С�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_SendCommandLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff+*FrameBuffIndex) = G_SendFrameStructure.Command;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendDataLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ������ݼ��غ�����
������֡�е����ݴӷ���֡�ṹ������м��ص�����֡�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendDataByteNumberLoad(uchar *FrameBuff,uchar *FrameBuffIndex)
* ������Χ:
FrameBuff������֡�����׵�ַ��
FrameBuffIndex����У��������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡�����ֽڸ������غ�����
��Ҫ�������ݵ��ֽڸ����ӷ���֡�ṹ���������ȡ�����������浽����֡���鵱�С�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_SendDataByteNumberLoad(uchar *const FrameBuff,uchar *const FrameBuffIndex)
{
  *(FrameBuff + *FrameBuffIndex) = G_SendFrameStructure.DataByteNumber;
  *FrameBuffIndex = *FrameBuffIndex + 1;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uchar HART_CRC(uchar *const FrameBuff,uchar FrameBuffLength,bool8 IsSendFrame)
* ������Χ:
FrameBuff����У�������׵�ַ��
FrameBuffIndex����У��������š�
* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ��CRCУ�麯����

*
* �ؼ���ע��
* - 
����֡�ͷ���֡��CRCУ�鲻һ��������֡��û��ǰ����
������֡��ǰ���롣
  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SendFrameStructureInit(CommandDef Command,
                        const HART_SendStructDef *const HART_SendVersionStruct)
* ������Χ:
typedef struct
{
  uchar LeadCodeNumber;         //ǰ�����ֽڸ���
  uchar Delimiter;              //�����
  uchar AddrByteNumber;         //��ַ�ֽڸ���
  uchar *AddrBuff;              //��ַ�����׵�ַָ��
  uchar Command;                //����
  uchar DataByteNumber;      //�����ֽڸ���
  uchar *DataBuff;           //���������յ�ַ
}HART_FrameDef;

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŷ���֡�ṹ�������ʼ��������
ͨ��������������Ӧ�Ĳ���������Ӧ�Ľṹ�����Ա��
* �ؼ���ע��
* - ������͵�����֡��д����
* δ�����:
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

  //��ȡ�˵������
  MenuTreeIndex = MENU_GetMenuTreeIndex();  
  if(HART_CommandSendTableInfoGet(CommandID) ==  TRUE)
  {
    //����ǰ����
    G_SendFrameStructure.LeadCodeNumber = G_NumRegPreams[0]; 
    G_SendFrameStructure.Delimiter = G_SendStructure.SendStructInfo.Delimiter;
    G_SendFrameStructure.AddrByteNumber = G_SendStructure.SendStructInfo.AddrByteNumber;
    //���ձ���ʵ����ID����Ϊ��Щ����ż��ݶ�����ܣ�����Դ˱�������Ϊ�����������������
    G_HART_ReceiveTableRealCommandID = G_SendStructure.SendStructInfo.Command;
    G_SendFrameStructure.Command = HART_CommandGet(G_SendStructure.SendStructInfo.Command,MenuTreeIndex);
    G_SendFrameStructure.DataByteNumber = G_SendStructure.SendStructInfo.VariableByteNumber;
    VariableIndexNumber = G_SendStructure.SendStructInfo.VariableIndexNumber;
    G_SendFrameStructure.W_R_Flag = G_SendStructure.SendStructInfo.W_R_Flag;
    //����д���ݱ���
    if(G_SendFrameStructure.W_R_Flag == WRITE)
    {
      Temp = G_SendStructure.SendStructInfo.VariableIndex;
      if(FlashReadLockStatusGet() == TRUE)
      {
        FlashReadLockHandle(FALSE);
        //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
        FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
        FlashReadLockHandle(TRUE);
      }
      else
      {
       //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
        FlashVariableGroupLoad(Temp,&PageVariableTable,&VariableGroupTable);
      }

      for(i = 0;i < VariableIndexNumber;i++)
      {
        VariableIndex = MENU_VariableIndexInfoGet(i,VariableGroupTable);
        //��ȡHART���������ݳ���
        DataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);
        //��ȡHART��������ָ��
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
    //�Ƿ�����
  }
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_AddrConnect(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŵ�ַ���Ӻ�����
��ַ����ָ�������豸ͨ��00�������Ӧ��ַ�Ĵ��豸��ȡ������Ϣ����ַƥ��󼴽������ӡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/

void HART_AddrConnect(void)
{
    G_SendFrameStructure.AddrBuff[0] = G_PollingAddress[0];
    HART_SingleAddrConnect();
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_StartConnect(PollingTypeDef ConnetectWay,uchar StartAddr)
* ������Χ:
ConnetectWay:
//HART��ѯ���ӷ�ʽ����
typedef enum 
{
  ALL_CONNECT,
  HALF_CONNECT,
  SINGLE_CONNECT
}HART_PollingConnectWayDef;

StartAddr����ѯ���ӵ���ʼ��ַ��

* ����ֵ˵��:void 
* ���ܽ���:
HARTͨ�ſ�ʼ���ӱ������ú�����
�������ӷ�ʽ����G_PollingConnectGroupIndex����ʼֵ��
ǰ���־��Ǵӵ�ַ0��ʼ��ѯ����HALF_CONNECT_8�Ǵӵ�ַ8��ʼ�ġ�
*
* �ؼ���ע��
* - 
G_PollingConnectGroupIndex
  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_SingleAddrConnect()
* ������Χ:

* ����ֵ˵��:void 
* ���ܽ���:   
HART����ַ���Ӻ�����
ÿ��ֻ���һ����ַ��������

*
* �ؼ���ע��
* - 
NOP(30);
�˴���ʱ��Ϊ�˴��������з�����������һ�ν���֡�ֿ�������鿴.

G_TimeStamp = 600;
�趨��ʱ���������2s 
���������ʱ������Ϊ��ȷ��

* δ�����:



*/

void HART_SingleAddrConnect()
{  
  //��������ģʽ
  HART_ReceiveSendEN(SEND_START);
  HART_FrameSend();
  HART_ReceiveSendEN(RECEIVE_START);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_ReceiveSendEN(HartRS_Flag Flag)
* ������Χ:
Flag
typedef enum
{
  SEND_START = 0,
  RECEIVE_START = 1
}HART_RS_Flag;
Flag = SEND_START����ʼ���͡�
Flag = RECEIVE_START����ʼ���ա�
* ����ֵ˵��:void 
* ���ܽ���:   
HART���ͽ�������ʹ�ܺ���
����������ߵ�����Ȩ���������ͻ��ǻ�Ӧ֡���ա�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_ReceiveSendEN(HART_RS_Flag Flag)
{
  //������ʱ����֤����֡���� 
  //NOP(50);
  RECEIVE_SEND_EN = Flag;
  G_HART_ReceiveEN = Flag;
  //������ʱ����֤����֡���� 
  NOP(50);
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_FrameStringSend(uchar *const FrameBuff,uchar FrameBuffLength)
* ������Χ:
FrameBuff[]:װ��HART����֡�����顣
FrameBuffLength:����֡������ַ�������
* ����ֵ˵��:void 
* ���ܽ���:   
HART֡�ַ������ͺ�������Ҫ���ͳ�ȥ������֡�ַ������͵�HART�����ϡ�

*
* �ؼ���ע��
* -
HART_ReceiveSendEN(SEND_START);�����߿��ƺ�����
��G_HART_ReceiveEN = SEND_START; 
�ǳ������б�־���������ֽ���֡�����������ı�־�Ա�����
  
* δ�����:



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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_FrameSend(void)
* ������Χ:
FrameBuff[]:װ��HART����֡�����顣
FrameBuffIndex:����֡�������š�

* ����ֵ˵��:void 
* ���ܽ���:   
HART֡���ͺ���������������������֡���͵�ȫ�����̣�����֡����Լ�֡���͡�

*
* �ؼ���ע��
* - 

  
* δ�����:



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
* ������Χ:
G_FrameReceiveBuff[]:����֡�������顣
ReceiveIndex������֡����������š�
G_ReceiveFrameStructure������֡�ṹ�������

* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡У������غ��������𽫽���֡�е�У���벿����ȡ��������ת�浽����֡
�ṹ�������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_ReceiveCheckoutLoad(uchar ReceiveIndex )
{
  G_ReceiveFrameStructure.Checkout = G_FrameReceiveBuff[ReceiveIndex];
}

/*
void HART_ReceiveCommandLoad(uchar *const ReceiveIndex)
* ������Χ:
G_FrameReceiveBuff[]:����֡�������顣
ReceiveIndex������֡����������š�
G_ReceiveFrameStructure������֡�ṹ�������

* ����ֵ˵��:void 
* ���ܽ���:   
����֡����ż��غ���
ÿһ����ȷ�Ľ���֡�ж����������Ӧ���������ţ�������������������
���浽����֡�ṹ������С�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_ReceiveCommandLoad(uchar *const ReceiveIndex )
{
  G_ReceiveFrameStructure.Command = (CommandDef)G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
void HART_LoadExpandedDeviceType()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��չ�豸���ͻ�ȡ������
��Ϊ�ܶ��������Ҫ�����豸�����Լ��豸�ͺ��������ִ���
�����ͨ��֡������ɣ����ϻ�ȡ�����Լ��ͺţ�������Ҫע��������
ֻ�ж�֡��00��������Ϊ02�����ҷ����ֲ������ݵ�HART�汾�Ż�ִ�б�������

*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
void HART_LoadExpandedDeviceType()
{
  //��Ҫ�ڵ�һʱ���ȡ�������Լ��豸�ͺ�
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡��ַ������غ���
���𽫽���֡�еĵ�ַ��ȡ���������浽����֡�ṹ��������С�

*
* �ؼ���ע��
* - 
�������ֱ�Գ�֡�ͺͶ�֡�͵ĵ�ַ������ȡ����

���˼��ص�ַ��Ϣ��ͬʱҲ��������ID�Լ���Ʒ������ȡ����������˵�������
  
* δ�����:


*/ 

void HART_ReceiveAddrBuffLoad()
{
  uchar i = 0;
#ifndef SAVE_MAMORY
  //����Ǳ��֡����
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡���ݼ��غ���
������֡�е����ݲ��ֱ��浽����֡�ṹ��������С�

*
* �ؼ���ע��
* - 

  
* δ�����:



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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡�����ֽڸ������غ���
������֡�����ݵ��ֽڸ�������Ľ���֡�ṹ�������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_ReceiveDataByteNumberLoad(uchar *const ReceiveIndex)
{
  G_ReceiveFrameStructure.DataByteNumber = G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
void HART_ReceiveDelimiterLoad(uchar *const ReceiveIndex)
* ������Χ:
uchar *const ReceiveIndex������֡���

* ����ֵ˵��:void 
* ���ܽ���:   
HART���ն�������غ���
������֡�еĶ�������浽����֡�ṹ������С�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_ReceiveDelimiterLoad(uchar *const ReceiveIndex)
{
  G_ReceiveFrameStructure.Delimiter = G_FrameReceiveBuff[*ReceiveIndex];
  *ReceiveIndex = *ReceiveIndex+1;
}
/*
uchar HART_VersionGet()
* ������Χ:

* ����ֵ˵��:HARTЭ��汾 
* ���ܽ���:   
HART�汾����������
ʹ�õ�����һ���汾��HARTЭ�顣

*
* �ؼ���ע��
* - 

  
* δ�����:
���������汾�󣬻���·�֧���


*/ 
uchar HART_VersionGet()
{
  return G_UniversalRev[0];
}
/*
void HART_WriteProtectHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
������д�����жϺ���
ͨ������֡���������ص������Ƿ�Ϊд���������롣

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
AbnormalStatusDef HART_AbnormalStatusHandle()
{
  AbnormalStatusDef Value = ABNORMAL_STANDBY;
  uchar DataByteNumber = G_ReceiveFrameStructure.DataByteNumber;
  uchar RecondCode = G_RecondCode[0];
  CommandDef ExecutingCommand = G_SendFrameStructure.Command;
  //������Ӧ�봦��

  if(DataByteNumber == 0x02)
  {
    Value = HART_ErrCodeWithSingleDefinitions(RecondCode,Value);
    Value = HART_ErrCodeWithMultipleDefinitions(RecondCode,ExecutingCommand,Value);
  }
  //������Ӧ�봦��
  Value = HART_WarningCodeWithSingleDefinitions(RecondCode,Value);
  Value = HART_WarningCodeWithMultipleDefinitions(RecondCode,ExecutingCommand,Value);
  return Value;
}
/*
void HART_AbnormalPageHandle(AbnormalStatusDef AbnormalStatus)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�쳣ҳ�洦����
ͨ�Ż�ϵͳ�����쳣ʱ����Ҫ�л��������֪ͨҳ��

*
* �ؼ���ע��
* - 

  
* δ�����:



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
  }//�����쳣����   
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
  
  }//Ŀǰδ֪�쳣�����������Բ��Ӿ�������л���������Ҫ�������ơ�
  else
  {
  
  }
  //��ʾ��ǰ����ҳ��
  G_RxFrameVerifyFlag = RESPOND_CODE_EXPRESSION;
  //��Ҫ���þ�������л�����������ҳ����ʾʱ��
  G_WarningPageRefreshFlag = WARNING_START;
  FlashReadLockHandle(FALSE);
  MENU_TimingIntervalSelect();
  FlashReadLockHandle(TRUE); 
}
/*
RecHandleDef HART_ReceiveFrameHandle(void)
* ������Χ:
typedef enum 
{
SHORT_FRAME_ERR,
LONG_FRAME_ERR,
VALID_FRAME,
RESPOND_CODE_ERR,
CRC_ERR,
}RecHandleDef;

* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡�����������ӵ�������֡����У����˶ԣ�ͨ����˺���н���֡��֣����Ժż���
������֡�ṹ���С�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

RecHandleDef HART_ReceiveFrameHandle()
{ 
  uchar ReceiveIndex = 2,CRC_LocalCalculate,FrameReceiveBuffIndex;
  //�����յ����ֽڸ������ص���ʱ�����У����ҽ�ȫ�ּ�����������
  FrameReceiveBuffIndex = FrameLength;
  G_FrameReceiveBuffIndex = 0;
  CRC_LocalCalculate = HART_CRC(G_FrameReceiveBuff,FrameReceiveBuffIndex,FALSE);
  HART_ReceiveCheckoutLoad(FrameReceiveBuffIndex);
  //У����ƥ��
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
      //������ܵ��ֽڸ�������������˵������������֡���������쳣״̬�򵥴���״̬������
      if(G_ReceiveFrameStructure.DataByteNumber > 0x02)
      { 
        HART_ReceiveDataBuffLoad(&ReceiveIndex);
        G_RxFrameVerifyFlag = REC_STANDBY;
        return VALID_FRAME;
      }
      else//��Ӧ���쳣
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
    //У����󷵻�У�������
    FrameLength = MAX_FRAME_LENGTH;
    /* Report CRC event end */
    return CRC_ERR;
  }
}


/*
void HART_InfoBuffPtrInit()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ����Ϣ����ָ���ʼ�����������շ�֡�ṹ��ĵ�ַ�����ݼ�������󶨵��ṹ��
�����ϡ�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_InfoBuffPtrInit()
{
  G_ReceiveFrameStructure.DataBuff = G_SendReceiveDataBuff;
  G_SendFrameStructure.DataBuff = G_SendReceiveDataBuff;
}


/*
void HART_ReceiveFrameAnalysis(const HART_ReceiveStructDef *const HART_ReceiveStruct)
* ������Χ:
const HART_ReceiveStructDef *const HART_ReceiveStruct��
HART����֡�ṹ�塣
* ����ֵ˵��:void 
* ���ܽ���:   
HART����֡����������
�����յ���HART����֡��ֵ���Ӧ�ı����ϡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



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

  //��������ID--CommandID�ҵ���Ӧ������ձ���������CommandIndex
  if(HART_CommandReceiveTableInfoGet(CommandID) ==  TRUE)
  {
   Temp = G_ReceiveStructure.ReceiveStructInfo.VariableIndex;
   if(FlashReadLockStatusGet() == TRUE)
   {
     FlashReadLockHandle(FALSE);
     //���ص�ǰҳ��ı�������Ϣ�Լ���������Ϣ������������ʾ���Ͱ󶨵�HART���
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
      //�ṹ���ж�ӦHART������ֵ
      DataByteNumber += HART_ReceiveStructVariableAssign(VariableIndex,DataByteNumber);
    }
  }
}
/*
void HART_ReceiveSuccessHandle()
* ������Χ:
HART_CommandSendTimes:HARTͨ������ʧ�ܺ��ط��Ĵ�����������֤ͨ�ųɹ��ʡ�

HART_CommandIndex��HARTͨ�ŵ�������ţ�
�ɸ��ݸ����ȷ����ǰ���͵�����������ִ���������һλ��

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�Ž��ճɹ���������
�ɹ����������ĺ󣬴ӻ���ظ�����һ����Ӧ���ģ�����ȷ����ȫ����֮��
������ճɹ��������������������

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 


void HART_ReceiveSuccessHandle()
{
    RecHandleDef Result;
    HART_ResendFlagReset();

    //�������ӵ�ַƥ��
    if(HART_AddrCompare() == TRUE)
    {
        //����֡���� 
        Result = HART_ReceiveFrameHandle();
        if((Result == VALID_FRAME)||(Result == RESPOND_CODE_ERR))
        {
          HART_AbnormalStatusHandleModule();
        }
        //�������֡�쳣
        if((Result == SHORT_FRAME_ERR)
                ||(Result == LONG_FRAME_ERR)
                  ||(Result == CRC_ERR))
        {
          //�ɹ���ʧ�ܴ���ͳ��
          SystemSucRateResultStatistis(FALSE);
          G_RxFrameVerifyFlag = REC_INCORRECT;
        }
        else
        {
          if(G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber == 0)
          {
            G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber = 1;
          }
          //�������ִ��������ű���ֵ�Ѿ��ﵽ������ִ�������װ����ʱ��
          if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex
             >= G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber-1)
          {
            G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
            G_CurrentPageCommandExecuteStructure.ResendCounter = 0;
            if(G_HART_HandleFlag == HART_START_INIT)
            {
              G_HART_HandleFlag = HART_INIT_COMPLETE;
              //Ӳ���汾��Ϊ���ֽڸ�5λ���������������һ��������������������������Ϣ
              G_HardwareRev[0] >>= 3;
            }
            else if(G_HART_HandleFlag == HART_START_COMMON)
            {
               G_HART_HandleFlag = HART_COMMON_COMPLETE;
            }
            //��һ����������ɣ���Ҫ���ض��ı༭������б�������
            G_ParamLoadLock = FALSE;
            //��ʱҪ�ر�HARTͨ��ͨ�����������������
            RECEIVE_SEND_EN = RECEIVE_START;
            /*�������е���������ִ����Ϻ�
              SINGLE_C����ҳ����Ҫ����ˢ�£����¶���*/
            if((MENU_CurrentPageTypeGet() == EDIT_PAGE)
               ||(MENU_CurrentPageTypeGet() == PARAM_SET_PAGE))
            {
              MENU_PageShowSwitch(TRUE);
              //���ڱ�����ȡ���֮����Ҫ��ҳ�������ʾ���ݣ���˳����������⣬����⿪flash��
              MENU_ClearLcdScreen();
              FlashReadLockHandle(FALSE);
              //����ѡ��ҳ���漰�����׷�����⣬�����Ҫ��������ִ�����������ڵڶ���ˢ��ҳ��ʱ����ѡ��
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
              //��ִֹ�����������������������ܸ���
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
          //��������ڱ��Ľ���ʧ�����Ӧ���쳣���󣬽����ձ�־���óɿ���
          if((G_RxFrameVerifyFlag != REC_INCORRECT)
             &&(G_RxFrameVerifyFlag != RESPOND_CODE_EXPRESSION))
          {
              //ͨ�ųɹ�ƥ��һ��
              SystemSucRateResultStatistis(TRUE);
              G_RxFrameVerifyFlag = REC_STANDBY;
          }
      }
    }
    else//��ַ��ƥ��
    {
      /* Report invalid frame event end */
      G_FrameReceiveBuffIndex = 0;
      G_RxFrameVerifyFlag = REC_INCORRECT;
    }
}

/*
void HART_IntToString(unsigned long int  Data,uchar *const DeviceStr)
* ������Χ:
DeviceStr������ASCII����ַ������顣
Data:���������ݡ�
* ����ֵ˵��:void 
* ���ܽ���:   
������������ת����ASCII���ַ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



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
* ������Χ:
DeviceStr������ASCII����ַ�ָ�롣
Data:�ַ������ݡ�
* ����ֵ˵��:void 
* ���ܽ���:   
���ַ�������ת����ASCII���ַ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_CharToString(uchar  Data,uchar *const DeviceStr)
{
  uchar i = 0,j = 0,flag = 0;
  uchar Scale = 100;

  
  for( i = 0;i < 3; i++)
  { 
    //��Ϣ����������ʾ��Ҫ�����
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
      //Revision 0��ʾΪ�ո���
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
* ������Χ:
HART_CommandIndex��HARTͨ�ŵ�������ţ�
�ɸ��ݸ����ȷ����ǰ���͵�����������ִ���������һλ��

* ����ֵ˵��:void 
* ���ܽ���:   
HART����ͺ�����
�����������������ִ���������ҵ���Ӧִ�е���š�

*
* �ؼ���ע��
* - 

  
* δ�����:

���ҳ��û�й��������Ҫͨ��������������ε�����͡�

����ͺ�����Ҫ���뷵��ֵ���Դ�������ҳ�������������������ָ���ûָ���
һ��ָ��Ƕ��ָ������

�����������֮����Ҫ����IDENTIFY��������ڷ�������ṹ�������һ���µ�����ṹ
����ʶҪ������IDENTIFY��
*/ 
PageCommandNumDef HART_CommandSend()
{
  PageCommandNumDef CommandNum = NO_COMMAND;
  CommandDef CommandID;
  CommandID = 
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[G_CurrentPageCommandExecuteStructure.CurrentCommandIndex];

  //ҳ����ر�����������0
  if(G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber > 0)
  {
    CommandNum = MORE_COMMAND;
    if((MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE)&&
       			(MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_101))
    {
      //��ɹ��ʽ��洦��
      CommandNum = TEST_COMMAND;
    }
    //�ɹ������㷢��ͳ��
    SystemSendStatistics();
    //�������ӷ��͵�����
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
  //ֻҪ��������ͣ��Ͳ����Զ�ʱ�ػ�
  G_PowerOffCounter = 0;
  return CommandNum;
}


/*
void HART_BusStart(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART���������������ڿ�ʼHARTͨ��ǰ��Ҫ�����߽�������һ��ʱ������ߵĲ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_BusStart()
{  
  HART_BUS_START = 0;
  NOP(5);
  HART_BUS_START = 1;
}
/*
void HART_InfoInit(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ����Ϣ��ʼ�趨������
HART���������Լ�һЩ��ʼ״̬�趨��
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void HART_InfoInit(void)
{
  HART_BusStart();
  //Set Polling mode
  G_ConnectWay = INIT_CONNECT;
  HART_InfoBuffPtrInit();
  //��������ģʽ
  RECEIVE_SEND_EN = RECEIVE_START;
}
/*
void HART_CommandExecuteArrLoad(CommandDef Command,uchar *const CommandIndexCount);
* ������Χ:
Command��HART����š�
CommandIndexCount�����������¼�����������¼ִ���������Ч���������
* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ������ִ��������غ�����
������ִ�������м��뵱ǰҳ����Ҫ���͵�����ţ�ͬʱȷ����ǰҳ�淢�͵����������

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void HART_CommandExecuteArrLoad(CommandDef Command,uchar *const CommandIndexCount)
{
  uint i = 0,Count = 0;
  //����������ͳ�Ƹ���Ϊ�㣬˵���ǶԵ�һ��������м��ز�����
  Count = *CommandIndexCount;
  if(Count == 0)
  {
    Count++;
    //����һ��������ص���ǰҳ������ִ�нṹ�������������
    G_CurrentPageCommandExecuteStructure.CurrentPageCommandBuff[0] = Command;
  }
  else//���ظ�������Ÿ��ǵ�
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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART�ط�״̬�����ú�����
��������Ҫ�����ǽ�HART�Ķ�ʱ�������Լ��ط�״̬�������ָ�����ʼ״̬��

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void HART_ResendFlagReset()
{
    G_FrameGap = 0;
}


/*
void HART_SingleConnectHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HART�������Ӵ������������ǽ���ѯ���ӵ�ַ��Ž����Լӣ�Ȼ����ҳ��任��־������
��ҳ����и��¡�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void HART_SingleConnectHandle()
{
   G_PollingAddress[0]++;
   MENU_PageShowSwitch(TRUE);
}
/*
void HART_SingleConnectFailHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ŵ��ε�ַ����ʧ�ܴ�������
������ε�ַ����ʧ�ܣ�������ѯ��������������ͬʱ��������ѯҳ�洦����������
ǰһ��ҳ�档
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
uchar TopAddr����ѯ��ַ���ޡ�

* ����ֵ˵��:void 
* ���ܽ���:   
��ѯ���޵�ַ��������
�����ѯ����������������ֵ�����˲���TopAddr����Ҫ����
��������ʧ�ܴ�������������ѯҳ���ǰһ��ҳ�档
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
HART_CommandSendTimes:HARTͨ������ʧ�ܺ��ط��Ĵ�����������֤ͨ�ųɹ��ʡ�

HART_CommandIndex��HARTͨ�ŵ�������ţ�
�ɸ��ݸ����ȷ����ǰ���͵�����������ִ���������һλ��

* ����ֵ˵��:void 
* ���ܽ���:   
  HARTͨ�Ž���֡����������
  �����ֹУ������ͨ�Ź�����©��������ɵ�ͨ�Ŵ��󣬽�ʧ�ܵ��������·���������Ρ�
  ������ξ�Ϊ���յ���ȷ��Ӧ�����жϱ���ͨ��ʧ�ܡ�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/


void HART_ReceiveErrHandle()
{     
  //�ط��������ڹ涨ֵ����Ҫ�ύ���󣬲�����������л�׼��
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
         //��ʼ����ʧ��״̬��  
         G_HART_HandleFlag = HART_INIT_ERR;
         MENU_CursorNumReset();
         MENU_VeriableReset();
       }
       else if((G_ConnectWay == COMMON_PAGE_CONNECT)||(G_ConnectWay == WAITING_CONNECT)
               ||(G_ConnectWay == REFRESH))
       {
         G_HART_HandleFlag = HART_COMMON_ERR;
       }
       //��ѯ����3����δ���ӵ��豸����Ҫ�������Ӵ����������������
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
* ������Χ:
HART_CommandIndex��HARTͨ�ŵ�������ţ�

* ����ֵ˵��:void 
* ���ܽ���:   
HART�����ʼ����������
�ú��������ǣ�����ʾҳ���Ϲ��ص�HART�����Ѿ�������ϣ�����������HART����ִ�����飬
ͨ��������������ִ������ĳ�ʼ�����顣
*
* �ؼ���ע��
* - 
�ر�ǿ��һ�£���ʼ������һ�����ڳ�ʼ���ӽ����Լ�Polling����Ż�ʹ�õ���
  
* δ�����:

����ͺ�����Ҫ���뷵��ֵ���Դ�������ҳ�������������������ָ���ûָ���
һ��ָ��Ƕ��ָ������



*/ 


void HART_CommandInitHandle()
{
  PageCommandNumDef CommandNum = NO_COMMAND;

  if(G_CurrentPageCommandExecuteStructure.CurrentCommandIndex <
   G_CurrentPageCommandExecuteStructure.CurrentPageCommandNumber)
  {
    CommandNum = HART_CommandSend(); 
  }
  //��ָ��ֻ����һ�������ҳ�档
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
    //�����ɹ�������
    G_HART_HandleFlag = HART_START_INIT;
    G_FrameGap = RECEIVE_TIME_INTERVAL;
  }
  else
    G_HART_HandleFlag = HART_STANDBY;      
}
/*
void HART_InitCompleteHandle(void );
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ų�ʼ���ɹ���������
�ú����������������豸����豸���ͨ�����Ӻ�
�ӳ�ʼ������ת�������˵�ҳ��Ĵ�����̡�

*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ų�ʼ������������
�ú����������������豸����豸δ���ͨ�����ӵ�����£�
�ӳ�ʼ������ת����������ʾҳ��Ĵ�����̡�

*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void HART_InitErrHandle()
{
  InitialpageHandle();
  MENU_PageShowSwitch(TRUE);
  //G_HART_ResendFlag = HART_STANDBY;
}
/*
static void HART_ReceiveFrameVerify(void );
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  HART���մӻ���Ӧ���ĺ�ʵ������
  ���ձ���ʱ���ܳ���������������ճɹ������ղ��ɹ������Բ��������β��������ɹ���
  ϵͳ��Ҫ��������������ֱ���
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void HART_ReceiveFrameVerify(void )
{
  if(G_RxFrameVerifyFlag == REC_INCORRECT)
  {
    //����֡����ȷ������ǵ���ͨ�ų����쳣����û��������β�������
    HART_ReceiveErrHandle();
  }
  if(G_RxFrameVerifyFlag == REC_STANDBY)
  {
    //��ʼ��HART��������
    if((G_HART_HandleFlag == HART_INIT_COMMAND_HANDLE)||(G_HART_HandleFlag == HART_COMMON_COMMAND_HANDLE))
    {
      //�����������
      HART_CommandInitHandle();
    }
    if((G_HART_HandleFlag == HART_INIT_COMPLETE)||(G_HART_HandleFlag == HART_COMMON_COMPLETE))
    {  
      //��������������
      HART_InitCompleteHandle();      
      HART_CommandSendIndexReset();
    }
  }
  if(G_RxFrameVerifyFlag == REC_ERR)
  {
    //ͨ�����β�����Ȼδ�ܽ�������
    if(G_HART_HandleFlag == HART_INIT_ERR)
    {
      HART_InitErrHandle();
      HART_CommandSendIndexReset();
    }
    else if(G_HART_HandleFlag == HART_COMMON_ERR)
    {
       //��Щ�˵�������Ҫ���η��Ͷ�ȡ������ñ��δ������ε��˵�������ˢ�������
       if(MENU_CurrentPageTypeGet() == MENU_BAR)
       {
       
       }
       else if(G_ConnectWay == REFRESH)
       {
          WaitingErrPageHandle(FALSE);  
       }
       else
       {
          /* ��ת��ͨ�Ŵ�����ʾ����*/
          HART_AbnormalPageHandle(COMMUNICATION_ERR); 
       }
    }
    G_RxFrameVerifyFlag =  REC_STANDBY;
    //��ʱҪ�ر�HARTͨ�ŷ���ͨ�����������������
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
* ������Χ:

* ����ֵ˵��:void 
* ���ܽ���:   
  HART��Ӧ֡���ճ�ʱ�жϺ������涨ʱ����û���յ��ӻ���Ӧ���ģ����һ��ͨ�Ŵ���
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void HART_RespondFrameTimeoutVerify(void )
{
  if((G_FrameGap == 0)&&
       ((G_HART_HandleFlag == HART_START_INIT)
        ||(G_HART_HandleFlag == HART_START_COMMON)))
  {
    /* Report receive incorrect event end */
    //�ɹ���ʧ�ܴ���ͳ��
    SystemSucRateResultStatistis(FALSE);
    //��ʱ�����ͨ�Ŵ���
    G_RxFrameVerifyFlag = REC_INCORRECT;
  }
}
/*
static void HART_RespondFrameReceiveCpltVerify(void );
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  �ӻ���Ӧ���Ľ�������жϺ�����
  ͨ�������жϽ��մӻ������ı��ģ����ֽ����ֽ�֮���ʱ��������50��HARTЭ��涨10ms������ʱ��
  �жϵ�ǰ���Ľ�����ɡ�
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void HART_RespondFrameReceiveCpltVerify(void )
{
  //֡���ս�������
  if((G_BytesGap == 0)&&(FrameHandle == INFO_CODE))
  {
    HART_ReceiveStateReset();
    //���س��̼��豸�ͺ�
    HART_LoadExpandedDeviceType();
    HART_ReceiveSuccessHandle();
  }
}
/*
void HART_CommunicateHandle(uchar *const HART_CommandSendTimes,uchar *const HART_CommandIndex)
* ������Χ:
HART_CommandSendTimes:HARTͨ������ʧ�ܺ��ط��Ĵ�����������֤ͨ�ųɹ��ʡ�

HART_CommandIndex��HARTͨ�ŵ�������ţ�
�ɸ��ݸ����ȷ����ǰ���͵�����������ִ���������һλ��

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�Ŵ�������
����������������HARTͨ��ģ������д�����̣���HARTͨ�ź��������ɣ�
һ������������е��á�

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void HART_CommunicateHandle()
{
  HART_ReceiveFrameVerify();
  HART_RespondFrameTimeoutVerify();
  HART_RespondFrameReceiveCpltVerify();
}
/*
void HART_CommandSendIndexReset(uchar *const HART_CommandSendTimes,uchar *const HART_CommandIndex)
* ������Χ:
HART_CommandSendTimes:HARTͨ������ʧ�ܺ��ط��Ĵ�����������֤ͨ�ųɹ��ʡ�
HART_CommandIndex��HARTͨ�ŵ�������ţ�
�ɸ��ݸ����ȷ����ǰ���͵�����������ִ���������һλ��

* ����ֵ˵��:void 
* ���ܽ���:   
//����ִ������������������㡣 

*
* �ؼ���ע��
* - 

  
* δ�����:




*/ 
void HART_CommandSendIndexReset()
{
   G_CurrentPageCommandExecuteStructure.ResendCounter = 0;
   G_CurrentPageCommandExecuteStructure.CurrentCommandIndex = 0;
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
bool8 HART_AddrCompare()
* ������Χ:


* ����ֵ˵��:bool8 
* ���ܽ���:   
ƥ�䷢��֡�ͽ���֡�ĵ�ַ����֤ͨ�ŵ�׼ȷ�ԡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
bool8 HART_AddrCompare()
{
  uchar i = 0;
  bool8 CompareResult = TRUE;
  //����Ǳ���
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
//�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
TranFloat��Ҫת���ĸ�����
DecimalN����ȷ��С������λ��
ShowDataBuffe��װ��ת���õĸ��������ַ�����
* ����ֵ˵��:����ֵ�����������������ֵ��ֽڸ��� 
* ���ܽ���:   
   �Ѹ�����ת��ASCII
   �����������������Ҫ��ʾС��λ
   ������������������ShowDataBuffe��
*
* �ؼ���ע��
* -
* δ�����: 
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
	{//�������Ǹ���ʱ
            TranFloat = 0-TranFloat;
            ShowDataBuffe[0] = '-';
            i++;
	}
	preValue = (long uint)TranFloat;
	TranFloat = TranFloat-preValue;
	//������������
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
	//����С������
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
	//����˳��,��λ��ǰ
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
              //С����ǰ�������9����ôֱ�ӽ�λ������ѭ��
              if(ShowDataBuffe[TempC] != '9')
              {
                ShowDataBuffe[TempC]++;
                TempC = 0;
              }
              else
              {
                  //���С����ǰ��9����Ҫ��λ���ѵ�ǰ��λ��ֵΪ0
                  if(TempC > 0)
                  {
                    ShowDataBuffe[TempC--] = '0';  
                  }	
                  //�жϵ�ǰ�Ƿ�Ϊ�������λ������ǣ����н�λ��λ�������������һ�ֽ�λ����
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
	ShowDataBuffe[SHOW_DATA_BUF_SIZE] = '\0';//�ַ���������
     return  DecimalP;
}

/*
uchar HART_ReceiveStructVariableAssign(uchar VariableIndex,uchar ValueAddr)
* ������Χ:
VariableIndex��HART�����ڱ����������е���š�
uchar ValueAddr����������


* ����ֵ˵��:������ռ�ֽڸ���
* ���ܽ���:   
���սṹ������Ӧ��ֵ������
������֡�е���ֵ����HART����������Ķ�Ӧ�����С�
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
ASCII_Tag:����ָ�룬ָ�򱣴������Tag���顣
DataLengthDef ReceiveLength��
DataLengthDef ShowDataLength��
uchar *const DataRam��

* ����ֵ˵��:void
* ���ܽ���:   
HART����Tag���뺯����
  ��ΪTag�Ĵ����ʽ��ASCII�������bitλ,������Ҫͨ���ú�����6λASCIIת��Ϊ8λASCII��
*
* �ؼ���ע��
* - 
6λASCII��ת8λASCII�룬ȡ������48��Ҳ��6λASCII������bit��
����i%6Ϊ0ʱ��i��=0����8λASCII����Ǳ��1��6λASCII��������λ���
��i%8�����ƣ������Ϳ��԰�6λ�����е�bit��˳�򱣴浽8λASCII�����С�
  
* δ�����:




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
  //����ֺõ����������8bitASCII
  for(i = 0;i < ShowDataLength;i++)
  {
    ASCII_Tag[i] >>=2;
    //��@ȥ��
    if(ASCII_Tag[i] == 0x00)
    {
      ASCII_Tag[i] = 0x20;
    }
    //�ж�#5bit������󣩣�
    if((ASCII_Tag[i]&0x20) == 0x00)
    {
      ASCII_Tag[i] |=0x40;
    }
    else if((ASCII_Tag[i]&0x20) == 0x20)
    {
      //������
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
* ������Χ:




* ����ֵ˵��:������ռ�ֽڸ���
* ���ܽ���:   
HART�����������͵�ת��
*
* �ؼ���ע��
* - 

  
* δ�����:

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
void HART_PercentileRatio(uchar length,uchar *const Temp);* ������Χ:


* ����ֵ˵��:void
* ���ܽ���:   

*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
uchar *const ASCII_Tag��
DataLengthDef ReceiveLength��
DataLengthDef ShowDataLength��
uchar *const DataRam��

* ����ֵ˵��:void
* ���ܽ���:   
HART TAG���뺯������8λASCII��ת����6λASCII�롣
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:

uchar *const DateStr�����ڻ�������ָ�롣


* ����ֵ˵��:void
* ���ܽ���:   
HART���ڴ�������
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:

uchar *const Month��


* ����ֵ˵��:void
* ���ܽ���:   
�·ݴ�����
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
uchar *const Day

* ����ֵ˵��:void
* ���ܽ���:   
������������
*
* �ؼ���ע��
* - 

  
* δ�����:




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
* ������Χ:
uchar *const Day��



* ����ֵ˵��:void
* ���ܽ���:   
��ݴ�������
*
* �ؼ���ע��
* - 

  
* δ�����:




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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_FloatToData(float FloatData,uchar *const ShowData,DataTypeDef ShowDataType)
* ������Χ:
float FloatData
uchar *const ShowData
DataTypeDef ShowDataType
* ���ܽ���:   
��float������ת���ɷ���֡��ʽ���ĸ��ֽڵ��ַ������ݡ�

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_FloatToData(float FloatData,uchar *const ShowData,DataTypeDef ShowDataType)
* ������Χ:
float FloatData
uchar *const ShowData
DataTypeDef ShowDataType
* ���ܽ���:   
��֡��ʽ����������ת��Ϊ�������������

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* ������Χ:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* ���ܽ���:   
  ��������ת��Ϊ��������

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* ������Χ:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* ���ܽ���:   
  ��������ת��Ϊ��������

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_IntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataType )
* ������Χ:
long uint LongIntData
uchar *const ShowData
DataTypeDef ShowDataType 
* ���ܽ���:   


*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_VariableProtect(ShowData,DataLength);
* ������Χ:
uchar *ShowData������HART����ָ��
DataLengthDef DataLength�� 
* ���ܽ���:   
HART���������������ڱ༭���������������Ҫ���ı�֮ǰ�ı�������������
��ֹ�����ʧ�ܱ��ر�����ʾ����

*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
void HART_ProtectedVariableGet();
* ������Χ:


* ���ܽ���:   
HART����������ȡ������
��д����ģʽ�£�����༭��������л�
*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
uchar HART_FunctionAndUnitArrIndexGet(HART_UnitDef* UnitOrFunctionPtr,uchar Code);
* ������Χ:

* ����ֵ˵��:���ص�λ��������Ӧ���������
* ���ܽ���:   
�����뼰��λ���ݱ�������Ż�ȡ����
ͨ�������������Ը��ݵ�λ���ܴ����ѯ���ַ���Ӧ�������Ӧ����ţ��Ӷ�������ȷ��ʾ��λ�������롣
*
* �ؼ���ע��
* - 

  
* δ�����:
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
//�������ƺͲ����ͷ���ֵ���͡�
uint HART_UnitShowHandle(const HART_UnitDef *Table,char* Variable)
* ������Χ:

* ����ֵ˵��:uint ���ص�λ���ִ������
* ���ܽ���:   
HART������λ��ʾ������
ͨ�����ʽ���ҵ���Ӧ�ĵ�λ��ʾ����
*
* �ؼ���ע��
* - 

  
* δ�����:
������ڵ�λ��������û��װ����ǰ���£�UnintIndex=0xff,˵���������
��Ҫ����
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
//�������ƺͲ����ͷ���ֵ���͡�
bool8 HART_CommandTableIndexGet(CommandDef CommandID,
                   const HART_SendStructDef *const HART_SendVersionStruct,uchar *Command)
* ������Χ:

* ����ֵ˵��:bool8 ���������Ч�ԣ�FALSE�ǷǷ���ţ�TRUE�ǺϷ���š�
* ���ܽ���:   
�������Ų�ѯ������
�������е�HART���������ÿ���汾���ֲ�����ȫ��ʹ�ã����������
������������ڽ�ʡ�ռ�
*
* �ؼ���ע��
* - 
      ��ѯ��ʽ����΢ռ�ü�����Դ����ȫ������Ҳ����255��������Ӱ�첻��
  
* δ�����:
   ���������Ϊ0xff,˵���ǷǷ�ָ��
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
//�������ƺͲ����ͷ���ֵ���͡�
bool8 HART_CommandTableIndexGet(CommandDef CommandID,
                   const HART_SendStructDef *const HART_SendVersionStruct,uchar *Command)
* ������Χ:

* ����ֵ˵��:bool8 ���������Ч�ԣ�FALSE�ǷǷ���ţ�TRUE�ǺϷ���š�
* ���ܽ���:   
�������Ų�ѯ������
�������е�HART���������ÿ���汾���ֲ�����ȫ��ʹ�ã����������
������������ڽ�ʡ�ռ�
*
* �ؼ���ע��
* - 
      ��ѯ��ʽ����΢ռ�ü�����Դ����ȫ������Ҳ����255��������Ӱ�첻��
  
* δ�����:
   ���������Ϊ0xff,˵���ǷǷ�ָ��
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
//�������ƺͲ����ͷ���ֵ���͡�
ProductTypeAndID_Def HART_GetProductTypeAndID();
* ������Χ:

* ����ֵ˵��:ProductTypeAndID_Def,��Ʒʶ��ö�ٶ��壬��Ϊ��ͬ�Ĳ�Ʒ�в�ͬ��
�����̣���ͬ���������в�ͬ�Ĳ�Ʒ���͡�
* ���ܽ���:   
������������ȷ����ǰͨ���豸���������Լ��豸�ͺţ��Ӷ�����ȷ��ʹ��ʲô�����
*
* �ؼ���ע��
* - 
  �豸���ͱ�źͲ˵�����Ż�������ͬ����Ϊͬһ���豸���Ϳ��ܻ�ӵ�в�ͬ�汾Э��
  ����˲˵��������������豸���ͱ��Ҫ�࣬��Ϊ��ͬЭ��汾����ͬ��Ʒ��Ҫ����
  ��ͬ�Ĳ˵�����
  
* δ�����:
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
    //�������80G
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
//�������ƺͲ����ͷ���ֵ���͡�
CommandDef HART_CommandGet(CommandDef Command,MenuTreeIndexDef MenuTreeIndex)
* ������Χ:
�ο�
 CommandDef�� MenuTreeIndexDef���塣
* ����ֵ˵��:
* ���ܽ���:   
����������������ID��ȡ���������е�������ţ���Ϊ��Щ�Զ�������ͬһ������Ÿ�����
���������Բ��ܲ���һ��һƥ�䣬�����Ҫ��������ȷ�Ϸ�������š�
*
* �ؼ���ע��
* - 

  
* δ�����:
  ��ǰ���ǲ˵�Ӧ���������ӵ�pds�ϣ����������Ӻʹ��ǵ�������ǵ����ģ��б�֮����Ҫ
����������
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
        //����һЩд������д�����Ϣ�ǹ̶��ģ������Ҫ�ڴ˽��з�������Ԥ����
        G_CHUAN_YI_VariableDisMode[0] = 0x16;
        CommandID = SIEMENS_WRITE_ROOTING;
        break;
       case CHUAN_YI_TRANSMITTER_TYPE:
        //����һЩд������д�����Ϣ�ǹ̶��ģ������Ҫ�ڴ˽��з�������Ԥ����
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
//�������ƺͲ����ͷ���ֵ���͡�
HART_ReceiveFlag HART_RespondCodeLoad(HART_ReceiveFlag FrameType)
* ������Χ:
HART_ReceiveFlag:LONG_FRAME,SHORT_FRAME
* ����ֵ˵��:
* ���ܽ���:   
HART��Ӧ֡��Ӧ����غ������ֳ�֡��Ӧ��Ͷ�֡��Ӧ�롣
*
* �ؼ���ע��
* - 

  
* δ�����:

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

//�Ѹ�����ת���ַ���
//�����������������Ҫ��ʾС��λ
//������������������ShowDataBuffe��
void	HART_FloatToChar(float TranFloat,unsigned char DecimalN)
{
	unsigned char j = 0;
	unsigned char i = 0;
	unsigned char TempC,CarryFlag = 0;
	unsigned long preValue,currValue;
//	ShowDataBuffe[0]=0;
	if(TranFloat < 0)
	{//�������Ǹ���ʱ
		TranFloat = 0-TranFloat;
		ShowDataBuffe[0] = '-';
		i++;
	}
	TranFloat = TranFloat+0.000008;
	preValue = (unsigned long)TranFloat;
	TranFloat = TranFloat-preValue;
	//������������
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
	//����С������
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
	//����˳��,��λ��ǰ
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
	ShowDataBuffe[6] = '\0';//�ַ���������
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_FrameReceiveHandle()
* ������Χ:

* ����ֵ˵��:
* ���ܽ���:   
HARTͨ��֡�����жϴ�����
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void HART_FrameReceiveHandle()
{
    if(G_HART_ReceiveEN == RECEIVE_START)	
    {                   
        G_FrameReceiveBuff[G_FrameReceiveBuffIndex] = UCA1RXBUF;
        if((G_FrameReceiveBuff[G_FrameReceiveBuffIndex] != LEAD_CODE_VAL)||(FrameHandle == INFO_CODE))
        {
          //����ǰ����
          if((FrameHandle == LEAD_CODE)
                  &&(G_FrameReceiveBuffIndex >= G_NumRegPreams[0]-1)
                     &&((G_FrameReceiveBuff[G_FrameReceiveBuffIndex] == 0x06)
                          ||(G_FrameReceiveBuff[G_FrameReceiveBuffIndex] == 0x86)))
          {
              FrameHandle = INFO_CODE;
              //���ض����
              G_FrameReceiveBuff[0] = G_FrameReceiveBuff[G_FrameReceiveBuffIndex];
              //�жϳ���֡
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
              //������֡���������������㣬��ǰ���븲�ǵ�
              G_FrameReceiveBuffIndex = 0;
          }
          if(FrameHandle == INFO_CODE)
          {
            G_BytesGap = 50;
            if(G_HART_ReceiveFrameType == LONG_FRAME)
            {
              if(G_FrameReceiveBuffIndex == LONG_FRAME_DATA_NUM_INDEX)
              {
                //���㳤֡֡��
                FrameLength = G_FrameReceiveBuff[G_FrameReceiveBuffIndex]+LONG_FRAME_DATA_NUM_INDEX +1;
              }
            }
            if(G_HART_ReceiveFrameType == SHORT_FRAME)
            {
              if(G_FrameReceiveBuffIndex == SHORT_FRAME_DATA_NUM_INDEX)
              {
                //�����֡֡��
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
//֡������ɣ��޸�״̬������λ֡������
void HART_ReceiveStateReset()
{
  G_RxFrameVerifyFlag = REC_COMPLETE;
  FrameHandle = REC_STANDBY;
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void HART_AbnormalStatusHandleModule()
* ������Χ:

* ����ֵ˵��:
* ���ܽ���:   
HARTͨ���쳣״̬����ģ�飬
���ͨ��֡�������ͽ����������������򣬽����쳣��������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void HART_AbnormalStatusHandleModule()
{
  AbnormalStatusDef AbnormalStatus = ABNORMAL_STANDBY;
  //��ȡ�쳣״̬��
  AbnormalStatus = HART_AbnormalStatusHandle();
  if(AbnormalStatus == ABNORMAL_STANDBY)
  {  
    //ˢ�����ݹرռ��ر�����
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
    //���𾯸���治��Ҫ��������ֵ��������Ҫ����������֡�������������
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
    //�쳣״̬����
    HART_AbnormalPageHandle(AbnormalStatus); 
  }
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void	HART_CableLengthReset(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:  
�³�ֵ���㺯����
������ֻ����������Ǳ�˵����������³�������ֵΪ0��
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void	HART_CableLengthReset(void)
{
  MENU_FloatToData(G_PublicVF0,0,FLOAT_T);
}
/*
void HART_DistCalibrateHandle()

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
  �˵����⴦����������ִ�в˵�ҳ���б���ִ�е��ض����㣬
  ���ݲ˵��ṹ�ĸ��ӹ������ȡ�ض������㣬ʹ��������٣�
  �����ڶ��Ʋ�Ʒ��Ŀǰ��������Ǳ�ľ���ϵ��У׼��
���������Ƶġ�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void HART_DistCalibrateHandle()
{
  //У׼ǰ����1
  float HistoryCalibrateValue1;
  //У׼ǰ����2
  float HistoryCalibrateValue2;
  //����ϵ���������
  float RadarRatioCorrect;
  //���ϵ���������
  float RadarZeroCorrect;
  //����ֵ1�������
  float RadarMeasure1;
  //����ֵ2�������
  float RadarMeasure2;
  //ʵ��ֵ1�������
  float RadarReality1;
  //ʵ��ֵ2�������
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
* ������Χ:



* ����ֵ˵��:AbnormalStatusDef�쳣״̬�롣
* ���ܽ���:   
  ���ж��������ȷ�Ϻ�����ͨ����������ȷ�ϴ��������͡�
*
* �ؼ���ע��
* - 

  
* δ�����:

���������Ӧ�ö��д����� ��Ʒʱ�����Ժ�����ӣ�Ŀǰ�õ�ʲô��дʲô��


*/
static AbnormalStatusDef HART_ErrCodeWithSingleDefinitions(uchar RecondCode,AbnormalStatusDef Value)
{
  if(IS_SINGLE_ERROR_RANGE)
  {
    //д�����������ж�
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
* ������Χ:



* ����ֵ˵��:AbnormalStatusDef�쳣״̬�롣
* ���ܽ���:   
  ���ö��������ȷ�Ϻ�����ͨ����������ȷ�ϴ��������͡�
*
* �ؼ���ע��
* - 

  
* δ�����:

���������Ӧ�ö��д����� ��Ʒʱ�����Ժ�����ӣ�Ŀǰ�õ�ʲô��дʲô��


*/

static AbnormalStatusDef HART_ErrCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value)
{
  //�������ô����ж�����Ҫ�����豸���Ҽ��ͺŵ��ж�����Ϊ��ͬ�����в�ͬ�ĸ��ô����ж���
  //Ŀǰ����Ĵ��������������������������޸ġ�
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
        //Incorrect Loop Current Mode or Value,��������
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
* ������Χ:



* ����ֵ˵��:AbnormalStatusDef�쳣״̬�롣
* ���ܽ���:   
  ���ж��徯����ȷ�Ϻ�����ͨ����������ȷ�Ͼ��������͡�
*
* �ؼ���ע��
* - 

  
* δ�����:

���������Ӧ�ö��д����� ��Ʒʱ�����Ժ�����ӣ�Ŀǰ�õ�ʲô��дʲô��


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
* ������Χ:



* ����ֵ˵��:AbnormalStatusDef�쳣״̬�롣
* ���ܽ���:   
  ���ö��徯����ȷ�Ϻ�����ͨ����������ȷ�Ͼ��������͡�
*
* �ؼ���ע��
* - 

  
* δ�����:

���������Ӧ�ö��д����� ��Ʒʱ�����Ժ�����ӣ�Ŀǰ�õ�ʲô��дʲô��


*/
static AbnormalStatusDef HART_WarningCodeWithMultipleDefinitions(uchar RecondCode,CommandDef ExecutingCommand,AbnormalStatusDef Value)
{
  //�������ô����ж�����Ҫ�����豸���Ҽ��ͺŵ��ж�����Ϊ��ͬ�����в�ͬ�ĸ��ô����ж���
  //Ŀǰ����Ĵ��������������������������޸ġ�
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
* ������Χ:



* ����ֵ˵��:AbnormalStatusDef�쳣״̬�롣
* ���ܽ���:   
  ��λ������´���һЩ��λѡ�����ȷ��ʱ����ͨ��������������ֵ���¡�
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void HART_UnitTempLoad(DataTypeDef DataType,bool8 IsVariableHandle,uchar *ShowData)
{
  if((DataType == FUNC_CODE_T)&&(IsVariableHandle == TRUE))
  {
    ShowData[0] = G_UnitTemp[0];
  }
}