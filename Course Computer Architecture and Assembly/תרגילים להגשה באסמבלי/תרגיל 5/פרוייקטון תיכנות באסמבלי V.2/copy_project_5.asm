# Title: Exercise 5	Filename: project_5.asm
# Author: Ornes Yigal 303893416       	Date:1Q84
# Description: mini project V.2
################# Data segment #####################
.data
# 4x4 matrix <<--------------------------
matrix: .byte 2,7,34,68,56,89,156,122,135,0,33,122,122,66,18,255
ROWS: .word 4 # is the same as we got them from the console
COLS: .word 4 # is the same as we got them from the console
# Testing other options
#---------------------------------------------
#matrix: .byte 2,7,34,68,56,89,156,122,122,66,18,255,135,0,33,122
#matrix: .byte 2,7,34,68,122,66,18,255,56,89,156,122,135,0,33,122
#matrix: .byte 2,11,34,1,156,89,1,122,135,0,1,122,122,1,18,255
#matrix: .byte 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
#matrix: .byte 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#matrix: .byte 25,25,25,25,2,2,2,2,20,20,20,20,255,255,255,255
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
here: .asciiz "\n@@@@@@@@@@\n "
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
# using a help procedure - print_num               # 	
####################################################	      
print:                                               
addiu $sp,$sp,-40# allocate space on prucedure stack
sw $ra,0($sp)# save the return address
sw $s0,4($sp)#save special reg. for MACRO 
sw $a0,8($sp)
sw $a1,12($sp)
sw $a2,16($sp)
sw $a3,20($sp)
sw $t1,24($sp)
sw $t2,28($sp)
sw $t3,28($sp)
sw $t4,32($sp)
sw $v0,36($sp) #in MACRO

DEBUG(in_print)# MACRO
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
lb $a2,0($a0) # Or addi +256 = 0100000000 , or masking, or lbu
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

DEBUG(out_print)# MACRO

lw $ra,0($sp)# save the return address
lw $s0,4($sp)#save special reg. for MACRO 
lw $a0,8($sp)
lw $a1,12($sp)
lw $a2,16($sp)
lw $a3,20($sp)
lw $t1,24($sp)
lw $t2,28($sp)
lw $t3,28($sp)
lw $t4,32($sp)
lw $v0,36($sp) #in MACRO
addiu $sp,$sp,40 # free allocated space

jr $ra # return from current procedure
####################################################
#Procedure:  change_number                         #
# input : $a0-->matrix address in memory           #  
# Description: changes a number in the matrix      #
# according to users choice                        #
# using a help procedure - get_position            # 	
####################################################	
change_number:                                         

addiu $sp,$sp,-20
sw $ra,0($sp)
sw $a0,4($sp)
sw $s0,8($sp)
sw $v0,12($sp)
sw $v1,16($sp)

DEBUG(in_change_num)# MACRO

jal get_position

lw $a0,4($sp)

printMsg(msg3)# MACRO

getNewNum:
li $v0,5
syscall
bgt $v0,255,error3# upper lim in unsigned , is it a byte input condition
blt $v0,-128,error3# lower lim in signed , -"-
add $a0,$v1,$a0
sb $v0,0($a0)
j return_from_change_num
error3:
printMsg(wrongInputMatrix)# MACRO
j getNewNum
return_from_change_num:

DEBUG(out_change_num)# MACRO

lw $ra,0($sp)
lw $a0,4($sp)
lw $s0,8($sp)
lw $v0,12($sp)
lw $v1,16($sp)
addiu $sp,$sp,20


jr $ra
####################################################
#Procedure:  negate                                #
# input : $a0-->matrix address in memory           # 
# Description: negates a number in 2th complement  #
# according to users choice                        #
# using a help procedure - get_position            # 	
####################################################	
negate:  
                                            
addiu $sp,$sp,-20
sw $ra,0($sp)
sw $a0,4($sp)
sw $t1,8($sp)
sw $t2,12($sp)
sw $s0,16($sp) #in MACRO

DEBUG(in_negate)# MACRO

jal get_position

add $a0,$a0,$v1
lb $t1,0($a0)
abs $t2,$t1
beq $t2,128,return_from_negate # have no reflecetion
nor $t1,$t1,$zero # breaks to OR + NOT
addi $t1,$t1,257 # 1 for NOT , 256 for correction/also we can use a mask as before
sb $t1,0($a0)
return_from_negate:

lw $ra,0($sp)
addi $sp,$sp,4

DEBUG(out_negate)# MACRO


sw $ra,0($sp)
sw $a0,4($sp)
sw $t1,8($sp)
sw $t2,12($sp)
sw $s0,16($sp) #in MACRO
addiu $sp,$sp,20

jr $ra
####################################################
#Procedure:  swap                                  #
# input : $a0-->matrix address in memory           #  
# Description: swaps two elements in the matrix    #
# using a help procedure - get_position            # 		
####################################################	
swap:                                                   

addiu $sp,$sp,-28
sw $ra,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
sw $t3,12($sp)
sw $t4,16($sp)
sw $a0,20($sp)
sw $s0,24($sp) #in Macro

DEBUG(in_swap)# MACRO

#------------------
# $t3 - first index --> first byte value
# $t4 - second index --> second byte value
# $t1 - first byte value
# $t2 - second byte value
#------------------

jal get_position
add $t3,$v1,$zero
jal get_position
add $t4,$v1,$zero
#get values
add $a0,$a0,$t3
lb $t1,0($a0)

lw $a0,20($sp)

add $a0,$a0,$t4
lb $t2,0($a0)
#replace values
sb $t1,0($a0)

lw $a0,20($sp)

add $a0,$a0,$t3
sb $t2,0($a0)


DEBUG(out_swap)# MACRO

lw $ra,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
lw $t3,12($sp)
lw $t4,16($sp)
lw $a0,20($sp)
lw $s0,24($sp) #in Macro
addiu $sp,$sp,28

jr $ra
####################################################
#Procedure:  find_max                              #
# input : $a0-->matrix address in memory	   #  
#         $a1-->user's choice value for this func  #  
#         $a2-->matrix rows              	   #  
#         $a3-->matrix cols              	   #  
# Description: prints the row in matrix            #
# with the highest sum unsigned                    #  
# using a help procedure - help_find_max           #
#                        - print_row               #	         		   	
####################################################	
find_max:  
                                             #<<<<<<<<<<<<-------------------------
addiu $sp,$sp,-24
sw $ra,0($sp)
sw $a0,4($sp)
sw $a1,8($sp)
sw $a3,12($sp)
sw $v1,16($sp)
sw $s0,20($sp) #in MACRO

DEBUG(in_find_max)

beq $a1,7,unsginedSum
beq $a1,8,signedSum

unsginedSum:
jal help_find_max
li $a1,1# next procedure called parameter
j gotoPrintRow

signedSum:
jal help_find_max
li $a1,2# next procedure called parameter 

gotoPrintRow:
lw $a0,4($sp)# next procedure called parameter
add $a3,$v1,$zero# next procedure parameter

jal print_row

DEBUG(out_find_max)

lw $ra,0($sp)
lw $a0,4($sp)
lw $a1,8($sp)
lw $a3,12($sp)
lw $v1,16($sp)
lw $s0,20($sp)
addiu $sp,$sp,24

jr $ra                                               
#---------------------------------------------   	   	   
	   # Exit program 
	   exit:
	   printMsg(msg9)
	   li $v0, 10	
	   syscall
#---------------------------------------------   
####################################################
#Procedure:  help_find_max                         #
# input : $a0-->matrix address in memory	   #  
#         $a1-->user's choice value      	   #  
#         $a2-->matrix rows              	   #  
#         $a3-->matrix cols              	   # 
#output : $v1--> max sum row index                 #  
#Description: finds the index in matrix 0-3        #
# with the highest sum                             #
####################################################	
help_find_max:

addi $sp,$sp,-32
sw $a0,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
sw $t3,12($sp)
sw $t4,16($sp)
sw $t5,20($sp)
sw $t6,24($sp)
sw $t7,28($sp)


#-------------------------
# $t1 - row ctr
# $t2 - col ctr
# $t3 - current sum
# $t4 - matrix offset
# $t5 - max sum
# $t6 - index in array (not matrix)
# $t7 - current byte size value to sum
# some local parameters are used twice ,differently then from mentioned above !
#-------------------------

andi $t1,$t1,0 # zeroing because they were used before
andi $t2,$t2,0
andi $t3,$t3,0 #

rowLoop:
      
      sll $t4,$t1,2
      add $t6,$a0,$zero
      add $t6,$t6,$t4
    
      colLoop:
      
      #-------
      bne $a1,7,signedSumming
      lbu $t7,0($t6) # $a1 - current byte size value to sum
      j skip
      signedSumming:
      lb $t7,0($t6) # $a1 - current byte size value to sum
      #-------
      skip:
      addi $t6,$t6,1
      add $t3,$t3,$t7
      addi $t2,$t2,1  
      bne $t2,$a3,colLoop
   
bnez $t1,continue2 # first time setup
add $t5,$t3,$zero
add $v1,$t1,$zero
continue2:
#-------
bne $a1,7,signedComparison
bleu $t3,$t5,continue3
j refresh
signedComparison:
ble $t3,$t5,continue3
#-------
refresh:
add $t5,$t3,$zero
add $v1,$t1,$zero
continue3:                       
lw $a0,0($sp)
andi $t3,$t3,0
andi $t2,$t2,0
addi $t1,$t1,1            
bne $t1,$a2,rowLoop

lw $a0,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
lw $t3,12($sp)
lw $t4,16($sp)
lw $t5,20($sp)
lw $t6,24($sp)
lw $t7,28($sp)
addi $sp,$sp,32

jr $ra
####################################################
#Procedure:  print_row                             #
# input : $a0-->matrix address                     #  
#         $a1-->user choice for prin_num 1-2       # 
#         $a3-->row to print index 0-3             #  
# Description: print a row in the matrix           #
# using a given index as a procedure  parameter    #
####################################################
print_row:                                           

