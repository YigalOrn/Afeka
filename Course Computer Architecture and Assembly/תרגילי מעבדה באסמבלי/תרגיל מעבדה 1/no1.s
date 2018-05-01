# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data
first: .word  0x12345678

################# Code segment #####################
.text
.globl main
main:	# main program entry

	lw  $s0,first
        
        //multiply each time by one padded with zeroes 0x00000001
        //put the result in some register
        //shift the word right by 4
        //with a loop run over the word 8 times
        
        addi $t3,$zero,0//counter
        
        loop:
         andi $t2,$s0,1 
         beq $t2,$zero, add
        add: 
        addu $t3,$t3,1
        srl $s0,$s0,4
        blt ,,loop
        

li $v0, 10	# Exit program
syscall

