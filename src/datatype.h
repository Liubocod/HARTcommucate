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




/***********************DataType.h�ļ�˵��**************************************
���ļ���Ҫ�Ǹ��ݲ�ͬ��mcu�������ͺ��������õ������������Զ�Ӧ��

��Ҫ�õ�����������uchar8��uint16��char8��int16��float32

�����ļ��е��������;��������������֡�
Ȼ���ڲ�ͬ��mcuƽ̨ͨ�����ļ���������mcu�ṩ���������Ͷ�Ӧ��
��Ҫ��һ���ĵط�������uchar8 ��Щƽֻ̨����16λ��ģ�£�����32λ��ģ�¡�
�ڱ�̵�ʱ��Ҫ����ʶ���Լ���uchar8 uint16������32λ�ģ���һЩ255֮��ļӷ���Ȼ����������λ�����Ĳ����ͻ��в�ͬ��

*******************************************************************************/




#ifndef _DATATYPE_H
#define _DATATYPE_H		// ��Ϊ��������ļ���������ļ�����ʱ������ͷ�ļ���Ҳ���������ļ���Ϊ��ȷ�����ظ����������Լ�һ������Ϊ��ǡ�
						// Ȼ������������ļ����ļ������һ�������ꡣ


#define _MSP430_TYPE		// ���������ѡ��ͬ��mcuƽ̨



#ifdef _RENESAS_M16C_TYPE       // Renesas ƽ̨ (M16C M30626FHPGP) 
typedef enum{
	       FALSE = 0,
	       TRUE = 1
	    }bool8;
typedef long int          int32;
typedef int               int16;
typedef char              char8;
typedef unsigned long int uint32;
typedef unsigned int      uint16;
typedef unsigned char     uchar8;
typedef float             float32;

#define BYTE_MASK         0xFF
#define BYTELENGTH        8
#define CHAR_BYTENUM      1
#define INT_BYTENUM       2
#define FLOAT_BYTENUM     4

#endif



#ifdef _MSP430_TYPE                   // MSP430ƽ̨

typedef enum{
	       FALSE = 0,
	       TRUE = 1
	    }bool8;
typedef long int          int32;
typedef int               int16;
typedef char              char8;
typedef unsigned long int uint32;
typedef unsigned int      uint16;
typedef unsigned char     uchar8;
typedef float             float32;

#define BYTE_MASK         0xFF
#define BYTELENGTH        8
#define CHAR_BYTENUM      1
#define INT_BYTENUM       2
#define FLOAT_BYTENUM     4

#endif



#ifdef _STM32F_TYPE     // STM32ƽ̨


typedef enum{
	       FALSE = 0,
	       TRUE = 1
	    }bool8;
typedef s32                    int32;
typedef s16                    int16;
typedef int8_t                 char8;
typedef u32                    uint32;
typedef u16                    uint16;
typedef u8                     uchar8;
typedef unsigned long int      uint64;
typedef unsigned long long int uint128;
typedef long int               int64;
typedef long long int          int128;
typedef float                  float32;

#define BYTE_MASK         0xFF
#define BYTELENGTH        8
#define CHAR_BYTENUM      1
#define INT_BYTENUM       2
#define FLOAT_BYTENUM     4

#endif






#endif























