#ifndef __BME280_APPLICATION_H__
#define __BME280_APPLICATION_H__

#include "LIB_Config.h"
#include "bme280.h"
#include "bme280_selftest.h"


void print_sensor_data(struct bme280_data *comp_data);

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev);
	
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);

#endif
