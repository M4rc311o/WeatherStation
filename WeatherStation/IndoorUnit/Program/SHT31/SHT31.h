/*
 * SHT31.h
 *
 * Created: 23.11.2021 17:11:05
 *  Author: M4rc3110
 */ 


#ifndef SHT31_H_
#define SHT31_H_

#include <avr/io.h>
#include "../TWI/TWI.h"

#define SHT31_ADDRESS 0x44

struct Measurments {
	int16_t Temperature;
	uint8_t Humidity;
};

void SHT31_Reset();
struct Measurments SHT31_Measure();

#endif /* SHT31_H_ */