#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)	//��ȡ����PC5
#define KEY1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define WE_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY0_pres 1				//KEY0 ����Ϊ1
#define KEY1_pres 2				//KEY1 ����Ϊ2
#define WE_UP_pres 3			//WE_Up ����Ϊ3

void KEY_Init(void);				//����IO�ڳ�ʼ��
u8 KEY_Scan(void);					//��������ɨ��
#endif
