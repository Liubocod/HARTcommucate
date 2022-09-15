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



/****************************AT24CXX.c文件说明********************************/
// 该文件为存储芯片AT24CXX的底层驱动函数，微波开关使用的是AT24C64存储芯片
// AT24C64 为64k bit,即 8192字节
/*****************************************************************************/


#include "AT24C64.h"
#include "DataType.h" 
#include "HardwareSet.h"
  



#define  EEPROM_SDAIN_H	             1

#define	 DELAY_6US		  	     50          
#define	 DELAY_350US		  	     2000
#define	 DELAY_1400US		  	     8000
#define	 DELAY_1800US		  	     10000
#define  DELAY_5MS                           10000

#define  EEPROM_TRY_TIME             3

#define  EEPROM_GENERATE_ACK         0
#define  EEPROM_UNGENERATE_ACK       1


bool8   G_EepromDeviceAck = FALSE;   // EEPROM应答变量，FALSE表示无应答，TRUE表示有应答




/** void  AT24CxxDelay(uint16  DelayTime)     //函数名称和参量和返回值类型。
* 变量范围: DelayTime为延时时间参数，0 ≤ DelayTime ≤ 65535
*
* 返回值说明: void
*
* 功能介绍: 延时函数
*
* 关键备注：该延时函数适用于延时时间较短的场合，时间较长的延时应在定时器中断中实现
*
* 未来提高:
* 
*/
void  AT24CxxDelay(uint16  DelayTime)
{ 
      uint16  i;  // 循环变量
	
      for (i = 0; i < DelayTime; i++);
}


/**void  I2c_initial()    //函数名称和参量和返回值类型。
* 变量范围: 
*
* 返回值说明: void
*
* 功能介绍: I2C初始化
*
* 关键备注：
*
* 未来提高:
* 
*/
void  I2c_initial()
{
      EEPROM_SCL_DIR_OUT;
      EEPROM_SDA_DIR_OUT;
      EEPROM_SDA_L;
      EEPROM_SCL_L;
      AT24CxxDelay(DELAY_6US);
}


/**void  Start_I2c()    //函数名称和参量和返回值类型。
* 变量范围: 
*
* 返回值说明: void
*
* 功能介绍: 产生I2C起始信号，SCL为高电平时，SDA由高电平向低电平跳变，开始传送数据
*
* 关键备注：
*
* 未来提高:
* 
*/
void  Start_I2c()
{
      I2c_initial();
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_H; 
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_L; 
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_L;   
      AT24CxxDelay(DELAY_6US);
}


/**void  Stop_I2c()    //函数名称和参量和返回值类型。
* 变量范围: 
*
* 返回值说明: void
*
* 功能介绍:产生I2C停止信号，SCL为高电平时，SDA由低电平向高电平跳变，结束传送数据
*
* 关键备注：
*
* 未来提高:
* 
*/
void  Stop_I2c()
{
      EEPROM_SDA_DIR_OUT;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_L;  
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;   
      AT24CxxDelay(DELAY_6US);
      EEPROM_SDA_H;  
      AT24CxxDelay(DELAY_6US);
}

/**bool8 Wait_Ack_I2C()   //函数名称和参量和返回值类型。
* 变量范围:  
*
* 返回值说明: bool8，FALSE表示无应答，TRUE表示有应答
*
* 功能介绍: I2C等待应答信号到来。接收设备在第九个时钟周期会发出低电平应答信号，以表明它已收到地址或数据。
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  Wait_Ack_I2C()
{
      EEPROM_SDA_H;         
      EEPROM_SDA_DIR_IN;
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);
      if (EEPROM_SDAIN == EEPROM_SDAIN_H)
      { 
          EEPROM_SCL_L;
          EEPROM_SDA_DIR_OUT;
          return FALSE;
      }
      else
      {
         EEPROM_SCL_L;
         EEPROM_SDA_DIR_OUT;
         return TRUE;
      }      
}


/**void  SendByte(uchar8  Data)    //函数名称和参量和返回值类型。
* 变量范围:Data为发送的字节数据，0 ≤ Data ≤ 255 
*
* 返回值说明: void
*
* 功能介绍: 发送一个字节
*
* 关键备注：传输数据时，只有在SCL为高电平时，SDA上的电平为有效数据。
*           编写单片机向总线送数据程序时则可以在SCL还在低电平时，把数据电平送到SDA，
*           然后拉高SCL，这时SDA不应有电平跳变，延时后拉低SCL，再进行下一位的数据传送直到完成。
*
* 未来提高: 
* 
*/
void  SendByte(uchar8  Data)
{
      uchar8  i;  // 循环变量

      EEPROM_SDA_DIR_OUT;
      EEPROM_SCL_DIR_OUT;
      for (i = 0; i < 8; i++)
      { 
          if ( (Data << i) & 0x80 )
          {
                EEPROM_SDA_H;  
          }
          else 
          { 
                EEPROM_SDA_L;
          }
          AT24CxxDelay(DELAY_6US);   
          EEPROM_SCL_H;         
          AT24CxxDelay(DELAY_6US);       
          EEPROM_SCL_L;
          AT24CxxDelay(DELAY_6US); 
     }
     G_EepromDeviceAck = Wait_Ack_I2C();
}


