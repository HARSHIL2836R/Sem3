.data
	prompt1: .asciiz "Enter the first integer: "
	prompt2: .asciiz "Enter the second integer: "
	result: .asciiz "The Sum of the integers is: "
	bye: .asciiz "\nGoodbye!\n"
	.globl main

.text
main:
	#initialise
	li $s0, 1
	li $s1, 2

	#prompt for input
	li $v0, 4
	la $a0, prompt1
	syscall

	#read the integer
	li $v0, 5
	syscall
	move $s0, $v0

	#prompt for input
	li $v0, 4
	la $a0, prompt2
	syscall

	#read the integer
	li $v0, 5
	syscall
	move $s1, $v0

	add $s2, $s0, $s1

	#print the result
	li $v0, 4
	la $a0, result
	syscall

	li $v0, 1 #print int
	move $a0, $s2
	syscall

	#print goodbye
	li $v0, 4
	la $a0, bye
	syscall