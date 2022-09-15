/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd£¬BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */

/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * msp430f5418a devices.
 *
 * Copyright 2007-2012 IAR Systems AB.
 *
 *
 *
 ********************************************************************/

#ifndef __IO430F5418A
#define __IO430F5418A

#ifdef  __IAR_SYSTEMS_ICC__

#include "intrinsics.h"
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430f5418a.h file for use with ICC430/A430 only
#endif

#if __REGISTER_MODEL__ == __REGISTER_MODEL_REG20__
#define __ACCESS_20BIT_REG__  void __data20 * volatile
#else
#define __ACCESS_20BIT_REG__  volatile unsigned short  /* only short access from C is allowed in small memory model */
#endif


#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430XV2 CPU */


#ifdef __IAR_SYSTEMS_ICC__
#pragma language=save
#pragma language=extended


#ifdef __cplusplus
#define __READ    /* not supported */
#else
#define __READ    const
#endif


/*-------------------------------------------------------------------------
 *   Standard Bits
 *-------------------------------------------------------------------------*/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

/*-------------------------------------------------------------------------
 *   Status register bits
 *-------------------------------------------------------------------------*/

#define C                   (0x0001)
#define Z                   (0x0002)
#define N                   (0x0004)
#define V                   (0x0100)
#define GIE                 (0x0008)
#define CPUOFF              (0x0010)
#define OSCOFF              (0x0020)
#define SCG0                (0x0040)
#define SCG1                (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)


#define LPM0      __bis_SR_register(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */



/*-------------------------------------------------------------------------
 *   ADC12
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short ADC12CTL0;   /* ADC12+ Control 0 */

  struct
  {
    unsigned short ADC12SC         : 1; /* ADC12 Start Conversion */
    unsigned short ADC12ENC        : 1; /* ADC12 Enable Conversion */
    unsigned short ADC12TOVIE      : 1; /* ADC12 Timer Overflow interrupt enable */
    unsigned short ADC12OVIE       : 1; /* ADC12 Overflow interrupt enable */
    unsigned short ADC12ON         : 1; /* ADC12 On/enable */
    unsigned short ADC12REFON      : 1; /* ADC12 Reference on */
    unsigned short ADC12REF2_5V    : 1; /*  */
    unsigned short ADC12MSC        : 1; /* ADC12 Multiple SampleConversion */
    unsigned short ADC12SHT00      : 1; /* ADC12 Sample Hold 0 Select Bit: 0 */
    unsigned short ADC12SHT01      : 1; /* ADC12 Sample Hold 0 Select Bit: 1 */
    unsigned short ADC12SHT02      : 1; /* ADC12 Sample Hold 0 Select Bit: 2 */
    unsigned short ADC12SHT03      : 1; /* ADC12 Sample Hold 0 Select Bit: 3 */
    unsigned short ADC12SHT10      : 1; /* ADC12 Sample Hold 1 Select Bit: 0 */
    unsigned short ADC12SHT11      : 1; /* ADC12 Sample Hold 1 Select Bit: 1 */
    unsigned short ADC12SHT12      : 1; /* ADC12 Sample Hold 1 Select Bit: 2 */
    unsigned short ADC12SHT13      : 1; /* ADC12 Sample Hold 1 Select Bit: 3 */
  } ADC12CTL0_bit;

  struct
  {
    unsigned char ADC12CTL0_L;
    unsigned char ADC12CTL0_H;
  };
} @0x0700;

enum {
  ADC12SC         = 0x0001,
  ADC12ENC        = 0x0002,
  ADC12TOVIE      = 0x0004,
  ADC12OVIE       = 0x0008,
  ADC12ON         = 0x0010,
  ADC12REFON      = 0x0020,
  ADC12REF2_5V    = 0x0040,
  ADC12MSC        = 0x0080,
  ADC12SHT00      = 0x0100,
  ADC12SHT01      = 0x0200,
  ADC12SHT02      = 0x0400,
  ADC12SHT03      = 0x0800,
  ADC12SHT10      = 0x1000,
  ADC12SHT11      = 0x2000,
  ADC12SHT12      = 0x4000,
  ADC12SHT13      = 0x8000
};

__no_init volatile union
{
  unsigned short ADC12CTL1;   /* ADC12+ Control 1 */

  struct
  {
    unsigned short ADC12BUSY       : 1; /* ADC12 Busy */
    unsigned short ADC12CONSEQ0    : 1; /* ADC12 Conversion Sequence Select Bit: 0 */
    unsigned short ADC12CONSEQ1    : 1; /* ADC12 Conversion Sequence Select Bit: 1 */
    unsigned short ADC12SSEL0      : 1; /* ADC12 Clock Source Select Bit: 0 */
    unsigned short ADC12SSEL1      : 1; /* ADC12 Clock Source Select Bit: 1 */
    unsigned short ADC12DIV0       : 1; /* ADC12 Clock Divider Select Bit: 0 */
    unsigned short ADC12DIV1       : 1; /* ADC12 Clock Divider Select Bit: 1 */
    unsigned short ADC12DIV2       : 1; /* ADC12 Clock Divider Select Bit: 2 */
    unsigned short ADC12ISSH       : 1; /* ADC12 Invert Sample Hold Signal */
    unsigned short ADC12SHP        : 1; /* ADC12 Sample/Hold Pulse Mode */
    unsigned short ADC12SHS0       : 1; /* ADC12 Sample/Hold Source Bit: 0 */
    unsigned short ADC12SHS1       : 1; /* ADC12 Sample/Hold Source Bit: 1 */
    unsigned short ADC12CSTARTADD0 : 1; /* ADC12 Conversion Start Address Bit: 0 */
    unsigned short ADC12CSTARTADD1 : 1; /* ADC12 Conversion Start Address Bit: 1 */
    unsigned short ADC12CSTARTADD2 : 1; /* ADC12 Conversion Start Address Bit: 2 */
    unsigned short ADC12CSTARTADD3 : 1; /* ADC12 Conversion Start Address Bit: 3 */
  } ADC12CTL1_bit;

  struct
  {
    unsigned char ADC12CTL1_L;
    unsigned char ADC12CTL1_H;
  };
} @0x0702;

enum {
  ADC12BUSY       = 0x0001,
  ADC12CONSEQ0    = 0x0002,
  ADC12CONSEQ1    = 0x0004,
  ADC12SSEL0      = 0x0008,
  ADC12SSEL1      = 0x0010,
  ADC12DIV0       = 0x0020,
  ADC12DIV1       = 0x0040,
  ADC12DIV2       = 0x0080,
  ADC12ISSH       = 0x0100,
  ADC12SHP        = 0x0200,
  ADC12SHS0       = 0x0400,
  ADC12SHS1       = 0x0800,
  ADC12CSTARTADD0 = 0x1000,
  ADC12CSTARTADD1 = 0x2000,
  ADC12CSTARTADD2 = 0x4000,
  ADC12CSTARTADD3 = 0x8000
};

__no_init volatile union
{
  unsigned short ADC12CTL2;   /* ADC12+ Control 2 */

  struct
  {
    unsigned short ADC12REFBURST   : 1; /* ADC12+ Reference Burst */
    unsigned short ADC12REFOUT     : 1; /* ADC12+ Reference Out */
    unsigned short ADC12SR         : 1; /* ADC12+ Sampling Rate */
    unsigned short ADC12DF         : 1; /* ADC12+ Data Format */
    unsigned short ADC12RES0       : 1; /* ADC12+ Resolution Bit: 0 */
    unsigned short ADC12RES1       : 1; /* ADC12+ Resolution Bit: 1 */
    unsigned short                : 1;
    unsigned short ADC12TCOFF      : 1; /* ADC12+ Temperature Sensor Off */
    unsigned short ADC12PDIV       : 1; /* ADC12+ predivider 0:/1   1:/4 */
  } ADC12CTL2_bit;

  struct
  {
    unsigned char ADC12CTL2_L;
    unsigned char ADC12CTL2_H;
  };
} @0x0704;

enum {
  ADC12REFBURST   = 0x0001,
  ADC12REFOUT     = 0x0002,
  ADC12SR         = 0x0004,
  ADC12DF         = 0x0008,
  ADC12RES0       = 0x0010,
  ADC12RES1       = 0x0020,
  ADC12TCOFF      = 0x0080,
  ADC12PDIV       = 0x0100
};

__no_init volatile union
{
  unsigned short ADC12IFG;   /* ADC12+ Interrupt Flag */

  struct
  {
    unsigned short ADC12IFG0       : 1; /* ADC12 Memory 0      Interrupt Flag */
    unsigned short ADC12IFG1       : 1; /* ADC12 Memory 1      Interrupt Flag */
    unsigned short ADC12IFG2       : 1; /* ADC12 Memory 2      Interrupt Flag */
    unsigned short ADC12IFG3       : 1; /* ADC12 Memory 3      Interrupt Flag */
    unsigned short ADC12IFG4       : 1; /* ADC12 Memory 4      Interrupt Flag */
    unsigned short ADC12IFG5       : 1; /* ADC12 Memory 5      Interrupt Flag */
    unsigned short ADC12IFG6       : 1; /* ADC12 Memory 6      Interrupt Flag */
    unsigned short ADC12IFG7       : 1; /* ADC12 Memory 7      Interrupt Flag */
    unsigned short ADC12IFG8       : 1; /* ADC12 Memory 8      Interrupt Flag */
    unsigned short ADC12IFG9       : 1; /* ADC12 Memory 9      Interrupt Flag */
    unsigned short ADC12IFG10      : 1; /* ADC12 Memory 10      Interrupt Flag */
    unsigned short ADC12IFG11      : 1; /* ADC12 Memory 11      Interrupt Flag */
    unsigned short ADC12IFG12      : 1; /* ADC12 Memory 12      Interrupt Flag */
    unsigned short ADC12IFG13      : 1; /* ADC12 Memory 13      Interrupt Flag */
    unsigned short ADC12IFG14      : 1; /* ADC12 Memory 14      Interrupt Flag */
    unsigned short ADC12IFG15      : 1; /* ADC12 Memory 15      Interrupt Flag */
  } ADC12IFG_bit;

  struct
  {
    unsigned char ADC12IFG_L;
    unsigned char ADC12IFG_H;
  };
} @0x070A;

enum {
  ADC12IFG0       = 0x0001,
  ADC12IFG1       = 0x0002,
  ADC12IFG2       = 0x0004,
  ADC12IFG3       = 0x0008,
  ADC12IFG4       = 0x0010,
  ADC12IFG5       = 0x0020,
  ADC12IFG6       = 0x0040,
  ADC12IFG7       = 0x0080,
  ADC12IFG8       = 0x0100,
  ADC12IFG9       = 0x0200,
  ADC12IFG10      = 0x0400,
  ADC12IFG11      = 0x0800,
  ADC12IFG12      = 0x1000,
  ADC12IFG13      = 0x2000,
  ADC12IFG14      = 0x4000,
  ADC12IFG15      = 0x8000
};

__no_init volatile union
{
  unsigned short ADC12IE;   /* ADC12+ Interrupt Enable */

  struct
  {
    unsigned short ADC12IE0        : 1; /* ADC12 Memory 0      Interrupt Enable */
    unsigned short ADC12IE1        : 1; /* ADC12 Memory 1      Interrupt Enable */
    unsigned short ADC12IE2        : 1; /* ADC12 Memory 2      Interrupt Enable */
    unsigned short ADC12IE3        : 1; /* ADC12 Memory 3      Interrupt Enable */
    unsigned short ADC12IE4        : 1; /* ADC12 Memory 4      Interrupt Enable */
    unsigned short ADC12IE5        : 1; /* ADC12 Memory 5      Interrupt Enable */
    unsigned short ADC12IE6        : 1; /* ADC12 Memory 6      Interrupt Enable */
    unsigned short ADC12IE7        : 1; /* ADC12 Memory 7      Interrupt Enable */
    unsigned short ADC12IE8        : 1; /* ADC12 Memory 8      Interrupt Enable */
    unsigned short ADC12IE9        : 1; /* ADC12 Memory 9      Interrupt Enable */
    unsigned short ADC12IE10       : 1; /* ADC12 Memory 10      Interrupt Enable */
    unsigned short ADC12IE11       : 1; /* ADC12 Memory 11      Interrupt Enable */
    unsigned short ADC12IE12       : 1; /* ADC12 Memory 12      Interrupt Enable */
    unsigned short ADC12IE13       : 1; /* ADC12 Memory 13      Interrupt Enable */
    unsigned short ADC12IE14       : 1; /* ADC12 Memory 14      Interrupt Enable */
    unsigned short ADC12IE15       : 1; /* ADC12 Memory 15      Interrupt Enable */
  } ADC12IE_bit;

  struct
  {
    unsigned char ADC12IE_L;
    unsigned char ADC12IE_H;
  };
} @0x070C;

enum {
  ADC12IE0        = 0x0001,
  ADC12IE1        = 0x0002,
  ADC12IE2        = 0x0004,
  ADC12IE3        = 0x0008,
  ADC12IE4        = 0x0010,
  ADC12IE5        = 0x0020,
  ADC12IE6        = 0x0040,
  ADC12IE7        = 0x0080,
  ADC12IE8        = 0x0100,
  ADC12IE9        = 0x0200,
  ADC12IE10       = 0x0400,
  ADC12IE11       = 0x0800,
  ADC12IE12       = 0x1000,
  ADC12IE13       = 0x2000,
  ADC12IE14       = 0x4000,
  ADC12IE15       = 0x8000
};

__no_init volatile union
{
  unsigned short ADC12IV;   /* ADC12+ Interrupt Vector Word */
  struct
  {
    unsigned char ADC12IV_L;
    unsigned char ADC12IV_H;
  };
} @0x070E;

__no_init volatile union
{
  unsigned short ADC12MEM0;   /* ADC12 Conversion Memory 0 */
  struct
  {
    unsigned char ADC12MEM0_L;
    unsigned char ADC12MEM0_H;
  };
} @0x0720;

__no_init volatile union
{
  unsigned short ADC12MEM1;   /* ADC12 Conversion Memory 1 */
  struct
  {
    unsigned char ADC12MEM1_L;
    unsigned char ADC12MEM1_H;
  };
} @0x0722;

__no_init volatile union
{
  unsigned short ADC12MEM2;   /* ADC12 Conversion Memory 2 */
  struct
  {
    unsigned char ADC12MEM2_L;
    unsigned char ADC12MEM2_H;
  };
} @0x0724;

__no_init volatile union
{
  unsigned short ADC12MEM3;   /* ADC12 Conversion Memory 3 */
  struct
  {
    unsigned char ADC12MEM3_L;
    unsigned char ADC12MEM3_H;
  };
} @0x0726;

__no_init volatile union
{
  unsigned short ADC12MEM4;   /* ADC12 Conversion Memory 4 */
  struct
  {
    unsigned char ADC12MEM4_L;
    unsigned char ADC12MEM4_H;
  };
} @0x0728;

__no_init volatile union
{
  unsigned short ADC12MEM5;   /* ADC12 Conversion Memory 5 */
  struct
  {
    unsigned char ADC12MEM5_L;
    unsigned char ADC12MEM5_H;
  };
} @0x072A;

__no_init volatile union
{
  unsigned short ADC12MEM6;   /* ADC12 Conversion Memory 6 */
  struct
  {
    unsigned char ADC12MEM6_L;
    unsigned char ADC12MEM6_H;
  };
} @0x072C;

__no_init volatile union
{
  unsigned short ADC12MEM7;   /* ADC12 Conversion Memory 7 */
  struct
  {
    unsigned char ADC12MEM7_L;
    unsigned char ADC12MEM7_H;
  };
} @0x072E;

__no_init volatile union
{
  unsigned short ADC12MEM8;   /* ADC12 Conversion Memory 8 */
  struct
  {
    unsigned char ADC12MEM8_L;
    unsigned char ADC12MEM8_H;
  };
} @0x0730;

__no_init volatile union
{
  unsigned short ADC12MEM9;   /* ADC12 Conversion Memory 9 */
  struct
  {
    unsigned char ADC12MEM9_L;
    unsigned char ADC12MEM9_H;
  };
} @0x0732;

__no_init volatile union
{
  unsigned short ADC12MEM10;   /* ADC12 Conversion Memory 10 */
  struct
  {
    unsigned char ADC12MEM10_L;
    unsigned char ADC12MEM10_H;
  };
} @0x0734;

__no_init volatile union
{
  unsigned short ADC12MEM11;   /* ADC12 Conversion Memory 11 */
  struct
  {
    unsigned char ADC12MEM11_L;
    unsigned char ADC12MEM11_H;
  };
} @0x0736;

__no_init volatile union
{
  unsigned short ADC12MEM12;   /* ADC12 Conversion Memory 12 */
  struct
  {
    unsigned char ADC12MEM12_L;
    unsigned char ADC12MEM12_H;
  };
} @0x0738;

__no_init volatile union
{
  unsigned short ADC12MEM13;   /* ADC12 Conversion Memory 13 */
  struct
  {
    unsigned char ADC12MEM13_L;
    unsigned char ADC12MEM13_H;
  };
} @0x073A;

__no_init volatile union
{
  unsigned short ADC12MEM14;   /* ADC12 Conversion Memory 14 */
  struct
  {
    unsigned char ADC12MEM14_L;
    unsigned char ADC12MEM14_H;
  };
} @0x073C;

__no_init volatile union
{
  unsigned short ADC12MEM15;   /* ADC12 Conversion Memory 15 */
  struct
  {
    unsigned char ADC12MEM15_L;
    unsigned char ADC12MEM15_H;
  };
} @0x073E;


__no_init volatile union
{
  unsigned char ADC12MCTL0;   /* ADC12 Memory Control 0 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL0_bit;
} @0x0710;


enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080
};


__no_init volatile union
{
  unsigned char ADC12MCTL1;   /* ADC12 Memory Control 1 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL1_bit;
} @0x0711;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL2;   /* ADC12 Memory Control 2 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL2_bit;
} @0x0712;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL3;   /* ADC12 Memory Control 3 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL3_bit;
} @0x0713;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL4;   /* ADC12 Memory Control 4 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL4_bit;
} @0x0714;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL5;   /* ADC12 Memory Control 5 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL5_bit;
} @0x0715;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL6;   /* ADC12 Memory Control 6 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL6_bit;
} @0x0716;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL7;   /* ADC12 Memory Control 7 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL7_bit;
} @0x0717;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL8;   /* ADC12 Memory Control 8 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL8_bit;
} @0x0718;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL9;   /* ADC12 Memory Control 9 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL9_bit;
} @0x0719;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL10;   /* ADC12 Memory Control 10 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL10_bit;
} @0x071A;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL11;   /* ADC12 Memory Control 11 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL11_bit;
} @0x071B;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL12;   /* ADC12 Memory Control 12 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL12_bit;
} @0x071C;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL13;   /* ADC12 Memory Control 13 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL13_bit;
} @0x071D;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL14;   /* ADC12 Memory Control 14 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL14_bit;
} @0x071E;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080,
};

*/

__no_init volatile union
{
  unsigned char ADC12MCTL15;   /* ADC12 Memory Control 15 */

  struct
  {
    unsigned char ADC12INCH0      : 1; /* ADC12 Input Channel Select Bit 0 */
    unsigned char ADC12INCH1      : 1; /* ADC12 Input Channel Select Bit 1 */
    unsigned char ADC12INCH2      : 1; /* ADC12 Input Channel Select Bit 2 */
    unsigned char ADC12INCH3      : 1; /* ADC12 Input Channel Select Bit 3 */
    unsigned char ADC12SREF0      : 1; /* ADC12 Select Reference Bit 0 */
    unsigned char ADC12SREF1      : 1; /* ADC12 Select Reference Bit 1 */
    unsigned char ADC12SREF2      : 1; /* ADC12 Select Reference Bit 2 */
    unsigned char ADC12EOS        : 1; /* ADC12 End of Sequence */
  }ADC12MCTL15_bit;
} @ 0x071F;


/*
enum {
  ADC12INCH0      = 0x0001,
  ADC12INCH1      = 0x0002,
  ADC12INCH2      = 0x0004,
  ADC12INCH3      = 0x0008,
  ADC12SREF0      = 0x0010,
  ADC12SREF1      = 0x0020,
  ADC12SREF2      = 0x0040,
  ADC12EOS        = 0x0080
};
*/



#define __MSP430_HAS_ADC12_PLUS__     /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC12_PLUS__ 0x0700
#define ADC12MEM_           ADC12MEM  /* ADC12 Conversion Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MEM            ADC12MEM0 /* ADC12 Conversion Memory (for assembler) */
#else
#endif
#define ADC12MCTL_          ADC12MCTL /* ADC12 Memory Control */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MCTL           ADC12MCTL0 /* ADC12 Memory Control (for assembler) */
#else
#endif
/* ADC12CTL0 Control Bits */
#define ADC12SC_L           (0x0001u)  /* ADC12 Start Conversion */
#define ADC12ENC_L          (0x0002u)  /* ADC12 Enable Conversion */
#define ADC12TOVIE_L        (0x0004u)  /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE_L         (0x0008u)  /* ADC12 Overflow interrupt enable */
#define ADC12ON_L           (0x0010u)  /* ADC12 On/enable */
#define ADC12REFON_L        (0x0020u)  /* ADC12 Reference on */
#define ADC12REF2_5V_L      (0x0040u)  /* ADC12 Ref 0:1.5V / 1:2.5V */
#define ADC12MSC_L          (0x0080u)  /* ADC12 Multiple SampleConversion */
/* ADC12CTL0 Control Bits */
#define ADC12SHT00_H        (0x0001u)  /* ADC12 Sample Hold 0 Select Bit: 0 */
#define ADC12SHT01_H        (0x0002u)  /* ADC12 Sample Hold 0 Select Bit: 1 */
#define ADC12SHT02_H        (0x0004u)  /* ADC12 Sample Hold 0 Select Bit: 2 */
#define ADC12SHT03_H        (0x0008u)  /* ADC12 Sample Hold 0 Select Bit: 3 */
#define ADC12SHT10_H        (0x0010u)  /* ADC12 Sample Hold 1 Select Bit: 0 */
#define ADC12SHT11_H        (0x0020u)  /* ADC12 Sample Hold 1 Select Bit: 1 */
#define ADC12SHT12_H        (0x0040u)  /* ADC12 Sample Hold 1 Select Bit: 2 */
#define ADC12SHT13_H        (0x0080u)  /* ADC12 Sample Hold 1 Select Bit: 3 */

#define ADC12SHT0_0         (0*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 0 */
#define ADC12SHT0_1         (1*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 1 */
#define ADC12SHT0_2         (2*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 2 */
#define ADC12SHT0_3         (3*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 3 */
#define ADC12SHT0_4         (4*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 4 */
#define ADC12SHT0_5         (5*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 5 */
#define ADC12SHT0_6         (6*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 6 */
#define ADC12SHT0_7         (7*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 7 */
#define ADC12SHT0_8         (8*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 8 */
#define ADC12SHT0_9         (9*0x100u)  /* ADC12 Sample Hold 0 Select Bit: 9 */
#define ADC12SHT0_10        (10*0x100u) /* ADC12 Sample Hold 0 Select Bit: 10 */
#define ADC12SHT0_11        (11*0x100u) /* ADC12 Sample Hold 0 Select Bit: 11 */
#define ADC12SHT0_12        (12*0x100u) /* ADC12 Sample Hold 0 Select Bit: 12 */
#define ADC12SHT0_13        (13*0x100u) /* ADC12 Sample Hold 0 Select Bit: 13 */
#define ADC12SHT0_14        (14*0x100u) /* ADC12 Sample Hold 0 Select Bit: 14 */
#define ADC12SHT0_15        (15*0x100u) /* ADC12 Sample Hold 0 Select Bit: 15 */

#define ADC12SHT1_0         (0*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 0 */
#define ADC12SHT1_1         (1*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 1 */
#define ADC12SHT1_2         (2*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 2 */
#define ADC12SHT1_3         (3*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 3 */
#define ADC12SHT1_4         (4*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 4 */
#define ADC12SHT1_5         (5*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 5 */
#define ADC12SHT1_6         (6*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 6 */
#define ADC12SHT1_7         (7*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 7 */
#define ADC12SHT1_8         (8*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 8 */
#define ADC12SHT1_9         (9*0x1000u)  /* ADC12 Sample Hold 1 Select Bit: 9 */
#define ADC12SHT1_10        (10*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 10 */
#define ADC12SHT1_11        (11*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 11 */
#define ADC12SHT1_12        (12*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 12 */
#define ADC12SHT1_13        (13*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 13 */
#define ADC12SHT1_14        (14*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 14 */
#define ADC12SHT1_15        (15*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 15 */
/* ADC12CTL1 Control Bits */
#define ADC12BUSY_L         (0x0001u)    /* ADC12 Busy */
#define ADC12CONSEQ0_L      (0x0002u)    /* ADC12 Conversion Sequence Select Bit: 0 */
#define ADC12CONSEQ1_L      (0x0004u)    /* ADC12 Conversion Sequence Select Bit: 1 */
#define ADC12SSEL0_L        (0x0008u)    /* ADC12 Clock Source Select Bit: 0 */
#define ADC12SSEL1_L        (0x0010u)    /* ADC12 Clock Source Select Bit: 1 */
#define ADC12DIV0_L         (0x0020u)    /* ADC12 Clock Divider Select Bit: 0 */
#define ADC12DIV1_L         (0x0040u)    /* ADC12 Clock Divider Select Bit: 1 */
#define ADC12DIV2_L         (0x0080u)    /* ADC12 Clock Divider Select Bit: 2 */
/* ADC12CTL1 Control Bits */
#define ADC12ISSH_H         (0x0001u)    /* ADC12 Invert Sample Hold Signal */
#define ADC12SHP_H          (0x0002u)    /* ADC12 Sample/Hold Pulse Mode */
#define ADC12SHS0_H         (0x0004u)    /* ADC12 Sample/Hold Source Bit: 0 */
#define ADC12SHS1_H         (0x0008u)    /* ADC12 Sample/Hold Source Bit: 1 */
#define ADC12CSTARTADD0_H   (0x0010u)    /* ADC12 Conversion Start Address Bit: 0 */
#define ADC12CSTARTADD1_H   (0x0020u)    /* ADC12 Conversion Start Address Bit: 1 */
#define ADC12CSTARTADD2_H   (0x0040u)    /* ADC12 Conversion Start Address Bit: 2 */
#define ADC12CSTARTADD3_H   (0x0080u)    /* ADC12 Conversion Start Address Bit: 3 */

#define ADC12CONSEQ_0        (0*2u)      /* ADC12 Conversion Sequence Select: 0 */
#define ADC12CONSEQ_1        (1*2u)      /* ADC12 Conversion Sequence Select: 1 */
#define ADC12CONSEQ_2        (2*2u)      /* ADC12 Conversion Sequence Select: 2 */
#define ADC12CONSEQ_3        (3*2u)      /* ADC12 Conversion Sequence Select: 3 */

#define ADC12SSEL_0          (0*8u)      /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1          (1*8u)      /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2          (2*8u)      /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3          (3*8u)      /* ADC12 Clock Source Select: 3 */

#define ADC12DIV_0           (0*0x20u)   /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1           (1*0x20u)   /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2           (2*0x20u)   /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3           (3*0x20u)   /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4           (4*0x20u)   /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5           (5*0x20u)   /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6           (6*0x20u)   /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7           (7*0x20u)   /* ADC12 Clock Divider Select: 7 */

#define ADC12SHS_0           (0*0x400u)  /* ADC12 Sample/Hold Source: 0 */
#define ADC12SHS_1           (1*0x400u)  /* ADC12 Sample/Hold Source: 1 */
#define ADC12SHS_2           (2*0x400u)  /* ADC12 Sample/Hold Source: 2 */
#define ADC12SHS_3           (3*0x400u)  /* ADC12 Sample/Hold Source: 3 */

#define ADC12CSTARTADD_0     (0*0x1000u) /* ADC12 Conversion Start Address: 0 */
#define ADC12CSTARTADD_1     (1*0x1000u) /* ADC12 Conversion Start Address: 1 */
#define ADC12CSTARTADD_2     (2*0x1000u) /* ADC12 Conversion Start Address: 2 */
#define ADC12CSTARTADD_3     (3*0x1000u) /* ADC12 Conversion Start Address: 3 */
#define ADC12CSTARTADD_4     (4*0x1000u) /* ADC12 Conversion Start Address: 4 */
#define ADC12CSTARTADD_5     (5*0x1000u) /* ADC12 Conversion Start Address: 5 */
#define ADC12CSTARTADD_6     (6*0x1000u) /* ADC12 Conversion Start Address: 6 */
#define ADC12CSTARTADD_7     (7*0x1000u) /* ADC12 Conversion Start Address: 7 */
#define ADC12CSTARTADD_8     (8*0x1000u) /* ADC12 Conversion Start Address: 8 */
#define ADC12CSTARTADD_9     (9*0x1000u) /* ADC12 Conversion Start Address: 9 */
#define ADC12CSTARTADD_10    (10*0x1000u) /* ADC12 Conversion Start Address: 10 */
#define ADC12CSTARTADD_11    (11*0x1000u) /* ADC12 Conversion Start Address: 11 */
#define ADC12CSTARTADD_12    (12*0x1000u) /* ADC12 Conversion Start Address: 12 */
#define ADC12CSTARTADD_13    (13*0x1000u) /* ADC12 Conversion Start Address: 13 */
#define ADC12CSTARTADD_14    (14*0x1000u) /* ADC12 Conversion Start Address: 14 */
#define ADC12CSTARTADD_15    (15*0x1000u) /* ADC12 Conversion Start Address: 15 */
/* ADC12CTL2 Control Bits */
#define ADC12REFBURST_L     (0x0001u)    /* ADC12+ Reference Burst */
#define ADC12REFOUT_L       (0x0002u)    /* ADC12+ Reference Out */
#define ADC12SR_L           (0x0004u)    /* ADC12+ Sampling Rate */
#define ADC12DF_L           (0x0008u)    /* ADC12+ Data Format */
#define ADC12RES0_L         (0x0010u)    /* ADC12+ Resolution Bit: 0 */
#define ADC12RES1_L         (0x0020u)    /* ADC12+ Resolution Bit: 1 */
#define ADC12TCOFF_L        (0x0080u)    /* ADC12+ Temperature Sensor Off */
/* ADC12CTL2 Control Bits */
#define ADC12PDIV_H         (0x0001u)    /* ADC12+ predivider 0:/1   1:/4 */

#define ADC12RES_0          (0x0000u)    /* ADC12+ Resolution : 8 Bit */
#define ADC12RES_1          (0x0010u)    /* ADC12+ Resolution : 10 Bit */
#define ADC12RES_2          (0x0020u)    /* ADC12+ Resolution : 12 Bit */
#define ADC12RES_3          (0x0030u)    /* ADC12+ Resolution : reserved */

#define ADC12INCH_0         (0x0000u)    /* ADC12 Input Channel 0 */
#define ADC12INCH_1         (0x0001u)    /* ADC12 Input Channel 1 */
#define ADC12INCH_2         (0x0002u)    /* ADC12 Input Channel 2 */
#define ADC12INCH_3         (0x0003u)    /* ADC12 Input Channel 3 */
#define ADC12INCH_4         (0x0004u)    /* ADC12 Input Channel 4 */
#define ADC12INCH_5         (0x0005u)    /* ADC12 Input Channel 5 */
#define ADC12INCH_6         (0x0006u)    /* ADC12 Input Channel 6 */
#define ADC12INCH_7         (0x0007u)    /* ADC12 Input Channel 7 */
#define ADC12INCH_8         (0x0008u)    /* ADC12 Input Channel 8 */
#define ADC12INCH_9         (0x0009u)    /* ADC12 Input Channel 9 */
#define ADC12INCH_10        (0x000Au)    /* ADC12 Input Channel 10 */
#define ADC12INCH_11        (0x000Bu)    /* ADC12 Input Channel 11 */
#define ADC12INCH_12        (0x000Cu)    /* ADC12 Input Channel 12 */
#define ADC12INCH_13        (0x000Du)    /* ADC12 Input Channel 13 */
#define ADC12INCH_14        (0x000Eu)    /* ADC12 Input Channel 14 */
#define ADC12INCH_15        (0x000Fu)    /* ADC12 Input Channel 15 */

#define ADC12SREF_0         (0*0x10u)    /* ADC12 Select Reference 0 */
#define ADC12SREF_1         (1*0x10u)    /* ADC12 Select Reference 1 */
#define ADC12SREF_2         (2*0x10u)    /* ADC12 Select Reference 2 */
#define ADC12SREF_3         (3*0x10u)    /* ADC12 Select Reference 3 */
#define ADC12SREF_4         (4*0x10u)    /* ADC12 Select Reference 4 */
#define ADC12SREF_5         (5*0x10u)    /* ADC12 Select Reference 5 */
#define ADC12SREF_6         (6*0x10u)    /* ADC12 Select Reference 6 */
#define ADC12SREF_7         (7*0x10u)    /* ADC12 Select Reference 7 */

#define ADC12IE0_L          (0x0001u)  /* ADC12 Memory 0      Interrupt Enable */
#define ADC12IE1_L          (0x0002u)  /* ADC12 Memory 1      Interrupt Enable */
#define ADC12IE2_L          (0x0004u)  /* ADC12 Memory 2      Interrupt Enable */
#define ADC12IE3_L          (0x0008u)  /* ADC12 Memory 3      Interrupt Enable */
#define ADC12IE4_L          (0x0010u)  /* ADC12 Memory 4      Interrupt Enable */
#define ADC12IE5_L          (0x0020u)  /* ADC12 Memory 5      Interrupt Enable */
#define ADC12IE6_L          (0x0040u)  /* ADC12 Memory 6      Interrupt Enable */
#define ADC12IE7_L          (0x0080u)  /* ADC12 Memory 7      Interrupt Enable */

#define ADC12IE8_H          (0x0001u)  /* ADC12 Memory 8      Interrupt Enable */
#define ADC12IE9_H          (0x0002u)  /* ADC12 Memory 9      Interrupt Enable */
#define ADC12IE10_H         (0x0004u)  /* ADC12 Memory 10      Interrupt Enable */
#define ADC12IE11_H         (0x0008u)  /* ADC12 Memory 11      Interrupt Enable */
#define ADC12IE12_H         (0x0010u)  /* ADC12 Memory 12      Interrupt Enable */
#define ADC12IE13_H         (0x0020u)  /* ADC12 Memory 13      Interrupt Enable */
#define ADC12IE14_H         (0x0040u)  /* ADC12 Memory 14      Interrupt Enable */
#define ADC12IE15_H         (0x0080u)  /* ADC12 Memory 15      Interrupt Enable */

#define ADC12IFG0_L         (0x0001u)  /* ADC12 Memory 0      Interrupt Flag */
#define ADC12IFG1_L         (0x0002u)  /* ADC12 Memory 1      Interrupt Flag */
#define ADC12IFG2_L         (0x0004u)  /* ADC12 Memory 2      Interrupt Flag */
#define ADC12IFG3_L         (0x0008u)  /* ADC12 Memory 3      Interrupt Flag */
#define ADC12IFG4_L         (0x0010u)  /* ADC12 Memory 4      Interrupt Flag */
#define ADC12IFG5_L         (0x0020u)  /* ADC12 Memory 5      Interrupt Flag */
#define ADC12IFG6_L         (0x0040u)  /* ADC12 Memory 6      Interrupt Flag */
#define ADC12IFG7_L         (0x0080u)  /* ADC12 Memory 7      Interrupt Flag */

#define ADC12IFG8_H         (0x0001u)  /* ADC12 Memory 8      Interrupt Flag */
#define ADC12IFG9_H         (0x0002u)  /* ADC12 Memory 9      Interrupt Flag */
#define ADC12IFG10_H        (0x0004u)  /* ADC12 Memory 10      Interrupt Flag */
#define ADC12IFG11_H        (0x0008u)  /* ADC12 Memory 11      Interrupt Flag */
#define ADC12IFG12_H        (0x0010u)  /* ADC12 Memory 12      Interrupt Flag */
#define ADC12IFG13_H        (0x0020u)  /* ADC12 Memory 13      Interrupt Flag */
#define ADC12IFG14_H        (0x0040u)  /* ADC12 Memory 14      Interrupt Flag */
#define ADC12IFG15_H        (0x0080u)  /* ADC12 Memory 15      Interrupt Flag */
/* ADC12IV Definitions */
#define ADC12IV_NONE        (0x0000u)    /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG  (0x0002u)    /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG (0x0004u)    /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0   (0x0006u)    /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1   (0x0008u)    /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2   (0x000Au)    /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3   (0x000Cu)    /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4   (0x000Eu)    /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5   (0x0010u)    /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6   (0x0012u)    /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7   (0x0014u)    /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8   (0x0016u)    /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9   (0x0018u)    /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10  (0x001Au)    /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11  (0x001Cu)    /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12  (0x001Eu)    /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13  (0x0020u)    /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14  (0x0022u)    /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15  (0x0024u)    /* ADC12IFG15 */

/*-------------------------------------------------------------------------
 *   CRC16
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short CRCDI;   /* CRC Data In Register */
  struct
  {
    unsigned char CRCDI_L;
    unsigned char CRCDI_H;
  }CRCDI_byte;
} @0x0150;

__no_init volatile union
{
  unsigned short CRCDIRB;   /* CRC data in reverse byte Register */
  struct
  {
    unsigned char CRCDIRB_L;
    unsigned char CRCDIRB_H;
  };
} @0x0152;

__no_init volatile union
{
  unsigned short CRCINIRES;   /* CRC Initialisation Register and Result Register */
  struct
  {
    unsigned char CRCINIRES_L;
    unsigned char CRCINIRES_H;
  };
} @0x0154;

__no_init volatile union
{
  unsigned short CRCRESR;   /* CRC reverse result Register */
  struct
  {
    unsigned char CRCRESR_L;
    unsigned char CRCRESR_H;
  };
} @0x0156;

#define __MSP430_HAS_CRC__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x0150

/*-------------------------------------------------------------------------
 *   DMA
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short DMACTL0;   /* DMA Module Control 0 */

  struct
  {
    unsigned short DMA0TSEL0       : 1; /* DMA channel 0 transfer select bit 0 */
    unsigned short DMA0TSEL1       : 1; /* DMA channel 0 transfer select bit 1 */
    unsigned short DMA0TSEL2       : 1; /* DMA channel 0 transfer select bit 2 */
    unsigned short DMA0TSEL3       : 1; /* DMA channel 0 transfer select bit 3 */
    unsigned short DMA0TSEL4       : 1; /* DMA channel 0 transfer select bit 4 */
    unsigned short                : 3;
    unsigned short DMA1TSEL0       : 1; /* DMA channel 1 transfer select bit 0 */
    unsigned short DMA1TSEL1       : 1; /* DMA channel 1 transfer select bit 1 */
    unsigned short DMA1TSEL2       : 1; /* DMA channel 1 transfer select bit 2 */
    unsigned short DMA1TSEL3       : 1; /* DMA channel 1 transfer select bit 3 */
    unsigned short DMA1TSEL4       : 1; /* DMA channel 1 transfer select bit 4 */
  } DMACTL0_bit;

  struct
  {
    unsigned char DMACTL0_L;
    unsigned char DMACTL0_H;
  };
} @0x0500;

enum {
  DMA0TSEL0       = 0x0001,
  DMA0TSEL1       = 0x0002,
  DMA0TSEL2       = 0x0004,
  DMA0TSEL3       = 0x0008,
  DMA0TSEL4       = 0x0010,
  DMA1TSEL0       = 0x0100,
  DMA1TSEL1       = 0x0200,
  DMA1TSEL2       = 0x0400,
  DMA1TSEL3       = 0x0800,
  DMA1TSEL4       = 0x1000
};

__no_init volatile union
{
  unsigned short DMACTL1;   /* DMA Module Control 1 */

  struct
  {
    unsigned short DMA2TSEL0       : 1; /* DMA channel 2 transfer select bit 0 */
    unsigned short DMA2TSEL1       : 1; /* DMA channel 2 transfer select bit 1 */
    unsigned short DMA2TSEL2       : 1; /* DMA channel 2 transfer select bit 2 */
    unsigned short DMA2TSEL3       : 1; /* DMA channel 2 transfer select bit 3 */
    unsigned short DMA2TSEL4       : 1; /* DMA channel 2 transfer select bit 4 */
  } DMACTL1_bit;

  struct
  {
    unsigned char DMACTL1_L;
    unsigned char DMACTL1_H;
  };
} @0x0502;

enum {
  DMA2TSEL0       = 0x0001,
  DMA2TSEL1       = 0x0002,
  DMA2TSEL2       = 0x0004,
  DMA2TSEL3       = 0x0008,
  DMA2TSEL4       = 0x0010
};

__no_init volatile union
{
  unsigned short DMACTL2;   /* DMA Module Control 2 */
  struct
  {
    unsigned char DMACTL2_L;
    unsigned char DMACTL2_H;
  };
} @0x0504;

__no_init volatile union
{
  unsigned short DMACTL3;   /* DMA Module Control 3 */
  struct
  {
    unsigned char DMACTL3_L;
    unsigned char DMACTL3_H;
  };
} @0x0506;

__no_init volatile union
{
  unsigned short DMACTL4;   /* DMA Module Control 4 */

  struct
  {
    unsigned short ENNMI           : 1; /* Enable NMI interruption of DMA */
    unsigned short ROUNDROBIN      : 1; /* Round-Robin DMA channel priorities */
    unsigned short DMARMWDIS       : 1; /* Inhibited DMA transfers during read-modify-write CPU operations */
  } DMACTL4_bit;

  struct
  {
    unsigned char DMACTL4_L;
    unsigned char DMACTL4_H;
  };
} @0x0508;

enum {
  ENNMI           = 0x0001,
  ROUNDROBIN      = 0x0002,
  DMARMWDIS       = 0x0004
};

__no_init volatile union
{
  unsigned short DMAIV;   /* DMA Interrupt Vector Word */
  struct
  {
    unsigned char DMAIV_L;
    unsigned char DMAIV_H;
  };
} @0x050E;

__no_init volatile union
{
  unsigned short DMA0CTL;   /* DMA Channel 0 Control */

  struct
  {
    unsigned short DMAREQ          : 1; /* Initiate DMA transfer with DMATSEL */
    unsigned short DMAABORT        : 1; /* DMA transfer aborted by NMI */
    unsigned short DMAIE           : 1; /* DMA interrupt enable */
    unsigned short DMAIFG          : 1; /* DMA interrupt flag */
    unsigned short DMAEN           : 1; /* DMA enable */
    unsigned short DMALEVEL        : 1; /* DMA level sensitive trigger select */
    unsigned short DMASRCBYTE      : 1; /* DMA source byte */
    unsigned short DMADSTBYTE      : 1; /* DMA destination byte */
    unsigned short DMASRCINCR0     : 1; /* DMA source increment bit 0 */
    unsigned short DMASRCINCR1     : 1; /* DMA source increment bit 1 */
    unsigned short DMADSTINCR0     : 1; /* DMA destination increment bit 0 */
    unsigned short DMADSTINCR1     : 1; /* DMA destination increment bit 1 */
    unsigned short DMADT0          : 1; /* DMA transfer mode bit 0 */
    unsigned short DMADT1          : 1; /* DMA transfer mode bit 1 */
    unsigned short DMADT2          : 1; /* DMA transfer mode bit 2 */
  } DMA0CTL_bit;

  struct
  {
    unsigned char DMA0CTL_L;
    unsigned char DMA0CTL_H;
  };
} @0x0510;

enum {
  DMAREQ          = 0x0001,
  DMAABORT        = 0x0002,
  DMAIE           = 0x0004,
  DMAIFG          = 0x0008,
  DMAEN           = 0x0010,
  DMALEVEL        = 0x0020,
  DMASRCBYTE      = 0x0040,
  DMADSTBYTE      = 0x0080,
  DMASRCINCR0     = 0x0100,
  DMASRCINCR1     = 0x0200,
  DMADSTINCR0     = 0x0400,
  DMADSTINCR1     = 0x0800,
  DMADT0          = 0x1000,
  DMADT1          = 0x2000,
  DMADT2          = 0x4000
};

__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA0SA;   /* DMA Channel 0 Source Address */
  struct
  {
    unsigned char DMA0SA_L;
    unsigned char DMA0SA_H;
  };
  struct
  {
    unsigned short DMA0SAL;
    unsigned short DMA0SAH;
  };
} @0x0512;

__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA0DA;   /* DMA Channel 0 Destination Address */
  struct
  {
    unsigned char DMA0DA_L;
    unsigned char DMA0DA_H;
  };
  struct
  {
    unsigned short DMA0DAL;
    unsigned short DMA0DAH;
  };
} @0x0516;


  /* DMA Channel 0 Transfer Size */
__no_init volatile unsigned short DMA0SZ @ 0x051A;


__no_init volatile union
{
  unsigned short DMA1CTL;   /* DMA Channel 1 Control */

  struct
  {
    unsigned short DMAREQ          : 1; /* Initiate DMA transfer with DMATSEL */
    unsigned short DMAABORT        : 1; /* DMA transfer aborted by NMI */
    unsigned short DMAIE           : 1; /* DMA interrupt enable */
    unsigned short DMAIFG          : 1; /* DMA interrupt flag */
    unsigned short DMAEN           : 1; /* DMA enable */
    unsigned short DMALEVEL        : 1; /* DMA level sensitive trigger select */
    unsigned short DMASRCBYTE      : 1; /* DMA source byte */
    unsigned short DMADSTBYTE      : 1; /* DMA destination byte */
    unsigned short DMASRCINCR0     : 1; /* DMA source increment bit 0 */
    unsigned short DMASRCINCR1     : 1; /* DMA source increment bit 1 */
    unsigned short DMADSTINCR0     : 1; /* DMA destination increment bit 0 */
    unsigned short DMADSTINCR1     : 1; /* DMA destination increment bit 1 */
    unsigned short DMADT0          : 1; /* DMA transfer mode bit 0 */
    unsigned short DMADT1          : 1; /* DMA transfer mode bit 1 */
    unsigned short DMADT2          : 1; /* DMA transfer mode bit 2 */
  } DMA1CTL_bit;

  struct
  {
    unsigned char DMA1CTL_L;
    unsigned char DMA1CTL_H;
  };
} @0x0520;

/*
enum {
  DMAREQ          = 0x0001,
  DMAABORT        = 0x0002,
  DMAIE           = 0x0004,
  DMAIFG          = 0x0008,
  DMAEN           = 0x0010,
  DMALEVEL        = 0x0020,
  DMASRCBYTE      = 0x0040,
  DMADSTBYTE      = 0x0080,
  DMASRCINCR0     = 0x0100,
  DMASRCINCR1     = 0x0200,
  DMADSTINCR0     = 0x0400,
  DMADSTINCR1     = 0x0800,
  DMADT0          = 0x1000,
  DMADT1          = 0x2000,
  DMADT2          = 0x4000,
};

*/
__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA1SA;   /* DMA Channel 1 Source Address */
  struct
  {
    unsigned char DMA1SA_L;
    unsigned char DMA1SA_H;
  };
  struct
  {
    unsigned short DMA1SAL;
    unsigned short DMA1SAH;
  };
} @0x0522;

__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA1DA;   /* DMA Channel 1 Destination Address */
  struct
  {
    unsigned char DMA1DA_L;
    unsigned char DMA1DA_H;
  };
  struct
  {
    unsigned short DMA1DAL;
    unsigned short DMA1DAH;
  };
} @0x0526;


  /* DMA Channel 1 Transfer Size */
__no_init volatile unsigned short DMA1SZ @ 0x052A;


__no_init volatile union
{
  unsigned short DMA2CTL;   /* DMA Channel 2 Control */

  struct
  {
    unsigned short DMAREQ          : 1; /* Initiate DMA transfer with DMATSEL */
    unsigned short DMAABORT        : 1; /* DMA transfer aborted by NMI */
    unsigned short DMAIE           : 1; /* DMA interrupt enable */
    unsigned short DMAIFG          : 1; /* DMA interrupt flag */
    unsigned short DMAEN           : 1; /* DMA enable */
    unsigned short DMALEVEL        : 1; /* DMA level sensitive trigger select */
    unsigned short DMASRCBYTE      : 1; /* DMA source byte */
    unsigned short DMADSTBYTE      : 1; /* DMA destination byte */
    unsigned short DMASRCINCR0     : 1; /* DMA source increment bit 0 */
    unsigned short DMASRCINCR1     : 1; /* DMA source increment bit 1 */
    unsigned short DMADSTINCR0     : 1; /* DMA destination increment bit 0 */
    unsigned short DMADSTINCR1     : 1; /* DMA destination increment bit 1 */
    unsigned short DMADT0          : 1; /* DMA transfer mode bit 0 */
    unsigned short DMADT1          : 1; /* DMA transfer mode bit 1 */
    unsigned short DMADT2          : 1; /* DMA transfer mode bit 2 */
  } DMA2CTL_bit;

  struct
  {
    unsigned char DMA2CTL_L;
    unsigned char DMA2CTL_H;
  };
} @0x0530;

/*
enum {
  DMAREQ          = 0x0001,
  DMAABORT        = 0x0002,
  DMAIE           = 0x0004,
  DMAIFG          = 0x0008,
  DMAEN           = 0x0010,
  DMALEVEL        = 0x0020,
  DMASRCBYTE      = 0x0040,
  DMADSTBYTE      = 0x0080,
  DMASRCINCR0     = 0x0100,
  DMASRCINCR1     = 0x0200,
  DMADSTINCR0     = 0x0400,
  DMADSTINCR1     = 0x0800,
  DMADT0          = 0x1000,
  DMADT1          = 0x2000,
  DMADT2          = 0x4000,
};

*/
__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA2SA;   /* DMA Channel 2 Source Address */
  struct
  {
    unsigned char DMA2SA_L;
    unsigned char DMA2SA_H;
  };
  struct
  {
    unsigned short DMA2SAL;
    unsigned short DMA2SAH;
  };
} @0x0532;

__no_init volatile union
{
  __ACCESS_20BIT_REG__ DMA2DA;   /* DMA Channel 2 Destination Address */
  struct
  {
    unsigned char DMA2DA_L;
    unsigned char DMA2DA_H;
  };
  struct
  {
    unsigned short DMA2DAL;
    unsigned short DMA2DAH;
  };
} @0x0536;


  /* DMA Channel 2 Transfer Size */
__no_init volatile unsigned short DMA2SZ @ 0x053A;


#define __MSP430_HAS_DMAX_3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_DMAX_3__ 0x0500
/* DMACTL0 Control Bits */
#define DMA0TSEL0_L         (0x0001u)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L         (0x0002u)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L         (0x0004u)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L         (0x0008u)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L         (0x0010u)    /* DMA channel 0 transfer select bit 4 */
/* DMACTL0 Control Bits */
#define DMA1TSEL0_H         (0x0001u)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H         (0x0002u)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H         (0x0004u)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H         (0x0008u)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H         (0x0010u)    /* DMA channel 1 transfer select bit 4 */
/* DMACTL01 Control Bits */
#define DMA2TSEL0_L         (0x0001u)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L         (0x0002u)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L         (0x0004u)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L         (0x0008u)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L         (0x0010u)    /* DMA channel 2 transfer select bit 4 */
/* DMACTL4 Control Bits */
#define ENNMI_L             (0x0001u)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN_L        (0x0002u)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS_L         (0x0004u)    /* Inhibited DMA transfers during read-modify-write CPU operations */
/* DMAxCTL Control Bits */
#define DMAREQ_L            (0x0001u)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT_L          (0x0002u)    /* DMA transfer aborted by NMI */
#define DMAIE_L             (0x0004u)    /* DMA interrupt enable */
#define DMAIFG_L            (0x0008u)    /* DMA interrupt flag */
#define DMAEN_L             (0x0010u)    /* DMA enable */
#define DMALEVEL_L          (0x0020u)    /* DMA level sensitive trigger select */
#define DMASRCBYTE_L        (0x0040u)    /* DMA source byte */
#define DMADSTBYTE_L        (0x0080u)    /* DMA destination byte */
/* DMAxCTL Control Bits */
#define DMASRCINCR0_H       (0x0001u)    /* DMA source increment bit 0 */
#define DMASRCINCR1_H       (0x0002u)    /* DMA source increment bit 1 */
#define DMADSTINCR0_H       (0x0004u)    /* DMA destination increment bit 0 */
#define DMADSTINCR1_H       (0x0008u)    /* DMA destination increment bit 1 */
#define DMADT0_H            (0x0010u)    /* DMA transfer mode bit 0 */
#define DMADT1_H            (0x0020u)    /* DMA transfer mode bit 1 */
#define DMADT2_H            (0x0040u)    /* DMA transfer mode bit 2 */

#define DMASWDW             (0*0x0040u)  /* DMA transfer: source word to destination word */
#define DMASBDW             (1*0x0040u)  /* DMA transfer: source byte to destination word */
#define DMASWDB             (2*0x0040u)  /* DMA transfer: source word to destination byte */
#define DMASBDB             (3*0x0040u)  /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0        (0*0x0100u)  /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1        (1*0x0100u)  /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2        (2*0x0100u)  /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3        (3*0x0100u)  /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0        (0*0x0400u)  /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1        (1*0x0400u)  /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2        (2*0x0400u)  /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3        (3*0x0400u)  /* DMA destination increment 3: destination address incremented */

#define DMADT_0             (0*0x1000u)  /* DMA transfer mode 0: Single transfer */
#define DMADT_1             (1*0x1000u)  /* DMA transfer mode 1: Block transfer */
#define DMADT_2             (2*0x1000u)  /* DMA transfer mode 2: Burst-Block transfer */
#define DMADT_3             (3*0x1000u)  /* DMA transfer mode 3: Burst-Block transfer */
#define DMADT_4             (4*0x1000u)  /* DMA transfer mode 4: Repeated Single transfer */
#define DMADT_5             (5*0x1000u)  /* DMA transfer mode 5: Repeated Block transfer */
#define DMADT_6             (6*0x1000u)  /* DMA transfer mode 6: Repeated Burst-Block transfer */
#define DMADT_7             (7*0x1000u)  /* DMA transfer mode 7: Repeated Burst-Block transfer */
/* DMAIV Definitions */
#define DMAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define DMAIV_DMA0IFG        (0x0002u)    /* DMA0IFG*/
#define DMAIV_DMA1IFG        (0x0004u)    /* DMA1IFG*/
#define DMAIV_DMA2IFG        (0x0006u)    /* DMA2IFG*/

#define DMA0TSEL_0          (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL_1          (1*0x0001u)  /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL_2          (2*0x0001u)  /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL_3          (3*0x0001u)  /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL_4          (4*0x0001u)  /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL_5          (5*0x0001u)  /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL_6          (6*0x0001u)  /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL_7          (7*0x0001u)  /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL_8          (8*0x0001u)  /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL_9          (9*0x0001u)  /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL_10         (10*0x0001u) /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL_11         (11*0x0001u) /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL_12         (12*0x0001u) /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL_13         (13*0x0001u) /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL_14         (14*0x0001u) /* DMA channel 0 transfer select 14: Reserved */
#define DMA0TSEL_15         (15*0x0001u) /* DMA channel 0 transfer select 15: Reserved */
#define DMA0TSEL_16         (16*0x0001u) /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL_17         (17*0x0001u) /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL_18         (18*0x0001u) /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL_19         (19*0x0001u) /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL_20         (20*0x0001u) /* DMA channel 0 transfer select 20: USCIA1 receive */
#define DMA0TSEL_21         (21*0x0001u) /* DMA channel 0 transfer select 21: USCIA1 transmit */
#define DMA0TSEL_22         (22*0x0001u) /* DMA channel 0 transfer select 22: USCIB1 receive */
#define DMA0TSEL_23         (23*0x0001u) /* DMA channel 0 transfer select 23: USCIB1 transmit */
#define DMA0TSEL_24         (24*0x0001u) /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL_25         (25*0x0001u) /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL_26         (26*0x0001u) /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL_27         (27*0x0001u) /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL_28         (28*0x0001u) /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL_29         (29*0x0001u) /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL_30         (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL_31         (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL_0          (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL_1          (1*0x0100u)  /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL_2          (2*0x0100u)  /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL_3          (3*0x0100u)  /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL_4          (4*0x0100u)  /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL_5          (5*0x0100u)  /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL_6          (6*0x0100u)  /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL_7          (7*0x0100u)  /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL_8          (8*0x0100u)  /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL_9          (9*0x0100u)  /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL_10         (10*0x0100u) /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL_11         (11*0x0100u) /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL_12         (12*0x0100u) /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL_13         (13*0x0100u) /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL_14         (14*0x0100u) /* DMA channel 1 transfer select 14: Reserved */
#define DMA1TSEL_15         (15*0x0100u) /* DMA channel 1 transfer select 15: Reserved */
#define DMA1TSEL_16         (16*0x0100u) /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL_17         (17*0x0100u) /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL_18         (18*0x0100u) /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL_19         (19*0x0100u) /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL_20         (20*0x0100u) /* DMA channel 1 transfer select 20: USCIA1 receive */
#define DMA1TSEL_21         (21*0x0100u) /* DMA channel 1 transfer select 21: USCIA1 transmit */
#define DMA1TSEL_22         (22*0x0100u) /* DMA channel 1 transfer select 22: USCIB1 receive */
#define DMA1TSEL_23         (23*0x0100u) /* DMA channel 1 transfer select 23: USCIB1 transmit */
#define DMA1TSEL_24         (24*0x0100u) /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL_25         (25*0x0100u) /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL_26         (26*0x0100u) /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL_27         (27*0x0100u) /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL_28         (28*0x0100u) /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL_29         (29*0x0100u) /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL_30         (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL_31         (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL_0          (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL_1          (1*0x0001u)  /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL_2          (2*0x0001u)  /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL_3          (3*0x0001u)  /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL_4          (4*0x0001u)  /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL_5          (5*0x0001u)  /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL_6          (6*0x0001u)  /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL_7          (7*0x0001u)  /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL_8          (8*0x0001u)  /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL_9          (9*0x0001u)  /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL_10         (10*0x0001u) /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL_11         (11*0x0001u) /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL_12         (12*0x0001u) /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL_13         (13*0x0001u) /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL_14         (14*0x0001u) /* DMA channel 2 transfer select 14: Reserved */
#define DMA2TSEL_15         (15*0x0001u) /* DMA channel 2 transfer select 15: Reserved */
#define DMA2TSEL_16         (16*0x0001u) /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL_17         (17*0x0001u) /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL_18         (18*0x0001u) /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL_19         (19*0x0001u) /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL_20         (20*0x0001u) /* DMA channel 2 transfer select 20: USCIA1 receive */
#define DMA2TSEL_21         (21*0x0001u) /* DMA channel 2 transfer select 21: USCIA1 transmit */
#define DMA2TSEL_22         (22*0x0001u) /* DMA channel 2 transfer select 22: USCIB1 receive */
#define DMA2TSEL_23         (23*0x0001u) /* DMA channel 2 transfer select 23: USCIB1 transmit */
#define DMA2TSEL_24         (24*0x0001u) /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL_25         (25*0x0001u) /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL_26         (26*0x0001u) /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL_27         (27*0x0001u) /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL_28         (28*0x0001u) /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL_29         (29*0x0001u) /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL_30         (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL_31         (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

#define DMA0TSEL__DMA_REQ   (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL__TA0CCR0   (1*0x0001u)  /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL__TA0CCR2   (2*0x0001u)  /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL__TA1CCR0   (3*0x0001u)  /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL__TA1CCR2   (4*0x0001u)  /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL__TB0CCR0   (5*0x0001u)  /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL__TB0CCR2   (6*0x0001u)  /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL__RES7      (7*0x0001u)  /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL__RES8      (8*0x0001u)  /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL__RES9      (9*0x0001u)  /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL__RES10     (10*0x0001u) /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL__RES11     (11*0x0001u) /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL__RES12     (12*0x0001u) /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL__RES13     (13*0x0001u) /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL__RES14     (14*0x0001u) /* DMA channel 0 transfer select 14: Reserved */
#define DMA0TSEL__RES15     (15*0x0001u) /* DMA channel 0 transfer select 15: Reserved */
#define DMA0TSEL__USCIA0RX  (16*0x0001u) /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL__USCIA0TX  (17*0x0001u) /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL__USCIB0RX  (18*0x0001u) /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL__USCIB0TX  (19*0x0001u) /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL__USCIA1RX  (20*0x0001u) /* DMA channel 0 transfer select 20: USCIA1 receive */
#define DMA0TSEL__USCIA1TX  (21*0x0001u) /* DMA channel 0 transfer select 21: USCIA1 transmit */
#define DMA0TSEL__USCIB1RX  (22*0x0001u) /* DMA channel 0 transfer select 22: USCIB1 receive */
#define DMA0TSEL__USCIB1TX  (23*0x0001u) /* DMA channel 0 transfer select 23: USCIB1 transmit */
#define DMA0TSEL__ADC12IFG  (24*0x0001u) /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL__RES25     (25*0x0001u) /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL__RES26     (26*0x0001u) /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL__RES27     (27*0x0001u) /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL__RES28     (28*0x0001u) /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL__MPY       (29*0x0001u) /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL__DMA2IFG   (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL__DMAE0     (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL__DMA_REQ   (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL__TA0CCR0   (1*0x0100u)  /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL__TA0CCR2   (2*0x0100u)  /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL__TA1CCR0   (3*0x0100u)  /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL__TA1CCR2   (4*0x0100u)  /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL__TB0CCR0   (5*0x0100u)  /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL__TB0CCR2   (6*0x0100u)  /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL__RES7      (7*0x0100u)  /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL__RES8      (8*0x0100u)  /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL__RES9      (9*0x0100u)  /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL__RES10     (10*0x0100u) /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL__RES11     (11*0x0100u) /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL__RES12     (12*0x0100u) /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL__RES13     (13*0x0100u) /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL__RES14     (14*0x0100u) /* DMA channel 1 transfer select 14: Reserved */
#define DMA1TSEL__RES15     (15*0x0100u) /* DMA channel 1 transfer select 15: Reserved */
#define DMA1TSEL__USCIA0RX  (16*0x0100u) /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL__USCIA0TX  (17*0x0100u) /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL__USCIB0RX  (18*0x0100u) /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL__USCIB0TX  (19*0x0100u) /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL__USCIA1RX  (20*0x0100u) /* DMA channel 1 transfer select 20: USCIA1 receive */
#define DMA1TSEL__USCIA1TX  (21*0x0100u) /* DMA channel 1 transfer select 21: USCIA1 transmit */
#define DMA1TSEL__USCIB1RX  (22*0x0100u) /* DMA channel 1 transfer select 22: USCIB1 receive */
#define DMA1TSEL__USCIB1TX  (23*0x0100u) /* DMA channel 1 transfer select 23: USCIB1 transmit */
#define DMA1TSEL__ADC12IFG  (24*0x0100u) /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL__RES25     (25*0x0100u) /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL__RES26     (26*0x0100u) /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL__RES27     (27*0x0100u) /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL__RES28     (28*0x0100u) /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL__MPY       (29*0x0100u) /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL__DMA0IFG   (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL__DMAE0     (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL__DMA_REQ   (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL__TA0CCR0   (1*0x0001u)  /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL__TA0CCR2   (2*0x0001u)  /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL__TA1CCR0   (3*0x0001u)  /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL__TA1CCR2   (4*0x0001u)  /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL__TB0CCR0   (5*0x0001u)  /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL__TB0CCR2   (6*0x0001u)  /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL__RES7      (7*0x0001u)  /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL__RES8      (8*0x0001u)  /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL__RES9      (9*0x0001u)  /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL__RES10     (10*0x0001u) /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL__RES11     (11*0x0001u) /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL__RES12     (12*0x0001u) /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL__RES13     (13*0x0001u) /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL__RES14     (14*0x0001u) /* DMA channel 2 transfer select 14: Reserved */
#define DMA2TSEL__RES15     (15*0x0001u) /* DMA channel 2 transfer select 15: Reserved */
#define DMA2TSEL__USCIA0RX  (16*0x0001u) /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL__USCIA0TX  (17*0x0001u) /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL__USCIB0RX  (18*0x0001u) /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL__USCIB0TX  (19*0x0001u) /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL__USCIA1RX  (20*0x0001u) /* DMA channel 2 transfer select 20: USCIA1 receive */
#define DMA2TSEL__USCIA1TX  (21*0x0001u) /* DMA channel 2 transfer select 21: USCIA1 transmit */
#define DMA2TSEL__USCIB1RX  (22*0x0001u) /* DMA channel 2 transfer select 22: USCIB1 receive */
#define DMA2TSEL__USCIB1TX  (23*0x0001u) /* DMA channel 2 transfer select 23: USCIB1 transmit */
#define DMA2TSEL__ADC12IFG  (24*0x0001u) /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL__RES25     (25*0x0001u) /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL__RES26     (26*0x0001u) /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL__RES27     (27*0x0001u) /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL__RES28     (28*0x0001u) /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL__MPY       (29*0x0001u) /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL__DMA1IFG   (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL__DMAE0     (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

/*-------------------------------------------------------------------------
 *   Flash
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short FCTL1;   /* FLASH Control 1 */

  struct
  {
    unsigned short                : 1;
    unsigned short ERASE           : 1; /* Enable bit for Flash segment erase */
    unsigned short MERAS           : 1; /* Enable bit for Flash mass erase */
    unsigned short                : 2;
    unsigned short SWRT            : 1; /* Smart Write enable */
    unsigned short WRT             : 1; /* Enable bit for Flash write */
    unsigned short BLKWRT          : 1; /* Enable bit for Flash segment write */
  } FCTL1_bit;

  struct
  {
    unsigned char FCTL1_L;
    unsigned char FCTL1_H;
  };
} @0x0140;

enum {
  ERASE           = 0x0002,
  MERAS           = 0x0004,
  SWRT            = 0x0020,
  WRT             = 0x0040,
  BLKWRT          = 0x0080
};

__no_init volatile union
{
  unsigned short FCTL3;   /* FLASH Control 3 */

  struct
  {
    unsigned short BUSY            : 1; /* Flash busy: 1 */
    unsigned short KEYV            : 1; /* Flash Key violation flag */
    unsigned short ACCVIFG         : 1; /* Flash Access violation flag */
    unsigned short WAIT            : 1; /* Wait flag for segment write */
    unsigned short LOCK            : 1; /* Lock bit: 1 - Flash is locked (read only) */
    unsigned short EMEX            : 1; /* Flash Emergency Exit */
    unsigned short LOCKA           : 1; /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
  } FCTL3_bit;

  struct
  {
    unsigned char FCTL3_L;
    unsigned char FCTL3_H;
  };
} @0x0144;

enum {
  BUSY            = 0x0001,
  KEYV            = 0x0002,
  ACCVIFG         = 0x0004,
  WAIT            = 0x0008,
  LOCK            = 0x0010,
  EMEX            = 0x0020,
  LOCKA           = 0x0040
};

__no_init volatile union
{
  unsigned short FCTL4;   /* FLASH Control 4 */

  struct
  {
    unsigned short VPE             : 1; /* Voltage Changed during Program Error Flag */
    unsigned short                : 3;
    unsigned short MGR0            : 1; /* Marginal read 0 mode. */
    unsigned short MGR1            : 1; /* Marginal read 1 mode. */
    unsigned short                : 1;
    unsigned short LOCKINFO        : 1; /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */
  } FCTL4_bit;

  struct
  {
    unsigned char FCTL4_L;
    unsigned char FCTL4_H;
  };
} @0x0146;

enum {
  VPE             = 0x0001,
  MGR0            = 0x0010,
  MGR1            = 0x0020,
  LOCKINFO        = 0x0080
};



#define __MSP430_HAS_FLASH__         /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FLASH__ 0x0140

#define FRPW                (0x9600u)  /* Flash password returned by read */
#define FWPW                (0xA500u)  /* Flash password for write */
#define FXPW                (0x3300u)  /* for use with XOR instruction */
#define FRKEY               (0x9600u)  /* (legacy definition) Flash key returned by read */
#define FWKEY               (0xA500u)  /* (legacy definition) Flash key for write */
#define FXKEY               (0x3300u)  /* (legacy definition) for use with XOR instruction */
#define ERASE_L             (0x0002u)  /* Enable bit for Flash segment erase */
#define MERAS_L             (0x0004u)  /* Enable bit for Flash mass erase */
#define SWRT_L              (0x0020u)  /* Smart Write enable */
#define WRT_L               (0x0040u)  /* Enable bit for Flash write */
#define BLKWRT_L            (0x0080u)  /* Enable bit for Flash segment write */
/* FCTL3 Control Bits */
#define BUSY_L              (0x0001u)  /* Flash busy: 1 */
#define KEYV_L              (0x0002u)  /* Flash Key violation flag */
#define ACCVIFG_L           (0x0004u)  /* Flash Access violation flag */
#define WAIT_L              (0x0008u)  /* Wait flag for segment write */
#define LOCK_L              (0x0010u)  /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX_L              (0x0020u)  /* Flash Emergency Exit */
#define LOCKA_L             (0x0040u)  /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
/* FCTL4 Control Bits */
#define VPE_L               (0x0001u)  /* Voltage Changed during Program Error Flag */
#define MGR0_L              (0x0010u)  /* Marginal read 0 mode. */
#define MGR1_L              (0x0020u)  /* Marginal read 1 mode. */
#define LOCKINFO_L          (0x0080u)  /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */

/*-------------------------------------------------------------------------
 *   MPY 16  Multiplier  16 Bit Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short MPY;   /* Multiply Unsigned/Operand 1 */
  struct
  {
    unsigned char MPY_L;
    unsigned char MPY_H;
  };
} @0x04C0;

__no_init volatile union
{
  unsigned short MPYS;   /* Multiply Signed/Operand 1 */
  struct
  {
    unsigned char MPYS_L;
    unsigned char MPYS_H;
  };
} @0x04C2;

__no_init volatile union
{
  unsigned short MAC;   /* Multiply Unsigned and Accumulate/Operand 1 */
  struct
  {
    unsigned char MAC_L;
    unsigned char MAC_H;
  };
} @0x04C4;

__no_init volatile union
{
  unsigned short MACS;   /* Multiply Signed and Accumulate/Operand 1 */
  struct
  {
    unsigned char MACS_L;
    unsigned char MACS_H;
  };
} @0x04C6;

__no_init volatile union
{
  unsigned short OP2;   /* Operand 2 */
  struct
  {
    unsigned char OP2_L;
    unsigned char OP2_H;
  };
} @0x04C8;

__no_init volatile union
{
  unsigned short RESLO;   /* Result Low Word */
  struct
  {
    unsigned char RESLO_L;
    unsigned char RESLO_H;
  };
} @0x04CA;

__no_init volatile union
{
  unsigned short RESHI;   /* Result High Word */
  struct
  {
    unsigned char RESHI_L;
    unsigned char RESHI_H;
  };
} @0x04CC;

__no_init volatile union
{
  unsigned __READ short SUMEXT;   /* Sum Extend */
  struct
  {
    unsigned __READ char SUMEXT_L;
    unsigned __READ char SUMEXT_H;
  };
} @0x04CE;

__no_init volatile union
{
  unsigned short MPY32CTL0;   /* MPY32 Control Register 0 */

  struct
  {
    unsigned short MPYC            : 1; /* Carry of the multiplier */
    unsigned short                : 1;
    unsigned short MPYFRAC         : 1; /* Fractional mode */
    unsigned short MPYSAT          : 1; /* Saturation mode */
    unsigned short MPYM0           : 1; /* Multiplier mode Bit:0 */
    unsigned short MPYM1           : 1; /* Multiplier mode Bit:1 */
    unsigned short OP1_32          : 1; /*  */
    unsigned short OP2_32          : 1; /*  */
    unsigned short MPYDLYWRTEN     : 1; /* Delayed write enable */
    unsigned short MPYDLY32        : 1; /* Delayed write mode */
  } MPY32CTL0_bit;

  struct
  {
    unsigned char MPY32CTL0_L;
    unsigned char MPY32CTL0_H;
  };
} @0x04EC;

enum {
  MPYC            = 0x0001,
  MPYFRAC         = 0x0004,
  MPYSAT          = 0x0008,
  MPYM0           = 0x0010,
  MPYM1           = 0x0020,
  OP1_32          = 0x0040,
  OP2_32          = 0x0080,
  MPYDLYWRTEN     = 0x0100,
  MPYDLY32        = 0x0200
};



#define __MSP430_HAS_MPY32__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPY32__ 0x04C0

#define MPY_B               MPY_L      /* Multiply Unsigned/Operand 1 (Byte Access) */
#define MPYS_B              MPYS_L     /* Multiply Signed/Operand 1 (Byte Access) */
#define MAC_B               MAC_L      /* Multiply Unsigned and Accumulate/Operand 1 (Byte Access) */
#define MACS_B              MACS_L     /* Multiply Signed and Accumulate/Operand 1 (Byte Access) */
#define OP2_B               OP2_L      /* Operand 2 (Byte Access) */
#define MPY32L_B            MPY32L_L   /* 32-bit operand 1 - multiply - low word (Byte Access) */
#define MPY32H_B            MPY32H_L   /* 32-bit operand 1 - multiply - high word (Byte Access) */
#define MPYS32L_B           MPYS32L_L  /* 32-bit operand 1 - signed multiply - low word (Byte Access) */
#define MPYS32H_B           MPYS32H_L  /* 32-bit operand 1 - signed multiply - high word (Byte Access) */
#define MAC32L_B            MAC32L_L   /* 32-bit operand 1 - multiply accumulate - low word (Byte Access) */
#define MAC32H_B            MAC32H_L   /* 32-bit operand 1 - multiply accumulate - high word (Byte Access) */
#define MACS32L_B           MACS32L_L  /* 32-bit operand 1 - signed multiply accumulate - low word (Byte Access) */
#define MACS32H_B           MACS32H_L  /* 32-bit operand 1 - signed multiply accumulate - high word (Byte Access) */
#define OP2L_B              OP2L_L     /* 32-bit operand 2 - low word (Byte Access) */
#define OP2H_B              OP2H_L     /* 32-bit operand 2 - high word (Byte Access) */
/* MPY32CTL0 Control Bits */
#define MPYC_L              (0x0001u)  /* Carry of the multiplier */
#define MPYFRAC_L           (0x0004u)  /* Fractional mode */
#define MPYSAT_L            (0x0008u)  /* Saturation mode */
#define MPYM0_L             (0x0010u)  /* Multiplier mode Bit:0 */
#define MPYM1_L             (0x0020u)  /* Multiplier mode Bit:1 */
#define OP1_32_L            (0x0040u)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32_L            (0x0080u)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */
#define MPYDLYWRTEN_H       (0x0001u)  /* Delayed write enable */
#define MPYDLY32_H          (0x0002u)  /* Delayed write mode */

#define MPYM_0              (0x0000u)  /* Multiplier mode: MPY */
#define MPYM_1              (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM_2              (0x0020u)  /* Multiplier mode: MAC */
#define MPYM_3              (0x0030u)  /* Multiplier mode: MACS */
#define MPYM__MPY           (0x0000u)  /* Multiplier mode: MPY */
#define MPYM__MPYS          (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM__MAC           (0x0020u)  /* Multiplier mode: MAC */
#define MPYM__MACS          (0x0030u)  /* Multiplier mode: MACS */

/*-------------------------------------------------------------------------
 *   MPY 32  Multiplier  32 Bit Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short MPY32L;   /* 32-bit operand 1 - multiply - low word */
  struct
  {
    unsigned char MPY32L_L;
    unsigned char MPY32L_H;
  };
} @0x04D0;

__no_init volatile union
{
  unsigned short MPY32H;   /* 32-bit operand 1 - multiply - high word */
  struct
  {
    unsigned char MPY32H_L;
    unsigned char MPY32H_H;
  };
} @0x04D2;

__no_init volatile union
{
  unsigned short MPYS32L;   /* 32-bit operand 1 - signed multiply - low word */
  struct
  {
    unsigned char MPYS32L_L;
    unsigned char MPYS32L_H;
  };
} @0x04D4;

__no_init volatile union
{
  unsigned short MPYS32H;   /* 32-bit operand 1 - signed multiply - high word */
  struct
  {
    unsigned char MPYS32H_L;
    unsigned char MPYS32H_H;
  };
} @0x04D6;

__no_init volatile union
{
  unsigned short MAC32L;   /* 32-bit operand 1 - multiply accumulate - low word */
  struct
  {
    unsigned char MAC32L_L;
    unsigned char MAC32L_H;
  };
} @0x04D8;

__no_init volatile union
{
  unsigned short MAC32H;   /* 32-bit operand 1 - multiply accumulate - high word */
  struct
  {
    unsigned char MAC32H_L;
    unsigned char MAC32H_H;
  };
} @0x04DA;

__no_init volatile union
{
  unsigned short MACS32L;   /* 32-bit operand 1 - signed multiply accumulate - low word */
  struct
  {
    unsigned char MACS32L_L;
    unsigned char MACS32L_H;
  };
} @0x04DC;

__no_init volatile union
{
  unsigned short MACS32H;   /* 32-bit operand 1 - signed multiply accumulate - high word */
  struct
  {
    unsigned char MACS32H_L;
    unsigned char MACS32H_H;
  };
} @0x04DE;

__no_init volatile union
{
  unsigned short OP2L;   /* 32-bit operand 2 - low word */
  struct
  {
    unsigned char OP2L_L;
    unsigned char OP2L_H;
  };
} @0x04E0;

__no_init volatile union
{
  unsigned short OP2H;   /* 32-bit operand 2 - high word */
  struct
  {
    unsigned char OP2H_L;
    unsigned char OP2H_H;
  };
} @0x04E2;

__no_init volatile union
{
  unsigned short RES0;   /* 32x32-bit result 0 - least significant word */
  struct
  {
    unsigned char RES0_L;
    unsigned char RES0_H;
  };
} @0x04E4;

__no_init volatile union
{
  unsigned short RES1;   /* 32x32-bit result 1 */
  struct
  {
    unsigned char RES1_L;
    unsigned char RES1_H;
  };
} @0x04E6;

__no_init volatile union
{
  unsigned short RES2;   /* 32x32-bit result 2 */
  struct
  {
    unsigned char RES2_L;
    unsigned char RES2_H;
  };
} @0x04E8;

__no_init volatile union
{
  unsigned short RES3;   /* 32x32-bit result 3 - most significant word */
  struct
  {
    unsigned char RES3_L;
    unsigned char RES3_H;
  };
} @0x04EA;

#define __MSP430_HAS_MPY32__          /* Definition to show that Module is available */

/*-------------------------------------------------------------------------
 *   Port A
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PAIN;   /* Port A Input */

  struct
  {
    unsigned __READ short PAIN0           : 1; /*  */
    unsigned __READ short PAIN1           : 1; /*  */
    unsigned __READ short PAIN2           : 1; /*  */
    unsigned __READ short PAIN3           : 1; /*  */
    unsigned __READ short PAIN4           : 1; /*  */
    unsigned __READ short PAIN5           : 1; /*  */
    unsigned __READ short PAIN6           : 1; /*  */
    unsigned __READ short PAIN7           : 1; /*  */
    unsigned __READ short PAIN8           : 1; /*  */
    unsigned __READ short PAIN9           : 1; /*  */
    unsigned __READ short PAIN10          : 1; /*  */
    unsigned __READ short PAIN11          : 1; /*  */
    unsigned __READ short PAIN12          : 1; /*  */
    unsigned __READ short PAIN13          : 1; /*  */
    unsigned __READ short PAIN14          : 1; /*  */
    unsigned __READ short PAIN15          : 1; /*  */
  } PAIN_bit;

  struct
  {
    unsigned __READ char PAIN_L;
    unsigned __READ char PAIN_H;
  };
  struct
  {
    unsigned char P1IN;   /* Port 1 Input */
    unsigned char P2IN;   /* Port 2 Input */
  };
  struct
  {
    struct
    {
      unsigned char P1IN0           : 1; /*  */
      unsigned char P1IN1           : 1; /*  */
      unsigned char P1IN2           : 1; /*  */
      unsigned char P1IN3           : 1; /*  */
      unsigned char P1IN4           : 1; /*  */
      unsigned char P1IN5           : 1; /*  */
      unsigned char P1IN6           : 1; /*  */
      unsigned char P1IN7           : 1; /*  */
    } P1IN_bit;

    struct
    {
      unsigned char P2IN0           : 1; /*  */
      unsigned char P2IN1           : 1; /*  */
      unsigned char P2IN2           : 1; /*  */
      unsigned char P2IN3           : 1; /*  */
      unsigned char P2IN4           : 1; /*  */
      unsigned char P2IN5           : 1; /*  */
      unsigned char P2IN6           : 1; /*  */
      unsigned char P2IN7           : 1; /*  */
    } P2IN_bit;
  }; 
} @0x0200;

enum {
  PAIN0           = 0x0001,
  PAIN1           = 0x0002,
  PAIN2           = 0x0004,
  PAIN3           = 0x0008,
  PAIN4           = 0x0010,
  PAIN5           = 0x0020,
  PAIN6           = 0x0040,
  PAIN7           = 0x0080,
  PAIN8           = 0x0100,
  PAIN9           = 0x0200,
  PAIN10          = 0x0400,
  PAIN11          = 0x0800,
  PAIN12          = 0x1000,
  PAIN13          = 0x2000,
  PAIN14          = 0x4000,
  PAIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PAOUT;   /* Port A Output */

  struct
  {
    unsigned short PAOUT0          : 1; /*  */
    unsigned short PAOUT1          : 1; /*  */
    unsigned short PAOUT2          : 1; /*  */
    unsigned short PAOUT3          : 1; /*  */
    unsigned short PAOUT4          : 1; /*  */
    unsigned short PAOUT5          : 1; /*  */
    unsigned short PAOUT6          : 1; /*  */
    unsigned short PAOUT7          : 1; /*  */
    unsigned short PAOUT8          : 1; /*  */
    unsigned short PAOUT9          : 1; /*  */
    unsigned short PAOUT10         : 1; /*  */
    unsigned short PAOUT11         : 1; /*  */
    unsigned short PAOUT12         : 1; /*  */
    unsigned short PAOUT13         : 1; /*  */
    unsigned short PAOUT14         : 1; /*  */
    unsigned short PAOUT15         : 1; /*  */
  } PAOUT_bit;

  struct
  {
    unsigned char PAOUT_L;
    unsigned char PAOUT_H;
  };
  struct
  {
    unsigned char P1OUT;   /* Port 1 Output */
    unsigned char P2OUT;   /* Port 2 Output */
  };
  struct
  {
    struct
    {
      unsigned char P1OUT0          : 1; /*  */
      unsigned char P1OUT1          : 1; /*  */
      unsigned char P1OUT2          : 1; /*  */
      unsigned char P1OUT3          : 1; /*  */
      unsigned char P1OUT4          : 1; /*  */
      unsigned char P1OUT5          : 1; /*  */
      unsigned char P1OUT6          : 1; /*  */
      unsigned char P1OUT7          : 1; /*  */
    } P1OUT_bit;

    struct
    {
      unsigned char P2OUT0          : 1; /*  */
      unsigned char P2OUT1          : 1; /*  */
      unsigned char P2OUT2          : 1; /*  */
      unsigned char P2OUT3          : 1; /*  */
      unsigned char P2OUT4          : 1; /*  */
      unsigned char P2OUT5          : 1; /*  */
      unsigned char P2OUT6          : 1; /*  */
      unsigned char P2OUT7          : 1; /*  */
    } P2OUT_bit;
  }; 
} @0x0202;

enum {
  PAOUT0          = 0x0001,
  PAOUT1          = 0x0002,
  PAOUT2          = 0x0004,
  PAOUT3          = 0x0008,
  PAOUT4          = 0x0010,
  PAOUT5          = 0x0020,
  PAOUT6          = 0x0040,
  PAOUT7          = 0x0080,
  PAOUT8          = 0x0100,
  PAOUT9          = 0x0200,
  PAOUT10         = 0x0400,
  PAOUT11         = 0x0800,
  PAOUT12         = 0x1000,
  PAOUT13         = 0x2000,
  PAOUT14         = 0x4000,
  PAOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PADIR;   /* Port A Direction */

  struct
  {
    unsigned short PADIR0          : 1; /*  */
    unsigned short PADIR1          : 1; /*  */
    unsigned short PADIR2          : 1; /*  */
    unsigned short PADIR3          : 1; /*  */
    unsigned short PADIR4          : 1; /*  */
    unsigned short PADIR5          : 1; /*  */
    unsigned short PADIR6          : 1; /*  */
    unsigned short PADIR7          : 1; /*  */
    unsigned short PADIR8          : 1; /*  */
    unsigned short PADIR9          : 1; /*  */
    unsigned short PADIR10         : 1; /*  */
    unsigned short PADIR11         : 1; /*  */
    unsigned short PADIR12         : 1; /*  */
    unsigned short PADIR13         : 1; /*  */
    unsigned short PADIR14         : 1; /*  */
    unsigned short PADIR15         : 1; /*  */
  } PADIR_bit;

  struct
  {
    unsigned char PADIR_L;
    unsigned char PADIR_H;
  };
  struct
  {
    unsigned char P1DIR;   /* Port 1 Direction */
    unsigned char P2DIR;   /* Port 2 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P1DIR0          : 1; /*  */
      unsigned char P1DIR1          : 1; /*  */
      unsigned char P1DIR2          : 1; /*  */
      unsigned char P1DIR3          : 1; /*  */
      unsigned char P1DIR4          : 1; /*  */
      unsigned char P1DIR5          : 1; /*  */
      unsigned char P1DIR6          : 1; /*  */
      unsigned char P1DIR7          : 1; /*  */
    } P1DIR_bit;

    struct
    {
      unsigned char P2DIR0          : 1; /*  */
      unsigned char P2DIR1          : 1; /*  */
      unsigned char P2DIR2          : 1; /*  */
      unsigned char P2DIR3          : 1; /*  */
      unsigned char P2DIR4          : 1; /*  */
      unsigned char P2DIR5          : 1; /*  */
      unsigned char P2DIR6          : 1; /*  */
      unsigned char P2DIR7          : 1; /*  */
    } P2DIR_bit;
  }; 
} @0x0204;

enum {
  PADIR0          = 0x0001,
  PADIR1          = 0x0002,
  PADIR2          = 0x0004,
  PADIR3          = 0x0008,
  PADIR4          = 0x0010,
  PADIR5          = 0x0020,
  PADIR6          = 0x0040,
  PADIR7          = 0x0080,
  PADIR8          = 0x0100,
  PADIR9          = 0x0200,
  PADIR10         = 0x0400,
  PADIR11         = 0x0800,
  PADIR12         = 0x1000,
  PADIR13         = 0x2000,
  PADIR14         = 0x4000,
  PADIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PAREN;   /* Port A Resistor Enable */

  struct
  {
    unsigned short PAREN0          : 1; /*  */
    unsigned short PAREN1          : 1; /*  */
    unsigned short PAREN2          : 1; /*  */
    unsigned short PAREN3          : 1; /*  */
    unsigned short PAREN4          : 1; /*  */
    unsigned short PAREN5          : 1; /*  */
    unsigned short PAREN6          : 1; /*  */
    unsigned short PAREN7          : 1; /*  */
    unsigned short PAREN8          : 1; /*  */
    unsigned short PAREN9          : 1; /*  */
    unsigned short PAREN10         : 1; /*  */
    unsigned short PAREN11         : 1; /*  */
    unsigned short PAREN12         : 1; /*  */
    unsigned short PAREN13         : 1; /*  */
    unsigned short PAREN14         : 1; /*  */
    unsigned short PAREN15         : 1; /*  */
  } PAREN_bit;

  struct
  {
    unsigned char PAREN_L;
    unsigned char PAREN_H;
  };
  struct
  {
    unsigned char P1REN;   /* Port 1 Resistor Enable */
    unsigned char P2REN;   /* Port 2 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P1REN0          : 1; /*  */
      unsigned char P1REN1          : 1; /*  */
      unsigned char P1REN2          : 1; /*  */
      unsigned char P1REN3          : 1; /*  */
      unsigned char P1REN4          : 1; /*  */
      unsigned char P1REN5          : 1; /*  */
      unsigned char P1REN6          : 1; /*  */
      unsigned char P1REN7          : 1; /*  */
    } P1REN_bit;

    struct
    {
      unsigned char P2REN0          : 1; /*  */
      unsigned char P2REN1          : 1; /*  */
      unsigned char P2REN2          : 1; /*  */
      unsigned char P2REN3          : 1; /*  */
      unsigned char P2REN4          : 1; /*  */
      unsigned char P2REN5          : 1; /*  */
      unsigned char P2REN6          : 1; /*  */
      unsigned char P2REN7          : 1; /*  */
    } P2REN_bit;
  }; 
} @0x0206;

enum {
  PAREN0          = 0x0001,
  PAREN1          = 0x0002,
  PAREN2          = 0x0004,
  PAREN3          = 0x0008,
  PAREN4          = 0x0010,
  PAREN5          = 0x0020,
  PAREN6          = 0x0040,
  PAREN7          = 0x0080,
  PAREN8          = 0x0100,
  PAREN9          = 0x0200,
  PAREN10         = 0x0400,
  PAREN11         = 0x0800,
  PAREN12         = 0x1000,
  PAREN13         = 0x2000,
  PAREN14         = 0x4000,
  PAREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PADS;   /* Port A Drive Strenght */

  struct
  {
    unsigned short PADS0           : 1; /*  */
    unsigned short PADS1           : 1; /*  */
    unsigned short PADS2           : 1; /*  */
    unsigned short PADS3           : 1; /*  */
    unsigned short PADS4           : 1; /*  */
    unsigned short PADS5           : 1; /*  */
    unsigned short PADS6           : 1; /*  */
    unsigned short PADS7           : 1; /*  */
    unsigned short PADS8           : 1; /*  */
    unsigned short PADS9           : 1; /*  */
    unsigned short PADS10          : 1; /*  */
    unsigned short PADS11          : 1; /*  */
    unsigned short PADS12          : 1; /*  */
    unsigned short PADS13          : 1; /*  */
    unsigned short PADS14          : 1; /*  */
    unsigned short PADS15          : 1; /*  */
  } PADS_bit;

  struct
  {
    unsigned char PADS_L;
    unsigned char PADS_H;
  };
  struct
  {
    unsigned char P1DS;   /* Port 1 Drive Strenght */
    unsigned char P2DS;   /* Port 2 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P1DS0           : 1; /*  */
      unsigned char P1DS1           : 1; /*  */
      unsigned char P1DS2           : 1; /*  */
      unsigned char P1DS3           : 1; /*  */
      unsigned char P1DS4           : 1; /*  */
      unsigned char P1DS5           : 1; /*  */
      unsigned char P1DS6           : 1; /*  */
      unsigned char P1DS7           : 1; /*  */
    } P1DS_bit;

    struct
    {
      unsigned char P2DS0           : 1; /*  */
      unsigned char P2DS1           : 1; /*  */
      unsigned char P2DS2           : 1; /*  */
      unsigned char P2DS3           : 1; /*  */
      unsigned char P2DS4           : 1; /*  */
      unsigned char P2DS5           : 1; /*  */
      unsigned char P2DS6           : 1; /*  */
      unsigned char P2DS7           : 1; /*  */
    } P2DS_bit;
  }; 
} @0x0208;

enum {
  PADS0           = 0x0001,
  PADS1           = 0x0002,
  PADS2           = 0x0004,
  PADS3           = 0x0008,
  PADS4           = 0x0010,
  PADS5           = 0x0020,
  PADS6           = 0x0040,
  PADS7           = 0x0080,
  PADS8           = 0x0100,
  PADS9           = 0x0200,
  PADS10          = 0x0400,
  PADS11          = 0x0800,
  PADS12          = 0x1000,
  PADS13          = 0x2000,
  PADS14          = 0x4000,
  PADS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PASEL;   /* Port A Selection */

  struct
  {
    unsigned short PASEL0          : 1; /*  */
    unsigned short PASEL1          : 1; /*  */
    unsigned short PASEL2          : 1; /*  */
    unsigned short PASEL3          : 1; /*  */
    unsigned short PASEL4          : 1; /*  */
    unsigned short PASEL5          : 1; /*  */
    unsigned short PASEL6          : 1; /*  */
    unsigned short PASEL7          : 1; /*  */
    unsigned short PASEL8          : 1; /*  */
    unsigned short PASEL9          : 1; /*  */
    unsigned short PASEL10         : 1; /*  */
    unsigned short PASEL11         : 1; /*  */
    unsigned short PASEL12         : 1; /*  */
    unsigned short PASEL13         : 1; /*  */
    unsigned short PASEL14         : 1; /*  */
    unsigned short PASEL15         : 1; /*  */
  } PASEL_bit;

  struct
  {
    unsigned char PASEL_L;
    unsigned char PASEL_H;
  };
  struct
  {
    unsigned char P1SEL;   /* Port 1 Selection */
    unsigned char P2SEL;   /* Port 2 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P1SEL0          : 1; /*  */
      unsigned char P1SEL1          : 1; /*  */
      unsigned char P1SEL2          : 1; /*  */
      unsigned char P1SEL3          : 1; /*  */
      unsigned char P1SEL4          : 1; /*  */
      unsigned char P1SEL5          : 1; /*  */
      unsigned char P1SEL6          : 1; /*  */
      unsigned char P1SEL7          : 1; /*  */
    } P1SEL_bit;

    struct
    {
      unsigned char P2SEL0          : 1; /*  */
      unsigned char P2SEL1          : 1; /*  */
      unsigned char P2SEL2          : 1; /*  */
      unsigned char P2SEL3          : 1; /*  */
      unsigned char P2SEL4          : 1; /*  */
      unsigned char P2SEL5          : 1; /*  */
      unsigned char P2SEL6          : 1; /*  */
      unsigned char P2SEL7          : 1; /*  */
    } P2SEL_bit;
  }; 
} @0x020A;

enum {
  PASEL0          = 0x0001,
  PASEL1          = 0x0002,
  PASEL2          = 0x0004,
  PASEL3          = 0x0008,
  PASEL4          = 0x0010,
  PASEL5          = 0x0020,
  PASEL6          = 0x0040,
  PASEL7          = 0x0080,
  PASEL8          = 0x0100,
  PASEL9          = 0x0200,
  PASEL10         = 0x0400,
  PASEL11         = 0x0800,
  PASEL12         = 0x1000,
  PASEL13         = 0x2000,
  PASEL14         = 0x4000,
  PASEL15         = 0x8000
};

__no_init volatile union
{
  unsigned short PAIES;   /* Port A Interrupt Edge Select */

  struct
  {
    unsigned short PAIES0          : 1; /*  */
    unsigned short PAIES1          : 1; /*  */
    unsigned short PAIES2          : 1; /*  */
    unsigned short PAIES3          : 1; /*  */
    unsigned short PAIES4          : 1; /*  */
    unsigned short PAIES5          : 1; /*  */
    unsigned short PAIES6          : 1; /*  */
    unsigned short PAIES7          : 1; /*  */
    unsigned short PAIES8          : 1; /*  */
    unsigned short PAIES9          : 1; /*  */
    unsigned short PAIES10         : 1; /*  */
    unsigned short PAIES11         : 1; /*  */
    unsigned short PAIES12         : 1; /*  */
    unsigned short PAIES13         : 1; /*  */
    unsigned short PAIES14         : 1; /*  */
    unsigned short PAIES15         : 1; /*  */
  } PAIES_bit;

  struct
  {
    unsigned char PAIES_L;
    unsigned char PAIES_H;
  };
  struct
  {
    unsigned char P1IES;   /* Port 1 Interrupt Edge Select */
    unsigned char P2IES;   /* Port 2 Interrupt Edge Select */
  };
  struct
  {
    struct
    {
      unsigned char P1IES0          : 1; /*  */
      unsigned char P1IES1          : 1; /*  */
      unsigned char P1IES2          : 1; /*  */
      unsigned char P1IES3          : 1; /*  */
      unsigned char P1IES4          : 1; /*  */
      unsigned char P1IES5          : 1; /*  */
      unsigned char P1IES6          : 1; /*  */
      unsigned char P1IES7          : 1; /*  */
    } P1IES_bit;

    struct
    {
      unsigned char P2IES0          : 1; /*  */
      unsigned char P2IES1          : 1; /*  */
      unsigned char P2IES2          : 1; /*  */
      unsigned char P2IES3          : 1; /*  */
      unsigned char P2IES4          : 1; /*  */
      unsigned char P2IES5          : 1; /*  */
      unsigned char P2IES6          : 1; /*  */
      unsigned char P2IES7          : 1; /*  */
    } P2IES_bit;
  }; 
} @0x0218;

enum {
  PAIES0          = 0x0001,
  PAIES1          = 0x0002,
  PAIES2          = 0x0004,
  PAIES3          = 0x0008,
  PAIES4          = 0x0010,
  PAIES5          = 0x0020,
  PAIES6          = 0x0040,
  PAIES7          = 0x0080,
  PAIES8          = 0x0100,
  PAIES9          = 0x0200,
  PAIES10         = 0x0400,
  PAIES11         = 0x0800,
  PAIES12         = 0x1000,
  PAIES13         = 0x2000,
  PAIES14         = 0x4000,
  PAIES15         = 0x8000
};

__no_init volatile union
{
  unsigned short PAIE;   /* Port A Interrupt Enable */

  struct
  {
    unsigned short PAIE0           : 1; /*  */
    unsigned short PAIE1           : 1; /*  */
    unsigned short PAIE2           : 1; /*  */
    unsigned short PAIE3           : 1; /*  */
    unsigned short PAIE4           : 1; /*  */
    unsigned short PAIE5           : 1; /*  */
    unsigned short PAIE6           : 1; /*  */
    unsigned short PAIE7           : 1; /*  */
    unsigned short PAIE8           : 1; /*  */
    unsigned short PAIE9           : 1; /*  */
    unsigned short PAIE10          : 1; /*  */
    unsigned short PAIE11          : 1; /*  */
    unsigned short PAIE12          : 1; /*  */
    unsigned short PAIE13          : 1; /*  */
    unsigned short PAIE14          : 1; /*  */
    unsigned short PAIE15          : 1; /*  */
  } PAIE_bit;

  struct
  {
    unsigned char PAIE_L;
    unsigned char PAIE_H;
  };
  struct
  {
    unsigned char P1IE;   /* Port 1 Interrupt Enable */
    unsigned char P2IE;   /* Port 2 Interrupt Enable */
  };
  struct
  {
    struct
    {
      unsigned char P1IE0           : 1; /*  */
      unsigned char P1IE1           : 1; /*  */
      unsigned char P1IE2           : 1; /*  */
      unsigned char P1IE3           : 1; /*  */
      unsigned char P1IE4           : 1; /*  */
      unsigned char P1IE5           : 1; /*  */
      unsigned char P1IE6           : 1; /*  */
      unsigned char P1IE7           : 1; /*  */
    } P1IE_bit;

    struct
    {
      unsigned char P2IE0           : 1; /*  */
      unsigned char P2IE1           : 1; /*  */
      unsigned char P2IE2           : 1; /*  */
      unsigned char P2IE3           : 1; /*  */
      unsigned char P2IE4           : 1; /*  */
      unsigned char P2IE5           : 1; /*  */
      unsigned char P2IE6           : 1; /*  */
      unsigned char P2IE7           : 1; /*  */
    } P2IE_bit;
  }; 
} @0x021A;

enum {
  PAIE0           = 0x0001,
  PAIE1           = 0x0002,
  PAIE2           = 0x0004,
  PAIE3           = 0x0008,
  PAIE4           = 0x0010,
  PAIE5           = 0x0020,
  PAIE6           = 0x0040,
  PAIE7           = 0x0080,
  PAIE8           = 0x0100,
  PAIE9           = 0x0200,
  PAIE10          = 0x0400,
  PAIE11          = 0x0800,
  PAIE12          = 0x1000,
  PAIE13          = 0x2000,
  PAIE14          = 0x4000,
  PAIE15          = 0x8000
};

__no_init volatile union
{
  unsigned short PAIFG;   /* Port A Interrupt Flag */

  struct
  {
    unsigned short PAIFG0          : 1; /*  */
    unsigned short PAIFG1          : 1; /*  */
    unsigned short PAIFG2          : 1; /*  */
    unsigned short PAIFG3          : 1; /*  */
    unsigned short PAIFG4          : 1; /*  */
    unsigned short PAIFG5          : 1; /*  */
    unsigned short PAIFG6          : 1; /*  */
    unsigned short PAIFG7          : 1; /*  */
    unsigned short PAIFG8          : 1; /*  */
    unsigned short PAIFG9          : 1; /*  */
    unsigned short PAIFG10         : 1; /*  */
    unsigned short PAIFG11         : 1; /*  */
    unsigned short PAIFG12         : 1; /*  */
    unsigned short PAIFG13         : 1; /*  */
    unsigned short PAIFG14         : 1; /*  */
    unsigned short PAIFG15         : 1; /*  */
  } PAIFG_bit;

  struct
  {
    unsigned char PAIFG_L;
    unsigned char PAIFG_H;
  };
  struct
  {
    unsigned char P1IFG;   /* Port 1 Interrupt Flag */
    unsigned char P2IFG;   /* Port 2 Interrupt Flag */
  };
  struct
  {
    struct
    {
      unsigned char P1IFG0          : 1; /*  */
      unsigned char P1IFG1          : 1; /*  */
      unsigned char P1IFG2          : 1; /*  */
      unsigned char P1IFG3          : 1; /*  */
      unsigned char P1IFG4          : 1; /*  */
      unsigned char P1IFG5          : 1; /*  */
      unsigned char P1IFG6          : 1; /*  */
      unsigned char P1IFG7          : 1; /*  */
    } P1IFG_bit;

    struct
    {
      unsigned char P2IFG0          : 1; /*  */
      unsigned char P2IFG1          : 1; /*  */
      unsigned char P2IFG2          : 1; /*  */
      unsigned char P2IFG3          : 1; /*  */
      unsigned char P2IFG4          : 1; /*  */
      unsigned char P2IFG5          : 1; /*  */
      unsigned char P2IFG6          : 1; /*  */
      unsigned char P2IFG7          : 1; /*  */
    } P2IFG_bit;
  }; 
} @0x021C;

enum {
  PAIFG0          = 0x0001,
  PAIFG1          = 0x0002,
  PAIFG2          = 0x0004,
  PAIFG3          = 0x0008,
  PAIFG4          = 0x0010,
  PAIFG5          = 0x0020,
  PAIFG6          = 0x0040,
  PAIFG7          = 0x0080,
  PAIFG8          = 0x0100,
  PAIFG9          = 0x0200,
  PAIFG10         = 0x0400,
  PAIFG11         = 0x0800,
  PAIFG12         = 0x1000,
  PAIFG13         = 0x2000,
  PAIFG14         = 0x4000,
  PAIFG15         = 0x8000
};



#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200
#define P1IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P1IV_P1IFG0          (0x0002u)    /* P1IV P1IFG.0 */
#define P1IV_P1IFG1          (0x0004u)    /* P1IV P1IFG.1 */
#define P1IV_P1IFG2          (0x0006u)    /* P1IV P1IFG.2 */
#define P1IV_P1IFG3          (0x0008u)    /* P1IV P1IFG.3 */
#define P1IV_P1IFG4          (0x000Au)    /* P1IV P1IFG.4 */
#define P1IV_P1IFG5          (0x000Cu)    /* P1IV P1IFG.5 */
#define P1IV_P1IFG6          (0x000Eu)    /* P1IV P1IFG.6 */
#define P1IV_P1IFG7          (0x0010u)    /* P1IV P1IFG.7 */
#define P2IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P2IV_P2IFG0          (0x0002u)    /* P2IV P2IFG.0 */
#define P2IV_P2IFG1          (0x0004u)    /* P2IV P2IFG.1 */
#define P2IV_P2IFG2          (0x0006u)    /* P2IV P2IFG.2 */
#define P2IV_P2IFG3          (0x0008u)    /* P2IV P2IFG.3 */
#define P2IV_P2IFG4          (0x000Au)    /* P2IV P2IFG.4 */
#define P2IV_P2IFG5          (0x000Cu)    /* P2IV P2IFG.5 */
#define P2IV_P2IFG6          (0x000Eu)    /* P2IV P2IFG.6 */
#define P2IV_P2IFG7          (0x0010u)    /* P2IV P2IFG.7 */

/*-------------------------------------------------------------------------
 *   Port 1/2
 *-------------------------------------------------------------------------*/


enum {
  P1IN0           = 0x0001,
  P1IN1           = 0x0002,
  P1IN2           = 0x0004,
  P1IN3           = 0x0008,
  P1IN4           = 0x0010,
  P1IN5           = 0x0020,
  P1IN6           = 0x0040,
  P1IN7           = 0x0080
};

enum {
  P1OUT0          = 0x0001,
  P1OUT1          = 0x0002,
  P1OUT2          = 0x0004,
  P1OUT3          = 0x0008,
  P1OUT4          = 0x0010,
  P1OUT5          = 0x0020,
  P1OUT6          = 0x0040,
  P1OUT7          = 0x0080
};

enum {
  P1DIR0          = 0x0001,
  P1DIR1          = 0x0002,
  P1DIR2          = 0x0004,
  P1DIR3          = 0x0008,
  P1DIR4          = 0x0010,
  P1DIR5          = 0x0020,
  P1DIR6          = 0x0040,
  P1DIR7          = 0x0080
};

enum {
  P1REN0          = 0x0001,
  P1REN1          = 0x0002,
  P1REN2          = 0x0004,
  P1REN3          = 0x0008,
  P1REN4          = 0x0010,
  P1REN5          = 0x0020,
  P1REN6          = 0x0040,
  P1REN7          = 0x0080
};

enum {
  P1DS0           = 0x0001,
  P1DS1           = 0x0002,
  P1DS2           = 0x0004,
  P1DS3           = 0x0008,
  P1DS4           = 0x0010,
  P1DS5           = 0x0020,
  P1DS6           = 0x0040,
  P1DS7           = 0x0080
};

enum {
  P1SEL0          = 0x0001,
  P1SEL1          = 0x0002,
  P1SEL2          = 0x0004,
  P1SEL3          = 0x0008,
  P1SEL4          = 0x0010,
  P1SEL5          = 0x0020,
  P1SEL6          = 0x0040,
  P1SEL7          = 0x0080
};


  /* Port 1 Interrupt Vector Word */
__no_init volatile unsigned short P1IV @ 0x020E;


enum {
  P1IES0          = 0x0001,
  P1IES1          = 0x0002,
  P1IES2          = 0x0004,
  P1IES3          = 0x0008,
  P1IES4          = 0x0010,
  P1IES5          = 0x0020,
  P1IES6          = 0x0040,
  P1IES7          = 0x0080
};

enum {
  P1IE0           = 0x0001,
  P1IE1           = 0x0002,
  P1IE2           = 0x0004,
  P1IE3           = 0x0008,
  P1IE4           = 0x0010,
  P1IE5           = 0x0020,
  P1IE6           = 0x0040,
  P1IE7           = 0x0080
};

enum {
  P1IFG0          = 0x0001,
  P1IFG1          = 0x0002,
  P1IFG2          = 0x0004,
  P1IFG3          = 0x0008,
  P1IFG4          = 0x0010,
  P1IFG5          = 0x0020,
  P1IFG6          = 0x0040,
  P1IFG7          = 0x0080
};

enum {
  P2IN0           = 0x0001,
  P2IN1           = 0x0002,
  P2IN2           = 0x0004,
  P2IN3           = 0x0008,
  P2IN4           = 0x0010,
  P2IN5           = 0x0020,
  P2IN6           = 0x0040,
  P2IN7           = 0x0080
};

enum {
  P2OUT0          = 0x0001,
  P2OUT1          = 0x0002,
  P2OUT2          = 0x0004,
  P2OUT3          = 0x0008,
  P2OUT4          = 0x0010,
  P2OUT5          = 0x0020,
  P2OUT6          = 0x0040,
  P2OUT7          = 0x0080
};

enum {
  P2DIR0          = 0x0001,
  P2DIR1          = 0x0002,
  P2DIR2          = 0x0004,
  P2DIR3          = 0x0008,
  P2DIR4          = 0x0010,
  P2DIR5          = 0x0020,
  P2DIR6          = 0x0040,
  P2DIR7          = 0x0080
};

enum {
  P2REN0          = 0x0001,
  P2REN1          = 0x0002,
  P2REN2          = 0x0004,
  P2REN3          = 0x0008,
  P2REN4          = 0x0010,
  P2REN5          = 0x0020,
  P2REN6          = 0x0040,
  P2REN7          = 0x0080
};

enum {
  P2DS0           = 0x0001,
  P2DS1           = 0x0002,
  P2DS2           = 0x0004,
  P2DS3           = 0x0008,
  P2DS4           = 0x0010,
  P2DS5           = 0x0020,
  P2DS6           = 0x0040,
  P2DS7           = 0x0080
};

enum {
  P2SEL0          = 0x0001,
  P2SEL1          = 0x0002,
  P2SEL2          = 0x0004,
  P2SEL3          = 0x0008,
  P2SEL4          = 0x0010,
  P2SEL5          = 0x0020,
  P2SEL6          = 0x0040,
  P2SEL7          = 0x0080
};


  /* Port 2 Interrupt Vector Word */
__no_init volatile unsigned short P2IV @ 0x021E;


enum {
  P2IES0          = 0x0001,
  P2IES1          = 0x0002,
  P2IES2          = 0x0004,
  P2IES3          = 0x0008,
  P2IES4          = 0x0010,
  P2IES5          = 0x0020,
  P2IES6          = 0x0040,
  P2IES7          = 0x0080
};

enum {
  P2IE0           = 0x0001,
  P2IE1           = 0x0002,
  P2IE2           = 0x0004,
  P2IE3           = 0x0008,
  P2IE4           = 0x0010,
  P2IE5           = 0x0020,
  P2IE6           = 0x0040,
  P2IE7           = 0x0080
};

enum {
  P2IFG0          = 0x0001,
  P2IFG1          = 0x0002,
  P2IFG2          = 0x0004,
  P2IFG3          = 0x0008,
  P2IFG4          = 0x0010,
  P2IFG5          = 0x0020,
  P2IFG6          = 0x0040,
  P2IFG7          = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port B
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PBIN;   /* Port B Input */

  struct
  {
    unsigned __READ short PBIN0           : 1; /*  */
    unsigned __READ short PBIN1           : 1; /*  */
    unsigned __READ short PBIN2           : 1; /*  */
    unsigned __READ short PBIN3           : 1; /*  */
    unsigned __READ short PBIN4           : 1; /*  */
    unsigned __READ short PBIN5           : 1; /*  */
    unsigned __READ short PBIN6           : 1; /*  */
    unsigned __READ short PBIN7           : 1; /*  */
    unsigned __READ short PBIN8           : 1; /*  */
    unsigned __READ short PBIN9           : 1; /*  */
    unsigned __READ short PBIN10          : 1; /*  */
    unsigned __READ short PBIN11          : 1; /*  */
    unsigned __READ short PBIN12          : 1; /*  */
    unsigned __READ short PBIN13          : 1; /*  */
    unsigned __READ short PBIN14          : 1; /*  */
    unsigned __READ short PBIN15          : 1; /*  */
  } PBIN_bit;

  struct
  {
    unsigned __READ char PBIN_L;
    unsigned __READ char PBIN_H;
  };
  struct
  {
    unsigned char P3IN;   /* Port 3 Input */
    unsigned char P4IN;   /* Port 4 Input */
  };
  struct
  {
    struct
    {
      unsigned char P3IN0           : 1; /*  */
      unsigned char P3IN1           : 1; /*  */
      unsigned char P3IN2           : 1; /*  */
      unsigned char P3IN3           : 1; /*  */
      unsigned char P3IN4           : 1; /*  */
      unsigned char P3IN5           : 1; /*  */
      unsigned char P3IN6           : 1; /*  */
      unsigned char P3IN7           : 1; /*  */
    } P3IN_bit;

    struct
    {
      unsigned char P4IN0           : 1; /*  */
      unsigned char P4IN1           : 1; /*  */
      unsigned char P4IN2           : 1; /*  */
      unsigned char P4IN3           : 1; /*  */
      unsigned char P4IN4           : 1; /*  */
      unsigned char P4IN5           : 1; /*  */
      unsigned char P4IN6           : 1; /*  */
      unsigned char P4IN7           : 1; /*  */
    } P4IN_bit;
  }; 
} @0x0220;

enum {
  PBIN0           = 0x0001,
  PBIN1           = 0x0002,
  PBIN2           = 0x0004,
  PBIN3           = 0x0008,
  PBIN4           = 0x0010,
  PBIN5           = 0x0020,
  PBIN6           = 0x0040,
  PBIN7           = 0x0080,
  PBIN8           = 0x0100,
  PBIN9           = 0x0200,
  PBIN10          = 0x0400,
  PBIN11          = 0x0800,
  PBIN12          = 0x1000,
  PBIN13          = 0x2000,
  PBIN14          = 0x4000,
  PBIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PBOUT;   /* Port B Output */

  struct
  {
    unsigned short PBOUT0          : 1; /*  */
    unsigned short PBOUT1          : 1; /*  */
    unsigned short PBOUT2          : 1; /*  */
    unsigned short PBOUT3          : 1; /*  */
    unsigned short PBOUT4          : 1; /*  */
    unsigned short PBOUT5          : 1; /*  */
    unsigned short PBOUT6          : 1; /*  */
    unsigned short PBOUT7          : 1; /*  */
    unsigned short PBOUT8          : 1; /*  */
    unsigned short PBOUT9          : 1; /*  */
    unsigned short PBOUT10         : 1; /*  */
    unsigned short PBOUT11         : 1; /*  */
    unsigned short PBOUT12         : 1; /*  */
    unsigned short PBOUT13         : 1; /*  */
    unsigned short PBOUT14         : 1; /*  */
    unsigned short PBOUT15         : 1; /*  */
  } PBOUT_bit;

  struct
  {
    unsigned char PBOUT_L;
    unsigned char PBOUT_H;
  };
  struct
  {
    unsigned char P3OUT;   /* Port 3 Output */
    unsigned char P4OUT;   /* Port 4 Output */
  };
  struct
  {
    struct
    {
      unsigned char P3OUT0          : 1; /*  */
      unsigned char P3OUT1          : 1; /*  */
      unsigned char P3OUT2          : 1; /*  */
      unsigned char P3OUT3          : 1; /*  */
      unsigned char P3OUT4          : 1; /*  */
      unsigned char P3OUT5          : 1; /*  */
      unsigned char P3OUT6          : 1; /*  */
      unsigned char P3OUT7          : 1; /*  */
    } P3OUT_bit;

    struct
    {
      unsigned char P4OUT0          : 1; /*  */
      unsigned char P4OUT1          : 1; /*  */
      unsigned char P4OUT2          : 1; /*  */
      unsigned char P4OUT3          : 1; /*  */
      unsigned char P4OUT4          : 1; /*  */
      unsigned char P4OUT5          : 1; /*  */
      unsigned char P4OUT6          : 1; /*  */
      unsigned char P4OUT7          : 1; /*  */
    } P4OUT_bit;
  }; 
} @0x0222;

enum {
  PBOUT0          = 0x0001,
  PBOUT1          = 0x0002,
  PBOUT2          = 0x0004,
  PBOUT3          = 0x0008,
  PBOUT4          = 0x0010,
  PBOUT5          = 0x0020,
  PBOUT6          = 0x0040,
  PBOUT7          = 0x0080,
  PBOUT8          = 0x0100,
  PBOUT9          = 0x0200,
  PBOUT10         = 0x0400,
  PBOUT11         = 0x0800,
  PBOUT12         = 0x1000,
  PBOUT13         = 0x2000,
  PBOUT14         = 0x4000,
  PBOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PBDIR;   /* Port B Direction */

  struct
  {
    unsigned short PBDIR0          : 1; /*  */
    unsigned short PBDIR1          : 1; /*  */
    unsigned short PBDIR2          : 1; /*  */
    unsigned short PBDIR3          : 1; /*  */
    unsigned short PBDIR4          : 1; /*  */
    unsigned short PBDIR5          : 1; /*  */
    unsigned short PBDIR6          : 1; /*  */
    unsigned short PBDIR7          : 1; /*  */
    unsigned short PBDIR8          : 1; /*  */
    unsigned short PBDIR9          : 1; /*  */
    unsigned short PBDIR10         : 1; /*  */
    unsigned short PBDIR11         : 1; /*  */
    unsigned short PBDIR12         : 1; /*  */
    unsigned short PBDIR13         : 1; /*  */
    unsigned short PBDIR14         : 1; /*  */
    unsigned short PBDIR15         : 1; /*  */
  } PBDIR_bit;

  struct
  {
    unsigned char PBDIR_L;
    unsigned char PBDIR_H;
  };
  struct
  {
    unsigned char P3DIR;   /* Port 3 Direction */
    unsigned char P4DIR;   /* Port 4 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P3DIR0          : 1; /*  */
      unsigned char P3DIR1          : 1; /*  */
      unsigned char P3DIR2          : 1; /*  */
      unsigned char P3DIR3          : 1; /*  */
      unsigned char P3DIR4          : 1; /*  */
      unsigned char P3DIR5          : 1; /*  */
      unsigned char P3DIR6          : 1; /*  */
      unsigned char P3DIR7          : 1; /*  */
    } P3DIR_bit;

    struct
    {
      unsigned char P4DIR0          : 1; /*  */
      unsigned char P4DIR1          : 1; /*  */
      unsigned char P4DIR2          : 1; /*  */
      unsigned char P4DIR3          : 1; /*  */
      unsigned char P4DIR4          : 1; /*  */
      unsigned char P4DIR5          : 1; /*  */
      unsigned char P4DIR6          : 1; /*  */
      unsigned char P4DIR7          : 1; /*  */
    } P4DIR_bit;
  }; 
} @0x0224;

enum {
  PBDIR0          = 0x0001,
  PBDIR1          = 0x0002,
  PBDIR2          = 0x0004,
  PBDIR3          = 0x0008,
  PBDIR4          = 0x0010,
  PBDIR5          = 0x0020,
  PBDIR6          = 0x0040,
  PBDIR7          = 0x0080,
  PBDIR8          = 0x0100,
  PBDIR9          = 0x0200,
  PBDIR10         = 0x0400,
  PBDIR11         = 0x0800,
  PBDIR12         = 0x1000,
  PBDIR13         = 0x2000,
  PBDIR14         = 0x4000,
  PBDIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PBREN;   /* Port B Resistor Enable */

  struct
  {
    unsigned short PBREN0          : 1; /*  */
    unsigned short PBREN1          : 1; /*  */
    unsigned short PBREN2          : 1; /*  */
    unsigned short PBREN3          : 1; /*  */
    unsigned short PBREN4          : 1; /*  */
    unsigned short PBREN5          : 1; /*  */
    unsigned short PBREN6          : 1; /*  */
    unsigned short PBREN7          : 1; /*  */
    unsigned short PBREN8          : 1; /*  */
    unsigned short PBREN9          : 1; /*  */
    unsigned short PBREN10         : 1; /*  */
    unsigned short PBREN11         : 1; /*  */
    unsigned short PBREN12         : 1; /*  */
    unsigned short PBREN13         : 1; /*  */
    unsigned short PBREN14         : 1; /*  */
    unsigned short PBREN15         : 1; /*  */
  } PBREN_bit;

  struct
  {
    unsigned char PBREN_L;
    unsigned char PBREN_H;
  };
  struct
  {
    unsigned char P3REN;   /* Port 3 Resistor Enable */
    unsigned char P4REN;   /* Port 4 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P3REN0          : 1; /*  */
      unsigned char P3REN1          : 1; /*  */
      unsigned char P3REN2          : 1; /*  */
      unsigned char P3REN3          : 1; /*  */
      unsigned char P3REN4          : 1; /*  */
      unsigned char P3REN5          : 1; /*  */
      unsigned char P3REN6          : 1; /*  */
      unsigned char P3REN7          : 1; /*  */
    } P3REN_bit;

    struct
    {
      unsigned char P4REN0          : 1; /*  */
      unsigned char P4REN1          : 1; /*  */
      unsigned char P4REN2          : 1; /*  */
      unsigned char P4REN3          : 1; /*  */
      unsigned char P4REN4          : 1; /*  */
      unsigned char P4REN5          : 1; /*  */
      unsigned char P4REN6          : 1; /*  */
      unsigned char P4REN7          : 1; /*  */
    } P4REN_bit;
  }; 
} @0x0226;

enum {
  PBREN0          = 0x0001,
  PBREN1          = 0x0002,
  PBREN2          = 0x0004,
  PBREN3          = 0x0008,
  PBREN4          = 0x0010,
  PBREN5          = 0x0020,
  PBREN6          = 0x0040,
  PBREN7          = 0x0080,
  PBREN8          = 0x0100,
  PBREN9          = 0x0200,
  PBREN10         = 0x0400,
  PBREN11         = 0x0800,
  PBREN12         = 0x1000,
  PBREN13         = 0x2000,
  PBREN14         = 0x4000,
  PBREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PBDS;   /* Port B Drive Strenght */

  struct
  {
    unsigned short PBDS0           : 1; /*  */
    unsigned short PBDS1           : 1; /*  */
    unsigned short PBDS2           : 1; /*  */
    unsigned short PBDS3           : 1; /*  */
    unsigned short PBDS4           : 1; /*  */
    unsigned short PBDS5           : 1; /*  */
    unsigned short PBDS6           : 1; /*  */
    unsigned short PBDS7           : 1; /*  */
    unsigned short PBDS8           : 1; /*  */
    unsigned short PBDS9           : 1; /*  */
    unsigned short PBDS10          : 1; /*  */
    unsigned short PBDS11          : 1; /*  */
    unsigned short PBDS12          : 1; /*  */
    unsigned short PBDS13          : 1; /*  */
    unsigned short PBDS14          : 1; /*  */
    unsigned short PBDS15          : 1; /*  */
  } PBDS_bit;

  struct
  {
    unsigned char PBDS_L;
    unsigned char PBDS_H;
  };
  struct
  {
    unsigned char P3DS;   /* Port 3 Drive Strenght */
    unsigned char P4DS;   /* Port 4 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P3DS0           : 1; /*  */
      unsigned char P3DS1           : 1; /*  */
      unsigned char P3DS2           : 1; /*  */
      unsigned char P3DS3           : 1; /*  */
      unsigned char P3DS4           : 1; /*  */
      unsigned char P3DS5           : 1; /*  */
      unsigned char P3DS6           : 1; /*  */
      unsigned char P3DS7           : 1; /*  */
    } P3DS_bit;

    struct
    {
      unsigned char P4DS0           : 1; /*  */
      unsigned char P4DS1           : 1; /*  */
      unsigned char P4DS2           : 1; /*  */
      unsigned char P4DS3           : 1; /*  */
      unsigned char P4DS4           : 1; /*  */
      unsigned char P4DS5           : 1; /*  */
      unsigned char P4DS6           : 1; /*  */
      unsigned char P4DS7           : 1; /*  */
    } P4DS_bit;
  }; 
} @0x0228;

enum {
  PBDS0           = 0x0001,
  PBDS1           = 0x0002,
  PBDS2           = 0x0004,
  PBDS3           = 0x0008,
  PBDS4           = 0x0010,
  PBDS5           = 0x0020,
  PBDS6           = 0x0040,
  PBDS7           = 0x0080,
  PBDS8           = 0x0100,
  PBDS9           = 0x0200,
  PBDS10          = 0x0400,
  PBDS11          = 0x0800,
  PBDS12          = 0x1000,
  PBDS13          = 0x2000,
  PBDS14          = 0x4000,
  PBDS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PBSEL;   /* Port B Selection */

  struct
  {
    unsigned short PBSEL0          : 1; /*  */
    unsigned short PBSEL1          : 1; /*  */
    unsigned short PBSEL2          : 1; /*  */
    unsigned short PBSEL3          : 1; /*  */
    unsigned short PBSEL4          : 1; /*  */
    unsigned short PBSEL5          : 1; /*  */
    unsigned short PBSEL6          : 1; /*  */
    unsigned short PBSEL7          : 1; /*  */
    unsigned short PBSEL8          : 1; /*  */
    unsigned short PBSEL9          : 1; /*  */
    unsigned short PBSEL10         : 1; /*  */
    unsigned short PBSEL11         : 1; /*  */
    unsigned short PBSEL12         : 1; /*  */
    unsigned short PBSEL13         : 1; /*  */
    unsigned short PBSEL14         : 1; /*  */
    unsigned short PBSEL15         : 1; /*  */
  } PBSEL_bit;

  struct
  {
    unsigned char PBSEL_L;
    unsigned char PBSEL_H;
  };
  struct
  {
    unsigned char P3SEL;   /* Port 3 Selection */
    unsigned char P4SEL;   /* Port 4 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P3SEL0          : 1; /*  */
      unsigned char P3SEL1          : 1; /*  */
      unsigned char P3SEL2          : 1; /*  */
      unsigned char P3SEL3          : 1; /*  */
      unsigned char P3SEL4          : 1; /*  */
      unsigned char P3SEL5          : 1; /*  */
      unsigned char P3SEL6          : 1; /*  */
      unsigned char P3SEL7          : 1; /*  */
    } P3SEL_bit;

    struct
    {
      unsigned char P4SEL0          : 1; /*  */
      unsigned char P4SEL1          : 1; /*  */
      unsigned char P4SEL2          : 1; /*  */
      unsigned char P4SEL3          : 1; /*  */
      unsigned char P4SEL4          : 1; /*  */
      unsigned char P4SEL5          : 1; /*  */
      unsigned char P4SEL6          : 1; /*  */
      unsigned char P4SEL7          : 1; /*  */
    } P4SEL_bit;
  }; 
} @0x022A;

enum {
  PBSEL0          = 0x0001,
  PBSEL1          = 0x0002,
  PBSEL2          = 0x0004,
  PBSEL3          = 0x0008,
  PBSEL4          = 0x0010,
  PBSEL5          = 0x0020,
  PBSEL6          = 0x0040,
  PBSEL7          = 0x0080,
  PBSEL8          = 0x0100,
  PBSEL9          = 0x0200,
  PBSEL10         = 0x0400,
  PBSEL11         = 0x0800,
  PBSEL12         = 0x1000,
  PBSEL13         = 0x2000,
  PBSEL14         = 0x4000,
  PBSEL15         = 0x8000
};



#define __MSP430_HAS_PORT3_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTB_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_R__ 0x0220
#define __MSP430_BASEADDRESS_PORT4_R__ 0x0220
#define __MSP430_BASEADDRESS_PORTB_R__ 0x0220

/*-------------------------------------------------------------------------
 *   Port 3/4
 *-------------------------------------------------------------------------*/


enum {
  P3IN0           = 0x0001,
  P3IN1           = 0x0002,
  P3IN2           = 0x0004,
  P3IN3           = 0x0008,
  P3IN4           = 0x0010,
  P3IN5           = 0x0020,
  P3IN6           = 0x0040,
  P3IN7           = 0x0080
};

enum {
  P3OUT0          = 0x0001,
  P3OUT1          = 0x0002,
  P3OUT2          = 0x0004,
  P3OUT3          = 0x0008,
  P3OUT4          = 0x0010,
  P3OUT5          = 0x0020,
  P3OUT6          = 0x0040,
  P3OUT7          = 0x0080
};

enum {
  P3DIR0          = 0x0001,
  P3DIR1          = 0x0002,
  P3DIR2          = 0x0004,
  P3DIR3          = 0x0008,
  P3DIR4          = 0x0010,
  P3DIR5          = 0x0020,
  P3DIR6          = 0x0040,
  P3DIR7          = 0x0080
};

enum {
  P3REN0          = 0x0001,
  P3REN1          = 0x0002,
  P3REN2          = 0x0004,
  P3REN3          = 0x0008,
  P3REN4          = 0x0010,
  P3REN5          = 0x0020,
  P3REN6          = 0x0040,
  P3REN7          = 0x0080
};

enum {
  P3DS0           = 0x0001,
  P3DS1           = 0x0002,
  P3DS2           = 0x0004,
  P3DS3           = 0x0008,
  P3DS4           = 0x0010,
  P3DS5           = 0x0020,
  P3DS6           = 0x0040,
  P3DS7           = 0x0080
};

enum {
  P3SEL0          = 0x0001,
  P3SEL1          = 0x0002,
  P3SEL2          = 0x0004,
  P3SEL3          = 0x0008,
  P3SEL4          = 0x0010,
  P3SEL5          = 0x0020,
  P3SEL6          = 0x0040,
  P3SEL7          = 0x0080
};

enum {
  P4IN0           = 0x0001,
  P4IN1           = 0x0002,
  P4IN2           = 0x0004,
  P4IN3           = 0x0008,
  P4IN4           = 0x0010,
  P4IN5           = 0x0020,
  P4IN6           = 0x0040,
  P4IN7           = 0x0080
};

enum {
  P4OUT0          = 0x0001,
  P4OUT1          = 0x0002,
  P4OUT2          = 0x0004,
  P4OUT3          = 0x0008,
  P4OUT4          = 0x0010,
  P4OUT5          = 0x0020,
  P4OUT6          = 0x0040,
  P4OUT7          = 0x0080
};

enum {
  P4DIR0          = 0x0001,
  P4DIR1          = 0x0002,
  P4DIR2          = 0x0004,
  P4DIR3          = 0x0008,
  P4DIR4          = 0x0010,
  P4DIR5          = 0x0020,
  P4DIR6          = 0x0040,
  P4DIR7          = 0x0080
};

enum {
  P4REN0          = 0x0001,
  P4REN1          = 0x0002,
  P4REN2          = 0x0004,
  P4REN3          = 0x0008,
  P4REN4          = 0x0010,
  P4REN5          = 0x0020,
  P4REN6          = 0x0040,
  P4REN7          = 0x0080
};

enum {
  P4DS0           = 0x0001,
  P4DS1           = 0x0002,
  P4DS2           = 0x0004,
  P4DS3           = 0x0008,
  P4DS4           = 0x0010,
  P4DS5           = 0x0020,
  P4DS6           = 0x0040,
  P4DS7           = 0x0080
};

enum {
  P4SEL0          = 0x0001,
  P4SEL1          = 0x0002,
  P4SEL2          = 0x0004,
  P4SEL3          = 0x0008,
  P4SEL4          = 0x0010,
  P4SEL5          = 0x0020,
  P4SEL6          = 0x0040,
  P4SEL7          = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port C
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PCIN;   /* Port C Input */

  struct
  {
    unsigned __READ short PCIN0           : 1; /*  */
    unsigned __READ short PCIN1           : 1; /*  */
    unsigned __READ short PCIN2           : 1; /*  */
    unsigned __READ short PCIN3           : 1; /*  */
    unsigned __READ short PCIN4           : 1; /*  */
    unsigned __READ short PCIN5           : 1; /*  */
    unsigned __READ short PCIN6           : 1; /*  */
    unsigned __READ short PCIN7           : 1; /*  */
    unsigned __READ short PCIN8           : 1; /*  */
    unsigned __READ short PCIN9           : 1; /*  */
    unsigned __READ short PCIN10          : 1; /*  */
    unsigned __READ short PCIN11          : 1; /*  */
    unsigned __READ short PCIN12          : 1; /*  */
    unsigned __READ short PCIN13          : 1; /*  */
    unsigned __READ short PCIN14          : 1; /*  */
    unsigned __READ short PCIN15          : 1; /*  */
  } PCIN_bit;

  struct
  {
    unsigned __READ char PCIN_L;
    unsigned __READ char PCIN_H;
  };
  struct
  {
    unsigned char P5IN;   /* Port 5 Input */
    unsigned char P6IN;   /* Port 6 Input */
  };
  struct
  {
    struct
    {
      unsigned char P5IN0           : 1; /*  */
      unsigned char P5IN1           : 1; /*  */
      unsigned char P5IN2           : 1; /*  */
      unsigned char P5IN3           : 1; /*  */
      unsigned char P5IN4           : 1; /*  */
      unsigned char P5IN5           : 1; /*  */
      unsigned char P5IN6           : 1; /*  */
      unsigned char P5IN7           : 1; /*  */
    } P5IN_bit;

    struct
    {
      unsigned char P6IN0           : 1; /*  */
      unsigned char P6IN1           : 1; /*  */
      unsigned char P6IN2           : 1; /*  */
      unsigned char P6IN3           : 1; /*  */
      unsigned char P6IN4           : 1; /*  */
      unsigned char P6IN5           : 1; /*  */
      unsigned char P6IN6           : 1; /*  */
      unsigned char P6IN7           : 1; /*  */
    } P6IN_bit;
  }; 
} @0x0240;

enum {
  PCIN0           = 0x0001,
  PCIN1           = 0x0002,
  PCIN2           = 0x0004,
  PCIN3           = 0x0008,
  PCIN4           = 0x0010,
  PCIN5           = 0x0020,
  PCIN6           = 0x0040,
  PCIN7           = 0x0080,
  PCIN8           = 0x0100,
  PCIN9           = 0x0200,
  PCIN10          = 0x0400,
  PCIN11          = 0x0800,
  PCIN12          = 0x1000,
  PCIN13          = 0x2000,
  PCIN14          = 0x4000,
  PCIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PCOUT;   /* Port C Output */

  struct
  {
    unsigned short PCOUT0          : 1; /*  */
    unsigned short PCOUT1          : 1; /*  */
    unsigned short PCOUT2          : 1; /*  */
    unsigned short PCOUT3          : 1; /*  */
    unsigned short PCOUT4          : 1; /*  */
    unsigned short PCOUT5          : 1; /*  */
    unsigned short PCOUT6          : 1; /*  */
    unsigned short PCOUT7          : 1; /*  */
    unsigned short PCOUT8          : 1; /*  */
    unsigned short PCOUT9          : 1; /*  */
    unsigned short PCOUT10         : 1; /*  */
    unsigned short PCOUT11         : 1; /*  */
    unsigned short PCOUT12         : 1; /*  */
    unsigned short PCOUT13         : 1; /*  */
    unsigned short PCOUT14         : 1; /*  */
    unsigned short PCOUT15         : 1; /*  */
  } PCOUT_bit;

  struct
  {
    unsigned char PCOUT_L;
    unsigned char PCOUT_H;
  };
  struct
  {
    unsigned char P5OUT;   /* Port 5 Output */
    unsigned char P6OUT;   /* Port 6 Output */
  };
  struct
  {
    struct
    {
      unsigned char P5OUT0          : 1; /*  */
      unsigned char P5OUT1          : 1; /*  */
      unsigned char P5OUT2          : 1; /*  */
      unsigned char P5OUT3          : 1; /*  */
      unsigned char P5OUT4          : 1; /*  */
      unsigned char P5OUT5          : 1; /*  */
      unsigned char P5OUT6          : 1; /*  */
      unsigned char P5OUT7          : 1; /*  */
    } P5OUT_bit;

    struct
    {
      unsigned char P6OUT0          : 1; /*  */
      unsigned char P6OUT1          : 1; /*  */
      unsigned char P6OUT2          : 1; /*  */
      unsigned char P6OUT3          : 1; /*  */
      unsigned char P6OUT4          : 1; /*  */
      unsigned char P6OUT5          : 1; /*  */
      unsigned char P6OUT6          : 1; /*  */
      unsigned char P6OUT7          : 1; /*  */
    } P6OUT_bit;
  }; 
} @0x0242;

enum {
  PCOUT0          = 0x0001,
  PCOUT1          = 0x0002,
  PCOUT2          = 0x0004,
  PCOUT3          = 0x0008,
  PCOUT4          = 0x0010,
  PCOUT5          = 0x0020,
  PCOUT6          = 0x0040,
  PCOUT7          = 0x0080,
  PCOUT8          = 0x0100,
  PCOUT9          = 0x0200,
  PCOUT10         = 0x0400,
  PCOUT11         = 0x0800,
  PCOUT12         = 0x1000,
  PCOUT13         = 0x2000,
  PCOUT14         = 0x4000,
  PCOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PCDIR;   /* Port C Direction */

  struct
  {
    unsigned short PCDIR0          : 1; /*  */
    unsigned short PCDIR1          : 1; /*  */
    unsigned short PCDIR2          : 1; /*  */
    unsigned short PCDIR3          : 1; /*  */
    unsigned short PCDIR4          : 1; /*  */
    unsigned short PCDIR5          : 1; /*  */
    unsigned short PCDIR6          : 1; /*  */
    unsigned short PCDIR7          : 1; /*  */
    unsigned short PCDIR8          : 1; /*  */
    unsigned short PCDIR9          : 1; /*  */
    unsigned short PCDIR10         : 1; /*  */
    unsigned short PCDIR11         : 1; /*  */
    unsigned short PCDIR12         : 1; /*  */
    unsigned short PCDIR13         : 1; /*  */
    unsigned short PCDIR14         : 1; /*  */
    unsigned short PCDIR15         : 1; /*  */
  } PCDIR_bit;

  struct
  {
    unsigned char PCDIR_L;
    unsigned char PCDIR_H;
  };
  struct
  {
    unsigned char P5DIR;   /* Port 5 Direction */
    unsigned char P6DIR;   /* Port 6 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P5DIR0          : 1; /*  */
      unsigned char P5DIR1          : 1; /*  */
      unsigned char P5DIR2          : 1; /*  */
      unsigned char P5DIR3          : 1; /*  */
      unsigned char P5DIR4          : 1; /*  */
      unsigned char P5DIR5          : 1; /*  */
      unsigned char P5DIR6          : 1; /*  */
      unsigned char P5DIR7          : 1; /*  */
    } P5DIR_bit;

    struct
    {
      unsigned char P6DIR0          : 1; /*  */
      unsigned char P6DIR1          : 1; /*  */
      unsigned char P6DIR2          : 1; /*  */
      unsigned char P6DIR3          : 1; /*  */
      unsigned char P6DIR4          : 1; /*  */
      unsigned char P6DIR5          : 1; /*  */
      unsigned char P6DIR6          : 1; /*  */
      unsigned char P6DIR7          : 1; /*  */
    } P6DIR_bit;
  }; 
} @0x0244;

enum {
  PCDIR0          = 0x0001,
  PCDIR1          = 0x0002,
  PCDIR2          = 0x0004,
  PCDIR3          = 0x0008,
  PCDIR4          = 0x0010,
  PCDIR5          = 0x0020,
  PCDIR6          = 0x0040,
  PCDIR7          = 0x0080,
  PCDIR8          = 0x0100,
  PCDIR9          = 0x0200,
  PCDIR10         = 0x0400,
  PCDIR11         = 0x0800,
  PCDIR12         = 0x1000,
  PCDIR13         = 0x2000,
  PCDIR14         = 0x4000,
  PCDIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PCREN;   /* Port C Resistor Enable */

  struct
  {
    unsigned short PCREN0          : 1; /*  */
    unsigned short PCREN1          : 1; /*  */
    unsigned short PCREN2          : 1; /*  */
    unsigned short PCREN3          : 1; /*  */
    unsigned short PCREN4          : 1; /*  */
    unsigned short PCREN5          : 1; /*  */
    unsigned short PCREN6          : 1; /*  */
    unsigned short PCREN7          : 1; /*  */
    unsigned short PCREN8          : 1; /*  */
    unsigned short PCREN9          : 1; /*  */
    unsigned short PCREN10         : 1; /*  */
    unsigned short PCREN11         : 1; /*  */
    unsigned short PCREN12         : 1; /*  */
    unsigned short PCREN13         : 1; /*  */
    unsigned short PCREN14         : 1; /*  */
    unsigned short PCREN15         : 1; /*  */
  } PCREN_bit;

  struct
  {
    unsigned char PCREN_L;
    unsigned char PCREN_H;
  };
  struct
  {
    unsigned char P5REN;   /* Port 5 Resistor Enable */
    unsigned char P6REN;   /* Port 6 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P5REN0          : 1; /*  */
      unsigned char P5REN1          : 1; /*  */
      unsigned char P5REN2          : 1; /*  */
      unsigned char P5REN3          : 1; /*  */
      unsigned char P5REN4          : 1; /*  */
      unsigned char P5REN5          : 1; /*  */
      unsigned char P5REN6          : 1; /*  */
      unsigned char P5REN7          : 1; /*  */
    } P5REN_bit;

    struct
    {
      unsigned char P6REN0          : 1; /*  */
      unsigned char P6REN1          : 1; /*  */
      unsigned char P6REN2          : 1; /*  */
      unsigned char P6REN3          : 1; /*  */
      unsigned char P6REN4          : 1; /*  */
      unsigned char P6REN5          : 1; /*  */
      unsigned char P6REN6          : 1; /*  */
      unsigned char P6REN7          : 1; /*  */
    } P6REN_bit;
  }; 
} @0x0246;

enum {
  PCREN0          = 0x0001,
  PCREN1          = 0x0002,
  PCREN2          = 0x0004,
  PCREN3          = 0x0008,
  PCREN4          = 0x0010,
  PCREN5          = 0x0020,
  PCREN6          = 0x0040,
  PCREN7          = 0x0080,
  PCREN8          = 0x0100,
  PCREN9          = 0x0200,
  PCREN10         = 0x0400,
  PCREN11         = 0x0800,
  PCREN12         = 0x1000,
  PCREN13         = 0x2000,
  PCREN14         = 0x4000,
  PCREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PCDS;   /* Port C Drive Strenght */

  struct
  {
    unsigned short PCDS0           : 1; /*  */
    unsigned short PCDS1           : 1; /*  */
    unsigned short PCDS2           : 1; /*  */
    unsigned short PCDS3           : 1; /*  */
    unsigned short PCDS4           : 1; /*  */
    unsigned short PCDS5           : 1; /*  */
    unsigned short PCDS6           : 1; /*  */
    unsigned short PCDS7           : 1; /*  */
    unsigned short PCDS8           : 1; /*  */
    unsigned short PCDS9           : 1; /*  */
    unsigned short PCDS10          : 1; /*  */
    unsigned short PCDS11          : 1; /*  */
    unsigned short PCDS12          : 1; /*  */
    unsigned short PCDS13          : 1; /*  */
    unsigned short PCDS14          : 1; /*  */
    unsigned short PCDS15          : 1; /*  */
  } PCDS_bit;

  struct
  {
    unsigned char PCDS_L;
    unsigned char PCDS_H;
  };
  struct
  {
    unsigned char P5DS;   /* Port 5 Drive Strenght */
    unsigned char P6DS;   /* Port 6 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P5DS0           : 1; /*  */
      unsigned char P5DS1           : 1; /*  */
      unsigned char P5DS2           : 1; /*  */
      unsigned char P5DS3           : 1; /*  */
      unsigned char P5DS4           : 1; /*  */
      unsigned char P5DS5           : 1; /*  */
      unsigned char P5DS6           : 1; /*  */
      unsigned char P5DS7           : 1; /*  */
    } P5DS_bit;

    struct
    {
      unsigned char P6DS0           : 1; /*  */
      unsigned char P6DS1           : 1; /*  */
      unsigned char P6DS2           : 1; /*  */
      unsigned char P6DS3           : 1; /*  */
      unsigned char P6DS4           : 1; /*  */
      unsigned char P6DS5           : 1; /*  */
      unsigned char P6DS6           : 1; /*  */
      unsigned char P6DS7           : 1; /*  */
    } P6DS_bit;
  }; 
} @0x0248;

enum {
  PCDS0           = 0x0001,
  PCDS1           = 0x0002,
  PCDS2           = 0x0004,
  PCDS3           = 0x0008,
  PCDS4           = 0x0010,
  PCDS5           = 0x0020,
  PCDS6           = 0x0040,
  PCDS7           = 0x0080,
  PCDS8           = 0x0100,
  PCDS9           = 0x0200,
  PCDS10          = 0x0400,
  PCDS11          = 0x0800,
  PCDS12          = 0x1000,
  PCDS13          = 0x2000,
  PCDS14          = 0x4000,
  PCDS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PCSEL;   /* Port C Selection */

  struct
  {
    unsigned short PCSEL0          : 1; /*  */
    unsigned short PCSEL1          : 1; /*  */
    unsigned short PCSEL2          : 1; /*  */
    unsigned short PCSEL3          : 1; /*  */
    unsigned short PCSEL4          : 1; /*  */
    unsigned short PCSEL5          : 1; /*  */
    unsigned short PCSEL6          : 1; /*  */
    unsigned short PCSEL7          : 1; /*  */
    unsigned short PCSEL8          : 1; /*  */
    unsigned short PCSEL9          : 1; /*  */
    unsigned short PCSEL10         : 1; /*  */
    unsigned short PCSEL11         : 1; /*  */
    unsigned short PCSEL12         : 1; /*  */
    unsigned short PCSEL13         : 1; /*  */
    unsigned short PCSEL14         : 1; /*  */
    unsigned short PCSEL15         : 1; /*  */
  } PCSEL_bit;

  struct
  {
    unsigned char PCSEL_L;
    unsigned char PCSEL_H;
  };
  struct
  {
    unsigned char P5SEL;   /* Port 5 Selection */
    unsigned char P6SEL;   /* Port 6 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P5SEL0          : 1; /*  */
      unsigned char P5SEL1          : 1; /*  */
      unsigned char P5SEL2          : 1; /*  */
      unsigned char P5SEL3          : 1; /*  */
      unsigned char P5SEL4          : 1; /*  */
      unsigned char P5SEL5          : 1; /*  */
      unsigned char P5SEL6          : 1; /*  */
      unsigned char P5SEL7          : 1; /*  */
    } P5SEL_bit;

    struct
    {
      unsigned char P6SEL0          : 1; /*  */
      unsigned char P6SEL1          : 1; /*  */
      unsigned char P6SEL2          : 1; /*  */
      unsigned char P6SEL3          : 1; /*  */
      unsigned char P6SEL4          : 1; /*  */
      unsigned char P6SEL5          : 1; /*  */
      unsigned char P6SEL6          : 1; /*  */
      unsigned char P6SEL7          : 1; /*  */
    } P6SEL_bit;
  }; 
} @0x024A;

enum {
  PCSEL0          = 0x0001,
  PCSEL1          = 0x0002,
  PCSEL2          = 0x0004,
  PCSEL3          = 0x0008,
  PCSEL4          = 0x0010,
  PCSEL5          = 0x0020,
  PCSEL6          = 0x0040,
  PCSEL7          = 0x0080,
  PCSEL8          = 0x0100,
  PCSEL9          = 0x0200,
  PCSEL10         = 0x0400,
  PCSEL11         = 0x0800,
  PCSEL12         = 0x1000,
  PCSEL13         = 0x2000,
  PCSEL14         = 0x4000,
  PCSEL15         = 0x8000
};



#define __MSP430_HAS_PORT5_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTC_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT5_R__ 0x0240
#define __MSP430_BASEADDRESS_PORT6_R__ 0x0240
#define __MSP430_BASEADDRESS_PORTC_R__ 0x0240

/*-------------------------------------------------------------------------
 *   Port 5/6
 *-------------------------------------------------------------------------*/


enum {
  P5IN0           = 0x0001,
  P5IN1           = 0x0002,
  P5IN2           = 0x0004,
  P5IN3           = 0x0008,
  P5IN4           = 0x0010,
  P5IN5           = 0x0020,
  P5IN6           = 0x0040,
  P5IN7           = 0x0080
};

enum {
  P5OUT0          = 0x0001,
  P5OUT1          = 0x0002,
  P5OUT2          = 0x0004,
  P5OUT3          = 0x0008,
  P5OUT4          = 0x0010,
  P5OUT5          = 0x0020,
  P5OUT6          = 0x0040,
  P5OUT7          = 0x0080
};

enum {
  P5DIR0          = 0x0001,
  P5DIR1          = 0x0002,
  P5DIR2          = 0x0004,
  P5DIR3          = 0x0008,
  P5DIR4          = 0x0010,
  P5DIR5          = 0x0020,
  P5DIR6          = 0x0040,
  P5DIR7          = 0x0080
};

enum {
  P5REN0          = 0x0001,
  P5REN1          = 0x0002,
  P5REN2          = 0x0004,
  P5REN3          = 0x0008,
  P5REN4          = 0x0010,
  P5REN5          = 0x0020,
  P5REN6          = 0x0040,
  P5REN7          = 0x0080
};

enum {
  P5DS0           = 0x0001,
  P5DS1           = 0x0002,
  P5DS2           = 0x0004,
  P5DS3           = 0x0008,
  P5DS4           = 0x0010,
  P5DS5           = 0x0020,
  P5DS6           = 0x0040,
  P5DS7           = 0x0080
};

enum {
  P5SEL0          = 0x0001,
  P5SEL1          = 0x0002,
  P5SEL2          = 0x0004,
  P5SEL3          = 0x0008,
  P5SEL4          = 0x0010,
  P5SEL5          = 0x0020,
  P5SEL6          = 0x0040,
  P5SEL7          = 0x0080
};

enum {
  P6IN0           = 0x0001,
  P6IN1           = 0x0002,
  P6IN2           = 0x0004,
  P6IN3           = 0x0008,
  P6IN4           = 0x0010,
  P6IN5           = 0x0020,
  P6IN6           = 0x0040,
  P6IN7           = 0x0080
};

enum {
  P6OUT0          = 0x0001,
  P6OUT1          = 0x0002,
  P6OUT2          = 0x0004,
  P6OUT3          = 0x0008,
  P6OUT4          = 0x0010,
  P6OUT5          = 0x0020,
  P6OUT6          = 0x0040,
  P6OUT7          = 0x0080
};

enum {
  P6DIR0          = 0x0001,
  P6DIR1          = 0x0002,
  P6DIR2          = 0x0004,
  P6DIR3          = 0x0008,
  P6DIR4          = 0x0010,
  P6DIR5          = 0x0020,
  P6DIR6          = 0x0040,
  P6DIR7          = 0x0080
};

enum {
  P6REN0          = 0x0001,
  P6REN1          = 0x0002,
  P6REN2          = 0x0004,
  P6REN3          = 0x0008,
  P6REN4          = 0x0010,
  P6REN5          = 0x0020,
  P6REN6          = 0x0040,
  P6REN7          = 0x0080
};

enum {
  P6DS0           = 0x0001,
  P6DS1           = 0x0002,
  P6DS2           = 0x0004,
  P6DS3           = 0x0008,
  P6DS4           = 0x0010,
  P6DS5           = 0x0020,
  P6DS6           = 0x0040,
  P6DS7           = 0x0080
};

enum {
  P6SEL0          = 0x0001,
  P6SEL1          = 0x0002,
  P6SEL2          = 0x0004,
  P6SEL3          = 0x0008,
  P6SEL4          = 0x0010,
  P6SEL5          = 0x0020,
  P6SEL6          = 0x0040,
  P6SEL7          = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port D
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PDIN;   /* Port D Input */

  struct
  {
    unsigned __READ short PDIN0           : 1; /*  */
    unsigned __READ short PDIN1           : 1; /*  */
    unsigned __READ short PDIN2           : 1; /*  */
    unsigned __READ short PDIN3           : 1; /*  */
    unsigned __READ short PDIN4           : 1; /*  */
    unsigned __READ short PDIN5           : 1; /*  */
    unsigned __READ short PDIN6           : 1; /*  */
    unsigned __READ short PDIN7           : 1; /*  */
    unsigned __READ short PDIN8           : 1; /*  */
    unsigned __READ short PDIN9           : 1; /*  */
    unsigned __READ short PDIN10          : 1; /*  */
    unsigned __READ short PDIN11          : 1; /*  */
    unsigned __READ short PDIN12          : 1; /*  */
    unsigned __READ short PDIN13          : 1; /*  */
    unsigned __READ short PDIN14          : 1; /*  */
    unsigned __READ short PDIN15          : 1; /*  */
  } PDIN_bit;

  struct
  {
    unsigned __READ char PDIN_L;
    unsigned __READ char PDIN_H;
  };
  struct
  {
    unsigned char P7IN;   /* Port 7 Input */
    unsigned char P8IN;   /* Port 8 Input */
  };
  struct
  {
    struct
    {
      unsigned char P7IN0           : 1; /*  */
      unsigned char P7IN1           : 1; /*  */
      unsigned char P7IN2           : 1; /*  */
      unsigned char P7IN3           : 1; /*  */
      unsigned char P7IN4           : 1; /*  */
      unsigned char P7IN5           : 1; /*  */
      unsigned char P7IN6           : 1; /*  */
      unsigned char P7IN7           : 1; /*  */
    } P7IN_bit;

    struct
    {
      unsigned char P8IN0           : 1; /*  */
      unsigned char P8IN1           : 1; /*  */
      unsigned char P8IN2           : 1; /*  */
      unsigned char P8IN3           : 1; /*  */
      unsigned char P8IN4           : 1; /*  */
      unsigned char P8IN5           : 1; /*  */
      unsigned char P8IN6           : 1; /*  */
      unsigned char P8IN7           : 1; /*  */
    } P8IN_bit;
  }; 
} @0x0260;

enum {
  PDIN0           = 0x0001,
  PDIN1           = 0x0002,
  PDIN2           = 0x0004,
  PDIN3           = 0x0008,
  PDIN4           = 0x0010,
  PDIN5           = 0x0020,
  PDIN6           = 0x0040,
  PDIN7           = 0x0080,
  PDIN8           = 0x0100,
  PDIN9           = 0x0200,
  PDIN10          = 0x0400,
  PDIN11          = 0x0800,
  PDIN12          = 0x1000,
  PDIN13          = 0x2000,
  PDIN14          = 0x4000,
  PDIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PDOUT;   /* Port D Output */

  struct
  {
    unsigned short PDOUT0          : 1; /*  */
    unsigned short PDOUT1          : 1; /*  */
    unsigned short PDOUT2          : 1; /*  */
    unsigned short PDOUT3          : 1; /*  */
    unsigned short PDOUT4          : 1; /*  */
    unsigned short PDOUT5          : 1; /*  */
    unsigned short PDOUT6          : 1; /*  */
    unsigned short PDOUT7          : 1; /*  */
    unsigned short PDOUT8          : 1; /*  */
    unsigned short PDOUT9          : 1; /*  */
    unsigned short PDOUT10         : 1; /*  */
    unsigned short PDOUT11         : 1; /*  */
    unsigned short PDOUT12         : 1; /*  */
    unsigned short PDOUT13         : 1; /*  */
    unsigned short PDOUT14         : 1; /*  */
    unsigned short PDOUT15         : 1; /*  */
  } PDOUT_bit;

  struct
  {
    unsigned char PDOUT_L;
    unsigned char PDOUT_H;
  };
  struct
  {
    unsigned char P7OUT;   /* Port 7 Output */
    unsigned char P8OUT;   /* Port 8 Output */
  };
  struct
  {
    struct
    {
      unsigned char P7OUT0          : 1; /*  */
      unsigned char P7OUT1          : 1; /*  */
      unsigned char P7OUT2          : 1; /*  */
      unsigned char P7OUT3          : 1; /*  */
      unsigned char P7OUT4          : 1; /*  */
      unsigned char P7OUT5          : 1; /*  */
      unsigned char P7OUT6          : 1; /*  */
      unsigned char P7OUT7          : 1; /*  */
    } P7OUT_bit;

    struct
    {
      unsigned char P8OUT0          : 1; /*  */
      unsigned char P8OUT1          : 1; /*  */
      unsigned char P8OUT2          : 1; /*  */
      unsigned char P8OUT3          : 1; /*  */
      unsigned char P8OUT4          : 1; /*  */
      unsigned char P8OUT5          : 1; /*  */
      unsigned char P8OUT6          : 1; /*  */
      unsigned char P8OUT7          : 1; /*  */
    } P8OUT_bit;
  }; 
} @0x0262;

enum {
  PDOUT0          = 0x0001,
  PDOUT1          = 0x0002,
  PDOUT2          = 0x0004,
  PDOUT3          = 0x0008,
  PDOUT4          = 0x0010,
  PDOUT5          = 0x0020,
  PDOUT6          = 0x0040,
  PDOUT7          = 0x0080,
  PDOUT8          = 0x0100,
  PDOUT9          = 0x0200,
  PDOUT10         = 0x0400,
  PDOUT11         = 0x0800,
  PDOUT12         = 0x1000,
  PDOUT13         = 0x2000,
  PDOUT14         = 0x4000,
  PDOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PDDIR;   /* Port D Direction */

  struct
  {
    unsigned short PDDIR0          : 1; /*  */
    unsigned short PDDIR1          : 1; /*  */
    unsigned short PDDIR2          : 1; /*  */
    unsigned short PDDIR3          : 1; /*  */
    unsigned short PDDIR4          : 1; /*  */
    unsigned short PDDIR5          : 1; /*  */
    unsigned short PDDIR6          : 1; /*  */
    unsigned short PDDIR7          : 1; /*  */
    unsigned short PDDIR8          : 1; /*  */
    unsigned short PDDIR9          : 1; /*  */
    unsigned short PDDIR10         : 1; /*  */
    unsigned short PDDIR11         : 1; /*  */
    unsigned short PDDIR12         : 1; /*  */
    unsigned short PDDIR13         : 1; /*  */
    unsigned short PDDIR14         : 1; /*  */
    unsigned short PDDIR15         : 1; /*  */
  } PDDIR_bit;

  struct
  {
    unsigned char PDDIR_L;
    unsigned char PDDIR_H;
  };
  struct
  {
    unsigned char P7DIR;   /* Port 7 Direction */
    unsigned char P8DIR;   /* Port 8 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P7DIR0          : 1; /*  */
      unsigned char P7DIR1          : 1; /*  */
      unsigned char P7DIR2          : 1; /*  */
      unsigned char P7DIR3          : 1; /*  */
      unsigned char P7DIR4          : 1; /*  */
      unsigned char P7DIR5          : 1; /*  */
      unsigned char P7DIR6          : 1; /*  */
      unsigned char P7DIR7          : 1; /*  */
    } P7DIR_bit;

    struct
    {
      unsigned char P8DIR0          : 1; /*  */
      unsigned char P8DIR1          : 1; /*  */
      unsigned char P8DIR2          : 1; /*  */
      unsigned char P8DIR3          : 1; /*  */
      unsigned char P8DIR4          : 1; /*  */
      unsigned char P8DIR5          : 1; /*  */
      unsigned char P8DIR6          : 1; /*  */
      unsigned char P8DIR7          : 1; /*  */
    } P8DIR_bit;
  }; 
} @0x0264;

enum {
  PDDIR0          = 0x0001,
  PDDIR1          = 0x0002,
  PDDIR2          = 0x0004,
  PDDIR3          = 0x0008,
  PDDIR4          = 0x0010,
  PDDIR5          = 0x0020,
  PDDIR6          = 0x0040,
  PDDIR7          = 0x0080,
  PDDIR8          = 0x0100,
  PDDIR9          = 0x0200,
  PDDIR10         = 0x0400,
  PDDIR11         = 0x0800,
  PDDIR12         = 0x1000,
  PDDIR13         = 0x2000,
  PDDIR14         = 0x4000,
  PDDIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PDREN;   /* Port D Resistor Enable */

  struct
  {
    unsigned short PDREN0          : 1; /*  */
    unsigned short PDREN1          : 1; /*  */
    unsigned short PDREN2          : 1; /*  */
    unsigned short PDREN3          : 1; /*  */
    unsigned short PDREN4          : 1; /*  */
    unsigned short PDREN5          : 1; /*  */
    unsigned short PDREN6          : 1; /*  */
    unsigned short PDREN7          : 1; /*  */
    unsigned short PDREN8          : 1; /*  */
    unsigned short PDREN9          : 1; /*  */
    unsigned short PDREN10         : 1; /*  */
    unsigned short PDREN11         : 1; /*  */
    unsigned short PDREN12         : 1; /*  */
    unsigned short PDREN13         : 1; /*  */
    unsigned short PDREN14         : 1; /*  */
    unsigned short PDREN15         : 1; /*  */
  } PDREN_bit;

  struct
  {
    unsigned char PDREN_L;
    unsigned char PDREN_H;
  };
  struct
  {
    unsigned char P7REN;   /* Port 7 Resistor Enable */
    unsigned char P8REN;   /* Port 8 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P7REN0          : 1; /*  */
      unsigned char P7REN1          : 1; /*  */
      unsigned char P7REN2          : 1; /*  */
      unsigned char P7REN3          : 1; /*  */
      unsigned char P7REN4          : 1; /*  */
      unsigned char P7REN5          : 1; /*  */
      unsigned char P7REN6          : 1; /*  */
      unsigned char P7REN7          : 1; /*  */
    } P7REN_bit;

    struct
    {
      unsigned char P8REN0          : 1; /*  */
      unsigned char P8REN1          : 1; /*  */
      unsigned char P8REN2          : 1; /*  */
      unsigned char P8REN3          : 1; /*  */
      unsigned char P8REN4          : 1; /*  */
      unsigned char P8REN5          : 1; /*  */
      unsigned char P8REN6          : 1; /*  */
      unsigned char P8REN7          : 1; /*  */
    } P8REN_bit;
  }; 
} @0x0266;

enum {
  PDREN0          = 0x0001,
  PDREN1          = 0x0002,
  PDREN2          = 0x0004,
  PDREN3          = 0x0008,
  PDREN4          = 0x0010,
  PDREN5          = 0x0020,
  PDREN6          = 0x0040,
  PDREN7          = 0x0080,
  PDREN8          = 0x0100,
  PDREN9          = 0x0200,
  PDREN10         = 0x0400,
  PDREN11         = 0x0800,
  PDREN12         = 0x1000,
  PDREN13         = 0x2000,
  PDREN14         = 0x4000,
  PDREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PDDS;   /* Port D Drive Strenght */

  struct
  {
    unsigned short PDDS0           : 1; /*  */
    unsigned short PDDS1           : 1; /*  */
    unsigned short PDDS2           : 1; /*  */
    unsigned short PDDS3           : 1; /*  */
    unsigned short PDDS4           : 1; /*  */
    unsigned short PDDS5           : 1; /*  */
    unsigned short PDDS6           : 1; /*  */
    unsigned short PDDS7           : 1; /*  */
    unsigned short PDDS8           : 1; /*  */
    unsigned short PDDS9           : 1; /*  */
    unsigned short PDDS10          : 1; /*  */
    unsigned short PDDS11          : 1; /*  */
    unsigned short PDDS12          : 1; /*  */
    unsigned short PDDS13          : 1; /*  */
    unsigned short PDDS14          : 1; /*  */
    unsigned short PDDS15          : 1; /*  */
  } PDDS_bit;

  struct
  {
    unsigned char PDDS_L;
    unsigned char PDDS_H;
  };
  struct
  {
    unsigned char P7DS;   /* Port 7 Drive Strenght */
    unsigned char P8DS;   /* Port 8 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P7DS0           : 1; /*  */
      unsigned char P7DS1           : 1; /*  */
      unsigned char P7DS2           : 1; /*  */
      unsigned char P7DS3           : 1; /*  */
      unsigned char P7DS4           : 1; /*  */
      unsigned char P7DS5           : 1; /*  */
      unsigned char P7DS6           : 1; /*  */
      unsigned char P7DS7           : 1; /*  */
    } P7DS_bit;

    struct
    {
      unsigned char P8DS0           : 1; /*  */
      unsigned char P8DS1           : 1; /*  */
      unsigned char P8DS2           : 1; /*  */
      unsigned char P8DS3           : 1; /*  */
      unsigned char P8DS4           : 1; /*  */
      unsigned char P8DS5           : 1; /*  */
      unsigned char P8DS6           : 1; /*  */
      unsigned char P8DS7           : 1; /*  */
    } P8DS_bit;
  }; 
} @0x0268;

enum {
  PDDS0           = 0x0001,
  PDDS1           = 0x0002,
  PDDS2           = 0x0004,
  PDDS3           = 0x0008,
  PDDS4           = 0x0010,
  PDDS5           = 0x0020,
  PDDS6           = 0x0040,
  PDDS7           = 0x0080,
  PDDS8           = 0x0100,
  PDDS9           = 0x0200,
  PDDS10          = 0x0400,
  PDDS11          = 0x0800,
  PDDS12          = 0x1000,
  PDDS13          = 0x2000,
  PDDS14          = 0x4000,
  PDDS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PDSEL;   /* Port D Selection */

  struct
  {
    unsigned short PDSEL0          : 1; /*  */
    unsigned short PDSEL1          : 1; /*  */
    unsigned short PDSEL2          : 1; /*  */
    unsigned short PDSEL3          : 1; /*  */
    unsigned short PDSEL4          : 1; /*  */
    unsigned short PDSEL5          : 1; /*  */
    unsigned short PDSEL6          : 1; /*  */
    unsigned short PDSEL7          : 1; /*  */
    unsigned short PDSEL8          : 1; /*  */
    unsigned short PDSEL9          : 1; /*  */
    unsigned short PDSEL10         : 1; /*  */
    unsigned short PDSEL11         : 1; /*  */
    unsigned short PDSEL12         : 1; /*  */
    unsigned short PDSEL13         : 1; /*  */
    unsigned short PDSEL14         : 1; /*  */
    unsigned short PDSEL15         : 1; /*  */
  } PDSEL_bit;

  struct
  {
    unsigned char PDSEL_L;
    unsigned char PDSEL_H;
  };
  struct
  {
    unsigned char P7SEL;   /* Port 7 Selection */
    unsigned char P8SEL;   /* Port 8 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P7SEL0          : 1; /*  */
      unsigned char P7SEL1          : 1; /*  */
      unsigned char P7SEL2          : 1; /*  */
      unsigned char P7SEL3          : 1; /*  */
      unsigned char P7SEL4          : 1; /*  */
      unsigned char P7SEL5          : 1; /*  */
      unsigned char P7SEL6          : 1; /*  */
      unsigned char P7SEL7          : 1; /*  */
    } P7SEL_bit;

    struct
    {
      unsigned char P8SEL0          : 1; /*  */
      unsigned char P8SEL1          : 1; /*  */
      unsigned char P8SEL2          : 1; /*  */
      unsigned char P8SEL3          : 1; /*  */
      unsigned char P8SEL4          : 1; /*  */
      unsigned char P8SEL5          : 1; /*  */
      unsigned char P8SEL6          : 1; /*  */
      unsigned char P8SEL7          : 1; /*  */
    } P8SEL_bit;
  }; 
} @0x026A;

enum {
  PDSEL0          = 0x0001,
  PDSEL1          = 0x0002,
  PDSEL2          = 0x0004,
  PDSEL3          = 0x0008,
  PDSEL4          = 0x0010,
  PDSEL5          = 0x0020,
  PDSEL6          = 0x0040,
  PDSEL7          = 0x0080,
  PDSEL8          = 0x0100,
  PDSEL9          = 0x0200,
  PDSEL10         = 0x0400,
  PDSEL11         = 0x0800,
  PDSEL12         = 0x1000,
  PDSEL13         = 0x2000,
  PDSEL14         = 0x4000,
  PDSEL15         = 0x8000
};



#define __MSP430_HAS_PORT7_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT8_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTD_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT7_R__ 0x0260
#define __MSP430_BASEADDRESS_PORT8_R__ 0x0260
#define __MSP430_BASEADDRESS_PORTD_R__ 0x0260

/*-------------------------------------------------------------------------
 *   Port 7/8
 *-------------------------------------------------------------------------*/


enum {
  P7IN0           = 0x0001,
  P7IN1           = 0x0002,
  P7IN2           = 0x0004,
  P7IN3           = 0x0008,
  P7IN4           = 0x0010,
  P7IN5           = 0x0020,
  P7IN6           = 0x0040,
  P7IN7           = 0x0080
};

enum {
  P7OUT0          = 0x0001,
  P7OUT1          = 0x0002,
  P7OUT2          = 0x0004,
  P7OUT3          = 0x0008,
  P7OUT4          = 0x0010,
  P7OUT5          = 0x0020,
  P7OUT6          = 0x0040,
  P7OUT7          = 0x0080
};

enum {
  P7DIR0          = 0x0001,
  P7DIR1          = 0x0002,
  P7DIR2          = 0x0004,
  P7DIR3          = 0x0008,
  P7DIR4          = 0x0010,
  P7DIR5          = 0x0020,
  P7DIR6          = 0x0040,
  P7DIR7          = 0x0080
};

enum {
  P7REN0          = 0x0001,
  P7REN1          = 0x0002,
  P7REN2          = 0x0004,
  P7REN3          = 0x0008,
  P7REN4          = 0x0010,
  P7REN5          = 0x0020,
  P7REN6          = 0x0040,
  P7REN7          = 0x0080
};

enum {
  P7DS0           = 0x0001,
  P7DS1           = 0x0002,
  P7DS2           = 0x0004,
  P7DS3           = 0x0008,
  P7DS4           = 0x0010,
  P7DS5           = 0x0020,
  P7DS6           = 0x0040,
  P7DS7           = 0x0080
};

enum {
  P7SEL0          = 0x0001,
  P7SEL1          = 0x0002,
  P7SEL2          = 0x0004,
  P7SEL3          = 0x0008,
  P7SEL4          = 0x0010,
  P7SEL5          = 0x0020,
  P7SEL6          = 0x0040,
  P7SEL7          = 0x0080
};

enum {
  P8IN0           = 0x0001,
  P8IN1           = 0x0002,
  P8IN2           = 0x0004,
  P8IN3           = 0x0008,
  P8IN4           = 0x0010,
  P8IN5           = 0x0020,
  P8IN6           = 0x0040,
  P8IN7           = 0x0080
};

enum {
  P8OUT0          = 0x0001,
  P8OUT1          = 0x0002,
  P8OUT2          = 0x0004,
  P8OUT3          = 0x0008,
  P8OUT4          = 0x0010,
  P8OUT5          = 0x0020,
  P8OUT6          = 0x0040,
  P8OUT7          = 0x0080
};

enum {
  P8DIR0          = 0x0001,
  P8DIR1          = 0x0002,
  P8DIR2          = 0x0004,
  P8DIR3          = 0x0008,
  P8DIR4          = 0x0010,
  P8DIR5          = 0x0020,
  P8DIR6          = 0x0040,
  P8DIR7          = 0x0080
};

enum {
  P8REN0          = 0x0001,
  P8REN1          = 0x0002,
  P8REN2          = 0x0004,
  P8REN3          = 0x0008,
  P8REN4          = 0x0010,
  P8REN5          = 0x0020,
  P8REN6          = 0x0040,
  P8REN7          = 0x0080
};

enum {
  P8DS0           = 0x0001,
  P8DS1           = 0x0002,
  P8DS2           = 0x0004,
  P8DS3           = 0x0008,
  P8DS4           = 0x0010,
  P8DS5           = 0x0020,
  P8DS6           = 0x0040,
  P8DS7           = 0x0080
};

enum {
  P8SEL0          = 0x0001,
  P8SEL1          = 0x0002,
  P8SEL2          = 0x0004,
  P8SEL3          = 0x0008,
  P8SEL4          = 0x0010,
  P8SEL5          = 0x0020,
  P8SEL6          = 0x0040,
  P8SEL7          = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port E
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PEIN;   /* Port E Input */

  struct
  {
    unsigned __READ short PEIN0           : 1; /*  */
    unsigned __READ short PEIN1           : 1; /*  */
    unsigned __READ short PEIN2           : 1; /*  */
    unsigned __READ short PEIN3           : 1; /*  */
    unsigned __READ short PEIN4           : 1; /*  */
    unsigned __READ short PEIN5           : 1; /*  */
    unsigned __READ short PEIN6           : 1; /*  */
    unsigned __READ short PEIN7           : 1; /*  */
    unsigned __READ short PEIN8           : 1; /*  */
    unsigned __READ short PEIN9           : 1; /*  */
    unsigned __READ short PEIN10          : 1; /*  */
    unsigned __READ short PEIN11          : 1; /*  */
    unsigned __READ short PEIN12          : 1; /*  */
    unsigned __READ short PEIN13          : 1; /*  */
    unsigned __READ short PEIN14          : 1; /*  */
    unsigned __READ short PEIN15          : 1; /*  */
  } PEIN_bit;

  struct
  {
    unsigned __READ char PEIN_L;
    unsigned __READ char PEIN_H;
  };
  struct
  {
    unsigned char P9IN;   /* Port 9 Input */
    unsigned char P10IN;   /* Port 10 Input */
  };
  struct
  {
    struct
    {
      unsigned char P9IN0           : 1; /*  */
      unsigned char P9IN1           : 1; /*  */
      unsigned char P9IN2           : 1; /*  */
      unsigned char P9IN3           : 1; /*  */
      unsigned char P9IN4           : 1; /*  */
      unsigned char P9IN5           : 1; /*  */
      unsigned char P9IN6           : 1; /*  */
      unsigned char P9IN7           : 1; /*  */
    } P9IN_bit;

    struct
    {
      unsigned char P10IN0          : 1; /*  */
      unsigned char P10IN1          : 1; /*  */
      unsigned char P10IN2          : 1; /*  */
      unsigned char P10IN3          : 1; /*  */
      unsigned char P10IN4          : 1; /*  */
      unsigned char P10IN5          : 1; /*  */
      unsigned char P10IN6          : 1; /*  */
      unsigned char P10IN7          : 1; /*  */
    } P10IN_bit;
  }; 
} @0x0280;

enum {
  PEIN0           = 0x0001,
  PEIN1           = 0x0002,
  PEIN2           = 0x0004,
  PEIN3           = 0x0008,
  PEIN4           = 0x0010,
  PEIN5           = 0x0020,
  PEIN6           = 0x0040,
  PEIN7           = 0x0080,
  PEIN8           = 0x0100,
  PEIN9           = 0x0200,
  PEIN10          = 0x0400,
  PEIN11          = 0x0800,
  PEIN12          = 0x1000,
  PEIN13          = 0x2000,
  PEIN14          = 0x4000,
  PEIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PEOUT;   /* Port E Output */

  struct
  {
    unsigned short PEOUT0          : 1; /*  */
    unsigned short PEOUT1          : 1; /*  */
    unsigned short PEOUT2          : 1; /*  */
    unsigned short PEOUT3          : 1; /*  */
    unsigned short PEOUT4          : 1; /*  */
    unsigned short PEOUT5          : 1; /*  */
    unsigned short PEOUT6          : 1; /*  */
    unsigned short PEOUT7          : 1; /*  */
    unsigned short PEOUT8          : 1; /*  */
    unsigned short PEOUT9          : 1; /*  */
    unsigned short PEOUT10         : 1; /*  */
    unsigned short PEOUT11         : 1; /*  */
    unsigned short PEOUT12         : 1; /*  */
    unsigned short PEOUT13         : 1; /*  */
    unsigned short PEOUT14         : 1; /*  */
    unsigned short PEOUT15         : 1; /*  */
  } PEOUT_bit;

  struct
  {
    unsigned char PEOUT_L;
    unsigned char PEOUT_H;
  };
  struct
  {
    unsigned char P9OUT;   /* Port 9 Output */
    unsigned char P10OUT;   /* Port 10 Output */
  };
  struct
  {
    struct
    {
      unsigned char P9OUT0          : 1; /*  */
      unsigned char P9OUT1          : 1; /*  */
      unsigned char P9OUT2          : 1; /*  */
      unsigned char P9OUT3          : 1; /*  */
      unsigned char P9OUT4          : 1; /*  */
      unsigned char P9OUT5          : 1; /*  */
      unsigned char P9OUT6          : 1; /*  */
      unsigned char P9OUT7          : 1; /*  */
    } P9OUT_bit;

    struct
    {
      unsigned char P10OUT0         : 1; /*  */
      unsigned char P10OUT1         : 1; /*  */
      unsigned char P10OUT2         : 1; /*  */
      unsigned char P10OUT3         : 1; /*  */
      unsigned char P10OUT4         : 1; /*  */
      unsigned char P10OUT5         : 1; /*  */
      unsigned char P10OUT6         : 1; /*  */
      unsigned char P10OUT7         : 1; /*  */
    } P10OUT_bit;
  }; 
} @0x0282;

enum {
  PEOUT0          = 0x0001,
  PEOUT1          = 0x0002,
  PEOUT2          = 0x0004,
  PEOUT3          = 0x0008,
  PEOUT4          = 0x0010,
  PEOUT5          = 0x0020,
  PEOUT6          = 0x0040,
  PEOUT7          = 0x0080,
  PEOUT8          = 0x0100,
  PEOUT9          = 0x0200,
  PEOUT10         = 0x0400,
  PEOUT11         = 0x0800,
  PEOUT12         = 0x1000,
  PEOUT13         = 0x2000,
  PEOUT14         = 0x4000,
  PEOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PEDIR;   /* Port E Direction */

  struct
  {
    unsigned short PEDIR0          : 1; /*  */
    unsigned short PEDIR1          : 1; /*  */
    unsigned short PEDIR2          : 1; /*  */
    unsigned short PEDIR3          : 1; /*  */
    unsigned short PEDIR4          : 1; /*  */
    unsigned short PEDIR5          : 1; /*  */
    unsigned short PEDIR6          : 1; /*  */
    unsigned short PEDIR7          : 1; /*  */
    unsigned short PEDIR8          : 1; /*  */
    unsigned short PEDIR9          : 1; /*  */
    unsigned short PEDIR10         : 1; /*  */
    unsigned short PEDIR11         : 1; /*  */
    unsigned short PEDIR12         : 1; /*  */
    unsigned short PEDIR13         : 1; /*  */
    unsigned short PEDIR14         : 1; /*  */
    unsigned short PEDIR15         : 1; /*  */
  } PEDIR_bit;

  struct
  {
    unsigned char PEDIR_L;
    unsigned char PEDIR_H;
  };
  struct
  {
    unsigned char P9DIR;   /* Port 9 Direction */
    unsigned char P10DIR;   /* Port 10 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P9DIR0          : 1; /*  */
      unsigned char P9DIR1          : 1; /*  */
      unsigned char P9DIR2          : 1; /*  */
      unsigned char P9DIR3          : 1; /*  */
      unsigned char P9DIR4          : 1; /*  */
      unsigned char P9DIR5          : 1; /*  */
      unsigned char P9DIR6          : 1; /*  */
      unsigned char P9DIR7          : 1; /*  */
    } P9DIR_bit;

    struct
    {
      unsigned char P10DIR0         : 1; /*  */
      unsigned char P10DIR1         : 1; /*  */
      unsigned char P10DIR2         : 1; /*  */
      unsigned char P10DIR3         : 1; /*  */
      unsigned char P10DIR4         : 1; /*  */
      unsigned char P10DIR5         : 1; /*  */
      unsigned char P10DIR6         : 1; /*  */
      unsigned char P10DIR7         : 1; /*  */
    } P10DIR_bit;
  }; 
} @0x0284;

enum {
  PEDIR0          = 0x0001,
  PEDIR1          = 0x0002,
  PEDIR2          = 0x0004,
  PEDIR3          = 0x0008,
  PEDIR4          = 0x0010,
  PEDIR5          = 0x0020,
  PEDIR6          = 0x0040,
  PEDIR7          = 0x0080,
  PEDIR8          = 0x0100,
  PEDIR9          = 0x0200,
  PEDIR10         = 0x0400,
  PEDIR11         = 0x0800,
  PEDIR12         = 0x1000,
  PEDIR13         = 0x2000,
  PEDIR14         = 0x4000,
  PEDIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PEREN;   /* Port E Resistor Enable */

  struct
  {
    unsigned short PEREN0          : 1; /*  */
    unsigned short PEREN1          : 1; /*  */
    unsigned short PEREN2          : 1; /*  */
    unsigned short PEREN3          : 1; /*  */
    unsigned short PEREN4          : 1; /*  */
    unsigned short PEREN5          : 1; /*  */
    unsigned short PEREN6          : 1; /*  */
    unsigned short PEREN7          : 1; /*  */
    unsigned short PEREN8          : 1; /*  */
    unsigned short PEREN9          : 1; /*  */
    unsigned short PEREN10         : 1; /*  */
    unsigned short PEREN11         : 1; /*  */
    unsigned short PEREN12         : 1; /*  */
    unsigned short PEREN13         : 1; /*  */
    unsigned short PEREN14         : 1; /*  */
    unsigned short PEREN15         : 1; /*  */
  } PEREN_bit;

  struct
  {
    unsigned char PEREN_L;
    unsigned char PEREN_H;
  };
  struct
  {
    unsigned char P9REN;   /* Port 9 Resistor Enable */
    unsigned char P10REN;   /* Port 10 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P9REN0          : 1; /*  */
      unsigned char P9REN1          : 1; /*  */
      unsigned char P9REN2          : 1; /*  */
      unsigned char P9REN3          : 1; /*  */
      unsigned char P9REN4          : 1; /*  */
      unsigned char P9REN5          : 1; /*  */
      unsigned char P9REN6          : 1; /*  */
      unsigned char P9REN7          : 1; /*  */
    } P9REN_bit;

    struct
    {
      unsigned char P10REN0         : 1; /*  */
      unsigned char P10REN1         : 1; /*  */
      unsigned char P10REN2         : 1; /*  */
      unsigned char P10REN3         : 1; /*  */
      unsigned char P10REN4         : 1; /*  */
      unsigned char P10REN5         : 1; /*  */
      unsigned char P10REN6         : 1; /*  */
      unsigned char P10REN7         : 1; /*  */
    } P10REN_bit;
  }; 
} @0x0286;

enum {
  PEREN0          = 0x0001,
  PEREN1          = 0x0002,
  PEREN2          = 0x0004,
  PEREN3          = 0x0008,
  PEREN4          = 0x0010,
  PEREN5          = 0x0020,
  PEREN6          = 0x0040,
  PEREN7          = 0x0080,
  PEREN8          = 0x0100,
  PEREN9          = 0x0200,
  PEREN10         = 0x0400,
  PEREN11         = 0x0800,
  PEREN12         = 0x1000,
  PEREN13         = 0x2000,
  PEREN14         = 0x4000,
  PEREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PEDS;   /* Port E Drive Strenght */

  struct
  {
    unsigned short PEDS0           : 1; /*  */
    unsigned short PEDS1           : 1; /*  */
    unsigned short PEDS2           : 1; /*  */
    unsigned short PEDS3           : 1; /*  */
    unsigned short PEDS4           : 1; /*  */
    unsigned short PEDS5           : 1; /*  */
    unsigned short PEDS6           : 1; /*  */
    unsigned short PEDS7           : 1; /*  */
    unsigned short PEDS8           : 1; /*  */
    unsigned short PEDS9           : 1; /*  */
    unsigned short PEDS10          : 1; /*  */
    unsigned short PEDS11          : 1; /*  */
    unsigned short PEDS12          : 1; /*  */
    unsigned short PEDS13          : 1; /*  */
    unsigned short PEDS14          : 1; /*  */
    unsigned short PEDS15          : 1; /*  */
  } PEDS_bit;

  struct
  {
    unsigned char PEDS_L;
    unsigned char PEDS_H;
  };
  struct
  {
    unsigned char P9DS;   /* Port 9 Drive Strenght */
    unsigned char P10DS;   /* Port 10 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P9DS0           : 1; /*  */
      unsigned char P9DS1           : 1; /*  */
      unsigned char P9DS2           : 1; /*  */
      unsigned char P9DS3           : 1; /*  */
      unsigned char P9DS4           : 1; /*  */
      unsigned char P9DS5           : 1; /*  */
      unsigned char P9DS6           : 1; /*  */
      unsigned char P9DS7           : 1; /*  */
    } P9DS_bit;

    struct
    {
      unsigned char P10DS0          : 1; /*  */
      unsigned char P10DS1          : 1; /*  */
      unsigned char P10DS2          : 1; /*  */
      unsigned char P10DS3          : 1; /*  */
      unsigned char P10DS4          : 1; /*  */
      unsigned char P10DS5          : 1; /*  */
      unsigned char P10DS6          : 1; /*  */
      unsigned char P10DS7          : 1; /*  */
    } P10DS_bit;
  }; 
} @0x0288;

enum {
  PEDS0           = 0x0001,
  PEDS1           = 0x0002,
  PEDS2           = 0x0004,
  PEDS3           = 0x0008,
  PEDS4           = 0x0010,
  PEDS5           = 0x0020,
  PEDS6           = 0x0040,
  PEDS7           = 0x0080,
  PEDS8           = 0x0100,
  PEDS9           = 0x0200,
  PEDS10          = 0x0400,
  PEDS11          = 0x0800,
  PEDS12          = 0x1000,
  PEDS13          = 0x2000,
  PEDS14          = 0x4000,
  PEDS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PESEL;   /* Port E Selection */

  struct
  {
    unsigned short PESEL0          : 1; /*  */
    unsigned short PESEL1          : 1; /*  */
    unsigned short PESEL2          : 1; /*  */
    unsigned short PESEL3          : 1; /*  */
    unsigned short PESEL4          : 1; /*  */
    unsigned short PESEL5          : 1; /*  */
    unsigned short PESEL6          : 1; /*  */
    unsigned short PESEL7          : 1; /*  */
    unsigned short PESEL8          : 1; /*  */
    unsigned short PESEL9          : 1; /*  */
    unsigned short PESEL10         : 1; /*  */
    unsigned short PESEL11         : 1; /*  */
    unsigned short PESEL12         : 1; /*  */
    unsigned short PESEL13         : 1; /*  */
    unsigned short PESEL14         : 1; /*  */
    unsigned short PESEL15         : 1; /*  */
  } PESEL_bit;

  struct
  {
    unsigned char PESEL_L;
    unsigned char PESEL_H;
  };
  struct
  {
    unsigned char P9SEL;   /* Port 9 Selection */
    unsigned char P10SEL;   /* Port 10 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P9SEL0          : 1; /*  */
      unsigned char P9SEL1          : 1; /*  */
      unsigned char P9SEL2          : 1; /*  */
      unsigned char P9SEL3          : 1; /*  */
      unsigned char P9SEL4          : 1; /*  */
      unsigned char P9SEL5          : 1; /*  */
      unsigned char P9SEL6          : 1; /*  */
      unsigned char P9SEL7          : 1; /*  */
    } P9SEL_bit;

    struct
    {
      unsigned char P10SEL0         : 1; /*  */
      unsigned char P10SEL1         : 1; /*  */
      unsigned char P10SEL2         : 1; /*  */
      unsigned char P10SEL3         : 1; /*  */
      unsigned char P10SEL4         : 1; /*  */
      unsigned char P10SEL5         : 1; /*  */
      unsigned char P10SEL6         : 1; /*  */
      unsigned char P10SEL7         : 1; /*  */
    } P10SEL_bit;
  }; 
} @0x028A;

enum {
  PESEL0          = 0x0001,
  PESEL1          = 0x0002,
  PESEL2          = 0x0004,
  PESEL3          = 0x0008,
  PESEL4          = 0x0010,
  PESEL5          = 0x0020,
  PESEL6          = 0x0040,
  PESEL7          = 0x0080,
  PESEL8          = 0x0100,
  PESEL9          = 0x0200,
  PESEL10         = 0x0400,
  PESEL11         = 0x0800,
  PESEL12         = 0x1000,
  PESEL13         = 0x2000,
  PESEL14         = 0x4000,
  PESEL15         = 0x8000
};



#define __MSP430_HAS_PORT9_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT10_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTE_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT9_R__ 0x0280
#define __MSP430_BASEADDRESS_PORT10_R__ 0x0280
#define __MSP430_BASEADDRESS_PORTE_R__ 0x0280

/*-------------------------------------------------------------------------
 *   Port 9/10
 *-------------------------------------------------------------------------*/


enum {
  P9IN0           = 0x0001,
  P9IN1           = 0x0002,
  P9IN2           = 0x0004,
  P9IN3           = 0x0008,
  P9IN4           = 0x0010,
  P9IN5           = 0x0020,
  P9IN6           = 0x0040,
  P9IN7           = 0x0080
};

enum {
  P9OUT0          = 0x0001,
  P9OUT1          = 0x0002,
  P9OUT2          = 0x0004,
  P9OUT3          = 0x0008,
  P9OUT4          = 0x0010,
  P9OUT5          = 0x0020,
  P9OUT6          = 0x0040,
  P9OUT7          = 0x0080
};

enum {
  P9DIR0          = 0x0001,
  P9DIR1          = 0x0002,
  P9DIR2          = 0x0004,
  P9DIR3          = 0x0008,
  P9DIR4          = 0x0010,
  P9DIR5          = 0x0020,
  P9DIR6          = 0x0040,
  P9DIR7          = 0x0080
};

enum {
  P9REN0          = 0x0001,
  P9REN1          = 0x0002,
  P9REN2          = 0x0004,
  P9REN3          = 0x0008,
  P9REN4          = 0x0010,
  P9REN5          = 0x0020,
  P9REN6          = 0x0040,
  P9REN7          = 0x0080
};

enum {
  P9DS0           = 0x0001,
  P9DS1           = 0x0002,
  P9DS2           = 0x0004,
  P9DS3           = 0x0008,
  P9DS4           = 0x0010,
  P9DS5           = 0x0020,
  P9DS6           = 0x0040,
  P9DS7           = 0x0080
};

enum {
  P9SEL0          = 0x0001,
  P9SEL1          = 0x0002,
  P9SEL2          = 0x0004,
  P9SEL3          = 0x0008,
  P9SEL4          = 0x0010,
  P9SEL5          = 0x0020,
  P9SEL6          = 0x0040,
  P9SEL7          = 0x0080
};

enum {
  P10IN0          = 0x0001,
  P10IN1          = 0x0002,
  P10IN2          = 0x0004,
  P10IN3          = 0x0008,
  P10IN4          = 0x0010,
  P10IN5          = 0x0020,
  P10IN6          = 0x0040,
  P10IN7          = 0x0080
};

enum {
  P10OUT0         = 0x0001,
  P10OUT1         = 0x0002,
  P10OUT2         = 0x0004,
  P10OUT3         = 0x0008,
  P10OUT4         = 0x0010,
  P10OUT5         = 0x0020,
  P10OUT6         = 0x0040,
  P10OUT7         = 0x0080
};

enum {
  P10DIR0         = 0x0001,
  P10DIR1         = 0x0002,
  P10DIR2         = 0x0004,
  P10DIR3         = 0x0008,
  P10DIR4         = 0x0010,
  P10DIR5         = 0x0020,
  P10DIR6         = 0x0040,
  P10DIR7         = 0x0080
};

enum {
  P10REN0         = 0x0001,
  P10REN1         = 0x0002,
  P10REN2         = 0x0004,
  P10REN3         = 0x0008,
  P10REN4         = 0x0010,
  P10REN5         = 0x0020,
  P10REN6         = 0x0040,
  P10REN7         = 0x0080
};

enum {
  P10DS0          = 0x0001,
  P10DS1          = 0x0002,
  P10DS2          = 0x0004,
  P10DS3          = 0x0008,
  P10DS4          = 0x0010,
  P10DS5          = 0x0020,
  P10DS6          = 0x0040,
  P10DS7          = 0x0080
};

enum {
  P10SEL0         = 0x0001,
  P10SEL1         = 0x0002,
  P10SEL2         = 0x0004,
  P10SEL3         = 0x0008,
  P10SEL4         = 0x0010,
  P10SEL5         = 0x0020,
  P10SEL6         = 0x0040,
  P10SEL7         = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port F
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PFIN;   /* Port F Input */

  struct
  {
    unsigned __READ short PFIN0           : 1; /*  */
    unsigned __READ short PFIN1           : 1; /*  */
    unsigned __READ short PFIN2           : 1; /*  */
    unsigned __READ short PFIN3           : 1; /*  */
    unsigned __READ short PFIN4           : 1; /*  */
    unsigned __READ short PFIN5           : 1; /*  */
    unsigned __READ short PFIN6           : 1; /*  */
    unsigned __READ short PFIN7           : 1; /*  */
    unsigned __READ short PFIN8           : 1; /*  */
    unsigned __READ short PFIN9           : 1; /*  */
    unsigned __READ short PFIN10          : 1; /*  */
    unsigned __READ short PFIN11          : 1; /*  */
    unsigned __READ short PFIN12          : 1; /*  */
    unsigned __READ short PFIN13          : 1; /*  */
    unsigned __READ short PFIN14          : 1; /*  */
    unsigned __READ short PFIN15          : 1; /*  */
  } PFIN_bit;

  struct
  {
    unsigned __READ char PFIN_L;
    unsigned __READ char PFIN_H;
  };
  struct
  {
    unsigned char P11IN;   /* Port 11 Input */
  };
  struct
  {
    struct
    {
      unsigned char P11IN0          : 1; /*  */
      unsigned char P11IN1          : 1; /*  */
      unsigned char P11IN2          : 1; /*  */
      unsigned char P11IN3          : 1; /*  */
      unsigned char P11IN4          : 1; /*  */
      unsigned char P11IN5          : 1; /*  */
      unsigned char P11IN6          : 1; /*  */
      unsigned char P11IN7          : 1; /*  */
    } P11IN_bit;

  }; 
} @0x02A0;

enum {
  PFIN0           = 0x0001,
  PFIN1           = 0x0002,
  PFIN2           = 0x0004,
  PFIN3           = 0x0008,
  PFIN4           = 0x0010,
  PFIN5           = 0x0020,
  PFIN6           = 0x0040,
  PFIN7           = 0x0080,
  PFIN8           = 0x0100,
  PFIN9           = 0x0200,
  PFIN10          = 0x0400,
  PFIN11          = 0x0800,
  PFIN12          = 0x1000,
  PFIN13          = 0x2000,
  PFIN14          = 0x4000,
  PFIN15          = 0x8000
};

__no_init volatile union
{
  unsigned short PFOUT;   /* Port F Output */

  struct
  {
    unsigned short PFOUT0          : 1; /*  */
    unsigned short PFOUT1          : 1; /*  */
    unsigned short PFOUT2          : 1; /*  */
    unsigned short PFOUT3          : 1; /*  */
    unsigned short PFOUT4          : 1; /*  */
    unsigned short PFOUT5          : 1; /*  */
    unsigned short PFOUT6          : 1; /*  */
    unsigned short PFOUT7          : 1; /*  */
    unsigned short PFOUT8          : 1; /*  */
    unsigned short PFOUT9          : 1; /*  */
    unsigned short PFOUT10         : 1; /*  */
    unsigned short PFOUT11         : 1; /*  */
    unsigned short PFOUT12         : 1; /*  */
    unsigned short PFOUT13         : 1; /*  */
    unsigned short PFOUT14         : 1; /*  */
    unsigned short PFOUT15         : 1; /*  */
  } PFOUT_bit;

  struct
  {
    unsigned char PFOUT_L;
    unsigned char PFOUT_H;
  };
  struct
  {
    unsigned char P11OUT;   /* Port 11 Output */
  };
  struct
  {
    struct
    {
      unsigned char P11OUT0         : 1; /*  */
      unsigned char P11OUT1         : 1; /*  */
      unsigned char P11OUT2         : 1; /*  */
      unsigned char P11OUT3         : 1; /*  */
      unsigned char P11OUT4         : 1; /*  */
      unsigned char P11OUT5         : 1; /*  */
      unsigned char P11OUT6         : 1; /*  */
      unsigned char P11OUT7         : 1; /*  */
    } P11OUT_bit;

  }; 
} @0x02A2;

enum {
  PFOUT0          = 0x0001,
  PFOUT1          = 0x0002,
  PFOUT2          = 0x0004,
  PFOUT3          = 0x0008,
  PFOUT4          = 0x0010,
  PFOUT5          = 0x0020,
  PFOUT6          = 0x0040,
  PFOUT7          = 0x0080,
  PFOUT8          = 0x0100,
  PFOUT9          = 0x0200,
  PFOUT10         = 0x0400,
  PFOUT11         = 0x0800,
  PFOUT12         = 0x1000,
  PFOUT13         = 0x2000,
  PFOUT14         = 0x4000,
  PFOUT15         = 0x8000
};

__no_init volatile union
{
  unsigned short PFDIR;   /* Port F Direction */

  struct
  {
    unsigned short PFDIR0          : 1; /*  */
    unsigned short PFDIR1          : 1; /*  */
    unsigned short PFDIR2          : 1; /*  */
    unsigned short PFDIR3          : 1; /*  */
    unsigned short PFDIR4          : 1; /*  */
    unsigned short PFDIR5          : 1; /*  */
    unsigned short PFDIR6          : 1; /*  */
    unsigned short PFDIR7          : 1; /*  */
    unsigned short PFDIR8          : 1; /*  */
    unsigned short PFDIR9          : 1; /*  */
    unsigned short PFDIR10         : 1; /*  */
    unsigned short PFDIR11         : 1; /*  */
    unsigned short PFDIR12         : 1; /*  */
    unsigned short PFDIR13         : 1; /*  */
    unsigned short PFDIR14         : 1; /*  */
    unsigned short PFDIR15         : 1; /*  */
  } PFDIR_bit;

  struct
  {
    unsigned char PFDIR_L;
    unsigned char PFDIR_H;
  };
  struct
  {
    unsigned char P11DIR;   /* Port 11 Direction */
  };
  struct
  {
    struct
    {
      unsigned char P11DIR0         : 1; /*  */
      unsigned char P11DIR1         : 1; /*  */
      unsigned char P11DIR2         : 1; /*  */
      unsigned char P11DIR3         : 1; /*  */
      unsigned char P11DIR4         : 1; /*  */
      unsigned char P11DIR5         : 1; /*  */
      unsigned char P11DIR6         : 1; /*  */
      unsigned char P11DIR7         : 1; /*  */
    } P11DIR_bit;

  }; 
} @0x02A4;

enum {
  PFDIR0          = 0x0001,
  PFDIR1          = 0x0002,
  PFDIR2          = 0x0004,
  PFDIR3          = 0x0008,
  PFDIR4          = 0x0010,
  PFDIR5          = 0x0020,
  PFDIR6          = 0x0040,
  PFDIR7          = 0x0080,
  PFDIR8          = 0x0100,
  PFDIR9          = 0x0200,
  PFDIR10         = 0x0400,
  PFDIR11         = 0x0800,
  PFDIR12         = 0x1000,
  PFDIR13         = 0x2000,
  PFDIR14         = 0x4000,
  PFDIR15         = 0x8000
};

__no_init volatile union
{
  unsigned short PFREN;   /* Port F Resistor Enable */

  struct
  {
    unsigned short PFREN0          : 1; /*  */
    unsigned short PFREN1          : 1; /*  */
    unsigned short PFREN2          : 1; /*  */
    unsigned short PFREN3          : 1; /*  */
    unsigned short PFREN4          : 1; /*  */
    unsigned short PFREN5          : 1; /*  */
    unsigned short PFREN6          : 1; /*  */
    unsigned short PFREN7          : 1; /*  */
    unsigned short PFREN8          : 1; /*  */
    unsigned short PFREN9          : 1; /*  */
    unsigned short PFREN10         : 1; /*  */
    unsigned short PFREN11         : 1; /*  */
    unsigned short PFREN12         : 1; /*  */
    unsigned short PFREN13         : 1; /*  */
    unsigned short PFREN14         : 1; /*  */
    unsigned short PFREN15         : 1; /*  */
  } PFREN_bit;

  struct
  {
    unsigned char PFREN_L;
    unsigned char PFREN_H;
  };
  struct
  {
    unsigned char P11REN;   /* Port 11 Resistor Enable */
  };
  struct
  {
    struct
    {
      unsigned char P11REN0         : 1; /*  */
      unsigned char P11REN1         : 1; /*  */
      unsigned char P11REN2         : 1; /*  */
      unsigned char P11REN3         : 1; /*  */
      unsigned char P11REN4         : 1; /*  */
      unsigned char P11REN5         : 1; /*  */
      unsigned char P11REN6         : 1; /*  */
      unsigned char P11REN7         : 1; /*  */
    } P11REN_bit;

  }; 
} @0x02A6;

enum {
  PFREN0          = 0x0001,
  PFREN1          = 0x0002,
  PFREN2          = 0x0004,
  PFREN3          = 0x0008,
  PFREN4          = 0x0010,
  PFREN5          = 0x0020,
  PFREN6          = 0x0040,
  PFREN7          = 0x0080,
  PFREN8          = 0x0100,
  PFREN9          = 0x0200,
  PFREN10         = 0x0400,
  PFREN11         = 0x0800,
  PFREN12         = 0x1000,
  PFREN13         = 0x2000,
  PFREN14         = 0x4000,
  PFREN15         = 0x8000
};

__no_init volatile union
{
  unsigned short PFDS;   /* Port F Drive Strenght */

  struct
  {
    unsigned short PFDS0           : 1; /*  */
    unsigned short PFDS1           : 1; /*  */
    unsigned short PFDS2           : 1; /*  */
    unsigned short PFDS3           : 1; /*  */
    unsigned short PFDS4           : 1; /*  */
    unsigned short PFDS5           : 1; /*  */
    unsigned short PFDS6           : 1; /*  */
    unsigned short PFDS7           : 1; /*  */
    unsigned short PFDS8           : 1; /*  */
    unsigned short PFDS9           : 1; /*  */
    unsigned short PFDS10          : 1; /*  */
    unsigned short PFDS11          : 1; /*  */
    unsigned short PFDS12          : 1; /*  */
    unsigned short PFDS13          : 1; /*  */
    unsigned short PFDS14          : 1; /*  */
    unsigned short PFDS15          : 1; /*  */
  } PFDS_bit;

  struct
  {
    unsigned char PFDS_L;
    unsigned char PFDS_H;
  };
  struct
  {
    unsigned char P11DS;   /* Port 11 Drive Strenght */
  };
  struct
  {
    struct
    {
      unsigned char P11DS0          : 1; /*  */
      unsigned char P11DS1          : 1; /*  */
      unsigned char P11DS2          : 1; /*  */
      unsigned char P11DS3          : 1; /*  */
      unsigned char P11DS4          : 1; /*  */
      unsigned char P11DS5          : 1; /*  */
      unsigned char P11DS6          : 1; /*  */
      unsigned char P11DS7          : 1; /*  */
    } P11DS_bit;

  }; 
} @0x02A8;

enum {
  PFDS0           = 0x0001,
  PFDS1           = 0x0002,
  PFDS2           = 0x0004,
  PFDS3           = 0x0008,
  PFDS4           = 0x0010,
  PFDS5           = 0x0020,
  PFDS6           = 0x0040,
  PFDS7           = 0x0080,
  PFDS8           = 0x0100,
  PFDS9           = 0x0200,
  PFDS10          = 0x0400,
  PFDS11          = 0x0800,
  PFDS12          = 0x1000,
  PFDS13          = 0x2000,
  PFDS14          = 0x4000,
  PFDS15          = 0x8000
};

__no_init volatile union
{
  unsigned short PFSEL;   /* Port F Selection */

  struct
  {
    unsigned short PFSEL0          : 1; /*  */
    unsigned short PFSEL1          : 1; /*  */
    unsigned short PFSEL2          : 1; /*  */
    unsigned short PFSEL3          : 1; /*  */
    unsigned short PFSEL4          : 1; /*  */
    unsigned short PFSEL5          : 1; /*  */
    unsigned short PFSEL6          : 1; /*  */
    unsigned short PFSEL7          : 1; /*  */
    unsigned short PFSEL8          : 1; /*  */
    unsigned short PFSEL9          : 1; /*  */
    unsigned short PFSEL10         : 1; /*  */
    unsigned short PFSEL11         : 1; /*  */
    unsigned short PFSEL12         : 1; /*  */
    unsigned short PFSEL13         : 1; /*  */
    unsigned short PFSEL14         : 1; /*  */
    unsigned short PFSEL15         : 1; /*  */
  } PFSEL_bit;

  struct
  {
    unsigned char PFSEL_L;
    unsigned char PFSEL_H;
  };
  struct
  {
    unsigned char P11SEL;   /* Port 11 Selection */
  };
  struct
  {
    struct
    {
      unsigned char P11SEL0         : 1; /*  */
      unsigned char P11SEL1         : 1; /*  */
      unsigned char P11SEL2         : 1; /*  */
      unsigned char P11SEL3         : 1; /*  */
      unsigned char P11SEL4         : 1; /*  */
      unsigned char P11SEL5         : 1; /*  */
      unsigned char P11SEL6         : 1; /*  */
      unsigned char P11SEL7         : 1; /*  */
    } P11SEL_bit;

  }; 
} @0x02AA;

enum {
  PFSEL0          = 0x0001,
  PFSEL1          = 0x0002,
  PFSEL2          = 0x0004,
  PFSEL3          = 0x0008,
  PFSEL4          = 0x0010,
  PFSEL5          = 0x0020,
  PFSEL6          = 0x0040,
  PFSEL7          = 0x0080,
  PFSEL8          = 0x0100,
  PFSEL9          = 0x0200,
  PFSEL10         = 0x0400,
  PFSEL11         = 0x0800,
  PFSEL12         = 0x1000,
  PFSEL13         = 0x2000,
  PFSEL14         = 0x4000,
  PFSEL15         = 0x8000
};



#define __MSP430_HAS_PORT11_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORTF_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT11_R__ 0x02A0
#define __MSP430_BASEADDRESS_PORTF_R__ 0x02A0

/*-------------------------------------------------------------------------
 *   Port 11
 *-------------------------------------------------------------------------*/


enum {
  P11IN0          = 0x0001,
  P11IN1          = 0x0002,
  P11IN2          = 0x0004,
  P11IN3          = 0x0008,
  P11IN4          = 0x0010,
  P11IN5          = 0x0020,
  P11IN6          = 0x0040,
  P11IN7          = 0x0080
};

enum {
  P11OUT0         = 0x0001,
  P11OUT1         = 0x0002,
  P11OUT2         = 0x0004,
  P11OUT3         = 0x0008,
  P11OUT4         = 0x0010,
  P11OUT5         = 0x0020,
  P11OUT6         = 0x0040,
  P11OUT7         = 0x0080
};

enum {
  P11DIR0         = 0x0001,
  P11DIR1         = 0x0002,
  P11DIR2         = 0x0004,
  P11DIR3         = 0x0008,
  P11DIR4         = 0x0010,
  P11DIR5         = 0x0020,
  P11DIR6         = 0x0040,
  P11DIR7         = 0x0080
};

enum {
  P11REN0         = 0x0001,
  P11REN1         = 0x0002,
  P11REN2         = 0x0004,
  P11REN3         = 0x0008,
  P11REN4         = 0x0010,
  P11REN5         = 0x0020,
  P11REN6         = 0x0040,
  P11REN7         = 0x0080
};

enum {
  P11DS0          = 0x0001,
  P11DS1          = 0x0002,
  P11DS2          = 0x0004,
  P11DS3          = 0x0008,
  P11DS4          = 0x0010,
  P11DS5          = 0x0020,
  P11DS6          = 0x0040,
  P11DS7          = 0x0080
};

enum {
  P11SEL0         = 0x0001,
  P11SEL1         = 0x0002,
  P11SEL2         = 0x0004,
  P11SEL3         = 0x0008,
  P11SEL4         = 0x0010,
  P11SEL5         = 0x0020,
  P11SEL6         = 0x0040,
  P11SEL7         = 0x0080
};



/*-------------------------------------------------------------------------
 *   Port J
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PJIN;   /* Port J Input */

  struct
  {
    unsigned __READ short PJIN0           : 1; /*  */
    unsigned __READ short PJIN1           : 1; /*  */
    unsigned __READ short PJIN2           : 1; /*  */
    unsigned __READ short PJIN3           : 1; /*  */
  } PJIN_bit;

  struct
  {
    unsigned __READ char PJIN_L;
    unsigned __READ char PJIN_H;
  };
} @0x0320;

enum {
  PJIN0           = 0x0001,
  PJIN1           = 0x0002,
  PJIN2           = 0x0004,
  PJIN3           = 0x0008
};

__no_init volatile union
{
  unsigned short PJOUT;   /* Port J Output */

  struct
  {
    unsigned short PJOUT0          : 1; /*  */
    unsigned short PJOUT1          : 1; /*  */
    unsigned short PJOUT2          : 1; /*  */
    unsigned short PJOUT3          : 1; /*  */
  } PJOUT_bit;

  struct
  {
    unsigned char PJOUT_L;
    unsigned char PJOUT_H;
  };
} @0x0322;

enum {
  PJOUT0          = 0x0001,
  PJOUT1          = 0x0002,
  PJOUT2          = 0x0004,
  PJOUT3          = 0x0008
};

__no_init volatile union
{
  unsigned short PJDIR;   /* Port J Direction */

  struct
  {
    unsigned short PJDIR0          : 1; /*  */
    unsigned short PJDIR1          : 1; /*  */
    unsigned short PJDIR2          : 1; /*  */
    unsigned short PJDIR3          : 1; /*  */
  } PJDIR_bit;

  struct
  {
    unsigned char PJDIR_L;
    unsigned char PJDIR_H;
  };
} @0x0324;

enum {
  PJDIR0          = 0x0001,
  PJDIR1          = 0x0002,
  PJDIR2          = 0x0004,
  PJDIR3          = 0x0008
};

__no_init volatile union
{
  unsigned short PJREN;   /* Port J Resistor Enable */

  struct
  {
    unsigned short PJREN0          : 1; /*  */
    unsigned short PJREN1          : 1; /*  */
    unsigned short PJREN2          : 1; /*  */
    unsigned short PJREN3          : 1; /*  */
  } PJREN_bit;

  struct
  {
    unsigned char PJREN_L;
    unsigned char PJREN_H;
  };
} @0x0326;

enum {
  PJREN0          = 0x0001,
  PJREN1          = 0x0002,
  PJREN2          = 0x0004,
  PJREN3          = 0x0008
};

__no_init volatile union
{
  unsigned short PJDS;   /* Port J Drive Strenght */

  struct
  {
    unsigned short PJDS0           : 1; /*  */
    unsigned short PJDS1           : 1; /*  */
    unsigned short PJDS2           : 1; /*  */
    unsigned short PJDS3           : 1; /*  */
  } PJDS_bit;

  struct
  {
    unsigned char PJDS_L;
    unsigned char PJDS_H;
  };
} @0x0328;

enum {
  PJDS0           = 0x0001,
  PJDS1           = 0x0002,
  PJDS2           = 0x0004,
  PJDS3           = 0x0008
};



#define __MSP430_HAS_PORTJ_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTJ_R__ 0x0320

/*-------------------------------------------------------------------------
 *   PMM  Power Management System
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short PMMCTL0;   /* PMM Control 0 */

  struct
  {
    unsigned short PMMCOREV0       : 1; /* PMM Core Voltage Bit: 0 */
    unsigned short PMMCOREV1       : 1; /* PMM Core Voltage Bit: 1 */
    unsigned short PMMSWBOR        : 1; /* PMM Software BOR */
    unsigned short PMMSWPOR        : 1; /* PMM Software POR */
    unsigned short PMMREGOFF       : 1; /* PMM Turn Regulator off */
    unsigned short                : 2;
    unsigned short PMMHPMRE        : 1; /* PMM Global High Power Module Request Enable */
  } PMMCTL0_bit;

  struct
  {
    unsigned char PMMCTL0_L;
    unsigned char PMMCTL0_H;
  };
} @0x0120;

enum {
  PMMCOREV0       = 0x0001,
  PMMCOREV1       = 0x0002,
  PMMSWBOR        = 0x0004,
  PMMSWPOR        = 0x0008,
  PMMREGOFF       = 0x0010,
  PMMHPMRE        = 0x0080
};

__no_init volatile union
{
  unsigned short PMMCTL1;   /* PMM Control 1 */

  struct
  {
    unsigned short PMMREFMD        : 1; /* PMM Reference Mode */
    unsigned short                : 3;
    unsigned short PMMCMD0         : 1; /* PMM Voltage Regulator Current Mode Bit: 0 */
    unsigned short PMMCMD1         : 1; /* PMM Voltage Regulator Current Mode Bit: 1 */
  } PMMCTL1_bit;

  struct
  {
    unsigned char PMMCTL1_L;
    unsigned char PMMCTL1_H;
  };
} @0x0122;

enum {
  PMMREFMD        = 0x0001,
  PMMCMD0         = 0x0010,
  PMMCMD1         = 0x0020
};

__no_init volatile union
{
  unsigned short SVSMHCTL;   /* SVS and SVM high side control register */

  struct
  {
    unsigned short SVSMHRRL0       : 1; /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
    unsigned short SVSMHRRL1       : 1; /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
    unsigned short SVSMHRRL2       : 1; /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
    unsigned short SVSMHDLYST      : 1; /* SVS and SVM high side delay status */
    unsigned short SVSHMD          : 1; /* SVS high side mode */
    unsigned short                : 1;
    unsigned short SVSMHEVM        : 1; /* SVS and SVM high side event mask */
    unsigned short SVSMHACE        : 1; /* SVS and SVM high side auto control enable */
    unsigned short SVSHRVL0        : 1; /* SVS high side reset voltage level Bit: 0 */
    unsigned short SVSHRVL1        : 1; /* SVS high side reset voltage level Bit: 1 */
    unsigned short SVSHE           : 1; /* SVS high side enable */
    unsigned short SVSHFP          : 1; /* SVS high side full performace mode */
    unsigned short SVMHOVPE        : 1; /* SVM high side over-voltage enable */
    unsigned short                : 1;
    unsigned short SVMHE           : 1; /* SVM high side enable */
    unsigned short SVMHFP          : 1; /* SVM high side full performace mode */
  } SVSMHCTL_bit;

  struct
  {
    unsigned char SVSMHCTL_L;
    unsigned char SVSMHCTL_H;
  };
} @0x0124;

enum {
  SVSMHRRL0       = 0x0001,
  SVSMHRRL1       = 0x0002,
  SVSMHRRL2       = 0x0004,
  SVSMHDLYST      = 0x0008,
  SVSHMD          = 0x0010,
  SVSMHEVM        = 0x0040,
  SVSMHACE        = 0x0080,
  SVSHRVL0        = 0x0100,
  SVSHRVL1        = 0x0200,
  SVSHE           = 0x0400,
  SVSHFP          = 0x0800,
  SVMHOVPE        = 0x1000,
  SVMHE           = 0x4000,
  SVMHFP          = 0x8000
};

__no_init volatile union
{
  unsigned short SVSMLCTL;   /* SVS and SVM low side control register */

  struct
  {
    unsigned short SVSMLRRL0       : 1; /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
    unsigned short SVSMLRRL1       : 1; /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
    unsigned short SVSMLRRL2       : 1; /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
    unsigned short SVSMLDLYST      : 1; /* SVS and SVM low side delay status */
    unsigned short SVSLMD          : 1; /* SVS low side mode */
    unsigned short                : 1;
    unsigned short SVSMLEVM        : 1; /* SVS and SVM low side event mask */
    unsigned short SVSMLACE        : 1; /* SVS and SVM low side auto control enable */
    unsigned short SVSLRVL0        : 1; /* SVS low side reset voltage level Bit: 0 */
    unsigned short SVSLRVL1        : 1; /* SVS low side reset voltage level Bit: 1 */
    unsigned short SVSLE           : 1; /* SVS low side enable */
    unsigned short SVSLFP          : 1; /* SVS low side full performace mode */
    unsigned short SVMLOVPE        : 1; /* SVM low side over-voltage enable */
    unsigned short                : 1;
    unsigned short SVMLE           : 1; /* SVM low side enable */
    unsigned short SVMLFP          : 1; /* SVM low side full performace mode */
  } SVSMLCTL_bit;

  struct
  {
    unsigned char SVSMLCTL_L;
    unsigned char SVSMLCTL_H;
  };
} @0x0126;

enum {
  SVSMLRRL0       = 0x0001,
  SVSMLRRL1       = 0x0002,
  SVSMLRRL2       = 0x0004,
  SVSMLDLYST      = 0x0008,
  SVSLMD          = 0x0010,
  SVSMLEVM        = 0x0040,
  SVSMLACE        = 0x0080,
  SVSLRVL0        = 0x0100,
  SVSLRVL1        = 0x0200,
  SVSLE           = 0x0400,
  SVSLFP          = 0x0800,
  SVMLOVPE        = 0x1000,
  SVMLE           = 0x4000,
  SVMLFP          = 0x8000
};

__no_init volatile union
{
  unsigned short SVSMIO;   /* SVSIN and SVSOUT control register */

  struct
  {
    unsigned short                : 3;
    unsigned short SVMLOE          : 1; /* SVM low side output enable */
    unsigned short SVMLVLROE       : 1; /* SVM low side voltage level reached output enable */
    unsigned short SVMOUTPOL       : 1; /* SVMOUT pin polarity */
    unsigned short                : 5;
    unsigned short SVMHOE          : 1; /* SVM high side output enable */
    unsigned short SVMHVLROE       : 1; /* SVM high side voltage level reached output enable */
  } SVSMIO_bit;

  struct
  {
    unsigned char SVSMIO_L;
    unsigned char SVSMIO_H;
  };
} @0x0128;

enum {
  SVMLOE          = 0x0008,
  SVMLVLROE       = 0x0010,
  SVMOUTPOL       = 0x0020,
  SVMHOE          = 0x0800,
  SVMHVLROE       = 0x1000
};

__no_init volatile union
{
  unsigned short PMMIFG;   /* PMM Interrupt Flag */

  struct
  {
    unsigned short SVSMLDLYIFG     : 1; /* SVS and SVM low side Delay expired interrupt flag */
    unsigned short SVMLIFG         : 1; /* SVM low side interrupt flag */
    unsigned short SVMLVLRIFG      : 1; /* SVM low side Voltage Level Reached interrupt flag */
    unsigned short                : 1;
    unsigned short SVSMHDLYIFG     : 1; /* SVS and SVM high side Delay expired interrupt flag */
    unsigned short SVMHIFG         : 1; /* SVM high side interrupt flag */
    unsigned short SVMHVLRIFG      : 1; /* SVM high side Voltage Level Reached interrupt flag */
    unsigned short                : 1;
    unsigned short PMMBORIFG       : 1; /* PMM Software BOR interrupt flag */
    unsigned short PMMRSTIFG       : 1; /* PMM RESET pin interrupt flag */
    unsigned short PMMPORIFG       : 1; /* PMM Software POR interrupt flag */
    unsigned short                : 1;
    unsigned short SVSHIFG         : 1; /* SVS low side interrupt flag */
    unsigned short SVSLIFG         : 1; /* SVS high side interrupt flag */
    unsigned short                : 1;
    unsigned short PMMLPM5IFG      : 1; /* LPM5 indication Flag */
  } PMMIFG_bit;

  struct
  {
    unsigned char PMMIFG_L;
    unsigned char PMMIFG_H;
  };
} @0x012C;

enum {
  SVSMLDLYIFG     = 0x0001,
  SVMLIFG         = 0x0002,
  SVMLVLRIFG      = 0x0004,
  SVSMHDLYIFG     = 0x0010,
  SVMHIFG         = 0x0020,
  SVMHVLRIFG      = 0x0040,
  PMMBORIFG       = 0x0100,
  PMMRSTIFG       = 0x0200,
  PMMPORIFG       = 0x0400,
  SVSHIFG         = 0x1000,
  SVSLIFG         = 0x2000,
  PMMLPM5IFG      = 0x8000
};

__no_init volatile union
{
  unsigned short PMMRIE;   /* PMM and RESET Interrupt Enable */

  struct
  {
    unsigned short SVSMLDLYIE      : 1; /* SVS and SVM low side Delay expired interrupt enable */
    unsigned short SVMLIE          : 1; /* SVM low side interrupt enable */
    unsigned short SVMLVLRIE       : 1; /* SVM low side Voltage Level Reached interrupt enable */
    unsigned short                : 1;
    unsigned short SVSMHDLYIE      : 1; /* SVS and SVM high side Delay expired interrupt enable */
    unsigned short SVMHIE          : 1; /* SVM high side interrupt enable */
    unsigned short SVMHVLRIE       : 1; /* SVM high side Voltage Level Reached interrupt enable */
    unsigned short                : 1;
    unsigned short SVSLPE          : 1; /* SVS low side POR enable */
    unsigned short SVMLVLRPE       : 1; /* SVM low side Voltage Level reached POR enable */
    unsigned short                : 2;
    unsigned short SVSHPE          : 1; /* SVS high side POR enable */
    unsigned short SVMHVLRPE       : 1; /* SVM high side Voltage Level reached POR enable */
  } PMMRIE_bit;

  struct
  {
    unsigned char PMMRIE_L;
    unsigned char PMMRIE_H;
  };
} @0x012E;

enum {
  SVSMLDLYIE      = 0x0001,
  SVMLIE          = 0x0002,
  SVMLVLRIE       = 0x0004,
  SVSMHDLYIE      = 0x0010,
  SVMHIE          = 0x0020,
  SVMHVLRIE       = 0x0040,
  SVSLPE          = 0x0100,
  SVMLVLRPE       = 0x0200,
  SVSHPE          = 0x1000,
  SVMHVLRPE       = 0x2000
};

__no_init volatile union
{
  unsigned short PM5CTL0;   /* PMM Power Mode 5 Control Register 0 */

  struct
  {
    unsigned short LOCKLPM5        : 1; /* Lock I/O pin configuration upon entry/exit to/from LPM5 */
  } PM5CTL0_bit;

  struct
  {
    unsigned char PM5CTL0_L;
    unsigned char PM5CTL0_H;
  };
} @0x0130;

enum {
  LOCKLPM5        = 0x0001
};



#define __MSP430_HAS_PMM__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM__ 0x0120

#define PMMPW               (0xA500u)  /* PMM Register Write Password */
#define PMMPW_H             (0xA5)    /* PMM Register Write Password for high word access */
/* PMMCTL0 Control Bits */
#define PMMCOREV0_L         (0x0001u)  /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1_L         (0x0002u)  /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR_L          (0x0004u)  /* PMM Software BOR */
#define PMMSWPOR_L          (0x0008u)  /* PMM Software POR */
#define PMMREGOFF_L         (0x0010u)  /* PMM Turn Regulator off */
#define PMMHPMRE_L          (0x0080u)  /* PMM Global High Power Module Request Enable */

#define PMMCOREV_0          (0x0000u)  /* PMM Core Voltage 0 (1.35V) */
#define PMMCOREV_1          (0x0001u)  /* PMM Core Voltage 1 (1.55V) */
#define PMMCOREV_2          (0x0002u)  /* PMM Core Voltage 2 (1.75V) */
#define PMMCOREV_3          (0x0003u)  /* PMM Core Voltage 3 (1.85V) */
/* PMMCTL1 Control Bits */
#define PMMREFMD_L          (0x0001u)  /* PMM Reference Mode */
#define PMMCMD0_L           (0x0010u)  /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1_L           (0x0020u)  /* PMM Voltage Regulator Current Mode Bit: 1 */
/* SVSMHCTL Control Bits */
#define SVSMHRRL0_L         (0x0001u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1_L         (0x0002u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2_L         (0x0004u)  /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST_L        (0x0008u)  /* SVS and SVM high side delay status */
#define SVSHMD_L            (0x0010u)  /* SVS high side mode */
#define SVSMHEVM_L          (0x0040u)  /* SVS and SVM high side event mask */
#define SVSMHACE_L          (0x0080u)  /* SVS and SVM high side auto control enable */
/* SVSMHCTL Control Bits */
#define SVSHRVL0_H          (0x0001u)  /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1_H          (0x0002u)  /* SVS high side reset voltage level Bit: 1 */
#define SVSHE_H             (0x0004u)  /* SVS high side enable */
#define SVSHFP_H            (0x0008u)  /* SVS high side full performace mode */
#define SVMHOVPE_H          (0x0010u)  /* SVM high side over-voltage enable */
#define SVMHE_H             (0x0040u)  /* SVM high side enable */
#define SVMHFP_H            (0x0080u)  /* SVM high side full performace mode */

#define SVSMHRRL_0          (0x0000u)  /* SVS and SVM high side Reset Release Voltage Level 0 */
#define SVSMHRRL_1          (0x0001u)  /* SVS and SVM high side Reset Release Voltage Level 1 */
#define SVSMHRRL_2          (0x0002u)  /* SVS and SVM high side Reset Release Voltage Level 2 */
#define SVSMHRRL_3          (0x0003u)  /* SVS and SVM high side Reset Release Voltage Level 3 */
#define SVSMHRRL_4          (0x0004u)  /* SVS and SVM high side Reset Release Voltage Level 4 */
#define SVSMHRRL_5          (0x0005u)  /* SVS and SVM high side Reset Release Voltage Level 5 */
#define SVSMHRRL_6          (0x0006u)  /* SVS and SVM high side Reset Release Voltage Level 6 */
#define SVSMHRRL_7          (0x0007u)  /* SVS and SVM high side Reset Release Voltage Level 7 */

#define SVSHRVL_0           (0x0000u)  /* SVS high side Reset Release Voltage Level 0 */
#define SVSHRVL_1           (0x0100u)  /* SVS high side Reset Release Voltage Level 1 */
#define SVSHRVL_2           (0x0200u)  /* SVS high side Reset Release Voltage Level 2 */
#define SVSHRVL_3           (0x0300u)  /* SVS high side Reset Release Voltage Level 3 */
/* SVSMLCTL Control Bits */
#define SVSMLRRL0_L         (0x0001u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1_L         (0x0002u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2_L         (0x0004u)  /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST_L        (0x0008u)  /* SVS and SVM low side delay status */
#define SVSLMD_L            (0x0010u)  /* SVS low side mode */
#define SVSMLEVM_L          (0x0040u)  /* SVS and SVM low side event mask */
#define SVSMLACE_L          (0x0080u)  /* SVS and SVM low side auto control enable */
/* SVSMLCTL Control Bits */
#define SVSLRVL0_H          (0x0001u)  /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1_H          (0x0002u)  /* SVS low side reset voltage level Bit: 1 */
#define SVSLE_H             (0x0004u)  /* SVS low side enable */
#define SVSLFP_H            (0x0008u)  /* SVS low side full performace mode */
#define SVMLOVPE_H          (0x0010u)  /* SVM low side over-voltage enable */
#define SVMLE_H             (0x0040u)  /* SVM low side enable */
#define SVMLFP_H            (0x0080u)  /* SVM low side full performace mode */

#define SVSMLRRL_0          (0x0000u)  /* SVS and SVM low side Reset Release Voltage Level 0 */
#define SVSMLRRL_1          (0x0001u)  /* SVS and SVM low side Reset Release Voltage Level 1 */
#define SVSMLRRL_2          (0x0002u)  /* SVS and SVM low side Reset Release Voltage Level 2 */
#define SVSMLRRL_3          (0x0003u)  /* SVS and SVM low side Reset Release Voltage Level 3 */
#define SVSMLRRL_4          (0x0004u)  /* SVS and SVM low side Reset Release Voltage Level 4 */
#define SVSMLRRL_5          (0x0005u)  /* SVS and SVM low side Reset Release Voltage Level 5 */
#define SVSMLRRL_6          (0x0006u)  /* SVS and SVM low side Reset Release Voltage Level 6 */
#define SVSMLRRL_7          (0x0007u)  /* SVS and SVM low side Reset Release Voltage Level 7 */

#define SVSLRVL_0           (0x0000u)  /* SVS low side Reset Release Voltage Level 0 */
#define SVSLRVL_1           (0x0100u)  /* SVS low side Reset Release Voltage Level 1 */
#define SVSLRVL_2           (0x0200u)  /* SVS low side Reset Release Voltage Level 2 */
#define SVSLRVL_3           (0x0300u)  /* SVS low side Reset Release Voltage Level 3 */
/* SVSMIO Control Bits */
#define SVMLOE_L            (0x0008u)  /* SVM low side output enable */
#define SVMLVLROE_L         (0x0010u)  /* SVM low side voltage level reached output enable */
#define SVMOUTPOL_L         (0x0020u)  /* SVMOUT pin polarity */
/* SVSMIO Control Bits */
#define SVMHOE_H            (0x0008u)  /* SVM high side output enable */
#define SVMHVLROE_H         (0x0010u)  /* SVM high side voltage level reached output enable */
/* PMMIFG Control Bits */
#define SVSMLDLYIFG_L       (0x0001u)  /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG_L           (0x0002u)  /* SVM low side interrupt flag */
#define SVMLVLRIFG_L        (0x0004u)  /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG_L       (0x0010u)  /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG_L           (0x0020u)  /* SVM high side interrupt flag */
#define SVMHVLRIFG_L        (0x0040u)  /* SVM high side Voltage Level Reached interrupt flag */
/* PMMIFG Control Bits */
#define PMMBORIFG_H         (0x0001u)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H         (0x0002u)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H         (0x0004u)  /* PMM Software POR interrupt flag */
#define SVSHIFG_H           (0x0010u)  /* SVS low side interrupt flag */
#define SVSLIFG_H           (0x0020u)  /* SVS high side interrupt flag */
#define PMMLPM5IFG_H        (0x0080u)  /* LPM5 indication Flag */

#define PMMRSTLPM5IFG       PMMLPM5IFG /* LPM5 indication Flag */
/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE_L        (0x0001u)  /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE_L            (0x0002u)  /* SVM low side interrupt enable */
#define SVMLVLRIE_L         (0x0004u)  /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE_L        (0x0010u)  /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE_L            (0x0020u)  /* SVM high side interrupt enable */
#define SVMHVLRIE_L         (0x0040u)  /* SVM high side Voltage Level Reached interrupt enable */
/* PMMIE and RESET Control Bits */
#define SVSLPE_H            (0x0001u)  /* SVS low side POR enable */
#define SVMLVLRPE_H         (0x0002u)  /* SVM low side Voltage Level reached POR enable */
#define SVSHPE_H            (0x0010u)  /* SVS high side POR enable */
#define SVMHVLRPE_H         (0x0020u)  /* SVM high side Voltage Level reached POR enable */
/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5_L          (0x0001u)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */
/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKIO              LOCKLPM5  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/*-------------------------------------------------------------------------
 *   RC  RAM Control Module
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short RCCTL0;   /* Ram Controller Control Register */

  struct
  {
    unsigned short RCRS0OFF        : 1; /* RAM Controller RAM Sector 0 Off */
    unsigned short RCRS1OFF        : 1; /* RAM Controller RAM Sector 1 Off */
    unsigned short RCRS2OFF        : 1; /* RAM Controller RAM Sector 2 Off */
    unsigned short RCRS3OFF        : 1; /* RAM Controller RAM Sector 3 Off */
  } RCCTL0_bit;

  struct
  {
    unsigned char RCCTL0_L;
    unsigned char RCCTL0_H;
  };
} @0x0158;

enum {
  RCRS0OFF        = 0x0001,
  RCRS1OFF        = 0x0002,
  RCRS2OFF        = 0x0004,
  RCRS3OFF        = 0x0008
};



#define __MSP430_HAS_RC__             /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RC__ 0x0158
/* RCCTL0 Control Bits */
#define RCRS0OFF_L          (0x0001u)  /* RAM Controller RAM Sector 0 Off */
#define RCRS1OFF_L          (0x0002u)  /* RAM Controller RAM Sector 1 Off */
#define RCRS2OFF_L          (0x0004u)  /* RAM Controller RAM Sector 2 Off */
#define RCRS3OFF_L          (0x0008u)  /* RAM Controller RAM Sector 3 Off */

#define RCKEY               (0x5A00u)

/*-------------------------------------------------------------------------
 *   Shared Reference
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short REFCTL0;   /* REF Shared Reference control register 0 */

  struct
  {
    unsigned short REFON           : 1; /* REF Reference On */
    unsigned short REFOUT          : 1; /* REF Reference output Buffer On */
    unsigned short                : 1;
    unsigned short REFTCOFF        : 1; /* REF Temp.Sensor off */
    unsigned short REFVSEL0        : 1; /* REF Reference Voltage Level Select Bit:0 */
    unsigned short REFVSEL1        : 1; /* REF Reference Voltage Level Select Bit:1 */
    unsigned short                : 1;
    unsigned short REFMSTR         : 1; /* REF Master Control */
    unsigned short REFGENACT       : 1; /* REF Reference generator active */
    unsigned short REFBGACT        : 1; /* REF Reference bandgap active */
    unsigned short REFGENBUSY      : 1; /* REF Reference generator busy */
    unsigned short BGMODE          : 1; /* REF Bandgap mode */
  } REFCTL0_bit;

  struct
  {
    unsigned char REFCTL0_L;
    unsigned char REFCTL0_H;
  };
} @0x01B0;

enum {
  REFON           = 0x0001,
  REFOUT          = 0x0002,
  REFTCOFF        = 0x0008,
  REFVSEL0        = 0x0010,
  REFVSEL1        = 0x0020,
  REFMSTR         = 0x0080,
  REFGENACT       = 0x0100,
  REFBGACT        = 0x0200,
  REFGENBUSY      = 0x0400,
  BGMODE          = 0x0800
};



#define __MSP430_HAS_REF__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_REF__ 0x01B0
/* REFCTL0 Control Bits */
#define REFON_L             (0x0001u)  /* REF Reference On */
#define REFOUT_L            (0x0002u)  /* REF Reference output Buffer On */
#define REFTCOFF_L          (0x0008u)  /* REF Temp.Sensor off */
#define REFVSEL0_L          (0x0010u)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1_L          (0x0020u)  /* REF Reference Voltage Level Select Bit:1 */
#define REFMSTR_L           (0x0080u)  /* REF Master Control */
#define REFGENACT_H         (0x0001u)  /* REF Reference generator active */
#define REFBGACT_H          (0x0002u)  /* REF Reference bandgap active */
#define REFGENBUSY_H        (0x0004u)  /* REF Reference generator busy */
#define BGMODE_H            (0x0008u)  /* REF Bandgap mode */

#define REFVSEL_0           (0x0000u)  /* REF Reference Voltage Level Select 1.5V */
#define REFVSEL_1           (0x0010u)  /* REF Reference Voltage Level Select 2.0V */
#define REFVSEL_2           (0x0020u)  /* REF Reference Voltage Level Select 2.5V */
#define REFVSEL_3           (0x0030u)  /* REF Reference Voltage Level Select 2.5V */

/*-------------------------------------------------------------------------
 *   RTC  Real Time Clock
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short RTCCTL01;   /* Real Timer Control 0/1 */

  struct
  {
    unsigned short RTCRDYIFG       : 1; /* RTC Ready Interrupt Flag */
    unsigned short RTCAIFG         : 1; /* RTC Alarm Interrupt Flag */
    unsigned short RTCTEVIFG       : 1; /* RTC Time Event Interrupt Flag */
    unsigned short                : 1;
    unsigned short RTCRDYIE        : 1; /* RTC Ready Interrupt Enable Flag */
    unsigned short RTCAIE          : 1; /* RTC Alarm Interrupt Enable Flag */
    unsigned short RTCTEVIE        : 1; /* RTC Time Event Interrupt Enable Flag */
    unsigned short                : 1;
    unsigned short RTCTEV0         : 1; /* RTC Time Event 0 */
    unsigned short RTCTEV1         : 1; /* RTC Time Event 1 */
    unsigned short RTCSSEL0        : 1; /* RTC Source Select 0 */
    unsigned short RTCSSEL1        : 1; /* RTC Source Select 1 */
    unsigned short RTCRDY          : 1; /* RTC Ready */
    unsigned short RTCMODE         : 1; /* RTC Mode 0:Counter / 1: Calendar */
    unsigned short RTCHOLD         : 1; /* RTC Hold */
    unsigned short RTCBCD          : 1; /* RTC BCD  0:Binary / 1:BCD */
  } RTCCTL01_bit;

  struct
  {
    unsigned char RTCCTL01_L;
    unsigned char RTCCTL01_H;
  };
} @0x04A0;

enum {
  RTCRDYIFG       = 0x0001,
  RTCAIFG         = 0x0002,
  RTCTEVIFG       = 0x0004,
  RTCRDYIE        = 0x0010,
  RTCAIE          = 0x0020,
  RTCTEVIE        = 0x0040,
  RTCTEV0         = 0x0100,
  RTCTEV1         = 0x0200,
  RTCSSEL0        = 0x0400,
  RTCSSEL1        = 0x0800,
  RTCRDY          = 0x1000,
  RTCMODE         = 0x2000,
  RTCHOLD         = 0x4000,
  RTCBCD          = 0x8000
};

__no_init volatile union
{
  unsigned short RTCCTL23;   /* Real Timer Control 2/3 */

  struct
  {
    unsigned short RTCCAL0         : 1; /* RTC Calibration Bit 0 */
    unsigned short RTCCAL1         : 1; /* RTC Calibration Bit 1 */
    unsigned short RTCCAL2         : 1; /* RTC Calibration Bit 2 */
    unsigned short RTCCAL3         : 1; /* RTC Calibration Bit 3 */
    unsigned short RTCCAL4         : 1; /* RTC Calibration Bit 4 */
    unsigned short RTCCAL5         : 1; /* RTC Calibration Bit 5 */
    unsigned short                : 1;
    unsigned short RTCCALS         : 1; /* RTC Calibration Sign */
    unsigned short RTCCALF0        : 1; /* RTC Calibration Frequency Bit 0 */
    unsigned short RTCCALF1        : 1; /* RTC Calibration Frequency Bit 1 */
  } RTCCTL23_bit;

  struct
  {
    unsigned char RTCCTL23_L;
    unsigned char RTCCTL23_H;
  };
} @0x04A2;

enum {
  RTCCAL0         = 0x0001,
  RTCCAL1         = 0x0002,
  RTCCAL2         = 0x0004,
  RTCCAL3         = 0x0008,
  RTCCAL4         = 0x0010,
  RTCCAL5         = 0x0020,
  RTCCALS         = 0x0080,
  RTCCALF0        = 0x0100,
  RTCCALF1        = 0x0200
};

__no_init volatile union
{
  unsigned short RTCPS0CTL;   /* Real Timer Prescale Timer 0 Control */

  struct
  {
    unsigned short RT0PSIFG        : 1; /* RTC Prescale Timer 0 Interrupt Flag */
    unsigned short RT0PSIE         : 1; /* RTC Prescale Timer 0 Interrupt Enable Flag */
    unsigned short RT0IP0          : 1; /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
    unsigned short RT0IP1          : 1; /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
    unsigned short RT0IP2          : 1; /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
    unsigned short                : 3;
    unsigned short RT0PSHOLD       : 1; /* RTC Prescale Timer 0 Hold */
    unsigned short                : 2;
    unsigned short RT0PSDIV0       : 1; /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
    unsigned short RT0PSDIV1       : 1; /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
    unsigned short RT0PSDIV2       : 1; /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
    unsigned short RT0SSEL         : 1; /* RTC Prescale Timer 0 Source Select 0:ACLK / 1:SMCLK */
  } RTCPS0CTL_bit;

  struct
  {
    unsigned char RTCPS0CTL_L;
    unsigned char RTCPS0CTL_H;
  };
} @0x04A8;

enum {
  RT0PSIFG        = 0x0001,
  RT0PSIE         = 0x0002,
  RT0IP0          = 0x0004,
  RT0IP1          = 0x0008,
  RT0IP2          = 0x0010,
  RT0PSHOLD       = 0x0100,
  RT0PSDIV0       = 0x0800,
  RT0PSDIV1       = 0x1000,
  RT0PSDIV2       = 0x2000,
  RT0SSEL         = 0x4000
};

__no_init volatile union
{
  unsigned short RTCPS1CTL;   /* Real Timer Prescale Timer 1 Control */

  struct
  {
    unsigned short RT1PSIFG        : 1; /* RTC Prescale Timer 1 Interrupt Flag */
    unsigned short RT1PSIE         : 1; /* RTC Prescale Timer 1 Interrupt Enable Flag */
    unsigned short RT1IP0          : 1; /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
    unsigned short RT1IP1          : 1; /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
    unsigned short RT1IP2          : 1; /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
    unsigned short                : 3;
    unsigned short RT1PSHOLD       : 1; /* RTC Prescale Timer 1 Hold */
    unsigned short                : 2;
    unsigned short RT1PSDIV0       : 1; /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
    unsigned short RT1PSDIV1       : 1; /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
    unsigned short RT1PSDIV2       : 1; /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
    unsigned short RT1SSEL0        : 1; /* RTC Prescale Timer 1 Source Select Bit 0 */
    unsigned short RT1SSEL1        : 1; /* RTC Prescale Timer 1 Source Select Bit 1 */
  } RTCPS1CTL_bit;

  struct
  {
    unsigned char RTCPS1CTL_L;
    unsigned char RTCPS1CTL_H;
  };
} @0x04AA;

enum {
  RT1PSIFG        = 0x0001,
  RT1PSIE         = 0x0002,
  RT1IP0          = 0x0004,
  RT1IP1          = 0x0008,
  RT1IP2          = 0x0010,
  RT1PSHOLD       = 0x0100,
  RT1PSDIV0       = 0x0800,
  RT1PSDIV1       = 0x1000,
  RT1PSDIV2       = 0x2000,
  RT1SSEL0        = 0x4000,
  RT1SSEL1        = 0x8000
};

__no_init volatile union
{
  unsigned short RTCPS;   /* Real Timer Prescale Timer Control */
  struct
  {
    unsigned char RTCPS_L;
    unsigned char RTCPS_H;
  };
} @0x04AC;


  /* Real Time Clock Interrupt Vector */
__no_init volatile unsigned short RTCIV @ 0x04AE;


__no_init volatile union
{
  unsigned short RTCTIM0;   /* Real Time Clock Time 0 */
  struct
  {
    unsigned char RTCTIM0_L;
    unsigned char RTCTIM0_H;
  };
} @0x04B0;

__no_init volatile union
{
  unsigned short RTCTIM1;   /* Real Time Clock Time 1 */
  struct
  {
    unsigned char RTCTIM1_L;
    unsigned char RTCTIM1_H;
  };
} @0x04B2;

__no_init volatile union
{
  unsigned short RTCDATE;   /* Real Time Clock Date */
  struct
  {
    unsigned char RTCDATE_L;
    unsigned char RTCDATE_H;
  };
} @0x04B4;

__no_init volatile union
{
  unsigned short RTCYEAR;   /* Real Time Clock Year */
  struct
  {
    unsigned char RTCYEAR_L;
    unsigned char RTCYEAR_H;
  };
} @0x04B6;

__no_init volatile union
{
  unsigned short RTCAMINHR;   /* Real Time Clock Alarm Min/Hour */
  struct
  {
    unsigned char RTCAMINHR_L;
    unsigned char RTCAMINHR_H;
  };
} @0x04B8;

__no_init volatile union
{
  unsigned short RTCADOWDAY;   /* Real Time Clock Alarm day of week/day */
  struct
  {
    unsigned char RTCADOWDAY_L;
    unsigned char RTCADOWDAY_H;
  };
} @0x04BA;

#define __MSP430_HAS_RTC__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC__ 0x04A0

#define RTCCTL0             RTCCTL01_L  /* Real Time Clock Control 0 */
#define RTCCTL1             RTCCTL01_H  /* Real Time Clock Control 1 */
#define RTCCTL2             RTCCTL23_L  /* Real Time Clock Control 2 */
#define RTCCTL3             RTCCTL23_H  /* Real Time Clock Control 3 */
#define RTCNT12             RTCTIM0
#define RTCNT34             RTCTIM1
#define RTCNT1              RTCTIM0_L
#define RTCNT2              RTCTIM0_H
#define RTCNT3              RTCTIM1_L
#define RTCNT4              RTCTIM1_H
#define RTCSEC              RTCTIM0_L
#define RTCMIN              RTCTIM0_H
#define RTCHOUR             RTCTIM1_L
#define RTCDOW              RTCTIM1_H
#define RTCDAY              RTCDATE_L
#define RTCMON              RTCDATE_H
#define RTCYEARL            RTCYEAR_L
#define RTCYEARH            RTCYEAR_H
#define RT0PS               RTCPS_L
#define RT1PS               RTCPS_H
#define RTCAMIN             RTCAMINHR_L  /* Real Time Clock Alarm Min */
#define RTCAHOUR            RTCAMINHR_H  /* Real Time Clock Alarm Hour */
#define RTCADOW             RTCADOWDAY_L /* Real Time Clock Alarm day of week */
#define RTCADAY             RTCADOWDAY_H /* Real Time Clock Alarm day */
#define RTCTEVIE_L          (0x0040u)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE_L            (0x0020u)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE_L          (0x0010u)     /* RTC Ready Interrupt Enable Flag */
#define RTCTEVIFG_L         (0x0004u)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG_L           (0x0002u)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG_L         (0x0001u)     /* RTC Ready Interrupt Flag */
/* RTCCTL01 Control Bits */
#define RTCBCD_H            (0x0080u)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD_H           (0x0040u)     /* RTC Hold */
#define RTCMODE_H           (0x0020u)     /* RTC Mode 0:Counter / 1: Calendar */
#define RTCRDY_H            (0x0010u)     /* RTC Ready */
#define RTCSSEL1_H          (0x0008u)     /* RTC Source Select 1 */
#define RTCSSEL0_H          (0x0004u)     /* RTC Source Select 0 */
#define RTCTEV1_H           (0x0002u)     /* RTC Time Event 1 */
#define RTCTEV0_H           (0x0001u)     /* RTC Time Event 0 */

#define RTCSSEL_0           (0x0000u)     /* RTC Source Select ACLK */
#define RTCSSEL_1           (0x0400u)     /* RTC Source Select SMCLK */
#define RTCSSEL_2           (0x0800u)     /* RTC Source Select RT1PS */
#define RTCSSEL_3           (0x0C00u)     /* RTC Source Select RT1PS */
#define RTCSSEL__ACLK       (0x0000u)     /* RTC Source Select ACLK */
#define RTCSSEL__SMCLK      (0x0400u)     /* RTC Source Select SMCLK */
#define RTCSSEL__RT1PS      (0x0800u)     /* RTC Source Select RT1PS */
#define RTCTEV_0            (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200u)     /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300u)     /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__0000        (0x0200u)     /* RTC Time Event: 2 (00:00 changed) */
#define RTCTEV__1200        (0x0300u)     /* RTC Time Event: 3 (12:00 changed) */
/* RTCCTL23 Control Bits */
#define RTCCALS_L           (0x0080u)     /* RTC Calibration Sign */
#define RTCCAL5_L           (0x0020u)     /* RTC Calibration Bit 5 */
#define RTCCAL4_L           (0x0010u)     /* RTC Calibration Bit 4 */
#define RTCCAL3_L           (0x0008u)     /* RTC Calibration Bit 3 */
#define RTCCAL2_L           (0x0004u)     /* RTC Calibration Bit 2 */
#define RTCCAL1_L           (0x0002u)     /* RTC Calibration Bit 1 */
#define RTCCAL0_L           (0x0001u)     /* RTC Calibration Bit 0 */
/* RTCCTL23 Control Bits */
#define RTCCALF1_H          (0x0002u)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0_H          (0x0001u)     /* RTC Calibration Frequency Bit 0 */

#define RTCCALF_0           (0x0000u)     /* RTC Calibration Frequency: No Output */
#define RTCCALF_1           (0x0100u)     /* RTC Calibration Frequency: 512 Hz */
#define RTCCALF_2           (0x0200u)     /* RTC Calibration Frequency: 256 Hz */
#define RTCCALF_3           (0x0300u)     /* RTC Calibration Frequency: 1 Hz */
#define RT0IP2_L            (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1_L            (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0_L            (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE_L           (0x0002u)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG_L          (0x0001u)     /* RTC Prescale Timer 0 Interrupt Flag */
#define RT0SSEL_H           (0x0040u)     /* RTC Prescale Timer 0 Source Select 0:ACLK / 1:SMCLK */
#define RT0PSDIV2_H         (0x0020u)     /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
#define RT0PSDIV1_H         (0x0010u)     /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
#define RT0PSDIV0_H         (0x0008u)     /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
#define RT0PSHOLD_H         (0x0001u)     /* RTC Prescale Timer 0 Hold */

#define RT0IP_0             (0x0000u)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000Cu)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014u)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018u)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001Cu)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0PSDIV_0          (0x0000u)     /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1          (0x0800u)     /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2          (0x1000u)     /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3          (0x1800u)     /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4          (0x2000u)     /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5          (0x2800u)     /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6          (0x3000u)     /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7          (0x3800u)     /* RTC Prescale Timer 0 Clock Divide /256 */
#define RT1IP2_L            (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1_L            (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0_L            (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE_L           (0x0002u)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG_L          (0x0001u)     /* RTC Prescale Timer 1 Interrupt Flag */
/* RTCPS1CTL Control Bits */
#define RT1SSEL1_H          (0x0080u)     /* RTC Prescale Timer 1 Source Select Bit 1 */
#define RT1SSEL0_H          (0x0040u)     /* RTC Prescale Timer 1 Source Select Bit 0 */
#define RT1PSDIV2_H         (0x0020u)     /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
#define RT1PSDIV1_H         (0x0010u)     /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
#define RT1PSDIV0_H         (0x0008u)     /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
#define RT1PSHOLD_H         (0x0001u)     /* RTC Prescale Timer 1 Hold */

#define RT1IP_0             (0x0000u)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000Cu)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014u)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018u)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001Cu)     /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1PSDIV_0          (0x0000u)     /* RTC Prescale Timer 1 Clock Divide /2 */
#define RT1PSDIV_1          (0x0800u)     /* RTC Prescale Timer 1 Clock Divide /4 */
#define RT1PSDIV_2          (0x1000u)     /* RTC Prescale Timer 1 Clock Divide /8 */
#define RT1PSDIV_3          (0x1800u)     /* RTC Prescale Timer 1 Clock Divide /16 */
#define RT1PSDIV_4          (0x2000u)     /* RTC Prescale Timer 1 Clock Divide /32 */
#define RT1PSDIV_5          (0x2800u)     /* RTC Prescale Timer 1 Clock Divide /64 */
#define RT1PSDIV_6          (0x3000u)     /* RTC Prescale Timer 1 Clock Divide /128 */
#define RT1PSDIV_7          (0x3800u)     /* RTC Prescale Timer 1 Clock Divide /256 */

#define RT1SSEL_0           (0x0000u)     /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL_1           (0x4000u)     /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL_2           (0x8000u)     /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL_3           (0xC000u)     /* RTC Prescale Timer Source Select RT0PS */
/* RTC Definitions */
#define RTCIV_NONE          (0x0000u)     /* No Interrupt pending */
#define RTCIV_RTCRDYIFG     (0x0002u)     /* RTC ready: RTCRDYIFG */
#define RTCIV_RTCTEVIFG     (0x0004u)     /* RTC interval timer: RTCTEVIFG */
#define RTCIV_RTCAIFG       (0x0006u)     /* RTC user alarm: RTCAIFG */
#define RTCIV_RT0PSIFG      (0x0008u)     /* RTC prescaler 0: RT0PSIFG */
#define RTCIV_RT1PSIFG      (0x000Au)     /* RTC prescaler 1: RT1PSIFG */
/* Legacy Definitions */
#define RTC_NONE            (0x0000u)     /* No Interrupt pending */
#define RTC_RTCRDYIFG       (0x0002u)     /* RTC ready: RTCRDYIFG */
#define RTC_RTCTEVIFG       (0x0004u)     /* RTC interval timer: RTCTEVIFG */
#define RTC_RTCAIFG         (0x0006u)     /* RTC user alarm: RTCAIFG */
#define RTC_RT0PSIFG        (0x0008u)     /* RTC prescaler 0: RT0PSIFG */
#define RTC_RT1PSIFG        (0x000Au)     /* RTC prescaler 1: RT1PSIFG */

/*-------------------------------------------------------------------------
 *   SFR  Special Function Registers
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SFRIE1;   /* Interrupt Enable 1 */

  struct
  {
    unsigned short WDTIE           : 1; /* WDT Interrupt Enable */
    unsigned short OFIE            : 1; /* Osc Fault Enable */
    unsigned short                : 1;
    unsigned short VMAIE           : 1; /* Vacant Memory Interrupt Enable */
    unsigned short NMIIE           : 1; /* NMI Interrupt Enable */
    unsigned short ACCVIE          : 1; /* Flash Access Violation Interrupt Enable */
    unsigned short JMBINIE         : 1; /* JTAG Mail Box input Interrupt Enable */
    unsigned short JMBOUTIE        : 1; /* JTAG Mail Box output Interrupt Enable */
  } SFRIE1_bit;

  struct
  {
    unsigned char SFRIE1_L;
    unsigned char SFRIE1_H;
  };
} @0x0100;

enum {
  WDTIE           = 0x0001,
  OFIE            = 0x0002,
  VMAIE           = 0x0008,
  NMIIE           = 0x0010,
  ACCVIE          = 0x0020,
  JMBINIE         = 0x0040,
  JMBOUTIE        = 0x0080
};

__no_init volatile union
{
  unsigned short SFRIFG1;   /* Interrupt Flag 1 */

  struct
  {
    unsigned short WDTIFG          : 1; /* WDT Interrupt Flag */
    unsigned short OFIFG           : 1; /* Osc Fault Flag */
    unsigned short                : 1;
    unsigned short VMAIFG          : 1; /* Vacant Memory Interrupt Flag */
    unsigned short NMIIFG          : 1; /* NMI Interrupt Flag */
    unsigned short                : 1;
    unsigned short JMBINIFG        : 1; /* JTAG Mail Box input Interrupt Flag */
    unsigned short JMBOUTIFG       : 1; /* JTAG Mail Box output Interrupt Flag */
  } SFRIFG1_bit;

  struct
  {
    unsigned char SFRIFG1_L;
    unsigned char SFRIFG1_H;
  };
} @0x0102;

enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  VMAIFG          = 0x0008,
  NMIIFG          = 0x0010,
  JMBINIFG        = 0x0040,
  JMBOUTIFG       = 0x0080
};

__no_init volatile union
{
  unsigned short SFRRPCR;   /* RESET Pin Control Register */

  struct
  {
    unsigned short SYSNMI          : 1; /* NMI select */
    unsigned short SYSNMIIES       : 1; /* NMI edge select */
    unsigned short SYSRSTUP        : 1; /* RESET Pin pull down/up select */
    unsigned short SYSRSTRE        : 1; /* RESET Pin Resistor enable */
  } SFRRPCR_bit;

  struct
  {
    unsigned char SFRRPCR_L;
    unsigned char SFRRPCR_H;
  };
} @0x0104;

enum {
  SYSNMI          = 0x0001,
  SYSNMIIES       = 0x0002,
  SYSRSTUP        = 0x0004,
  SYSRSTRE        = 0x0008
};



#define __MSP430_HAS_SFR__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100

#define WDTIE_L             (0x0001u)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002u)  /* Osc Fault Enable */
#define VMAIE_L             (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010u)  /* NMI Interrupt Enable */
#define ACCVIE_L            (0x0020u)  /* Flash Access Violation Interrupt Enable */
#define JMBINIE_L           (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080u)  /* JTAG Mail Box output Interrupt Enable */

#define WDTIFG_L            (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG_L             (0x0002u)  /* Osc Fault Flag */
#define VMAIFG_L            (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG_L            (0x0010u)  /* NMI Interrupt Flag */
#define JMBINIFG_L          (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L         (0x0080u)  /* JTAG Mail Box output Interrupt Flag */

#define SYSNMI_L            (0x0001u)  /* NMI select */
#define SYSNMIIES_L         (0x0002u)  /* NMI edge select */
#define SYSRSTUP_L          (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE_L          (0x0008u)  /* RESET Pin Resistor enable */

/*-------------------------------------------------------------------------
 *   SYS  System Module
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SYSCTL;   /* System control */

  struct
  {
    unsigned short SYSRIVECT       : 1; /* SYS - RAM based interrupt vectors */
    unsigned short                : 1;
    unsigned short SYSPMMPE        : 1; /* SYS - PMM access protect */
    unsigned short                : 1;
    unsigned short SYSBSLIND       : 1; /* SYS - TCK/RST indication detected */
    unsigned short SYSJTAGPIN      : 1; /* SYS - Dedicated JTAG pins enabled */
  } SYSCTL_bit;

  struct
  {
    unsigned char SYSCTL_L;
    unsigned char SYSCTL_H;
  };
} @0x0180;

enum {
  SYSRIVECT       = 0x0001,
  SYSPMMPE        = 0x0004,
  SYSBSLIND       = 0x0010,
  SYSJTAGPIN      = 0x0020
};

__no_init volatile union
{
  unsigned short SYSBSLC;   /* Boot strap configuration area */

  struct
  {
    unsigned short SYSBSLSIZE0     : 1; /* SYS - BSL Protection Size 0 */
    unsigned short SYSBSLSIZE1     : 1; /* SYS - BSL Protection Size 1 */
    unsigned short SYSBSLR         : 1; /* SYS - RAM assigned to BSL */
    unsigned short                : 11;
    unsigned short SYSBSLOFF       : 1; /* SYS - BSL Memeory disabled */
    unsigned short SYSBSLPE        : 1; /* SYS - BSL Memory protection enabled */
  } SYSBSLC_bit;

  struct
  {
    unsigned char SYSBSLC_L;
    unsigned char SYSBSLC_H;
  };
} @0x0182;

enum {
  SYSBSLSIZE0     = 0x0001,
  SYSBSLSIZE1     = 0x0002,
  SYSBSLR         = 0x0004,
  SYSBSLOFF       = 0x4000,
  SYSBSLPE        = 0x8000
};

__no_init volatile union
{
  unsigned short SYSJMBC;   /* JTAG mailbox control */

  struct
  {
    unsigned short JMBIN0FG        : 1; /* SYS - Incoming JTAG Mailbox 0 Flag */
    unsigned short JMBIN1FG        : 1; /* SYS - Incoming JTAG Mailbox 1 Flag */
    unsigned short JMBOUT0FG       : 1; /* SYS - Outgoing JTAG Mailbox 0 Flag */
    unsigned short JMBOUT1FG       : 1; /* SYS - Outgoing JTAG Mailbox 1 Flag */
    unsigned short JMBMODE         : 1; /* SYS - JMB 16/32 Bit Mode */
    unsigned short                : 1;
    unsigned short JMBCLR0OFF      : 1; /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
    unsigned short JMBCLR1OFF      : 1; /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
  } SYSJMBC_bit;

  struct
  {
    unsigned char SYSJMBC_L;
    unsigned char SYSJMBC_H;
  };
} @0x0186;

enum {
  JMBIN0FG        = 0x0001,
  JMBIN1FG        = 0x0002,
  JMBOUT0FG       = 0x0004,
  JMBOUT1FG       = 0x0008,
  JMBMODE         = 0x0010,
  JMBCLR0OFF      = 0x0040,
  JMBCLR1OFF      = 0x0080
};

__no_init volatile union
{
  unsigned short SYSJMBI0;   /* JTAG mailbox input 0 */
  struct
  {
    unsigned char SYSJMBI0_L;
    unsigned char SYSJMBI0_H;
  };
} @0x0188;

__no_init volatile union
{
  unsigned short SYSJMBI1;   /* JTAG mailbox input 1 */
  struct
  {
    unsigned char SYSJMBI1_L;
    unsigned char SYSJMBI1_H;
  };
} @0x018A;

__no_init volatile union
{
  unsigned short SYSJMBO0;   /* JTAG mailbox output 0 */
  struct
  {
    unsigned char SYSJMBO0_L;
    unsigned char SYSJMBO0_H;
  };
} @0x018C;

__no_init volatile union
{
  unsigned short SYSJMBO1;   /* JTAG mailbox output 1 */
  struct
  {
    unsigned char SYSJMBO1_L;
    unsigned char SYSJMBO1_H;
  };
} @0x018E;

__no_init volatile union
{
  unsigned short SYSBERRIV;   /* Bus Error vector generator */
  struct
  {
    unsigned char SYSBERRIV_L;
    unsigned char SYSBERRIV_H;
  };
} @0x0198;

__no_init volatile union
{
  unsigned short SYSUNIV;   /* User NMI vector generator */
  struct
  {
    unsigned char SYSUNIV_L;
    unsigned char SYSUNIV_H;
  };
} @0x019A;

__no_init volatile union
{
  unsigned short SYSSNIV;   /* System NMI vector generator */
  struct
  {
    unsigned char SYSSNIV_L;
    unsigned char SYSSNIV_H;
  };
} @0x019C;

__no_init volatile union
{
  unsigned short SYSRSTIV;   /* Reset vector generator */
  struct
  {
    unsigned char SYSRSTIV_L;
    unsigned char SYSRSTIV_H;
  };
} @0x019E;

#define __MSP430_HAS_SYS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0180
/* SYSCTL Control Bits */
#define SYSRIVECT_L         (0x0001u)  /* SYS - RAM based interrupt vectors */
#define SYSPMMPE_L          (0x0004u)  /* SYS - PMM access protect */
#define SYSBSLIND_L         (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L        (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L       (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L       (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L           (0x0004u)  /* SYS - RAM assigned to BSL */
#define SYSBSLOFF_H         (0x0040u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE_H          (0x0080u)  /* SYS - BSL Memory protection enabled */
/* SYSJMBC Control Bits */
#define JMBIN0FG_L          (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L          (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L         (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L         (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L           (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
#define JMBCLR0OFF_L        (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L        (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002u)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004u)    /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_ACCVIFG    (0x0006u)    /* SYSUNIV : Access Violation - ACCVIFG */
#define SYSUNIV_SYSBERRIV  (0x0008u)    /* SYSUNIV : Bus Error - SYSBERRIV */
/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSSNIV_SVMLIFG    (0x0002u)    /* SYSSNIV : SVMLIFG */
#define SYSSNIV_SVMHIFG    (0x0004u)    /* SYSSNIV : SVMHIFG */
#define SYSSNIV_DLYLIFG    (0x0006u)    /* SYSSNIV : DLYLIFG */
#define SYSSNIV_DLYHIFG    (0x0008u)    /* SYSSNIV : DLYHIFG */
#define SYSSNIV_VMAIFG     (0x000Au)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x000Cu)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x000Eu)    /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_VLRLIFG    (0x0010u)    /* SYSSNIV : VLRLIFG */
#define SYSSNIV_VLRHIFG    (0x0012u)    /* SYSSNIV : VLRHIFG */
/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000u)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002u)    /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI    (0x0004u)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0006u)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU    (0x0008u)    /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV     (0x000Au)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSL      (0x000Cu)    /* SYSRSTIV : SVSL */
#define SYSRSTIV_SVSH      (0x000Eu)    /* SYSRSTIV : SVSH */
#define SYSRSTIV_SVML_OVP  (0x0010u)    /* SYSRSTIV : SVML_OVP */
#define SYSRSTIV_SVMH_OVP  (0x0012u)    /* SYSRSTIV : SVMH_OVP */
#define SYSRSTIV_DOPOR     (0x0014u)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x0016u)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0018u)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_KEYV      (0x001Au)    /* SYSRSTIV : Flash Key violation */
#define SYSRSTIV_PLLUL     (0x001Cu)    /* SYSRSTIV : PLL unlock */
#define SYSRSTIV_PERF      (0x001Eu)    /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMKEY    (0x0020u)    /* SYSRSTIV : PMMKEY violation */

#define SYSRSTIV_PSSKEY    (0x0020u)    /* SYSRSTIV : Legacy: PMMKEY violation */

/*-------------------------------------------------------------------------
 *   Timer0_A5
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short TA0CTL;   /* Timer0_A5 Control */

  struct
  {
    unsigned short TAIFG           : 1; /* Timer A counter interrupt flag */
    unsigned short TAIE            : 1; /* Timer A counter interrupt enable */
    unsigned short TACLR           : 1; /* Timer A counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TASSEL0         : 1; /* Timer A clock source select 0 */
    unsigned short TASSEL1         : 1; /* Timer A clock source select 1 */
  }TA0CTL_bit;
} @0x0340;


enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200
};


__no_init volatile union
{
  unsigned short TA0CCTL0;   /* Timer0_A5 Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA0CCTL0_bit;
} @0x0342;


enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000
};


__no_init volatile union
{
  unsigned short TA0CCTL1;   /* Timer0_A5 Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA0CCTL1_bit;
} @0x0344;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TA0CCTL2;   /* Timer0_A5 Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA0CCTL2_bit;
} @0x0346;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TA0CCTL3;   /* Timer0_A5 Capture/Compare Control 3 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA0CCTL3_bit;
} @0x0348;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TA0CCTL4;   /* Timer0_A5 Capture/Compare Control 4 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA0CCTL4_bit;
} @0x034A;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer0_A5 */
__no_init volatile unsigned short TA0R @ 0x0350;



  /* Timer0_A5 Capture/Compare 0 */
__no_init volatile unsigned short TA0CCR0 @ 0x0352;



  /* Timer0_A5 Capture/Compare 1 */
__no_init volatile unsigned short TA0CCR1 @ 0x0354;



  /* Timer0_A5 Capture/Compare 2 */
__no_init volatile unsigned short TA0CCR2 @ 0x0356;



  /* Timer0_A5 Capture/Compare 3 */
__no_init volatile unsigned short TA0CCR3 @ 0x0358;



  /* Timer0_A5 Capture/Compare 4 */
__no_init volatile unsigned short TA0CCR4 @ 0x035A;



  /* Timer0_A5 Interrupt Vector Word */
__no_init volatile unsigned short TA0IV @ 0x036E;



__no_init volatile union
{
  unsigned short TA0EX0;   /* Timer0_A5 Expansion Register 0 */

  struct
  {
    unsigned short TAIDEX0         : 1; /* Timer A Input divider expansion Bit: 0 */
    unsigned short TAIDEX1         : 1; /* Timer A Input divider expansion Bit: 1 */
    unsigned short TAIDEX2         : 1; /* Timer A Input divider expansion Bit: 2 */
  }TA0EX0_bit;
} @ 0x0360;


enum {
  TAIDEX0         = 0x0001,
  TAIDEX1         = 0x0002,
  TAIDEX2         = 0x0004
};



#define __MSP430_HAS_T0A5__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A5__ 0x0340

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continuous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */
#define MC__STOP            (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC__UP              (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINUOUS      (2*0x10u)  /* Timer A mode control: 2 - Continuous up */
#define MC__CONTINOUS       (2*0x10u)  /* Legacy define */
#define MC__UPDOWN          (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID__1               (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID__2               (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID__4               (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID__8               (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK       (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK        (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK       (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK       (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */

#define TAIDEX_0            (0*0x0001u) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (1*0x0001u) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (2*0x0001u) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (3*0x0001u) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (4*0x0001u) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (5*0x0001u) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (6*0x0001u) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (7*0x0001u) /* Timer A Input divider expansion : /8 */
/* T0A5IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TA0CCR1       (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2       (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_TA0CCR3       (0x0006u)    /* TA0CCR3_CCIFG */
#define TA0IV_TA0CCR4       (0x0008u)    /* TA0CCR4_CCIFG */
#define TA0IV_5             (0x000Au)    /* Reserved */
#define TA0IV_6             (0x000Cu)    /* Reserved */
#define TA0IV_TA0IFG        (0x000Eu)    /* TA0IFG */

/*-------------------------------------------------------------------------
 *   Timer1_A3
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short TA1CTL;   /* Timer1_A3 Control */

  struct
  {
    unsigned short TAIFG           : 1; /* Timer A counter interrupt flag */
    unsigned short TAIE            : 1; /* Timer A counter interrupt enable */
    unsigned short TACLR           : 1; /* Timer A counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TASSEL0         : 1; /* Timer A clock source select 0 */
    unsigned short TASSEL1         : 1; /* Timer A clock source select 1 */
  }TA1CTL_bit;
} @0x0380;


/*
enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200,
};

*/

__no_init volatile union
{
  unsigned short TA1CCTL0;   /* Timer1_A3 Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA1CCTL0_bit;
} @0x0382;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TA1CCTL1;   /* Timer1_A3 Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA1CCTL1_bit;
} @0x0384;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TA1CCTL2;   /* Timer1_A3 Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read) */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TA1CCTL2_bit;
} @0x0386;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer1_A3 */
__no_init volatile unsigned short TA1R @ 0x0390;



  /* Timer1_A3 Capture/Compare 0 */
__no_init volatile unsigned short TA1CCR0 @ 0x0392;



  /* Timer1_A3 Capture/Compare 1 */
__no_init volatile unsigned short TA1CCR1 @ 0x0394;



  /* Timer1_A3 Capture/Compare 2 */
__no_init volatile unsigned short TA1CCR2 @ 0x0396;



  /* Timer1_A3 Interrupt Vector Word */
__no_init volatile unsigned short TA1IV @ 0x03AE;



__no_init volatile union
{
  unsigned short TA1EX0;   /* Timer1_A3 Expansion Register 0 */

  struct
  {
    unsigned short TAIDEX0         : 1; /* Timer A Input divider expansion Bit: 0 */
    unsigned short TAIDEX1         : 1; /* Timer A Input divider expansion Bit: 1 */
    unsigned short TAIDEX2         : 1; /* Timer A Input divider expansion Bit: 2 */
  }TA1EX0_bit;
} @ 0x03A0;


/*
enum {
  TAIDEX0         = 0x0001,
  TAIDEX1         = 0x0002,
  TAIDEX2         = 0x0004
};
*/



#define __MSP430_HAS_T1A3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0380
/* TA1IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TA1CCR1       (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2       (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_3             (0x0006u)    /* Reserved */
#define TA1IV_4             (0x0008u)    /* Reserved */
#define TA1IV_5             (0x000Au)    /* Reserved */
#define TA1IV_6             (0x000Cu)    /* Reserved */
#define TA1IV_TA1IFG        (0x000Eu)    /* TA1IFG */

/*-------------------------------------------------------------------------
 *   Timer0_B7
 *-------------------------------------------------------------------------*/



__no_init volatile union
{
  unsigned short TB0CTL;   /* Timer0_B7 Control */

  struct
  {
    unsigned short TBIFG           : 1; /* Timer0_B7 interrupt flag */
    unsigned short TBIE            : 1; /* Timer0_B7 interrupt enable */
    unsigned short TBCLR           : 1; /* Timer0_B7 counter clear */
    unsigned short                : 1;
    unsigned short MC0             : 1; /* Timer A mode control 0 */
    unsigned short MC1             : 1; /* Timer A mode control 1 */
    unsigned short ID0             : 1; /* Timer A clock input divider 0 */
    unsigned short ID1             : 1; /* Timer A clock input divider 1 */
    unsigned short TBSSEL0         : 1; /* Clock source 0 */
    unsigned short TBSSEL1         : 1; /* Clock source 1 */
    unsigned short                : 1;
    unsigned short CNTL0           : 1; /* Counter lenght 0 */
    unsigned short CNTL1           : 1; /* Counter lenght 1 */
    unsigned short TBCLGRP0        : 1; /* Timer0_B7 Compare latch load group 0 */
    unsigned short TBCLGRP1        : 1; /* Timer0_B7 Compare latch load group 1 */
  }TB0CTL_bit;
} @0x03C0;


enum {
  TBIFG           = 0x0001,
  TBIE            = 0x0002,
  TBCLR           = 0x0004,
/*  MC0             = 0x0010, */
/*  MC1             = 0x0020, */
/*  ID0             = 0x0040, */
/*  ID1             = 0x0080, */
  TBSSEL0         = 0x0100,
  TBSSEL1         = 0x0200,
  CNTL0           = 0x0800,
  CNTL1           = 0x1000,
  TBCLGRP0        = 0x2000,
  TBCLGRP1        = 0x4000
};


__no_init volatile union
{
  unsigned short TB0CCTL0;   /* Timer0_B7 Capture/Compare Control 0 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL0_bit;
} @0x03C2;


enum {
/*  CCIFG           = 0x0001, */
/*  COV             = 0x0002, */
/*  OUT             = 0x0004, */
/*  CCI             = 0x0008, */
/*  CCIE            = 0x0010, */
/*  OUTMOD0         = 0x0020, */
/*  OUTMOD1         = 0x0040, */
/*  OUTMOD2         = 0x0080, */
/*  CAP             = 0x0100, */
  CLLD0           = 0x0200,
  CLLD1           = 0x0400
/*  SCS             = 0x0800, */
/*  CCIS0           = 0x1000, */
/*  CCIS1           = 0x2000, */
/*  CM0             = 0x4000, */
/*  CM1             = 0x8000, */
};


__no_init volatile union
{
  unsigned short TB0CCTL1;   /* Timer0_B7 Capture/Compare Control 1 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL1_bit;
} @0x03C4;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TB0CCTL2;   /* Timer0_B7 Capture/Compare Control 2 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL2_bit;
} @0x03C6;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TB0CCTL3;   /* Timer0_B7 Capture/Compare Control 3 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL3_bit;
} @0x03C8;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TB0CCTL4;   /* Timer0_B7 Capture/Compare Control 4 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL4_bit;
} @0x03CA;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TB0CCTL5;   /* Timer0_B7 Capture/Compare Control 5 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL5_bit;
} @0x03CC;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

__no_init volatile union
{
  unsigned short TB0CCTL6;   /* Timer0_B7 Capture/Compare Control 6 */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag */
    unsigned short COV             : 1; /* Capture/compare overflow flag */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0 */
    unsigned short CCI             : 1; /* Capture input signal (read) */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable */
    unsigned short OUTMOD0         : 1; /* Output mode 0 */
    unsigned short OUTMOD1         : 1; /* Output mode 1 */
    unsigned short OUTMOD2         : 1; /* Output mode 2 */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0 */
    unsigned short CLLD0           : 1; /* Compare latch load source 0 */
    unsigned short CLLD1           : 1; /* Compare latch load source 1 */
    unsigned short SCS             : 1; /* Capture sychronize */
    unsigned short CCIS0           : 1; /* Capture input select 0 */
    unsigned short CCIS1           : 1; /* Capture input select 1 */
    unsigned short CM0             : 1; /* Capture mode 0 */
    unsigned short CM1             : 1; /* Capture mode 1 */
  }TB0CCTL6_bit;
} @0x03CE;


/*
enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  CLLD0           = 0x0200,
  CLLD1           = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000,
};

*/

  /* Timer0_B7 */
__no_init volatile unsigned short TB0R @ 0x03D0;



  /* Timer0_B7 Capture/Compare 0 */
__no_init volatile unsigned short TB0CCR0 @ 0x03D2;



  /* Timer0_B7 Capture/Compare 1 */
__no_init volatile unsigned short TB0CCR1 @ 0x03D4;



  /* Timer0_B7 Capture/Compare 2 */
__no_init volatile unsigned short TB0CCR2 @ 0x03D6;



  /* Timer0_B7 Capture/Compare 3 */
__no_init volatile unsigned short TB0CCR3 @ 0x03D8;



  /* Timer0_B7 Capture/Compare 4 */
__no_init volatile unsigned short TB0CCR4 @ 0x03DA;



  /* Timer0_B7 Capture/Compare 5 */
__no_init volatile unsigned short TB0CCR5 @ 0x03DC;



  /* Timer0_B7 Capture/Compare 6 */
__no_init volatile unsigned short TB0CCR6 @ 0x03DE;



__no_init volatile union
{
  unsigned short TB0EX0;   /* Timer0_B7 Expansion Register 0 */

  struct
  {
    unsigned short TBIDEX0         : 1; /* Timer0_B7 Input divider expansion Bit: 0 */
    unsigned short TBIDEX1         : 1; /* Timer0_B7 Input divider expansion Bit: 1 */
    unsigned short TBIDEX2         : 1; /* Timer0_B7 Input divider expansion Bit: 2 */
  }TB0EX0_bit;
} @0x03E0;


enum {
  TBIDEX0         = 0x0001,
  TBIDEX1         = 0x0002,
  TBIDEX2         = 0x0004
};


  /* Timer0_B7 Interrupt Vector Word */
__no_init volatile unsigned short TB0IV @ 0x03EE;


#define __MSP430_HAS_T0B7__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0B7__ 0x03C0
/* Legacy Type Definitions for TimerB */
#define TBCTL                TB0CTL    /* Timer0_B7 Control */
#define TBCCTL0              TB0CCTL0  /* Timer0_B7 Capture/Compare Control 0 */
#define TBCCTL1              TB0CCTL1  /* Timer0_B7 Capture/Compare Control 1 */
#define TBCCTL2              TB0CCTL2  /* Timer0_B7 Capture/Compare Control 2 */
#define TBCCTL3              TB0CCTL3  /* Timer0_B7 Capture/Compare Control 3 */
#define TBCCTL4              TB0CCTL4  /* Timer0_B7 Capture/Compare Control 4 */
#define TBCCTL5              TB0CCTL5  /* Timer0_B7 Capture/Compare Control 5 */
#define TBCCTL6              TB0CCTL6  /* Timer0_B7 Capture/Compare Control 6 */
#define TBR                  TB0R      /* Timer0_B7 */
#define TBCCR0               TB0CCR0   /* Timer0_B7 Capture/Compare 0 */
#define TBCCR1               TB0CCR1   /* Timer0_B7 Capture/Compare 1 */
#define TBCCR2               TB0CCR2   /* Timer0_B7 Capture/Compare 2 */
#define TBCCR3               TB0CCR3   /* Timer0_B7 Capture/Compare 3 */
#define TBCCR4               TB0CCR4   /* Timer0_B7 Capture/Compare 4 */
#define TBCCR5               TB0CCR5   /* Timer0_B7 Capture/Compare 5 */
#define TBCCR6               TB0CCR6   /* Timer0_B7 Capture/Compare 6 */
#define TBEX0                TB0EX0    /* Timer0_B7 Expansion Register 0 */
#define TBIV                 TB0IV     /* Timer0_B7 Interrupt Vector Word */
#define TIMERB1_VECTOR       TIMER0_B1_VECTOR /* Timer0_B7 CC1-6, TB */
#define TIMERB0_VECTOR       TIMER0_B0_VECTOR /* Timer0_B7 CC0 */

#define SHR1                (0x4000u)  /* Timer0_B7 Compare latch load group 1 */
#define SHR0                (0x2000u)  /* Timer0_B7 Compare latch load group 0 */

#define TBSSEL_0            (0*0x0100u)  /* Clock Source: TBCLK */
#define TBSSEL_1            (1*0x0100u)  /* Clock Source: ACLK  */
#define TBSSEL_2            (2*0x0100u)  /* Clock Source: SMCLK */
#define TBSSEL_3            (3*0x0100u)  /* Clock Source: INCLK */
#define CNTL_0              (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL_1              (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL_2              (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL_3              (3*0x0800u)  /* Counter lenght:  8 bit */
#define SHR_0               (0*0x2000u)  /* Timer0_B7 Group: 0 - individually */
#define SHR_1               (1*0x2000u)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (2*0x2000u)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (3*0x2000u)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0*0x2000u)  /* Timer0_B7 Group: 0 - individually */
#define TBCLGRP_1           (1*0x2000u)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (2*0x2000u)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (3*0x2000u)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBSSEL__TACLK       (0*0x100u) /* Timer0_B7 clock source select: 0 - TACLK */
#define TBSSEL__ACLK        (1*0x100u) /* Timer0_B7 clock source select: 1 - ACLK  */
#define TBSSEL__SMCLK       (2*0x100u) /* Timer0_B7 clock source select: 2 - SMCLK */
#define TBSSEL__INCLK       (3*0x100u) /* Timer0_B7 clock source select: 3 - INCLK */
#define CNTL__16            (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL__12            (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL__10            (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL__8             (3*0x0800u)  /* Counter lenght:  8 bit */

#define SLSHR1              (0x0400u)  /* Compare latch load source 1 */
#define SLSHR0              (0x0200u)  /* Compare latch load source 0 */

#define SLSHR_0             (0*0x0200u) /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1             (1*0x0200u) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2             (2*0x0200u) /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3             (3*0x0200u) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0*0x0200u) /* Compare latch load sourec : 0 - immediate */
#define CLLD_1              (1*0x0200u) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2              (2*0x0200u) /* Compare latch load sourec : 2 - up/down */
#define CLLD_3              (3*0x0200u) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define TBIDEX_0            (0*0x0001u) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX_1            (1*0x0001u) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX_2            (2*0x0001u) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX_3            (3*0x0001u) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX_4            (4*0x0001u) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX_5            (5*0x0001u) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX_6            (6*0x0001u) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX_7            (7*0x0001u) /* Timer0_B7 Input divider expansion : /8 */
#define TBIDEX__1           (0*0x0001u) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX__2           (1*0x0001u) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX__3           (2*0x0001u) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX__4           (3*0x0001u) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX__5           (4*0x0001u) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX__6           (5*0x0001u) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX__7           (6*0x0001u) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX__8           (7*0x0001u) /* Timer0_B7 Input divider expansion : /8 */
/* TB0IV Definitions */
#define TB0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TB0IV_TB1CCR1       (0x0002u)    /* TBCCR1_CCIFG */
#define TB0IV_TB1CCR2       (0x0004u)    /* TBCCR2_CCIFG */
#define TB0IV_3             (0x0006u)    /* Reserved */
#define TB0IV_4             (0x0008u)    /* Reserved */
#define TB0IV_5             (0x000Au)    /* Reserved */
#define TB0IV_6             (0x000Cu)    /* Reserved */
#define TB0IV_TB0IFG        (0x000Eu)    /* TBIFG */

/*-------------------------------------------------------------------------
 *   UCS  Unified System Clock
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCSCTL0;   /* UCS Control Register 0 */

  struct
  {
    unsigned short                : 3;
    unsigned short MOD0            : 1; /* Modulation Bit Counter Bit : 0 */
    unsigned short MOD1            : 1; /* Modulation Bit Counter Bit : 1 */
    unsigned short MOD2            : 1; /* Modulation Bit Counter Bit : 2 */
    unsigned short MOD3            : 1; /* Modulation Bit Counter Bit : 3 */
    unsigned short MOD4            : 1; /* Modulation Bit Counter Bit : 4 */
    unsigned short DCO0            : 1; /* DCO TAP Bit : 0 */
    unsigned short DCO1            : 1; /* DCO TAP Bit : 1 */
    unsigned short DCO2            : 1; /* DCO TAP Bit : 2 */
    unsigned short DCO3            : 1; /* DCO TAP Bit : 3 */
    unsigned short DCO4            : 1; /* DCO TAP Bit : 4 */
  } UCSCTL0_bit;

  struct
  {
    unsigned char UCSCTL0_L;
    unsigned char UCSCTL0_H;
  };
} @0x0160;

enum {
  MOD0            = 0x0008,
  MOD1            = 0x0010,
  MOD2            = 0x0020,
  MOD3            = 0x0040,
  MOD4            = 0x0080,
  DCO0            = 0x0100,
  DCO1            = 0x0200,
  DCO2            = 0x0400,
  DCO3            = 0x0800,
  DCO4            = 0x1000
};

__no_init volatile union
{
  unsigned short UCSCTL1;   /* UCS Control Register 1 */

  struct
  {
    unsigned short DISMOD          : 1; /* Disable Modulation */
    unsigned short                : 3;
    unsigned short DCORSEL0        : 1; /* DCO Freq. Range Select Bit : 0 */
    unsigned short DCORSEL1        : 1; /* DCO Freq. Range Select Bit : 1 */
    unsigned short DCORSEL2        : 1; /* DCO Freq. Range Select Bit : 2 */
  } UCSCTL1_bit;

  struct
  {
    unsigned char UCSCTL1_L;
    unsigned char UCSCTL1_H;
  };
} @0x0162;

enum {
  DISMOD          = 0x0001,
  DCORSEL0        = 0x0010,
  DCORSEL1        = 0x0020,
  DCORSEL2        = 0x0040
};

__no_init volatile union
{
  unsigned short UCSCTL2;   /* UCS Control Register 2 */

  struct
  {
    unsigned short FLLN0           : 1; /* FLL Multipier Bit : 0 */
    unsigned short FLLN1           : 1; /* FLL Multipier Bit : 1 */
    unsigned short FLLN2           : 1; /* FLL Multipier Bit : 2 */
    unsigned short FLLN3           : 1; /* FLL Multipier Bit : 3 */
    unsigned short FLLN4           : 1; /* FLL Multipier Bit : 4 */
    unsigned short FLLN5           : 1; /* FLL Multipier Bit : 5 */
    unsigned short FLLN6           : 1; /* FLL Multipier Bit : 6 */
    unsigned short FLLN7           : 1; /* FLL Multipier Bit : 7 */
    unsigned short FLLN8           : 1; /* FLL Multipier Bit : 8 */
    unsigned short FLLN9           : 1; /* FLL Multipier Bit : 9 */
    unsigned short                : 2;
    unsigned short FLLD0           : 1; /* Loop Divider Bit : 0 */
    unsigned short FLLD1           : 1; /* Loop Divider Bit : 1 */
    unsigned short FLLD2           : 1; /* Loop Divider Bit : 1 */
  } UCSCTL2_bit;

  struct
  {
    unsigned char UCSCTL2_L;
    unsigned char UCSCTL2_H;
  };
} @0x0164;

enum {
  FLLN0           = 0x0001,
  FLLN1           = 0x0002,
  FLLN2           = 0x0004,
  FLLN3           = 0x0008,
  FLLN4           = 0x0010,
  FLLN5           = 0x0020,
  FLLN6           = 0x0040,
  FLLN7           = 0x0080,
  FLLN8           = 0x0100,
  FLLN9           = 0x0200,
  FLLD0           = 0x1000,
  FLLD1           = 0x2000,
  FLLD2           = 0x4000
};

__no_init volatile union
{
  unsigned short UCSCTL3;   /* UCS Control Register 3 */

  struct
  {
    unsigned short FLLREFDIV0      : 1; /* Reference Divider Bit : 0 */
    unsigned short FLLREFDIV1      : 1; /* Reference Divider Bit : 1 */
    unsigned short FLLREFDIV2      : 1; /* Reference Divider Bit : 2 */
    unsigned short                : 1;
    unsigned short SELREF0         : 1; /* FLL Reference Clock Select Bit : 0 */
    unsigned short SELREF1         : 1; /* FLL Reference Clock Select Bit : 1 */
    unsigned short SELREF2         : 1; /* FLL Reference Clock Select Bit : 2 */
  } UCSCTL3_bit;

  struct
  {
    unsigned char UCSCTL3_L;
    unsigned char UCSCTL3_H;
  };
} @0x0166;

enum {
  FLLREFDIV0      = 0x0001,
  FLLREFDIV1      = 0x0002,
  FLLREFDIV2      = 0x0004,
  SELREF0         = 0x0010,
  SELREF1         = 0x0020,
  SELREF2         = 0x0040
};

__no_init volatile union
{
  unsigned short UCSCTL4;   /* UCS Control Register 4 */

  struct
  {
    unsigned short SELM0           : 1; /* MCLK Source Select Bit: 0 */
    unsigned short SELM1           : 1; /* MCLK Source Select Bit: 1 */
    unsigned short SELM2           : 1; /* MCLK Source Select Bit: 2 */
    unsigned short                : 1;
    unsigned short SELS0           : 1; /* SMCLK Source Select Bit: 0 */
    unsigned short SELS1           : 1; /* SMCLK Source Select Bit: 1 */
    unsigned short SELS2           : 1; /* SMCLK Source Select Bit: 2 */
    unsigned short                : 1;
    unsigned short SELA0           : 1; /* ACLK Source Select Bit: 0 */
    unsigned short SELA1           : 1; /* ACLK Source Select Bit: 1 */
    unsigned short SELA2           : 1; /* ACLK Source Select Bit: 2 */
  } UCSCTL4_bit;

  struct
  {
    unsigned char UCSCTL4_L;
    unsigned char UCSCTL4_H;
  };
} @0x0168;

enum {
  SELM0           = 0x0001,
  SELM1           = 0x0002,
  SELM2           = 0x0004,
  SELS0           = 0x0010,
  SELS1           = 0x0020,
  SELS2           = 0x0040,
  SELA0           = 0x0100,
  SELA1           = 0x0200,
  SELA2           = 0x0400
};

__no_init volatile union
{
  unsigned short UCSCTL5;   /* UCS Control Register 5 */

  struct
  {
    unsigned short DIVM0           : 1; /* MCLK Divider Bit: 0 */
    unsigned short DIVM1           : 1; /* MCLK Divider Bit: 1 */
    unsigned short DIVM2           : 1; /* MCLK Divider Bit: 2 */
    unsigned short                : 1;
    unsigned short DIVS0           : 1; /* SMCLK Divider Bit: 0 */
    unsigned short DIVS1           : 1; /* SMCLK Divider Bit: 1 */
    unsigned short DIVS2           : 1; /* SMCLK Divider Bit: 2 */
    unsigned short                : 1;
    unsigned short DIVA0           : 1; /* ACLK Divider Bit: 0 */
    unsigned short DIVA1           : 1; /* ACLK Divider Bit: 1 */
    unsigned short DIVA2           : 1; /* ACLK Divider Bit: 2 */
    unsigned short                : 1;
    unsigned short DIVPA0          : 1; /* ACLK from Pin Divider Bit: 0 */
    unsigned short DIVPA1          : 1; /* ACLK from Pin Divider Bit: 1 */
    unsigned short DIVPA2          : 1; /* ACLK from Pin Divider Bit: 2 */
  } UCSCTL5_bit;

  struct
  {
    unsigned char UCSCTL5_L;
    unsigned char UCSCTL5_H;
  };
} @0x016A;

enum {
  DIVM0           = 0x0001,
  DIVM1           = 0x0002,
  DIVM2           = 0x0004,
  DIVS0           = 0x0010,
  DIVS1           = 0x0020,
  DIVS2           = 0x0040,
  DIVA0           = 0x0100,
  DIVA1           = 0x0200,
  DIVA2           = 0x0400,
  DIVPA0          = 0x1000,
  DIVPA1          = 0x2000,
  DIVPA2          = 0x4000
};

__no_init volatile union
{
  unsigned short UCSCTL6;   /* UCS Control Register 6 */

  struct
  {
    unsigned short XT1OFF          : 1; /* High Frequency Oscillator 1 (XT1) disable */
    unsigned short SMCLKOFF        : 1; /* SMCLK Off */
    unsigned short XCAP0           : 1; /* XIN/XOUT Cap Bit: 0 */
    unsigned short XCAP1           : 1; /* XIN/XOUT Cap Bit: 1 */
    unsigned short XT1BYPASS       : 1; /* XT1 bypass mode : 0: internal 1:sourced from external pin */
    unsigned short XTS             : 1; /* 1: Selects high-freq. oscillator */
    unsigned short XT1DRIVE0       : 1; /* XT1 Drive Level mode Bit 0 */
    unsigned short XT1DRIVE1       : 1; /* XT1 Drive Level mode Bit 1 */
    unsigned short XT2OFF          : 1; /* High Frequency Oscillator 2 (XT2) disable */
    unsigned short                : 3;
    unsigned short XT2BYPASS       : 1; /* XT2 bypass mode : 0: internal 1:sourced from external pin */
    unsigned short                : 1;
    unsigned short XT2DRIVE0       : 1; /* XT2 Drive Level mode Bit 0 */
    unsigned short XT2DRIVE1       : 1; /* XT2 Drive Level mode Bit 1 */
  } UCSCTL6_bit;

  struct
  {
    unsigned char UCSCTL6_L;
    unsigned char UCSCTL6_H;
  };
} @0x016C;

enum {
  XT1OFF          = 0x0001,
  SMCLKOFF        = 0x0002,
  XCAP0           = 0x0004,
  XCAP1           = 0x0008,
  XT1BYPASS       = 0x0010,
  XTS             = 0x0020,
  XT1DRIVE0       = 0x0040,
  XT1DRIVE1       = 0x0080,
  XT2OFF          = 0x0100,
  XT2BYPASS       = 0x1000,
  XT2DRIVE0       = 0x4000,
  XT2DRIVE1       = 0x8000
};

__no_init volatile union
{
  unsigned short UCSCTL7;   /* UCS Control Register 7 */

  struct
  {
    unsigned short DCOFFG          : 1; /* DCO Fault Flag */
    unsigned short XT1LFOFFG       : 1; /* XT1 Low Frequency Oscillator Fault Flag */
    unsigned short XT1HFOFFG       : 1; /* XT1 High Frequency Oscillator 1 Fault Flag */
    unsigned short XT2OFFG         : 1; /* High Frequency Oscillator 2 Fault Flag */
  } UCSCTL7_bit;

  struct
  {
    unsigned char UCSCTL7_L;
    unsigned char UCSCTL7_H;
  };
} @0x016E;

enum {
  DCOFFG          = 0x0001,
  XT1LFOFFG       = 0x0002,
  XT1HFOFFG       = 0x0004,
  XT2OFFG         = 0x0008
};

__no_init volatile union
{
  unsigned short UCSCTL8;   /* UCS Control Register 8 */

  struct
  {
    unsigned short ACLKREQEN       : 1; /* ACLK Clock Request Enable */
    unsigned short MCLKREQEN       : 1; /* MCLK Clock Request Enable */
    unsigned short SMCLKREQEN      : 1; /* SMCLK Clock Request Enable */
    unsigned short MODOSCREQEN     : 1; /* MODOSC Clock Request Enable */
  } UCSCTL8_bit;

  struct
  {
    unsigned char UCSCTL8_L;
    unsigned char UCSCTL8_H;
  };
} @0x0170;

enum {
  ACLKREQEN       = 0x0001,
  MCLKREQEN       = 0x0002,
  SMCLKREQEN      = 0x0004,
  MODOSCREQEN     = 0x0008
};



#define __MSP430_HAS_UCS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_UCS__ 0x0160
#define MOD0_L              (0x0008u)    /* Modulation Bit Counter Bit : 0 */
#define MOD1_L              (0x0010u)    /* Modulation Bit Counter Bit : 1 */
#define MOD2_L              (0x0020u)    /* Modulation Bit Counter Bit : 2 */
#define MOD3_L              (0x0040u)    /* Modulation Bit Counter Bit : 3 */
#define MOD4_L              (0x0080u)    /* Modulation Bit Counter Bit : 4 */
#define DCO0_H              (0x0001u)    /* DCO TAP Bit : 0 */
#define DCO1_H              (0x0002u)    /* DCO TAP Bit : 1 */
#define DCO2_H              (0x0004u)    /* DCO TAP Bit : 2 */
#define DCO3_H              (0x0008u)    /* DCO TAP Bit : 3 */
#define DCO4_H              (0x0010u)    /* DCO TAP Bit : 4 */
/* UCSCTL1 Control Bits */
#define DISMOD_L            (0x0001u)    /* Disable Modulation */
#define DCORSEL0_L          (0x0010u)    /* DCO Freq. Range Select Bit : 0 */
#define DCORSEL1_L          (0x0020u)    /* DCO Freq. Range Select Bit : 1 */
#define DCORSEL2_L          (0x0040u)    /* DCO Freq. Range Select Bit : 2 */

#define DCORSEL_0           (0x0000u)    /* DCO RSEL 0 */
#define DCORSEL_1           (0x0010u)    /* DCO RSEL 1 */
#define DCORSEL_2           (0x0020u)    /* DCO RSEL 2 */
#define DCORSEL_3           (0x0030u)    /* DCO RSEL 3 */
#define DCORSEL_4           (0x0040u)    /* DCO RSEL 4 */
#define DCORSEL_5           (0x0050u)    /* DCO RSEL 5 */
#define DCORSEL_6           (0x0060u)    /* DCO RSEL 6 */
#define DCORSEL_7           (0x0070u)    /* DCO RSEL 7 */
/* UCSCTL2 Control Bits */
#define FLLN0_L             (0x0001u)    /* FLL Multipier Bit : 0 */
#define FLLN1_L             (0x0002u)    /* FLL Multipier Bit : 1 */
#define FLLN2_L             (0x0004u)    /* FLL Multipier Bit : 2 */
#define FLLN3_L             (0x0008u)    /* FLL Multipier Bit : 3 */
#define FLLN4_L             (0x0010u)    /* FLL Multipier Bit : 4 */
#define FLLN5_L             (0x0020u)    /* FLL Multipier Bit : 5 */
#define FLLN6_L             (0x0040u)    /* FLL Multipier Bit : 6 */
#define FLLN7_L             (0x0080u)    /* FLL Multipier Bit : 7 */
/* UCSCTL2 Control Bits */
#define FLLN8_H             (0x0001u)    /* FLL Multipier Bit : 8 */
#define FLLN9_H             (0x0002u)    /* FLL Multipier Bit : 9 */
#define FLLD0_H             (0x0010u)    /* Loop Divider Bit : 0 */
#define FLLD1_H             (0x0020u)    /* Loop Divider Bit : 1 */
#define FLLD2_H             (0x0040u)    /* Loop Divider Bit : 1 */

#define FLLD_0             (0x0000u)    /* Multiply Selected Loop Freq. 1 */
#define FLLD_1             (0x1000u)    /* Multiply Selected Loop Freq. 2 */
#define FLLD_2             (0x2000u)    /* Multiply Selected Loop Freq. 4 */
#define FLLD_3             (0x3000u)    /* Multiply Selected Loop Freq. 8 */
#define FLLD_4             (0x4000u)    /* Multiply Selected Loop Freq. 16 */
#define FLLD_5             (0x5000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_6             (0x6000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_7             (0x7000u)    /* Multiply Selected Loop Freq. 32 */
#define FLLD__1            (0x0000u)    /* Multiply Selected Loop Freq. By 1 */
#define FLLD__2            (0x1000u)    /* Multiply Selected Loop Freq. By 2 */
#define FLLD__4            (0x2000u)    /* Multiply Selected Loop Freq. By 4 */
#define FLLD__8            (0x3000u)    /* Multiply Selected Loop Freq. By 8 */
#define FLLD__16           (0x4000u)    /* Multiply Selected Loop Freq. By 16 */
#define FLLD__32           (0x5000u)    /* Multiply Selected Loop Freq. By 32 */
/* UCSCTL3 Control Bits */
#define FLLREFDIV0_L        (0x0001u)    /* Reference Divider Bit : 0 */
#define FLLREFDIV1_L        (0x0002u)    /* Reference Divider Bit : 1 */
#define FLLREFDIV2_L        (0x0004u)    /* Reference Divider Bit : 2 */
#define SELREF0_L           (0x0010u)    /* FLL Reference Clock Select Bit : 0 */
#define SELREF1_L           (0x0020u)    /* FLL Reference Clock Select Bit : 1 */
#define SELREF2_L           (0x0040u)    /* FLL Reference Clock Select Bit : 2 */

#define FLLREFDIV_0         (0x0000u)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV_1         (0x0001u)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV_2         (0x0002u)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV_3         (0x0003u)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV_4         (0x0004u)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV_5         (0x0005u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_6         (0x0006u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_7         (0x0007u)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV__1        (0x0000u)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV__2        (0x0001u)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV__4        (0x0002u)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV__8        (0x0003u)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV__12       (0x0004u)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV__16       (0x0005u)    /* Reference Divider: f(LFCLK)/16 */
#define SELREF_0            (0x0000u)    /* FLL Reference Clock Select 0 */
#define SELREF_1            (0x0010u)    /* FLL Reference Clock Select 1 */
#define SELREF_2            (0x0020u)    /* FLL Reference Clock Select 2 */
#define SELREF_3            (0x0030u)    /* FLL Reference Clock Select 3 */
#define SELREF_4            (0x0040u)    /* FLL Reference Clock Select 4 */
#define SELREF_5            (0x0050u)    /* FLL Reference Clock Select 5 */
#define SELREF_6            (0x0060u)    /* FLL Reference Clock Select 6 */
#define SELREF_7            (0x0070u)    /* FLL Reference Clock Select 7 */
#define SELREF__XT1CLK      (0x0000u)    /* Multiply Selected Loop Freq. By XT1CLK */
#define SELREF__REFOCLK     (0x0020u)    /* Multiply Selected Loop Freq. By REFOCLK */
#define SELREF__XT2CLK      (0x0050u)    /* Multiply Selected Loop Freq. By XT2CLK */
/* UCSCTL4 Control Bits */
#define SELM0_L             (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELM2_L             (0x0004u)   /* MCLK Source Select Bit: 2 */
#define SELS0_L             (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELS2_L             (0x0040u)   /* SMCLK Source Select Bit: 2 */
#define SELA0_H             (0x0001u)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002u)   /* ACLK Source Select Bit: 1 */
#define SELA2_H             (0x0004u)   /* ACLK Source Select Bit: 2 */

#define SELM_0              (0x0000u)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001u)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002u)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003u)   /* MCLK Source Select 3 */
#define SELM_4              (0x0004u)   /* MCLK Source Select 4 */
#define SELM_5              (0x0005u)   /* MCLK Source Select 5 */
#define SELM_6              (0x0006u)   /* MCLK Source Select 6 */
#define SELM_7              (0x0007u)   /* MCLK Source Select 7 */
#define SELM__XT1CLK        (0x0000u)   /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK        (0x0001u)   /* MCLK Source Select VLOCLK */
#define SELM__REFOCLK       (0x0002u)   /* MCLK Source Select REFOCLK */
#define SELM__DCOCLK        (0x0003u)   /* MCLK Source Select DCOCLK */
#define SELM__DCOCLKDIV     (0x0004u)   /* MCLK Source Select DCOCLKDIV */
#define SELM__XT2CLK        (0x0005u)   /* MCLK Source Select XT2CLK */

#define SELS_0              (0x0000u)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010u)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020u)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030u)   /* SMCLK Source Select 3 */
#define SELS_4              (0x0040u)   /* SMCLK Source Select 4 */
#define SELS_5              (0x0050u)   /* SMCLK Source Select 5 */
#define SELS_6              (0x0060u)   /* SMCLK Source Select 6 */
#define SELS_7              (0x0070u)   /* SMCLK Source Select 7 */
#define SELS__XT1CLK        (0x0000u)   /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK        (0x0010u)   /* SMCLK Source Select VLOCLK */
#define SELS__REFOCLK       (0x0020u)   /* SMCLK Source Select REFOCLK */
#define SELS__DCOCLK        (0x0030u)   /* SMCLK Source Select DCOCLK */
#define SELS__DCOCLKDIV     (0x0040u)   /* SMCLK Source Select DCOCLKDIV */
#define SELS__XT2CLK        (0x0050u)   /* SMCLK Source Select XT2CLK */

#define SELA_0              (0x0000u)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100u)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200u)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300u)   /* ACLK Source Select 3 */
#define SELA_4              (0x0400u)   /* ACLK Source Select 4 */
#define SELA_5              (0x0500u)   /* ACLK Source Select 5 */
#define SELA_6              (0x0600u)   /* ACLK Source Select 6 */
#define SELA_7              (0x0700u)   /* ACLK Source Select 7 */
#define SELA__XT1CLK        (0x0000u)   /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK        (0x0100u)   /* ACLK Source Select VLOCLK */
#define SELA__REFOCLK       (0x0200u)   /* ACLK Source Select REFOCLK */
#define SELA__DCOCLK        (0x0300u)   /* ACLK Source Select DCOCLK */
#define SELA__DCOCLKDIV     (0x0400u)   /* ACLK Source Select DCOCLKDIV */
#define SELA__XT2CLK        (0x0500u)   /* ACLK Source Select XT2CLK */
/* UCSCTL5 Control Bits */
#define DIVM0_L             (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1_L             (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2_L             (0x0004u)   /* MCLK Divider Bit: 2 */
#define DIVS0_L             (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1_L             (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2_L             (0x0040u)   /* SMCLK Divider Bit: 2 */
#define DIVA0_H             (0x0001u)   /* ACLK Divider Bit: 0 */
#define DIVA1_H             (0x0002u)   /* ACLK Divider Bit: 1 */
#define DIVA2_H             (0x0004u)   /* ACLK Divider Bit: 2 */
#define DIVPA0_H            (0x0010u)   /* ACLK from Pin Divider Bit: 0 */
#define DIVPA1_H            (0x0020u)   /* ACLK from Pin Divider Bit: 1 */
#define DIVPA2_H            (0x0040u)   /* ACLK from Pin Divider Bit: 2 */

#define DIVM_0              (0x0000u)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001u)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002u)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003u)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004u)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005u)    /* MCLK Source Divider 5 */
#define DIVM_6              (0x0006u)    /* MCLK Source Divider 6 */
#define DIVM_7              (0x0007u)    /* MCLK Source Divider 7 */
#define DIVM__1             (0x0000u)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001u)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002u)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003u)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004u)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005u)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000u)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010u)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020u)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030u)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040u)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050u)    /* SMCLK Source Divider 5 */
#define DIVS_6              (0x0060u)    /* SMCLK Source Divider 6 */
#define DIVS_7              (0x0070u)    /* SMCLK Source Divider 7 */
#define DIVS__1             (0x0000u)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010u)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020u)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030u)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040u)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050u)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000u)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100u)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200u)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300u)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400u)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500u)    /* ACLK Source Divider 5 */
#define DIVA_6              (0x0600u)    /* ACLK Source Divider 6 */
#define DIVA_7              (0x0700u)    /* ACLK Source Divider 7 */
#define DIVA__1             (0x0000u)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100u)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200u)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300u)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400u)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500u)    /* ACLK Source Divider f(ACLK)/32 */

#define DIVPA_0             (0x0000u)    /* ACLK from Pin Source Divider 0 */
#define DIVPA_1             (0x1000u)    /* ACLK from Pin Source Divider 1 */
#define DIVPA_2             (0x2000u)    /* ACLK from Pin Source Divider 2 */
#define DIVPA_3             (0x3000u)    /* ACLK from Pin Source Divider 3 */
#define DIVPA_4             (0x4000u)    /* ACLK from Pin Source Divider 4 */
#define DIVPA_5             (0x5000u)    /* ACLK from Pin Source Divider 5 */
#define DIVPA_6             (0x6000u)    /* ACLK from Pin Source Divider 6 */
#define DIVPA_7             (0x7000u)    /* ACLK from Pin Source Divider 7 */
#define DIVPA__1            (0x0000u)    /* ACLK from Pin Source Divider f(ACLK)/1 */
#define DIVPA__2            (0x1000u)    /* ACLK from Pin Source Divider f(ACLK)/2 */
#define DIVPA__4            (0x2000u)    /* ACLK from Pin Source Divider f(ACLK)/4 */
#define DIVPA__8            (0x3000u)    /* ACLK from Pin Source Divider f(ACLK)/8 */
#define DIVPA__16           (0x4000u)    /* ACLK from Pin Source Divider f(ACLK)/16 */
#define DIVPA__32           (0x5000u)    /* ACLK from Pin Source Divider f(ACLK)/32 */
/* UCSCTL6 Control Bits */
#define XT1OFF_L            (0x0001u)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF_L          (0x0002u)    /* SMCLK Off */
#define XCAP0_L             (0x0004u)   /* XIN/XOUT Cap Bit: 0 */
#define XCAP1_L             (0x0008u)   /* XIN/XOUT Cap Bit: 1 */
#define XT1BYPASS_L         (0x0010u)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L               (0x0020u)   /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L         (0x0040u)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L         (0x0080u)    /* XT1 Drive Level mode Bit 1 */
/* UCSCTL6 Control Bits */
#define XT2OFF_H            (0x0001u)    /* High Frequency Oscillator 2 (XT2) disable */
#define XT2BYPASS_H         (0x0010u)    /* XT2 bypass mode : 0: internal 1:sourced from external pin */
#define XT2DRIVE0_H         (0x0040u)    /* XT2 Drive Level mode Bit 0 */
#define XT2DRIVE1_H         (0x0080u)    /* XT2 Drive Level mode Bit 1 */

#define XCAP_0              (0x0000u)    /* XIN/XOUT Cap 0 */
#define XCAP_1              (0x0004u)    /* XIN/XOUT Cap 1 */
#define XCAP_2              (0x0008u)    /* XIN/XOUT Cap 2 */
#define XCAP_3              (0x000Cu)    /* XIN/XOUT Cap 3 */
#define XT1DRIVE_0          (0x0000u)    /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1          (0x0040u)    /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2          (0x0080u)    /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3          (0x00C0u)    /* XT1 Drive Level mode: 3 */
#define XT2DRIVE_0          (0x0000u)    /* XT2 Drive Level mode: 0 */
#define XT2DRIVE_1          (0x4000u)    /* XT2 Drive Level mode: 1 */
#define XT2DRIVE_2          (0x8000u)    /* XT2 Drive Level mode: 2 */
#define XT2DRIVE_3          (0xC000u)    /* XT2 Drive Level mode: 3 */
/* UCSCTL7 Control Bits */
#define DCOFFG_L            (0x0001u)    /* DCO Fault Flag */
#define XT1LFOFFG_L         (0x0002u)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT1HFOFFG_L         (0x0004u)    /* XT1 High Frequency Oscillator 1 Fault Flag */
#define XT2OFFG_L           (0x0008u)    /* High Frequency Oscillator 2 Fault Flag */
/* UCSCTL8 Control Bits */
#define ACLKREQEN_L         (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004u)    /* SMCLK Clock Request Enable */
#define MODOSCREQEN_L       (0x0008u)    /* MODOSC Clock Request Enable */

/*-------------------------------------------------------------------------
 *   USCI_A0  UART Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCA0CTLW0;   /* USCI A0 Control Word Register 0 */
  struct
  {
    unsigned char UCA0CTLW0_L;
    unsigned char UCA0CTLW0_H;
  };
  struct
  {
    unsigned char UCA0CTL1;   /* USCI A0 Control Register 1 */
    unsigned char UCA0CTL0;   /* USCI A0 Control Register 0 */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char UCTXBRK         : 1; /* Send next Data as Break */
      unsigned char UCTXADDR        : 1; /* Send next Data as Address */
      unsigned char UCDORM          : 1; /* Dormant (Sleep) Mode */
      unsigned char UCBRKIE         : 1; /* Break interrupt enable */
      unsigned char UCRXEIE         : 1; /* RX Error interrupt enable */
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCA0CTL1_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCSPB           : 1; /* Async. Mode: Stop Bits  0:one / 1: two */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCPAR           : 1; /* Async. Mode: Parity     0:odd / 1:even */
      unsigned char UCPEN           : 1; /* Async. Mode: Parity enable */
    } UCA0CTL0_bit;
  }; 
  unsigned short UCA0CTLW0__SPI;   /*  */
  struct
  {
    unsigned char UCA0CTL1__SPI;   /*  */
    unsigned char UCA0CTL0__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char                : 5;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCA0CTL1__SPI_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
      unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
    } UCA0CTL0__SPI_bit;
  }; 
} @0x05C0;

enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCSPB           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCPAR           = 0x0040,
  UCPEN           = 0x0080
};

enum {
  UCSWRST         = 0x0001,
  UCTXBRK         = 0x0002,
  UCTXADDR        = 0x0004,
  UCDORM          = 0x0008,
  UCBRKIE         = 0x0010,
  UCRXEIE         = 0x0020,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080
};

__no_init volatile union
{
  unsigned short UCA0BRW;   /* USCI A0 Baud Word Rate 0 */
  struct
  {
    unsigned char UCA0BRW_L;
    unsigned char UCA0BRW_H;
  };
  struct
  {
    unsigned char UCA0BR0;   /* USCI A0 Baud Rate 0 */
    unsigned char UCA0BR1;   /* USCI A0 Baud Rate 1 */
  };
  unsigned short UCA0BRW__SPI;   /*  */
  struct
  {
    unsigned char UCA0BR0__SPI;   /*  */
    unsigned char UCA0BR1__SPI;   /*  */
  };
} @0x05C6;

__no_init volatile union
{
  unsigned char UCA0MCTL;   /* USCI A0 Modulation Control */

  struct
  {
    unsigned char UCOS16          : 1; /* USCI 16-times Oversampling enable */
    unsigned char UCBRS0          : 1; /* USCI Second Stage Modulation Select 0 */
    unsigned char UCBRS1          : 1; /* USCI Second Stage Modulation Select 1 */
    unsigned char UCBRS2          : 1; /* USCI Second Stage Modulation Select 2 */
    unsigned char UCBRF0          : 1; /* USCI First Stage Modulation Select 0 */
    unsigned char UCBRF1          : 1; /* USCI First Stage Modulation Select 1 */
    unsigned char UCBRF2          : 1; /* USCI First Stage Modulation Select 2 */
    unsigned char UCBRF3          : 1; /* USCI First Stage Modulation Select 3 */
  } UCA0MCTL_bit;

  unsigned char UCA0MCTL__SPI;   /*  */
} @0x05C8;

enum {
  UCOS16          = 0x0001,
  UCBRS0          = 0x0002,
  UCBRS1          = 0x0004,
  UCBRS2          = 0x0008,
  UCBRF0          = 0x0010,
  UCBRF1          = 0x0020,
  UCBRF2          = 0x0040,
  UCBRF3          = 0x0080
};

__no_init volatile union
{
  unsigned char UCA0STAT;   /* USCI A0 Status Register */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char UCADDR          : 1; /* USCI Address received Flag */
    unsigned char UCRXERR         : 1; /* USCI RX Error Flag */
    unsigned char UCBRK           : 1; /* USCI Break received */
    unsigned char UCPE            : 1; /* USCI Parity Error Flag */
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA0STAT_bit;

  unsigned char UCA0STAT__SPI;   /*  */
  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA0STAT__SPI_bit;

} @0x05CA;

enum {
  UCBUSY          = 0x0001,
  UCADDR          = 0x0002,
  UCRXERR         = 0x0004,
  UCBRK           = 0x0008,
  UCPE            = 0x0010,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080
};

__no_init volatile union
{
  unsigned __READ char UCA0RXBUF;   /* USCI A0 Receive Buffer */
  unsigned char UCA0RXBUF__SPI;   /*  */
} @0x05CC;

__no_init volatile union
{
  unsigned char UCA0TXBUF;   /* USCI A0 Transmit Buffer */
  unsigned char UCA0TXBUF__SPI;   /*  */
} @0x05CE;


__no_init volatile union
{
  unsigned char UCA0ABCTL;   /* USCI A0 LIN Control */

  struct
  {
    unsigned char UCABDEN         : 1; /* Auto Baud Rate detect enable */
    unsigned char                : 1;
    unsigned char UCBTOE          : 1; /* Break Timeout error */
    unsigned char UCSTOE          : 1; /* Sync-Field Timeout error */
    unsigned char UCDELIM0        : 1; /* Break Sync Delimiter 0 */
    unsigned char UCDELIM1        : 1; /* Break Sync Delimiter 1 */
  }UCA0ABCTL_bit;
} @0x05D0;


enum {
  UCABDEN         = 0x0001,
  UCBTOE          = 0x0004,
  UCSTOE          = 0x0008,
  UCDELIM0        = 0x0010,
  UCDELIM1        = 0x0020
};

__no_init volatile union
{
  unsigned short UCA0IRCTL;   /* USCI A0 IrDA Transmit Control */
  struct
  {
    unsigned char UCA0IRCTL_L;
    unsigned char UCA0IRCTL_H;
  };
  struct
  {
    unsigned char UCA0IRTCTL;   /* USCI A0 IrDA Transmit Control */
    unsigned char UCA0IRRCTL;   /* USCI A0 IrDA Receive Control */
  };
  struct
  {
    struct
    {
      unsigned char UCIREN          : 1; /* IRDA Encoder/Decoder enable */
      unsigned char UCIRTXCLK       : 1; /* IRDA Transmit Pulse Clock Select */
      unsigned char UCIRTXPL0       : 1; /* IRDA Transmit Pulse Length 0 */
      unsigned char UCIRTXPL1       : 1; /* IRDA Transmit Pulse Length 1 */
      unsigned char UCIRTXPL2       : 1; /* IRDA Transmit Pulse Length 2 */
      unsigned char UCIRTXPL3       : 1; /* IRDA Transmit Pulse Length 3 */
      unsigned char UCIRTXPL4       : 1; /* IRDA Transmit Pulse Length 4 */
      unsigned char UCIRTXPL5       : 1; /* IRDA Transmit Pulse Length 5 */
    } UCA0IRTCTL_bit;

    struct
    {
      unsigned char UCIRRXFE        : 1; /* IRDA Receive Filter enable */
      unsigned char UCIRRXPL        : 1; /* IRDA Receive Input Polarity */
      unsigned char UCIRRXFL0       : 1; /* IRDA Receive Filter Length 0 */
      unsigned char UCIRRXFL1       : 1; /* IRDA Receive Filter Length 1 */
      unsigned char UCIRRXFL2       : 1; /* IRDA Receive Filter Length 2 */
      unsigned char UCIRRXFL3       : 1; /* IRDA Receive Filter Length 3 */
      unsigned char UCIRRXFL4       : 1; /* IRDA Receive Filter Length 4 */
      unsigned char UCIRRXFL5       : 1; /* IRDA Receive Filter Length 5 */
    } UCA0IRRCTL_bit;
  }; 
} @0x05D2;

enum {
  UCIREN          = 0x0001,
  UCIRTXCLK       = 0x0002,
  UCIRTXPL0       = 0x0004,
  UCIRTXPL1       = 0x0008,
  UCIRTXPL2       = 0x0010,
  UCIRTXPL3       = 0x0020,
  UCIRTXPL4       = 0x0040,
  UCIRTXPL5       = 0x0080
};

enum {
  UCIRRXFE        = 0x0001,
  UCIRRXPL        = 0x0002,
  UCIRRXFL0       = 0x0004,
  UCIRRXFL1       = 0x0008,
  UCIRRXFL2       = 0x0010,
  UCIRRXFL3       = 0x0020,
  UCIRRXFL4       = 0x0040,
  UCIRRXFL5       = 0x0080
};

__no_init volatile union
{
  unsigned short UCA0ICTL;   /* USCI A0 Interrupt Enable Register */
  struct
  {
    unsigned char UCA0ICTL_L;
    unsigned char UCA0ICTL_H;
  };
  struct
  {
    unsigned char UCA0IE;   /* USCI A0 Interrupt Enable Register */
    unsigned char UCA0IFG;   /* USCI A0 Interrupt Flags Register */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
    } UCA0IE_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCA0IFG_bit;
  }; 
  unsigned short UCA0ICTL__SPI;   /*  */
  struct
  {
    unsigned char UCA0IE__SPI;   /*  */
    unsigned char UCA0IFG__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCA0IE__SPI_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCA0IFG__SPI_bit;
  }; 
} @0x05DC;

enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002
};

enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002
};

__no_init volatile union
{
  unsigned short  UCA0IV;   /* USCI A0 Interrupt Vector Register */
  unsigned short UCA0IV__SPI;   /*  */
} @0x05DE;

#define __MSP430_HAS_USCI_A0__       /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_A0__ 0x05C0

/*-------------------------------------------------------------------------
 *   USCI_A0  SPI Mode
 *-------------------------------------------------------------------------*/


enum {
/*  UCSYNC          = 0x0001, */
/*  UCMODE0         = 0x0002, */
/*  UCMODE1         = 0x0004, */
  UCMST           = 0x0008,
/*  UC7BIT          = 0x0010, */
/*  UCMSB           = 0x0020, */
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080
};

/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
enum {
/*  UCRXIE          = 0x0001, */
/*  UCTXIE          = 0x0002, */
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020
};

/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
};

*/
/*-------------------------------------------------------------------------
 *   USCI_B0  SPI Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCB0CTLW0__SPI;   /*  */
  struct
  {
    unsigned char UCB0CTL1__SPI;   /*  */
    unsigned char UCB0CTL0__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char                : 5;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCB0CTL1__SPI_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
      unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
    } UCB0CTL0__SPI_bit;
  }; 
  unsigned short UCB0CTLW0;   /* USCI B0 Control Word Register 0 */
  struct
  {
    unsigned char UCB0CTL1;   /* USCI B0 Control Register 1 */
    unsigned char UCB0CTL0;   /* USCI B0 Control Register 0 */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char UCTXSTT         : 1; /* Transmit START */
      unsigned char UCTXSTP         : 1; /* Transmit STOP */
      unsigned char UCTXNACK        : 1; /* Transmit NACK */
      unsigned char UCTR            : 1; /* Transmit/Receive Select/Flag */
      unsigned char                : 1;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCB0CTL1_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char                : 1;
      unsigned char UCMM            : 1; /* Multi-Master Environment */
      unsigned char UCSLA10         : 1; /* 10-bit Slave Address Mode */
      unsigned char UCA10           : 1; /* 10-bit Address Mode */
    } UCB0CTL0_bit;
  }; 
} @0x05E0;



typedef enum                     
{
  AD_SAMPLE,
  UPDATE_LCD
}UpdateLcdStatusDef;


/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCMST           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080,
};

*/
/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
__no_init volatile union
{
  unsigned short UCB0BRW__SPI;   /*  */
  struct
  {
    unsigned char UCB0BR0__SPI;   /*  */
    unsigned char UCB0BR1__SPI;   /*  */
  };
  unsigned short UCB0BRW;   /* USCI B0 Baud Word Rate 0 */
  struct
  {
    unsigned char UCB0BR0;   /* USCI B0 Baud Rate 0 */
    unsigned char UCB0BR1;   /* USCI B0 Baud Rate 1 */
  };
} @0x05E6;

__no_init volatile union
{
  unsigned char UCB0STAT__SPI;   /*  */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB0STAT__SPI_bit;

  unsigned char UCB0STAT;   /* USCI B0 Status Register */
  struct
  {
    unsigned char                : 4;
    unsigned char UCBBUSY         : 1; /* Bus Busy Flag */
    unsigned char UCGC            : 1; /* General Call address received Flag */
    unsigned char UCSCLLOW        : 1; /* SCL low */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB0STAT_bit;

} @0x05EA;

/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCB0RXBUF__SPI;   /*  */
  unsigned __READ char UCB0RXBUF;   /* USCI B0 Receive Buffer */
} @0x05EC;

__no_init volatile union
{
  unsigned char UCB0TXBUF__SPI;   /*  */
  unsigned char UCB0TXBUF;   /* USCI B0 Transmit Buffer */
} @0x05EE;

__no_init volatile union
{
  unsigned short UCB0ICTL__SPI;   /*  */
  struct
  {
    unsigned char UCB0IE__SPI;   /*  */
    unsigned char UCB0IFG__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCB0IE__SPI_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCB0IFG__SPI_bit;
  }; 
  unsigned short UCB0ICTL;   /* USCI B0 Interrupt Enable Register */
  struct
  {
    unsigned char UCB0IE;   /* USCI B0 Interrupt Enable Register */
    unsigned char UCB0IFG;   /* USCI B0 Interrupt Flags Register */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCB0IE_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
      unsigned char UCSTTIFG        : 1; /* START Condition interrupt Flag */
      unsigned char UCSTPIFG        : 1; /* STOP Condition interrupt Flag */
      unsigned char UCALIFG         : 1; /* Arbitration Lost interrupt Flag */
      unsigned char UCNACKIFG       : 1; /* NAK Condition interrupt Flag */
    } UCB0IFG_bit;
  }; 
} @0x05FC;

/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020,
};

*/
/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
};

*/
__no_init volatile union
{
  unsigned short UCB0IV__SPI;   /*  */
  unsigned short UCB0IV;   /* USCI B0 Interrupt Vector Register */
} @0x05FE;

/*-------------------------------------------------------------------------
 *   USCI_B0  I2C Mode
 *-------------------------------------------------------------------------*/


enum {
/*  UCSYNC          = 0x0001, */
/*  UCMODE0         = 0x0002, */
/*  UCMODE1         = 0x0004, */
/*  UCMST           = 0x0008, */
  UCMM            = 0x0020,
  UCSLA10         = 0x0040,
  UCA10           = 0x0080
};

enum {
/*  UCSWRST         = 0x0001, */
  UCTXSTT         = 0x0002,
  UCTXSTP         = 0x0004,
  UCTXNACK        = 0x0008,
  UCTR            = 0x0010
/*  UCSSEL0         = 0x0040, */
/*  UCSSEL1         = 0x0080, */
};

enum {
  UCBBUSY         = 0x0010,
  UCGC            = 0x0020,
  UCSCLLOW        = 0x0040
/*  UCLISTEN        = 0x0080, */
};

__no_init volatile union
{
  unsigned short UCB0I2COA;   /* USCI B0 I2C Own Address */

  struct
  {
    unsigned short UCOA0           : 1; /* I2C Own Address 0 */
    unsigned short UCOA1           : 1; /* I2C Own Address 1 */
    unsigned short UCOA2           : 1; /* I2C Own Address 2 */
    unsigned short UCOA3           : 1; /* I2C Own Address 3 */
    unsigned short UCOA4           : 1; /* I2C Own Address 4 */
    unsigned short UCOA5           : 1; /* I2C Own Address 5 */
    unsigned short UCOA6           : 1; /* I2C Own Address 6 */
    unsigned short UCOA7           : 1; /* I2C Own Address 7 */
    unsigned short UCOA8           : 1; /* I2C Own Address 8 */
    unsigned short UCOA9           : 1; /* I2C Own Address 9 */
    unsigned short                : 5;
    unsigned short UCGCEN          : 1; /* I2C General Call enable */
  } UCB0I2COA_bit;

  struct
  {
    unsigned char UCB0I2COA_L;
    unsigned char UCB0I2COA_H;
  };
} @0x05F0;

enum {
  UCOA0           = 0x0001,
  UCOA1           = 0x0002,
  UCOA2           = 0x0004,
  UCOA3           = 0x0008,
  UCOA4           = 0x0010,
  UCOA5           = 0x0020,
  UCOA6           = 0x0040,
  UCOA7           = 0x0080,
  UCOA8           = 0x0100,
  UCOA9           = 0x0200,
  UCGCEN          = 0x8000
};

__no_init volatile union
{
  unsigned short UCB0I2CSA;   /* USCI B0 I2C Slave Address */

  struct
  {
    unsigned short UCSA0           : 1; /* I2C Slave Address 0 */
    unsigned short UCSA1           : 1; /* I2C Slave Address 1 */
    unsigned short UCSA2           : 1; /* I2C Slave Address 2 */
    unsigned short UCSA3           : 1; /* I2C Slave Address 3 */
    unsigned short UCSA4           : 1; /* I2C Slave Address 4 */
    unsigned short UCSA5           : 1; /* I2C Slave Address 5 */
    unsigned short UCSA6           : 1; /* I2C Slave Address 6 */
    unsigned short UCSA7           : 1; /* I2C Slave Address 7 */
    unsigned short UCSA8           : 1; /* I2C Slave Address 8 */
    unsigned short UCSA9           : 1; /* I2C Slave Address 9 */
  } UCB0I2CSA_bit;

  struct
  {
    unsigned char UCB0I2CSA_L;
    unsigned char UCB0I2CSA_H;
  };
} @0x05F2;

enum {
  UCSA0           = 0x0001,
  UCSA1           = 0x0002,
  UCSA2           = 0x0004,
  UCSA3           = 0x0008,
  UCSA4           = 0x0010,
  UCSA5           = 0x0020,
  UCSA6           = 0x0040,
  UCSA7           = 0x0080,
  UCSA8           = 0x0100,
  UCSA9           = 0x0200
};

/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020,
};

*/
enum {
/*  UCRXIFG         = 0x0001, */
/*  UCTXIFG         = 0x0002, */
  UCSTTIFG        = 0x0004,
  UCSTPIFG        = 0x0008,
  UCALIFG         = 0x0010,
  UCNACKIFG       = 0x0020
};

#define __MSP430_HAS_USCI_B0__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_B0__ 0x05E0
#define UCMODE_0            (0x00)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x02)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x04)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x06)    /* Sync. Mode: USCI Mode: 3 */
#define UCSSEL_0            (0x00)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x40)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x80)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0xC0)    /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK        (0x00)    /* USCI 0 Clock Source: UCLK */
#define UCSSEL__ACLK        (0x40)    /* USCI 0 Clock Source: ACLK */
#define UCSSEL__SMCLK       (0x80)    /* USCI 0 Clock Source: SMCLK */

#define UCBRF_0             (0x00)    /* USCI First Stage Modulation: 0 */
#define UCBRF_1             (0x10)    /* USCI First Stage Modulation: 1 */
#define UCBRF_2             (0x20)    /* USCI First Stage Modulation: 2 */
#define UCBRF_3             (0x30)    /* USCI First Stage Modulation: 3 */
#define UCBRF_4             (0x40)    /* USCI First Stage Modulation: 4 */
#define UCBRF_5             (0x50)    /* USCI First Stage Modulation: 5 */
#define UCBRF_6             (0x60)    /* USCI First Stage Modulation: 6 */
#define UCBRF_7             (0x70)    /* USCI First Stage Modulation: 7 */
#define UCBRF_8             (0x80)    /* USCI First Stage Modulation: 8 */
#define UCBRF_9             (0x90)    /* USCI First Stage Modulation: 9 */
#define UCBRF_10            (0xA0)    /* USCI First Stage Modulation: A */
#define UCBRF_11            (0xB0)    /* USCI First Stage Modulation: B */
#define UCBRF_12            (0xC0)    /* USCI First Stage Modulation: C */
#define UCBRF_13            (0xD0)    /* USCI First Stage Modulation: D */
#define UCBRF_14            (0xE0)    /* USCI First Stage Modulation: E */
#define UCBRF_15            (0xF0)    /* USCI First Stage Modulation: F */

#define UCBRS_0             (0x00)    /* USCI Second Stage Modulation: 0 */
#define UCBRS_1             (0x02)    /* USCI Second Stage Modulation: 1 */
#define UCBRS_2             (0x04)    /* USCI Second Stage Modulation: 2 */
#define UCBRS_3             (0x06)    /* USCI Second Stage Modulation: 3 */
#define UCBRS_4             (0x08)    /* USCI Second Stage Modulation: 4 */
#define UCBRS_5             (0x0A)    /* USCI Second Stage Modulation: 5 */
#define UCBRS_6             (0x0C)    /* USCI Second Stage Modulation: 6 */
#define UCBRS_7             (0x0E)    /* USCI Second Stage Modulation: 7 */
#define UCIDLE              (0x02)    /* USCI Idle line detected Flag */
/* UCBxI2COA Control Bits */
#define UCOA7_L             (0x0080u)  /* I2C Own Address 7 */
#define UCOA6_L             (0x0040u)  /* I2C Own Address 6 */
#define UCOA5_L             (0x0020u)  /* I2C Own Address 5 */
#define UCOA4_L             (0x0010u)  /* I2C Own Address 4 */
#define UCOA3_L             (0x0008u)  /* I2C Own Address 3 */
#define UCOA2_L             (0x0004u)  /* I2C Own Address 2 */
#define UCOA1_L             (0x0002u)  /* I2C Own Address 1 */
#define UCOA0_L             (0x0001u)  /* I2C Own Address 0 */
/* UCBxI2COA Control Bits */
#define UCGCEN_H            (0x0080u)  /* I2C General Call enable */
#define UCOA9_H             (0x0002u)  /* I2C Own Address 9 */
#define UCOA8_H             (0x0001u)  /* I2C Own Address 8 */
/* UCBxI2CSA Control Bits */
#define UCSA7_L             (0x0080u)  /* I2C Slave Address 7 */
#define UCSA6_L             (0x0040u)  /* I2C Slave Address 6 */
#define UCSA5_L             (0x0020u)  /* I2C Slave Address 5 */
#define UCSA4_L             (0x0010u)  /* I2C Slave Address 4 */
#define UCSA3_L             (0x0008u)  /* I2C Slave Address 3 */
#define UCSA2_L             (0x0004u)  /* I2C Slave Address 2 */
#define UCSA1_L             (0x0002u)  /* I2C Slave Address 1 */
#define UCSA0_L             (0x0001u)  /* I2C Slave Address 0 */
/* UCBxI2CSA Control Bits */
#define UCSA9_H             (0x0002u)  /* I2C Slave Address 9 */
#define UCSA8_H             (0x0001u)  /* I2C Slave Address 8 */
/* USCI Definitions */
#define USCI_NONE           (0x0000u)    /* No Interrupt pending */
#define USCI_UCRXIFG        (0x0002u)    /* USCI UCRXIFG */
#define USCI_UCTXIFG        (0x0004u)    /* USCI UCTXIFG */
#define USCI_I2C_UCALIFG    (0x0002u)    /* USCI I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG  (0x0004u)    /* USCI I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG   (0x0006u)    /* USCI I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG   (0x0008u)    /* USCI I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG    (0x000Au)    /* USCI I2C Mode: UCRXIFG */
#define USCI_I2C_UCTXIFG    (0x000Cu)    /* USCI I2C Mode: UCTXIFG */

/*-------------------------------------------------------------------------
 *   USCI_A1  UART Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCA1CTLW0;   /* USCI A1 Control Word Register 0 */
  struct
  {
    unsigned char UCA1CTLW0_L;
    unsigned char UCA1CTLW0_H;
  };
  struct
  {
    unsigned char UCA1CTL1;   /* USCI A1 Control Register 1 */
    unsigned char UCA1CTL0;   /* USCI A1 Control Register 0 */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char UCTXBRK         : 1; /* Send next Data as Break */
      unsigned char UCTXADDR        : 1; /* Send next Data as Address */
      unsigned char UCDORM          : 1; /* Dormant (Sleep) Mode */
      unsigned char UCBRKIE         : 1; /* Break interrupt enable */
      unsigned char UCRXEIE         : 1; /* RX Error interrupt enable */
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCA1CTL1_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCSPB           : 1; /* Async. Mode: Stop Bits  0:one / 1: two */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCPAR           : 1; /* Async. Mode: Parity     0:odd / 1:even */
      unsigned char UCPEN           : 1; /* Async. Mode: Parity enable */
    } UCA1CTL0_bit;
  }; 
  unsigned short UCA1CTLW0__SPI;   /*  */
  struct
  {
    unsigned char UCA1CTL1__SPI;   /*  */
    unsigned char UCA1CTL0__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char                : 5;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCA1CTL1__SPI_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
      unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
    } UCA1CTL0__SPI_bit;
  }; 
} @0x0600;

/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCSPB           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCPAR           = 0x0040,
  UCPEN           = 0x0080,
};

*/
/*
enum {
  UCSWRST         = 0x0001,
  UCTXBRK         = 0x0002,
  UCTXADDR        = 0x0004,
  UCDORM          = 0x0008,
  UCBRKIE         = 0x0010,
  UCRXEIE         = 0x0020,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
__no_init volatile union
{
  unsigned short UCA1BRW;   /* USCI A1 Baud Word Rate 0 */
  struct
  {
    unsigned char UCA1BRW_L;
    unsigned char UCA1BRW_H;
  };
  struct
  {
    unsigned char UCA1BR0;   /* USCI A1 Baud Rate 0 */
    unsigned char UCA1BR1;   /* USCI A1 Baud Rate 1 */
  };
  unsigned short UCA1BRW__SPI;   /*  */
  struct
  {
    unsigned char UCA1BR0__SPI;   /*  */
    unsigned char UCA1BR1__SPI;   /*  */
  };
} @0x0606;

__no_init volatile union
{
  unsigned char UCA1MCTL;   /* USCI A1 Modulation Control */

  struct
  {
    unsigned char UCOS16          : 1; /* USCI 16-times Oversampling enable */
    unsigned char UCBRS0          : 1; /* USCI Second Stage Modulation Select 0 */
    unsigned char UCBRS1          : 1; /* USCI Second Stage Modulation Select 1 */
    unsigned char UCBRS2          : 1; /* USCI Second Stage Modulation Select 2 */
    unsigned char UCBRF0          : 1; /* USCI First Stage Modulation Select 0 */
    unsigned char UCBRF1          : 1; /* USCI First Stage Modulation Select 1 */
    unsigned char UCBRF2          : 1; /* USCI First Stage Modulation Select 2 */
    unsigned char UCBRF3          : 1; /* USCI First Stage Modulation Select 3 */
  } UCA1MCTL_bit;

  unsigned char UCA1MCTL__SPI;   /*  */
} @0x0608;

/*
enum {
  UCOS16          = 0x0001,
  UCBRS0          = 0x0002,
  UCBRS1          = 0x0004,
  UCBRS2          = 0x0008,
  UCBRF0          = 0x0010,
  UCBRF1          = 0x0020,
  UCBRF2          = 0x0040,
  UCBRF3          = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCA1STAT;   /* USCI A1 Status Register */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char UCADDR          : 1; /* USCI Address received Flag */
    unsigned char UCRXERR         : 1; /* USCI RX Error Flag */
    unsigned char UCBRK           : 1; /* USCI Break received */
    unsigned char UCPE            : 1; /* USCI Parity Error Flag */
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA1STAT_bit;

  unsigned char UCA1STAT__SPI;   /*  */
  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCA1STAT__SPI_bit;

} @0x060A;

/*
enum {
  UCBUSY          = 0x0001,
  UCADDR          = 0x0002,
  UCRXERR         = 0x0004,
  UCBRK           = 0x0008,
  UCPE            = 0x0010,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
__no_init volatile union
{
  unsigned __READ char UCA1RXBUF;   /* USCI A1 Receive Buffer */
  unsigned char UCA1RXBUF__SPI;   /*  */
} @0x060C;

__no_init volatile union
{
  unsigned char UCA1TXBUF;   /* USCI A1 Transmit Buffer */
  unsigned char UCA1TXBUF__SPI;   /*  */
} @0x060E;


__no_init volatile union
{
  unsigned char UCA1ABCTL;   /* USCI A1 LIN Control */

  struct
  {
    unsigned char UCABDEN         : 1; /* Auto Baud Rate detect enable */
    unsigned char                : 1;
    unsigned char UCBTOE          : 1; /* Break Timeout error */
    unsigned char UCSTOE          : 1; /* Sync-Field Timeout error */
    unsigned char UCDELIM0        : 1; /* Break Sync Delimiter 0 */
    unsigned char UCDELIM1        : 1; /* Break Sync Delimiter 1 */
  }UCA1ABCTL_bit;
} @0x0610;


/*
enum {
  UCABDEN         = 0x0001,
  UCBTOE          = 0x0004,
  UCSTOE          = 0x0008,
  UCDELIM0        = 0x0010,
  UCDELIM1        = 0x0020,
};

*/
__no_init volatile union
{
  unsigned short UCA1IRCTL;   /* USCI A1 IrDA Transmit Control */
  struct
  {
    unsigned char UCA1IRCTL_L;
    unsigned char UCA1IRCTL_H;
  };
  struct
  {
    unsigned char UCA1IRTCTL;   /* USCI A1 IrDA Transmit Control */
    unsigned char UCA1IRRCTL;   /* USCI A1 IrDA Receive Control */
  };
  struct
  {
    struct
    {
      unsigned char UCIREN          : 1; /* IRDA Encoder/Decoder enable */
      unsigned char UCIRTXCLK       : 1; /* IRDA Transmit Pulse Clock Select */
      unsigned char UCIRTXPL0       : 1; /* IRDA Transmit Pulse Length 0 */
      unsigned char UCIRTXPL1       : 1; /* IRDA Transmit Pulse Length 1 */
      unsigned char UCIRTXPL2       : 1; /* IRDA Transmit Pulse Length 2 */
      unsigned char UCIRTXPL3       : 1; /* IRDA Transmit Pulse Length 3 */
      unsigned char UCIRTXPL4       : 1; /* IRDA Transmit Pulse Length 4 */
      unsigned char UCIRTXPL5       : 1; /* IRDA Transmit Pulse Length 5 */
    } UCA1IRTCTL_bit;

    struct
    {
      unsigned char UCIRRXFE        : 1; /* IRDA Receive Filter enable */
      unsigned char UCIRRXPL        : 1; /* IRDA Receive Input Polarity */
      unsigned char UCIRRXFL0       : 1; /* IRDA Receive Filter Length 0 */
      unsigned char UCIRRXFL1       : 1; /* IRDA Receive Filter Length 1 */
      unsigned char UCIRRXFL2       : 1; /* IRDA Receive Filter Length 2 */
      unsigned char UCIRRXFL3       : 1; /* IRDA Receive Filter Length 3 */
      unsigned char UCIRRXFL4       : 1; /* IRDA Receive Filter Length 4 */
      unsigned char UCIRRXFL5       : 1; /* IRDA Receive Filter Length 5 */
    } UCA1IRRCTL_bit;
  }; 
} @0x0612;

/*
enum {
  UCIREN          = 0x0001,
  UCIRTXCLK       = 0x0002,
  UCIRTXPL0       = 0x0004,
  UCIRTXPL1       = 0x0008,
  UCIRTXPL2       = 0x0010,
  UCIRTXPL3       = 0x0020,
  UCIRTXPL4       = 0x0040,
  UCIRTXPL5       = 0x0080,
};

*/
/*
enum {
  UCIRRXFE        = 0x0001,
  UCIRRXPL        = 0x0002,
  UCIRRXFL0       = 0x0004,
  UCIRRXFL1       = 0x0008,
  UCIRRXFL2       = 0x0010,
  UCIRRXFL3       = 0x0020,
  UCIRRXFL4       = 0x0040,
  UCIRRXFL5       = 0x0080,
};

*/
__no_init volatile union
{
  unsigned short UCA1ICTL;   /* USCI A1 Interrupt Enable Register */
  struct
  {
    unsigned char UCA1ICTL_L;
    unsigned char UCA1ICTL_H;
  };
  struct
  {
    unsigned char UCA1IE;   /* USCI A1 Interrupt Enable Register */
    unsigned char UCA1IFG;   /* USCI A1 Interrupt Flags Register */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
    } UCA1IE_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCA1IFG_bit;
  }; 
  unsigned short UCA1ICTL__SPI;   /*  */
  struct
  {
    unsigned char UCA1IE__SPI;   /*  */
    unsigned char UCA1IFG__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCA1IE__SPI_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCA1IFG__SPI_bit;
  }; 
} @0x061C;

/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
};

*/
/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
};

*/
__no_init volatile union
{
  unsigned short UCA1IV;   /* USCI A1 Interrupt Vector Register */
  unsigned short UCA1IV__SPI;   /*  */
} @0x061E;

#define __MSP430_HAS_USCI_A1__       /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_A1__ 0x0600

/*-------------------------------------------------------------------------
 *   USCI_A1  SPI Mode
 *-------------------------------------------------------------------------*/


/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCMST           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080,
};

*/
/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020,
};

*/
/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
};

*/
/*-------------------------------------------------------------------------
 *   USCI_B1  SPI Mode
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCB1CTLW0__SPI;   /*  */
  struct
  {
    unsigned char UCB1CTL1__SPI;   /*  */
    unsigned char UCB1CTL0__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char                : 5;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCB1CTL1__SPI_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char UC7BIT          : 1; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      unsigned char UCMSB           : 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      unsigned char UCCKPL          : 1; /* Sync. Mode: Clock Polarity */
      unsigned char UCCKPH          : 1; /* Sync. Mode: Clock Phase */
    } UCB1CTL0__SPI_bit;
  }; 
  unsigned short UCB1CTLW0;   /* USCI B1 Control Word Register 0 */
  struct
  {
    unsigned char UCB1CTL1;   /* USCI B1 Control Register 1 */
    unsigned char UCB1CTL0;   /* USCI B1 Control Register 0 */
  };
  struct
  {
    struct
    {
      unsigned char UCSWRST         : 1; /* USCI Software Reset */
      unsigned char UCTXSTT         : 1; /* Transmit START */
      unsigned char UCTXSTP         : 1; /* Transmit STOP */
      unsigned char UCTXNACK        : 1; /* Transmit NACK */
      unsigned char UCTR            : 1; /* Transmit/Receive Select/Flag */
      unsigned char                : 1;
      unsigned char UCSSEL0         : 1; /* USCI 0 Clock Source Select 0 */
      unsigned char UCSSEL1         : 1; /* USCI 0 Clock Source Select 1 */
    } UCB1CTL1_bit;

    struct
    {
      unsigned char UCSYNC          : 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      unsigned char UCMODE0         : 1; /* Async. Mode: USCI Mode 0 */
      unsigned char UCMODE1         : 1; /* Async. Mode: USCI Mode 1 */
      unsigned char UCMST           : 1; /* Sync. Mode: Master Select */
      unsigned char                : 1;
      unsigned char UCMM            : 1; /* Multi-Master Environment */
      unsigned char UCSLA10         : 1; /* 10-bit Slave Address Mode */
      unsigned char UCA10           : 1; /* 10-bit Address Mode */
    } UCB1CTL0_bit;
  }; 
} @0x0620;

/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCMST           = 0x0008,
  UC7BIT          = 0x0010,
  UCMSB           = 0x0020,
  UCCKPL          = 0x0040,
  UCCKPH          = 0x0080,
};

*/
/*
enum {
  UCSWRST         = 0x0001,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
__no_init volatile union
{
  unsigned short UCB1BRW__SPI;   /*  */
  struct
  {
    unsigned char UCB1BR0__SPI;   /*  */
    unsigned char UCB1BR1__SPI;   /*  */
  };
  unsigned short UCB1BRW;   /* USCI B1 Baud Word Rate 0 */
  struct
  {
    unsigned char UCB1BR0;   /* USCI B1 Baud Rate 0 */
    unsigned char UCB1BR1;   /* USCI B1 Baud Rate 1 */
  };
} @0x0626;

__no_init volatile union
{
  unsigned char UCB1STAT__SPI;   /*  */

  struct
  {
    unsigned char UCBUSY          : 1; /* USCI Busy Flag */
    unsigned char                : 4;
    unsigned char UCOE            : 1; /* USCI Overrun Error Flag */
    unsigned char UCFE            : 1; /* USCI Frame Error Flag */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB1STAT__SPI_bit;

  unsigned char UCB1STAT;   /* USCI B1 Status Register */
  struct
  {
    unsigned char                : 4;
    unsigned char UCBBUSY         : 1; /* Bus Busy Flag */
    unsigned char UCGC            : 1; /* General Call address received Flag */
    unsigned char UCSCLLOW        : 1; /* SCL low */
    unsigned char UCLISTEN        : 1; /* USCI Listen mode */
  } UCB1STAT_bit;

} @0x062A;

/*
enum {
  UCBUSY          = 0x0001,
  UCOE            = 0x0020,
  UCFE            = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
__no_init volatile union
{
  unsigned char UCB1RXBUF__SPI;   /*  */
  unsigned __READ char UCB1RXBUF;   /* USCI B1 Receive Buffer */
} @0x062C;

__no_init volatile union
{
  unsigned char UCB1TXBUF__SPI;   /*  */
  unsigned char UCB1TXBUF;   /* USCI B1 Transmit Buffer */
} @0x062E;

__no_init volatile union
{
  unsigned short UCB1ICTL__SPI;   /*  */
  struct
  {
    unsigned char UCB1IE__SPI;   /*  */
    unsigned char UCB1IFG__SPI;   /*  */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCB1IE__SPI_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
    } UCB1IFG__SPI_bit;
  }; 
  unsigned short UCB1ICTL;   /* USCI B1 Interrupt Enable Register */
  struct
  {
    unsigned char UCB1IE;   /* USCI B1 Interrupt Enable Register */
    unsigned char UCB1IFG;   /* USCI B1 Interrupt Flags Register */
  };
  struct
  {
    struct
    {
      unsigned char UCRXIE          : 1; /* USCI Receive Interrupt Enable */
      unsigned char UCTXIE          : 1; /* USCI Transmit Interrupt Enable */
      unsigned char UCSTTIE         : 1; /* START Condition interrupt enable */
      unsigned char UCSTPIE         : 1; /* STOP Condition interrupt enable */
      unsigned char UCALIE          : 1; /* Arbitration Lost interrupt enable */
      unsigned char UCNACKIE        : 1; /* NACK Condition interrupt enable */
    } UCB1IE_bit;

    struct
    {
      unsigned char UCRXIFG         : 1; /* USCI Receive Interrupt Flag */
      unsigned char UCTXIFG         : 1; /* USCI Transmit Interrupt Flag */
      unsigned char UCSTTIFG        : 1; /* START Condition interrupt Flag */
      unsigned char UCSTPIFG        : 1; /* STOP Condition interrupt Flag */
      unsigned char UCALIFG         : 1; /* Arbitration Lost interrupt Flag */
      unsigned char UCNACKIFG       : 1; /* NAK Condition interrupt Flag */
    } UCB1IFG_bit;
  }; 
} @0x063C;

/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020,
};

*/
/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
};

*/
__no_init volatile union
{
  unsigned short UCB1IV__SPI;   /*  */
  unsigned short UCB1IV;   /* USCI B1 Interrupt Vector Register */
} @0x063E;

/*-------------------------------------------------------------------------
 *   USCI_B1  I2C Mode
 *-------------------------------------------------------------------------*/


/*
enum {
  UCSYNC          = 0x0001,
  UCMODE0         = 0x0002,
  UCMODE1         = 0x0004,
  UCMST           = 0x0008,
  UCMM            = 0x0020,
  UCSLA10         = 0x0040,
  UCA10           = 0x0080,
};

*/
/*
enum {
  UCSWRST         = 0x0001,
  UCTXSTT         = 0x0002,
  UCTXSTP         = 0x0004,
  UCTXNACK        = 0x0008,
  UCTR            = 0x0010,
  UCSSEL0         = 0x0040,
  UCSSEL1         = 0x0080,
};

*/
/*
enum {
  UCBBUSY         = 0x0010,
  UCGC            = 0x0020,
  UCSCLLOW        = 0x0040,
  UCLISTEN        = 0x0080,
};

*/
__no_init volatile union
{
  unsigned short UCB1I2COA;   /* USCI B1 I2C Own Address */

  struct
  {
    unsigned short UCOA0           : 1; /* I2C Own Address 0 */
    unsigned short UCOA1           : 1; /* I2C Own Address 1 */
    unsigned short UCOA2           : 1; /* I2C Own Address 2 */
    unsigned short UCOA3           : 1; /* I2C Own Address 3 */
    unsigned short UCOA4           : 1; /* I2C Own Address 4 */
    unsigned short UCOA5           : 1; /* I2C Own Address 5 */
    unsigned short UCOA6           : 1; /* I2C Own Address 6 */
    unsigned short UCOA7           : 1; /* I2C Own Address 7 */
    unsigned short UCOA8           : 1; /* I2C Own Address 8 */
    unsigned short UCOA9           : 1; /* I2C Own Address 9 */
    unsigned short                : 5;
    unsigned short UCGCEN          : 1; /* I2C General Call enable */
  } UCB1I2COA_bit;

  struct
  {
    unsigned char UCB1I2COA_L;
    unsigned char UCB1I2COA_H;
  };
} @0x0630;

/*
enum {
  UCOA0           = 0x0001,
  UCOA1           = 0x0002,
  UCOA2           = 0x0004,
  UCOA3           = 0x0008,
  UCOA4           = 0x0010,
  UCOA5           = 0x0020,
  UCOA6           = 0x0040,
  UCOA7           = 0x0080,
  UCOA8           = 0x0100,
  UCOA9           = 0x0200,
  UCGCEN          = 0x8000,
};

*/
__no_init volatile union
{
  unsigned short UCB1I2CSA;   /* USCI B1 I2C Slave Address */

  struct
  {
    unsigned short UCSA0           : 1; /* I2C Slave Address 0 */
    unsigned short UCSA1           : 1; /* I2C Slave Address 1 */
    unsigned short UCSA2           : 1; /* I2C Slave Address 2 */
    unsigned short UCSA3           : 1; /* I2C Slave Address 3 */
    unsigned short UCSA4           : 1; /* I2C Slave Address 4 */
    unsigned short UCSA5           : 1; /* I2C Slave Address 5 */
    unsigned short UCSA6           : 1; /* I2C Slave Address 6 */
    unsigned short UCSA7           : 1; /* I2C Slave Address 7 */
    unsigned short UCSA8           : 1; /* I2C Slave Address 8 */
    unsigned short UCSA9           : 1; /* I2C Slave Address 9 */
  } UCB1I2CSA_bit;

  struct
  {
    unsigned char UCB1I2CSA_L;
    unsigned char UCB1I2CSA_H;
  };
} @0x0632;

/*
enum {
  UCSA0           = 0x0001,
  UCSA1           = 0x0002,
  UCSA2           = 0x0004,
  UCSA3           = 0x0008,
  UCSA4           = 0x0010,
  UCSA5           = 0x0020,
  UCSA6           = 0x0040,
  UCSA7           = 0x0080,
  UCSA8           = 0x0100,
  UCSA9           = 0x0200,
};

*/
/*
enum {
  UCRXIE          = 0x0001,
  UCTXIE          = 0x0002,
  UCSTTIE         = 0x0004,
  UCSTPIE         = 0x0008,
  UCALIE          = 0x0010,
  UCNACKIE        = 0x0020,
};

*/
/*
enum {
  UCRXIFG         = 0x0001,
  UCTXIFG         = 0x0002,
  UCSTTIFG        = 0x0004,
  UCSTPIFG        = 0x0008,
  UCALIFG         = 0x0010,
  UCNACKIFG       = 0x0020,
};

*/
#define __MSP430_HAS_USCI_B1__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_B1__ 0x0620

/*-------------------------------------------------------------------------
 *   Watchdog Timer
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short WDTCTL;   /* Watchdog Timer Control */

  struct
  {
    unsigned short WDTIS0          : 1; /* WDT - Timer Interval Select 0 */
    unsigned short WDTIS1          : 1; /* WDT - Timer Interval Select 1 */
    unsigned short WDTIS2          : 1; /* WDT - Timer Interval Select 2 */
    unsigned short WDTCNTCL        : 1; /* WDT - Timer Clear */
    unsigned short WDTTMSEL        : 1; /* WDT - Timer Mode Select */
    unsigned short WDTSSEL0        : 1; /* WDT - Timer Clock Source Select 0 */
    unsigned short WDTSSEL1        : 1; /* WDT - Timer Clock Source Select 1 */
    unsigned short WDTHOLD         : 1; /* WDT - Timer hold */
  } WDTCTL_bit;

  struct
  {
    unsigned char WDTCTL_L;
    unsigned char WDTCTL_H;
  };
} @0x015C;

enum {
  WDTIS0          = 0x0001,
  WDTIS1          = 0x0002,
  WDTIS2          = 0x0004,
  WDTCNTCL        = 0x0008,
  WDTTMSEL        = 0x0010,
  WDTSSEL0        = 0x0020,
  WDTSSEL1        = 0x0040,
  WDTHOLD         = 0x0080
};



#define __MSP430_HAS_WDT_A__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x0150
/* WDTCTL Control Bits */
#define WDTIS0_L            (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1_L            (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2_L            (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L          (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL_L          (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0_L          (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L          (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L           (0x0080u)  /* WDT - Timer hold */

#define WDTPW               (0x5A00u)

#define WDTIS_0           (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS_1           (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS_2           (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3           (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS_4           (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS_5           (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6           (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS_7           (7*0x0001u)  /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G         (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M       (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K      (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K       (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K        (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192       (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512        (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS__64         (7*0x0001u)  /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0         (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1         (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2         (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3         (3*0x0020u)  /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK    (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK     (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO      (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */




#pragma language=restore
#endif  /* __IAR_SYSTEMS_ICC__  */


/************************************************************
* Timer A interrupt vector value
************************************************************/

/* Compability definitions */

#define TAIV_CCIFG1         TAIV_TACCR1       /* Capture/compare 1 */
#define TAIV_CCIFG2         TAIV_TACCR2       /* Capture/compare 2 */
#define TAIV_CCIFG3         TAIV_6            /* Capture/compare 3 */
#define TAIV_CCIFG4         TAIV_8            /* Capture/compare 4 */

/************************************************************
* Interrupt Vectors (offset from 0xFF80)
************************************************************/

#define RTC_VECTOR          (41 * 2u) /* 0xFFD2 RTC */
#define PORT2_VECTOR        (42 * 2u) /* 0xFFD4 Port 2 */
#define USCI_B1_VECTOR      (45 * 2u) /* 0xFFDA USCI B1 Receive/Transmit */
#define USCI_A1_VECTOR      (46 * 2u) /* 0xFFDC USCI A1 Receive/Transmit */
#define PORT1_VECTOR        (47 * 2u) /* 0xFFDE Port 1 */
#define TIMER1_A1_VECTOR    (48 * 2u) /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR    (49 * 2u) /* 0xFFE2 Timer1_A3 CC0 */
#define DMA_VECTOR          (50 * 2u) /* 0xFFE4 DMA */
#define TIMER0_A1_VECTOR    (53 * 2u) /* 0xFFEA Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR    (54 * 2u) /* 0xFFEC Timer0_A5 CC0 */
#define ADC12_VECTOR        (55 * 2u) /* 0xFFEE ADC */
#define USCI_B0_VECTOR      (56 * 2u) /* 0xFFF0 USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR      (57 * 2u) /* 0xFFF2 USCI A0 Receive/Transmit */
#define WDT_VECTOR          (58 * 2u) /* 0xFFF4 Watchdog Timer */
#define TIMER0_B1_VECTOR    (59 * 2u) /* 0xFFF6 Timer0_B7 CC1-6, TB */
#define TIMER0_B0_VECTOR    (60 * 2u) /* 0xFFF8 Timer0_B7 CC0 */
#define UNMI_VECTOR         (61 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (62 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (63 * 2u) /* 0xFFFE Reset [Highest Priority] */


#endif /* __IO430xxxx */
