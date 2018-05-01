# Computer Architecture  q4.s
#	 
# Input: array of 10 bytes that represent sign numbers  
#.
# Output: 1)the sum of the 10 numbers (to the screen)
#	2)copy the diffrence of eace pair in array into array1
#	
#
## for example 

# for the array: 23,-2,45,67,89,12,-100,0,120,6

#  the sum is 260 

#  and array1: 25,-47,-22,-22, 77, 112,-100,-120,114

# in mem you should get

# Address +0x0 +0x4 +0x8 +0xc +0x10
#0x10010000 0x432dfe17 0x009c0c59 0xd1190678 0x704deaea x0a72889c 

# we can disrigard overflow !

################# Data segment #####################
.data
array:   	.byte   23,-2,45,67,89,12,-100,0,120,6
#array: 	.byte   1,2,3,4,5,6,7,8,9,10
#array: 	.byte   2,4,8,16,32,64,128,256,512,1024 #overflow 
#array: 	.byte   1,1,1,1,1,1,1,1,1,10
#array: 	.byte   -1,-1,-1,-1,-1,-1,-1,-1,-1,9

array1:	.space  9
			
msg1:   .asciiz "\n The sum of the numbers in the array is :     "
msg2:   .asciiz "\n array1 elements:\n"
ch :    .byte ','

.macro specPrint(%arg)
 
 move $a0,%arg
 li $v0,1		# system call to print an int
 syscall	

 lb $a0,ch
 li $v0,11		# system call to print an char
 syscall
 
.end_macro
################# Code segment #####################
.text
.globl main
main:	# main program entry
 
        # print input msg syscall 4
	la $a0,msg1	# The sum of the numbers in the array is :
	li $v0,4	# system call to print
	syscall		# out a string 
    
#answer

andi $s0,$s0,0  # $s0 - diff	
andi $a0,$a0,0  # sum
#andi $t9,$t9,0 #index counter		
la $t0,array
la $t8,array
la $t5,array1
				
loop:

lb $t1,0($t0)

subu $t9,$t0,$t8  # using the address to find the index , just for fun !

addu $a0,$a0,$t1  # calc the sum , save move com. by using reg $a0

beq $t9,9,continue
lb $t2,1($t0)
subu $t1,$t1,$t2
sb $t1,0($t5)
addiu $t5,$t5,1 # next int index

continue:
addiu $t0,$t0,1  # next int index
#addiu $t9,$t9,1 #
blt $t9,9,loop   # or - ble $t9,8,loop , NOTICE: when $t0 = 1  $t9 = 0

      
       #print sum
	li $v0,1	# system call to print
	syscall	
       #print diff
       la $a0,msg2
       li $v0,4		# system call to print an int
       syscall

       la $t5,array1
       andi $t9,$t9,0
       loop1:

       lb $t1,0($t0)
       specPrint($t1)
       addiu $t0,$t0,1
       addiu $t9,$t9,1
       ble $t9,8,loop1


# end of program
exit:	
	li $v0,10
	syscall
	