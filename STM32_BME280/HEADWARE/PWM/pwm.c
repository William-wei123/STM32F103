#include "PWM.h"


void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//A8 B13
	//A9 B14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;      //CH2
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;   //GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //CH2N
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;  //GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); 
	
	
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//pwm1ģʽ	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState=TIM_OCPolarity_High;//������Ը�
 	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;//TIM_OCPolarity_Low;	 //������Ը�(������) 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//�	��������
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Set; //��MOE=0����TIM8����Ƚ�N����״̬ ��������
	TIM_OCInitStructure.TIM_Pulse	= 6000;//���ռ�ձ�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 	
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}
