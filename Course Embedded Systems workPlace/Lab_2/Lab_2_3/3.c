
#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void main(void)
{
	int x;
	TRISF = 0;
	TRISD = 0;
	while (1)
	{
		TRISE = 0xff;//input mode
		PORTF = 3;//select switches, we want to input from them
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x = PORTE;
		TRISE = 0;
		PORTF = 4;
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
	}
}
