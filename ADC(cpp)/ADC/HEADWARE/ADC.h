
//#pragma once ADC__H__
#ifndef ADC__H__
#define ADC__H__
#include "sys.h"
#include "delay.h"

#define ADC ADC1
class ADC_Test{
	public:
		ADC_InitTypeDef ADC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		uint32_t RCC_APB2Periph;
		FunctionalState NewState;
		ADC_TypeDef* ADCx;
		GPIO_TypeDef * GPIO_X;
		uint16_t Pin;
		u8 a;
		ADC_Test();//自动初始化ADC1 一通道（PA1）
		ADC_Test(uint32_t RCC_APB2Periph, FunctionalState NewState,ADC_TypeDef* ADCx,GPIO_TypeDef * GPIO_X,uint16_t Pin,u8 a);
		void Adc_IniT();
		 double Get_Adc(u8 ch);
		 double Get_Adc_Average(u8 ch ,u8 times);
		void ADCSHOW(u8 X1,u8 Y1 ,u8 X2,u8 Y2);
		~ADC_Test();

};

#endif
