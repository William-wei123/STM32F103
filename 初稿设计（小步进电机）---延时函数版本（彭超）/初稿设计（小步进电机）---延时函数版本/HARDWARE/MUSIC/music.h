#ifndef _MUSUC_H
#define _MUSUC_H
#include "sys.h"
extern u8 music_control[]; 
extern u8 volume_control[];
//ָ����Ŀ   7E FF 06 03 00 00 01 EF   �޸�01������Ŀ   01����һ��
extern u8 single_tune_cir_control[]; 
//����ѭ��ָ������   7E FF 06 08 00 00 01 EF   �޸�01���ĵ���ѭ����Ŀ  01��ѭ����һ��

void sand_cmd(u8 table[]);
void sand_control_jian(u8 table[]);
void sand_control_jia(u8 table[]);
void mp3_cmd(u8 cmd);
void radio_cmd(u8 cmd);
void control_mp3(u8 t,u8 table[]);

#endif
