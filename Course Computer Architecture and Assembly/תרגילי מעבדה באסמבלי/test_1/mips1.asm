# Title: test       	Filename:
# Author:       	Date:
# Description:
# Input:
# Output:
################# Data segment #####################
.data

ch: .byte 'z'

################# Code segment #####################
.text



.globl main
main:	# main program entry

lb $t0,ch

addi $t0,$t0,1

exit:
	li $v0, 10	# Exit program
	syscall






