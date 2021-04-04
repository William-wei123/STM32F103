#include "sys.h"
#ifndef USART_____H__
#define USART_____H__
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define HEADER 					0x59	//��������ͷ

typedef struct {
	u8 Array_[9];					//���յ������ݰ�
	u16 Average_array[5];
	u16 Average_DATA;					//����ƽ��ֵ��û�е���
	u8 Flag_Start;						//���տ�ʼ�ı�־λ��ÿ���յ�һ�����ݰ���0
	char DATA_TO_FLY[5];
	void (*method)(int);				//һ������ָ�룬ָ���Ӧ���ݴ���ĺ�������name.method=&������
} DATA_array;						//�������ݵĽṹ��

typedef struct {
	s8 err_xia;					//��	//����ʼ�����ϰ���ʱ��ʼ�������������ֵ
	s8 err_qiang;					//ǰ
	s8 err_zuo;					//��
} _err_;
void uart1_init(u32 bound1);
void uart3_init(u32 bound2);
void uart2_init(u32 bound3);
u16 panduan(u8 _DIST_[9]);
extern float HIGHT_CTRL_OUTPUT_[5];
extern float PITCH_CTRL_OUTPUT_[5];
extern float ROLL_CTRL_OUTPUT_[5];

extern u16  USART_RX_STA;  	//���ܱ�ʶ����/****����������в��ڷ��ͺ������
							//			 �ͻ᲻�ϵ���USART_RX_BUF��д���ݣ�д��Ϊֹ�����USART_RX_BUF******/
extern u8 USART_RX_BUF[USART_REC_LEN];	//������Ŵ���������ݣ����˹涨�����ݼĴ�����
#endif
