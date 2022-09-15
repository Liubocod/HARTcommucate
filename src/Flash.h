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

#ifndef FLASH_H
#define FLASH_H
#include "HardwareSet.h"
#include "System.h"
//调试程序时，片上flash保存大量数据会严重影响烧写速度，因此通过该宏屏蔽片上数据表定义
#define ENABLE_FLASH_WRITE         0
//如果菜单容量超过片上flash容量，可分块向片外FLASH写入数据
#define FLASH_WRITE_PART1          1

#if  (ENABLE_FLASH_WRITE == 1) 
  #if  (FLASH_WRITE_PART_1 == 1) 
    #define	EJA530_INFO_ADDR         	        0X1000UL
    #define	CY_HVP7_PAGE_INFO_ADDR	                EJA530_INFO_ADDR+sizeof(G_EJA530_InfoPageArr)/sizeof(uchar)//2714
    #define	CY_HVP5_PAGE_INFO_ADDR	                CY_HVP7_PAGE_INFO_ADDR+sizeof(G_CY_HVP7PageArr)/sizeof(uchar)//3059
    #define	CY_TTS_V6_PAGE_INFO_ADDR	        CY_HVP5_PAGE_INFO_ADDR+sizeof(G_CY_HVP5_PageArr)/sizeof(uchar)//1886
    #define	RADAR_INFO_ADDR	                        CY_TTS_V6_PAGE_INFO_ADDR+sizeof(G_CY_TTS_V6PageArr)/sizeof(uchar)//2507
    #define	SIEMENS_INFO_ADDR	                RADAR_INFO_ADDR+sizeof(G_RadarInfoPageArr)/sizeof(uchar)//2599
    #define	EJA_INFO_ADDR	                        SIEMENS_INFO_ADDR+sizeof(G_SiemensInfoPageArr)/sizeof(uchar)//3611
    #define	LM_INFO_ADDR	                        EJA_INFO_ADDR+sizeof(G_EJA_InfoPageArr)/sizeof(uchar)//3473
    #define	HW_INFO_ADDR	                        LM_INFO_ADDR+sizeof(G_LM_InfoPageArr)/sizeof(uchar)//3381
    #define	CY_HVP7_RECEIVE_ADDR	                HW_INFO_ADDR+sizeof(G_HW_InfoPageArr)/sizeof(uchar)//2208
    #define	CY_HVP7_ITEM_ADDR	                CY_HVP7_RECEIVE_ADDR+sizeof(G_CY_HVP7_ReceiveStruct)/sizeof(uchar)//325
    #define	CY_HVP5_ITEM_ADDR	                CY_HVP7_ITEM_ADDR+sizeof(G_CY_HVP7ItemArr)/sizeof(uchar)//2744
    #define	CY_TTS_V6_ITEM_ADDR	                CY_HVP5_ITEM_ADDR+sizeof(G_CY_HVP5_ItemArr)/sizeof(uchar)//2032
    #define	RADAR_ITEM_ADDR	                        CY_TTS_V6_ITEM_ADDR+sizeof(G_CY_TTS_V6ItemArr)/sizeof(uchar)//2528
    #define	SIEMENS_ITEM_ADDR	                RADAR_ITEM_ADDR+sizeof(G_RadarMenuItemArr)/sizeof(uchar)//2312
    #define	EJA_ITEM_ADDR	                        SIEMENS_ITEM_ADDR+sizeof(G_SiemensMenuItemArr)/sizeof(uchar)//2752
    #define	LM_ITEM_ADDR	                        EJA_ITEM_ADDR+sizeof(G_EJA_MenuItemArr)/sizeof(uchar)//4488
    #define	HW_ITEM_ADDR	                        LM_ITEM_ADDR+sizeof(G_LM_MenuItemArr)/sizeof(uchar)//3480
    #define	EJA530_ITEM_ADDR	                HW_ITEM_ADDR+sizeof(G_HW_MenuItemArr)/sizeof(uchar)//3232
    #define	SIEMENS_TYPE1_SEND_ADDR	                EJA530_ITEM_ADDR+sizeof(G_EJA530_MenuItemArr)/sizeof(uchar)//2624
    #define	SIEMENS_TYPE1_RECEIVE_ADDR	        SIEMENS_TYPE1_SEND_ADDR+sizeof(G_SIEMENS6SendStruct)/sizeof(uchar)//279
    #define	HW_TYPE1_SEND_ADDR	                SIEMENS_TYPE1_RECEIVE_ADDR+sizeof(G_SIEMENS6ReceiveStruct)/sizeof(uchar)//155
    #define	HW_TYPE1_RECEIVE_ADDR	                HW_TYPE1_SEND_ADDR+sizeof(G_HW7SendStruct)/sizeof(uchar)//252
    #define	EJA530_SEND_ADDR	                HW_TYPE1_RECEIVE_ADDR+sizeof(G_HW7ReceiveStruct)/sizeof(uchar)//140
    #define	EJA530_RECEIVE_ADDR	                EJA530_SEND_ADDR+sizeof(G_Eja530SendStruct)/sizeof(uchar)//270
    #define	EJA_RECEIVE_ADDR	                EJA530_RECEIVE_ADDR+sizeof(G_Eja530ReceiveStruct)/sizeof(uchar)//150
    #define	EJA_SEND_ADDR	                        EJA_RECEIVE_ADDR+sizeof(G_EjaV5ReceiveStruct)/sizeof(uchar)//255
    #define	LM_SEND_ADDR	                        EJA_SEND_ADDR+sizeof(G_EjaV5SendStruct)/sizeof(uchar)//459
    #define	LM_RECEIVE_ADDR	                        LM_SEND_ADDR+sizeof(G_LM5SendStruct)/sizeof(uchar)//288
    #define	CY_TTS_RECEIVE_ADDR	                LM_RECEIVE_ADDR+sizeof(G_LM5ReceiveStruct)/sizeof(uchar)//160
    #define	CY_TTS_SEND_ADDR	                CY_TTS_RECEIVE_ADDR+sizeof(G_CY_TTS_V6ReceiveStruct)/sizeof(uchar)//165
    #define	RADAR_SEND_ADDR	                        CY_TTS_SEND_ADDR+sizeof(G_CY_TTS_V6SendStruct)/sizeof(uchar)//297
    #define	RADAR_RECEIVE_ADDR	                RADAR_SEND_ADDR+sizeof(G_RadarV5SendStruct)/sizeof(uchar)//549
    #define	CY_HVP7_SEND_ADDR	                RADAR_RECEIVE_ADDR+sizeof(G_RadarV5ReceiveStruct)/sizeof(uchar)//305
    #define	GENERAL_RECEIVE_ADDR	                CY_HVP7_SEND_ADDR+sizeof(G_CY_HVP7_SendStruct)/sizeof(uchar)//585
    #define	GENERAL_SEND_ADDR	                GENERAL_RECEIVE_ADDR+sizeof(G_GeneralV5ReceiveStruct)/sizeof(uchar)//110
    #define	CY_PDS_V6_RECEIVE_ADDR	                GENERAL_SEND_ADDR+sizeof(G_GeneralV5SendStruct)/sizeof(uchar)//198
    #define	CY_PDS_V6_SEND_ADDR	                CY_PDS_V6_RECEIVE_ADDR+sizeof(G_CY_PDS_V6ReceiveStruct)/sizeof(uchar)//195
    #define	CY_PDS_V6_INFO_ADDR	                CY_PDS_V6_SEND_ADDR+sizeof(G_CY_PDS_V6SendStruct)/sizeof(uchar)//351
    #define	CY_PDS_V6_ITEM_ADDR	                CY_PDS_V6_INFO_ADDR+sizeof(G_CY_PDS6InfoPageArr)/sizeof(uchar)//3680
    #define	GENERAL_PAGE_INFO_ADDR	                CY_PDS_V6_ITEM_ADDR+sizeof(G_CY_PDS6MenuItemArr)/sizeof(uchar)//3112
    #define	GENERAL_ITEM_ADDR	                GENERAL_PAGE_INFO_ADDR+sizeof(G_GeneralPageInfoArr)/sizeof(uchar)//2944
    #define	CY_PDS7_PAGE_INFO_ADDR	                GENERAL_ITEM_ADDR+sizeof(G_GeneralMenuItemArr)/sizeof(uchar)//3512
    #define	CY_PDS7_ITEM	                        CY_PDS7_PAGE_INFO_ADDR+sizeof(G_CY_PDS7InfoPageArr)/sizeof(uchar)//3335
    #define	CY_PDS7_RECEIVE_ADDR	                CY_PDS7_ITEM+sizeof(G_CY_PDS7ItemArr)/sizeof(uchar)//2880
    #define	CY_PDS7_SEND_ADDR	                CY_PDS7_RECEIVE_ADDR+sizeof(G_CY_PDS_V7ReceiveStruct)/sizeof(uchar)//320
    #define     RAYDAR_80G_INFO_ADDR                    CY_PDS7_SEND_ADDR+sizeof(G_CY_PDS_V7SendStruct)
    #define     RAYDAR_80G_ITEM_ADDR                    RAYDAR_80G_INFO_ADDR+sizeof(G_Raydar80GInfoPage1_0)
    #define     RAYDAR_80G_RECEIVE_ADDR                 RAYDAR_80G_ITEM_ADDR+sizeof(G_Raydar80GItem1_0)
    #define     RAYDAR_80G_SEND_ADDR                    RAYDAR_80G_RECEIVE_ADDR+sizeof(G_Raydar80GReceiveStruct)
    #define	VARIABLE_INFO_ADDR	                RAYDAR_80G_SEND_ADDR+sizeof(G_Raydar80GSendStruct)/sizeof(uchar)//576
    #define	HART_PAGE_VARIABLE_ARR	                VARIABLE_INFO_ADDR+sizeof(G_VariableStructureTable)/sizeof(uchar)//2436
    #define	VARIABLE_GROUP_ADDRESS	                HART_PAGE_VARIABLE_ARR+sizeof(G_HART_PageVariableArr)/sizeof(uchar)//1320
    #define	STRING_TABLE_ADDR	                VARIABLE_GROUP_ADDRESS+sizeof(G_VariableGroupAddress)/sizeof(uchar)//1410
    #define	EN_STR_CODE_ADDR	                STRING_TABLE_ADDR+sizeof(G_GeneralStrTable)/sizeof(uchar)//13608
    #define	CH_STR_CODE_ADDRESS	                EN_STR_CODE_ADDR+sizeof(G_EnlishShortStringArr)/sizeof(uchar)//24354
    #define	ASCII_6X8_LIB	                        CH_STR_CODE_ADDRESS+sizeof(ChineseShortStringArr)/sizeof(uchar)//3920
    #define	ASCII_6X16_LIB	                        ASCII_6X8_LIB+sizeof(Ascii_6x8)/sizeof(uchar)//588
    #define	ASCII_12X16_LIB	                        ASCII_6X16_LIB+sizeof(Ascii_6x16)/sizeof(uchar)//396
  #endif