/**uchar8  RcvByte()   //函数名称和参量和返回值类型。
* 变量范围: 无 
*
* 返回值说明: uchar8，范围0x00 ≤ ReceivedData ≤ 0xFF 
*
* 功能介绍:接收一个字节
*
* 关键备注：
*
* 未来提高:
* 
*/ 
uchar8  RcvByte()
{
        uchar8  ReceivedData = 0;   // 接收到的数据 
        uchar8  i;   // 循环变量
      
        EEPROM_SDA_H;         
        EEPROM_SDA_DIR_IN;
        for (i = 0; i < 8; i++)
        {
            EEPROM_SCL_L;     
            AT24CxxDelay(DELAY_6US); 
            EEPROM_SCL_H;     
            AT24CxxDelay(DELAY_6US);
            ReceivedData = ReceivedData << 1;
            if (EEPROM_SDAIN == EEPROM_SDAIN_H)
            {
                ReceivedData += 1; 
            }
            AT24CxxDelay(DELAY_6US);
        }
        EEPROM_SCL_L;
        AT24CxxDelay(DELAY_6US);
        return(ReceivedData);
}


/**void Ack_I2C(uchar8  Data)   //函数名称和参量和返回值类型。
* 变量范围:  Data为是否应答信号，TRUE时不产生应答，为FALSE时产生应答
*
* 返回值说明: void
*
* 功能介绍: I2C应答，Data为1时不产生ACK应答，为0时产生ACK应答
*
* 关键备注：接收数据的IC在接收到8bit数据后，向发送数据的IC发出特定的低电平信号，表示已经收到数据。
*
* 未来提高: 
* 
*/ 
void  Ack_I2c(uchar8  Data)
{
      EEPROM_SDA_DIR_OUT;
      if (Data)
      {
          EEPROM_SDA_H;  
      }    
      else
      {
          EEPROM_SDA_L;
      }
      AT24CxxDelay(DELAY_6US);
      EEPROM_SCL_H;
      AT24CxxDelay(DELAY_6US);             
      EEPROM_SCL_L;              
      AT24CxxDelay(DELAY_6US);
}


