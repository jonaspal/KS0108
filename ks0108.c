/*
 * ks0108.c
 *
 * Created: 10/13/2012 4:32:34 PM
 *  Author: welldonejonas
 */ 

#include "ks0108.h"

/**
* Initialize and clear the LCD
*/
void lcd_init(){
	turnOnCS1();
	turnOnCS2();	

	lcd_write_command(LCD_ON);
	lcd_clear();
}

/**
* Write a command to the LCD
* @param  command command to be executed
*/
void lcd_write_command(uint8_t command){
		lcd_busy();
		turnOffRS();	 // set RS to low
		turnOffRW();	 // set RW to low
		dataPortDirection(OUTPUT);
		writeDataPort(command);
		lcd_toggle();
}


/**
* Write data to the LCD
* @param  data data to be transmitted
*/
void lcd_write_data(uint8_t data){
	lcd_busy();
	turnOnRS();		// RS high
	turnOffRW();	 // set RW to low ( write mode )
	dataPortDirection(OUTPUT);
	writeDataPort(data);
	lcd_toggle();
}


/**
* Read page
* @param  col column ( X axis, must be between 0 and 127)
* @param pageNumber page number ( Y axis, must be between 0 and 8)
* @return page
*/
uint8_t lcd_read_data(uint8_t col, uint8_t pageNumber){
	uint8_t data = 0x00;
	
	if(col < 63)
		lcd_select_chip(CHIP1);
	else
		lcd_select_chip(CHIP2);
	
	lcd_select_col_row( col, pageNumber ); 
	
	dataPortDirection(INPUT);

	turnOnRS(); // Register Select On
	turnOnRW(); // Enable Read mode

	// dummy read
	lcd_toggle();
	data = readDataPort();
	
	// actual read
	lcd_toggle();
	data = readDataPort();
	
	return data;
}

/**
* Clear the LCD
*/
void lcd_clear(){
	uint8_t x;
	uint8_t y;
	
	for(x = 0;  x < 128; x++){
		for(y = 0;  y < 8; y++){
			lcd_select_col_row(x, y);
			lcd_write_data(0x00);
		}	
	}
}


/**
*	 Loop while the LCD is busy
*/
void lcd_busy(){
	/*
	// prepare the lcd to read its status
	turnOffRS();
	turnOnRW();
	turnOnEN();

	while(  ( readDataPort() &  BUSY_FLAG ) ); // loop while busy flag is high
*/
	_delay_us(5);
}


/**
* Toggle the enable pin (also called pulse)
*/
void lcd_toggle(){
		turnOnEN();
		lcd_busy();
		turnOffEN();
		lcd_busy();
}

/**
* Select an appropriate row
* @param row row to be selected
*/
void lcd_select_row(uint8_t row){ // @todo: rename to select_page?
	lcd_write_command( ( row | 0xB8 ) & 0xBF ); // put the row address on the data port @todo: use defines and bit shifts
}


/**
* Select the appropriate column
* @param col col to be selected
*/
void lcd_select_col(uint8_t col){
		uint8_t columnData;
		
		if(col < 64){
			lcd_select_chip(CHIP1);
			columnData = col;
		}else{
			lcd_select_chip(CHIP2);
			columnData = col -64;
		}
		
		columnData   = (columnData | 0x40) & 0x7F; //@todo: use shifts+ document + use defines
		lcd_write_command(columnData);	
}

/**
* Select the appropriate row & column
* @param col col to be selected
* @param row row to be selected
*/
void lcd_select_col_row(uint8_t col, uint8_t row){
	lcd_select_col(col);
	lcd_select_row(row);
}


/**
* Select the appropriate LCD controller
* @param chip LCD controller to be activated
*/
void lcd_select_chip(uint8_t chip){
	if(chip == CHIP1){
		turnOnCS1();
		turnOffCS2();
	}else{
		turnOffCS1();
		turnOnCS2();
	}
}


/**
* Draw a dot at the specified coordinate
* @param x x axis
* @param y y axis
*/
void lcd_draw_dot(uint8_t x, uint8_t y){
	uint8_t currentData = lcd_read_data(x, y >> 3 ); // Divide y by 8 to get the correct page
	
	// the read operation increments the internal Y counter, we need to reselect the correct coordinates.
	lcd_select_col_row( x, ( y >> 3 ) );
	
	lcd_write_data( (currentData) | (1 << (y % 8)) ); // @todo: document this
}