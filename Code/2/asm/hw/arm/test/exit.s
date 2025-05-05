.global _start

_start:
    mov r0, #69


_exit:
    // exit with code stored in r0
    mov r7, #1      // exit syscall
    svc 0           // syscall
