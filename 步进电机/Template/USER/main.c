#include "stm32f10x.h"
#include "delay.h"


void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}

u16 temp = 2000;

void accelerate(int C)
{
	if(temp >51)
		temp-=C;
	else temp =6000;
}

void decelerate (int C)
{
	if(temp <=20000)
		temp+=C;
	else 
		temp = 2000;
}
void Step_Motor_CW()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6);
	delay_us(temp);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_6);
	delay_us(temp);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8);
	delay_us(temp);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_8);
	delay_us(temp);

}

void Step_Motor_CCW()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	delay_ms(2000);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_ms(2000);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_ms(2000);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	delay_ms(2000);	

}
void Step_Motor_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|
	RCC_APB2Periph_GPIOE, ENABLE);	    //??PB,PE????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;			    //LED0-->PB.5 ????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO????50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			     //???GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_5);					//PB.5 ???
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //LED1-->PE.5????
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  	       //???GPIO
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 			 //PE.5 ??? 	  
}
u16 count =1;
int main(void)
{	
	int i;
	delay_init();
	Step_Motor_Init();
	
	while(1)
	{
		for (;count>0;count--){
			for (i=0;i<=64;i++)
				Step_Motor_CW();
		}
			
		
		//accelerate(25);
	}
}
