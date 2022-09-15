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



/****************************iic_protocal.c文件说明***************************/
//该文件为存储芯片AT24CXX的底层驱动函数
/*****************************************************************************/



#include "iic_protocal.h"




unsigned char Ack;  //应答标志位，0表示无应答，1表示有应答




/** void  Delay(unsigned int Time)     //函数名称和参量和返回值类型。
* 变量范围:Time为延时时间参数，0 ≤ Time ≤ 65535
*
* 返回值说明: void
*
* 功能介绍: 延时函数
*
* 关键备注：Time为1时延时约2.25us
*
* 未来提高:
* 
*/
void  Delay(unsigned int Time)
{ 
	unsigned int i;
	
    for (i = 0;i < Time;i++);
}



/********************************以下为存储芯片AT24CXX底层驱动函数**********************************/

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
	I2C_SCLOUT;
	I2C_SDAOUT;
  	I2C_SDA_0;
	I2C_SCL_0;
	Delay(DELAYSTAY);
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
	Delay(DELAYSTAY);
	I2C_SDA_1; 
	Delay(DELAYSTAY);
	I2C_SCL_1;
	Delay(DELAY_VALUE_10);
    I2C_SDA_0; 
    Delay(DELAYUP);
    I2C_SCL_0;   
    Delay(DELAYSTAY);
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
  I2C_SDAOUT;
  Delay(DELAYSTAY);
  I2C_SDA_0;  
  Delay(DELAYSTAY);
  I2C_SCL_1;   
  Delay(DELAY_VALUE_10);
  I2C_SDA_1;  
  Delay(DELAYSTAY);
}

/**unsigned char Wait_Ack_I2C()   //函数名称和参量和返回值类型。
* 变量范围:  
*
* 返回值说明: unsigned char，0接收应答失败，1接收应答成功
*
* 功能介绍: I2C等待应答信号到来。接收设备在第九个时钟周期会发出低电平应答信号，以表明它已收到地址或数据。
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char Wait_Ack_I2C()
{
    I2C_SDA_1;         
    I2C_SDAIN;
    Delay(DELAYSTAY);
    I2C_SCL_1;
    Delay(DELAY_VALUE_16);
    if (I2C_DATAIN == I2C_DATAIN_1)
    {
      I2C_SCL_0;
      I2C_SDAOUT;
      return I2C_ACK_FAIL;
    }
    else
    {
      I2C_SCL_0;
      I2C_SDAOUT;
      return I2C_ACK_SUCCESS;
    }      
}


/**void  SendByte(unsigned char Data)    //函数名称和参量和返回值类型。
* 变量范围:Data为发送的字节数据，0 ≤ Data ≤ 255 
*
* 返回值说明: void
*
* 功能介绍: 发送一个字节，返回从机有无应答信号，Ack = 1有应答，Ack = 0无应答
*
* 关键备注：传输数据时，只有在SCL为高电平时，SDA上的电平为有效数据。
*           编写单片机向总线送数据程序时则可以在SCL还在低电平时，把数据电平送到SDA，
*           然后拉高SCL，这时SDA不应有电平跳变，延时后拉低SCL，再进行下一位的数据传送直到完成。
*
* 未来提高:
* 
*/
void  SendByte(unsigned char Data)
{
  unsigned char BitCnt;
  
  I2C_SDAOUT;
  I2C_SCLOUT;
  for (BitCnt = 0;BitCnt < 8;BitCnt++)
  { 
    if ((Data<<BitCnt)&0x80)
	    I2C_SDA_1;  
    else  
	    I2C_SDA_0;
    Delay(DELAYUP);   
    I2C_SCL_1;         
    Delay(DELAYSTAY);       
    I2C_SCL_0;
    Delay(DELAYSTAY); 
  }
  Ack =  Wait_Ack_I2C();
}


/**unsigned char RcvByte()   //函数名称和参量和返回值类型。
* 变量范围: 无 
*
* 返回值说明: unsigned char，范围0 ≤ Retc ≤ 255 
*
* 功能介绍:接收一个字节
*
* 关键备注：
*
* 未来提高:
* 
*/ 
unsigned char  RcvByte()
{
  unsigned char  Retc = 0;
  unsigned char  BitCnt; 
	  
  I2C_SDA_1;         
  I2C_SDAIN;
  for (BitCnt = 0;BitCnt < 8;BitCnt++)
  {
    I2C_SCL_0;     
    Delay(DELAYSTAY); 
    I2C_SCL_1;     
    Delay(DELAYSTAY);
    Retc = Retc<<1;
    if (I2C_DATAIN == I2C_DATAIN_1)
	    Retc += 1; 
    Delay(DELAYSTAY);
  }
  I2C_SCL_0;
  Delay(DELAYSTAY);
  return(Retc);
}


