#include "sys.h"
#include "exit.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "motor.h"
#include "delay.h"
#include "music.h"
FLAG flag;

u16 cs = 0;

void flag_init()  //标志位初始化
{
  flag.automatic = 1;   //0:未开启自动模式     1:开启自动模式

	flag.fall      = 0;   //0:处于收缩状态       1:不处于收缩状态

	flag.raise     = 0;   //1:处于伸出状态       0:不处于伸出状态   

  flag.exit9_5   = 0;   //0:
  
}

void EXITX_init()
{
  EXTI_InitTypeDef  EXTI_InitStructure;
  NVIC_InitTypeDef	NVIC_InitStructure;
	KEY_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //开启 AFIO 时钟	
  //雨水传感器中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);  
  EXTI_InitStructure.EXTI_Line = EXTI_Line6 ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //按键接口连接高电平时，上升沿触发更加准确EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_Init(&EXTI_InitStructure);
	//光敏传感器中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);  
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //按键接口连接高电平时，上升沿触发更加准确EXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_Init(&EXTI_InitStructure);
	//按键
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //按键接口连接低电平时，下降沿触发更准确
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //按键接口连接低电平时，下降沿触发更准确
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //按键接口连接低电平时，下降沿触发更准确
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	//传感器中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd =  ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_Init(&NVIC_InitStructure);	
  //按键中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;     //
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStructure);	
	
	flag_init();
}
/*
void EXTI0_IRQHandler(void)    //KEY2 触发中断
{
  delay_ms(20);
	if(KEY2==0)
	{
	 BEEP = ~BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
*/

void EXTI9_5_IRQHandler(void)    //KEY1触发中断
{
  delay_ms(10);
	if(rain==0)      //监测到雨水，收缩衣架
	{
		if(flag.automatic==1)
		{
		  if(flag.fall==1&&flag.raise==1)  //当前处于伸出状态
		  {
	      motor_num(0,2);
        motor2_num(0,2);				
        flag.raise = 0;
        flag.fall  = 0;
				control_mp3(2,music_control);
        printf("衣架缩回\r\n");
        printf("步数：%d\r\n",4*cs);
        cs = 0;			
      }		
		}
	}
	if(sun==0)
	{
		if(flag.automatic)
		{
		 if(flag.fall==1&&flag.raise==1)  //当前处于伸出状态
		 {
	     motor_num(0,2);
       motor2_num(0,2);			 
       flag.raise = 0;
       flag.fall  = 0;
			 control_mp3(2,music_control);
       printf("衣架缩回\r\n");
       printf("步数：%d\r\n",4*cs);
       cs = 0;			
     }	
	  }		 
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE0上的中断标志位 
}

		
void EXTI15_10_IRQHandler(void)    //KEY1触发中断
{
  delay_ms(20);
	if(KEY1==0)           //伸出raise
	{
		if(flag.fall==0&&flag.raise==0)  //当前处于缩回状态
		{
			 motor2_num(1,2);
	     motor_num(1,2);  		 	
       flag.raise = 1;
       flag.fall  = 1;
       control_mp3(1,music_control);			
       printf("衣架伸出\r\n");	
       printf("步数：%d\r\n",4*cs);
       cs = 0;					
    }		
    else
    {
			 control_mp3(3,music_control);
		   printf("对不起，您的衣架当前已处于伸出状态\r\n");
		}			
	}
	if(KEY2==0)           //缩回fall
	{
	  if(flag.fall==1&&flag.raise==1)  //当前处于伸出状态
		{
	     motor_num(0,2); 
       motor2_num(0,2);			
       flag.raise = 0;
       flag.fall  = 0;
			 control_mp3(2,music_control);
       printf("衣架缩回\r\n");
       printf("步数：%d\r\n",4*cs);
       cs = 0;			
    }		
    else
    {
			 control_mp3(4,music_control);
		   printf("对不起，您的衣架当前已处于缩回状态\r\n");
		}		
	}
	if(KEY3==0)           //auto模式切换
	{	
		mp3_cmd(5); 
		if(flag.automatic==0)
		{
	     flag.automatic = 1;
			 control_mp3(5,music_control);
			 printf("传感器检测自动模式开启\r\n");	
		}   
		else
		{
			 flag.automatic = 0;
			 control_mp3(6,music_control);
			 printf("传感器检测手动模式开启\r\n");
		} 
	}
	EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE0上的中断标志位 
	EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE0上的中断标志位 
	EXTI_ClearITPendingBit(EXTI_Line15); //清除LINE0上的中断标志位 
}
