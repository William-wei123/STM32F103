#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
typedef struct {
	u8 Array_[9];					//下
	u16 Average_DATA;					//下平均值
	u8 Flag_Start;
} DATA_array;

typedef struct {
	s8 err_xia;					//下	//当开始靠近障碍物时开始计算真正的误差值
	s8 err_qiang;					//前
	s8 err_zuo;					//左
} _err_;
void uart1_init(u32 bound1);
void uart3_init(u32 bound2);
void uart2_init(u32 bound3);
u16 panduan(u8 _DIST_[9]);

extern u16  USART_RX_STA;  	//接受标识符，/****如果主函数中不在发送后清除，
							//			 就会不断地往USART_RX_BUF中写数据，写爆为止才清空USART_RX_BUF******/
extern u8 USART_RX_BUF[USART_REC_LEN];	//用来存放存进来的数据（个人规定的数据寄存器）

#endif
