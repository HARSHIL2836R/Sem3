.text
main:
	#initialise
	li $s0, 1
	li $s1, 2

	#read the integer
	li $v0, 5
	syscall
	move $s0, $v0

	#read the integer
	li $v0, 5
	syscall
	move $s1, $v0

	add $s2, $s0, $s1

	li $v0, 1 #print int
	move $a0, $s2
	syscall