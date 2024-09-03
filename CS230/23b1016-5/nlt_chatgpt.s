# Data Section
.data
prompt1: .asciiz "Enter the Real part: "
prompt2: .asciiz "Enter the Imaginary part: "
result: .asciiz "Numbers in array less than given element is: "

A:
        .word   0           # A[0].re
        .word   0           # A[0].im
        .word   -1          # A[1].re
        .word   2           # A[1].im
        .word   0           # A[2].re
        .word   2           # A[2].im
        .word   -1          # A[3].re
        .word   -1          # A[3].im
len:
        .word   4           # Number of complex numbers in array

.text
# isLessThan Function
# Arguments: $a0 = x_re, $a1 = x_im, $a2 = el_re, $a3 = el_im
isLessThan:
        addiu   $sp, $sp, -8       # Allocate space on stack
        sw      $fp, 4($sp)        # Save old frame pointer
        move    $fp, $sp           # Set up new frame pointer

        sw      $a0, 8($fp)        # Save $a0 (x real) to stack
        sw      $a1, 12($fp)       # Save $a1 (x im) to stack
        sw      $a2, 16($fp)       # Save $a2 (el real) to stack
        sw      $a3, 20($fp)       # Save $a3 (el im) to stack

        lw      $v1, 8($fp)        # Load x real into $v1
        lw      $v0, 16($fp)       # Load el real into $v0
        
        slt     $v0, $v0, $v1      # $v0 = (el real < x real)
        bne     $v0, $zero, real_is_less    # If el re < x re, branch to real_is_less

        lw      $v1, 8($fp)        # Load x real into $v1
        lw      $v0, 16($fp)       # Load el real into $v0

        bne     $v1, $v0, false_out      # If x real != el real, branch to false_out

        lw      $v1, 12($fp)       # Load x im into $v1
        lw      $v0, 20($fp)       # Load el im into $v0

        slt     $v0, $v0, $v1      # $v0 = (el im < x im)
        beq     $v0, $zero, false_out    # If el im >= x im, branch to false_out

real_is_less:
        li      $v0, 1             # Return 1 (true)
        b       restore_and_return

false_out:
        move    $v0, $zero         # Return 0 (false)

restore_and_return:
        move    $sp, $fp           # Restore stack pointer
        lw      $fp, 4($sp)        # Restore frame pointer
        addiu   $sp, $sp, 8        # Deallocate stack space
        jr      $ra                # Return to caller

# numLessThan Function
# Arguments: $a0 = X1, $a1 = X2, $a2 = Array base address, $a3 = Array length, 16($sp) = len
numLessThan:
        addiu   $sp, $sp, -40      # Allocate space on stack
        sw      $ra, 36($sp)       # Save return address
        sw      $fp, 32($sp)       # Save old frame pointer
        move    $fp, $sp           # Set up new frame pointer

        sw      $a0, 40($fp)       # Save $a0 (X real) to stack
        sw      $a1, 44($fp)       # Save $a1 (X im) to stack
        sw      $a2, 48($fp)       # Save $a2 (array base) to stack
        sw      $a3, 52($fp)       # Save $a3 (length) to stack

        sw      $0, 28($fp)       # Save index to stack

        sw      $zero, 24($fp)     # Initialize count to 0
        b       while_condition    # Jump to while condition

while_loop:
        lw      $v0, 28($fp)       # Load current index into $v0

        sll     $v0, $v0, 3        # Multiply index by 8 (2 words)
        lw      $v1, 48($fp)       # Load base address into $v1, not using a2 because we're going to call another function

        addu    $v0, $v1, $v0      # Calculate address of number
        lw      $a2, 0($v0)        # Load real part
        lw      $a3, 4($v0)        # Load imaginary part

        lw      $a0, 40($fp)       # x's real part
        lw      $a1, 44($fp)       # x's imaginary part
        jal     isLessThan         # Call isLessThan(x, A[i])

        beq     $v0, $zero, dont_increment_count    # If result is 0, skip incrementing

        lw      $v0, 24($fp)       # Load count into $v0
        addiu   $v0, $v0, 1        # Increment count
        sw      $v0, 24($fp)       # Store updated count

dont_increment_count:
        lw      $v0, 28($fp)       # Load index
        addiu   $v0, $v0, 1        # Increment index
        sw      $v0, 28($fp)       # Store updated index

while_condition:
        lw      $v1, 28($fp)       # Load current index
        lw      $v0, 56($fp)       # Load length

        bne     $v1, $v0, while_loop      # If index != length, loop

        lw      $v0, 24($fp)       # Load count into $v0, to transfer to main
        move    $sp, $fp           # Restore stack pointer
        lw      $ra, 36($sp)       # Restore return address
        lw      $fp, 32($sp)       # Restore frame pointer
        addiu   $sp, $sp, 40       # Deallocate stack space

        jr      $ra                # Return to caller

# main Function
main:
        addiu   $sp, $sp, -56      # Allocate 56 byte space on stack
        sw      $ra, 52($sp)       # Save return address
        sw      $fp, 48($sp)       # Save old frame pointer
        move    $fp, $sp           # Set up new frame pointer

	li      $v0, 4             # prompt for input
	la      $a0, prompt1
	syscall

	li      $v0, 5	           # read the integer
	syscall
        sw      $v0, 36($fp)       # Save x re to stack

	li      $v0, 4             # prompt for input
	la      $a0, prompt2
	syscall

	li      $v0, 5	           # read the integer
	syscall
        sw      $v0, 40($fp)       # Save X im to stack

        lw      $v0, len           # Load len into $v0
        sw      $v0, 16($sp)       # Save len to stack

        move    $a3, $zero         # Initialize $a3 to 0
        la      $a2, A             # Load base address of A into $a2
        lw      $a1, 40($fp)       # Load X2 into $a1
        lw      $a0, 36($fp)       # Load X1 into $a0
        jal     numLessThan        # Call numLessThan(X1, X2, A, len)

        sw      $v0, 32($fp)       # Save result of numLessThan
	li      $v0, 4             # print the result
	la      $a0, result
	syscall

        li      $v0, 1             # print int
        lw      $t0, 32($fp)
	move    $a0, $t0
	syscall

        move    $v0, $zero         # Clear $v0
        move    $sp, $fp           # Restore stack pointer
        lw      $ra, 52($sp)       # Restore return address
        lw      $fp, 48($sp)       # Restore frame pointer
        addiu   $sp, $sp, 56       # Deallocate stack space
        jr      $ra                # Return to caller
