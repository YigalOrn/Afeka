/*
הוצאת גל שן משולש המרה: דיגיטאלית לאנלוגית
*/

#include <p32xxxx.h>
#include <math.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortD(void);
void initPortE(void);
void initPortF(void);

int main()
{
	char dataChA_I[255];
	char dataChB_I[255];
	int x =0;
	
	for (x = 0; x < 255; x++)
	{
		dataChA_I[x] = 255 - x;
		dataChB_I[x] = x;
	}

	initPortD();
	initPortE();
	initPortF();

	x = 0;
	while (1)
	{
		PORTFbits.RF8 = 1;
		PORTF = 0x05;//Select DAC channel A
		PORTE = dataChA_I[x];
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;

		PORTFbits.RF8 = 1;
		PORTF = 0x06;//Select DAC channel A
		PORTE = dataChB_I[x];
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
		if (x == 255)
			x = 0;
	
	}
	return 0;
}//main

void initPortD(void)
{
	unsigned int portMap;

	portMap = TRISD;
	portMap &= 0xFFFFFFCF;//1100-1111
	TRISD = portMap;
	PORTDbits.RD4 = 0;
	PORTDbits.RD5 = 0;
}

void initPortE(void)
{
	unsigned int portMap;

	portMap = TRISE;
	portMap &= 0xFFFFFF00;
	TRISE = portMap;
	PORTE = 0x00;
}

void initPortF(void)
{
	unsigned int portMap;

	portMap = TRISF;
	portMap &= 0xFFFFFEF8;
	TRISF = portMap;
	PORTFbits.RF8 = 1;
}
