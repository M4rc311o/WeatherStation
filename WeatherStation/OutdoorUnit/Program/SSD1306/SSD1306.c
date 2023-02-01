/*
 * SSD1306.c
 *
 * Created: 27.10.2021 18:06:12
 *  Author: M4rc3110
 */ 

#include "SSD1306.h"
#include <avr/pgmspace.h>
#include "symbols.h"
#include "SSD1306_Commands.h"

#define SUCCESS 0
#define ERROR 1

#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2

void SSD1306_Command_sequence(uint8_t *sequence, uint8_t Byte_count);
void SSD1306_Command(uint8_t command);
void SSD1306_Clear_buffer();
void SSD1306_Send_buffer();
void SSD1306_Print_su(uint8_t su);
void SSD1306_Print_n(uint8_t number, uint8_t start_c);
void SSD1306_Print_minus(uint8_t start_c);
void SSD1306_Print_decPoint(uint8_t start_c);


uint8_t Init_sequence[] = {
	SSD1306_DISPLAY_OFF,			//turn display OFF
	SSD1306_SET_MULTIPLEXRATIO, SSD1306_DISPLAY_HEIGHT - 1,		//set display MUX
	SSD1306_SET_OFFSET, 0x0,		//set display offset to 0
	SSD1306_SET_START_LINE,			//set display start line to 0
	SSD1306_SEGREMAP_NORMAL,		//set segment remap to normal (address 0 is mapped to SEG0)
	SSD1306_SCANDIR_NORMAL,			//set scan direction to normal (from COM0 to COM[n - 1])
	SSD1306_SET_COMCONF, 0x02,		//set COM pins hardware configuration
	SSD1306_SET_CONTRAST, 0x7F,		//set display contrast
	SSD1306_ENTIREDISPLAYON_RESUME,	//disable entire display on
	SSD1306_DISPLAY_NORMAL,			//set display to normal mode (non inverted)
	SSD1306_DEACTIVATESCROLL,		//deactivate scroll
	SSD1306_SET_MEMADRESSMODE, 0x0,	//set horizontal addressing mode
	SSD1306_SET_PAGE_ADD, 0x0, 0x3,	//set start and end page address
	SSD1306_SET_CLOCKDIV, 0x80,		//set display clock divide ration and oscillator frequency
	SSD1306_SET_PRECHARGE, 0xF1,	//set pre-charge period
	SSD1306_SET_VCOM, 0x30,			//set deselect voltage level
	SSD1306_SET_CHARGEPUMP, 0x14,	//turn on charge pump
	SSD1306_DISPLAY_ON				//turn display ON
};

static uint8_t display_buffer[513];

//send sequence of commands
void SSD1306_Command_sequence(uint8_t *sequence, uint8_t Byte_count){
	uint8_t	com_s[Byte_count + 1];
	com_s[0] = 0x0;
	for(uint8_t c = 0; c < Byte_count; c++) com_s[c + 1] = sequence[c];
	TWI_Write(SSD1306_ADDRESS, com_s, sizeof(com_s));
}

//send on command
void SSD1306_Command(uint8_t command){
	uint8_t com[2];
	com[0] = 0b00000000;
	com[1] = command;
	TWI_Write(SSD1306_ADDRESS, com, 2);
}

//clear buffer array
void SSD1306_Clear_buffer(){
	for(uint16_t i = 0; i < 513; i++) display_buffer[i] = 0;
}

//send buffer
void SSD1306_Send_buffer(){
	display_buffer[0] = 0x40;
	TWI_Write(SSD1306_ADDRESS, display_buffer, 513);
}

//initialize display
void SSD1306_Init(){
	SSD1306_Command_sequence(Init_sequence, sizeof(Init_sequence));
	SSD1306_Clear_buffer();
}

void SSD1306_Clear(){
	SSD1306_Clear_buffer();
	SSD1306_Send_buffer();
}

void SSD1306_Sleep(){
	SSD1306_Command(SSD1306_DISPLAY_OFF);
}

void SSD1306_WakeUP(){
	SSD1306_Command(SSD1306_DISPLAY_ON);
}

//print humidity on screen
_Bool SSD1306_PrintHUM(uint32_t hum){
	if((hum < 0) || (hum > 100)) return ERROR;
	SSD1306_Clear_buffer();
	SSD1306_Print_su(HUMIDITY);
	if(hum / 10) SSD1306_Print_n(hum / 10, 65);
	SSD1306_Print_n(hum % 10, 83);
	SSD1306_Send_buffer();
	return SUCCESS;
}

//print temperature on screen
_Bool SSD1306_PrintTEMP(int32_t temp){
	if((temp < -9999) || (temp > 9999)) return ERROR;
	_Bool negative = 0;
	SSD1306_Clear_buffer();
	SSD1306_Print_su(TEMPERATURE);
	if(temp < 0){
		temp *= -1;
		negative = 1;
	}
	if(negative) SSD1306_Print_minus(29);
	if(temp / 1000) SSD1306_Print_n(temp / 1000, 47);
	SSD1306_Print_n((temp % 1000) / 100, 65);
	SSD1306_Print_n(((temp % 100) / 10), 83);
	SSD1306_Print_decPoint(80);
	SSD1306_Send_buffer();
	return SUCCESS;
}

//print pressure on screen
_Bool SSD1306_PrintPRESS(uint32_t press){
	if((press < 0) || (press > 9999)) return ERROR;
	SSD1306_Clear_buffer();
	SSD1306_Print_su(PRESSURE);
	if(press / 1000) SSD1306_Print_n(press / 1000, 29);
	if(press / 100) SSD1306_Print_n((press % 1000) / 100, 47);
	if(press / 10) SSD1306_Print_n((press % 100) / 10, 65);
	SSD1306_Print_n(press % 10, 83);
	SSD1306_Send_buffer();
	return SUCCESS;
}

void SSD1306_Print_su(uint8_t su){
	const uint8_t (*s)[24];
	const uint8_t (*u)[24];
	
	switch(su){
		case TEMPERATURE:
			s = &(temperature_s[0]);
			u = &(cdegree_u[0]);
			break;
			
		case HUMIDITY:
			s = &(humidity_s[0]);
			u = &(rhp_u[0]);
			break;
			
		case PRESSURE:
			s = &(pressure_s[0]);
			u = &(hpa_u[0]);
			break;
			
		default:
			return;
	}
	
	//variable symbol
	for(uint8_t r = 0; r < 4; r++){
		for(uint8_t b = 0; b < 24; b++) display_buffer[1 + (SSD1306_DISPLAY_WIDTH * r) + b] = pgm_read_byte(&(s[0 + r][b]));
	}
	
	//variable_unit
	for(uint8_t r = 0; r < 4; r++){
		for(uint8_t b = 0; b < 24; b++) display_buffer[105 + (SSD1306_DISPLAY_WIDTH * r) + b] = pgm_read_byte(&(u[0 + r][b]));
	}
}

void SSD1306_Print_n(uint8_t number, uint8_t start_c){
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
		for(uint8_t b = 0; b < 18; b++) display_buffer[start_c + (SSD1306_DISPLAY_WIDTH * r) + b] = pgm_read_byte(&(n[0 + r][b]));
	}
}

void SSD1306_Print_minus(uint8_t start_c){
	for(uint8_t b = 0; b < 18; b++) display_buffer[start_c + 256 + b] = pgm_read_byte(&(minus[b]));
}

void SSD1306_Print_decPoint(uint8_t start_c){
	for(uint8_t b = 0; b < 6; b++) display_buffer[start_c + 384 + b] = pgm_read_byte(&(dec_point[b]));
}