   .data
A: .word 10
B: .word 76
C: .word 0
 .text
	la $t0, A
	la $t1, B
	la $t2, C

main:
 lw $t3, 0($t0)
 lw $t4, 0($t1)
 add $t5,$t3, $t4
 sw $t5, 0($t2)
 li $v0, 10
 syscall 