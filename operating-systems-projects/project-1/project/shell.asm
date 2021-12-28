.data

Intro: .asciiz "Enter the program name to execute (with ShowPrimes, Factorize or BubbleSort command) or exit the shell (with Exit command): "
Wrong: .asciiz "Enter the command truly: "
Bye: .asciiz "Goodbye!\n"

ShowPrimes: .asciiz "ShowPrimes\n"
Factorize: .asciiz "Factorize\n"
BubbleSort: .asciiz "BubbleSort\n"
Space: .asciiz "\n"
Exit: .asciiz "Exit\n"

ShowPrimesAsm: .asciiz "ShowPrimes.asm"
FactorizeAsm: .asciiz "Factorize.asm"
BubbleSortAsm: .asciiz "BubbleSort.asm"
Buffer: .space 50

.text
.globl main

main:

	loop:
		li $v0,4
		la $a0,Intro
		syscall

	buffer:
		li $v0,8
		la $a0,Buffer
		li $a1,20
		syscall

		la $s5, Buffer

		prime:
			move $t1,$s5
			la $t2, ShowPrimes

			innerPrime:
				lb $s3,0($t1)
				lb $s4,0($t2)
				bne $s3,$s4,factor
				beq $s3,$zero,isPrime
				addi $t1,$t1,1
				addi $t2,$t2,1
				j innerPrime

			isPrime:

				li $v0, 18
				la $a0, ShowPrimesAsm
				syscall
				j end

		factor:
			move $t1,$s5
			la $t2, Factorize

			innerFactor:
				lb $s3,0($t1)
				lb $s4,0($t2)
				bne $s3,$s4,sort
				beq $s3,$zero,isFactor
				addi $t1,$t1,1
				addi $t2,$t2,1
				j innerFactor

			isFactor:

				li $v0, 18
				la $a0, FactorizeAsm
				syscall
				j end

		sort:
			move $t1,$s5
			la $t2, BubbleSort

			innerSort:
				lb $s3,0($t1)
				lb $s4,0($t2)
				bne $s3,$s4,space
				beq $s3,$zero,isSort
				addi $t1,$t1,1
				addi $t2,$t2,1
				j innerSort

			isSort:
				li $v0, 18
				la $a0, BubbleSortAsm
				syscall
				j end

		space:
			move $t1,$s5
			la $t2, Space

			innerSpace:
				lb $s3,0($t1)
				lb $s4,0($t2)
				bne $s3,$s4,exit
				beq $s3,$zero,isSpace
				addi $t1,$t1,1
				addi $t2,$t2,1
				j innerSpace

			isSpace:
				j buffer

		exit:
			move $t1,$s5
			la $t2, Exit

			innerExit:
				lb $s3,0($t1)
				lb $s4,0($t2)
				bne $s3,$s4,else
				beq $s3,$zero,isExit
				addi $t1,$t1,1
				addi $t2,$t2,1
				j innerExit

		else:
			li $v0,4
			la $a0,Wrong
			syscall
			j buffer

	end:
		j loop

isExit:
	li $v0,4
	la $a0,Bye
	syscall
	li $v0,10
	syscall
