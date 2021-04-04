#include "lora.h"
#include "delay.h"

 short s,y; 
 u8 temperature;  	    
 u8 humidity;
/*   接收端使用
short ReceiveData_FORM_LORA[4];
char LORA[8];
char a,b,c,d,e,f,g,h;
*/
//发送端使用
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
void Lora_Init(u32 bat)//初始化
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	//普通模式下   M0:0   M1:0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
  GPIO_ResetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);						 //PB.5 输出高
/*	 AUX需要配置为输入中断引脚  PB13
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
  GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.5 输出高
	*/
  UART_1_init(bat);
}

void Lora_data_change()
{
  s = get_adcAverage(ADC_Channel_8,10);
	y = get_adcAverage(ADC_Channel_9,10);
  DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
	
	lora_sendtable[0]  =  short_to_char_high(s);
	lora_sendtable[1]  =  short_to_char_low(s);
	
	lora_sendtable[2]  =  short_to_char_high(y);
	lora_sendtable[3]  =  short_to_char_low(y);	
	
	lora_sendtable[4]  =  temperature;
	lora_sendtable[5]  =  humidity;
}


void Lora_data_send()  //发送8位数据   第一位和最后一位是校验位
{
	u8 i = 0;
	Lora_data_change();
  USART_SendData(USART1,jyw_table[0]);
  delay_ms(2);
	for(i=0;i<6;i++)   //6位数据
	{
	 USART_SendData(USART1,lora_sendtable[i]);
	 delay_ms(2);
	}
  USART_SendData(USART1,jyw_table[1]);		  	
}




/*  接收端使用  解析数据包        样版
void USART1_IRQHandler(void)   //USART1中断
{   
  static u8 res=0;
	static u8  recdata;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) //
	{
	  USART_ClearFlag(USART1, USART_IT_RXNE); 
		
		if(recdata=='a')  //通过校验位
		{
	   LORA[res-1]  = USART_ReceiveData(USART1);		 
		}	  
		if(res==0)  //检验位判断
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

//解析数据   
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