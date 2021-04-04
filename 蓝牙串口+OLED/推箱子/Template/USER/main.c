#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "sys.h"
#include "usart..h"
#include "BOXman.h"

/************************************************

************************************************/

int main(void)
{	
	
	delay_init();
	usart1_Init(9600);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	OLED_Display_On();
	//OLED_SHOW();
	Clear_OLED();
	OLED_WCMD(0x2e);						//关闭所有翻滚功能，之后需要重新加载发生翻滚区域的数据
//	OLED_SHOW_DRAW(0,0,128,64,OLED_GRAM);
//	OLED_SHOW16X16(36,0,40,16,wen);
//	OLED_SHOW16X16(36,4,40,16,shi);
	OLED_SHOW_Explain();
	while(USART_RX_STA==0);
	switch(USART_RX_BUF[0]){
		case '1':Level(1,map1);
			break;
		case 'w':Level(2,map2);
			break;
		case '3':Level(3,map3);
			break;
	}	
//	DrawMap1(map1);

//	OLED_SHOW16X16(36,2,48,16,ERROR___);	
//	Horizontal_Scroll(1,0,3,7);				//水平滚屏
//	Vertical_and_Horizontal_Scroll(0,0,3,3);//滚屏
}
