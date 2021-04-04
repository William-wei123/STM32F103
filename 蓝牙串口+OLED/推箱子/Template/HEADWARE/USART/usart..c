#include "usart..h"
#include "sys.h"
#include "LED.h"
//记得再main函数中初始化
/************

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2

*************/
u16  USART_RX_STA=0;  	//接受标识符

char USART_RX_BUF[USART_REC_LEN];

/****************************
初始化IO口，串口1
bound：波特率
*/



void usart1_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);//串口使能，GPIO使能，复用功能使能
	USART_DeInit(USART1);							//串口1复位
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART1_TX  PA.9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//复用推挽方式
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//初始化PA.9口
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;		//USART1_RX   PA.10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//初始化PA10口
	
	USART_InitStructure.USART_BaudRate=bound;		//波特率设置
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//字长为8BIT
	USART_InitStructure.USART_Parity=USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //收发模式
	USART_Init(USART1,&USART_InitStructure);			//初始化串口	
//	#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;		//??????buxiaode
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;	//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
//	#endif
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//开启中断
	USART_Cmd(USART1,ENABLE);							//使能串口
	
}
void USART1_IRQHandler(void)//串口一的中断服务程序
{
	u8 DATA;//用来储存单个数据
//	LED_Init();		  	 //初始化与LED连接的硬件接口 

	LED0=!LED0;//	/*判断出是否每传输一个字符进一次中断
	LED1=!LED1;//	*/
	DATA=USART_ReceiveData(USART1);
	if(DATA=='1'){
		LED1=!LED1;//用来检验是否收到字符‘1’
	}
	if(USART_RX_STA<1)
		USART_RX_BUF[USART_RX_STA++]=DATA;//把传回来的数放进数组USART_RX_BUF里头
	else USART_Cmd(USART1,DISABLE);
	
}

