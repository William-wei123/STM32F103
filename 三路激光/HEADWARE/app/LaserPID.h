#ifndef _LaserPID_H
#define _LaserPID_H
#include "sys.h"
struct PID_Height
{ 
  float kp,ki,kd;//PID系数
  float err;//当前误差
  float err_last;//下次误差保存当前误差	]
  float integ;//积分器
};
#define limit(x,min,max) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

extern float height_ctrl_output;
extern u16 ultra_distance;
extern s16 ultra_delta;
extern s8 ultra_start_f;
extern u16 expect_height;	// 预期高度
extern struct PID_Height height;//高度环结构体
extern struct PID_Height speed;//速度环结构体 
void Ultra_Get(int com_data);  //激光数据处理函数

void PID_Height_init(void);
void HEIGHT_CTRL(float time);

#endif
