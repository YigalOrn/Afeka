# MPLAB IDE generated this makefile for use with GNU make.
# Project: Lab_Ex_3.mcp
# Date: Tue Apr 18 21:45:57 2017

AS = pic32-as.exe
CC = pic32-gcc.exe
LD = pic32-ld.exe
AR = pic32-ar.exe
HX = pic32-bin2hex.exe
RM = rm

Lab_Ex_3.hex : Lab_Ex_3.elf
	$(HX) "Lab_Ex_3.elf"

Lab_Ex_3.elf : Lab_Ex_3.o
	$(CC) -mdebugger -mprocessor=32MX460F512L "Lab_Ex_3.o" -o"Lab_Ex_3.elf" -Wl,-L"C:\Program Files (x86)\Microchip\MPLAB C32\lib",-L"C:\Program Files (x86)\Microchip\MPLAB C32\pic32mx\lib",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,--defsym=__ICD2RAM=1,-Map="Lab_Ex_3.map"

Lab_Ex_3.o : Lab_Ex_3.c
	$(CC) -mprocessor=32MX460F512L -x c -c "Lab_Ex_3.c" -o"Lab_Ex_3.o" -MMD -MF"Lab_Ex_3.d" -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -g

clean : 
	$(RM) "Lab_Ex_3.o" "Lab_Ex_3.elf" "Lab_Ex_3.hex"

