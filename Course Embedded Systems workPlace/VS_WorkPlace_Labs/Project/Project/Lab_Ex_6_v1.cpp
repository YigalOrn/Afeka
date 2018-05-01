#include <p32xxxx.h>
#include <stdlib.h>
#include <string.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


//------------------------------------------------------------


//prototypes
void initPortB(void);
void initPortD(void);
void initPortE(void);
void initPortF(void);
void initPortG(void);
int scan_key(void);
void delay(long int j);

void makeBeep(void);
void write_to_LCD_Lab_Ex_6(char str[], int size);
char* convertVoltToString(float digitalVolt);
char* createDescriptionStr(char* str1, char* str2);
void analog1();
void analog2();
void analog3();

char description_str_control[7] = {
	0x38,// 0x38 = 0011 1000 : Function Set ---> 0 0 1 DL N F - -
	0x38,// 0x38 = 0011 1000
	0x38,// 0x38 = 0011 1000
	0x0e,// 0x0e = 0000 1110 : Display on/off control ---> 0 0 0 0 1 D C B
	0x06,// 0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S
	0x1, // 0x01 = 0000 0001 : Clear display - Clears entire display and sets DDRAM address 0 in address counter.
	0xc0 //set DDRAM address to start of second line
};



//------------------------------------------------------------

void main(void)
{
	unsigned char s, flag_scan = '9';
	int x;

	initPortB();
	initPortD();
	initPortE();
	initPortF();
	initPortG();

	while (1)
	{
		PORTG = 0x00;//keypad
		PORTF = 0x07;//second decoder enable

		s = scan_key();
		if (s != 0xff)
		{
			switch (s)
			{
			case '1':
				flag_scan = s;//memory element
				makeBeep();
				break;
			case '2':
				flag_scan = s;//memory element
				makeBeep();
				break;
			case '3':
				flag_scan = s;//memory element
				makeBeep();
				break;
			default:
				makeBeep();
				makeBeep();
				break;
			}
		}

		if (flag_scan == '1')//
		{
			analog1();
		}
		else if (flag_scan == '2')
		{
			analog2();
		}
		else if (flag_scan == '3')
		{
			analog3();
		}

	}//while
}//main

