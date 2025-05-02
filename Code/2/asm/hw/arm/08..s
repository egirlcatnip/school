// print_row
print_row:
    push {lr}              // Save the link register (return address)

    cmp r0, #0             // Compare n with 0
    beq done                // If n == 0, skip the printing loop

print_loop:
    bl putchar             // Call putchar to print the character
    subs r0, r0, #1        // Decrement n (r0)
    bne print_loop         // If n > 0, repeat the loop

    mov r0, #10            // Set r0 to 10 (ASCII code for '\n')
    bl putchar             // Print newline

done:
    pop {pc}               // Restore the return address and return


// print_rect
print_rect:
    push {lr}              // Save the link register (return address)

    mov r2, r0             // Copy rows (n) to r2
    mov r3, r1             // Copy columns (m) to r3

    cmp r2, #0             // If rows == 0, skip printing
    beq done               // Exit if no rows

print_row_loop:
    mov r0, #42            // Set r0 to ASCII code for '*'
    bl print_row           // Call print_row to print the stars
    subs r2, r2, #1        // Decrement row count (r2)
    bne print_row_loop     // If rows > 0, continue printing

done:
    pop {pc}               // Restore the return address and return
