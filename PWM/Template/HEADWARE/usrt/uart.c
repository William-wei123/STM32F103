#include "uart.h"
#include "sys.h"
#include "LED.h"
//�ǵ���main�����г�ʼ��
/************

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2

*************/
u16  USART_RX_STA=0;  	//���ܱ�ʶ��[USART_REC_LEN]

char USART_RX_BUF;

/****************************
��ʼ��IO�ڣ�����1
bound��������
*/



void usart3_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����ʹ�ܣ�GPIOʹ�ܣ����ù���ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_DeInit(USART3);							//����1��λ
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART1_TX  PA.9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�������췽ʽ
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA.9��
	//B10 B11
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;		//USART1_RX   PA.10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA10��
	
	USART_InitStructure.USART_BaudRate=bound;		//����������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//�ֳ�Ϊ8BIT
	USART_InitStructure.USART_Parity=USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART3,&USART_InitStructure);			//��ʼ������	
//	#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;		//??????buxiaode
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;	//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
//	#endif
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);		//�����ж�
	USART_Cmd(USART3,ENABLE);							//ʹ�ܴ���
}
void USART3_IRQHandler(void)//����һ���жϷ������
{
	u8 DATA;//�������浥������
	//LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 

	LED0=!LED0;//	/*�жϳ��Ƿ�ÿ����һ���ַ���һ���ж�*/
	LED1=!LED1;	
	DATA=USART_ReceiveData(USART3);
//	if(DATA==1)
//	{
//		LED1=!LED1;//���������Ƿ��յ��ַ���1��
//	}
//	if(USART_RX_STA<1)
		USART_RX_BUF=DATA;//�Ѵ����������Ž�����USART_RX_BUF��ͷ[USART_RX_STA++]
	//USART_Cmd(USART3,DISABLE);
}

