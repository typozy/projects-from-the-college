.data

intList: .word 23, 15, 7, 22, 8, 18, 6, 24, 3, 17
length: .word 10

output: .asciiz "The list after sorting: \n"
space: .asciiz " "
enter: .asciiz "\n"
notOrdered: .asciiz "The order before sorting the list:\n"
ordered: .asciiz "The order after sorting the list:\n"

.text
.globl main

main:

	move $t0,$zero
	la $t1,length
	lw $t1,0($t1)
	addi $t1,$t1,-1
	la $t2, intList
	li $t3,4

	li $v0,4
	la $a0,notOrdered
	syscall

	move $s2,$t2
	move $s3,$zero

	before:

		lw $s1,0($s2)

		li $v0,1
		move $a0,$s1
		syscall

		li $v0,4
		la $a0,space
		syscall

		addi $s2,$s2,4
		addi $s3,$s3,1
		ble $s3,$t1, before

	li $v0,4
	la $a0,enter
	syscall

	addi $s1,$zero,0
	move $t4,$t1

	loop:
		move $s2,$s1

		inner:
			addi $s3,$s2,0
			addi $s4,$s2,1
			mul $s3,$s3,$t3
			mul $s4,$s4,$t3

			add $s3,$s3,$t2
			add $s4,$s4,$t2

			lw $s5,0($s3)
			lw $s6,0($s4)

			ble $s5,$s6, notSwitch

			sw $s5,0($s4)
			sw $s6,0($s3)
			
		notSwitch:
			addi $s2, $s2, 1
			blt $s2,$t1, inner

		addi $t4, $t4, -1
		blt $s1, $t4, loop

	li $v0,4
	la $a0,ordered
	syscall

	move $s2,$t2
	move $s3,$zero

	after:

		lw $s1,0($s2)

		li $v0,1
		move $a0,$s1
		syscall

		li $v0,4
		la $a0,space
		syscall

		addi $s2,$s2,4
		addi $s3,$s3,1
		ble $s3,$t1, after

	li $v0,4
	la $a0,enter
	syscall

	li $v0,10
	syscall
