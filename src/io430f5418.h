
/********************************************************************
 *
 * Standard register and bit definitions for the Texas Instruments
 * MSP430 microcontroller.
 *
 * This file supports assembler and C/EC++ development for
 * MSP430F5418 devices.
 *
 * Copyright (C) 2007-2009 IAR Systems AB.
 *
 * $Revision: 6361 $
 *
 ********************************************************************/

#ifndef __IO430F5418
#define __IO430F5418

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error io430f5418.h file for use with ICC430/A430 only
#endif

#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430X CPU */

 
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


#define LPM0      _BIS_SR(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT _BIC_SR_IRQ(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      _BIS_SR(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT _BIC_SR_IRQ(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      _BIS_SR(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT _BIC_SR_IRQ(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      _BIS_SR(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT _BIC_SR_IRQ(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      _BIS_SR(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT _BIC_SR_IRQ(LPM4_bits) /* Exit Low Power Mode 4 */



/*-------------------------------------------------------------------------
 *   SFR  Special Function Registers
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SFRIE1;  /* Interrupt Enable 1 */ 
  
  struct
  {
    unsigned short WDTIE         : 1;  /* WDT Interrupt Enable */ 
    unsigned short OFIE          : 1;  /* Osc Fault Enable */ 
    unsigned short               : 1; 
    unsigned short VMAIE         : 1;  /* Vacant Memory Interrupt Enable */ 
    unsigned short NMIIE         : 1;  /* NMI Interrupt Enable */ 
    unsigned short ACCVIE        : 1;  /* Flash Access Violation Interrupt Enable */ 
    unsigned short JMBINIE       : 1;  /* JTAG Mail Box input Interrupt Enable */ 
    unsigned short JMBOUTIE      : 1;  /* JTAG Mail Box output Interrupt Enable */ 
  } SFRIE1_bit;  
} @ 0x0100;


enum {
  WDTIE               = 0x0001,
  OFIE                = 0x0002,
  VMAIE               = 0x0008,
  NMIIE               = 0x0010,
  ACCVIE              = 0x0020,
  JMBINIE             = 0x0040,
  JMBOUTIE            = 0x0080,
};


__no_init volatile union
{
  unsigned short SFRIFG1;  /* Interrupt Flag 1 */ 
  
  struct
  {
    unsigned short WDTIFG        : 1;  /* WDT Interrupt Flag */ 
    unsigned short OFIFG         : 1;  /* Osc Fault Flag */ 
    unsigned short               : 1; 
    unsigned short VMAIFG        : 1;  /* Vacant Memory Interrupt Flag */ 
    unsigned short NMIIFG        : 1;  /* NMI Interrupt Flag */ 
    unsigned short               : 1; 
    unsigned short JMBINIFG      : 1;  /* JTAG Mail Box input Interrupt Flag */ 
    unsigned short JMBOUTIFG     : 1;  /* JTAG Mail Box output Interrupt Flag */ 
  } SFRIFG1_bit;  
} @ 0x0102;


enum {
  WDTIFG              = 0x0001,
  OFIFG               = 0x0002,
  VMAIFG              = 0x0008,
  NMIIFG              = 0x0010,
  JMBINIFG            = 0x0040,
  JMBOUTIFG           = 0x0080,
};


__no_init volatile union
{
  unsigned short SFRRPCR;  /* RESET Pin Control Register */ 
  
  struct
  {
    unsigned short SYSNMI        : 1;  /* NMI select */ 
    unsigned short SYSNMIIES     : 1;  /* NMI edge select */ 
    unsigned short SYSRSTUP      : 1;  /* RESET Pin pull down/up select */ 
    unsigned short SYSRSTRE      : 1;  /* RESET Pin Resistor enalbe */ 
  } SFRRPCR_bit;  
} @ 0x0104;


enum {
  SYSNMI              = 0x0001,
  SYSNMIIES           = 0x0002,
  SYSRSTUP            = 0x0004,
  SYSRSTRE            = 0x0008,
};



/*-------------------------------------------------------------------------
 *   ADC12
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short ADC12CTL0;  /* ADC12+ Control 0 */ 
  
  struct
  {
    unsigned short ADC12SC       : 1;  /* ADC12 Start Conversion */ 
    unsigned short ADC12ENC      : 1;  /* ADC12 Enable Conversion */ 
    unsigned short ADC12TOVIE    : 1;  /* ADC12 Timer Overflow interrupt enable */ 
    unsigned short ADC12OVIE     : 1;  /* ADC12 Overflow interrupt enable */ 
    unsigned short ADC12ON       : 1;  /* ADC12 On/enable */ 
    unsigned short ADC12REFON    : 1;  /* ADC12 Reference on */ 
    unsigned short ADC12REF2_5V  : 1;  /*  */ 
    unsigned short ADC12MSC      : 1;  /* ADC12 Multiple SampleConversion */ 
    unsigned short ADC12SHT00    : 1;  /* ADC12 Sample Hold 0 Select 0 */ 
    unsigned short ADC12SHT01    : 1;  /* ADC12 Sample Hold 0 Select 1 */ 
    unsigned short ADC12SHT02    : 1;  /* ADC12 Sample Hold 0 Select 2 */ 
    unsigned short ADC12SHT03    : 1;  /* ADC12 Sample Hold 0 Select 3 */ 
    unsigned short ADC12SHT10    : 1;  /* ADC12 Sample Hold 0 Select 0 */ 
    unsigned short ADC12SHT11    : 1;  /* ADC12 Sample Hold 1 Select 1 */ 
    unsigned short ADC12SHT12    : 1;  /* ADC12 Sample Hold 2 Select 2 */ 
    unsigned short ADC12SHT13    : 1;  /* ADC12 Sample Hold 3 Select 3 */ 
  } ADC12CTL0_bit;  
} @ 0x0700;


enum {
  ADC12SC             = 0x0001,
  ADC12ENC            = 0x0002,
  ADC12TOVIE          = 0x0004,
  ADC12OVIE           = 0x0008,
  ADC12ON             = 0x0010,
  ADC12REFON          = 0x0020,
  ADC12REF2_5V        = 0x0040,
  ADC12MSC            = 0x0080,
  ADC12SHT00          = 0x0100,
  ADC12SHT01          = 0x0200,
  ADC12SHT02          = 0x0400,
  ADC12SHT03          = 0x0800,
  ADC12SHT10          = 0x1000,
  ADC12SHT11          = 0x2000,
  ADC12SHT12          = 0x4000,
  ADC12SHT13          = 0x8000,
};


__no_init volatile union
{
  unsigned short ADC12CTL1;  /* ADC12+ Control 1 */ 
  
  struct
  {
    unsigned short ADC12BUSY     : 1;  /* ADC12 Busy */ 
    unsigned short ADC12CONSEQ0  : 1;  /* ADC12 Conversion Sequence Select 0 */ 
    unsigned short ADC12CONSEQ1  : 1;  /* ADC12 Conversion Sequence Select 1 */ 
    unsigned short ADC12SSEL0    : 1;  /* ADC12 Clock Source Select 0 */ 
    unsigned short ADC12SSEL1    : 1;  /* ADC12 Clock Source Select 1 */ 
    unsigned short ADC12DIV0     : 1;  /* ADC12 Clock Divider Select 0 */ 
    unsigned short ADC12DIV1     : 1;  /* ADC12 Clock Divider Select 1 */ 
    unsigned short ADC12DIV2     : 1;  /* ADC12 Clock Divider Select 2 */ 
    unsigned short ADC12ISSH     : 1;  /* ADC12 Invert Sample Hold Signal */ 
    unsigned short ADC12SHP      : 1;  /* ADC12 Sample/Hold Pulse Mode */ 
    unsigned short ADC12SHS0     : 1;  /* ADC12 Sample/Hold Source 0 */ 
    unsigned short ADC12SHS1     : 1;  /* ADC12 Sample/Hold Source 1 */ 
    unsigned short ADC12CSTARTADD0 : 1;  /* ADC12 Conversion Start Address 0 */ 
    unsigned short ADC12CSTARTADD1 : 1;  /* ADC12 Conversion Start Address 1 */ 
    unsigned short ADC12CSTARTADD2 : 1;  /* ADC12 Conversion Start Address 2 */ 
    unsigned short ADC12CSTARTADD3 : 1;  /* ADC12 Conversion Start Address 3 */ 
  } ADC12CTL1_bit;  
} @ 0x0702;


enum {
  ADC12BUSY           = 0x0001,
  ADC12CONSEQ0        = 0x0002,
  ADC12CONSEQ1        = 0x0004,
  ADC12SSEL0          = 0x0008,
  ADC12SSEL1          = 0x0010,
  ADC12DIV0           = 0x0020,
  ADC12DIV1           = 0x0040,
  ADC12DIV2           = 0x0080,
  ADC12ISSH           = 0x0100,
  ADC12SHP            = 0x0200,
  ADC12SHS0           = 0x0400,
  ADC12SHS1           = 0x0800,
  ADC12CSTARTADD0     = 0x1000,
  ADC12CSTARTADD1     = 0x2000,
  ADC12CSTARTADD2     = 0x4000,
  ADC12CSTARTADD3     = 0x8000,
};


__no_init volatile union
{
  unsigned short ADC12CTL2;  /* ADC12+ Control 2 */ 
  
  struct
  {
    unsigned short ADC12REFBURST : 1;  /* ADC12+ Reference Burst */ 
    unsigned short ADC12REFOUT   : 1;  /* ADC12+ Reference Out */ 
    unsigned short ADC12SR       : 1;  /* ADC12+ Sampling Rate */ 
    unsigned short ADC12DF       : 1;  /* ADC12+ Data Format */ 
    unsigned short ADC12RES0     : 1;  /* ADC12+ Resolution Bit: 0 */ 
    unsigned short ADC12RES1     : 1;  /* ADC12+ Resolution Bit: 1 */ 
    unsigned short               : 1; 
    unsigned short ADC12TCOFF    : 1;  /* ADC12+ Temperature Sensor Off */ 
    unsigned short ADC12PDIV     : 1;  /* ADC12+ predivider 0:/1   1:/4 */ 
  } ADC12CTL2_bit;  
} @ 0x0704;


enum {
  ADC12REFBURST       = 0x0001,
  ADC12REFOUT         = 0x0002,
  ADC12SR             = 0x0004,
  ADC12DF             = 0x0008,
  ADC12RES0           = 0x0010,
  ADC12RES1           = 0x0020,
  ADC12TCOFF          = 0x0080,
  ADC12PDIV           = 0x0100,
};


__no_init volatile union
{
  unsigned short ADC12IFG;  /* ADC12+ Interrupt Flag */ 
  
  struct
  {
    unsigned short ADC12IFG0     : 1;  /* ADC12 Memory 0      Interrupt Flag */ 
    unsigned short ADC12IFG1     : 1;  /* ADC12 Memory 1      Interrupt Flag */ 
    unsigned short ADC12IFG2     : 1;  /* ADC12 Memory 2      Interrupt Flag */ 
    unsigned short ADC12IFG3     : 1;  /* ADC12 Memory 3      Interrupt Flag */ 
    unsigned short ADC12IFG4     : 1;  /* ADC12 Memory 4      Interrupt Flag */ 
    unsigned short ADC12IFG5     : 1;  /* ADC12 Memory 5      Interrupt Flag */ 
    unsigned short ADC12IFG6     : 1;  /* ADC12 Memory 6      Interrupt Flag */ 
    unsigned short ADC12IFG7     : 1;  /* ADC12 Memory 7      Interrupt Flag */ 
    unsigned short ADC12IFG8     : 1;  /* ADC12 Memory 8      Interrupt Flag */ 
    unsigned short ADC12IFG9     : 1;  /* ADC12 Memory 9      Interrupt Flag */ 
    unsigned short ADC12IFG10    : 1;  /* ADC12 Memory 10      Interrupt Flag */ 
    unsigned short ADC12IFG11    : 1;  /* ADC12 Memory 11      Interrupt Flag */ 
    unsigned short ADC12IFG12    : 1;  /* ADC12 Memory 12      Interrupt Flag */ 
    unsigned short ADC12IFG13    : 1;  /* ADC12 Memory 13      Interrupt Flag */ 
    unsigned short ADC12IFG14    : 1;  /* ADC12 Memory 14      Interrupt Flag */ 
    unsigned short ADC12IFG15    : 1;  /* ADC12 Memory 15      Interrupt Flag */ 
  } ADC12IFG_bit;  
} @ 0x070A;


enum {
  ADC12IFG0           = 0x0001,
  ADC12IFG1           = 0x0002,
  ADC12IFG2           = 0x0004,
  ADC12IFG3           = 0x0008,
  ADC12IFG4           = 0x0010,
  ADC12IFG5           = 0x0020,
  ADC12IFG6           = 0x0040,
  ADC12IFG7           = 0x0080,
  ADC12IFG8           = 0x0100,
  ADC12IFG9           = 0x0200,
  ADC12IFG10          = 0x0400,
  ADC12IFG11          = 0x0800,
  ADC12IFG12          = 0x1000,
  ADC12IFG13          = 0x2000,
  ADC12IFG14          = 0x4000,
  ADC12IFG15          = 0x8000,
};


__no_init volatile union
{
  unsigned short ADC12IE;  /* ADC12+ Interrupt Enable */ 
  
  struct
  {
    unsigned short ADC12IE0      : 1;  /* ADC12 Memory 0      Interrupt Enable */ 
    unsigned short ADC12IE1      : 1;  /* ADC12 Memory 1      Interrupt Enable */ 
    unsigned short ADC12IE2      : 1;  /* ADC12 Memory 2      Interrupt Enable */ 
    unsigned short ADC12IE3      : 1;  /* ADC12 Memory 3      Interrupt Enable */ 
    unsigned short ADC12IE4      : 1;  /* ADC12 Memory 4      Interrupt Enable */ 
    unsigned short ADC12IE5      : 1;  /* ADC12 Memory 5      Interrupt Enable */ 
    unsigned short ADC12IE6      : 1;  /* ADC12 Memory 6      Interrupt Enable */ 
    unsigned short ADC12IE7      : 1;  /* ADC12 Memory 7      Interrupt Enable */ 
    unsigned short ADC12IE8      : 1;  /* ADC12 Memory 8      Interrupt Enable */ 
    unsigned short ADC12IE9      : 1;  /* ADC12 Memory 9      Interrupt Enable */ 
    unsigned short ADC12IE10     : 1;  /* ADC12 Memory 10      Interrupt Enable */ 
    unsigned short ADC12IE11     : 1;  /* ADC12 Memory 11      Interrupt Enable */ 
    unsigned short ADC12IE12     : 1;  /* ADC12 Memory 12      Interrupt Enable */ 
    unsigned short ADC12IE13     : 1;  /* ADC12 Memory 13      Interrupt Enable */ 
    unsigned short ADC12IE14     : 1;  /* ADC12 Memory 14      Interrupt Enable */ 
    unsigned short ADC12IE15     : 1;  /* ADC12 Memory 15      Interrupt Enable */ 
  } ADC12IE_bit;  
} @ 0x070C;


enum {
  ADC12IE0            = 0x0001,
  ADC12IE1            = 0x0002,
  ADC12IE2            = 0x0004,
  ADC12IE3            = 0x0008,
  ADC12IE4            = 0x0010,
  ADC12IE5            = 0x0020,
  ADC12IE6            = 0x0040,
  ADC12IE7            = 0x0080,
  ADC12IE8            = 0x0100,
  ADC12IE9            = 0x0200,
  ADC12IE10           = 0x0400,
  ADC12IE11           = 0x0800,
  ADC12IE12           = 0x1000,
  ADC12IE13           = 0x2000,
  ADC12IE14           = 0x4000,
  ADC12IE15           = 0x8000,
};


 /* ADC12+ Interrupt Vector Word */ 
__no_init volatile unsigned short ADC12IV @ 0x070E;  
 

 /* ADC12 Conversion Memory 0 */ 
__no_init volatile unsigned short ADC12MEM0 @ 0x0720;  
 

 /* ADC12 Conversion Memory 1 */ 
__no_init volatile unsigned short ADC12MEM1 @ 0x0722;  
 

 /* ADC12 Conversion Memory 2 */ 
__no_init volatile unsigned short ADC12MEM2 @ 0x0724;  
 

 /* ADC12 Conversion Memory 3 */ 
__no_init volatile unsigned short ADC12MEM3 @ 0x0726;  
 

 /* ADC12 Conversion Memory 4 */ 
__no_init volatile unsigned short ADC12MEM4 @ 0x0728;  
 

 /* ADC12 Conversion Memory 5 */ 
__no_init volatile unsigned short ADC12MEM5 @ 0x072A;  
 

 /* ADC12 Conversion Memory 6 */ 
__no_init volatile unsigned short ADC12MEM6 @ 0x072C;  
 

 /* ADC12 Conversion Memory 7 */ 
__no_init volatile unsigned short ADC12MEM7 @ 0x072E;  
 

 /* ADC12 Conversion Memory 8 */ 
__no_init volatile unsigned short ADC12MEM8 @ 0x0730;  
 

 /* ADC12 Conversion Memory 9 */ 
__no_init volatile unsigned short ADC12MEM9 @ 0x0732;  
 

 /* ADC12 Conversion Memory 10 */ 
__no_init volatile unsigned short ADC12MEM10 @ 0x0734;  
 

 /* ADC12 Conversion Memory 11 */ 
__no_init volatile unsigned short ADC12MEM11 @ 0x0736;  
 

 /* ADC12 Conversion Memory 12 */ 
__no_init volatile unsigned short ADC12MEM12 @ 0x0738;  
 

 /* ADC12 Conversion Memory 13 */ 
__no_init volatile unsigned short ADC12MEM13 @ 0x073A;  
 

 /* ADC12 Conversion Memory 14 */ 
__no_init volatile unsigned short ADC12MEM14 @ 0x073C;  
 

 /* ADC12 Conversion Memory 15 */ 
__no_init volatile unsigned short ADC12MEM15 @ 0x073E;  
 

__no_init volatile union
{
  unsigned char ADC12MCTL0;  /* ADC12 Memory Control 0 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL0_bit;  
} @ 0x0710;


enum {
  ADC12INCH0          = 0x0001,
  ADC12INCH1          = 0x0002,
  ADC12INCH2          = 0x0004,
  ADC12INCH3          = 0x0008,
  ADC12SREF0          = 0x0010,
  ADC12SREF1          = 0x0020,
  ADC12SREF2          = 0x0040,
  ADC12EOS            = 0x0080,
};


__no_init volatile union
{
  unsigned char ADC12MCTL1;  /* ADC12 Memory Control 1 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL1_bit;  
} @ 0x0711;




__no_init volatile union
{
  unsigned char ADC12MCTL2;  /* ADC12 Memory Control 2 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL2_bit;  
} @ 0x0712;




__no_init volatile union
{
  unsigned char ADC12MCTL3;  /* ADC12 Memory Control 3 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL3_bit;  
} @ 0x0713;




__no_init volatile union
{
  unsigned char ADC12MCTL4;  /* ADC12 Memory Control 4 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL4_bit;  
} @ 0x0714;




__no_init volatile union
{
  unsigned char ADC12MCTL5;  /* ADC12 Memory Control 5 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL5_bit;  
} @ 0x0715;




__no_init volatile union
{
  unsigned char ADC12MCTL6;  /* ADC12 Memory Control 6 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL6_bit;  
} @ 0x0716;




__no_init volatile union
{
  unsigned char ADC12MCTL7;  /* ADC12 Memory Control 7 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL7_bit;  
} @ 0x0717;




__no_init volatile union
{
  unsigned char ADC12MCTL8;  /* ADC12 Memory Control 8 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL8_bit;  
} @ 0x0718;




__no_init volatile union
{
  unsigned char ADC12MCTL9;  /* ADC12 Memory Control 9 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL9_bit;  
} @ 0x0719;




__no_init volatile union
{
  unsigned char ADC12MCTL10;  /* ADC12 Memory Control 10 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL10_bit;  
} @ 0x071A;




__no_init volatile union
{
  unsigned char ADC12MCTL11;  /* ADC12 Memory Control 11 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL11_bit;  
} @ 0x071B;




__no_init volatile union
{
  unsigned char ADC12MCTL12;  /* ADC12 Memory Control 12 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL12_bit;  
} @ 0x071C;




__no_init volatile union
{
  unsigned char ADC12MCTL13;  /* ADC12 Memory Control 13 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL13_bit;  
} @ 0x071D;




__no_init volatile union
{
  unsigned char ADC12MCTL14;  /* ADC12 Memory Control 14 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL14_bit;  
} @ 0x071E;




__no_init volatile union
{
  unsigned char ADC12MCTL15;  /* ADC12 Memory Control 15 */ 
  
  struct
  {
    unsigned char ADC12INCH0     : 1;  /* ADC12 Input Channel Select Bit 0 */ 
    unsigned char ADC12INCH1     : 1;  /* ADC12 Input Channel Select Bit 1 */ 
    unsigned char ADC12INCH2     : 1;  /* ADC12 Input Channel Select Bit 2 */ 
    unsigned char ADC12INCH3     : 1;  /* ADC12 Input Channel Select Bit 3 */ 
    unsigned char ADC12SREF0     : 1;  /* ADC12 Select Reference Bit 0 */ 
    unsigned char ADC12SREF1     : 1;  /* ADC12 Select Reference Bit 1 */ 
    unsigned char ADC12SREF2     : 1;  /* ADC12 Select Reference Bit 2 */ 
    unsigned char ADC12EOS       : 1;  /* ADC12 End of Sequence */ 
  } ADC12MCTL15_bit;  
} @ 0x071F;



 
#define __MSP430_HAS_ADC12_PLUS__          /* Definition to show that Module is available */

#define ADC12SHT0_0         (0*0x100u)
#define ADC12SHT0_1         (1*0x100u)
#define ADC12SHT0_2         (2*0x100u)
#define ADC12SHT0_3         (3*0x100u)
#define ADC12SHT0_4         (4*0x100u)
#define ADC12SHT0_5         (5*0x100u)
#define ADC12SHT0_6         (6*0x100u)
#define ADC12SHT0_7         (7*0x100u)
#define ADC12SHT0_8         (8*0x100u)
#define ADC12SHT0_9         (9*0x100u)
#define ADC12SHT0_10        (10*0x100u)
#define ADC12SHT0_11        (11*0x100u)
#define ADC12SHT0_12        (12*0x100u)
#define ADC12SHT0_13        (13*0x100u)
#define ADC12SHT0_14        (14*0x100u)
#define ADC12SHT0_15        (15*0x100u)

#define ADC12SHT1_0         (0*0x1000u)
#define ADC12SHT1_1         (1*0x1000u)
#define ADC12SHT1_2         (2*0x1000u)
#define ADC12SHT1_3         (3*0x1000u)
#define ADC12SHT1_4         (4*0x1000u)
#define ADC12SHT1_5         (5*0x1000u)
#define ADC12SHT1_6         (6*0x1000u)
#define ADC12SHT1_7         (7*0x1000u)
#define ADC12SHT1_8         (8*0x1000u)
#define ADC12SHT1_9         (9*0x1000u)
#define ADC12SHT1_10        (10*0x1000u)
#define ADC12SHT1_11        (11*0x1000u)
#define ADC12SHT1_12        (12*0x1000u)
#define ADC12SHT1_13        (13*0x1000u)
#define ADC12SHT1_14        (14*0x1000u)
#define ADC12SHT1_15        (15*0x1000u)

#define ADC12CONSEQ_0        (0*2u)
#define ADC12CONSEQ_1        (1*2u)
#define ADC12CONSEQ_2        (2*2u)
#define ADC12CONSEQ_3        (3*2u)
#define ADC12SSEL_0          (0*8u)
#define ADC12SSEL_1          (1*8u)
#define ADC12SSEL_2          (2*8u)
#define ADC12SSEL_3          (3*8u)
#define ADC12DIV_0           (0*0x20u)
#define ADC12DIV_1           (1*0x20u)
#define ADC12DIV_2           (2*0x20u)
#define ADC12DIV_3           (3*0x20u)
#define ADC12DIV_4           (4*0x20u)
#define ADC12DIV_5           (5*0x20u)
#define ADC12DIV_6           (6*0x20u)
#define ADC12DIV_7           (7*0x20u)
#define ADC12SHS_0           (0*0x400u)
#define ADC12SHS_1           (1*0x400u)
#define ADC12SHS_2           (2*0x400u)
#define ADC12SHS_3           (3*0x400u)
#define ADC12CSTARTADD_0     (0*0x1000u)
#define ADC12CSTARTADD_1     (1*0x1000u)
#define ADC12CSTARTADD_2     (2*0x1000u)
#define ADC12CSTARTADD_3     (3*0x1000u)
#define ADC12CSTARTADD_4     (4*0x1000u)
#define ADC12CSTARTADD_5     (5*0x1000u)
#define ADC12CSTARTADD_6     (6*0x1000u)
#define ADC12CSTARTADD_7     (7*0x1000u)
#define ADC12CSTARTADD_8     (8*0x1000u)
#define ADC12CSTARTADD_9     (9*0x1000u)
#define ADC12CSTARTADD_10    (10*0x1000u)
#define ADC12CSTARTADD_11    (11*0x1000u)
#define ADC12CSTARTADD_12    (12*0x1000u)
#define ADC12CSTARTADD_13    (13*0x1000u)
#define ADC12CSTARTADD_14    (14*0x1000u)
#define ADC12CSTARTADD_15    (15*0x1000u)

#define ADC12INCH_0         (0)
#define ADC12INCH_1         (1)
#define ADC12INCH_2         (2)
#define ADC12INCH_3         (3)
#define ADC12INCH_4         (4)
#define ADC12INCH_5         (5)
#define ADC12INCH_6         (6)
#define ADC12INCH_7         (7)
#define ADC12INCH_8         (8)
#define ADC12INCH_9         (9)
#define ADC12INCH_10        (10)
#define ADC12INCH_11        (11)
#define ADC12INCH_12        (12)
#define ADC12INCH_13        (13)
#define ADC12INCH_14        (14)
#define ADC12INCH_15        (15)

#define ADC12SREF_0         (0*0x10u)
#define ADC12SREF_1         (1*0x10u)
#define ADC12SREF_2         (2*0x10u)
#define ADC12SREF_3         (3*0x10u)
#define ADC12SREF_4         (4*0x10u)
#define ADC12SREF_5         (5*0x10u)
#define ADC12SREF_6         (6*0x10u)
#define ADC12SREF_7         (7*0x10u)


 

/*-------------------------------------------------------------------------
 *   CRC
 *-------------------------------------------------------------------------*/


 /* CRC Data In Register */ 
__no_init volatile union
{
  unsigned short CRCDI;   
  
  struct
  {
	unsigned char CRCDI_L	: 8;
	unsigned char CRCDI_H	: 8;
  } CRCDI_byte;  
} @ 0x0150;
//__no_init volatile unsigned short CRCDI @ 0x0150;  
 

 /* CRC Initialisation Register and Result Register */ 
__no_init volatile unsigned short CRCINIRES @ 0x0154;  
 


/*-------------------------------------------------------------------------
 *   DMA_X
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short DMACTL0;  /* DMA Module Control 0 */ 
  
  struct
  {
    unsigned short DMA0TSEL0     : 1;  /* DMA channel 0 transfer select bit 0 */ 
    unsigned short DMA0TSEL1     : 1;  /* DMA channel 0 transfer select bit 1 */ 
    unsigned short DMA0TSEL2     : 1;  /* DMA channel 0 transfer select bit 2 */ 
    unsigned short DMA0TSEL3     : 1;  /* DMA channel 0 transfer select bit 3 */ 
    unsigned short DMA0TSEL4     : 1;  /* DMA channel 0 transfer select bit 4 */ 
    unsigned short               : 3; 
    unsigned short DMA1TSEL0     : 1;  /* DMA channel 1 transfer select bit 0 */ 
    unsigned short DMA1TSEL1     : 1;  /* DMA channel 1 transfer select bit 1 */ 
    unsigned short DMA1TSEL2     : 1;  /* DMA channel 1 transfer select bit 2 */ 
    unsigned short DMA1TSEL3     : 1;  /* DMA channel 1 transfer select bit 3 */ 
    unsigned short DMA1TSEL4     : 1;  /* DMA channel 1 transfer select bit 4 */ 
  } DMACTL0_bit;  
} @ 0x0500;


enum {
  DMA0TSEL0           = 0x0001,
  DMA0TSEL1           = 0x0002,
  DMA0TSEL2           = 0x0004,
  DMA0TSEL3           = 0x0008,
  DMA0TSEL4           = 0x0010,
  DMA1TSEL0           = 0x0100,
  DMA1TSEL1           = 0x0200,
  DMA1TSEL2           = 0x0400,
  DMA1TSEL3           = 0x0800,
  DMA1TSEL4           = 0x1000,
};


__no_init volatile union
{
  unsigned short DMACTL1;  /* DMA Module Control 1 */ 
  
  struct
  {
    unsigned short DMA2TSEL0     : 1;  /* DMA channel 2 transfer select bit 0 */ 
    unsigned short DMA2TSEL1     : 1;  /* DMA channel 2 transfer select bit 1 */ 
    unsigned short DMA2TSEL2     : 1;  /* DMA channel 2 transfer select bit 2 */ 
    unsigned short DMA2TSEL3     : 1;  /* DMA channel 2 transfer select bit 3 */ 
    unsigned short DMA2TSEL4     : 1;  /* DMA channel 2 transfer select bit 4 */ 
  } DMACTL1_bit;  
} @ 0x0502;


enum {
  DMA2TSEL0           = 0x0001,
  DMA2TSEL1           = 0x0002,
  DMA2TSEL2           = 0x0004,
  DMA2TSEL3           = 0x0008,
  DMA2TSEL4           = 0x0010,
};


 /* DMA Module Control 2 */ 
__no_init volatile unsigned short DMACTL2 @ 0x0504;  
 

 /* DMA Module Control 3 */ 
__no_init volatile unsigned short DMACTL3 @ 0x0506;  
 

__no_init volatile union
{
  unsigned short DMACTL4;  /* DMA Module Control 4 */ 
  
  struct
  {
    unsigned short ENNMI         : 1;  /* Enable NMI interruption of DMA */ 
    unsigned short ROUNDROBIN    : 1;  /* Round-Robin DMA channel priorities */ 
    unsigned short DMARMWDIS     : 1;  /* Inhibited DMA transfers during read-modify-write CPU operations */ 
  } DMACTL4_bit;  
} @ 0x0508;


enum {
  ENNMI               = 0x0001,
  ROUNDROBIN          = 0x0002,
  DMARMWDIS           = 0x0004,
};


 /* DMA Interrupt Vector Word */ 
__no_init volatile unsigned short DMAIV @ 0x050E;  
 

__no_init volatile union
{
  unsigned short DMA0CTL;  /* DMA Channel 0 Control */ 
  
  struct
  {
    unsigned short DMAREQ        : 1;  /* Initiate DMA transfer with DMATSEL */ 
    unsigned short DMAABORT      : 1;  /* DMA transfer aborted by NMI */ 
    unsigned short DMAIE         : 1;  /* DMA interrupt enable */ 
    unsigned short DMAIFG        : 1;  /* DMA interrupt flag */ 
    unsigned short DMAEN         : 1;  /* DMA enable */ 
    unsigned short DMALEVEL      : 1;  /* DMA level sensitive trigger select */ 
    unsigned short DMASRCBYTE    : 1;  /* DMA source byte */ 
    unsigned short DMADSTBYTE    : 1;  /* DMA destination byte */ 
    unsigned short DMASRCINCR0   : 1;  /* DMA source increment bit 0 */ 
    unsigned short DMASRCINCR1   : 1;  /* DMA source increment bit 1 */ 
    unsigned short DMADSTINCR0   : 1;  /* DMA destination increment bit 0 */ 
    unsigned short DMADSTINCR1   : 1;  /* DMA destination increment bit 1 */ 
    unsigned short DMADT0        : 1;  /* DMA transfer mode bit 0 */ 
    unsigned short DMADT1        : 1;  /* DMA transfer mode bit 1 */ 
    unsigned short DMADT2        : 1;  /* DMA transfer mode bit 2 */ 
  } DMA0CTL_bit;  
} @ 0x0510;


enum {
  DMAREQ              = 0x0001,
  DMAABORT            = 0x0002,
  DMAIE               = 0x0004,
  DMAIFG              = 0x0008,
  DMAEN               = 0x0010,
  DMALEVEL            = 0x0020,
  DMASRCBYTE          = 0x0040,
  DMADSTBYTE          = 0x0080,
  DMASRCINCR0         = 0x0100,
  DMASRCINCR1         = 0x0200,
  DMADSTINCR0         = 0x0400,
  DMADSTINCR1         = 0x0800,
  DMADT0              = 0x1000,
  DMADT1              = 0x2000,
  DMADT2              = 0x4000,
};


 /* DMA Channel 0 Source Address */ 
__no_init volatile unsigned long DMA0SA @ 0x0512;  
 

 /* DMA Channel 0 Destination Address */ 
__no_init volatile unsigned long DMA0DA @ 0x0516;  
 

 /* DMA Channel 0 Transfer Size */ 
__no_init volatile unsigned short DMA0SZ @ 0x051A;  
 

__no_init volatile union
{
  unsigned short DMA1CTL;  /* DMA Channel 1 Control */ 
  
  struct
  {
    unsigned short DMAREQ        : 1;  /* Initiate DMA transfer with DMATSEL */ 
    unsigned short DMAABORT      : 1;  /* DMA transfer aborted by NMI */ 
    unsigned short DMAIE         : 1;  /* DMA interrupt enable */ 
    unsigned short DMAIFG        : 1;  /* DMA interrupt flag */ 
    unsigned short DMAEN         : 1;  /* DMA enable */ 
    unsigned short DMALEVEL      : 1;  /* DMA level sensitive trigger select */ 
    unsigned short DMASRCBYTE    : 1;  /* DMA source byte */ 
    unsigned short DMADSTBYTE    : 1;  /* DMA destination byte */ 
    unsigned short DMASRCINCR0   : 1;  /* DMA source increment bit 0 */ 
    unsigned short DMASRCINCR1   : 1;  /* DMA source increment bit 1 */ 
    unsigned short DMADSTINCR0   : 1;  /* DMA destination increment bit 0 */ 
    unsigned short DMADSTINCR1   : 1;  /* DMA destination increment bit 1 */ 
    unsigned short DMADT0        : 1;  /* DMA transfer mode bit 0 */ 
    unsigned short DMADT1        : 1;  /* DMA transfer mode bit 1 */ 
    unsigned short DMADT2        : 1;  /* DMA transfer mode bit 2 */ 
  } DMA1CTL_bit;  
} @ 0x0520;




 /* DMA Channel 1 Source Address */ 
