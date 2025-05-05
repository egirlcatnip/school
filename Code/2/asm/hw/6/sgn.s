// int sgn(int i)


.global sgn
// r0 = int i

sgn:
    cmp r0, #0
    bgt positive_case // If i > 0
    blt negative_case // If i < 0,
    beq zero_case     // If i == 0

    bx lr

positive_case:
    mov r0, #2
    bx lr

zero_case:
    mov r0, #0
    bx lr


negative_case:
    mov r0, #1
    bx lr

