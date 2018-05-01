# Title: Lab1        	Filename:
# Author:       	Date:
# Description:
# Input: $s0= a word hexa 8 digit number
# Output: $t0= the number of even hexa digits
################# Data segment #####################
.data
str: .asciiz  "Hellow World\n"

################# Code segment #####################
.text
.globl main
main:	# main program entry



la $a0,str
li $v0,4
syscall

#li $a0,'N'
li $a0,97  #shows the lower 8 ascii bits in the reg of 32 bits
li $v0,11
syscall

#syscall פקודת אסמבלי בסיסית של המעבד הגורמת למעבר הבקרה לקטה הקוד של מערכת ההפעלה
#exception handler הקטע נקרא






li $v0, 10	# Exit program
syscall












li $v0, 10	# Exit program
syscall