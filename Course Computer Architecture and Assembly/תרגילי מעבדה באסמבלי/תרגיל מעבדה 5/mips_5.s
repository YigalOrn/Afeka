# Title: lab5       	 Filename:
# Author:      ID:    	  Date:
# Description: String and ASCII games :)))))))))))))))
# Input: 
# Output:
################# Data segment #####################
.data
buf:    .space    19
str:	.asciiz "Please enter a string\n"
msg1:   .asciiz "\nThe swap string is:\n"
msg2:   .asciiz "\nThe reverse string is:\n"
msg3:   .asciiz "\nThe number of <a> in the string is: " 
msg4:   .asciiz "\nThe number of <ab> in the string is: "         
msg5:   .asciiz "\nThe number of <abc> in the string is: "
     
msg6: .asciiz "\nThe string you entred is:\n"

small_z: .byte 'z'
cap_z: .byte 'Z'
CRLF: .byte '\n' #  '\n' + 0x20   ---->   '*'
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

#NOTICE : buffer allocation is 19 bytes but the system... 
#automatically allocates 18 bytes for the string + null terminator

##########################################
	li $a1,19 #string length + null terminator
	la $a0,buf
	li $v0,8
	syscall
	
##########################################
# print the input from user
##########################################	
	
	#move $t0,$a0 # save the string pointer							
	la $a0,msg6
	li $v0,4
	syscall
	
	#move $a0,$t0																			
	la $a0,buf
	li $v0,4
	syscall																			
	
																																																									
################################################
#1) Swap from big --> small , small --> big

#assumption the string contains letters only!!

#################################################
	
	#print result
	li $v0,4
	la $a0,msg1     #"The swap string is:"
	syscall
							
	# $t1 - temp char
	# $t2 - base address of buf
	# $s1 - offset/index
	# $t3 - 'z' +1
	# $t4 - 'Z' +1
	# $t5 - CRLF
	
         #check if lingth = 0
         la $t2,buf
	 lb $t1,0($t2)
	 beq $t1,'\0',getString
	
	#preper lims for conditions
	lb $t3,small_z
	addiu $t3,$t3,1 
	lb $t4,cap_z
	addiu $t4,$t4,1 
	lb $t5,CRLF
	
	
	swap:
	
	beq $t1,$t5,swapContinue #null terminator
	
	blt $t1,$t4,moreToSmall #    $t1 <= Z
	j checkMore
	moreToSmall:
	bge $t1,'A',swapToSmall
	j printAsIs
	
	checkMore:
	blt $t1,$t3,moreToCap #    $t1 <= z
	#j printAsIs
	moreToCap:
	bge $t1,'a',swapToCapital
	j printAsIs
	
	
	swapToSmall:
	addiu $t1,$t1,0x20
	#sb $t1,0($t2)
	move $a0,$t1									
      	li $v0,11
	syscall
	j swapContinue
	
	swapToCapital:
	 bne $t1,'a',continue# count 'a' letters
         addi $v1,$v1,1 
         continue:
	
	subiu $t1,$t1,0x20
	#sb $t1,0($t2)
	move $a0,$t1									
      	li $v0,11
	syscall	
	j swapContinue
	
	printAsIs:
	move $a0,$t1									
      	li $v0,11
	syscall	
	
	swapContinue:
	#addi $s1,$s1,1
	# increment the base register (address) by ine byte !
	#jumping in bytes and not words !! , Little Endian, mark ASCII in data segment
	addiu  $t2,$t2,1 
	lb $t1,0($t2)
	bne $t1,'\0',swap
	
	

################################################
#2) print the string reverse 
#################################################
	li $v0,4
	la $a0,msg2    
	syscall
	
	la $a0,buf
	#call a recursive procedure
	jal printBackwards
	
	
	
################################################
#3) count the number of <a> in the string 
#################################################	

      	la $a0,msg3									
      	li $v0,4
	syscall	
      						
      																
      	move $a0,$v1										
      	li $v0,1
	syscall															
      																										
