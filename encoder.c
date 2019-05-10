#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "encoder.h"

void EncoderInit(void)
{
	PORTC.DIR = (PORTC.DIR & 0b11001111);
	CPU.SREG = (CPU.SREG | 0b10000000);
	
}
int EncoderGetPos(void)
{
	return;
}