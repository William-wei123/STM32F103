#include "MyWIFI_.h"
#include "usart.h"
#include "delay.h"
#include "math.h"
#include "OLED.h"
char *COM_AT="AT\r\n";
char *COM_CWMODE1="AT+CWMODE=1\r\n";
char *COM_RST="AT+RST\r\n";

char *COM_Conect="AT+CWJAP=\"113_IN\",\"113inside\"\r\n";				//����ָ��WiFi    	CWP	zxcvbnmasdfghjkl
char *COM_Conect_Sever="AT+CIPSTART=\"TCP\",\"192.168.2.222\",8001\r\n";//����ָ���������Ͷ˿ں�192.168.136.1		
char COM_DATA_Lenght[20]="AT+CIPSEND=";									//�����������
char ALL_Data_buf[200];													
/*********************************
���ܣ�У��ָ���Ƿ��ͳɹ�
���أ����ͳɹ�����1��ʧ��0
���ߣ�cwp
˵��������WIFIģ��Ļش����ƣ�ÿ����һ��ָ���ش�����ָ�����ɹ����ں����3or12or14λ�ش�OK
*****************************/
char WIFI_XIAOYANG(char *COM)
{
	char i,num,temp=0;
	//USART_RX_STA=0;
	for(num=0;(*(COM+num)!='\0');num++);
	for (i=0;(*(COM+i)!='\0')&&*(COM+i)==*(USART_RX_BUF+i);i++);
	if(i+1!=num)												//WIFI �ش�����Ϊ���͹�ȥ������+0xOD��\r��,0xOD(\r),0x(\n)
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
			}//������ʾ��Ϊʲô���ˣ�ͨ����ʾUSART_RX_BUFWIFI_Send(COM_Conect_Sever);

		}
//		if(*(USART_RX_BUF+num+3)=='O'||*(USART_RX_BUF+num+12)=='O'||*(USART_RX_BUF+num+14)=='O'||*(USART_RX_BUF+81)=='O'||*(USART_RX_BUF+num+1)==62)		//WIFI�ش����ݵ�һЩ��ʽ���ɹ�����ָ�����ָ��λ�ûش�OK
//			return 1;
	}
	return temp;
}
/*********************************
���ܣ�����ָ��
���ߣ�cwp

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
���ܣ���������תΪ�ַ�
���ߣ�cwp
*******************************/
void NUM_TO_STR(int NUM,char *STR)
{
	char temp=0;
	int c=NUM;
	for (temp=1;c/10>0;temp++){		//�ж�cΪ��λ��
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
//		if(NUM%cc>=cc)					//�����100001����������ֱ��0����������
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
���ܣ����ַ�תΪint���ͣ�precision���ȿ��Կ��ƣ�
���ߣ�cwp


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
���ܣ���double����תΪ�ַ���precision���ȿ��Կ��ƣ�
���ߣ�cwp


*******************************/
void Duoble_TO_STR(double NUM,char *STR,char precision)
{
	char temp=0,Dot_Flag=0,i=0;
	double c=NUM*pow(10,precision);			//����2λС��
	for (temp=1;(int)c/10>0;temp++){		//�ж�c����������Ϊ��λ��
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
	for(num=0;(*(DAT+num)!='\0');num++);//��ȡ���ݳ���
	NUM_TO_STR(num,(COM_DATA_Lenght+11));
}
u16 Send_flag=0;		//==2��ʾ����ģʽ  
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
	while((USART1->SR&0X40)==0);//�ȴ����ͽ���
	USART1->DR='\n';
	while((USART1->SR&0X40)==0);//�ȴ����ͽ���
}
/****************************
���ܣ�����С����precision���ȿ��Կ��ƣ�
���ߣ�cwp


*******************************/
void Send_Double(double NUM,char precision)
{
	char Double[10];
	Duoble_TO_STR(NUM,Double,precision);
	WIFI_Send_DATA(Double);
}
/****************************
���ܣ���������
���ߣ�cwp


*******************************/

void Send_Int(int NUM)
{
	char INT[10];
	NUM_TO_STR(NUM,INT);
	WIFI_Send_DATA(INT);

}
/****************************
���ܣ��������
���ߣ�cwp


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
				if((Acce_Flag&0x8000)==0)//����δ���
				{
				if(Acce_Flag&0x4000)//���յ���0x0d
					{
					if(Res!=0x0a)Acce_Flag=0;//���մ���,���¿�ʼ
					else {
						Acce_Flag|=0x8000;	//��������� 
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
				else //��û�յ�0X0D
					{	
					if(Res==0x0d&&Acce_Flag>1){
						Acce_Flag|=0x4000;
						DATA_Acc[Acce_Flag&0X3FFF]='\0' ;
					}
					else
						{
						DATA_Acc[Acce_Flag&0X3FFF]=Res ;
						Acce_Flag++;
						if(Acce_Flag>(USART_REC_LEN-1))Acce_Flag=0;//�������ݴ���,���¿�ʼ����	  
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

int Acc_DATA_LEN;			//�������ݳ���

/*****************************************************
���ܣ���ȡ����

˵����	case 0����ȡ�������ݳ���
		case 1���ж���ͷ
		case 2����ȡ��������

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
			case 0:				//��ȡ�ֽڳ���
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
���ܣ�WIFI��ʼ��
���ߣ�cwp
˵����ǰ������ͨ��������ǰ���úã����������·���ATָ��
	  ֻ��ѷ�������IP�Ͷ˿ں�ȷ������

*******************************/
void MyWIFI_Init(void)
{
	//����ͨ��������ǰ���úã����������ӷ���������һ��ָ��
//	WIFI_Send(COM_AT);
//	WIFI_Send(COM_CWMODE1);
//	WIFI_Send(COM_RST);
//	delay_ms(3000);					//rst�����һ����֪�����ݷ��أ��˴�Ӧ�õȴ���Щ�����յ����鳤��ҲӦ��Ҫ��Щ >300
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

