#ifndef USART_H
#define USART_H
#include<stdio.h>
//set the correct usart port here
#define USART USARTD0  // kwam van USARTD0 -> debug naar J5 zodat
#define USART_PORT PORTD // kwam van PORTD

void USARTInit(void); //Initialize USART, bind to stdin,stdout
int stdio_putchar(char c, FILE * stream);
int stdio_getchar(FILE *stream);
#endif