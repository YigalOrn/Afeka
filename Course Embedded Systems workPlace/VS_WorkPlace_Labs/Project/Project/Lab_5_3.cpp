/*
הוצאת גל סינוס: המרה דיגיטאלית לאנלוגית
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
	int x;
	initPortD();
	initPortE();
	initPortF();
	while (1)
	{
		PORTF = 0x05;//Select DAC channel A
		while (1)
		{
			for (x = 0;x < 180;x++)
			{
				PORTE = 127 + 127 * sin((2 * 3.14*x) / 180);
				PORTDbits.RD4 = 1;
				PORTDbits.RD4 = 0;
			}
		}
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

