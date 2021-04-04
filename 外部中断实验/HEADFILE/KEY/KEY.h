#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)	//读取按键PC5
#define KEY1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define WE_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY0_pres 1				//KEY0 按下为1
#define KEY1_pres 2				//KEY1 按下为2
#define WE_UP_pres 3			//WE_Up 按下为3

void KEY_Init(void);				//声明IO口初始化
u8 KEY_Scan(void);					//声明按键扫描
#endif
