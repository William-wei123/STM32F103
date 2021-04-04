#ifndef All_init__
#define All_init__
#define MYADDR 0x5d	`//01011101	那么读此时地址为addr<<1|1,写此时addr<<1;
#include "stm32f10x.h"
#include "usart..h"
#include "ALL_init.h"
#include "delay.h"
#include "LaserPID.h"
void float_to_char(float *temp,char *_array_);//temp[4],_array_[5] Function:把内环输出转换成char类型给USART


void char_to_float(char *_array_);	//转换数据，个人检测float_to_char是否正确

void LASER_ACCEPT_DATA(u8 DATA,DATA_array *LASER__DATA);		//接收激光所给数据（获取有效数据）

void LASER_DATA_HANDLE(s8 Flag,DATA_array *LASER__DATA,void (*FUNC)(int));//处理激光所给数据(解析数据并运算PID)

void FLY_DATA_HANDLE(u8 *FLY_DATA_ARRAY);	//处理飞控所给数据

u16 average_Data(u16 arr[] , int n);       //晓辉求平均值函数
    
u8 _ACCEPT_DATA_BY_FLY(u8 DATA);			//接收飞控所传数据

extern u8 FLAG_Remap;						//USART1 重映射标志，1为重映射

extern u8 data_save_flag;					//飞控所传数据是否正确，1为正确


#endif
