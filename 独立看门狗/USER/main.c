#include "Key.h"
#include "wdg.h"
#include "delay.h"

int main(void)
{
	delay_init();//��ʱ��ʼ��
	Init_KeyLed();//��ʼ���ƺͰ���
	delay_ms(300);//��ʱ300���룬������ɼ�
	IWDG_Init(4,625);//Ԥ��Ƶ64����ת��ֵΪ625�����ʱ��Ϊ1S��
	LED0=0;//����
	while(1){
		if(Key_Scan()==1){
			IWDG_Feed();
		}
	}
}


