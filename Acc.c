#include <avr/io.h>
#include "acc.h"



void AccInit(void)
{
 PORTC.DIRSET = 0b01000000; //set PC6 as output
 PORTC.PIN6CTRL = 0b00010000; //totem pole configuration with pull down if we would want to turn the acc off 
 PORTC.OUT |= 0b01000000;//turn on output so chip becomes active
 PORTA.PIN0CTRL = 0; //all pins set to totem pole inputs with no resistor for adc measurements. 
 PORTA.PIN1CTRL = 0;
 PORTA.PIN2CTRL = 0;
 PORTA.PIN4CTRL = 0;
 PORTA.DIRCLR = 0b00010111;


}
unsigned int AccGetXAxisRaw(void)
{
	return abs(AnalogGetCh(0,4));//the abs value wil not introduce any problems because we wil never encounter a negative signal 
}
unsigned int AccGetYAxisRaw(void)
{
	return abs(AnalogGetCh(1,4));
}
unsigned int AccGetZAxisRaw(void)
{
	return abs(AnalogGetCh(2,4));
}

int AccGetXAxis(unsigned int AccRaw)
{
	return (AccRaw - 300)/4;
}

int AccGetYAxis(unsigned int AccRaw)
{
	return (AccRaw - 350)/4;
}

int AccGetZAxis(unsigned int AccRaw)
{
	return (AccRaw - 200)/4;
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return ((x - in_min) * (out_max - out_min)) / ((in_max - in_min) + out_min);
}