/**bool8  ISendStr(uchar8 SlaveAddress, uint16 SaveAddress, ucha8r  *Str, uchar8 StringLength)  //函数名称和参量和返回值类型。
* 变量范围: SlaveAddress为从机设备地址，1 0 1 0 A2 A1 A0 R/W ，0xA0 ≤ SlaveAddress ≤ 0xAE ,本软件只有一个AT24C64，其地址设为0xA0
*           SaveAddress为数据待存储的地址，0 ≤ SaveAddress ≤ 8192
*           Str为指向字符型数据的地址，里面存放待存储数据的首字节
*           StringLength为待存储数据的字节数，0 ≤ StringLength ≤ 255
*
* 返回值说明: bool8，存储成功返回TRUE，存储失败返回FALSE
*
* 功能介绍: 在从机地址为SlaveAddress的AT24CXX指定地址SaveAddress写入StringLength个字节数据
*
* 关键备注：1、AT24C64支持32字节页写模式，当存储地址是32的整数倍时，进行翻页操作
*              n个字节发送时需要发送第一个字节的地址，然后一次性发送n字节的写入数据后，再发送停止位。
*              写入过程中其余的地址增量自己由芯片内部完成。
*           2、进行页写时，当数据的存储地址达到页边界地址（地址为32的整数倍）时，下一个字节将会存放在同一页的起始地址处
*              为避免这种情况的出现，当存储地址是32的整数倍时，发送停止条件，延时一会儿再次发送起始条件等写操作
*           3、每次写完一个字节后，需要延时至少约2条AT24CxxDelay(DELAY_350US);语句才可以从EEPROM中读取此次写入的数据
*              每次写完超过32个字节后，需要延时至少约4条AT24CxxDelay(DELAY_350US);语句才可以从EEPROM中读取此次写入的数据
*           4、写一个字节0.8ms
*           
* 未来提高: 
* 
*/ 
bool8  ISendStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)
{
        uchar8  i;  // 循环变量

        Start_I2c();             
        SendByte(SlaveAddress);           
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        SendByte(SaveAddress>>8);            // send the first address
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        SendByte(SaveAddress & 0xFF);        // send second address
        if (G_EepromDeviceAck == FALSE)
        {
            return FALSE;
        }
        i = 0;
        do
        {
              SendByte(*Str);           
              if (G_EepromDeviceAck == FALSE)
              {
                  return FALSE;
              }
              Str++;
              i++;
              SaveAddress++;
              if ( ((SaveAddress & 0x1F) == 0) && (i < StringLength) ) //The 64K EEPROM is capable of 32-byte Page Writes
              {
                      Stop_I2c();
                      AT24CxxDelay(DELAY_1800US);    // 当连续写大于32个字节，有地址翻页时，AT24C64支持32字节页写，
                                                     // 遇到地址翻页时，至少需要DELAY_1400US=800 ，为增加可靠型，延时1.8ms						       
                      Start_I2c();             
                      SendByte(SlaveAddress);           
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;
                      }
                      SendByte(SaveAddress>>8);          // send the first address
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;
                      }
                      SendByte(SaveAddress & 0xff);      // send second address
                      if (G_EepromDeviceAck == FALSE)
                      {
                          return FALSE;	
                      }  
              }
        }
        while(i < StringLength);
        Stop_I2c();              
        return TRUE;
}


/**uchar8  IRcvStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)  //函数名称和参量和返回值类型。
* 变量范围: SlaveAddress为从机设备地址，1 0 1 0 A2 A1 A0 R/W, 0xA0 ≤ SlaveAddress ≤ 0xAE ,本软件只有一个AT24C64，其地址设为0xA0
*           SaveAddress为数据存储的地址，0 ≤ SaveAddress ≤ 8192
*           Str为指向字符型数据的地址，里面存放所需读取数据的首字节
*           StringLength为待读取数据的字节数，0 ≤ StringLength ≤ 255
*
* 返回值说明: uchar8，读取成功返回TRUE，读取失败返回FALSE
*
* 功能介绍: 在从机地址为SlaveAddress的AT24CXX指定地址SaveAddress读取StringLength个字节数据
*
* 关键备注: 1、连续读取数据时，每读取一个字节，主机回应芯片一个低电平的ACK应答，
*              当读取完最后一个字节时，主机不应答
*           2、读取一个字节数据时耗时1.2ms
*
* 未来提高: 
* 
*/ 
uchar8  IRcvStr(uchar8 SlaveAddress, uint16 SaveAddress, uchar8 *Str, uchar8 StringLength)
{
        uchar8  i;  // 循环变量

        Start_I2c();            
        SendByte(SlaveAddress);        
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        SendByte(SaveAddress>>8);          //send first address 
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        SendByte(SaveAddress & 0xFF);     //send second address    
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;  
        } 
        Start_I2c();
        SendByte(SlaveAddress + 1);
        if (G_EepromDeviceAck == FALSE)
        {
          return FALSE;
        }
        for (i = 0; i < StringLength - 1; i++)
        {
            *Str = RcvByte();         
            Ack_I2c(EEPROM_GENERATE_ACK);         
            Str++;
        }
        *Str = RcvByte();
        Ack_I2c(EEPROM_UNGENERATE_ACK);       
        Stop_I2c();                  
        return TRUE;
}



