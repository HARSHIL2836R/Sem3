A:
        .word   0
        .word   0
        .word   -1
        .word   2
        .word   0
        .word   2
        .word   -1
        .word   -1
len:
        .word   4
isLessThan:
        addiu   $sp,$sp,-8
        sw      $fp,4($sp)
        move    $fp,$sp
        sw      $4,8($fp)
        sw      $5,12($fp)
        sw      $6,16($fp)
        sw      $7,20($fp)
        lw      $3,8($fp)
        lw      $2,16($fp)
        nop
        slt     $2,$3,$2
        bne     $2,$0,$L2
        nop

        lw      $3,8($fp)
        lw      $2,16($fp)
        nop
        bne     $3,$2,$L3
        nop

        lw      $3,12($fp)
        lw      $2,20($fp)
        nop
        slt     $2,$3,$2
        beq     $2,$0,$L3
        nop

$L2:
        li      $2,1                        # 0x1
        b       $L5
        nop

$L3:
        move    $2,$0
$L5:
        move    $sp,$fp
        lw      $fp,4($sp)
        addiu   $sp,$sp,8
        jr      $31
        nop

numLessThan:
        addiu   $sp,$sp,-40
        sw      $31,36($sp)
        sw      $fp,32($sp)
        move    $fp,$sp
        sw      $4,40($fp)
        sw      $5,44($fp)
        sw      $6,48($fp)
        sw      $7,52($fp)
        sw      $0,24($fp)
        lw      $2,52($fp)
        nop
        sw      $2,28($fp)
        b       $L7
        nop

$L9:
        lw      $2,28($fp)
        nop
        sll     $2,$2,3
        lw      $3,48($fp)
        nop
        addu    $2,$3,$2
        lw      $6,40($fp)
        lw      $7,44($fp)
        lw      $4,0($2)
        lw      $5,4($2)
        jal     isLessThan
        nop

        beq     $2,$0,$L8
        nop

        lw      $2,24($fp)
        nop
        addiu   $2,$2,1
        sw      $2,24($fp)
$L8:
        lw      $2,28($fp)
        nop
        addiu   $2,$2,1
        sw      $2,28($fp)
$L7:
        lw      $3,28($fp)
        lw      $2,56($fp)
        nop
        bne     $3,$2,$L9
        nop

        lw      $2,24($fp)
        move    $sp,$fp
        lw      $31,36($sp)
        lw      $fp,32($sp)
        addiu   $sp,$sp,40
        jr      $31
        nop

main:
        addiu   $sp,$sp,-56
        sw      $31,52($sp)
        sw      $fp,48($sp)
        move    $fp,$sp
        li      $2,1                        # 0x1
        sw      $2,36($fp)
        li      $2,1                        # 0x1
        sw      $2,40($fp)
        lui     $2,%hi(len)
        lw      $2,%lo(len)($2)
        nop
        sw      $2,16($sp)
        move    $7,$0
        lui     $2,%hi(A)
        addiu   $6,$2,%lo(A)
        lw      $4,36($fp)
        lw      $5,40($fp)
        jal     numLessThan
        nop

        sw      $2,32($fp)
        move    $2,$0
        move    $sp,$fp
        lw      $31,52($sp)
        lw      $fp,48($sp)
        addiu   $sp,$sp,56
        jr      $31
        nop