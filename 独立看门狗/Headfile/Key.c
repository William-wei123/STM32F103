#include "Key.h"
#include "delay.h"

void Init_KeyLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

u8 Key_Scan(void)
{
	u8 key,temp=0;
	key=WE_UP;
	switch(key){
		case 1:delay_ms(10);
			key=WE_UP;
			switch(key){
				case 1:temp=1;
			}
		default :break;
	}
	return temp;
}
