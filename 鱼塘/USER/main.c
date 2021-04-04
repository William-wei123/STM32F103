#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "i2c_soft.h"
#include "bme280_defs.h"
#include "bme280.h"
#include "bme280_application.h"
#include "deal.h"
#include "PWM.h"
#include "MyWIFI_.h"
#include "adc.h"
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


void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}
int main(void)
{	
	
	struct bme280_dev dev;
	int8_t rslt = BME280_OK;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(115200);		//串口1初始化，为WIFI
	usart2_init(9600);
	usart3_init(9600);
	
	TIM4_PWM_Init(3599,399);	//两个抽水电机
	TIM_SetCompare1(TIM4,800);
	TIM_SetCompare2(TIM4,900);
	TIM_SetCompare3(TIM4,7.5*36);
	I2c_Soft_Init();		//I2C
	Adc_Init();
	MyWIFI_Init();			//WIFI
	

	rslt = bme280_init(&dev);
	if(rslt == 0)
	{
		WIFI_Send_DATA("Init Success\r\n");
	}
	else
	{
		WIFI_Send_DATA("Init Fail,Please Check your address or the wire you connected!!!\r\n");
		while(1);
	}
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	
	TIM1_PWM_Init(9999,7199);	//定时发送数据，
	stream_sensor_data_normal_mode(&dev);
//	while(1)
//	{
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//		GPIO_SetBits(GPIOE,GPIO_Pin_5);
//		Delay(3000000);
//		GPIO_SetBits(GPIOB,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//		Delay(3000000);
//	}
}



