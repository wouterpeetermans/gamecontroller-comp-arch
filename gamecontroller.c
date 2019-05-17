#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Clock.h"
#include "USART.h"
#include "Analog.h"
#include "acc.h"
#include "LED.h"
#include "switch.h"
#include "encoder.h"
#include "speaker.h"


char text[11];
char a;

void SimpleFunction(void);	//A simple function: print a counter (0 to 9) to the terminal

int main(void)
{	
	//###1###
	 
	//Initialize subsystems
	ClockInit();			//Initialize system clock (16 MHz)
	USARTInit();			//Initialize USART and bind to stdout,stdin
	AnalogInit();			//Initialize ADC
	AccInit();				//Initialize accelerometer system
	LEDInit();				//Initialize LEDs
	SwitchInit();			//Initialize switches
	EncoderInit();			//Initialize encoder
	SpeakerInit();			//Initialize speaker system
	
	//Enable interrupts
	PMIC.CTRL|=0b00000111;  //Enable low, medium, high priority interrupts
	SREG|=0b10000000;		//Global interrupt enable
	_delay_ms(500);
	
	
	
	while (1){
		// Start ADC conversion
		AnalogGetCh(1,2);
		
		
		
		//putchar('U');
	}

}

void runningLight(){
	for (int i = 0; i<4; i++)
	{
		LEDSet(0b00000001 << i);
	}
}
/*
int getAD10(){
	int rslt;
	while(!ADC_Ch_Conversion_Complete(&ADCA.CH0));
	rslt = ADC_ResultCh_GetWord(&ADCA.CH0);
	ADCA.CTRLA = 0x05;    //start conv.
	return rslt;
}
*/