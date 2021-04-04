#ifndef __PWM_H
#define __PWM_H

#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc);	//舵机
void TIM4_PWM_Init(u16 arr,u16 psc);//普通电机

extern int Timel_NUM2;

#endif
