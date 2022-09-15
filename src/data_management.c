/**
  ******************************************************************************
  * @file    data_management.c
  * @author  LIU BO
  * @version V3.5.0
  * @date    2017.4.12
  * @brief   data_management module
  ******************************************************************************
  * @description
  *
  * ��Ŀ���ܣ�ͨ��Modbus���״�Һλ�ƺͶ���¶ȼ�ͨ�ţ�����������ת��ΪBPM���ݱ���
  * �ڻ��������ȴ�BPM������ѯ�����ӵ�������ѯ֡������뱾�豸��ַƥ�䣬�򽫻�����
  * �ݷ��͸�BPM������
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */ 
#include "data_management.h"//����
//#include "alarm.h"
#include "data_range_list.h"



#define COMPARE for(i = 0; i < Length;i++) \
      {                                   \
        if(*(p1+i) != *(p2+i))            \
        {                                 \
          return FALSE;                   \
        }                                 \
      }                                   

//�¼��������ҵ�ַ
#define EVENT_PROTECT_CHAR_GROUP_READ 0x00
#define EVENT_PROTECT_CHAR_GROUP_WRITE 0x01
#define EVENT_PROTECT_CHAR_WRITE_RESULT_FEEDBACK 0x02
#define EVENT_PROTECT_CHAR_PARAM_WRITE 0x03
#define EVENT_PROTECT_CHAR_BUFF_INIT 0x04
#define EVENT_PROTECT_CHAR_ROUTING_CHECK 0x05
#define EVENT_PROTECT_CHAR_GROUP_GENERATE 0x06
#define EVENT_PROTECT_CHAR_GROUP_RESTORE 0x07
#define EVENT_PROTECT_CHAR_SAVE_WRITE 0x08
#define EVENT_PROTECT_CHAR_SAVE_READ 0x09



//RAM������
#define EVENT_RAM_ORIGINAL_DATA_CHANGE_ERR 0x07
#define EVENT_RAM_REVERSE_DATA_CHANGE_ERR 0x08
#define EVENT_RAM_XOR_DATA_CHANGE_ERR 0x09
#define EVENT_RAM_ALL_DATA_CHANGE_ERR 0x0a
#define EVENT_RAM_WRITE_PAR_ERR 0x0b
#define EVENT_RAM_WRITING_CONFIRM_ERR 0x0c
#define EVENT_RAM_INIT_ERR 0x0d
#define EVENT_RAM_DATA_BUFF_FULL 0x0e

//д�벻�ɹ�ʱ���涨�ظ�д�Ĵ���
#define REPETITIVE_WRITING_TIMES 3

//�ճ���ѯÿ�β�ѯ����
#define ROUTING_CHECK_TIMES 10

//�������������
#define XOR_MARK_CHAR 0XAA
//�������������
#define XOR_MARK_INT 0XAAAAAAAA

//�¼��ļ����ҵ�ַ
#define PROTECT_FILE 0x07

typedef struct
{
  uchar8 CurrentCapcity;
  uchar8 *SourceCodePtr;
  uchar8 *SecondCodePtr;
  uchar8 *ThirdCodePtr;
}CharParamStructDef;
typedef struct
{
  uchar8 CurrentCapcity;
  uint32 *SourceCodePtr;
  uint32 *SecondCodePtr;
  uint32 *ThirdCodePtr;  
}IntParamStructDef;
typedef struct
{
  uchar8 CurrentCapcity;
  uint32 *SourceCodePtr;
  uint32 *SecondCodePtr;
  uint32 *ThirdCodePtr;    
}FloatParamStructDef;


typedef enum
{
  NO_PAR_ERR,        // ��ȡ���Ϊ�޴��� 
  ORIGINAL_PAR_ERR,  // ��ȡ���Ϊԭ�뷢��ʧ��
  REVERS_PAR_ERR,    // ��ȡ���Ϊ���뷢��ʧ��
  XOR_PAR_ERR,       // ��ȡ���Ϊ����뷢��ʧ��
  ALL_PAR_ERR        // ��ȡ���Ϊ���в�����ʧ��
}ReadResultDef;

CharParamStructDef CharParamStructure = {0};
IntParamStructDef IntParamStructure = {0};
FloatParamStructDef FloatParamStructure = {0};


static Bool PROTECT_ParamSafeWrite(void*const Param,
                                              uint16 Index,DataTypeDef DataType);
static Bool PROTECT_ParamSafeRead(void*const Param, uint16 Index,DataTypeDef DataType);
static void PROTECT_ParamGroupCreate(void* const Param,void *const arr,DataTypeDef DataType);
static Bool PROTECT_ParamRewrite(void *const ParamGroup,
                                              uint16 Index,DataTypeDef DataType);
static Bool PROTECT_ParamWritingConfirm(void*const arr,
                                             uint16 Index,DataTypeDef DataType);
static void PROTECT_ParamGroupWrite(void*const buff,
                                        uint16 index,DataTypeDef DataType);
static void PROTECT_ParamGroupRead(void*const GroupReceive,
                                      uint16 Index,DataTypeDef DataType);
static Bool PROTECT_GroupWriteResultCheck(void*const ptr1,
                                           void*const ptr2,DataTypeDef DataType);
static ReadResultDef PROTECT_ParamGroupCheck(void*const GroupRestore,
                                 void *const EffectiveValue,DataTypeDef DataType);
static void PROTECT_ParamGroupDecode(void*const GroupReceive,
                                           void*const GroupRestore,DataTypeDef DataType);
static Bool PROTECT_ParamModifyResult(void*const Param, uint16 Index,DataTypeDef DataType);
static void PROTECT_ParamGroupErrResult(ReadResultDef ParamResult,uint16 Index,DataTypeDef DataType);





//���Ժ���ר��ȫ�ֱ���
static uchar8 G_GroupChangeFlag = FALSE;

