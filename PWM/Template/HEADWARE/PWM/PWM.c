#include "PWM.h"
#include "LED.h"
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimerBaseStructuure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//设置GPIOA_8口为复用输出
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
	//设置TIM1
	TIM_TimerBaseStructuure.TIM_Period=arr;
	TIM_TimerBaseStructuure.TIM_Prescaler=psc;
	TIM_TimerBaseStructuure.TIM_ClockDivision=0;//设置时钟分频
	TIM_TimerBaseStructuure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM4,&TIM_TimerBaseStructuure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	//脉宽调制模式2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse=455;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性高
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);//初始化外设TIMx

	TIM_OC1Init(TIM4,&TIM_OCInitStructure);//初始化外设TIMx

	TIM_OC4Init(TIM4,&TIM_OCInitStructure);//初始化外设TIMx

	TIM_OC3Init(TIM4,&TIM_OCInitStructure);//初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM4,ENABLE);//MOE主输出使能

	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1预装载使能

	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1预装载使能

	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1预装载使能

	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);//CH1预装载使能

	TIM_ARRPreloadConfig(TIM4,ENABLE);//使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM4,ENABLE);//使能TIM1
	
}
