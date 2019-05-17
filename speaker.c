#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "speaker.h"

void SpeakerInit(void)
{
		//Setup IO
		PORTC.DIRCLR= 0b00000001;
		PORTC.PIN0CTRL = 0b00010000;
		
		//Setup TC for frequency generation
		TCC0.CTRLA= 0b00000110;
		TCC0.CTRLB= 0b00010011;
		//TCC0.CTRLC= 
		TCC0.CTRLD= 0;
		TCC0.CTRLE= 0;
		
		//Setup TC for duration timing
		//TCC1.CTRLA=
		//TCC1.CTRLB=
		//TCC1.CTRLC=
		//TCC1.CTRLD=
		//TCC1.CTRLE=
		
}
void SpeakerBeep(int Frequency,int Length)
{
	TCC0.PER = 125000/Frequency;
	TCC0.CCA = TCC0.PER / 2;
	PORTC.DIRSET = 0b00000001;
	_delay_ms(Length);
	PORTC.DIRCLR = 0b00000001;
}



