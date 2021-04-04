#ifndef __LORA_H
#define __LORA_H	 
#include "sys.h"
#include "uart.h"
#include "adc.h"
#include "dht11.h"

#define M0    PBout(15)// PA6
#define M1    PBout(14)// PA7	
#define AUX   PBin(13)//    

void Lora_Init(u32 bat);//≥ı ºªØ
void Read_MPU6050_DATA(void);
void Lora_data_send(void);


		 				    
#endif
