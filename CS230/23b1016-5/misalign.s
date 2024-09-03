.data
    str1: 
        .asciiz "abc"
        .asciiz "defgh"

    str2:
        .asciiz "abc"
        .align 4 # Reserves a 16 bit block for the string
        .asciiz "defgh"
        .align 4
        .asciiz "defgh"
        .align 4
        .asciiz "ij"

# Data Segment:
#[10010000]    00636261  67666564  62610068  00000063    a b c . d e f g h . a b c . . . 
#[10010010]    67666564  00000068  00000000  00000000    d e f g h . . . . . . . . . . . 
#[10010020]    67666564  00000068  00000000  00000000    d e f g h . . . . . . . . . . . 
#[10010030]    00006a69  00000000  00000000  00000000    i j . . . . . . . . . . . . . . 