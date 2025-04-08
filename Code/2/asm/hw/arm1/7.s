.global minimum

minimum:
    cbz w0, end
    mov x2, #1
    ldr w1, [x1]
1:
    cmp x2, x0
    b.ge end
    ldr w3, [x1, x2, lsl #2]
    cmp w3, w1
    csel w1, w3, w1, lt
    add x2, x2, #1
    b 1b
end:
    mov w0, w1
    ret
