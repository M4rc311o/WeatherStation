// VirtualWire.h
//
// Virtual Wire implementation for Arduino
// See the README file in this directory fdor documentation
// 
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: VirtualWire.h,v 1.3 2009/03/30 00:07:24 mikem Exp $

#ifndef VirtualWire_h
#define VirtualWire_h

#include <stdlib.h>
#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <avr/interrupt.h>

#define VW_PORT PORTD
#define VW_DPORT DDRD
#define VW_TX_PIN PORTD5
#define VW_RX_PIN PORTD4
#define VW_PTT_PIN PORTD3
#define INVERTED 1

// Maximum number of bytes in a message, counting the byte count and FCS
#define VW_MAX_MESSAGE_LEN 30

// The maximum payload length
#define VW_MAX_PAYLOAD VW_MAX_MESSAGE_LEN-3

// The size of the receiver ramp. Ramp wraps modulu this number
#define VW_RX_RAMP_LEN 160

#define VW_RX_SAMPLES_PER_BIT 8

#define VW_RAMP_INC (VW_RX_RAMP_LEN/VW_RX_SAMPLES_PER_BIT)
#define VW_RAMP_TRANSITION VW_RX_RAMP_LEN/2
#define VW_RAMP_ADJUST 9
#define VW_RAMP_INC_RETARD (VW_RAMP_INC-VW_RAMP_ADJUST)
#define VW_RAMP_INC_ADVANCE (VW_RAMP_INC+VW_RAMP_ADJUST)

#define VW_HEADER_LEN 8

    void vw_setup(uint16_t speed);

    void vw_rx_start();

    void vw_rx_stop();

    void vw_wait_tx();

    void vw_wait_rx();

    //uint8_t vw_wait_rx_max(unsigned long milliseconds);

    uint8_t vw_send(uint8_t* buf, uint8_t len);

    uint8_t vw_have_message();

    uint8_t vw_get_message(uint8_t* buf, uint8_t* len);

#endif