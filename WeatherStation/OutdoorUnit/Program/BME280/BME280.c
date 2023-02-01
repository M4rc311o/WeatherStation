/*
 * BME280.c
 *
 * Created: 04.08.2021 14:09:46
 *  Author: M4rc3110
 */ 

#include "BME280.h"

#include <util/delay.h>
#include "BME280_Registers.h"

#define SUCCESS 0
#define ERROR 1

#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 0

void BME280_WriteREG(uint8_t Register, uint8_t Data);
uint32_t BME280_ReadREG(uint8_t Register, uint8_t Byte_count, _Bool Endian);
_Bool BME280_Status_Measuring();
_Bool BME280_Status_Copying();
void BME280_Read_CompensationPAR();
void BME280_ForceMODE();
int32_t BME280_TempCOMP();
uint32_t BME280_PressCOMP();
uint32_t BME280_HumCOMP();

static int32_t t_fine;

//struct for compensation parameters
static struct BME280_Compensation_Parameters{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
}BME280_Comp;

//write value to a register
void BME280_WriteREG(uint8_t Register, uint8_t Data){
	uint8_t comp[2];
	comp[0] = Register;
	comp[1] = Data;
	TWI_Write(BME280_ADDRESS, comp, 2);
}

//read value from one or multiple registers
uint32_t BME280_ReadREG(uint8_t Register, uint8_t Byte_count, _Bool Endian){
	uint32_t Data;
	uint8_t Bytes[Byte_count];
	TWI_Write(BME280_ADDRESS, &Register, 1);
	TWI_Read(BME280_ADDRESS, Bytes, Byte_count);
	
	Data = Bytes[0];
	
	if(Byte_count != 1){
		
		//BIG ENDIAN	
		if(Endian){
			for(uint8_t b = 1; b < Byte_count; b++){
				Data <<= 8;
				Data |= Bytes[b];
			}	
			return Data;
		}
		
		//LITTLE ENDIAN
		else{
			for (uint8_t b = 1; b < Byte_count; b++){
				Data |= ((uint32_t)Bytes[b] << (8 * b));
			}
			return Data;
		}
	}
	
	else return Data;
}

//return 1 if sensor is measuring
_Bool BME280_Status_Measuring(){
	return (BME280_ReadREG(BME280_STATUS, 1, BIG_ENDIAN) & 0x08) != 0;
}

//return 1 if sensor is copying NVM data to image registers
_Bool BME280_Status_Copying(){
	return (BME280_ReadREG(BME280_STATUS, 1, BIG_ENDIAN) & 0x01);
}

void BME280_Reset(){
	BME280_WriteREG(BME280_RESET, 0xB6);			//soft reset sensor
	_delay_ms(10);									//wait until soft reset is done
}

