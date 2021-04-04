#include "stm32f10x.h"
#include "ADC.h"
#include "OLED.h"
#include "delay.h"

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


int main(void)
{
	char *c;
	char *c1;
	float Adc_data;
	double temp;
	c="ADC_CH1_VAL:";
	c1="ADC_CH1_VAL:";
	delay_init();
	OLED_Init();

	ADC_Test A=ADC_Test();
	ADC_Test A1=ADC_Test(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1,ENABLE,ADC1,GPIOA,GPIO_Pin_2,1);
	show_Str(0,0,8, 16,c);
	show_Str(0,4,8, 16,c1);
	A.Adc_IniT();
	A1.Adc_IniT();
	while(1){
		Clear_OLED(0,2,128,3);
		Clear_OLED(0,6,128,7);
		temp=A.Get_Adc_Average(1,10);	//A.Get_Adc(1);
		OLED_SHOWNumber(0,2,8,16,temp);
		Adc_data=temp*(3.3/4096);
		OLED_SHOWNumber(0,6,8,16,(int)Adc_data);
		Adc_data-=(int)Adc_data;
		show_char(16,6,8,16,'.');
		OLED_SHOWNumber(16,6,8,16,Adc_data*1000);
		
		temp=A.Get_Adc_Average(2,10);	//A.Get_Adc(1);
		OLED_SHOWNumber(64,2,8,16,temp);
		Adc_data=temp*(3.3/4096);
		OLED_SHOWNumber(64,6,8,16,(int)Adc_data);
		Adc_data-=(int)Adc_data;
		show_char(80,6,8,16,'.');
		OLED_SHOWNumber(80,6,8,16,Adc_data*1000);
		delay_ms(250);
	}

}
 