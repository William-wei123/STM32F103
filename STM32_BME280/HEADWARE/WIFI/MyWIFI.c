#include "MyWIFI_.h"
#include "usart.h"
#include "delay.h"
#include "math.h"
#include "OLED.h"
char *COM_AT="AT\r\n";
char *COM_CWMODE1="AT+CWMODE=1\r\n";
char *COM_RST="AT+RST\r\n";

char *COM_Conect="AT+CWJAP=\"113_IN\",\"113inside\"\r\n";				//连接指定WiFi    	CWP	zxcvbnmasdfghjkl
char *COM_Conect_Sever="AT+CIPSTART=\"TCP\",\"192.168.2.222\",8001\r\n";//连接指定服务器和端口号192.168.136.1		
char COM_DATA_Lenght[20]="AT+CIPSEND=";									//用于数据组合
char ALL_Data_buf[200];													
/*********************************
功能：校验指令是否发送成功
返回：发送成功返回1，失败0
作者：cwp
说明：利用WIFI模块的回传机制，每发送一条指令，会回传该条指令，如果成功会在后面第3or12or14位回传OK
*****************************/
char WIFI_XIAOYANG(char *COM)
{
	char i,num,temp=0;
	//USART_RX_STA=0;
	for(num=0;(*(COM+num)!='\0');num++);
	for (i=0;(*(COM+i)!='\0')&&*(COM+i)==*(USART_RX_BUF+i);i++);
	if(i+1!=num)												//WIFI 回传数据为发送过去的数据+0xOD（\r）,0xOD(\r),0x(\n)
		temp=0;
	else{
		for (;num<USART_RX_STA;num++){
			if((*(USART_RX_BUF+num)=='O'&&*(USART_RX_BUF+num+1)=='K')||*(USART_RX_BUF+num)==62){
				Clear_OLED(0,0,128,8);
				temp = 1;
			}
			else if(temp==0&&(num+1)==USART_RX_STA){
				Clear_OLED(0,0,128,8);
				show_Str(0,0,8,16,USART_RX_BUF);
				for(;i<USART_RX_STA;i++)
					if((*(USART_RX_BUF+i)=='l'&&*(USART_RX_BUF+i+1)=='i')&&*(USART_RX_BUF+i+12)=='v'){
						WIFI_Send(COM_Conect_Sever);
					}
			}//可以显示出为什么错了，通过显示USART_RX_BUFWIFI_Send(COM_Conect_Sever);

		}
//		if(*(USART_RX_BUF+num+3)=='O'||*(USART_RX_BUF+num+12)=='O'||*(USART_RX_BUF+num+14)=='O'||*(USART_RX_BUF+81)=='O'||*(USART_RX_BUF+num+1)==62)		//WIFI回传数据的一些格式，成功发送指令会在指定位置回传OK
//			return 1;
	}
	return temp;
}
/*********************************
功能：发送指令
作者：cwp

*****************************/
void WIFI_Send(char *COM)
{
	int i=1;
	for (;*(COM+i)!='\0';i++);

	USART_RX_BUF[0]=USART_RX_BUF[1]=0;		
	while(WIFI_XIAOYANG(COM)!=1)
	{
		USART_RX_STA=0;
		USART_Send_Str(COM,4);
		Send_New_Line();
		delay_ms(50);
		if(COM==COM_Conect||COM==COM_Conect_Sever||COM==COM_RST)
			delay_ms(10000);
	}

}

