.global _start

.section .data
message:
    .ascii "Hello, World!\n"
length = . - message

.section .text
_start:
    mov x8, #64         // syscall number for sys_write
    mov x0, #1          // file descriptor 1 (stdout)
    ldr x1, =message    // pointer to message
    mov x2, #length     // message length
    svc #0              // make syscall

_exit:
    mov x8, #93         // syscall number for sys_exit
    mov x0, #0          // exit code 0
    svc #0              // make syscall
