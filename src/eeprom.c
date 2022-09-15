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



/****************************eeprom.c文件说明*************************************/
//该文件为根据iic_protocal.c文件中的底层驱动文件所编写的有关参数读写的函数，包括
// 1、单个字符型参数的存储函数、读取函数
// 2、单个整型数据的存储函数、读取函数
// 3、单个浮点型数据的存储函数、读取函数
// 4、字符数组的存储函数、读取函数
// 5、整型数组的存储函数、读取函数
// 6、浮点型数组的存储函数、读取函数
//以上函数可被其它文件调用
/********************************************************************************/

/***************************************************************************
本文件主要是eeprom的读写操作函数提供出eeprom读写各类参数的函数



******************************************************************************/

/**********************eeprom的底层操作函数关系************************************


ISendStr  IRcvStr  分别用单片机的普通引脚模拟iic的发送一个字符串和接收一个字符串的功能。

然后利用上面两个函数 实现了 ReadEEPChar WriteEEPChar 等函数。但是这个层次的函数就是读写一次的具体类型的变量。还没有进行校验和检查。

然后进一步有 read和write函数 构成了 LoadChar 和SaveChar等函数。Load和Save中就是进行校验了。 但是这也只是具有检查的读写基本的数据类型。

在读写基本数据类型的Load  和 Write  基础上。进一步写了各个参数的Load和Write



***********************************************************/





/**********************参数更改和存储的分时操作逻辑************************************

为所有的变量都提供了一个标志位。例如FlagOfChange_PVUnit 。在更改了变量之后也会把这个标志位做更改。这部分一般在通讯里面完成。
然后当系统有时间了，就对这个标志位做检查，发现标志位被更改，那么就把对应的变量保存，然后把这个标志位做恢复。

更改参数与保存参数是分时操作的。主要的原因是存储eeprom的速度太慢。如果放到中断里面进行则会耽误很多的时间。
更改参数之后会更改一个该参数对应的标志位，然后存储程序根据这个标志位进行存储。保存存储出厂设置，恢复出厂设置，拷贝出厂参数等等。
就好像是更改参数的程序给存储参数的程序发了一个指令。这个指令可以用于高速存储参数的程序干任何事情。

检查参数是否更改的标志位(响应更改参数函数传递过来的指令)，并且对相应的参数进行存储或者进行其他操作的函数就是Save_All_Para() 
因为参数在其逻辑上，存储上，结构上 有着很大的不同。有些是一个char 有些是许多char 或者int等等。
所以我们为每一个变量都做了两个函数，读和写。

***********************************************************/







#include "eeprom.h"
#include "iic_protocal.h"







/** void  Delay5ms(unsigned int DelayTime)     //函数名称和参量和返回值类型。
* 变量范围:DelayTime为延时时间参数，0 ≤ DelayTime ≤ 65535
*
* 返回值说明: void
*
* 功能介绍: 延时函数
*
* 关键备注：for mem write  , the at24c64 has this problem need 5ms to save data into eeprom
*
* 未来提高:
* 
*/
void  Delay5ms(unsigned int DelayTime)   
{
	unsigned int i;
	
    for (i = 0;i < DelayTime;i++)
  	{;}
}


