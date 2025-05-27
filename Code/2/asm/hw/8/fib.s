// void fib(int n)

.global _start
_start:
  mov r0, #10          // Example input for Fibonacci
  bl fib               // Call fib function

  b exit

.global fib
// r0 = n

fib:
  mov r3, lr           // save return address
  b loop

  bx lr


loop:
  cmp r0, #0
  beq case_zero         // If n == 0, return 0

  cmp r0, #1
  beq case_one          // If n == 1, return 1
  cmp r0, #2
  beq case_one          // If n == 2, return 1

  b case_other          // If n > 2, calculate fib(n-1) + fib(n-2)


case_zero:
  mov r0, #0           // fib(0) = 0
  b exit_fib

case_one:
  mov r0, #1           // fib(1) = 1
  b exit_fib

case_other:
  sub r0, r0, #1       // n - 1
  bl fib               // fib(n-1)
  mov r4, r0           // Save result of fib(n-1) in r4

  sub r0, r0, #2       // n - 2
  bl fib               // fib(n-2)
  add r0, r0, r4       // fib(n) = fib(n-1) + fib(n-2)

  b exit_fib

exit_fib:
  bx r3                // Return to saved address

exit:
  mov r7, #1          // syscall number for exit
  svc 0               // make syscall to exit
