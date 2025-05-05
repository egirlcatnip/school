// int obvod_trojuhelnika(int a, int b, int c)


.global obvod_trojuhelnika
// r0 = int a
// r1 = int b
// r2 = int c

obvod_trojuhelnika:
    add r0, r0, r1 // r0 = a + b
    add r0, r0, r2 // r0 = r0 + c

    bx lr
