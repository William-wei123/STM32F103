#ifndef TIMER__H_
#define TIMER__H_
#include "sys.h"
#define TIMERX  TIM3   //�ǵû�timer.cȥ��TIMERX_IRQn���жϷ�����
void TIMERX_Int_Init(u16 arr,u16 pas);//����
#endif
