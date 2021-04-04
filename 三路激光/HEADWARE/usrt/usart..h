#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define HEADER 					0x59	//激光数据头

typedef struct {
	u8 Array_[9];					//接收到的数据包
	u16 Average_array[5];
	u16 Average_DATA;					//计算平均值（没有到）
	u8 Flag_Start;						//接收开始的标志位，每接收到一个数据包置0
	char DATA_TO_FLY[5];
	void (*method)(int);				//一个函数指针，指向对应数据处理的函数名，name.method=&函数名
} DATA_array;						//激光数据的结构体

typedef struct {
	s8 err_xia;					//下	//当开始靠近障碍物时开始计算真正的误差值
	s8 err_qiang;					//前
	s8 err_zuo;					//左
} _err_;
void uart1_init(u32 bound1);
void uart3_init(u32 bound2);
void uart2_init(u32 bound3);
u16 panduan(u8 _DIST_[9]);
extern float HIGHT_CTRL_OUTPUT_[5];
extern float PITCH_CTRL_OUTPUT_[5];
extern float ROLL_CTRL_OUTPUT_[5];

extern u16  USART_RX_STA;  	//接受标识符，/****如果主函数中不在发送后清除，
							//			 就会不断地往USART_RX_BUF中写数据，写爆为止才清空USART_RX_BUF******/
extern u8 USART_RX_BUF[USART_REC_LEN];	//用来存放存进来的数据（个人规定的数据寄存器）
#endif
