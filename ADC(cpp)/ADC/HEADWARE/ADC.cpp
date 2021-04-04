#include "ADC.h"
#include "delay.h"
#include "OLED.h"
/*
uint32_t RCC_APB2Periph		//����ĵ�ַʱ��
FunctionalState NewState	//�Ƿ�ʹ��
ADC_TypeDef* ADCx			//����ADCx
GPIO_TypeDef * GPIO_X		//����GPIO_X
uint16_t Pin				//����GPIO_Pin_x   ��ʽ��GPIO_Pin_1
u8 a						//����ͨ����a,
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
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIO_X, &GPIO_InitStructure);
	ADC_DeInit(ADCx);  //��λADCx 	
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ  ?????
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = a;	//˳����й���ת����ADCͨ������Ŀ					
	ADC_Init(ADCx, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	ADC_Cmd(ADCx, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADCx);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADCx));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADCx);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADCx));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}

/*
ch ��ʾͨ��ch		ADC1 ch(0,15);ADC2 ch(0,15);ADC3 ch(0,8)~ch(10,13)


*/
double ADC_Test::Get_Adc(u8 ch)
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADCx);	//�������һ��ADC1�������ת�����
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
