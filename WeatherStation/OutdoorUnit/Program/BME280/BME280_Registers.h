/*
 * BME280_Registers.h
 *
 * Created: 21.11.2021 12:46:45
 *  Author: M4rc3110
 */ 


#ifndef BME280_REGISTERS_H_
#define BME280_REGISTERS_H_

#define BME280_ID 0xD0
#define BME280_RESET 0xE0
#define BME280_CTRL_HUM 0xF2
#define BME280_STATUS 0xF3
#define BME280_CTRL_MEAS 0xF4
#define BME280_CONFIG 0xF5
#define BME280_PRESS_DATA 0xF7
#define BME280_TEMP_DATA 0xFA
#define BME280_HUM_DATA 0xFD

#define BME280_DIG_T1 0x88
#define BME280_DIG_T2 0x8A
#define BME280_DIG_T3 0x8C

#define BME280_DIG_P1 0x8E
#define BME280_DIG_P2 0x90
#define BME280_DIG_P3 0x92
#define BME280_DIG_P4 0x94
#define BME280_DIG_P5 0x96
#define BME280_DIG_P6 0x98
#define BME280_DIG_P7 0x9A
#define BME280_DIG_P8 0x9C
#define BME280_DIG_P9 0x9E

#define BME280_DIG_H1 0xA1
#define BME280_DIG_H2 0xE1
#define BME280_DIG_H3 0xE3
#define BME280_DIG_H4 0xE4
#define BME280_DIG_H5 0xE5
#define BME280_DIG_H6 0xE7

#endif /* BME280_REGISTERS_H_ */