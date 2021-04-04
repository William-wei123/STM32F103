#include "MPU6050.h"
#include "I2C.h"

u8 MPU_Init(void) 								//��ʼ��MPU6050
{
	u8 res=0;

	MyI2C_Init();
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU6050
	delay_ms(100);
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0x00);//����MPU6050
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_INT_EN_REG,0X00);	//�ر������ж�
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MyI2C_Write_One_Byte(MPU_ADDR,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MyI2C_Read_One_Byte(MPU_ADDR,MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ
	{
		MyI2C_Write_One_Byte(MPU_ADDR,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MyI2C_Write_One_Byte(MPU_ADDR,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;	
}



//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MyI2C_Write_One_Byte(MPU_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MyI2C_Write_One_Byte(MPU_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MyI2C_Write_One_Byte(MPU_ADDR,MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MyI2C_Write_One_Byte(MPU_ADDR,MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i,temp=1; 
    MyI2C_Star(); 
	temp=MyI2C_Write_Byte((addr<<1)|0);//����������ַ+д����	
	if(temp)	//�ȴ�Ӧ��
	{
		MyI2C_Stop();		 
		return 1;		
	}
    MyI2C_Write_Byte(reg);	//д�Ĵ�����ַ
    //MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		temp=MyI2C_Write_Byte(buf[i]);	//��������
		if(temp)		//�ȴ�ACK
		{
			MyI2C_Stop();	 
			return 1;		 
		}		
	}    
    MyI2C_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	u8 temp;
	MyI2C_Star(); 
	temp=MyI2C_Write_Byte((addr<<1)|0);//����������ַ+д����	
	if(temp)	//�ȴ�Ӧ��
	{
		MyI2C_Star();		 
		return 1;		
	}
    temp=MyI2C_Write_Byte(reg);	//д�Ĵ�����ַ
   // MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MyI2C_Star();
	MyI2C_Write_Byte((addr<<1)|1);//����������ַ+������	
    //MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=MyI2C_read_Byte(1);//������,����nACK 
		else *buf=MyI2C_read_Byte(0);		//������,����ACK  
		len--;
		buf++; 
	}    
    MyI2C_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
