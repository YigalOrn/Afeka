# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data
getChar: .asciiz  "\nPlease enter a latter:\n"
wrongInput: .asciiz  "\nThe latter is not between a-z:\n"

################# Code segment #####################
.text
.globl main
main:	# main program entry


li $s1,97
li $s2,122




wrong:
la $a0,wrongInput
li $v0,4
syscall

loop:

la $a0,getChar
li $v0,4
syscall

li $v0,12
syscall

move $a0,$v0#save command by transfering it to $a0

blt $a0,$s1,wrong
bgt $a0,$s2,wrong



loop2:


li $v0,11
syscall



addi $a0,$a0,1

bgt $a0,$s2,exit

j loop2


exit:
li $v0, 10	# Exit program
syscall


