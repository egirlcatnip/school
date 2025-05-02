// obvod_trojuhelnika
obvod_trojuhelnika:
    add r0, r0, r1
    add r0, r0, r2
    bx lr

// objem_krychle
objem_krychle:
    mov r1, r0        // Move a into r1
    mul r0, r1, r0    // r0 = a * a
    bx lr

// avg
avg:
    add r0, r0, r1
    add r0, r0, r2
    mov r1, #3
    udiv r0, r0, r1
    bx lr

// sgn
sgn:
    cmp r0, #0
    movlt r0, #-1
    moveq r0, #0
    movgt r0, #1
    bx lr

// min3u
min3u:
    cmp r0, r1
    movhi r0, r1
    cmp r0, r2
    movhi r0, r2
    bx lr

// fact
fact:
    cmp r0, #0
    moveq r0, #1
    bxeq lr
    push {r1, lr}
    mov r1, r0
    sub r0, r0, #1
    bl fact
    mul r0, r1, r0
    pop {r1, pc}

// mocnina
mocnina:
    cmp r1, #0
    moveq r0, #1
    bxeq lr
    push {r2, r3, lr}
    mov r2, r0
    mov r3, #1
mocnina_loop:
    mul r3, r2, r3
    subs r1, r1, #1
    bne mocnina_loop
    mov r0, r3
    pop {r2, r3, pc}
