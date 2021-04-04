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
//PB0  ����ʪ�Ȳ��� ADC
//PB1  ��ˮ����   ADC
//PB6  DHT11 ����ʪ���¶�  ONEWIRE
//PA9 PA10 UART����
//PA0 ˮ�ü̵���
//PA6 PA7 LED

//short p,r,y,temp; 
#define SYSCLK_FREQ_72MHz 72000000   //ʱ������Ϊ72MHZ

/*	 
short get_temperature(u8 channel)
{
	u32 adcx;
	short result;
 	double temperate;
	adcx = get_adcAverage(channel,20);//ADC_Channel_16
	temperate=(float)adcx*(3.3/4096);		//��ѹֵ 
	temperate=(1.43-temperate)/0.0043+25;	//ת��Ϊ�¶�ֵ 	 
	result=temperate*=100;					//����100��.
	return result;
}
*/


int main(void)
{	
	short s,y; 
	SystemInit();  //ʱ������Ϊ72MHZ
	delay_init();	//��ʱ��ʼ��  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  EXITX_init();
//	TIMER_3_init(7199,1000);
	UART_1_init(38400);
	UART_2_init(9600);
	
	ADC1_init();
	motor_init();
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
// 	while(DHT11_Init())	//DHT11��ʼ��	
//	{
//    LED0 = 0;    
//		delay_ms(200);
//	}
  mp3_cmd(5); //��������
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
 
