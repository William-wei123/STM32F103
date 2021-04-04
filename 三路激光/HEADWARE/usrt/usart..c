#include "ALL_init.h"
//#include "LED.h"
//�ǵ���main�����г�ʼ��
/************

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2

*************/
float HIGHT_CTRL_OUTPUT_[5];
float PITCH_CTRL_OUTPUT_[5];
float ROLL_CTRL_OUTPUT_[5];

extern u8 FLAG_Remap;
u16  USART_RX_STA=0;  	//���ܱ�ʶ��

u8 USART_RX_BUF[USART_REC_LEN];
//u8 _DIST_[9]={0x59,0x59};//����״����������
int dist;//�״�ʵ�����ֵ
int strength;//�״��ź�ǿ��
int check;//У����ֵ���
u8 FLY_CMD;
/****************************
��ʼ��IO�ڣ�����1
bound��������
*/


DATA_array XIA;

DATA_array QIAN;

DATA_array ZUO;


void uart1_init(u32 bound1)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//����ʹ�ܣ�GPIOʹ�ܣ����ù���ʹ��
	USART_DeInit(USART1);							//����1��λ
	//����ӳ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART1_TX  PA.9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�������췽ʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//��ʼ��PA.9��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;		//USART1_RX   PA.10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//��ʼ��PA10��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART1_TX  PB.6
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�������췽ʽ
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA.9��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;		//USART1_RX   PB.7
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA10��

	
	USART_InitStructure.USART_BaudRate=bound1;		//����������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//�ֳ�Ϊ8BIT
	USART_InitStructure.USART_Parity=USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART1,&USART_InitStructure);			//��ʼ������	
//	#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;		//??????buxiaode
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
//	#endif
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//�����ж�
	USART_Cmd(USART1,ENABLE);							//ʹ�ܴ���
	XIA.Flag_Start=0;
	XIA.method=&Ultra_Get;

}
u16 panduan(u8 _DIST_[9])
{
	if(_DIST_[0]==HEADER)
		if(_DIST_[1]==HEADER){
			check=_DIST_[0]+_DIST_[1]+_DIST_[2]+_DIST_[3]+_DIST_[4]+_DIST_[5]+_DIST_[6]+_DIST_[7];
			if(_DIST_[8]==(check&0xff)){
				dist=_DIST_[2]+_DIST_[3]*256;//�������ֵ
				strength=_DIST_[4]+_DIST_[5]*256;//�����ź�ǿ��ֵ
				
			}//����Э����յ������ݽ���У��
				
		}
		return dist;
}

// Byte0   Byte1   Byte2   Byte3   Byte4   Byte5   Byte6   Byte7   Byte8
// 0x59    0x59    Dist_L  Dist_H  Str_L   Str_H   Mode    0x00    CheckSum
//�����·����루��ӳ��FLAG_Remap=1���ͷɿ����ݣ�����ӳ��FLAG_Remap=0��
void USART1_IRQHandler(void)//����һ���жϷ������
{
	u8 DATA;//�������浥������
	u8 SP_;
	u8 ACCEPT_ok_f=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){ 
		DATA=USART_ReceiveData(USART1);
		if(FLAG_Remap==0){				//���շɿ�����
			
			ACCEPT_ok_f=_ACCEPT_DATA_BY_FLY(DATA);
//				USART1->DR=DATA;			//����ͷ
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			
			if(data_save_flag==1){			//�����������
				USART1->DR=0x5A;			//����ͷ
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���

				for(SP_=0;SP_<5;SP_++){
					USART1->DR=XIA.DATA_TO_FLY[SP_];		//�������ݸ��ɿ�
					while((USART1->SR&0X40)==0);//�ȴ����ͽ���
				}
				data_save_flag=0;
				FLAG_Remap++;				//�ı䴮�ڹ�����ʽ����ʼ���ռ�������
				
			}
//			else if(ACCEPT_ok_f==59){							//������ݽ���ʧ�ܣ����͡�ero��,���ȴ��ٴ�����
//				USART1->DR='e';
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//				USART1->DR='r';
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//				USART1->DR='o';
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//				FLAG_Remap=0;
//			}
			
		}else {
			LASER_ACCEPT_DATA(DATA,&XIA);
			LASER_DATA_HANDLE(ultra_start_f,&XIA,XIA.method);

		}
	}
}
	