__no_init volatile unsigned long DMA1SA @ 0x0522;  
 

 /* DMA Channel 1 Destination Address */ 
__no_init volatile unsigned long DMA1DA @ 0x0526;  
 

 /* DMA Channel 1 Transfer Size */ 
__no_init volatile unsigned short DMA1SZ @ 0x052A;  
 

__no_init volatile union
{
  unsigned short DMA2CTL;  /* DMA Channel 2 Control */ 
  
  struct
  {
    unsigned short DMAREQ        : 1;  /* Initiate DMA transfer with DMATSEL */ 
    unsigned short DMAABORT      : 1;  /* DMA transfer aborted by NMI */ 
    unsigned short DMAIE         : 1;  /* DMA interrupt enable */ 
    unsigned short DMAIFG        : 1;  /* DMA interrupt flag */ 
    unsigned short DMAEN         : 1;  /* DMA enable */ 
    unsigned short DMALEVEL      : 1;  /* DMA level sensitive trigger select */ 
    unsigned short DMASRCBYTE    : 1;  /* DMA source byte */ 
    unsigned short DMADSTBYTE    : 1;  /* DMA destination byte */ 
    unsigned short DMASRCINCR0   : 1;  /* DMA source increment bit 0 */ 
    unsigned short DMASRCINCR1   : 1;  /* DMA source increment bit 1 */ 
    unsigned short DMADSTINCR0   : 1;  /* DMA destination increment bit 0 */ 
    unsigned short DMADSTINCR1   : 1;  /* DMA destination increment bit 1 */ 
    unsigned short DMADT0        : 1;  /* DMA transfer mode bit 0 */ 
    unsigned short DMADT1        : 1;  /* DMA transfer mode bit 1 */ 
    unsigned short DMADT2        : 1;  /* DMA transfer mode bit 2 */ 
  } DMA2CTL_bit;  
} @ 0x0530;




 /* DMA Channel 2 Source Address */ 
__no_init volatile unsigned long DMA2SA @ 0x0532;  
 

 /* DMA Channel 2 Destination Address */ 
__no_init volatile unsigned long DMA2DA @ 0x0536;  
 

 /* DMA Channel 2 Transfer Size */ 
__no_init volatile unsigned short DMA2SZ @ 0x053A;  
 
 
#define __MSP430_HAS_DMAX_3__         /* Definition to show that Module is available */



/* DMACTL0 Control Bits */
#define DMA0TSEL0_L         (0x0001)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L         (0x0002)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L         (0x0004)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L         (0x0008)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L         (0x0010)    /* DMA channel 0 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA1TSEL0_H         (0x0001)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H         (0x0002)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H         (0x0004)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H         (0x0008)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H         (0x0010)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0_L         (0x0001)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L         (0x0002)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L         (0x0004)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L         (0x0008)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L         (0x0010)    /* DMA channel 2 transfer select bit 4 */




 

/*-------------------------------------------------------------------------
 *   Flash Memory
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short FCTL1;  /* FLASH Control 1 */ 
  
  struct
  {
    unsigned short               : 1; 
    unsigned short ERASE         : 1;  /* Enable bit for Flash segment erase */ 
    unsigned short MERAS         : 1;  /* Enable bit for Flash mass erase */ 
    unsigned short EEI           : 1;  /* Enable Erase Interrupts */ 
    unsigned short EEIEX         : 1;  /* Enable Emergency Interrupt Exit */ 
    unsigned short SWRT          : 1;  /* Smart Write enable */ 
    unsigned short WRT           : 1;  /* Enable bit for Flash write */ 
    unsigned short BLKWRT        : 1;  /* Enable bit for Flash segment write */ 
  } FCTL1_bit;  
} @ 0x0140;


enum {
  ERASE               = 0x0002,
  MERAS               = 0x0004,
  EEI                 = 0x0008,
  EEIEX               = 0x0010,
  SWRT                = 0x0020,
  WRT                 = 0x0040,
  BLKWRT              = 0x0080,
};


__no_init volatile union
{
  unsigned short FCTL3;  /* FLASH Control 3 */ 
  
  struct
  {
    unsigned short BUSY          : 1;  /* Flash busy: 1 */ 
    unsigned short KEYV          : 1;  /* Flash Key violation flag */ 
    unsigned short ACCVIFG       : 1;  /* Flash Access violation flag */ 
    unsigned short WAIT          : 1;  /* Wait flag for segment write */ 
    unsigned short LOCK          : 1;  /* Lock bit: 1 - Flash is locked (read only) */ 
    unsigned short EMEX          : 1;  /* Flash Emergency Exit */ 
    unsigned short LOCKA         : 1;  /* Segment A Lock bit: read = 1 - Segment is locked (read only) */ 
    unsigned short FAIL          : 1;  /* Last Program or Erase failed */ 
  } FCTL3_bit;  
} @ 0x0144;


enum {
  BUSY                = 0x0001,
  KEYV                = 0x0002,
  ACCVIFG             = 0x0004,
  WAIT                = 0x0008,
  LOCK                = 0x0010,
  EMEX                = 0x0020,
  LOCKA               = 0x0040,
  FAIL                = 0x0080,
};


__no_init volatile union
{
  unsigned short FCTL4;  /* FLASH Control 4 */ 
  
  struct
  {
    unsigned short VPE           : 1;  /* Voltage Changed during Program Error Flag */ 
    unsigned short               : 3; 
    unsigned short MGR0          : 1;  /* Marginal read mode. */ 
    unsigned short MGR1          : 1;  /* Marginal read mode. */ 
    unsigned short               : 1; 
    unsigned short LOCKINFO      : 1;  /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */ 
  } FCTL4_bit;  
} @ 0x0146;


enum {
  VPE                 = 0x0001,
  MGR0                = 0x0010,
  MGR1                = 0x0020,
  LOCKINFO            = 0x0080,
};

 
#define __MSP430_HAS_FLASH__         /* Definition to show that Module is available */

#define FRKEY               (0x9600)  /* Flash key returned by read */
#define FWKEY               (0xA500)  /* Flash key for write */
#define FXKEY               (0x3300)  /* for use with XOR instruction */


 

/*-------------------------------------------------------------------------
 *   Hardware Multiplier
 *-------------------------------------------------------------------------*/


 /* 32-bit operand 1 - multiply - low word */ 
__no_init volatile unsigned short MPY32L @ 0x04D0;  
 

 /* 32-bit operand 1 - multiply - high word */ 
__no_init volatile unsigned short MPY32H @ 0x04D2;  
 

 /* 32-bit operand 1 - signed multiply - low word */ 
__no_init volatile unsigned short MPYS32L @ 0x04D4;  
 

 /* 32-bit operand 1 - signed multiply - high word */ 
__no_init volatile unsigned short MPYS32H @ 0x04D6;  
 

 /* 32-bit operand 1 - multiply accumulate - low word */ 
__no_init volatile unsigned short MAC32L @ 0x04D8;  
 

 /* 32-bit operand 1 - multiply accumulate - high word */ 
__no_init volatile unsigned short MAC32H @ 0x04DA;  
 

 /* 32-bit operand 1 - signed multiply accumulate - low word */ 
__no_init volatile unsigned short MACS32L @ 0x04DC;  
 

 /* 32-bit operand 1 - signed multiply accumulate - high word */ 
__no_init volatile unsigned short MACS32H @ 0x04DE;  
 

 /* 32-bit operand 2 - low word */ 
__no_init volatile unsigned short OP2L @ 0x04E0;  
 

 /* 32-bit operand 2 - high word */ 
__no_init volatile unsigned short OP2H @ 0x04E2;  
 

 /* 32x32-bit result 0 - least significant word */ 
__no_init volatile unsigned short RES0 @ 0x04E4;  
 

 /* 32x32-bit result 1 */ 
__no_init volatile unsigned short RES1 @ 0x04E6;  
 

 /* 32x32-bit result 2 */ 
__no_init volatile unsigned short RES2 @ 0x04E8;  
 

 /* 32x32-bit result 3 - most significant word */ 
__no_init volatile unsigned short RES3 @ 0x04EA;  
 

__no_init volatile union
{
  unsigned short MPY32CTL0;  /* MPY32 Control Register 0 */ 
  
  struct
  {
    unsigned short MPYC          : 1;  /* Carry of the multiplier */ 
    unsigned short               : 1; 
    unsigned short MPYFRAC       : 1;  /* Fractional mode */ 
    unsigned short MPYSAT        : 1;  /* Saturation mode */ 
    unsigned short MPYM0         : 1;  /* Multiplier mode Bit:0 */ 
    unsigned short MPYM1         : 1;  /* Multiplier mode Bit:1 */ 
    unsigned short OP1_32        : 1;  /* Bit-width of operand 1 0:16Bit / 1:32Bit */ 
    unsigned short OP2_32        : 1;  /* Bit-width of operand 2 0:16Bit / 1:32Bit */ 
    unsigned short MPYDLYWRTEN   : 1;  /* Delayed write enable */ 
    unsigned short MPYDLY32      : 1;  /* Delayed write mode */ 
  } MPY32CTL0_bit;  
} @ 0x04EC;


enum {
  MPYC                = 0x0001,
  MPYFRAC             = 0x0004,
  MPYSAT              = 0x0008,
  MPYM0               = 0x0010,
  MPYM1               = 0x0020,
  OP1_32              = 0x0040,
  OP2_32              = 0x0080,
  MPYDLYWRTEN         = 0x0100,
  MPYDLY32            = 0x0200,
};


 /* Multiply Unsigned/Operand 1 */ 
__no_init volatile unsigned short MPY @ 0x04C0;  
 

 /* Multiply Signed/Operand 1 */ 
__no_init volatile unsigned short MPYS @ 0x04C2;  
 

 /* Multiply Unsigned and Accumulate/Operand 1 */ 
__no_init volatile unsigned short MAC @ 0x04C4;  
 

 /* Multiply Signed and Accumulate/Operand 1 */ 
__no_init volatile unsigned short MACS @ 0x04C6;  
 

 /* Operand 2 */ 
__no_init volatile unsigned short OP2 @ 0x04C8;  
 

 /* Result Low Word */ 
__no_init volatile unsigned short RESLO @ 0x04CA;  
 

 /* Result High Word */ 
__no_init volatile unsigned short RESHI @ 0x04CC;  
 

 /* Sum Extend */ 
__no_init volatile unsigned __READ short SUMEXT @ 0x04CE;  
 
 
#define __MSP430_HAS_MPY32__            /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port1/2 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port A In */ 
__no_init volatile unsigned __READ short PAIN @ 0x0200;  
 

__no_init volatile union
{
  unsigned short PAOUT;  /* Port A Output */ 
  
  struct
  {
    unsigned short PAOUT_0       : 1; 
    unsigned short PAOUT_1       : 1; 
    unsigned short PAOUT_2       : 1; 
    unsigned short PAOUT_3       : 1; 
    unsigned short PAOUT_4       : 1; 
    unsigned short PAOUT_5       : 1; 
    unsigned short PAOUT_6       : 1; 
    unsigned short PAOUT_7       : 1; 
    unsigned short PAOUT_8       : 1; 
    unsigned short PAOUT_9       : 1; 
    unsigned short PAOUT_10      : 1; 
    unsigned short PAOUT_11      : 1; 
    unsigned short PAOUT_12      : 1; 
    unsigned short PAOUT_13      : 1; 
    unsigned short PAOUT_14      : 1; 
    unsigned short PAOUT_15      : 1; 
  } PAOUT_bit;  
} @ 0x0202;


enum {
  PAOUT_0             = 0x0001,
  PAOUT_1             = 0x0002,
  PAOUT_2             = 0x0004,
  PAOUT_3             = 0x0008,
  PAOUT_4             = 0x0010,
  PAOUT_5             = 0x0020,
  PAOUT_6             = 0x0040,
  PAOUT_7             = 0x0080,
  PAOUT_8             = 0x0100,
  PAOUT_9             = 0x0200,
  PAOUT_10            = 0x0400,
  PAOUT_11            = 0x0800,
  PAOUT_12            = 0x1000,
  PAOUT_13            = 0x2000,
  PAOUT_14            = 0x4000,
  PAOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PADIR;  /* Port A Direction */ 
  
  struct
  {
    unsigned short PADIR_0       : 1; 
    unsigned short PADIR_1       : 1; 
    unsigned short PADIR_2       : 1; 
    unsigned short PADIR_3       : 1; 
    unsigned short PADIR_4       : 1; 
    unsigned short PADIR_5       : 1; 
    unsigned short PADIR_6       : 1; 
    unsigned short PADIR_7       : 1; 
    unsigned short PADIR_8       : 1; 
    unsigned short PADIR_9       : 1; 
    unsigned short PADIR_10      : 1; 
    unsigned short PADIR_11      : 1; 
    unsigned short PADIR_12      : 1; 
    unsigned short PADIR_13      : 1; 
    unsigned short PADIR_14      : 1; 
    unsigned short PADIR_15      : 1; 
  } PADIR_bit;  
} @ 0x0204;


enum {
  PADIR_0             = 0x0001,
  PADIR_1             = 0x0002,
  PADIR_2             = 0x0004,
  PADIR_3             = 0x0008,
  PADIR_4             = 0x0010,
  PADIR_5             = 0x0020,
  PADIR_6             = 0x0040,
  PADIR_7             = 0x0080,
  PADIR_8             = 0x0100,
  PADIR_9             = 0x0200,
  PADIR_10            = 0x0400,
  PADIR_11            = 0x0800,
  PADIR_12            = 0x1000,
  PADIR_13            = 0x2000,
  PADIR_14            = 0x4000,
  PADIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PAREN;  /* Port A Resistor Enable */ 
  
  struct
  {
    unsigned short PAREN_0       : 1; 
    unsigned short PAREN_1       : 1; 
    unsigned short PAREN_2       : 1; 
    unsigned short PAREN_3       : 1; 
    unsigned short PAREN_4       : 1; 
    unsigned short PAREN_5       : 1; 
    unsigned short PAREN_6       : 1; 
    unsigned short PAREN_7       : 1; 
    unsigned short PAREN_8       : 1; 
    unsigned short PAREN_9       : 1; 
    unsigned short PAREN_10      : 1; 
    unsigned short PAREN_11      : 1; 
    unsigned short PAREN_12      : 1; 
    unsigned short PAREN_13      : 1; 
    unsigned short PAREN_14      : 1; 
    unsigned short PAREN_15      : 1; 
  } PAREN_bit;  
} @ 0x0206;


enum {
  PAREN_0             = 0x0001,
  PAREN_1             = 0x0002,
  PAREN_2             = 0x0004,
  PAREN_3             = 0x0008,
  PAREN_4             = 0x0010,
  PAREN_5             = 0x0020,
  PAREN_6             = 0x0040,
  PAREN_7             = 0x0080,
  PAREN_8             = 0x0100,
  PAREN_9             = 0x0200,
  PAREN_10            = 0x0400,
  PAREN_11            = 0x0800,
  PAREN_12            = 0x1000,
  PAREN_13            = 0x2000,
  PAREN_14            = 0x4000,
  PAREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PADS;  /* Port A Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PADS_0        : 1; 
    unsigned short PADS_1        : 1; 
    unsigned short PADS_2        : 1; 
    unsigned short PADS_3        : 1; 
    unsigned short PADS_4        : 1; 
    unsigned short PADS_5        : 1; 
    unsigned short PADS_6        : 1; 
    unsigned short PADS_7        : 1; 
    unsigned short PADS_8        : 1; 
    unsigned short PADS_9        : 1; 
    unsigned short PADS_10       : 1; 
    unsigned short PADS_11       : 1; 
    unsigned short PADS_12       : 1; 
    unsigned short PADS_13       : 1; 
    unsigned short PADS_14       : 1; 
    unsigned short PADS_15       : 1; 
  } PADS_bit;  
} @ 0x0208;


enum {
  PADS_0              = 0x0001,
  PADS_1              = 0x0002,
  PADS_2              = 0x0004,
  PADS_3              = 0x0008,
  PADS_4              = 0x0010,
  PADS_5              = 0x0020,
  PADS_6              = 0x0040,
  PADS_7              = 0x0080,
  PADS_8              = 0x0100,
  PADS_9              = 0x0200,
  PADS_10             = 0x0400,
  PADS_11             = 0x0800,
  PADS_12             = 0x1000,
  PADS_13             = 0x2000,
  PADS_14             = 0x4000,
  PADS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PASEL;  /* Port A Selection */ 
  
  struct
  {
    unsigned short PASEL_0       : 1; 
    unsigned short PASEL_1       : 1; 
    unsigned short PASEL_2       : 1; 
    unsigned short PASEL_3       : 1; 
    unsigned short PASEL_4       : 1; 
    unsigned short PASEL_5       : 1; 
    unsigned short PASEL_6       : 1; 
    unsigned short PASEL_7       : 1; 
    unsigned short PASEL_8       : 1; 
    unsigned short PASEL_9       : 1; 
    unsigned short PASEL_10      : 1; 
    unsigned short PASEL_11      : 1; 
    unsigned short PASEL_12      : 1; 
    unsigned short PASEL_13      : 1; 
    unsigned short PASEL_14      : 1; 
    unsigned short PASEL_15      : 1; 
  } PASEL_bit;  
} @ 0x020A;


enum {
  PASEL_0             = 0x0001,
  PASEL_1             = 0x0002,
  PASEL_2             = 0x0004,
  PASEL_3             = 0x0008,
  PASEL_4             = 0x0010,
  PASEL_5             = 0x0020,
  PASEL_6             = 0x0040,
  PASEL_7             = 0x0080,
  PASEL_8             = 0x0100,
  PASEL_9             = 0x0200,
  PASEL_10            = 0x0400,
  PASEL_11            = 0x0800,
  PASEL_12            = 0x1000,
  PASEL_13            = 0x2000,
  PASEL_14            = 0x4000,
  PASEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PAIES;  /* Port A Interrupt Edge Select */ 
  
  struct
  {
    unsigned short PAIES_0       : 1; 
    unsigned short PAIES_1       : 1; 
    unsigned short PAIES_2       : 1; 
    unsigned short PAIES_3       : 1; 
    unsigned short PAIES_4       : 1; 
    unsigned short PAIES_5       : 1; 
    unsigned short PAIES_6       : 1; 
    unsigned short PAIES_7       : 1; 
    unsigned short PAIES_8       : 1; 
    unsigned short PAIES_9       : 1; 
    unsigned short PAIES_10      : 1; 
    unsigned short PAIES_11      : 1; 
    unsigned short PAIES_12      : 1; 
    unsigned short PAIES_13      : 1; 
    unsigned short PAIES_14      : 1; 
    unsigned short PAIES_15      : 1; 
  } PAIES_bit;  
} @ 0x0218;


enum {
  PAIES_0             = 0x0001,
  PAIES_1             = 0x0002,
  PAIES_2             = 0x0004,
  PAIES_3             = 0x0008,
  PAIES_4             = 0x0010,
  PAIES_5             = 0x0020,
  PAIES_6             = 0x0040,
  PAIES_7             = 0x0080,
  PAIES_8             = 0x0100,
  PAIES_9             = 0x0200,
  PAIES_10            = 0x0400,
  PAIES_11            = 0x0800,
  PAIES_12            = 0x1000,
  PAIES_13            = 0x2000,
  PAIES_14            = 0x4000,
  PAIES_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PAIE;  /* Port A Interrupt Enable */ 
  
  struct
  {
    unsigned short PAIE_0        : 1; 
    unsigned short PAIE_1        : 1; 
    unsigned short PAIE_2        : 1; 
    unsigned short PAIE_3        : 1; 
    unsigned short PAIE_4        : 1; 
    unsigned short PAIE_5        : 1; 
    unsigned short PAIE_6        : 1; 
    unsigned short PAIE_7        : 1; 
    unsigned short PAIE_8        : 1; 
    unsigned short PAIE_9        : 1; 
    unsigned short PAIE_10       : 1; 
    unsigned short PAIE_11       : 1; 
    unsigned short PAIE_12       : 1; 
    unsigned short PAIE_13       : 1; 
    unsigned short PAIE_14       : 1; 
    unsigned short PAIE_15       : 1; 
  } PAIE_bit;  
} @ 0x021A;


enum {
  PAIE_0              = 0x0001,
  PAIE_1              = 0x0002,
  PAIE_2              = 0x0004,
  PAIE_3              = 0x0008,
  PAIE_4              = 0x0010,
  PAIE_5              = 0x0020,
  PAIE_6              = 0x0040,
  PAIE_7              = 0x0080,
  PAIE_8              = 0x0100,
  PAIE_9              = 0x0200,
  PAIE_10             = 0x0400,
  PAIE_11             = 0x0800,
  PAIE_12             = 0x1000,
  PAIE_13             = 0x2000,
  PAIE_14             = 0x4000,
  PAIE_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PAIFG;  /* Port A Interrupt Flag */ 
  
  struct
  {
    unsigned short PAIFG_0       : 1; 
    unsigned short PAIFG_1       : 1; 
    unsigned short PAIFG_2       : 1; 
    unsigned short PAIFG_3       : 1; 
    unsigned short PAIFG_4       : 1; 
    unsigned short PAIFG_5       : 1; 
    unsigned short PAIFG_6       : 1; 
    unsigned short PAIFG_7       : 1; 
    unsigned short PAIFG_8       : 1; 
    unsigned short PAIFG_9       : 1; 
    unsigned short PAIFG_10      : 1; 
    unsigned short PAIFG_11      : 1; 
    unsigned short PAIFG_12      : 1; 
    unsigned short PAIFG_13      : 1; 
    unsigned short PAIFG_14      : 1; 
    unsigned short PAIFG_15      : 1; 
  } PAIFG_bit;  
} @ 0x021C;


enum {
  PAIFG_0             = 0x0001,
  PAIFG_1             = 0x0002,
  PAIFG_2             = 0x0004,
  PAIFG_3             = 0x0008,
  PAIFG_4             = 0x0010,
  PAIFG_5             = 0x0020,
  PAIFG_6             = 0x0040,
  PAIFG_7             = 0x0080,
  PAIFG_8             = 0x0100,
  PAIFG_9             = 0x0200,
  PAIFG_10            = 0x0400,
  PAIFG_11            = 0x0800,
  PAIFG_12            = 0x1000,
  PAIFG_13            = 0x2000,
  PAIFG_14            = 0x4000,
  PAIFG_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P1IN;  /* Port 1 Input */ 
  
  struct
  {
    unsigned char P1IN_0         : 1; 
    unsigned char P1IN_1         : 1; 
    unsigned char P1IN_2         : 1; 
    unsigned char P1IN_3         : 1; 
    unsigned char P1IN_4         : 1; 
    unsigned char P1IN_5         : 1; 
    unsigned char P1IN_6         : 1; 
    unsigned char P1IN_7         : 1; 
  } P1IN_bit;  
} @ 0x0200;




__no_init volatile union
{
  unsigned char P1OUT;  /* Port 1 Output */ 
  
  struct
  {
    unsigned char P1OUT_0        : 1; 
    unsigned char P1OUT_1        : 1; 
    unsigned char P1OUT_2        : 1; 
    unsigned char P1OUT_3        : 1; 
    unsigned char P1OUT_4        : 1; 
    unsigned char P1OUT_5        : 1; 
    unsigned char P1OUT_6        : 1; 
    unsigned char P1OUT_7        : 1; 
  } P1OUT_bit;  
} @ 0x0202;


enum {
  P1OUT_0             = 0x0001,
  P1OUT_1             = 0x0002,
  P1OUT_2             = 0x0004,
  P1OUT_3             = 0x0008,
  P1OUT_4             = 0x0010,
  P1OUT_5             = 0x0020,
  P1OUT_6             = 0x0040,
  P1OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P1DIR;  /* Port 1 Direction */ 
  
  struct
  {
    unsigned char P1DIR_0        : 1; 
    unsigned char P1DIR_1        : 1; 
    unsigned char P1DIR_2        : 1; 
    unsigned char P1DIR_3        : 1; 
    unsigned char P1DIR_4        : 1; 
    unsigned char P1DIR_5        : 1; 
    unsigned char P1DIR_6        : 1; 
    unsigned char P1DIR_7        : 1; 
  } P1DIR_bit;  
} @ 0x0204;


enum {
  P1DIR_0             = 0x0001,
  P1DIR_1             = 0x0002,
  P1DIR_2             = 0x0004,
  P1DIR_3             = 0x0008,
  P1DIR_4             = 0x0010,
  P1DIR_5             = 0x0020,
  P1DIR_6             = 0x0040,
  P1DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P1REN;  /* Port 1 Resistor Enable */ 
  
  struct
  {
    unsigned char P1REN_0        : 1; 
    unsigned char P1REN_1        : 1; 
    unsigned char P1REN_2        : 1; 
    unsigned char P1REN_3        : 1; 
    unsigned char P1REN_4        : 1; 
    unsigned char P1REN_5        : 1; 
    unsigned char P1REN_6        : 1; 
    unsigned char P1REN_7        : 1; 
  } P1REN_bit;  
} @ 0x0206;


enum {
  P1REN_0             = 0x0001,
  P1REN_1             = 0x0002,
  P1REN_2             = 0x0004,
  P1REN_3             = 0x0008,
  P1REN_4             = 0x0010,
  P1REN_5             = 0x0020,
  P1REN_6             = 0x0040,
  P1REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P1DS;  /* Port 1 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P1DS_0         : 1; 
    unsigned char P1DS_1         : 1; 
    unsigned char P1DS_2         : 1; 
    unsigned char P1DS_3         : 1; 
    unsigned char P1DS_4         : 1; 
    unsigned char P1DS_5         : 1; 
    unsigned char P1DS_6         : 1; 
    unsigned char P1DS_7         : 1; 
  } P1DS_bit;  
} @ 0x0208;


enum {
  P1DS_0              = 0x0001,
  P1DS_1              = 0x0002,
  P1DS_2              = 0x0004,
  P1DS_3              = 0x0008,
  P1DS_4              = 0x0010,
  P1DS_5              = 0x0020,
  P1DS_6              = 0x0040,
  P1DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P1SEL;  /* Port 1 Selection */ 
  
  struct
  {
    unsigned char P1SEL_0        : 1; 
    unsigned char P1SEL_1        : 1; 
    unsigned char P1SEL_2        : 1; 
    unsigned char P1SEL_3        : 1; 
    unsigned char P1SEL_4        : 1; 
    unsigned char P1SEL_5        : 1; 
    unsigned char P1SEL_6        : 1; 
    unsigned char P1SEL_7        : 1; 
  } P1SEL_bit;  
} @ 0x020A;


enum {
  P1SEL_0             = 0x0001,
  P1SEL_1             = 0x0002,
  P1SEL_2             = 0x0004,
  P1SEL_3             = 0x0008,
  P1SEL_4             = 0x0010,
  P1SEL_5             = 0x0020,
  P1SEL_6             = 0x0040,
  P1SEL_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P1IES;  /* Port 1 Interrupt Edge Select */ 
  
  struct
  {
    unsigned char P1IES_0        : 1; 
    unsigned char P1IES_1        : 1; 
    unsigned char P1IES_2        : 1; 
    unsigned char P1IES_3        : 1; 
    unsigned char P1IES_4        : 1; 
    unsigned char P1IES_5        : 1; 
    unsigned char P1IES_6        : 1; 
    unsigned char P1IES_7        : 1; 
  } P1IES_bit;  
} @ 0x0218;


enum {
  P1IES_0             = 0x0001,
  P1IES_1             = 0x0002,
  P1IES_2             = 0x0004,
  P1IES_3             = 0x0008,
  P1IES_4             = 0x0010,
  P1IES_5             = 0x0020,
  P1IES_6             = 0x0040,
  P1IES_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P1IE;  /* Port 1 Interrupt Enable */ 
  
  struct
  {
    unsigned char P1IE_0         : 1; 
    unsigned char P1IE_1         : 1; 
    unsigned char P1IE_2         : 1; 
    unsigned char P1IE_3         : 1; 
    unsigned char P1IE_4         : 1; 
    unsigned char P1IE_5         : 1; 
    unsigned char P1IE_6         : 1; 
    unsigned char P1IE_7         : 1; 
  } P1IE_bit;  
} @ 0x021A;


enum {
  P1IE_0              = 0x0001,
  P1IE_1              = 0x0002,
  P1IE_2              = 0x0004,
  P1IE_3              = 0x0008,
  P1IE_4              = 0x0010,
  P1IE_5              = 0x0020,
  P1IE_6              = 0x0040,
  P1IE_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P1IFG;  /* Port 1 Interrupt Flag */ 
  
  struct
  {
    unsigned char P1IFG_0        : 1; 
    unsigned char P1IFG_1        : 1; 
    unsigned char P1IFG_2        : 1; 
    unsigned char P1IFG_3        : 1; 
    unsigned char P1IFG_4        : 1; 
    unsigned char P1IFG_5        : 1; 
    unsigned char P1IFG_6        : 1; 
    unsigned char P1IFG_7        : 1; 
  } P1IFG_bit;  
} @ 0x021C;


enum {
  P1IFG_0             = 0x0001,
  P1IFG_1             = 0x0002,
  P1IFG_2             = 0x0004,
  P1IFG_3             = 0x0008,
  P1IFG_4             = 0x0010,
  P1IFG_5             = 0x0020,
  P1IFG_6             = 0x0040,
  P1IFG_7             = 0x0080,
};


 /* Port 1 Interrupt Vector Word */ 
__no_init volatile unsigned short P1IV @ 0x020E;  
 

__no_init volatile union
{
  unsigned char P2IN;  /* Port 2 Input */ 
  
  struct
  {
    unsigned char P2IN_0         : 1; 
    unsigned char P2IN_1         : 1; 
    unsigned char P2IN_2         : 1; 
    unsigned char P2IN_3         : 1; 
    unsigned char P2IN_4         : 1; 
    unsigned char P2IN_5         : 1; 
    unsigned char P2IN_6         : 1; 
    unsigned char P2IN_7         : 1; 
  } P2IN_bit;  
} @ 0x0201;


enum {
  P2IN_0              = 0x0001,
  P2IN_1              = 0x0002,
  P2IN_2              = 0x0004,
  P2IN_3              = 0x0008,
  P2IN_4              = 0x0010,
  P2IN_5              = 0x0020,
  P2IN_6              = 0x0040,
  P2IN_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P2OUT;  /* Port 2 Output */ 
  
  struct
  {
    unsigned char P2OUT_0        : 1; 
    unsigned char P2OUT_1        : 1; 
    unsigned char P2OUT_2        : 1; 
    unsigned char P2OUT_3        : 1; 
    unsigned char P2OUT_4        : 1; 
    unsigned char P2OUT_5        : 1; 
    unsigned char P2OUT_6        : 1; 
    unsigned char P2OUT_7        : 1; 
  } P2OUT_bit;  
} @ 0x0203;


enum {
  P2OUT_0             = 0x0001,
  P2OUT_1             = 0x0002,
  P2OUT_2             = 0x0004,
  P2OUT_3             = 0x0008,
  P2OUT_4             = 0x0010,
  P2OUT_5             = 0x0020,
  P2OUT_6             = 0x0040,
  P2OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P2DIR;  /* Port 2 Direction */ 
  
  struct
  {
    unsigned char P2DIR_0        : 1; 
    unsigned char P2DIR_1        : 1; 
    unsigned char P2DIR_2        : 1; 
    unsigned char P2DIR_3        : 1; 
    unsigned char P2DIR_4        : 1; 
    unsigned char P2DIR_5        : 1; 
    unsigned char P2DIR_6        : 1; 
    unsigned char P2DIR_7        : 1; 
  } P2DIR_bit;  
} @ 0x0205;


enum {
  P2DIR_0             = 0x0001,
  P2DIR_1             = 0x0002,
  P2DIR_2             = 0x0004,
  P2DIR_3             = 0x0008,
  P2DIR_4             = 0x0010,
  P2DIR_5             = 0x0020,
  P2DIR_6             = 0x0040,
  P2DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P2REN;  /* Port 2 Resistor Enable */ 
  
  struct
  {
    unsigned char P2REN_0        : 1; 
    unsigned char P2REN_1        : 1; 
    unsigned char P2REN_2        : 1; 
    unsigned char P2REN_3        : 1; 
    unsigned char P2REN_4        : 1; 
    unsigned char P2REN_5        : 1; 
    unsigned char P2REN_6        : 1; 
    unsigned char P2REN_7        : 1; 
  } P2REN_bit;  
} @ 0x0207;


enum {
  P2REN_0             = 0x0001,
  P2REN_1             = 0x0002,
  P2REN_2             = 0x0004,
  P2REN_3             = 0x0008,
  P2REN_4             = 0x0010,
  P2REN_5             = 0x0020,
  P2REN_6             = 0x0040,
  P2REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P2DS;  /* Port 2 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P2DS_0         : 1; 
    unsigned char P2DS_1         : 1; 
    unsigned char P2DS_2         : 1; 
    unsigned char P2DS_3         : 1; 
    unsigned char P2DS_4         : 1; 
    unsigned char P2DS_5         : 1; 
    unsigned char P2DS_6         : 1; 
    unsigned char P2DS_7         : 1; 
  } P2DS_bit;  
} @ 0x0209;


enum {
  P2DS_0              = 0x0001,
  P2DS_1              = 0x0002,
  P2DS_2              = 0x0004,
  P2DS_3              = 0x0008,
  P2DS_4              = 0x0010,
  P2DS_5              = 0x0020,
  P2DS_6              = 0x0040,
  P2DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P2SEL;  /* Port 2 Selection */ 
  
  struct
  {
    unsigned char P2SEL_0        : 1; 
    unsigned char P2SEL_1        : 1; 
    unsigned char P2SEL_2        : 1; 
    unsigned char P2SEL_3        : 1; 
    unsigned char P2SEL_4        : 1; 
    unsigned char P2SEL_5        : 1; 
    unsigned char P2SEL_6        : 1; 
    unsigned char P2SEL_7        : 1; 
  } P2SEL_bit;  
} @ 0x020B;


enum {
  P2SEL_0             = 0x0001,
  P2SEL_1             = 0x0002,
  P2SEL_2             = 0x0004,
  P2SEL_3             = 0x0008,
  P2SEL_4             = 0x0010,
  P2SEL_5             = 0x0020,
  P2SEL_6             = 0x0040,
  P2SEL_7             = 0x0080,
};


 /* Port 2 Interrupt Vector Word */ 
__no_init volatile unsigned short P2IV @ 0x021E;  
 

