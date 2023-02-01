/*
 * SH1106.c
 *
 * Created: 10.01.2022 13:14:13
 *  Author: M4rc3110
 */ 

#include "SH1106.h"
#include "SH1106_Commands.h"
#include <avr/pgmspace.h>
#include "symbols.h"

#define SUCCESS 0
#define ERROR 1

#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2

void SH1106_Command_sequence(uint8_t address, uint8_t *sequence, uint8_t Byte_count);
void SH1106_Command(uint8_t address, uint8_t command);
void SH1106_Clear_buffer();
void SH1106_Send_buffer(uint8_t address);
void SH1106_Print_symbol(uint8_t symbol, uint8_t start_r, uint8_t start_c);
void SH1106_Print_unit(uint8_t unit, uint8_t start_r, uint8_t start_c);
void SH1106_Print_n(uint8_t number, uint8_t start_r, uint8_t start_c);
void SH1106_Print_decPoint(uint8_t start_r, uint8_t start_c);
void SH1106_Print_minus(uint8_t start_r, uint8_t start_c);

uint8_t Init_sequence[] = {
	SH1106_DISPLAY_OFF,				//turn display OFF
	SH1106_SEGREMAP_INVERT,			//set segment remap to normal (address 0 is mapped to SEG0)
	SH1106_SET_COMCONF, 0x12,		//set COM pins hardware configuration
	SH1106_SCANDIR_INVERT,			//set scan direction to normal (from COM0 to COM[n - 1])
	SH1106_SET_MULTIPLEXRATIO, 0x3F,//set display MUX
	SH1106_SET_OFFSET, 0x00,		//set display offset to 0
	SH1106_SEGREMAP_NORMAL,			//set segment remap to normal (address 0 is mapped to SEG0)
	SH1106_SET_VCOM, 0x35,			//set deselect voltage level
	SH1106_SET_CONTRAST, 0x7F,		//set display contrast
	SH1106_ENTIREDISPLAYON_RESUME,	//disable entire display on
	SH1106_DISPLAY_NORMAL,			//set display to normal mode (non inverted)
	SH1106_SET_CLOCKDIV, 0x50,		//set display clock divide ration and oscillator frequency
	SH1106_SET_PRECHARGE, 0x22,		//set pre-charge period
	SH1106_SET_CHARGEPUMP,			//turn on charge pump
	SH1106_SET_DC_DC, 0x8B,			//turn on DC-DC converter
	SH1106_DISPLAY_ON,				//turn display ON
	SH1106_SET_START_LINE,			//set display start line to 0
	SH1106_SET_PAGE_ADD_0,			//set page address
	SH1106_SET_LOWER_COLUMN_START_ADD, 0x02,	//set column
	SH1106_SET_HIGHER_COLUMN_START_ADD, 0x10
};

static uint8_t display_buffer[8][129];

//send sequence of commands
void SH1106_Command_sequence(uint8_t address, uint8_t *sequence, uint8_t Byte_count){
	uint8_t	com_s[Byte_count + 1];
	com_s[0] = 0x0;
	for(uint8_t c = 0; c < Byte_count; c++) com_s[c + 1] = sequence[c];
	TWI_Write(address, com_s, sizeof(com_s));
}

//send on command
void SH1106_Command(uint8_t address, uint8_t command){
	uint8_t com[2];
	com[0] = 0x00;
	com[1] = command;
	TWI_Write(address, com, 2);
}

//clear buffer array
void SH1106_Clear_buffer(){
	for(uint8_t r = 0; r < 8; r++){
		for(uint8_t c = 0; c < 129; c++) display_buffer[r][c] = 0x00;
	}
}

//send buffer
void SH1106_Send_buffer(uint8_t address){
	uint8_t shift[] = {
		SH1106_SET_START_LINE,
		SH1106_SET_PAGE_ADD_0,
		SH1106_SET_LOWER_COLUMN_START_ADD, 0x02,
		SH1106_SET_HIGHER_COLUMN_START_ADD, 0x10
	};
	
	for(uint8_t r = 0; r < 8; r++){
		display_buffer[r][0] = 0x40;
		SH1106_Command_sequence(address, shift, sizeof(shift));
		TWI_Write(address, display_buffer[r], 129);	
		shift[1]++;
	}
}

//initialize display
void SH1106_Init(uint8_t address){
	SH1106_Command_sequence(address, Init_sequence, sizeof(Init_sequence));
	SH1106_Clear_buffer();
	SH1106_Send_buffer(address);
}

void SH1106_Clear(uint8_t address){
	SH1106_Clear_buffer();
	SH1106_Send_buffer(address);
}

void SH1106_Sleep(uint8_t address){
	SH1106_Command(address, SH1106_DISPLAY_OFF);
}

void SH1106_WakeUP(uint8_t address){
	SH1106_Command(address, SH1106_DISPLAY_ON);
}

//refresh display with indoor values
_Bool SH1106_Refresh_IN(int16_t temperature, uint8_t humidity){
	SH1106_Clear_buffer();
	
	//symbols and units
	SH1106_Print_symbol(TEMPERATURE, 0, 128);
	SH1106_Print_unit(TEMPERATURE, 0, 24);
	SH1106_Print_symbol(HUMIDITY, 4, 128);
	SH1106_Print_unit(HUMIDITY, 4, 24);
	
	//temperature
	if((temperature < -9999) || (temperature > 9999)) return ERROR;
	_Bool negative = 0;
	if(temperature < 0){
		temperature *= -1;
		negative = 1;
	}
	if(negative) SH1106_Print_minus(2, 99);
	if(temperature / 1000) SH1106_Print_n(temperature / 1000, 0, 81);
	SH1106_Print_n((temperature % 1000) / 100, 0, 63);
	SH1106_Print_n(((temperature % 100) / 10), 0, 45);
	SH1106_Print_decPoint(3, 48);
	
	//humidity
	if((humidity < 0) || (humidity > 100)) return ERROR;
	if(humidity / 10) SH1106_Print_n(humidity / 10, 4, 63);
	SH1106_Print_n(humidity % 10, 4, 45);
	
	SH1106_Send_buffer(SH1106_ADDRESS_IN);
	
	return SUCCESS;
}

