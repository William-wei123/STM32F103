#include "sys.h"
#ifndef DEAL_____H__
#define DEAL_____H__
void advance(void);
void counter(void);
void left(void);
void right(void);
void stop(void);
void speed_up(void);
void speed_low(void);

void Draw_Water(void);
void Draw_Air(void);
void Draw_food(void);

void TDS_SEND_FUC(void);
void TDS_acc(u8 res);

void PH_SEND_FUC(void);
void PH_acc(u8 res);


extern double TDS_DATA;

extern double PH_DATA_T;
extern double PH_DATA_PH;


//extern int n;
#endif
