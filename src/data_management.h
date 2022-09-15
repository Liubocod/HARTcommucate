#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H

#include "datatype.h"

//#define DATA_MANAGEMENT_WRITE_ERR_TEST_BLOCK
//#define DATA_MANAGEMENT_READ_TEST_BLOCK


//EVENT TYPE
#define EVENT_RAM_ERROR_TYPE 0x04

void PROTECT_ParamAreaInit();
Bool IsParamAreaFull(DataTypeDef DataType);
uchar8 PROTECT_GetParamIndex(DataTypeDef DataType);

Bool PROTECT_CharParamWrite(uchar *const Param,uint16 Index,DataTypeDef DataType);
Bool PROTECT_IntParamWrite(uint32 *const Param,uint16 Index,DataTypeDef DataType);
Bool PROTECT_FloatParamWrite(uint32 *const Param,uint16 Index,DataTypeDef DataType);
Bool PROTECT_ParamRead(void*const Param,uint16 Index,DataTypeDef DataType);

void PROTECT_ParamBuffInit(void);//加入检验，初始化是否成功
void PROTECT_ParamRoutingcheck(void );

void Test_ChangeGroup(void);



#endif