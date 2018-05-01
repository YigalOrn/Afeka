# Computer Architecture
#Q3        	
# Input: 1)a string (max 40 chars)in buf  
#        2)a char (ASCII)
# 
# Output: 1)The string is copied to buf1 replace the char with    '*'
#    if there are more than five replacements the char to replace with is '@' 
#
#	2)print the new string	
#
## Example:
#
#Please enter a string(max 40 chars)
#    aaabbbaaabbbaaabbb
# Please enter a char:   b 
# The string with the char replaced is:
#    aaa***aaa**@aaa@@@
################# Data segment #####################
.data
buf:    .space  41
buf1:    .space   41
			
msg1:   .asciiz "\n Please enter a string(max 40 chars)\n"
msg2:   .asciiz " \n Please enter a char:   "
msg3:	.asciiz " \n The string with the char replaced is:\n"

ch: .byte '*','@'
################# Code segment #####################
.text
.globl main
main:	# main program entry

   	la $a0,msg1	# Please enter a string(max 40 chars)
	li $v0,4	# system call to print
	syscall		# out a string 

        # get string from the user syscall 8
	li  $v0,8
	la  $a0,buf #the start address of the string
	li  $a1,41  #max chars
	syscall
	
	la $a0,msg2	# Please enter a char
	li $v0,4	# system call to print
	syscall		# out a string
 
	li $v0,12
	syscall

#answer

la $t0,buf #pointer to str		
la $t1,buf1 #pointer to str	
andi $s0,$s0,0#counter for char appearances in given str

la $t3,ch# pointer to special chars array
lb $t8,0($t3)# '*'
lb $t9,1($t3)# '@'
								
loop:

lb $t2,0($t0) #get one char from buf array
#beq $t2,'\0',result # depends on the given char ! , somthing funny happens

bne $t2,$v0,continue #($t2 == $v0) ? 1:0		 		

blt $s0,5,putAsterisk # ($s0 < 5) ? 1:0

#putKroohit
sb $t9,0($t1)
addiu $t1,$t1,1	
j continue1

putAsterisk:
addiu $s0,$s0,1 #increment counter , here it saves the burden of cal. if $s0 >= 5 .
sb $t8,0($t1)
addiu $t1,$t1,1	
j continue1

continue:	
sb $t2,0($t1)
addiu $t1,$t1,1	
continue1:
addiu $t0,$t0,1	

bne $t2,'\0',loop	


#result:
li $v0,4 # system call to print	
la $a0,msg3
syscall	
la $a0,buf1	
syscall	
	
			
# end of program
exit:	
	li $v0,10
	syscall
	
