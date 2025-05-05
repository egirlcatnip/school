// void print_rect(int rows, int columns)

.global _start
_start:
	mov r0, #2
	mov r1, #69
  bx print_rect

  b exit



.global print_rect
  // r0 = rows
  // r1 = columns

print_rect:
  mov r3, lr           // save return address

  cmp r0, #0           // Check if rows == 0
  beq exit_loop        // If rows == 0, exit

  mov r4, r0           // Copy rows to r4 for loop control
  mov r5, r1           // Copy columns to r5 for printing

printrect_loop:
  cmp r4, #0           // Check if rows == 0
  beq exit_loop        // If rows == 0, exit

  mov r0, r5           // Set r0 to columns
  mov r1, #42          // Set r1 to ASCII code for '*'
  bl print_row         // Call print_row with columns

  subs r4, r4, #1      // Decrement row count
  b printrect_loop     // Repeat for next row


.global print_row
  // r0 = n
  // r1 = c

print_row:
  mov r3, lr           // save return address
  bx printrow_loop

  bx lr


printrow_loop:
  cmp r0, #0
  beq newline          // If n == 0, print newline
  bne printchar        // If n != 0, print character

  subs r0, r0, #1      // decrement counter

  b printrow_loop               // repeat

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
