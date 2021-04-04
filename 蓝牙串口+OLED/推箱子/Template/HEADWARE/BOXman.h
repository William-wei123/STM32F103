#ifndef BOXMAN__H__
#define BOXMAN__H__
#include "sys.h"
#include "usart..h"
extern char boxs[8][1];
extern char goal[8][1];
extern char Wall[8][1];
extern char man[8][1];

extern char map1[8][8];
extern char map2[8][8];
extern char map3[8][8];
extern char Wall1[8][1];
extern u8 explain[72][2];
void DrawMap1(char map[8][8]);
void FindManLocation(char *X,char *Y,char map[8][8]);                   //找人
void MoveMan(char *X,char *Y,char map[8][8],char a);                                                   /*移动函数*/
void Level(char n,char map[8][8]);
void marking(char map[8][8]);                                    //计分数


#endif
