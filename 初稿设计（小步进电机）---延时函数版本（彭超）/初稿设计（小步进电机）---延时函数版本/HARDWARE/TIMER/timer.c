#include "sys.h"
#include "timer.h"
#include "led.h"

void TIMER_3_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef	  NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //���� AFIO ʱ��
	//��ʱ����������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�
	
	//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X02;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,DISABLE);  //��ʱ��3ʹ��
		
}

//�жϷ�����
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static u8 k = 0;
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)  //�жϸ���
	{
		if(k==50)
		{
		 TIM_Cmd(TIM3,DISABLE);  //��ʱ��3ʹ��
		}
		k++;
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);
	}
}




