.data

intList: .word 23, 15, 7, 22, 8, 18, 6, 24, 3, 17, 29, 13 #works with arrays with 4n length
tempList: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 #temporary array with the same length
length: .word 12

output: .asciiz "The list after sorting: \n"
space: .asciiz " "
enter: .asciiz "\n"
notOrdered: .asciiz "The order before sorting the list:\n"
ordered: .asciiz "The order after sorting the list:\n"
indexStart: .asciiz "Index start: "
indexEnd: .asciiz "Index end: "

.text
.globl main
.globl thread

main:
    
    li $v0,4
    la $a0,notOrdered
    syscall

    la $t1,intList
    move $t0,$zero

    la $t3,length
    lw $t3,0($t3)
    addi $t3,$t3,-1

    before:

        lw $t2,0($t1)

        li $v0,1
        move $a0,$t2
        syscall

        li $v0,4
        la $a0,space
        syscall

        addi $t1,$t1,4
        addi $t0,$t0,1
        ble $t0,$t3, before

    li $v0,4
    la $a0,enter
    syscall

    li $v0,4
    la $a0,enter
    syscall

    li $s0,0
    li $s1,4

    la $s2,length
    lw $s2,0($s2)
    div $s2,$s1
    mflo $s2

    li $s3,1

    loop:
        addi $sp,$sp,-1000
        li $v0,18
        move $a1,$s1
        mult $s0,$s2
        mflo $a2
        addi $s0,$s0,1
        move $a0,$s0
        mult $s0,$s2
        mflo $a3
        addi $a3,$a3,-1
        move $s4,$s0
        syscall
        blt $s0,$s1,loop

    li $s0,0

    stackLoop:

        addi $sp,$sp,1000
        addi $s0,$s0,1
        blt $s0,$s1,stackLoop

    join0:

        li $v0,19
        li $a0,1
        syscall

        beq $a1,$zero,join0

    join1:

        li $v0,19
        li $a0,2
        syscall

        beq $a1,$zero,join1

    join2:

        li $v0,19
        li $a0,3
        syscall

        beq $a1,$zero,join2

    join3:

        li $v0,19
        li $a0,4
        syscall

        beq $a1,$zero,join3

    li $s0,0

    mult $s0,$s2
    mflo $t0
    addi $s0,$s0,1
    mult $s0,$s2
    mflo $t1
    addi $t1,$t1,-1

    mult $s0,$s2
    mflo $t2
    addi $s0,$s0,1
    mult $s0,$s2
    mflo $t3
    addi $t3,$t3,-1

    jal Merge

    mult $s0,$s2
    mflo $t0
    addi $s0,$s0,1
    mult $s0,$s2
    mflo $t1
    addi $t1,$t1,-1

    mult $s0,$s2
    mflo $t2
    addi $s0,$s0,1
    mult $s0,$s2
    mflo $t3
    addi $t3,$t3,-1

    jal Merge

    li $s0,0

    mult $s0,$s2
    mflo $t0
    addi $s0,$s0,2
    mult $s0,$s2
    mflo $t1
    addi $t1,$t1,-1

    mult $s0,$s2
    mflo $t2
    addi $s0,$s0,2
    mult $s0,$s2
    mflo $t3
    addi $t3,$t3,-1

    jal Merge

    li $v0,4
    la $a0,ordered
    syscall

    la $t1,intList
    move $t0,$zero

    la $t3,length
    lw $t3,0($t3)
    addi $t3,$t3,-1

    after:

        lw $t2,0($t1)

        li $v0,1
        move $a0,$t2
        syscall

        li $v0,4
        la $a0,space
        syscall

        addi $t1,$t1,4
        addi $t0,$t0,1
        ble $t0,$t3, after

    li $v0,4
    la $a0,enter
    syscall

    li $v0,10
    syscall

thread:

    move $t0,$a2
    move $t3,$a3
    jal MergeSort
    li $v0,20
    move $a0,$s4
    syscall

junk:
    j junk

MergeSort:

    ble $t3,$t0, NotRecursion
    addi $sp,$sp,-12
    sw $ra,8,($sp)
    sw $t0,0($sp)
    sw $t3,4($sp)
    add $t3,$t0,$t3
    li $t2,2
    div $t3,$t2
    mflo $t3
    jal MergeSort
    lw $t0,0($sp)
    lw $t3,4($sp)
    add $t0,$t0,$t3
    li $t2,2
    div $t0,$t2
    mflo $t0
    addi $t0,$t0,1
    jal MergeSort
    lw $t0,0($sp)
    lw $t3,4($sp)
    add $t1,$t0,$t3
    li $t2,2
    div $t1,$t2
    mflo $t1
    addi $t2,$t1,1
    jal Merge
    lw $ra,8($sp)
    addi $sp,$sp,12

NotRecursion:
    jr $ra
    
Merge:

    add $t6,$zero,$zero
    la $t7,intList
    la $t8,tempList
    blt $t6,$t0,NotThere
    j There
    NotThere:
        addi $t6,$t6,1
        addi $t7,$t7,4
        addi $t8,$t8,4
        blt $t6,$t0,NotThere
    There:
        lw $t9,0($t7)
        sw $t9,0($t8)
        addi $t7,$t7,4
        addi $t8,$t8,4
        addi $t6,$t6,1
        ble $t6,$t3,There
    la $t4, tempList
    la $t6, intList
    move $t8,$zero
    blt $t8,$t0,FirstIndex
    j FirstIndexed
    FirstIndex:
        addi $t4,$t4,4
        addi $t6,$t6,4
        addi $t8,$t8,1
        blt $t8,$t0,FirstIndex
    FirstIndexed:
    move $t5,$t4
    #move $t7,$t6
    SecondIndex:
        addi $t5,$t5,4
        #addi $t7,$t7,4
        addi $t8,$t8,1
        blt $t8,$t2,SecondIndex
    Loop:
        lw $t8,0($t4)
        lw $t9,0($t5)
        blt $t9,$t8,If
        j Else
        EndIf:
            blt $t1,$t0,EndLoop
            blt $t3,$t2,EndLoop
            j Loop
    EndLoop:
    ble $t0,$t1,LeftLoop
    ble $t2,$t3,RightLoop
    EndMerge:
    jr $ra

If:
    sw $t9,0($t6)
    addi $t5,$t5,4
    addi $t2,$t2,1
    addi $t6,$t6,4
    j EndIf

Else:
    sw $t8,0($t6)
    addi $t4,$t4,4
    addi $t6,$t6,4
    addi $t0,$t0,1
    j EndIf

LeftLoop:
    lw $t8,0($t4)
    sw $t8,0($t6)
    addi $t4,$t4,4
    addi $t6,$t6,4
    addi $t0,$t0,1
    ble $t0,$t1,LeftLoop
    j EndMerge

RightLoop:
    lw $t9,0($t5)
    sw $t9,0($t6)
    addi $t5,$t5,4
    addi $t6,$t6,4
    addi $t2,$t2,1
    ble $t2,$t3,RightLoop
    j EndMerge

