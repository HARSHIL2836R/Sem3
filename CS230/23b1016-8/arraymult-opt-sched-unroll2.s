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
    daddi r5, r4, 8
    l.d f5, A(r4) ; a[i]
    l.d f6, B(r4) ; b[i]
    mul.d f7, f5, f6 ; c[i], temporary, 1 RAW at M0
    l.d f10, A(r5) ; a[i]2
    l.d f11, B(r5) ; b[i]2
    mul.d f12, f10, f11 ; c[i], temporary, 1 RAW at M0
    s.d f7, C(r4) ;  3 RAW at EX, 1 Str at EX
    l.d f8, alpha(r0) ; alpha
    mul.d f7, f7, f8 ; c[i] * alpha, 1 RAW at M0
    s.d f12, C(r5) ; 
    l.d f13, alpha(r0) ; alpha2
    mul.d f12, f12, f13 ; c[i] * alpha2
    l.d f9, D(r4) ; d[i]
    add.d f9, f9, f7 ; d[i] += c[i] * alpha, 3 RAW at A0
    l.d f14, D(r5) ; d[i]2
    add.d f14, f14, f12 ; d[i] += c[i] * alpha2,2 RAW at A0
    s.d f9, D(r4) ; 2 Str at EX
    daddi r1, r1, 2
    s.d f14, D(r5) ;

condition:
    lw r2, n(r0); r2 stofes the value of n
    slt r3,r1, r2 ; 1 RAW Stall at EX
    bnez r3, loop ; 1 RAW Stall at ID
    halt

; Total cycles reduced from 193 to 121 by interspersing instructions