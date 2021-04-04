#include "deal.h"
//#include "uart.h"
//#include "led.h"
#include "delay.h"
#include "PWM.h"
#include "MyWIFI_.h"
#include "usart.h"
//void advance()//前进
//{
//	TIM_SetCompare1(TIM1,6000);
//	TIM_SetCompare2(TIM1,6000);
//}
//void counter()//后退
//{
//	TIM_SetCompare1(TIM1,4000);
//	TIM_SetCompare2(TIM1,4000);
//}
//void left()//左转
//{
//	TIM_SetCompare1(TIM1,5500);
//	TIM_SetCompare2(TIM1,6000);
//}
//void right()//右转
//{
//	TIM_SetCompare1(TIM1,6000);
//	TIM_SetCompare2(TIM1,5500);
//}
//void stop()
//{
//	TIM_SetCompare1(TIM1,5000);
//	TIM_SetCompare2(TIM1,5000);
//}
//void speed_up()
//{
//}

char ANgle_text=23;
#define Angle  ANgle_text
#define Angle_ (Angle*2)

void Draw_food(void)
{
	if(sche_1_flag==1&&Timel_NUM2<=sche_1_time)
		TIM_SetCompare3(TIM4,270-Angle_);
		
	else {
		sche_1_flag=0;
		TIM_SetCompare3(TIM4,7.5*36);
	}
}
void Draw_Water(void)
{
	if(sche_2_flag==1){
		TIM_SetCompare1(TIM4,2000);
		if(sche_3_flag==1){
			TIM_SetCompare2(TIM4,sche_3_class*36);
		}else
		TIM_SetCompare2(TIM4,2400);
	}
	else{ 
		TIM_SetCompare1(TIM4,0);
		if(sche_3_flag==1){
			TIM_SetCompare2(TIM4,sche_3_class*36);
		}else
		TIM_SetCompare2(TIM4,0);
	}
}
void Draw_Air(void)
{
	if(sche_3_flag==1)
		TIM_SetCompare2(TIM4,sche_3_class*36);
	else if(sche_2_flag==1){
		
		}else
		TIM_SetCompare2(TIM4,0);
}
char TDS_SEND[4]={0xFD,0xFD,0xFD,0x00};

void TDS_SEND_FUC(void)
{
	USART2_Send_Str(TDS_SEND,4);
}
char TDS_flag=0;
char Acc_TDS_DATA[5];
//int TDS_DATA_ARR[10];
char TDS_DATA_num=0;
double TDS_DATA;
double TDS_DATA_sum=0;
void TDS_acc(u8 res)
{
	static char temp=0;
	switch(temp){
		case 0:
			if(res==0xfd){
				Acc_TDS_DATA[temp]=res;
				temp=1;
			}
			else temp=0;
			break;
			
		case 1:
			Acc_TDS_DATA[temp]=res;
			temp=2;
			break;
		case 2:
			Acc_TDS_DATA[temp]=res;
			temp=3;
			break;
		
		case 3:
			Acc_TDS_DATA[temp]=res;
			if(res==0xfc){
				
				temp=4;
				TDS_flag=1;
			}else {
				temp=0;
				TDS_flag=0;
			}
			break;	

		case 4:
			Acc_TDS_DATA[temp]=res;
			if(res==0xfd){
				TDS_flag=2;
			}
			else TDS_flag=0;
			
			temp=0;
			break;	
	}
	if(TDS_flag==2){
		
		TDS_DATA_sum+=Acc_TDS_DATA[1]+Acc_TDS_DATA[2]*256;
//		TDS_DATA_ARR[TDS_DATA_num++]=Acc_TDS_DATA[1]+Acc_TDS_DATA[2]*256;
		TDS_DATA=TDS_DATA_sum/(++TDS_DATA_num)/1.0;
		if(TDS_DATA_num>9){
			TDS_DATA_num=0;
//			TDS_DATA=TDS_DATA_sum/10;
			TDS_DATA_sum=0;
		}
		TDS_flag=0;
		Acc_TDS_DATA[1]=Acc_TDS_DATA[2]=0;
	}
	
}


char PH_SEND[9]={0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B,0x00};

void PH_SEND_FUC(void)
{
	USART3_Send_Str(PH_SEND,8);
}
char PH_flag=0;
char Acc_PH_DATA[9];
double PH_DATA_T;
double PH_DATA_PH;

char PH_DATA_num=0;
double PH_DATA_sum=0;
double T_DATA_sum=0;
void PH_acc(u8 res)
{
	static char temp=0;
	switch(temp){
		case 0:
			if(res==0x01){
				Acc_PH_DATA[temp]=res;
				temp=1;
			}
			else temp=0;
			break;
			
		case 1:
			Acc_PH_DATA[temp]=res;
			if(res==0x03){
				
				temp=2;
			}
			else temp=0;
			break;
		case 2:
			Acc_PH_DATA[temp]=res;
			if(res==0x04){
				
				temp=3;
			}
			else temp=0;
			break;
		
		case 3:
			Acc_PH_DATA[temp]=res;
			temp=4;
			break;	

		case 4:
			Acc_PH_DATA[temp]=res;
			temp=5;
			break;
		case 5:
			Acc_PH_DATA[temp]=res;
			temp=6;
			break;
		case 6:
			Acc_PH_DATA[temp]=res;
			temp=0;
			PH_flag=2;
			break;
				
//		case 7:
//			Acc_PH_DATA[temp]=res;
//			if(res==0x8A){
//				temp=8;
//				PH_flag=1;
//			}else {
//				temp=0;
//				PH_flag=0;
//			}
//			break;	
//		case 8:
//			Acc_PH_DATA[temp]=res;
//			if(res==0x29){
//				PH_flag=2;
//			}else {
//				temp=0;
//				PH_flag=0;
//			}
//			break;	

	}
	if(PH_flag==2){
		
		PH_DATA_sum+=(Acc_PH_DATA[6]+Acc_PH_DATA[5]*256)/10.0;
		T_DATA_sum+=(Acc_PH_DATA[4]+Acc_PH_DATA[3]*256)/10.0;
		PH_DATA_num++;
		PH_DATA_T=T_DATA_sum/(PH_DATA_num)/1.0;

		PH_DATA_PH=PH_DATA_sum/(PH_DATA_num)/1.0;
		if(PH_DATA_num>9){
			PH_DATA_num=0;
			PH_DATA_sum=0;
			T_DATA_sum=0;
		}

		
//		PH_DATA_T=(Acc_PH_DATA[4]+Acc_PH_DATA[3]*256)/10.0;
//		PH_DATA_PH=(Acc_PH_DATA[6]+Acc_PH_DATA[5]*256)/10.0;
		PH_flag=0;
		Acc_PH_DATA[1]=Acc_PH_DATA[2]=0;
	}
	
}

