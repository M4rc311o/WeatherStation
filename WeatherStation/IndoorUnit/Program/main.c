/*
 * WS_indoor_unit.c
 *
 * Created: 19.02.2022 11:38:49
 * Author : Marcel Kubín
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "SH1106/SH1106.h"
#include "SHT31/SHT31.h"
#include "VirtualWire/VirtualWire.h"
#include "millis/millis.h"

void Renew_SHT31Data();
void WDT_2sR();

struct Measurments SHT31_Data;
struct Outer_Data {
	int16_t Temperature;
	uint8_t Humidity;
	uint16_t Pressure;
} BME280_Data;
_Bool last_bState = 0;
_Bool current_bState;
_Bool d_awake = 0;
_Bool s_line = 0;
uint64_t last_rTime = 0;
uint64_t last_lChange = 0;

int main(void)
{	
	WDT_2sR();					//set 2s watchdog
	
	ADCSRA = 0;					//make sure that ADC is turned off before shut down
	PRR |= (1 << PRUSART0) | (1 << PRADC) | (1 << PRTIM0);	//turn off unnecessary  parts
	
	DDRD &= ~(1 << PORTD2);		//set button as input
	
	TWI_Init(400, 0);					//initialize TWI
	SH1106_Init(SH1106_ADDRESS_IN);		//initialize SH1106 inner
	SH1106_Clear(SH1106_ADDRESS_IN);	//clear SH1106 inner
	SH1106_Sleep(SH1106_ADDRESS_IN);	//set SH1106 inner to sleep
	SH1106_Init(SH1106_ADDRESS_OUT);	//initialize SH1106 outer
	SH1106_Clear(SH1106_ADDRESS_OUT);	//clear SH1106 outer
	SH1106_Sleep(SH1106_ADDRESS_OUT);	//set SH1106 outer to sleep
	vw_setup(2000);						//initialize VirtulWire
	vw_rx_start();						//start receiving
	sei();
    
    while (1){
		//declare buffer for VirtualWire
		uint8_t RX_buffer[VW_MAX_MESSAGE_LEN];
		uint8_t RX_bufferL = VW_MAX_MESSAGE_LEN;
		
		//check for message with correct CRC
		if(vw_get_message(RX_buffer, &RX_bufferL)){
			BME280_Data.Temperature = (int16_t)(((RX_buffer[0] & 0x7F) << 8) | RX_buffer[1]);
			if(RX_buffer[0] & 0x80) BME280_Data.Temperature *= -1; 
			BME280_Data.Humidity = RX_buffer[2];
			BME280_Data.Pressure = (uint16_t)((RX_buffer[3] << 8) | RX_buffer[4]);
		}
		
		//turn on displays when button is pressed
		current_bState = ((PIND & (1 << PIND2)) >> PIND2);
		if(current_bState != last_bState){
			last_bState = current_bState;
			if(!((PIND & (1 << PIND2)) >> PIND2)){
				if(!d_awake){
					d_awake = 1;
					s_line = 0;
					Renew_SHT31Data();
					SH1106_WakeUP(SH1106_ADDRESS_IN);
					SH1106_WakeUP(SH1106_ADDRESS_OUT);
					SH1106_Init(SH1106_ADDRESS_IN);
					SH1106_Init(SH1106_ADDRESS_OUT);
					SH1106_Refresh_IN(SHT31_Data.Temperature, SHT31_Data.Humidity);
					SH1106_Refresh_OUT(BME280_Data.Temperature, BME280_Data.Humidity, BME280_Data.Pressure, s_line);
					millis_Init();
					millis_Start();
				}
			}
		}
		
		if(d_awake){
			//refresh displays
			if(millis() - last_rTime > 500){
				last_rTime = millis();
				Renew_SHT31Data();
				SH1106_Refresh_IN(SHT31_Data.Temperature, SHT31_Data.Humidity);
				SH1106_Refresh_OUT(BME280_Data.Temperature, BME280_Data.Humidity, BME280_Data.Pressure, s_line);
			}
			
			//change second line of outdoor unit
			if(millis() - last_lChange > 2000){
				last_lChange = millis();
				s_line ^= 1;	
			}
			
			//go to sleep after 6s
			if(millis() > 6000){
				d_awake = 0;
				millis_Reset();
				SH1106_Sleep(SH1106_ADDRESS_IN);
				SH1106_Sleep(SH1106_ADDRESS_OUT);
			}	
		}
		
		wdt_reset();
    }
}

//renew data from SHT31
void Renew_SHT31Data(){
	SHT31_Data = SHT31_Measure();
}

//setting up 2s watchdog
void WDT_2sR(){
	MCUSR = 0;
	wdt_disable();
	wdt_reset();
	WDTCSR = (1 << WDCE) | (1 << WDE);
	WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);		//set watchdog to reset mode time-out to 2s
	wdt_reset();
}