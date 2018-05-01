# Title: Exercise 6	Filename: project_6.asm
# Author: Ornes Yigal 303893416       	Date:
# Description: mini project
################# Data segment #####################
.data
# 4x4 matrix <<--------------------------
matrix: .byte 2,7,34,68,56,89,156,122,135,0,33,122,122,66,18,255
ROWS: .word 4
COLS: .word 4
# Tesing other options
#---------------------------------------------
#matrix: .byte 2,11,34,1,156,89,1,122,135,0,1,122,122,1,18,255
#matrix: .byte 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
#matrix: .byte 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#matrix: .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#matrix: .byte 0,-1,-76,76,125,-125,0,0,1,-1,255,-128,-3,3,0,0
#matrix: .byte -128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,128,128,128,128
#matrix: .byte -128,-128,128,-128,-128,128,-128,-128,-128,128,-128,-128,128,128-128,128
#---------------------------------------------
# Jump address table (look up table)
#---------------------------------------------
#Description: works the same as a pointer to an array of pointers ! , each entry 32 bit a word
#1.loading an address from the lookUpTableArr is loading a pointer to a specific address
#2.using that pointer to load the concrete wanted address
jumpTable: .word menu,print,print,print,change_number,negate,swap,find_max,find_max,exit # NOTICE: zero label is menu !
#---------------------------------------------
# Strings
#---------------------------------------------
menuStr: .asciiz "\nThe options are:\n1.Print matrix unsigned\n2.Print matrix sign\n3.Print matrix Octa(unsign)\n4.Change a number in the matrix\n5.Negate a number in the matrix\n6.Swap numbers in the matrix\n7.Find the max sum of arow(unsign)\n8.Find the max sum of arow(sign)\n9.END\n" 
msg0: .asciiz "\nPlease enter your choice between 1-9:\n"
msg1: .asciiz "\nPlease enter row num:\n"
msg2: .asciiz "\nPlease enter col num:\n"
msg3: .asciiz "\nPlease enter the new num:\n"
wrongInputMatrix: .asciiz "\nIndex out of bound,try again:\n"
wrongInputByte: .asciiz "\nThe new value takes more then byte!\n"
msg9: .asciiz "\nThe program will terminate now...\n "
#---------------------------------------------
# Debug strings
#---------------------------------------------
in_print: .asciiz "\nin_print\n"
out_print: .asciiz "\nout_print\n"
in_print_num: .asciiz "\nin_print_num\n"
out_print_num: .asciiz "\nout_print_num\n"
in_change_num: .asciiz "\nin_change_num\n"
out_change_num: .asciiz "\nout_change_num\n"
in_negate: .asciiz "\nin_negate\n"
out_negate: .asciiz "\nout_negate\n"
in_swap: .asciiz "\nin_swap\n"
out_swap: .asciiz "\nout_swap\n"
in_find_max: .asciiz "\nin_find_max\n"
out_find_max: .asciiz "\nout_find_max\n"
here: .asciiz "\nHERE-HERE\n "
#---------------------------------------------
# MACROS
#---------------------------------------------
CRLF : .byte '\n'
.macro printCRLF
move $s0,$a0
lb $a0,CRLF
li $v0,11
syscall
move $a0,$s0
.end_macro

tab: .byte '\t'
.macro printTab
move $s0,$a0
lb $a0,tab
li $v0,11
syscall
move $a0,$s0
.end_macro

.macro printMsg(%msg)
move $s0,$a0
la $a0,%msg
li $v0,4
syscall
move $a0,$s0
.end_macro

.macro DEBUG(%msg)
move $s0,$a0
la $a0,%msg
li $v0,4
syscall
move $a0,$s0
.end_macro

.macro printInt
li $v0,1
syscall
.end_macro

.macro printChar
li $v0,11
syscall
.end_macro
#---------------------------------------------
################# Code segment #####################
.text
.globl main # to call from other files
main:	# main program entry
	  
