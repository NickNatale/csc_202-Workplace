
.thumb
.global my_asm_16bitset
.global my_asm_16bitclr
.global my_asm_16bitcheck

my_asm_16bitset:
    orrs r0, r0, r1       // Perform bitwise OR with r1
    bx lr                // Return from the function

my_asm_16bitclr:
    bics r0, r0, r1       // Perform bitwise AND with r1
    bx lr                // Return from the function

my_asm_16bitcheck:
    ands r0, r0, r1       // Perform bitwise AND with the bitmask in r1
    bx lr                // Return from the function