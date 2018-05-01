/*
Present a string of chars on the LCD
*/

#include <p32xxxx.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

//prototypes
void delay(void);


void main(void)
{
	unsigned int portMap;

	char control[6] = {
		0x38,// 0x38 = 0011 1000 : Function Set ---> 0 0 1 DL N F - -
		0x38,// 0x38 = 0011 1000
		0x38,// 0x38 = 0011 1000
		0x0e,// 0x0e = 0000 1110 : Display on/off control ---> 0 0 0 0 1 D C B
		0x04,// 0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S
		0x1	 // 0x01 = 0000 0001 : Clear display - Clears entire display and sets DDRAM address 0 in address counter. 
	};


	char string[] = "Menachem Epstein";
	int i;

	//----------------------------------
	portMap = TRISG;
	portMap &= 0xFFFF7FFF;
	TRISG = portMap;
	PORTGbits.RG15 = 0;//buzzer=0ff
	portMap = TRISB;
	portMap &= 0xFFFF7FFF;
	TRISB = portMap;

	portMap = TRISF;
	portMap &= 0xFFFFFEF8;
	TRISF = portMap;
	PORTFbits.RF8 = 1;//RF8(Enable)

	portMap = TRISE;
	portMap &= 0xFFFFFF00;
	TRISE = portMap;

	portMap = TRISD;
	portMap &= 0xFFFFFFCF;
	TRISD = portMap;
	//----------------------------------

	//----------------------------------
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < 6; i++)
	{
		PORTE = control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		delay();
	}
	//----------------------------------

	//----------------------------------
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < 16; i++)
	{
		PORTE = string[i];

		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0

		delay();

		/*
		PORTGbits.RG15 = 1;//buzzer on
		delay();
		delay();
		PORTGbits.RG15 = 0;//buzzer off
		*/
	}
	//----------------------------------

	//-----------------------------------
	//extra to Lab_3_1
	//moves the text from rigth to left on the LCD screen

	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTF = 0x00;
	do
	{
		for (i = 0; i < 16; i++)
		{
			/*
			right,
			becuase RD5 and RB15 are both set to 0 this is a control string for the LCD
			Cursor or display shift ---> 0 0 0 1 S/C R/L - - 
			0x1f = 0001 1111

			it is a display shift, each shift command to LCD is by one char and it is controled by the for loop!!!
			our LCD has a display of 16 chars per line.
			*/
			PORTE = 0x1f;
			PORTDbits.RD4 = 1;//enable=1
			PORTDbits.RD4 = 0;//enable=0
			delay();
			delay();
			delay();
		}

		for (i = 0; i < 16; i++)
		{
			/*
			left,
			becuase RD5 and RB15 are both set to 0 this is a control string for the LCD
			Cursor or display shift ---> 0 0 0 1 S/C R/L - - 
			0x18 = 0001 1000

			it is a display shift, each shift command to LCD is by one char and it is controled by the for loop!!!
			our LCD has a display of 16 chars per line.
			*/
			PORTE = 0x18;

			PORTDbits.RD4 = 1;//enable=1
			PORTDbits.RD4 = 0;//enable=0
			delay();
			delay();
			delay();
		}

	} while (1);
	//-----------------------------------

}//main

void delay(void)
{
	unsigned long i;
	for (i = 0; i < 64000; i++);
}//delay

