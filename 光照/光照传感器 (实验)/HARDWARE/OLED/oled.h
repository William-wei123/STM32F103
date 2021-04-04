#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	


#define OLED_MODE 0

#define OLED_SCLK PBout(0)
#define OLED_SDIN PBout(1)
#define OLED_DC PBout(6)

#define DATAOUT(DataValue) {GPIO_Write(GPIOB,(GPIO_ReadOutputData(GPIOB)&0xff00)|(DataValue&0x00FF));}  

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const char  *p,u8 size);
void OLED_ShowModel(u8 x,u8 y,u8 m,u8 n,u8 mode,u8 c);
#endif  
	 


