#include "I2C.h"
#include "delay.h"
void MyI2C_Init(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��ֹJTAG,�Ӷ�PA15��������ͨIOʹ��,����PA15��������ͨIO!!!
	RCC->APB2ENR|=1<<4;//ʹ��GPIOA�ڣ�����ȥ��32�����ֲ�6.3
	GPIOC->CRH&=0X00FFFFFF;	//PA14 15 �������		����ȥ��32�����ֲ�8.2
	GPIOC->CRH|=0X33000000;	   
	GPIOC->ODR|=3<<14;     	//P �����		����ȥ��32�����ֲ�8.2.4

}

void MyI2C_Star(void)
{
	SDA_OUT();		//SDA���
	IIC_SCL=1;
	IIC_SDA=1;
	delay_us(5);
	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

void MyI2C_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MyI2C_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)//�͵�ƽΪ��ЧӦ��
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MyI2C_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 ��//�ɼ�����������	   
	return 0;  
} 

//����ACKӦ��
void MyI2C_Ack(u8 AC)//0Ϊ��ЧӦ��
{
	IIC_SCL=0;
	SDA_OUT();//��Ϊ���ģʽ
	IIC_SDA=AC;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
u8 MyI2C_Write_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }
	return MyI2C_Wait_Ack();	//�ȴ�Ӧ��
} 

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MyI2C_read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    MyI2C_Ack(ack);
    return receive;

}

u8 MyI2C_Write_One_Byte(u8 daddr,u8 addr,u8 data)
{
	u8 temp,m;
	MyI2C_Star();
	m=MyI2C_Write_Byte((daddr<<1)|0);//�����ַ+д����
	MyI2C_Write_Byte(addr);//���ݵ�ַ
	temp=MyI2C_Write_Byte(data);//���ݷ���
	
	MyI2C_Stop();
	delay_ms(10);	 				//EEPROM��д���ٶȱȽ����������ӳ�  //�ɼӿɲ��ӣ�
	return temp ;
}
u8 MyI2C_Read_One_Byte(u8 daddr,u8 addr)
{
	u8 k,temp=0;		  	    																 
	MyI2C_Star();
	MyI2C_Write_Byte((daddr<<1)|0);//�����ַ+д����
	k=MyI2C_Write_Byte(addr);//���ݵ�ַ
	MyI2C_Star();
	MyI2C_Write_Byte((daddr<<1)|1);//�����ַ+������//���
	temp=MyI2C_read_Byte(1);
	delay_ms(10);	 				//EEPROM��д���ٶȱȽ����������ӳ�  //�ɼӿɲ��ӣ�
	MyI2C_Stop();
	return temp;

}

