/*
הוצאת גל שן משולש המרה: דיגיטאלית לאנלוגית
*/

#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortD(void);
void initPortE(void);
void initPortF(void);

int main()
{
	initPortD();
	initPortE();
	initPortF();

	while (1)
	{
		PORTF = 0x05;//Select DAC channel A
					 // Select DAC channel b = 0x06
		while (PORTE < 0xFF)
		{
			PORTE++;
			PORTDbits.RD4 = 1;
			PORTDbits.RD4 = 0;
		}
		while (PORTE > 0x00)
		{
			PORTE--;
			PORTDbits.RD4 = 1;
			PORTDbits.RD4 = 0;
		}
		PORTFbits.RF8 = 1;
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
