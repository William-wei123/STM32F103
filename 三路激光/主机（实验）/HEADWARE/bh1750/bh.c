#include "bh.h"
#include "I2C.h"
#include "delay.h"
#include "stdio.h"

float result_lx=0;

u8 BUF[2]={0};
u16 result=0;

//��ʼ��
void BH1750_Init(void)
{
	  MyI2C_Init();
}

void Cmd_Write_BH1750(u8 cmd)
{
    MyI2C_Star();                    //IIC��ʼ�ź�
	
    MyI2C_Write_Byte(BH1750_Addr+0);   //�����豸��ַ+д�ź�
//	  while(MyI2C_Wait_Ack());
	
    MyI2C_Write_Byte(cmd);             //�ڲ��Ĵ�����ַ
//	  while(MyI2C_Wait_Ack());
	
    MyI2C_Stop();                     //����ֹͣ�ź�
	  delay_ms(5);
}
void Start_BH1750(void)
{
	  Cmd_Write_BH1750(BH1750_ON);	  //power on
	  Cmd_Write_BH1750(BH1750_RSET);	//����
	  Cmd_Write_BH1750(BH1750_ONE);   //һ��H�ֱ���ģʽ������120ms��֮�����ϵ�ģʽ    
}
void Read_BH1750(void)
{   	
    MyI2C_Star();                          //IIC��ʼ�ź�
    MyI2C_Write_Byte(BH1750_Addr+1);         //�����豸��ַ+���ź�
//	  while(MyI2C_Wait_Ack());
	  BUF[0]=MyI2C_read_Byte(0);              //����ACK
	  BUF[1]=MyI2C_read_Byte(1);              //����NACK
 
    MyI2C_Stop();                           //IICֹͣ�ź�
    delay_ms(5);
}
void Convert_BH1750(void)
{
	
	  result=BUF[0];
	  result=(result<<8)+BUF[1];  //�ϳɹ���ǿ��
	
	  result_lx=(float)result/1.2;
	
	  //printf("illuminance:%.1f lx",result_lx);		
}


//void conversion(u16 temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
//{  
//	u8   ge,shi,bai,qian,wan;
//    wan=temp_data/10000+0x30 ;
//    temp_data=temp_data%10000;   //ȡ������
//	qian=temp_data/1000+0x30 ;
//    temp_data=temp_data%1000;    //ȡ������
//    bai=temp_data/100+0x30   ;
//    temp_data=temp_data%100;     //ȡ������
//    shi=temp_data/10+0x30    ;
//    temp_data=temp_data%10;      //ȡ������
//    ge=temp_data+0x30; 	
//}