/****************************
功能：将整形数转为字符
作者：cwp
*******************************/
void NUM_TO_STR(int NUM,char *STR)
{
	char temp=0;
	int c=NUM;
	for (temp=1;c/10>0;temp++){		//判断c为几位数
		c/=10;	
	}
	c=NUM;
	*(STR+temp)='\r';
	*(STR+temp+1)='\n';
	*(STR+temp+2)='\0';
	for (;temp>0;temp--){
		//cc=pow(10,(temp-1));		//cc=10^(temp-1)
		*(STR+temp-1)=c%10+48;
		c=c/10;
	
	}
//	if (temp>1){
//		cc=pow(10,(temp-1));		//cc=10^(temp-1)
//		
//		*STR=NUM/cc+48;
//		if(NUM%cc>=cc)					//解决像100001这样的数字直接0不见的问题
//			NUM_TO_STR(NUM%cc,STR+1);
//		else{
//			*(STR+1)=0+48;
//			if(NUM%cc>=(cc/10))
//				NUM_TO_STR(NUM%cc,STR+2);
//		}
//	}
//	else {
//		
//		*STR=c+48;
//		*(STR+1)='\r';
//		*(STR+2)='\n';
//		*(STR+3)='\0';
//	}
	
}

/****************************
功能：将字符转为int类型（precision精度可以控制）
作者：cwp


*******************************/
int char_To_int(char *DATA)
{
	char temp,temp_1;
	int Len=0;
	for(temp=0;*(DATA+temp)!='\0';temp++);
	for(temp_1=0;temp!=0;temp--,temp_1++)
		Len=(*(DATA)-48)*pow(10,temp-1);
	return Len;

}
	
/****************************
功能：将double类型转为字符（precision精度可以控制）
作者：cwp


*******************************/
void Duoble_TO_STR(double NUM,char *STR,char precision)
{
	char temp=0,Dot_Flag=0,i=0;
	double c=NUM*pow(10,precision);			//保留2位小数
	for (temp=1;(int)c/10>0;temp++){		//判断c的整数部分为几位数
		c/=10;	
	}
	c=NUM*pow(10,precision);
	*(STR+temp+1)='\r';
	*(STR+temp+2)='\n';
	*(STR+temp+3)='\0';
	for (;temp>0;temp--,i++){
		//cc=pow(10,(temp-1));		//cc=10^(temp-1)
		if(i<precision){
			*(STR+temp)=(int)c%10+48;
			c=c/10;	
		}else if(i==precision&&Dot_Flag==0){
			*(STR+temp)='.';
			Dot_Flag=1;
			temp++;
			continue;
		}else {
			*(STR+temp-1)=(long)c%10+48;
			c=c/10;
		}
		
	
	}

}
void DATA_To_COM(char *DAT)
{
	int num;
	for(num=0;(*(DAT+num)!='\0');num++);//获取数据长度
	NUM_TO_STR(num,(COM_DATA_Lenght+11));
}
u16 Send_flag=0;		//==2表示接收模式  
void WIFI_Send_DATA(char *DAT)
{

	USART_Send_Str("AT\r\n",8);

	DATA_To_COM(DAT);
	WIFI_Send(COM_DATA_Lenght);
	delay_ms(500);
	USART_Send_Str(DAT,4);
	Send_New_Line();
	delay_ms(50);

}
void Send_New_Line(void)
{
	USART1->DR='\r';
	while((USART1->SR&0X40)==0);//等待发送结束
	USART1->DR='\n';
	while((USART1->SR&0X40)==0);//等待发送结束
}
/****************************
功能：发送小数（precision精度可以控制）
作者：cwp


*******************************/
void Send_Double(double NUM,char precision)
{
	char Double[10];
	Duoble_TO_STR(NUM,Double,precision);
	WIFI_Send_DATA(Double);
}
/****************************
功能：发送整数
作者：cwp


*******************************/

void Send_Int(int NUM)
{
	char INT[10];
	NUM_TO_STR(NUM,INT);
	WIFI_Send_DATA(INT);

}
/****************************
功能：数据组合
作者：cwp


*******************************/
void DATA_Integration()
{
	
}
u16 Acce_Flag=0;
char Acce_Flag_Success=0;
char DATA_Acc[2048];

