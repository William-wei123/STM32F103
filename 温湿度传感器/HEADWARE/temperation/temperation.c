#include "temperation.h"
#include "delay.h"
#include "sys.h"
GPIO_InitTypeDef GPIO_InitStructure;
u8 Data[5]={1,1,1,1,1};
//8bitʪ����������+8bitʪ��С������+8bi�¶���������+8bit�¶�С������+8bitУ���
unsigned char Humidity[8]="ʪ��Ϊ:";
unsigned char Temperation[8]="�¶�Ϊ:";
/************************
*������u8 Judge0_1(void)
*���ܣ������صİ��ֽ�����ת��Ϊ10����
*���ߣ���ΰƽ
**************************/
u8 Judge0_1(void)
{
	u8 temp=0;
	int i;
//	temp<<=1;
	for(i=0;i<8;i++){
		while(!PC6i);//ÿһ�����ݿ�ʼǰ�ȴ�50us
		delay_us(29);//��ʱ30us�ж���0 or 1
		if(PC6i==0){
			temp<<=1;//�����30΢�����0���򴫻�0�����򴫻�1
		}else{
			temp|=1;
			temp<<=1;
			while(PC6i);//�ȴ�70usʣ�µĸߵ�ƽ��ȥ
		}
	}
	temp>>=1;
	return temp;
}
/*************************
*������TemperationSendCmd(void)
*���ܣ���DHT11���Ͳ����ź�
*���ߣ���ΰƽ
*************************/
void TemperationSendCmd(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	//���3.3V��ƽ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	PC6o=1;											//����
	delay_ms(100);									//�ȴ�100ms
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	delay_ms(19);									//�͵�ƽ18ms���ϣ������ź�
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	delay_us(40);//��������20`40us�ȴ�
}


/*************************
*������TemperationGetData(void)
*���ܣ���DHT11��������
*����ֵ��j ��ʾ�Ƿ񴫻���Чֵ  1/0 ��Чֵ/��Чֵ
*���ߣ���ΰƽ
**************************/
int TemperationGetData(void)
{
	int i,j=3;
	for(i=0;i<5;i++){		//��֮ǰ���ص��������
		Data[i]=1;
	}
		if(PC6i==0){
		//DHT��Ӧ80us
		while(PC6i==0);		//DHT��Ӧ80us
		if(PC6i==1){
			while(PC6i);
			for(i=0;i<5;i++){
				Data[i]=Judge0_1();
			}
		}
		if(Data[4]==(Data[0]+Data[1]+Data[2]+Data[3]))j=1;//У�������Ƿ���ȷ�������ȷ����1�����򷵻�0��
	}else j=0;
	return j;
}
/*************************
*������TXTemperation(void)
*���ܣ�ͨ�����ڷ���������
*����ֵ��j ��ʾ�Ƿ񴫻���Чֵ  1/0 ��Чֵ/��Чֵ
*���ߣ���ΰƽ
**************************/

void TXTemperation(void)
{
	int i;
	for(i=0;i<8;i++){
		USART1->DR=Humidity[i];
		while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	}
	USART1->DR=(48+Data[0]/10);		//����ʪ������
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=48+Data[0]%10;		//����ʪ������
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR='.';		//����ʪ������
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=(48+Data[0]/10);		//����ʪ��С��
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=48+Data[1]%10;		//����ʪ��С��
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=' ';		//���Ϳո�
	for(i=0;i<8;i++){
		USART1->DR=Temperation[i];
		while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	}
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=(48+Data[2]/10);		//�����¶�����
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=(48+Data[2]%10);		//�����¶�����
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR='.';		//����ʪ������
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=(48+Data[3]/10);		//�����¶�С��
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
	USART1->DR=48+Data[3]%10;		//�����¶�С��
	while((USART1->SR&0X40)==0);//�ȴ����ͽ��� //��״̬������
}
