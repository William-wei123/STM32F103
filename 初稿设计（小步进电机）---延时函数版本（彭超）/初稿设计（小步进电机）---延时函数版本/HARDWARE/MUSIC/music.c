#include "music.h"
#include "delay.h"
//#include "key.h"
//////
/*********
20200524
��
MP3���ֲ��Ų�������
********/


/***
��У���  ֱ������
***/
u8 next_song[]={0x7E,0XFF,0X06,0X01,0X00,0X00,0X00,0XEF}; 
//��һ��     7E FF 06 01 00 00 00 EF
u8 pre_song[]={0x7E,0XFF,0X06,0X02,0X00,0X00,0X00,0XEF};
//��һ��     7E FF 06 02 00 00 00 EF
u8 single_tune_cir_now[]={0x7E,0XFF,0X06,0X19,0X00,0X00,0X00,0XEF}; 
//����ѭ����ǰ��Ŀ   7E FF 06 19 00 00 00 EF
u8 all_tune_cir[]={0x7E,0XFF,0X06,0X11,0X00,0X00,0X01,0XEF}; 
//ѭ��ȫ������       7E FF 06 11 00 00 01 EF  
u8 play_song[]={0x7E,0XFF,0X06,0X0D,0X00,0X00,0X00,0XEF};
//����       7E FF 06 0D 00 00 00 EF
u8 pause_song[]={0x7E,0XFF,0X06,0X0E,0X00,0X00,0X00,0XEF}; 
//��ͣ       7E FF 06 0E 00 00 00 EF
u8 res[]={0x7E,0XFF,0X06,0X03,0X00,0X00,0X01,0XEF}; 
//��λ       7E FF 06 0C 00 00 00 EF



/*****
7E FF 06 06 00 00 1E FE D7 EF
0x7E,0XFF,0X06,0X06,0X00,0X00,0X1D,0XEF
��У���   ָ������
****/
u8 volume_control[]={0x7E,0XFF,0X06,0X06,0X00,0X00,0X1D,0XEF}; 
//ָ������   7E FF 06 06 00 00 16 EF   �޸�16��������   1E:�������30
u8 music_control[]={0x7E,0XFF,0X06,0X03,0X00,0X00,0X01,0XEF}; 
//ָ����Ŀ   7E FF 06 03 00 00 01 EF   �޸�01������Ŀ   01����һ��
u8 single_tune_cir_control[]={0x7E,0XFF,0X06,0X08,0X00,0X00,0X01,0XEF}; 
//����ѭ��ָ������   7E FF 06 08 00 00 01 EF   �޸�01���ĵ���ѭ����Ŀ  01��ѭ����һ��

/*******
У����ѯ����
*******/
u8 volume_query[]={0x7E,0XFF,0X06,0X43,0X00,0X00,0X00,0XEF}; 
//��ѯ��ǰ����     7E FF 06 43 00 00 00 EF

//��У���  ֱ�������������
void sand_cmd(u8 table[])  
{
  u8 i;
	for(i=0;i<8;i++)
	{
	 USART_SendData(USART2,table[i]);
	 delay_ms(1);
	}
}


//ָ������   -�Ӳ���
void sand_control_cmd(u8 table[])  
{
  u8 a;
	table[6] = table[6] + 15;
	if(table[6] >= 30)  table[6] = 30;     //�˴����Ϊ30
	for(a=0;a<8;a++)
	{
	 USART_SendData(USART2,table[a]);
	 delay_ms(1);
	}
}

//ָ������   -������
void sand_control_jian(u8 table[])  
{
  u8 a;
	table[6] = table[6] - 2;
	if(table[6] <= 5)  table[6] = 5;
	for(a=0;a<8;a++)
	{
	 USART_SendData(USART2,table[a]);
	 delay_ms(1);
	}
}

void control_mp3(u8 t,u8 table[])
{
  u8 i;
	table[6] = t;
	for(i=0;i<8;i++)
	{
	 USART_SendData(USART2,table[i]);
	 delay_ms(1);
	}
}

//��������������
void mp3_cmd(u8 cmd)
{
	//KEY_Scan();
  switch(cmd)
	{
		case 1:
			sand_cmd(pre_song);
		  break;
		case 2:
			sand_cmd(play_song);
		  break;
	  case 3:
			sand_cmd(pause_song);
		  break;
		case 4:
			sand_control_jian(volume_control);
		  break;	
		case 5:
			sand_control_cmd(volume_control)  ;
		  break;	
		default:
			delay_ms(15);
			break;
	}
}

