/*
 * SH1106.h
 *
 * Created: 10.01.2022 13:14:42
 *  Author: M4rc3110
 */ 


#ifndef SSH1106_H_
#define SSH1106_H_

#include <avr/io.h>
#include "../TWI/TWI.h"

#define SH1106_ADDRESS_IN 0x3C
#define SH1106_ADDRESS_OUT 0x3D

void SH1106_Init(uint8_t address);
void SH1106_Clear(uint8_t address);
void SH1106_Sleep(uint8_t address);
void SH1106_WakeUP(uint8_t address);
_Bool SH1106_Refresh_IN(int16_t temperature, uint8_t humidity);
_Bool SH1106_Refresh_OUT(int16_t temperature, uint8_t humidity, uint16_t pressure, _Bool s_line);
#endif /* SH1106_H_ */