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
 //函数名称和参量和返回值类型。
void FlashSpiCsDrive(uchar Flag)
* 变量范围:
0 低电平，1高电平。
* 返回值说明:
* 功能介绍:   
Flash Spi CS管脚驱动函数。
*
* 关键备注：
* - 

  
* 未来提高:



*/
void FlashSpiCsDrive(bool8 IsStartTx)
{
  P3OUT_bit.P3OUT0 = !IsStartTx;
  //NOP(1);
}
/**
 //函数名称和参量和返回值类型。
uchar FlashSpiGetFlagStatus(SpiFlagStatusDef Flag)
* 变量范围:
  typedef enum
  {
    TxFlag,
    RxFlag,
  }SpiFlagStatusDef
* 返回值说明:
* 功能介绍:   
Flash Spi驱动状态标志获取函数。
*
* 关键备注：
* - 

  
* 未来提高:



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
 //函数名称和参量和返回值类型。
void FlashSpiSendData(uchar TxData)
* 变量范围:

* 返回值说明:
* 功能介绍:   
Flash Spi字节发送函数，将字节发送到MOSI。
*
* 关键备注：
* - 

  
* 未来提高:



*/
static void FlashSpiSendData(uchar TxData)
{
  UCB0TXBUF__SPI = TxData;
}
/**
 //函数名称和参量和返回值类型。
uchar SPI_I2S_ReceiveData()
* 变量范围:

* 返回值说明:读取的字节。
* 功能介绍:   
Flash Spi字节接收函数，将读MISO读取的字节返回。
*
* 关键备注：
* - 

  
* 未来提高:



*/
static uchar SPI_I2S_ReceiveData()
{
  return UCB0RXBUF__SPI;
}
/**
 //函数名称和参量和返回值类型。
uchar FlashSpiReadWriteByte(uchar TxData)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi读写字节函数，发送一个字节的同时，读取一个字节。
*
* 关键备注：
* - 

  
* 未来提高:



*/
uchar FlashSpiReadWriteByte(uchar TxData)
{		
	while (FlashSpiGetFlagStatus(TxFlag) == 0);//检查指定的SPI标志位设置与否:发送缓存空标志位
        G_TxFlag = FALSE;     
	FlashSpiSendData(TxData); //通过外设SPIx发送一个数据

	while (FlashSpiGetFlagStatus(RxFlag) == 0); //检查指定的SPI标志位设置与否:接受缓存非空标志位
        G_RxFlag = FALSE; 
	return SPI_I2S_ReceiveData(); //返回通过SPIx最近接收的数据					    
}

/**
 //函数名称和参量和返回值类型。
static uchar FlashRegisterStatusGet(FlashCmdDef Instruction)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash 寄存器状态读取函数。
*
* 关键备注：
* - 

  
* 未来提高:



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
 //函数名称和参量和返回值类型。
static void FlashHoldOn()
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash 保持函数，用于烧写时等待烧写完毕。
*
* 关键备注：
* - 

  
* 未来提高:



*/
static void FlashHoldOn()
{
  while(FlashRegisterStatusGet(Register1Status)&0x01 == 0x01);
}
/**
 //函数名称和参量和返回值类型。
uchar FlashSpiReadWriteByte(uchar TxData)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi读写字节函数，发送一个字节的同时，读取一个字节。
*
* 关键备注：
* - 

  
* 未来提高:



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
 //函数名称和参量和返回值类型。
void FlashSpiPageProgram(long int Address,uchar ByteNumber,uchar *ReceiveBuff)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi页编程函数，根据字节个数，写入地址，向Flash编程。
*
* 关键备注：
* - 

  
* 未来提高:



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
 //函数名称和参量和返回值类型。
void FlashSpiErase(long unsigned int Address,FlashCmdDef Instruction)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi擦除函数，可以根据不同指令进行扇区擦除，块擦除。
*
* 关键备注：
* - 

  
* 未来提高:



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
 //函数名称和参量和返回值类型。
void FlashSpiInstructionSend(FlashCmdDef Instruction)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi指令发送函数。
*
* 关键备注：
* - 

  
* 未来提高:



*/

