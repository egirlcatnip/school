.global memset

memset:
    mov x3, x0          // save pointer
1:
    cbz x2, 2f
    strb w1, [x0]
    add x0, x0, #1
    sub x2, x2, #1
    b 1b
2:
    mov x0, x3          // return original pointer
    ret