menu:	  
   printMsg(menuStr)# MACRO
   printMsg(msg0)# MACRO
   li $v0,12 # get the choice value as char to avoid bugs
   syscall
   blt $v0,0x31,menu  # check lower limit
   bgt $v0,0x39,menu  # check upper limit
   subiu $t1,$v0,0x30 # $t1 contains the value correctly
   printCRLF
   la $a0,matrix # FIRST procedure parameter
   add $a1,$t1,$zero # SECOND procedure parameter
   lw $a2,ROWS # THIRD procedure parameter
   lw $a3,COLS # FOURTH procedure parameter
   sll $t2,$t1,2 # shift left by n bits = multiply by 2^n , for word address alignment 
   la $t3,jumpTable # load base address
   addu $t4,$t3,$t2 # increment to the wanted index(pointer) in jumpTable
   lw $t5,0($t4)  
   jalr $t5
   j menu # return to menu     
####################################################
#Procedure:  print                                 #
# input : $a0-->matrix address in memory	   #  
#         $a1-->user's choice value      	   #  
#         $a2-->matrix rows              	   #  
#         $a3-->matrix cols              	   #  
# Description: prints the matrix values in n*n     #
# form in unsinged decimal values, byte size	   # 	
# using a help procedure                 	   # 	
####################################################	      
print:
DEBUG(in_print)# MACRO
addi $sp,$sp,-4 # allocate space on prucedure stack
sw $ra,0($sp)# save the return address
#--------------------
# $t1 - upper lim
# $t2 - loop counter
# $t3 - remainder
# $t4 - how many nums in a row counter
# $a2 - after serving as ROWS , serves as a current (byte size) num
#--------------------
 mul $t1,$a2,$a3 # $t1 = ROWS*COLS
 and $t2,$t2,$zero
loop1:
printTab# MACRO
lbu  $a2,0($a0) # Or addi,  + 256 = 0100000000
jal print_num
move $t4,$t2
addi $t4,$t4,1
div $t4,$a3
mfhi $t3
bnez $t3,continue1
printCRLF# MACRO
continue1:
addiu $t2,$t2,1
addiu $a0,$a0,1
bne $t2,$t1,loop1
#--------------------
lw $ra,0($sp)
addi $sp,$sp,4 # free allocated space
DEBUG(out_print)# MACRO
jr $ra # return from current procedure
####################################################
#Procedure:  change_number                         #
# input : $a0-->matrix address in memory           #  
# Description:                                     #
# using a help procedure                 	   # 	
####################################################	
change_number:
DEBUG(in_change_num)# MACRO
addi $sp,$sp,-8
sw $ra,0($sp)
sw $a0,4($sp)
jal get_position
lw $a0,4($sp)
printMsg(msg3)# MACRO
getNewNum:
li $v0,5
syscall
bgt $v0,255,error3
blt $v0,-128,error3
add $a0,$v1,$a0
sb $v0,0($a0)
j return_from_change_num
error3:
printMsg(wrongInputMatrix)# MACRO
j getNewNum
return_from_change_num:
lw $ra,0($sp)
addi $sp,$sp,8
DEBUG(out_change_num)# MACRO
jr $ra
####################################################
#Procedure:  negate                                #
# input : $a0-->matrix address in memory           # 
# Description:                                     #
# using a help procedure                 	   # 	
####################################################	
negate:
DEBUG(in_negate)# MACRO
addi $sp,$sp,-4
sw $ra,0($sp)
jal get_position
add $a0,$a0,$v1
lb $t1,0($a0)
abs $t2,$t1
beq $t2,128,return_from_negate # have no reflecetion
nor $t1,$t1,$zero # breaks to OR + NOT
addi $t1,$t1,257 # 1 for NOT , 256 for correction
sb $t1,0($a0)
return_from_negate:
lw $ra,0($sp)
addi $sp,$sp,4
DEBUG(out_negate)# MACRO
jr $ra
####################################################
#Procedure:  swap                                  #
# input : $a0-->matrix address in memory           #  
# Description: swaps two elements in the matrix    #
# using a help procedure                 	   # 		
####################################################	
swap:
DEBUG(in_swap)# MACRO
addi $sp,$sp,-8
sw $ra,0($sp)
sw $a0,4($sp)
#NOTICE : there is an implemantion of bubble swap in the book
# $t3 - first index --> first byte value
# $t4 - second index --> second byte value
# $t1 - first byte value
# $t2 - second byte value

