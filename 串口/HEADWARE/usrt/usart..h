#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
typedef struct {
	u8 Array_[9];					//��
	u16 Average_DATA;					//��ƽ��ֵ
	u8 Flag_Start;
} DATA_array;

typedef struct {
	s8 err_xia;					//��	//����ʼ�����ϰ���ʱ��ʼ�������������ֵ
	s8 err_qiang;					//ǰ
	s8 err_zuo;					//��
} _err_;
void uart1_init(u32 bound1);
void uart3_init(u32 bound2);
void uart2_init(u32 bound3);
u16 panduan(u8 _DIST_[9]);

extern u16  USART_RX_STA;  	//���ܱ�ʶ����/****����������в��ڷ��ͺ������
							//			 �ͻ᲻�ϵ���USART_RX_BUF��д���ݣ�д��Ϊֹ�����USART_RX_BUF******/
extern u8 USART_RX_BUF[USART_REC_LEN];	//������Ŵ���������ݣ����˹涨�����ݼĴ�����

#endif
