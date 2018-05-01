# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data
getChar: .asciiz  "\nPlease enter a char:\n"
getNum: .asciiz "\nPlease enter an integer between 1-9:\n"
numNotInRangeException: .asciiz  "\nThe number is not in range !\n"

################# Code segment #####################
.text
.globl main
main:	# main program entry


#load lims for conditions
li $s1,1
li $s2,9
#use as printing counter
and $s3,$s3,0






#print some string to console
la $a0,getChar
li $v0,4
syscall
#read one char
li $v0,12
syscall
#save the readen char
move $a1,$v0

readNumLoop:

#print some string to console
la $a0,getNum
li $v0,4
syscall
#read one char
li $v0,5
syscall
#save the readen num
move $a2,$v0


#check lims using condition statements
blt $a2,$s1,wrongInput
bgt $a2,$s2,wrongInput
j printValuesLoop


wrongInput:
la $a0,numNotInRangeException
li $v0,4
syscall
j readNumLoop




printValuesLoop:

move $a0,$a1
li $v0,11
syscall

addi $s3,$s3,1

beq $s3,$a2,exit

j printValuesLoop


# Exit program
exit:
li $v0, 10	
syscall


