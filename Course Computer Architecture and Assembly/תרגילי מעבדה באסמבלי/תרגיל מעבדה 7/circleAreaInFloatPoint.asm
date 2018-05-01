# based on  99 [b 139]
	.data
	msg: .asciiz "the cicle's area is: "
  pi:     .float 3.1415926
  rad:    .float 12.3456
	.text
main:     l.s $f0,pi
          l.s $f3,rad
          mul.s $f12,$f3,$f3
          mul.s $f12,$f0,$f12
          li $v0,4
          la $a0,msg
          syscall	
          li $v0,2
          syscall
          li $v0,10
 	syscall