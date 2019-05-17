
#ifndef ANALOG_H
#define ANALOG_H
#include <stdint.h>
#include "Analog.h"
#include <avr/io.h>

void AnalogInit(void);			//Initialize ADC system
int AnalogGetCh(int PinPos,int PinNeg);

#endif