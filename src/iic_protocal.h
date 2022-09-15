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



/****************************iic_protocal.h文件说明**************************************/
//该文件为iic_protocal.c文件定义了一些宏定义，以及对可被其它文件调用的变量和函数进行声明
/****************************************************************************************/



/********************************存储芯片AT24CXX相关定义*************************************/
#define I2C_SDAIN          P3DIR_bit.P3DIR1 = 0            //set direction of I2C_SDA sinal in
#define I2C_SDAOUT	   P3DIR_bit.P3DIR1 = 1            //set direction of I2C_SDA signal out
#define I2C_SCLOUT         P3DIR_bit.P3DIR2 = 1            //set direction of I2C_SCL signal out

#define I2C_DATAIN         P3IN_bit.P3IN1                //"输入"
#define I2C_SDA_1          P3OUT_bit.P3OUT1 = 1            //set I2C_SDA signal 1
#define I2C_SDA_0          P3OUT_bit.P3OUT1 = 0             //reset I2C_SDA signal 0
#define I2C_SCL_1          P3OUT_bit.P3OUT2 = 1             //set I2C_SCL signal 1
#define I2C_SCL_0          P3OUT_bit.P3OUT2 = 0             //reset I2C_SCL signal 0

#define I2C_ADDRESS        0xa0 


#define I2C_ACK_SUCCESS    1
#define I2C_ACK_FAIL       0

#define I2C_GENERATE_ACK   0
#define I2C_UNGENERATE_ACK 1

#define I2C_DATAIN_1	   1

#define DELAYUP            0
#define DELAYSTAY          8
#define	DELAY_VALUE_10	   10
#define	DELAY_VALUE_16	   16
#define	DELAYSTAYL		   200

#define OK 				   1
#define FAIL 			   0




//对外文件
unsigned char  IRcvStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength);
unsigned char  ISendStr(unsigned char  SlaveAddress,unsigned int  SaveAddress,unsigned char  *Str,unsigned char  StringLength);
void  Delay(unsigned int Time);






