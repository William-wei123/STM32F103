#include "LIB_Config.h"
#include "i2c_soft.h"
#include "spi_hard.h"
#include "bme280_application.h"

/*
This Demo is tested on  Xnucleo, STM32F103RBT6 Chip.
IIC1:
	IIC1_SCL:PB6
	IIC1_SDA:PB7
SPI1:
	SPI1_SCK: PA5
	SPI1_MISO:PA6
	SPI1_MOSI:PA7
	SPI1_CS:  PB6
USART2:
	USART_TX:PA2
	USART_RX:PA3
You can use USART 2 to print the information to your host computer with Baud rate 115200
*/

//This Macro definition decide whether you use I2C or SPI
//When USEIIC is 1 use I2C interface, When it is 0,use SPI interface
#define USEIIC 1

int main(void) 
{
	system_init();
	
	struct bme280_dev dev;
	int8_t rslt = BME280_OK;
	
	#if(USEIIC)
	I2c_Soft_Init();
	//when I2C address is 0x76
	dev.dev_id = BME280_I2C_ADDR_PRIM;
	//when I2C address is 0x77
//	dev.dev_id = BME280_I2C_ADDR_SEC;
	dev.intf = BME280_I2C_INTF;
	dev.read = user_i2c_read;
	dev.write = user_i2c_write;
	dev.delay_ms = user_delay_ms;
	#else
	SPI1_Init();
	SPI_CS_Init();
	dev.dev_id = 0;
	dev.intf = BME280_SPI_INTF;
	dev.read = user_spi_read;
	dev.write = user_spi_write;
	dev.delay_ms = user_delay_ms;
	#endif
	
	//before you init bme280, you can choose to do a selftest
	//rslt = bme280_crc_selftest(&dev);
	//if(rslt == 0)
	//{
	//	printf("BME280 self test pass\r\n");
	//}
	
	rslt = bme280_init(&dev);
	if(rslt == 0)
	{
		printf("Init Success\r\n");
	}
	else
	{
		printf("Init Fail,Please Check your address or the wire you connected!!!\r\n");
		while(1);
	}
	
	//Using normal mode to read the data
	stream_sensor_data_normal_mode(&dev);
	//Using forced mode to read the data
	//stream_sensor_data_forced_mode(&dev);
}
/*-------------------------------END OF FILE-------------------------------*/