__no_init volatile union
{
  unsigned char P2IES;  /* Port 2 Interrupt Edge Select */ 
  
  struct
  {
    unsigned char P2IES_0        : 1; 
    unsigned char P2IES_1        : 1; 
    unsigned char P2IES_2        : 1; 
    unsigned char P2IES_3        : 1; 
    unsigned char P2IES_4        : 1; 
    unsigned char P2IES_5        : 1; 
    unsigned char P2IES_6        : 1; 
    unsigned char P2IES_7        : 1; 
  } P2IES_bit;  
} @ 0x0219;


enum {
  P2IES_0             = 0x0001,
  P2IES_1             = 0x0002,
  P2IES_2             = 0x0004,
  P2IES_3             = 0x0008,
  P2IES_4             = 0x0010,
  P2IES_5             = 0x0020,
  P2IES_6             = 0x0040,
  P2IES_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P2IE;  /* Port 2 Interrupt Enable  */ 
  
  struct
  {
    unsigned char P2IE_0         : 1; 
    unsigned char P2IE_1         : 1; 
    unsigned char P2IE_2         : 1; 
    unsigned char P2IE_3         : 1; 
    unsigned char P2IE_4         : 1; 
    unsigned char P2IE_5         : 1; 
    unsigned char P2IE_6         : 1; 
    unsigned char P2IE_7         : 1; 
  } P2IE_bit;  
} @ 0x021B;


enum {
  P2IE_0              = 0x0001,
  P2IE_1              = 0x0002,
  P2IE_2              = 0x0004,
  P2IE_3              = 0x0008,
  P2IE_4              = 0x0010,
  P2IE_5              = 0x0020,
  P2IE_6              = 0x0040,
  P2IE_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P2IFG;  /* Port 2 Interrupt Flag */ 
  
  struct
  {
    unsigned char P2IFG_0        : 1; 
    unsigned char P2IFG_1        : 1; 
    unsigned char P2IFG_2        : 1; 
    unsigned char P2IFG_3        : 1; 
    unsigned char P2IFG_4        : 1; 
    unsigned char P2IFG_5        : 1; 
    unsigned char P2IFG_6        : 1; 
    unsigned char P2IFG_7        : 1; 
  } P2IFG_bit;  
} @ 0x021D;


enum {
  P2IFG_0             = 0x0001,
  P2IFG_1             = 0x0002,
  P2IFG_2             = 0x0004,
  P2IFG_3             = 0x0008,
  P2IFG_4             = 0x0010,
  P2IFG_5             = 0x0020,
  P2IFG_6             = 0x0040,
  P2IFG_7             = 0x0080,
};

 
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port3/4 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port B In */ 
__no_init volatile unsigned __READ short PBIN @ 0x0220;  
 

__no_init volatile union
{
  unsigned short PBOUT;  /* Port B Output */ 
  
  struct
  {
    unsigned short PBOUT_0       : 1; 
    unsigned short PBOUT_1       : 1; 
    unsigned short PBOUT_2       : 1; 
    unsigned short PBOUT_3       : 1; 
    unsigned short PBOUT_4       : 1; 
    unsigned short PBOUT_5       : 1; 
    unsigned short PBOUT_6       : 1; 
    unsigned short PBOUT_7       : 1; 
    unsigned short PBOUT_8       : 1; 
    unsigned short PBOUT_9       : 1; 
    unsigned short PBOUT_10      : 1; 
    unsigned short PBOUT_11      : 1; 
    unsigned short PBOUT_12      : 1; 
    unsigned short PBOUT_13      : 1; 
    unsigned short PBOUT_14      : 1; 
    unsigned short PBOUT_15      : 1; 
  } PBOUT_bit;  
} @ 0x0222;


enum {
  PBOUT_0             = 0x0001,
  PBOUT_1             = 0x0002,
  PBOUT_2             = 0x0004,
  PBOUT_3             = 0x0008,
  PBOUT_4             = 0x0010,
  PBOUT_5             = 0x0020,
  PBOUT_6             = 0x0040,
  PBOUT_7             = 0x0080,
  PBOUT_8             = 0x0100,
  PBOUT_9             = 0x0200,
  PBOUT_10            = 0x0400,
  PBOUT_11            = 0x0800,
  PBOUT_12            = 0x1000,
  PBOUT_13            = 0x2000,
  PBOUT_14            = 0x4000,
  PBOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PBDIR;  /* Port B Direction */ 
  
  struct
  {
    unsigned short PBDIR_0       : 1; 
    unsigned short PBDIR_1       : 1; 
    unsigned short PBDIR_2       : 1; 
    unsigned short PBDIR_3       : 1; 
    unsigned short PBDIR_4       : 1; 
    unsigned short PBDIR_5       : 1; 
    unsigned short PBDIR_6       : 1; 
    unsigned short PBDIR_7       : 1; 
    unsigned short PBDIR_8       : 1; 
    unsigned short PBDIR_9       : 1; 
    unsigned short PBDIR_10      : 1; 
    unsigned short PBDIR_11      : 1; 
    unsigned short PBDIR_12      : 1; 
    unsigned short PBDIR_13      : 1; 
    unsigned short PBDIR_14      : 1; 
    unsigned short PBDIR_15      : 1; 
  } PBDIR_bit;  
} @ 0x0224;


enum {
  PBDIR_0             = 0x0001,
  PBDIR_1             = 0x0002,
  PBDIR_2             = 0x0004,
  PBDIR_3             = 0x0008,
  PBDIR_4             = 0x0010,
  PBDIR_5             = 0x0020,
  PBDIR_6             = 0x0040,
  PBDIR_7             = 0x0080,
  PBDIR_8             = 0x0100,
  PBDIR_9             = 0x0200,
  PBDIR_10            = 0x0400,
  PBDIR_11            = 0x0800,
  PBDIR_12            = 0x1000,
  PBDIR_13            = 0x2000,
  PBDIR_14            = 0x4000,
  PBDIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PBREN;  /* Port B Resistor Enable */ 
  
  struct
  {
    unsigned short PBREN_0       : 1; 
    unsigned short PBREN_1       : 1; 
    unsigned short PBREN_2       : 1; 
    unsigned short PBREN_3       : 1; 
    unsigned short PBREN_4       : 1; 
    unsigned short PBREN_5       : 1; 
    unsigned short PBREN_6       : 1; 
    unsigned short PBREN_7       : 1; 
    unsigned short PBREN_8       : 1; 
    unsigned short PBREN_9       : 1; 
    unsigned short PBREN_10      : 1; 
    unsigned short PBREN_11      : 1; 
    unsigned short PBREN_12      : 1; 
    unsigned short PBREN_13      : 1; 
    unsigned short PBREN_14      : 1; 
    unsigned short PBREN_15      : 1; 
  } PBREN_bit;  
} @ 0x0226;


enum {
  PBREN_0             = 0x0001,
  PBREN_1             = 0x0002,
  PBREN_2             = 0x0004,
  PBREN_3             = 0x0008,
  PBREN_4             = 0x0010,
  PBREN_5             = 0x0020,
  PBREN_6             = 0x0040,
  PBREN_7             = 0x0080,
  PBREN_8             = 0x0100,
  PBREN_9             = 0x0200,
  PBREN_10            = 0x0400,
  PBREN_11            = 0x0800,
  PBREN_12            = 0x1000,
  PBREN_13            = 0x2000,
  PBREN_14            = 0x4000,
  PBREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PBDS;  /* Port B Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PBDS_0        : 1; 
    unsigned short PBDS_1        : 1; 
    unsigned short PBDS_2        : 1; 
    unsigned short PBDS_3        : 1; 
    unsigned short PBDS_4        : 1; 
    unsigned short PBDS_5        : 1; 
    unsigned short PBDS_6        : 1; 
    unsigned short PBDS_7        : 1; 
    unsigned short PBDS_8        : 1; 
    unsigned short PBDS_9        : 1; 
    unsigned short PBDS_10       : 1; 
    unsigned short PBDS_11       : 1; 
    unsigned short PBDS_12       : 1; 
    unsigned short PBDS_13       : 1; 
    unsigned short PBDS_14       : 1; 
    unsigned short PBDS_15       : 1; 
  } PBDS_bit;  
} @ 0x0228;


enum {
  PBDS_0              = 0x0001,
  PBDS_1              = 0x0002,
  PBDS_2              = 0x0004,
  PBDS_3              = 0x0008,
  PBDS_4              = 0x0010,
  PBDS_5              = 0x0020,
  PBDS_6              = 0x0040,
  PBDS_7              = 0x0080,
  PBDS_8              = 0x0100,
  PBDS_9              = 0x0200,
  PBDS_10             = 0x0400,
  PBDS_11             = 0x0800,
  PBDS_12             = 0x1000,
  PBDS_13             = 0x2000,
  PBDS_14             = 0x4000,
  PBDS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PBSEL;  /* Port B Selection */ 
  
  struct
  {
    unsigned short PBSEL_0       : 1; 
    unsigned short PBSEL_1       : 1; 
    unsigned short PBSEL_2       : 1; 
    unsigned short PBSEL_3       : 1; 
    unsigned short PBSEL_4       : 1; 
    unsigned short PBSEL_5       : 1; 
    unsigned short PBSEL_6       : 1; 
    unsigned short PBSEL_7       : 1; 
    unsigned short PBSEL_8       : 1; 
    unsigned short PBSEL_9       : 1; 
    unsigned short PBSEL_10      : 1; 
    unsigned short PBSEL_11      : 1; 
    unsigned short PBSEL_12      : 1; 
    unsigned short PBSEL_13      : 1; 
    unsigned short PBSEL_14      : 1; 
    unsigned short PBSEL_15      : 1; 
  } PBSEL_bit;  
} @ 0x022A;


enum {
  PBSEL_0             = 0x0001,
  PBSEL_1             = 0x0002,
  PBSEL_2             = 0x0004,
  PBSEL_3             = 0x0008,
  PBSEL_4             = 0x0010,
  PBSEL_5             = 0x0020,
  PBSEL_6             = 0x0040,
  PBSEL_7             = 0x0080,
  PBSEL_8             = 0x0100,
  PBSEL_9             = 0x0200,
  PBSEL_10            = 0x0400,
  PBSEL_11            = 0x0800,
  PBSEL_12            = 0x1000,
  PBSEL_13            = 0x2000,
  PBSEL_14            = 0x4000,
  PBSEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P3IN;  /* Port 3 Input */ 
  
  struct
  {
    unsigned char P3IN_0         : 1; 
    unsigned char P3IN_1         : 1; 
    unsigned char P3IN_2         : 1; 
    unsigned char P3IN_3         : 1; 
    unsigned char P3IN_4         : 1; 
    unsigned char P3IN_5         : 1; 
    unsigned char P3IN_6         : 1; 
    unsigned char P3IN_7         : 1; 
  } P3IN_bit;  
} @ 0x0220;




__no_init volatile union
{
  unsigned char P3OUT;  /* Port 3 Output */ 
  
  struct
  {
    unsigned char P3OUT_0        : 1; 
    unsigned char P3OUT_1        : 1; 
    unsigned char P3OUT_2        : 1; 
    unsigned char P3OUT_3        : 1; 
    unsigned char P3OUT_4        : 1; 
    unsigned char P3OUT_5        : 1; 
    unsigned char P3OUT_6        : 1; 
    unsigned char P3OUT_7        : 1; 
  } P3OUT_bit;  
} @ 0x0222;


enum {
  P3OUT_0             = 0x0001,
  P3OUT_1             = 0x0002,
  P3OUT_2             = 0x0004,
  P3OUT_3             = 0x0008,
  P3OUT_4             = 0x0010,
  P3OUT_5             = 0x0020,
  P3OUT_6             = 0x0040,
  P3OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P3DIR;  /* Port 3 Direction */ 
  
  struct
  {
    unsigned char P3DIR_0        : 1; 
    unsigned char P3DIR_1        : 1; 
    unsigned char P3DIR_2        : 1; 
    unsigned char P3DIR_3        : 1; 
    unsigned char P3DIR_4        : 1; 
    unsigned char P3DIR_5        : 1; 
    unsigned char P3DIR_6        : 1; 
    unsigned char P3DIR_7        : 1; 
  } P3DIR_bit;  
} @ 0x0224;


enum {
  P3DIR_0             = 0x0001,
  P3DIR_1             = 0x0002,
  P3DIR_2             = 0x0004,
  P3DIR_3             = 0x0008,
  P3DIR_4             = 0x0010,
  P3DIR_5             = 0x0020,
  P3DIR_6             = 0x0040,
  P3DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P3REN;  /* Port 3 Resistor Enable */ 
  
  struct
  {
    unsigned char P3REN_0        : 1; 
    unsigned char P3REN_1        : 1; 
    unsigned char P3REN_2        : 1; 
    unsigned char P3REN_3        : 1; 
    unsigned char P3REN_4        : 1; 
    unsigned char P3REN_5        : 1; 
    unsigned char P3REN_6        : 1; 
    unsigned char P3REN_7        : 1; 
  } P3REN_bit;  
} @ 0x0226;


enum {
  P3REN_0             = 0x0001,
  P3REN_1             = 0x0002,
  P3REN_2             = 0x0004,
  P3REN_3             = 0x0008,
  P3REN_4             = 0x0010,
  P3REN_5             = 0x0020,
  P3REN_6             = 0x0040,
  P3REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P3DS;  /* Port 3 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P3DS_0         : 1; 
    unsigned char P3DS_1         : 1; 
    unsigned char P3DS_2         : 1; 
    unsigned char P3DS_3         : 1; 
    unsigned char P3DS_4         : 1; 
    unsigned char P3DS_5         : 1; 
    unsigned char P3DS_6         : 1; 
    unsigned char P3DS_7         : 1; 
  } P3DS_bit;  
} @ 0x0228;


enum {
  P3DS_0              = 0x0001,
  P3DS_1              = 0x0002,
  P3DS_2              = 0x0004,
  P3DS_3              = 0x0008,
  P3DS_4              = 0x0010,
  P3DS_5              = 0x0020,
  P3DS_6              = 0x0040,
  P3DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P3SEL;  /* Port 3 Selection */ 
  
  struct
  {
    unsigned char P3SEL_0        : 1; 
    unsigned char P3SEL_1        : 1; 
    unsigned char P3SEL_2        : 1; 
    unsigned char P3SEL_3        : 1; 
    unsigned char P3SEL_4        : 1; 
    unsigned char P3SEL_5        : 1; 
    unsigned char P3SEL_6        : 1; 
    unsigned char P3SEL_7        : 1; 
  } P3SEL_bit;  
} @ 0x022A;


enum {
  P3SEL_0             = 0x0001,
  P3SEL_1             = 0x0002,
  P3SEL_2             = 0x0004,
  P3SEL_3             = 0x0008,
  P3SEL_4             = 0x0010,
  P3SEL_5             = 0x0020,
  P3SEL_6             = 0x0040,
  P3SEL_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P4IN;  /* Port 4 Input */ 
  
  struct
  {
    unsigned char P4IN_0         : 1; 
    unsigned char P4IN_1         : 1; 
    unsigned char P4IN_2         : 1; 
    unsigned char P4IN_3         : 1; 
    unsigned char P4IN_4         : 1; 
    unsigned char P4IN_5         : 1; 
    unsigned char P4IN_6         : 1; 
    unsigned char P4IN_7         : 1; 
  } P4IN_bit;  
} @ 0x0221;


enum {
  P4IN_0              = 0x0001,
  P4IN_1              = 0x0002,
  P4IN_2              = 0x0004,
  P4IN_3              = 0x0008,
  P4IN_4              = 0x0010,
  P4IN_5              = 0x0020,
  P4IN_6              = 0x0040,
  P4IN_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P4OUT;  /* Port 4 Output */ 
  
  struct
  {
    unsigned char P4OUT_0        : 1; 
    unsigned char P4OUT_1        : 1; 
    unsigned char P4OUT_2        : 1; 
    unsigned char P4OUT_3        : 1; 
    unsigned char P4OUT_4        : 1; 
    unsigned char P4OUT_5        : 1; 
    unsigned char P4OUT_6        : 1; 
    unsigned char P4OUT_7        : 1; 
  } P4OUT_bit;  
} @ 0x0223;


enum {
  P4OUT_0             = 0x0001,
  P4OUT_1             = 0x0002,
  P4OUT_2             = 0x0004,
  P4OUT_3             = 0x0008,
  P4OUT_4             = 0x0010,
  P4OUT_5             = 0x0020,
  P4OUT_6             = 0x0040,
  P4OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P4DIR;  /* Port 4 Direction */ 
  
  struct
  {
    unsigned char P4DIR_0        : 1; 
    unsigned char P4DIR_1        : 1; 
    unsigned char P4DIR_2        : 1; 
    unsigned char P4DIR_3        : 1; 
    unsigned char P4DIR_4        : 1; 
    unsigned char P4DIR_5        : 1; 
    unsigned char P4DIR_6        : 1; 
    unsigned char P4DIR_7        : 1; 
  } P4DIR_bit;  
} @ 0x0225;


enum {
  P4DIR_0             = 0x0001,
  P4DIR_1             = 0x0002,
  P4DIR_2             = 0x0004,
  P4DIR_3             = 0x0008,
  P4DIR_4             = 0x0010,
  P4DIR_5             = 0x0020,
  P4DIR_6             = 0x0040,
  P4DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P4REN;  /* Port 4 Resistor Enable */ 
  
  struct
  {
    unsigned char P4REN_0        : 1; 
    unsigned char P4REN_1        : 1; 
    unsigned char P4REN_2        : 1; 
    unsigned char P4REN_3        : 1; 
    unsigned char P4REN_4        : 1; 
    unsigned char P4REN_5        : 1; 
    unsigned char P4REN_6        : 1; 
    unsigned char P4REN_7        : 1; 
  } P4REN_bit;  
} @ 0x0227;


enum {
  P4REN_0             = 0x0001,
  P4REN_1             = 0x0002,
  P4REN_2             = 0x0004,
  P4REN_3             = 0x0008,
  P4REN_4             = 0x0010,
  P4REN_5             = 0x0020,
  P4REN_6             = 0x0040,
  P4REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P4DS;  /* Port 4 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P4DS_0         : 1; 
    unsigned char P4DS_1         : 1; 
    unsigned char P4DS_2         : 1; 
    unsigned char P4DS_3         : 1; 
    unsigned char P4DS_4         : 1; 
    unsigned char P4DS_5         : 1; 
    unsigned char P4DS_6         : 1; 
    unsigned char P4DS_7         : 1; 
  } P4DS_bit;  
} @ 0x0229;


enum {
  P4DS_0              = 0x0001,
  P4DS_1              = 0x0002,
  P4DS_2              = 0x0004,
  P4DS_3              = 0x0008,
  P4DS_4              = 0x0010,
  P4DS_5              = 0x0020,
  P4DS_6              = 0x0040,
  P4DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P4SEL;  /* Port 4 Selection */ 
  
  struct
  {
    unsigned char P4SEL_0        : 1; 
    unsigned char P4SEL_1        : 1; 
    unsigned char P4SEL_2        : 1; 
    unsigned char P4SEL_3        : 1; 
    unsigned char P4SEL_4        : 1; 
    unsigned char P4SEL_5        : 1; 
    unsigned char P4SEL_6        : 1; 
    unsigned char P4SEL_7        : 1; 
  } P4SEL_bit;  
} @ 0x022B;


enum {
  P4SEL_0             = 0x0001,
  P4SEL_1             = 0x0002,
  P4SEL_2             = 0x0004,
  P4SEL_3             = 0x0008,
  P4SEL_4             = 0x0010,
  P4SEL_5             = 0x0020,
  P4SEL_6             = 0x0040,
  P4SEL_7             = 0x0080,
};

 
#define __MSP430_HAS_PORTB_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT3_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port5/6 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port C In */ 
__no_init volatile unsigned __READ short PCIN @ 0x0240;  
 

__no_init volatile union
{
  unsigned short PCOUT;  /* Port C Output */ 
  
  struct
  {
    unsigned short PCOUT_0       : 1; 
    unsigned short PCOUT_1       : 1; 
    unsigned short PCOUT_2       : 1; 
    unsigned short PCOUT_3       : 1; 
    unsigned short PCOUT_4       : 1; 
    unsigned short PCOUT_5       : 1; 
    unsigned short PCOUT_6       : 1; 
    unsigned short PCOUT_7       : 1; 
    unsigned short PCOUT_8       : 1; 
    unsigned short PCOUT_9       : 1; 
    unsigned short PCOUT_10      : 1; 
    unsigned short PCOUT_11      : 1; 
    unsigned short PCOUT_12      : 1; 
    unsigned short PCOUT_13      : 1; 
    unsigned short PCOUT_14      : 1; 
    unsigned short PCOUT_15      : 1; 
  } PCOUT_bit;  
} @ 0x0242;


enum {
  PCOUT_0             = 0x0001,
  PCOUT_1             = 0x0002,
  PCOUT_2             = 0x0004,
  PCOUT_3             = 0x0008,
  PCOUT_4             = 0x0010,
  PCOUT_5             = 0x0020,
  PCOUT_6             = 0x0040,
  PCOUT_7             = 0x0080,
  PCOUT_8             = 0x0100,
  PCOUT_9             = 0x0200,
  PCOUT_10            = 0x0400,
  PCOUT_11            = 0x0800,
  PCOUT_12            = 0x1000,
  PCOUT_13            = 0x2000,
  PCOUT_14            = 0x4000,
  PCOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PCDIR;  /* Port C Direction */ 
  
  struct
  {
    unsigned short PCDIR_0       : 1; 
    unsigned short PCDIR_1       : 1; 
    unsigned short PCDIR_2       : 1; 
    unsigned short PCDIR_3       : 1; 
    unsigned short PCDIR_4       : 1; 
    unsigned short PCDIR_5       : 1; 
    unsigned short PCDIR_6       : 1; 
    unsigned short PCDIR_7       : 1; 
    unsigned short PCDIR_8       : 1; 
    unsigned short PCDIR_9       : 1; 
    unsigned short PCDIR_10      : 1; 
    unsigned short PCDIR_11      : 1; 
    unsigned short PCDIR_12      : 1; 
    unsigned short PCDIR_13      : 1; 
    unsigned short PCDIR_14      : 1; 
    unsigned short PCDIR_15      : 1; 
  } PCDIR_bit;  
} @ 0x0244;


enum {
  PCDIR_0             = 0x0001,
  PCDIR_1             = 0x0002,
  PCDIR_2             = 0x0004,
  PCDIR_3             = 0x0008,
  PCDIR_4             = 0x0010,
  PCDIR_5             = 0x0020,
  PCDIR_6             = 0x0040,
  PCDIR_7             = 0x0080,
  PCDIR_8             = 0x0100,
  PCDIR_9             = 0x0200,
  PCDIR_10            = 0x0400,
  PCDIR_11            = 0x0800,
  PCDIR_12            = 0x1000,
  PCDIR_13            = 0x2000,
  PCDIR_14            = 0x4000,
  PCDIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PCREN;  /* Port C Resistor Enable */ 
  
  struct
  {
    unsigned short PCREN_0       : 1; 
    unsigned short PCREN_1       : 1; 
    unsigned short PCREN_2       : 1; 
    unsigned short PCREN_3       : 1; 
    unsigned short PCREN_4       : 1; 
    unsigned short PCREN_5       : 1; 
    unsigned short PCREN_6       : 1; 
    unsigned short PCREN_7       : 1; 
    unsigned short PCREN_8       : 1; 
    unsigned short PCREN_9       : 1; 
    unsigned short PCREN_10      : 1; 
    unsigned short PCREN_11      : 1; 
    unsigned short PCREN_12      : 1; 
    unsigned short PCREN_13      : 1; 
    unsigned short PCREN_14      : 1; 
    unsigned short PCREN_15      : 1; 
  } PCREN_bit;  
} @ 0x0246;


enum {
  PCREN_0             = 0x0001,
  PCREN_1             = 0x0002,
  PCREN_2             = 0x0004,
  PCREN_3             = 0x0008,
  PCREN_4             = 0x0010,
  PCREN_5             = 0x0020,
  PCREN_6             = 0x0040,
  PCREN_7             = 0x0080,
  PCREN_8             = 0x0100,
  PCREN_9             = 0x0200,
  PCREN_10            = 0x0400,
  PCREN_11            = 0x0800,
  PCREN_12            = 0x1000,
  PCREN_13            = 0x2000,
  PCREN_14            = 0x4000,
  PCREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PCDS;  /* Port C Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PCDS_0        : 1; 
    unsigned short PCDS_1        : 1; 
    unsigned short PCDS_2        : 1; 
    unsigned short PCDS_3        : 1; 
    unsigned short PCDS_4        : 1; 
    unsigned short PCDS_5        : 1; 
    unsigned short PCDS_6        : 1; 
    unsigned short PCDS_7        : 1; 
    unsigned short PCDS_8        : 1; 
    unsigned short PCDS_9        : 1; 
    unsigned short PCDS_10       : 1; 
    unsigned short PCDS_11       : 1; 
    unsigned short PCDS_12       : 1; 
    unsigned short PCDS_13       : 1; 
    unsigned short PCDS_14       : 1; 
    unsigned short PCDS_15       : 1; 
  } PCDS_bit;  
} @ 0x0248;


enum {
  PCDS_0              = 0x0001,
  PCDS_1              = 0x0002,
  PCDS_2              = 0x0004,
  PCDS_3              = 0x0008,
  PCDS_4              = 0x0010,
  PCDS_5              = 0x0020,
  PCDS_6              = 0x0040,
  PCDS_7              = 0x0080,
  PCDS_8              = 0x0100,
  PCDS_9              = 0x0200,
  PCDS_10             = 0x0400,
  PCDS_11             = 0x0800,
  PCDS_12             = 0x1000,
  PCDS_13             = 0x2000,
  PCDS_14             = 0x4000,
  PCDS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PCSEL;  /* Port C Selection */ 
  
  struct
  {
    unsigned short PCSEL_0       : 1; 
    unsigned short PCSEL_1       : 1; 
    unsigned short PCSEL_2       : 1; 
    unsigned short PCSEL_3       : 1; 
    unsigned short PCSEL_4       : 1; 
    unsigned short PCSEL_5       : 1; 
    unsigned short PCSEL_6       : 1; 
    unsigned short PCSEL_7       : 1; 
    unsigned short PCSEL_8       : 1; 
    unsigned short PCSEL_9       : 1; 
    unsigned short PCSEL_10      : 1; 
    unsigned short PCSEL_11      : 1; 
    unsigned short PCSEL_12      : 1; 
    unsigned short PCSEL_13      : 1; 
    unsigned short PCSEL_14      : 1; 
    unsigned short PCSEL_15      : 1; 
  } PCSEL_bit;  
} @ 0x024A;


enum {
  PCSEL_0             = 0x0001,
  PCSEL_1             = 0x0002,
  PCSEL_2             = 0x0004,
  PCSEL_3             = 0x0008,
  PCSEL_4             = 0x0010,
  PCSEL_5             = 0x0020,
  PCSEL_6             = 0x0040,
  PCSEL_7             = 0x0080,
  PCSEL_8             = 0x0100,
  PCSEL_9             = 0x0200,
  PCSEL_10            = 0x0400,
  PCSEL_11            = 0x0800,
  PCSEL_12            = 0x1000,
  PCSEL_13            = 0x2000,
  PCSEL_14            = 0x4000,
  PCSEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P5IN;  /* Port 5 Input */ 
  
  struct
  {
    unsigned char P5IN_0         : 1; 
    unsigned char P5IN_1         : 1; 
    unsigned char P5IN_2         : 1; 
    unsigned char P5IN_3         : 1; 
    unsigned char P5IN_4         : 1; 
    unsigned char P5IN_5         : 1; 
    unsigned char P5IN_6         : 1; 
    unsigned char P5IN_7         : 1; 
  } P5IN_bit;  
} @ 0x0240;




__no_init volatile union
{
  unsigned char P5OUT;  /* Port 5 Output */ 
  
  struct
  {
    unsigned char P5OUT_0        : 1; 
    unsigned char P5OUT_1        : 1; 
    unsigned char P5OUT_2        : 1; 
    unsigned char P5OUT_3        : 1; 
    unsigned char P5OUT_4        : 1; 
    unsigned char P5OUT_5        : 1; 
    unsigned char P5OUT_6        : 1; 
    unsigned char P5OUT_7        : 1; 
  } P5OUT_bit;  
} @ 0x0242;


enum {
  P5OUT_0             = 0x0001,
  P5OUT_1             = 0x0002,
  P5OUT_2             = 0x0004,
  P5OUT_3             = 0x0008,
  P5OUT_4             = 0x0010,
  P5OUT_5             = 0x0020,
  P5OUT_6             = 0x0040,
  P5OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P5DIR;  /* Port 5 Direction */ 
  
  struct
  {
    unsigned char P5DIR_0        : 1; 
    unsigned char P5DIR_1        : 1; 
    unsigned char P5DIR_2        : 1; 
    unsigned char P5DIR_3        : 1; 
    unsigned char P5DIR_4        : 1; 
    unsigned char P5DIR_5        : 1; 
    unsigned char P5DIR_6        : 1; 
    unsigned char P5DIR_7        : 1; 
  } P5DIR_bit;  
} @ 0x0244;


enum {
  P5DIR_0             = 0x0001,
  P5DIR_1             = 0x0002,
  P5DIR_2             = 0x0004,
  P5DIR_3             = 0x0008,
  P5DIR_4             = 0x0010,
  P5DIR_5             = 0x0020,
  P5DIR_6             = 0x0040,
  P5DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P5REN;  /* Port 5 Resistor Enable */ 
  
  struct
  {
    unsigned char P5REN_0        : 1; 
    unsigned char P5REN_1        : 1; 
    unsigned char P5REN_2        : 1; 
    unsigned char P5REN_3        : 1; 
    unsigned char P5REN_4        : 1; 
    unsigned char P5REN_5        : 1; 
    unsigned char P5REN_6        : 1; 
    unsigned char P5REN_7        : 1; 
  } P5REN_bit;  
} @ 0x0246;


enum {
  P5REN_0             = 0x0001,
  P5REN_1             = 0x0002,
  P5REN_2             = 0x0004,
  P5REN_3             = 0x0008,
  P5REN_4             = 0x0010,
  P5REN_5             = 0x0020,
  P5REN_6             = 0x0040,
  P5REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P5DS;  /* Port 5 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P5DS_0         : 1; 
    unsigned char P5DS_1         : 1; 
    unsigned char P5DS_2         : 1; 
    unsigned char P5DS_3         : 1; 
    unsigned char P5DS_4         : 1; 
    unsigned char P5DS_5         : 1; 
    unsigned char P5DS_6         : 1; 
    unsigned char P5DS_7         : 1; 
  } P5DS_bit;  
} @ 0x0248;


enum {
  P5DS_0              = 0x0001,
  P5DS_1              = 0x0002,
  P5DS_2              = 0x0004,
  P5DS_3              = 0x0008,
  P5DS_4              = 0x0010,
  P5DS_5              = 0x0020,
  P5DS_6              = 0x0040,
  P5DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P5SEL;  /* Port 5 Selection */ 
  
  struct
  {
    unsigned char P5SEL_0        : 1; 
    unsigned char P5SEL_1        : 1; 
    unsigned char P5SEL_2        : 1; 
    unsigned char P5SEL_3        : 1; 
    unsigned char P5SEL_4        : 1; 
    unsigned char P5SEL_5        : 1; 
    unsigned char P5SEL_6        : 1; 
    unsigned char P5SEL_7        : 1; 
  } P5SEL_bit;  
} @ 0x024A;


enum {
  P5SEL_0             = 0x0001,
  P5SEL_1             = 0x0002,
  P5SEL_2             = 0x0004,
  P5SEL_3             = 0x0008,
  P5SEL_4             = 0x0010,
  P5SEL_5             = 0x0020,
  P5SEL_6             = 0x0040,
  P5SEL_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P6IN;  /* Port 6 Input */ 
  
  struct
  {
    unsigned char P6IN_0         : 1; 
    unsigned char P6IN_1         : 1; 
    unsigned char P6IN_2         : 1; 
    unsigned char P6IN_3         : 1; 
    unsigned char P6IN_4         : 1; 
    unsigned char P6IN_5         : 1; 
    unsigned char P6IN_6         : 1; 
    unsigned char P6IN_7         : 1; 
  } P6IN_bit;  
} @ 0x0241;


enum {
  P6IN_0              = 0x0001,
  P6IN_1              = 0x0002,
  P6IN_2              = 0x0004,
  P6IN_3              = 0x0008,
  P6IN_4              = 0x0010,
  P6IN_5              = 0x0020,
  P6IN_6              = 0x0040,
  P6IN_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P6OUT;  /* Port 6 Output */ 
  
  struct
  {
    unsigned char P6OUT_0        : 1; 
    unsigned char P6OUT_1        : 1; 
    unsigned char P6OUT_2        : 1; 
    unsigned char P6OUT_3        : 1; 
    unsigned char P6OUT_4        : 1; 
    unsigned char P6OUT_5        : 1; 
    unsigned char P6OUT_6        : 1; 
    unsigned char P6OUT_7        : 1; 
  } P6OUT_bit;  
} @ 0x0243;


enum {
  P6OUT_0             = 0x0001,
  P6OUT_1             = 0x0002,
  P6OUT_2             = 0x0004,
  P6OUT_3             = 0x0008,
  P6OUT_4             = 0x0010,
  P6OUT_5             = 0x0020,
  P6OUT_6             = 0x0040,
  P6OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P6DIR;  /* Port 6 Direction */ 
  
  struct
  {
    unsigned char P6DIR_0        : 1; 
    unsigned char P6DIR_1        : 1; 
    unsigned char P6DIR_2        : 1; 
    unsigned char P6DIR_3        : 1; 
    unsigned char P6DIR_4        : 1; 
    unsigned char P6DIR_5        : 1; 
    unsigned char P6DIR_6        : 1; 
    unsigned char P6DIR_7        : 1; 
  } P6DIR_bit;  
} @ 0x0245;


enum {
  P6DIR_0             = 0x0001,
  P6DIR_1             = 0x0002,
  P6DIR_2             = 0x0004,
  P6DIR_3             = 0x0008,
  P6DIR_4             = 0x0010,
  P6DIR_5             = 0x0020,
  P6DIR_6             = 0x0040,
  P6DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P6REN;  /* Port 6 Resistor Enable */ 
  
  struct
  {
    unsigned char P6REN_0        : 1; 
    unsigned char P6REN_1        : 1; 
    unsigned char P6REN_2        : 1; 
    unsigned char P6REN_3        : 1; 
    unsigned char P6REN_4        : 1; 
    unsigned char P6REN_5        : 1; 
    unsigned char P6REN_6        : 1; 
    unsigned char P6REN_7        : 1; 
  } P6REN_bit;  
} @ 0x0247;


