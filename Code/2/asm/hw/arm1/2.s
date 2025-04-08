.global fnzb              // first non-zero binary

fnzb:
    clz w1, w0            // count leading zeros
    cmp w1, #32
    csel w0, wzr, w0, eq
    sub w0, #31, w1       // index highest bit
    ret
