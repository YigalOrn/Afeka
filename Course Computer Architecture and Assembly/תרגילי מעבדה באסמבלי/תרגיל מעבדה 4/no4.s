# Title: Lab 4       	Filename:
# Author:       	Date:
# Description:
# Input: a number between 1-99
# Output: An isosceles triangle
################# Data segment #####################
.data

msg1: .asciiz "\n Please enter a number between 1-99: \n"
msg2: .asciiz "Wrong input"

################# Code segment #####################
.text
wrong:
	la $a0,msg2	# put string address into a0
	li $v0,4		# system call to print
	syscall		# out a string 		



.globl main
main:	# main program entry
	
  	la $a0,msg1	# put string address into a0
	li $v0,4	# system call to print
	syscall		# out a string 			


	li $v0,5  #get a number from the user
	syscall
	bgt $v0,99,wrong
	blt   $v0,1,wrong	
	




	li $v0, 10	# Exit program
	syscall

