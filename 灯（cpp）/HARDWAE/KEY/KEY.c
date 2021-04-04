#include "KEY.h"
#include "delay.h"
/***********************
*函数名：KEY_Init()
*功能  ：初始化按键
***********************/

void KEY_Init()										
{
	GPIO_InitTypeDef GPIO_InitStrucure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);		//对PORTA和PortC时钟使能
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);							//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_1;		//PC15口
	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPU;		//上拉输入
	//GPIO_InitStructure.GPIO_Speed					好像不用定义速度
	GPIO_Init(GPIOC,&GPIO_InitStrucure);			//初始化PA15口
	
//	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_1;			//PC1口
//	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPU;		//上拉输入
//	GPIO_Init(GPIOC,&GPIO_InitStrucure);			//初始化和PA 15口一样上拉输入
	
	GPIO_InitStrucure.GPIO_Pin=GPIO_Pin_0;			//PA0口
	GPIO_InitStrucure.GPIO_Mode=GPIO_Mode_IPD;		//下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStrucure);			//初始化PA0口
}
/***********************
*函数名：KEY_Init()
*功能  ：初始化按键
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
