// int mul11(int x)


.global mul11
// r0 = x

mul11:
  add r1, r0, r0    // r1 = 2 * x
  add r2, r1, r1    // r2 = 4 * x
  add r2, r2, r2    // r2 = 8 * x
  add r1, r2, r1    // r1 = 10 * x
  add r0, r0, r1    // r0 = 11 * x

  bx lr
