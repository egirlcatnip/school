// int fact(int i)


.global fact
// r0 = int i

fact:
  cmp r0, #1
  beq zero_one_case // If i == 1
  cmp r0, #0
  beq zero_one_case // If i == 0

  blt negative_case // If i < 0,
  bgt positive_case // If i > 0

  bx lr

zero_one_case:
  mov r0, #1 // fact(0) = 1
  bx lr

negative_case:
  mov r0, #0 // fact(i) = 0 for i < 0
  bx lr

positive_case:
  mov r1, r0       // save i in r1
  mov r0, #1       // initialize result to 1
  mov r2, lr       // save return address of fact

loop:
  cmp r1, #1       // check if counter is 1
  beq exit_loop    // if yes, return to fact

  mul r0, r1, r0   // multiply i by counter
  sub r1, r1, #1   // decrement counter

  b loop           // repeat

exit_loop:
 bx r2            // return to saved address

