// int fnzb(int x)


.global fnzb
// r0 = x

fnzb:
  clz r0, r0         // Count leading zeros
  sub r0, r0, #31    // r0 - 31 to get bit

  bx lr
