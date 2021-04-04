#include "ALL_init.h"
#define MYADDR 0x5d	`//01011101	那么读此时地址为addr<<1|1,写此时addr<<1;
u8 BUF__RX[10]={0,1,2,3,4,5,6,7,8,9};
u8 I2c_Addr;
uint8_t  Buffer_Rx_IIC1[40];//接收缓存
uint8_t  Rx_Idx_IIC1=0;//接收计数
uint8_t  Flag_RcvOK_IIC1 = 0;// 接收完成标志 
uint8_t  Tx_Idx_IIC1=0;//发送计数
u8 Response_Message[40];//发送缓存
u16 averageArr[4];     //晓辉建用于对得到的激光的原始数据求平均值
int count=0;
float _DATA_;
u8 data_save_flag=0;


extern DATA_array XIA;
//--------------------- 
//作者：夜风~ 
//来源：CSDN 
//原文：https://blog.csdn.net/u014470361/article/details/82317285 
//版权声明：本文为博主原创文章，转载请附上博文链接！
void IIC_init()
{
/*GPIO与IIC初始化结构体*/  
GPIO_InitTypeDef GPIO_InitStructure;  
I2C_InitTypeDef I2C_InitStructure;  
NVIC_InitTypeDef NVIC_InitStructure;

/*GPIO与IIC时钟使能*/  
RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE );     //GPIOB时钟使能  
RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );      //IIC2时钟使能  

GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7 ;   //初始化GPIO.B6(IIC1_SCL)，GPIO.B7(IIC1_SDA)  
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //最高输出速度50Hz  
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;             //输入输出模式为复用功能开漏输出  
GPIO_Init( GPIOB, &GPIO_InitStructure );                    //根据GPIO初始化结构体初始化GPIOB  
I2C_DeInit(I2C1);                                           //复位I2C
/*初始化IIC2*/  
I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                  //设置为IIC模式  
I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;          //设置IIC的占空比，低电平除以高电平值为2  
I2C_InitStructure.I2C_OwnAddress1 = 0x02;				//指定第一个设备的地址为7位地址 从设备地址为函数参数add
I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 //使能ACK信号  
I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   //指定7位地址  
I2C_InitStructure.I2C_ClockSpeed = 100000;                  //时钟频率，必须小于等于400KHz  
I2C_Init( I2C1, &I2C_InitStructure );   
I2C1->CR2&=0xff00;                 //**//设置I2C输入时钟频率为4Mhz**  根据时钟树配置
I2C1->CR2|=0x04; 
I2C_Cmd( I2C1, ENABLE );                                 //使能硬件IIC2  
I2C_ITConfig(I2C1,I2C_IT_EVT|I2C_IT_BUF,ENABLE);

NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

//--------------------- 
//作者：a351357741 
//来源：CSDN 
//原文：https://blog.csdn.net/a351357741/article/details/77050802 
//版权声明：本文为博主原创文章，转载请附上博文链接！
}
//发送顺序	EV1—>EV3-1—>EV3—>EV3-2
//接受顺序	EV1—>EV2—>EV4
void I2C1_EV_IRQHandler(void)
{
__IO uint32_t SR1Register =0;
  __IO uint32_t SR2Register =0;

  SR1Register = I2C1->SR1;
  SR2Register = I2C1->SR2;

    /* I2C1是从机(MSL = 0) */
  if((SR2Register &0x0001) != 0x0001)
  {
    /* 主机已发送地址，地址为被置位·(ADDR = 1: EV1(包括发送和接收)) */
    if((SR1Register & 0x0002) == 0x0002)
    {
        /* 清除标志位 */
        SR1Register = 0;
        SR2Register = 0;

        Rx_Idx_IIC1=0;
        Tx_Idx_IIC1=0;
    }



    /* 接收数据(RXNE = 1: EV2) */
    if((SR1Register & 0x0040) == 0x0040)
    {
        Buffer_Rx_IIC1[Rx_Idx_IIC1++] = I2C1->DR;
        SR1Register = 0;
        SR2Register = 0;
    }
    /* 检测到停止条件(STOPF =1: EV4) */
    if(( SR1Register & 0x0010) == 0x0010)
    {
        I2C1->CR1 |= 0x0001;
        SR1Register = 0;
        SR2Register = 0;
        Flag_RcvOK_IIC1 = 1;            
    }




    /* 发送数据(TxE = 1: EV3、EV3-1) */
    if((SR1Register & 0x0080) == 0x0080)
    {
        I2C1->DR = Response_Message[Tx_Idx_IIC1++]; 
        SR1Register = 0;
        SR2Register = 0;
    }
    /* 检测到非应答(AF =1: EV3-2) */
    if(( SR1Register & 0x0400) == 0x0400)
    {
        I2C1->SR1 &= 0xFDFF;
        SR1Register = 0;
        SR2Register = 0;        
    }       
  }

//--------------------- 
//作者：夜风~ 
//来源：CSDN 
//原文：https://blog.csdn.net/u014470361/article/details/82317285 
//版权声明：本文为博主原创文章，转载请附上博文链接！                
}
//--------------------- 
//作者：a351357741 
//来源：CSDN 
//原文：https://blog.csdn.net/a351357741/article/details/77050802 
//版权声明：本文为博主原创文章，转载请附上博文链接！

