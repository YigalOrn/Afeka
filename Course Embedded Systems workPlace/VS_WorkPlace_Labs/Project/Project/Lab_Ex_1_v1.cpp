#include <p32xxxx.h>
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


long z, delay_speed = 640000;


void reset_led_display_operation()
{
	TRISE = 0;
	PORTF = 4;
	PORTE = 0;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
}

void counter_operation(int switch_input)
{
	static int counter = 0;

	if (switch_input & 8)
	{
		counter--;
	}
	else
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

void shift_operation(int switch_input)
{
	static int y = 1;
	TRISE = 0;
	PORTF = 4;
	PORTE = y;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	for (z = 0; z < delay_speed; z++);

	if (switch_input & 8)
	{
		if (y >1)
			y >>= 1;
		else
			y = 128;
	}
	else
	{
		if (y < 128)
			y <<= 1;
		else
			y = 1;
	}
}

void menifa_operation(int switch_input)
{
	static int lefty = 16, righty = 8;
	TRISE = 0;
	PORTF = 4;
	PORTE = (lefty | righty);
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	for (z = 0; z < delay_speed; z++);

	if (switch_input & 8)
	{
		if (righty<8)
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
	else
	{
		if (righty>0)
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


		if (switch_input & 128)//RD7-S7
		{
			break;
		}
		else if (!(switch_input & 32))//RD5-S5
		{
			if (switch_input & 16)//RD4-S4
			{
				delay_speed = 340000;
			}
			else
			{
				delay_speed = 640000;
			}

			if (switch_input & 4)//menifa
			{
				menifa_operation(switch_input);
			}
			else if (switch_input & 2)//shift
			{
				shift_operation(switch_input);
			}
			else if (switch_input & 1)//counter
			{
				counter_operation(switch_input);
			}
			else//explicitly do nothing
			{
				reset_led_display_operation();
			}
		}
	}//while
}//main
