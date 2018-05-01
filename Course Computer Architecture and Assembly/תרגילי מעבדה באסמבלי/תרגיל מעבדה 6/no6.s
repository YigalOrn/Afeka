# Title: lab 6	Filename:
# Author:       	Date:
# Description:
# Input: 2 arrays of 10 word sign numbers in acending order
# Output:The number that exists in both arrays in decending order
################# Data segment #####################
.data
array1:  .space 40 #array of 10 WORDS!  --> 1 word = 4 bytes
array2:  .space 40 #array of 10 words
msg1: .asciiz "Please enter 10 sign numbers in ascending order\n"
msg2: .asciiz "\n The number that exists in both arrays in decending order are :\n"
#msg3: .asciiz "\n wrong input please enter again!\n"


reEnterMsg: .asciiz "\n wrong input please enter again!\n"
getNumMsg: .asciiz "Please enter an int:\n"
  
hyphen : .byte '>'

.macro printHyphen
lb $a0,hyphen
li $v0,11
syscall
.end_macro


.macro printMsg(%msg)
la $a0,%msg
li $v0,4
syscall
.end_macro


.macro printInt
li $v0,1
syscall
.end_macro

################# Code segment #####################
.text
.globl main
main:	# main program entry

	
	        la $a0,msg1	# Please enter 10 sign numbers in ascending order
		li $v0,4	# system call to print
		syscall		# out a string 		

		la $a1,array1
		jal  get_array

		la $a0,msg1	# Please enter 10 sign numbers in ascending order
		li $v0,4	# system call to print
		syscall		# out a string 		

		la $a1,array2
		jal  get_array
	
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
# in ascending order	         		   # 	
####################################################	 

#function(calle)
#1)put parameters in place where prudecure can access them.
#2)transfer control to procedure.
#3)acquire the storage resources needed for the procedure,, using the stack data struct.
#4)perfom the desired task
#5)put the result where the caller can access it
#6)return control to the calling instruction + 4	


#Ask Ram how to exploit the advantage shown in page 109 in the bottom???

 #$t9  - array length counter
 #$t8 - last value entred by user   
 get_array:

 addi $sp,$sp,-4 #allocate space on prodecure stack
 sw $ra,0($sp) #save return address 
 and $t9,$t9,$zero #zeroing

#First input
printMsg(getNumMsg)# MACRO
li $v0,5
syscall
move $t8,$v0 #save last entred value for future comparison
sw $v0,0($a1)
addiu $a1,$a1,4

arrayLoop: 

checkSequenceLoop:
printMsg(getNumMsg)# MACRO
li $v0,5
syscall
blt $v0,$t8,printErrorMsg # eventually goes to Label =  checkSequenceLoop 

move $t8,$v0 #save last entred value for future comparison
sw $v0,0($a1)
addiu $a1,$a1,4
addiu $t9,$t9,1

bne $t9,9,arrayLoop # still need to loop at 8th time

addi $sp,$sp,4 #free allocated memory on  func stack
jr $ra #return to caller

printErrorMsg:
printMsg(reEnterMsg)# MACRO
j checkSequenceLoop 


###################################################################
#Procedure find_eq						  # 		 
#input : $a1, $a2 -->Address of two arrays of 10 sign numbers     # 
# in ascending order				                  # 
#output:The numbers that exists in both arrays in decending order #
###################################################################


# $t1 - array1 value , may be use $a0 for one of them!
# $t2 - array2 value

# $t8 - array1 counter
# $t9 - array2 counter

find_eq:

addi $sp,$sp,-4 #allocate space on prodecure stack
sw $ra,0($sp) #save return address 

and $t8,$t8,$zero #zeroing
and $t9,$t9,$zero

addiu $a1,$a1,36 # move the pointer to the last int because we have a rising sequence
addiu $a2,$a2,36

lw $t1,0($a1)
lw $t2,0($a2)

loop:

beq $t8,10,onlyArray2Left
beq $t9,10,onlyArray1Left

ble $t1,$t2,array2BTarray1
#else continue

###
#array1BTarray2: # BT = bigger then
addiu $a1,$a1,-4
addiu $t8,$t8,1

move $a0,$t1
printInt# MACRO
printHyphen# MACRO

lw $t1,0($a1)
j loop
###

###
array2BTarray1:
addiu $a2,$a2,-4
addiu $t9,$t9,1

move $a0,$t2
printInt# MACRO
printHyphen# MACRO

lw $t2,0($a2)
j loop
###

onlyArray2Left:

move $a0,$t2
printInt# MACRO
printHyphen# MACRO

addiu $a2,$a2,-4
lw $t2,0($a2)
addiu $t9,$t9,1


bne $t9,10,onlyArray2Left
j return

onlyArray1Left:

move $a0,$t1
printInt# MACRO
printHyphen# MACRO

addiu $a1,$a1,-4
lw $t1,0($a1)
addiu $t8,$t8,1


bne $t8,10,onlyArray1Left

return:
addi $sp,$sp,4 #free allocated memory on  func stack
jr $ra #return to caller











