#include "wdg.h"
void IWDG_Init(u8 PRr,u16 RL)//初始化独立看门狗
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//使能对寄存器IWDG_PR和IWDG_RLR的写功能
	IWDG_SetPrescaler(PRr);//设置预分频
	IWDG_SetReload(RL);//设置重转载值
	IWDG_ReloadCounter();//按照IWDG重转载寄存器的值重装IWDG计数器
	IWDG_Enable();//使能IWDG
	
}

void IWDG_Feed(void)
{
	IWDG->KR=0xAAAA;//reload
}
