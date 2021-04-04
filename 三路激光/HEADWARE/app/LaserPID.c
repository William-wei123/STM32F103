#include "usart.h"
#include "sys.h"
#include "LaserPID.h"

/*****************************PID��ض���************************************/
u8 flymode;
//extern struct _auto fly_state;
struct PID_Height height;//�߶Ȼ��ṹ��
struct PID_Height speed;//�ٶȻ��ṹ�� 
u16 expect_height=1000;	// Ԥ�ڸ߶�
float height_output;//�߶Ȼ����
float height_ctrl_output;//�ڻ����������   speed�ڻ�
float ultra_distance_lpf;//�˲�֮���ʵ�ʸ߶�ֵ
/**************************************************************************/


/**************************************************************************/
#define MED_WIDTH_NUM 11
#define MED_FIL_ITEM  2

float med_filter_tmp[MED_FIL_ITEM][MED_WIDTH_NUM ];
float med_filter_out[MED_FIL_ITEM];

u8 med_fil_cnt[MED_FIL_ITEM];
float Moving_Median(u8 item,u8 width_num,float in);

#define ABS(x) ( (x)>0?(x):-(x) )
/*
	LIMIT ԭ����x < minʱ�� ���� min
				��x > minʱ������ x �� max ֮���С�ġ�
				Ҳ����˵��������ζ�������������
*/
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**************************************************************************/

float Dbug_Set_Speed  = 0.0;

void PID_Height_init(void)//������ʼ��
{
                        // ԭ����   // 0921		// 0228		// 0320		// 0324
	speed.kp = 0.6f;	// 0.6      // 0.6  	// 0.6		// 0.6f		// 0.6f		// ����P������Χ�ܴ󣬽�ϵ���0.7���ֶ�����0.5��Ӧ��
	speed.ki = 0;		// 0        // 0.01 	// 0.001	// 0		// 0		// ���ܹ����ۻ�Ч��
    speed.kd = 0.005f;	// 0.05    	// 0.05 	// 0.05		// 0.005f	// 0.005f	// ���ô���0.2�����Զ�����̫С����Ч��������	 

    height.kp = 3.5f;	// 4.10f    // 4.25f	// 4.5f		// 3.5f		// 3.5f
	height.ki = 0.22f;	// 0.0005f  // 0.0f		// 0.0005f	// 0.22f	// 0.22f	// �ӻ���Խ��Խ�ߣ��ͣ�
    height.kd = 4;		// 4.5      // 4.0		// 4.0		// 5		// 4

}

void height_ctrl(float T)
{  
    static u8 flag = 0;//��������
	float ultra_dis_tmp;	
//	static float tmp_kec = 0;
//	float fm = 0;	
	
	// ultra_distance�� ��ǰ�߶�
	// ultra_dis_tmp�� 
	ultra_dis_tmp = Moving_Median(1,50,ultra_distance);//
	//Ӧ��������������
	if( ultra_dis_tmp < 2000 )						//����4mΪ��Чֵ
	{
		// ��ǰ�߶� - ǰһ�θ߶�
		if( ABS(ultra_dis_tmp - ultra_distance_lpf) < 10 )  //�����ֵ
		{
			ultra_distance_lpf += ( 1 / ( 1 + 1 / ( 2.0f *3.14f *T ) ) ) * (ultra_dis_tmp - ultra_distance_lpf) ;
		}
		else if( ABS(ultra_dis_tmp - ultra_distance_lpf) < 20 )
		{
			ultra_distance_lpf += ( 1 / ( 1 + 1 / ( 1.5f *3.14f *T ) ) ) *(ultra_dis_tmp- ultra_distance_lpf) ;
		}
		else if( ABS(ultra_dis_tmp - ultra_distance_lpf) < 40 )
		{
			ultra_distance_lpf += ( 1 / ( 1 + 1 / ( 1.0f *3.14f *T ) ) ) *(ultra_dis_tmp- ultra_distance_lpf) ;
		}
		else
		{
			ultra_distance_lpf += ( 1 / ( 1 + 1 / ( 0.8f *3.14f *T ) ) ) *(ultra_dis_tmp- ultra_distance_lpf) ;
		}
	}
//	else
//	{
//		
//	}	
	
	//ultra_distance_lpf�� ��ǰ�߶Ⱦ����˲�֮���ֵ
	height.err=(expect_height - ultra_distance_lpf)/10.0f;//�����

	if(1 == flymode && 0 == flag)
	{
		flag = 1;
		speed.integ = 0;//��ֹ���ֱ���
	}
	
//  	
//	if((height.err >= 50) && (0 == flag))
//	{
//			
//	height.kp = 3.25;
//	}
//	
//	else
//	{
//		 flag = 1;
//	 height.kp=4.5;
//	}
 	  
//	if(height_output>=450)//������
//	{ 
//		if(height.err<0)
//		height.integ+=height.err;	   
//	}	  
//	else if(height_output<-450)
//	{
//		if(height.err>0)
//		height.integ+=height.err;
//	}
//	else
//		height.integ+=height.err;

  if((height.err>=-10)&&(height.err<=10))
	{
			height.integ+=height.err*T*0.1;
	}
	else
	{
			height.integ+=height.err*T*0.01;
			//speed.integ = 0;
	}


  
	//height.integ��
	height.integ=limit(height.integ,-150,150);
	// �⻷���߶Ȼ������
	height_output=height.kp*height.err+height.ki*height.integ/2.0f+height.kd*(height.err-height.err_last)/T;
	height.err_last=height.err;
	height_output = limit(height_output,-300,300);	// �޷�
	//height_ctrl_output = limit(height_output,-300,300)+100;    //�ڻ��ٶȲ�������������
}
float ultra_speed_pid = 0.0;

