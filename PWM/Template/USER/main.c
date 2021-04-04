#include "stm32f10x.h"
#include "PWM.h"
#include "sys.h"
#include "delay.h"
#include "LED.h"
#include "KEY.h"
#include "uart.h"
char youmen_l=5,youmen_r=5,youmen_z=0,youmen_zl=0,youmen_zr=0;
char dir=1;//前进标志位
char youmen_1=0,youmen_2=0,youmen_3=0,youmen_4=0;

/************************************************

************************************************/


void Delay(u32 count)
{
   u32 i=0;
   for(;i<count;i++);
}
void advance()//前进
{
	TIM_SetCompare1(TIM4,youmen_l*50);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,youmen_r*50);
	TIM_SetCompare4(TIM4,0);
	dir=1;
}
void counter()//后退
{
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,youmen_l*50);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,youmen_r*50);
	dir=0;
}
void left()//左转
{
//	if(dir==1)
//	{
		TIM_SetCompare1(TIM4,youmen_1*100);//youmen_l*50
		TIM_SetCompare2(TIM4,youmen_2*100);
		TIM_SetCompare3(TIM4,youmen_3*100);
		TIM_SetCompare4(TIM4,youmen_4*100);//youmen_r*50
//	}
//	else
//	{
//		TIM_SetCompare1(TIM4,0);
//		TIM_SetCompare2(TIM4,0+youmen_zl*100);//youmen_l*50
//		TIM_SetCompare3(TIM4,0+youmen_zr*100);//youmen_r*50
//		TIM_SetCompare4(TIM4,0);

//	}
}
void right()//右转
{
//	if(dir==1)
//	{
		TIM_SetCompare1(TIM4,youmen_1*100);//youmen_l*50
		TIM_SetCompare2(TIM4,youmen_2*100);
		TIM_SetCompare3(TIM4,youmen_3*100);
		TIM_SetCompare4(TIM4,youmen_4*100);//youmen_r*50
//	}
//	else
//	{
//		TIM_SetCompare1(TIM4,0+youmen_zl*100);//youmen_l*50
//		TIM_SetCompare2(TIM4,0);
//		TIM_SetCompare3(TIM4,0);
//		TIM_SetCompare4(TIM4,0+youmen_zr*100);//youmen_r*50
//	}
}
void stop()
{
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);

}
int main(void)
{	
//	u16 led0pwmval=0;
//	u8 Temp;
	delay_init();
	usart3_Init(9600);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

//	KEY_Init();
//	LED_Init();
	TIM4_PWM_Init(899,0);//899+1，0+1   即900/72Mhz为一个周期，然后占空比为led0pwmval/（899+1）频率为80KHz
	while(1){
////		delay_ms(10);
////		if(dir){
////			led0pwmval+=1;
////		}
////		else led0pwmval--;
////		if(led0pwmval>300)dir=0;
////		if(led0pwmval==0)dir=1;
//		Temp=KEY_Scan();
//		switch(Temp){
//			case 1:led0pwmval=899;break;
//			case 2:led0pwmval=0;break;
//			default:break;
//		}
//		advance();
//		delay_ms(5535);
//		counter();//前进
//		delay_ms(5535);
//		left();
//		delay_ms(5535);
//		right();//右转
//		delay_ms(5535);
//		stop();
//		delay_ms(5535);
		switch(USART_RX_BUF)
		{			
			case 'W': advance();break;
			case 'S': counter();break;
			case 'A': left();	break;
			case 'D': right();	break;
			case 'P': stop();	break;
			case 'l': youmen_l++;USART_RX_BUF='P';break;
			case 'L': youmen_l--;USART_RX_BUF='P';break;
			case 'r': youmen_r++;USART_RX_BUF='P';break;
			case 'R': youmen_r--;USART_RX_BUF='P';break;
			case '1': youmen_1++;USART_RX_BUF='P';break;
			case '2': youmen_2++;USART_RX_BUF='P';break;
			case '3': youmen_3++;USART_RX_BUF='P';break;
			case '4': youmen_4++;USART_RX_BUF='P';break;
			case '+': youmen_r++;youmen_l++;USART_RX_BUF='P';break;
			case '-': youmen_r--;youmen_l--;USART_RX_BUF='P';break;
			case '0': youmen_1=0;youmen_2=0;youmen_3=0;youmen_4=0;break;
			default :break;
		}
		if(youmen_l>10)youmen_l=10;
		if(youmen_r>10)youmen_r=10;
		if(youmen_l<3)youmen_l=3;
		if(youmen_r<3)youmen_r=3;
		if(youmen_zl>8)youmen_zl=8;
		if(youmen_zl<1)youmen_zl=0;
		if(youmen_zr>8)youmen_zr=8;
		if(youmen_zr<1)youmen_zr=0;

		USART_Cmd(USART3,ENABLE); 
//		TIM_SetCompare1(TIM4,100);
//		TIM_SetCompare2(TIM4,200);
//		TIM_SetCompare3(TIM4,300);
//		TIM_SetCompare4(TIM4,400);

	}

}
