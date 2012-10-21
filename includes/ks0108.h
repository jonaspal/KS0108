/*
 * ks0108.h
 *
 * Created: 10/13/2012 4:32:18 PM
 *  Author: welldonejonas
 */ 


#ifndef KS0108_H_
#define KS0108_H_

#include "ioWrapper.h"

#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 16000000 // Clock Speed
#include <util/delay.h>


#define CHIP1 0x00
#define CHIP2 0x01
#define BUSY_FLAG 0x80 // LCD Port 7


// Commands
#define LCD_ON 0x3F

void ksInit();

void ksWriteCommand(uint8_t command);

void ksWriteData(uint8_t data);

uint8_t ksReadData(uint8_t col, uint8_t pageNumber);

void ksClear();

void ksBusy();

void ksToggle();

void ksSelectRow(uint8_t row);

void ksSelectCol(uint8_t col);

void ksSelectColRow(uint8_t col, uint8_t row);

void ksSelectChip(uint8_t chip);

void ksDrawDot(uint8_t x, uint8_t y);


#endif /* KS0108_H_ */