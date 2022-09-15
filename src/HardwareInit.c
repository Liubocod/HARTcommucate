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

#include "HardwareSet.h"
#include "intrinsics.h"
#include "in430.h"
#include "CopyRightActivate.h"
//#include "AT24C64.h"
#include "Uart.h"
//#include "IICROM24AA02E48T.h"

#include "Lcd0064Drive.c"
#include "HandleKey.c"
#include "Menu_Tree.c"
#include "Menu.c"
#include "EXP_Page.c"
#include "InfoPage.c"

#include "ParamSetPage.c"
#include "DynamicPage.c"
#include "HART.c"
#include "PollingPage.c"
#include "InitialPage.c"
#include "WarningPage.c"
#include "EditPage.c"
#include "CurvePage.c"
#include "Password.c"
#include "Flash.c"


#include "Uart.c"
#include "CopyRightActivate.c"




#define KEY_COUNT_VAL                    10
#define IO_KEY_COUNT_VAL                 40


#define SAMPLE_NUM                       5
#define EXTERNAL_CRYSTAL                 0
#define POWER_DEADLINE                   25



uchar G_KeyCount = 0;
uchar G_IO_KeyCount = 0;
bool8 G_IO_Flag = FALSE;
uchar	G_SampleCount = 0; 
bool8	G_SampleEndFlag = FALSE;
//AD�����������
uint    G_ADResults[][SAMPLE_NUM] = {0};
//AD��ʱ��ʼ��ʱ�����������ʱ����ص���
uint G_AD_TimingStamp = 0xEA60;
//��ʱ�ػ�������
uint G_PowerOffCounter = 0x00;
bool8 G_KeyScanFlag = FALSE;
bool8 G_RxFlag = FALSE,G_TxFlag = FALSE;
void	ScanKey(void);
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	I2CDeviceInit(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
I2C�豸��ʼ��������

*
* �ؼ���ע��
* - 
���������ݳ�ʼ������
  
* δ�����:

��������δͶ��ʹ�á�




void	I2CDeviceInit(void)
{
	SET_I2CSDA;
	SET_I2CSCL;
	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;		// I2C Master, synchronous mode
	UCB0I2CSA = 0x50;						//Slave Device Address
	UCB0BR0 = 5;
	UCB0BR1 = 0;
	UCB0CTL1 |= UCSSEL0;
	UCB0CTL1 &= ~UCSWRST;
	UCB0IE = UCTXIE + UCRXIE;				//

	SET_I2CSDA1;
	SET_I2CSCL1;
	UCB1CTL1 |= UCSWRST;
	UCB1CTL0 = UCMODE_3 + UCSYNC;		// I2C Slave, synchronous mode
	UCB1I2COA = 0x47;						//Ower Device Address
	UCB1BR0 = 5;
	UCB1BR1 = 0;
	UCB1CTL1 |= UCSSEL0;
	UCB1CTL1 &= ~UCSWRST;
	UCB1IE = UCRXIE + UCTXIE + UCSTPIE + UCSTTIE; 				//
}
*/ 
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	InitUart0(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
Uart0��ʼ��������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

void	InitUart0(void)
{
      P3SEL |= 0x30;                             // P3.4 = UCA0TXD, P3.5 = UCA0RXD
      UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCA0CTL0 &= ~UCPEN;
      
      UCA0BR0 = 0xA2;                           // ʱ��Ԥ��Ƶ�����ֽڣ�32768Hz 1200 (see User's Guide)  N=32768/1200=27.306,UCA0BRx=int(N)=27
      UCA0BR1 = 0x01;                           // ʱ��Ԥ��Ƶ�����ֽڣ�Ԥ��Ƶ����ֵ=UCA0BR1*256+UCA0BR0
      
      UCA0CTL1 |= UCSSEL_2;                     // SMCLK
      UCA0MCTL |= UCBRS_2 + UCBRF_0 + UCOS16;            // Modulation UCBRSx=2, UCBRFx=0(UCOS16=0ʱ�����ú���),UCBRSx=round[(N-INT(N))*8]����������
      UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
      UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
      UCA0IE |= UCTXIE;                         // Enable USCI_A0 TX interrupt
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	InitUart0(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
Uart0��ʼ��������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

void	InitFlashSpi(void)
{
      P3SEL |= 0x0e;                             // P3.4 = UCA0TXD, P3.5 = UCA0RXD
      P3DS_bit.P3DS0 = 1;
      P3DIR_bit.P3DIR0 = 1;
      
      UCB0CTL1__SPI_bit.UCSWRST = 1; /* USCI Software Reset */
      UCB0CTL0__SPI_bit.UCSYNC = 1; /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
      UCB0CTL0__SPI_bit.UCMODE0 = 0; /* Async. Mode: USCI Mode 0 */
      UCB0CTL0__SPI_bit.UCMODE1 = 0; /* Async. Mode: USCI Mode 1 */
      UCB0CTL0__SPI_bit.UCMST = 1; /* Sync. Mode: Master Select */
      UCB0CTL0__SPI_bit.UC7BIT = 0; /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
      UCB0CTL0__SPI_bit.UCMSB = 1; /* Async. Mode: MSB first  0:LSB / 1:MSB */
      UCB0CTL0__SPI_bit.UCCKPL = 1; /* Sync. Mode: Clock Polarity */
      UCB0CTL0__SPI_bit.UCCKPH = 0; /* Sync. Mode: Clock Phase */

      
      

      UCB0CTL1__SPI_bit.UCSSEL0 = 0; /* USCI 0 Clock Source Select 0 */
      UCB0CTL1__SPI_bit.UCSSEL1 = 1; /* USCI 0 Clock Source Select 1 */

      
      UCB0BR0 = 1;
      UCB0BR1 = 0;
      
      UCB0CTL1__SPI_bit.UCSWRST = 0; /* USCI Software Reset */

      UCB0IE__SPI_bit.UCRXIE = 1;
      UCB0IE__SPI_bit.UCTXIE = 1;
}
/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	InitUart1(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
Uart1��ʼ��������

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void	InitUart1(void)
{
	P5SEL |= 0xC0;                             // P5.6,7 = USCI_A0 TXD/RXD
	UCA1CTL0 |= UCPEN;
	UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA1CTL1 |= UCSSEL_2;                     // SMCLK
	UCA1BR0 = 0xA2;                              //  1200 (see User's Guide)
	UCA1BR1 = 0x01;                              //  1200
	UCA1MCTL |= UCBRS_0 + UCBRF_2 + UCOS16;            // Modulation UCBRSx=1, UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
	UCA1IE |= UCTXIE;                         // Enable USCI_A0 RX interrupt
}

/*
 //�������ƺͲ����ͷ���ֵ���͡�
void	UCSInit(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ʱ�����ú�������Ϊ��Ӿ�����ڲ��ο�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void	UCSInit(void)
{
#ifndef EXTERNAL_CRYSTAL
    P4DIR |= 0x80;
    P4SEL |= 0x80;
    UCSCTL3 = SELREF__XT1CLK;		// Set DCO FLL reference = REFO
    __bis_SR_register(SCG0);	        // Disable the FLL control loop
    UCSCTL0 = 0x0000;		        // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_3;
    UCSCTL4 = SELS__REFOCLK+SELM__DCOCLK+SELA__REFOCLK;				// Set ACLK = REFO
    __bic_SR_register(SCG0);	        // Enable the FLL control loop*/
    
#else 
  //���8M����ʱ������
    //����Ƶ�ʲ��Խ�
    P4DIR |= 0x80;
    P4SEL |= 0x80;
    
    P7SEL |= 0x03;                                       // Port select XT1
    UCSCTL6 &= ~(XT1OFF);                                // Set XT1 On
    UCSCTL3 = SELREF_2;		                         // Set DCO FLL reference = REFO
    UCSCTL6 |= XT1DRIVE_1 + XTS;                         // Max drive strength, adjust according to crystal frequency.
                                                         // Loop until XT1,XT2 & DCO stabilizes
    do
    {
            UCSCTL7 &= ~(XT1LFOFFG + XT1HFOFFG + DCOFFG);// Clear XT2,XT1,DCO fault flags
            SFRIFG1 &= ~OFIFG;	                         // Clear fault flags
    }while (SFRIFG1&OFIFG);	                         // Test oscillator fault flag

    UCSCTL0 = 0x0000;					 // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_0;
    UCSCTL4 = SELS__XT1CLK+SELM__XT1CLK+SELA__XT1CLK;	 // Set ACLK = REFO
    UCSCTL5 = 0x0500;                                    //��ʱ�Ӳ���Ƶ,����ʱ��32��Ƶ
#endif
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void LcdPinInit()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
Һ�������ܽų�ʼ����������Һ�������漰�ĹܽŽ�����Ӧ���á�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void  LcdPinInit(void)            
{
    //P1_1��P1_7����Ϊ���	
    P1DIR  = 0xfe;
    //P2��Ϊ8λ������
    //P2ѡ��I/O�˿ڹ���
    P2SEL = 0x00;
    //�趨P2Ϊ����
    P2DIR = 0x00;
    //����������������
    P2REN = 0xFF;
    //����͵�ƽ
    P2OUT = 0x00;
    //Һ����λ�ź�������Ϊ����ܽ�
    P3DIR |= 0x01;
    LCDVCC_ON;
    LCDDATADIRWRITE;
    LCD_RES_1;
    LCDCS1_1;
    LCDCS2_1;
    LCD_E_1;
    LCD_WR_1;
    LCD_DI_1;
    WRITELCDDATA = 0xFF;
    BACKLIGHT_ON;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void KeyPinInit()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�����ܽų�ʼ���������������漰�ĹܽŽ�����Ӧ���á�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void KeyPinInit(PageKeyScanDef PageKeyScanFlag)
{
  if(PageKeyScanFlag == COMMON_SCAN)
  {
    //P3�˿ڷ�����Ϊ�����������������Ϊȫ��������������߸��������ɨ��ܽ�
    P3DIR |= 0xc0;
    P3OUT |= 0xc0;
    P3DS |= 0xc0;
    P8DIR |= 0x01;
    P8OUT |= 0x01;
    P8DS |= 0x01;
    //P4�ڰ�������
    P4DIR &= 0x00;
    
#ifdef PIN_TEST
    //P8��1������Ϊ���,���Խ�
    P8DIR |= 0x02;
    P8DS |= 0x02;
    P8OUT |= 0x02;
#endif
    P5DIR_bit.P5DIR4 = SET;
    P5OUT_bit.P5OUT4 = SET;
    P5DS_bit.P5DS4 = SET;
  }
  else if(PageKeyScanFlag == DYNAMIC_SCAN)
  {
    P3DIR &= 0x3f;
    P4DIR |= 0x7f;
  }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void	PortInit(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
�ܽų�ʼ��
*
* �ؼ���ע��
* - 

  
* δ�����:

��ǰ���ò���ϵͳ���������䡣

*/ 
void	PortInit(void)
{
    P7DIR |= 0x08; 
    P5DIR_bit.P5DIR5 = SET;  
    P6DIR |= 0x01;
    P6DIR &= 0xCF;
    //�˿�1�жϹر�
    P1IE = 0x00;
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void	InitTimer1A0(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ʱ��1A0��ʼ������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void	InitTimer1A0(void)
{
    //�����Ƚ�/�����ж�
    TA1CCTL0 = CCIE;
    //�趨��ʱ���ڣ�����ֵΪ32����1ms
    TA1CCR0 = 32;
    //ʱ��ѡ��SMCLK,
    //ģʽѡ��Continuous��
    //��ʱ�����㣬
    //ʱ��8��Ƶ
    TA1CTL = TASSEL_1 + MC_2 + TACLR + ID_3;  
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void	HardwareInit(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
Ӳ����ʼ��������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

void	HardwareInit(void)
{
  //���ÿ��Ź����ƼĴ������趨���Ź���ʱ���İ�ȫֵ��ͬʱ�رտ��Ź�
  EnalePower;
  WDTCTL = WDTPW + WDTHOLD;
  UCSInit();
  InitUart0();
  InitUart1();
  InitFlashSpi();
  PortInit();
  LcdPinInit();
  KeyPinInit(COMMON_SCAN); 
  InitTimer1A0();
  __enable_interrupt();
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void PORT1_ISR(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
PORT1�˿��ⲿ�����жϴ�����
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
  if(P1IFG != 0)
  {
     P1IFG = 0;
  }
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
 void TIMER1_A0_ISR(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
TIMER1_A0��ʱ���жϴ�������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    TA1CCR0 += 32;            //1ms  Add Offset to CCR0 32KHz/32 = 1ms
    
    //��ؼ�⼰��ʱ�ػ�����
    if(G_AD_TimingStamp)
    {
      G_AD_TimingStamp--;
    }
    else
    {
      G_AD_TimingStamp = 0xEA60;
      if(G_ActivateCheckCounter != 0xA5)
      {
        G_CheckActivateCodeTimer++;
      }
      InitAD();
      G_PowerOffCounter++;
    }
    if(G_PowerOffCounter >= POWER_DEADLINE)
    {
      DisablePower;
    }
	//�ɹ��ʶ������㺯��

    if(G_KeyCount >= KEY_COUNT_VAL)
    {
      //���Ź�ι��       
      FEED_DOG = ~FEED_DOG;
      if(G_IO_KeyCount >= IO_KEY_COUNT_VAL)
      {
        G_IO_KeyCount = 0;
        if(G_IO_Flag == TRUE)
        DisablePower;
      }
      if(P4IN&0x80)
      {
        G_IO_KeyCount++;
      }
      else
      {
        G_IO_KeyCount = 0;
        G_IO_Flag = TRUE;
      }
      G_KeyScanFlag = TRUE;
      G_KeyCount = 0;
      if(G_KeyTask == CONTINUED_PRESS)
      {
        if(G_KeyValue == RIGHT_UP_SELECT)
        {
          G_BackLightCount++;
          if(G_BackLightCount >= 50)
          {
            G_BackLightCount = 0;
            G_KeyValue =  NO_KEY_STATUS;
            G_KeyTask = WAIT_HANDLE_KEY;
            if(G_BackLightFlag == TRUE)
            {
              BACKLIGHT_ON;
              G_BackLightFlag = FALSE;
            }
            else
            {
              BACKLIGHT_OFF;
              G_BackLightFlag = TRUE;
            }
          }
        }   
      }      
    }

    G_KeyCount++;
    //����ʱ�رտ��Ź�
    //WDTCTL = WDT_ARST_1000;
    if(G_FrameGap)
    {
      G_FrameGap--;
    }
    if(G_BytesGap)
    {
      G_BytesGap--;
    }
    if(G_WarningTimeStamp)
    {
      G_WarningTimeStamp--;
    }
    if(G_DelayStamp)
    {
      G_DelayStamp--;
    }
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void USCI_A1_ISR(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
USCI_A1�жϴ�������UART�����ж�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 



#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{

	switch(__even_in_range(UCA1IV,4))
	{
		case 0:break;                             // Vector 0 - no interrupt
		case 2:                                   // Vector 2 - RXIFG
                  HART_FrameReceiveHandle();
		break;
		case 4: // Vector 4 - TXIFG
			
			break;
		default: break;
	}
}

/*
//�������ƺͲ����ͷ���ֵ���͡�
void	InitAD(void)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
AD������ʼ������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 

void	InitAD(void)
{
	P6SEL |= 0x02;								// Enable A/D channel A1 A2
	P5SEL |= 0x03;								// Enable refout
//	REFCTL0 = 
	REFCTL0 |= REFMSTR + REFVSEL_2 + REFON;       
	ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8+ADC12REFON;		// Turn on ADC12, set sampling time
	ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3+ADC12DIV_7;					// Use sampling timer
	ADC12CTL2 = ADC12REFOUT+ADC12RES1;
	ADC12MCTL1 = ADC12INCH_1+ADC12SREF_1+ADC12EOS;			// Vr+=Vref+ and Vr-=AVss
//	ADC12MCTL2 = ADC12INCH_2+ADC12SREF_1;				// Vr+=Vref+ and Vr-=AVss
	ADC12IE = 0x02;
	ADC12CTL0 |= ADC12ENC; 
	ADC12CTL0 |= ADC12SC;							// Start conversion
	G_SampleCount = 0;
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void	CloseAD(void)
* ������Χ:


* ����ֵ˵��:void   
* ���ܽ���:   
AD�����رպ���
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
void	CloseAD(void)
{
	REFCTL0 = 0;
	ADC12CTL0 = 0;
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
	switch(__even_in_range(ADC12IV,34))
	{
		case  0: break;                           // Vector  0:  No interrupt
		case  2: break;                           // Vector  2:  ADC overflow
		case  4: break;                           // Vector  4:  ADC timing overflow
		case  6: break;                           // Vector  6:  ADC12IFG0
		case  8: 
			G_ADResults[0][G_SampleCount] = ADC12MEM1; 
//			ADResults[1][SampleCount] = ADC12MEM2;
			G_SampleCount++;
			if(G_SampleCount >= SAMPLE_NUM)
			{
				ADC12CTL0 &= ~ADC12ENC; 
				ADC12CTL0 &= ~ADC12SC;							// Start conversion
                                
				G_SampleCount = 0; 
				G_SampleEndFlag = TRUE;
			}
			LPM3_EXIT;
		break;                           // Vector  8:  ADC12IFG1
		case 10:
		break;						// Vector 10:  ADC12IFG2
		case 12: break;					// Vector 12:  ADC12IFG3
		case 14: break;					// Vector 14:  ADC12IFG4
		case 16: break;					// Vector 16:  ADC12IFG5
		case 18: break;					// Vector 18:  ADC12IFG6
		case 20: break;					// Vector 20:  ADC12IFG7
		case 22: break;					// Vector 22:  ADC12IFG8
		case 24: break;					// Vector 24:  ADC12IFG9
		case 26: break;					// Vector 26:  ADC12IFG10
		case 28: break;					// Vector 28:  ADC12IFG11
		case 30: break;					// Vector 30:  ADC12IFG12
		case 32: break;					// Vector 32:  ADC12IFG13
		case 34: break;					// Vector 34:  ADC12IFG14
		default: break; 
	}  
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
uint GetAverageOfAD(uint *AD_data)
* ������Χ:
uint *AD_data��AD���ݱ�������ָ�롣

* ����ֵ˵��:void   
* ���ܽ���:   
AD�����رպ���
*
* �ؼ���ע��
* - 

  
* δ�����:



*/ 
uint GetAverageOfAD(uint *AD_data)
{
   unsigned char TempC;
   unsigned long TempL;
   uint Max = 0,Min = 0,ADSampleValue = 0;
   
  
   Min = 4095;
   Max = 0; 
   TempL = 0;     
   for (TempC = 0; TempC < SAMPLE_NUM; TempC++) //��ȥg_ADResults[][0]�����ų����ڸ�������������ɵĲ���ֵ��׼ȷ����
   {
     if (AD_data[TempC] > Max)
       Max = AD_data[TempC];
     else if (AD_data[TempC] < Min)
       Min = AD_data[TempC];
     TempL = TempL + AD_data[TempC];       
   }
   TempL = TempL - Max - Min;         
   ADSampleValue = TempL/(SAMPLE_NUM - MAX_MIN_NUM); 
   

   return ADSampleValue;   
}

/** void USCI_A0_ISR(void)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void 
*
* ���ܽ���: USCI_A0�жϷ�����
*
* �ؼ���ע��USCI����һ���ж�����������ͽ��չ���
*
* δ�����:
* 
*/
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{        
	switch (__even_in_range(UCA0IV,4))
	{
		case 0:break;					// Vector 0 - no interrupt
		case 2:					        // Vector 2 - RXIFG  
                   ActivationRequestHandle();
		break;
		case 4:						// Vector 4 - TXIFG
                   ActivationRespondHandle();                       
		break;
		default: break;
	}
} 
/** void USCI_B0_ISR(void)  //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ: 
*
* ����ֵ˵��: void 
*
* ���ܽ���: USCI_B0�жϷ�������spiģʽ
*
* �ؼ���ע��
*
* δ�����:
* 
*/
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{        
	switch (__even_in_range(UCB0IV,4))
	{
		case 0:break;					// Vector 0 - no interrupt
		case 2:					        // Vector 2 - UCRXIFG  
		G_RxFlag = TRUE;
                break;
		case 4:						// Vector 4 - UCTXIFG
		G_TxFlag = TRUE;
                break;
		default: break;
	}
} 

/*
//�������ƺͲ����ͷ���ֵ���͡�
void UsartFrameCharSend(uchar FrameBuffDataChar)
* ������Χ:
uchar FrameBuffDataChar����Ҫͨ�����ڷ��͵�����֡�ֽڡ�

* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ��֡�ַ����ͺ�����

*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void UsartFrameCharSend(uchar FrameBuffDataChar)
{
    UCA1TXBUF = FrameBuffDataChar;
    while(UCA1STAT&UCBUSY);
}
/*
//�������ƺͲ����ͷ���ֵ���͡�
void EnableUartTxInterrupt(uchar FrameBuffDataChar)
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
ʹ�ܴ����ж�

*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void EnableUartTxInterrupt()
{
  UCA0IE |= UCTXIE;
}
/** void DisableUartTxInterrupt(void)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: void 
*
* ���ܽ���: ��ʹ�ܴ��ڷ����ж�
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  DisableUartTxInterrupt()
{
      UCA0IE &= ~UCTXIE; 
}

/** void ReadDataFromUartRxBuf(void)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: void 
*
* ���ܽ���: ��UART�Ľ��ջ������ж�ȡ����
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  ReadDataFromUartRxBuf()
{
       G_RxBuf[G_RxByteNum] = UCA0RXBUF; 
}


/** void WriteDataToUartTxBuf(void)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: void 
*
* ���ܽ���: д���ݵ�UART�ķ��ͻ�������
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  WriteDataToUartTxBuf()
{
      UCA0TXBUF = G_TxBuf[G_TxByteNum];  
}
/** void WriteDataToUartTxBuf(void)     //�������ƺͲ����ͷ���ֵ���͡�
* ������Χ:  
*
* ����ֵ˵��: void 
*
* ���ܽ���: д���ݵ�UART�ķ��ͻ�������
*
* �ؼ���ע��
*
* δ�����:
* 
*/ 
void  COPY_EncryptionHandle()
{
  if(G_ActivateCheckCounter < 10)
  {
    if(G_IfRevenge == FALSE)
    { 
        ActivateReceiveFrameHandle();
        ActivateMeterThroughUartActivator();
        CheckActivationCode();
        TransmitGenerateActivateCodeOrNotToActivator();
        TransmitActivateCodeCorrectOrNotToActivator();
        G_IfRevenge = IfRevengeOrNot();
    }
    else 
    {
      //�л����ͷ���ʾ����
      MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
      MENU_PageTypeSetHandle(WARNING_PAGE);
      MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_114);
      MENU_PageShow();
      while(1);
    }
  }
  else 
  {
    G_ActivateCheckCounter = 0xA5;
  }


}




