// lc


.global _start

_start:
  mov r0, #5          // rows
  mov r1, #20         // columns
  bl lc

  b exit

.global lc
lc:
  /*  */

exit:
  mov r0, #0          // exit code
  mov r7, #1          // syscall: exit
  svc 0
