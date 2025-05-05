// int avg(int a, int b, int c)


.global avg
// r0 = int a
// r1 = int b
// r2 = int c

avg:
    add r0, r0, r1 // r0 = a + b
    add r0, r0, r2 // r0 = r0 + c
    mov r1, #3     // r1 = 3
    udiv r0, r0, r1 // r0 = (a + b + c) / 3

    bx lr