/*
Function:把内环输出转换成char类型给USART
name:	 flaot_to_char(float temp)

*/
void float_to_char(float *temp,char *_array_)//temp[4],_array_[5]
{
	u8 i;
	float t=0;
	s16 DATA;
	for(i=0;i<4;i++){
		t+=temp[i]/4;

	}
	DATA=t*100;
	//内环输出
	_array_[0]=DATA/256;
	_array_[1]=DATA%256;
	//效验位，内环高8位的高四位+低八位的低四位
	_array_[2]=_array_[0]/4+_array_[1]%4;//
	//滤波之后的高度
	_array_[3]=ultra_distance/256;
	_array_[4]=ultra_distance%256;

}
void char_to_float(char *_array_)//temp[4],_array_[2]
{
	u16 temp;
	temp =_array_[0]*256+_array_[1];
	_DATA_=(s16)temp/100.0;
}
/***************************
功能：接收单个串口数据，放入对应结构体，得到距离值

*************************/
void LASER_ACCEPT_DATA(u8 DATA,DATA_array *LASER__DATA)
{
	static u8 i=0;
	if(LASER__DATA->Flag_Start==0&&i==0){
		if(DATA==HEADER){
			LASER__DATA->Array_[i]=DATA;
			LASER__DATA->Flag_Start=1;
			i++;
		}
	}else if(LASER__DATA->Flag_Start==1&&i==1&&DATA==HEADER){
		LASER__DATA->Array_[i]=DATA;
		i++;
	}else if(LASER__DATA->Flag_Start==1){
		LASER__DATA->Array_[i]=DATA;
		i++;
	}
	if(i==9){
		i=0;
		LASER__DATA->Flag_Start=0;
 //--------------------------------------------------------- ---      
        averageArr[count++]=panduan(XIA.Array_); 
        
        if(count == 4)
         {
            LASER__DATA->Average_DATA = average_Data(averageArr , 4);
             count = 0;
         }
         
  //----------------------------------------------------------------
//				ultra_distance=panduan(XIA.Array_);
		ultra_start_f=1;

	}
}
//-----------------------晓辉,求平均值------------------------
u16 average_Data(u16 arr[] , int n)
{
   u16 sum=0;
   int i ;
   for(i =0; i< n ; i++){
            sum +=arr[i];
   }
   return sum/n;
}
//---------------------------------------------------------
void LASER_DATA_HANDLE(s8 Flag,DATA_array *LASER__DATA,void (*FUNC)(int))
{
	static u8 temp=0;
	if(Flag==1){			//开启数据处理的标志，不开启数据不可靠
	FUNC(LASER__DATA->Average_DATA);
	HIGHT_CTRL_OUTPUT_[temp++]=height_ctrl_output;
	HEIGHT_CTRL(0.01);
//				FLAG_Remap++;
	if(++FLAG_Remap>4){
		FLAG_Remap=0;
		temp=0;
		float_to_char(HIGHT_CTRL_OUTPUT_,XIA.DATA_TO_FLY);
		char_to_float(XIA.DATA_TO_FLY);
	}			
}
}
void FLY_DATA_HANDLE(u8 *FLY_DATA_ARRAY)
{
	
	u8 temp=0;
	expect_height=FLY_DATA_ARRAY[temp++]*100;
	
	height.kp = FLY_DATA_ARRAY[temp++]/10.0;
	height.ki = FLY_DATA_ARRAY[temp++]/100.0;
	height.kd = FLY_DATA_ARRAY[temp++]/10.0;
	
	speed.kp = FLY_DATA_ARRAY[temp++]/10.0;
	speed.ki = FLY_DATA_ARRAY[temp++]/10.0;
	speed.kd = FLY_DATA_ARRAY[temp++]/1000.0;
}
u8 FLY_DATA_ARRAY[8];
u8 _ACCEPT_DATA_BY_FLY(u8 DATA)
{
	static u8 i=0;
	u8 temp=0;
	
	switch (i){
		case 0:
			if(DATA == 0x96)
				i=1;
			else  {
				i=0;
				temp=59;
			}
			break ;
		case 1:			
			if(DATA == 0x99)
				i=2;
			else {
				i=0;
				temp=59;
			}
			break ;
		case 2:
			FLY_DATA_ARRAY[0]=DATA;
			i=3;
			break ;
		case 3:
			FLY_DATA_ARRAY[1]=DATA;
			i=4;
			break ;
		case 4:
			FLY_DATA_ARRAY[2]=DATA;
			i=5;
			break ;
		case 5:
			FLY_DATA_ARRAY[3]=DATA;
			i=6;
			break ;
		case 6:
			FLY_DATA_ARRAY[4]=DATA;
			i=7;
			break ;
		case 7:
			FLY_DATA_ARRAY[5]=DATA;
			i=8;
			break ;
		case 8:
			FLY_DATA_ARRAY[6]=DATA;
			i=9;
			break ;
		case 9:
			FLY_DATA_ARRAY[7]=DATA;
//			for(i=0,temp=0;i<7;i++){
//				temp+=FLY_DATA_ARRAY[i]%4;
//			}
			if(0x05==FLY_DATA_ARRAY[7]){
				FLY_DATA_HANDLE(FLY_DATA_ARRAY);
				data_save_flag=1;
//				temp=1;
			}
			i=0;
			temp=0;
			break ;
		case 10:
			break ;
		default :i=0;
			break ;
	}
	
//		USART1->DR=i;			//数据头
//		while((USART1->SR&0X40)==0);//等待发送结束
//		USART1->DR=DATA;			//数据头
//		while((USART1->SR&0X40)==0);//等待发送结束
		return temp;	

}
