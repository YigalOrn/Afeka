/*
Lab_4_1
תוכנית לזיהוי מקש והצגת הקוד שלו על גבי תצוגת המנורות
*/
#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortB(void);
void initPortD(void);
void initPortE(void);
void initPortF(void);
void initPortG(void);
void print_led(char x);
void delay(void);

int num_led, i, keyVal, column;

void main(void)
{
	char flag = 0;
	int RUN_ZERO[4] = { 0xee, 0xdd, 0xbb, 0x77 };
	initPortB();
	initPortD();
	initPortE();
	initPortF();
	initPortG();

	PORTG = 0x00;
	PORTF = 0x07;
	flag = 0;

	while (1)
	{
		column = 0;
		while (1)
		{
			PORTG = 0x00;
			PORTF = 0x07;
			PORTE = RUN_ZERO[column];
			delay();
			keyVal = PORTB & 0x0F;
			if (keyVal != 0x0f)
			{
				flag = 1;
				break;
			}
			column++;
			if (column == 4)
			{
				column = 0;
			}
		}
		num_led = ((RUN_ZERO[column] & 0xf0) | (keyVal));
		print_led(num_led);
	}
}//main

void print_led(char x)
{
	PORTF = 4;
	PORTE = x;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
}

void initPortB(void)
{
	unsigned int portMap;
	portMap = TRISB;
	portMap &= 0xFFFF7FFF;//1111...1111-0111-1111...1111//for RB15
	portMap |= 0xF;//for RB(3-0)
	TRISB = portMap;

	AD1PCFG |= 0x800f; //Select PORTB to be digital port input (and not analog see ch 5 and 6)
	
	//0x3C = 0011-1100
	CNCONbits.ON = 0;//Change Notice Module - On bit, CN module is disabled
	CNEN |= 0x3C;
	CNPUE |= 0x3C; //Set RB0 - RB3 as inputs with weak pull-up
	CNCONbits.ON = 1; //1 = CN module is enabled
}

void initPortD(void)
{
	unsigned int portMap;
	portMap = TRISD;
	portMap &= 0xFFFFFFCF;//...1100 - 1111
	TRISD = portMap;
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

void initPortG(void)
{
	unsigned int portMap;
	portMap = TRISG;
	portMap &= 0xFFFFFFFC;
	TRISG = portMap;
	PORTG = 0x00;
}

void delay(void)
{
	unsigned int i;
	for (i = 0;i < 6400;i++);
}