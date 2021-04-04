#ifndef _EXIT_H
#define _EXIT_H
#include "sys.h"


typedef struct   //���Ʊ�־λ�ṹ��
{
 u8 raise;       //�¼�����ı�־λ
 u8 fall;        //�¼����صı�־λ
 u8 automatic;   //���������������Զ�ģʽ��־λ
 u8 exit9_5;
 u8 exit15_10;
}FLAG;
extern FLAG flag;

extern u8 tempture_flag;
extern u16 cs;
void EXITX_init(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
