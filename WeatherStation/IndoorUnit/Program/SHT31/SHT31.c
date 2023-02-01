/*
 * SHT31.c
 *
 * Created: 23.11.2021 17:10:47
 *  Author: M4rc3110
 */ 

#include "SHT31.h"
#include "../CRC_8/CRC_8.h"
#include <util/delay.h>

#define CLK_STR_EN 0x2C
#define CLK_STR_DI 0x24

void SHT31_SendCOM(uint8_t command_MSB, uint8_t command_LSB);

//send commands to SHT31
void SHT31_SendCOM(uint8_t command_MSB, uint8_t command_LSB){
	uint8_t comp[2];
	comp[0] = command_MSB;
	comp[1] = command_LSB;
	TWI_Write(SHT31_ADDRESS, comp, 2);
	_delay_ms(1);
}

//returns measurements(temp, hum) in Measurments struct 
struct Measurments SHT31_Measure(){	
	struct Measurments meas;
	uint8_t data[6];
	
	meas_again:
	SHT31_SendCOM(0x2C, 0x06);
	TWI_Read(SHT31_ADDRESS, data, 6);
	
	if(CRC_8_Check(0x31, 0xff, 0x0, data, 3) != 0) goto meas_again;
	meas.Temperature = ((-45 + 175 * ((((uint16_t)data[0] << 8) | data[1]) / (float)65535)) * 100);
	
	if(CRC_8_Check(0x31, 0xff, 0x0, data + 3, 3) != 0) goto meas_again;
	meas.Humidity = (100 * ((((uint16_t)data[3] << 8) | data[4]) / (float)65535));
	
	return meas;
}

void SHT31_Reset(){
	SHT31_SendCOM(0x30, 0xA2);
}