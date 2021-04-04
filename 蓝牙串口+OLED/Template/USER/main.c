#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "sys.h"
#include "usart..h"
extern u8 OLED_GRAM[128][8];
extern u8 wen[40][2];
extern u8 shi[40][2];
extern u8 number[10][16];
extern u8 ERROR___[64][2];
extern u8 tamperator[35][8];

/************************************************

************************************************/

int main(void)
{	
	
//	int i;
	delay_init();
	usart1_Init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	OLED_Display_On();
	//OLED_SHOW();
	Clear_OLED();
	OLED_WCMD(0x2e);						//关闭所有翻滚功能，之后需要重新加载发生翻滚区域的数据
//	OLED_SHOW_DRAW(0,0,128,64,OLED_GRAM);
//	OLED_SHOW16X16(36,0,40,16,wen);
//	OLED_SHOW16X16(36,4,40,16,shi);
	//OLED_SHOW_DRAW(85,0,35,64,tamperator);
	while(1){
		if(USART_RX_STA>0){
			delay_ms(50);
			Clear_OLED();
			show_Str(1,0,8,16,USART_RX_BUF);
			delay_ms(500);
			Clear_OLED();
			USART_RX_STA=0;
			
			USART_Cmd(USART1,ENABLE);
		}
	}
//	OLED_SHOW16X16(36,2,48,16,ERROR___);	
//	Horizontal_Scroll(1,0,3,7);				//水平滚屏
//	Vertical_and_Horizontal_Scroll(0,0,3,3);//滚屏
}
