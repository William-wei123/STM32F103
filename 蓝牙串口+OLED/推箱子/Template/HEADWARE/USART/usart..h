#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
void usart1_Init(u32 bound);
extern u16  USART_RX_STA;  	//���ܱ�ʶ����/****����������в��ڷ��ͺ������
							//			 �ͻ᲻�ϵ���USART_RX_BUF��д���ݣ�д��Ϊֹ�����USART_RX_BUF******/
extern char USART_RX_BUF[USART_REC_LEN];	//������Ŵ���������ݣ����˹涨�����ݼĴ�����

#endif
