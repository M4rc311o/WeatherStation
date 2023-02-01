/*
 * CRC_8.h
 *
 * Created: 26.12.2021 13:47:05
 *  Author: M4rc3110
 */ 


#ifndef CRC_8_H_
#define CRC_8_H_

#include <avr/io.h>

uint8_t CRC_8_Check(uint8_t poly, uint8_t init, uint8_t f_XOR, uint8_t *data, uint8_t byte_count);
uint8_t CRC_8_Compute(uint8_t poly, uint8_t init, uint8_t f_XOR, uint8_t *data, uint8_t byte_count);

#endif /* CRC_8_H_ */