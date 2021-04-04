#include "adc.h"
#include "delay.h"



void ADC1_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	 ADC_InitTypeDef  ADC_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1, ENABLE);	 //使能A端口时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //推挽输出
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA1
	
	ADC_DeInit(ADC1); //
	ADC_InitStructure.ADC_ContinuousConvMode =  DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode =  DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1); //?????? 
  while(ADC_GetResetCalibrationStatus(ADC1)); //????????
  ADC_StartCalibration(ADC1); //?? AD ??
  while(ADC_GetCalibrationStatus(ADC1)); //??????
}

short get_adcvable(u8 ch)
{
  ADC_RegularChannelConfig(ADC1, ch , 1 , ADC_SampleTime_71Cycles5);  //采样顺序值为1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //????????
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//??????
  return ADC_GetConversionValue(ADC1); //?????? ADC1 ????????
}

short get_adcAverage(u8 ch,u8 times)  //取采样10次的平均值
{
  u32 temp_val=0;
  u8 t;
  for(t=0;t<times;t++)
  { temp_val+=get_adcvable(ch);
    delay_ms(5);
  }
return temp_val/times;
}