/**void  WriteEEPChar(uint16 SaveAddress, uchar8 Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255 
*
* 返回值说明: void
*
* 功能介绍: 写一个字节字符型数据Data到EEProm的SaveAddress地址
*
* 关键备注:
*
* 未来提高:
* 
*/ 
void  WriteEEPChar(uint16 SaveAddress, uchar8 Data)
{
      ISendStr(EEPROM_DEVICE_ADDRESS, SaveAddress, &Data, CHAR_BYTENUM);	   
}


/**void ReadByte(uint16 SaveAddress, uchar8 * Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: void
*
* 功能介绍: 从EEProm的SaveAddress地址中读一个字节字符型数据，放在地址Data中
*
* 关键备注:
*
* 未来提高:
* 
*/ 
void  ReadEEPChar(uint16 SaveAddress, uchar8 * Data)
{  
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, Data, CHAR_BYTENUM);   
}


/**bool8 SaveChar(uint16 SaveAddress, uchar8 Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*
* 返回值说明: bool8，存储成功返回TRUE，存储失败返回FALSE

* 功能介绍: 保存字符型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回SUCCESS，否则返回FAIL
*
* 关键备注: 如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*           执行一次该函数约4ms
*
* 未来提高:
* 
*/ 
bool8  SaveChar(uint16 SaveAddress, uchar8 Data)
{
        uchar8 EEPTemp;  // 临时变量，用于存放从AT24CXX中读出的数据
        uchar8 i;        // 循环变量

        for (i = 0; i < EEPROM_TRY_TIME; i++)
        {	
              WriteEEPChar(SaveAddress, Data);   	     
              AT24CxxDelay(DELAY_5MS);  // 每次写完数据后，由于写数据时发送完停止命令后，会进入一个内部写周期，内部写周期(字节写或页写)最大5ms
                                           // 因此需要延时一会儿再读取
                                                                       // The write cycle time tWR is the time from a valid stop condition 
                                       // of a write sequence to the end of the internal clear/write cycle.
              ReadEEPChar(SaveAddress, &EEPTemp);
              if (EEPTemp == Data) 
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);  // 记录事件故障次数，包括记录某器件最近100次以内通讯发生故障次数、近期10000次的故障次数、自上电以来的故障总数
                  return TRUE;
              }
              else
              {		
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**bool8  LoadChar(uint16 SaveAddress, uchar8 * Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: bool8，读取成功返回TRUE，失败返回FALSE
*
* 功能介绍: 从EEProm的SaveAddress地址中读一个字节数据，放在地址Data中
*
* 关键备注: 1、如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*           2、执行一次该函数约2.2ms
*
* 未来提高: 
* 
*/ 
bool8  LoadChar(uint16 SaveAddress, uchar8 *Data)
{
        uchar8 EEPTemp; // 临时变量，用于存放从AT24CXX中读出的数据
        uchar8 i;       // 循环变量	

        for (i = 0;i < EEPROM_TRY_TIME;i++)
        {	
              ReadEEPChar(SaveAddress, Data);
              ReadEEPChar(SaveAddress, &EEPTemp);
              if (EEPTemp == *Data) 
              {
//		   RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                 return TRUE;
              }
              else
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**void  WriteEEPInt(uint16 SaveAddress,uint16 Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 65535  
*
* 返回值说明: void
*
* 功能介绍: 写整型数据Data到EEProm，首字节存储在EEProm的地址SaveAddress中，共占SaveAddress、SaveAddress+1两个字节地址
*
* 关键备注:
*
* 未来提高:
* 
*/ 
void  WriteEEPInt(uint16 SaveAddress,uint16 Data)
{
      uchar8 * ByteAddress;  // 指向Data首字节数据的的指针
    
      ByteAddress = (uchar8*)&Data;
      ISendStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, INT_BYTENUM);
}

/**void  ReadEEPInt(uint16 SaveAddress,uint16 Data)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 65535  
*
* 返回值说明: void
*
* 功能介绍: 从EEProm的地址SaveAddress~SaveAddress+1中读两个字节整型数据，存放在以Data开头的地址中
*
* 关键备注:
*
* 未来提高:
* 
*/ 
void  ReadEEPInt(uint16 SaveAddress, uint16 * Data)
{
      uchar8 * ByteAddress;  // 指向Data首字节数据的的指针

      ByteAddress = (uchar8*)Data;
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, INT_BYTENUM);
}


/**bool8  SaveInt(uint16 SaveAddress,uint16 Data)   //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为待存储的数据，0 ≤ Data ≤ 65535 
*
* 返回值说明: bool8 ，存储成功返回TRUE，失败返回FALSE
*
* 功能介绍: 保存整型数据Data到EEProm的地址SaveAddress~SaveAddress+1中，,保存后再读出，如果读出值和保存的值一致，返回SUCCESS，否则返回FAIL
*
* 关键备注: 如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
bool8  SaveInt(uint16 SaveAddress, uint16 Data)
{
      uint16 EEPTemp;  // 临时变量，用于存放从AT24CXX中读出的数据
      uchar8 i;       // 循环变量

      for (i = 0; i < EEPROM_TRY_TIME; i++)
      {	
            WriteEEPInt(SaveAddress,Data);
            AT24CxxDelay(DELAY_5MS);  // 每次写完数据后，由于写数据时发送完停止命令后，会进入一个内部写周期，内部写周期(字节写或页写)最大5ms
                                         // 因此需要延时一会儿再读取
                                                                     // The write cycle time tWR is the time from a valid stop condition 
                                     // of a write sequence to the end of the internal clear/write cycle.
            ReadEEPInt(SaveAddress, &EEPTemp);
            if (EEPTemp == Data)
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {			
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
      }
      return FALSE;
}

/**bool8  LoadInt(uint16 SaveAddress,uint16 * Data)   //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向整型数据的指针，里面存放读取出来的数据首字节  
*
* 返回值说明: bool8, 读取成功返回TRUE，失败返回FALSE
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+1中读两个字节整型数据，存放在以Data开头的地址中
*
* 关键备注: 如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
bool8  LoadInt(uint16 SaveAddress,  uint16 * Data)
{
      uint16 EEPTemp;  // 临时变量，用于存放从AT24CXX中读出的数据
      uchar8 i;       // 循环变量	

      for (i = 0; i < EEPROM_TRY_TIME; i++)
      {	
            ReadEEPInt(SaveAddress, Data);
            ReadEEPInt(SaveAddress, &EEPTemp);
            if (EEPTemp == *Data)
            { 
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
      }
      return FALSE;
}


/**void  WriteEEPFloat(uint16 SaveAddress, float  Data)  //函数名称和参量和返回值类型。
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
void  WriteEEPFloat(uint16 SaveAddress, float Data)
{
      uchar8 * ByteAddress;  // 指向Data首字节数据的的指针
    
      ByteAddress = (uchar8*)&Data;
      ISendStr(EEPROM_DEVICE_ADDRESS,SaveAddress,ByteAddress,FLOAT_BYTENUM);	
}


/**void ReadEEPFloat (uint16 SaveAddress, float * Data)  //函数名称和参量和返回值类型。
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
void  ReadEEPFloat (uint16 SaveAddress, float * Data)
{
      uchar8 * ByteAddress;  // 指向Data首字节数据的的指针
	
      ByteAddress = (uchar8*)Data;
      IRcvStr(EEPROM_DEVICE_ADDRESS, SaveAddress, ByteAddress, FLOAT_BYTENUM);	
}


/**bool8  SaveFloat(uint16 SaveAddress, float  Data)  //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为待存储的数据，3.4e-38 ≤ Data ≤ 3.4e38 
*
* 返回值说明: bool8, 写入成功返回TRUE，失败返回FALSE
*
* 功能介绍: 写浮点型数据Data到EEProm，首字节存储在EEProm的地址SaveAddress中，共占SaveAddress~SaveAddress+3四个字节地址
*
* 关键备注：如果一次存储不成功，则再存储一次，若存储3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
bool8  SaveFloat(uint16 SaveAddress, float Data)
{
        float EEPTemp;   // 临时变量，用于存放从AT24CXX中读出的数据
        uchar8 i; // 循环变量

        for (i = 0; i < EEPROM_TRY_TIME; i++)
        {		
              WriteEEPFloat(SaveAddress,Data);
              AT24CxxDelay(DELAY_5MS);  // 每次写完数据后，由于写数据时发送完停止命令后，会进入一个内部写周期，内部写周期(字节写或页写)最大5ms
                                           // 因此需要延时一会儿再读取
                                           // The write cycle time tWR is the time from a valid stop condition 
                                           // of a write sequence to the end of the internal clear/write cycle.
              ReadEEPFloat(SaveAddress, &EEPTemp);
              if (EEPTemp == Data) 
              {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                  return TRUE;
              }
              else
              {			
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
              }
        }
        return FALSE;
}


/**bool8 ReadEEPFloat (uint16 SaveAddress, float * Data)  //函数名称和参量和返回值类型。
* 变量范围:  SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*            Data为指向浮点型数据的指针，里面存放读取出来的数据首字节 
*  
* 返回值说明: bool8，读取成功返回TRUE，失败返回FALSE
*
* 功能介绍:从EEProm的地址SaveAddress~SaveAddress+3中读四个字节数据，存放在以Data开头的地址中
*
* 关键备注：如果一次读取不成功，则再读取一次，若读取3次均不成功，则返回0（FAIL）
*
* 未来提高:
* 
*/ 
bool8  LoadFloat(uint16 SaveAddress, float * Data)
{
       float EEPTemp;    // 临时变量，用于存放从AT24CXX中读出的数据
       uchar8 i;  // 循环变量	

       for (i = 0; i < EEPROM_TRY_TIME; i++)
       {
            ReadEEPFloat(SaveAddress,Data);	
            ReadEEPFloat(SaveAddress,&EEPTemp);
            if (EEPTemp == *Data)
            {
//			    RecordEventFaultNumber(&EEpromPerfV,FAULT_UNHAPPEN);
                return TRUE;
            }
            else
            {
//			RecordEventFaultNumber(&EEpromPerfV,FAULT_HAPPEN);
            }
       }
       return FALSE;
}


/**bool8  LoadCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，读取成功返回TRUE，失败返回FALSE
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个字节数据，放在地址Data~Data+ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  LoadCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadChar(SaveAddress + i, (Data + i)) != TRUE)
            {
                return FALSE;	
            } 
       }
       return TRUE;
}


/**bool8  LoadIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的整型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: bool8，读取成功返回TRUE，失败返回FALSE
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个整型数据，放在地址Data~Data+2*ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  LoadIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadInt(SaveAddress + i*INT_BYTENUM, (Data + i))!=TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  LoadFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为指向字符型数据的指针，里面存放读取出来的数据首字节  
*           ArrayLength为待读取的浮点型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: bool8，读取成功返回TRUE，失败返回FALSE
*
* 功能介绍: 从EEProm的SaveAddress地址中读ArrayLength个浮点型数据，放在地址Data~Data+4*ArrayLength-1中
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  LoadFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量

       for (i = 0; i < ArrayLength; i++)
       {
            if (LoadFloat(SaveAddress+i*FLOAT_BYTENUM, (Data+i))!=TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  SaveCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: unsigned char，存储成功返回TRUE，失败返回FALSE
*
* 功能介绍: 保存字符型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  SaveCharArray(uint16 SaveAddress, uchar8 * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveChar(SaveAddress + i, *(Data + i)) != TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8 SaveIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: bool8，存储成功返回TRUE，失败返回FALSE
*
* 功能介绍: 保存整型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  SaveIntArray(uint16 SaveAddress, uint16 * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveInt(SaveAddress + i*INT_BYTENUM, *(Data+i)) != TRUE)
            {
                return FALSE;
            }
       }
       return TRUE;
}


/**bool8  SaveIntArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)   //函数名称和参量和返回值类型。
* 变量范围: SaveAddress为存储地址，0 ≤ SaveAddress ≤ 8191
*           Data为待存储的数据，0 ≤ Data ≤ 255   
*           ArrayLength为待保存的字符型数组的长度，0 ≤ ArrayLength ≤ 65535
*
* 返回值说明: bool8，存储成功返回TRUE，失败返回FALSE
*
* 功能介绍: 保存浮点型数据Data到EEProm的SaveAddress地址，保存后再读出，如果读出值和保存的值一致，返回OK，否则返回FAIL
*
* 关键备注：
*
* 未来提高:
* 
*/ 
bool8  SaveFloatArray(uint16 SaveAddress, float * Data, uint16 ArrayLength)
{
       uint16 i;  // 循环变量
    
       for (i = 0;i < ArrayLength;i++)
       {
            if (SaveFloat(SaveAddress + i * FLOAT_BYTENUM, *(Data + i)) != TRUE)
            {
                return FALSE;
            }
            else
            {
              ;
            }
       }
       return TRUE;
}


