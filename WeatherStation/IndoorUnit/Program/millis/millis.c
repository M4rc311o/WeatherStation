/*
 * millis.c
 *
 * Created: 14.02.2022 12:22:30
 *  Author: M4rc3110
 */ 

#include "millis.h"
#include <avr/interrupt.h>

static volatile uint64_t m_time = 0;

void millis_Init(){
	TCCR2A |= (1 << WGM21);						//set timer to CTC mode
	OCR2A = ((F_CPU / 64) / 1000);				//set timer to compare match at 1ms
	TCCR2B = 0;
}

void millis_Start(){
	TCNT2 = 0;
	TIMSK2 |= (1 << OCIE2A);
	TCCR2B |= (1 << CS22);						//set prescaler 64
}

void millis_Stop(){
	TCCR2B = 0;
	TIMSK2 = 0;
}

void millis_Reset(){
	millis_Stop();
	m_time = 0;	
}

uint64_t millis(){
	return m_time;
}

ISR(TIMER2_COMPA_vect){
	m_time++;
}