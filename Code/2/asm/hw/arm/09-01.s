.globl _start
.text
.equ STDOUT, 1
.equ SYS_EXIT, 1
.equ SYS_WRITE, 4
.equ SYS_CALL, 0

_start:
    mov r0, #20           // Width of the rectangle (x)
    mov r1, #5            // Height of the rectangle (y)
    bl draw_rectangle     // Call the draw_rectangle function

    mov r7, #SYS_EXIT     // Exit the program
    mov r0, #42           // Exit code
    svc #SYS_CALL

draw_rectangle:
    push {r4, r5, r6, r7, lr}  // Save registers
    mov r4, r0                // Store width (x) in r4
    mov r5, r1                // Store height (y) in r5

draw_row:
    mov r6, r4                // Copy width (x) to r6 for each row

print_stars:
    cmp r6, #0                // Check if we've printed all stars for this row
    beq end_row               // If no more stars to print, end the row

    mov r7, #SYS_WRITE        // SYS_WRITE system call
    mov r0, #STDOUT           // File descriptor STDOUT
    adr r1, star_char         // Address of the '*' character
    mov r2, #1                // Length of the '*' character (1 byte)
    svc #SYS_CALL

    subs r6, r6, #1           // Decrement the width counter
    b print_stars             // Repeat for the next star

end_row:
    adr r1, newline           // Address of newline character
    mov r2, #1                // Length of newline string
    svc #0                    // Write newline character

    subs r5, r5, #1           // Decrement height (y)
    bne draw_row              // Repeat if there are more rows

    pop {r4, r5, r6, r7, lr}  // Restore registers
    bx lr                     // Return from function

star_char:
    .ascii "*"                // Single '*' character

newline:
    .ascii "\n"               // Newline character
