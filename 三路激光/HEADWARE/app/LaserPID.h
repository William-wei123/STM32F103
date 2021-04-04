#ifndef _LaserPID_H
#define _LaserPID_H
#include "sys.h"
struct PID_Height
{ 
  float kp,ki,kd;//PIDϵ��
  float err;//��ǰ���
  float err_last;//�´����浱ǰ���	]
  float integ;//������
};
#define limit(x,min,max) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

extern float height_ctrl_output;
extern u16 ultra_distance;
extern s16 ultra_delta;
extern s8 ultra_start_f;
extern u16 expect_height;	// Ԥ�ڸ߶�
extern struct PID_Height height;//�߶Ȼ��ṹ��
extern struct PID_Height speed;//�ٶȻ��ṹ�� 
void Ultra_Get(int com_data);  //�������ݴ�����

void PID_Height_init(void);
void HEIGHT_CTRL(float time);

#endif
