# Computer Architecture
#q2       	
# Input: 1)a string (max 40 chars)in buf  
#        2)a number x between 1-9
# 
# Output: 1)The string endcoded every even ASCII value substracted by x
#	   and every odd ASCII value added by x 
#	the endcoded ASCII values are stored in buf1 in the same order as in buf
#        2)print the new string  (buf1)	
# 
# Example
#Please enter a string(max 40 chars)
# abcdefghijklmnop
# Please enter a number (1-9): 1
# The encoded string is:
# badcfehgjilknmpo   
################# Data segment #####################
.data
buf:    .space  41 # 41 bytes including null terminator
buf1:    .space   41
			
msg1:   .asciiz "\n Please enter a string(max 40 chars)\n"
msg2:   .asciiz " \n Please enter a number (1-9):\n"
msg3:	.asciiz " \n The endoded string is:\n"

#CRLF : .byte '\n'

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
   	#la $a0,msg1	# Please enter a string(max 40 chars)
	#li $v0,4		# system call to print
	#syscall		# out a string 

        #get string from the user syscall 8
	li  $v0,8
	la  $a0,buf #the start address of the string
	li  $a1,41 #max chars
	syscall
	
	#la $a0,msg2	# Please enter a number (1-9):
	#li $v0,4	# system call to print
	#syscall		# out a string
 	   	   	   	   	   
#answer	
 again:
	printMsg(msg2)# MACRO
	li $v0,5
	syscall

ble $v0,0,again   # $v0 <= 0
bge $v0,10,again  # $v0 >= 10

move $t0,$v0 # save the integer from user input

la $t2,buf #pointer to str
la $a0,buf1 #pointer to str

loop1:#create buf1 loop

li $s1,1#mask
sll $s1,$s1,31#may be save shift com. by loading 0x80000000

lb $t1,0($t2)#get a char from buf
beq $t1,'\0',exitLoop # end of buf

sll $t1,$t1,31
and $s1,$t1,$s1
lb $t1,0($t2)
srl $s1,$s1,31 #sarah :)

bne $s1,0,add_x # if the number is odd branch

#sub_x
sub $t1,$t1,$t0
sb $t1,0($a0)
addiu $a0,$a0,1
j continue

add_x:	  
add $t1,$t1,$t0
sb $t1,0($a0)
addiu $a0,$a0,1
	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   
continue:
addiu $t2,$t2,1	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   
andi $s1,$t1,0	 
  	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   		   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   
bne $t1,'\0',loop1	   

# abcdefghijklmnop ,1 , badcfehgjilknmpo

exitLoop:	# we can put it also in exit label !   

        la $a0,buf1	
	li $v0,4	
	syscall	
   
# end of program
exit:	
	li $v0,10
	syscall
	
