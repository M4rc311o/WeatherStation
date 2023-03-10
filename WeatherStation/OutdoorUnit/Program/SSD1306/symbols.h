/*
 * symbols.h
 *
 * Created: 14.11.2021 13:47:49
 *  Author: M4rc3110
 */ 


#ifndef SYMBOLS_H_
#define SYMBOLS_H_

const uint8_t temperature_s[4][24] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x04, 0xe2, 0xe2, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x3f, 0x00, 0xff, 0xff, 0x00, 0x3f, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x19, 0x20, 0x20, 0x4f, 0x4f, 0x4b, 0x4f, 0x20, 0x20, 0x19, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t humidity_s[4][24] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xf0, 0x1c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x06, 0x18, 0xf0, 0x98, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x38, 0x60, 0x80, 0x00},
	{0x00, 0x1f, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x00, 0xe0, 0x9f, 0x00, 0x00, 0x00, 0x40, 0x20, 0x90, 0x40, 0x3f, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t pressure_s[4][24] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0xf0, 0x0c, 0x03, 0xe1, 0x18, 0x08, 0x64, 0xc4, 0x82, 0x02, 0x02, 0x02, 0x04, 0x04, 0x08, 0x18, 0xe1, 0x03, 0x0c, 0xf0, 0x00, 0x00},
	{0x00, 0x00, 0x0f, 0x30, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x30, 0x0f, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t zero_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t one_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t two_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc1, 0xff, 0x7e, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00}
};

const uint8_t three_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe1, 0x3f, 0x1e, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t four_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x38, 0x3e, 0x37, 0x31, 0x30, 0x30, 0x30, 0xfe, 0xfe, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t five_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t six_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xff, 0xff, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0xfc, 0xf8, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t seven_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t eight_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x3e, 0x7f, 0xc1, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc1, 0x7f, 0x3e, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0xfc, 0xfe, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0xfe, 0xfc, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t nine_n[4][18] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x3e, 0x7f, 0xc1, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc1, 0xff, 0xfe, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t hpa_u[4][24] PROGMEM = {
	{0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0xff, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00},
	{0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x08, 0x08, 0x08, 0x07, 0x00, 0x70, 0x88, 0x04, 0x04, 0x04, 0x84, 0xff, 0x00},
	{0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00}
};

const uint8_t cdegree_u[4][24] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x03, 0xf0, 0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8_t rhp_u[4][24] PROGMEM = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0e, 0x11, 0x11, 0x91, 0xce, 0x60, 0x30, 0x98, 0x8c, 0x86, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00, 0xfc, 0x64, 0xa4, 0x18, 0x00, 0xfc, 0x20, 0x20, 0xfc, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00}
};

const uint8_t minus[18] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00};

const uint8_t dec_point[6] PROGMEM = {0x00, 0x8e, 0x4e, 0x7e, 0x3c, 0x00};

#endif /* SYMBOLS_H_ */