/**
 //�������ƺͲ����ͷ���ֵ���͡�
 Bool PROTECT_ParamReadAndWrite(void* Param,uint16 Index,
                                    DataTypeDef DataType,ParamReadWriteDef RW_Status)
* ������Χ: 
  void* Param��ָ�򱻱���������void*ָ�롣�����������Ҫд�뵽�����������ò�����Ҳ������
  Ҫת��Ҫ����ȡ�����ò����ĵ�ַ��������� ��RW_Status�������ж���
  ������������������������ͣ�������char�ͣ�int�ͻ�����float�ͣ�������ʲô���Ϳ��Ը��ݱ�
  ����DataType�����ж�����Ϊ���������ͣ����Է�Χ������unsigned char�ķ�Χ��Ҳ�п���������
  �������͵ķ�Χ��
  
  Index���������ݱ������ľ���λ�ã���Χ0-65535
  
  DataType��typedef enum{UCHAR,UINT,FLOAT}DataTypeDef


* ����ֵ˵��:����ֵBool����ֵ���ж϶�ȡ��д���Ƿ�ɹ� 
* ���ܽ���:   
   ��������Ϊģ��ʹ�����ṩ��һ������������д����ȡ�Ľӿڣ�ʹ���߿��Ը��ݽӿڲ���������
  ��ͬ�����ɱ�����������д�룬��ȡ������
*
* �ؼ���ע��
* -
  
* δ�����: 
* 
*/


