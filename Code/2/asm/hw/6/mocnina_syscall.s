// int mocnina(int m, unsigned int n)


.global _start
// r0 = int m
// r1 = unsigned int n

_start:
  ldr r0, =5        // m = 5
  ldr r1, =3        // n = 3
  bl mocnina        // test with mocnina(5, 3) = 125
  b exit

.global mocnina
// r0 = m
// r1 = n

mocnina:
  cmp r1, #1
  beq one_case        // m^1 = m

  cmp r1, #0
  beq zero_case       // m^0 = 1

  blt negative_case   // n < 0, return 0, unsupported
  bgt positive_case   // n > 1, calculate m^n

  bx lr

zero_case:
  mov r0, #1
  bx lr

one_case:
  // r0 is already m
  bx lr

negative_case:
  mov r0, #0         // return 0 for negative exponent
  bx lr

positive_case:
  mov r2, r1         // copy n to r2
  mov r1, r0         // save m in r1
  mov r0, #1         // initialize result to 1
  mov r3, lr         // save return address of mocnina

loop:
  cmp r2, #0
  beq exit_loop

  mul r0, r1, r0     // result *= m
  sub r2, r2, #1     // decrement counter
  b loop

exit_loop:
  bx r3

exit:
  mov r7, #1      // exit syscall
  svc 0           // syscall


