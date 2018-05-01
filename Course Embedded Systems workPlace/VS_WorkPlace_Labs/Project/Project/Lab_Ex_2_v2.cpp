#include <p32xxxx.h>


#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


//globals
long z;//LEDS delay for-loop counter
long delay_speed;
long fast = 340000;
long slow = 640000;

enum DIRECTION { UP, DOWN } typedef DIRECTION;
DIRECTION direction;

enum MODE { MODE_NONE, COUNTER = 0 , SHIFT, MENIFA, HALT } typedef MODE;
MODE curr_mode, next_mode = MODE_NONE;

enum SPEED_MODE { SPEED_MODE_NONE, SPEED_FAST, SPEED_SLOW } typedef SPEED_MODE;
SPEED_MODE curr_speed_mode, next_speed_mode = SPEED_MODE_NONE;

enum DIR_MODE { DIR_MODE_NONE, DIR_UP, DIR_DOWN } typedef DIR_MODE;
DIR_MODE curr_dir_mode, next_dir_mode = DIR_MODE_NONE;

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
	"HALT"
};
int description_str_size_arr[] = {
	15, 15, 17, 17,
	13, 13, 15, 15,
	13, 13, 15, 15,
	4
};

char* mode_str_arr[] = {"Mode 0:", "Mode 1:", "Mode 2:", "Mode 5:"};
int mode_str_size = 7;


void delay(void)
{
	unsigned long i;
	for (i = 0; i < 64000; i++);
}

void check_configuration()
{
	if (direction == UP & curr_speed_mode == SPEED_FAST)
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
	else if (direction == UP & curr_speed_mode == SPEED_SLOW)
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
		}
	}
	else if (direction == DOWN & curr_speed_mode == SPEED_FAST)
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
	else if (direction == DOWN & curr_speed_mode == SPEED_SLOW)
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

void write_to_LCD()
{
	//----------------------------------
	check_configuration();
	//----------------------------------

	int i;

	TRISE = 0x00;//write to bus

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
		delay();
	}
	
	//write mode_str
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < mode_str_size; i++)
	{
		PORTE = (mode_str_arr[curr_mode])[i];

		PORTDbits.RD4 = 1;//enable=1
		PORTDbits.RD4 = 0;//enable=0

		delay();
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
		delay();
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

		delay();
	}
	//----------------------------------	
}

void reset_led_display_operation()
{
	TRISE = 0;
	PORTF = 4;
	PORTE = 0;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
}

void counter_operation()
{
	static int counter = 0;

	if (direction == DOWN)
	{
		counter--;
	}
	else if (direction == UP)
	{
		counter++;
	}

	TRISE = 0;
	PORTF = 4;
	PORTE = counter;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	for (z = 0; z < delay_speed; z++);
}

void shift_operation()
{
	static int y = 1;
	TRISE = 0;
	PORTF = 4;
	PORTE = y;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	for (z = 0; z < delay_speed; z++);

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
	static int lefty = 16, righty = 8;

	TRISE = 0;
	PORTF = 4;
	PORTE = (lefty | righty);
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	for (z = 0; z < delay_speed; z++);

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

void main(void)
{
	int switch_input;
	unsigned int portMap;

	//----------------------------------
	//save current status abd effect only the wanted and known port bits
	portMap = TRISG;
	portMap &= 0xFFFF7FFF;// 1111 1111 1111 1111 0111 1111 1111 1111 , only 15th bit is set to 0 
	TRISG = portMap;
	PORTGbits.RG15 = 0;//buzzer = off

	portMap = TRISB;
	portMap &= 0xFFFF7FFF;// 1111 1111 1111 1111 0111 1111 1111 1111 , only 15th bit is set to 0 
	TRISB = portMap;

	portMap = TRISF;
	portMap &= 0xFFFFFEF8;// 1111 1111 1111 1111 1111 1110 1111 1000 , only 8th and 2-0 bits are set to 0 
	TRISF = portMap;

	portMap = TRISE;
	portMap &= 0xFFFFFF00;// 1111 1111 1111 1111 1111 1111 0000 0000 , only  7-0 bits are set to 0 
	TRISE = portMap;

	portMap = TRISD;
	portMap &= 0xFFFFFFCF;// 1111 1111 1111 1111 1111 1111 1100 1111 , only  4th and 5th bits are set to 0 
	TRISD = portMap;
	//----------------------------------

	while (1)
	{
		//--------------------------------------
		//read from bus switch configuration
		TRISE = 0xff;
		PORTF = 3;
		PORTDbits.RD4 = 1;
		PORTDbits.RD4 = 0;
		switch_input = PORTE;
		//--------------------------------------

		//--------------------------------------
		//set speed and direction params, they are global!
		if (switch_input & 16)//RD4-S4
		{
			delay_speed = fast;
			curr_speed_mode = SPEED_FAST;
		}
		else
		{
			delay_speed = slow;
			curr_speed_mode = SPEED_SLOW;
		}

		if (switch_input & 8)//RD4-S3
		{
			direction = DOWN;
			curr_dir_mode = DIR_DOWN;
		}
		else
		{
			direction = UP;
			curr_dir_mode = DIR_UP;
		}
		//--------------------------------------

		//--------------------------------------
		//set LEDs logic
		if (switch_input & 128)//RD7-S7, stop program execution
		{
			break;
		}
		else if (!(switch_input & 32))//RD5-S5, freeze program execution
		{
			if (switch_input & 4)//menifa
			{
				curr_mode = MENIFA;
				menifa_operation();
			}
			else if (switch_input & 2)//shift
			{
				curr_mode = SHIFT;
				shift_operation();
			}
			else if (switch_input & 1)//counter
			{
				curr_mode = COUNTER;
				counter_operation();
			}
			else//explicitly do nothing
			{
				reset_led_display_operation();
			}
		}
		else
		{
			curr_mode = HALT;
		}
		//--------------------------------------

		//--------------------------------------
		if ((next_mode != curr_mode) | (next_speed_mode != curr_speed_mode) | (next_dir_mode != curr_dir_mode))
		{
			write_to_LCD();
			next_mode = curr_mode;
			next_speed_mode = curr_speed_mode;
			next_dir_mode = curr_dir_mode;
		}
		//--------------------------------------

	}//while
}//main
