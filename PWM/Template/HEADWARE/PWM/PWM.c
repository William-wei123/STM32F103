#include "PWM.h"
#include "LED.h"
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimerBaseStructuure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//����GPIOA_8��Ϊ�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//����TIM1
	TIM_TimerBaseStructuure.TIM_Period=arr;
	TIM_TimerBaseStructuure.TIM_Prescaler=psc;
	TIM_TimerBaseStructuure.TIM_ClockDivision=0;//����ʱ�ӷ�Ƶ
	TIM_TimerBaseStructuure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM4,&TIM_TimerBaseStructuure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	//�������ģʽ2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=455;//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//������Ը�
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);//��ʼ������TIMx

	TIM_OC1Init(TIM4,&TIM_OCInitStructure);//��ʼ������TIMx

	TIM_OC4Init(TIM4,&TIM_OCInitStructure);//��ʼ������TIMx

	TIM_OC3Init(TIM4,&TIM_OCInitStructure);//��ʼ������TIMx

	TIM_CtrlPWMOutputs(TIM4,ENABLE);//MOE�����ʹ��

	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��

	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��

	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��

	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��

	TIM_ARRPreloadConfig(TIM4,ENABLE);//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM4,ENABLE);//ʹ��TIM1
	
}
