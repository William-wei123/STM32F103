#include "temperation.h"
#include "delay.h"
#include "sys.h"
GPIO_InitTypeDef GPIO_InitStructure;
u8 Data[5]={1,1,1,1,1};
//8bit湿度整数数据+8bit湿度小数数据+8bi温度整数数据+8bit温度小数数据+8bit校验和
unsigned char Humidity[8]="湿度为:";
unsigned char Temperation[8]="温度为:";
/************************
*函数：u8 Judge0_1(void)
*功能：将传回的八字节数据转换为10进制
*作者：陈伟平
**************************/
u8 Judge0_1(void)
{
	u8 temp=0;
	int i;
//	temp<<=1;
	for(i=0;i<8;i++){
		while(!PC6i);//每一个数据开始前等待50us
		delay_us(29);//延时30us判断是0 or 1
		if(PC6i==0){
			temp<<=1;//如果是30微秒后是0，则传回0，否则传回1
		}else{
			temp|=1;
			temp<<=1;
			while(PC6i);//等待70us剩下的高电平过去
		}
	}
	temp>>=1;
	return temp;
}
/*************************
*函数：TemperationSendCmd(void)
*功能：对DHT11发送测试信号
*作者：陈伟平
*************************/
void TemperationSendCmd(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	//输出3.3V电平
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	PC6o=1;											//拉高
	delay_ms(100);									//等待100ms
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	delay_ms(19);									//低电平18ms以上，发送信号
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	delay_us(40);//主机拉高20`40us等待
}


/*************************
*函数：TemperationGetData(void)
*功能：对DHT11接受数据
*返回值：j 表示是否传回有效值  1/0 有效值/无效值
*作者：陈伟平
**************************/
int TemperationGetData(void)
{
	int i,j=3;
	for(i=0;i<5;i++){		//把之前传回的数据清空
		Data[i]=1;
	}
		if(PC6i==0){
		//DHT响应80us
		while(PC6i==0);		//DHT响应80us
		if(PC6i==1){
			while(PC6i);
			for(i=0;i<5;i++){
				Data[i]=Judge0_1();
			}
		}
		if(Data[4]==(Data[0]+Data[1]+Data[2]+Data[3]))j=1;//校验数据是否正确，如果正确返回1，否则返回0；
	}else j=0;
	return j;
}
/*************************
*函数：TXTemperation(void)
*功能：通过串口发送数据至
*返回值：j 表示是否传回有效值  1/0 有效值/无效值
*作者：陈伟平
**************************/

void TXTemperation(void)
{
	int i;
	for(i=0;i<8;i++){
		USART1->DR=Humidity[i];
		while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	}
	USART1->DR=(48+Data[0]/10);		//发送湿度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=48+Data[0]%10;		//发送湿度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR='.';		//发送湿度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=(48+Data[0]/10);		//发送湿度小数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=48+Data[1]%10;		//发送湿度小数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=' ';		//发送空格
	for(i=0;i<8;i++){
		USART1->DR=Temperation[i];
		while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	}
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=(48+Data[2]/10);		//发送温度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=(48+Data[2]%10);		//发送温度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR='.';		//发送湿度整数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=(48+Data[3]/10);		//发送温度小数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
	USART1->DR=48+Data[3]%10;		//发送温度小数
	while((USART1->SR&0X40)==0);//等待发送结束 //读状态，继续
}
