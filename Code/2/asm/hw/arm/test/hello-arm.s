.global _start

.section .data
message:
    .ascii "Hello, World!\n"
length = . - message

.section .text
_start:
    mov r7, #4          // syscall number for sys_write
    mov r0, #1          // file descriptor 1 (stdout)
    ldr r1, =message    // pointer to message
    mov r2, #length     // message length
    svc 0               // make syscall

_exit:
    mov r7, #1          // syscall number for sys_exit
    mov r0, #0          // exit code 0
    svc 0               // make syscall
