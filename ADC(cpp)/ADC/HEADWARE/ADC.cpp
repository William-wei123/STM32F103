#include "ADC.h"
#include "delay.h"
#include "OLED.h"
/*
uint32_t RCC_APB2Periph		//外设的地址时钟
FunctionalState NewState	//是否使能
ADC_TypeDef* ADCx			//启用ADCx
GPIO_TypeDef * GPIO_X		//启用GPIO_X
uint16_t Pin				//启用GPIO_Pin_x   格式如GPIO_Pin_1
u8 a						//启用通道数a,
						ADC1 a(0,15);ADC2 a(0,15);ADC3 a(0,8)~a(10,13)
*/
ADC_Test::ADC_Test(uint32_t RCC_APB2Periph, FunctionalState NewState,ADC_TypeDef* ADCx,GPIO_TypeDef * GPIO_X,uint16_t Pin,u8 a)
{
	this->RCC_APB2Periph=RCC_APB2Periph;
	this->NewState=NewState;
	this->ADCx=ADCx;
	this->GPIO_X=GPIO_X;
	this->Pin=Pin;
	this->a=a;
}
ADC_Test::ADC_Test()
{
	this->RCC_APB2Periph=RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1;
	this->NewState=ENABLE;
	this->ADCx=ADC1;
	this->GPIO_X=GPIOA;
	this->Pin=GPIO_Pin_1;
	this->a=1;
}
void ADC_Test::Adc_IniT()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,NewState);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIO_X, &GPIO_InitStructure);
	ADC_DeInit(ADCx);  //复位ADCx 	
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式  ?????
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = a;	//顺序进行规则转换的ADC通道的数目					
	ADC_Init(ADCx, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

	ADC_Cmd(ADCx, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADCx);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADCx));	//等待复位校准结束
	
	ADC_StartCalibration(ADCx);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADCx));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}

/*
ch 表示通道ch		ADC1 ch(0,15);ADC2 ch(0,15);ADC3 ch(0,8)~ch(10,13)


*/
double ADC_Test::Get_Adc(u8 ch)
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADCx);	//返回最近一次ADC1规则组的转换结果
}
double  ADC_Test::Get_Adc_Average(u8 ch,u8 times)
{
	double temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}
/*
u8 X1,u8 Y1 ,u8 X2,u8 Y2
X1:
*/
void ADC_Test::ADCSHOW(u8 X1,u8 Y1 ,u8 X2,u8 Y2)
{
		
	float Adc_data;
	double temp;
	OLED_SHOWNumber(X1,Y1,8,16,temp);
	Adc_data=temp*(3.3/4096);
	OLED_SHOWNumber(X2,Y2,8,16,(int)Adc_data);
	Adc_data-=(int)Adc_data;
	show_char(X2+16,Y2,8,16,'.');
	OLED_SHOWNumber(X2+16,Y2,8,16,Adc_data*1000);
}
ADC_Test::~ADC_Test()
{
}
