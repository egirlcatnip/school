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

_exit:
    mov r7, #SYS_EXIT     // Exit the program
    mov r0, #0           // Exit code
    svc #SYS_CALL

draw_rectangle:
    push {r4, r5, r6, r7, lr}  // Save registers
    mov r4, r0                // Store width (x) in r4
    mov r5, r1                // Store height (y) in r5

    bl draw_outer_loop  // Call the outer loop

draw_outer_loop:
    cmp r5, #0                // Compare height (y) with 0
    beq draw_exit             // If y == 0, exit the loop

    mov r6, r4                // Store width (x) in r6
    bl draw_inner_loop        // Call the inner loop
draw_inner_loop:
    cmp r6, #0                // Compare width (x) with 0
    beq draw_newline          // If x == 0, go to newline

    ldr r0, =STDOUT           // Load STDOUT file descriptor
    ldr r1, =star_char       // Load address of '*' character
    mov r2, #1                // Number of bytes to write
    mov r7, #SYS_WRITE        // System call for write
    svc #SYS_CALL             // Make the system call

    sub r6, r6, #1            // Decrement width (x)
    b draw_inner_loop         // Repeat inner loop

draw_newline:
    ldr r0, =STDOUT           // Load STDOUT file descriptor
    ldr r1, =newline          // Load address of newline character
    mov r2, #1                // Number of bytes to write
    mov r7, #SYS_WRITE        // System call for write
    svc #SYS_CALL             // Make the system call

    sub r5, r5, #1            // Decrement height (y)
    b draw_outer_loop         // Repeat outer loop

draw_exit:
    pop {r4, r5, r6, r7, pc}  // Restore registers and return
    bx lr



star_char:
    .ascii "*"                // Single '*' character
    .align 2                  // Ensure proper alignment
newline:
    .ascii "\n"               // Newline character
