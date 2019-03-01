#include "switch.h"
#include <avr/io.h>

void SwitchInit(void)
{
	PORTD.DIRCLR=0b11110001;
	PORTD.PIN0CTRL=0b01011000;
	PORTD.PIN4CTRL=0b01011000;
	PORTD.PIN5CTRL=0b01011000;
	PORTD.PIN6CTRL=0b01011000;
	PORTD.PIN7CTRL=0b01011000;
}


char SwitchGet(void)
{
	return ((PORTD.IN & 0b11110000) >> 3) | (PORTD.IN & 0b00000001);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                