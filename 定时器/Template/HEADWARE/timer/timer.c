#include "sys.h"
#include "timer.h"
#include "LED.h"
/*****************************
arr:自动重装值
psc:设置时钟频率除数的预分频
*****************************/
void TIMERX_Int_Init(u16 arr,u16 pas)
{
	TIM_TimeBaseInitTypeDef TIM_TimeStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//初始化TIMERX定时器
	TIM_TimeStructure.TIM_Period=arr;	//设置周期
	TIM_TimeStructure.TIM_Prescaler=pas;//设置预分频
	TIM_TimeStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置时间分割
	TIM_TimeStructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM向上计数
	TIM_TimeBaseInit(TIMERX,&TIM_TimeStructure);//初始化TIMERX
	
	TIM_ITConfig(TIMERX,TIM_IT_Update,ENABLE);//允许更新中断
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//先占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//从占优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC寄存器
	
	TIM_Cmd(TIMERX,ENABLE);
	
	
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIMERX,TIM_IT_Update)!=RESET){		//判断TIM3更新中断是否发生
		TIM_ClearITPendingBit(TIMERX,TIM_IT_Update); 		//清除TIM3中断标志
		LED1=!LED1;
	}
}

