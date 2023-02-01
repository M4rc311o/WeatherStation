/*
 * BME280.h
 *
 * Created: 04.08.2021 14:10:01
 *  Author: M4rc3110
 */ 


#ifndef BME280_H_
#define BME280_H_

#include <avr/io.h>
#include "../TWI/TWI.h"

#define BME280_ADDRESS 0x76

struct Measurments {
	int32_t Temperature;
	uint32_t Pressure;
	uint32_t Humidity;
};

void BME280_Init();
void BME280_Reset();
struct Measurments BME280_MeasureAll();
int32_t BME280_Temperature();
uint32_t BME280_Humidity();
uint32_t BME280_Pressure();

#endif /* BME280_H_ */