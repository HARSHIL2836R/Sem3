.data
A:  
    .word 0
    .word 1
    .word 2
    .word 3
    .word 4
    .word 5
    .word 6
    .word 7
    .word 8
    .word 9

prompt1: .asciiz "Enter the Element to search: "
.text
binarySearch:
    addiu $sp, $sp, -24
    sw $ra, 20($sp)

    lw $s0, 40($sp) #val
    lw $s1, 36($sp) #end
    lw $s2, 32($sp) #start
    lw $s3, 28($sp) #len
    lw $s4, 24($sp) #A

    slt $t0, $s1, $s0
    bne $t0, $0, ret_false # start>end* return -1

    move $s5, $s2 #s5 = start
    sub $t0, $s1, $s2 #t0 = end - start
    srl $t0,$t0,1 #t0 = (end-start)/2
    add $s5, $s5, $t0 #s5 = mid

    sll $t0, $s5, 2 #t0 = byte address for mid
    addu $s6, $s4, $t0 #s6 = A[mid]

    lw $t0, 0($s6)
    beq $t0, $s0, ret_mid

    slt $t0, $s0, $s6
    beq $t0, $0, lower
    bne $t0, $0, upper

upper:
    addi $t0, $s5, -1
    move $a3, $t0
    move $a2, $s2
    move $a1, $s3
    move $a0, $s4

    #Store Arguements
    sw $s0, 16($sp)
    sw $a3, 12($sp)
    sw $a2, 8($sp)
    sw $a1, 4($sp)
    sw $a0, 0($sp)
    jal binarySearch

    lw $s0, 16($sp)
    lw $a3, 12($sp)
    lw $a2, 8($sp)
    lw $a1, 4($sp)
    lw $a0, 0($sp)

    j EXIT

lower:
    addi $t0, $s5, 1
    move $a3, $s1
    move $a2, $t0
    move $a1, $s3
    move $a0, $s4

    #Store Arguements
    sw $s0, 16($sp)
    sw $a3, 12($sp)
    sw $a2, 8($sp)
    sw $a1, 4($sp)
    sw $a0, 0($sp)
    jal binarySearch

    lw $s0, 16($sp)
    lw $a3, 12($sp)
    lw $a2, 8($sp)
    lw $a1, 4($sp)
    lw $a0, 0($sp)
    
    j EXIT

ret_mid:
    move $v0, $s5
    j EXIT

ret_false:
    addi $v0, $0, -1
    j EXIT

EXIT:
    lw $ra, 20($sp)
    addiu $sp, $sp, 24
    jr $ra

main:
    addiu $sp, $sp, -24
    sw $ra, 20($sp)

    #prompt for input
	li $v0, 4
	la $a0, prompt1
	syscall

	#read the integer
	li $v0, 5
	syscall
	move $s0, $v0

    li $a3, 9 #store end index 2
    move $a2, $0
    li $a1, 10 #store length as 10
    la $a0, A

    #Store Arguements
    sw $s0, 16($sp)
    sw $a3, 12($sp)
    sw $a2, 8($sp)
    sw $a1, 4($sp)
    sw $a0, 0($sp)
    jal binarySearch

    move $t0, $v0 # Return value of function
    li $v0, 1 #print int
	move $a0, $t0
	syscall

    lw $ra, 20($sp)
    jr $ra