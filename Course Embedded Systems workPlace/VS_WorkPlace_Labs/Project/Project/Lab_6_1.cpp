#include "p32xxxx.h"
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void print_led(int x);

void main(void)
{
	unsigned long j, ADCValue;
	AD1PCFG = 0xFEFF; // convert from digital to analog: rest of PORTB = Digital; RB8 = analog
	AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ... // and starts converting
	AD1CHS = 0x00080000; // in this example RB8/AN8 is the input
	AD1CSSL = 0x100; // Select  RB8
	AD1CON3 = 0x0002; // Clock select
	AD1CON2 = 0; // 00x00..0,  Vref-not Scan-BUFM  Result –MUX  A
	AD1CON1SET = 0x8000; // turn ADC ON
	while (1) // repeat continuously
	{
		AD1CON1SET = 0x0002; // start sampling ...
		for (j = 0; j < 100000; j++); // DelayNmSec(100); // for 100 mS
		AD1CON1CLR = 0x0002; // start Converting
		while (!(AD1CON1 & 0x0001)); // conversion done?
		ADCValue = ADC1BUF0; // yes then get ADC value
		print_led(ADCValue / 4); //  compression 10 bit  1024/4  256  8 bit , only to show on LED
	}
}//main

void print_led(int x)
{
	TRISF = 0;
	TRISE = 0;
	TRISD = 0;
	PORTF = 4;
	PORTE = x;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
}