Bool PROTECT_ParamRead(void*const Param,uint16 Index,
                                    DataTypeDef DataType)
{
  Bool ReadResult;
  uchar8 *Pchar = Param;
  uint32 *Pint = Param;
  uint32 FloatValue;
  float *Pfloat = Param;
  
  union FloatToInt
  {
    uint32 IntData;
    float  FloatData;
  }FloatParamData;

  switch(DataType)
  {
    case UCHAR:
        ReadResult = PROTECT_ParamSafeRead(Pchar,Index,DataType);
        if(ReadResult == FALSE)
        {
          return FALSE;
        }
      break;
    case UINT:
        ReadResult = PROTECT_ParamSafeRead(Pint,Index,DataType);
        if(ReadResult == FALSE)
        {
          return FALSE;
        }
      break;
    case FLOAT:
        ReadResult = PROTECT_ParamSafeRead(&FloatValue,Index,DataType);
        FloatParamData.IntData = FloatValue;
        *Pfloat = FloatParamData.FloatData;
        if(ReadResult == FALSE)
        {
          return FALSE;
        }
      break;
    default:
      //event report
      break;
  }
  
    return TRUE;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
 Bool PROTECT_ParamReadAndWrite(void* Param,uint16 Index,
                                    DataTypeDef DataType,ParamReadWriteDef RW_Status)
* ������Χ: 
  void* Param��ָ�򱻱���������void*ָ�롣�����������Ҫд�뵽�����������ò�����Ҳ������
  Ҫת��Ҫ����ȡ�����ò����ĵ�ַ��������� ��RW_Status�������ж���
  ������������������������ͣ�������char�ͣ�int�ͻ�����float�ͣ�������ʲô���Ϳ��Ը��ݱ�
  ����DataType�����ж�����Ϊ���������ͣ����Է�Χ������unsigned char�ķ�Χ��Ҳ�п���������
  �������͵ķ�Χ��
  
  Index���������ݱ������ľ���λ�ã���Χ0-65535
  
  DataType��typedef enum{UCHAR,UINT,FLOAT}DataTypeDef


* ����ֵ˵��:����ֵBool����ֵ���ж϶�ȡ��д���Ƿ�ɹ� 
* ���ܽ���:   
   ��������Ϊģ��ʹ�����ṩ��һ������������д����ȡ�Ľӿڣ�ʹ���߿��Ը��ݽӿڲ���������
  ��ͬ�����ɱ�����������д�룬��ȡ������
*
* �ؼ���ע��
* -
  
* δ�����: 
* 
*/
Bool PROTECT_ParamWrite(void*const Param,uint16 Index,
                                    DataTypeDef DataType)
{
  Bool WriteResult;
  uchar8 *Pchar = Param;
  uint32 *Pint = Param;
  float *Pfloat = Param;
  
  union FloatToInt
  {
    uint32 IntData;
    float  FloatData;
  }FloatParamData;

  switch(DataType)
  {
    case UCHAR:
        WriteResult = PROTECT_ParamSafeWrite(Pchar,Index,DataType);
        if(WriteResult == FALSE)
        {
           return FALSE;
        }
      
      break;
    case UINT:
        WriteResult = PROTECT_ParamSafeWrite(Pint,Index,DataType);
        if(WriteResult == FALSE)
        {
           return FALSE;
        }
      
      break;
    case FLOAT:      
        FloatParamData.FloatData = *Pfloat;
        WriteResult = PROTECT_ParamSafeWrite(&FloatParamData,Index,DataType);
        if(WriteResult == FALSE)
        {
           return FALSE;
        }
      
      break;
    default:
      //event report
      break;
  }
  
    return TRUE;
}

Bool PROTECT_CharParamWrite(uchar*const Param,uint16 Index,
                                    DataTypeDef DataType)
{

  return TRUE;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_CharGroupWriteArrayCompare(uchar8 const*const ptr1,
                                        uchar8 const*const ptr2��uchar8 Length);
* ������Χ: 
*ptr1:�Ƚ�����1�������СPARAM_GROUP_BUFF_SIZE��
*ptr2:�Ƚ�����2�������СPARAM_GROUP_BUFF_SIZE��
Length���Ƚ����鳤�ȣ�С��PARAM_GROUP_BUFF_SIZE��
* ����ֵ˵��:����ֵ��ʾ���������Ƿ���ȫ��ͬ�������ȫ��ͬ����TRUE������ͬFALSE 
* ���ܽ���:   
  ���������ǣ����������ڹ涨�ĳ������Ƿ���ȫ��ͬ�� 
*
* �ؼ���ע��
* - COMPARE ����ͨ���궨�彫�ظ�ʹ�õĴ�������� 
* δ�����: 
* 
*/

static Bool PROTECT_GroupWriteArrayCompare(void*const ptr1,void*const ptr2,
                                               uchar8 Length,DataTypeDef DataType)
{
    uchar8 i;
    
    if(DataType == UCHAR)
    {
      uchar8 *p1 = ptr1,*p2 = ptr2;
      COMPARE ;
      
    }
    else if(DataType == UINT)
    {
      uint32 *p1 = ptr1,*p2 = ptr2;
      COMPARE;
    }
    else if(DataType == FLOAT)
    {
      uint32 *p1 = ptr1,*p2 = ptr2;
      COMPARE;
    }
    return TRUE;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void PROTECT_CharCharParamBuffInit();
* ������Χ: 

.

* ����ֵ˵��:�Ƿ��ʼ���ɹ��� 
* ���ܽ���:   
   ����������˵��������ա�
*
* �ؼ���ע��
* -  �ⲿ�ӿڣ�����������ݱ�������
* δ�����: 
* 
* 
* 
*/
//
void PROTECT_ParamBuffInit(void)
{
  uchar8 i,CharInitValue = 0;
  uint32 IntInitValue = 0;
  for( i = 0;i <  RAM_DATA_SIZE;i++)
  {
    PROTECT_ParamSafeWrite((void*)&CharInitValue,i,UCHAR);
    PROTECT_ParamSafeWrite((void*)&IntInitValue,i,UINT);
    PROTECT_ParamSafeWrite((void*)&IntInitValue,i,FLOAT);
  }
}



/**
 //�������ƺͲ����ͷ���ֵ���͡�
void PROTECT_CharParamRoutingcheck(void );
* ������Χ: 

.

* ����ֵ˵��: 
* ���ܽ���:   
  �������ճ���飬�Ա������б����ÿһ���������м��޲��飬�緢����ȡ�����󼴿��޸ĺ��ύ
  �ͼ��¼�������޸����ɹ���Ҫ�ύ�߼��¼��������������ȫ���ύ�ߵȼ��¼�֪ͨ��Ʒ�û�
  �������ò�����
*
* �ؼ���ע��
* - 
  ROUTING_CHECK_TIMES����ʾÿ�ε����ճ���麯��ʱ��Ҫ�Ա��������м��ĳ��ȡ�����������
  �����ݹ��������еĲ�����������ROUTING_CHECK_TIMESʱ�����Էֶ��������ݱ��������м�飬
  ���Խ�ʡ��Դ��
  j��ʾ�ճ�����������CharBuffStructure.RamBuffTop��Ŀǰ���ݹ��������б���ľ������
  ��������j�ﵽ�������ʱ��ÿ���ж�jǰ����ִ��j++�����ͻ��Զ����㣬��������ѭ����˵����
  ����ɡ�
  ��j���������������������ʱ�����б�������j���㣬����ѭ�������־����ȼ������ߡ�
* δ�����: 
* 
*/
void PROTECT_ParamRoutingcheck(void )
{
  uint16 i;
  static uint16 j = 0;
  uint32 Param = 0;
  //����static  �ֶμ��

 
  for(i=0 ;i < ROUTING_CHECK_TIMES ;i++,j++)   
  {
    if(j >= RAM_DATA_SIZE)
    {
      if(j > RAM_DATA_SIZE)
      {
#ifdef EVENT_TEST        
        EventReport(EVENT_SOFTWARE_ERROR_TYPE, EVENT_MCU_SOURCE, EVENT_VALUE_OUT_OF_BORDER,
                    EVENT_DANGEROUS_LEVEL3, EVENT_PROTECT_CHAR_ROUTING_CHECK, PROTECT_FILE);
#endif      
      }
      j = 0;
      break;
    }
    //PROTECT_CharParamSafeRead(&Param,j);
    PROTECT_ParamSafeRead((void*)&Param,j,UCHAR);
    PROTECT_ParamSafeRead((void*)&Param,j,UINT);
    PROTECT_ParamSafeRead((void*)&Param,j,FLOAT);
  }
}




 /**
 //�������ƺͲ����ͷ���ֵ���͡�
static void PROTECT_IntParamGroupDecode(uint32 const *GroupReceive,
                                                      uint32 const *GroupRestore);
* ������Χ: 
*GroupReceive�����������ݶ�ȡװ�������׵�ַ�������СPARAM_GROUP_BUFF_SIZE��
*GroupRestore��װ�ػ�ԭ������� �������СPARAM_GROUP_BUFF_SIZE��

* ����ֵ˵��: 
* ���ܽ���:   
  ������Ҳ���ڲ��ӿڣ���Ҫ�����ǽ������GroupReceive[]�ж�ȡ�Ա�����������,��ԭ������ԭ�룬
  �������GroupRestore[]�����д��ء� 
*
* �ؼ���ע��
* -  
* δ�����: 
* 
*/
static void PROTECT_ParamGroupDecode(void*const GroupReceive,
                                           void*const GroupRestore,DataTypeDef DataType)
{
  uchar8 *CharGroupReceive = GroupReceive,*CharGroupRestore = GroupRestore;
  uint32 *IntGroupReceive = GroupReceive, *IntGroupRestore = GroupRestore;
  
  if(DataType == UCHAR)
  {
    *CharGroupRestore = *CharGroupReceive;
    *(CharGroupRestore+1) = ~(*(CharGroupReceive+1));
    *(CharGroupRestore+2) = (*(CharGroupReceive+2))^XOR_MARK_CHAR;
  }
  else  if((DataType == FLOAT)||(DataType == UINT))
  {
    *IntGroupRestore = *IntGroupReceive;
    *(IntGroupRestore+1) = ~(*(IntGroupReceive+1));
    *(IntGroupRestore+2) = (*(IntGroupReceive+2))^XOR_MARK_INT;
  }
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_IntGroupWriteResultCheck(uint32 const*const GroupBuff,  
                                                        uint32 const*const GroupReceive)
* ������Χ: 
GroupBuff[]:�����뺯�����ɵ��������飬�����СPARAM_GROUP_BUFF_SIZE��
GroupReceive[]:�Ƕ�ȡ������ȡ��д�뱣�����е��������飬�����СDATA_PROTECT_BUFF_SIZE��
.

* ����ֵ˵��:�����Ƿ�˶Գɹ����������������ȫ��ͬ���򷵻�TRUE����֮����FALSE�� 
* ���ܽ���:   
 ����������������бȽϣ��Ƿ���ȫһ���������һ������FALSE��һ���ͷ���TRUE��  
*
* �ؼ���ע��
* -  
* δ�����: 
* 
*/                   
 //ptr ͳһһ��
static Bool PROTECT_GroupWriteResultCheck(void*const GroupBuff,  
                                      void*const GroupReceive,DataTypeDef DataType)
{
  if(PROTECT_GroupWriteArrayCompare((void*)GroupBuff,(void*)GroupReceive,PARAM_GROUP_BUFF_SIZE,DataType)
                                                                        == FALSE)
  {
     return FALSE; 
  }
  else
  return TRUE;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static ReadResultDef PROTECT_IntParamGroupCheck(uint32 const * const GroupRestore,
                                                        uint32 *const EffectiveValue);
* ������Χ: 
* GroupRestore��װ�ػ�ԭ������� �������СPARAM_GROUP_BUFF_SIZE��
* EffectiveValue��������Чֵ��ָ�롣

* ����ֵ˵��:
Typedef enum//ö��
{
  NO_PAR_ERR,
  ORIGINAL_PAR_ERR,
  REVERS_PAR_ERR,
  XOR_PAR_ERR,
  ALL_PAR_ERR
}ReadResultDef;
 ����ֵ���ò�������˵����Чֵ�Ƿ���Ч��ҲΪ�¼�ϵͳָ���������е���һ���뷢���˱仯��
* ���ܽ���:   
  ����ԭ�������е�����ԭ����л���ȶԣ������Ƿ���ͬ������ʲô���Ĳ�ͬ 
*
* �ؼ���ע��
* -
��Ҫǿ��һ�£����������* EffectiveValue�����ݵ���Чֵ�Ǹ��ݷ���ֵ�����Ƿ���Ч�ģ�
����˵�������ݱ������з���洢�����쳣�����Ƿ���REVERS_PAR_ERR����Ϊһ�������쳣�ǲ�Ӱ��
��Чֵ����Ч�ԣ�����*EffectiveValue���ص���ֵ�ǿ��Ա�ʹ�õġ�����������ݱ�������ԭ�룬
���������붼�����쳣���ͻ᷵��ALL_PAR_ERR����ͱ�ʾ��������Ѿ�����ʧ�棬���Է��ص�
*EffectiveValueҲ����Ч�ģ����ɱ�ʹ�á���Ȼ�������붼��ȷ��ʱ�򣬴��ص���Чֵ��Ȼ����Ч�ġ� 
* δ�����: 
* 
*/
static ReadResultDef PROTECT_ParamGroupCheck(void*const GroupRestore,
                                 void*const EffectiveValue,DataTypeDef DataType)
{
  ReadResultDef  a = NO_PAR_ERR;
  
  uchar8 *CharGroupRestore = GroupRestore,*CharValue = EffectiveValue;
  uint32 *IntGroupRestore = GroupRestore,*IntValue = EffectiveValue;
  
  
  if(DataType == UCHAR)
  {
    if(CharGroupRestore[0] == CharGroupRestore[1])
    {
       if(CharGroupRestore[1] == CharGroupRestore[2])
       {
         a = NO_PAR_ERR;
       }
       else
       {
         a = XOR_PAR_ERR;
       }
       *CharValue = CharGroupRestore[0];  
    }
    else if(CharGroupRestore[0] == CharGroupRestore[2])
    {
      a = REVERS_PAR_ERR;
      *CharValue = CharGroupRestore[0];
    }
    else if(CharGroupRestore[1] == CharGroupRestore[2])
    {
      a = ORIGINAL_PAR_ERR;
      *CharValue = CharGroupRestore[1];
    }
    else
    {
      a = ALL_PAR_ERR;
    }
  }
  else  if((DataType == FLOAT)||(DataType == UINT))
  {
        if(IntGroupRestore[0] == IntGroupRestore[1])
    {
       if(IntGroupRestore[1] == IntGroupRestore[2])
       {
         a = NO_PAR_ERR;
       }
       else
       {
         a = XOR_PAR_ERR;
       }
       *IntValue = IntGroupRestore[0];  
    }
    else if(IntGroupRestore[0] == IntGroupRestore[2])
    {
      a = REVERS_PAR_ERR;
      *IntValue = IntGroupRestore[0];
    }
    else if(IntGroupRestore[1] == IntGroupRestore[2])
    {
      a = ORIGINAL_PAR_ERR;
      *IntValue = IntGroupRestore[1];
    }
    else
    {
      a = ALL_PAR_ERR;
    }
  }
  
  return a;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void PROTECT_IntParamGroupRead(uint32 *const GroupReceive,uint16 Index);
* ������Χ: 
*GroupReceive�����������ݶ�ȡװ�������׵�ַ�������СPARAM_GROUP_BUFF_SIZE��

Index���Ǳ������Ĳ�����ַ��Ҫ�Ѳ��������ĸ�λ�ö����������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��

* ����ֵ˵��:
* ���ܽ���:   
  ��ȡ�����ڱ�������������룬װ��GroupReceive[]�����С��ڱ�������Indexλ����ȡ���ݡ� 
*
* �ؼ���ע��
* -  
* δ�����: 
* 
*/
static void PROTECT_ParamGroupRead(void*const GroupReceive,
                                      uint16 Index,DataTypeDef DataType)
{
  uchar8 i;
  uchar8 *CharGroupReceive = GroupReceive;
  uint32 *IntGroupReceive = GroupReceive,*FloatGroupReceive = GroupReceive;
  
  
  
  for(i = 0; i < PARAM_GROUP_BUFF_SIZE; i++)
  {
    if(DataType == UINT)
    {
      IntGroupReceive[i] =  G_PROTECT_IntParamBuff[Index][i];
    }
    else if(DataType == FLOAT)
    {
      FloatGroupReceive[i] =  G_PROTECT_FloatParamBuff[Index][i];
    }
    else if(DataType == UCHAR)
    {
      CharGroupReceive[i] = G_PROTECT_CharParamBuff[Index][i];
    }
  }    
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void PROTECT_IntParamGroupWrite(uint32 const *GroupBuff,uint16 Index);
* ������Χ: 
*GroupBuff�����������ɺ����ṩ�����������׵�ַ�������СPARAM_GROUP_BUFF_SIZE��


Index���Ǳ������Ĳ�����ַ��Ҫ�Ѳ��������ĸ�λ�ö����������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��.

* ����ֵ˵��: 
* ���ܽ���:   
  ͨ��������������󣬿ɽ����ɵ�����д�ڱ�������Index��ָ����λ���ϡ� 
*
* �ؼ���ע��
* -  
* δ�����: 
* 
*/
static void PROTECT_ParamGroupWrite(void*const GroupBuff,
                                       uint16 Index,DataTypeDef DataType)//ͳһ����
{
  uchar8 i;
  uchar8 *CharGroupBuff = GroupBuff;
  uint32 *IntGroupBuff = GroupBuff,*FloatGroupBuff = GroupBuff;
  //һ���������������������顣��������ͨ����ע˵��
 
  for(i = 0; i<PARAM_GROUP_BUFF_SIZE; i++)
  {
    
    if(DataType == UINT)
    {
      G_PROTECT_IntParamBuff[Index][i] = *(IntGroupBuff+i);
    }
    else if(DataType == FLOAT)
    {
      G_PROTECT_FloatParamBuff[Index][i] = *(FloatGroupBuff+i);
    }
    else if(DataType == UCHAR)
    {
      G_PROTECT_CharParamBuff[Index][i] = *(CharGroupBuff+i);
    }
  }    

}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_IntParamWritingConfirm(uint32 const*const GroupBuff,uint16 Index);
* ������Χ: 
GroupBuff[]:�������������ɵ��������顣
Index�����ݱ������ĵ�ַ��

* ����ֵ˵��: 
* ���ܽ���:   
  ����������ͨ��������д�뺯��д�뵽���ݱ�������,
  Ȼ��ͨ��������������ȡ��������д�뵽�������в����������,
  �ٵ���д�����ݺ˶Ժ���������������GroupBuff[]�Ͷ�ȡ����������
  GroupReceive[]��Ϊ�������к˶�ȷ�ϡ�
*
* �ؼ���ע��
* -  
  ����Ҫǿ��һ�£������һ�ξ�д��ɹ�����Ϊ����д�룬
  ����Ҫ�ύ�¼�������һ�Σ���������������޴�����Ϊ��ȼ��¼�������ﵽ������޴�����
  ���Ϊ�ߵȼ��¼���
* δ�����: 
* 
*/
static Bool PROTECT_ParamWritingConfirm(void*const GroupBuff,
                                           uint16 Index,DataTypeDef DataType)
{
  uint32 IntGroupReceive[PARAM_GROUP_BUFF_SIZE];
  uchar8 CharGroupReceive[PARAM_GROUP_BUFF_SIZE];
  uchar8 *CharGroupBuff = GroupBuff;
  uint32 *IntGroupBuff =  GroupBuff;
  Bool Result = TRUE;
  if(DataType == UCHAR)
  {
    PROTECT_ParamGroupWrite((void*)CharGroupBuff,Index,DataType);    
#ifdef DATA_MANAGEMENT_WRITE_ERR_TEST_BLOCK
    uchar8 CharTestGroup[] = {1,2,3};
    PROTECT_ParamGroupWrite((void*)CharTestGroup,Index,DataType);
#endif
    PROTECT_ParamGroupRead((void*)CharGroupReceive,Index,DataType);
    Result = PROTECT_GroupWriteResultCheck((void*)CharGroupBuff,
                                          (void*)CharGroupReceive,DataType);
  }
  else  if((DataType == FLOAT)||(DataType == UINT))
  {
    PROTECT_ParamGroupWrite((void*)IntGroupBuff,Index,DataType);
    PROTECT_ParamGroupRead((void*)IntGroupReceive,Index,DataType);
    Result = PROTECT_GroupWriteResultCheck((void*)IntGroupBuff,
                                          (void*)IntGroupReceive,DataType);
  }
  if(Result == TRUE)
  {
    return TRUE;
  }
  return FALSE;
}


/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_IntParamRewrite(uint32 const *ParamGroup,uint16 Index)
* ������Χ: 
*buff�����������ɺ����ṩ�����������׵�ַ�������СPARAM_GROUP_BUFF_SIZE��


Index���Ǳ������Ĳ�����ַ��Ҫ�Ѳ��������ĸ�λ�ö����������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��.

* ����ֵ˵��:����ֵ��ʾ�����Ƿ�д��ɹ�������ɹ�����TRUE,ʧ�ܷ���FALSE. 
* ���ܽ���:   
  ͨ��������������󣬿ɽ����ɵ�����д�ڱ�������Index��ָ����λ���ϡ�
  ���а���д��ȷ�Ϲ��ܡ�
*
* �ؼ���ע��
* -  
* δ�����: 
* 
*/

static Bool PROTECT_ParamRewrite(void *const ParamGroup,
                                    uint16 Index,DataTypeDef DataType)
{
  uchar8 i;
  uchar8 *CharParamGroup = ParamGroup;
  uint32 *IntParamGroup = ParamGroup;
  Bool ConfirmFeedback = TRUE;
  
  if(DataType == UCHAR)
  { 
    ConfirmFeedback  = PROTECT_ParamWritingConfirm((void*)CharParamGroup,Index,DataType);
  }
  else  if((DataType == FLOAT)||(DataType == UINT))
  {
    ConfirmFeedback  = PROTECT_ParamWritingConfirm((void*)IntParamGroup,Index,DataType);
  }
  
  if(ConfirmFeedback == TRUE)
  {
     return TRUE;
  } 
  else if(ConfirmFeedback == FALSE)
   {
      for(i = 0;i < REPETITIVE_WRITING_TIMES;i++) 
      {
          if(DataType == UCHAR)
          { 
            ConfirmFeedback  = PROTECT_ParamWritingConfirm((void*)CharParamGroup,Index,DataType);
            if(ConfirmFeedback == TRUE)
            {
#ifdef EVENT_TEST
              //event report low level
              EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITING_CONFIRM_ERR,
                                                    EVENT_DANGEROUS_LEVEL5,UINT,Index);
#endif
              return TRUE;
            }
           }
           else  if((DataType == FLOAT)||(DataType == UINT))
           {
              ConfirmFeedback  = PROTECT_ParamWritingConfirm((void*)IntParamGroup,Index,DataType);
              if(ConfirmFeedback == TRUE)
              {
                if(DataType == UINT)
                {
#ifdef EVENT_TEST
                  //event report low level
                  EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITING_CONFIRM_ERR,
                                                        EVENT_DANGEROUS_LEVEL5,UINT,Index);
#endif
                }
                else
                {
#ifdef EVENT_TEST
                  //event report low level
                  EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITING_CONFIRM_ERR,
                                                        EVENT_DANGEROUS_LEVEL5,FLOAT,Index);
#endif
                }
                return TRUE;
              }
           }
       }      
   }
   return FALSE;
}



/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void PROTECT_IntParamGroupCreate(uint32 Param,uint32 *const arr);
* ������Χ: 
 Param��Ҫ�趨�Ĳ���ֵ����Χ��uint.
 *arr��װ�ز�������������׵�ַ�������СPARAM_GROUP_BUFF_SIZE��
* ����ֵ˵��:����ֵ�������Ƿ����ɳɹ��ı�־�� 
* ���ܽ���:   
  �Բ�Ʒ���趨����Ϊģ�壬���ɷ��������룬��������arr[]������ 
*
* �ؼ���ע��
* - �����������Ҫһ�����λXOR_MARK��������������Ҫʹ�õ�����롣 
* δ�����: 
* 
*/
static void PROTECT_ParamGroupCreate(void* const Param,
                                            void*const arr,DataTypeDef DataType)
{
  uchar8 *CharParam = Param,*CharArr = arr;
  uint32 *IntParam = Param,*IntArr = arr;
  
  if(DataType == UCHAR)
  {
    *CharArr = *CharParam;
    *(CharArr+1) = ~(*CharParam);
    *(CharArr+2) = (*CharParam)^XOR_MARK_CHAR;
  }
  else  if((DataType == FLOAT)||(DataType == UINT))
  {
    *IntArr = *IntParam;
    *(IntArr+1) = ~(*IntParam);
    *(IntArr+2) = (*IntParam)^XOR_MARK_INT;
  }
}



/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_IntParamSafeWrite(uint32 Param,uint16 Index)
* ������Χ: 
Param:Ҫ��д�뱣�����Ĳ�������Χ��uint.

Index���Ǳ������Ĳ�����ַ��Ҫ�Ѳ��������ĸ�λ�ö����������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��
.

* ����ֵ˵��:
Bool �ͷ���ֵ������TRUE��ʾ�������������سɹ�������FALSE��ʾ��������������ʧ�ܡ�
* ���ܽ���:   
  ������Ϊģ�����ӿڣ����ṩ��ʹ��ģ��ĳ��������Ա�������ԱֻҪ�ṩҪ�趨��
  ����ֵ���Լ�Ҫд�뱣������λ�þͿ�����ɲ�������������
*
* �ؼ���ע��
* -  �������ֵ��ʾ����ʧ�ܣ�����Ҫ�ύ�¼�����ʾ��Ʒ�û������趨���߹��ϼ��ޡ�
* 

δ�����: 
*   ���д��ʧ�ܺ󣬿���ѡ��д���Σ�����ڸ�д�����гɹ����ύһ���ȼ��ϵ͵��¼�
  ����ﵽ��д�������޺���ȻΪ�ɹ�������Ҫ�ύһ���ߵȼ��¼�����ʾ��Ʒ�û�����
*/
static Bool PROTECT_ParamSafeWrite(void*const Param,uint16 Index,DataTypeDef DataType)
{
  uint32 IntParamGroup[PARAM_GROUP_BUFF_SIZE] = {0};
  uchar8 CharParamGroup[PARAM_GROUP_BUFF_SIZE] = {0};
  uint32 *IntWriteValue = Param;
  uchar8 *CharWriteValue = Param;
  Bool WriteResult = TRUE;   
  if((DataType == FLOAT)||(DataType == UINT))
  {
    PROTECT_ParamGroupCreate((void*)IntWriteValue,(void*)IntParamGroup,DataType);
    WriteResult = PROTECT_ParamRewrite(IntParamGroup,Index,DataType);
    
    if(WriteResult == TRUE)
    {
      return TRUE;
    }
  }
  else if(DataType == UCHAR)
  {
    PROTECT_ParamGroupCreate((void*)CharWriteValue,(void*)CharParamGroup,DataType);
    WriteResult = PROTECT_ParamRewrite((void*)CharParamGroup,Index,DataType);
    
    if(WriteResult == TRUE)
    {
      return TRUE;
    }  
  }
  if(DataType == UINT)
  {
#ifdef EVENT_TEST
    //event report hight level
    EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITE_PAR_ERR,
                                          EVENT_DANGEROUS_LEVEL9,UINT,Index);
#endif
  }
  else if(DataType == UCHAR)
  {
#ifdef EVENT_TEST
    //event report hight level
    EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITE_PAR_ERR,
                                          EVENT_DANGEROUS_LEVEL9,UCHAR,Index);
#endif
  }
  else if(DataType == FLOAT)
  {
#ifdef EVENT_TEST
    //event report hight level
    EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_WRITE_PAR_ERR,
                                          EVENT_DANGEROUS_LEVEL9,FLOAT,Index);
#endif
  }
  return FALSE;
}


/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_IntParamSafeRead(uint32 const* Param, uint16 Index,DataTypeDef DataType);
* ������Χ: 
* Param���ӱ�������ȡ����Ч��������Χ��0~255.

Index���Ǳ������Ĳ�����ַ���������ĸ�λ�û�ȡ���������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��


* ����ֵ˵��:
Bool �ͷ���ֵ������TRUE��ʾ�������������سɹ�������FALSE��ʾ��������������ʧ�ܡ�
* ���ܽ���:   
   
*
* �ؼ���ע��
* -  ע�⣬�����������������ʧ�ܣ���* Param��ֵ����Ч�ģ��޷���ʹ�á�ͬʱӦ���ύ
��ȡ�����¼��������޸�����ΪֻҪ����ֵ����Ч�ģ���֤�����ݱ����������ݷ�������ʧ�棬����
����
* δ�����: 
* 
*/
static Bool PROTECT_ParamSafeRead(void*const Param, uint16 Index,DataTypeDef DataType)
{
  ReadResultDef ParamResult = NO_PAR_ERR;
  
  
  uint32 IntGroupReceive[PARAM_GROUP_BUFF_SIZE] = {0};
  uint32 IntGroupRestore[PARAM_GROUP_BUFF_SIZE] = {0};
  uchar8 CharGroupReceive[PARAM_GROUP_BUFF_SIZE] = {0};
  uchar8 CharGroupRestore[PARAM_GROUP_BUFF_SIZE] = {0};

  
  if((DataType == FLOAT)||(DataType == UINT))
  {
    PROTECT_ParamGroupRead(IntGroupReceive,Index,DataType);
    PROTECT_ParamGroupDecode(IntGroupReceive,IntGroupRestore,DataType);
    ParamResult = PROTECT_ParamGroupCheck(IntGroupRestore,Param,DataType);
  }
  else if(DataType == UCHAR)
  {
    PROTECT_ParamGroupRead(CharGroupReceive,Index,DataType);
    PROTECT_ParamGroupDecode(CharGroupReceive,CharGroupRestore,DataType);
    ParamResult = PROTECT_ParamGroupCheck(CharGroupRestore,Param,DataType);
  }
  if((ParamResult == ORIGINAL_PAR_ERR)|| 
                  (ParamResult == REVERS_PAR_ERR)||(ParamResult == XOR_PAR_ERR))
  {
    //��д��������¼����棬���ε������¼�����
    if(PROTECT_ParamModifyResult((void*)Param,Index,DataType) == FALSE)
    {
      return FALSE;
    }
    PROTECT_ParamGroupErrResult(ParamResult,Index,DataType);
  }
  else if(ParamResult == ALL_PAR_ERR)
  {
      //����������ȫ��ʧ��󣬽�Ĭ��ֵд�����ݱ��������ȴ�ģ��ʹ���������趨��
      //��д��������¼����棬�����ε������¼�����
      if(PROTECT_ParamModifyResult((void*)Param,Index,DataType) == FALSE)
      {
        return FALSE;
      }
    //event report
     if(DataType == UINT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ALL_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL9,UINT,Index);
#endif
        *((uint32*)Param) = IntDataRangeListBuff[Index][0];
      }
      else if(DataType == FLOAT)
      {
        union FloatToInt
        {
          uint32 IntData;
          float  FloatData;
        }FloatParamData;
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ALL_DATA_CHANGE_ERR,
                                            EVENT_DANGEROUS_LEVEL9,FLOAT,Index);
#endif
        FloatParamData.FloatData = FloatDataRangeListBuff[Index][0];
        *((uint32*)Param) = FloatParamData.IntData;
      }
      else if(DataType == UCHAR)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ALL_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL9,UCHAR,Index);
