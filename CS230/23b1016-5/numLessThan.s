A:
        .word   0
        .word   0
        .word   -1
        .word   2
        .word   0
        .word   2
        .word   -1
        .word   -1
len:
        .word   4
numLessThan:
        addiu $sp,$sp,-32

        sw $ra, 28($sp)
        sw $fp, 24($sp)
        move $fp, $sp

        sw $a0, 20($sp)
        sw $a1, 16($sp)
        sw $a2, 12($sp)
        sw $a3, 8($sp)

        sw $0, 4($sp) #MAIN Loop Counter

LOOP:

main:
        addiu $sp,$sp,-12 # Store ra,fp,len
        sw $ra, 8($sp)
        sw $fp, 4($sp)
        move $fp, $sp

        move $a0, $0 #X re
        move $a1, $0 #X im
        la $a2, A #A
        move $a3, $0 #start
        lw $v0, len
        sw $v0, 0($sp)

        jal numLessThan