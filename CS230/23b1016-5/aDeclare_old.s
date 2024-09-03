.data
    A0R: .word 0
    .align 2
    A0I: .word 0
    .align 2
    A1R: .word -1
    .align 2
    A1I: .word 2
    .align 2
    A2R: .word 0
    .align 2
    A2I: .word 2
    .align 2
    A3R: .word -1
    .align 2
    A3I: .word -1
    .align 2

.text
main:
    #Add real and imaginary parts of A[2]
    lw $s0, A2I
    lw $s1, A2R
    add $s2, $s0, $s1