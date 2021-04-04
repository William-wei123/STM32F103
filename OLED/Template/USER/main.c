#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "sys.h"
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
		char *Str;
		char *cccc;
	char *c1;
	delay_init();
	OLED_Init();
	OLED_Display_On();
	//OLED_SHOW();
	Clear_OLED(0,0,128,8);
	OLED_WCMD(0x2e);						//关闭所有翻滚功能，之后需要重新加载发生翻滚区域的数据
//	OLED_SHOW_DRAW(0,0,128,64,OLED_GRAM);
//	OLED_SHOW16X16(36,0,40,16,wen);
//	OLED_SHOW16X16(36,4,40,16,shi);
//	OLED_SHOW_DRAW(85,0,35,64,tamperator);
	OLED_SHOWNumber(77,0,8, 16,10363);
	show_char(36,4,8,16,'0');
	Str ="sdfs";
		cccc="ADC";
		c1="ADC";
//	show_Str(0,0,8, 16,Str);
//	show_char(36,5,8,16,'0');
		show_Str(0,0,8, 16,Str);
		show_Str(0,3,24, 16,cccc);


//	OLED_SHOW16X16(36,2,48,16,ERROR___);
//	Horizontal_Scroll(1,0,3,7);
//	Vertical_and_Horizontal_Scroll(0,0,3,3);
}