/**void Ack_I2C(unsigned char  Data)   //函数名称和参量和返回值类型。
* 变量范围:  Data为选择信号，0 ≤ Data ≤ 1，Data为1时不产生ACK应答，为0时产生ACK应答
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
void  Ack_I2c(unsigned char  Data)
{
  I2C_SDAOUT;
  if (Data)
      I2C_SDA_1;      
  else
      I2C_SDA_0;
  Delay(DELAYSTAY);
  I2C_SCL_1;
  Delay(DELAYSTAY);             
  I2C_SCL_0;              
  Delay(DELAYSTAY);
}


/**unsigned char  ISendStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)  //函数名称和参量和返回值类型。
* 变量范围: SlaveAddress为从机设备地址，1 0 1 0 A2 A1 A0 R/W ，0xA0 ≤ SlaveAddress ≤ 0xAE ,本软件只有一个AT24C64，其地址设为0xA0
*           SaveAddress为数据待存储的地址，0 ≤ SaveAddress ≤ 8192
*           Str为指向字符型数据的地址，里面存放待存储数据的首字节
*           StringLength为待存储数据的字节数，0 ≤ StringLength ≤ 255
*
* 返回值说明: unsigned char，存储成功返回1，存储失败返回0
*
* 功能介绍: 在从机地址为SlaveAddress的AT24CXX指定地址SaveAddress写入StringLength个字节数据
*
* 关键备注：AT24C64支持32字节页写模式，当存储地址是31的整数倍时，进行翻页操作
*           n个字节发送时需要发送第一个字节的地址，然后一次性发送n字节的写入数据后，再发送停止位。
*           写入过程中其余的地址增量自己由芯片内部完成。
*
* 未来提高:
* 
*/ 
unsigned char  ISendStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)
{
	unsigned char  i;
	
	Start_I2c();             
	SendByte(SlaveAddress);           
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	SendByte(SaveAddress>>8);          // send the first address
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	SendByte(SaveAddress & 0xff);        // send second address
	if (Ack == I2C_ACK_FAIL)
	    return FAIL;
	i = 0;
	do
	{
		SendByte(*Str);           
		if (Ack == I2C_ACK_FAIL)
	        return FAIL;
		Str++;
		i++;
		SaveAddress++;
		if (((SaveAddress&0x1F) == 0)&&(i< StringLength)) //The 64K EEPROM is capable of 32-byte Page Writes
		{
			Stop_I2c();
			Delay(DELAYSTAYL);
  			Delay(DELAYSTAYL);             
			Delay(DELAYSTAYL);
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
  			Delay(DELAYSTAYL);             
			Start_I2c();             
			SendByte(SlaveAddress);           
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;
			SendByte(SaveAddress>>8);          // send the first address
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;
			SendByte(SaveAddress & 0xff);      // send second address
			if (Ack == I2C_ACK_FAIL)
	            return FAIL;			
		}
	}
	while(i< StringLength);
	Stop_I2c();              
	return OK;
}


/**unsigned char IRcvStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)  //函数名称和参量和返回值类型。
* 变量范围: SlaveAddress为从机设备地址，1 0 1 0 A2 A1 A0 R/W, 0xA0 ≤ SlaveAddress ≤ 0xAE ,本软件只有一个AT24C64，其地址设为0xA0
*           SaveAddress为数据存储的地址，0 ≤ SaveAddress ≤ 8192
*           Str为指向字符型数据的地址，里面存放所需读取数据的首字节
*           StringLength为待读取数据的字节数，0 ≤ StringLength ≤ 255
*
* 返回值说明: unsigned char，读取成功返回1，读取失败返回0
*
* 功能介绍: 在从机地址为SlaveAddress的AT24CXX指定地址SaveAddress读取StringLength个字节数据
*
* 关键备注：连续读取数据时，每读取一个字节，主机回应芯片一个低电平的ACK应答，
*           当读取完最后一个字节时，主机不应答，
*
* 未来提高:
* 
*/ 
unsigned char  IRcvStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength)
{
  unsigned char  i;
  
  Start_I2c();            
  SendByte(SlaveAddress);        
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  SendByte(SaveAddress>>8);          //send first address 
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  SendByte(SaveAddress & 0xff);        
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;       //sebd second address
  Start_I2c();
  SendByte(SlaveAddress + 1);
  if (Ack == I2C_ACK_FAIL)
	  return FAIL;
  for (i=0;i < StringLength - 1;i++)
  {
    *Str = RcvByte();         
    Ack_I2c(I2C_GENERATE_ACK);         
    Str++;
  }
  *Str = RcvByte();
  Ack_I2c(I2C_UNGENERATE_ACK);       
  Stop_I2c();                  
  return OK;
}


