// void fact_tc(int n)

.global _start
_start:
  mov r0, #10          // fact_tc(10)
  bl fact_tc

  b exit

.global fact_tc
// r0 = n

fact_tc:
  mov r3, lr           // save return address
  b loop

  bx lr

  loop:
    cmp r0, #0
    beq case_zero         // If n == 0, return 1

    cmp r0, #1
    beq case_one          // If n == 1, return 1

    b case_other          // If n > 1, calculate fact(n-1) * n

case_zero:
    mov r0, #1           // fact(0) = 1
    b exit_fact_tc

case_one:
    mov r0, #1           // fact(1) = 1
    b exit_fact_tc

case_other:
    sub r0, r0, #1       // n - 1
    bl fact_tc           // fact(n-1)
    mul r0, r0, r1       // fact(n) = fact(n-1) * n

    b exit_fact_tc

exit_fact_tc:
    bx r3                // Return to saved address
