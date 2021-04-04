#include "lora.h"
#include "delay.h"

 short s,y; 
 u8 temperature;  	    
 u8 humidity;
/*   ���ն�ʹ��
short ReceiveData_FORM_LORA[4];
char LORA[8];
char a,b,c,d,e,f,g,h;
*/
//���Ͷ�ʹ��
char lora_sendtable[6];    //high1  high2   low1 low2

u8 jyw_table[2]={'a','b'};

	

char short_to_char_low(short sh)
{
	char low; 
  low = sh & 0xff;
  return low;	
}

char short_to_char_high(short sh)
{
	char high; 
  high = (sh >> 8) & 0xff; //
  return high;	
}



//UART_1_init(38400);
void Lora_Init(u32 bat)//��ʼ��
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	//��ͨģʽ��   M0:0   M1:0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
  GPIO_ResetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);						 //PB.5 �����
/*	 AUX��Ҫ����Ϊ�����ж�����  PB13
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PB.5 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
  GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.5 �����
	*/
  UART_1_init(bat);
}

void Lora_data_change()
{
  s = get_adcAverage(ADC_Channel_8,10);
	y = get_adcAverage(ADC_Channel_9,10);
  DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
	
	lora_sendtable[0]  =  short_to_char_high(s);
	lora_sendtable[1]  =  short_to_char_low(s);
	
	lora_sendtable[2]  =  short_to_char_high(y);
	lora_sendtable[3]  =  short_to_char_low(y);	
	
	lora_sendtable[4]  =  temperature;
	lora_sendtable[5]  =  humidity;
}


void Lora_data_send()  //����8λ����   ��һλ�����һλ��У��λ
{
	u8 i = 0;
	Lora_data_change();
  USART_SendData(USART1,jyw_table[0]);
  delay_ms(2);
	for(i=0;i<6;i++)   //6λ����
	{
	 USART_SendData(USART1,lora_sendtable[i]);
	 delay_ms(2);
	}
  USART_SendData(USART1,jyw_table[1]);		  	
}




/*  ���ն�ʹ��  �������ݰ�        ����
void USART1_IRQHandler(void)   //USART1�ж�
{   
  static u8 res=0;
	static u8  recdata;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) //
	{
	  USART_ClearFlag(USART1, USART_IT_RXNE); 
		
		if(recdata=='a')  //ͨ��У��λ
		{
	   LORA[res-1]  = USART_ReceiveData(USART1);		 
		}	  
		if(res==0)  //����λ�ж�
		{
     recdata = USART_ReceiveData(USART1);
		}   		
	  res++;
    if(res>=9) 
	    {
			  res=0;
        recdata=0;			
		  }		
	}
}

//��������   
void Read_MPU6050_DATA()
{	
    a = LORA[0];
    b = LORA[1]; 
    ReceiveData_FORM_LORA[0] = (short)(a<<8)|b;
    c = LORA[2];
    d = LORA[3]; 
    ReceiveData_FORM_LORA[1] = (short)(c<<8)|d;
		e = LORA[4];
    f = LORA[5]; 
    ReceiveData_FORM_LORA[2] = (short)(e<<8)|f;
		g = LORA[6];
    h = LORA[7]; 
    ReceiveData_FORM_LORA[3] = (short)(g<<8)|h;
}
*/