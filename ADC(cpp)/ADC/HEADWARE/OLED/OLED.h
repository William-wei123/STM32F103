#ifndef __OLED__H__
#define __OLED__H__
#ifdef   __cplusplus
extern "C" {
#endif
#include "sys.h"
#define SDI PBout(15)
#define SCL PBout(13)
#define DC PBout(12)		//1为数据，0 为命令
void OLED_WDATA(u8 cmd);
void  OLED_WCMD(u8 cmd);
void OLED_Init(void);
void OLED_Display_On(void);
void OLED_SHOW_DRAW(u8 X,u8 Y,u8 width, u8 hight,u8 DRAW[128][8]);
void OLED_SHOW16X16(u8 X,u8 Y,u8 width, u8 hight,u8 DATA[40][2]);
void Clear_OLED(u8 X1,u8 Y1,u8 X2,u8 Y2);
void OLED_SHOWNumber(u8 X,u8 Y,u8 width, u8 hight,u32 c);
void  Horizontal_Scroll(u8 CMD,u8 Y1,u8 Y2,u8 speed);
void  Vertical_and_Horizontal_Scroll(u8 CMD,u8 Y1,u8 Y2,u8 speed);
void show_char(u8 X,u8 Y,u8 width, u8 hight,u8 c);
void show_Str(u8 X,u8 Y,u8 width, u8 hight,char *c);




#ifdef __cplusplus
}
#endif
#endif