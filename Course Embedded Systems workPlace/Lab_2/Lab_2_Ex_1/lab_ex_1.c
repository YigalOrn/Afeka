#include <p32xxxx.h>


#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


//globals
long z;//for-loop counter
long delay_speed;
long delay_1 = 340000;
long delay_2 = 640000;

enum DIRECTION { OP1, OP2 };
enum DIRECTION direction;


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

	if (direction == OP1)
	{
		counter--;
	}
	else if (direction == OP2)
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

	if (direction == OP1)
	{
		if (y > 1)
			y >>= 1;
		else
			y = 128;
	}
	else if (direction == OP2)
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

	if (direction == OP1)//inwards
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
	else if (direction == OP2)//outwards
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
	int p;//data holder for the LEDs

	TRISF = 0;
	TRISD = 0;

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
			delay_speed = delay_1;
		}
		else
		{
			delay_speed = delay_2;
		}

		if (switch_input & 8)
		{
			direction = OP1;
		}
		else
		{
			direction = OP2;
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
				menifa_operation();
			}
			else if (switch_input & 2)//shift
			{
				shift_operation();
			}
			else if (switch_input & 1)//counter
			{
				counter_operation();
			}
			else//explicitly do nothing
			{
				reset_led_display_operation();
			}
		}
		//--------------------------------------

	}//while
}//main
