#ifndef WEIYI__H
#define WEYII__H
#include "sys.h"
class TypeGpioX{
	public:
		GPIO_InitTypeDef GPIO_InitStructure;//
	
		void Init(){
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		}
		TypeGpioX(char X,u16 dat, float U){
			Init();
			switch (X){
				case 'A':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟使能A口
						Init();
						GPIO_Init(GPIOA,&GPIO_InitStructure);break;
				case 'B':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//时钟使能B口
						Init();GPIO_Init(GPIOB,&GPIO_InitStructure);break;
				case 'C':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
						Init();GPIO_Init(GPIOC,&GPIO_InitStructure);break;
				case 'D':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
						Init();GPIO_Init(GPIOD,&GPIO_InitStructure);break;
				case 'E':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
						Init();GPIO_Init(GPIOE,&GPIO_InitStructure);break;
				case 'F':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
						Init();GPIO_Init(GPIOF,&GPIO_InitStructure);break;
				case 'G':RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
						Init();GPIO_Init(GPIOG,&GPIO_InitStructure);break;
			}
		
		
		}
		~TypeGpioX();
};

#endif