enum {
  P6REN_0             = 0x0001,
  P6REN_1             = 0x0002,
  P6REN_2             = 0x0004,
  P6REN_3             = 0x0008,
  P6REN_4             = 0x0010,
  P6REN_5             = 0x0020,
  P6REN_6             = 0x0040,
  P6REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P6DS;  /* Port 6 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P6DS_0         : 1; 
    unsigned char P6DS_1         : 1; 
    unsigned char P6DS_2         : 1; 
    unsigned char P6DS_3         : 1; 
    unsigned char P6DS_4         : 1; 
    unsigned char P6DS_5         : 1; 
    unsigned char P6DS_6         : 1; 
    unsigned char P6DS_7         : 1; 
  } P6DS_bit;  
} @ 0x0249;


enum {
  P6DS_0              = 0x0001,
  P6DS_1              = 0x0002,
  P6DS_2              = 0x0004,
  P6DS_3              = 0x0008,
  P6DS_4              = 0x0010,
  P6DS_5              = 0x0020,
  P6DS_6              = 0x0040,
  P6DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P6SEL;  /* Port 6 Selection */ 
  
  struct
  {
    unsigned char P6SEL_0        : 1; 
    unsigned char P6SEL_1        : 1; 
    unsigned char P6SEL_2        : 1; 
    unsigned char P6SEL_3        : 1; 
    unsigned char P6SEL_4        : 1; 
    unsigned char P6SEL_5        : 1; 
    unsigned char P6SEL_6        : 1; 
    unsigned char P6SEL_7        : 1; 
  } P6SEL_bit;  
} @ 0x024B;


enum {
  P6SEL_0             = 0x0001,
  P6SEL_1             = 0x0002,
  P6SEL_2             = 0x0004,
  P6SEL_3             = 0x0008,
  P6SEL_4             = 0x0010,
  P6SEL_5             = 0x0020,
  P6SEL_6             = 0x0040,
  P6SEL_7             = 0x0080,
};

 
#define __MSP430_HAS_PORTC_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT5_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port7/8 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port D In */ 
__no_init volatile unsigned __READ short PDIN @ 0x0260;  
 

__no_init volatile union
{
  unsigned short PDOUT;  /* Port D Output */ 
  
  struct
  {
    unsigned short PDOUT_0       : 1; 
    unsigned short PDOUT_1       : 1; 
    unsigned short PDOUT_2       : 1; 
    unsigned short PDOUT_3       : 1; 
    unsigned short PDOUT_4       : 1; 
    unsigned short PDOUT_5       : 1; 
    unsigned short PDOUT_6       : 1; 
    unsigned short PDOUT_7       : 1; 
    unsigned short PDOUT_8       : 1; 
    unsigned short PDOUT_9       : 1; 
    unsigned short PDOUT_10      : 1; 
    unsigned short PDOUT_11      : 1; 
    unsigned short PDOUT_12      : 1; 
    unsigned short PDOUT_13      : 1; 
    unsigned short PDOUT_14      : 1; 
    unsigned short PDOUT_15      : 1; 
  } PDOUT_bit;  
} @ 0x0262;


enum {
  PDOUT_0             = 0x0001,
  PDOUT_1             = 0x0002,
  PDOUT_2             = 0x0004,
  PDOUT_3             = 0x0008,
  PDOUT_4             = 0x0010,
  PDOUT_5             = 0x0020,
  PDOUT_6             = 0x0040,
  PDOUT_7             = 0x0080,
  PDOUT_8             = 0x0100,
  PDOUT_9             = 0x0200,
  PDOUT_10            = 0x0400,
  PDOUT_11            = 0x0800,
  PDOUT_12            = 0x1000,
  PDOUT_13            = 0x2000,
  PDOUT_14            = 0x4000,
  PDOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PDDIR;  /* Port D Direction */ 
  
  struct
  {
    unsigned short PDDIR_0       : 1; 
    unsigned short PDDIR_1       : 1; 
    unsigned short PDDIR_2       : 1; 
    unsigned short PDDIR_3       : 1; 
    unsigned short PDDIR_4       : 1; 
    unsigned short PDDIR_5       : 1; 
    unsigned short PDDIR_6       : 1; 
    unsigned short PDDIR_7       : 1; 
    unsigned short PDDIR_8       : 1; 
    unsigned short PDDIR_9       : 1; 
    unsigned short PDDIR_10      : 1; 
    unsigned short PDDIR_11      : 1; 
    unsigned short PDDIR_12      : 1; 
    unsigned short PDDIR_13      : 1; 
    unsigned short PDDIR_14      : 1; 
    unsigned short PDDIR_15      : 1; 
  } PDDIR_bit;  
} @ 0x0264;


enum {
  PDDIR_0             = 0x0001,
  PDDIR_1             = 0x0002,
  PDDIR_2             = 0x0004,
  PDDIR_3             = 0x0008,
  PDDIR_4             = 0x0010,
  PDDIR_5             = 0x0020,
  PDDIR_6             = 0x0040,
  PDDIR_7             = 0x0080,
  PDDIR_8             = 0x0100,
  PDDIR_9             = 0x0200,
  PDDIR_10            = 0x0400,
  PDDIR_11            = 0x0800,
  PDDIR_12            = 0x1000,
  PDDIR_13            = 0x2000,
  PDDIR_14            = 0x4000,
  PDDIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PDREN;  /* Port D Resistor Enable */ 
  
  struct
  {
    unsigned short PDREN_0       : 1; 
    unsigned short PDREN_1       : 1; 
    unsigned short PDREN_2       : 1; 
    unsigned short PDREN_3       : 1; 
    unsigned short PDREN_4       : 1; 
    unsigned short PDREN_5       : 1; 
    unsigned short PDREN_6       : 1; 
    unsigned short PDREN_7       : 1; 
    unsigned short PDREN_8       : 1; 
    unsigned short PDREN_9       : 1; 
    unsigned short PDREN_10      : 1; 
    unsigned short PDREN_11      : 1; 
    unsigned short PDREN_12      : 1; 
    unsigned short PDREN_13      : 1; 
    unsigned short PDREN_14      : 1; 
    unsigned short PDREN_15      : 1; 
  } PDREN_bit;  
} @ 0x0266;


enum {
  PDREN_0             = 0x0001,
  PDREN_1             = 0x0002,
  PDREN_2             = 0x0004,
  PDREN_3             = 0x0008,
  PDREN_4             = 0x0010,
  PDREN_5             = 0x0020,
  PDREN_6             = 0x0040,
  PDREN_7             = 0x0080,
  PDREN_8             = 0x0100,
  PDREN_9             = 0x0200,
  PDREN_10            = 0x0400,
  PDREN_11            = 0x0800,
  PDREN_12            = 0x1000,
  PDREN_13            = 0x2000,
  PDREN_14            = 0x4000,
  PDREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PDDS;  /* Port D Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PDDS_0        : 1; 
    unsigned short PDDS_1        : 1; 
    unsigned short PDDS_2        : 1; 
    unsigned short PDDS_3        : 1; 
    unsigned short PDDS_4        : 1; 
    unsigned short PDDS_5        : 1; 
    unsigned short PDDS_6        : 1; 
    unsigned short PDDS_7        : 1; 
    unsigned short PDDS_8        : 1; 
    unsigned short PDDS_9        : 1; 
    unsigned short PDDS_10       : 1; 
    unsigned short PDDS_11       : 1; 
    unsigned short PDDS_12       : 1; 
    unsigned short PDDS_13       : 1; 
    unsigned short PDDS_14       : 1; 
    unsigned short PDDS_15       : 1; 
  } PDDS_bit;  
} @ 0x0268;


enum {
  PDDS_0              = 0x0001,
  PDDS_1              = 0x0002,
  PDDS_2              = 0x0004,
  PDDS_3              = 0x0008,
  PDDS_4              = 0x0010,
  PDDS_5              = 0x0020,
  PDDS_6              = 0x0040,
  PDDS_7              = 0x0080,
  PDDS_8              = 0x0100,
  PDDS_9              = 0x0200,
  PDDS_10             = 0x0400,
  PDDS_11             = 0x0800,
  PDDS_12             = 0x1000,
  PDDS_13             = 0x2000,
  PDDS_14             = 0x4000,
  PDDS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PDSEL;  /* Port D Selection */ 
  
  struct
  {
    unsigned short PDSEL_0       : 1; 
    unsigned short PDSEL_1       : 1; 
    unsigned short PDSEL_2       : 1; 
    unsigned short PDSEL_3       : 1; 
    unsigned short PDSEL_4       : 1; 
    unsigned short PDSEL_5       : 1; 
    unsigned short PDSEL_6       : 1; 
    unsigned short PDSEL_7       : 1; 
    unsigned short PDSEL_8       : 1; 
    unsigned short PDSEL_9       : 1; 
    unsigned short PDSEL_10      : 1; 
    unsigned short PDSEL_11      : 1; 
    unsigned short PDSEL_12      : 1; 
    unsigned short PDSEL_13      : 1; 
    unsigned short PDSEL_14      : 1; 
    unsigned short PDSEL_15      : 1; 
  } PDSEL_bit;  
} @ 0x026A;


enum {
  PDSEL_0             = 0x0001,
  PDSEL_1             = 0x0002,
  PDSEL_2             = 0x0004,
  PDSEL_3             = 0x0008,
  PDSEL_4             = 0x0010,
  PDSEL_5             = 0x0020,
  PDSEL_6             = 0x0040,
  PDSEL_7             = 0x0080,
  PDSEL_8             = 0x0100,
  PDSEL_9             = 0x0200,
  PDSEL_10            = 0x0400,
  PDSEL_11            = 0x0800,
  PDSEL_12            = 0x1000,
  PDSEL_13            = 0x2000,
  PDSEL_14            = 0x4000,
  PDSEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P7IN;  /* Port 7 Input */ 
  
  struct
  {
    unsigned char P7IN_0         : 1; 
    unsigned char P7IN_1         : 1; 
    unsigned char P7IN_2         : 1; 
    unsigned char P7IN_3         : 1; 
    unsigned char P7IN_4         : 1; 
    unsigned char P7IN_5         : 1; 
    unsigned char P7IN_6         : 1; 
    unsigned char P7IN_7         : 1; 
  } P7IN_bit;  
} @ 0x0260;




__no_init volatile union
{
  unsigned char P7OUT;  /* Port 7 Output */ 
  
  struct
  {
    unsigned char P7OUT_0        : 1; 
    unsigned char P7OUT_1        : 1; 
    unsigned char P7OUT_2        : 1; 
    unsigned char P7OUT_3        : 1; 
    unsigned char P7OUT_4        : 1; 
    unsigned char P7OUT_5        : 1; 
    unsigned char P7OUT_6        : 1; 
    unsigned char P7OUT_7        : 1; 
  } P7OUT_bit;  
} @ 0x0262;


enum {
  P7OUT_0             = 0x0001,
  P7OUT_1             = 0x0002,
  P7OUT_2             = 0x0004,
  P7OUT_3             = 0x0008,
  P7OUT_4             = 0x0010,
  P7OUT_5             = 0x0020,
  P7OUT_6             = 0x0040,
  P7OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P7DIR;  /* Port 7 Direction */ 
  
  struct
  {
    unsigned char P7DIR_0        : 1; 
    unsigned char P7DIR_1        : 1; 
    unsigned char P7DIR_2        : 1; 
    unsigned char P7DIR_3        : 1; 
    unsigned char P7DIR_4        : 1; 
    unsigned char P7DIR_5        : 1; 
    unsigned char P7DIR_6        : 1; 
    unsigned char P7DIR_7        : 1; 
  } P7DIR_bit;  
} @ 0x0264;


enum {
  P7DIR_0             = 0x0001,
  P7DIR_1             = 0x0002,
  P7DIR_2             = 0x0004,
  P7DIR_3             = 0x0008,
  P7DIR_4             = 0x0010,
  P7DIR_5             = 0x0020,
  P7DIR_6             = 0x0040,
  P7DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P7REN;  /* Port 7 Resistor Enable */ 
  
  struct
  {
    unsigned char P7REN_0        : 1; 
    unsigned char P7REN_1        : 1; 
    unsigned char P7REN_2        : 1; 
    unsigned char P7REN_3        : 1; 
    unsigned char P7REN_4        : 1; 
    unsigned char P7REN_5        : 1; 
    unsigned char P7REN_6        : 1; 
    unsigned char P7REN_7        : 1; 
  } P7REN_bit;  
} @ 0x0266;


enum {
  P7REN_0             = 0x0001,
  P7REN_1             = 0x0002,
  P7REN_2             = 0x0004,
  P7REN_3             = 0x0008,
  P7REN_4             = 0x0010,
  P7REN_5             = 0x0020,
  P7REN_6             = 0x0040,
  P7REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P7DS;  /* Port 7 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P7DS_0         : 1; 
    unsigned char P7DS_1         : 1; 
    unsigned char P7DS_2         : 1; 
    unsigned char P7DS_3         : 1; 
    unsigned char P7DS_4         : 1; 
    unsigned char P7DS_5         : 1; 
    unsigned char P7DS_6         : 1; 
    unsigned char P7DS_7         : 1; 
  } P7DS_bit;  
} @ 0x0268;


enum {
  P7DS_0              = 0x0001,
  P7DS_1              = 0x0002,
  P7DS_2              = 0x0004,
  P7DS_3              = 0x0008,
  P7DS_4              = 0x0010,
  P7DS_5              = 0x0020,
  P7DS_6              = 0x0040,
  P7DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P7SEL;  /* Port 7 Selection */ 
  
  struct
  {
    unsigned char P7SEL_0        : 1; 
    unsigned char P7SEL_1        : 1; 
    unsigned char P7SEL_2        : 1; 
    unsigned char P7SEL_3        : 1; 
    unsigned char P7SEL_4        : 1; 
    unsigned char P7SEL_5        : 1; 
    unsigned char P7SEL_6        : 1; 
    unsigned char P7SEL_7        : 1; 
  } P7SEL_bit;  
} @ 0x026A;


enum {
  P7SEL_0             = 0x0001,
  P7SEL_1             = 0x0002,
  P7SEL_2             = 0x0004,
  P7SEL_3             = 0x0008,
  P7SEL_4             = 0x0010,
  P7SEL_5             = 0x0020,
  P7SEL_6             = 0x0040,
  P7SEL_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P8IN;  /* Port 8 Input */ 
  
  struct
  {
    unsigned char P8IN_0         : 1; 
    unsigned char P8IN_1         : 1; 
    unsigned char P8IN_2         : 1; 
    unsigned char P8IN_3         : 1; 
    unsigned char P8IN_4         : 1; 
    unsigned char P8IN_5         : 1; 
    unsigned char P8IN_6         : 1; 
    unsigned char P8IN_7         : 1; 
  } P8IN_bit;  
} @ 0x0261;


enum {
  P8IN_0              = 0x0001,
  P8IN_1              = 0x0002,
  P8IN_2              = 0x0004,
  P8IN_3              = 0x0008,
  P8IN_4              = 0x0010,
  P8IN_5              = 0x0020,
  P8IN_6              = 0x0040,
  P8IN_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P8OUT;  /* Port 8 Output */ 
  
  struct
  {
    unsigned char P8OUT_0        : 1; 
    unsigned char P8OUT_1        : 1; 
    unsigned char P8OUT_2        : 1; 
    unsigned char P8OUT_3        : 1; 
    unsigned char P8OUT_4        : 1; 
    unsigned char P8OUT_5        : 1; 
    unsigned char P8OUT_6        : 1; 
    unsigned char P8OUT_7        : 1; 
  } P8OUT_bit;  
} @ 0x0263;


enum {
  P8OUT_0             = 0x0001,
  P8OUT_1             = 0x0002,
  P8OUT_2             = 0x0004,
  P8OUT_3             = 0x0008,
  P8OUT_4             = 0x0010,
  P8OUT_5             = 0x0020,
  P8OUT_6             = 0x0040,
  P8OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P8DIR;  /* Port 8 Direction */ 
  
  struct
  {
    unsigned char P8DIR_0        : 1; 
    unsigned char P8DIR_1        : 1; 
    unsigned char P8DIR_2        : 1; 
    unsigned char P8DIR_3        : 1; 
    unsigned char P8DIR_4        : 1; 
    unsigned char P8DIR_5        : 1; 
    unsigned char P8DIR_6        : 1; 
    unsigned char P8DIR_7        : 1; 
  } P8DIR_bit;  
} @ 0x0265;


enum {
  P8DIR_0             = 0x0001,
  P8DIR_1             = 0x0002,
  P8DIR_2             = 0x0004,
  P8DIR_3             = 0x0008,
  P8DIR_4             = 0x0010,
  P8DIR_5             = 0x0020,
  P8DIR_6             = 0x0040,
  P8DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P8REN;  /* Port 8 Resistor Enable */ 
  
  struct
  {
    unsigned char P8REN_0        : 1; 
    unsigned char P8REN_1        : 1; 
    unsigned char P8REN_2        : 1; 
    unsigned char P8REN_3        : 1; 
    unsigned char P8REN_4        : 1; 
    unsigned char P8REN_5        : 1; 
    unsigned char P8REN_6        : 1; 
    unsigned char P8REN_7        : 1; 
  } P8REN_bit;  
} @ 0x0267;


enum {
  P8REN_0             = 0x0001,
  P8REN_1             = 0x0002,
  P8REN_2             = 0x0004,
  P8REN_3             = 0x0008,
  P8REN_4             = 0x0010,
  P8REN_5             = 0x0020,
  P8REN_6             = 0x0040,
  P8REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P8DS;  /* Port 8 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P8DS_0         : 1; 
    unsigned char P8DS_1         : 1; 
    unsigned char P8DS_2         : 1; 
    unsigned char P8DS_3         : 1; 
    unsigned char P8DS_4         : 1; 
    unsigned char P8DS_5         : 1; 
    unsigned char P8DS_6         : 1; 
    unsigned char P8DS_7         : 1; 
  } P8DS_bit;  
} @ 0x0269;


enum {
  P8DS_0              = 0x0001,
  P8DS_1              = 0x0002,
  P8DS_2              = 0x0004,
  P8DS_3              = 0x0008,
  P8DS_4              = 0x0010,
  P8DS_5              = 0x0020,
  P8DS_6              = 0x0040,
  P8DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P8SEL;  /* Port 8 Selection */ 
  
  struct
  {
    unsigned char P8SEL_0        : 1; 
    unsigned char P8SEL_1        : 1; 
    unsigned char P8SEL_2        : 1; 
    unsigned char P8SEL_3        : 1; 
    unsigned char P8SEL_4        : 1; 
    unsigned char P8SEL_5        : 1; 
    unsigned char P8SEL_6        : 1; 
    unsigned char P8SEL_7        : 1; 
  } P8SEL_bit;  
} @ 0x026B;


enum {
  P8SEL_0             = 0x0001,
  P8SEL_1             = 0x0002,
  P8SEL_2             = 0x0004,
  P8SEL_3             = 0x0008,
  P8SEL_4             = 0x0010,
  P8SEL_5             = 0x0020,
  P8SEL_6             = 0x0040,
  P8SEL_7             = 0x0080,
};

 
#define __MSP430_HAS_PORTD_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT7_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT8_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port9/10 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port E In */ 
__no_init volatile unsigned __READ short PEIN @ 0x0280;  
 

__no_init volatile union
{
  unsigned short PEOUT;  /* Port E Output */ 
  
  struct
  {
    unsigned short PEOUT_0       : 1; 
    unsigned short PEOUT_1       : 1; 
    unsigned short PEOUT_2       : 1; 
    unsigned short PEOUT_3       : 1; 
    unsigned short PEOUT_4       : 1; 
    unsigned short PEOUT_5       : 1; 
    unsigned short PEOUT_6       : 1; 
    unsigned short PEOUT_7       : 1; 
    unsigned short PEOUT_8       : 1; 
    unsigned short PEOUT_9       : 1; 
    unsigned short PEOUT_10      : 1; 
    unsigned short PEOUT_11      : 1; 
    unsigned short PEOUT_12      : 1; 
    unsigned short PEOUT_13      : 1; 
    unsigned short PEOUT_14      : 1; 
    unsigned short PEOUT_15      : 1; 
  } PEOUT_bit;  
} @ 0x0282;


enum {
  PEOUT_0             = 0x0001,
  PEOUT_1             = 0x0002,
  PEOUT_2             = 0x0004,
  PEOUT_3             = 0x0008,
  PEOUT_4             = 0x0010,
  PEOUT_5             = 0x0020,
  PEOUT_6             = 0x0040,
  PEOUT_7             = 0x0080,
  PEOUT_8             = 0x0100,
  PEOUT_9             = 0x0200,
  PEOUT_10            = 0x0400,
  PEOUT_11            = 0x0800,
  PEOUT_12            = 0x1000,
  PEOUT_13            = 0x2000,
  PEOUT_14            = 0x4000,
  PEOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PEDIR;  /* Port E Direction */ 
  
  struct
  {
    unsigned short PEDIR_0       : 1; 
    unsigned short PEDIR_1       : 1; 
    unsigned short PEDIR_2       : 1; 
    unsigned short PEDIR_3       : 1; 
    unsigned short PEDIR_4       : 1; 
    unsigned short PEDIR_5       : 1; 
    unsigned short PEDIR_6       : 1; 
    unsigned short PEDIR_7       : 1; 
    unsigned short PEDIR_8       : 1; 
    unsigned short PEDIR_9       : 1; 
    unsigned short PEDIR_10      : 1; 
    unsigned short PEDIR_11      : 1; 
    unsigned short PEDIR_12      : 1; 
    unsigned short PEDIR_13      : 1; 
    unsigned short PEDIR_14      : 1; 
    unsigned short PEDIR_15      : 1; 
  } PEDIR_bit;  
} @ 0x0284;


enum {
  PEDIR_0             = 0x0001,
  PEDIR_1             = 0x0002,
  PEDIR_2             = 0x0004,
  PEDIR_3             = 0x0008,
  PEDIR_4             = 0x0010,
  PEDIR_5             = 0x0020,
  PEDIR_6             = 0x0040,
  PEDIR_7             = 0x0080,
  PEDIR_8             = 0x0100,
  PEDIR_9             = 0x0200,
  PEDIR_10            = 0x0400,
  PEDIR_11            = 0x0800,
  PEDIR_12            = 0x1000,
  PEDIR_13            = 0x2000,
  PEDIR_14            = 0x4000,
  PEDIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PEREN;  /* Port E Resistor Enable */ 
  
  struct
  {
    unsigned short PEREN_0       : 1; 
    unsigned short PEREN_1       : 1; 
    unsigned short PEREN_2       : 1; 
    unsigned short PEREN_3       : 1; 
    unsigned short PEREN_4       : 1; 
    unsigned short PEREN_5       : 1; 
    unsigned short PEREN_6       : 1; 
    unsigned short PEREN_7       : 1; 
    unsigned short PEREN_8       : 1; 
    unsigned short PEREN_9       : 1; 
    unsigned short PEREN_10      : 1; 
    unsigned short PEREN_11      : 1; 
    unsigned short PEREN_12      : 1; 
    unsigned short PEREN_13      : 1; 
    unsigned short PEREN_14      : 1; 
    unsigned short PEREN_15      : 1; 
  } PEREN_bit;  
} @ 0x0286;


enum {
  PEREN_0             = 0x0001,
  PEREN_1             = 0x0002,
  PEREN_2             = 0x0004,
  PEREN_3             = 0x0008,
  PEREN_4             = 0x0010,
  PEREN_5             = 0x0020,
  PEREN_6             = 0x0040,
  PEREN_7             = 0x0080,
  PEREN_8             = 0x0100,
  PEREN_9             = 0x0200,
  PEREN_10            = 0x0400,
  PEREN_11            = 0x0800,
  PEREN_12            = 0x1000,
  PEREN_13            = 0x2000,
  PEREN_14            = 0x4000,
  PEREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PEDS;  /* Port E Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PEDS_0        : 1; 
    unsigned short PEDS_1        : 1; 
    unsigned short PEDS_2        : 1; 
    unsigned short PEDS_3        : 1; 
    unsigned short PEDS_4        : 1; 
    unsigned short PEDS_5        : 1; 
    unsigned short PEDS_6        : 1; 
    unsigned short PEDS_7        : 1; 
    unsigned short PEDS_8        : 1; 
    unsigned short PEDS_9        : 1; 
    unsigned short PEDS_10       : 1; 
    unsigned short PEDS_11       : 1; 
    unsigned short PEDS_12       : 1; 
    unsigned short PEDS_13       : 1; 
    unsigned short PEDS_14       : 1; 
    unsigned short PEDS_15       : 1; 
  } PEDS_bit;  
} @ 0x0288;


enum {
  PEDS_0              = 0x0001,
  PEDS_1              = 0x0002,
  PEDS_2              = 0x0004,
  PEDS_3              = 0x0008,
  PEDS_4              = 0x0010,
  PEDS_5              = 0x0020,
  PEDS_6              = 0x0040,
  PEDS_7              = 0x0080,
  PEDS_8              = 0x0100,
  PEDS_9              = 0x0200,
  PEDS_10             = 0x0400,
  PEDS_11             = 0x0800,
  PEDS_12             = 0x1000,
  PEDS_13             = 0x2000,
  PEDS_14             = 0x4000,
  PEDS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PESEL;  /* Port E Selection */ 
  
  struct
  {
    unsigned short PESEL_0       : 1; 
    unsigned short PESEL_1       : 1; 
    unsigned short PESEL_2       : 1; 
    unsigned short PESEL_3       : 1; 
    unsigned short PESEL_4       : 1; 
    unsigned short PESEL_5       : 1; 
    unsigned short PESEL_6       : 1; 
    unsigned short PESEL_7       : 1; 
    unsigned short PESEL_8       : 1; 
    unsigned short PESEL_9       : 1; 
    unsigned short PESEL_10      : 1; 
    unsigned short PESEL_11      : 1; 
    unsigned short PESEL_12      : 1; 
    unsigned short PESEL_13      : 1; 
    unsigned short PESEL_14      : 1; 
    unsigned short PESEL_15      : 1; 
  } PESEL_bit;  
} @ 0x028A;


enum {
  PESEL_0             = 0x0001,
  PESEL_1             = 0x0002,
  PESEL_2             = 0x0004,
  PESEL_3             = 0x0008,
  PESEL_4             = 0x0010,
  PESEL_5             = 0x0020,
  PESEL_6             = 0x0040,
  PESEL_7             = 0x0080,
  PESEL_8             = 0x0100,
  PESEL_9             = 0x0200,
  PESEL_10            = 0x0400,
  PESEL_11            = 0x0800,
  PESEL_12            = 0x1000,
  PESEL_13            = 0x2000,
  PESEL_14            = 0x4000,
  PESEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P9IN;  /* Port 9 Input */ 
  
  struct
  {
    unsigned char P9IN_0         : 1; 
    unsigned char P9IN_1         : 1; 
    unsigned char P9IN_2         : 1; 
    unsigned char P9IN_3         : 1; 
    unsigned char P9IN_4         : 1; 
    unsigned char P9IN_5         : 1; 
    unsigned char P9IN_6         : 1; 
    unsigned char P9IN_7         : 1; 
  } P9IN_bit;  
} @ 0x0280;




__no_init volatile union
{
  unsigned char P9OUT;  /* Port 9 Output */ 
  
  struct
  {
    unsigned char P9OUT_0        : 1; 
    unsigned char P9OUT_1        : 1; 
    unsigned char P9OUT_2        : 1; 
    unsigned char P9OUT_3        : 1; 
    unsigned char P9OUT_4        : 1; 
    unsigned char P9OUT_5        : 1; 
    unsigned char P9OUT_6        : 1; 
    unsigned char P9OUT_7        : 1; 
  } P9OUT_bit;  
} @ 0x0282;


enum {
  P9OUT_0             = 0x0001,
  P9OUT_1             = 0x0002,
  P9OUT_2             = 0x0004,
  P9OUT_3             = 0x0008,
  P9OUT_4             = 0x0010,
  P9OUT_5             = 0x0020,
  P9OUT_6             = 0x0040,
  P9OUT_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P9DIR;  /* Port 9 Direction */ 
  
  struct
  {
    unsigned char P9DIR_0        : 1; 
    unsigned char P9DIR_1        : 1; 
    unsigned char P9DIR_2        : 1; 
    unsigned char P9DIR_3        : 1; 
    unsigned char P9DIR_4        : 1; 
    unsigned char P9DIR_5        : 1; 
    unsigned char P9DIR_6        : 1; 
    unsigned char P9DIR_7        : 1; 
  } P9DIR_bit;  
} @ 0x0284;


enum {
  P9DIR_0             = 0x0001,
  P9DIR_1             = 0x0002,
  P9DIR_2             = 0x0004,
  P9DIR_3             = 0x0008,
  P9DIR_4             = 0x0010,
  P9DIR_5             = 0x0020,
  P9DIR_6             = 0x0040,
  P9DIR_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P9REN;  /* Port 9 Resistor Enable */ 
  
  struct
  {
    unsigned char P9REN_0        : 1; 
    unsigned char P9REN_1        : 1; 
    unsigned char P9REN_2        : 1; 
    unsigned char P9REN_3        : 1; 
    unsigned char P9REN_4        : 1; 
    unsigned char P9REN_5        : 1; 
    unsigned char P9REN_6        : 1; 
    unsigned char P9REN_7        : 1; 
  } P9REN_bit;  
} @ 0x0286;


enum {
  P9REN_0             = 0x0001,
  P9REN_1             = 0x0002,
  P9REN_2             = 0x0004,
  P9REN_3             = 0x0008,
  P9REN_4             = 0x0010,
  P9REN_5             = 0x0020,
  P9REN_6             = 0x0040,
  P9REN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P9DS;  /* Port 9 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P9DS_0         : 1; 
    unsigned char P9DS_1         : 1; 
    unsigned char P9DS_2         : 1; 
    unsigned char P9DS_3         : 1; 
    unsigned char P9DS_4         : 1; 
    unsigned char P9DS_5         : 1; 
    unsigned char P9DS_6         : 1; 
    unsigned char P9DS_7         : 1; 
  } P9DS_bit;  
} @ 0x0288;


enum {
  P9DS_0              = 0x0001,
  P9DS_1              = 0x0002,
  P9DS_2              = 0x0004,
  P9DS_3              = 0x0008,
  P9DS_4              = 0x0010,
  P9DS_5              = 0x0020,
  P9DS_6              = 0x0040,
  P9DS_7              = 0x0080,
};


__no_init volatile union
{
  unsigned char P9SEL;  /* Port 9 Selection */ 
  
  struct
  {
    unsigned char P9SEL_0        : 1; 
    unsigned char P9SEL_1        : 1; 
    unsigned char P9SEL_2        : 1; 
    unsigned char P9SEL_3        : 1; 
    unsigned char P9SEL_4        : 1; 
    unsigned char P9SEL_5        : 1; 
    unsigned char P9SEL_6        : 1; 
    unsigned char P9SEL_7        : 1; 
  } P9SEL_bit;  
} @ 0x028A;


enum {
  P9SEL_0             = 0x0001,
  P9SEL_1             = 0x0002,
  P9SEL_2             = 0x0004,
  P9SEL_3             = 0x0008,
  P9SEL_4             = 0x0010,
  P9SEL_5             = 0x0020,
  P9SEL_6             = 0x0040,
  P9SEL_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P10IN;  /* Port 10 Input */ 
  
  struct
  {
    unsigned char P10IN_0        : 1; 
    unsigned char P10IN_1        : 1; 
    unsigned char P10IN_2        : 1; 
    unsigned char P10IN_3        : 1; 
    unsigned char P10IN_4        : 1; 
    unsigned char P10IN_5        : 1; 
    unsigned char P10IN_6        : 1; 
    unsigned char P10IN_7        : 1; 
  } P10IN_bit;  
} @ 0x0281;


enum {
  P10IN_0             = 0x0001,
  P10IN_1             = 0x0002,
  P10IN_2             = 0x0004,
  P10IN_3             = 0x0008,
  P10IN_4             = 0x0010,
  P10IN_5             = 0x0020,
  P10IN_6             = 0x0040,
  P10IN_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P10OUT;  /* Port 10 Output */ 
  
  struct
  {
    unsigned char P10OUT_0       : 1; 
    unsigned char P10OUT_1       : 1; 
    unsigned char P10OUT_2       : 1; 
    unsigned char P10OUT_3       : 1; 
    unsigned char P10OUT_4       : 1; 
    unsigned char P10OUT_5       : 1; 
    unsigned char P10OUT_6       : 1; 
    unsigned char P10OUT_7       : 1; 
  } P10OUT_bit;  
} @ 0x0283;


enum {
  P10OUT_0            = 0x0001,
  P10OUT_1            = 0x0002,
  P10OUT_2            = 0x0004,
  P10OUT_3            = 0x0008,
  P10OUT_4            = 0x0010,
  P10OUT_5            = 0x0020,
  P10OUT_6            = 0x0040,
  P10OUT_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P10DIR;  /* Port 10 Direction */ 
  
  struct
  {
    unsigned char P10DIR_0       : 1; 
    unsigned char P10DIR_1       : 1; 
    unsigned char P10DIR_2       : 1; 
    unsigned char P10DIR_3       : 1; 
    unsigned char P10DIR_4       : 1; 
    unsigned char P10DIR_5       : 1; 
    unsigned char P10DIR_6       : 1; 
    unsigned char P10DIR_7       : 1; 
  } P10DIR_bit;  
} @ 0x0285;


enum {
  P10DIR_0            = 0x0001,
  P10DIR_1            = 0x0002,
  P10DIR_2            = 0x0004,
  P10DIR_3            = 0x0008,
  P10DIR_4            = 0x0010,
  P10DIR_5            = 0x0020,
  P10DIR_6            = 0x0040,
  P10DIR_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P10REN;  /* Port 10 Resistor Enable */ 
  
  struct
  {
    unsigned char P10REN_0       : 1; 
    unsigned char P10REN_1       : 1; 
    unsigned char P10REN_2       : 1; 
    unsigned char P10REN_3       : 1; 
    unsigned char P10REN_4       : 1; 
    unsigned char P10REN_5       : 1; 
    unsigned char P10REN_6       : 1; 
    unsigned char P10REN_7       : 1; 
  } P10REN_bit;  
} @ 0x0287;


