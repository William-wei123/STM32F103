#ifndef TIMER__H_
#define TIMER__H_
#include "sys.h"
#define TIMERX  TIM3   //记得回timer.c去改TIMERX_IRQn和中断服务函数
void TIMERX_Int_Init(u16 arr,u16 pas);//声明
#endif
