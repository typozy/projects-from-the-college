.data

buffer: .word 0
bufferSize: .word 100
result: .asciiz "Result without mutex: "
resultWithMutex: .asciiz "Result with mutex: "
enter: .asciiz "\n"

.text
.globl main
.globl thread

main:

	li $s0,0
	li $s1,2
	li $s2,0

	addi $sp,$sp,-4
	sw $zero,0($sp)
	addi $sp,$sp,4

loop0:
	li $v0,18
	move $a1,$s1
	addi $s0,$s0,1
	move $a0,$s0
	addi $s2,$s2,1
	move $a2,$s2
	move $s4,$s0
	syscall
	blt $s0,$s1,loop0

join00:

	li $v0,19
	li $a0,1
	syscall
	beq $a1,$zero,join00

join01:

	li $v0,19
	li $a0,2
	syscall
	beq $a1,$zero,join01



	li $s0,0
	li $s1,2
	li $s2,2

	#la $s3,buffer
	#sw $zero,0($s3)

	addi $sp,$sp,-8
	sw $zero,0($sp)
	addi $sp,$sp,8

loop1:
	li $v0,18
	move $a1,$s1
	addi $s0,$s0,1
	move $a0,$s0
	addi $s2,$s2,1
	move $a2,$s2
	move $s4,$s0
	syscall
	blt $s0,$s1,loop1

join10:

	li $v0,19
	li $a0,1
	syscall
	beq $a1,$zero,join10

join11:

	li $v0,19
	li $a0,2
	syscall
	beq $a1,$zero,join11

    li $v0,4
    la $a0,result
    syscall

        li $v0,1
        addi $sp,$sp,-4
        lw $a0,0($sp)
        addi $sp,$sp,4
        syscall

    li $v0,4
    la $a0,enter
    syscall

    li $v0,4
    la $a0,enter
    syscall

    li $v0,4
    la $a0,resultWithMutex
    syscall

        li $v0,1
        addi $sp,$sp,-8
        lw $a0,0($sp)
        addi $sp,$sp,8
        syscall

    li $v0,4
    la $a0,enter
    syscall

    li $v0,10
    syscall

thread:

	move $t0,$a2
    li $t1,1
    li $t2,2
    li $t3,3
    li $t4,4
    beq $t0,$t1,producer
    beq $t0,$t2,consumer
    beq $t0,$t3,producerWithMutex
    beq $t0,$t4,consumerWithMutex

threadExit:
    li $v0,20
    move $a0,$s4
    syscall

junk:
	j junk

producer:

	li $t0,0
	li $t1,500
	#addi $sp,$sp,-4

	loopProducer:
		#la $t2,buffer
		#lw $t3,0($t2)
		#addi $t3,$t3,1
		#sw $t3,0($t2)

		addi $sp,$sp,-4
		lw $t3,0($sp)
		addi $t3,$t3,1
		sw $t3,0($sp)
		addi $sp,$sp,4

		addi $t0,$t0,1
		blt $t0,$t1, loopProducer

	#addi $sp,$sp,4

	j threadExit

consumer:

	li $t0,0
	li $t1,500

	#addi $sp,$sp,-4

	loopConsumer:
		#la $t2,buffer
		#lw $t3,0($t2)
		#addi $t3,$t3,-1
		#sw $t3,0($t2)
		addi $sp,$sp,-4
		lw $t3,0($sp)
		addi $t3,$t3,-1
		sw $t3,0($sp)
		addi $sp,$sp,4

		addi $t0,$t0,1
		blt $t0,$t1, loopConsumer

	#addi $sp,$sp,4

	j threadExit

producerWithMutex:

	li $t0,0
	li $t1,500
	addi $sp,$sp,-8

	loopProducerWithMutex:
		producerLock:
			li $v0,21
			move $a0,$s4
			syscall
			beq $a1,$zero,producerLock
		
		#la $t2,buffer
		#lw $t3,0($t2)
		#addi $t3,$t3,1
		#sw $t3,0($t2)

		#addi $sp,$sp,-8
		lw $t3,0($sp)
		addi $t3,$t3,1
		sw $t3,0($sp)
		#addi $sp,$sp,8

		li $v0,22
		move $a0,$s4
		syscall
		addi $t0,$t0,1
		blt $t0,$t1, loopProducerWithMutex

	addi $sp,$sp,8

	j threadExit

consumerWithMutex:

	li $t0,0
	li $t1,500
	addi $sp,$sp,-8

	loopConsumerWithMutex:
		consumerLock:
			li $v0,21
			move $a0,$s4
			syscall
			beq $a1,$zero,consumerLock
		#la $t2,buffer
		#lw $t3,0($t2)
		#addi $t3,$t3,-1
		#sw $t3,0($t2)
		
		#addi $sp,$sp,-8
		lw $t3,0($sp)
		addi $t3,$t3,-1
		sw $t3,0($sp)
		#addi $sp,$sp,8

		li $v0,22
		move $a0,$s4
		syscall
		addi $t0,$t0,1
		blt $t0,$t1, loopConsumerWithMutex

	addi $sp,$sp,8

	j threadExit