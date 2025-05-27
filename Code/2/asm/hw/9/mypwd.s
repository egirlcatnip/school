// mypwd

.section .data
buffer:     .space 256
bufsize:    .word 256

.section .text
.global _start

_start:
    mov r0, r4         // r0 = buffer address
    ldr r1, =buffer    // get address of buffer
    ldr r2, =256       // size of buffer
    mov r7, #183       // syscall number for getcwd
    svc #0             // syscall: getcwd(buffer, size)

    cmp r0, #0
    blt exit           // if error, exit

    mov r1, r0         // r1 = buffer address
    mov r0, #1         // stdout
    bl get_strlen
    mov r2, r0         // r2 = length
    mov r0, #1         // stdout
    mov r7, #4         // syscall number for write
    svc #0

exit:
    mov r0, #0
    mov r7, #1         // syscall number for exit
    svc #0

get_strlen:
    push {r1, r2, r3, lr}
    mov r2, r1
strlen_loop:
    ldrb r3, [r2], #1
    cmp r3, #0
    bne strlen_loop
    sub r0, r2, r1
    pop {r1, r2, r3, lr}
    bx lr
