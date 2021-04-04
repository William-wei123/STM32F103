#include "bh.h"
#include "I2C.h"
#include "delay.h"
#include "stdio.h"

float result_lx=0;

u8 BUF[2]={0};
u16 result=0;

//初始化
void BH1750_Init(void)
{
	  MyI2C_Init();
}

void Cmd_Write_BH1750(u8 cmd)
{
    MyI2C_Star();                    //IIC起始信号
	
    MyI2C_Write_Byte(BH1750_Addr+0);   //发送设备地址+写信号
//	  while(MyI2C_Wait_Ack());
	
    MyI2C_Write_Byte(cmd);             //内部寄存器地址
//	  while(MyI2C_Wait_Ack());
	
    MyI2C_Stop();                     //发送停止信号
	  delay_ms(5);
}
void Start_BH1750(void)
{
	  Cmd_Write_BH1750(BH1750_ON);	  //power on
	  Cmd_Write_BH1750(BH1750_RSET);	//重置
	  Cmd_Write_BH1750(BH1750_ONE);   //一次H分辨率模式，至少120ms，之后进入断电模式    
}
void Read_BH1750(void)
{   	
    MyI2C_Star();                          //IIC起始信号
    MyI2C_Write_Byte(BH1750_Addr+1);         //发送设备地址+读信号
//	  while(MyI2C_Wait_Ack());
	  BUF[0]=MyI2C_read_Byte(0);              //发送ACK
	  BUF[1]=MyI2C_read_Byte(1);              //发送NACK
 
    MyI2C_Stop();                           //IIC停止信号
    delay_ms(5);
}
void Convert_BH1750(void)
{
	
	  result=BUF[0];
	  result=(result<<8)+BUF[1];  //合成光照强度
	
	  result_lx=(float)result/1.2;
	
	  //printf("illuminance:%.1f lx",result_lx);		
}


//void conversion(u16 temp_data)  //  数据转换出 个，十，百，千，万
//{  
//	u8   ge,shi,bai,qian,wan;
//    wan=temp_data/10000+0x30 ;
//    temp_data=temp_data%10000;   //取余运算
//	qian=temp_data/1000+0x30 ;
//    temp_data=temp_data%1000;    //取余运算
//    bai=temp_data/100+0x30   ;
//    temp_data=temp_data%100;     //取余运算
//    shi=temp_data/10+0x30    ;
//    temp_data=temp_data%10;      //取余运算
//    ge=temp_data+0x30; 	
//}



