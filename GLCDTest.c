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
	lcd_init();
	
	// draw some lines
	lcd_draw_line(0, 0, 127,64);
	
	lcd_draw_line(0, 63, 127, 0);
	
	lcd_draw_line(0, 0, 127, 0);
	
	lcd_draw_line(0, 63, 127, 63);
	
	lcd_draw_line(0, 0, 0, 63);
	
	lcd_draw_line(127, 0, 127 , 63);
	
	// draw some dots
	lcd_draw_dot(0,0);
	lcd_draw_dot(0,63);

	lcd_draw_dot(127,0);
	lcd_draw_dot(127,63);
	
	
	// print some text	
	lcd_draw_string( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" , 0, 0);
	lcd_draw_string( "Hello World" , 3, 2);
	
	
    while(1)
    {
		

	
    }
}