jal get_position
add $t3,$v1,$zero
jal get_position
add $t4,$v1,$zero

add $a0,$a0,$t3
lb $t1,0($a0)
lw $a0,4($sp)
add $a0,$a0,$t4
lb $t2,0($a0)

sb $t1,0($a0)
lw $a0,4($sp)
add $a0,$a0,$t3
sb $t2,0($a0)

lw $ra,0($sp)
addi $sp,$sp,8
DEBUG(out_swap)# MACRO
jr $ra
####################################################
#Procedure:  find_max                              #
# input : $a0-->matrix address in memory	   #  
#         $a1-->user's choice value      	   #  
#         $a2-->matrix rows              	   #  
#         $a3-->matrix cols              	   #  
# Description:                                     #              	         		   	
####################################################	
find_max:
DEBUG(in_find_max)
addi $sp,$sp,-8
sw $ra,0($sp)
sw $a0,4($sp)

# $t1 - row ctr
# $t2 - col ctr
# $t3 - sum
# $t4 - matrix offset
# $t5 - max sum
# $t6 - index in array (not matrix)
# $t7 - max sum row index
# some local parameters are used twice differently then from mentioned above !
andi $t1,$t1,0
andi $t2,$t2,0
andi $t3,$t3,0

beq $a1,7,unsginedSum
beq $a1,8,signedSum

unsginedSum:

rowLoop1:
      
      sll $t4,$t1,2
      add $t6,$a0,$zero
      add $t6,$t6,$t4
    
      colLoop1:

      lbu $a1,0($t6) # $a1 - current byte size value to sum
      addi $t6,$t6,1
      add $t3,$t3,$a1
      addi $t2,$t2,1  
      bne $t2,$a3,colLoop1
   
bnez $t1,continue2 # first time setup
add $t5,$t3,$zero
add $t7,$t1,$zero
continue2:
bleu $t3,$t5,continue3
add $t5,$t3,$zero
add $t7,$t1,$zero
continue3:                       
lw $a0,4($sp)
andi $t3,$t3,0
andi $t2,$t2,0
addi $t1,$t1,1            
bne $t1,$a2,rowLoop1

li $a1,1

j printRow

signedSum:

rowLoop11:
      
      sll $t4,$t1,2
      add $t6,$a0,$zero
      add $t6,$t6,$t4
    
      colLoop11:

      lb $a1,0($t6) # $a1 - current byte size value to sum
      addi $t6,$t6,1
      add $t3,$t3,$a1
      addi $t2,$t2,1  
      bne $t2,$a3,colLoop11
   
bnez $t1,continue22 # first time setup
add $t5,$t3,$zero
add $t7,$t1,$zero
continue22:
ble $t3,$t5,continue33
add $t5,$t3,$zero
add $t7,$t1,$zero
continue33:                       
lw $a0,4($sp)
andi $t3,$t3,0
andi $t2,$t2,0
addi $t1,$t1,1            
bne $t1,$a2,rowLoop11

li $a1,2

printRow:

move $a0,$t7
printInt # MACRO
printTab # MACRO

# $t7 - max sum row index , for print loop
#call to print_num , parameters of func: $a1 - choice , $a2 - value 
lw $a0,4($sp)
andi $t1,$t1,0
sll $t7,$t7,2
add $t7,$t7,$a0
printRowElements:
lbu $a2,0($t7)
jal print_num
printTab# MACRO
addi $t7,$t7,1
addi $t1,$t1,1
bne $t1,4,printRowElements

lw $ra,0($sp)
addi $sp,$sp,8
DEBUG(out_find_max)
jr $ra
#---------------------------------------------   	   	   
	   # Exit program 
	   exit:
	   printMsg(msg9)
	   li $v0, 10	
	   syscall
