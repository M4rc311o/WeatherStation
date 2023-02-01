/*
 * TWI.h
 *
 * Created: 21.07.2021 18:14:58
 *  Author: M4rc3110
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <util/twi.h>

#define SCL_PIN PORTC5
#define SDA_PIN PORTC4

typedef uint8_t error_code;

void TWI_Init(uint16_t FREQUENCY, _Bool internal_pullup_en);
error_code TWI_Write(uint8_t Slave_adress, uint8_t *Data, uint16_t Byte_count);
error_code TWI_Read(uint8_t Slave_address, uint8_t *Data, uint16_t Byte_count);

#endif /* TWI_H_ */