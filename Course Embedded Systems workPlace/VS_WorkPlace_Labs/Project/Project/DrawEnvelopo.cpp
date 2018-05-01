/*
ציור מעטפה ע"י שני ערוצים 
in XY mode
*/

#include <p32xxxx.h>     
#include <math.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortD(void);
void initPortE(void);
void initPortF(void);

void drawEnvelope();

int main()
{
	initPortD();
	initPortE();
	initPortF();

	while (1)
	{
		drawEnvelope();
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

void drawEnvelope()
{
	int x;
	int y;

	//-------------------------------------------
	//horizontal right
	x = 0;
	PORTF = 0x05;//Select DAC channel A
	while (x < 256)
	{
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
	}
	//-------------------------------------------

	//-------------------------------------------
	//vertical up
	x = 0;
	PORTF = 0x06;//Select DAC channel B
	while (x < 256)
	{
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
	}
	//-------------------------------------------

	//-------------------------------------------
	//horizontal left
	x = 255;
	PORTF = 0x05;//Select DAC channel A
	while (x >= 0)
	{
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x--;
	}
	//-------------------------------------------

	//-------------------------------------------
	//middle from right
	x = 0;
	y = 255;
	while (x <= 127)
	{
		PORTF = 0x05;//Select DAC channel A
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
		PORTF = 0x06;//Select DAC channel B
		PORTE = y;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		y--;
	}
	//-------------------------------------------

	//-------------------------------------------
	//
	x = 127;
	while (x <= 255)
	{
		PORTF = 0x05;//Select DAC channel A
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		PORTF = 0x06;//Select DAC channel B
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x++;
	}
	//-------------------------------------------

	//-------------------------------------------
	//horizontal left
	x = 255;
	PORTF = 0x05;//Select DAC channel A
	while (x >= 0)
	{
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x--;
	}
	//-----------------------------------------

	//-------------------------------------------
	//vertical down
	x = 255;
	PORTF = 0x06;//Select DAC channel A
	while (x >= 0)
	{
		PORTE = x;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		x--;
	}
	//-------------------------------------------
}