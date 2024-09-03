	.data
prompt:	.asciiz "Enter in an integer: " #directive asciiz creates a null terminated string
str1:	.asciiz "the answer is: "
newline: .asciiz	"\n"
bye:	.asciiz	"Goodbye!\n"
	.globl	main
	
	.text
main:
    #I/O is done in SPIM using the syscall opcode. For each I/O operation, a specific value is placed(li) in the $2 register (also referred to as $v0).
	# initialize 
	li	$s0, 10
	
	# prompt for input
	li	$v0, 4 #Syscall code for printing the string
	la	$a0, prompt #Store the address of string prompt in a0
	syscall #print the string "Enter in an integer: "

	# read in the value
	li	$v0, 5 #Read the integer in v0
	syscall
	move 	$s0, $v0 #Move the integer read from v0 to s0

	
loop:
	# print str1
	li	$v0, 4 
	la	$a0, str1
	syscall #Print "the answer is: "

	# print loop value
	li	$v0, 1 #print integer
	move	$a0, $s0
	syscall #Print value of a0

	# print newline
	li	$v0, 4
	la	$a0, newline
	syscall

	# decrement loop value and branch if not negative
	sub	$s0, $s0, 1
	bgez	$s0, loop

	# print goodbye message
	li	$v0, 4
	la	$a0, bye
	syscall


