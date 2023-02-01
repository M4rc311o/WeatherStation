/*
 * millis.h
 *
 * Created: 14.02.2022 12:22:49
 *  Author: M4rc3110
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_

#include <avr/io.h>

void millis_Init();
void millis_Start();
void millis_Stop();
void millis_Reset();
uint64_t millis();

#endif /* MILLIS_H_ */