.data
    arr:
        .word 0
        .align 2
        .word 0
        .align 2
        .word -1
        .align 2
        .word 2
        .align 2
        .word 0
        .align 2
        .word 2
        .align 2
        .word -1
        .align 2
        .word -1
        .align 2
    len: .word 4

.text
main:
    #Add real and imaginary parts of A[2]
    la $s0, arr #Load Address
    lw $t0, 16($s0)
    lw $t1, 20($s0)
    add $s1, $t0, $t1
