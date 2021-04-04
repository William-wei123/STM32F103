#include "exit.h"
#include "sys.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"

//外部中断初始化函数
void EXTIX_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;		//定义EXTI结构体
	NVIC_InitTypeDef NVIC_Initstructure;		//定义NVIC结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
	KEY_Init();//初始化按键对应IO口
	
	//GPIOC.1 中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;//中断线1
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//根据EXTI_InitStructure中所指定的参数初始化外设EXTI寄存器
	
	//GPIOC.13 中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;//中断线1
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//根据EXTI_InitStructure中所指定的参数初始化外设EXTI寄存器
	
	//GPIOA.0 中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;//中断线0
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//上升沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//根据EXTI_InitStructure中所指定的参数初始化外设EXTI寄存器
	
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI0_IRQn;//使能按键WE__Up所在的外部中断通道
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//抢占优先级2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//子优先级1；
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//使能外部中断
	
	NVIC_Init(&NVIC_Initstructure);//根据NVIC_InitStructure指定的参数设定NVIC寄存器
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//抢占优先级2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//子优先级1；
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//使能外部中断
	
	NVIC_Init(&NVIC_Initstructure);//根据NVIC_InitStructure指定的参数设定NVIC寄存器
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//抢占优先级2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//子优先级1；
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//使能外部中断
	
	NVIC_Init(&NVIC_Initstructure);//根据NVIC_InitStructure指定的参数设定NVIC寄存器	
}

void EXTI0_IRQHandler()//外部中断函数  STM32中只有六个     书本P166
{
	delay_ms(10);	//消抖
	if(WE_UP==1){
		LED0=!LED0;
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//清除LINE0线路挂起位
}

void EXTI1_IRQHandler()
{
	delay_ms(10);	//消抖
	if(KEY0==0){
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line1);//清除LiNE1上的中断标志位
	
}

void EXTI15_10_IRQHandler()
{
	delay_ms(10);	//消抖
	if(KEY1==0){
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13);//清除LINE13线路挂起位
	
}

