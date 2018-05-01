# Title: Lab1        	Filename:
# Author:       	Date:
# Description: TEST 13.06.2013 moed alef
################# Data segment #####################
.data
str: .asciiz  "COMPUTER ARCHITECTURE and assembly!"
CRLF: .asciiz "\n"
BYE: .asciiz "\nGOOD-BYE\n"
################# Code segment #####################
.text
.globl main
main:	# main program entry


la $a1,str
jal compare

  # print BYE
        la $a0,BYE
        li $v0,4
        syscall

# Exit program
exit:
li $v0, 10	
syscall


####################################################
#Procedure:                                        #
# input : 	                                   #  
# Description:                                     #	
####################################################	
compare:


li $t1,'A'
add $t2,$a1,$zero 
# $t1 - letter to print 
# $t2 - moving ptr
# $t3 - current char

allStr:

        loop:
        lb $t3,0($t2)
        bne $t1,$t3,continue
        # print char
        add $a0,$t3,$zero 
        li $v0,11
        syscall
        # print CRLF
        la $a0,CRLF
        li $v0,4
        syscall
        j goto

        continue:
        addiu $t2,$t2,1
        bne $t3,'!',loop


goto:
addiu $t1,$t1,1 # increment to get the next letter in the ABC (e.g : A --> B )
add $t2,$a1,$zero 

ble $t1,'Z',allStr # branch if $t1 <= 'Z' 

jr $ra