enum {
  P10REN_0            = 0x0001,
  P10REN_1            = 0x0002,
  P10REN_2            = 0x0004,
  P10REN_3            = 0x0008,
  P10REN_4            = 0x0010,
  P10REN_5            = 0x0020,
  P10REN_6            = 0x0040,
  P10REN_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P10DS;  /* Port 10 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P10DS_0        : 1; 
    unsigned char P10DS_1        : 1; 
    unsigned char P10DS_2        : 1; 
    unsigned char P10DS_3        : 1; 
    unsigned char P10DS_4        : 1; 
    unsigned char P10DS_5        : 1; 
    unsigned char P10DS_6        : 1; 
    unsigned char P10DS_7        : 1; 
  } P10DS_bit;  
} @ 0x0289;


enum {
  P10DS_0             = 0x0001,
  P10DS_1             = 0x0002,
  P10DS_2             = 0x0004,
  P10DS_3             = 0x0008,
  P10DS_4             = 0x0010,
  P10DS_5             = 0x0020,
  P10DS_6             = 0x0040,
  P10DS_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P10SEL;  /* Port 10 Selection */ 
  
  struct
  {
    unsigned char P10SEL_0       : 1; 
    unsigned char P10SEL_1       : 1; 
    unsigned char P10SEL_2       : 1; 
    unsigned char P10SEL_3       : 1; 
    unsigned char P10SEL_4       : 1; 
    unsigned char P10SEL_5       : 1; 
    unsigned char P10SEL_6       : 1; 
    unsigned char P10SEL_7       : 1; 
  } P10SEL_bit;  
} @ 0x028B;


enum {
  P10SEL_0            = 0x0001,
  P10SEL_1            = 0x0002,
  P10SEL_2            = 0x0004,
  P10SEL_3            = 0x0008,
  P10SEL_4            = 0x0010,
  P10SEL_5            = 0x0020,
  P10SEL_6            = 0x0040,
  P10SEL_7            = 0x0080,
};

 
#define __MSP430_HAS_PORTE_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT9_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT10_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port 11 Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


 /* Port F In */ 
__no_init volatile unsigned __READ short PFIN @ 0x02A0;  
 

__no_init volatile union
{
  unsigned short PFOUT;  /* Port F Output */ 
  
  struct
  {
    unsigned short PFOUT_0       : 1; 
    unsigned short PFOUT_1       : 1; 
    unsigned short PFOUT_2       : 1; 
    unsigned short PFOUT_3       : 1; 
    unsigned short PFOUT_4       : 1; 
    unsigned short PFOUT_5       : 1; 
    unsigned short PFOUT_6       : 1; 
    unsigned short PFOUT_7       : 1; 
    unsigned short PFOUT_8       : 1; 
    unsigned short PFOUT_9       : 1; 
    unsigned short PFOUT_10      : 1; 
    unsigned short PFOUT_11      : 1; 
    unsigned short PFOUT_12      : 1; 
    unsigned short PFOUT_13      : 1; 
    unsigned short PFOUT_14      : 1; 
    unsigned short PFOUT_15      : 1; 
  } PFOUT_bit;  
} @ 0x02A2;


enum {
  PFOUT_0             = 0x0001,
  PFOUT_1             = 0x0002,
  PFOUT_2             = 0x0004,
  PFOUT_3             = 0x0008,
  PFOUT_4             = 0x0010,
  PFOUT_5             = 0x0020,
  PFOUT_6             = 0x0040,
  PFOUT_7             = 0x0080,
  PFOUT_8             = 0x0100,
  PFOUT_9             = 0x0200,
  PFOUT_10            = 0x0400,
  PFOUT_11            = 0x0800,
  PFOUT_12            = 0x1000,
  PFOUT_13            = 0x2000,
  PFOUT_14            = 0x4000,
  PFOUT_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PFDIR;  /* Port F Direction */ 
  
  struct
  {
    unsigned short PFDIR_0       : 1; 
    unsigned short PFDIR_1       : 1; 
    unsigned short PFDIR_2       : 1; 
    unsigned short PFDIR_3       : 1; 
    unsigned short PFDIR_4       : 1; 
    unsigned short PFDIR_5       : 1; 
    unsigned short PFDIR_6       : 1; 
    unsigned short PFDIR_7       : 1; 
    unsigned short PFDIR_8       : 1; 
    unsigned short PFDIR_9       : 1; 
    unsigned short PFDIR_10      : 1; 
    unsigned short PFDIR_11      : 1; 
    unsigned short PFDIR_12      : 1; 
    unsigned short PFDIR_13      : 1; 
    unsigned short PFDIR_14      : 1; 
    unsigned short PFDIR_15      : 1; 
  } PFDIR_bit;  
} @ 0x02A4;


enum {
  PFDIR_0             = 0x0001,
  PFDIR_1             = 0x0002,
  PFDIR_2             = 0x0004,
  PFDIR_3             = 0x0008,
  PFDIR_4             = 0x0010,
  PFDIR_5             = 0x0020,
  PFDIR_6             = 0x0040,
  PFDIR_7             = 0x0080,
  PFDIR_8             = 0x0100,
  PFDIR_9             = 0x0200,
  PFDIR_10            = 0x0400,
  PFDIR_11            = 0x0800,
  PFDIR_12            = 0x1000,
  PFDIR_13            = 0x2000,
  PFDIR_14            = 0x4000,
  PFDIR_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PFREN;  /* Port F Resistor Enable */ 
  
  struct
  {
    unsigned short PFREN_0       : 1; 
    unsigned short PFREN_1       : 1; 
    unsigned short PFREN_2       : 1; 
    unsigned short PFREN_3       : 1; 
    unsigned short PFREN_4       : 1; 
    unsigned short PFREN_5       : 1; 
    unsigned short PFREN_6       : 1; 
    unsigned short PFREN_7       : 1; 
    unsigned short PFREN_8       : 1; 
    unsigned short PFREN_9       : 1; 
    unsigned short PFREN_10      : 1; 
    unsigned short PFREN_11      : 1; 
    unsigned short PFREN_12      : 1; 
    unsigned short PFREN_13      : 1; 
    unsigned short PFREN_14      : 1; 
    unsigned short PFREN_15      : 1; 
  } PFREN_bit;  
} @ 0x02A6;


enum {
  PFREN_0             = 0x0001,
  PFREN_1             = 0x0002,
  PFREN_2             = 0x0004,
  PFREN_3             = 0x0008,
  PFREN_4             = 0x0010,
  PFREN_5             = 0x0020,
  PFREN_6             = 0x0040,
  PFREN_7             = 0x0080,
  PFREN_8             = 0x0100,
  PFREN_9             = 0x0200,
  PFREN_10            = 0x0400,
  PFREN_11            = 0x0800,
  PFREN_12            = 0x1000,
  PFREN_13            = 0x2000,
  PFREN_14            = 0x4000,
  PFREN_15            = 0x8000,
};


__no_init volatile union
{
  unsigned short PFDS;  /* Port F Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PFDS_0        : 1; 
    unsigned short PFDS_1        : 1; 
    unsigned short PFDS_2        : 1; 
    unsigned short PFDS_3        : 1; 
    unsigned short PFDS_4        : 1; 
    unsigned short PFDS_5        : 1; 
    unsigned short PFDS_6        : 1; 
    unsigned short PFDS_7        : 1; 
    unsigned short PFDS_8        : 1; 
    unsigned short PFDS_9        : 1; 
    unsigned short PFDS_10       : 1; 
    unsigned short PFDS_11       : 1; 
    unsigned short PFDS_12       : 1; 
    unsigned short PFDS_13       : 1; 
    unsigned short PFDS_14       : 1; 
    unsigned short PFDS_15       : 1; 
  } PFDS_bit;  
} @ 0x02A8;


enum {
  PFDS_0              = 0x0001,
  PFDS_1              = 0x0002,
  PFDS_2              = 0x0004,
  PFDS_3              = 0x0008,
  PFDS_4              = 0x0010,
  PFDS_5              = 0x0020,
  PFDS_6              = 0x0040,
  PFDS_7              = 0x0080,
  PFDS_8              = 0x0100,
  PFDS_9              = 0x0200,
  PFDS_10             = 0x0400,
  PFDS_11             = 0x0800,
  PFDS_12             = 0x1000,
  PFDS_13             = 0x2000,
  PFDS_14             = 0x4000,
  PFDS_15             = 0x8000,
};


__no_init volatile union
{
  unsigned short PFSEL;  /* Port F Selection */ 
  
  struct
  {
    unsigned short PFSEL_0       : 1; 
    unsigned short PFSEL_1       : 1; 
    unsigned short PFSEL_2       : 1; 
    unsigned short PFSEL_3       : 1; 
    unsigned short PFSEL_4       : 1; 
    unsigned short PFSEL_5       : 1; 
    unsigned short PFSEL_6       : 1; 
    unsigned short PFSEL_7       : 1; 
    unsigned short PFSEL_8       : 1; 
    unsigned short PFSEL_9       : 1; 
    unsigned short PFSEL_10      : 1; 
    unsigned short PFSEL_11      : 1; 
    unsigned short PFSEL_12      : 1; 
    unsigned short PFSEL_13      : 1; 
    unsigned short PFSEL_14      : 1; 
    unsigned short PFSEL_15      : 1; 
  } PFSEL_bit;  
} @ 0x02AA;


enum {
  PFSEL_0             = 0x0001,
  PFSEL_1             = 0x0002,
  PFSEL_2             = 0x0004,
  PFSEL_3             = 0x0008,
  PFSEL_4             = 0x0010,
  PFSEL_5             = 0x0020,
  PFSEL_6             = 0x0040,
  PFSEL_7             = 0x0080,
  PFSEL_8             = 0x0100,
  PFSEL_9             = 0x0200,
  PFSEL_10            = 0x0400,
  PFSEL_11            = 0x0800,
  PFSEL_12            = 0x1000,
  PFSEL_13            = 0x2000,
  PFSEL_14            = 0x4000,
  PFSEL_15            = 0x8000,
};


__no_init volatile union
{
  unsigned char P11IN;  /* Port 11 Input */ 
  
  struct
  {
    unsigned char P11IN_0        : 1; 
    unsigned char P11IN_1        : 1; 
    unsigned char P11IN_2        : 1; 
    unsigned char P11IN_3        : 1; 
    unsigned char P11IN_4        : 1; 
    unsigned char P11IN_5        : 1; 
    unsigned char P11IN_6        : 1; 
    unsigned char P11IN_7        : 1; 
  } P11IN_bit;  
} @ 0x02A0;




__no_init volatile union
{
  unsigned char P11OUT;  /* Port 11 Output */ 
  
  struct
  {
    unsigned char P11OUT_0       : 1; 
    unsigned char P11OUT_1       : 1; 
    unsigned char P11OUT_2       : 1; 
    unsigned char P11OUT_3       : 1; 
    unsigned char P11OUT_4       : 1; 
    unsigned char P11OUT_5       : 1; 
    unsigned char P11OUT_6       : 1; 
    unsigned char P11OUT_7       : 1; 
  } P11OUT_bit;  
} @ 0x02A2;


enum {
  P11OUT_0            = 0x0001,
  P11OUT_1            = 0x0002,
  P11OUT_2            = 0x0004,
  P11OUT_3            = 0x0008,
  P11OUT_4            = 0x0010,
  P11OUT_5            = 0x0020,
  P11OUT_6            = 0x0040,
  P11OUT_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P11DIR;  /* Port 11 Direction */ 
  
  struct
  {
    unsigned char P11DIR_0       : 1; 
    unsigned char P11DIR_1       : 1; 
    unsigned char P11DIR_2       : 1; 
    unsigned char P11DIR_3       : 1; 
    unsigned char P11DIR_4       : 1; 
    unsigned char P11DIR_5       : 1; 
    unsigned char P11DIR_6       : 1; 
    unsigned char P11DIR_7       : 1; 
  } P11DIR_bit;  
} @ 0x02A4;


enum {
  P11DIR_0            = 0x0001,
  P11DIR_1            = 0x0002,
  P11DIR_2            = 0x0004,
  P11DIR_3            = 0x0008,
  P11DIR_4            = 0x0010,
  P11DIR_5            = 0x0020,
  P11DIR_6            = 0x0040,
  P11DIR_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P11REN;  /* Port 11 Resistor Enable */ 
  
  struct
  {
    unsigned char P11REN_0       : 1; 
    unsigned char P11REN_1       : 1; 
    unsigned char P11REN_2       : 1; 
    unsigned char P11REN_3       : 1; 
    unsigned char P11REN_4       : 1; 
    unsigned char P11REN_5       : 1; 
    unsigned char P11REN_6       : 1; 
    unsigned char P11REN_7       : 1; 
  } P11REN_bit;  
} @ 0x02A6;


enum {
  P11REN_0            = 0x0001,
  P11REN_1            = 0x0002,
  P11REN_2            = 0x0004,
  P11REN_3            = 0x0008,
  P11REN_4            = 0x0010,
  P11REN_5            = 0x0020,
  P11REN_6            = 0x0040,
  P11REN_7            = 0x0080,
};


__no_init volatile union
{
  unsigned char P11DS;  /* Port 11 Resistor Drive Strenght */ 
  
  struct
  {
    unsigned char P11DS_0        : 1; 
    unsigned char P11DS_1        : 1; 
    unsigned char P11DS_2        : 1; 
    unsigned char P11DS_3        : 1; 
    unsigned char P11DS_4        : 1; 
    unsigned char P11DS_5        : 1; 
    unsigned char P11DS_6        : 1; 
    unsigned char P11DS_7        : 1; 
  } P11DS_bit;  
} @ 0x02A8;


enum {
  P11DS_0             = 0x0001,
  P11DS_1             = 0x0002,
  P11DS_2             = 0x0004,
  P11DS_3             = 0x0008,
  P11DS_4             = 0x0010,
  P11DS_5             = 0x0020,
  P11DS_6             = 0x0040,
  P11DS_7             = 0x0080,
};


__no_init volatile union
{
  unsigned char P11SEL;  /* Port 11 Selection */ 
  
  struct
  {
    unsigned char P11SEL_0       : 1; 
    unsigned char P11SEL_1       : 1; 
    unsigned char P11SEL_2       : 1; 
    unsigned char P11SEL_3       : 1; 
    unsigned char P11SEL_4       : 1; 
    unsigned char P11SEL_5       : 1; 
    unsigned char P11SEL_6       : 1; 
    unsigned char P11SEL_7       : 1; 
  } P11SEL_bit;  
} @ 0x02AA;


enum {
  P11SEL_0            = 0x0001,
  P11SEL_1            = 0x0002,
  P11SEL_2            = 0x0004,
  P11SEL_3            = 0x0008,
  P11SEL_4            = 0x0010,
  P11SEL_5            = 0x0020,
  P11SEL_6            = 0x0040,
  P11SEL_7            = 0x0080,
};

 
#define __MSP430_HAS_PORTF_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT11_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   DIGITAL I/O Port J Pull up / Pull down Resistors
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned __READ short PJIN;  /* Port J Input */ 
  
  struct
  {
    unsigned __READ short PJIN0  : 1;  /*  */ 
    unsigned __READ short PJIN1  : 1;  /*  */ 
    unsigned __READ short PJIN2  : 1;  /*  */ 
    unsigned __READ short PJIN3  : 1;  /*  */ 
  } PJIN_bit;  
} @ 0x0320;


enum {
  PJIN0               = 0x0001,
  PJIN1               = 0x0002,
  PJIN2               = 0x0004,
  PJIN3               = 0x0008,
};


__no_init volatile union
{
  unsigned short PJOUT;  /* Port J Output */ 
  
  struct
  {
    unsigned short PJOUT_0       : 1; 
    unsigned short PJOUT_1       : 1; 
    unsigned short PJOUT_2       : 1; 
    unsigned short PJOUT_3       : 1; 
  } PJOUT_bit;  
} @ 0x0322;


enum {
  PJOUT_0             = 0x0001,
  PJOUT_1             = 0x0002,
  PJOUT_2             = 0x0004,
  PJOUT_3             = 0x0008,
};


__no_init volatile union
{
  unsigned short PJDIR;  /* Port J Direction */ 
  
  struct
  {
    unsigned short PJDIR_0       : 1; 
    unsigned short PJDIR_1       : 1; 
    unsigned short PJDIR_2       : 1; 
    unsigned short PJDIR_3       : 1; 
  } PJDIR_bit;  
} @ 0x0324;


enum {
  PJDIR_0             = 0x0001,
  PJDIR_1             = 0x0002,
  PJDIR_2             = 0x0004,
  PJDIR_3             = 0x0008,
};


__no_init volatile union
{
  unsigned short PJREN;  /* Port J Resistor Enable */ 
  
  struct
  {
    unsigned short PJREN_0       : 1; 
    unsigned short PJREN_1       : 1; 
    unsigned short PJREN_2       : 1; 
    unsigned short PJREN_3       : 1; 
  } PJREN_bit;  
} @ 0x0326;


enum {
  PJREN_0             = 0x0001,
  PJREN_1             = 0x0002,
  PJREN_2             = 0x0004,
  PJREN_3             = 0x0008,
};


__no_init volatile union
{
  unsigned short PJDS;  /* Port J Resistor Drive Strenght */ 
  
  struct
  {
    unsigned short PJDS_0        : 1; 
    unsigned short PJDS_1        : 1; 
    unsigned short PJDS_2        : 1; 
    unsigned short PJDS_3        : 1; 
  } PJDS_bit;  
} @ 0x0328;


enum {
  PJDS_0              = 0x0001,
  PJDS_1              = 0x0002,
  PJDS_2              = 0x0004,
  PJDS_3              = 0x0008,
};

 
#define __MSP430_HAS_PORTJ_R__        /* Definition to show that Module is available */
 

/*-------------------------------------------------------------------------
 *   PMM
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short PMMCTL0;  /* PMM Control 0 */ 
  
  struct
  {
    unsigned short PMMCOREV0     : 1;  /* PMM Core Voltage Bit: 0 */ 
    unsigned short PMMCOREV1     : 1;  /* PMM Core Voltage Bit: 1 */ 
    unsigned short PMMSWBOR      : 1;  /* PMM Software BOR */ 
    unsigned short PMMSWPOR      : 1;  /* PMM Software POR */ 
    unsigned short PMMREGOFF     : 1;  /* PMM Turn Regulator off */ 
    unsigned short               : 2; 
    unsigned short PMMHPMRE      : 1;  /* PMM Global High Power Module Request Enable */ 
  } PMMCTL0_bit;  
} @ 0x0120;


enum {
  PMMCOREV0           = 0x0001,
  PMMCOREV1           = 0x0002,
  PMMSWBOR            = 0x0004,
  PMMSWPOR            = 0x0008,
  PMMREGOFF           = 0x0010,
  PMMHPMRE            = 0x0080,
};


__no_init volatile union
{
  unsigned short PMMCTL1;  /* PMM Control 1 */ 
  
  struct
  {
    unsigned short PMMREFMD      : 1;  /* PMM Reference Mode */ 
    unsigned short               : 3; 
    unsigned short PMMCMD0       : 1;  /* PMM Voltage Regulator Current Mode Bit: 0 */ 
    unsigned short PMMCMD1       : 1;  /* PMM Voltage Regulator Current Mode Bit: 1 */ 
  } PMMCTL1_bit;  
} @ 0x0122;


enum {
  PMMREFMD            = 0x0001,
  PMMCMD0             = 0x0010,
  PMMCMD1             = 0x0020,
};


__no_init volatile union
{
  unsigned short SVSMHCTL;  /* SVS and SVM high side control register */ 
  
  struct
  {
    unsigned short SVSMHRRL0     : 1;  /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */ 
    unsigned short SVSMHRRL1     : 1;  /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */ 
    unsigned short SVSMHRRL2     : 1;  /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */ 
    unsigned short SVSMHDLYST    : 1;  /* SVS and SVM high side delay status */ 
    unsigned short SVSHMD        : 1;  /* SVS high side mode */ 
    unsigned short               : 1; 
    unsigned short SVSMHEVM      : 1;  /* SVS and SVM high side event mask */ 
    unsigned short SVSMHACE      : 1;  /* SVS and SVM high side auto control enable */ 
    unsigned short SVSHRVL0      : 1;  /* SVS high side reset voltage level Bit: 0 */ 
    unsigned short SVSHRVL1      : 1;  /* SVS high side reset voltage level Bit: 1 */ 
    unsigned short SVSHE         : 1;  /* SVS high side enable */ 
    unsigned short SVSHFP        : 1;  /* SVS high side full performace mode */ 
    unsigned short SVMHOVPE      : 1;  /* SVM high side over-voltage enable */ 
    unsigned short               : 1; 
    unsigned short SVMHE         : 1;  /* SVM high side enable */ 
    unsigned short SVMHFP        : 1;  /* SVM high side full performace mode */ 
  } SVSMHCTL_bit;  
} @ 0x0124;


enum {
  SVSMHRRL0           = 0x0001,
  SVSMHRRL1           = 0x0002,
  SVSMHRRL2           = 0x0004,
  SVSMHDLYST          = 0x0008,
  SVSHMD              = 0x0010,
  SVSMHEVM            = 0x0040,
  SVSMHACE            = 0x0080,
  SVSHRVL0            = 0x0100,
  SVSHRVL1            = 0x0200,
  SVSHE               = 0x0400,
  SVSHFP              = 0x0800,
  SVMHOVPE            = 0x1000,
  SVMHE               = 0x4000,
  SVMHFP              = 0x8000,
};


__no_init volatile union
{
  unsigned short SVSMLCTL;  /* SVS and SVM low side control register */ 
  
  struct
  {
    unsigned short SVSMLRRL0     : 1;  /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */ 
    unsigned short SVSMLRRL1     : 1;  /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */ 
    unsigned short SVSMLRRL2     : 1;  /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */ 
    unsigned short SVSMLDLYST    : 1;  /* SVS and SVM low side delay status */ 
    unsigned short SVSLMD        : 1;  /* SVS low side mode */ 
    unsigned short               : 1; 
    unsigned short SVSMLEVM      : 1;  /* SVS and SVM low side event mask */ 
    unsigned short SVSMLACE      : 1;  /* SVS and SVM low side auto control enable */ 
    unsigned short SVSLRVL0      : 1;  /* SVS low side reset voltage level Bit: 0 */ 
    unsigned short SVSLRVL1      : 1;  /* SVS low side reset voltage level Bit: 1 */ 
    unsigned short SVSLE         : 1;  /* SVS low side enable */ 
    unsigned short SVSLFP        : 1;  /* SVS low side full performace mode */ 
    unsigned short SVMLOVPE      : 1;  /* SVM low side over-voltage enable */ 
    unsigned short               : 1; 
    unsigned short SVMLE         : 1;  /* SVM low side enable */ 
    unsigned short SVMLFP        : 1;  /* SVM low side full performace mode */ 
  } SVSMLCTL_bit;  
} @ 0x0126;


enum {
  SVSMLRRL0           = 0x0001,
  SVSMLRRL1           = 0x0002,
  SVSMLRRL2           = 0x0004,
  SVSMLDLYST          = 0x0008,
  SVSLMD              = 0x0010,
  SVSMLEVM            = 0x0040,
  SVSMLACE            = 0x0080,
  SVSLRVL0            = 0x0100,
  SVSLRVL1            = 0x0200,
  SVSLE               = 0x0400,
  SVSLFP              = 0x0800,
  SVMLOVPE            = 0x1000,
  SVMLE               = 0x4000,
  SVMLFP              = 0x8000,
};


__no_init volatile union
{
  unsigned short SVSMIO;  /* SVSIN and SVSOUT control register */ 
  
  struct
  {
    unsigned short               : 3; 
    unsigned short SVMLOE        : 1;  /* SVM low side output enable */ 
    unsigned short SVMLVLROE     : 1;  /* SVM low side voltage level reached output enable */ 
    unsigned short SVMOUTPOL     : 1;  /* SVMOUT pin polarity */ 
    unsigned short               : 5; 
    unsigned short SVMHOE        : 1;  /* SVM high side output enable */ 
    unsigned short SVMHVLROE     : 1;  /* SVM high side voltage level reached output enable */ 
  } SVSMIO_bit;  
} @ 0x0128;


enum {
  SVMLOE              = 0x0008,
  SVMLVLROE           = 0x0010,
  SVMOUTPOL           = 0x0020,
  SVMHOE              = 0x0800,
  SVMHVLROE           = 0x1000,
};


__no_init volatile union
{
  unsigned short PMMIFG;  /* PMM Interrupt Flag */ 
  
  struct
  {
    unsigned short SVSMLDLYIFG   : 1;  /* SVS and SVM low side Delay expired interrupt flag */ 
    unsigned short SVMLIFG       : 1;  /* SVM low side interrupt flag */ 
    unsigned short SVMLVLRIFG    : 1;  /* SVM low side Voltage Level Reached interrupt flag */ 
    unsigned short               : 1; 
    unsigned short SVSMHDLYIFG   : 1;  /* SVS and SVM high side Delay expired interrupt flag */ 
    unsigned short SVMHIFG       : 1;  /* SVM high side interrupt flag */ 
    unsigned short SVMHVLRIFG    : 1;  /* SVM high side Voltage Level Reached interrupt flag */ 
    unsigned short               : 1; 
    unsigned short PMMBORIFG     : 1;  /* PMM Software BOR interrupt flag */ 
    unsigned short PMMRSTIFG     : 1;  /* PMM RESET pin interrupt flag */ 
    unsigned short PMMPORIFG     : 1;  /* PMM Software POR interrupt flag */ 
    unsigned short               : 1; 
    unsigned short SVSHIFG       : 1;  /* SVS low side interrupt flag */ 
    unsigned short SVSLIFG       : 1;  /* SVS high side interrupt flag */ 
    unsigned short               : 1; 
    unsigned short PMMRSTLPM5IFG : 1;  /* LPM5 indication Flag */ 
  } PMMIFG_bit;  
} @ 0x012C;


enum {
  SVSMLDLYIFG         = 0x0001,
  SVMLIFG             = 0x0002,
  SVMLVLRIFG          = 0x0004,
  SVSMHDLYIFG         = 0x0010,
  SVMHIFG             = 0x0020,
  SVMHVLRIFG          = 0x0040,
  PMMBORIFG           = 0x0100,
  PMMRSTIFG           = 0x0200,
  PMMPORIFG           = 0x0400,
  SVSHIFG             = 0x1000,
  SVSLIFG             = 0x2000,
  PMMRSTLPM5IFG       = 0x8000,
};


__no_init volatile union
{
  unsigned short PMMRIE;  /* PMM and RESET Interrupt Enable */ 
  
  struct
  {
    unsigned short SVSMLDLYIE    : 1;  /* SVS and SVM low side Delay expired interrupt enable */ 
    unsigned short SVMLIE        : 1;  /* SVM low side interrupt enable */ 
    unsigned short SVMLVLRIE     : 1;  /* SVM low side Voltage Level Reached interrupt enable */ 
    unsigned short               : 1; 
    unsigned short SVSMHDLYIE    : 1;  /* SVS and SVM high side Delay expired interrupt enable */ 
    unsigned short SVMHIE        : 1;  /* SVM high side interrupt enable */ 
    unsigned short SVMHVLRIE     : 1;  /* SVM high side Voltage Level Reached interrupt enable */ 
    unsigned short               : 1; 
    unsigned short SVSLPE        : 1;  /* SVS low side POR enable */ 
    unsigned short SVMLVLRPE     : 1;  /* SVM low side Voltage Level reached POR enable */ 
    unsigned short               : 2; 
    unsigned short SVSHPE        : 1;  /* SVS high side POR enable */ 
    unsigned short SVMHVLRPE     : 1;  /* SVM high side Voltage Level reached POR enable */ 
  } PMMRIE_bit;  
} @ 0x012E;


enum {
  SVSMLDLYIE          = 0x0001,
  SVMLIE              = 0x0002,
  SVMLVLRIE           = 0x0004,
  SVSMHDLYIE          = 0x0010,
  SVMHIE              = 0x0020,
  SVMHVLRIE           = 0x0040,
  SVSLPE              = 0x0100,
  SVMLVLRPE           = 0x0200,
  SVSHPE              = 0x1000,
  SVMHVLRPE           = 0x2000,
};

 
#define __MSP430_HAS_PMM__          /* Definition to show that Module is available */

#define PMMPW               (0xA500)  /* PMM Register Write Password */
#define PMMPW_H             (0xA5)    /* PMM Register Write Password for high word access */


/* PMMCTL0 Control Bits */
#define PMMCOREV0_L         (0x0001)  /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1_L         (0x0002)  /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR_L          (0x0004)  /* PMM Software BOR */
#define PMMSWPOR_L          (0x0008)  /* PMM Software POR */
#define PMMREGOFF_L         (0x0010)  /* PMM Turn Regulator off */
#define PMMHPMRE_L          (0x0080)  /* PMM Global High Power Module Request Enable */

/* PMMCTL0 Control Bits */

#define PMMCOREV_0          (0x0000)  /* PMM Core Voltage 0 (1.35V) */
#define PMMCOREV_1          (0x0001)  /* PMM Core Voltage 1 (1.55V) */
#define PMMCOREV_2          (0x0002)  /* PMM Core Voltage 2 (1.75V) */
#define PMMCOREV_3          (0x0003)  /* PMM Core Voltage 3 (1.85V) */


/* PMMCTL1 Control Bits */
#define PMMREFMD_L          (0x0001)  /* PMM Reference Mode */
#define PMMCMD0_L           (0x0010)  /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1_L           (0x0020)  /* PMM Voltage Regulator Current Mode Bit: 1 */


/* SVSMHCTL Control Bits */
#define SVSMHRRL0_L         (0x0001)  /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1_L         (0x0002)  /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2_L         (0x0004)  /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST_L        (0x0008)  /* SVS and SVM high side delay status */
#define SVSHMD_L            (0x0010)  /* SVS high side mode */
#define SVSMHEVM_L          (0x0040)  /* SVS and SVM high side event mask */
#define SVSMHACE_L          (0x0080)  /* SVS and SVM high side auto control enable */

/* SVSMHCTL Control Bits */
#define SVSHRVL0_H          (0x0001)  /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1_H          (0x0002)  /* SVS high side reset voltage level Bit: 1 */
#define SVSHE_H             (0x0004)  /* SVS high side enable */
#define SVSHFP_H            (0x0008)  /* SVS high side full performace mode */
#define SVMHOVPE_H          (0x0010)  /* SVM high side over-voltage enable */
#define SVMHE_H             (0x0040)  /* SVM high side enable */
#define SVMHFP_H            (0x0080)  /* SVM high side full performace mode */

#define SVSMHRRL_0          (0x0000)  /* SVS and SVM high side Reset Release Voltage Level 0 */
#define SVSMHRRL_1          (0x0001)  /* SVS and SVM high side Reset Release Voltage Level 1 */
#define SVSMHRRL_2          (0x0002)  /* SVS and SVM high side Reset Release Voltage Level 2 */
#define SVSMHRRL_3          (0x0003)  /* SVS and SVM high side Reset Release Voltage Level 3 */
#define SVSMHRRL_4          (0x0004)  /* SVS and SVM high side Reset Release Voltage Level 4 */
#define SVSMHRRL_5          (0x0005)  /* SVS and SVM high side Reset Release Voltage Level 5 */
#define SVSMHRRL_6          (0x0006)  /* SVS and SVM high side Reset Release Voltage Level 6 */
#define SVSMHRRL_7          (0x0007)  /* SVS and SVM high side Reset Release Voltage Level 7 */

#define SVSHRVL_0           (0x0000)  /* SVS high side Reset Release Voltage Level 0 */
#define SVSHRVL_1           (0x0100)  /* SVS high side Reset Release Voltage Level 1 */
#define SVSHRVL_2           (0x0200)  /* SVS high side Reset Release Voltage Level 2 */
#define SVSHRVL_3           (0x0300)  /* SVS high side Reset Release Voltage Level 3 */

/* SVSMLCTL Control Bits */
#define SVSMLRRL0_L         (0x0001)  /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1_L         (0x0002)  /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2_L         (0x0004)  /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST_L        (0x0008)  /* SVS and SVM low side delay status */
#define SVSLMD_L            (0x0010)  /* SVS low side mode */
#define SVSMLEVM_L          (0x0040)  /* SVS and SVM low side event mask */
#define SVSMLACE_L          (0x0080)  /* SVS and SVM low side auto control enable */

/* SVSMLCTL Control Bits */
#define SVSLRVL0_H          (0x0001)  /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1_H          (0x0002)  /* SVS low side reset voltage level Bit: 1 */
#define SVSLE_H             (0x0004)  /* SVS low side enable */
#define SVSLFP_H            (0x0008)  /* SVS low side full performace mode */
#define SVMLOVPE_H          (0x0010)  /* SVM low side over-voltage enable */
#define SVMLE_H             (0x0040)  /* SVM low side enable */
#define SVMLFP_H            (0x0080)  /* SVM low side full performace mode */

#define SVSMLRRL_0          (0x0000)  /* SVS and SVM low side Reset Release Voltage Level 0 */
#define SVSMLRRL_1          (0x0001)  /* SVS and SVM low side Reset Release Voltage Level 1 */
#define SVSMLRRL_2          (0x0002)  /* SVS and SVM low side Reset Release Voltage Level 2 */
#define SVSMLRRL_3          (0x0003)  /* SVS and SVM low side Reset Release Voltage Level 3 */
#define SVSMLRRL_4          (0x0004)  /* SVS and SVM low side Reset Release Voltage Level 4 */
#define SVSMLRRL_5          (0x0005)  /* SVS and SVM low side Reset Release Voltage Level 5 */
#define SVSMLRRL_6          (0x0006)  /* SVS and SVM low side Reset Release Voltage Level 6 */
#define SVSMLRRL_7          (0x0007)  /* SVS and SVM low side Reset Release Voltage Level 7 */

#define SVSLRVL_0           (0x0000)  /* SVS low side Reset Release Voltage Level 0 */
#define SVSLRVL_1           (0x0100)  /* SVS low side Reset Release Voltage Level 1 */
#define SVSLRVL_2           (0x0200)  /* SVS low side Reset Release Voltage Level 2 */
#define SVSLRVL_3           (0x0300)  /* SVS low side Reset Release Voltage Level 3 */

/* SVSMIO Control Bits */
#define SVMLOE_L            (0x0008)  /* SVM low side output enable */
#define SVMLVLROE_L         (0x0010)  /* SVM low side voltage level reached output enable */
#define SVMOUTPOL_L         (0x0020)  /* SVMOUT pin polarity */

/* SVSMIO Control Bits */
#define SVMHOE_H            (0x0008)  /* SVM high side output enable */
#define SVMHVLROE_H         (0x0010)  /* SVM high side voltage level reached output enable */

