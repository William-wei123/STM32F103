#include "wdg.h"
void IWDG_Init(u8 PRr,u16 RL)//��ʼ���������Ź�
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	IWDG_SetPrescaler(PRr);//����Ԥ��Ƶ
	IWDG_SetReload(RL);//������ת��ֵ
	IWDG_ReloadCounter();//����IWDG��ת�ؼĴ�����ֵ��װIWDG������
	IWDG_Enable();//ʹ��IWDG
	
}

void IWDG_Feed(void)
{
	IWDG->KR=0xAAAA;//reload
}
