.data
    A: .double 1.0, 2.0, 3.0, 4.0, 5.0, 6.0
    B: .double 2.0, 3.0, 4.0, 5.0, 6.0, 7.0
    C: .double 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    D: .double 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    n: .word 6
    alpha: .double 10.0

.text
main:
    daddi r1, r0, 0 ; r1 stores the value of i
    j condition

loop:
    dsll r4,r1,3 ; r4 has byte address
    l.d f5, A(r4) ; a[i]
    l.d f6, B(r4) ; b[i]
    l.d f8, alpha(r0) ; alpha
    mul.d f7, f5, f6 ; c[i], temporary, 1 RAW Stall at M0 removed 
    l.d f9, D(r4) ; d[i]
    s.d f7, C(r4) ; 1 RAW at ID removed and 4 RAW at EX (1 removed) and 1 Str at EX (mul.d in MEM stage)
    mul.d f7, f7, f8 ; c[i] * alpha, 5 WAR at ID introduced/ corresponding to 5 stalls above
    add.d f9, f9, f7 ; d[i] += c[i] * alpha, 6 RAW at A0
    s.d f9, D(r4) ; 6 RAW at ID, 2 RAW at EX, 1 Str at EX

    daddi r1,r1, 1

condition:
    lw r2, n(r0); r2 stofes the value of n
    slt r3,r1, r2 ; 1 RAW Stall at EX
    bnez r3, loop ; 1 RAW Stall at ID
    halt

; TOTAL Cycles reduced from 211 to 199