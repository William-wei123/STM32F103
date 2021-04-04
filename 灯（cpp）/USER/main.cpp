#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "LED.h"
#include "KEY.h"
#include "weiyi.h"
 
int main(void)
{
	u8 T;
	delay_init();
	LED_Init();
	KEY_Init();
	TypeGpioX A=TypeGpioX('a',0x1222,3.3);
	while(1){
		T=0;

		T=KEY_Scan();
		switch(T){
			case 1:LED0 =!LED0 ;break ;
			case 2:LED1=!LED1;break;
			case 3:LED0=!LED0;
					LED1=!LED1;break;
			default:break;
		}
	}
//	LedRun();

}

