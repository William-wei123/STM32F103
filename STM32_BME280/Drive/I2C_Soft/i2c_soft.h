#ifndef _I2C_SOFT_H
#define	_I2C_SOFT_H



//#include "time.h"

#include "stm32f10x.h"

#define SCL_L 			(I2C_PORT->BRR |= I2C_SCL)
#define SCL_H 			(I2C_PORT->BSRR |= I2C_SCL)
#define SDA_L 			(I2C_PORT->BRR |= I2C_SDA)
#define SDA_H 			(I2C_PORT->BSRR |= I2C_SDA)
#define SDA_read 		(I2C_PORT->IDR & I2C_SDA)
#define SCL_read 		(I2C_PORT->IDR & I2C_SCL) //unused

/***************I2C GPIO∂®“Â******************/
#define I2C_PORT	        GPIOB
#define I2C_SCL		        GPIO_Pin_6
#define I2C_SDA		        GPIO_Pin_7

#define RCC_I2C_PORT 		RCC_APB2Periph_GPIOB
/*********************************************/
extern volatile u8 I2C_FastMode;

void I2c_Soft_Init(void);
void I2c_Soft_SendByte(u8 SendByte);
u8 I2c_Soft_ReadByte(u8);

//int I2c_Soft_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
//int I2c_Soft_Single_Read(u8 SlaveAddress,u8 REG_Address);
//int I2c_Soft_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size);

//u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);
//u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);

u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data);
u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u16 len, u8 *buf);
u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u16 len, u8 *buf);


int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

#endif
