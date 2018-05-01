# Title: Lab1        	Filename:
# Author:       	Date:
# Description: TEST 22.10.2012 moed bet
################# Data segment #####################
.data
#str: .asciiz  "abcabcdeNs43efghijk#"
str: .asciiz  "abcabcdeNs43#"
CRLF: .asciiz "\n"
BYE: .asciiz "\nGOOD-BYE\n"
################# Code segment #####################
.text
.globl main
main:	# main program entry


la $a0,str
jal count_abc


  # print outcome from procedure
        move $a0,$v0
        li $v0,1
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
count_abc:

move $t1,$a0 # ptr_current
move $t2,$a0    # ptr_next
addiu $t2,$t2,1 #

# $t3 - current byte
# $t4 - next byte
# $t5 - sum
# $t6 - counter = 1
# $t7 - sub element

addiu $t6,$t6,1


loop:

lb $t3,0($t1)
lb $t4,0($t2)

sub $t7,$t4,$t3 # avoid abs
bne $t7,1,continue

addiu $t6,$t6,1 # increment ctr
addiu $t2,$t2,1 # increment ptr_next
addiu $t1,$t1,1 # increment ptr_current

j goto
continue:

blt $t6,$t5,skip
move $t5,$t6 # change the sum to the longest sequence
skip:
move $t1,$t2 # ptr_curent = ptr_next
addiu $t2,$t2,1 # increment ptr_next

and $t6,,$t6,$zero # adjust ctr
add $t6,$t6,1      # initial value = 1

goto:

bne $t4,'#',loop

move $v0,$t5

jr $ra







