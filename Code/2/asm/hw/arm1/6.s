.global multiples

multiples:
    mov x2, #0
1:
    cmp x2, #10
    b.ge 2f
    mul w3, w1, w2
    strh w3, [x0, x2, lsl #1]
    add x2, x2, #1
    b 1b
2:
    ret