//	USART_RX_BUF[USART_RX_STA++]=DATA;//�Ѵ����������Ž�����USART_RX_BUF��ͷ
	
	


void uart2_init(u32 bound2)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����ʹ�ܣ�GPIOʹ�ܣ����ù���ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2);							//����1��λ
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART2_TX  PA.2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�������췽ʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//��ʼ��PA.9��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;		//USART2_RX   PA.30
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//��ʼ��PA10��
	
	USART_InitStructure.USART_BaudRate=bound2;		//����������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//�ֳ�Ϊ8BIT
	USART_InitStructure.USART_Parity=USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART2,&USART_InitStructure);			//��ʼ������	
//	#if EN_USART2_RX
//	USART2->BRR=0x00000271;
//	USART2->CR2=0x00002000;
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;		//??????buxiaode
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
//	#endif
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);		//�����ж�
	USART_Cmd(USART2,ENABLE);							//ʹ�ܴ���
	ZUO.Flag_Start=0;
}
void USART2_IRQHandler(void)//����һ���жϷ������
{
	u8 DATA;//�������浥������
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){ 
		DATA=USART_ReceiveData(USART2);
		LASER_ACCEPT_DATA(DATA,&ZUO);
//		if(ZUO.Flag_Start==0&&i==0){
//			if(DATA==HEADER){
//				ZUO.Array_[i]=DATA;
//				ZUO.Flag_Start=1;
//				i++;
//			}
//		}else if(ZUO.Flag_Start==1&&i==1&&DATA==HEADER){
//			ZUO.Array_[i]=DATA;
//			i++;
//		}else if(ZUO.Flag_Start==1){
//			ZUO.Array_[i]=DATA;
//			i++;
//		}
//		
//		if(i==9){
//			i=0;
//			ZUO.Flag_Start=0;
//			ZUO.Average_DATA = panduan(ZUO.Array_);

//		}
	}	
}

void uart3_init(u32 bound3)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����ʹ�ܣ�GPIOʹ�ܣ����ù���ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_DeInit(USART3);							//����1��λ
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//USART3_TX  PB.10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�������췽ʽ
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA.9��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;		//USART3_RX   PB.11
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//��ʼ��PA10��
	
	USART_InitStructure.USART_BaudRate=115200;		//����������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//�ֳ�Ϊ8BIT
	USART_InitStructure.USART_Parity=USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART3,&USART_InitStructure);			//��ʼ������	
//	#if EN_USART1_RX
//	USART3->BRR=0x00000271;
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;		//??????buxiaode
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;	//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
//	#endif
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);		//�����ж�
	USART_Cmd(USART3,ENABLE);							//ʹ�ܴ���
	QIAN.Flag_Start=0;
}
void USART3_IRQHandler(void)//����һ���жϷ������
{
	u8 DATA;//�������浥������
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){ 
		DATA=USART_ReceiveData(USART3);
		LASER_ACCEPT_DATA(DATA,&ZUO);
//		if(QIAN.Flag_Start==0&&i==0){
//			if(DATA==HEADER){
//				QIAN.Array_[i]=DATA;
//				QIAN.Flag_Start=1;
//				i++;
//				
//			}
//		}else if(QIAN.Flag_Start==1&&i==1&&DATA==HEADER){
//			QIAN.Array_[i]=DATA;
//			i++;
//		}else if(QIAN.Flag_Start==1){
//			QIAN.Array_[i]=DATA;
//			i++;
//		}
//		
//		if(i==9){
//			i=0;
//			QIAN.Flag_Start=0;
//			QIAN.Average_DATA = panduan(QIAN.Array_);
////			USART_SendData(USART3,QIAN.Average_DATA);

//		}
	}		
}

