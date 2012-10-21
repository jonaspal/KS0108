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
void ksInit(){
	turnOnCS1();
	turnOnCS2();	

	ksWriteCommand(LCD_ON);
	ksClear();
}

/**
* Write a command to the LCD
* @param  command command to be executed
*/
void ksWriteCommand(uint8_t command){
		ksBusy();
		turnOffRS();	 // set RS to low
		turnOffRW();	 // set RW to low
		dataPortDirection(OUTPUT);
		writeDataPort(command);
		ksToggle();
}


/**
* Write data to the LCD
* @param  data data to be transmitted
*/
void ksWriteData(uint8_t data){
	ksBusy();
	turnOnRS();		// RS high
	turnOffRW();	 // set RW to low ( write mode )
	dataPortDirection(OUTPUT);
	writeDataPort(data);
	ksToggle();
}


/**
* Read page
* @param  col column ( X axis, must be between 0 and 127)
* @param pageNumber page number ( Y axis, must be between 0 and 8)
* @return page
*/
uint8_t ksReadData(uint8_t col, uint8_t pageNumber){
	uint8_t data = 0x00;
	
	if(col < 63)
		ksSelectChip(CHIP1);
	else
		ksSelectChip(CHIP2);
	
	ksSelectColRow( col, pageNumber ); 
	
	dataPortDirection(INPUT);

	turnOnRS(); // Register Select On
	turnOnRW(); // Enable Read mode

	// dummy read
	ksToggle();
	data = readDataPort();
	
	// actual read
	ksToggle();
	data = readDataPort();
	
	return data;
}

/**
* Clear the LCD
*/
void ksClear(){
	uint8_t x;
	uint8_t y;
	
	for(x = 0;  x < 128; x++){
		for(y = 0;  y < 8; y++){
			ksSelectColRow(x, y);
			ksWriteData(0x00);
		}	
	}
}


/**
*	 Loop while the LCD is busy
*/
void ksBusy(){
	/* @todo: instead of using a delay, read LCD status:
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
void ksToggle(){
		turnOnEN();
		ksBusy();
		turnOffEN();
		ksBusy();
}

/**
* Select an appropriate row
* @param row row to be selected
*/
void ksSelectRow(uint8_t row){ // @todo: rename to select_page?
	ksWriteCommand( ( row | 0xB8 ) & 0xBF ); // put the row address on the data port @todo: use defines and bit shifts
}


/**
* Select the appropriate column
* @param col col to be selected
*/
void ksSelectCol(uint8_t col){
		uint8_t columnData;
		
		if(col < 64){
			ksSelectChip(CHIP1);
			columnData = col;
		}else{
			ksSelectChip(CHIP2);
			columnData = col -64;
		}
		
		columnData   = (columnData | 0x40) & 0x7F; //@todo: use shifts+ document + use defines
		ksWriteCommand(columnData);	
}

/**
* Select the appropriate row & column
* @param col col to be selected
* @param row row to be selected
*/
void ksSelectColRow(uint8_t col, uint8_t row){
	ksSelectCol(col);
	ksSelectRow(row);
}


/**
* Select the appropriate LCD controller
* @param chip LCD controller to be activated
*/
void ksSelectChip(uint8_t chip){
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
void ksDrawDot(uint8_t x, uint8_t y){
	uint8_t currentData = ksReadData(x, y >> 3 ); // Divide y by 8 to get the correct page
	
	// the read operation increments the internal Y counter, we need to reselect the correct coordinates.
	ksSelectColRow( x, ( y >> 3 ) );
	
	ksWriteData( (currentData) | (1 << (y % 8)) ); // @todo: document this
}