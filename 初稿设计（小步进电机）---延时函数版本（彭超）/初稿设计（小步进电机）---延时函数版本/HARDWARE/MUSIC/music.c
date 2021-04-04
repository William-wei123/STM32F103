#include "music.h"
#include "delay.h"
//#include "key.h"
//////
/*********
20200524
彭超
MP3音乐播放部分命令
********/


/***
无校验版  直接命令
***/
u8 next_song[]={0x7E,0XFF,0X06,0X01,0X00,0X00,0X00,0XEF}; 
//下一首     7E FF 06 01 00 00 00 EF
u8 pre_song[]={0x7E,0XFF,0X06,0X02,0X00,0X00,0X00,0XEF};
//上一首     7E FF 06 02 00 00 00 EF
u8 single_tune_cir_now[]={0x7E,0XFF,0X06,0X19,0X00,0X00,0X00,0XEF}; 
//单曲循环当前曲目   7E FF 06 19 00 00 00 EF
u8 all_tune_cir[]={0x7E,0XFF,0X06,0X11,0X00,0X00,0X01,0XEF}; 
//循环全部歌曲       7E FF 06 11 00 00 01 EF  
u8 play_song[]={0x7E,0XFF,0X06,0X0D,0X00,0X00,0X00,0XEF};
//播放       7E FF 06 0D 00 00 00 EF
u8 pause_song[]={0x7E,0XFF,0X06,0X0E,0X00,0X00,0X00,0XEF}; 
//暂停       7E FF 06 0E 00 00 00 EF
u8 res[]={0x7E,0XFF,0X06,0X03,0X00,0X00,0X01,0XEF}; 
//复位       7E FF 06 0C 00 00 00 EF



/*****
7E FF 06 06 00 00 1E FE D7 EF
0x7E,0XFF,0X06,0X06,0X00,0X00,0X1D,0XEF
无校验版   指定命令
****/
u8 volume_control[]={0x7E,0XFF,0X06,0X06,0X00,0X00,0X1D,0XEF}; 
//指定音量   7E FF 06 06 00 00 16 EF   修改16来改音量   1E:音量最高30
u8 music_control[]={0x7E,0XFF,0X06,0X03,0X00,0X00,0X01,0XEF}; 
//指定曲目   7E FF 06 03 00 00 01 EF   修改01来改曲目   01：第一首
u8 single_tune_cir_control[]={0x7E,0XFF,0X06,0X08,0X00,0X00,0X01,0XEF}; 
//单曲循环指定歌曲   7E FF 06 08 00 00 01 EF   修改01来改单曲循环曲目  01：循环第一首

/*******
校验版查询命令
*******/
u8 volume_query[]={0x7E,0XFF,0X06,0X43,0X00,0X00,0X00,0XEF}; 
//查询当前音量     7E FF 06 43 00 00 00 EF

//无校验版  直接命令操作函数
void sand_cmd(u8 table[])  
{
  u8 i;
	for(i=0;i<8;i++)
	{
	 USART_SendData(USART2,table[i]);
	 delay_ms(1);
	}
}


//指定命令   -加操作
void sand_control_cmd(u8 table[])  
{
  u8 a;
	table[6] = table[6] + 15;
	if(table[6] >= 30)  table[6] = 30;     //此处最大为30
	for(a=0;a<8;a++)
	{
	 USART_SendData(USART2,table[a]);
	 delay_ms(1);
	}
}

//指定命令   -减操作
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

//主函数调用命令
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

