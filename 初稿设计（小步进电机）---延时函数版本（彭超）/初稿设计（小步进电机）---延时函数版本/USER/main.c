#include "led.h"
#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "uart.h"
#include "stm32f10x.h"
#include "exit.h"
#include "motor.h"
#include "adc.h"
#include "usart.h"	
#include "uart2.h"
#include "music.h"
//#include "oled.h"
//PB0  土壤湿度采用 ADC
//PB1  雨水采样   ADC
//PB6  DHT11 空气湿度温度  ONEWIRE
//PA9 PA10 UART蓝牙
//PA0 水泵继电器
//PA6 PA7 LED

//short p,r,y,temp; 
#define SYSCLK_FREQ_72MHz 72000000   //时钟配置为72MHZ

/*	 
short get_temperature(u8 channel)
{
	u32 adcx;
	short result;
 	double temperate;
	adcx = get_adcAverage(channel,20);//ADC_Channel_16
	temperate=(float)adcx*(3.3/4096);		//电压值 
	temperate=(1.43-temperate)/0.0043+25;	//转换为温度值 	 
	result=temperate*=100;					//扩大100倍.
	return result;
}
*/


int main(void)
{	
	short s,y; 
	SystemInit();  //时钟配置为72MHZ
	delay_init();	//延时初始化  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  EXITX_init();
//	TIMER_3_init(7199,1000);
	UART_1_init(38400);
	UART_2_init(9600);
	
	ADC1_init();
	motor_init();
	LED_Init();		  			//初始化与LED连接的硬件接口
// 	while(DHT11_Init())	//DHT11初始化	
//	{
//    LED0 = 0;    
//		delay_ms(200);
//	}
  mp3_cmd(5); //音量增大
	//control_mp3(0x00,volume_control);
	while(1)
	{
		s = get_adcAverage(ADC_Channel_8,10);
	  y = get_adcAverage(ADC_Channel_9,10);
		s = 100-s/41;
	  y = 100-y/41;
		printf("s:%d y:%d\r\n",s,y);
	//	LED0 = !LED0;
		delay_ms(1000);
	}
}
 
