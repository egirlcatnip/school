.global strcmp

strcmp:
1:
    ldrb w2, [x0], #1
    ldrb w3, [x1], #1
    cmp w2, w3
    b.ne 2f
    cbz w2, 3f
    b 1b
2:
    sub w0, w2, w3
    ret
3:
    mov w0, #0
    ret
