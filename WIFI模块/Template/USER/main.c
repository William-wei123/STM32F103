#include "stm32f10x.h"
#include "usart.h"
#include "MyWIFI_.h"
#include "delay.h"
#include "OLED.h"
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



int main(void)
{
	int i=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级	  

	uart_init(115200);
	OLED_Init();
	MyWIFI_Init();
	
	while(1)
	{
//		USART_Send_Str("AT\r\n",8);
//		delay_ms(5000);
		Send_Int(i++);
		i++;
//		Send_Double((i+100)/100.0,3);
//		WIFI_Send_DATA("12.222,151654161,184516984519451984151946116,41841516981316941616165131851,15498465194\r\n");
		if(USART_RX_STA>=200)USART_RX_STA=0;
	}
}
