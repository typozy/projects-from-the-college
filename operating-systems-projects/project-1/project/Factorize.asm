.data

input: .asciiz "Give the number to factorize: "
wrong: .asciiz "Give a positive number: "
output: .asciiz "Factors of "
are: .asciiz " are:\n"
space: .asciiz " "
enter: .asciiz "\n"

.text
.globl main

main:

	li $v0,4
	la $a0,input
	syscall

	li $v0,5
	syscall
	move $s1,$v0

	loop:

		blt $zero,$s1, endloop

		li $v0,4
		la $a0,wrong
		syscall

		li $v0,5
		syscall
		move $s1,$v0

		j loop

	endloop:
		li $v0,4
		la $a0,output
		syscall

		li $v0,1
		move $a0,$s1
		syscall
		
		li $v0,4
		la $a0,are
		syscall

		addi $t0,$zero,1

		inner:
			div $s1,$t0
			mfhi $t1
			beq $t1,$zero,factor
			j notFactor

		factor:
			li $v0,1
			move $a0,$t0
			syscall

			li $v0,4
			la $a0,space
			syscall

		notFactor:
			addi $t0,$t0,1
			ble $t0,$s1,inner


	li $v0,4
	la $a0,enter
	syscall

	li $v0,10
	syscall
