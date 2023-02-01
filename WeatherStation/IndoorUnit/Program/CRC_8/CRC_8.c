/*
 * CRC_8.c
 *
 * Created: 26.12.2021 13:46:42
 *  Author: M4rc3110
 */ 

#include "CRC_8.h"

uint8_t CRC_8_Check(uint8_t poly, uint8_t init, uint8_t f_XOR, uint8_t *data, uint8_t byte_count){
	uint8_t CRC = init;
	
	for(uint8_t b = 0; b < byte_count; b++){
		CRC ^= (b == (byte_count - 1)) ? (data[b] ^ f_XOR) : data[b];
		
		for(uint8_t i = 0; i < 8; i++){
			if((CRC & 0x80) != 0){
				CRC = ((CRC << 1) ^ poly);
			}
			
			else CRC <<= 1;
		}
	}
	
	return CRC;
}

uint8_t CRC_8_Compute(uint8_t poly, uint8_t init, uint8_t f_XOR, uint8_t *data, uint8_t byte_count){
	uint8_t CRC = init;
	
	for(uint8_t b = 0; b < byte_count; b++){
		CRC ^= data[b];
		
		for(uint8_t i = 0; i < 8; i++){
			if((CRC & 0x80) != 0){
				CRC = ((CRC << 1) ^ poly);
			}
			
			else CRC <<= 1;
		}
	}
	
	return (CRC ^ f_XOR);
}