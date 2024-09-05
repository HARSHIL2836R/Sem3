main:
li $s0, 0x7fffffff
li $s1, 0x7fffffff
addu $s2, $s0,$s1
add $s3, $s0,$s1 # Gives no exception