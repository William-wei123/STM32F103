#include "OLED.h"
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"
#include "math.h"
extern u8 explain[72][2];
u8 number[10][16]={0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,
0x08,0x20,0x10,0x10,0xE0,0x0F,0x00,0x00,/*"0",0*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x00,0x00,0x10,0x20,0x10,0x20,
0xF8,0x3F,0x00,0x20,0x00,0x20,0x00,0x00,/*"1",1*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x70,0x30,0x08,0x28,0x08,0x24,
0x08,0x22,0x08,0x21,0xF0,0x30,0x00,0x00,/*"2",2*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x30,0x18,0x08,0x20,0x08,0x21,
0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,/*"3",3*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x00,0x06,0x80,0x05,0x40,0x24,
0x30,0x24,0xF8,0x3F,0x00,0x24,0x00,0x24,/*"4",4*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0xF8,0x19,0x88,0x20,0x88,0x20,
0x88,0x20,0x08,0x11,0x08,0x0E,0x00,0x00,/*"5",5*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0xE0,0x0F,0x10,0x11,0x88,0x20,
0x88,0x20,0x90,0x20,0x00,0x1F,0x00,0x00,/*"6",6*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x18,0x00,0x08,0x00,0x08,0x3E,
0x88,0x01,0x68,0x00,0x18,0x00,0x00,0x00,/*"7",7*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,
0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00,/*"8",8*/
/* (8 X 16 , 宋体 ) */

0x00,0x00,0xF0,0x01,0x08,0x12,0x08,0x22,
0x08,0x22,0x10,0x11,0xE0,0x0F,0x00,0x00,/*"9",9*/
/* (8 X 16 , 宋体 ) */
};

/************************
*函数：void OLED_WDATA(u8 cmd)
*作用：写数据字节
*cmd为数据
************************/
void OLED_WDATA(u8 cmd)
{
	u8 i;
	DC=1;
	for(i=0;i<8;i++){
		SCL=0;
		SDI=cmd>>7;
		cmd<<=1;
		SCL=1;	//上升沿存取数据
		delay_us(1);
	}
	
}
/************************
*函数：void  OLED_WCMD(u8 cmd)
*作用：写命令字节
*cmd为命令
************************/
void  OLED_WCMD(u8 cmd)
{
	u8 i;
	DC=0;
	for(i=0;i<8;i++){
		SCL=0;
		SDI=cmd>>7;
		cmd<<=1;
		SCL=1;
//		delay_us(1);
	}
//	DC=1;	
}
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WCMD(0X8D);  //SET DCDC命令
	OLED_WCMD(0X14);  //DCDC ON
	OLED_WCMD(0XAF);  //DISPLAY ON
}
/***********************
显示16X16大小的字符或图片
*******/
void OLED_SHOW16X16(u8 X,u8 Y,u8 width, u8 hight,char DATA[40][2])
{
	u8 i,j,n;		
	hight=hight/8;		//转换成页码
		
	for(i=Y,j=0;i<Y+hight&&i<8;i++,j++)  
	{  

		OLED_WCMD (0xb0+i);    //设置页地址（0~7）
		OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
		OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
		for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
	} 
	if(Y+hight>7){		
		for(i=0,j=8-Y;i<(Y+hight-8)&&i<8;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
			OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
		}   

	}
}
void OLED_SHOW8X8(u8 X,u8 Y,u8 width, u8 hight,char DATA[8][1])
{
	u8 i,j,n;		
	hight=hight/8;		//转换成页码
		
	for(i=Y,j=0;i<Y+hight&&i<8;i++,j++)  
	{  

		OLED_WCMD (0xb0+i);    //设置页地址（0~7）
		OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
		OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
		for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
	} 
	if(Y+hight>7){		
		for(i=0,j=8-Y;i<(Y+hight-8)&&i<8;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
			OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
		}   

	}
}

