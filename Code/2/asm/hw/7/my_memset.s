// int *my_memset(void *s, int c, size_t n)


.global my_memset
// r0 = void *s
// r1 = int c
// r2 = size_t n

my_memset:
  cmp r2, #0
  beq exit

  mov r3, r2         // r3 = n
  lsl r3, r3, #2     // r3 = n * sizeof(int)
  add r3, r0, r3     // r3 = s + n * sizeof(int)

loop:
  str r1, [r0], #4   // Store c at s and increment s by sizeof(int)
  cmp r0, r3         // Compare s with end address
  blt loop           // If s < end address, continue loop

exit:
  bx lr
