#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void main(void)
{
	int x, y = 0;
	long z;
	TRISF = 0;
	TRISD = 0;

	//zero display
	TRISE = 0;
	PORTF = 4;
	PORTE = 0;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	//---------------


	while (1)
	{
		TRISE = 0xff;
		PORTF = 3;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x = PORTE;
		if (x & 1)
			y++;
		else
			y--;
		TRISE = 0;
		PORTF = 4;
		PORTE = y;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		for (z = 0; z < 640000; z++);
	}


}
