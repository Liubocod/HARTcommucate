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
  * 项目功能：通过Modbus与雷达液位计和多点温度计通信，测量的数据转换为BPM数据保存
  * 在缓冲区，等待BPM主机查询，当接到主机查询帧后解析与本设备地址匹配，则将缓冲数
  * 据发送给BPM主机。
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */ 
#include "data_management.h"//管理
//#include "alarm.h"
#include "data_range_list.h"



#define COMPARE for(i = 0; i < Length;i++) \
      {                                   \
        if(*(p1+i) != *(p2+i))            \
        {                                 \
          return FALSE;                   \
        }                                 \
      }                                   

//事件函数查找地址
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



//RAM区错误
#define EVENT_RAM_ORIGINAL_DATA_CHANGE_ERR 0x07
#define EVENT_RAM_REVERSE_DATA_CHANGE_ERR 0x08
#define EVENT_RAM_XOR_DATA_CHANGE_ERR 0x09
#define EVENT_RAM_ALL_DATA_CHANGE_ERR 0x0a
#define EVENT_RAM_WRITE_PAR_ERR 0x0b
#define EVENT_RAM_WRITING_CONFIRM_ERR 0x0c
#define EVENT_RAM_INIT_ERR 0x0d
#define EVENT_RAM_DATA_BUFF_FULL 0x0e

//写入不成功时，规定重复写的次数
#define REPETITIVE_WRITING_TIMES 3

//日常查询每次查询长度
#define ROUTING_CHECK_TIMES 10

//异或码生成条件
#define XOR_MARK_CHAR 0XAA
//异或码生成条件
#define XOR_MARK_INT 0XAAAAAAAA

//事件文件查找地址
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
  NO_PAR_ERR,        // 读取结果为无错误 
  ORIGINAL_PAR_ERR,  // 读取结果为原码发生失真
  REVERS_PAR_ERR,    // 读取结果为反码发生失真
  XOR_PAR_ERR,       // 读取结果为异或码发生失真
  ALL_PAR_ERR        // 读取结果为所有参数码失真
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





//测试函数专用全局变量
static uchar8 G_GroupChangeFlag = FALSE;

