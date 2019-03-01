
#ifndef ANALOG_H
#define ANALOG_H

void AnalogInit(void);			//Initialize ADC system
int AnalogGetCh(int PinPos,int PinNeg);
								//Get analog channel value
								//PinPos: 
									//Differential mode: positive input pin (0 to 15)
									//Single ended mode: input pin (0 to 15)
								//PinNeg: 
									//Differential mode: negative input pin (0 to 7)
									//Single ended mode: write '-1' to select single ended mode
								//Return value:
								//-2048 to 2047 (signed) or 0 to 4095 (unsigned)
								//10000: Invalid pin settings

#endif