#endif
        *((uchar8*)Param) = CharDataRangeListBuff[Index][0];
      }

     
     G_GroupChangeFlag = TRUE;//TEST
    return FALSE;
  }
  return TRUE;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static Bool PROTECT_ParamModifyResult(void*const Param, uint16 Index,DataTypeDef DataType)
* ������Χ: 
* Param���ӱ�������ȡ����Ч��������Χ��0~255.

Index���Ǳ������Ĳ�����ַ���������ĸ�λ�û�ȡ���������ָ������Χ������
DATA_SERIAL_NUMBER_SIZE��Ҳ���ǲ�����ŵ����ֵ��

* ����ֵ˵��:TRUE˵���޸ĳɹ���FALSE˵���޸�ʧ�� 
* ���ܽ���:   
  ������������һ����Դ��ʧ�棬��Ҫ���ݱ���ģ�������޸�һ�£����Ա��������ǶԵ�����Դʧ��
  �����޸ġ�
*
* �ؼ���ע��
* - 
  
* δ�����: 
* 
*/
static Bool PROTECT_ParamModifyResult(void*const Param, uint16 Index,DataTypeDef DataType)
{
    Bool UpdateResult = TRUE;
    UpdateResult = PROTECT_ParamSafeWrite((void*)Param,Index,DataType);
    if(UpdateResult == FALSE)
    {
      //event report
      /*if(DataType == UINT)
      {
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_MODIFY_ERR,
                                            EVENT_DANGEROUS_LEVEL9,UINT,Index);
      }
      else if(DataType == FLOAT)
      {
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_MODIFY_ERR,
                                            EVENT_DANGEROUS_LEVEL9,FLOAT,Index);      
      }
      else if(DataType == UCHAR)
      {
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_MODIFY_ERR,
                                                  EVENT_DANGEROUS_LEVEL9,UCHAR,Index);
      } */
      
      return FALSE;
    }
    return TRUE;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void PROTECT_ParamErrResult(ReadResultDef ParamResult,uint16 Index,DataTypeDef DataType)
* ������Χ: 

.

* ����ֵ˵��: 
* ���ܽ���:   
  ����������Ҫ�Խ��������ԭ�������һ�Աȣ����ԱȽ�����ء����صĽ�������Ϸ����֣�
  һ��������ԭ�������ͬ������һ�־����뱾������صģ��������г�����һ���������������
  ������£����Ǹ�����һ���������Ӧ���¼�¼�������
*
* �ؼ���ע��
* - 
   ¼���¼���ԭ����󣬷������������������������Ϊ���֣���ÿ���������ַ�Ϊ��char��
  ���ݣ�int�����ݺ�float�����ݡ�
* δ�����: 
* 
*/
static void PROTECT_ParamGroupErrResult(ReadResultDef ParamResult,uint16 Index,DataTypeDef DataType)
{
    if(ParamResult == ORIGINAL_PAR_ERR)
    { 
      if(DataType == UINT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ORIGINAL_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UINT,Index);
#endif
      }
      else if(DataType == FLOAT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ORIGINAL_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,FLOAT,Index);      
#endif
      }
      else if(DataType == UCHAR)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_ORIGINAL_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UCHAR,Index);