void BME280_Read_CompensationPAR(){
	BME280_Comp.dig_T1 = (uint16_t)BME280_ReadREG(BME280_DIG_T1, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_T2 = (int16_t)BME280_ReadREG(BME280_DIG_T2, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_T3 = (int16_t)BME280_ReadREG(BME280_DIG_T3, 2, LITTLE_ENDIAN);
	
	BME280_Comp.dig_P1 = (uint16_t)BME280_ReadREG(BME280_DIG_P1, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P2 = (int16_t)BME280_ReadREG(BME280_DIG_P2, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P3 = (int16_t)BME280_ReadREG(BME280_DIG_P3, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P4 = (int16_t)BME280_ReadREG(BME280_DIG_P4, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P5 = (int16_t)BME280_ReadREG(BME280_DIG_P5, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P6 = (int16_t)BME280_ReadREG(BME280_DIG_P6, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P7 = (int16_t)BME280_ReadREG(BME280_DIG_P7, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P8 = (int16_t)BME280_ReadREG(BME280_DIG_P8, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_P9 = (int16_t)BME280_ReadREG(BME280_DIG_P9, 2, LITTLE_ENDIAN);
	
	BME280_Comp.dig_H1 = (uint8_t)BME280_ReadREG(BME280_DIG_H1, 1, LITTLE_ENDIAN);
	BME280_Comp.dig_H2 = (int16_t)BME280_ReadREG(BME280_DIG_H2, 2, LITTLE_ENDIAN);
	BME280_Comp.dig_H3 = (uint8_t)BME280_ReadREG(BME280_DIG_H3, 1, LITTLE_ENDIAN);
	BME280_Comp.dig_H4 = ((int16_t)BME280_ReadREG(BME280_DIG_H4, 1, LITTLE_ENDIAN) << 4) | ((int16_t)BME280_ReadREG(BME280_DIG_H4 + 1, 1, LITTLE_ENDIAN) & 0xF);
	BME280_Comp.dig_H5 = ((int16_t)BME280_ReadREG(BME280_DIG_H5 + 1, 1, LITTLE_ENDIAN) << 4) | ((int16_t)BME280_ReadREG(BME280_DIG_H5, 1, LITTLE_ENDIAN) >> 4);
	BME280_Comp.dig_H6 = (int8_t)BME280_ReadREG(BME280_DIG_H6, 1, LITTLE_ENDIAN);
}

void BME280_ForceMODE(){
	uint8_t reg = 0;
	reg = BME280_ReadREG(BME280_CTRL_MEAS, 1, BIG_ENDIAN);
	
	reg &= ~(0b11);
	reg |= 1;
	
	BME280_WriteREG(BME280_CTRL_MEAS, reg);			//enter force mode
	while(BME280_Status_Measuring());				//wait until measuring is completed
}

void BME280_Init(){
	if(BME280_ReadREG(BME280_ID, 1, BIG_ENDIAN) != 0x60) return;	//check if correct sensor is connected
	
	BME280_Reset();									//soft reset sensor
	while(BME280_Status_Copying());					//wait until NVM data are copied to image registers
	BME280_Read_CompensationPAR();					//read compensation parameters
	
	BME280_WriteREG(BME280_CTRL_HUM, 0x01);			//set humidity control register
	BME280_WriteREG(BME280_CONFIG, 0x0);			//set config register
	BME280_WriteREG(BME280_CTRL_MEAS, 0x24);		//set pressure and temperature control register + sensor mode
}

int32_t BME280_TempCOMP(){
	int32_t adc_T = (BME280_ReadREG(BME280_TEMP_DATA, 3, BIG_ENDIAN) >> 4);	//read temperature data from ADC register
	
	//temperature compensation
	int32_t var1, var2, T;
	var1 = ((((adc_T >> 3) - ((int32_t)BME280_Comp.dig_T1 << 1))) * ((int32_t)BME280_Comp.dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)BME280_Comp.dig_T1)) * ((adc_T >> 4) - ((int32_t)BME280_Comp.dig_T1))) >> 12) * ((int32_t)BME280_Comp.dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	
	return T;
}

uint32_t BME280_PressCOMP(){
	int32_t adc_P = (BME280_ReadREG(BME280_PRESS_DATA, 3, BIG_ENDIAN) >> 4);	//read pressure data from ADC register
	
	//pressure compensation
	int64_t var1, var2, p;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)BME280_Comp.dig_P6;
	var2 = var2 + ((var1 * (int64_t)BME280_Comp.dig_P5) << 17);
	var2 = var2 + (((int64_t)BME280_Comp.dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)BME280_Comp.dig_P3) >> 8) + ((var1 * (int64_t)BME280_Comp.dig_P2) << 12);
	var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)BME280_Comp.dig_P1) >> 33;
	if(var1 == 0) return 0;
	p = 1048576 - adc_P;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((int64_t)BME280_Comp.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((int64_t)BME280_Comp.dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)BME280_Comp.dig_P7) << 4);
	
	return (uint32_t)p;
} 

uint32_t BME280_HumCOMP(){
	int32_t adc_H = BME280_ReadREG(BME280_HUM_DATA, 2, BIG_ENDIAN);		//read humidity data from ADC register
	
	//humidity compensation
	int32_t var1;
	var1 = (t_fine - ((int32_t)76800));
	var1 = (((((adc_H << 14) - (((int32_t)BME280_Comp.dig_H4) << 20) - (((int32_t)BME280_Comp.dig_H5) * var1)) + ((int32_t)16384)) >> 15) * (((((((var1 * ((int32_t)BME280_Comp.dig_H6)) >> 10) * (((var1 * ((int32_t)BME280_Comp.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)BME280_Comp.dig_H2) + 8192) >> 14));
	var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t)BME280_Comp.dig_H1)) >> 4));
	var1 = (var1 < 0 ? 0 : var1);
	var1 = (var1 > 419430400 ? 419430400 : var1);
	
	return (uint32_t)(var1 >> 12);
}

int32_t BME280_Temperature(){
	BME280_ForceMODE();
	return BME280_TempCOMP();
}

uint32_t BME280_Pressure(){
	BME280_ForceMODE();
	BME280_TempCOMP();
	return (((BME280_PressCOMP() / 256) + (100 / 2)) / 100);
}

uint32_t BME280_Humidity(){
	BME280_ForceMODE();
	BME280_TempCOMP();
	return ((BME280_HumCOMP() + (1024 / 2)) / 1024);
}

struct Measurments BME280_MeasureAll(){
	struct Measurments meas;
	BME280_ForceMODE();
	meas.Temperature = BME280_TempCOMP();
	meas.Pressure = (((BME280_PressCOMP() / 256) + (100 / 2)) / 100);
	meas.Humidity = ((BME280_HumCOMP() + (1024 / 2)) / 1024);
	
	return meas;
}