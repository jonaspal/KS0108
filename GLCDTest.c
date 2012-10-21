/*
 * GLCD.c
 *
 * Created: 10/10/2012 8:55:45 PM
 *  Author: welldonejonas
 */ 


#define F_CPU 16000000 // Clock Speed

#include "ioWrapper.h"
#include "ks0108.h"
#include "ks0108_draw.h"

#include <util/delay.h>


int main(void)
{
	
	// configure the AVR ports
	portsInit();

	// turn on the LCD and clear the screen
	ksInit();
	
	// draw some lines
	
	ksDrawLine(0, 0, 127, 0);
	
	ksDrawLine(0, 63, 127, 63);
	
	ksDrawLine(0, 0, 0, 63);
	
	ksDrawLine(127, 0, 127 , 63);
	
	// draw some dots
	ksDrawDot(0,0);
	ksDrawDot(0,63);

	ksDrawDot(127,0);
	ksDrawDot(127,63);
	
	
	// print some text	
	ksDrawString( "WelldoneJonas" , 40, 1);
	ksDrawString( "Hello World" , 5, 4);
	
	
    while(1);
}