//------------------------------------------------------------

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
		0xee, '1', 0xde, '2', 0xbe, '3', 0x7e, 'A',
		0xed, '4', 0xdd, '5', 0xbd, '6', 0x7d, 'B',
		0xeb, '7', 0xdb, '8', 0xbb, '9', 0x7b, 'C',
		0xe7, '*', 0xd7, '0', 0xb7, '#', 0x77, 'D'
	};

	int i, num_code, keyVal;
	int  column = 0;
	int  flag = 0;
	PORTG = 0x00;
	PORTF = 0x07;

	for (i = 0; i < 100; i++)
	{
		PORTE = RUN_ZERO[column];
		delay(10);
		keyVal = PORTB & 0x0F;
		if (keyVal != 0x0f)
		{
			flag = 1;
			break;
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
		for (i = 0; i < 32; i += 2)
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

void initPortB(void)
{
	unsigned int portMap;
	portMap = TRISB;
	portMap &= 0xFFFF7FFF;//RB15 out
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
	portMap &= 0xFFFFFFCF;//1111...1100 1111// RD4 and RD5 out
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
	portMap &= 0xFFFFFEF8;//1111...1111 1110 1111 1000
	TRISF = portMap;
	PORTFbits.RF8 = 1;
}

void initPortG(void)
{
	unsigned int portMap;
	portMap = TRISG;
	portMap &= 0xFFFF7FFC;// 1111 1111 1111 1111 0111 1111 1111 1100 //15-12 11-8 7-4 3-0 // set buzzer RG15 out
	TRISG = portMap;
	PORTG = 0x00;
}

void delay(long int j)
{
	static long int i;
	for (i = 0; i < j; i++);
}

void busy(void)
{
	char RD;//RD5(w/r)
	char RS;//RB15(RS)
	int STATUS_TRISE;
	unsigned int portMap;

	//save current system state
	RS = PORTBbits.RB15;
	RD = PORTDbits.RD5;
	STATUS_TRISE = TRISE;

	/*
	check the BF bit status, by definitoin in our system conf. it is the the 7th bit in RE(7-0) i.e our bus
	you could check it in the LCD code table.
	what is going on here:
	we set RB15, RD5 and the RE(7-0) bus to the following, 0 1|BF AC AC AC|AC AC AC AC.
	we set the BF to 1 because when we repeatably send the - Read busy flag & address control string
	the LCD will ultimately will flip the BF bit to 0 indicating it is willing to accept more data to the specified
	DDRAM or CGRM ! address, here we give the address of the first line in DDRAM i.e. 0x80 .
	*/

	//adjust to create a control command to send to the LCD
	PORTBbits.RB15 = 0;// set RS 15th bit
	PORTDbits.RD5 = 1;//set RD5(w/r), set RD 5th bit

	portMap = TRISE;
	portMap |= 0x80; //0x80 = 1000 0000// set RE7 IN
	TRISE = portMap;

	do
	{
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0	
	} while (PORTEbits.RE7);

	PORTDbits.RD5 = RD;
	PORTBbits.RB15 = RS;
	TRISE = STATUS_TRISE;
}

//------------------------------------------------------------

void makeBeep(void)
{
	PORTGbits.RG15 = 1;//buzzer on
	delay(32000 * 2);
	PORTGbits.RG15 = 0;//buzzer off
}

void write_to_LCD_Lab_Ex_6(char str[], int size)
{
	int portMapE = TRISE;
	int portMapF = TRISF;
	int portMapB = TRISB;
	int portMapD = TRISD;
	unsigned char PORTF_curr = PORTF;
	unsigned char PORTE_curr = PORTE;
	unsigned char PORTB_curr = PORTB;
	unsigned char PORTD_curr = PORTD;
	int i;


	TRISE &= 0xFF00;//out (7-0)
	TRISD &= 0xFFCF;//....1100 1111
	TRISB &= 0x7FFF;//0111 1111 1111 1111
	TRISF &= 0xFEF8;//1111 1110 1111 1000

	//----------------------------------
	//send a control string for the descr str
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTF = 0x00;

	for (i = 0; i < 7; i++)
	{
		PORTE = description_str_control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}
	//----------------------------------

	//----------------------------------
	//write descripstion string
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < size; i++)
	{
		PORTE = str[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}
	//----------------------------------

	TRISE = portMapE;
	TRISB = portMapB;
	PORTE = PORTE_curr;
	PORTF = PORTF_curr;
	PORTB = PORTB_curr;
}

//------------------------------------------------------------

char* convertVoltToString(float digitalVolt)
{
	char* voltStr = (char*)malloc(sizeof(char)* 4);
	digitalVolt = (digitalVolt*3.3) / 1023;

	voltStr[3] = ((int)(digitalVolt * 100) % 10) + '0';
	voltStr[2] = ((int)(digitalVolt * 10) % 10) + '0';
	voltStr[1] = '.';
	voltStr[0] = ((int)digitalVolt % 10) + '0';

	return voltStr;
}

char* createDescriptionStr(char* str1, char* str2)
{
	int str1len = strlen(str1);
	int str2len = strlen(str2);

	char* descrStr = (char*)malloc(sizeof(char)*(str1len + str2len + 1));
	descrStr = strcat(str1, str2);
	descrStr[str1len + str2len] = '\0';

	return descrStr;
}

void analog1()
{
	unsigned long i, ADCValue;
	float digitalVolt;


	AD1PCFG = 0xFEFF; // convert from digital to analog: rest of PORTB = Digital; RB8 = 0 = analog
	AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ... 
	// and start/set converting process
	AD1CHS = 0x00080000; // in this example RB8/AN8 is the input
	AD1CSSL = 0x100; // Select  RB8
	AD1CON3 = 0x0002; // Clock select
	AD1CON2 = 0; // 0 -> 0x00..0,  Vref-not Scan-BUFM  Result –MUX  A
	AD1CON1SET = 0x8000; // turn ADC ON


	AD1CON1SET = 0x0002; // start sampling ...
	delay(100000);//// DelayNmSec(100); // for 100 mS
	AD1CON1CLR = 0x0002; // start Converting
	while (!(AD1CON1 & 0x0001)); // conversion done?
	ADCValue = ADC1BUF0; // yes then get ADC value

	//--------------------
	digitalVolt = (float)ADCValue;
	digitalVolt = (digitalVolt*3.3) / 1023;

	char descrptStr[14] = "Analog1 - ";
	descrptStr[13] = ((int)(digitalVolt * 100) % 10) + '0';
	descrptStr[12] = ((int)(digitalVolt * 10) % 10) + '0';
	descrptStr[11] = '.';
	descrptStr[10] = ((int)digitalVolt % 10) + '0';
	descrptStr[14] = 'V';

	write_to_LCD_Lab_Ex_6(descrptStr, 14);
}

void analog2()
{
	unsigned long i, ADCValue;
	float digitalVolt;


	AD1PCFG = 0xFEFF; // convert from digital to analog: rest of PORTB = Digital; RB8 = 0 = analog
	AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ... 
	// and start/set converting process
	AD1CHS = 0x00090000; // in this example RB8/AN8 is the input
	AD1CSSL = 0x100; // Select  RB8
	AD1CON3 = 0x0002; // Clock select
	AD1CON2 = 0; // 0 -> 0x00..0,  Vref-not Scan-BUFM  Result –MUX  A
	AD1CON1SET = 0x8000; // turn ADC ON


	AD1CON1SET = 0x0002; // start sampling ...
	delay(100000);//// DelayNmSec(100); // for 100 mS
	AD1CON1CLR = 0x0002; // start Converting
	while (!(AD1CON1 & 0x0001)); // conversion done?
	ADCValue = ADC1BUF0; // yes then get ADC value

	//--------------------
	digitalVolt = (float)ADCValue;
	digitalVolt = (digitalVolt*3.3) / 1023;

	char descrptStr[14] = "Analog2 - ";
	descrptStr[13] = ((int)(digitalVolt * 100) % 10) + '0';
	descrptStr[12] = ((int)(digitalVolt * 10) % 10) + '0';
	descrptStr[11] = '.';
	descrptStr[10] = ((int)digitalVolt % 10) + '0';
	descrptStr[14] = 'V';

	write_to_LCD_Lab_Ex_6(descrptStr, 14);
}

void analog3()
{
	unsigned long i, ADCValue;
	float digitalVolt;


	AD1PCFG = 0xFEFF; // convert from digital to analog: rest of PORTB = Digital; RB8 = 0 = analog
	AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ... 
	// and start/set converting process
	AD1CHS = 0x00090000; // in this example RB8/AN8 is the input
	AD1CSSL = 0x100; // Select  RB8
	AD1CON3 = 0x0002; // Clock select
	AD1CON2 = 0; // 0 -> 0x00..0,  Vref-not Scan-BUFM  Result –MUX  A
	AD1CON1SET = 0x8000; // turn ADC ON



	AD1CON1SET = 0x0002; // start sampling ...
	delay(100000);//// DelayNmSec(100); // for 100 mS
	AD1CON1CLR = 0x0002; // start Converting
	while (!(AD1CON1 & 0x0001)); // conversion done?
	ADCValue = ADC1BUF0; // yes then get ADC value, 1024 bit


	float digitalVal = ADCValue / 4;//compression for D/A 

	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTF = 0x05;//Select DAC channel A
	PORTE = digitalVal;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;

	write_to_LCD_Lab_Ex_6("A to D to scope", 15);


}
//------------------------------------------------------------