/* PMMIFG Control Bits */
#define SVSMLDLYIFG_L       (0x0001)  /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG_L           (0x0002)  /* SVM low side interrupt flag */
#define SVMLVLRIFG_L        (0x0004)  /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG_L       (0x0010)  /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG_L           (0x0020)  /* SVM high side interrupt flag */
#define SVMHVLRIFG_L        (0x0040)  /* SVM high side Voltage Level Reached interrupt flag */

/* PMMIFG Control Bits */
#define PMMBORIFG_H         (0x0001)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H         (0x0002)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H         (0x0004)  /* PMM Software POR interrupt flag */
#define SVSHIFG_H           (0x0010)  /* SVS low side interrupt flag */
#define SVSLIFG_H           (0x0020)  /* SVS high side interrupt flag */
#define PMMLPM5IFG_H        (0x0080)  /* LPM5 indication Flag */

/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE_L        (0x0001)  /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE_L            (0x0002)  /* SVM low side interrupt enable */
#define SVMLVLRIE_L         (0x0004)  /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE_L        (0x0010)  /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE_L            (0x0020)  /* SVM high side interrupt enable */
#define SVMHVLRIE_L         (0x0040)  /* SVM high side Voltage Level Reached interrupt enable */

/* PMMIE and RESET Control Bits */
#define SVSLPE_H            (0x0001)  /* SVS low side POR enable */
#define SVMLVLRPE_H         (0x0002)  /* SVM low side Voltage Level reached POR enable */
#define SVSHPE_H            (0x0010)  /* SVS high side POR enable */
#define SVMHVLRPE_H         (0x0020)  /* SVM high side Voltage Level reached POR enable */



 

/*-------------------------------------------------------------------------
 *   RC
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short RCCTL0;  /* Ram Controller Control Register */ 
  
  struct
  {
    unsigned short RCRS0OFF      : 1;  /* RAM Controller RAM Sector 0 Off */ 
    unsigned short RCRS1OFF      : 1;  /* RAM Controller RAM Sector 1 Off */ 
    unsigned short RCRS2OFF      : 1;  /* RAM Controller RAM Sector 2 Off */ 
    unsigned short RCRS3OFF      : 1;  /* RAM Controller RAM Sector 3 Off */ 
  } RCCTL0_bit;  
} @ 0x0158;


enum {
  RCRS0OFF            = 0x0001,
  RCRS1OFF            = 0x0002,
  RCRS2OFF            = 0x0004,
  RCRS3OFF            = 0x0008,
};

 
#define __MSP430_HAS_RC__          /* Definition to show that Module is available */
#define RCKEY               (0x5A00)

 

/*-------------------------------------------------------------------------
 *   RTC
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short RTCCTL01;  /* Real Timer Control 0/1 */ 
  
  struct
  {
    unsigned short RTCRDYIFG     : 1;  /* RTC Ready Interrupt Flag */ 
    unsigned short RTCAIFG       : 1;  /* RTC Alarm Interrupt Flag */ 
    unsigned short RTCTEVIFG     : 1;  /* RTC Time Event Interrupt Flag */ 
    unsigned short               : 1; 
    unsigned short RTCRDYIE      : 1;  /* RTC Ready Interrupt Enable Flag */ 
    unsigned short RTCAIE        : 1;  /* RTC Alarm Interrupt Enable Flag */ 
    unsigned short RTCTEVIE      : 1;  /* RTC Time Event Interrupt Enable Flag */ 
    unsigned short               : 1; 
    unsigned short RTCTEV        : 2;  /* RTC Time Event */ 
    unsigned short RTCSSEL       : 2;  /* RTC Source Select */ 
    unsigned short RTCRDY        : 1;  /* RTC Ready */ 
    unsigned short RTCMODE       : 1;  /* RTC Mode 0:Counter / 1: Calendar */ 
    unsigned short RTCHOLD       : 1;  /* RTC Hold */ 
    unsigned short RTCBCD        : 1;  /* RTC BCD  0:Binary / 1:BCD */ 
  } RTCCTL01_bit;  
} @ 0x04A0;


enum {
  RTCRDYIFG           = 0x0001,
  RTCAIFG             = 0x0002,
  RTCTEVIFG           = 0x0004,
  RTCRDYIE            = 0x0010,
  RTCAIE              = 0x0020,
  RTCTEVIE            = 0x0040,
  RTCTEV              = 0x0200,
  RTCSSEL             = 0x0800,
  RTCRDY              = 0x1000,
  RTCMODE             = 0x2000,
  RTCHOLD             = 0x4000,
  RTCBCD              = 0x8000,
};


__no_init volatile union
{
  unsigned short RTCCTL23;  /* Real Timer Control 2/3 */ 
  
  struct
  {
    unsigned short RTCCAL        : 6;  /* RTC Calibration */ 
    unsigned short               : 1; 
    unsigned short RTCCALS       : 1;  /* RTC Calibration Sign */ 
    unsigned short RTCCALF       : 2;  /* RTC Calibration Frequency */ 
  } RTCCTL23_bit;  
} @ 0x04A2;


enum {
  RTCCAL              = 0x0020,
  RTCCALS             = 0x0080,
  RTCCALF             = 0x0200,
};


__no_init volatile union
{
  unsigned short RTCPS0CTL;  /* Real Timer Prescale Timer 0 Control */ 
  
  struct
  {
    unsigned short RT0PSIFG      : 1;  /* RTC Prescale Timer 0 Interrupt Flag */ 
    unsigned short RT0PSIE       : 1;  /* RTC Prescale Timer 0 Interrupt Enalbe Flag */ 
    unsigned short RT0IP         : 3;  /* RTC Prescale Timer 0 Interrupt Interval */ 
    unsigned short               : 3; 
    unsigned short RT0PSHOLD     : 1;  /* RTC Prescale Timer 0 Hold */ 
    unsigned short               : 2; 
    unsigned short RT0PSDIV      : 3;  /* RTC Prescale Timer 0 Clock Divide */ 
    unsigned short RT0SSEL       : 1;  /* RTC Prescale Timer 0 Source Select 0:ACLK / 1:SMCLK */ 
  } RTCPS0CTL_bit;  
} @ 0x04A8;


enum {
  RT0PSIFG            = 0x0001,
  RT0PSIE             = 0x0002,
  RT0IP               = 0x0010,
  RT0PSHOLD           = 0x0100,
  RT0PSDIV            = 0x2000,
  RT0SSEL             = 0x4000,
};


__no_init volatile union
{
  unsigned short RTCPS1CTL;  /* Real Timer Prescale Timer 1 Control */ 
  
  struct
  {
    unsigned short RT1PSIFG      : 1;  /* RTC Prescale Timer 1 Interrupt Flag */ 
    unsigned short RT1PSIE       : 1;  /* RTC Prescale Timer 1 Interrupt Enalbe Flag */ 
    unsigned short RT1IP         : 3;  /* RTC Prescale Timer 1 Interrupt Interval */ 
    unsigned short               : 3; 
    unsigned short RT1PSHOLD     : 1;  /* RTC Prescale Timer 1 Hold */ 
    unsigned short               : 2; 
    unsigned short RT1PSDIV      : 3;  /* RTC Prescale Timer 1 Clock Divide */ 
    unsigned short RT1SSEL       : 2;  /* RTC Prescale Timer 1 Source Select */ 
  } RTCPS1CTL_bit;  
} @ 0x04AA;


enum {
  RT1PSIFG            = 0x0001,
  RT1PSIE             = 0x0002,
  RT1IP               = 0x0010,
  RT1PSHOLD           = 0x0100,
  RT1PSDIV            = 0x2000,
  RT1SSEL             = 0x8000,
};


 /* Real Timer Prescale Timer Control */ 
__no_init volatile unsigned short RTCPS @ 0x04AC;  
 

 /* Real Time Clock Interrupt Vector */ 
__no_init volatile unsigned short RTCIV @ 0x04AE;  
 

 /* Real Time Clock Time 0 */ 
__no_init volatile unsigned short RTCTIM0 @ 0x04B0;  
 

 /* Real Time Clock Time 1 */ 
__no_init volatile unsigned short RTCTIM1 @ 0x04B2;  
 

 /* Real Time Clock Date */ 
__no_init volatile unsigned short RTCDATE @ 0x04B4;  
 

 /* Real Time Clock Year */ 
__no_init volatile unsigned short RTCYEAR @ 0x04B6;  
 

 /* Real Time Clock Alarm Min/Hour */ 
__no_init volatile unsigned short RTCAMINHR @ 0x04B8;  
 

 /* Real Time Clock Alarm day of week/day */ 
__no_init volatile unsigned short RTCADOWDAY @ 0x04BA;  
 
 
#define __MSP430_HAS_RTC__          /* Definition to show that Module is available */

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


#define RTCSSEL_0           (0x0000)                   /* RTC Source Select ACLK */
#define RTCSSEL_1           (0x0400)                   /* RTC Source Select SMCLK */
#define RTCSSEL_2           (0x0800)                   /* RTC Source Select RT1PS */
#define RTCSSEL_3           (0x0C00)                   /* RTC Source Select RT1PS */
#define RTCSSEL__ACLK       (0x0000)                   /* RTC Source Select ACLK */
#define RTCSSEL__SMCLK      (0x0400)                   /* RTC Source Select SMCLK */
#define RTCSSEL__RT1PS      (0x0800)                   /* RTC Source Select RT1PS */
#define RTCTEV_0            (0x0000)                   /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100)                   /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200)                   /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300)                   /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000)                   /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100)                   /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__1200        (0x0200)                   /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV__0000        (0x0300)                   /* RTC Time Event: 3 (00:00 changed) */

#define RT0IP_0             (0x0000)                   /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004)                   /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008)                   /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000C)                   /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010)                   /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014)                   /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018)                   /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001C)                   /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0PSDIV_0          (0x0000)                   /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1          (0x0800)                   /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2          (0x1000)                   /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3          (0x1800)                   /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4          (0x2000)                   /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5          (0x2800)                   /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6          (0x3000)                   /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7          (0x3800)                   /* RTC Prescale Timer 0 Clock Divide /256 */


#define RT1IP_0             (0x0000)                   /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004)                   /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008)                   /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000C)                   /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010)                   /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014)                   /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018)                   /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001C)                   /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1PSDIV_0          (0x0000)                   /* RTC Prescale Timer 1 Clock Divide /2 */
#define RT1PSDIV_1          (0x0800)                   /* RTC Prescale Timer 1 Clock Divide /4 */
#define RT1PSDIV_2          (0x1000)                   /* RTC Prescale Timer 1 Clock Divide /8 */
#define RT1PSDIV_3          (0x1800)                   /* RTC Prescale Timer 1 Clock Divide /16 */
#define RT1PSDIV_4          (0x2000)                   /* RTC Prescale Timer 1 Clock Divide /32 */
#define RT1PSDIV_5          (0x2800)                   /* RTC Prescale Timer 1 Clock Divide /64 */
#define RT1PSDIV_6          (0x3000)                   /* RTC Prescale Timer 1 Clock Divide /128 */
#define RT1PSDIV_7          (0x3800)                   /* RTC Prescale Timer 1 Clock Divide /256 */

#define RT1SSEL_0           (0x0000)                   /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL_1           (0x4000)                   /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL_2           (0x8000)                   /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL_3           (0xC000)                   /* RTC Prescale Timer Source Select RT0PS */

 

/*-------------------------------------------------------------------------
 *   SYS
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short SYSCTL;  /* System control */ 
  
  struct
  {
    unsigned short SYSRIVECT     : 1;  /* SYS - RAM based interrupt vectors */ 
    unsigned short               : 1; 
    unsigned short SYSPMMPE      : 1;  /* SYS - PMM access protect */ 
    unsigned short               : 1; 
    unsigned short SYSBSLIND     : 1;  /* SYS - TCK/RST indication detected */ 
    unsigned short SYSJTAGPIN    : 1;  /* SYS - Dedicated JTAG pins enabled */ 
    unsigned short               : 2; 
  } SYSCTL_bit;  
} @ 0x0180;


enum {
  SYSRIVECT           = 0x0001,
  SYSPMMPE            = 0x0004,
  SYSBSLIND           = 0x0010,
  SYSJTAGPIN          = 0x0020,
};


__no_init volatile union
{
  unsigned short SYSBSLC;  /* Boot strap configuration area */ 
  
  struct
  {
    unsigned short SYSBSLSIZE0   : 1;  /* SYS - BSL Protection Size 0 */ 
    unsigned short SYSBSLSIZE1   : 1;  /* SYS - BSL Protection Size 1 */ 
    unsigned short SYSBSLR       : 1;  /* SYS - RAM assigned to BSL */ 
    unsigned short               : 11; 
    unsigned short SYSBSLOFF     : 1;  /* SYS - BSL Memeory disabled */ 
    unsigned short SYSBSLPE      : 1;  /* SYS - BSL Memory protection enalbed */ 
  } SYSBSLC_bit;  
} @ 0x0182;


enum {
  SYSBSLSIZE0         = 0x0001,
  SYSBSLSIZE1         = 0x0002,
  SYSBSLR             = 0x0004,
  SYSBSLOFF           = 0x4000,
  SYSBSLPE            = 0x8000,
};


__no_init volatile union
{
  unsigned short SYSJMBC;  /* JTAG mailbox control */ 
  
  struct
  {
    unsigned short JMBIN0FG      : 1;  /* SYS - Incoming JTAG Mailbox 0 Flag */ 
    unsigned short JMBIN1FG      : 1;  /* SYS - Incoming JTAG Mailbox 1 Flag */ 
    unsigned short JJMBOUT0FG    : 1;  /* SYS - Outgoing JTAG Mailbox 0 Flag */ 
    unsigned short JMBOUT1FG     : 1;  /* SYS - Outgoing JTAG Mailbox 1 Flag */ 
    unsigned short JMBMODE       : 1;  /* SYS - JMB 16/32 Bit Mode */ 
    unsigned short               : 1; 
    unsigned short JMBCLR0OFF    : 1;  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */ 
    unsigned short JMBCLR1OFF    : 1;  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */ 
  } SYSJMBC_bit;  
} @ 0x0186;


enum {
  JMBIN0FG            = 0x0001,
  JMBIN1FG            = 0x0002,
  JJMBOUT0FG          = 0x0004,
  JMBOUT1FG           = 0x0008,
  JMBMODE             = 0x0010,
  JMBCLR0OFF          = 0x0040,
  JMBCLR1OFF          = 0x0080,
};


 /* JTAG mailbox input 0 */ 
__no_init volatile unsigned short SYSJMBI0 @ 0x0188;  
 

 /* JTAG mailbox input 1 */ 
__no_init volatile unsigned short SYSJMBI1 @ 0x018A;  
 

 /* JTAG mailbox output 0 */ 
__no_init volatile unsigned short SYSJMBO0 @ 0x018C;  
 

 /* JTAG mailbox output 1 */ 
__no_init volatile unsigned short SYSJMBO1 @ 0x018E;  
 

 /* User NMI vector generator */ 
__no_init volatile unsigned short SYSUNIV @ 0x019A;  
 

 /* System NMI vector generator */ 
__no_init volatile unsigned short SYSSNIV @ 0x019C;  
 

 /* Reset vector generator */ 
__no_init volatile unsigned short SYSRSTIV @ 0x019E;  
 
 
#define __MSP430_HAS_SYS__          /* Definition to show that Module is available */


#define RTCSSEL_0           (0x0000)                   /* RTC Source Select ACLK */
#define RTCSSEL_1           (0x0400)                   /* RTC Source Select SMCLK */
#define RTCSSEL_2           (0x0800)                   /* RTC Source Select RT1PS */
#define RTCSSEL_3           (0x0C00)                   /* RTC Source Select RT1PS */
#define RTCSSEL__ACLK       (0x0000)                   /* RTC Source Select ACLK */
#define RTCSSEL__SMCLK      (0x0400)                   /* RTC Source Select SMCLK */
#define RTCSSEL__RT1PS      (0x0800)                   /* RTC Source Select RT1PS */
#define RTCTEV_0            (0x0000)                   /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100)                   /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200)                   /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300)                   /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000)                   /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100)                   /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__1200        (0x0200)                   /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV__0000        (0x0300)                   /* RTC Time Event: 3 (00:00 changed) */

#define RT0IP_0             (0x0000)                   /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004)                   /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008)                   /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000C)                   /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010)                   /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014)                   /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018)                   /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001C)                   /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0PSDIV_0          (0x0000)                   /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1          (0x0800)                   /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2          (0x1000)                   /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3          (0x1800)                   /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4          (0x2000)                   /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5          (0x2800)                   /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6          (0x3000)                   /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7          (0x3800)                   /* RTC Prescale Timer 0 Clock Divide /256 */


#define RT1IP_0             (0x0000)                   /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004)                   /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008)                   /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000C)                   /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010)                   /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014)                   /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018)                   /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001C)                   /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1PSDIV_0          (0x0000)                   /* RTC Prescale Timer 1 Clock Divide /2 */
#define RT1PSDIV_1          (0x0800)                   /* RTC Prescale Timer 1 Clock Divide /4 */
#define RT1PSDIV_2          (0x1000)                   /* RTC Prescale Timer 1 Clock Divide /8 */
#define RT1PSDIV_3          (0x1800)                   /* RTC Prescale Timer 1 Clock Divide /16 */
#define RT1PSDIV_4          (0x2000)                   /* RTC Prescale Timer 1 Clock Divide /32 */
#define RT1PSDIV_5          (0x2800)                   /* RTC Prescale Timer 1 Clock Divide /64 */
#define RT1PSDIV_6          (0x3000)                   /* RTC Prescale Timer 1 Clock Divide /128 */
#define RT1PSDIV_7          (0x3800)                   /* RTC Prescale Timer 1 Clock Divide /256 */

#define RT1SSEL_0           (0x0000)                   /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL_1           (0x4000)                   /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL_2           (0x8000)                   /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL_3           (0xC000)                   /* RTC Prescale Timer Source Select RT0PS */

/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004)    /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_ACCVIFG    (0x0006)    /* SYSUNIV : Access Violation - ACCVIFG */
#define SYSUNIV_SYSBERRIV  (0x0008)    /* SYSUNIV : Bus Error - SYSBERRIV */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000)    /* No Interrupt pending */
#define SYSSNIV_SVMLIFG    (0x0002)    /* SYSSNIV : SVMLIFG */
#define SYSSNIV_SVMHIFG    (0x0004)    /* SYSSNIV : SVMHIFG */
#define SYSSNIV_DLYLIFG    (0x0006)    /* SYSSNIV : DLYLIFG */
#define SYSSNIV_DLYHIFG    (0x0008)    /* SYSSNIV : DLYHIFG */
#define SYSSNIV_VMAIFG     (0x000A)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x000C)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x000E)    /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_VLRLIFG    (0x0010)    /* SYSSNIV : VLRLIFG */
#define SYSSNIV_VLRHIFG    (0x0012)    /* SYSSNIV : VLRHIFG */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002)    /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI    (0x0004)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0006)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU    (0x0008)    /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV     (0x000A)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSL      (0x000C)    /* SYSRSTIV : SVSL */
#define SYSRSTIV_SVSH      (0x000E)    /* SYSRSTIV : SVSH */
#define SYSRSTIV_SVML_OVP  (0x0010)    /* SYSRSTIV : SVML_OVP */
#define SYSRSTIV_SVMH_OVP  (0x0012)    /* SYSRSTIV : SVMH_OVP */
#define SYSRSTIV_DOPOR     (0x0014)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x0016)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0018)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_KEYV      (0x001A)    /* SYSRSTIV : Flash Key violation */
#define SYSRSTIV_PLLUL     (0x001C)    /* SYSRSTIV : PLL unlock */
#define SYSRSTIV_PERF      (0x001E)    /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PSSKEY    (0x0020)    /* SYSRSTIV : PSSKEY violation */


 

/*-------------------------------------------------------------------------
 *   Timer0_A5
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short TA0CTL;  /* Timer0_A5 Control */ 
  
  struct
  {
    unsigned short TAIFG         : 1;  /* Timer A counter interrupt flag */ 
    unsigned short TAIE          : 1;  /* Timer A counter interrupt enable */ 
    unsigned short TACLR         : 1;  /* Timer A counter clear */ 
    unsigned short               : 1; 
    unsigned short MC0           : 1;  /* Timer A mode control 0 */ 
    unsigned short MC1           : 1;  /* Timer A mode control 1 */ 
    unsigned short ID0           : 1;  /* Timer A clock input divider 0 */ 
    unsigned short ID1           : 1;  /* Timer A clock input divider 1 */ 
    unsigned short TASSEL0       : 1;  /* Timer A clock source select 1 */ 
    unsigned short TASSEL1       : 1;  /* Timer A clock source select 0 */ 
  } TA0CTL_bit;  
} @ 0x0340;




__no_init volatile union
{
  unsigned short TA0CCTL0;  /* Timer0_A5 Capture/Compare Control 0 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA0CCTL0_bit;  
} @ 0x0342;




__no_init volatile union
{
  unsigned short TA0CCTL1;  /* Timer0_A5 Capture/Compare Control 1 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA0CCTL1_bit;  
} @ 0x0344;




__no_init volatile union
{
  unsigned short TA0CCTL2;  /* Timer0_A5 Capture/Compare Control 2 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA0CCTL2_bit;  
} @ 0x0346;




__no_init volatile union
{
  unsigned short TA0CCTL3;  /* Timer0_A5 Capture/Compare Control 3 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA0CCTL3_bit;  
} @ 0x0348;




__no_init volatile union
{
  unsigned short TA0CCTL4;  /* Timer0_A5 Capture/Compare Control 4 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA0CCTL4_bit;  
} @ 0x034A;




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
__no_init volatile unsigned __READ short TA0IV @ 0x036E;  
 

__no_init volatile union
{
  unsigned short TA0EX0;  /* Timer0_A3 Expansion Register 0 */ 
  
  struct
  {
    unsigned short TAIDEX0       : 1;  /* Timer A Input divider expansion Bit: 0 */ 
    unsigned short TAIDEX1       : 1;  /* Timer A Input divider expansion Bit: 1 */ 
    unsigned short TAIDEX2       : 1;  /* Timer A Input divider expansion Bit: 2 */ 
  } TA0EX0_bit;  
} @ 0x0360;



 
#define __MSP430_HAS_T0A5__           /* Definition to show that Module is available */

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


/* TAxEX0 Control Bits */

#define TAIDEX_0            (0*0x0001u) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (1*0x0001u) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (2*0x0001u) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (3*0x0001u) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (4*0x0001u) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (5*0x0001u) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (6*0x0001u) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (7*0x0001u) /* Timer A Input divider expansion : /8 */
 

/*-------------------------------------------------------------------------
 *   Timer1_A3
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short TA1CTL;  /* Timer1_A3 Control */ 
  
  struct
  {
    unsigned short TAIFG         : 1;  /* Timer A counter interrupt flag */ 
    unsigned short TAIE          : 1;  /* Timer A counter interrupt enable */ 
    unsigned short TACLR         : 1;  /* Timer A counter clear */ 
    unsigned short               : 1; 
    unsigned short MC0           : 1;  /* Timer A mode control 0 */ 
    unsigned short MC1           : 1;  /* Timer A mode control 1 */ 
    unsigned short ID0           : 1;  /* Timer A clock input divider 0 */ 
    unsigned short ID1           : 1;  /* Timer A clock input divider 1 */ 
    unsigned short TASSEL0       : 1;  /* Timer A clock source select 1 */ 
    unsigned short TASSEL1       : 1;  /* Timer A clock source select 0 */ 
  } TA1CTL_bit;  
} @ 0x0380;


enum {
  TAIFG               = 0x0001,
  TAIE                = 0x0002,
  TACLR               = 0x0004,
  MC0                 = 0x0010,
  MC1                 = 0x0020,
  ID0                 = 0x0040,
  ID1                 = 0x0080,
  TASSEL0             = 0x0100,
  TASSEL1             = 0x0200,
};


__no_init volatile union
{
  unsigned short TA1CCTL0;  /* Timer1_A3 Capture/Compare Control 0 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA1CCTL0_bit;  
} @ 0x0382;


enum {
  CCIFG               = 0x0001,
  COV                 = 0x0002,
  OUT                 = 0x0004,
  CCI                 = 0x0008,
  CCIE                = 0x0010,
  OUTMOD0             = 0x0020,
  OUTMOD1             = 0x0040,
  OUTMOD2             = 0x0080,
  CAP                 = 0x0100,
  SCCI                = 0x0400,
  SCS                 = 0x0800,
  CCIS0               = 0x1000,
  CCIS1               = 0x2000,
  CM0                 = 0x4000,
  CM1                 = 0x8000,
};


__no_init volatile union
{
  unsigned short TA1CCTL1;  /* Timer1_A3 Capture/Compare Control 1 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA1CCTL1_bit;  
} @ 0x0384;




__no_init volatile union
{
  unsigned short TA1CCTL2;  /* Timer1_A3 Capture/Compare Control 2 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD0       : 1;  /* Output mode 0 */ 
    unsigned short OUTMOD1       : 1;  /* Output mode 1 */ 
    unsigned short OUTMOD2       : 1;  /* Output mode 2 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short               : 1; 
    unsigned short SCCI          : 1;  /* Latched capture signal (read) */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS0         : 1;  /* Capture input select 0 */ 
    unsigned short CCIS1         : 1;  /* Capture input select 1 */ 
    unsigned short CM0           : 1;  /* Capture mode 0 */ 
    unsigned short CM1           : 1;  /* Capture mode 1 */ 
  } TA1CCTL2_bit;  
} @ 0x0386;




 /* Timer1_A3 */ 
__no_init volatile unsigned short TA1R @ 0x0390;  
 

 /* Timer1_A3 Capture/Compare 0 */ 
__no_init volatile unsigned short TA1CCR0 @ 0x0392;  
 

 /* Timer1_A3 Capture/Compare 1 */ 
__no_init volatile unsigned short TA1CCR1 @ 0x0394;  
 

 /* Timer1_A3 Capture/Compare 2 */ 
__no_init volatile unsigned short TA1CCR2 @ 0x0396;  
 

 /* Timer1_A3 Interrupt Vector Word */ 
__no_init volatile unsigned __READ short TA1IV @ 0x03AE;  
 

__no_init volatile union
{
  unsigned short TA1EX0;  /* Timer1_A3 Expansion Register 0 */ 
  
  struct
  {
    unsigned short TAIDEX0       : 1;  /* Timer A Input divider expansion Bit: 0 */ 
    unsigned short TAIDEX1       : 1;  /* Timer A Input divider expansion Bit: 1 */ 
    unsigned short TAIDEX2       : 1;  /* Timer A Input divider expansion Bit: 2 */ 
  } TA1EX0_bit;  
} @ 0x03A0;


enum {
  TAIDEX0             = 0x0001,
  TAIDEX1             = 0x0002,
  TAIDEX2             = 0x0004,
};

 
#define __MSP430_HAS_T1A3__        /* Definition to show that Module is available */

#define MC_0            (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1            (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2            (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3            (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0            (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1            (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2            (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3            (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0        (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1        (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2        (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3        (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define OUTMOD_0        (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1        (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2        (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3        (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4        (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5        (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6        (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7        (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0          (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1          (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2          (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3          (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0            (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1            (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2            (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3            (3*0x4000u) /* Capture mode: 1 - both edges */

/* Alternate register names */
#define CCTL0           TACCTL0   /* Timer A Capture/Compare Control 0 */
#define CCTL1           TACCTL1   /* Timer A Capture/Compare Control 1 */
#define CCTL2           TACCTL2   /* Timer A Capture/Compare Control 2 */
#define CCR0            TACCR0    /* Timer A Capture/Compare 0 */
#define CCR1            TACCR1    /* Timer A Capture/Compare 1 */
#define CCR2            TACCR2    /* Timer A Capture/Compare 2 */
#define CCTL0_          TACCTL0   /* Timer A Capture/Compare Control 0 */
#define CCTL1_          TACCTL1   /* Timer A Capture/Compare Control 1 */
#define CCTL2_          TACCTL2   /* Timer A Capture/Compare Control 2 */
#define CCR0_           TACCR0    /* Timer A Capture/Compare 0 */
#define CCR1_           TACCR1    /* Timer A Capture/Compare 1 */
#define CCR2_           TACCR2    /* Timer A Capture/Compare 2 */
 

/*-------------------------------------------------------------------------
 *   Timer B7
 *-------------------------------------------------------------------------*/


 /* Timer B Interrupt Vector Word */ 
__no_init volatile unsigned __READ short TB0IV @ 0x03EE;  
 

__no_init volatile union
{
  unsigned short TB0CTL;  /* Timer B Control */ 
  
  struct
  {
    unsigned short TBIFG         : 1;  /* Timer B interrupt flag */ 
    unsigned short TBIE          : 1;  /* Timer B interrupt enable */ 
    unsigned short TBCLR         : 1;  /* Timer B counter clear */ 
    unsigned short               : 1; 
    unsigned short TBMC          : 2;  /* Timer B mode control 1 */ 
    unsigned short TBID          : 2;  /* Timer B clock input divider */ 
    unsigned short TBSSEL        : 2;  /* Timer B clock source select */ 
    unsigned short               : 1; 
    unsigned short CNTL          : 2;  /* Timer B Control */ 
    unsigned short TBCLGRP       : 2;  /* Timer B Compare latch load group */ 
    unsigned short               : 1; 
  } TB0CTL_bit;  
} @ 0x03C0;


enum {
  TBIFG               = 0x0001,
  TBIE                = 0x0002,
  TBCLR               = 0x0004,
  TBMC                = 0x0020,
  TBID                = 0x0080,
  TBSSEL              = 0x0200,
  CNTL                = 0x1000,
  TBCLGRP             = 0x4000,
};


__no_init volatile union
{
  unsigned short TB0CCTL0;  /* Timer B Capture/Compare Control 0 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL0_bit;  
} @ 0x03C2;


enum {
  CLLD                = 0x0400,
};


__no_init volatile union
{
  unsigned short TB0CCTL1;  /* Timer B Capture/Compare Control 1 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL1_bit;  
} @ 0x03C4;




__no_init volatile union
{
  unsigned short TB0CCTL2;  /* Timer B Capture/Compare Control 2 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL2_bit;  
} @ 0x03C6;




__no_init volatile union
{
  unsigned short TB0CCTL3;  /* Timer B Capture/Compare Control 3 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL3_bit;  
} @ 0x03C8;




__no_init volatile union
{
  unsigned short TB0CCTL4;  /* Timer B Capture/Compare Control 4 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL4_bit;  
} @ 0x03CA;




__no_init volatile union
{
  unsigned short TB0CCTL5;  /* Timer B Capture/Compare Control 5 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL5_bit;  
} @ 0x03CC;




__no_init volatile union
{
  unsigned short TB0CCTL6;  /* Timer B Capture/Compare Control 6 */ 
  
  struct
  {
    unsigned short CCIFG         : 1;  /* Capture/compare interrupt flag */ 
    unsigned short COV           : 1;  /* Capture/compare overflow flag */ 
    unsigned short OUT           : 1;  /* PWM Output signal if output mode 0 */ 
    unsigned short CCI           : 1;  /* Capture input signal (read) */ 
    unsigned short CCIE          : 1;  /* Capture/compare interrupt enable */ 
    unsigned short OUTMOD        : 3;  /* Output mode 0 */ 
    unsigned short CAP           : 1;  /* Capture mode: 1 /Compare mode : 0 */ 
    unsigned short CLLD          : 2;  /* Compare latch load source */ 
    unsigned short SCS           : 1;  /* Capture sychronize */ 
    unsigned short CCIS          : 2;  /* Capture input select */ 
    unsigned short CM            : 2;  /* Capture mode */ 
  } TB0CCTL6_bit;  
} @ 0x03CE;




 /* Timer B */ 
__no_init volatile unsigned short TB0R @ 0x03D0;  
 

 /* Timer B Capture/Compare 0 */ 
__no_init volatile unsigned short TB0CCR0 @ 0x03D2;  
 

 /* Timer B Capture/Compare 1 */ 
__no_init volatile unsigned short TB0CCR1 @ 0x03D4;  
 

 /* Timer B Capture/Compare 2 */ 
__no_init volatile unsigned short TB0CCR2 @ 0x03D6;  
 

 /* Timer B Capture/Compare 3 */ 
__no_init volatile unsigned short TB0CCR3 @ 0x03D8;  
 

 /* Timer B Capture/Compare 4 */ 
__no_init volatile unsigned short TB0CCR4 @ 0x03DA;  
 

 /* Timer B Capture/Compare 5 */ 
__no_init volatile unsigned short TB0CCR5 @ 0x03DC;  
 

 /* Timer B Capture/Compare 6 */ 
__no_init volatile unsigned short TB0CCR6 @ 0x03DE;  
 

__no_init volatile union
{
  unsigned short TB0EX0;  /* Timer_B7 Expansion Register 0 */ 
  
  struct
  {
    unsigned short TBIDEX        : 3; 
  } TB0EX0_bit;  
} @ 0x03E0;



 
#define __MSP430_HAS_TB7__            /* Definition to show that Module is available */

#define TBSSEL_0      (0*0x0100u)  /* Clock Source: TBCLK */
#define TBSSEL_1      (1*0x0100u)  /* Clock Source: ACLK  */
#define TBSSEL_2      (2*0x0100u)  /* Clock Source: SMCLK */
#define TBSSEL_3      (3*0x0100u)  /* Clock Source: INCLK */
#define CNTL_0        (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL_1        (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL_2        (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL_3        (3*0x0800u)  /* Counter lenght:  8 bit */
#define SHR_0         (0*0x2000u)  /* Timer B Group: 0 - individually */
#define SHR_1         (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2         (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3         (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0     (0*0x2000u)  /* Timer B Group: 0 - individually */
#define TBCLGRP_1     (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2     (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3     (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */

#define CLLD1         (0x0400)     /* Compare latch load source 1 */
#define CLLD0         (0x0200)     /* Compare latch load source 0 */

#define SLSHR1        (0x0400)     /* Compare latch load source 1 */
#define SLSHR0        (0x0200)     /* Compare latch load source 0 */

#define SLSHR_0       (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1       (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2       (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3       (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0        (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define CLLD_1        (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2        (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define CLLD_3        (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TBEX0 Control Bits */

