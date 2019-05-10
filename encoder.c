#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"
volatile int encoderPos = 0;
volatile uint8_t prevpos;

void EncoderInit(void)
{
	PORTC.DIR = (PORTC.DIR & 0b11001111);
	PORTC.INTCTRL = 0b00001111;
	PORTC.INT0MASK = 0b00010000;
	PORTC.INT1MASK = 0b00001000;
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

int readEncoder(){
	uint8_t currentPos = (PORTC.IN >> 3) & 0b00000011;
	switch (currentPos) {
		case 0:
			if (prevpos == 3){
				return 1;
			} else if (prevpos == 1){
				return -1;
			}
			break;
		case 1:
			if (prevpos == 0){
				return 1;
				} else if (prevpos == 2){
				return -1;
			}
			break;
		case 2:
			if (prevpos == 1){
				return 1;
				} else if (prevpos == 3){
				return -1;
			}
			break;
		case 3:
			if (prevpos == 2){
				return 1;
				} else if (prevpos == 0){
				return -1;
			}
			break;
		default:
			return 0;
	}
}
