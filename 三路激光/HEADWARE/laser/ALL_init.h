#ifndef All_init__
#define All_init__
#define MYADDR 0x5d	`//01011101	��ô����ʱ��ַΪaddr<<1|1,д��ʱaddr<<1;
#include "stm32f10x.h"
#include "usart..h"
#include "ALL_init.h"
#include "delay.h"
#include "LaserPID.h"
void float_to_char(float *temp,char *_array_);//temp[4],_array_[5] Function:���ڻ����ת����char���͸�USART


void char_to_float(char *_array_);	//ת�����ݣ����˼��float_to_char�Ƿ���ȷ

void LASER_ACCEPT_DATA(u8 DATA,DATA_array *LASER__DATA);		//���ռ����������ݣ���ȡ��Ч���ݣ�

void LASER_DATA_HANDLE(s8 Flag,DATA_array *LASER__DATA,void (*FUNC)(int));//��������������(�������ݲ�����PID)

void FLY_DATA_HANDLE(u8 *FLY_DATA_ARRAY);	//����ɿ���������

u16 average_Data(u16 arr[] , int n);       //������ƽ��ֵ����
    
u8 _ACCEPT_DATA_BY_FLY(u8 DATA);			//���շɿ���������

extern u8 FLAG_Remap;						//USART1 ��ӳ���־��1Ϊ��ӳ��

extern u8 data_save_flag;					//�ɿ����������Ƿ���ȷ��1Ϊ��ȷ


#endif
