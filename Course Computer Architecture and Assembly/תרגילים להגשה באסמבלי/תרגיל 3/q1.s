#q1.s
################# Data segment #####################
.data
msg1: .ASCIIZ "\nPlease Enter a 32  bit signed number:  "
msg2: .ASCIIZ "\nThe negation of the number in 32 bits is:  " # :) using NOR
msg3: .ASCIIZ "\nDecimal result:  "
msg4: .ASCIIZ "\nBinary result:\n"

CRLF : .byte '\n'

################# Code segment #####################
.text
.globl main
	
main:	# main program entry

	
	li $v0,4
	la,$a0,msg1
	syscall 	
	li $v0,5 #get a number from the user, $vo contains the input
	syscall
		
	#copy the value in $v0	
	move $t0,$v0
	nor $t1,$t0,$zero # nor(a+0)= not(a)
	
	#print negated number
	li $v0,4
	la,$a0,msg2
	syscall
	
	move $a0,$t1
	li $v0,1
	syscall
	#print negated number
	
	addiu $t1,$t1,1
	
	#print result
	li $v0,4
	la,$a0,msg3
	syscall
	move $a0,$t1
	li $v0,1
	syscall
	li $v0,11
	lb,$a0,CRLF
	syscall
	#print result
	
	# $t9 - bit counter , initial value set to 31
	# decimal value 48   00110000 - '0' , 00110001 - '1'
	# $t8 - mask 
	# $t1 - the result 
	
	# Algorithm #
	#1) create a mask and use logical AND operator to isolate each most left bit
	#2) using logical OR add to the bits 5 and 6 a 1
	#3) print the result in ascii that is as a char
	
	
	li $v0,4
	la,$a0,msg4
	syscall
	
	addi $t9,$t9,31
	addi $t8,$t8,1
	
	binaryPrint:
	#masking
	sllv $t8,$t8,$t9
	and $a0,$t8,$t1
	srlv $a0,$a0,$t9
	#reset mask
	andi $t8,$t8,0
	addi $t8,$t8,1
	#reduce index counter
	subiu $t9,$t9,1
	#create the binary ascii char '0' or '1' respectively
	ori $a0,$a0,48
	#print one bit as a char
	li $v0,11
	syscall
	#reset temp bit to print reg
	andi $a0,$a0,0
	
	bgt $t9,-1,binaryPrint # $t9 > -1 ? continue:stop , NOTICE:  0 > -1  

		
exit:	
	li $v0, 10	# Exit program
	syscall 
 