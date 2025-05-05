// void multiples(short *shorts, short n)


.global multiples
// r0 = short shorts[]
// r1 = short n

multiples:
  bl mul_loop
  bx lr

mul_loop:
  mov r2 ,#1                  // counter
  mov r3 ,#1                  // multiple
  mov r4 ,lr                  // save return address of multiples

loop:
  cmp r2, #10                 // check if counter == 10
  beq exit_loop               // if yes, return to multiples

  mul r3, r2, r1              // r3 = multiple * n
  strh r3, [r0, r2, lsl #1]   // shorts[counter] = r3
  add r2, #1                  // increment counter

  b loop                      // repeat the loop

exit_loop:
  b r4                        // return to saved address

