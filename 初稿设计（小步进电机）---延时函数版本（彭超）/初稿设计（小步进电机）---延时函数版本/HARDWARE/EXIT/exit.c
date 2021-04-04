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

void flag_init()  //��־λ��ʼ��
{
  flag.automatic = 1;   //0:δ�����Զ�ģʽ     1:�����Զ�ģʽ

	flag.fall      = 0;   //0:��������״̬       1:����������״̬

	flag.raise     = 0;   //1:�������״̬       0:���������״̬   

  flag.exit9_5   = 0;   //0:
  
}

void EXITX_init()
{
  EXTI_InitTypeDef  EXTI_InitStructure;
  NVIC_InitTypeDef	NVIC_InitStructure;
	KEY_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //���� AFIO ʱ��	
  //��ˮ�������ж�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);  
  EXTI_InitStructure.EXTI_Line = EXTI_Line6 ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //�����ӿ����Ӹߵ�ƽʱ�������ش�������׼ȷEXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_Init(&EXTI_InitStructure);
	//�����������ж�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);  
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //�����ӿ����Ӹߵ�ƽʱ�������ش�������׼ȷEXTI_Trigger_Rising
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_Init(&EXTI_InitStructure);
	//����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ӿ����ӵ͵�ƽʱ���½��ش�����׼ȷ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ӿ����ӵ͵�ƽʱ���½��ش�����׼ȷ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ӿ����ӵ͵�ƽʱ���½��ش�����׼ȷ
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init(&EXTI_InitStructure);
	//�������ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd =  ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_Init(&NVIC_InitStructure);	
  //�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;     //
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStructure);	
	
	flag_init();
}
/*
void EXTI0_IRQHandler(void)    //KEY2 �����ж�
{
  delay_ms(20);
	if(KEY2==0)
	{
	 BEEP = ~BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
*/

void EXTI9_5_IRQHandler(void)    //KEY1�����ж�
{
  delay_ms(10);
	if(rain==0)      //��⵽��ˮ�������¼�
	{
		if(flag.automatic==1)
		{
		  if(flag.fall==1&&flag.raise==1)  //��ǰ�������״̬
		  {
	      motor_num(0,2);
        motor2_num(0,2);				
        flag.raise = 0;
        flag.fall  = 0;
				control_mp3(2,music_control);
        printf("�¼�����\r\n");
        printf("������%d\r\n",4*cs);
        cs = 0;			
      }		
		}
	}
	if(sun==0)
	{
		if(flag.automatic)
		{
		 if(flag.fall==1&&flag.raise==1)  //��ǰ�������״̬
		 {
	     motor_num(0,2);
       motor2_num(0,2);			 
       flag.raise = 0;
       flag.fall  = 0;
			 control_mp3(2,music_control);
       printf("�¼�����\r\n");
       printf("������%d\r\n",4*cs);
       cs = 0;			
     }	
	  }		 
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //���LINE0�ϵ��жϱ�־λ  
	EXTI_ClearITPendingBit(EXTI_Line7); //���LINE0�ϵ��жϱ�־λ 
}

		
void EXTI15_10_IRQHandler(void)    //KEY1�����ж�
{
  delay_ms(20);
	if(KEY1==0)           //���raise
	{
		if(flag.fall==0&&flag.raise==0)  //��ǰ��������״̬
		{
			 motor2_num(1,2);
	     motor_num(1,2);  		 	
       flag.raise = 1;
       flag.fall  = 1;
       control_mp3(1,music_control);			
       printf("�¼����\r\n");	
       printf("������%d\r\n",4*cs);
       cs = 0;					
    }		
    else
    {
			 control_mp3(3,music_control);
		   printf("�Բ��������¼ܵ�ǰ�Ѵ������״̬\r\n");
		}			
	}
	if(KEY2==0)           //����fall
	{
	  if(flag.fall==1&&flag.raise==1)  //��ǰ�������״̬
		{
	     motor_num(0,2); 
       motor2_num(0,2);			
       flag.raise = 0;
       flag.fall  = 0;
			 control_mp3(2,music_control);
       printf("�¼�����\r\n");
       printf("������%d\r\n",4*cs);
       cs = 0;			
    }		
    else
    {
			 control_mp3(4,music_control);
		   printf("�Բ��������¼ܵ�ǰ�Ѵ�������״̬\r\n");
		}		
	}
	if(KEY3==0)           //autoģʽ�л�
	{	
		mp3_cmd(5); 
		if(flag.automatic==0)
		{
	     flag.automatic = 1;
			 control_mp3(5,music_control);
			 printf("����������Զ�ģʽ����\r\n");	
		}   
		else
		{
			 flag.automatic = 0;
			 control_mp3(6,music_control);
			 printf("����������ֶ�ģʽ����\r\n");
		} 
	}
	EXTI_ClearITPendingBit(EXTI_Line13); //���LINE0�ϵ��жϱ�־λ 
	EXTI_ClearITPendingBit(EXTI_Line14); //���LINE0�ϵ��жϱ�־λ 
	EXTI_ClearITPendingBit(EXTI_Line15); //���LINE0�ϵ��жϱ�־λ 
}