/************************
*函数：OLED_SHOWNumber(u8 X,u8 Y,u8 width, u8 hight,u8 c)
*功能：显示16X16数字
*width 数字宽度
*hight 数字高度
*X Y图片起始坐标（Y表示页码）
*c 要显示的数字，c可任意位中间无0数
*****************/
/************************
*函数：OLED_SHOWNumber(u8 X,u8 Y,u8 width, u8 hight,u8 c)
*功能：显示16X16数字
*width 数字宽度
*hight 数字高度
*X Y图片起始坐标（Y表示页码）
*c 要显示的数字，c可任意位中间无0数
*****************/
void OLED_SHOWNumber(u8 X,u8 Y,u8 width, u8 hight,u32 c)//c可任意位中间无0数
{
	u8 i,j,n,num;
	u32 temp;
	u8 	DATA[8][2];
	temp =c;
	for (num=1;temp/10>0;num++){//判断c为几位数
		temp/=10;	
	}
	if(num>1){
		temp=pow(10,(num-1));						//temp=10^(num-1)
		for(i=0;i<2;i++){
			for(n=0;n<8;n++){
				DATA[n][i]=number[c%10][2*n+i];//把数组number[][16]转换成DATA[][2]即偶数位是每一行的第一个元素
			}
		}
		c=c/10;
		OLED_SHOWNumber(X, Y, width,  hight, c);
	}
	else{
		for(i=0;i<2;i++){
			for(n=0;n<8;n++){
				DATA[n][i]=number[c][2*n+i];//把数组number[][16]转换成DATA[][2]即偶数位是每一行的第一个元素
			}
		}
	}
	hight=hight/8;		//转换成页码
		
	for(i=Y,j=0;i<Y+hight&&i<8;i++,j++)  
	{  

		OLED_WCMD (0xb0+i);    //设置页地址（0~7）
		OLED_WCMD ((X+num*width+1)&0x0f);      //设置显示位置—列低地址
		OLED_WCMD (((X+num*width+1)&0xf0)/16|0x10);      //设置显示位置—列高地址   
		for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
	} 
	if(Y+hight>7){		
		for(i=0,j=8-Y;i<(Y+hight-8)&&i<8;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD ((X+num*width+1)&0x0f);      //设置显示位置—列低地址
			OLED_WCMD (((X+num*width+1)&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
		}   

	}
}
//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
//void OLED_DrawPoint(u8 x,u8 y,u8 t)
//{
//	u8 pos,bx,temp=0;
//	if(x>127||y>63)return;//超出范围了.
//	pos=7-y/8;
//	bx=y%8;
//	temp=1<<(7-bx);
//	if(t)OLED_GRAM[x][pos]|=temp;
//	else OLED_GRAM[x][pos]&=~temp;	    
//}

/************************
*显示当个字符
*width 图片宽度
*hight 图片高度
*X Y图片起始坐标
*****************/
//void show_char(u8 X,u8 Y,u8 width, u8 hight,u8 c)
//{
//	u8 ch=c-' ';
//	u8 i,j,n;
//	u8 	DATA[8][2];
//	hight=hight/8;		//转换成页码
//	for(i=0;i<hight;i++){
//		for(n=0;n<width;n++){
//			DATA[n][i]=asc2_1608[ch][2*n+i];//把数组asc2_1608[][16]转换成DATA[][2]即奇数位是每一行的第一个元素//因为逆序取码
//		}
//	}
//	for(i=Y,j=0;i<Y+hight&&i<8;i++,j++)  
//	{  
//		OLED_WCMD (0xb0+i);    //设置页地址（0~7）
//		OLED_WCMD ((X)&0x0f);      //设置显示位置—列低地址
//		OLED_WCMD (((X)&0xf0)/16|0x10);      //设置显示位置—列高地址   
//		for(n=0;n<width;n++)OLED_WDATA(DATA[n][j]); 
//	} 	
//}

//void show_Str(u8 X,u8 Y,u8 width, u8 hight,char *c)
//{
//	u8 i,j;
//	while ((*c)!=0x00){
//		show_char(X,Y,width,hight,*c);
//		X+=width;
//		if(X>=128){
//			Y+=2;
//			X=0;
//		}
//		c++;
//	}
//}
/************************
*显示图片
*width 图片宽度
*hight 图片高度
*X Y图片起始坐标
*****************/
void OLED_SHOW_DRAW(u8 X,u8 Y,u8 width, u8 hight,u8 DRAW[128][8])
{
	u8 i,j,n;	//i表示页码，j表示数组的位置，n表示数组的位置	
	hight=(hight/8);		//转换成页码
		for(i=Y,j=0;i<Y+hight&&i<8;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
			OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<width;n++)OLED_WDATA(DRAW[n][j]); 
		}   
	if(Y+hight>7){
		for(i=0,j=8-Y;i<(Y+hight-8)&&i<8;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD (X&0x0f);      //设置显示位置—列低地址
			OLED_WCMD ((X&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<width;n++)OLED_WDATA(DRAW[n][j]); 
		}   

	}
}
void OLED_SHOW_Explain()
{
	u8 i,j,n;	//i表示页码，j表示数组的位置，n表示数组的位置	
			//转换成页码
		for(i=0,j=0;i<2;i++,j++)  
		{  

			OLED_WCMD (0xb0+i);    //设置页地址（0~7）
			OLED_WCMD (0&0x0f);      //设置显示位置—列低地址
			OLED_WCMD ((0&0xf0)/16|0x10);      //设置显示位置—列高地址   
			for(n=0;n<72;n++)OLED_WDATA(explain[n][j]); 
		}   
}
//清屏
void Clear_OLED(void)
{
	u8 i,n;
	for(i=0;i<8;i++){
		OLED_WCMD (0xb0+i);    //设置页地址（0~7）
		OLED_WCMD (0x00);      //设置显示位置—列低地址
		OLED_WCMD (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WDATA(0x00); 
	}
}
/************************
*函数：Horizontal_Scroll(u8 X1,u8 X2,u8 speed)
*功能：水平翻滚  CMD 为1左移；为0右移
*Y1 右移的上地址（页码）
*Y2 右移的下地址（页码）
*speed 移动速度	000b–5 frames  	001b–64 frames  	010b – 128 frames 		011b – 256 frames 
				100b–3 frames  	101b–4 frames	 	110b – 25 frame   	111b – 2 frame
*作者：陈伟平			
*****************/
void  Horizontal_Scroll(u8 CMD,u8 Y1,u8 Y2,u8 speed)
{
	OLED_WCMD(0x26+CMD);	//开启翻滚指令
	OLED_WCMD(0x00);		//必走流程
	OLED_WCMD(Y1);		
	OLED_WCMD(speed);
	OLED_WCMD(Y2);
	OLED_WCMD(0x00);//必走流程
	OLED_WCMD(0xff);//必走流程
	OLED_WCMD(0x2F);//开启翻滚指令
}
/************************
*函数：Vertical_Horizontal_Scroll(u8 X1,u8 X2,u8 speed)
*功能：水平翻滚  CMD 为1左移；为0右移
*Y1 右移的上地址（页码）
*Y2 右移的下地址（页码）
*speed 移动速度	000b–5 frames  	001b–64 frames  	010b – 128 frames 		011b – 256 frames 
				100b–3 frames  	101b–4 frames	 	110b – 25 frame   	111b – 2 frame
*作者：陈伟平			
*****************/

void  Vertical_and_Horizontal_Scroll(u8 CMD,u8 Y1,u8 Y2,u8 speed)
{
	OLED_WCMD(0xA3);		//设置垂直翻滚地址指令
	OLED_WCMD(Y1*8);		//设置垂直翻滚的首地址
	OLED_WCMD(Y2*8);		//设置垂直翻滚的末地址（大于首地址）
	OLED_WCMD(0x29+CMD);	//开启翻滚指令
	OLED_WCMD(0x00);		//必走流程
	OLED_WCMD(Y1);		
	OLED_WCMD(speed);
	OLED_WCMD(Y2);
	OLED_WCMD(8);			//设置垂直偏移量
	OLED_WCMD(0x2F);//开启翻滚指令
}

void OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	OLED_WCMD(0xAE);//关闭显示
	OLED_WCMD(0xD5);//设置时钟分频因子，振荡频率
	OLED_WCMD(80);	//[3:0]，分频因子；[7：4],振荡频率    //0????
	OLED_WCMD(0xA8);//设置驱动路数
	OLED_WCMD(0X3F);//默认0X3F(1/64)
	OLED_WCMD(0xD3);//设置显示偏移
	OLED_WCMD(0X00);//默认为0
	
	OLED_WCMD(0x40);//设置显示开始行【5：0】，行数
	
	OLED_WCMD(0x8D);//电荷泵设置
	OLED_WCMD(0x14);//bit2,开启/关闭
	OLED_WCMD(0x20);//设置内存地址模式
	OLED_WCMD(0x02);//[1:0],00,列地址模式；01，行地址模式；10，页地址模式；默认10；
	OLED_WCMD(0xA1);//段重定义设置，bit0:0,0->0;1,0-.127;
	OLED_WCMD(0xC8);//设置COM扫描方向：bit3:0,普通模式；1，重定义模式 COM[N-1]->COM0;N:驱动路数
	//0xC8,从上扫到下 即上面为第0页，0xC0从下扫到上，即下面为第0页
	OLED_WCMD(0xDA);//设置COM硬件引脚配置
	OLED_WCMD(0x12);//[5:4]配置
	
	OLED_WCMD(0x81);//对比度设置
	OLED_WCMD(0xEF);//1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WCMD(0xD9);//设置预充电周期
	OLED_WCMD(0xf1);//[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WCMD(0xDB);//设置VCOMH 电压倍率
	OLED_WCMD(0x30);//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	
	OLED_WCMD(0xA4);//全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WCMD(0xA6);//设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	OLED_WCMD(0xAF);//开启显示
}
