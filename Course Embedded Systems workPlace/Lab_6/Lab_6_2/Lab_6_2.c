#include "p32xxxx.h"
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void print_led(int x);
void print_lcd(float num);
void busy(void);
void delay(int k);

unsigned int portMap;

void main(void)
{
	unsigned long j, ADCValue;
	char control[7] = {
		0x38,
		0x38,
		0x38,
		0x0e,
		0x06,
		0x1
	};
	int i;

	portMap = TRISG;
	portMap &= 0xFFFF7FFF;
	TRISG = portMap;
	PORTGbits.RG15 = 0;//buzzer=0ff

	portMap = TRISB;
	portMap &= 0xFFFF7FFF;
	TRISB = portMap;

	portMap = TRISF;
	portMap &= 0xFFFFFEF8;
	TRISF = portMap;
	PORTFbits.RF8 = 1;

	portMap = TRISE;
	portMap &= 0xFFFFFF00;
	TRISE = portMap;

	portMap = TRISD;
	portMap &= 0xFFFFFFCF;
	TRISD = portMap;

	PORTF = 0x00;

	for (i = 0; i < 7; i++)
	{
		PORTDbits.RD5 = 0;//w/r
		PORTBbits.RB15 = 0;//rs 
		PORTE = control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	AD1PCFG = 0xFEFF; // PORTB = Digital; RB8 = analog
	AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ...
	// and starts converting
	AD1CHS = 0x00080000;// in this example RB8/AN8 is the input
	AD1CSSL = 0x100;
	AD1CON3 = 0x0002; // Manual Sample, Tad = 6 TPB
	AD1CON2 = 0;
	AD1CON1SET = 0x8000; // turn ADC ON

	while (1) // repeat continuously
	{
		AD1CON1SET = 0x0002; // start sampling ...
		for (j = 0; j < 100000; j++);//DelayNmSec(100); // for 100 mS
		AD1CON1CLR = 0x0002; // start Converting
		while (!(AD1CON1 & 0x0001));// conversion done?
		ADCValue = ADC1BUF0; // yes then get ADC value
		//print_led(ADCValue / 4);//?????
		print_lcd(ADCValue);
	}

}//main 

void print_lcd(float num)
{
	int mes[4];
	int i, k;
	float f;
	PORTFbits.RF8 = 1;
	PORTF = 0x00;
	k = num;
	num = (num*3.3) / 1023;
	mes[3] = ((int)(num * 100) % 10) + '0';
	mes[2] = ((int)(num * 10) % 10) + '0';
	mes[1] = '.';
	mes[0] = ((int)num % 10) + '0';

	PORTDbits.RD5 = 0;//w/r
	PORTBbits.RB15 = 0;//rs 
	PORTE = 0x1;//clear lcd
	PORTDbits.RD4 = 1;//enable=1
	PORTDbits.RD4 = 0;//enable=0
	busy();


	for (i = 0; i < 4; i++)
	{
		PORTDbits.RD5 = 0;//w/r
		PORTBbits.RB15 = 1;//rs 
		PORTE = mes[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
		//PORTGbits.RG15 = 1;//buzzer on
		//delay(k);
		//PORTGbits.RG15 = 0;//buzzer off
		//delay(k);
	}
}//print_lcd

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

void delay(int k)
{
	unsigned long i;
	for (i = 0; i < 200 * (k + 100); i++);
}

void busy(void)
{
	PORTDbits.RD5 = 1;//w/r
	PORTBbits.RB15 = 0;//rs 
	portMap = TRISE;
	portMap &= 0xFFFFFFFF;
	TRISE = portMap;
	do
	{
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
	} while (PORTEbits.RE7);
	portMap = TRISE;
	portMap &= 0xFFFFFF00;
	TRISE = portMap;
}
