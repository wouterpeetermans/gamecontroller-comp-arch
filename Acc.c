#include <avr/io.h>
#include "acc.h"



void AccInit(void)
{
 PORTC.DIR = (PORTC.DIR | 0b11110000);
 PORTC.PIN6CTRL = 0b00010000;
PORTA.PIN0CTRL = 0b00000000;
PORTA.PIN1CTRL = 0b00000000;
PORTA.PIN2CTRL = 0b00000000;


}
unsigned int AccGetXAxisRaw(void)
{
	PORTA.IN = 0b00000001;
	return PORTA.IN;
}
unsigned int AccGetYAxisRaw(void)
{
	PORTA.IN = 0b00000010;

	return PORTA.IN;
}
unsigned int AccGetZAxisRaw(void)
{
PORTA.IN = 0b00000100;
	return PORTA.IN;
}

int AccGetXAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetYAxis(unsigned int AccRaw)
{
	return 0;
}

int AccGetZAxis(unsigned int AccRaw)
{
	return 0;
}