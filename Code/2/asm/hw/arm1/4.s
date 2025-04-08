.global strlen
strlen:
    mov x1, #0
1:
    ldrb w2, [x0, x1]
    cbz w2, 2f
    add x1, x1, #1
    b 1b
2:
    mov x0, x1
    ret