#define TBIDEX_0            (0*0x0001u) /* Timer B Input divider expansion : /1 */
#define TBIDEX_1            (1*0x0001u) /* Timer B Input divider expansion : /2 */
#define TBIDEX_2            (2*0x0001u) /* Timer B Input divider expansion : /3 */
#define TBIDEX_3            (3*0x0001u) /* Timer B Input divider expansion : /4 */
#define TBIDEX_4            (4*0x0001u) /* Timer B Input divider expansion : /5 */
#define TBIDEX_5            (5*0x0001u) /* Timer B Input divider expansion : /6 */
#define TBIDEX_6            (6*0x0001u) /* Timer B Input divider expansion : /7 */
#define TBIDEX_7            (7*0x0001u) /* Timer B Input divider expansion : /8 */
#define TBIDEX__1           (0*0x0001u) /* Timer B Input divider expansion : /1 */
#define TBIDEX__2           (1*0x0001u) /* Timer B Input divider expansion : /2 */
#define TBIDEX__3           (2*0x0001u) /* Timer B Input divider expansion : /3 */
#define TBIDEX__4           (3*0x0001u) /* Timer B Input divider expansion : /4 */
#define TBIDEX__5           (4*0x0001u) /* Timer B Input divider expansion : /5 */
#define TBIDEX__6           (5*0x0001u) /* Timer B Input divider expansion : /6 */
#define TBIDEX__7           (6*0x0001u) /* Timer B Input divider expansion : /7 */
#define TBIDEX__8           (7*0x0001u) /* Timer B Input divider expansion : /8 */

 

/*-------------------------------------------------------------------------
 *   UCS  Unified System Clock
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short UCSCTL0;  /* UCS Control Register 0 */ 
  
  struct
  {
    unsigned short               : 3; 
    unsigned short MOD0          : 1;  /* Modulation Bit Counter Bit : 0 */ 
    unsigned short MOD1          : 1;  /* Modulation Bit Counter Bit : 1 */ 
    unsigned short MOD2          : 1;  /* Modulation Bit Counter Bit : 2 */ 
    unsigned short MOD3          : 1;  /* Modulation Bit Counter Bit : 3 */ 
    unsigned short MOD4          : 1;  /* Modulation Bit Counter Bit : 4 */ 
    unsigned short DCO0          : 1;  /* DCO TAP Bit : 0 */ 
    unsigned short DCO1          : 1;  /* DCO TAP Bit : 1 */ 
    unsigned short DCO2          : 1;  /* DCO TAP Bit : 2 */ 
    unsigned short DCO3          : 1;  /* DCO TAP Bit : 3 */ 
    unsigned short DCO4          : 1;  /* DCO TAP Bit : 4 */ 
  } UCSCTL0_bit;  
} @ 0x0160;


enum {
  MOD0                = 0x0008,
  MOD1                = 0x0010,
  MOD2                = 0x0020,
  MOD3                = 0x0040,
  MOD4                = 0x0080,
  DCO0                = 0x0100,
  DCO1                = 0x0200,
  DCO2                = 0x0400,
  DCO3                = 0x0800,
  DCO4                = 0x1000,
};


__no_init volatile union
{
  unsigned short UCSCTL1;  /* UCS Control Register 1 */ 
  
  struct
  {
    unsigned short DISMOD        : 1;  /* Disable Modulation */ 
    unsigned short DCOR          : 1;  /* DCO External Resistor Select */ 
    unsigned short               : 2; 
    unsigned short DCORSEL0      : 1;  /* DCO Freq. Range Select Bit : 0 */ 
    unsigned short DCORSEL1      : 1;  /* DCO Freq. Range Select Bit : 1 */ 
    unsigned short DCORSEL2      : 1;  /* DCO Freq. Range Select Bit : 2 */ 
  } UCSCTL1_bit;  
} @ 0x0162;


enum {
  DISMOD              = 0x0001,
  DCOR                = 0x0002,
  DCORSEL0            = 0x0010,
  DCORSEL1            = 0x0020,
  DCORSEL2            = 0x0040,
};


__no_init volatile union
{
  unsigned short UCSCTL2;  /* UCS Control Register 2 */ 
  
  struct
  {
    unsigned short FLLN0         : 1;  /* FLL Multipier Bit : 0 */ 
    unsigned short FLLN1         : 1;  /* FLL Multipier Bit : 1 */ 
    unsigned short FLLN2         : 1;  /* FLL Multipier Bit : 2 */ 
    unsigned short FLLN3         : 1;  /* FLL Multipier Bit : 3 */ 
    unsigned short FLLN4         : 1;  /* FLL Multipier Bit : 4 */ 
    unsigned short FLLN5         : 1;  /* FLL Multipier Bit : 5 */ 
    unsigned short FLLN6         : 1;  /* FLL Multipier Bit : 6 */ 
    unsigned short FLLN7         : 1;  /* FLL Multipier Bit : 7 */ 
    unsigned short FLLN8         : 1;  /* FLL Multipier Bit : 8 */ 
    unsigned short FLLN9         : 1;  /* FLL Multipier Bit : 9 */ 
    unsigned short               : 2; 
    unsigned short FLLD0         : 1;  /* Loop Divider Bit : 0 */ 
    unsigned short FLLD1         : 1;  /* Loop Divider Bit : 1 */ 
    unsigned short FLLD2         : 1;  /* Loop Divider Bit : 1 */ 
  } UCSCTL2_bit;  
} @ 0x0164;


enum {
  FLLN0               = 0x0001,
  FLLN1               = 0x0002,
  FLLN2               = 0x0004,
  FLLN3               = 0x0008,
  FLLN4               = 0x0010,
  FLLN5               = 0x0020,
  FLLN6               = 0x0040,
  FLLN7               = 0x0080,
  FLLN8               = 0x0100,
  FLLN9               = 0x0200,
  FLLD0               = 0x1000,
  FLLD1               = 0x2000,
  FLLD2               = 0x4000,
};


__no_init volatile union
{
  unsigned short UCSCTL3;  /* UCS Control Register 3 */ 
  
  struct
  {
    unsigned short FLLREFDIV0    : 1;  /* Reference Divider Bit : 0 */ 
    unsigned short FLLREFDIV1    : 1;  /* Reference Divider Bit : 1 */ 
    unsigned short FLLREFDIV2    : 1;  /* Reference Divider Bit : 2 */ 
    unsigned short               : 1; 
    unsigned short SELREF0       : 1;  /* FLL Reference Clock Select Bit : 0 */ 
    unsigned short SELREF1       : 1;  /* FLL Reference Clock Select Bit : 1 */ 
    unsigned short SELREF2       : 1;  /* FLL Reference Clock Select Bit : 2 */ 
  } UCSCTL3_bit;  
} @ 0x0166;


enum {
  FLLREFDIV0          = 0x0001,
  FLLREFDIV1          = 0x0002,
  FLLREFDIV2          = 0x0004,
  SELREF0             = 0x0010,
  SELREF1             = 0x0020,
  SELREF2             = 0x0040,
};


__no_init volatile union
{
  unsigned short UCSCTL4;  /* UCS Control Register 4 */ 
  
  struct
  {
    unsigned short SELM0         : 1;  /* MCLK Source Select Bit: 0 */ 
    unsigned short SELM1         : 1;  /* MCLK Source Select Bit: 1 */ 
    unsigned short SELM2         : 1;  /* MCLK Source Select Bit: 2 */ 
    unsigned short               : 1; 
    unsigned short SELS0         : 1;  /* SMCLK Source Select Bit: 0 */ 
    unsigned short SELS1         : 1;  /* SMCLK Source Select Bit: 1 */ 
    unsigned short SELS2         : 1;  /* SMCLK Source Select Bit: 2 */ 
    unsigned short               : 1; 
    unsigned short SELA0         : 1;  /* ACLK Source Select Bit: 0 */ 
    unsigned short SELA1         : 1;  /* ACLK Source Select Bit: 1 */ 
    unsigned short SELA2         : 1;  /* ACLK Source Select Bit: 2 */ 
  } UCSCTL4_bit;  
} @ 0x0168;


enum {
  SELM0               = 0x0001,
  SELM1               = 0x0002,
  SELM2               = 0x0004,
  SELS0               = 0x0010,
  SELS1               = 0x0020,
  SELS2               = 0x0040,
  SELA0               = 0x0100,
  SELA1               = 0x0200,
  SELA2               = 0x0400,
};


__no_init volatile union
{
  unsigned short UCSCTL5;  /* UCS Control Register 5 */ 
  
  struct
  {
    unsigned short DIVM0         : 1;  /* MCLK Divider Bit: 0 */ 
    unsigned short DIVM1         : 1;  /* MCLK Divider Bit: 1 */ 
    unsigned short DIVM2         : 1;  /* MCLK Divider Bit: 2 */ 
    unsigned short               : 1; 
    unsigned short DIVS0         : 1;  /* SMCLK Divider Bit: 0 */ 
    unsigned short DIVS1         : 1;  /* SMCLK Divider Bit: 1 */ 
    unsigned short DIVS2         : 1;  /* SMCLK Divider Bit: 2 */ 
    unsigned short               : 1; 
    unsigned short DIVA0         : 1;  /* ACLK Divider Bit: 0 */ 
    unsigned short DIVA1         : 1;  /* ACLK Divider Bit: 1 */ 
    unsigned short DIVA2         : 1;  /* ACLK Divider Bit: 2 */ 
    unsigned short               : 1; 
    unsigned short DIVPA0        : 1;  /* ACLK from Pin Divider Bit: 0 */ 
    unsigned short DIVPA1        : 1;  /* ACLK from Pin Divider Bit: 1 */ 
    unsigned short DIVPA2        : 1;  /* ACLK from Pin Divider Bit: 2 */ 
  } UCSCTL5_bit;  
} @ 0x016A;


enum {
  DIVM0               = 0x0001,
  DIVM1               = 0x0002,
  DIVM2               = 0x0004,
  DIVS0               = 0x0010,
  DIVS1               = 0x0020,
  DIVS2               = 0x0040,
  DIVA0               = 0x0100,
  DIVA1               = 0x0200,
  DIVA2               = 0x0400,
  DIVPA0              = 0x1000,
  DIVPA1              = 0x2000,
  DIVPA2              = 0x4000,
};


__no_init volatile union
{
  unsigned short UCSCTL6;  /* UCS Control Register 6 */ 
  
  struct
  {
    unsigned short XT1OFF        : 1;  /* High Frequency Oscillator 1 (XT1) disable */ 
    unsigned short SMCLKOFF      : 1;  /* SMCLK Off */ 
    unsigned short XCAP0         : 1;  /* XIN/XOUT Cap Bit: 0 */ 
    unsigned short XCAP1         : 1;  /* XIN/XOUT Cap Bit: 1 */ 
    unsigned short XT1BYPASS     : 1;  /* XT1 bypass mode : 0: internal 1:sourced from external pin */ 
    unsigned short XTS           : 1;  /* 1: Selects high-freq. oscillator */ 
    unsigned short XT1DRIVE0     : 1;  /* XT1 Drive Level mode Bit 0 */ 
    unsigned short XT1DRIVE1     : 1;  /* XT1 Drive Level mode Bit 1 */ 
    unsigned short XT2OFF        : 1;  /* High Frequency Oscillator 2 (XT2) disable */ 
    unsigned short               : 3; 
    unsigned short XT2BYPASS     : 1;  /* XT2 bypass mode : 0: internal 1:sourced from external pin */ 
    unsigned short               : 1; 
    unsigned short XT2DRIVE0     : 1;  /* XT2 Drive Level mode Bit 0 */ 
    unsigned short XT2DRIVE1     : 1;  /* XT2 Drive Level mode Bit 1 */ 
  } UCSCTL6_bit;  
} @ 0x016C;


enum {
  XT1OFF              = 0x0001,
  SMCLKOFF            = 0x0002,
  XCAP0               = 0x0004,
  XCAP1               = 0x0008,
  XT1BYPASS           = 0x0010,
  XTS                 = 0x0020,
  XT1DRIVE0           = 0x0040,
  XT1DRIVE1           = 0x0080,
  XT2OFF              = 0x0100,
  XT2BYPASS           = 0x1000,
  XT2DRIVE0           = 0x4000,
  XT2DRIVE1           = 0x8000,
};


__no_init volatile union
{
  unsigned short UCSCTL7;  /* UCS Control Register 7 */ 
  
  struct
  {
    unsigned short DCOFFG        : 1;  /* DCO Fault Flag */ 
    unsigned short XT1LFOFFG     : 1;  /* XT1 Low Frequency Oscillator Fault Flag */ 
    unsigned short XT1HFOFFG     : 1;  /* XT1 High Frequency Oscillator 1 Fault Flag */ 
    unsigned short XT2OFFG       : 1;  /* High Frequency Oscillator 2 Fault Flag */ 
  } UCSCTL7_bit;  
} @ 0x016E;


enum {
  DCOFFG              = 0x0001,
  XT1LFOFFG           = 0x0002,
  XT1HFOFFG           = 0x0004,
  XT2OFFG             = 0x0008,
};


__no_init volatile union
{
  unsigned short UCSCTL8;  /* UCS Control Register 8 */ 
  
  struct
  {
    unsigned short ACLKREQEN     : 1;  /* ACLK Clock Request Enable */ 
    unsigned short MCLKREQEN     : 1;  /* MCLK Clock Request Enable */ 
    unsigned short SMCLKREQEN    : 1;  /* SMCLK Clock Request Enable */ 
    unsigned short MODOSCREQEN   : 1;  /* MODOSC Clock Request Enable */ 
  } UCSCTL8_bit;  
} @ 0x0170;


enum {
  ACLKREQEN           = 0x0001,
  MCLKREQEN           = 0x0002,
  SMCLKREQEN          = 0x0004,
  MODOSCREQEN         = 0x0008,
};

 
#define __MSP430_HAS_UCS__           /* Definition to show that Module is available */

/* UCSCTL1 Control Bits */
#define DCORSEL_0           (0x0000)    /* DCO RSEL 0 */
#define DCORSEL_1           (0x0010)    /* DCO RSEL 1 */
#define DCORSEL_2           (0x0020)    /* DCO RSEL 2 */
#define DCORSEL_3           (0x0030)    /* DCO RSEL 3 */
#define DCORSEL_4           (0x0040)    /* DCO RSEL 4 */
#define DCORSEL_5           (0x0050)    /* DCO RSEL 5 */
#define DCORSEL_6           (0x0060)    /* DCO RSEL 6 */
#define DCORSEL_7           (0x0070)    /* DCO RSEL 7 */

#define FLLD_0             (0x0000)    /* Multiply Selected Loop Freq. 1 */
#define FLLD_1             (0x1000)    /* Multiply Selected Loop Freq. 2 */
#define FLLD_2             (0x2000)    /* Multiply Selected Loop Freq. 4 */
#define FLLD_3             (0x3000)    /* Multiply Selected Loop Freq. 8 */
#define FLLD_4             (0x4000)    /* Multiply Selected Loop Freq. 16 */
#define FLLD_5             (0x5000)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_6             (0x6000)    /* Multiply Selected Loop Freq. 32 */
#define FLLD_7             (0x7000)    /* Multiply Selected Loop Freq. 32 */
#define FLLD__1            (0x0000)    /* Multiply Selected Loop Freq. By 1 */
#define FLLD__2            (0x1000)    /* Multiply Selected Loop Freq. By 2 */
#define FLLD__4            (0x2000)    /* Multiply Selected Loop Freq. By 4 */
#define FLLD__8            (0x3000)    /* Multiply Selected Loop Freq. By 8 */
#define FLLD__16           (0x4000)    /* Multiply Selected Loop Freq. By 16 */
#define FLLD__32           (0x5000)    /* Multiply Selected Loop Freq. By 32 */

#define FLLREFDIV_0         (0x0000)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV_1         (0x0001)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV_2         (0x0002)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV_3         (0x0003)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV_4         (0x0004)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV_5         (0x0005)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_6         (0x0006)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_7         (0x0007)    /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV__1        (0x0000)    /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV__2        (0x0001)    /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV__4        (0x0002)    /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV__8        (0x0003)    /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV__12       (0x0004)    /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV__16       (0x0005)    /* Reference Divider: f(LFCLK)/16 */
#define SELREF_0            (0x0000)    /* FLL Reference Clock Select 0 */
#define SELREF_1            (0x0010)    /* FLL Reference Clock Select 1 */
#define SELREF_2            (0x0020)    /* FLL Reference Clock Select 2 */
#define SELREF_3            (0x0030)    /* FLL Reference Clock Select 3 */
#define SELREF_4            (0x0040)    /* FLL Reference Clock Select 4 */
#define SELREF_5            (0x0050)    /* FLL Reference Clock Select 5 */
#define SELREF_6            (0x0060)    /* FLL Reference Clock Select 6 */
#define SELREF_7            (0x0070)    /* FLL Reference Clock Select 7 */
#define SELREF__XT1CLK      (0x0000)    /* Multiply Selected Loop Freq. By XT1CLK */
#define SELREF__VLOCLK      (0x0010)    /* Multiply Selected Loop Freq. By VLOCLK */
#define SELREF__REFOCLK     (0x0020)    /* Multiply Selected Loop Freq. By REFOCLK */
#define SELREF__XT2CLK      (0x0050)    /* Multiply Selected Loop Freq. By XT2CLK */

#define SELM_0              (0x0000)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003)   /* MCLK Source Select 3 */
#define SELM_4              (0x0004)   /* MCLK Source Select 4 */
#define SELM_5              (0x0005)   /* MCLK Source Select 5 */
#define SELM_6              (0x0006)   /* MCLK Source Select 6 */
#define SELM_7              (0x0007)   /* MCLK Source Select 7 */
#define SELM__XT1CLK        (0x0000)   /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK        (0x0001)   /* MCLK Source Select VLOCLK */
#define SELM__REFOCLK       (0x0002)   /* MCLK Source Select REFOCLK */
#define SELM__DCOCLK        (0x0003)   /* MCLK Source Select DCOCLK */
#define SELM__DCOCLKDIV     (0x0004)   /* MCLK Source Select DCOCLKDIV */
#define SELM__XT2CLK        (0x0005)   /* MCLK Source Select XT2CLK */

#define SELS_0              (0x0000)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030)   /* SMCLK Source Select 3 */
#define SELS_4              (0x0040)   /* SMCLK Source Select 4 */
#define SELS_5              (0x0050)   /* SMCLK Source Select 5 */
#define SELS_6              (0x0060)   /* SMCLK Source Select 6 */
#define SELS_7              (0x0070)   /* SMCLK Source Select 7 */
#define SELS__XT1CLK        (0x0000)   /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK        (0x0010)   /* SMCLK Source Select VLOCLK */
#define SELS__REFOCLK       (0x0020)   /* SMCLK Source Select REFOCLK */
#define SELS__DCOCLK        (0x0030)   /* SMCLK Source Select DCOCLK */
#define SELS__DCOCLKDIV     (0x0040)   /* SMCLK Source Select DCOCLKDIV */
#define SELS__XT2CLK        (0x0050)   /* SMCLK Source Select XT2CLK */

#define SELA_0              (0x0000)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300)   /* ACLK Source Select 3 */
#define SELA_4              (0x0400)   /* ACLK Source Select 4 */
#define SELA_5              (0x0500)   /* ACLK Source Select 5 */
#define SELA_6              (0x0600)   /* ACLK Source Select 6 */
#define SELA_7              (0x0700)   /* ACLK Source Select 7 */
#define SELA__XT1CLK        (0x0000)   /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK        (0x0100)   /* ACLK Source Select VLOCLK */
#define SELA__REFOCLK       (0x0200)   /* ACLK Source Select REFOCLK */
#define SELA__DCOCLK        (0x0300)   /* ACLK Source Select DCOCLK */
#define SELA__DCOCLKDIV     (0x0400)   /* ACLK Source Select DCOCLKDIV */
#define SELA__XT2CLK        (0x0500)   /* ACLK Source Select XT2CLK */

#define DIVM_0              (0x0000)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005)    /* MCLK Source Divider 5 */
#define DIVM_6              (0x0006)    /* MCLK Source Divider 6 */
#define DIVM_7              (0x0007)    /* MCLK Source Divider 7 */
#define DIVM__1             (0x0000)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050)    /* SMCLK Source Divider 5 */
#define DIVS_6              (0x0060)    /* SMCLK Source Divider 6 */
#define DIVS_7              (0x0070)    /* SMCLK Source Divider 7 */
#define DIVS__1             (0x0000)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500)    /* ACLK Source Divider 5 */
#define DIVA_6              (0x0600)    /* ACLK Source Divider 6 */
#define DIVA_7              (0x0700)    /* ACLK Source Divider 7 */
#define DIVA__1             (0x0000)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500)    /* ACLK Source Divider f(ACLK)/32 */

#define DIVPA_0             (0x0000)    /* ACLK from Pin Source Divider 0 */
#define DIVPA_1             (0x1000)    /* ACLK from Pin Source Divider 1 */
#define DIVPA_2             (0x2000)    /* ACLK from Pin Source Divider 2 */
#define DIVPA_3             (0x3000)    /* ACLK from Pin Source Divider 3 */
#define DIVPA_4             (0x4000)    /* ACLK from Pin Source Divider 4 */
#define DIVPA_5             (0x5000)    /* ACLK from Pin Source Divider 5 */
#define DIVPA_6             (0x6000)    /* ACLK from Pin Source Divider 6 */
#define DIVPA_7             (0x7000)    /* ACLK from Pin Source Divider 7 */
#define DIVPA__1            (0x0000)    /* ACLK from Pin Source Divider f(ACLK)/1 */
#define DIVPA__2            (0x1000)    /* ACLK from Pin Source Divider f(ACLK)/2 */
#define DIVPA__4            (0x2000)    /* ACLK from Pin Source Divider f(ACLK)/4 */
#define DIVPA__8            (0x3000)    /* ACLK from Pin Source Divider f(ACLK)/8 */
#define DIVPA__16           (0x4000)    /* ACLK from Pin Source Divider f(ACLK)/16 */
#define DIVPA__32           (0x5000)    /* ACLK from Pin Source Divider f(ACLK)/32 */

#define XCAP_0              (0x0000)    /* XIN/XOUT Cap 0 */
#define XCAP_1              (0x0004)    /* XIN/XOUT Cap 1 */
#define XCAP_2              (0x0008)    /* XIN/XOUT Cap 2 */
#define XCAP_3              (0x000C)    /* XIN/XOUT Cap 3 */
#define XT1DRIVE_0          (0x0000)    /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1          (0x0040)    /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2          (0x0080)    /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3          (0x00C0)    /* XT1 Drive Level mode: 3 */
#define XT2DRIVE_0          (0x0000)    /* XT2 Drive Level mode: 0 */
#define XT2DRIVE_1          (0x4000)    /* XT2 Drive Level mode: 1 */
#define XT2DRIVE_2          (0x8000)    /* XT2 Drive Level mode: 2 */
#define XT2DRIVE_3          (0xC000)    /* XT2 Drive Level mode: 3 */

 

/*-------------------------------------------------------------------------
 *   USCI_A0  UART Mode
 *-------------------------------------------------------------------------*/


 /* USCI A0 Control Word Register 0 */ 
__no_init volatile unsigned short UCA0CTLW0 @ 0x05C0;  
 

__no_init volatile union
{
  unsigned char UCA0CTL0;  /* USCI A0 Control Register 0 */ 
  
  struct
  {
    unsigned char UCSYNC         : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0        : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1        : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCSPB          : 1;  /* Async. Mode: Stop Bits  0:one / 1: two */ 
    unsigned char UC7BIT         : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSB          : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCPAR          : 1;  /* Async. Mode: Parity     0:odd / 1:even */ 
    unsigned char UCPEN          : 1;  /* Async. Mode: Parity enable */ 
  } UCA0CTL0_bit;  
} @ 0x05C1;


enum {
  UCSYNC              = 0x0001,
  UCMODE0             = 0x0002,
  UCMODE1             = 0x0004,
  UCSPB               = 0x0008,
  UC7BIT              = 0x0010,
  UCMSB               = 0x0020,
  UCPAR               = 0x0040,
  UCPEN               = 0x0080,
};


__no_init volatile union
{
  unsigned char UCA0CTL1;  /* USCI A0 Control Register 1 */ 
  
  struct
  {
    unsigned char UCA0SWRST      : 1;  /* USCI Software Reset */ 
    unsigned char UCTXBRK        : 1;  /* Send next Data as Break */ 
    unsigned char UCTXADDR       : 1;  /* Send next Data as Address */ 
    unsigned char UCDORM         : 1;  /* Dormant (Sleep) Mode */ 
    unsigned char UCBRKIE        : 1;  /* Break interrupt enable */ 
    unsigned char UCRXEIE        : 1;  /* RX Error interrupt enable */ 
    unsigned char UCA0SSEL0      : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCA0SSEL1      : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCA0CTL1_bit;  
} @ 0x05C0;


enum {
  UCA0SWRST           = 0x0001,
  UCTXBRK             = 0x0002,
  UCTXADDR            = 0x0004,
  UCDORM              = 0x0008,
  UCBRKIE             = 0x0010,
  UCRXEIE             = 0x0020,
  UCA0SSEL0           = 0x0040,
  UCA0SSEL1           = 0x0080,
};


 /* USCI A0 Baud Word Rate 0 */ 
__no_init volatile unsigned short UCA0BRW @ 0x05C6;  
 

 /* USCI A0 Baud Rate 0 */ 
__no_init volatile unsigned char UCA0BR0 @ 0x05C6;  
 

 /* USCI A0 Baud Rate 1 */ 
__no_init volatile unsigned char UCA0BR1 @ 0x05C7;  
 

__no_init volatile union
{
  unsigned char UCA0MCTL;  /* USCI A0 Modulation Control */ 
  
  struct
  {
    unsigned char UCOS16         : 1;  /* USCI 16-times Oversampling enable */ 
    unsigned char UCBRS0         : 1;  /* USCI Second Stage Modulation Select 0 */ 
    unsigned char UCBRS1         : 1;  /* USCI Second Stage Modulation Select 1 */ 
    unsigned char UCBRS2         : 1;  /* USCI Second Stage Modulation Select 2 */ 
    unsigned char UCBRF0         : 1;  /* USCI First Stage Modulation Select 0 */ 
    unsigned char UCBRF1         : 1;  /* USCI First Stage Modulation Select 1 */ 
    unsigned char UCBRF2         : 1;  /* USCI First Stage Modulation Select 2 */ 
    unsigned char UCBRF3         : 1;  /* USCI First Stage Modulation Select 3 */ 
  } UCA0MCTL_bit;  
} @ 0x05C8;


enum {
  UCOS16              = 0x0001,
  UCBRS0              = 0x0002,
  UCBRS1              = 0x0004,
  UCBRS2              = 0x0008,
  UCBRF0              = 0x0010,
  UCBRF1              = 0x0020,
  UCBRF2              = 0x0040,
  UCBRF3              = 0x0080,
};


__no_init volatile union
{
  unsigned char UCA0STAT;  /* USCI A0 Status Register */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char UCADDR         : 1;  /* USCI Address received Flag */ 
    unsigned char UCRXERR        : 1;  /* USCI RX Error Flag */ 
    unsigned char UCBRK          : 1;  /* USCI Break received */ 
    unsigned char UCPE           : 1;  /* USCI Parity Error Flag */ 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCA0STAT_bit;  
} @ 0x05CA;


enum {
  UCBUSY              = 0x0001,
  UCADDR              = 0x0002,
  UCRXERR             = 0x0004,
  UCBRK               = 0x0008,
  UCPE                = 0x0010,
  UCOE                = 0x0020,
  UCFE                = 0x0040,
  UCLISTEN            = 0x0080,
};


 /* USCI A0 Receive Buffer */ 
__no_init volatile unsigned __READ char UCA0RXBUF @ 0x05CC;  
 

 /* USCI A0 Transmit Buffer */ 
__no_init volatile unsigned char UCA0TXBUF @ 0x05CE;  
 

__no_init volatile union
{
  unsigned char UCA0ABCTL;  /* USCI A0 LIN Control */ 
  
  struct
  {
    unsigned char UCABDEN        : 1;  /* Auto Baud Rate detect enable */ 
    unsigned char                : 1; 
    unsigned char UCBTOE         : 1;  /* Break Timeout error */ 
    unsigned char UCSTOE         : 1;  /* Sync-Field Timeout error */ 
    unsigned char UCDELIM0       : 1;  /* Break Sync Delimiter 0 */ 
    unsigned char UCDELIM1       : 1;  /* Break Sync Delimiter 1 */ 
  } UCA0ABCTL_bit;  
} @ 0x05D0;


enum {
  UCABDEN             = 0x0001,
  UCBTOE              = 0x0004,
  UCSTOE              = 0x0008,
  UCDELIM0            = 0x0010,
  UCDELIM1            = 0x0020,
};


 /* USCI A0 IrDA Transmit Control */ 
__no_init volatile unsigned short UCA0IRCTL @ 0x05D2;  
 

__no_init volatile union
{
  unsigned char UCA0IRTCTL;  /* USCI A0 IrDA Transmit Control */ 
  
  struct
  {
    unsigned char UCIREN         : 1;  /* IRDA Encoder/Decoder enable */ 
    unsigned char UCIRTXCLK      : 1;  /* IRDA Transmit Pulse Clock Select */ 
    unsigned char UCIRTXPL0      : 1;  /* IRDA Transmit Pulse Length 0 */ 
    unsigned char UCIRTXPL1      : 1;  /* IRDA Transmit Pulse Length 1 */ 
    unsigned char UCIRTXPL2      : 1;  /* IRDA Transmit Pulse Length 2 */ 
    unsigned char UCIRTXPL3      : 1;  /* IRDA Transmit Pulse Length 3 */ 
    unsigned char UCIRTXPL4      : 1;  /* IRDA Transmit Pulse Length 4 */ 
    unsigned char UCIRTXPL5      : 1;  /* IRDA Transmit Pulse Length 5 */ 
  } UCA0IRTCTL_bit;  
} @ 0x05D2;


enum {
  UCIREN              = 0x0001,
  UCIRTXCLK           = 0x0002,
  UCIRTXPL0           = 0x0004,
  UCIRTXPL1           = 0x0008,
  UCIRTXPL2           = 0x0010,
  UCIRTXPL3           = 0x0020,
  UCIRTXPL4           = 0x0040,
  UCIRTXPL5           = 0x0080,
};


__no_init volatile union
{
  unsigned char UCA0IRRCTL;  /* USCI A0 IrDA Receive Control */ 
  
  struct
  {
    unsigned char UCIRRXFE       : 1;  /* IRDA Receive Filter enable */ 
    unsigned char UCIRRXPL       : 1;  /* IRDA Receive Input Polarity */ 
    unsigned char UCIRRXFL0      : 1;  /* IRDA Receive Filter Length 0 */ 
    unsigned char UCIRRXFL1      : 1;  /* IRDA Receive Filter Length 1 */ 
    unsigned char UCIRRXFL2      : 1;  /* IRDA Receive Filter Length 2 */ 
    unsigned char UCIRRXFL3      : 1;  /* IRDA Receive Filter Length 3 */ 
    unsigned char UCIRRXFL4      : 1;  /* IRDA Receive Filter Length 4 */ 
    unsigned char UCIRRXFL5      : 1;  /* IRDA Receive Filter Length 5 */ 
  } UCA0IRRCTL_bit;  
} @ 0x05D3;


enum {
  UCIRRXFE            = 0x0001,
  UCIRRXPL            = 0x0002,
  UCIRRXFL0           = 0x0004,
  UCIRRXFL1           = 0x0008,
  UCIRRXFL2           = 0x0010,
  UCIRRXFL3           = 0x0020,
  UCIRRXFL4           = 0x0040,
  UCIRRXFL5           = 0x0080,
};


 /* USCI A0 Interrupt Enable Register */ 
__no_init volatile unsigned short UCA0ICTL @ 0x05DC;  
 

__no_init volatile union
{
  unsigned char UCA0IE;  /* USCI A0 Interrupt Enable Register */ 
  
  struct
  {
    unsigned char UCRXIE         : 1;  /* USCI Receive Interrupt Enable */ 
    unsigned char UCTXIE         : 1;  /* USCI Transmit Interrupt Enable */ 
  } UCA0IE_bit;  
} @ 0x05DC;




__no_init volatile union
{
  unsigned char UCA0IFG;  /* USCI A0 Interrupt Flags Register */ 
  
  struct
  {
    unsigned char UCRXIFG        : 1;  /* USCI Receive Interrupt Flag */ 
    unsigned char UCTXIFG        : 1;  /* USCI Transmit Interrupt Flag */ 
  } UCA0IFG_bit;  
} @ 0x05DD;




 /* USCI A0 Interrupt Vector Register */ 
__no_init volatile unsigned short UCA0IV @ 0x05DE;  
 


/*-------------------------------------------------------------------------
 *   USCI_A0  SPI Mode
 *-------------------------------------------------------------------------*/


 /*  */ 
__no_init volatile unsigned short UCA0CTLW0__SPI @ 0x05C0;  
 

__no_init volatile union
{
  unsigned char UCA0CTL0__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSYNCSPI      : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0SPI     : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1SPI     : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCMSTSPI       : 1;  /* Sync. Mode: Master Select */ 
    unsigned char UC7BITSPI      : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSBSPI       : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCCKPLSPI      : 1;  /* Sync. Mode: Clock Polarity */ 
    unsigned char UCCKPHSPI      : 1;  /* Sync. Mode: Clock Phase */ 
  } UCA0CTL0__SPI_bit;  
} @ 0x05C1;


enum {
  UCSYNCSPI           = 0x0001,
  UCMODE0SPI          = 0x0002,
  UCMODE1SPI          = 0x0004,
  UCMSTSPI            = 0x0008,
  UC7BITSPI           = 0x0010,
  UCMSBSPI            = 0x0020,
  UCCKPLSPI           = 0x0040,
  UCCKPHSPI           = 0x0080,
};


__no_init volatile union
{
  unsigned char UCA0CTL1__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char                : 5; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCA0CTL1__SPI_bit;  
} @ 0x05C0;




 /*  */ 
__no_init volatile unsigned short UCA0BRW__SPI @ 0x05C6;  
 

 /*  */ 
__no_init volatile unsigned char UCA0BR0__SPI @ 0x05C6;  
 

 /*  */ 
__no_init volatile unsigned char UCA0BR1__SPI @ 0x05C7;  
 

 /*  */ 
__no_init volatile unsigned char UCA0MCTL__SPI @ 0x05C8;  
 

__no_init volatile union
{
  unsigned char UCA0STAT__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char                : 4; 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCA0STAT__SPI_bit;  
} @ 0x05CA;




 /*  */ 
__no_init volatile unsigned char UCA0RXBUF__SPI @ 0x05CC;  
 

 /*  */ 
__no_init volatile unsigned char UCA0TXBUF__SPI @ 0x05CE;  
 


