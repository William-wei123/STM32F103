#include "stm32f10x.h"
#include "sys.h"
#include "temperation.h"
#include "delay.h"
#include "usart..h"
#include "OLED.h"
#include "Buzzer.h"
extern u8 OLED_GRAM[128][8];
extern u8 wen[40][2];
extern u8 shi[40][2];
extern u8 number[10][16];
unsigned char ERROR__[7]="ERROR!";
extern u8 ERROR___[64][2];
extern u8 dot[8][2];
#define Warning  20						//�¶���ֵ
void DATA_To_OLED()//��������ʾ��Oled����
{
	Clear_OLED(77,0,128,2);
	Clear_OLED(77,4,128,6);
	OLED_SHOWNumber(77,0,8, 16,Data[2]);
	OLED_SHOW16X16(95,0,8,16,dot);
	OLED_SHOWNumber(104,0,8, 16,Data[3]/10);
	OLED_SHOWNumber(113,0,8, 16,Data[3]%10);
	OLED_SHOWNumber(77,4,8, 16,Data[0]);
	OLED_SHOW16X16(95,4,8,16,dot);
	OLED_SHOWNumber(104,4,8, 16,Data[1]/10);
	OLED_SHOWNumber(113,4,8, 16,Data[1]%10);

}
u8 TESTTemperature()  //�����¶�
{
	unsigned int temp=3;
	unsigned int i;
	u8 warning=0;
	TemperationSendCmd();
	temp=TemperationGetData();
	switch(temp){
		case 1:				//��ʪ�ȴ�����������Ч����
			TXTemperation();
			delay_ms(1000);
			DATA_To_OLED();
			if(Data[2]>Warning)warning=1;
			break;
		case 0:
			for(i=0;i<7;i++){
				USART1->DR=ERROR__[i];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
			}
			OLED_SHOW16X16(77,0,48,16,ERROR___);
			
			OLED_SHOW16X16(77,4,48,16,ERROR___);
			break;
	}			
	delay_ms(5000);
	return warning;
}
/*************************
*������ main(void)
*���ܣ��ۺϸ�������ʵ�ֱ����͹���
*����ֵ����
*���ߣ���ΰƽ
**************************/

int main(void)
{
	delay_init();
	uart1_init(38400);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	OLED_Init();
	Buzzer_Init();
	delay_ms(1500);
	while(1){
		switch(TESTTemperature()){
			case 1:
				Buzzer=1;
				break;	
			case 0:
				Buzzer=0;
				break ;
			}
	}
}
