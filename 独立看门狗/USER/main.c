#include "Key.h"
#include "wdg.h"
#include "delay.h"

int main(void)
{
	delay_init();//延时初始化
	Init_KeyLed();//初始化灯和按键
	delay_ms(300);//延时300毫秒，让亮灭可见
	IWDG_Init(4,625);//预分频64，重转载值为625，溢出时间为1S；
	LED0=0;//灯亮
	while(1){
		if(Key_Scan()==1){
			IWDG_Feed();
		}
	}
}


