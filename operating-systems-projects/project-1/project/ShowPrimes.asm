.data

begin: .asciiz "The prime numbers from 1 to 1000 are:\n"
enter: .asciiz "\n"
space: .asciiz " "
prime: .asciiz "prime "

.text
.globl main

main:

	li $v0,4
	la $a0,begin
	syscall

	addi $s1, $zero, 1

	li $v0,1
	move $a0,$s1
	syscall

	li $v0,4
	la $a0,space
	syscall

	addi $s1, $zero, 2

	li $v0,1
	move $a0,$s1
	syscall

	li $v0,4
	la $a0,space
	syscall

	li $v0,4
	la $a0,prime
	syscall

	addi $s1, $zero, 3
	addi $s2, $zero, 1000

	loop:

		li $v0,1
		move $a0,$s1
		syscall

		li $v0,4
		la $a0,space
		syscall

		addi $t0, $zero, 2
		addi $t1 ,$s1, -1

		inner:
			div $s1,$t0
			mfhi $t2
			beq $t2,$zero,notPrime
			addi $t0, $t0, 1
			ble $t0,$t1,inner

		isPrime:
			li $v0,4
			la $a0,prime
			syscall

		notPrime:

		addi $s1, $s1, 1
		ble $s1,$s2,loop

	li $v0,4
	la $a0,enter
	syscall

	li $v0,10
	syscall
