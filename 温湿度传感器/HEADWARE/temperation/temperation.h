#ifndef TEMPERATION__H
#define TEMPERATION__H
#include "sys.h"
#define PC6o PCout(6)
#define PC6i PCin(6)
extern GPIO_InitTypeDef GPIO_InitStructure;
extern u8 Data[5];
//unsigned char Humidity[8]="湿度为:";
//unsigned char Temperation[8]="温度为:";

void temperation_Init(void);
void TemperationSendCmd(void);
int TemperationGetData(void);
u8 Judge0_1(void);
void TXTemperation(void);


#endif
