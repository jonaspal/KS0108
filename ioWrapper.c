/*
 * ioWrapper.c
 *
 * Created: 10/11/2012 2:35:25 PM
 *  Author: welldonejonas
 */ 

#include "ioWrapper.h"


void portsInit(){
	DDRD |= (1 << 6 | (1 << 7) ) ; // configure PD.5, PD.6 as an output
	DDRB |= ( (1 << 0) | (1 << 1) | (1 << 2) );  // configure PB.0, PB.1, PB.2 as an output
}

void dataPortDirection(uint8_t direction){
	if(direction == OUTPUT){
		DDRC |= 0x0F; // configure PC.0 -> PC.3 as outputs 
		DDRD |= 0x0F; // configure PD.0 -> PD.3 as outputs
	}
	else{
		DDRC &= 0xF0; // configure PC.0 -> PC.3 as inputs
		DDRD &= 0xF0; // configure PD.0 -> PD.3 as inputs
	}		
	
}


/*
	write data to Port C (low) and Port D ( low )
*/
void writeDataPort(uint8_t data){

	// take the lowest 4 bits of data and uses it to set up the first 4 pins of port c
	PORTC = (PORTC & 0xF0) | (data & 0x0F);
	
	// take the highest 4 bits of data and uses it to set up the first 4 pins port d
	PORTD = (PORTD & 0xF0) | ( data >> 4);

}

/* read data port
	PC.0 through PC.3 represents the lowest nibble
	PD.0 through PD.3 represents the highest nibble
*/
uint8_t readDataPort(){

	uint8_t data = 0;
	
	// disable pull ups
	PORTC &= 0xF0;
	PORTD &= 0xF0;

	data = (PIND << 4) | (PINC & 0x0f);
	
	return data;
}
void turnOnRS(){
	PORTD |= (1 << 6); // turn PD.6 On
}

void turnOffRS(){
	PORTD &= ~(1 << 6); // turn PD.6 Off
}

void turnOnRW(){
	PORTD |= (1 << 7); // turn PD.7 On
}

void turnOffRW(){
	PORTD &= ~(1 << 7); // turn PD.7 Off
} 

void turnOnEN(){
	PORTB |= (1 << 0); // turn PB.0 On
}

void turnOffEN(){
	PORTB &= ~(1 << 0); //turn PB.0 off
}

void turnOnCS1(){
	PORTB |= (1 << 1); //turn PB.1 on
}

void turnOffCS1(){
	PORTB &= ~( 1 << 1 ); //turn PB.1 off
}

void turnOnCS2(){
	PORTB |= (1 << 2 ); // turn PB.2 On
}

void turnOffCS2(){
	PORTB &= ~( 1 << 2 ); // turn PB.2 Off
}