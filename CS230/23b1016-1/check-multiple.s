.text

main:
    li $s0, 3
    li $s1, 7
    slt $t0,$s1,$s0
    beq $t0, $zero, B2

    div $s0,$s1
    mfhi $t1 # remainder to $t1
    beq $t1, $zero, B12

    addi $s2, $zero, 0
    j EXIT

B12:
    addi $s2,$zero,1
    j EXIT

B2:
    div $s1,$s0
    mfhi $t2 # remainder to $t2
    beq $t2, $zero, B22

    addi $s2, $zero, 0
    j EXIT

B22:
    addi $s2,$zero,1
    j EXIT

EXIT: