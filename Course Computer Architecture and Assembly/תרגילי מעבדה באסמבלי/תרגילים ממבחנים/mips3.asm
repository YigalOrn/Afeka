# Title: Lab1        	Filename:
# Author:       	Date:
# Description: TEST 22.10.2012 moed bet
################# Data segment #####################
.data
str: .asciiz  "The State of Israel$"
CRLF: .asciiz "\n"
BYE: .asciiz "\nGOOD-BYE\n"
################# Code segment #####################
.text
.globl main
main:	# main program entry


la $a1,str
jal steps


        
  # print BYE
      
        li $v0,4
        la $a0,CRLF
        syscall
        la $a0,BYE
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
steps:

move $t1,$a1 # $t1 - ptr_char
and $t2,$t2,$zero
and $t3,$t3,$zero
# $t3 - counter
# $t2 - upper limit
# $a0 - current char to print

loop1:

            loop2:
            lb $a0,0($t1) 
            lb $t7,1($t1)
            
            #print char
            li $v0,11
            syscall
            #print char

addiu $t3,$t3,1
addiu $t1,$t1,1
beq $t7,'$',return 
ble $t3,$t2,loop2

            #print CRLF
            move $t7,$a0
            li $v0,4
            la $a0,CRLF
            syscall
            move $a0,$t7
            #print CRLF

move $t1,$a1
and $t3,$t3,$zero
addiu $t2,$t2,1

j loop1

return:

jr $ra



