#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

 int stdio_putchar(char c, FILE * stream);
 int stdio_getchar(FILE *stream);
static FILE UsartStdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar,_FDEV_SETUP_WRITE);

void USARTInit(void)
{
	USART_PORT.DIRSET=0b00001000;	//set pin as an output
	USART_PORT.DIRCLR=0b00000100;	//set pin as input
	
	USART.CTRLA=0b00000000;			//turn of interrupts of usart
	USART.CTRLB=0b00011000;			//turn on receive and transmit 
	USART.CTRLC=0b00000011;			//asynchronous mode with no parity, 1 stop bit and an 8-bit size
	
	USART.BAUDCTRLA=0xD7; //BSEL=3301, BSCALE=-5 9600 baud see matlab code for calculations
	USART.BAUDCTRLB=0x93; 
	
	stdout=&UsartStdio;
	stdin=&UsartStdio;
}


int stdio_putchar(char c, FILE * stream)
{
	USART.DATA = c;
	while (!(USART.STATUS & 0b01000000)); //wait for transmit complete flag
	USART.STATUS=0b01000000;
	return 0;
}
	
int stdio_getchar(FILE *stream)
{
	while (!(USART.STATUS & 0b10000000)); //wait for receive complete flag
	return USART.DATA;
}
