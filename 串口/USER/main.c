//#include "stm32f10x.h"
#include "usart..h"
#include "delay.h"
#include "sys.h"
#include "LED.h"
u8 FLAG_Remap=1;

unsigned char hello[10]="��ð�\r\n";
int main(){
	u8 t;
	u8 len;	
	u16 times=0; 
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	
	uart1_init(115200);	 //���ڳ�ʼ��Ϊ9600
//	LED0=0;
	while(1)
	{
////		if(USART_RX_STA&0x8000)				//��Ӧ����&&������
////		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
////			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<10&&USART_RX_STA!=0;t++){
////				USART1->DR=hello[t];
////				while((USART1->SR&0X40)==0);//�ȴ����ͽ���       *�ǳ��ؼ�������֪��Ϊʲô*
//				
//			}
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//			}
//			//printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
////		}else
////		{
//			times++;
////			if(times%5000==0)
////			{
////				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
////				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
////			}
////			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			//if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
//			delay_ms(1000);
//			LED0=!LED0;
////		}
				USART1->DR=0x16;
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���       *�ǳ��ؼ�������֪��Ϊʲô*
		delay_ms(49);
	}	 
}
