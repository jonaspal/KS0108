/*
 * ioWrapper.h
 *
 * Created: 10/11/2012 2:35:02 PM
 *  Author: welldonejonas
 */ 


#ifndef IOWRAPPER_H_
#define IOWRAPPER_H_
#include <avr/io.h>

#define OUTPUT 0xff
#define INPUT 0x00


void portsInit();
void dataPortDirection(uint8_t direction);

void writeDataPort(uint8_t data);
uint8_t readDataPort();

// control helpers

void turnOnRS();
void turnOffRS();

void turnOnRW();
void turnOffRW();

void turnOnEN();
void turnOffEN();

void turnOnCS1();
void turnOffCS1();

void turnOnCS2();
void turnOffCS2();
#endif /* IOWRAPPER_H_ */