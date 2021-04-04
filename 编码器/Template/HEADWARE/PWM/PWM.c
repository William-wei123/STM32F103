#include "PWM.h"
//#include "LED.h"
void TIM1_PWM_Init(u16 arr,u16 psc)//arr+1，psc+1   即(arr+1)/72Mhz为一个周期，然后占空比为led0pwmval/（arr+1）频率为80KHz
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimerBaseStructuure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//设置GPIOA_8口为复用输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//设置TIM1
	TIM_TimerBaseStructuure.TIM_Period=arr;
	TIM_TimerBaseStructuure.TIM_Prescaler=psc;
	TIM_TimerBaseStructuure.TIM_ClockDivision=0;//设置时钟分频
	TIM_TimerBaseStructuure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM1,&TIM_TimerBaseStructuure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;	//脉宽调制模式2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse=0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性高
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//初始化外设TIMx
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//MOE主输出使能
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//CH1预装载使能
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1,ENABLE);//使能TIM1
	
}
