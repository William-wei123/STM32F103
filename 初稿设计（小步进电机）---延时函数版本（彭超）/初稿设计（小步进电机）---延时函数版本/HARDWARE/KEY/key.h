#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 


#define KEY1 PBin(13)   	//
#define KEY2 PBin(14)	//
#define KEY3 PBin(15)	//

#define rain PAin(6)   	//
#define sun  PAin(7)	//


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
