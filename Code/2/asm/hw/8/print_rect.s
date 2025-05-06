// void print_rect(int rows, int columns);
// void print_row(int n, char c);


.global _start

_start:
  mov r0, #5          // rows
  mov r1, #20         // columns
  bl print_rect
  b exit

.global print_rect
// r0 = rows
// r1 = columns

print_rect:
  push {lr}          // save return address for print_rect
  mov r4, r0         // save rows
  mov r5, r1         // save columns

rect_loop:
  cmp r4, #0          // if rows == 0, exit loop
  beq rect_done

  mov r0, r5
  mov r1, #42         // '*' character
  bl print_row

  subs r4, r4, #1
  b rect_loop         // repeat

rect_done:
  pop {lr}            // restore return address for print_rect
  bx lr               // return to print_rect




.global print_row
// r0 = n
// r1 = c

print_row:
  push {lr}           // save return address for print_row
  mov r2, r0          // counter

char_loop:
  cmp r2, #0          // if n == 0, exit loop
  beq char_done

  mov r0, r1          // character to print
  bl print_char

  subs r2, r2, #1     // decrement counter
  b char_loop         // repeat

char_done:
  b print_nl

print_nl:
  mov r0, #10        // newline character ('\n')
  bl putchar
  pop {lr}           // restore return address for print_row
  bx lr              // return to print_row caller

.global print_char
print_char:
  push {lr}          // save return address for print_char

  bl putchar

  pop {lr}           // restore return address for print_char
  bx lr              // return to print_char caller



// Testing putchar
.global putchar
// putchar from glibc


exit:
  mov r0, #0         // exit code
  mov r7, #1
  svc 0
