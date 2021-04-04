#ifndef _MUSUC_H
#define _MUSUC_H
#include "sys.h"
extern u8 music_control[]; 
extern u8 volume_control[];
//指定曲目   7E FF 06 03 00 00 01 EF   修改01来改曲目   01：第一首
extern u8 single_tune_cir_control[]; 
//单曲循环指定歌曲   7E FF 06 08 00 00 01 EF   修改01来改单曲循环曲目  01：循环第一首

void sand_cmd(u8 table[]);
void sand_control_jian(u8 table[]);
void sand_control_jia(u8 table[]);
void mp3_cmd(u8 cmd);
void radio_cmd(u8 cmd);
void control_mp3(u8 t,u8 table[]);

#endif
