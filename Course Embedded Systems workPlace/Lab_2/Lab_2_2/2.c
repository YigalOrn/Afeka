#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void main(void)
{
	int x, i;
	TRISF = 0;
	TRISE = 0;
	TRISD = 0;
	PORTF = 4;
	PORTE = 0;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	while (1)
	{
		for (x = 0; x < 256; x++)
		{
			PORTE = x;
			PORTDbits.RD4 = 1;
			PORTDbits.RD4 = 0;
			for (i = 0; i < 64000; i++);

		}
	}
}
