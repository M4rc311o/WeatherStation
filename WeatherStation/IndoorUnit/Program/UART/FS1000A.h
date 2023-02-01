/*
 * FS1000A.h
 *
 * Created: 21.01.2022 14:19:02
 *  Author: M4rc3110
 */ 


#ifndef FS1000A_H_
#define FS1000A_H_

#include <avr/io.h>

#define BAUD_RATE 9600

void USART_Init();
void FS1000A_Send();
void USART_Transmit(uint8_t data);

#endif /* FS1000A_H_ */