# Title: Lab1        	Filename:
# Author:       	Date:
# Description: TEST 05.06.2014 moed alef
#
#get a number in $a1 - e.g 0x12345478 , checks if the number is a palindrom in bytes!
#if it is return 1 in $v1  else return 0 in $v1
#print the number in $a1 in base 4
#
################# Data segment #####################
.data

CRLF: .asciiz "\n"
BYE: .asciiz "\nGOOD-BYE\n"
################# Code segment #####################
.text
.globl main
main:	# main program entry




#addi $a1,$a1,0x12345478
addi $a1,$a1,0x12343412 # byte palindrom

jal wow
        
        
        #is palindrom print answer
        li $v0,1
        move $a0,$v1
        syscall
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
wow:

lui $t1,0xff00
and $t2,$a1,$t1
srl $t2,$t2,24
li $t1,0xff
and $t3,$a1,$t1

beq $t2,$t3,skip1
li $v1,0
j print

skip1:

lui $t1,0x00ff
and $t2,$a1,$t1
srl $t2,$t2,8
li $t1,0xff00
and $t3,$a1,$t1

beq $t2,$t3,skip2
li $v1,0
j print

skip2:

li $v1,1

print:

li $t1,30
li $t2,3
li $v0,1

loop:

add $a0,$a1,$zero
srlv $a0,$a0,$t1
and $a0,$a0,$t2
syscall

addi $t1,$t1,-2
bgez $t1,loop

        #CRLF
        li $v0,4
        la $a0,CRLF
        syscall


jr $ra # return





