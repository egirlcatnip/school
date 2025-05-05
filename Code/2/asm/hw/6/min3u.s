// unsigned short min3u(int a, int b, int c)


.global min3u
// r0 = int a
// r1 = int b
// r2 = int c

min3u:
    cmp r0, r1
    blt a_lt_b // If a < b

    cmp r0, r2
    blt a_lt_c // If a < c

    // If a is smallest, no need to do anything
    // r0 already contains a

    bx lr

a_lt_b:
    mov r0, r1 // set a to b
    bx lr

b_lt_c:
    mov r0, r2 // set a to c
    bx lr

