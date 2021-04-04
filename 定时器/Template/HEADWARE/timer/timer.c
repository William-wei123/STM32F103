#include "sys.h"
#include "timer.h"
#include "LED.h"
/*****************************
arr:�Զ���װֵ
psc:����ʱ��Ƶ�ʳ�����Ԥ��Ƶ
*****************************/
void TIMERX_Int_Init(u16 arr,u16 pas)
{
	TIM_TimeBaseInitTypeDef TIM_TimeStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//��ʼ��TIMERX��ʱ��
	TIM_TimeStructure.TIM_Period=arr;	//��������
	TIM_TimeStructure.TIM_Prescaler=pas;//����Ԥ��Ƶ
	TIM_TimeStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ��ָ�
	TIM_TimeStructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM���ϼ���
	TIM_TimeBaseInit(TIMERX,&TIM_TimeStructure);//��ʼ��TIMERX
	
	TIM_ITConfig(TIMERX,TIM_IT_Update,ENABLE);//��������ж�
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIMERX,ENABLE);
	
	
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIMERX,TIM_IT_Update)!=RESET){		//�ж�TIM3�����ж��Ƿ���
		TIM_ClearITPendingBit(TIMERX,TIM_IT_Update); 		//���TIM3�жϱ�־
		LED1=!LED1;
	}
}

