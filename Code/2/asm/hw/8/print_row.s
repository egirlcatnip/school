// void print_row(int n, char c)

.global _start
_start:
	mov r0, #2
	mov r1, #69
  bx print_row

  b exit

.global print_row
// r0 = n
// r1 = c

print_row:
  mov r3, lr           // save return address
  bx loop

  bx lr


loop:
  cmp r0, #0
  beq newline          // If n == 0, print newline
  bne printchar        // If n != 0, print character

  subs r0, r0, #1      // decrement counter

  b loop               // repeat

newline:
    mov r2, r0         // save counter
    mov r0, #10        // Set r0 to 10 ('\n')
    bl putchar         // Print newline

    mov r0, r2         // restore counter
    b exit_loop        // Exit the function

printchar:
  mov r2, r0           // save counter

  mov r0, r1           // r0 = c

  bl putchar           // putchar
  mov r0, r2           // restore counter
  b exit_loop

exit_loop:
  bx r3              // Return from function

exit:
  mov r7, #1         // syscall number for exit
  svc 0              // make syscall to exit
