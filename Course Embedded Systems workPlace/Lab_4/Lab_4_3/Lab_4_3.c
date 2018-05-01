/*
Lab_4_3
תוכנית עזר לניסוי מספר 4 – הפעלת מקלדת
File: key_test3_pic_32

התוכנית משנה את זרימת התוכנית כך שהתוכנית תהיה אינרקטיבית ולא תחכה עד ללחיצת מקש
התוכנית היא מונה בינרי פשוט על גבי תצוגת הנורות הנשלט ע"י המקשים 1 ו 2 במקלדת
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
int scan_key(void);
void delay(int j);

int num_led, i, keyVal, column;

void main(void)
{
	int i;
	char k, flag_scan = 1;
	char flag = 0;
	unsigned char s;
	initPortB();
	initPortD();
	initPortE();
	initPortF();
	initPortG();


	PORTG = 0x00;
	PORTF = 0x07;
	while (1)
	{
		s = scan_key();
		if (s != 0xff)
			flag_scan = s;
		if (flag_scan == '1')
		{
			k++;
			print_led(k);
		}
		if (flag_scan == '2')
		{
			k--;
			print_led(k);
		}
	}
}//main

int scan_key(void)
{
	int RUN_ZERO[4] =
	{
		0xee, 
		0xdd, 
		0xbb, 
		0x77
	};
	int scan_key_code_ascii[32] =
	{
		 0xee,'1',0xde,'2',0xbe,'3',0x7e,'A',                                      
		 0xed,'4',0xdd,'5',0xbd,'6',0x7d,'B',                                      
		 0xeb,'7',0xdb,'8',0xbb,'9',0x7b,'C',                                        
		 0xe7,'*',0xd7,'0',0xb7,'#',0x77,'D'
	};
	int i, num_code;
	int  column = 0;
	int  flag = 0;
	PORTG = 0x00;
	PORTF = 0x07;
	for (i = 0;i < 100;i++)
	{
		PORTE = RUN_ZERO[column];
		delay(10);
		keyVal = PORTB & 0x0F;
		if (keyVal != 0x0f) 
		{ 
			flag = 1; break; 
		}
		column++;
		if (column == 4) 
		{
			column = 0;//  טור 
		}
	}


	if (flag == 1)
	{
		num_code = ((RUN_ZERO[column] & 0xf0) | (keyVal));
		for (i = 0;i < 32;i += 2)
		{
			if (num_code == scan_key_code_ascii[i])
			{
				i = scan_key_code_ascii[i + 1];
				break;
			}
		}
	}
	else
	{
		i = 0xff;
	}
	return(i);
}

void print_led(char x)
{
	PORTF = 4;
	PORTE = x;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	delay(640000);
}

void initPortB(void)
{
	unsigned int portMap;
	portMap = TRISB;
	portMap &= 0xFFFF7FFF;
	TRISB = portMap;
	AD1PCFG = 0x800f; //Select PORTB to be digital //port input
	CNCONbits.ON = 0;
	CNEN = 0x3C;
	CNPUE |= 0x3C;//Set RB0 - RB3 as inputs with weak //pull-up
	CNCONbits.ON = 1;
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

void delay(int j)
{
	unsigned int i;
	for (i = 0;i < j;i++);
}