#endif
      }
    }
    if(ParamResult == REVERS_PAR_ERR)
    {
      if(DataType == UINT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_REVERSE_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UINT,Index);
#endif
      }
      else if(DataType == FLOAT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_REVERSE_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,FLOAT,Index);      
#endif
      }
      else if(DataType == UCHAR)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_REVERSE_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UCHAR,Index);
#endif
      }      
    }
    if(ParamResult == XOR_PAR_ERR)
    {
      if(DataType == UINT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_XOR_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UINT,Index);
#endif
      }
      else if(DataType == FLOAT)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_XOR_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,FLOAT,Index);      
#endif
      }
      else if(DataType == UCHAR)
      {
#ifdef EVENT_TEST
        EventReport(EVENT_RAM_ERROR_TYPE,EVENT_MCU_SOURCE,EVENT_RAM_XOR_DATA_CHANGE_ERR,
                                                  EVENT_DANGEROUS_LEVEL5,UCHAR,Index);
#endif
      }     
    }
}


/**
 //�������ƺͲ����ͷ���ֵ���͡�

* ������Χ: 

.

* ����ֵ˵��: 
* ���ܽ���:   

*
* �ؼ���ע��
* - 
  
* δ�����: 
* 
*/
void Test_ChangeGroup(void )
{
  if(G_GroupChangeFlag == TRUE)
  {
    //G_PROTECT_IntParamBuff[5][0] = 1; //ԭ��
    G_PROTECT_CharParamBuff[5][1] = 2; //����
    //G_PROTECT_IntParamBuff[5][2] = 3; //�����
  }
  G_GroupChangeFlag = FALSE;
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar8 PROTECT_GetParamIndex(DataTypeDef DataType)
* ������Χ: 
DataTypeDef DataType:�������ͣ����ݲ�ͬ���������ͣ����ʲ�ͬ�Ĳ���������
typedef enum
{
  UCHAR = 1,
  UINT = 2,
  THREE_BYTES = 3,
  LONG_UINT = 4,
  FLOAT = 4,
  ASCII_6 = 6,
  ASCII_12 = 12,
  ASCII_24 = 24,
}DataTypeDef;
������UCHAR��UINT��FLOAT�������ͣ�������ǣ����ύ�¼���
.

* ����ֵ˵��: uchar8���͵����ݣ������ֵ�ǵ�ǰ�������Ѵ���Ĳ���ռ�ÿռ�+1��
Ҳ������һ���������Ĳ���Ҫ�����������š�
* ���ܽ���:   
����������������ȡ������ͨ������������ȷ����ǰ��������ʹ�õ�������ж���һ������
�Ƿ�����������棬���⣬������Ա��棬���������ص����ݾ��ǽ�Ҫ��������Ĳ���������
��š�
*
* �ؼ���ע��
* - 
  
* δ�����: 
* 
*/
uchar8 PROTECT_GetParamIndex(DataTypeDef DataType)
{
  uchar8 ProtectCurrentIndex = 0;
  switch(DataType)
  {
    case UCHAR:
      ProtectCurrentIndex = RAM_DATA_SIZE - CharParamStructure.CurrentCapcity;
      break;
    case UINT:
      ProtectCurrentIndex = RAM_DATA_SIZE - IntParamStructure.CurrentCapcity;
      break;
    case FLOAT:
      ProtectCurrentIndex = RAM_DATA_SIZE - FloatParamStructure.CurrentCapcity;
      break;
    default:break;
  }
  return ProtectCurrentIndex;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void PROTECT_InitParamArea()
* ������Χ: 
CharParamStructDef CharParamStructure = {0};
IntParamStructDef IntParamStructure = {0};
FloatParamStructDef FloatParamStructure = {0};
.

* ����ֵ˵��: void
* ���ܽ���:   
���ݱ������������ʼ��������Ϊ����������Ĭ��ֵ��ͬʱ�����ݱ������顣
*
* �ؼ���ע��
* - 
  
* δ�����: 
* 
*/
void PROTECT_InitParamArea(DataTypeDef DataType)
{
  CharParamStructure.CurrentCapcity = RAM_DATA_SIZE;
  CharParamStructure.SourceCodePtr = G_PROTECT_CharParamSourceCodeBuff;
  CharParamStructure.SecondCodePtr = G_PROTECT_CharParamSecondCodeBuff;
  CharParamStructure.ThirdCodePtr = G_PROTECT_CharParamThirdCodeBuff;
  
  IntParamStructure.CurrentCapcity = RAM_DATA_SIZE;
  IntParamStructure.SourceCodePtr = G_PROTECT_IntParamSourceCodeBuff;
  IntParamStructure.SecondCodePtr = G_PROTECT_IntParamSecondCodeBuff;
  IntParamStructure.ThirdCodePtr = G_PROTECT_IntParamThirdCodeBuff;
  
  FloatParamStructure.CurrentCapcity = RAM_DATA_SIZE;
  FloatParamStructure.SourceCodePtr = G_PROTECT_FloatParamSourceCodeBuff;
  FloatParamStructure.SecondCodePtr = G_PROTECT_FloatParamSecondCodeBuff;
  FloatParamStructure.ThirdCodePtr = G_PROTECT_FloatParamThirdCodeBuff;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
Bool IsParamAreaFull(DataTypeDef DataType)
* ������Χ: 

.

* ����ֵ˵��: void
* ���ܽ���:   
�жϲ������������Ƿ��������
*
* �ؼ���ע��
* - 
  
* δ�����: 
* 
*/
Bool IsParamAreaFull(DataTypeDef DataType)
{
  Bool Result = TRUE;
  switch(DataType)
  {
    case UCHAR:
      if(CharParamStructure.CurrentCapcity == 0)
      {
        Result = TRUE;
      }
      else
        Result = FALSE;
      break;
    case UINT:
      if(IntParamStructure.CurrentCapcity == 0)
      {
        Result = TRUE;
      }
      else
        Result = FALSE;
      break;
    case FLOAT:
      if(FloatParamStructure.CurrentCapcity == 0)
      {
        Result = TRUE;
      }
      else
        Result = FALSE;
      break;
    default:break;
  }
  return Result;
}
























