# Title: test       	Filename:
# Author:       	Date:
# Description:
# Input:
# Output:
################# Data segment #####################
.data

buf: .asciiz "abcd" 



################# Code segment #####################
.text



.globl main
main:	# main program entry

# $t1 - char's array (the string) index.
# $t2 - base register for this string.

and $t1,$t1,$zero
la $t2,buf # load the base address of the string

printCharLoop:
 
lb $a0,0($t2)

        #print one char each time
        li $v0, 11	
	syscall

addiu $t2,$t2,1 # increment the base register (address) by ine byte !

bne $a0,'\0',printCharLoop



exit:
	li $v0, 10	# Exit program
	syscall






