# Title: Lab2       	Filename:
# Author:       	Date:
# Description:
# Input: 
# Output:
################# Data segment #####################
.data

msg1: .asciiz  "\n Please enter a letter a-z \n"
msg2: .asciiz  "\n wrong input please enter again \n"




################# Code segment #####################
.text
.globl main

main:	# main program entry

	la $a0,msg1	# put string address into a0
	li $v0,4	          # system call to print
	syscall		# out a string 		

check_start:
	li $v0,12 #get symbol
	syscall
	move $a0,$v0 #copy to printable register
	bgt $a0,'z',wrong
	blt $a0,'a',wrong
	beq $a0,'z',stop_cycle
	li $v0,11	
start_cycle:	
	addi $a0,$a0,1
	syscall #print char
	bne $a0,'z',start_cycle
stop_cycle:
	li $v0, 10	# Exit program
	syscall
	wrong:
	la $a0,msg2	# put string ms2 address into a0
	li $v0,4	          # system call to print
	syscall		# out a string 
	j main

	