void FlashSpiInstructionSend(FlashCmdDef Instruction)
{
    FlashSpiCsDrive(TRUE);
    FlashSpiReadWriteByte(Instruction);
    FlashSpiCsDrive(FALSE);
}
/**
 //函数名称和参量和返回值类型。
void FlashSpiPageProgram(long int Address,uchar ByteNumber,uchar *ReceiveBuff)
* 变量范围:
。
* 返回值说明:
* 功能介绍:   
Flash Spi页编程函数，根据字节个数，写入地址，向Flash编程。
*
* 关键备注：
* - 

  
* 未来提高:



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

* 变量范围:



* 返回值说明:void
* 功能介绍:   
扇区保护函数，由于flash烧写时只能从1->0，所以每次烧写都需要擦除扇区重置存储空间，
因此需要对扇区原有数据进行保护。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void FlashSectorProtect(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)
{
  uchar buff[SECTOR_SIZE] = {0};
  uint i = 0;
  uint SecOffset = (Address%SECTOR_SIZE);
  long uint SecPosition = Address/SECTOR_SIZE;
  
  FlashSpiReadData(SecPosition*SECTOR_SIZE,SECTOR_SIZE,buff);
  for(i=0;i<sizeT;i++)//校验数据
  {
    if(buff[SecOffset+i]!=0XFF)break;//需要擦除  	  
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

* 变量范围:



* 返回值说明:void
* 功能介绍:   
页面信息flash下载函数，将页面信息存入flash。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:void
* 功能介绍:   
页面信息flash下载函数，将页面信息存入flash。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:void
* 功能介绍:   
页面信息flash下载函数，将页面信息存入flash。
*
* 关键备注：
* - 

  
* 未来提高:

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
    //空间问题，只能定义静态区变量
    FlashSectorProtect(Address,sizeT%SECTOR_SIZE,PagePtr);
    FlashHoldOn();
  }
}

/*
long unsigned int FlashAddressGet(MenuTreeIndexDef MenuTreeIndex);

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash访问地址，通过当前菜单树序号，查找flash地址。
*
* 关键备注：
* - 

  
* 未来提高:


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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash页面信息读取函数，读取当前显示的页面信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash菜单项信息读取函数，读取当前显示的菜单项信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash命令接收解析表读取函数，读取接收命令的解析信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash命令发送解析表读取函数，读取发送命令的解析信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash字符串信息表读取函数，获取使用到的字串信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash字符串信息表读取函数，获取使用到的字串信息。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void FlashWordLibInfoGet(long unsigned int Address,uchar StringNum,uchar* StringInfo)
{
  FlashSpiReadData(Address,StringNum,StringInfo);
}
/*
void FlashStringCodeGet(uint StringNum,uchar* StringInfo);

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash字符串码表读取函数，获取字符码，方便显示字符。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:
* 功能介绍:   
  获取Flash变量信息表读取函数，获取使用到的变量信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:
* 功能介绍:   
  页面字串缓存处理函数，也为了减少每次操作后读取flash字串的次数，通过本函数可以减少
  页面刷新或功能操作带来的flash读取动作。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:
* 功能介绍:   
  Flash页面变量组信息加载函数，
  包括当前页面需要显示或挂载命令的变量的信息，可以通过变量信息变量索引序号
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash变量组表读取函数，获取变量组信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash变量表信息读取函数，获取变量信息。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:
  IsReadLock：是否设置读取锁定
TRUE:锁定
FALSE:不锁定

* 返回值说明:
* 功能介绍:   
  Flash读取锁定处理函数，由于有些界面需要不停的刷新，
  因此会不停的读取FLASH，造成不必要的能耗，因此设定读取操作锁定。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void FlashReadLockHandle(bool8 IsReadLock)
{
  G_FlashReadLock = IsReadLock;
}
/*
bool8 FlashReadLockStatusGet();

* 变量范围:


* 返回值说明:
TRUE:锁定
FALSE:不锁定
* 功能介绍:   
  Flash读取锁定状态获取函数函数，根据锁定的状态决定是否进行Flash读取操作。
*
* 关键备注：
* - 

  
* 未来提高:

*/
bool8 FlashReadLockStatusGet()
{
  return G_FlashReadLock;
}


/*
static void FlashDataInput(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr)


* 变量范围:
Address:数据写入地址
sizeT：数据写入大小
PagePtr：写入内容

* 返回值说明:
* 功能介绍:   
  Flash信息输入函数，将对应的数据表写在对应的存储空间。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void FlashDataInput(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr,uint i)
{
  FlashSectorProgram(Address,sizeT,PagePtr);
  FlashSectorProgram(DATA_SHEET_CONT_GET(i),sizeof(long uint),(uchar*)&Address);
}
/*
static void FlashSectorProgramHandle(bool8 IsReviewSize);

* 变量范围:

bool8 IsReviewSize：查看烧写空间大小时屏蔽烧写代码。

* 返回值说明:
* 功能介绍:   
  Flash调试烧写处理，用于日常编码及调试使用。
*
* 关键备注：
* - 

  
* 未来提高:

*/
static void FlashSectorProgramHandle(bool8 IsReviewSize)
{
#if (ENABLE_FLASH_WRITE == 1)
  long uint sizeT = 0;
  //数据表计数器，跨片上块临界时需要将i写入Flash
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

* 变量范围:

  bool8 IsReviewSize：查看烧写空间大小时屏蔽烧写代码。

* 返回值说明:菜单树对应的flash地址
* 功能介绍:   
  获取Flash变量组表信息读取函数，获取变量组信息。
*
* 关键备注：
* - 

  
* 未来提高:

*/
void FlashMenuWriteModule(bool8 IsReviewSize)
{
  FlashSectorProgramHandle(IsReviewSize);
}
/*
void FlashWriteResultReview();

* 变量范围:



* 返回值说明:
* 功能介绍:   
  Flash烧写结果浏览。
*
* 关键备注：
* - 

  
* 未来提高:

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

* 变量范围:



* 返回值说明:
* 功能介绍:   
  Flash Erase处理函数。
*
* 关键备注：
* - 

  
* 未来提高:

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