################################################
#4) count the number of <ab> in the string 
#################################################	
	
        la $a0,msg4									
      	li $v0,4
	syscall	
      		
        la $a0,buf
	#call a procedure
	jal count_ab_sequence 
        
        move $a0,$v1									
      	li $v0,1
	syscall	
			
################################################
#5) count the number of <abc> in the string 
#################################################	
 		

	la $a0,msg5									
      	li $v0,4
	syscall	
      		
        la $a0,buf
	#call a procedure
	jal count_abc_sequence 
        
        move $a0,$v1									
      	li $v0,1
	syscall	
		
				
						
exit:
	li $v0,10
	syscall
################################################
#procedure count_ab_sequence
#################################################

count_ab_sequence :

addi $sp,$sp,-4
sw $ra,0($sp) #save return address

andi $v1,$v1,0 # count appearances
andi $s0,$s0,0 #flag
li $t8,2 #condition to flag

strLoop:

lb $t1,0($a0)
beq $t1,'\0',return

bne $t1,'a',goto
addiu $s0,$s0,1
addiu $a0,$a0,1
lb $t1,0($a0)
beq $t1,'\0',return

bne $t1,'b',goto11
addiu $s0,$s0,1

goto:

bne $t8,$s0,continue1
addiu $v1,$v1,1
continue1:

addiu $a0,$a0,1
goto11:
andi $s0,$s0,0 #flag

bne $t1,'\0',strLoop #

return:
addi $sp,$sp,4
jr $ra

################################################
#procedure count_ab_sequence
#################################################

################################################
#procedure count_abc_sequence
#################################################

count_abc_sequence :

addi $sp,$sp,-4
sw $ra,0($sp) #save return address

andi $v1,$v1,0 # count appearances
andi $s0,$s0,0 #flag
li $t8,3 #condition to flag

strLoop2:

lb $t1,0($a0)
beq $t1,'\0',return2

#***********#
bne $t1,'a',goto2
addiu $s0,$s0,1
#***********#


addiu $a0,$a0,1
lb $t1,0($a0)
beq $t1,'\0',return2

#***********#
bne $t1,'b',goto3
addiu $s0,$s0,1
#***********#

addiu $a0,$a0,1
lb $t1,0($a0)
beq $t1,'\0',return2

#***********#
bne $t1,'c',goto3
addiu $s0,$s0,1
#***********#


goto2:

bne $t8,$s0,continue2
addiu $v1,$v1,1
continue2:

addiu $a0,$a0,1
goto3:
andi $s0,$s0,0 #flag

bne $t1,'\0',strLoop2 #

return2:
addi $sp,$sp,4
jr $ra

################################################
#procedure count_abc_sequence
#################################################

#################################################
#procedure printBackwards


#function(calle)
#1)put parameters in place where prudecure can access them.
#2)transfer control to procedure.
#3)acquire the storage resources needed for the procedure,, using the stack data struct.
#4)perfom the desired task
#5)put the result where the caller can access it
#6)return control to the calling instruction + 4




#"Contrariwise,continued Tweedledee, if it was so, it might be;
#and if it were so, it would be; but as it isnt, it aint.
#Thats logic."
	
#################################################
printBackwards:

#allocate space on function stack
addi $sp,$sp,-8
sw $ra,4($sp) #save return address
lb $t9,0($a0)
sw $t9,0($sp) #save char in this level


bne $t9,'\0',L1 #recursive stoping condition

addi $sp,$sp,8 #free allocated memory on  func stack
jr $ra #return to caller

L1:
#increment str pointer to next char
#Lets assume we can solve the problem for a smaller input
addiu $a0,$a0,1
jal printBackwards
  
  #return - execute next instruction in each level
  #restore current level func-variables
  lw $ra,4($sp)
  lw $t9,0($sp)
  #preper for printing
  move $a0,$t9
  
  #free allocated memory on  func stack
  addi $sp,$sp,8
  
        li $v0,11
	syscall
  
  jr $ra #return to caller


#################################################
#printBackwards
#################################################









