/*
 * FS1000A.c
 *
 * Created: 21.01.2022 14:18:24
 *  Author: M4rc3110
 */ 

#include "FS1000A.h"

//initialize communication (USART in asynchronous mode)
void USART_Init(){
	uint16_t UBRR = ((F_CPU / (16 * (long)BAUD_RATE)) - 1);
	
	//set baud rate
	UBRR0H = (uint8_t) (UBRR >> 8);
	UBRR0L = (uint8_t) UBRR;
	
	//set frame format
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 <<UCSZ00);
}

//send one byte of data
void USART_Transmit(uint8_t data){
	//wait until transmit buffer is ready to receive new data
	while(!(UCSR0A & (1 << UDRE0)));
	
	UDR0 = data;
}

void FS1000A_Send(){
	USART_Transmit(0x41);
	USART_Transmit(0x68);
	USART_Transmit(0x6F);
	USART_Transmit(0x6A);
}