/**void WriteEEPChar(unsigned int SaveAddress,unsigned char Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255 
*
* 返回值说明: void
*
* 功能介绍:写一个字节字符型数据Data到EEProm的SaveAddress地址
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  WriteEEPChar(unsigned int SaveAddress, unsigned char Data)
{
	ISendStr(I2C_ADDRESS,SaveAddress,&Data,BYTE_NUM_1);
	Delay5ms(EEPROM_5MS);
}


/**void ReadByte(unsigned int SaveAddress, unsigned char * Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: void
*
* 功能介绍: 从EEProm的SaveAddress地址中读一个字节字符型数据，放在地址Data中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  ReadEEPChar(unsigned int SaveAddress, unsigned char * Data)
{
	IRcvStr(I2C_ADDRESS,SaveAddress,Data,BYTE_NUM_1);
}


/**unsigned char SaveChar(unsigned int SaveAddress, unsigned char Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*
* 返回值说明: unsigned char，存储成功返回OK，存储失败返回FAIL

* 功能介绍: 保存字符型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回SUCCESS，否则返回FAIL
*
* 关键备注：如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char  SaveChar(unsigned int SaveAddress, unsigned char  Data)
{
	unsigned char EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		WriteEEPChar(SaveAddress, Data);
		ReadEEPChar(SaveAddress,&EEPTemp);
		if (EEPTemp == Data) 
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char LoadChar(unsigned int SaveAddress, unsigned char * Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: unsigned char，读取成功返回OK，失败返回FAIL
*
* 功能介绍: 从EEProm的SaveAddress地址中读一个字节数据，放在地址Data中
*
* 关键备注：如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char  LoadChar(unsigned int SaveAddress, unsigned char* Data)
{
	unsigned char EEPTemp;
	unsigned char i;
	
	ReadEEPChar(SaveAddress,Data);
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		ReadEEPChar(SaveAddress,&EEPTemp);
		if(EEPTemp == *Data) 
		{
		   //RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		   return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**void  WriteEEPInt(unsigned int SaveAddress,unsigned int Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 65535  
*
* 返回值说明: void
*
* 功能介绍:写整型数据Data到EEProm，首字节存储在EEProm的地址SaveAddress中，共占SaveAddress、SaveAddress+1两个字节地址
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  WriteEEPInt(unsigned int SaveAddress,unsigned int Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress = (unsigned char*)&Data;
	ISendStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_2);
	Delay5ms(EEPROM_5MS);
}

/**void  ReadEEPInt(unsigned int SaveAddress,unsigned int Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 65535  
*
* 返回值说明: void
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+1中读两个字节整型数据，存放在以Data开头的地址中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  ReadEEPInt(unsigned int SaveAddress, unsigned int * Data)
{
	unsigned char * ByteAddress;

	ByteAddress = (unsigned char*)Data;
	IRcvStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_2);
}


/**unsigned char SaveInt(unsigned int SaveAddress,unsigned int  Data)   //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为待存储的数据，0 ≤ Data ≤ 65535 
*
* 返回值说明: unsigned char，存储成功返回OK，存储失败返回FAIL
*
* 功能介绍:保存整型数据Data到EEProm的地址SaveAddress~SaveAddress+1中，,保存后再读出，如果读出值和保存的值一致，返回SUCCESS，否则返回FAIL
*
* 关键备注：如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char SaveInt(unsigned int SaveAddress, unsigned int  Data)
{
	unsigned int EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		WriteEEPInt(SaveAddress,Data);
		ReadEEPInt(SaveAddress, &EEPTemp);
		if (EEPTemp == Data)
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}

/**unsigned char LoadInt(unsigned int SaveAddress,unsigned int * Data)   //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向整型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: unsigned char,读取成功返回OK，失败返回FAIL
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+1中读两个字节整型数据，存放在以Data开头的地址中
*
* 关键备注：如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char  LoadInt(unsigned int SaveAddress,  unsigned int * Data)
{
	unsigned int EEPTemp;
	unsigned char i;
	
	ReadEEPInt(SaveAddress,Data);
	for (i=0;i<EEP_TRY_TIME;i++)
	{	
		ReadEEPInt(SaveAddress,&EEPTemp);
		if (EEPTemp == *Data)
		{ 
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**void  WriteEEPFloat(unsigned int SaveAddress, float  Data)  //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为待存储的数据，3.4e-38 ≤ Data ≤ 3.4e38 
*
* 返回值说明:void
*
* 功能介绍: 写浮点型数据Data到EEProm，首字节存储在EEProm的地址SaveAddress中，共占SaveAddress~SaveAddress+3四个字节地址
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  WriteEEPFloat(unsigned int SaveAddress, float Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress = (unsigned char*)&Data;
	ISendStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_4);
	Delay5ms(EEPROM_5MS);
}


/**void ReadEEPFloat (unsigned int SaveAddress, float * Data)  //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为指向浮点型数据的指针，里面存放读取出来的数据首字节 
*  
* 返回值说明: void
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+3中读四个字节数据，存放在以Data开头的地址中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
void  ReadEEPFloat (unsigned int SaveAddress, float * Data)
{
	unsigned char * ByteAddress;
	
	ByteAddress=(unsigned char*)Data;
	IRcvStr(I2C_ADDRESS,SaveAddress,ByteAddress,BYTE_NUM_4);	
}


/**unsigned char SaveFloat(unsigned int SaveAddress, float  Data)  //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为待存储的数据，3.4e-38 ≤ Data ≤ 3.4e38 
*
* 返回值说明: unsigned char,写入成功返回OK，失败返回FAIL
*
* 功能介绍: 写浮点型数据Data到EEProm，首字节存储在EEProm的地址SaveAddress中，共占SaveAddress~SaveAddress+3四个字节地址
*
* 关键备注：如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char SaveFloat(unsigned int SaveAddress, float Data)
{
	float EEPTemp;
	unsigned char i;
	
	for (i = 0;i < EEP_TRY_TIME;i++)
	{		
		WriteEEPFloat(SaveAddress,Data);
		ReadEEPFloat(SaveAddress, &EEPTemp);
		if (EEPTemp == Data) 
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char ReadEEPFloat (unsigned int SaveAddress, float * Data)  //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为指向浮点型数据的指针，里面存放读取出来的数据首字节 
*  
* 返回值说明: unsigned char，读取成功返回OK，失败返回FAIL
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+3中读四个字节数据，存放在以Data开头的地址中
*
* 关键备注：如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
unsigned char LoadFloat(unsigned int SaveAddress, float * Data)
{
	float EEPTemp;
	unsigned char i;
	
	ReadEEPFloat(SaveAddress,Data);
	for (i = 0;i < EEP_TRY_TIME;i++)
	{	
		ReadEEPFloat(SaveAddress,&EEPTemp);
		if (EEPTemp == *Data)
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
		    return OK;
		}
		else
		{
			//RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
		}
	}
	return FAIL;
}


/**unsigned char  LoadCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，读取成功返回OK，失败返回FAIL
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个字节数据，放在地址Data~Data+ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char  LoadCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadChar(SaveAddress+i, (Data+i)) != OK)
			return FAIL;		
	}
	return OK;
}


/**unsigned char  LoadIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的整型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，读取成功返回OK，失败返回FAIL
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个整型数据，放在地址Data~Data+2*ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char  LoadIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)
{
	unsigned int i;

	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadInt(SaveAddress+i*BYTE_NUM_2, (Data+i))!=OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char  LoadFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的浮点型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，读取成功返回OK，失败返回FAIL
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个浮点型数据，放在地址Data~Data+4*ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char LoadFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)
{
	int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (LoadFloat(SaveAddress+i*BYTE_NUM_4, (Data+i))!=OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，存储成功返回OK，存储失败返回FAIL
*
* 功能介绍: 保存字符型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char SaveCharArray(unsigned int SaveAddress, unsigned char * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveChar(SaveAddress+i, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，存储成功返回OK，存储失败返回FAIL
*
* 功能介绍: 保存整型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char SaveIntArray(unsigned int SaveAddress, unsigned int * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveInt(SaveAddress + i*BYTE_NUM_2, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}


/**unsigned char SaveIntArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，存储成功返回OK，存储失败返回FAIL
*
* 功能介绍: 保存浮点型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char SaveFloatArray(unsigned int SaveAddress, float * Data, unsigned int ArrayLength)
{
	unsigned int i;
	
	for (i = 0;i < ArrayLength;i++)
	{
		if (SaveFloat(SaveAddress + i*BYTE_NUM_4, *(Data+i)) != OK)
			return FAIL;
	}
	return OK;
}




