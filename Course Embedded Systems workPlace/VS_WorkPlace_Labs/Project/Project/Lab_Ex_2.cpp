#include <p32xxxx.h>


#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8


//globals
long z;//for-loop counter
long delay_speed;
long delay_1 = 340000;
long delay_2 = 640000;

enum DIRECTION { OP1, OP2 };
DIRECTION direction;

enum MODE {COUNTER, SHIFT, MENIFA};

char control[6] = {
	0x38,// 0x38 = 0011 1000 : Function Set ---> 0 0 1 DL N F - -
	0x38,// 0x38 = 0011 1000
	0x38,// 0x38 = 0011 1000
	0x0e,// 0x0e = 0000 1110 : Display on/off control ---> 0 0 0 0 1 D C B
	0x06,// 0x06 = 0000 0110 : Entry mode set ---> 0 0 0 0 1 I/D S
	0x1	 // 0x01 = 0000 0001 : Clear display - Clears entire display and sets DDRAM address 0 in address counter. 
};

void delay(void)
{
	unsigned long i;
	for (i = 0; i < 64000; i++);
}

void write_to_LCD(MODE mode)
{
	int i;
	int string_size;
	int string_index;
	char* string_arr[] = {
		"Counter Up Slow", "Counter Up Fast", "Counter Down Slow", "Counter Down Fast",
		"Shift Up Slow", "Shift Up Fast", "Shift Down Slow", "Shift Down Fast",
		"Swing Up Slow", "Swing Up Fast", "Swing Down Slow", "Swing Down Fast",
	};

	TRISE = 0x00;//write to bus

	//----------------------------------
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 0;//RB15(RS)
	PORTFbits.RF8 = 1;//RF8(Enable)
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
	if (direction == OP2 & delay_speed == delay_1)//up + speed up
	{
		switch (mode) 
		{
		case COUNTER:
			string_index = 1;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case SHIFT:
			string_index = 5;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case MENIFA:
			string_index = 9;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		}
	}
	else if (direction == OP2 & delay_speed == delay_2)//up + normal speed
	{
		switch (mode)
		{
		case COUNTER:
			string_index = 0;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case SHIFT:
			string_index = 4;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case MENIFA:
			string_index = 8;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		}
	}
	else if (direction == OP1 & delay_speed == delay_1)//down + speed up
	{
		switch (mode)
		{
		case COUNTER:
			string_index = 3;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case SHIFT:
			string_index = 7;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case MENIFA:
			string_index = 11;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		}
	}
	else if (direction == OP1 & delay_speed == delay_2)//down + normal speed
	{
		switch (mode)
		{
		case COUNTER:
			string_index = 2;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case SHIFT:
			string_index = 6;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		case MENIFA:
			string_index = 10;
			string_size = sizeof(string_arr[string_index]) / sizeof(char);
			break;
		}
	}
	//----------------------------------

	//----------------------------------
	PORTFbits.RF8 = 1;//RF8(Enable)
	PORTDbits.RD5 = 0;//RD5(w/r)
	PORTBbits.RB15 = 1;//RB15(RS)
	PORTF = 0x00;

	for (i = 0; i < string_size; i++)
	{
		PORTE = (string_arr[string_index])[i];

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

	if (direction == OP1)
	{
		counter--;
	}
	else if (direction == OP2)
	{
		counter++;
	}

	write_to_LCD(COUNTER);

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

	write_to_LCD(SHIFT);
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

	write_to_LCD(MENIFA);
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
		//stop program execution
		if (switch_input & 128)//RD7-S7
		{
			break;
		}
		//--------------------------------------

		//--------------------------------------
		//freeze program execution
		while (switch_input & 32);//RD5-S5
								  //--------------------------------------

	    //--------------------------------------
		//set speed and direction params, they are global!
		if (switch_input & 16)//RD4-S4
		{
			delay_speed = delay_1;//speed up
		}
		else
		{
			delay_speed = delay_2;//speed normal
		}

		if (switch_input & 8)
		{
			direction = OP1;//not normal
		}
		else
		{
			direction = OP2;//normal
		}
		//--------------------------------------

		//--------------------------------------
		//set LEDs logic
		if (switch_input & 1)//counter 
		{
			if (switch_input & 2)//shift 
			{
				if (switch_input & 4)//menifa 
				{
					menifa_operation();
				}
				shift_operation();
			}
			counter_operation();
		}
		else//explicitly do nothing 
		{
			reset_led_display_operation();
		}
		//--------------------------------------

	}//while
}//main
