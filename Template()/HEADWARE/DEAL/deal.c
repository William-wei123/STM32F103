#include "deal.h"
//#include "uart.h"
//#include "led.h"
#include "delay.h"
#include "PWM.h"
void advance()//前进
{
	TIM_SetCompare1(TIM1,6000);
	TIM_SetCompare2(TIM1,6000);
}
void counter()//后退
{
	TIM_SetCompare1(TIM1,4000);
	TIM_SetCompare2(TIM1,4000);
}
void left()//左转
{
	TIM_SetCompare1(TIM1,5500);
	TIM_SetCompare2(TIM1,6000);
}
void right()//右转
{
	TIM_SetCompare1(TIM1,6000);
	TIM_SetCompare2(TIM1,5500);
}
void stop()
{
	TIM_SetCompare1(TIM1,5000);
	TIM_SetCompare2(TIM1,5000);
}
void speed_up()
{
}

