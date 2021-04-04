#include "LED.h"
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrucure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_Out_PP;		/*推挽输出*/
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_8;				//Pin=8
	
	GPIO_InitStrucure.GPIO_Speed=GPIO_Speed_50MHz;		//IO口速度为50MHz
	
	GPIO_Init(GPIOA,&GPIO_InitStrucure);				//统一加载初始化
	//GPIO_SetBits(GPIOA,GPIO_Pin_8);					//PA.8输出为高电平
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_2;
	
	GPIO_Init(GPIOD,&GPIO_InitStrucure);
	
	//GPIO_SetBits(GPIOD,GPIO_Pin_2);
}
void LedRun()
{
	while(1){
		LED0=0;
		LED1=1;
		delay_ms(300);
		LED0=1;
		LED1=0;
		delay_ms(300);
	}

}