/**
 //函数名称和参量和返回值类型。
 Bool PROTECT_ParamReadAndWrite(void* Param,uint16 Index,
                                    DataTypeDef DataType,ParamReadWriteDef RW_Status)
* 变量范围: 
  void* Param：指向被保护参数的void*指针。在这里可能是要写入到保护区的设置参数，也可能是
  要转载要被读取的设置参数的地址，具体根据 “RW_Status”变量判定。
  这个参数可以是三种数据类型，可以是char型，int型或者是float型，具体是什么类型可以根据变
  量“DataType”来判定。因为有三种类型，所以范围可能是unsigned char的范围，也有可能是其他
  数据类型的范围。
  
  Index：是在数据保护区的具体位置，范围0-65535
  
  DataType：typedef enum{UCHAR,UINT,FLOAT}DataTypeDef


* 返回值说明:返回值Bool型数值，判断读取或写入是否成功 
* 功能介绍:   
   本函数是为模块使用者提供的一个被保护参数写入或读取的接口，使用者可以根据接口参数变量的
  不同组合完成被保护参数的写入，读取动作。
*
* 关键备注：
* -
  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
 Bool PROTECT_ParamReadAndWrite(void* Param,uint16 Index,
                                    DataTypeDef DataType,ParamReadWriteDef RW_Status)
* 变量范围: 
  void* Param：指向被保护参数的void*指针。在这里可能是要写入到保护区的设置参数，也可能是
  要转载要被读取的设置参数的地址，具体根据 “RW_Status”变量判定。
  这个参数可以是三种数据类型，可以是char型，int型或者是float型，具体是什么类型可以根据变
  量“DataType”来判定。因为有三种类型，所以范围可能是unsigned char的范围，也有可能是其他
  数据类型的范围。
  
  Index：是在数据保护区的具体位置，范围0-65535
  
  DataType：typedef enum{UCHAR,UINT,FLOAT}DataTypeDef


* 返回值说明:返回值Bool型数值，判断读取或写入是否成功 
* 功能介绍:   
   本函数是为模块使用者提供的一个被保护参数写入或读取的接口，使用者可以根据接口参数变量的
  不同组合完成被保护参数的写入，读取动作。
*
* 关键备注：
* -
  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_CharGroupWriteArrayCompare(uchar8 const*const ptr1,
                                        uchar8 const*const ptr2，uchar8 Length);
* 变量范围: 
*ptr1:比较数组1，数组大小PARAM_GROUP_BUFF_SIZE。
*ptr2:比较数组2，数组大小PARAM_GROUP_BUFF_SIZE。
Length：比较数组长度，小于PARAM_GROUP_BUFF_SIZE。
* 返回值说明:返回值表示两个数组是否完全相同，如果完全相同返回TRUE，不相同FALSE 
* 功能介绍:   
  函数功能是，两个数组在规定的长度内是否完全相同。 
*
* 关键备注：
* - COMPARE ：是通过宏定义将重复使用的代码替代掉 
* 未来提高: 
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
 //函数名称和参量和返回值类型。
void PROTECT_CharCharParamBuffInit();
* 变量范围: 

.

* 返回值说明:是否初始化成功。 
* 功能介绍:   
   将保护区的说有数据清空。
*
* 关键备注：
* -  外部接口，用来清空数据保护区。
* 未来提高: 
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
 //函数名称和参量和返回值类型。
void PROTECT_CharParamRoutingcheck(void );
* 变量范围: 

.

* 返回值说明: 
* 功能介绍:   
  保护区日常检查，对保护区中保存的每一个参数进行检修察验，如发现三取二错误即可修改后提交
  低级事件，如果修复不成功，要提交高级事件。如果发现三码全错，提交高等级事件通知产品用户
  重新设置参数。
*
* 关键备注：
* - 
  ROUTING_CHECK_TIMES：表示每次调用日常检查函数时，要对保护区进行检查的长度。他的作用是
  当数据管理数组中的参数个数多于ROUTING_CHECK_TIMES时，可以分段来对数据保护区进行检查，
  可以节省资源。
  j表示日常检查的索引，CharBuffStructure.RamBuffTop是目前数据管理数组中保存的具体参数
  个数，当j达到这个个数时（每次判断j前都会执行j++），就会自动清零，并且跳出循环，说明检
  查完成。
  当j超过数组参数个数的上限时，进行报错，并对j清零，跳出循环，这种警报等级并不高。
* 未来提高: 
* 
*/
void PROTECT_ParamRoutingcheck(void )
{
  uint16 i;
  static uint16 j = 0;
  uint32 Param = 0;
  //定义static  分段检查

 
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
 //函数名称和参量和返回值类型。
static void PROTECT_IntParamGroupDecode(uint32 const *GroupReceive,
                                                      uint32 const *GroupRestore);
* 变量范围: 
*GroupReceive：保护区数据读取装载数组首地址，数组大小PARAM_GROUP_BUFF_SIZE。
*GroupRestore：装载还原码的数组 ，数组大小PARAM_GROUP_BUFF_SIZE。

* 返回值说明: 
* 功能介绍:   
  本函数也是内部接口，主要功能是将存放在GroupReceive[]中读取自保护区的组码,还原成三组原码，
  并存放在GroupRestore[]数组中传回。 
*
* 关键备注：
* -  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_IntGroupWriteResultCheck(uint32 const*const GroupBuff,  
                                                        uint32 const*const GroupReceive)
* 变量范围: 
GroupBuff[]:是组码函数生成的组码数组，数组大小PARAM_GROUP_BUFF_SIZE。
GroupReceive[]:是读取函数读取刚写入保护区中的组码数组，数组大小DATA_PROTECT_BUFF_SIZE。
.

* 返回值说明:返回是否核对成功，如果两个数组完全相同，则返回TRUE，反之返回FALSE。 
* 功能介绍:   
 将两个组码数组进行比较，是否完全一样，如果不一样返回FALSE，一样就返回TRUE。  
*
* 关键备注：
* -  
* 未来提高: 
* 
*/                   
 //ptr 统一一下
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
 //函数名称和参量和返回值类型。
static ReadResultDef PROTECT_IntParamGroupCheck(uint32 const * const GroupRestore,
                                                        uint32 *const EffectiveValue);
* 变量范围: 
* GroupRestore：装载还原码的数组 ，数组大小PARAM_GROUP_BUFF_SIZE。
* EffectiveValue：传递有效值的指针。

* 返回值说明:
Typedef enum//枚举
{
  NO_PAR_ERR,
  ORIGINAL_PAR_ERR,
  REVERS_PAR_ERR,
  XOR_PAR_ERR,
  ALL_PAR_ERR
}ReadResultDef;
 返回值作用不单单是说明有效值是否有效，也为事件系统指明数据区中的哪一个码发生了变化。
* 功能介绍:   
  将还原吗数组中的三个原码进行互相比对，看看是否相同或者有什么样的不同 
*
* 关键备注：
* -
需要强调一下，这个函数的* EffectiveValue所传递的有效值是根据返回值决定是否有效的，
比如说，当数据保护区中反码存储出现异常，我们返回REVERS_PAR_ERR，因为一个反码异常是不影响
有效值的有效性，所以*EffectiveValue传回的数值是可以被使用的。但是如果数据保护区的原码，
反码和异或码都发生异常，就会返回ALL_PAR_ERR，这就表示这个数据已经严重失真，所以返回的
*EffectiveValue也是无效的，不可被使用。当然，所有码都正确的时候，传回的有效值自然是有效的。 
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static void PROTECT_IntParamGroupRead(uint32 *const GroupReceive,uint16 Index);
* 变量范围: 
*GroupReceive：保护区数据读取装载数组首地址，数组大小PARAM_GROUP_BUFF_SIZE。

Index：是保护区的参数地址，要把参数存在哪个位置都用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。

* 返回值说明:
* 功能介绍:   
  读取保存在保护区保存的组码，装在GroupReceive[]数组中。在保护区的Index位置提取数据。 
*
* 关键备注：
* -  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static void PROTECT_IntParamGroupWrite(uint32 const *GroupBuff,uint16 Index);
* 变量范围: 
*GroupBuff：是组码生成函数提供的组码数组首地址，数组大小PARAM_GROUP_BUFF_SIZE。


Index：是保护区的参数地址，要把参数存在哪个位置都用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。.

* 返回值说明: 
* 功能介绍:   
  通过参数生成组码后，可将生成的组码写在保护区中Index所指定的位置上。 
*
* 关键备注：
* -  
* 未来提高: 
* 
*/
static void PROTECT_ParamGroupWrite(void*const GroupBuff,
                                       uint16 Index,DataTypeDef DataType)//统一名称
{
  uchar8 i;
  uchar8 *CharGroupBuff = GroupBuff;
  uint32 *IntGroupBuff = GroupBuff,*FloatGroupBuff = GroupBuff;
  //一般检验变量，常量不常检验。常量，宏通过备注说明
 
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_IntParamWritingConfirm(uint32 const*const GroupBuff,uint16 Index);
* 变量范围: 
GroupBuff[]:被保护参数生成的组码数组。
Index：数据保护区的地址。

* 返回值说明: 
* 功能介绍:   
  将组码数组通过保护区写入函数写入到数据保护区中,
  然后通过保护区参数读取函数，将写入到保护区中参数组码读出,
  再调用写入数据核对函数，将组码数组GroupBuff[]和读取的组码数组
  GroupReceive[]作为参数进行核对确认。
*
* 关键备注：
* -  
  这里要强调一下，如果第一次就写入成功，即为正常写入，
  不需要提交事件，超过一次，并且少于最高上限次数记为轻等级事件，如果达到最高上限次数，
  则记为高等级事件。
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_IntParamRewrite(uint32 const *ParamGroup,uint16 Index)
* 变量范围: 
*buff：是组码生成函数提供的组码数组首地址，数组大小PARAM_GROUP_BUFF_SIZE。


Index：是保护区的参数地址，要把参数存在哪个位置都用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。.

* 返回值说明:返回值表示组码是否写入成功，如果成功返回TRUE,失败返回FALSE. 
* 功能介绍:   
  通过参数生成组码后，可将生成的组码写在保护区中Index所指定的位置上。
  其中包括写入确认功能。
*
* 关键备注：
* -  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static void PROTECT_IntParamGroupCreate(uint32 Param,uint32 *const arr);
* 变量范围: 
 Param：要设定的参数值，范围是uint.
 *arr：装载参数组码的数组首地址，数组大小PARAM_GROUP_BUFF_SIZE。
* 返回值说明:返回值是组码是否生成成功的标志。 
* 功能介绍:   
  以产品的设定参数为模板，生成反码和异或码，并保存在arr[]数组中 
*
* 关键备注：
* - 异或码生成需要一个异或单位XOR_MARK，才能生成我们要使用的异或码。 
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_IntParamSafeWrite(uint32 Param,uint16 Index)
* 变量范围: 
Param:要被写入保护区的参数，范围是uint.

Index：是保护区的参数地址，要把参数存在哪个位置都用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。
.

* 返回值说明:
Bool 型返回值，返回TRUE表示被保护参数加载成功，返回FALSE表示被保护参数加载失败。
* 功能介绍:   
  本函数为模块对外接口，是提供给使用模块的程序设计人员，设计人员只要提供要设定的
  参数值，以及要写入保护区的位置就可以完成参数保护操作。
*
* 关键备注：
* -  如果返回值表示加载失败，则需要提交事件来提示产品用户重新设定或者故障检修。
* 

未来提高: 
*   如果写入失败后，可以选择复写几次，如果在复写过程中成功，提交一个等级较低的事件
  如果达到复写次数上限后仍然为成功，则需要提交一个高等级事件，提示产品用户修理。
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_IntParamSafeRead(uint32 const* Param, uint16 Index,DataTypeDef DataType);
* 变量范围: 
* Param：从保护区读取的有效参数，范围是0~255.

Index：是保护区的参数地址，参数从哪个位置获取用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。


* 返回值说明:
Bool 型返回值，返回TRUE表示被保护参数下载成功，返回FALSE表示被保护参数加载失败。
* 功能介绍:   
   
*
* 关键备注：
* -  注意，如果被保护参数下载失败，则* Param的值是无效的，无法被使用。同时应该提交
读取故障事件，请求修复。因为只要返回值是无效的，就证明数据保护区的数据发生严重失真，急需
修理。
* 未来提高: 
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
    //对写错误进行事件报告，屏蔽掉其他事件报告
    if(PROTECT_ParamModifyResult((void*)Param,Index,DataType) == FALSE)
    {
      return FALSE;
    }
    PROTECT_ParamGroupErrResult(ParamResult,Index,DataType);
  }
  else if(ParamResult == ALL_PAR_ERR)
  {
      //发现三组码全部失真后，将默认值写入数据保护区，等待模块使用者重新设定。
      //对写错误进行事件报告，就屏蔽掉其他事件报告
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
 //函数名称和参量和返回值类型。
static Bool PROTECT_ParamModifyResult(void*const Param, uint16 Index,DataTypeDef DataType)
* 变量范围: 
* Param：从保护区读取的有效参数，范围是0~255.

Index：是保护区的参数地址，参数从哪个位置获取用这个参数指定，范围不超过
DATA_SERIAL_NUMBER_SIZE，也就是参数序号的最大值。

* 返回值说明:TRUE说明修改成功，FALSE说明修改失败 
* 功能介绍:   
  当数据区发生一个码源的失真，需要数据保护模块自行修改一下，所以本函数就是对单个码源失真
  进行修改。
*
* 关键备注：
* - 
  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
static void PROTECT_ParamErrResult(ReadResultDef ParamResult,uint16 Index,DataTypeDef DataType)
* 变量范围: 

.

* 返回值说明: 
* 功能介绍:   
  三组码解码后，要对解出的三组原码进行逐一对比，将对比结果返回。返回的结果大体上分两种，
  一种是三组原码均不相同，而另一种就是与本函数相关的，三组码中出现了一组错误的情况，在这
  种情况下，我们根据这一结果进行相应的事件录入操作。
*
* 关键备注：
* - 
   录入事件从原码错误，反码错误，异或码错误三个大类作为区分，而每个大类中又分为，char型
  数据，int型数据和float型数据。
* 未来提高: 
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
 //函数名称和参量和返回值类型。

* 变量范围: 

.

* 返回值说明: 
* 功能介绍:   

*
* 关键备注：
* - 
  
* 未来提高: 
* 
*/
void Test_ChangeGroup(void )
{
  if(G_GroupChangeFlag == TRUE)
  {
    //G_PROTECT_IntParamBuff[5][0] = 1; //原码
    G_PROTECT_CharParamBuff[5][1] = 2; //反码
    //G_PROTECT_IntParamBuff[5][2] = 3; //异或码
  }
  G_GroupChangeFlag = FALSE;
}

/**
 //函数名称和参量和返回值类型。
uchar8 PROTECT_GetParamIndex(DataTypeDef DataType)
* 变量范围: 
DataTypeDef DataType:数据类型，根据不同的数据类型，访问不同的参数保护区
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
可能是UCHAR，UINT或FLOAT三种类型，如果不是，请提交事件。
.

* 返回值说明: uchar8类型的数据，这个数值是当前保护区已存入的参数占用空间+1，
也就是下一个被保护的参数要存入的数组序号。
* 功能介绍:   
保护区参数索引获取函数，通过本函数可以确定当前保护区被使用的情况，判断下一个参数
是否可以正常保存，另外，如果可以保存，本函数返回的数据就是将要保存进来的参数的索引
序号。
*
* 关键备注：
* - 
  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
void PROTECT_InitParamArea()
* 变量范围: 
CharParamStructDef CharParamStructure = {0};
IntParamStructDef IntParamStructure = {0};
FloatParamStructDef FloatParamStructure = {0};
.

* 返回值说明: void
* 功能介绍:   
数据保护参数区域初始化函数，为保护区加载默认值，同时绑定数据保护数组。
*
* 关键备注：
* - 
  
* 未来提高: 
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
 //函数名称和参量和返回值类型。
Bool IsParamAreaFull(DataTypeDef DataType)
* 变量范围: 

.

* 返回值说明: void
* 功能介绍:   
判断参数保护区域是否发生溢出。
*
* 关键备注：
* - 
  
* 未来提高: 
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
























