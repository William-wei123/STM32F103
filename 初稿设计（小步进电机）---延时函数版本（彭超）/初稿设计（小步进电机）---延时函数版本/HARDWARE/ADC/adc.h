#ifndef _ADC_H
#define _ADC_H
#include "sys.h"


void ADC1_init(void);
short get_adcAverage(u8 ch,u8 times);  //取采样10次的平均值

#endif
