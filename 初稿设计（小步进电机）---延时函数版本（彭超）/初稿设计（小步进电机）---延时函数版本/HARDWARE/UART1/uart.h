#ifndef _UART_H
#define _UART_H
#include "sys.h"

void UART_1_init(u32 bat);
void u32tostr(unsigned long dat,char *str) ;
void USART1_Putc(unsigned char c);
void USART1_Puts(char * str);
void UART_Send_Enter(void);
void UART_Send_Str(char *s);
void UART_Put_Num(unsigned long dat);
void Read_MPU6050_DATA(void);

#endif
