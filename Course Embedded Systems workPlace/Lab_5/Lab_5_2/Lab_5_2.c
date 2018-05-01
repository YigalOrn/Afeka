/*
הוצאת גל ריבועי: המרה דיגיטאלית לאנלוגית 
*/

#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortD(void);
void initPortE(void);
void initPortF(void);

int main()
{
	int x;
	initPortD();
	initPortE();
	initPortF();
	while (1)
	{
		PORTF = 0x05;//Select DAC channel A
		while (PORTE < 0xFF)
		{
			PORTE = 0xff;
			PORTDbits.RD4 = 1;
			PORTDbits.RD4 = 0;
			for (x = 0;x < 1000;x++);
		}
		while (PORTE > 0x00)
		{
			PORTE = 0;
			PORTDbits.RD4 = 1;
			PORTDbits.RD4 = 0;
			for (x = 0;x < 1000;x++);
		}
		PORTFbits.RF8 = 1;
	}
	return 0;
}

void initPortD(void)
{
	unsigned int portMap;

	portMap = TRISD;
	portMap &= 0xFFFFFFCF;
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


