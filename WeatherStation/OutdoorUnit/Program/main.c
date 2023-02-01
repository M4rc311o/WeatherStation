/*
 * WS_outdoor_unit.c
 *
 * Created: 09.02.2022 12:40:48
 * Author : Marcel Kubín
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include "BME280/BME280.h"
#include "SSD1306/SSD1306.h"
#include "VirtualWire/VirtualWire.h"
#include "millis/millis.h"

void Renew_BME280Data();
void Send_BME280Data();
void Unit_Sleep();
void WDT_2sR();

enum modes {TEMPERATURE, HUMIDITY, PRESSURE};
enum modes mode;

struct Measurments BME280_Data;
uint64_t last_rTime = 0;
_Bool last_bState = 0;
_Bool current_bState;
volatile _Bool f_run = 0;
volatile _Bool sending = 1;

int main(void)
{	
	WDT_2sR();					//set 2s watchdog

	ADCSRA = 0;					//make sure that ADC is turned off before shut down
	PRR |= (1 << PRUSART0) | (1 << PRADC) | (1 << PRTIM0);	//turn off unnecessary  parts
	
	DDRD &= ~(1 << PORTD2);		//set button pin as input
	
	TWI_Init(100, 0);			//initialize TWI
	BME280_Init();				//initialize BME280
	SSD1306_Init();				//initialize SSD1306
	SSD1306_Sleep();			//set SSD1306 to sleep
	vw_setup(2000);				//initialize VirtulaWire
	
	
    while (1){
		
		//sending data
		if(sending){
			WDT_2sR();
			Renew_BME280Data();
			sei();
			Send_BME280Data();
			Send_BME280Data();
			cli();
			
			Unit_Sleep();			//sleep for 8s
		}
		
		//waked up by button
		else{
			//first run
			if(f_run){
				WDT_2sR();
				sei();
				SSD1306_WakeUP();
				millis_Init();
				millis_Start();
			}
			
			current_bState = ((PIND & (1 << PIND2)) >> PIND2);
			if(current_bState != last_bState || f_run){
				last_bState = current_bState;
				if(!((PIND & (1 << PIND2)) >> PIND2) && !f_run){
					mode++;
					if(mode > 2) mode = 0;
					
					f_run = 1;
					
					millis_Reset();
					millis_Start();
				}
			}
			
			//display refresh
			if(f_run || millis() - last_rTime > 500){
				last_rTime = millis();
				f_run = 0;
				
				switch(mode){
					case TEMPERATURE:
					Renew_BME280Data();
					SSD1306_PrintTEMP(BME280_Data.Temperature);
					break;
					
					case HUMIDITY:
					Renew_BME280Data();
					SSD1306_PrintHUM(BME280_Data.Humidity);
					break;
					
					case PRESSURE:
					Renew_BME280Data();
					SSD1306_PrintPRESS(BME280_Data.Pressure);
					break;
				}
			}
			
			//go to sleep after 3s
			if(millis() > 3000){
				cli();
				SSD1306_Sleep();
				millis_Reset();
				Unit_Sleep();	
			}
		}
		
		wdt_reset();
    }
}

//renew data from BME280
void Renew_BME280Data(){
	BME280_Data = BME280_MeasureAll();
}

//prepare packet and send
void Send_BME280Data(){
	uint8_t TX_buffer[5];
	if(BME280_Data.Temperature >= 0){
		TX_buffer[0] = (uint8_t)(BME280_Data.Temperature >> 8);
		TX_buffer[1] = (uint8_t)(BME280_Data.Temperature & 0xFF);
	}
	else{
		TX_buffer[0] = (uint8_t)((abs(BME280_Data.Temperature) >> 8) | 0x80);
		TX_buffer[1] = (uint8_t)(abs(BME280_Data.Temperature) & 0xFF);
	}
	
	TX_buffer[2] = (uint8_t)BME280_Data.Humidity;
	TX_buffer[3] = (uint8_t)(BME280_Data.Pressure >> 8);
	TX_buffer[4] = (uint8_t)(BME280_Data.Pressure & 0xFF);
	
	vw_send(TX_buffer, sizeof(TX_buffer));
	vw_wait_tx();
}

//go to sleep
void Unit_Sleep(){
	MCUSR = 0;
	wdt_disable();
	wdt_reset();
	WDTCSR = (1 << WDCE) | (1 << WDE);
	WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);		//set watchdog to interrupt mode time-out to 8s
	wdt_reset();
	EIMSK |= (1 << INT0);									//enable mask on INT0
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
	cli();
}

//setting up 2s watchdog
void WDT_2sR(){
	MCUSR = 0;
	wdt_disable();
	wdt_reset();
	WDTCSR = (1 << WDCE) | (1 << WDE);
	WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);		//set watchdog to interrupt mode time-out to 8s
	wdt_reset();
}

//interrupt handler for button
ISR(INT0_vect){
	wdt_disable();
	EIMSK &= ~(1 << INT0);
	mode = TEMPERATURE;
	sending = 0;
	f_run = 1;
}

//interrupt handler for watchdog overflow
ISR(WDT_vect){
	wdt_disable();
	EIMSK &= ~(1 << INT0);
	sending = 1;
}