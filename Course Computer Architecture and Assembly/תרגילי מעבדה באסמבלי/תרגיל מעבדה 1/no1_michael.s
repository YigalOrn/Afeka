# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data
first: .word  0x1111ace0

################# Code segment #####################
.text
.globl main
main:	# main program entry


#start even counter with 8
#each time sub the last bit in a byte from even counter
#do while the even counter is different form zero !


	lw  $s0,first
	addi $t0,$0,0 #even counter
	addi $t1,$0, 8  #$t1=loop counter
	#addi $t2,$0, 0
loop:	andi $t3, $s0, 1 # get the value of the lsb of $s0 in $t3
	bne  $t3,$0,odd
	addi $t0,$t0,1
odd:
	srl $s0, $s0, 4 # shift the bits 4 times to the right
	addi $t1,$t1,-1 #001-->100-->101
	bne   $t1, $0, loop # loop for 8 times

	

li $v0, 10	# Exit program
syscall

