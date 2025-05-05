// int my_strlen(char *s)


.global my_strlen
// r0 = char *s

my_strlen:
  mov r1, r0          // r1 = s
  mov r0, #0          // Initialize result to 0

loop:
  ldrb r2, [r1], #1   // load byte from s and increment s
  cmp r2, #0          // check if end of string ("\0")
  beq exit_loop

  add r0, r0, #1      // increment length
  b loop              // repeat

exit_loop:
  bx lr               // return length in r0