addi $sp,$sp,-28
sw $a0,0($sp)
sw $ra,4($sp)
sw $v0,8($sp) #in MACRO
sw $t1,12($sp)
sw $a3,16($sp)
sw $a2,20($sp)
sw $s0,24($sp) #in MACRO



move $a0,$a3 # print row number 0-3
printInt # MACRO
printTab # MACRO

# $a3 - max sum row index , for print loop

lw $a0,0($sp)
andi $t1,$t1,0 # loop counter
sll $a3,$a3,2 # example: $a3=index=3 --> 3*4=12 goto element(in bytes) that starts at 12
add $a3,$a3,$a0# base + offset

printRowElements:

lbu $a2,0($a3)

jal print_num # call to print_num , parameters of func: $a1 - choice , $a2 - value 

printTab# MACRO

addi $a3,$a3,1
addi $t1,$t1,1
bne $t1,4,printRowElements

lw $a0,0($sp)
lw $ra,4($sp)
lw $v0,8($sp) #in MACRO
lw $t1,12($sp)
lw $a3,16($sp)
lw $a2,20($sp)
lw $s0,24($sp) #in MACRO
addi $sp,$sp,28


jr $ra                                                
####################################################
#Procedure:  print_num                             #
# input : $a2-->byte size num value	           #  
#         $a1-->user's choice value      	   #  
# Description: prints one byte num in the          #
# chosen format                    	           #
####################################################		
print_num:                                           

addi $sp,$sp,-28
sw $ra,0($sp)
sw $s0,4($sp)
sw $a0,8($sp)
sw $a1,12($sp)
sw $t2,16($sp)
sw $t1,20($sp)
sw $t5,24($sp)

li $t1,255 # for masking

beq $a1,1,unsgined
beq $a1,2,signed
beq $a1,3,octa
#--------------------
unsgined:
li $a1,10 # base
and $a2,$a2,$t1# masking
jal help_print_num
j return_from_print_num
#--------------------
#(2's comp. , NOTICE : 1000000 has no reflection ! page 90)
signed:
li $a1,10 # base
and $a2,$a2,$t1 # masking
srl  $t5,$a2,7
bne $t5,1,isPos
move $s0,$a0
li $a0,'-'
printChar# MACRO
move $a0,$s0
nor $a2,$a2,$zero # breaks to OR + NOT
and $a2,$a2,$t1 # masking
addi $a2,$a2,1
j goto_help_print_num
isPos:
move $s0,$a0
li $a0,'+'
printChar# MACRO
move $a0,$s0
goto_help_print_num:
jal help_print_num
j return_from_print_num
#--------------------
octa:
li $a1,8 # base
and $a2,$a2,$t1# masking
jal help_print_num
#--------------------
return_from_print_num:

lw $ra,0($sp)
lw $s0,4($sp)
lw $a0,8($sp)
lw $a1,12($sp)
lw $t2,16($sp)
lw $t1,20($sp)
lw $t5,24($sp)
addi $sp,$sp,28

jr $ra                                                     
####################################################
#Procedure:  help_print_num                        #
# input : $a2 - byte value                         #  
#         $a1 - base                               # 
# output :                                         #   
# Description: actually prints                     #
# the 3 decimal digits given in reg a2             #
####################################################
help_print_num:

addi $sp,$sp,-40
sw $a0,0($sp)
sw $a1,4($sp)
sw $a2,8($sp)
sw $t1,12($sp)
sw $t2,16($sp)
sw $t3,20($sp)
sw $v0,24($sp) #in MACRO


# $t1 - loop counter
# $t2 - base+offset
# $t3 - remainder


add $t2,$sp,$zero# set $t2 to the address of $sp that is -36 bytes from the end of the stack! 
addiu $t2,$t2,28
andi $t1,$t1,0

loop2:
divu $a2,$a1
mflo $a2
mfhi $t3
sw $t3,0($t2)

addi $t2,$t2,4
addi $t1,$t1,1
bne $t1,3,loop2

#NOTICE:also possible to create the number with multiples of 10^n using only one reg.
move $t1,$a0
lw $a0,36($sp)
printInt
lw $a0,32($sp)
printInt
lw $a0,28($sp)
printInt
move $a0,$t1


lw $a0,0($sp)
lw $a1,4($sp)
lw $a2,8($sp)
lw $t1,12($sp)
lw $t2,16($sp)
lw $t3,20($sp)
lw $v0,24($sp) #in MACRO
addi $sp,$sp,40

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

addi $sp,$sp,-20
sw $t1,0($sp)
sw $t2,4($sp)
sw $v0,8($sp) #in MACRO
sw $s0,12($sp) #in MACRO
sw $a2,16($sp)

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


lw $t1,0($sp)
lw $t2,4($sp)
lw $v0,8($sp) #in MACRO
lw $s0,12($sp) #in MACRO
lw $a2,16($sp)
addi $sp,$sp,20

jr $ra                                                



