#include "PWM.h"
#include "MyWIFI_.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
//	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	NVIC_InitTypeDef NVIC_Init_Structure;	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

//   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	 //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM_CH1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	//A8 B13
//	//A9 B14
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;      //CH2
//	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;   //GPIO_Mode_Out_PP;   
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //CH2N
//	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;  //GPIO_Mode_Out_PP;   
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	
	NVIC_Init_Structure.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init_Structure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_Init_Structure);
	
// 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//pwm1ģʽ	
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OutputNState=TIM_OCPolarity_High;//������Ը�
// 	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;//TIM_OCPolarity_Low;	 //������Ը�(������) 
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//�	��������
//	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Set; //��MOE=0����TIM8����Ƚ�N����״̬ ��������
//	TIM_OCInitStructure.TIM_Pulse	= 6000;//���ռ�ձ�
//	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 	
//	
//	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 

//	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
//	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	
//	
//	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimerBaseStructuure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
	//����GPIOA_8��Ϊ�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//ʹ�ܶ�PC8��PC9��PC10��PC11��PC12��PC13
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_4);
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);

	//����TIM1
	TIM_TimerBaseStructuure.TIM_Period=arr;
	TIM_TimerBaseStructuure.TIM_Prescaler=psc;
	TIM_TimerBaseStructuure.TIM_ClockDivision=0;//����ʱ�ӷ�Ƶ
	TIM_TimerBaseStructuure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM4,&TIM_TimerBaseStructuure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	//�������ģʽ2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=0;//���ô�װ�벶��ȽϼĴ���������ֵ
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
int Time1_Num=0;
int Timel_NUM2=0;
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 		//���TIM3�жϱ�־
		Time1_Num++;
		Timel_NUM2++;
	}
	
	if(Time1_Num>=3){
		DATA_Integration();
		Time1_Num=0;
	}
	if(Timel_NUM2>30000)
		Timel_NUM2=0;
}
