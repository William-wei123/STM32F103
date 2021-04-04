#include "stm32f10x.h"
#include "MPU6050.h"
#include "OLED.h"
#include "bh.h"
u8 Illuminance_data[9];
extern float result_lx;
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

u8 key;
 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
int main(void)
{	
	u8 t=0;
	u8 report=1;			//Ĭ�Ͽ����ϱ�
	u8 ttt=11;
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�	
	delay_init();	//��ʱ��ʼ�� 
	delay_ms(1000);

	MyI2C_Init();
	key=MPU_Init();					//��ʼ��MPU6050//0Ϊ�ɹ�
	BH1750_Init();
	OLED_Init();
//	OLED_SHOWNumber(0,5,8,16,123);//��ʾ����
//		ttt=mpu_dmp_init();
	Clear_OLED(0,0,128,8);
	while(ttt) {
		ttt=mpu_dmp_init();
		OLED_SHOWNumber(0,0,8,16,ttt);//��ʾ����
		OLED_SHOWNumber(64,0,8,16,key);//��ʾ����
		delay_ms(1000);
		Clear_OLED(0,0,128,8);
	}
	while(1)
	{
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
		report=mpu_dmp_get_data(&pitch,&roll,&yaw);
		delay_ms(1000);
		delay_ms(100);
		Start_BH1750();
		delay_ms(180);                                                       //180ms
		Read_BH1750(); 
		Convert_BH1750(); 
		
		 
			
//		Illuminance_data[0]=(int)(result_lx)/10000+'0';                      //65535.1
//		Illuminance_data[1]=(int)(result_lx)%10000/1000+'0';                 //5535
//		Illuminance_data[2]=(int)(result_lx)%10000%1000/100+'0';             //535
//		Illuminance_data[3]=(int)(result_lx)%10000%1000%100/10+'0';          //35	
//		Illuminance_data[4]=(int)(result_lx)%10+'0';
//		Illuminance_data[5]='.';	
//		Illuminance_data[6]=(int)(result_lx*10)%10+'0';
//	    Illuminance_data[7]='l';		
//		Illuminance_data[8]='x';

		OLED_SHOWNumber(0,0,8,16,roll);
		OLED_SHOWNumber(64,0,8,16,pitch);
		OLED_SHOWNumber(0,2,8,16,yaw);
		OLED_SHOWNumber(64,2,8,16,gyrox);
		OLED_SHOWNumber(0,4,8,16,gyroy);
		OLED_SHOWNumber(64,4,8,16,gyroz);
		OLED_SHOWNumber(0,6,8,16,aacx);
		OLED_SHOWNumber(0,6,8,16,aacy);

		delay_ms(500);

		Clear_OLED(0,0,128,8);
	}
}
 