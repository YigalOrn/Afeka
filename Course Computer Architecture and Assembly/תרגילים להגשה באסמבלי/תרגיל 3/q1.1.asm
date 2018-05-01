#q1.s
################# Data segment #####################
.data
msg1: .ASCIIZ "\nPlease Enter a 32  bit signed number:  "
msg2: .ASCIIZ "\nThe negation of the number in 32 bits is:     " # :) using NOR
msg3: .ASCIIZ "\nDecimal result:  "
msg4: .ASCIIZ "\nBinary result:\n"

CRLF : .byte '\n'

.macro printMsg(%msg)
la $a0,%msg
li $v0,4
syscall
.end_macro

################# Code segment #####################
.text
.globl main
	
main:	# main program entry

	printMsg(msg1)# MACRO
	li $v0,5 #get a number from the user, $vo contains the input
	syscall
		
	#copy the value in $v0	
	move $t0,$v0
	nor $t1,$t0,$zero # NOR(a+0)= NOT(a)
	
	####################
	#print negated number
	printMsg(msg2)# MACRO	
	move $a0,$t1
	li $v0,1
	syscall
	
	li $v0,11
	lb,$a0,CRLF
	syscall
	
	move $a1,$t1
	jal  binary32BitPrint #procedure
	####################
	
	addiu $t1,$t1,1
	
	####################
	#print result
	printMsg(msg3) # WARNING : macro	
	
	move $a0,$t1
	li $v0,1
	syscall
	
	li $v0,11
	lb,$a0,CRLF
	syscall
	
	printMsg(msg4) # MACRO	
	move $a1,$t1
	jal  binary32BitPrint #procedure
	####################

		
exit:	
	li $v0, 10	# Exit program
	syscall 
  
 ######################################
 #prodecure - binary32BitPrint
 ######################################
 
 
        # $t9 - bit counter , initial value set to 31
	# decimal value 48   00110000 - '0' , 00110001 - '1'
	# $t8 - mask 
	# $t1 - the result 
	
	# Algorithm #
	#1) create a mask and use logical AND operator to isolate each bit starting from left!
	#2) using logical OR add to the bits 5 and 6 a-1 to create ASCII char '1' or '0'
	#3) print the result in AACII that is as a char
 
 
 binary32BitPrint:
 
 addi $sp,$sp,-8
 sw $ra,4($sp) #return address
 sw $a1,0($sp) #argument , reg that holds the integer value
 
        andi $t9,$t9,0#zeroing
        andi $t8,$t8,0#zeroing
  
        addi $t9,$t9,31 #bit counter
	addi $t8,$t8,1 #mask
	
	binaryPrint:
	#masking
	sllv $t8,$t8,$t9
	and $a1,$t8,$t1
	srlv $a1,$a1,$t9 # Logic shifts not Arithmetic shift - no sign duplication!
	#reset mask
	andi $t8,$t8,0
	addi $t8,$t8,1
	#reduce index counter
	subiu $t9,$t9,1
	#create the binary ascii char '0' or '1' respectively
	ori $a1,$a1,48
	#print one bit as a char
	move $a0,$a1
	li $v0,11
	syscall
	#reset temp bit to print reg
	lw $a1,0($sp)
	
	bgt $t9,-1,binaryPrint # $t9 > -1 ? continue:stop , NOTICE:  0 >= 0  

        addi $sp,$sp,8 # free stack memory allocation
        jr $ra # return address + 4 , next instruction after the call

 ######################################
 #prodecure - binary32BitPrint
 ######################################
 
