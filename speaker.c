#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "speaker.h"

//All calculations for timers are based on the external 16MHz base clock. 

void SpeakerInit(void)
{
		//Setup IO
		PORTC.DIRCLR= 0b00000001; //set pin as input so no signal comes trough
		PORTC.PIN0CTRL = 0b00010000; 
		
		//Setup TC for frequency generation
		TCC0.CTRLA= 0; //turn counter of
		TCC0.CTRLB= 0b00010011; //set counter in single slope pwm mode and overwrite the first pin of the port with the pwm signal.
		//TCC0.CTRLC=  //nothing to see here
		TCC0.CTRLD= 0; //random settings not important just turn of
		TCC0.CTRLE= 0;
		
		//Setup TC for duration timing
		TCC1.CTRLA= 0; //turn counter off
		TCC1.CTRLB= 0; //nothing to set here
		//TCC1.CTRLC=
		TCC1.CTRLD= 0;
		TCC1.CTRLE= 0;
		TCC1.INTCTRLA = 0b00000011; //set overflow interrupt to top level
		
		
}
void SpeakerBeep(int Frequency,int Length)
{
	TCC0.CTRLA= 0b00000101; //turn on timer with prescaler divide by 64
	TCC0.CNT = 0; //set count to 0
	TCC0.PER = 250000/Frequency; //set period of the pwm signal
	TCC0.CCA = TCC0.PER / 2; //duty cycle 0.5
	PORTC.DIRSET = 0b00000001; //turn port as output
	TCC1.CTRLA= 0b00000111; //turn on counter2 with prescaler divide by 1024 for a max time of 2 sec
	TCC1.CNT = 0; //set count to 0
	TCC1.PER = (Length*15);//not exactly correct because real value is 15.625 but processor doesn't like floating point operations.
	while(PORTC.DIR & 1){ //this function can not move on because other sounds could overrule the current one
		
	}
}

ISR(TCC1_OVF_vect){ //turn pin to input and turn of timers.
	PORTC.DIRCLR = 0b00000001; 
	TCC0.CTRLA = 0;
	TCC1.CTRLA = 0;
}



