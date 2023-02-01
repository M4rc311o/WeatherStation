/*
 * TWI.c
 *
 * Created: 21.07.2021 18:14:09
 * Author : M4rc3110
 */ 

#include "TWI.h"

#define SUCCES 0


void TWI_Init(uint16_t FREQUENCY, _Bool internal_pullup_en){
	PRR &= ~(1 << PRTWI);								//disable power reduction on TWI
	TWSR &= ~(0b11);									//set prescaler to one
	TWBR = ((F_CPU / (2000 *(long)FREQUENCY)) - 8);		//calculates the value for TWBR
	
	//enable internal pullup
	if(internal_pullup_en){
		DDRC &= ~((1 << SCL_PIN) | (1 << SDA_PIN));
		PORTC |= ((1 << SCL_PIN) | (1 << SDA_PIN));
	}
	
	//disable internal pullup
	else{
		DDRC &= ~((1 << SCL_PIN) | (1 << SDA_PIN));
		PORTC &= ~((1 << SCL_PIN) | (1 << SDA_PIN));
	}
	
	TWCR = (1 << TWEN);	//enable TWI
}

error_code TWI_Start(){
	TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));	//send START condition
	while(!(TWCR & (1 << TWINT)));						//wait until the START condition is sent
	if(TW_STATUS != TW_START) return TW_STATUS;			//check for errors
	return SUCCES;
}

void TWI_Stop(){
	TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO));	//send STOP condition
}

error_code TWI_TransmitSLA(uint8_t SLA){
	TWDR = SLA;											//load SLA + R/W into TWDR
	TWCR = ((1 << TWINT) | (1 << TWEN));				//send SLA + R/W
	while(!(TWCR & (1 << TWINT)));						//wait until the SLA + R/W condition is sent
	if((TW_STATUS != TW_MR_SLA_ACK) && (TW_STATUS != TW_MT_SLA_ACK)) return TW_STATUS;	//check for errors
	return SUCCES;
}

error_code TWI_TransmitData(uint8_t Data){
	TWDR = Data;										//load Data into TWDR
	TWCR = ((1 << TWINT) | (1 << TWEN));				//send Data
	while(!(TWCR & (1 << TWINT)));						//wait until the Data are sent
	if(TW_STATUS != TW_MT_DATA_ACK) return TW_STATUS;	//check for errors
	return SUCCES;
}

error_code TWI_ReceiveData(_Bool ACK, uint8_t *Address){
	if(ACK){
		TWCR = ((1 << TWINT) | (1 << TWEA) | (1 << TWEN));	//get ready to receive the Data and send ACK after
		while(!(TWCR & (1 << TWINT)));					//wait until the Data are received
		if(TW_STATUS != TW_MR_DATA_ACK) return TW_STATUS;	//check for errors
		*Address = TWDR;								//save received Byte
	}
	
	else{
		TWCR = ((1 << TWINT) | (1 << TWEN));			//get ready to receive the Data and send NACK after
		while(!(TWCR & (1 << TWINT)));					//wait until the Data are received
		if(TW_STATUS != TW_MR_DATA_NACK) return TW_STATUS;	//check for errors
		*Address = TWDR;								//save received Byte
	}
	
	return SUCCES;
}

error_code TWI_Write(uint8_t Slave_adress, uint8_t *Data, uint16_t Byte_count){
	uint8_t error_n;
	
	error_n = TWI_Start();								//send START condition
	if(error_n != SUCCES) return error_n;				//returns an error code if any
	
	error_n = TWI_TransmitSLA(Slave_adress << 1);		//send SLA + W
	if(error_n != SUCCES) return error_n;				//returns an error code if any
	
	for(uint16_t c = 0; c < Byte_count; c++){
		error_n = TWI_TransmitData(*(Data + c));		//send Data
		if(error_n != SUCCES) return error_n;			//returns an error code if any
	}
	
	TWI_Stop();											//send STOP condition
	
	return SUCCES;
}

error_code TWI_Read(uint8_t Slave_address, uint8_t *Data, uint16_t Byte_count){
	uint8_t error_n;
	
	error_n = TWI_Start();								//send START condition
	if(error_n != SUCCES) return error_n;				//returns an error code if any
	
	error_n = TWI_TransmitSLA((Slave_address << 1) | 0b1);		//send SLA + R
	if(error_n != SUCCES) return error_n;				//returns an error code if any
	
	for(uint16_t c = 0; c < (Byte_count - 1); c++){
		error_n = TWI_ReceiveData(1, (Data + c));		//send ACK after data receive
		if(error_n != SUCCES) return error_n;			//returns an error code if any
	}
	
	error_n = TWI_ReceiveData(0, (Data + (Byte_count - 1)));	//send NACK after data receive
	if(error_n != SUCCES) return error_n;				//returns an error code if any
	
	TWI_Stop();											//send STOP condition
	
	return SUCCES;
}