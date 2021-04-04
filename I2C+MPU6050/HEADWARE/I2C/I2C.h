#ifndef I2C__H__
#define I2C__H__
#include "sys.h"

#define IIC_SDA    PCout(15) 		//SDA
#define IIC_SCL    PCout(14)			//SCL
#define READ_SDA   PCin(15) 	 		//输入SDA 

#define SDA_IN()  {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=(u32)8<<28;}	//设为输入模式
#define SDA_OUT() {GPIOC->CRH&=0X0FFFFFFF;GPIOC ->CRH|=(u32)3<<28;}	//设为输出模式
void MyI2C_Init(void);
u8 MyI2C_Write_Byte(u8 txd);
u8 MyI2C_read_Byte(unsigned char ack);

void MyI2C_Star(void);
void MyI2C_Stop(void);

void MyI2C_Ack(u8 AC);//0为有效应答
u8 MyI2C_Wait_Ack(void);
//void MyI2C_Send_Byte(u8 txd);

u8 MyI2C_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MyI2C_Read_One_Byte(u8 daddr,u8 addr);	  

#endif
