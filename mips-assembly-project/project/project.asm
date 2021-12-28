.data
file: .asciiz "input_project.txt"
buffer: .space 256

zero: .asciiz "zero"
zeroStart: .asciiz "Zero"
one: .asciiz "one"
oneStart: .asciiz "One"
two: .asciiz "two"
twoStart: .asciiz "Two"
three: .asciiz "three"
threeStart: .asciiz "Three"
four: .asciiz "four"
fourStart: .asciiz "Four"
five: .asciiz "five"
fiveStart: .asciiz "Five"
six: .asciiz "six"
sixStart: .asciiz "Six"
seven: .asciiz "seven"
sevenStart: .asciiz "Seven"
eight: .asciiz "eight"
eightStart: .asciiz "Eight"
nine: .asciiz "nine"
nineStart: .asciiz "Nine"

.text
jal fileOpen

move $s0, $v0 #file pointer

jal fileRead

move $s1,$v0 #text length
move $t5,$zero #counter

loop:
	beq $t5,$s1,exit
	la $t2,buffer($t5)
	lb $t6,($t2)
	j check #checking if number, and which number
notNum:	li $v0,11
	move  $a0,$t6
	syscall
num:	addi $t5,$t5,1
	j loop
fileOpen:
	li $v0,13
	la $a0,file
	li $a1,0
	li $a2,0
	syscall
	jr $31
fileRead:
	li $v0,14
	move $a0,$s0
	la $a1,buffer
	li $a2,256
	syscall
	jr $31
fileClose:
	li $v0,16
	move $a0,$s0
	syscall
	jr $31
check:
	jal isNum
	beq $v0,1,isDigit #if a number, checks if it is a single digit in the text file
	j notNum #if not a number, returns to the loop and prints the character
isNum:
	slti $t9,$t6,57
	slti $t8,$t6,48
	slt $v0,$t8,$t9 #this function returns 1 if the indexed character is a number
	jr $31
isDigit:
	bne $t5,0,isLast
	addi $t0,$t5,1
	la $t2,buffer($t0)
	lb $t3,($t2)
	beq $t3,32,bigNum
isLast:
	sub $t9,$s1,$t5
	bne $t9,2,isStart
	addi $t0,$t5,-1
	la $t2,buffer($t0)
	lb $t3,($t2)
	beq $t3,32,smallNum
isStart:
	addi $t0,$t5,-2
	la $t2,buffer($t0)
	lb $t3,($t2)
	bne $t3,46,isEnd
	addi $t0,$t0,1
	la $t2,buffer($t0)
	lb $t3,($t2)
	bne $t3,32,isEnd
	addi $t0,$t0,2
	la $t2,buffer($t0)
	lb $t3,($t2)
	beq $t3,32,bigNum
isEnd:
	addi $t0,$t5,-1
	la $t2,buffer($t0)
	lb $t3,($t2)
	bne $t3,32,isBetween
	addi $t0,$t0,2
	la $t2,buffer($t0)
	lb $t3,($t2)
	bne $t3,46,isBetween
	addi $t0,$t0,1
	la $t2,buffer($t0)
	lb $t3,($t2)
	beq $t3,32,smallNum
isBetween:
	addi $t0,$t5,-1
	la $t2,buffer($t0)
	lb $t3,($t2)
	bne $t3,32,notNum
	addi $t0,$t0,2
	la $t2,buffer($t0)
	lb $t3,($t2)
	beq $t3,32,smallNum
	j notNum
smallNum:
	beq $t6,48,smallZero
	beq $t6,49,smallOne
	beq $t6,50,smallTwo
	beq $t6,51,smallThree
	beq $t6,52,smallFour
	beq $t6,53,smallFive
	beq $t6,54,smallSix
	beq $t6,55,smallSeven
	beq $t6,56,smallEight
	beq $t6,57,smallNine
bigNum:
	beq $t6,48,bigZero
	beq $t6,49,bigOne
	beq $t6,50,bigTwo
	beq $t6,51,bigThree
	beq $t6,52,bigFour
	beq $t6,53,bigFive
	beq $t6,54,bigSix
	beq $t6,55,bigSeven
	beq $t6,56,bigEight
	beq $t6,57,bigNine
smallZero:
	li $v0,4
	la $a0,zero
	syscall
	j num
bigZero:
	li $v0,4
	la $a0,zeroStart
	syscall
	j num	
smallOne:
	li $v0,4
	la $a0,one
	syscall
	j num
bigOne:
	li $v0,4
	la $a0,oneStart
	syscall
	j num	
smallTwo:
	li $v0,4
	la $a0,two
	syscall
	j num
bigTwo:
	li $v0,4
	la $a0,twoStart
	syscall
	j num
smallThree:
	li $v0,4
	la $a0,three
	syscall
	j num
bigThree:
	li $v0,4
	la $a0,threeStart
	syscall
	j num
smallFour:
	li $v0,4
	la $a0,four
	syscall
	j num
bigFour:
	li $v0,4
	la $a0,fourStart
	syscall
	j num
smallFive:
	li $v0,4
	la $a0,five
	syscall
	j num
bigFive:
	li $v0,4
	la $a0,fiveStart
	syscall
	j num
smallSix:
	li $v0,4
	la $a0,six
	syscall
	j num
bigSix:
	li $v0,4
	la $a0,sixStart
	syscall
	j num
smallSeven:
	li $v0,4
	la $a0,seven
	syscall
	j num
bigSeven:
	li $v0,4
	la $a0,sevenStart
	syscall
	j num
smallEight:
	li $v0,4
	la $a0,eight
	syscall
	j num
bigEight:
	li $v0,4
	la $a0,eightStart
	syscall
	j num
smallNine:
	li $v0,4
	la $a0,nine
	syscall
	j num
bigNine:
	li $v0,4
	la $a0,nineStart
	syscall
	j num
exit:
	jal fileClose
	li $v0 10
	syscall
