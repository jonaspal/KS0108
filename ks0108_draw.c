/*
* ks0108_draw.c
*
* Created: 10/16/2012 7:39:38 PM
*  Author: welldonejonas
*/

#include "ks0108_draw.h"



/**
* Print text at the specified Location
* Currently override pages
* Expect the font to be 5x8
* @param  string text to print
* @param  x horizintal position of the first character
* @param  y vertical position of the first charachter
*/
void lcd_draw_string(char *s, uint8_t x, uint8_t y){
	lcd_select_col_row(x,y);

	int start, j;

	while( *s != '\0' ){
		 
			// stop the loop when characters can not fit in the screen
			if(x>127)
				break;
			
			
			start = ( ( *s++ ) - 32) * 5;

			for(j =start; j < start + 5 ; j++){
				lcd_write_data(Font5x7[j]);
			}
			
			x+=6;
			lcd_select_col_row(x,y);
	  }
	
}


/**
* Draw a line.
* Algorithm found on http://www.edaboard.com/thread68526.html
* @param  x1	
* @param  y1
* @param  x2
* @param  y1
*/
void lcd_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){ 

int i, deltax, deltay, numpixels;
int d, dinc1, dinc2;
int x, xinc1, xinc2;
int y, yinc1, yinc2;

//calculate deltaX and deltaY
deltax = abs(x2 - x1);
deltay = abs(y2 - y1);

//initialize
if(deltax >= deltay)
{
	//If x is independent variable
	numpixels = deltax + 1;
	d = (2 * deltay) - deltax;
	dinc1 = deltay << 1;
	dinc2 = (deltay - deltax) << 1;
	xinc1 = 1;
	xinc2 = 1;
	yinc1 = 0;
	yinc2 = 1;
}
else
{
	//if y is independent variable
	numpixels = deltay + 1;
	d = (2 * deltax) - deltay;
	dinc1 = deltax << 1;
	dinc2 = (deltax - deltay) << 1;
	xinc1 = 0;
	xinc2 = 1;
	yinc1 = 1;
	yinc2 = 1;
}
//move the right direction
if(x1 > x2)
{
	xinc1 = -xinc1;
	xinc2 = -xinc2;
}
if(y1 > y2)
{
	yinc1 = -yinc1;
	yinc2 = -yinc2;
}
x = x1;
y = y1;

//draw the pixels
for(i = 1; i < numpixels; i++)
{
	lcd_draw_dot(x, y);
	if(d < 0)
	{
		d = d + dinc1;
		x = x + xinc1;
		y = y + yinc1;
	}
	else
	{
		d = d + dinc2;
		x = x + xinc2;
		y = y + yinc2;
	}
}
}	