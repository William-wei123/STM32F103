#include "exit.h"
#include "sys.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"

//�ⲿ�жϳ�ʼ������
void EXTIX_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;		//����EXTI�ṹ��
	NVIC_InitTypeDef NVIC_Initstructure;		//����NVIC�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	KEY_Init();//��ʼ��������ӦIO��
	
	//GPIOC.1 �ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;//�ж���1
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//����EXTI_InitStructure����ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	//GPIOC.13 �ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;//�ж���1
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//����EXTI_InitStructure����ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	//GPIOA.0 �ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;//�ж���0
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//�����ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//����EXTI_InitStructure����ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI0_IRQn;//ʹ�ܰ���WE__Up���ڵ��ⲿ�ж�ͨ��
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//�����ȼ�1��
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�
	
	NVIC_Init(&NVIC_Initstructure);//����NVIC_InitStructureָ���Ĳ����趨NVIC�Ĵ���
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//�����ȼ�1��
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�
	
	NVIC_Init(&NVIC_Initstructure);//����NVIC_InitStructureָ���Ĳ����趨NVIC�Ĵ���
	
	NVIC_Initstructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0x02;//��ռ���ȼ�2
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0x01;//�����ȼ�1��
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�
	
	NVIC_Init(&NVIC_Initstructure);//����NVIC_InitStructureָ���Ĳ����趨NVIC�Ĵ���	
}

void EXTI0_IRQHandler()//�ⲿ�жϺ���  STM32��ֻ������     �鱾P166
{
	delay_ms(10);	//����
	if(WE_UP==1){
		LED0=!LED0;
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//���LINE0��·����λ
}

void EXTI1_IRQHandler()
{
	delay_ms(10);	//����
	if(KEY0==0){
		LED0=!LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line1);//���LiNE1�ϵ��жϱ�־λ
	
}

void EXTI15_10_IRQHandler()
{
	delay_ms(10);	//����
	if(KEY1==0){
		LED1=!LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13);//���LINE13��·����λ
	
}

