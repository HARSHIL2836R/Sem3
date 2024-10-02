.data
A:    .word 10
B:    .word 8
C:    .word 0

.text
main:

    # 1a. Data Stall, 4. forwarding from MEM to ID stage

    lw r1, A(r0)
    beqz r1, brch # Stalls on ID stage for 2 cycles and exectures on last because r1 is available for forwarding in the MEM stage

    # 1b. Control Stall

    daddi r3, r0, 20 # Stalls for 2 cycles because it is not verified whether the branch is taken or not
    daddi r1, r0, 12
    slt r3,r3,r1

    # 2. Branch ID stall, 3. EX to ID forwarding
    bnez r3, brch # Stalls (RAW) in ID stage because data from slt is available to be forwarded from MEM stage 2.

    lw r2, C(r0)
    beqz r2, long_branch_1 

brch:
    daddi r3,r3,0

long_branch_1:
    dadd r1, r2, r3
    sw r5, A(r0)
    bnez r1, brch # 6. Maxmimum Possible data forwarding, across one cycle

    ddivu r1,r2,r3 # 7. WAW stall can be introduced using mult because it takes 7 cycles to complete while the addi instruction below can write after EX stage but is not able to 
    # 8. Structural stall happens because both ddivu and daddi wants to use DM in same cycle, but dmulu is allowed to use it first
    daddi r1,r2,1
    # 5. Maximum possible stalls are 6 because of WAW and Str Stalls

halt
