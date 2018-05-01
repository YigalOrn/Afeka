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

# The main program computes e(exponant) using the infinite series, and
# calls your flpadd(floating point addition) function (below).
#
# PLEASE DO NOT CHANGE THIS PART OF THE CODE <<<<-------------------------
#
#-----------------------
# The code uses the registers as follows:
#    $s0 - 1 (constant integer)
#    $s1 - i (loop index variable)
#    $s2 - temp
#    $f0 - 1 (constant single precision float)
#    $f1 - e (result accumulator) - the sum
#    $f2 - 1/i!
#    $f3 - i!
#    $f4 - temp
#-----------------------
                
main:   
        li $s0,1                # load constant 1
        mtc1 $s0,$f0            # copy 1 into $f0
        cvt.s.w $f0,$f0         # convert 1 to float , 0x3F800000
        
        mtc1 $0,$f1             # zero out result accumulator <<<<-------- ?
        
        li $s1,0                # initialize loop index

tloop:  
        addi $s2,$s1,-11        # Have we summed the first 11 terms?
        beq $s2,$0,end          # If so, terminate loop
        bnez $s1,fact           # If this is not the first time, skip init
        mov.s $f3,$f0           # Initialize 0! = 1
        j dfact                 # bypass fact

fact:                           # factorial calc.   
        mtc1 $s1,$f4            # copy i into $f4
        cvt.s.w $f4,$f4         # convert i to float
        mul.s $f3,$f3,$f4       # update running fact
dfact:  
        div.s $f2,$f0,$f3       # compute 1/i! = $f2
        #add.s $f1,$f1,$f2#     # we use your flpadd function instead!
       
        mfc1 $a0,$f1            #\  These lines should do the same thing
        mfc1 $a1,$f2            # \ as the commented out line above.
        jal flpadd              # / This is where we call your function.
        mtc1 $v0,$f1            #/  $v0 - the result of addition from procedure flpadd 
                                # $a0,$a1 procedure flpadd parameters
################# printing the float number ###################	
	li $v0, 2
        mov.s $f12,$f1          	
	syscall
	li $v0, 11
	li $a0, ' ' 
	syscall
	syscall	
################################################################
        addi $s1,$s1,1          # increment i
        j tloop                 #

end:    
	li $v0,10   		# exit program
	syscall                 #

# If you have trouble getting the right values from the program
# above, you can comment it out and do some simpler tests using
# the following program instead.  It allows you to add two numbers
# (specified as atest and btest, above), leaving the result in $v0.

#main:   lw $a0,atest
#        lw $a1,btest
#        jal flpadd
#end:    j end



# Here is the function that performs floating point addition of
# single-precision numbers.  It accepts its arguments from
# registers $a0 and $a1, and leaves the sum in register $v0
# before returning.
#
# Make sure not to use any of the registers $s0-$s7, or any
# floating point registers, because these registers are used
# by the main program.  All of the registers $t0-$t9, however,
# are okay to use.
#
# YOU SHOULD NOT USE ANY OF THE MIPS BUILT-IN FLOATING POINT
# INSTRUCTIONS.  Also, don't forget to add comments to each line
# of code that you write.
#
# Remember the single precision format (see page 276):
#      bit 31 = sign (1 bit)
#       bits 30-23 = exponent (8 bits)
#        bits 22-0 = significand (23 bits)
#
#
#
#	Explain your registers here
#
#Enter your code here
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
#
# $t7 - flag
#---------------------

#initial values of: 
# $a0 = 0  , $a1 = 1   iteration 0
# $a0 = 1  , $a1 = 1   iteration 1
# $a0 = 2  , $a1 = 1/2
# $a0 = 2.5 , $a1 = 1/6

#stage_1
lw $t5,emask
and $t1,$a0,$t5 #get the Exponent portion from $a0
srl $t1,$t1,23  #adjust the Exponent so the value will be correct in a reg.

and $t3,$a1,$t5 #get the Exponent portion from $a1
srl $t3,$t3,23

#stage_2
lw $t5,smask
and $t2,$a0,$t5 #get the fracation portion from $a0 , without hidden 1 ! 
ori $t2,$t2,0x00800000 #form the significand by adding 1 to the 24 bit

and $t4,$a1,$t5 #get the fracation portion from $a1 , without hidden 1 ! 
ori $t4,$t4,0x00800000 #form the significand by adding 1 to the 24 bit

#stage_3
# $t5 - the difference between exponents
#comparison instructions
#-"-
#-"-
sleu   $t7,$t1,$t3 # $at = ($t1<=$t3) ? 1:0

bnez $t7,continue1
sub $t5,$t1,$t3 #the difference between the exponents
j goto1
continue1:
sub $t5,$t3,$t1 #the difference between the exponents
goto1:

#stage_4
bnez $t7,continue2
add $t3,$t3,$t5 #adjust the small exponent to be with the same value as big one for addition

j goto2
continue2:
add $t1,$t1,$t5 #adjust the small exponent to be with the same value as big one for addition

goto2:

#stage_5
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


#stage_7
#check for overflow
#check over flow here : add $v0,$t4,$t2  #summation of significands, LINE:214
blt $v0,0x01000000,L
srl $v0,$v0,1

bnez $t7,continue33
addi $t3,$t3,1 
j L
continue33:
addi $t1,$t1,1 
L:

#stage_8
andi $v0,$v0,0x007fffff #strip the hidden 1 from the significand

#stage_9
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






