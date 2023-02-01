/*
 * SSD1306.h
 *
 * Created: 27.10.2021 18:06:30
 *  Author: M4rc3110
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_

#include <avr/io.h>
#include "../TWI/TWI.h"

#define SSD1306_ADDRESS 0x3C
#define SSD1306_DISPLAY_WIDTH 128
#define SSD1306_DISPLAY_HEIGHT 32

void SSD1306_Init();
_Bool SSD1306_PrintTEMP(int32_t temp);
_Bool SSD1306_PrintHUM(uint32_t hum);
_Bool SSD1306_PrintPRESS(uint32_t press);
void SSD1306_Clear();
void SSD1306_Sleep();
void SSD1306_WakeUP();
#endif /* SSD1306_H_ */