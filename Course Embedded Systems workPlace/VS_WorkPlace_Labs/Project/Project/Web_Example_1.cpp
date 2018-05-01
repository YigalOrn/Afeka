/*
* File:   LCD_FIRST.c
* Author: Simon
*
* Created on 23 December 2011, 22:30

http://www.microchip.com/forums/m622650.aspx
*/

#include <p32xxxx.h> 
#include <plib.h>   /* Configuration Bits */ 

#pragma config FNOSC    = PRIPLL        // Oscillator Selection 
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (PIC32 Starter Kit: use divide by 2 only) 
#pragma config FPLLMUL  = MUL_18        // PLL Multiplier 
#pragma config FPLLODIV = DIV_1         // PLL Output Divider 
#pragma config FPBDIV   = DIV_2         // Peripheral Clock divisor 
#pragma config POSCMOD  = XT            // Primary Oscillator   #define SYS_CLOCK 72000000L             //MAIN CLOCK MHZ 
#define FPB_CLOCK 36000000L             //PERIPHERAL CLOCK MHZ   #define LCD_D4   _RE4                  //SETUP PINS FOR LCD 
#define LCD_D5   _RE5 
#define LCD_D6   _RE6 
#define LCD_D7   _RE7 
#define LCD_RS   _RE0 
#define LCD_EN   _RE1 #define LCD_D4_DIR   _TRISE4           //SETUP PIN DIRECTIONS FOR LCD 
#define LCD_D5_DIR   _TRISE5 
#define LCD_D6_DIR   _TRISE6 
#define LCD_D7_DIR   _TRISE7 
#define LCD_RS_DIR   _TRISE0 
#define LCD_EN_DIR   _TRISE1 #define LCD_COMMAND 0                   //SOME COMANDS FOR LCD 
#define LCD_DATA    1 
#define CLEAR_SCREEN 0X01 
#define SET_HOME     0X02   

typedef union
{                         //DEFINES BITS IN A BYTE 
	struct
	{                              //THIS IS USED BY LCD_WRITE 
		unsigned D0 : 1;
		unsigned D1 : 1;
		unsigned D2 : 1;
		unsigned D3 : 1;
		unsigned D4 : 1;
		unsigned D5 : 1;
		unsigned D6 : 1;
		unsigned D7 : 1;
	};
	struct
	{
		unsigned w : 8;
	};
} _LCD_DATA;

char TXT[4];                            //SOME VAR'S 
char NUM = 123;   void LCD_INIT();
void DELAY_US(unsigned T);
void LCD_WRITE(char RS, char C);
void LCD_WRITE_TEXT(char LINE, char COL, char *TEXT);


void DELAY_MS(unsigned T);   int main(void) 
{
	LCD_INIT();
	LCD_WRITE(LCD_COMMAND, CLEAR_SCREEN);                   //WRITES A CLEAR SCREEN COMMAND AFTER INIT 
	DELAY_MS(50);                                                               //SHORT DELAY AFTER CLEAR 
	LCD_WRITE(LCD_COMMAND, SET_HOME);                           //MOVE TO FIRST COL ON TOP LINE 
	DELAY_MS(50);                                                   //SHORT DELAY AFTER MOVE 

	LCD_WRITE_TEXT(1, 0, "HELLO WORLD!!");            //WRITE A "HELLO WORLD!!" MSG ON THE TOP LINE              sprintf(TXT," NUM = %d",NUM);                   //USE SPRINTF TO CONVERT VAR'S TO STRING 
	LCD_WRITE_TEXT(2, 0, TXT);     return 0;
}
void LCD_WRITE(char RS, char C) 
{
	_LCD_DATA LCDDATA;                                                                          //SENDS THE BYTE TO THE LCD IN TWO PARTS 
	DELAY_MS(1);                                                                                //USE THE DATASHEETS FROM CRYSTAL FONTZ 
	LCDDATA.w = C;                                                                          //TO UNDERSTAND TIMINGS. 
	LCD_EN = 1; LCD_RS = RS;
	LCD_D4 = LCDDATA.D4; LCD_D5 = LCDDATA.D5; LCD_D6 = LCDDATA.D6; LCD_D7 = LCDDATA.D7;
	DELAY_US(5);
	LCD_EN = 0;
	DELAY_US(5);
	LCD_EN = 1;
	LCD_D4 = LCDDATA.D0; LCD_D5 = LCDDATA.D1; LCD_D6 = LCDDATA.D2; LCD_D7 = LCDDATA.D3;
	DELAY_US(5);
	LCD_EN = 0;
	DELAY_US(5);
	LCD_EN = 1;
}
void LCD_WRITE_TEXT(char LINE, char COL, char *TEXT) 
{
	char ADDR = 0;
	if (LINE == 1) 
	{ 
		ADDR = 0X80 + COL; 
	}                                           //WORKS OUT ADDRESS FOR TEXT 
	if (LINE == 2) 
	{ 
		ADDR = (0X80 + 0X40) + COL; 
	}
	LCD_WRITE(LCD_COMMAND, ADDR);                                                //SET ADDRESS 
	while (*TEXT > 0) 
	{                                                           //WRITE TEXT 
		LCD_WRITE(LCD_DATA, *TEXT++);
	}
}   
void LCD_INIT() 
{
	_LCD_DATA LCDDATA;
	LCD_D4_DIR = 0; LCD_D5_DIR = 0; LCD_D6_DIR = 0; LCD_D7_DIR = 0;             //SET PORT DIRECTIONS 
	LCD_RS_DIR = 0; LCD_EN_DIR = 0;     DELAY_MS(100);                                                                  //POWER UP DELAY 
	LCDDATA.w = 0X30;                                                               //SEND REGISTERS 
	LCD_EN = 1; LCD_RS = LCD_COMMAND;
	LCD_D4 = LCDDATA.D4; LCD_D5 = LCDDATA.D5; LCD_D6 = LCDDATA.D6; LCD_D7 = LCDDATA.D7;
	DELAY_US(5);
	LCD_EN = 0;
	DELAY_US(5);
	LCD_EN = 1;     LCD_WRITE(LCD_COMMAND, 0X28);                                                    //SEND FUNCTION COMMAND FIRST 
	LCD_WRITE(LCD_COMMAND, 0X28);                                                    //SEND FUNCTION COMMAND SECOND 
	LCD_WRITE(LCD_COMMAND, 0X0F);                                                    //SET SHIFT REG 
	LCD_WRITE(LCD_COMMAND, CLEAR_SCREEN);                                            //CLEAR SCREEN 
	DELAY_MS(20);
	LCD_WRITE(LCD_COMMAND, 0X06);                                                    //I FORGOT 
}
void DELAY_MS(unsigned T) 
{
	T1CONbits.ON = 1;
	T1CONbits.TCKPS = 0;
	T1CONbits.TCS = 0;
	while (T--) 
	{
		TMR1 = 0;
		while (TMR1 < FPB_CLOCK / 1000);
	}
}
void DELAY_US(unsigned T) 
{
	T1CONbits.ON = 1;
	T1CONbits.TCKPS = 0;
	T1CONbits.TCS = 0;
	while (T--) 
	{
		TMR1 = 0;
		while (TMR1 < FPB_CLOCK / 1000000);
	}
}