void Acceive_DATA(u8 Res)
{

	USART_RX_BUF[USART_RX_STA++]=Res;
	switch(Send_flag){
			case 0:
				if(Res=='+')
					Send_flag=1;
//				else USART_RX_BUF[USART_RX_STA++]=Res;

				break;
			case 1:
				if(Res=='I')
					Send_flag=2;
				else Send_flag=0;
				break;
			case 2:
				if(Res=='P')
					Send_flag=3;
				else Send_flag=0;
				break;
			case 3:
				if(Res=='D')
					Send_flag=4;
				else Send_flag=0;
				break;
			case 4:
				if(Res==',')
					Send_flag=5;
				else Send_flag=0;
				break;
			case 5:
				if((Acce_Flag&0x8000)==0)//接收未完成
				{
				if(Acce_Flag&0x4000)//接收到了0x0d
					{
					if(Res!=0x0a)Acce_Flag=0;//接收错误,重新开始
					else {
						Acce_Flag|=0x8000;	//接收完成了 
						Clear_OLED(0,0,128,8);
						show_Str(0,0,8,16,DATA_Acc);
						DATA_HANDLE(DATA_Acc);
						Acce_Flag=0;
	//					Send_Int(13);
						Send_flag=0;
//						WIFI_Send_DATA(DATA_Acc);
						Acce_Flag_Success=1;
//						delay_ms(1000);

						}
					}
				else //还没收到0X0D
					{	
					if(Res==0x0d&&Acce_Flag>1){
						Acce_Flag|=0x4000;
						DATA_Acc[Acce_Flag&0X3FFF]='\0' ;
					}
					else
						{
						DATA_Acc[Acce_Flag&0X3FFF]=Res ;
						Acce_Flag++;
						if(Acce_Flag>(USART_REC_LEN-1))Acce_Flag=0;//接收数据错误,重新开始接收	  
						}		 
					}
				}				
	//				if(Res==',')
	//					Send_flag=5;
	//				else Send_flag=0;
					break;
			deflaut :break;
			
		}	
}

int Acc_DATA_LEN;			//接收数据长度

/*****************************************************
功能：提取数据

说明：	case 0；提取接收数据长度
		case 1：判断侦头
		case 2：提取所需数据

*****************************************************/
void DATA_HANDLE(char *DATA_ARR)
{
	int i=0;
	char Flag=0;
	char temp;
	char LENGTH[6]={0,0,0,0,0,0};
	Acc_DATA_LEN=0;
	for (;i<(Acce_Flag&0x3FFF);i++){
		switch(Flag){
			case 0:				//提取字节长度
				for(temp=0;*(DATA_ARR+i)!=':'&&temp<6;temp++,i++)
					LENGTH[temp]=*(DATA_ARR+i);
				show_Str(4,4,8,16,LENGTH);
				Acc_DATA_LEN=char_To_int(LENGTH);
				//Send_Int(Acc_DATA_LEN);
				Flag+=1;
			break;
			deflaut :break;
		}break;
	}
}
/****************************
功能：WIFI初始化
作者：cwp
说明：前三步可通过串口提前配置好，无需再重新发送AT指令
	  只需把服务器的IP和端口号确定即可

*******************************/
void MyWIFI_Init(void)
{
	//可以通过串口提前配置好，至发送连接服务器的那一条指令
//	WIFI_Send(COM_AT);
//	WIFI_Send(COM_CWMODE1);
//	WIFI_Send(COM_RST);
//	delay_ms(3000);					//rst后会有一串不知名数据返回，此处应该等待久些，接收的数组长度也应该要长些 >300
	WIFI_Send(COM_Conect);
	delay_ms(6000);
	WIFI_Send(COM_Conect_Sever);
	delay_ms(6000);

	WIFI_Send_DATA("1234567891123\r\n");
	WIFI_Send_DATA(COM_AT);
	WIFI_Send_DATA(COM_CWMODE1);
	WIFI_Send_DATA(COM_RST);
	WIFI_Send_DATA(COM_Conect);
//	WIFI_Send(COM_AT);	
}

