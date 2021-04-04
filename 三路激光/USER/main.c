#include "ALL_init.h"
/************************************************
 ALIENTEK ??STM32F103?????0
 ????
 ??,???????????????main?? 
 ????:www.openedv.com
 ????:http://eboard.taobao.com 
 ???????????:"????",????STM32???
 ?????????????  
 ??:???? @ALIENTEK
************************************************/

u8 FLAG_Remap=0;
void Delay(u32 count)
{
u32 i=0;
for(;i<count;i++);
}
int main(void)
{	
	u32 _CRL;
	u32 _CRH;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能APB2外设的重映射
	//	IIC_init();
	delay_init();
	uart1_init(115200);
//	
	uart3_init(115200);
//	
	uart2_init(115200);
	PID_Height_init();
	while(1)
	{
		if(FLAG_Remap==0){
			GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);
			_CRL=GPIOB->CRL;
			_CRL=(_CRL&0x00FFFFFF)|0x44000000;	//PB6设置为浮空输入
			GPIOB->CRL=_CRL;
			
			_CRH=GPIOA->CRH;
			_CRH=(_CRH&0xFFFFF00F)|0x000004B0;	//PA9设置为复用推挽输出（开启非重映射的串口输出）	
			GPIOA->CRH=_CRH;
			USART_Cmd(USART2,DISABLE);
			USART_Cmd(USART3,DISABLE);
		}else {
			USART_Cmd(USART2,ENABLE);	//使能串口2和3，准备接收激光数据
			USART_Cmd(USART3,ENABLE);
			GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
			_CRH=GPIOA->CRH;
			_CRH=(_CRH&0xFFFFF00F)|0x00000440;	//PA9设置为浮空输入(关闭串口输出)		
			GPIOA->CRH=_CRH;
			
			_CRL=GPIOB->CRL;
			_CRL=(_CRL&0x00FFFFFF)|0x4B000000;	//PB6设置为复用推挽输出（开启重映射的串口输出）
			GPIOB->CRL=_CRL;

		}
		



		
	}
 }
