#ifndef __MyWIFI__H____
#define __MyWIFI__H____
#include "sys.h"
#define USART_Send_Str 		USART1_Send_Str			//�ı����ĸı�ͨ���Ǹ����ڷ���

void MyWIFI_Init(void);

void WIFI_Send(char *COM);

void DATA_To_COM(char *DAT);

void WIFI_Send_DATA(char *DAT);

void NUM_TO_STR(int NUM,char *STR);


void Duoble_TO_STR(double NUM,char *STR,char precision);

void Send_Double(double NUM,char precision);

void Send_Int(int NUM);

void Send_New_Line(void);

void Acceive_DATA(u8 Res);

void DATA_HANDLE(char *DATA_ARR);


extern u16 Send_flag;		//==2��ʾ�������  �о�û��Ҫ
extern char DATA_Acc[2048];
extern u16 Acce_Flag;
extern int Acc_DATA_LEN;			//�������ݳ���



#endif
