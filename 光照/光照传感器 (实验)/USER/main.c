#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "key.h"  
#include "bh.h" 
#include "myiic.h"
 
extern float result_lx;

u8 Distance_data[7];
u8 Illuminance_data[9];

u8  Distance_threshold=80;
u16 Illuminance_threshold=100;
u8  Temperature_threshold=25;


 int main(void)
 { 
	u8 i=0;	
	OLED_Init();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                          // 设置中断优先级分组2  
	uart_init(115200);	 	                                                 //串口初始化为115200
	LED_Init();		  		                                                 //初始化与LED连接的硬件接口		
	BH1750_Init();			                                                 //IIC初始化 	
	OLED_Display_On();
	OLED_Refresh_Gram();                                                     //更新显示到OLED	 
	 
	while(1)
	{	
		LED0=!LED0;
		delay_ms(1000);
//		OLED_ShowNum(60,0,1234,6,24);	
//		OLED_ShowModel(0,16,24,24,1,0);
//		OLED_ShowModel(30,16,24,24,1,1);
//		OLED_ShowString(60,16,":",24);
		OLED_Refresh_Gram();                                                 //更新显示到OLED	 	
		delay_ms(100);
		Start_BH1750();
		delay_ms(180);                                                       //180ms
		Read_BH1750(); 
		Convert_BH1750(); 
		
		 
			
		Illuminance_data[0]=(int)(result_lx)/10000+'0';                      //65535.1
		Illuminance_data[1]=(int)(result_lx)%10000/1000+'0';                 //5535
		Illuminance_data[2]=(int)(result_lx)%10000%1000/100+'0';             //535
		Illuminance_data[3]=(int)(result_lx)%10000%1000%100/10+'0';          //35	
		Illuminance_data[4]=(int)(result_lx)%10+'0';
		Illuminance_data[5]='.';	
		Illuminance_data[6]=(int)(result_lx*10)%10+'0';
	    Illuminance_data[7]='l';		
		Illuminance_data[8]='x';
		OLED_ShowString(0,0,&Illuminance_data[i],24);
	}	
}
