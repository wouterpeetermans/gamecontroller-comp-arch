#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

static int stdio_putchar(char c, FILE * stream);
static int stdio_getchar(FILE *stream);
static FILE UsartStdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar,_FDEV_SETUP_WRITE);

void USARTInit(void)
{
	USART_PORT.DIRSET=0b00001000;	
	USART_PORT.DIRCLR=0b00000100;
	
	USART.CTRLA=0b00000000;
	USART.CTRLB=0b00011000;
	USART.CTRLC=0b00000011;
	
	USART.BAUDCTRLA=0xE5; //BSEL=3301, BSCALE=-5 9600 baud
	USART.BAUDCTRLB=0xBC; 
	
	stdout=&UsartStdio;
	stdin=&UsartStdio;
}


static int stdio_putchar(char c, FILE * stream)
{
	USART.DATA = c;
	while (!(USART.STATUS & 0b01000000));
	USART.STATUS=0b01000000;
	return 0;
}
	
static int stdio_getchar(FILE *stream)
{
	while (!(USART.STATUS & 0b10000000));
	return USART.DATA;
}
