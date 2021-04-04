#include "usart.h"
#include "sys.h"
#include "LaserPID.h"
u16 ultra_distance,ultra_distance_old;
s16 ultra_delta;//高度差
char Dbug11 = 0;
int com_data_tmp;
float Roll,Pitch,Yaw;    
#define MY_PPPIII   3.14159f
#define ONE_PI   (3.14159265)
s8 ultra_start_f;
u8 ultra_ok = 0;

/***********函数声明及定义*********************/
float my_cos(double rad);
double my_sin(double rad); 
double mx_sin(double rad);

/********************************************/

void Ultra_Get(int com_data)  //激光数据处理函数
{
	static int  ultra_tmp;
	double Pitch_Rad,Roll_Rad;
	Pitch_Rad=(Pitch*MY_PPPIII)/180;
	Roll_Rad=(Roll*MY_PPPIII)/180;
	
//	com_data_tmp = com_data;
//	if( ultra_start_f == 1 )
//	{
//		ultra_tmp = com_data;
//		ultra_start_f = 2;
//		
//		//Dbug11 = 1;
//	}
	ultra_tmp=com_data;
	 if( ultra_start_f == 1 )
	{
		Pitch_Rad=my_cos(Pitch_Rad);
		Roll_Rad=my_cos(Roll_Rad);
		ultra_distance = (com_data)*Pitch_Rad*Roll_Rad;
		if(ultra_distance>1800) //补偿错误
		{
			ultra_distance = ultra_tmp;
			if(ultra_distance>1800)//还是错误
				ultra_distance = ultra_distance_old;
		}
		if(ultra_distance_old - ultra_distance>250)
			ultra_distance =ultra_distance_old;
		    ultra_start_f = 0;
		    ultra_ok = 1;
		
		
	}
	
	ultra_delta = ultra_distance - ultra_distance_old;//高度差
	//ultra_delta = ultra_delta;
	
	ultra_distance=0.9*ultra_distance+0.1*ultra_distance_old;//低通滤波后的值
	ultra_distance_old = ultra_distance;	
}


float my_cos(double rad)
{
	s8 flag = 1;
	rad += ONE_PI/2.0;

	if (rad >= ONE_PI)
	{
		flag = -1;
		rad -= ONE_PI;
	}

	return my_sin(rad)*flag;
}

double my_sin(double rad)
{
	s8 flag = 1;

	if (rad >= ONE_PI)
	{
		rad -= ONE_PI;
		flag = -1;
	}

	return mx_sin(rad) * flag;
    
}

double mx_sin(double rad)
{   
	double sine;
	if (rad < 0)
		sine = rad*(1.27323954f + 0.405284735f * rad);
	else
		sine = rad * (1.27323954f - 0.405284735f * rad);
	if (sine < 0)
		sine = sine*(-0.225f * (sine + 1) + 1);
	else
		sine = sine * (0.225f *( sine - 1) + 1);
	return sine;
}
