#ifndef _LED_H
#define _LED_H
#include "sys.h"
#include "delay.h"
#define LED0 PAout(8)//PA8¿Ú
#define LED1 PDout(2)
//LED0<<=1;
void LED_Init(void);
void LedRun(void);

#endif
