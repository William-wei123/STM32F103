#ifndef _EXIT_H
#define _EXIT_H
#include "sys.h"


typedef struct   //控制标志位结构体
{
 u8 raise;       //衣架伸出的标志位
 u8 fall;        //衣架缩回的标志位
 u8 automatic;   //开启传感器检测的自动模式标志位
 u8 exit9_5;
 u8 exit15_10;
}FLAG;
extern FLAG flag;

extern u8 tempture_flag;
extern u16 cs;
void EXITX_init(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
