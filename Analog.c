#include "Analog.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>



void AnalogInit(void)
{
	ADCA.CTRLA = 0;
	ADCA.CTRLB = 0b00010000; //no current limit signed mode 12bit.
	ADCA.REFCTRL = 2; //enable bandgap and set reference to 1v internal source disable temp detection
	ADCA.EVCTRL = 0; //no events
	ADCA.PRESCALER = 0; //div 4 prescaler
	
}



int AnalogGetCh(int PinPos,int PinNeg)
{
	ADCA.CH0.MUXCTRL = (((uint8_t) PinPos) << 3) | ((uint8_t) PinNeg);
	ADCA.CTRLA = 7; //flush all data and start measurement enable adc
	ADCA.CH0.CTRL = 0b10000011; //gain 1 difwgain mode
	//while(!ADCA.CH0.RES){ //wait for data in the register. can be done with interupt ... (didn't work)
		//
	//}
	_delay_ms(1);//delay to wait for measurement to complete 
	int result = ADCA.CH0.RES;
	ADCA.CTRLA = 0; //turn of adc
	return result;
}
