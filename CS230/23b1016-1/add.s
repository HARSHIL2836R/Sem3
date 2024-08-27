# Reinitialise and load file
.text

main:

# Add 0x20000001 and 0x10000002
lui $t0, 0x2000
ori $t1, $t0, 1
lui $t2, 0x1000
ori $t3, $t2, 2
add $s0, $t1, $t3