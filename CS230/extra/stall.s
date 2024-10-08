.data
A: .word 10
.text
lw r1, A(r0)
dadd r2, r1, r3
dsub r3,r3,r3
halt