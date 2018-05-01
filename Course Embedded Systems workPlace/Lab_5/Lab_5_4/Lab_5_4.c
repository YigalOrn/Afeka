/*
הוצאת שני גלי סינוס בהפרש פאזה של 90 מעלות
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
	int x = 0, y = 45;//הפרש 90 מעלות 
	char data[180];
	initPortD();
	initPortE();
	initPortF();
	for (x = 0;x < 180;x++)
	{
		data[x] = 127 + 127 * sin((2 * 3.14*x) / 180);
	}

	x = 0;
	while (1)
	{
		PORTFbits.RF8 = 1;
		PORTF = 0x05;//Select DAC channel A
		PORTE = data[x];
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		PORTFbits.RF8 = 1;		
		PORTF = 0x06;//Select DAC channel B
		PORTE = data[y];
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
		y++;
		if (x == 180)
			x = 0;
		if (y == 180)
			y = 0;
	}
	return 0;
}//main

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