#---------------------------------------------   
####################################################
#Procedure:  print_num                             #
# input : $a2-->byte size num value	           #  
#         $a1-->user's choice value      	   #  
# Description: prints one byte num in the          #
# chosen format                    	           #
####################################################		
print_num:
addi $sp,$sp,-36 #allocate space
sw $a0,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
sw $t3,12($sp)
sw $t4,16($sp)
beq $a1,1,unsgined
beq $a1,2,signed
beq $a1,3,octa
#--------------------
unsgined:
# $t1 - loop counter , using that byte size num has max. 3 digits
# $t2 - imm.
# $t3 - remainder
# $t4 - stack base+offset
and $t1,$t1,$zero
move $t4,$sp
li $t2,10
loop2:
divu  $a2,$t2
mflo $a2
mfhi $t3
sw $t3,20($t4)
# we could sum the remainders after mul. in 10^n in one reg.
addi $t4,$t4,4
addi $t1,$t1,1
bne $t1,3,loop2
lw $a0,28($sp)
printInt# MACRO
lw $a0,24($sp)
printInt# MACRO
lw $a0,20($sp)
printInt# MACRO
j return_from_print_num
#--------------------
#(2's comp. , NOTICE : 1000000 has no reflection ! page 90)
signed:
# $t1 - loop counter , using that byte size num has max. 3 digits
# $t2 - imm.
# $t3 - remainder
# $t4 - stack base+offset
# $t5 - sign char
and $t1,$t1,$zero
move $t4,$sp
li $t2,10
srl  $t5,$a2,7
bne $t5,1,isPos
li $t5,'-'
sw $t5,32($sp)
nor $a2,$a2,$zero # breaks to OR + NOT
addi $a2,$a2,257 # 1 for NOT , 256 for correction
j loop3
isPos:
li $t5,'+'
sw $t5,32($sp)
loop3:
divu  $a2,$t2
mflo $a2
mfhi $t3
sw $t3,20($t4)
# we could sum the remainders after mul. in 10^n in one reg.
addi $t4,$t4,4
addi $t1,$t1,1
bne $t1,3,loop3
lw $a0,32($sp)
printChar# MACRO
lw $a0,28($sp)
printInt# MACRO
lw $a0,24($sp)
printInt# MACRO
lw $a0,20($sp)
printInt# MACRO
j return_from_print_num
#--------------------
octa:
# $t1 - loop counter , using that byte size num has max. 3 digits
# $t2 - imm.
# $t3 - remainder
# $t4 - stack base+offset
and $t1,$t1,$zero
move $t4,$sp
li $t2,8
loop4:
divu  $a2,$t2
mflo $a2
mfhi $t3
sw $t3,20($t4)
# we could sum the remainders after mul. in 10^n in one reg.
addi $t4,$t4,4
addi $t1,$t1,1
bne $t1,3,loop4
lw $a0,28($sp)
printInt# MACRO
lw $a0,24($sp)
printInt# MACRO
lw $a0,20($sp)
printInt# MACRO
#--------------------
return_from_print_num:
lw $a0,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
lw $t3,12($sp)
lw $t4,16($sp)
addi $sp,$sp,36
jr $ra
####################################################
#Procedure:  get_position                          #
# input : $a2 - ROWS                               #  
#         $a3 - COLS                               # 
# output : $v1 - index in array of bytes           #   
# Description: get the sequential index of a       #
# matrix member as it would be in an array         # 	
####################################################
get_position:
addi $sp,$sp,-8
sw $t1,0($sp)
sw $t2,4($sp)
# $t1 - row num
# $t2 - col num
printMsg(msg1)# MACRO
getRow:
li $v0,5
syscall
blt $v0,1,error1
bgt $v0,$a2,error1
add $t1,$v0,$zero
printMsg(msg2)# MACRO
getCol:
li $v0,5
syscall
blt $v0,1,error2
bgt $v0,$a3,error2
add $t2,$v0,$zero
#addi $v1,$t1,-1
#sll $v1,,$v1,2
#add $v1,$v1,$t2
#addi $v1,$v1,-1
sll $t1,$t1,2
addi $t1,,$t1,-5
add $v1,$t1,$t2
j return_from_get_position
error2:
printMsg(wrongInputMatrix)# MACRO
j getCol
error1:
printMsg(wrongInputMatrix)# MACRO
j getRow
return_from_get_position:
addi $sp,$sp,8
lw $t1,0($sp)
lw $t2,4($sp)
jr $ra
