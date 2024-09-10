.data
    num: .word 4
.text
factorial:
    addiu $sp, $sp, -20
    sw $ra, 16($sp)

    lw $t0, 20($sp)
    addiu $t0, $t0, -1
    beq $t0, $0, ret_1 #If argument is 1, return 1

    addiu $a0, $a0, -1 
    sw $a0, 0($sp)
    jal factorial # Call function to get the return value in v0

    lw $t1, 20($sp)
    mul $t1, $t1, $v0
    move $v0, $t1
    lw $ra, 16($sp)
    addiu $sp, $sp, 20
    jr $ra

ret_1:
    addi $t1, $0, 1
    move $v0, $t1 # Save the return value to 1 and Jump back sqeuentially
    lw $ra, 16($sp)
    jr $ra

main:
    addiu $sp, $sp, -8
    sw $ra, 4($sp)
    lw $s0, num
    move $a0,$s0
    sw $a0, 0($sp)
    jal factorial