#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
void uart1_init(u32 bound);
extern u16  USART_RX_STA;  	//接受标识符，/****如果主函数中不在发送后清除，
							//			 就会不断地往USART_RX_BUF中写数据，写爆为止才清空USART_RX_BUF******/
extern u8 USART_RX_BUF[USART_REC_LEN];	//用来存放存进来的数据（个人规定的数据寄存器）

#endif