_Bool SH1106_Refresh_OUT(int16_t temperature, uint8_t humidity, uint16_t pressure, _Bool s_line){
	SH1106_Clear_buffer();
	
	//symbols and units
	SH1106_Print_symbol(TEMPERATURE, 0, 128);
	SH1106_Print_unit(TEMPERATURE, 0, 24);
	if(s_line){
		SH1106_Print_symbol(PRESSURE, 4, 128);
		SH1106_Print_unit(PRESSURE, 4, 24);
	}
	else if(!s_line){
		SH1106_Print_symbol(HUMIDITY, 4, 128);
		SH1106_Print_unit(HUMIDITY, 4, 24);
	}
	
	//temperature
	if((temperature < -9999) || (temperature > 9999)) return ERROR;
	_Bool negative = 0;
	if(temperature < 0){
		temperature *= -1;
		negative = 1;
	}
	if(negative) SH1106_Print_minus(2, 99);
	if(temperature / 1000) SH1106_Print_n(temperature / 1000, 0, 81);
	SH1106_Print_n((temperature % 1000) / 100, 0, 63);
	SH1106_Print_n(((temperature % 100) / 10), 0, 45);
	SH1106_Print_decPoint(3, 48);
	
	if(s_line){
		if((pressure < 0) || (pressure > 9999)) return ERROR;
		if(pressure / 1000) SH1106_Print_n(pressure / 1000, 4, 99);
		if(pressure / 100) SH1106_Print_n((pressure % 1000) / 100, 4, 81);
		if(pressure / 10) SH1106_Print_n((pressure % 100) / 10, 4, 63);
		SH1106_Print_n(pressure % 10, 4, 45);
	}
	else if(!s_line){
		if((humidity < 0) || (humidity > 100)) return ERROR;
		if(humidity / 10) SH1106_Print_n(humidity / 10, 4, 63);
		SH1106_Print_n(humidity % 10, 4, 45);
	}
	
	SH1106_Send_buffer(SH1106_ADDRESS_OUT);
	
	return SUCCESS;
}

void SH1106_Print_symbol(uint8_t symbol, uint8_t start_r, uint8_t start_c){
	const uint8_t (*s)[24];
	
	switch(symbol){
		case TEMPERATURE:
		s = &(temperature_s[0]);
		break;
		
		case HUMIDITY:
		s = &(humidity_s[0]);
		break;
		
		case PRESSURE:
		s = &(pressure_s[0]);
		break;
		
		default:
		return;
	}
	
	//print symbol
	for(uint8_t r = 0; r < 4; r++){
		for(uint8_t c = 0; c < 24; c++) display_buffer[r + start_r][start_c - c] = pgm_read_byte(&(s[r][c]));
	}
}

void SH1106_Print_unit(uint8_t unit, uint8_t start_r, uint8_t start_c){
	const uint8_t (*u)[24];
	
	switch(unit){
		case TEMPERATURE:
		u = &(cdegree_u[0]);
		break;
		
		case HUMIDITY:
		u = &(rhp_u[0]);
		break;
		
		case PRESSURE:
		u = &(hpa_u[0]);
		break;
		
		default:
		return;
	}
	
	//print unit
	for(uint8_t r = 0; r < 4; r++){
		for(uint8_t c = 0; c < 24; c++) display_buffer[r + start_r][start_c - c] = pgm_read_byte(&(u[r][c]));
	}
}

void SH1106_Print_n(uint8_t number, uint8_t start_r, uint8_t start_c){
	const uint8_t (*n)[18];
	
	switch(number){
		case 0:
		n = &(zero_n[0]);
		break;
		
		case 1:
		n = &(one_n[0]);
		break;
		
		case 2:
		n = &(two_n[0]);
		break;
		
		case 3:
		n = &(three_n[0]);
		break;
		
		case 4:
		n = &(four_n[0]);
		break;
		
		case 5:
		n = &(five_n[0]);
		break;
		
		case 6:
		n = &(six_n[0]);
		break;
		
		case 7:
		n = &(seven_n[0]);
		break;
		
		case 8:
		n = &(eight_n[0]);
		break;

		case 9:
		n = &(nine_n[0]);
		break;
		
		default:
		return;
	}
	
	for(uint8_t r = 0; r < 4; r++){
		for(uint8_t c = 0; c < 18; c++) display_buffer[r + start_r][start_c - c] = pgm_read_byte(&(n[r][c]));
	}
}

void SH1106_Print_minus(uint8_t start_r, uint8_t start_c){
	for(uint8_t c = 0; c < 18; c++) display_buffer[start_r][start_c - c] = pgm_read_byte(&(minus[c]));
}

void SH1106_Print_decPoint(uint8_t start_r, uint8_t start_c){
	for(uint8_t c = 0; c < 6; c++) display_buffer[start_r][start_c - c] = pgm_read_byte(&(dec_point[c]));
}