// 50ms duty
void speed_ctrl(float T)
{      
	float ultra_sp_tmp;
	static int thr = 0;
	static int thr_t = 0;
	thr_t ++;
	// ultra_delta �����β����ĸ߶Ȳ�
	ultra_sp_tmp = Moving_Median(1,5,ultra_delta); //ultra_delta/T;

	// ultra_sp_tmp�� ����θ߶Ȳ����ֵ�� ���൱��һ���˲�����
	if( ABS(ultra_sp_tmp) < 10 )
	{
		// ultra_speed�� 
		ultra_speed_pid += ( 1 / ( 1 + 1 / ( 3 *3.14f *T ) ) ) * ( (float)(ultra_sp_tmp) - ultra_speed_pid );
	}
	else
	{
		ultra_speed_pid += ( 1 / ( 1 + 1 / ( 1.0f *3.14f *T ) ) ) * ( (float)(ultra_sp_tmp) - ultra_speed_pid );
	}

    speed.err=height_output-ultra_delta;	//height_output  Dbug_Set_Speed�� �ڻ�����  �����ڻ�,�⻷����
	
	// �ǲ�������ʱ������ӣ���ص������٣�Ȼ������thr��֤�߶�
/*
    if((thr_t >= 4000 && 1 == flymode))
	{   
		thr_t = 0;
		thr += 20;
	  if(thr >= 100)
		thr = 100;
	}// 40s	// 4000 * 50 ms
	
	if(1 == fly_state.down)		// ����
	{
		thr = 0;
	}
*/	
    
//	if(height_ctrl_output>=300)//������
//	{ 
//		if(speed.err<0)
//			speed.integ+=speed.err;	   
//	}	  
//	else if(height_ctrl_output<=-80)
//	{
//		if(speed.err>0)
//		speed.integ+=speed.err;

//	}     
//	else
//		speed.integ+=speed.err; 	
	if((speed.err>=-10)&&(speed.err<=10))
	{
			speed.integ+=speed.err*T*0.1;
	}
	else
	{
			speed.integ+=speed.err*T*0.01;
	}

	   
	speed.integ=limit(speed.integ,-100,100);//�����޷� 
	// height_ctrl_output�� �������
	height_ctrl_output=speed.kp*speed.err+speed.ki*speed.integ/2.0f+speed.kd*(speed.err-speed.err_last)/T; 	
	speed.err_last=speed.err;
	   
  // height_output=limit(height_ctrl_output,-300,300)+100+thr; //-100 300			// �⻷���
	height_ctrl_output = limit(height_ctrl_output,-300,300)+100;		// speed ��������������   
	//height_ctrl_output=limit(height_ctrl_output,-300,300)+100+thr; //-100 300

}

void HEIGHT_CTRL(float time)
{  
	 
	  height_ctrl(time);	//����Ϊ100MS	// �߶Ȼ�--�⻷��
	  speed_ctrl(time);		//�ٶȻ�--�ڻ�  �߶Ȼ������ -- �ٶȻ�������
}



 
float Moving_Median(u8 item,u8 width_num,float in)	// �β��ǣ�1,  5,  ultra_distance
{
	u8 i,j;
	float t;
	float tmp[MED_WIDTH_NUM];	// tmp[11]
	
	if(item >= MED_FIL_ITEM || width_num >= MED_WIDTH_NUM )
	{
		return 0;
	}
	else
	{
		// �������if ����ǵ�width_num<=1ʱ�� med_fil_cnt[item] = 0;
		if( ++med_fil_cnt[item] >= width_num )	
		{
			med_fil_cnt[item] = 0;	//med_fil_cnt[item]  = 1 ���� 0
		}
		
		med_filter_tmp[item][ med_fil_cnt[item] ] = in;	// in = ultra_distance
		/*
			med_filter_tmp[item] �������һ����ֻ��ֵ��һ�Σ����
		*/
		
		for(i=0;i<width_num;i++)
		{
			tmp[i] = med_filter_tmp[item][i];
		}
		
		// �����費��ð��������
		for(i=0;i<width_num-1;i++)
		{
			for(j=0;j<(width_num-1-i);j++)
			{
				if(tmp[j] > tmp[j+1])
				{
					t = tmp[j];
					tmp[j] = tmp[j+1];
					tmp[j+1] = t;
				}
			}
		}
	
		// ����ֵ��tep�����м��ֵ
		return ( tmp[(u16)width_num/2] );
	}
}
