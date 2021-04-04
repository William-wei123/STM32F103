#ifndef _MOTOR_H
#define _MOTOR_H
#include "sys.h"

//motor_1
#define IN0 PAout(0)
#define IN1 PAout(1)
#define IN2 PAout(4)
#define IN3 PAout(5)

#define IN0_H  IN0=1;
#define IN0_L  IN0=0;
#define IN1_H  IN1=1;
#define IN1_L  IN1=0;
#define IN2_H  IN2=1;
#define IN2_L  IN2=0;
#define IN3_H  IN3=1;
#define IN3_L  IN3=0;

//motor_2
#define IN5 PBout(5)
#define IN6 PBout(6)
#define IN7 PBout(7)
#define IN8 PBout(8)

#define IN5_H  IN5=1;
#define IN5_L  IN5=0;
#define IN6_H  IN6=1;
#define IN6_L  IN6=0;
#define IN7_H  IN7=1;
#define IN7_L  IN7=0;
#define IN8_H  IN8=1;
#define IN8_L  IN8=0;




void motor_init(void);
void motor_n(u8 delay);
void motor_z(u8 delay);
void motor_num(u8 tab,u16 num);   //正反转360°的整数倍数
void motor_30_row(u8 tab,u16 row);   //row  30°的整数倍 
void motor_45_row(u8 tab,u16 row);   //row  45°的整数倍 

void motor2_n(u8 delay);
void motor2_z(u8 delay);
void motor2_num(u8 tab,u16 num);   //正反转360°的整数倍数
void motor2_30_row(u8 tab,u16 row);   //row  30°的整数倍 
void motor2_45_row(u8 tab,u16 row);   //row  45°的整数倍 
#endif
