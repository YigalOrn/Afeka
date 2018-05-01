/*
Lab_4_2
תוכנית לזיהוי מקש והצגת קוד ה-אסקי המתאים על גבי המנורות
*/
#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8
void initPortB(void);
void print_led(char x);
void initPortD(void);
void initPortE(void);
void initPortF(void);
void initPortG(void);
void delay(void);

int num_led, i, keyVal, column;

void main(void)
{
	int i;
	char flag = 0;
	int RUN_ZERO[4] = { 0xee, 0xdd, 0xbb, 0x77 };
	int scan_key_code_ascii[32] =
	{
		0xee,'1',0xde,'2',0xbe,'3',0x7e,'A',
		0xed,'4',0xdd,'5',0xbd,'6',0x7d,'B',
		0xeb,'7',0xdb,'8',0xbb,'9',0x7b,'C',
		0xe7,'*',0xd7,'0',0xb7,'#',0x77,'D'
	};
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
		for (i = 0;i < 32;i += 2)
		{
			if (num_led == scan_key_code_ascii[i])
			{
				break;
			}
		}
		print_led(scan_key_code_ascii[i + 1]);
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
	portMap &= 0xFFFF7FFF;
	TRISB = portMap;
	AD1PCFG = 0x800f; //Select PORTB to be digital port input
	CNCONbits.ON = 0;
	CNEN = 0x3C;
	CNPUE |= 0x3C; //Set RB0 - RB3 as inputs with weak pull-up
	CNCONbits.ON = 1;
}

void delay(void)
{
	unsigned int i;
	for (i = 0;i < 6400;i++);
}

void initPortD(void)
{
	unsigned int portMap;
	portMap = TRISD;
	portMap &= 0xFFFFFFCF;
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


