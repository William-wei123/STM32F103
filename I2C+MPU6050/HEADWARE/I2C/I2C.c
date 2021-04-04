#include "I2C.h"
#include "delay.h"
void MyI2C_Init(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//禁止JTAG,从而PA15可以做普通IO使用,否则PA15不能做普通IO!!!
	RCC->APB2ENR|=1<<4;//使能GPIOA口，具体去看32技术手册6.3
	GPIOC->CRH&=0X00FFFFFF;	//PA14 15 推挽输出		具体去看32技术手册8.2
	GPIOC->CRH|=0X33000000;	   
	GPIOC->ODR|=3<<14;     	//P 输出高		具体去看32技术手册8.2.4

}

void MyI2C_Star(void)
{
	SDA_OUT();		//SDA输出
	IIC_SCL=1;
	IIC_SDA=1;
	delay_us(5);
	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}

void MyI2C_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 MyI2C_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)//低电平为有效应答
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MyI2C_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 ，//可继续发送数据	   
	return 0;  
} 

//产生ACK应答
void MyI2C_Ack(u8 AC)//0为有效应答
{
	IIC_SCL=0;
	SDA_OUT();//设为输出模式
	IIC_SDA=AC;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
u8 MyI2C_Write_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }
	return MyI2C_Wait_Ack();	//等待应答
} 

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 MyI2C_read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    MyI2C_Ack(ack);
    return receive;

}

u8 MyI2C_Write_One_Byte(u8 daddr,u8 addr,u8 data)
{
	u8 temp,m;
	MyI2C_Star();
	m=MyI2C_Write_Byte((daddr<<1)|0);//外设地址+写命令
	MyI2C_Write_Byte(addr);//数据地址
	temp=MyI2C_Write_Byte(data);//数据发送
	
	MyI2C_Stop();
	delay_ms(10);	 				//EEPROM的写入速度比较慢，加入延迟  //可加可不加？
	return temp ;
}
u8 MyI2C_Read_One_Byte(u8 daddr,u8 addr)
{
	u8 k,temp=0;		  	    																 
	MyI2C_Star();
	MyI2C_Write_Byte((daddr<<1)|0);//外设地址+写命令
	k=MyI2C_Write_Byte(addr);//数据地址
	MyI2C_Star();
	MyI2C_Write_Byte((daddr<<1)|1);//外设地址+读命令//需改
	temp=MyI2C_read_Byte(1);
	delay_ms(10);	 				//EEPROM的写入速度比较慢，加入延迟  //可加可不加？
	MyI2C_Stop();
	return temp;

}

