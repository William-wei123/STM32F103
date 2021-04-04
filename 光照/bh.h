#ifndef __BH_H
#define __BH_H	 
#include "sys.h"

#define BH1750_Addr 0x46          //iic从机地址
#define BH1750_ON   0x01          //启动
#define BH1750_CON  0x10          //连续读取
#define BH1750_ONE  0x20          //一次读取
#define BH1750_RSET 0x07          //重置

void BH1750_Init(void);			//IO初始化
void Start_BH1750(void);	  //上电、设置、清除数据寄存器
void Read_BH1750(void);     //连续读取内部寄存器数据              
void Convert_BH1750(void);  //数据转化









#endif