/*-------------------------------------------------------------------------
 *   USCI_B0  SPI Mode
 *-------------------------------------------------------------------------*/


 /*  */ 
__no_init volatile unsigned short UCB0CTLW0__SPI @ 0x05E0;  
 

__no_init volatile union
{
  unsigned char UCB0CTL0__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSYNCSPI      : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0SPI     : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1SPI     : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCMSTSPI       : 1;  /* Sync. Mode: Master Select */ 
    unsigned char UC7BITSPI      : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSBSPI       : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCCKPLSPI      : 1;  /* Sync. Mode: Clock Polarity */ 
    unsigned char UCCKPHSPI      : 1;  /* Sync. Mode: Clock Phase */ 
  } UCB0CTL0__SPI_bit;  
} @ 0x05E1;




__no_init volatile union
{
  unsigned char UCB0CTL1__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char                : 5; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCB0CTL1__SPI_bit;  
} @ 0x05E0;




 /*  */ 
__no_init volatile unsigned short UCB0BRW__SPI @ 0x05E6;  
 

 /*  */ 
__no_init volatile unsigned char UCB0BR0__SPI @ 0x05E6;  
 

 /*  */ 
__no_init volatile unsigned char UCB0BR1__SPI @ 0x05E7;  
 

__no_init volatile union
{
  unsigned char UCB0STAT__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char                : 4; 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCB0STAT__SPI_bit;  
} @ 0x05EA;




 /*  */ 
__no_init volatile unsigned char UCB0RXBUF__SPI @ 0x05EC;  
 

 /*  */ 
__no_init volatile unsigned char UCB0TXBUF__SPI @ 0x05EE;  
 

 /* USCI B0 Interrupt Enable Register */ 
__no_init volatile unsigned short UCB0ICTL @ 0x05FC;  
 

__no_init volatile union
{
  unsigned char UCB0IE;  /* USCI B0 Interrupt Enable Register */ 
  
  struct
  {
    unsigned char UCRXIE         : 1;  /* USCI Receive Interrupt Enable */ 
    unsigned char UCTXIE         : 1;  /* USCI Transmit Interrupt Enable */ 
    unsigned char UCSTTIE        : 1;  /* START Condition interrupt enable */ 
    unsigned char UCSTPIE        : 1;  /* STOP Condition interrupt enable */ 
    unsigned char UCALIE         : 1;  /* Arbitration Lost interrupt enable */ 
    unsigned char UCNACKIE       : 1;  /* NACK Condition interrupt enable */ 
  } UCB0IE_bit;  
} @ 0x05FC;


enum {
  UCRXIE              = 0x0001,
  UCTXIE              = 0x0002,
  UCSTTIE             = 0x0004,
  UCSTPIE             = 0x0008,
  UCALIE              = 0x0010,
  UCNACKIE            = 0x0020,
};


__no_init volatile union
{
  unsigned char UCB0IFG;  /* USCI B0 Interrupt Flags Register */ 
  
  struct
  {
    unsigned char UCRXIFG        : 1;  /* USCI Receive Interrupt Flag */ 
    unsigned char UCTXIFG        : 1;  /* USCI Transmit Interrupt Flag */ 
    unsigned char UCSTTIFG       : 1;  /* START Condition interrupt Flag */ 
    unsigned char UCSTPIFG       : 1;  /* STOP Condition interrupt Flag */ 
    unsigned char UCALIFG        : 1;  /* Arbitration Lost interrupt Flag */ 
    unsigned char UCNACKIFG      : 1;  /* NAK Condition interrupt Flag */ 
  } UCB0IFG_bit;  
} @ 0x05FD;


enum {
  UCRXIFG             = 0x0001,
  UCTXIFG             = 0x0002,
  UCSTTIFG            = 0x0004,
  UCSTPIFG            = 0x0008,
  UCALIFG             = 0x0010,
  UCNACKIFG           = 0x0020,
};


 /* USCI B0 Interrupt Vector Register */ 
__no_init volatile unsigned short UCB0IV @ 0x05FE;  
 


/*-------------------------------------------------------------------------
 *   USCI_B0  I2C Mode
 *-------------------------------------------------------------------------*/


 /* USCI B0 Control Word Register 0 */ 
__no_init volatile unsigned short UCB0CTLW0 @ 0x05E0;  
 

__no_init volatile union
{
  unsigned char UCB0CTL0;  /* USCI B0 Control Register 0 */ 
  
  struct
  {
    unsigned char UCB0SYNC       : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCB0MODE0      : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCB0MODE1      : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCB0MST        : 1;  /* Sync. Mode: Master Select */ 
    unsigned char                : 1; 
    unsigned char UCB0MM         : 1;  /* Multi-Master Environment */ 
    unsigned char UCB0SLA10      : 1;  /* 10-bit Slave Address Mode */ 
    unsigned char UCB0A10        : 1;  /* 10-bit Address Mode */ 
  } UCB0CTL0_bit;  
} @ 0x05E1;


enum {
  UCB0SYNC            = 0x0001,
  UCB0MODE0           = 0x0002,
  UCB0MODE1           = 0x0004,
  UCB0MST             = 0x0008,
  UCB0MM              = 0x0020,
  UCB0SLA10           = 0x0040,
  UCB0A10             = 0x0080,
};


__no_init volatile union
{
  unsigned char UCB0CTL1;  /* USCI B0 Control Register 1 */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char UCTXSTT        : 1;  /* Transmit START */ 
    unsigned char UCTXSTP        : 1;  /* Transmit STOP */ 
    unsigned char UCTXNACK       : 1;  /* Transmit NACK */ 
    unsigned char UCTR           : 1;  /* Transmit/Receive Select/Flag */ 
    unsigned char                : 1; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCB0CTL1_bit;  
} @ 0x05E0;


enum {
  UCSWRST             = 0x0001,
  UCTXSTT             = 0x0002,
  UCTXSTP             = 0x0004,
  UCTXNACK            = 0x0008,
  UCTR                = 0x0010,
  UCSSEL0             = 0x0040,
  UCSSEL1             = 0x0080,
};


 /* USCI B0 Baud Word Rate 0 */ 
__no_init volatile unsigned short UCB0BRW @ 0x05E6;  
 

 /* USCI B0 Baud Rate 0 */ 
__no_init volatile unsigned char UCB0BR0 @ 0x05E6;  
 

 /* USCI B0 Baud Rate 1 */ 
__no_init volatile unsigned char UCB0BR1 @ 0x05E7;  
 

__no_init volatile union
{
  unsigned char UCB0STAT;  /* USCI B0 Status Register */ 
  
  struct
  {
    unsigned char                : 4; 
    unsigned char UCBBUSY        : 1;  /* Bus Busy Flag */ 
    unsigned char UCGC           : 1;  /* General Call address received Flag */ 
    unsigned char UCSCLLOW       : 1;  /* SCL low */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCB0STAT_bit;  
} @ 0x05EA;




 /* USCI B0 Receive Buffer */ 
__no_init volatile unsigned __READ char UCB0RXBUF @ 0x05EC;  
 

 /* USCI B0 Transmit Buffer */ 
__no_init volatile unsigned char UCB0TXBUF @ 0x05EE;  
 

__no_init volatile union
{
  unsigned short UCB0I2COA;  /* USCI B0 I2C Own Address */ 
  
  struct
  {
    unsigned short UCOA0         : 1;  /* I2C Own Address 0 */ 
    unsigned short UCOA1         : 1;  /* I2C Own Address 1 */ 
    unsigned short UCOA2         : 1;  /* I2C Own Address 2 */ 
    unsigned short UCOA3         : 1;  /* I2C Own Address 3 */ 
    unsigned short UCOA4         : 1;  /* I2C Own Address 4 */ 
    unsigned short UCOA5         : 1;  /* I2C Own Address 5 */ 
    unsigned short UCOA6         : 1;  /* I2C Own Address 6 */ 
    unsigned short UCOA7         : 1;  /* I2C Own Address 7 */ 
    unsigned short UCOA8         : 1;  /* I2C Own Address 8 */ 
    unsigned short UCOA9         : 1;  /* I2C Own Address 9 */ 
    unsigned short               : 5; 
    unsigned short UCGCEN        : 1;  /* I2C General Call enable */ 
  } UCB0I2COA_bit;  
} @ 0x05F0;


enum {
  UCOA0               = 0x0001,
  UCOA1               = 0x0002,
  UCOA2               = 0x0004,
  UCOA3               = 0x0008,
  UCOA4               = 0x0010,
  UCOA5               = 0x0020,
  UCOA6               = 0x0040,
  UCOA7               = 0x0080,
  UCOA8               = 0x0100,
  UCOA9               = 0x0200,
  UCGCEN              = 0x8000,
};


__no_init volatile union
{
  unsigned short UCB0I2CSA;  /* USCI B0 I2C Slave Address */ 
  
  struct
  {
    unsigned short UCSA0         : 1;  /* I2C Slave Address 0 */ 
    unsigned short UCSA1         : 1;  /* I2C Slave Address 1 */ 
    unsigned short UCSA2         : 1;  /* I2C Slave Address 2 */ 
    unsigned short UCSA3         : 1;  /* I2C Slave Address 3 */ 
    unsigned short UCSA4         : 1;  /* I2C Slave Address 4 */ 
    unsigned short UCSA5         : 1;  /* I2C Slave Address 5 */ 
    unsigned short UCSA6         : 1;  /* I2C Slave Address 6 */ 
    unsigned short UCSA7         : 1;  /* I2C Slave Address 7 */ 
    unsigned short UCSA8         : 1;  /* I2C Slave Address 8 */ 
    unsigned short UCSA9         : 1;  /* I2C Slave Address 9 */ 
  } UCB0I2CSA_bit;  
} @ 0x05F2;


enum {
  UCSA0               = 0x0001,
  UCSA1               = 0x0002,
  UCSA2               = 0x0004,
  UCSA3               = 0x0008,
  UCSA4               = 0x0010,
  UCSA5               = 0x0020,
  UCSA6               = 0x0040,
  UCSA7               = 0x0080,
  UCSA8               = 0x0100,
  UCSA9               = 0x0200,
};



/*-------------------------------------------------------------------------
 *   USCI_A1  UART Mode
 *-------------------------------------------------------------------------*/


 /* USCI A1 Control Word Register 0 */ 
__no_init volatile unsigned short UCA1CTLW0 @ 0x0600;  
 

__no_init volatile union
{
  unsigned char UCA1CTL0;  /* USCI A1 Control Register 0 */ 
  
  struct
  {
    unsigned char UCSYNC         : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0        : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1        : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCSPB          : 1;  /* Async. Mode: Stop Bits  0:one / 1: two */ 
    unsigned char UC7BIT         : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSB          : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCPAR          : 1;  /* Async. Mode: Parity     0:odd / 1:even */ 
    unsigned char UCPEN          : 1;  /* Async. Mode: Parity enable */ 
  } UCA1CTL0_bit;  
} @ 0x0601;




__no_init volatile union
{
  unsigned char UCA1CTL1;  /* USCI A1 Control Register 1 */ 
  
  struct
  {
    unsigned char UCA1SWRST      : 1;  /* USCI Software Reset */ 
    unsigned char UCTXBRK        : 1;  /* Send next Data as Break */ 
    unsigned char UCTXADDR       : 1;  /* Send next Data as Address */ 
    unsigned char UCDORM         : 1;  /* Dormant (Sleep) Mode */ 
    unsigned char UCBRKIE        : 1;  /* Break interrupt enable */ 
    unsigned char UCRXEIE        : 1;  /* RX Error interrupt enable */ 
    unsigned char UCA1SSEL0      : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCA1SSEL1      : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCA1CTL1_bit;  
} @ 0x0600;




 /* USCI A1 Baud Word Rate 0 */ 
__no_init volatile unsigned short UCA1BRW @ 0x0606;  
 

 /* USCI A1 Baud Rate 0 */ 
__no_init volatile unsigned char UCA1BR0 @ 0x0606;  
 

 /* USCI A1 Baud Rate 1 */ 
__no_init volatile unsigned char UCA1BR1 @ 0x0607;  
 

__no_init volatile union
{
  unsigned char UCA1MCTL;  /* USCI A1 Modulation Control */ 
  
  struct
  {
    unsigned char UCOS16         : 1;  /* USCI 16-times Oversampling enable */ 
    unsigned char UCBRS0         : 1;  /* USCI Second Stage Modulation Select 0 */ 
    unsigned char UCBRS1         : 1;  /* USCI Second Stage Modulation Select 1 */ 
    unsigned char UCBRS2         : 1;  /* USCI Second Stage Modulation Select 2 */ 
    unsigned char UCBRF0         : 1;  /* USCI First Stage Modulation Select 0 */ 
    unsigned char UCBRF1         : 1;  /* USCI First Stage Modulation Select 1 */ 
    unsigned char UCBRF2         : 1;  /* USCI First Stage Modulation Select 2 */ 
    unsigned char UCBRF3         : 1;  /* USCI First Stage Modulation Select 3 */ 
  } UCA1MCTL_bit;  
} @ 0x0608;




__no_init volatile union
{
  unsigned char UCA1STAT;  /* USCI A1 Status Register */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char UCADDR         : 1;  /* USCI Address received Flag */ 
    unsigned char UCRXERR        : 1;  /* USCI RX Error Flag */ 
    unsigned char UCBRK          : 1;  /* USCI Break received */ 
    unsigned char UCPE           : 1;  /* USCI Parity Error Flag */ 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCA1STAT_bit;  
} @ 0x060A;




 /* USCI A1 Receive Buffer */ 
__no_init volatile unsigned __READ char UCA1RXBUF @ 0x060C;  
 

 /* USCI A1 Transmit Buffer */ 
__no_init volatile unsigned char UCA1TXBUF @ 0x060E;  
 

__no_init volatile union
{
  unsigned char UCA1ABCTL;  /* USCI A1 LIN Control */ 
  
  struct
  {
    unsigned char UCABDEN        : 1;  /* Auto Baud Rate detect enable */ 
    unsigned char                : 1; 
    unsigned char UCBTOE         : 1;  /* Break Timeout error */ 
    unsigned char UCSTOE         : 1;  /* Sync-Field Timeout error */ 
    unsigned char UCDELIM0       : 1;  /* Break Sync Delimiter 0 */ 
    unsigned char UCDELIM1       : 1;  /* Break Sync Delimiter 1 */ 
  } UCA1ABCTL_bit;  
} @ 0x0610;




 /* USCI A1 IrDA Transmit Control */ 
__no_init volatile unsigned short UCA1IRCTL @ 0x0612;  
 

__no_init volatile union
{
  unsigned char UCA1IRTCTL;  /* USCI A1 IrDA Transmit Control */ 
  
  struct
  {
    unsigned char UCIREN         : 1;  /* IRDA Encoder/Decoder enable */ 
    unsigned char UCIRTXCLK      : 1;  /* IRDA Transmit Pulse Clock Select */ 
    unsigned char UCIRTXPL0      : 1;  /* IRDA Transmit Pulse Length 0 */ 
    unsigned char UCIRTXPL1      : 1;  /* IRDA Transmit Pulse Length 1 */ 
    unsigned char UCIRTXPL2      : 1;  /* IRDA Transmit Pulse Length 2 */ 
    unsigned char UCIRTXPL3      : 1;  /* IRDA Transmit Pulse Length 3 */ 
    unsigned char UCIRTXPL4      : 1;  /* IRDA Transmit Pulse Length 4 */ 
    unsigned char UCIRTXPL5      : 1;  /* IRDA Transmit Pulse Length 5 */ 
  } UCA1IRTCTL_bit;  
} @ 0x0612;




__no_init volatile union
{
  unsigned char UCA1IRRCTL;  /* USCI A1 IrDA Receive Control */ 
  
  struct
  {
    unsigned char UCIRRXFE       : 1;  /* IRDA Receive Filter enable */ 
    unsigned char UCIRRXPL       : 1;  /* IRDA Receive Input Polarity */ 
    unsigned char UCIRRXFL0      : 1;  /* IRDA Receive Filter Length 0 */ 
    unsigned char UCIRRXFL1      : 1;  /* IRDA Receive Filter Length 1 */ 
    unsigned char UCIRRXFL2      : 1;  /* IRDA Receive Filter Length 2 */ 
    unsigned char UCIRRXFL3      : 1;  /* IRDA Receive Filter Length 3 */ 
    unsigned char UCIRRXFL4      : 1;  /* IRDA Receive Filter Length 4 */ 
    unsigned char UCIRRXFL5      : 1;  /* IRDA Receive Filter Length 5 */ 
  } UCA1IRRCTL_bit;  
} @ 0x0613;




 /* USCI A1 Interrupt Enable Register */ 
__no_init volatile unsigned short UCA1ICTL @ 0x061C;  
 

__no_init volatile union
{
  unsigned char UCA1IE;  /* USCI A1 Interrupt Enable Register */ 
  
  struct
  {
    unsigned char UCRXIE         : 1;  /* USCI Receive Interrupt Enable */ 
    unsigned char UCTXIE         : 1;  /* USCI Transmit Interrupt Enable */ 
  } UCA1IE_bit;  
} @ 0x061C;




__no_init volatile union
{
  unsigned char UCA1IFG;  /* USCI A1 Interrupt Flags Register */ 
  
  struct
  {
    unsigned char UCRXIFG        : 1;  /* USCI Receive Interrupt Flag */ 
    unsigned char UCTXIFG        : 1;  /* USCI Transmit Interrupt Flag */ 
  } UCA1IFG_bit;  
} @ 0x061D;




 /* USCI A1 Interrupt Vector Register */ 
__no_init volatile unsigned short UCA1IV @ 0x061E;  
 


/*-------------------------------------------------------------------------
 *   USCI_A1  SPI Mode
 *-------------------------------------------------------------------------*/


 /*  */ 
__no_init volatile unsigned short UCA1CTLW0__SPI @ 0x0600;  
 

__no_init volatile union
{
  unsigned char UCA1CTL0__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSYNCSPI      : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0SPI     : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1SPI     : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCMSTSPI       : 1;  /* Sync. Mode: Master Select */ 
    unsigned char UC7BITSPI      : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSBSPI       : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCCKPLSPI      : 1;  /* Sync. Mode: Clock Polarity */ 
    unsigned char UCCKPHSPI      : 1;  /* Sync. Mode: Clock Phase */ 
  } UCA1CTL0__SPI_bit;  
} @ 0x0601;




__no_init volatile union
{
  unsigned char UCA1CTL1__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char                : 5; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCA1CTL1__SPI_bit;  
} @ 0x0600;




 /*  */ 
__no_init volatile unsigned short UCA1BRW__SPI @ 0x0606;  
 

 /*  */ 
__no_init volatile unsigned char UCA1BR0__SPI @ 0x0606;  
 

 /*  */ 
__no_init volatile unsigned char UCA1BR1__SPI @ 0x0607;  
 

 /*  */ 
__no_init volatile unsigned char UCA1MCTL__SPI @ 0x0608;  
 

__no_init volatile union
{
  unsigned char UCA1STAT__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char                : 4; 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCA1STAT__SPI_bit;  
} @ 0x060A;




 /*  */ 
__no_init volatile unsigned char UCA1RXBUF__SPI @ 0x060C;  
 

 /*  */ 
__no_init volatile unsigned char UCA1TXBUF__SPI @ 0x060E;  
 


/*-------------------------------------------------------------------------
 *   USCI_B1  SPI Mode
 *-------------------------------------------------------------------------*/


 /*  */ 
__no_init volatile unsigned short UCB1CTLW0__SPI @ 0x0620;  
 

__no_init volatile union
{
  unsigned char UCB1CTL0__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSYNCSPI      : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCMODE0SPI     : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCMODE1SPI     : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCMSTSPI       : 1;  /* Sync. Mode: Master Select */ 
    unsigned char UC7BITSPI      : 1;  /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */ 
    unsigned char UCMSBSPI       : 1;  /* Async. Mode: MSB first  0:LSB / 1:MSB */ 
    unsigned char UCCKPLSPI      : 1;  /* Sync. Mode: Clock Polarity */ 
    unsigned char UCCKPHSPI      : 1;  /* Sync. Mode: Clock Phase */ 
  } UCB1CTL0__SPI_bit;  
} @ 0x0621;




__no_init volatile union
{
  unsigned char UCB1CTL1__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char                : 5; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCB1CTL1__SPI_bit;  
} @ 0x0620;




 /*  */ 
__no_init volatile unsigned short UCB1BRW__SPI @ 0x0626;  
 

 /*  */ 
__no_init volatile unsigned char UCB1BR0__SPI @ 0x0626;  
 

 /*  */ 
__no_init volatile unsigned char UCB1BR1__SPI @ 0x0627;  
 

__no_init volatile union
{
  unsigned char UCB1STAT__SPI;  /*  */ 
  
  struct
  {
    unsigned char UCBUSY         : 1;  /* USCI Busy Flag */ 
    unsigned char                : 4; 
    unsigned char UCOE           : 1;  /* USCI Overrun Error Flag */ 
    unsigned char UCFE           : 1;  /* USCI Frame Error Flag */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCB1STAT__SPI_bit;  
} @ 0x062A;




 /*  */ 
__no_init volatile unsigned char UCB1RXBUF__SPI @ 0x062C;  
 

 /*  */ 
__no_init volatile unsigned char UCB1TXBUF__SPI @ 0x062E;  
 

 /* USCI B1 Interrupt Enable Register */ 
__no_init volatile unsigned short UCB1ICTL @ 0x063C;  
 

__no_init volatile union
{
  unsigned char UCB1IE;  /* USCI B1 Interrupt Enable Register */ 
  
  struct
  {
    unsigned char UCRXIE         : 1;  /* USCI Receive Interrupt Enable */ 
    unsigned char UCTXIE         : 1;  /* USCI Transmit Interrupt Enable */ 
    unsigned char UCSTTIE        : 1;  /* START Condition interrupt enable */ 
    unsigned char UCSTPIE        : 1;  /* STOP Condition interrupt enable */ 
    unsigned char UCALIE         : 1;  /* Arbitration Lost interrupt enable */ 
    unsigned char UCNACKIE       : 1;  /* NACK Condition interrupt enable */ 
  } UCB1IE_bit;  
} @ 0x063C;




__no_init volatile union
{
  unsigned char UCB1IFG;  /* USCI B1 Interrupt Flags Register */ 
  
  struct
  {
    unsigned char UCRXIFG        : 1;  /* USCI Receive Interrupt Flag */ 
    unsigned char UCTXIFG        : 1;  /* USCI Transmit Interrupt Flag */ 
    unsigned char UCSTTIFG       : 1;  /* START Condition interrupt Flag */ 
    unsigned char UCSTPIFG       : 1;  /* STOP Condition interrupt Flag */ 
    unsigned char UCALIFG        : 1;  /* Arbitration Lost interrupt Flag */ 
    unsigned char UCNACKIFG      : 1;  /* NAK Condition interrupt Flag */ 
  } UCB1IFG_bit;  
} @ 0x063D;




 /* USCI B1 Interrupt Vector Register */ 
__no_init volatile unsigned short UCB1IV @ 0x063E;  
 


/*-------------------------------------------------------------------------
 *   USCI_B1  I2C Mode
 *-------------------------------------------------------------------------*/


 /* USCI B1 Control Word Register 0 */ 
__no_init volatile unsigned short UCB1CTLW0 @ 0x0620;  
 

__no_init volatile union
{
  unsigned char UCB1CTL0;  /* USCI B1 Control Register 0 */ 
  
  struct
  {
    unsigned char UCB1SYNC       : 1;  /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */ 
    unsigned char UCB1MODE0      : 1;  /* Async. Mode: USCI Mode 0 */ 
    unsigned char UCB1MODE1      : 1;  /* Async. Mode: USCI Mode 1 */ 
    unsigned char UCB1MST        : 1;  /* Sync. Mode: Master Select */ 
    unsigned char                : 1; 
    unsigned char UCB1MM         : 1;  /* Multi-Master Environment */ 
    unsigned char UCB1SLA10      : 1;  /* 10-bit Slave Address Mode */ 
    unsigned char UCB1A10        : 1;  /* 10-bit Address Mode */ 
  } UCB1CTL0_bit;  
} @ 0x0621;


enum {
  UCB1SYNC            = 0x0001,
  UCB1MODE0           = 0x0002,
  UCB1MODE1           = 0x0004,
  UCB1MST             = 0x0008,
  UCB1MM              = 0x0020,
  UCB1SLA10           = 0x0040,
  UCB1A10             = 0x0080,
};


__no_init volatile union
{
  unsigned char UCB1CTL1;  /* USCI B1 Control Register 1 */ 
  
  struct
  {
    unsigned char UCSWRST        : 1;  /* USCI Software Reset */ 
    unsigned char UCTXSTT        : 1;  /* Transmit START */ 
    unsigned char UCTXSTP        : 1;  /* Transmit STOP */ 
    unsigned char UCTXNACK       : 1;  /* Transmit NACK */ 
    unsigned char UCTR           : 1;  /* Transmit/Receive Select/Flag */ 
    unsigned char                : 1; 
    unsigned char UCSSEL0        : 1;  /* USCI 0 Clock Source Select 0 */ 
    unsigned char UCSSEL1        : 1;  /* USCI 0 Clock Source Select 1 */ 
  } UCB1CTL1_bit;  
} @ 0x0620;




 /* USCI B1 Baud Word Rate 0 */ 
__no_init volatile unsigned short UCB1BRW @ 0x0626;  
 

 /* USCI B1 Baud Rate 0 */ 
__no_init volatile unsigned char UCB1BR0 @ 0x0626;  
 

 /* USCI B1 Baud Rate 1 */ 
__no_init volatile unsigned char UCB1BR1 @ 0x0627;  
 

__no_init volatile union
{
  unsigned char UCB1STAT;  /* USCI B1 Status Register */ 
  
  struct
  {
    unsigned char                : 4; 
    unsigned char UCBBUSY        : 1;  /* Bus Busy Flag */ 
    unsigned char UCGC           : 1;  /* General Call address received Flag */ 
    unsigned char UCSCLLOW       : 1;  /* SCL low */ 
    unsigned char UCLISTEN       : 1;  /* USCI Listen mode */ 
  } UCB1STAT_bit;  
} @ 0x062A;




 /* USCI B1 Receive Buffer */ 
__no_init volatile unsigned __READ char UCB1RXBUF @ 0x062C;  
 

 /* USCI B1 Transmit Buffer */ 
__no_init volatile unsigned char UCB1TXBUF @ 0x062E;  
 

__no_init volatile union
{
  unsigned short UCB1I2COA;  /* USCI B1 I2C Own Address */ 
  
  struct
  {
    unsigned short UCOA0         : 1;  /* I2C Own Address 0 */ 
    unsigned short UCOA1         : 1;  /* I2C Own Address 1 */ 
    unsigned short UCOA2         : 1;  /* I2C Own Address 2 */ 
    unsigned short UCOA3         : 1;  /* I2C Own Address 3 */ 
    unsigned short UCOA4         : 1;  /* I2C Own Address 4 */ 
    unsigned short UCOA5         : 1;  /* I2C Own Address 5 */ 
    unsigned short UCOA6         : 1;  /* I2C Own Address 6 */ 
    unsigned short UCOA7         : 1;  /* I2C Own Address 7 */ 
    unsigned short UCOA8         : 1;  /* I2C Own Address 8 */ 
    unsigned short UCOA9         : 1;  /* I2C Own Address 9 */ 
    unsigned short               : 5; 
    unsigned short UCGCEN        : 1;  /* I2C General Call enable */ 
  } UCB1I2COA_bit;  
} @ 0x0630;




__no_init volatile union
{
  unsigned short UCB1I2CSA;  /* USCI B1 I2C Slave Address */ 
  
  struct
  {
    unsigned short UCSA0         : 1;  /* I2C Slave Address 0 */ 
    unsigned short UCSA1         : 1;  /* I2C Slave Address 1 */ 
    unsigned short UCSA2         : 1;  /* I2C Slave Address 2 */ 
    unsigned short UCSA3         : 1;  /* I2C Slave Address 3 */ 
    unsigned short UCSA4         : 1;  /* I2C Slave Address 4 */ 
    unsigned short UCSA5         : 1;  /* I2C Slave Address 5 */ 
    unsigned short UCSA6         : 1;  /* I2C Slave Address 6 */ 
    unsigned short UCSA7         : 1;  /* I2C Slave Address 7 */ 
    unsigned short UCSA8         : 1;  /* I2C Slave Address 8 */ 
    unsigned short UCSA9         : 1;  /* I2C Slave Address 9 */ 
  } UCB1I2CSA_bit;  
} @ 0x0632;



 
#define __MSP430_HAS_USCI__           /* Definition to show that Module is available */
#define __MSP430_HAS_USCI_AB0__       /* Definition to show that Module is available */
#define __MSP430_HAS_USCI_AB1__       /* Definition to show that Module is available */


// UCBxCTL0 I2C-Mode Control Bits
//#define res               (0x10)    /* reserved */
#define UCMODE_0            (0x00)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x02)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x04)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x06)    /* Sync. Mode: USCI Mode: 3 */

// UCBxCTL1 I2C-Mode Control Bits
//#define res               (0x20)    /* reserved */
#define UCSSEL_0            (0x00)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x40)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x80)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0xC0)    /* USCI 0 Clock Source: 3 */

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

/* UCBxI2COA Control Bits */
#define UCOA7_L             (0x0080)  /* I2C Own Address 7 */
#define UCOA6_L             (0x0040)  /* I2C Own Address 6 */
#define UCOA5_L             (0x0020)  /* I2C Own Address 5 */
#define UCOA4_L             (0x0010)  /* I2C Own Address 4 */
#define UCOA3_L             (0x0008)  /* I2C Own Address 3 */
#define UCOA2_L             (0x0004)  /* I2C Own Address 2 */
#define UCOA1_L             (0x0002)  /* I2C Own Address 1 */
#define UCOA0_L             (0x0001)  /* I2C Own Address 0 */

/* UCBxI2COA Control Bits */
#define UCGCEN_H            (0x0080)  /* I2C General Call enable */
#define UCOA9_H             (0x0002)  /* I2C Own Address 9 */
#define UCOA8_H             (0x0001)  /* I2C Own Address 8 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L             (0x0080)  /* I2C Slave Address 7 */
#define UCSA6_L             (0x0040)  /* I2C Slave Address 6 */
#define UCSA5_L             (0x0020)  /* I2C Slave Address 5 */
#define UCSA4_L             (0x0010)  /* I2C Slave Address 4 */
#define UCSA3_L             (0x0008)  /* I2C Slave Address 3 */
#define UCSA2_L             (0x0004)  /* I2C Slave Address 2 */
#define UCSA1_L             (0x0002)  /* I2C Slave Address 1 */
#define UCSA0_L             (0x0001)  /* I2C Slave Address 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H             (0x0002)  /* I2C Slave Address 9 */
#define UCSA8_H             (0x0001)  /* I2C Slave Address 8 */

 

/*-------------------------------------------------------------------------
 *   Watchdog Timer
 *-------------------------------------------------------------------------*/


__no_init volatile union
{
  unsigned short WDTCTL;  /* Watchdog Timer Control */ 
  
  struct
  {
    unsigned short WDTIS0        : 1; 
    unsigned short WDTIS1        : 1; 
    unsigned short WDTIS2        : 1; 
    unsigned short WDTCNTCL      : 1; 
    unsigned short WDTTMSEL      : 1; 
    unsigned short WDTSSEL0      : 1; 
    unsigned short WDTSSEL1      : 1; 
    unsigned short WDTHOLD       : 1; 
    unsigned short               : 8; 
  } WDTCTL_bit;  
} @ 0x015C;


enum {
  WDTIS0              = 0x0001,
  WDTIS1              = 0x0002,
  WDTIS2              = 0x0004,
  WDTCNTCL            = 0x0008,
  WDTTMSEL            = 0x0010,
  WDTSSEL0            = 0x0020,
  WDTSSEL1            = 0x0040,
  WDTHOLD             = 0x0080,
};

 
#define __MSP430_HAS_WDT_A__            /* Definition to show that Module is available */
    
#define WDTPW               (0x5A00)
  
/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms      */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms    */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms  */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms   */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms    */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms     */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms    */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms      */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms    */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms  */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms   */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms    */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms     */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms    */
  
 


#pragma language=restore
#endif  /* __IAR_SYSTEMS_ICC__  */




/************************************************************
* Interrupt Vectors (offset from 0xFF80)
************************************************************/


#define RTC_VECTOR          (41 * 2u) /* 0xFFD2 RTC */
#define PORT2_VECTOR        (42 * 2u) /* 0xFFD4 Port 2 */
#define USCI_B3_VECTOR      (43 * 2u) /* 0xFFD6 USCI B3 Receive/Transmit */
#define USCI_A3_VECTOR      (44 * 2u) /* 0xFFD8 USCI A3 Receive/Transmit */
#define USCI_B1_VECTOR      (45 * 2u) /* 0xFFDA USCI B1 Receive/Transmit */
#define USCI_A1_VECTOR      (46 * 2u) /* 0xFFDC USCI A1 Receive/Transmit */
#define PORT1_VECTOR        (47 * 2u) /* 0xFFDE Port 1 */
#define TIMER1_A1_VECTOR    (48 * 2u) /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR    (49 * 2u) /* 0xFFE2 Timer1_A3 CC0 */
#define DMA_VECTOR          (50 * 2u) /* 0xFFE4 DMA */
#define USCI_B2_VECTOR      (51 * 2u) /* 0xFFE6 USCI B2 Receive/Transmit */
#define USCI_A2_VECTOR      (52 * 2u) /* 0xFFE8 USCI A2 Receive/Transmit */
#define TIMER0_A1_VECTOR    (53 * 2u) /* 0xFFEA Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR    (54 * 2u) /* 0xFFEC Timer0_A5 CC0 */
#define ADC12_VECTOR        (55 * 2u) /* 0xFFEE ADC */
#define USCI_B0_VECTOR      (56 * 2u) /* 0xFFF0 USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR      (57 * 2u) /* 0xFFF2 USCI A0 Receive/Transmit */
#define WDT_VECTOR          (58 * 2u) /* 0xFFF4 Watchdog Timer */
#define TIMERB1_VECTOR      (59 * 2u) /* 0xFFF6 Timer B CC1-2, TB */
#define TIMERB0_VECTOR      (60 * 2u) /* 0xFFF8 Timer B CC0 */
#define UNMI_VECTOR         (61 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (62 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (63 * 2u) /* 0xFFFE Reset [Highest Priority] */


#endif /* __IO430xxxx */


