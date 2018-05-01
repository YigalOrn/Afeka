# Title: lab 6	Filename:
# Author:       	Date:
# Description:
# Input: 2 arrays of 10 word sign numbers in acending order
# Output:The number that exists in both arrays in decending order
################# Data segment #####################
.data
array1:  .space 40 #array of 10 words
array2:  .space 40 #array of 10 words
msg1: .asciiz "Please enter 10 sign numbers in ascending order\n"
msg2: .asciiz "\n The number that exists in both arrays in decending order are :\n"
msg3: .asciiz "\n wrong input please enter again!\n"


################# Code segment #####################
.text
.globl main
main:	# main program entry

	
	   	la $a0,msg1	# Please enter 10 sign numbers in ascending order
		li $v0,4	# system call to print
		syscall		# out a string 		

		la	$a1,array1
		jal	get_array

		la $a0,msg1	# Please enter 10 sign numbers in ascending order
		li $v0,4	# system call to print
		syscall		# out a string 		

		la   	$a1,array2
		jal  	get_array
	
		la $a0,msg2	# The number that exists in both arrays in decending order are 
		li $v0,4	# system call to print
		syscall		# out a string 	
		
		la $a1,array1
		la $a2,array2
		jal  find_eq

	   li $v0, 10	# Exit program
	   syscall
	   

####################################################
#Procedure:  get array                             #
# input : $a1-->array address in memory	           #  
# Description save in the array  10 sign numbers   #
# in ascending order			           # 	
####################################################	 

get_array:
	li $v0, 5
	syscall		#syscall 5 read int
	sw $v0, 0($a1)
	li $t0, 9	#loop counter
	move $t1, $v0
loop:
	li $v0, 5
	syscall
	bgt $v0, $t1, good
	li $v0, 4
	la $a0, msg3
	syscall
	j	loop
good:
	add $a1, $a1, 4
	sw $v0, 0($a1)
	move $t1, $v0
	add $t0, $t0, -1
	bnez $t0, loop
	
	jr $ra
###################################################################
#Procedure find_eq						  # 		 
#input : $a1, $a2 -->Address of two arrays of 10 sign numbers   # 
# in ascending order				                  # 
#output:The numbers that exists in both arrays in decending order #
##############################################################

find_eq:
	li $t1, 0	#t1 includes how many ints we read on array1 (a1)
	li $t2, 0	#t2 includes how many ints we read on array2 (a2)
	add $a1, $a1, 36
	add $a2, $a2, 36

loopB:
	lw $t3, ($a1)
	lw $t4, ($a2)
	blt $t3, $t4, firstlow
	blt $t4, $t3, secondlow
	beq $t3, $t4, equals
firstlow:
	add $t2, $t2, 1
	beq $t2, 10, exit
	sub $a2, $a2, 4
	b	loopB
secondlow:
	add $t1, $t1, 1
	beq $t1, 10, exit
	sub $a1, $a1, 4
	b	loopB
equals:
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 11
	li $a0, ' '
	syscall

	add $t2, $t2, 1
	beq $t2, 10, exit
	sub $a2, $a2, 4
	b	loopB
	add $t1, $t1, 1
	beq $t1, 10, exit
	sub $a1, $a1, 4
	b	loopB
exit:
	jr $ra