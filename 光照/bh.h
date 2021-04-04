#ifndef __BH_H
#define __BH_H	 
#include "sys.h"

#define BH1750_Addr 0x46          //iic�ӻ���ַ
#define BH1750_ON   0x01          //����
#define BH1750_CON  0x10          //������ȡ
#define BH1750_ONE  0x20          //һ�ζ�ȡ
#define BH1750_RSET 0x07          //����

void BH1750_Init(void);			//IO��ʼ��
void Start_BH1750(void);	  //�ϵ硢���á�������ݼĴ���
void Read_BH1750(void);     //������ȡ�ڲ��Ĵ�������              
void Convert_BH1750(void);  //����ת��









#endif

