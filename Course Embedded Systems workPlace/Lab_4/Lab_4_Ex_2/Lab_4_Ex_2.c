#include <p32xxxx.h>
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
void write_to_LCD();
void write_to_LED(unsigned char val);
void counter_operation();
void shift_operation();
void menifa_operation();


//globals
int halt_flag_up = 0, dir_flag_up = 0, speed_flag_up = 0;
long fast = 340000;
long slow = 640000;
long delay_speed = 640000;


enum DIRECTION { UP, DOWN } typedef DIRECTION;
DIRECTION direction = UP;

enum MODE { MODE_NONE = -1, COUNTER = 0, SHIFT, MENIFA, HALT } typedef MODE;
MODE curr_mode = MODE_NONE, next_mode = MODE_NONE;

enum SPEED_MODE { SPEED_MODE_NONE, SPEED_FAST, SPEED_SLOW } typedef SPEED_MODE;
SPEED_MODE curr_speed_mode = SPEED_SLOW, next_speed_mode = SPEED_MODE_NONE;

enum DIR_MODE { DIR_MODE_NONE, DIR_UP, DIR_DOWN } typedef DIR_MODE;
DIR_MODE curr_dir_mode = DIR_UP, next_dir_mode = DIR_MODE_NONE;

char mode_str_control[6] = {
	0x38,// 0x38 = 0011 1000 : Function Set ---> 0 0 1 DL N F - -
	0x38,// 0x38 = 0011 1000
	0x38,// 0x38 = 0011 1000
	0x0e,// 0x0e = 0000 1110 : Display on/off control ---> 0 0 0 0 1 D C B
	0x06,// 0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S
	0x1	 // 0x01 = 0000 0001 : Clear display - Clears entire display and sets DDRAM address 0 in address counter. 
};

char description_str_control[6] = {
	0xc0,// 0xc0 = 1100 0000 : Set DDRAM address ---> 1 ADD ADD ADD ADD ADD ADD ADD
	0x06,// 0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S
};

int description_str_index;
char* description_str_arr[] = {
	"Counter Up Slow", "Counter Up Fast", "Counter Down Slow", "Counter Down Fast",
	"Shift Up Slow", "Shift Up Fast", "Shift Down Slow", "Shift Down Fast",
	"Swing Up Slow", "Swing Up Fast", "Swing Down Slow", "Swing Down Fast",
	"HALT", "No Input Yet"
};
int description_str_size_arr[] = {
	15, 15, 17, 17,
	13, 13, 15, 15,
	13, 13, 15, 15,
	4, 12
};

char* mode_str_arr[] = { "Mode 0:", "Mode 1:", "Mode 2:", "Mode 5:" };
int mode_str_size = 7;


//------------------------------------------------------------


