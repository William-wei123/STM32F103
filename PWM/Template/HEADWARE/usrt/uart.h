#include "sys.h"
#ifndef UART_____H__
#define UART_____H__
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
void usart3_Init(u32 bound);
extern u16  USART_RX_STA;  	//���ܱ�ʶ����/****����������в��ڷ��ͺ������
							//			 �ͻ᲻�ϵ���USART_RX_BUF��д���ݣ�д��Ϊֹ�����USART_RX_BUF******/
extern char USART_RX_BUF;	//������Ŵ���������ݣ����˹涨�����ݼĴ�����[USART_REC_LEN]

#endif
