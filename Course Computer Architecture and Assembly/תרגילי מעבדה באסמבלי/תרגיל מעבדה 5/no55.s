# Title: lab5       	 Filename:
# Author:      ID:    	  Date:
# Description: String and ASCII games :)))))))))))))))
# Input: 
# Output:
################# Data segment #####################
.data
buf:    .space    19
str:	.asciiz "Please enter a string\n"
msg1:   .asciiz "\n The swap string is:\n"
msg2:   .asciiz "\n The reverse string is:\n"
msg3:   .asciiz "\n The number of <a> in the string is: " 
msg4:   .asciiz "\n The number of <ab> in the string is: "         
msg5:   .asciiz "\n The number of <abc> in the string is: "
     
msg6: .asciiz "\nThe string you entred is:\n"

CRLF: .asciiz "\n"

.macro printStr(%msg)
la $a0,%msg
li $v0,4
syscall
.end_macro

.macro printInt
li $v0,1
syscall
.end_macro

.macro space
la $a0,CRLF
li $v0,4
syscall
.end_macro

################# Code segment #####################
.text
.globl main
main:	# main program entry
		
	getString:
	li $v0,4
	la $a0,str     #"please enter a string"
	syscall

##########################################
# get string from the user (syscall 8)

#NOTICE : buffer allocation is 19 bytes but the ... 
#automatically allocates 18 bytes for the string + null terminator

##########################################
	li $a1,19 #string size + null terminator
	la $a0,buf
	li $v0,8
	syscall
	
																		
																																																									
################################################
#1) Swap from big --> small , small --> big

#################################################

	printStr(msg1)#MACRO
			
	li $t1,0
	li $v0,11 # load once !
	
	loop:		
	lb $a0,buf($t1)#use label as array base allows you to set $a0 to the wanted print in syscall!					
							
        #range terms :  
        bgt $a0,'z',dont_swap
        blt $a0,'A',dont_swap
        ble $a0,'Z',swap
	bge $a0,'a',swap
	
	swap:
        xori $a0,$a0,0x20

	dont_swap:#just print !
        syscall

        addi $t1,$t1,1 # increment index by one	
	bne $a0,'\0',loop # loop the string until null-terminator
	
	
################################################
#2) print the string reverse 
#################################################
	
	printStr(msg2)#MACRO
	#space #MACRO
	li $v0,11

	printBack:
	add $t1,$t1,-1#we have it from last time !!!!
	lb $a0,buf($t1) # print from the end
	syscall 
	
	bnez $t1,printBack
	
################################################
#3) count the number of <a> in the string 
#################################################	
	
	#possible to do at once!!
	li $t0,0
	
	# $t1 - "a" ctr
	# $t2 - "ab" ctr
	# $t3 - "abc" ctr
	
	loopOverStr:
	lb $a0,buf($t0)
	
	askIf_A:
	bne $a0,'a',stepOver_B_C
	addiu $t1,$t1,1
	addiu $t0,$t0,1
	lb $a0,buf($t0)
	
	bne $a0,'b',askIf_A
	addiu $t2,$t2,1
	addiu $t0,$t0,1
	lb $a0,buf($t0)
	
	bne $a0,'c',askIf_A
	addiu $t3,$t3,1

	stepOver_B_C:
	addiu $t0,$t0,1
	bnez $a0,loopOverStr
	
	
		
        			
	printStr(msg3)#MACRO			
	add $a0,$t1,$zero
	printInt
	
	printStr(msg4)#MACRO
        add $a0,$t2,$zero
	printInt
        
        printStr(msg5)#MACRO		
        add $a0,$t3,$zero
	printInt					
				
################################################
#4) count the number of <ab> in the string 
#################################################	
	
	
			
################################################
#5) count the number of <abc> in the string 
#################################################	
	
	
		
exit:
	li $v0,10
	syscall