#endif
typedef enum
{
  EJA530_PAGE,
  CY_HVP7_PAGE,
  CY_HVP5_PAGE,
  CY_TTS_V6_PAGE,
  RADAR_PAGE,
  SIEMENS_PAGE,
  EJA_PAGE,
  LM_PAGE,
  HW_PAGE,
  CY_HVP7_RECV,
  CY_HVP7_ITEM,
  CY_HVP5_ITEM,
  CY_TTS_V6_ITEM,
  RADAR_ITEM,
  SIEMENS_ITEM,
  EJA_ITEM,
  LM_ITEM,
  HW_ITEM,
  EJA530_ITEM,
  SIEMENS_SEND,
  SIEMENS_RECV,
  HW_SEND,
  HW_RECV,
  EJA530_SEND,
  EJA530_RECV,
  EJA_RECV,
  EJA_SEND,
  LM_SEND,
  LM_RECV,
  CY_TTS_RECV,
  CY_TTS_SEND,
  RADAR_SEND,
  RADAR_RECV,
  CY_HVP7_SEND,
  GENERAL_RECV,
  GENERAL_SEND,
  CY_PDS_V6_RECV,
  CY_PDS_V6_SEND,
  CY_PDS_V6_INFO,
  CY_PDS_V6_ITEM,
  GENERAL_PAGE,
  GENERAL_ITEM,
  CY_PDS7_PAGE,
  CY_PDS7_ITEM_,
  CY_PDS7_RECV,
  CY_PDS7_SEND,
  RAYDAR_80G_PAGE,
  RAYDAR_80G_ITEM,
  RAYDAR_80G_RECV,
  RAYDAR_80G_SEND,
  VARIABLE_INFO,
  HART_PAGE_VAR,
  VAR_GROUP,
  STRING_TABLE,
  EN_STR_CODE,
  CH_STR_CODE,
  ASCII_6X8_LIB_,
  ASCII_6X16_LIB_,
  ASCII_12X16_LIB_,
}DataSheetIndexDef;

