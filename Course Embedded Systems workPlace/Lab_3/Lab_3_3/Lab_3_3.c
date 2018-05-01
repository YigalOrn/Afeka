/*
create new fonts and use them! to write a string of chars to present on the LCD
*/


#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


//prototypes
void busy(void);


//globals
unsigned  int  portMap;


void main(void)
{
	int i;

	char  CG_father[16] =
	{
		//-----------
		//à , tuple of 8 hex nums
		0x09,
		0x0a,
		0x0c,
		0x0c,
		0x0c,
		0x0a,
		0x09,
		0x09,
		//-----------

		//-----------
		//á , next tuple of 8 hex nums
		0x26,
		0x29,
		0x31,
		0x21,
		0x29,
		0x2b,
		0x36,
		0x34
		//-----------
	};

	char father[3] =
	{
		0,//à
		1,//á 
		0// à 
	};

	char control[7] =
	{
		0x38,// 0x38 = 0011 1000 : Function Set ---> 0 0 1 DL N F - - , notice F=0 because we use 5x8 matrix!
		0x38,// 0x38 = 0011 1000 
		0x38,// 0x38 = 0011 1000 
		0xe,//  0x0e = 0000 1110 : Display on/off control ---> 0 0 0 0 1 D C B 
		0x6,//  0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S 
		0x1,//  0x01 = 0000 0001 : Clear display - Clears entire display and sets DDRAM address 0 in address counter.  
		0x40//  0x40 = 0100 0000 : Set CGRAM address ---> 0 1 ACG ACG ACG ACG ACG ACG
	};


	portMap = TRISG;
	portMap &= 0xFFFF7FFF;
	TRISG = portMap;
	PORTGbits.RG15 = 0;//buzzer=0ff

	portMap = TRISB;
	portMap &= 0xFFFF7FFF;
	TRISB = portMap;


	//------------------------------------
	//special, marked red in ppt
	AD1PCFG |= 0x8000; // RB15-Digital
	//------------------------------------

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

	PORTF = 0x00;
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS) 

	for (i = 0; i < 7; i++)
	{
		PORTE = control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	PORTBbits.RB15 = 1;//RB15(RS), to write to CGRAM memory, the data is on the bus

	for (i = 0; i < 16; i++)
	{

		PORTE = CG_father[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	PORTBbits.RB15 = 0;//RB15(RS)
	PORTE = 0x80;//set to use the DDRAM to display on LCD
	PORTDbits.RD4 = 1;//enable=1
	PORTDbits.RD4 = 0;//enable=0
	busy();

	PORTBbits.RB15 = 1;//RB15(RS)

	for (i = 0; i < 3; i++)
	{
		PORTE = father[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	while (1);
}

void busy(void)
{
	char RD;//RD5(w/r)
	char RS;//RB15(RS)
	int STATUS_TRISE;

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

	portMap = TRISE; //portMap is a global var
	portMap |= 0x80; //0x80 = 1000 0000
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

