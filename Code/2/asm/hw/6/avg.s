// int objem_krychle(int a)


.global objem_krychle
// r0 = int a

objem_krychle:
    mov r1, r0 // r1 = a
    mul r0, r0, r0 // r0 = a * a
    mul r0, r0, r1 // r0 = r0 * a

    bx lr