/*
数据表寻址运算常亮，
系统先在0X1000UL地址之前保存的是每个数据表在flash中保存的地址，我称之为数据表寻址地址
然后根据这个寻址地址在flash中获取数据表信息,写入的寻址地址数据类型相对固定，
因此可以通过这个公式计算寻址地址保存跨度。
*/
#define DATA_SHEET_CONT_GET(INDEX)                        sizeof(uint)+sizeof(long uint)*INDEX
/*
  根据寻址地址读取对应的数据表信息。
*/
#define GET_DATASHEET_ADDR(FLASH_ADDR_INDEX,pAddr)        FlashSpiReadData(DATA_SHEET_CONT_GET(FLASH_ADDR_INDEX),sizeof(long uint),pAddr)

typedef enum
{
  PageProgram = 0x02,
  ReadData = 0x03,
  WriteDisable = 0x04,  
  Register1Status = 0x05,
  WriteEnable = 0x06,
  SectorErase = 0x20,
  BlockLock = 0x36,
  BlockUnlock = 0x36,
  BlockErase32B = 0x52,
  BlockErase64B = 0xD8,
  ChipErase = 0x60,
  ReadDeviceID = 0x90,
  GlobalUnclock = 0x98,
  PowerDown = 0xB9,
  ReleasePowerDown = 0xAb,
}FlashCmdDef;
typedef enum
{
  PageInfoAddress,
  ItemInfoAddress,
  CmdSendTableAddress,
  CmdReceiveTableAddress,
}AddressTypeDef;
extern uchar FlashSpiReadWriteByte(uchar TxData);
extern void FlashSpiPageProgram(long unsigned int Address,uint ByteNumber,uchar *TxBuff);
extern void FlashSpiInstructionSend(FlashCmdDef Instruction);
extern void FlashSpiErase(long unsigned int Address,FlashCmdDef Instruction);
extern void FlashPageInfoDownload(long unsigned int Address,long unsigned int sizeT,uchar* PagePtr);
extern void FlashCurrentPageInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentPageNum,uchar* CurrentPageInfo);
extern void FlashCurrentItemInfoGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CurrentItemNum,uchar* CurrentItemInfo);
extern void FlashStringInfoGet(uint StringNum,uchar* StringInfo);
extern void FlashStringCodeGet(StringDef *StringStruct,uchar* StringInfo,LanguageTypeDef Language);
extern void FlashVariableInfoGet(uint VariableIndex,uchar* VariableInfo);
extern void FlashCmdReceiveTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdReceiveTableInfo);
extern void FlashCmdSendTableGet(MenuTreeIndexDef MenuTreeIndex,
                             uint CmdArrIndex,uchar* CmdSendTableInfo);
extern void FlashStringReadLockHandle(uchar StructIndex,uint StringNum,LanguageTypeDef Language);
extern void FlashVariableGroupLoad(ArrIndexDef VariableIndex,PageVariableTableDef* VariableTable,VariableGroupDef* GroupTable);
extern void FlashMenuWriteModule(bool8 IsReviewSize);
extern void FlashWriteResultReview(bool8 IsRead);
extern void FlashReadLockHandle(bool8 IsReadLock);
extern bool8 FlashReadLockStatusGet();
extern void FlashWordLibInfoGet(long unsigned int Address,uchar StringNum,uchar* StringInfo);
extern void FlashSpiReadData(long unsigned int Address,long unsigned int ByteNumber,uchar *const RxBuff);
#endif