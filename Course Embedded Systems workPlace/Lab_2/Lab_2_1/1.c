#include <p32xxxx.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void main(void)
       {
              TRISF=0;
              TRISE=0;
              TRISD=0;
              
			  //PORTF=4;
              PORTE=0x55;
              
			  PORTDbits.RD4=1;
              PORTDbits.RD4=0;
              
			  while(1);
       } 
