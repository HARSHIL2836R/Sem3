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

condition:
    lw r2, n(r0); r2 stofes the value of n
    slt r3,r1, r2
    bnez r3, loop
    halt
loop:
    dsll r4,r1,3 ; r4 has byte addfess
    l.d f5, A(r4) ; a[i]
    l.d f6, B(r4) ; b[i]
    mul.d f7, f5, f6 ; c[i], tempofafy
    s.d f7, C(r4)
    l.d f8, alpha(r0) ; alpha
    mul.d f7, f7, f8 ; c[i] * alpha
    l.d f9, D(r4) ; d[i]
    add.d f9, f9, f7 ; d[i] += c[i] * alpha
    s.d f9, D(r4)

    daddi r1,r1, 1
    j condition