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

#include "Flash.h"

#define BLOCK64                 65536UL
#define SECTOR_SIZE             4096
#define PAGE_SIZE               256


typedef enum
{
  TxFlag,
  RxFlag,
}SpiFlagStatusDef;

static void FlashPageProgram(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr);
static void FlashVariableGroupInfoGet(HART_VariableIndexDef PageVariableInfo,uchar* StringInfo);
static void FlashVariableTableInfoGet(ArrIndexDef VariableIndex,uchar* VariableInfo);
static uchar FlashRegisterStatusGet(FlashCmdDef Instruction);
static void FlashSectorProgramHandle(bool8 IsReviewSize);
static void FlashNoCheckProgramHanlde(bool8 IsReviewSize);
static void FlashHoldOn();
static void FlashEraseHandle();
static void FlashDataInput(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr,uint i);

bool8 G_FlashReadLock = FALSE;

/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiCsDrive(uchar Flag)
* ������Χ:
0 �͵�ƽ��1�ߵ�ƽ��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spi CS�ܽ�����������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void FlashSpiCsDrive(bool8 IsStartTx)
{
  P3OUT_bit.P3OUT0 = !IsStartTx;
  //NOP(1);
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar FlashSpiGetFlagStatus(SpiFlagStatusDef Flag)
* ������Χ:
  typedef enum
  {
    TxFlag,
    RxFlag,
  }SpiFlagStatusDef
* ����ֵ˵��:
* ���ܽ���:   
Flash Spi����״̬��־��ȡ������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/

static uchar FlashSpiGetFlagStatus(SpiFlagStatusDef Flag)
{
  uchar Result = 0xff;
  switch(Flag)
  {
  case TxFlag:
    Result = G_TxFlag;
    break;
  case RxFlag:
    Result = G_RxFlag;
    break;
  default:break;
  }
  return Result;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiSendData(uchar TxData)
* ������Χ:

* ����ֵ˵��:
* ���ܽ���:   
Flash Spi�ֽڷ��ͺ��������ֽڷ��͵�MOSI��
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
static void FlashSpiSendData(uchar TxData)
{
  UCB0TXBUF__SPI = TxData;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar SPI_I2S_ReceiveData()
* ������Χ:

* ����ֵ˵��:��ȡ���ֽڡ�
* ���ܽ���:   
Flash Spi�ֽڽ��պ���������MISO��ȡ���ֽڷ��ء�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
static uchar SPI_I2S_ReceiveData()
{
  return UCB0RXBUF__SPI;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar FlashSpiReadWriteByte(uchar TxData)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spi��д�ֽں���������һ���ֽڵ�ͬʱ����ȡһ���ֽڡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
uchar FlashSpiReadWriteByte(uchar TxData)
{		
	while (FlashSpiGetFlagStatus(TxFlag) == 0);//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
        G_TxFlag = FALSE;     
	FlashSpiSendData(TxData); //ͨ������SPIx����һ������

	while (FlashSpiGetFlagStatus(RxFlag) == 0); //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
        G_RxFlag = FALSE; 
	return SPI_I2S_ReceiveData(); //����ͨ��SPIx������յ�����					    
}

/**
 //�������ƺͲ����ͷ���ֵ���͡�
static uchar FlashRegisterStatusGet(FlashCmdDef Instruction)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash �Ĵ���״̬��ȡ������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
static uchar FlashRegisterStatusGet(FlashCmdDef Instruction)
{
  uchar Temp = 0;
  
  FlashSpiCsDrive(TRUE);
  FlashSpiReadWriteByte(Instruction);
  Temp =  FlashSpiReadWriteByte(0xFF);
  FlashSpiCsDrive(FALSE);
  return Temp;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
static void FlashHoldOn()
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash ���ֺ�����������дʱ�ȴ���д��ϡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
static void FlashHoldOn()
{
  while(FlashRegisterStatusGet(Register1Status)&0x01 == 0x01);
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
uchar FlashSpiReadWriteByte(uchar TxData)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spi��д�ֽں���������һ���ֽڵ�ͬʱ����ȡһ���ֽڡ�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
uint FlashReadDeviceID()
{
  uint Temp = 0;
  
  FlashSpiCsDrive(TRUE);
  FlashSpiReadWriteByte(ReadDeviceID);
  FlashSpiReadWriteByte(0x00);
  FlashSpiReadWriteByte(0x00);
  FlashSpiReadWriteByte(0x00);
  Temp |=  FlashSpiReadWriteByte(0xFF)<<8;
  Temp |=  FlashSpiReadWriteByte(0xFF);
  FlashSpiCsDrive(FALSE);

  return Temp;
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiPageProgram(long int Address,uchar ByteNumber,uchar *ReceiveBuff)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spiҳ��̺����������ֽڸ�����д���ַ����Flash��̡�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void FlashSpiPageProgram(long unsigned int Address,uint ByteNumber,uchar *TxBuff)
{
  FlashSpiInstructionSend(WriteEnable);
  FlashHoldOn();
  FlashSpiCsDrive(TRUE);
  FlashSpiReadWriteByte(PageProgram);
  FlashSpiReadWriteByte(Address>>16);
  FlashSpiReadWriteByte(Address>>8);
  FlashSpiReadWriteByte(Address);
  for(uint i = 0;i < ByteNumber;i++)
  {
    FlashSpiReadWriteByte(TxBuff[i]);
  }
  FlashSpiCsDrive(FALSE);
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiErase(long unsigned int Address,FlashCmdDef Instruction)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spi�������������Ը��ݲ�ָͬ����������������������
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void FlashSpiSpecialCmd(long unsigned int Address,FlashCmdDef Instruction)
{
  FlashSpiInstructionSend(WriteEnable);
  FlashSpiCsDrive(TRUE);
  FlashSpiReadWriteByte(Instruction);
  FlashSpiReadWriteByte(Address>>16);
  FlashSpiReadWriteByte(Address>>8);
  FlashSpiReadWriteByte(Address);
  FlashSpiCsDrive(FALSE);
}


/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiInstructionSend(FlashCmdDef Instruction)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spiָ��ͺ�����
*
* �ؼ���ע��
* - 

  
* δ�����:



*/

void FlashSpiInstructionSend(FlashCmdDef Instruction)
{
    FlashSpiCsDrive(TRUE);
    FlashSpiReadWriteByte(Instruction);
    FlashSpiCsDrive(FALSE);
}
/**
 //�������ƺͲ����ͷ���ֵ���͡�
void FlashSpiPageProgram(long int Address,uchar ByteNumber,uchar *ReceiveBuff)
* ������Χ:
��
* ����ֵ˵��:
* ���ܽ���:   
Flash Spiҳ��̺����������ֽڸ�����д���ַ����Flash��̡�
*
* �ؼ���ע��
* - 

  
* δ�����:



*/
void FlashSpiReadData(long unsigned int Address,long unsigned int ByteNumber,uchar *const RxBuff)
{

  FlashSpiCsDrive(TRUE);
  FlashSpiReadWriteByte(ReadData);
  FlashSpiReadWriteByte(Address>>16);
  FlashSpiReadWriteByte(Address>>8);
  FlashSpiReadWriteByte(Address);
  for(long unsigned int i = 0;i < ByteNumber;i++)
  {
    RxBuff[i] = FlashSpiReadWriteByte(0xFF);
  }
  FlashSpiCsDrive(FALSE);
}
/*
static void FlashSectorProtect(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
������������������flash��дʱֻ�ܴ�1->0������ÿ����д����Ҫ�����������ô洢�ռ䣬
�����Ҫ������ԭ�����ݽ��б�����
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashSectorProtect(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)
{
  uchar buff[SECTOR_SIZE] = {0};
  uint i = 0;
  uint SecOffset = (Address%SECTOR_SIZE);
  long uint SecPosition = Address/SECTOR_SIZE;
  
  FlashSpiReadData(SecPosition*SECTOR_SIZE,SECTOR_SIZE,buff);
  for(i=0;i<sizeT;i++)//У������
  {
    if(buff[SecOffset+i]!=0XFF)break;//��Ҫ����  	  
  }
  if(i < sizeT)
  {
    FlashSpiSpecialCmd(SecPosition*SECTOR_SIZE,SectorErase);
    for(i = 0;i < sizeT;i++)
    {
      buff[i+SecOffset] = *(PagePtr+i);
    }
    FlashHoldOn();
    FlashPageProgram(SecPosition*SECTOR_SIZE,SECTOR_SIZE,buff);
    FlashHoldOn();
  }
  else
  {
    FlashHoldOn();
    FlashPageProgram(Address,sizeT,PagePtr);
    FlashHoldOn();
  }
}
/*
void void FlashSectorProgram()

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
ҳ����Ϣflash���غ�������ҳ����Ϣ����flash��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashPageInfoDownload(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)
{
  uchar buff[PAGE_SIZE] = {0};
  uint i = 0;

    
  if(Address%PAGE_SIZE != 0)
  {
    if(sizeT > (PAGE_SIZE-(Address%PAGE_SIZE)))
    {
      FlashSpiReadData(Address-(Address%PAGE_SIZE),(Address%PAGE_SIZE),buff);
      for(i = (Address%PAGE_SIZE);i < PAGE_SIZE;i++)
      {
        buff[i] = *(PagePtr+i-(Address%PAGE_SIZE));
      }
      FlashSpiPageProgram(Address-(Address%PAGE_SIZE),PAGE_SIZE,buff);
      FlashHoldOn();
      PagePtr += PAGE_SIZE-Address%PAGE_SIZE;
      sizeT -= PAGE_SIZE-Address%PAGE_SIZE;
      Address += PAGE_SIZE-Address%PAGE_SIZE;
    }
  }

  FlashPageProgram(Address,sizeT,PagePtr);
  FlashHoldOn();
}
/*
static void FlashPageProgram(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
ҳ����Ϣflash���غ�������ҳ����Ϣ����flash��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashPageProgram(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)
{
  uint i = 0,size = 0;

  size = sizeT/PAGE_SIZE;
  for(i = 0;i < size;i++)
  {
    FlashSpiPageProgram(Address+i*PAGE_SIZE,PAGE_SIZE,PagePtr+i*PAGE_SIZE);
    FlashHoldOn();
  }
  size = sizeT%PAGE_SIZE;
  FlashSpiPageProgram(Address+i*PAGE_SIZE,size,PagePtr+i*PAGE_SIZE);
  FlashHoldOn();
}
/*
void void FlashPageInfoDownload()

* ������Χ:



* ����ֵ˵��:void
* ���ܽ���:   
ҳ����Ϣflash���غ�������ҳ����Ϣ����flash��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashSectorProgram(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)
{
  long uint SecPosition = Address/SECTOR_SIZE;
  uint SecRemain = SECTOR_SIZE-(Address%SECTOR_SIZE);
  uint i = 0;

  if(sizeT <= SecRemain)
  {
    FlashSectorProtect(Address,sizeT,PagePtr);
  }
  else if(sizeT > SecRemain)
  {
    FlashSectorProtect(Address,SecRemain,PagePtr);
    sizeT -= SecRemain;
    Address = (SecPosition+1)*SECTOR_SIZE;
    PagePtr += SecRemain;
    for(i = 0;i < sizeT/SECTOR_SIZE;i++)
    {
      FlashSectorProtect(Address,SECTOR_SIZE,PagePtr);
      FlashHoldOn();
      Address += SECTOR_SIZE;
      PagePtr += SECTOR_SIZE;
    }
    //�ռ����⣬ֻ�ܶ��徲̬������
    FlashSectorProtect(Address,sizeT%SECTOR_SIZE,PagePtr);
    FlashHoldOn();
  }
}

/*
long unsigned int FlashAddressGet(MenuTreeIndexDef MenuTreeIndex);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash���ʵ�ַ��ͨ����ǰ�˵�����ţ�����flash��ַ��
*
* �ؼ���ע��
* - 

  
* δ�����:


*/
long uint FlashAddressGet(MenuTreeIndexDef MenuTreeIndex,AddressTypeDef AddressType)
{
  long uint addr = 0;
  switch(MenuTreeIndex)
  {
  case GENERAL_MENU_TREE:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(GENERAL_RECV,(uchar*)&addr);
    }
    break;
  case CHUAN_YI_HVP:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP7_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP7_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP7_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(CY_HVP7_RECV,(uchar*)&addr);
    }
    break;
  case CHUAN_YI_HVP5:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP5_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP5_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(CY_HVP7_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(CY_HVP7_RECV,(uchar*)&addr);
    }
    break;
  case CHUAN_YI_T1:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_TTS_V6_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_TTS_V6_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(CY_TTS_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(CY_TTS_RECV,(uchar*)&addr);
    }
    break;
  case RADAR:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(RADAR_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(RADAR_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(RADAR_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(RADAR_RECV,(uchar*)&addr);
    }
    break;
  case CY_HART7_PDS:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS7_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS7_ITEM_,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS7_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(CY_PDS7_RECV,(uchar*)&addr);
    }
    break;
  case CHUAN_YI:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS_V6_INFO,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS_V6_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(CY_PDS_V6_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(CY_PDS_V6_RECV,(uchar*)&addr);
    }
    break;
  case SIEMENS:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(SIEMENS_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(SIEMENS_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(SIEMENS_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(SIEMENS_RECV,(uchar*)&addr);
    }
    break;
  case EJA:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(EJA_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(EJA_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(EJA_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(EJA_RECV,(uchar*)&addr);
    }
    break;
  case LM:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(LM_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(LM_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(LM_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(LM_RECV,(uchar*)&addr);
    }
    break;
  case HW:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(HW_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(HW_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(HW_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(HW_RECV,(uchar*)&addr);
    }
    break;
  case EJA530E:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(EJA530_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(EJA530_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(EJA530_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(EJA530_RECV,(uchar*)&addr);
    }
    break;
  case RAYDAR80G1_0:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(RAYDAR_80G,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(RAYDAR_80G_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(RAYDAR_80G_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(RAYDAR_80G_RECV,(uchar*)&addr);
    }
    break;
  default:
    if(AddressType == PageInfoAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_PAGE,(uchar*)&addr);
    }
    else if(AddressType == ItemInfoAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_ITEM,(uchar*)&addr);
    }
    else if(AddressType == CmdSendTableAddress)
    {
      GET_DATASHEET_ADDR(GENERAL_SEND,(uchar*)&addr);
    }
    else
    {
      GET_DATASHEET_ADDR(GENERAL_RECV,(uchar*)&addr);
    }
    break;
  }
  return addr;
}
/*
void FlashCurrentPageInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentPageNum,uchar* CurrentPageInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlashҳ����Ϣ��ȡ��������ȡ��ǰ��ʾ��ҳ����Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashCurrentPageInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentPageNum,uchar* CurrentPageInfo)
{
  long unsigned int Address = 0;
  Address = FlashAddressGet(MenuTreeIndex,PageInfoAddress);
  Address += CurrentPageNum*sizeof(PageDef);
  FlashSpiReadData(Address,sizeof(PageDef)/sizeof(uchar),CurrentPageInfo);
}
/*
void FlashCurrentItemInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentItemNum,uchar* CurrentItemInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash�˵�����Ϣ��ȡ��������ȡ��ǰ��ʾ�Ĳ˵�����Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashCurrentItemInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentItemNum,uchar* CurrentItemInfo)
{
  long unsigned int Address = 0;
  Address = FlashAddressGet(MenuTreeIndex,ItemInfoAddress);
  Address += CurrentItemNum*sizeof(ItemDef);
  FlashSpiReadData(Address,sizeof(ItemDef)/sizeof(uchar),CurrentItemInfo);
}
/*
void FlashCmdReceiveTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdReceiveTableInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash������ս������ȡ��������ȡ��������Ľ�����Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashCmdReceiveTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdReceiveTableInfo)
{
  long unsigned int Address = 0;
  Address = FlashAddressGet(MenuTreeIndex,CmdReceiveTableAddress);
  Address += CmdArrIndex*sizeof(HART_ReceiveStructDef);
  FlashSpiReadData(Address,sizeof(HART_ReceiveStructDef)/sizeof(uchar),CmdReceiveTableInfo);
}
/*
void FlashCmdSendTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdSendTableInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash����ͽ������ȡ��������ȡ��������Ľ�����Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashCmdSendTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdSendTableInfo)
{
  long unsigned int Address = 0;
  Address = FlashAddressGet(MenuTreeIndex,CmdSendTableAddress);
  Address += CmdArrIndex*sizeof(HART_SendStructDef);
  FlashSpiReadData(Address,sizeof(HART_SendStructDef)/sizeof(uchar),CmdSendTableInfo);
}
/*
void FlashStringInfoGet(uint StringNum,uchar* StringInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash�ַ�����Ϣ���ȡ��������ȡʹ�õ����ִ���Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashStringInfoGet(uint StringNum,uchar* StringInfo)
{
  long unsigned int addr = 0;
  GET_DATASHEET_ADDR(STRING_TABLE,(uchar*)&addr);
  addr += StringNum*sizeof(StringDef);
  FlashSpiReadData(addr,sizeof(StringDef)/sizeof(uchar),StringInfo);
}
/*
void FlashStringInfoGet(uint StringNum,uchar* StringInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash�ַ�����Ϣ���ȡ��������ȡʹ�õ����ִ���Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashWordLibInfoGet(long unsigned int Address,uchar StringNum,uchar* StringInfo)
{
  FlashSpiReadData(Address,StringNum,StringInfo);
}
/*
void FlashStringCodeGet(uint StringNum,uchar* StringInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash�ַ�������ȡ��������ȡ�ַ��룬������ʾ�ַ���
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashStringCodeGet(StringDef *StringStruct,uchar* StringInfo,LanguageTypeDef Language)
{
  long unsigned int addr = 0;
  if(Language == ENGLISH)
  {
    GET_DATASHEET_ADDR(EN_STR_CODE,(uchar*)&addr);
    addr += StringStruct->LanguageTypeNumE*COMMON_STRING_SIZE;
    FlashSpiReadData(addr,COMMON_STRING_SIZE,StringInfo);
  }
  else if(Language == CHINESE)
  {
    GET_DATASHEET_ADDR(CH_STR_CODE,(uchar*)&addr);
    addr += StringStruct->LanguageTypeNumC*CHINESE_STRING_SIZE*2;
    FlashSpiReadData(addr,CHINESE_STRING_SIZE*2,StringInfo);
  }
}

/*
void FlashVariableInfoGet(uint VariableIndex,uchar* VariableInfo);

* ������Χ:



* ����ֵ˵��:
* ���ܽ���:   
  ��ȡFlash������Ϣ���ȡ��������ȡʹ�õ��ı�����Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashVariableInfoGet(uint VariableIndex,uchar* VariableInfo)
{
  long unsigned int Address = 0;
  GET_DATASHEET_ADDR(VARIABLE_INFO,(uchar*)&Address);
  Address += VariableIndex*sizeof(HART_VariableDef);
  FlashSpiReadData(Address,sizeof(HART_VariableDef)/sizeof(uchar),VariableInfo);
}
/*
void FlashStringReadLockHandle(uchar StructIndex,uint StringNum);

* ������Χ:



* ����ֵ˵��:
* ���ܽ���:   
  ҳ���ִ����洦������ҲΪ�˼���ÿ�β������ȡflash�ִ��Ĵ�����ͨ�����������Լ���
  ҳ��ˢ�»��ܲ���������flash��ȡ������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashStringReadLockHandle(uchar StructIndex,uint StringNum,LanguageTypeDef Language)
{
  if(FlashReadLockStatusGet() == FALSE)
  {
    G_StrStruct[StructIndex] = MENU_GetStrStruct(StringNum);
    FlashStringCodeGet(G_StrStruct+StructIndex,G_StringCodeBuff[StructIndex],Language);
  }
}
/*
void FlashVariableGroupLoad(ArrIndexDef VariableIndex);

* ������Χ:



* ����ֵ˵��:
* ���ܽ���:   
  Flashҳ���������Ϣ���غ�����
  ������ǰҳ����Ҫ��ʾ���������ı�������Ϣ������ͨ��������Ϣ�����������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashVariableGroupLoad(ArrIndexDef VariableIndex,PageVariableTableDef* VariableTable,VariableGroupDef* GroupTable)
{
  if(FlashReadLockStatusGet() == FALSE)
  {
    FlashVariableTableInfoGet(VariableIndex,VariableTable->PageVariableStructure);
    FlashVariableGroupInfoGet(VariableTable->PageVariableInfo,GroupTable->VariableGroupC);
  }
}
/*
void FlashStringCodeGet(uint StringNum,uchar* StringInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash��������ȡ��������ȡ��������Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashVariableGroupInfoGet(HART_VariableIndexDef PageVariableInfo,uchar* StringInfo)
{
  long unsigned int Address = 0;
  GET_DATASHEET_ADDR(VAR_GROUP,(uchar*)&Address);
  Address += PageVariableInfo.CurrentPageVariableBuffIndex*sizeof(uint);
  FlashSpiReadData(Address,PageVariableInfo.CurrentPageVariableNumber*sizeof(uint),StringInfo);
}
/*
void FlashVariableTableInfoGet(ArrIndexDef VariableIndex,uchar* VariableInfo);

* ������Χ:



* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash��������Ϣ��ȡ��������ȡ������Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashVariableTableInfoGet(ArrIndexDef VariableIndex,uchar* VariableInfo)
{
  long unsigned int Address = 0;
  GET_DATASHEET_ADDR(HART_PAGE_VAR,(uchar*)&Address);
  Address += VariableIndex*sizeof(HART_VariableIndexDef);
  FlashSpiReadData(Address,sizeof(HART_VariableIndexDef),VariableInfo);
}
/*
void FlashReadLockHandle(bool8 IsReadLock);

* ������Χ:
  IsReadLock���Ƿ����ö�ȡ����
TRUE:����
FALSE:������

* ����ֵ˵��:
* ���ܽ���:   
  Flash��ȡ������������������Щ������Ҫ��ͣ��ˢ�£�
  ��˻᲻ͣ�Ķ�ȡFLASH����ɲ���Ҫ���ܺģ�����趨��ȡ����������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashReadLockHandle(bool8 IsReadLock)
{
  G_FlashReadLock = IsReadLock;
}
/*
bool8 FlashReadLockStatusGet();

* ������Χ:


* ����ֵ˵��:
TRUE:����
FALSE:������
* ���ܽ���:   
  Flash��ȡ����״̬��ȡ��������������������״̬�����Ƿ����Flash��ȡ������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
bool8 FlashReadLockStatusGet()
{
  return G_FlashReadLock;
}


/*
static void FlashDataInput(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)


* ������Χ:
Address:����д���ַ
sizeT������д���С
PagePtr��д������

* ����ֵ˵��:
* ���ܽ���:   
  Flash��Ϣ���뺯��������Ӧ�����ݱ�д�ڶ�Ӧ�Ĵ洢�ռ䡣
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashDataInput(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr,uint i)
{
  FlashSectorProgram(Address,sizeT,PagePtr);
  FlashSectorProgram(DATA_SHEET_CONT_GET(i),sizeof(long uint),(uchar*)&Address);
}
/*
static void FlashSectorProgramHandle(bool8 IsReviewSize);

* ������Χ:

bool8 IsReviewSize���鿴��д�ռ��Сʱ������д���롣

* ����ֵ˵��:
* ���ܽ���:   
  Flash������д���������ճ����뼰����ʹ�á�
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashSectorProgramHandle(bool8 IsReviewSize)
{
#if (ENABLE_FLASH_WRITE == 1)
  long uint sizeT = 0;
  //���ݱ����������Ƭ�Ͽ��ٽ�ʱ��Ҫ��iд��Flash
  uint i = 0;
#if (FLASH_WRITE_PART1 == 1 )
  //EJA530
  sizeT = sizeof(G_EJA530_InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA530_INFO_ADDR,sizeT,(uchar*)G_EJA530_InfoPageArr,i++);
  }
  //CY_HVP7_PAGE
  sizeT = sizeof(G_CY_HVP7PageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP7_PAGE_INFO_ADDR,sizeT,(uchar*)G_CY_HVP7PageArr,i++);
  }

  //CY_HVP5_PAGE
  sizeT = sizeof(G_CY_HVP5_PageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP5_PAGE_INFO_ADDR,sizeT,(uchar*)G_CY_HVP5_PageArr,i++);
  }
  //CY_TTS_V6_PAGE
  sizeT = sizeof(G_CY_TTS_V6PageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_TTS_V6_PAGE_INFO_ADDR,sizeT,(uchar*)G_CY_TTS_V6PageArr,i++);
  }

  //RADAR_PAGE
  sizeT = sizeof(G_RadarInfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RADAR_INFO_ADDR,sizeT,(uchar*)G_RadarInfoPageArr,i++);
  }
  //SIEMENS_PAGE
  sizeT = sizeof(G_SiemensInfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(SIEMENS_INFO_ADDR,sizeT,(uchar*)G_SiemensInfoPageArr,i++);
  }
//EJA_PAGE
  sizeT = sizeof(G_EJA_InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA_INFO_ADDR,sizeT,(uchar*)G_EJA_InfoPageArr,i++);
  }
  //LM_PAGE
  sizeT = sizeof(G_LM_InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(LM_INFO_ADDR,sizeT,(uchar*)G_LM_InfoPageArr,i++);
  }
  //HW_PAGE
  sizeT = sizeof(G_HW_InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(HW_INFO_ADDR,sizeT,(uchar*)G_HW_InfoPageArr,i++);
  }
  //CY_HVP7_RECV
  sizeT = sizeof(G_CY_HVP7_ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP7_RECEIVE_ADDR,sizeT,(uchar*)G_CY_HVP7_ReceiveStruct,i++);
  }
  //CY_HVP7_ITEM
  sizeT = sizeof(G_CY_HVP7ItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP7_ITEM_ADDR,sizeT,(uchar*)G_CY_HVP7ItemArr,i++);
  }
  //CY_HVP5_ITEM
  sizeT = sizeof(G_CY_HVP5_ItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP5_ITEM_ADDR,sizeT,(uchar*)G_CY_HVP5_ItemArr,i++);
  }
  //CY_TTS_V6_ITEM
  sizeT = sizeof(G_CY_TTS_V6ItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_TTS_V6_ITEM_ADDR,sizeT,(uchar*)G_CY_TTS_V6ItemArr,i++);
  }
 //RADAR_ITEM
  sizeT = sizeof(G_RadarMenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RADAR_ITEM_ADDR,sizeT,(uchar*)G_RadarMenuItemArr,i++);
  }
  //SIEMENS_ITEM
  sizeT = sizeof(G_SiemensMenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(SIEMENS_ITEM_ADDR,sizeT,(uchar*)G_SiemensMenuItemArr,i++);
  }
  //EJA_ITEM
  sizeT = sizeof(G_EJA_MenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA_ITEM_ADDR,sizeT,(uchar*)G_EJA_MenuItemArr,i++);
  }
  //LM_ITEM
  sizeT = sizeof(G_LM_MenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(LM_ITEM_ADDR,sizeT,(uchar*)G_LM_MenuItemArr,i++);
  }
  //HW_ITEM
  sizeT = sizeof(G_HW_MenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(HW_ITEM_ADDR,sizeT,(uchar*)G_HW_MenuItemArr,i++);
  }
  //EJA530_ITEM
  sizeT = sizeof(G_EJA530_MenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA530_ITEM_ADDR,sizeT,(uchar*)G_EJA530_MenuItemArr,i++);
  }
  //SIEMENS_SEND
  sizeT = sizeof(G_SIEMENS6SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(SIEMENS_TYPE1_SEND_ADDR,sizeT,(uchar*)G_SIEMENS6SendStruct,i++);
  }
  //SIEMENS_RECV
  sizeT = sizeof(G_SIEMENS6ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(SIEMENS_TYPE1_RECEIVE_ADDR,sizeT,(uchar*)G_SIEMENS6ReceiveStruct,i++);
  }
  //HW_SEND
  sizeT = sizeof(G_HW7SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(HW_TYPE1_SEND_ADDR,sizeT,(uchar*)G_HW7SendStruct,i++);
  }
  //HW_RECV
  sizeT = sizeof(G_HW7ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(HW_TYPE1_RECEIVE_ADDR,sizeT,(uchar*)G_HW7ReceiveStruct,i++);
  }
  //EJA530_SEND
  sizeT = sizeof(G_Eja530SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA530_SEND_ADDR,sizeT,(uchar*)G_Eja530SendStruct,i++);
  }
  //EJA530_RECV
  sizeT = sizeof(G_Eja530ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA530_RECEIVE_ADDR,sizeT,(uchar*)G_Eja530ReceiveStruct,i++);
  }
  //EJA_RECV
  sizeT = sizeof(G_EjaV5ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA_RECEIVE_ADDR,sizeT,(uchar*)G_EjaV5ReceiveStruct,i++);
  }
  //EJA_SEND
  sizeT = sizeof(G_EjaV5SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EJA_SEND_ADDR,sizeT,(uchar*)G_EjaV5SendStruct,i++);
  }
  //LM_SEND
  sizeT = sizeof(G_LM5SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(LM_SEND_ADDR,sizeT,(uchar*)G_LM5SendStruct,i++);
  }
  //LM_RECV
  sizeT = sizeof(G_LM5ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(LM_RECEIVE_ADDR,sizeT,(uchar*)G_LM5ReceiveStruct,i++);
  }
  //CY_TTS_RECV
  sizeT = sizeof(G_CY_TTS_V6ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_TTS_RECEIVE_ADDR,sizeT,(uchar*)G_CY_TTS_V6ReceiveStruct,i++);
  }
  //CY_TTS_SEND
  sizeT = sizeof(G_CY_TTS_V6SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_TTS_SEND_ADDR,sizeT,(uchar*)G_CY_TTS_V6SendStruct,i++);
  }
  //RADAR_SEND
  sizeT = sizeof(G_RadarV5SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RADAR_SEND_ADDR,sizeT,(uchar*)G_RadarV5SendStruct,i++);
  }
  //RADAR_RECV
  sizeT = sizeof(G_RadarV5ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RADAR_RECEIVE_ADDR,sizeT,(uchar*)G_RadarV5ReceiveStruct,i++);
  }
  //CY_HVP7_SEND
  sizeT = sizeof(G_CY_HVP7_SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_HVP7_SEND_ADDR,sizeT,(uchar*)G_CY_HVP7_SendStruct,i++);
  }
  //GENERAL_RECV
  sizeT = sizeof(G_GeneralV5ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(GENERAL_RECEIVE_ADDR,sizeT,(uchar*)G_GeneralV5ReceiveStruct,i++);
  }
  //GENERAL_SEND
  sizeT = sizeof(G_GeneralV5SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(GENERAL_SEND_ADDR,sizeT,(uchar*)G_GeneralV5SendStruct,i++);
  }
  //CY_PDS_V6_RECV
  sizeT = sizeof(G_CY_PDS_V6ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS_V6_RECEIVE_ADDR,sizeT,(uchar*)G_CY_PDS_V6ReceiveStruct,i++);
  }
  //CY_PDS_V6_SEND
  sizeT = sizeof(G_CY_PDS_V6SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS_V6_SEND_ADDR,sizeT,(uchar*)G_CY_PDS_V6SendStruct,i++);
  }
  //CY_PDS_V6_INFO
  sizeT = sizeof(G_CY_PDS6InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS_V6_INFO_ADDR,sizeT,(uchar*)G_CY_PDS6InfoPageArr,i++);
  }
  //CY_PDS_V6_ITEM
  sizeT = sizeof(G_CY_PDS6MenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS_V6_ITEM_ADDR,sizeT,(uchar*)G_CY_PDS6MenuItemArr,i++);
  }
  //GENERAL_PAGE
  sizeT = sizeof(G_GeneralPageInfoArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(GENERAL_PAGE_INFO_ADDR,sizeT,(uchar*)G_GeneralPageInfoArr,i++);
  }
  //GENERAL_ITEM
  sizeT = sizeof(G_GeneralMenuItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(GENERAL_ITEM_ADDR,sizeT,(uchar*)G_GeneralMenuItemArr,i++);
  }

  
  //CY_PDS7_PAGE
  sizeT = sizeof(G_CY_PDS7InfoPageArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS7_PAGE_INFO_ADDR,sizeT,(uchar*)G_CY_PDS7InfoPageArr,i++);
  }
  //CY_PDS7_ITEM_
  sizeT = sizeof(G_CY_PDS7ItemArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS7_ITEM,sizeT,(uchar*)G_CY_PDS7ItemArr,i++);
  }
  //CY_PDS7_RECV
  sizeT = sizeof(G_CY_PDS_V7ReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS7_RECEIVE_ADDR,sizeT,(uchar*)G_CY_PDS_V7ReceiveStruct,i++);
  }
  //CY_PDS7_SEND
  sizeT = sizeof(G_CY_PDS_V7SendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CY_PDS7_SEND_ADDR,sizeT,(uchar*)G_CY_PDS_V7SendStruct,i++);
  }
  //RAYDAR_80G
  sizeT = sizeof(G_Raydar80GInfoPage1_0)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RAYDAR_80G_INFO_ADDR,sizeT,(uchar*)G_Raydar80GInfoPage1_0,i++);
  }
  //RAYDAR_80G_ITEM
  sizeT = sizeof(G_Raydar80GItem1_0)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RAYDAR_80G_ITEM_ADDR,sizeT,(uchar*)G_Raydar80GItem1_0,i++);
  }
  //RAYDAR_80G_RECV
  sizeT = sizeof(G_Raydar80GReceiveStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RAYDAR_80G_RECEIVE_ADDR,sizeT,(uchar*)G_Raydar80GReceiveStruct,i++);
  }
  //RAYDAR_80G_SEND
  sizeT = sizeof(G_Raydar80GSendStruct)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(RAYDAR_80G_SEND_ADDR,sizeT,(uchar*)G_Raydar80GSendStruct,i++);
  }
  //VARIABLE_INFO
  sizeT = sizeof(G_VariableStructureTable)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(VARIABLE_INFO_ADDR,sizeT,(uchar*)G_VariableStructureTable,i++);
  }
  //HART_PAGE_VAR
  sizeT = sizeof(G_HART_PageVariableArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(HART_PAGE_VARIABLE_ARR,sizeT,(uchar*)G_HART_PageVariableArr,i++);
  }
  //VAR_GROUP
  sizeT = sizeof(G_VariableGroupAddress)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(VARIABLE_GROUP_ADDRESS,sizeT,(uchar*)G_VariableGroupAddress,i++);
  }
  //STRING_TABLE
  sizeT = sizeof(G_GeneralStrTable)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(STRING_TABLE_ADDR,sizeT,(uchar*)G_GeneralStrTable,i++);
  }
  //EN_STR_CODE
  sizeT = sizeof(G_EnlishShortStringArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(EN_STR_CODE_ADDR,sizeT,(uchar*)G_EnlishShortStringArr,i++);
  }
  //CH_STR_CODE
  sizeT = sizeof(ChineseShortStringArr)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(CH_STR_CODE_ADDRESS,sizeT,(uchar*)ChineseShortStringArr,i++);
  }
  //ASCII_6X8_LIB_
  sizeT = sizeof(Ascii_6x8)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(ASCII_6X8_LIB,sizeT,(uchar*)Ascii_6x8,i++);
  }
  //ASCII_6X16_LIB_
  sizeT = sizeof(Ascii_6x16)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(ASCII_6X16_LIB,sizeT,(uchar*)Ascii_6x16,i++);
  }
  //ASCII_12X16_LIB_
  sizeT = sizeof(GB_12x16)/sizeof(uchar);
  if(IsReviewSize == FALSE)
  {
    FlashDataInput(ASCII_12X16_LIB,sizeT,(uchar*)GB_12x16,i++);
  }
  #endif  
#endif
}
/*
void FlashMenuWriteModule();

* ������Χ:

  bool8 IsReviewSize���鿴��д�ռ��Сʱ������д���롣

* ����ֵ˵��:�˵�����Ӧ��flash��ַ
* ���ܽ���:   
  ��ȡFlash���������Ϣ��ȡ��������ȡ��������Ϣ��
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashMenuWriteModule(bool8 IsReviewSize)
{
  FlashSectorProgramHandle(IsReviewSize);
}
/*
void FlashWriteResultReview();

* ������Χ:



* ����ֵ˵��:
* ���ܽ���:   
  Flash��д��������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
void FlashWriteResultReview(bool8 IsRead)
{
  //uchar TEST[500] = {0};
  if(IsRead == TRUE)
  {
    /*FlashSpiReadData(CY_PDS_V6_INFO_ADDR,500,TEST);
    FlashSpiReadData(SIEMENS_INFO_ADDR,500,TEST);
    FlashSpiReadData(EJA_INFO_ADDR,500,TEST);
    FlashSpiReadData(LM_INFO_ADDR,500,TEST);
    FlashSpiReadData(HW_INFO_ADDR,500,TEST);
    
    FlashSpiReadData(EJA530_INFO_ADDR,500,TEST);
    FlashSpiReadData(GENERAL_ITEM_ADDR,500,TEST);
    FlashSpiReadData(CY_HVP7_ITEM_ADDR,500,TEST);
    FlashSpiReadData(CY_HVP5_ITEM_ADDR,500,TEST);
    FlashSpiReadData(CY_TTS_V6_ITEM_ADDR,500,TEST);
    FlashSpiReadData(RADAR_ITEM_ADDR,500,TEST);
    FlashSpiReadData(CY_PDS_V6_ITEM_ADDR,500,TEST);
    FlashSpiReadData(SIEMENS_ITEM_ADDR,500,TEST);
    FlashSpiReadData(EJA_ITEM_ADDR,500,TEST);
    FlashSpiReadData(LM_ITEM_ADDR,500,TEST);
    FlashSpiReadData(HW_ITEM_ADDR,500,TEST);
    FlashSpiReadData(EJA530_ITEM_ADDR,500,TEST);
    
    FlashSpiReadData(STRING_TABLE_ADDR,500,TEST);
    FlashSpiReadData(VARIABLE_INFO_ADDR,500,TEST);
    FlashSpiReadData(STRING_CODE_ADDR,500,TEST);
    FlashSpiReadData(SIEMENS_TYPE1_SEND_ADDR,500,TEST);
    FlashSpiReadData(SIEMENS_TYPE1_RECEIVE_ADDR,500,TEST);
    FlashSpiReadData(HW_TYPE1_SEND_ADDR,500,TEST);
    FlashSpiReadData(HW_TYPE1_RECEIVE_ADDR,500,TEST);*/
  }
}
/*
static void FlashEraseHandle();

* ������Χ:



* ����ֵ˵��:
* ���ܽ���:   
  Flash Erase��������
*
* �ؼ���ע��
* - 

  
* δ�����:

*/
static void FlashEraseHandle()
{
  long uint EraseCounter = 0,GlobalSize = 0;
  
  if(GlobalSize % 4096 != 0)
    EraseCounter = GlobalSize/4096+1;
  else
    EraseCounter = GlobalSize/4096;
  
  if(EraseCounter <= 8)
  {
    FlashSpiSpecialCmd(0,BlockErase32B);
    FlashHoldOn();
  }
  else if(EraseCounter <= 16)
  {
    FlashSpiSpecialCmd(0,BlockErase64B);
    FlashHoldOn();
  }
  else
  {
    if(EraseCounter % 16 != 0)
      EraseCounter = EraseCounter/16+1;
    else
      EraseCounter = EraseCounter/16;
    for(uint j = 0;j < EraseCounter ;j++)
    {
      FlashSpiSpecialCmd(j*BLOCK64,BlockErase64B);
      FlashHoldOn();
    }
  }
  FlashWriteResultReview(TRUE);
}
