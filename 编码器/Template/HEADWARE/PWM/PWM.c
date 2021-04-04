#include "PWM.h"
//#include "LED.h"
void TIM1_PWM_Init(u16 arr,u16 psc)//arr+1��psc+1   ��(arr+1)/72MhzΪһ�����ڣ�Ȼ��ռ�ձ�Ϊled0pwmval/��arr+1��Ƶ��Ϊ80KHz
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimerBaseStructuure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//����GPIOA_8��Ϊ�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//����TIM1
	TIM_TimerBaseStructuure.TIM_Period=arr;
	TIM_TimerBaseStructuure.TIM_Prescaler=psc;
	TIM_TimerBaseStructuure.TIM_ClockDivision=0;//����ʱ�ӷ�Ƶ
	TIM_TimerBaseStructuure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM1,&TIM_TimerBaseStructuure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;	//�������ģʽ2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=0;//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//������Ը�
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//��ʼ������TIMx
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//MOE�����ʹ��
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1,ENABLE);//ʹ��TIM1
	
}
