#include "usart.h"
#include "sys.h"
#include "LaserPID.h"

/*****************************PID相关定义************************************/
u8 flymode;
//extern struct _auto fly_state;
struct PID_Height height;//高度环结构体
struct PID_Height speed;//速度环结构体 
u16 expect_height=1000;	// 预期高度
float height_output;//高度环输出
float height_ctrl_output;//内环输出给油门   speed内环
float ultra_distance_lpf;//滤波之后的实际高度值
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
	LIMIT 原理：当x < min时， 返回 min
				当x > min时，返回 x 和 max 之间较小的。
				也就是说，无论如何都不可能是最大的
*/
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**************************************************************************/

float Dbug_Set_Speed  = 0.0;

void PID_Height_init(void)//参数初始化
{
                        // 原数据   // 0921		// 0228		// 0320		// 0324
	speed.kp = 0.6f;	// 0.6      // 0.6  	// 0.6		// 0.6f		// 0.6f		// 单调P，合理范围很大，结合调，0.7出现抖动，0.5响应慢
	speed.ki = 0;		// 0        // 0.01 	// 0.001	// 0		// 0		// 不能过大，累积效果
    speed.kd = 0.005f;	// 0.05    	// 0.05 	// 0.05		// 0.005f	// 0.005f	// 不得大于0.2，明显抖动，太小抑制效果不明显	 

    height.kp = 3.5f;	// 4.10f    // 4.25f	// 4.5f		// 3.5f		// 3.5f
	height.ki = 0.22f;	// 0.0005f  // 0.0f		// 0.0005f	// 0.22f	// 0.22f	// 加积分越飞越高（低）
    height.kd = 4;		// 4.5      // 4.0		// 4.0		// 5		// 4

}

void height_ctrl(float T)
{  
    static u8 flag = 0;//开启定高
	float ultra_dis_tmp;	
//	static float tmp_kec = 0;
//	float fm = 0;	
	
	// ultra_distance： 当前高度
	// ultra_dis_tmp： 
	ultra_dis_tmp = Moving_Median(1,50,ultra_distance);//
	//应该是这里有问题
	if( ultra_dis_tmp < 2000 )						//少于4m为有效值
	{
		// 当前高度 - 前一次高度
		if( ABS(ultra_dis_tmp - ultra_distance_lpf) < 10 )  //求绝对值
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
	
	//ultra_distance_lpf： 当前高度经过滤波之后的值
	height.err=(expect_height - ultra_distance_lpf)/10.0f;//求误差

	if(1 == flymode && 0 == flag)
	{
		flag = 1;
		speed.integ = 0;//防止积分饱和
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
 	  
//	if(height_output>=450)//抗饱和
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


  
	//height.integ：
	height.integ=limit(height.integ,-150,150);
	// 外环（高度环输出）
	height_output=height.kp*height.err+height.ki*height.integ/2.0f+height.kd*(height.err-height.err_last)/T;
	height.err_last=height.err;
	height_output = limit(height_output,-300,300);	// 限幅
	//height_ctrl_output = limit(height_output,-300,300)+100;    //内环速度不够，补充油门
}
float ultra_speed_pid = 0.0;

// 50ms duty
void speed_ctrl(float T)
{      
	float ultra_sp_tmp;
	static int thr = 0;
	static int thr_t = 0;
	thr_t ++;
	// ultra_delta 是两次测量的高度差
	ultra_sp_tmp = Moving_Median(1,5,ultra_delta); //ultra_delta/T;

	// ultra_sp_tmp： 近五次高度差的中值， 即相当于一个滤波处理
	if( ABS(ultra_sp_tmp) < 10 )
	{
		// ultra_speed： 
		ultra_speed_pid += ( 1 / ( 1 + 1 / ( 3 *3.14f *T ) ) ) * ( (float)(ultra_sp_tmp) - ultra_speed_pid );
	}
	else
	{
		ultra_speed_pid += ( 1 / ( 1 + 1 / ( 1.0f *3.14f *T ) ) ) * ( (float)(ultra_sp_tmp) - ultra_speed_pid );
	}

    speed.err=height_output-ultra_delta;	//height_output  Dbug_Set_Speed： 内环期望  调节内环,外环置零
	
	// 是不是随着时间的增加，电池电量减少，然后增加thr保证高度
/*
    if((thr_t >= 4000 && 1 == flymode))
	{   
		thr_t = 0;
		thr += 20;
	  if(thr >= 100)
		thr = 100;
	}// 40s	// 4000 * 50 ms
	
	if(1 == fly_state.down)		// 降落
	{
		thr = 0;
	}
*/	
    
//	if(height_ctrl_output>=300)//抗饱和
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

	   
	speed.integ=limit(speed.integ,-100,100);//积分限幅 
	// height_ctrl_output： 最终输出
	height_ctrl_output=speed.kp*speed.err+speed.ki*speed.integ/2.0f+speed.kd*(speed.err-speed.err_last)/T; 	
	speed.err_last=speed.err;
	   
  // height_output=limit(height_ctrl_output,-300,300)+100+thr; //-100 300			// 外环输出
	height_ctrl_output = limit(height_ctrl_output,-300,300)+100;		// speed 输出给到最终输出   
	//height_ctrl_output=limit(height_ctrl_output,-300,300)+100+thr; //-100 300

}

void HEIGHT_CTRL(float time)
{  
	 
	  height_ctrl(time);	//周期为100MS	// 高度环--外环，
	  speed_ctrl(time);		//速度环--内环  高度环的输出 -- 速度环的输入
}



 
float Moving_Median(u8 item,u8 width_num,float in)	// 形参是：1,  5,  ultra_distance
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
		// 下面这个if 语句是当width_num<=1时， med_fil_cnt[item] = 0;
		if( ++med_fil_cnt[item] >= width_num )	
		{
			med_fil_cnt[item] = 0;	//med_fil_cnt[item]  = 1 或者 0
		}
		
		med_filter_tmp[item][ med_fil_cnt[item] ] = in;	// in = ultra_distance
		/*
			med_filter_tmp[item] 这个数组一共就只赋值了一次，因此
		*/
		
		for(i=0;i<width_num;i++)
		{
			tmp[i] = med_filter_tmp[item][i];
		}
		
		// 这他妈不是冒泡排序吗
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
	
		// 返回值是tep数组中间的值
		return ( tmp[(u16)width_num/2] );
	}
}
