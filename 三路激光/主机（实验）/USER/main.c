#include "stm32f10x.h"
#include "MPU6050.h"
#include "OLED.h"
#include "bh.h"
#include "usart.h"
#define MYADDR 0x5d
u8 Illuminance_data[9];
extern float result_lx;
extern u8 BUF[2];

/************************************************
 ALIENTEK ??STM32F103?????0
 ????
 ??,???????????????main?? 
 ????:www.openedv.com
 ????:http://eboard.taobao.com 
 ???????????:"????",????STM32???
 ?????????????  
 ??:???? @ALIENTEK
************************************************/

u8 key;
 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
int main(void)
{	
	u8 t=0;
	u8 report=1;			//默认开启上报
	u8 ttt=11;
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	
	delay_init();	//延时初始化
	uart_init(9600);	
	delay_ms(1000);
	

	MyI2C_Init();
//	Start_BH1750();
	
	while(1)
	{
		t=MyI2C_Read_OOne_Byte(0x01);
		USART1->DR=t;
		delay_ms(1000);
		
//		Start_BH1750();
//		delay_ms(180);
//		
//		Read_BH1750();
//		USART1->DR=BUF[1];
//		delay_ms(50);
//		USART1->DR=BUF[0];
//		Convert_BH1750();
//		delay_ms(50);
//		USART1->DR=(char)result_lx;
//		delay_ms(1000);
	}

}	