void main(void)
{
	unsigned char s, flag_scan = '9';

	initPortB();
	initPortD();
	initPortE();
	initPortF();
	initPortG();

	write_to_LED(0);//reset LED display

	while (1)
	{
		PORTG = 0x00;//keypad
		PORTF = 0x07;//second decoder enable

		s = scan_key();
		if (s != 0xff)
		{
			if (s != '4' & s != '5' & s != '6')
			{
				flag_scan = s;//memory element
			}
			makeBeep();
		}


		/*
		Table of translation:
		switch : keypad
		RD0-S0 : 1  counter
		RD1-S1 : 2  shift
		RD2-S2 : 3  menifa
		RD3-S3 : 4  speed
		RD4-S4 : 5  direction
		RD5-S5 : 6  halt
		RD7-S7 : 7  exit program
		*/

		//--------------------------------------
		//set speed, direction
		if (s == '4' && !speed_flag_up)//RD4-S4
		{
			delay_speed = fast;
			curr_speed_mode = SPEED_FAST;
			speed_flag_up = 1;
		}
		else if (s == '4' && speed_flag_up)
		{
			delay_speed = slow;
			curr_speed_mode = SPEED_SLOW;
			speed_flag_up = 0;
		}


		if (s == '5' && !dir_flag_up)//RD4-S3
		{
			direction = DOWN;
			curr_dir_mode = DIR_DOWN;
			dir_flag_up = 1;
		}
		else if (s == '5' && dir_flag_up)
		{
			direction = UP;
			curr_dir_mode = DIR_UP;
			dir_flag_up = 0;
		}

		if (s == '6' && !halt_flag_up)
		{
			halt_flag_up = 1;
			curr_mode = HALT;
		}
		else if (s == '6' && halt_flag_up)
		{
			halt_flag_up = 0;
		}
		//--------------------------------------

		//--------------------------------------
		//set logic
		if (flag_scan == '7')
		{
			write_to_LED(255);
			break;
		}

		if (!halt_flag_up)
		{
			if (flag_scan == '1')//counter
			{
				curr_mode = COUNTER;
				counter_operation();
			}
			else if (flag_scan == '2')//shift
			{
				curr_mode = SHIFT;
				shift_operation();
			}
			else if (flag_scan == '3')//menifa
			{
				curr_mode = MENIFA;
				menifa_operation();
			}
		}
		//--------------------------------------

		//--------------------------------------
		if ((next_mode != curr_mode) || (next_speed_mode != curr_speed_mode) || (next_dir_mode != curr_dir_mode))
		{
			write_to_LCD();
			next_mode = curr_mode;
			next_speed_mode = curr_speed_mode;
			next_dir_mode = curr_dir_mode;
		}
		//--------------------------------------
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
			column = 0;//  иеш 
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

void write_to_LCD()
{
	void check_configuration();//prototype

	int portMapE = TRISE;
	int portMapF = TRISF;
	int portMapB = TRISB;
	int portMapD = TRISD;
	unsigned char PORTF_curr = PORTF;
	unsigned char PORTE_curr = PORTE;
	unsigned char PORTB_curr = PORTB;
	unsigned char PORTD_curr = PORTD;
	int i;

	check_configuration();

	TRISE &= 0xFF00;//out (7-0)
	TRISD &= 0xFFCF;//....1100 1111
	TRISB &= 0x7FFF;//0111 1111 1111 1111
	TRISF &= 0xFEF8;//1111 1110 1111 1000

	//----------------------------------
	//send a control string fo the mode str
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTF = 0x00;

	for (i = 0; i < 6; i++)
	{
		PORTE = mode_str_control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	//write mode_str
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTF = 0x00;

	for (i = 0; i < mode_str_size; i++)
	{
		if (curr_mode != MODE_NONE)
		{
			PORTE = (mode_str_arr[curr_mode])[i];
		}
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}
	//----------------------------------

	//----------------------------------
	//send a control string for the description str
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTF = 0x00;

	for (i = 0; i < 2; i++)
	{
		PORTE = description_str_control[i];
		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}

	//write descripstion string
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < description_str_size_arr[description_str_index]; i++)
	{
		PORTE = (description_str_arr[description_str_index])[i];

		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0
		busy();
	}
	//----------------------------------	

	TRISE = portMapE;
	TRISF = portMapF;
	TRISB = portMapB;
	PORTE = PORTE_curr;
	PORTF = PORTF_curr;
	PORTB = PORTB_curr;
}

void check_configuration()
{
	if (direction == UP && curr_speed_mode == SPEED_FAST)
	{
		switch (curr_mode)
		{
		case COUNTER:
			description_str_index = 1;
			break;
		case SHIFT:
			description_str_index = 5;
			break;
		case MENIFA:
			description_str_index = 9;
			break;
		case HALT:
			description_str_index = 12;
			break;
		}
	}
	else if (direction == UP && curr_speed_mode == SPEED_SLOW)
	{
		switch (curr_mode)
		{
		case COUNTER:
			description_str_index = 0;
			break;
		case SHIFT:
			description_str_index = 4;
			break;
		case MENIFA:
			description_str_index = 8;
			break;
		case HALT:
			description_str_index = 12;
			break;
		case MODE_NONE:
			description_str_index = 13;
			break;
		}
	}
	else if (direction == DOWN && curr_speed_mode == SPEED_FAST)
	{
		switch (curr_mode)
		{
		case COUNTER:
			description_str_index = 3;
			break;
		case SHIFT:
			description_str_index = 7;
			break;
		case MENIFA:
			description_str_index = 11;
			break;
		case HALT:
			description_str_index = 12;
			break;
		}
	}
	else if (direction == DOWN && curr_speed_mode == SPEED_SLOW)
	{
		switch (curr_mode)
		{
		case COUNTER:
			description_str_index = 2;
			break;
		case SHIFT:
			description_str_index = 6;
			break;
		case MENIFA:
			description_str_index = 10;
			break;
		case HALT:
			description_str_index = 12;
			break;
		}
	}
}

void write_to_LED(unsigned char val)
{
	unsigned char PORTF_curr = PORTF;
	unsigned char PORTE_curr = PORTE;
	unsigned int portMapF = TRISF;
	unsigned int portMapE = TRISE;

	TRISE &= 0xFF00;//...0000 0000
	TRISF &= 0xFFF8;//1111 1110 1111 1000

	PORTFbits.RF8 = 1;
	PORTF = 0x04;//0000 0100 : 4

	PORTE = val;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	delay(delay_speed);

	PORTF = PORTF_curr;
	PORTE = PORTE_curr;
	TRISF = portMapF;
	TRISE = portMapE;
}


//------------------------------------------------------------


void counter_operation()
{
	static unsigned char counter = 0;

	if (direction == DOWN)
	{
		counter--;
	}
	else if (direction == UP)
	{
		counter++;
	}
	write_to_LED(counter);
}

void shift_operation()
{
	static unsigned char y = 1;

	write_to_LED(y);

	if (direction == DOWN)
	{
		if (y > 1)
			y >>= 1;
		else
			y = 128;
	}
	else if (direction == UP)
	{
		if (y < 128)
			y <<= 1;
		else
			y = 1;
	}
}

void menifa_operation()
{
	static unsigned char lefty = 16, righty = 8;

	write_to_LED(lefty | righty);

	if (direction == DOWN)
	{
		if (righty < 8)
		{
			lefty >>= 1;
			righty <<= 1;
		}
		else
		{
			lefty = 128;
			righty = 1;
		}
	}
	else if (direction == UP)
	{
		if (righty > 0)
		{
			lefty <<= 1;
			righty >>= 1;
		}
		else
		{
			lefty = 16;
			righty = 8;
		}
	}
}


//------------------------------------------------------------