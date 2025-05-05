// int my_strcmp(char *s1, char *s2)


.global my_strcmp
// r0 = char *s1
// r1 = char *s2

my_strcmp:
  cmp r0, #0         // Check if s1 is NULL
  beq exit  // If s1 is NULL, return 0
  cmp r1, #0         // Check if s2 is NULL
  beq exit  // If s2 is NULL, return 0

loop:
  ldrb r2, [r0], #1   // Load byte from s1 and increment s1
  ldrb r3, [r1], #1   // Load byte from s2 and increment s2
  cmp r2, r3          // Compare the bytes
  bne not_equal       // If not equal, branch to not_equal

  cmp r2, #0          // Check if end of string ("\0")
  beq exit   // If end of string, return 0

  b loop              // Continue loop

not_equal:
  sub r0, r2, r3      // Calculate difference
  // If r2 > r3, r0 = positive
  // If r2 < r3, r0 = negative
  bx lr

exit:
  mov r0, #0          // If r2 == r3, r0 = 0
  bx lr

