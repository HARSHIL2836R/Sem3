# IMPORTANT: DO NOT EDIT eratosthenes-original.s
# Make any changes in eratosthenes.s

.data

CR: .word32 0x10000
DR: .word32 0x10008
# Create space corresponding to NMAX 64-bit integers
A: .space 144

# Map A to R1, i to R2, N to R3, running_multiplier to R4
# R5, R6 are used for different purposes in different parts of the code
# R10 is CR, R11 is DR - for printing, in winmips64 - see sample code in testio.s
# R12 is to be used for counting number of nop-s

.text

main:

daddi   R12, R0, 0  # nop count is initialized to 0
daddi	R1, R0, A   # Initialize A
daddi   R3, R0, 18  # Initialize N

daddi   R2, R0, 0   # i=0

sltu	R5, R2, R3
daddi   R6, R0, 1   # Value to store onto A[i], scheduled here to save 1 RAW stall
beqz    R5, EXIT1
nop #

LOOP1:
dsll    R5, R2, 3   # i*8
sd      R6, A(R5)   # A[i] = 1
daddi   R2, R2, 1   # i++

dsll    R5, R2, 3   # i*8
daddi   R2, R2, 1   # i++

sltu	R7, R2, R3  # R5 renamed to R7 to enable scheduling
sd      R6, A(R5)   # A[i] = 1
bnez    R7, LOOP1
nop #

EXIT1:

lwu     R10, CR(R0) # Control Register
lwu     R11, DR(R0) # Data Register

daddi   R2, R0, 2   # i = 2
LOOP2:
slt     R5, R2, R3  # R5 = (i < N)
beqz    R5, EXIT2
nop #

dsll    R5, R2, 3   # i*8
ld      R5, A(R5)   # R5 is now A[i]
sd      R2, (R11)   # Prepare DR to print i, move up to save 2 RAWs
daddi   R6, R0, 1   # To print integer, moved up to save 2 RAWs
beqz    R5, ELSEPART
nop #

sd      R6, (R10)   # CR=1 to print integer

daddi   R4, R0, 2   # running_multiplier=2

    INNER_LOOP:
        dmul    R5, R2, R4  # R5=running_multiplier*i
        slt     R6, R5, R3  # R6=(R5<N)
        daddi   R4, R4, 1   # running_multiplier++ # moved up to reduce 1 RAW
        beqz    R6, INNER_EXIT
        nop #

        dsll    R6, R5, 3   # R5*8
        sd      R0, A(R6)   # A[R5] = 0
        j       INNER_LOOP
        nop #

    INNER_EXIT:
        # Nothing to do here

ELSEPART:
daddi   R2, R2, 1   # i++
j       LOOP2
nop #

EXIT2:
halt
