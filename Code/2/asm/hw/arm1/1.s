.global mul11

mul11:
    lsl x1, x0, #3      // x * 2^3  =  8x
    lsl x2, x0, #1      // x * 2^1  =  2x
    add x0, x0, x1      // x + x*8  =  9x
    add x0, x0, x2      // 2x + 9x  = 11x
    ret
