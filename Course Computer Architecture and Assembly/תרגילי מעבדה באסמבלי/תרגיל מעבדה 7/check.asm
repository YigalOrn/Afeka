# Lab 6: Floating Point Addition
# Created 2/12/99 by Travis Furrer & David Harris
#
#--------------------------------
# <Please put your name here>
#--------------------------------

################# Data segment #####################
# The numbers below are loaded into memory (the Data Segment)
# before your program runs.  You can use a lw instruction to
# load these numbers into a register for use by your code.
.data
atest:  .word 0x40000000 # you can change this to anything you want
btest:  .word 0x40000000 # you can change this to anything you want
smask:  .word 0x007FFFFF # significand mask ,  NOTICE : the S.N - 1.xxxxx...xx
emask:  .word 0x7F800000 # exponent mask
ibit:   .word 0x00800000
obit:   .word 0x01000000
################# Code segment #####################
.text

main:

        li $a0,0
        li $a1,0x3e400000 # 1.11*2^5
        
        #li $a1,0x42600000 # 1.1*2^(-3)
        #li $a0,0x3e400000 # 1.11*2^5
        
        #li $a0,0x42600000
        #li $a1,0x3e400000
        
        jal flpadd
        
        mtc1 $v0,$f1 
	
	li $v0, 2
        mov.s $f12,$f1          	
	syscall
	li $v0, 11
	li $a0, ' ' 
	syscall
	syscall	

end:    
	li $v0,10   		# exit program
	syscall                 #


####################################################
#Procedure: flpadd                                 #
# input : $a0-->current sum,result accumulator     #
#         $a1-->next element in the series         # 
# output : $v0-->addition result                   # 
# Description:addition in floating point           #
# single precision IEE 754 standard                #
####################################################
flpadd:

# NOTICE_1# 
# The sum $a0 is always bigger then the next elemnt to add $a1 !
# Thats why we are going to align the binary point of $a1 hence making the correct 
# adjustment to $a1  8-bit Exponent !
# NOTICE_2# 
# We add two possitive f.p numbers , the sign bit is always zero.
# NOTICE_3# 
# From the same reason the logical shift will be always to the right.


#---------------------
# $t1 - $a0 : Exponent
# $t2 - $a0 : Mantisa(fraction) without the Hidden bit !!
# $t3 - $a1 : Exponent
# $t4 - $a1 : Mantisa(fraction) without the Hidden bit !!
# $t5 - mask and other dirty jobs
# $t7 - flag
#---------------------

#stage_1#
lw $t5,emask
and $t1,$a0,$t5 #get the Exponent portion from $a0
srl $t1,$t1,23  #adjust the Exponent postion in the reg $t1.
and $t3,$a1,$t5 #get the Exponent portion from $a1
srl $t3,$t3,23  #adjust the Exponent postion in the reg $t3.
#stage_2#
lw $t5,smask
and $t2,$a0,$t5 #get the fracation portion from $a0 , without hidden 1 ! 
ori $t2,$t2,0x00800000 #form the significand by adding 1 to the 24 bit
and $t4,$a1,$t5 #get the fracation portion from $a1 , without hidden 1 ! 
ori $t4,$t4,0x00800000 #form the significand by adding 1 to the 24 bit
#stage_3#
# $t5 - the difference between exponents
sleu   $t7,$t1,$t3 # $t7 = ($t1<=$t3) ? 1:0
bnez $t7,continue1
sub $t5,$t1,$t3 #the difference between the two exponents
j goto1
continue1:
sub $t5,$t3,$t1 #the difference between the exponents
goto1:
#stage_4#
bnez $t7,continue2
add $t3,$t3,$t5 #adjust the small exponent to be with the same value as big one for addition
j goto2
continue2:
add $t1,$t1,$t5 #adjust the small exponent to be with the same value as big one for addition
goto2:
#stage_5#
bnez $t7,continue3
# the exponent in $t3 has the significand in $t4
srav $t4,$t4,$t5 #alignment , 0.12*10^(-4) = 12*10^(-6)
j goto3
continue3:
# the exponent in $t1 has the significand in $t2
srav $t2,$t2,$t5 #alignment , 0.12*10^(-4) = 12*10^(-6)
goto3:
#stage_6
add $v0,$t4,$t2 #summation of significands
#stage_7#
#check for overflow
#check over flow here : add $v0,$t4,$t2  #summation of significands, LINE:214
blt $v0,0x01000000,L
srl $v0,$v0,1
bnez $t7,R
addi $t3,$t3,1 
j L
R:
addi $t1,$t1,1 
L:
#stage_8#
andi $v0,$v0,0x007fffff #strip the hidden 1 from the significand
#stage_9#
bnez $t7,continue4
sll $t3,$t3,23 #place the exponent in the correct f.p format  
andi $t3,$t3,0x7f800000 #zeroing all except the exponent portion
j goto4
continue4:
sll $t1,$t1,23 #place the exponent in the correct f.p format  
andi $t1,$t1,0x7f800000 #zeroing all except the exponent portion
goto4:
bnez $t7,continue5
add $v0,$v0,$t3 #welding the sign exponent and fraction(without hidden bit) together
j return
continue5:
add $v0,$v0,$t1 #welding the sign exponent and fraction(without hidden bit) together

return:
jr $ra


