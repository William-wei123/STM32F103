#include "stm32f10x.h"
#include "sys.h"
#include "timer.h"
#include "delay.h"
#include "LED.h"


/************************************************

************************************************/


// void Delay(u32 count)
// {
//   u32 i=0;
//   for(;i<count;i++);
// }
 int main(void)
{
	delay_init();
	TIMERX_Int_Init(9999,3599);//对定时器3初始化    （9999+1）*（3599+1）/72MHz=10000/2 *10^-4s=500ms激发一次上溢中断上溢
	LED_Init();				//(9999,3599)=(4999,7199)
	
  	  
	while(1)
	{
		LED0=!LED0;
		delay_ms(1000);
	}
}
