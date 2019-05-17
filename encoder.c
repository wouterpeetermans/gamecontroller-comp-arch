#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"
volatile int encoderPos = 0;
volatile uint8_t prevpos;
volatile uint8_t currentPos;

void EncoderInit(void)
{
	PORTC.DIR = (PORTC.DIR & 0b11001111);
	PORTC.PIN4CTRL = 0b00011000;
	PORTC.PIN5CTRL = 0b00011000;
	PORTC.INTCTRL = 0b00001111;
	PORTC.INT0MASK = 0b00010000;
	PORTC.INT1MASK = 0b00100000;
	SREG = (SREG | 0b10000000);
	PMIC.CTRL = 0b00000100;
	
	
	
}
int EncoderGetPos(void)
{
	return encoderPos;
}

ISR(PORTC_INT0_vect){
	encoderPos += readEncoder();
}

ISR(PORTC_INT1_vect){
	encoderPos += readEncoder();
}


// documentation of the arduino encoder library
//                           _______         _______       
//               Pin1 ______|       |_______|       |______ Pin1
// negative <---         _______         _______         __      --> positive
//               Pin2 __|       |_______|       |_______|   Pin2

		//	new	new	old	old
		//	pin2	pin1	pin2	pin1	Result
		//	----	----	----	----	------
		//	0	0	0	0	no movement
		//	0	0	0	1	+1
		//	0	0	1	0	-1
		//	0	0	1	1	+2  (assume pin1 edges only)
		//	0	1	0	0	-1
		//	0	1	0	1	no movement
		//	0	1	1	0	-2  (assume pin1 edges only)
		//	0	1	1	1	+1
		//	1	0	0	0	+1
		//	1	0	0	1	-2  (assume pin1 edges only)
		//	1	0	1	0	no movement
		//	1	0	1	1	-1
		//	1	1	0	0	+2  (assume pin1 edges only)
		//	1	1	0	1	-1
		//	1	1	1	0	+1
		//	1	1	1	1	no movement
/*
	// Simple, easy-to-read "documentation" version :-)
	//
	void update(void) {
		uint8_t s = state & 3;
		if (digitalRead(pin1)) s |= 4;
		if (digitalRead(pin2)) s |= 8;
		switch (s) {
			case 0: case 5: case 10: case 15:
				break;
			case 1: case 7: case 8: case 14:
				position++; break;
			case 2: case 4: case 11: case 13:
				position--; break;
			case 3: case 12:
				position += 2; break;
			default:
				position -= 2; break;
		}
		state = (s >> 2);
	}
*/

int readEncoder(){
	currentPos = (PORTC.IN >> 4) & 3;
	uint8_t s = (currentPos << 2) | prevpos;
	int position = 0;
	switch (s) {
		case 0: case 5: case 10: case 15:
		break;
		case 1: case 7: case 8: case 14:
		position++; break;
		case 2: case 4: case 11: case 13:
		position--; break;
		case 3: case 12:
		position += 2; break;
		default:
		position -= 2; break;
	}
	prevpos = currentPos;
	return position;
}
