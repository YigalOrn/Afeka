# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data


################# Code segment #####################
.text
.globl main
main:	# main program entry

li $t1,169
li $t2,-9

add $t3,$t1,$t2

li $v0, 10	# Exit program
syscall

