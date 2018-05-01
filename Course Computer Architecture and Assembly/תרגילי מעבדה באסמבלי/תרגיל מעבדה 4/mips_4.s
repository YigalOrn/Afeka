# Title: Lab 4       	Filename:
# Author:       	Date:
# Description:
# Input: a number between 1-99
# Output: An isosceles triangle
################# Data segment #####################
.data

msg1: .asciiz "\n Please enter a number between 1-99: \n"
msg2: .asciiz "Wrong input"

char: .byte '*'
enter: .asciiz "\n"
blank: .byte '-'
#blank: .byte ' '

################# Code segment #####################
.text
wrong:
	la $a0,msg2	# put string address into a0
	li $v0,4        # system call to print
	syscall		# out a string 	
        j main


.globl main
main:	# main program entry
	
	
  	la $a0,msg1	# put string address into a0
	li $v0,4	# system call to print
	syscall		# out a string 			

	li $v0,5  #get a number from the user
	syscall
	bgt $v0,99,wrong
	blt $v0,1,wrong	
	move $s2,$v0#save value - number of rows

	
	and $s3,$s3,0 # zeroing counter for lines
        
lineLoop:

beq $s3,$s2,exit# if $s3 = $s2 goto exit
add $s3,$s3,1
and $s4,$s4,0 #counter / zeroing counter              

   
    #   '\n' 
    la $a0,enter
    li $v0,4  
    syscall           
       
    #given formula
    sll  $s5,$s3,1  # same as mul $s5,$s3,2
    sub $s5,$s5,1          
    sub $s6,$s2,$s3 #spaces counter for equilateral triangle    
    addiu $s6,,$s6,5
    
    # make sure that inside LOOPS instructions will be atom and not pseudo!
    beq $s6,0,continue    
   
   loop:
    
    #for placing the triangle we need to find a way to exclude the n-factor in the formula!!!
    #print spaces to console 
    lb $a0,blank
    li $v0,11  
    syscall 
    add $s4,$s4,1
    blt $s4,$s6,loop # $s4 < $s6                                                                                       
   
    continue:
    andi $s4,0 #zeroing counter                                                                                                                                                                              
                             
                charsLoop:
              
                beq $s4,$s5,lineLoop# if $s4 = $s5 goto lineLoop
              
                #print char '*'
                lb $a0,char#load char '*' to reg 
                li $v0,11  
	        syscall   
                add $s4,$s4,1
                j charsLoop 

exit:
	li $v0, 10	# Exit program
	syscall

# syscall 5  gets an int number in ascii code in 10 base (in the background the ascii to integer is procedure is activated atoi)
#syscall 5 saves the value to $v0 !




