#include "motor.h"
#include "delay.h"
#include "exit.h"

void motor_init()
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);
	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
}


void motor_n(u8 delay)//电机逆转
{
  IN0_H;
	delay_ms(delay);
	delay_us(500);
	IN0_L; 
	
	IN1_H;
	delay_ms(delay);
	delay_us(500);
	IN1_L; 
	
	IN2_H;
	delay_ms(delay);
	delay_us(500);
	IN2_L; 

	IN3_H;
	delay_ms(delay);
	delay_us(500);
	IN3_L; 
	
	cs++;
}


void motor_z(u8 delay)//电机正转
{
  IN3_H;
	delay_ms(delay);
	delay_us(500);
	IN3_L; 
	
	IN2_H;
	delay_ms(delay);
	delay_us(500);
	IN2_L; 
	
	IN1_H;
	delay_ms(delay);
	delay_us(500);
	IN1_L; 
	
	IN0_H;
	delay_ms(delay);
	delay_us(500);
	IN0_L; 
	
	cs++;
}


void motor_num(u8 tab,u16 num)   //正反转180°的整数倍数
{
	u16 p,n;
	if(tab) 
	{		
		  for(p=0;p<256;p++)
	     for(n=0;n<num;n++)
	      motor_n(2); //正转一圈
	}
	else  
	{		
      for(p=0;p<256;p++)
	     for(n=0;n<num;n++)
	      motor_z(2);
	}
	delay_ms(100);
}

void motor_30_row(u8 tab,u16 row)   //row  30°的整数倍 
{
  u16 p,n;
	if(tab)
	{		
		  for(p=0;p<43;p++)
	     for(n=0;n<row;n++)
	      motor_z(3);         //正转一圈
	}
	else       
  {
	    for(p=0;p<43;p++)
	     for(n=0;n<row;n++)
	      motor_n(3);
	}
	delay_ms(100);
}

void motor_45_row(u8 tab,u16 row)   //row  45°的整数倍 
{
  u16 p,n;
	if(tab) 
	{		
		  for(p=0;p<64;p++)
	     for(n=0;n<row;n++)
	      motor_z(3);         //正转一圈
	}
	else       
  {
	    for(p=0;p<64;p++)
	     for(n=0;n<row;n++)
	      motor_n(3);
	}
	delay_ms(100);
}



void motor2_n(u8 delay)//2号电机逆转
{
  IN5_H;
	delay_ms(delay);
	delay_us(500);
	IN5_L; 
	
	IN6_H;
	delay_ms(delay);
	delay_us(500);
	IN6_L; 
	
	IN7_H;
	delay_ms(delay);
	delay_us(500);
	IN7_L; 

	IN8_H;
	delay_ms(delay);
	delay_us(500);
	IN8_L; 
	
	cs++;
}


void motor2_z(u8 delay)//2号电机正转
{
  IN8_H;
	delay_ms(delay);
	delay_us(500);
	IN8_L; 
	
	IN7_H;
	delay_ms(delay);
	delay_us(500);
	IN7_L; 
	
	IN6_H;
	delay_ms(delay);
	delay_us(500);
	IN6_L; 
	
	IN5_H;
	delay_ms(delay);
	delay_us(500);
	IN5_L; 
	
	cs++;
}


void motor2_num(u8 tab,u16 num)   //正反转180°的整数倍数
{
	u16 p,n;
	if(tab) 
	{		
		  for(p=0;p<256;p++)
	     for(n=0;n<num;n++)
	      motor2_n(2); //正转一圈
	}
	else  
	{		
      for(p=0;p<256;p++)
	     for(n=0;n<num;n++)
	      motor2_z(2);
	}
	delay_ms(100);
}

void motor2_30_row(u8 tab,u16 row)   //row  30°的整数倍 
{
  u16 p,n;
	if(tab)
	{		
		  for(p=0;p<43;p++)
	     for(n=0;n<row;n++)
	      motor2_z(3);         //正转一圈
	}
	else       
  {
	    for(p=0;p<43;p++)
	     for(n=0;n<row;n++)
	      motor2_n(3);
	}
	delay_ms(100);
}

void motor2_45_row(u8 tab,u16 row)   //row  45°的整数倍 
{
  u16 p,n;
	if(tab) 
	{		
		  for(p=0;p<64;p++)
	     for(n=0;n<row;n++)
	      motor2_z(3);         //正转一圈
	}
	else       
  {
	    for(p=0;p<64;p++)
	     for(n=0;n<row;n++)
	      motor2_n(3);
	}
	delay_ms(100);
}
