#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "encoder.h"
#include "CCWCW.h"
#include "PWM.h"

/************************************************
 ALIENTEK ??STM32F103?????0
 ????
 ??,???????????????main?? 
 ????:www.openedv.com
 ????:http://eboard.taobao.com 
 ???????????:"????",????STM32???
 ?????????????  
 ??:???? @ALIENTEK
************************************************/


//void Delay(u32 count)
//{
//	u32 i=0;
//	for(;i<count;i++);
//}
int acc;
int temp=1000;
u8 i;
int main(void)
{
	
//	int temp=1000;
//	int acc;
	i=1;
	delay_init();
	OLED_Init();
	OLED_Display_On();
	Encoder_Init_TIM4();
	CCW_CW_Init();
	TIM1_PWM_Init(899,0);
	acc=450;
	while(1){
		
		BIN1=i;
		BIN2=!i;
		temp=Read_Encoder(4);
		OLED_SHOWNumber(1,0,8,16,temp);
		
//		delay_ms(1000);
		Clear_OLED(0,0,128,2);
//		BIN1=0,BIN2=1;
		TIM_SetCompare1(TIM1,acc);

	}	
}
 