#include "KEY.h"
#include "delay.h"
/***********************
*��������KEY_Init()
*����  ����ʼ������
***********************/

void KEY_Init()										
{
	GPIO_InitTypeDef GPIO_InitStrucure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);		//��PORTA��PortCʱ��ʹ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);							//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_1;		//PC15��
	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPU;		//��������
	//GPIO_InitStructure.GPIO_Speed					�����ö����ٶ�
	GPIO_Init(GPIOC,&GPIO_InitStrucure);			//��ʼ��PA15��
	
//	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_1;			//PC1��
//	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPU;		//��������
//	GPIO_Init(GPIOC,&GPIO_InitStrucure);			//��ʼ����PA 15��һ����������
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_0;			//PA0��
	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPD;		//��������
	GPIO_Init(GPIOA,&GPIO_InitStrucure);			//��ʼ��PA0��
}
/***********************
*��������KEY_Init()
*����  ����ʼ������
***********************/
u8 KEY_Scan()
{
	u8 Temp;
	u8 key;
	key=4;
	Temp=0;
	key=KEY0;
	switch(key){
		case 0:delay_ms(10);
				key=4;
				key=KEY0;
				switch(key){
					case 0:Temp=1;while(KEY0==0);
					break;
					default:break;
				}break;
		default:break;
	}
	key=KEY1;
	switch(key){
		case 0:delay_ms(10);
				key=4;
				key=KEY1;
				switch(key){
					case 0:Temp =2;while(KEY1==0);
					break;
					default:break;

				}break;
		default:break;
	}
	key=WE_UP;
	switch(key){
		case 1:delay_ms(10);
				key=4;
				key=WE_UP;
				switch(key){
					case 1:Temp =3;while(WE_UP==1);
					break;
					default:break;
				}break;
		default:break;
	}
	return Temp;
}
