// mul11
mul11:
    add r1, r0, r0    // r1 = 2 * x
    add r2, r1, r1    // r2 = 4 * x
    add r2, r2, r2    // r2 = 8 * x
    add r1, r2, r1    // r1 = 10 * x
    add r0, r0, r1    // r0 = 11 * x
end_mul11:
    bx lr

// fnzb
fnzb:
    clz r0, r0         // Count leading zeros in r0
    sub r0, r0, #31    // Subtract from 31 to get the bit position
end_fnzb:
    bx lr

// my_memset
my_memset:
    cmp r2, #0          // Check if n == 0
    beq end_memset/
loop_memset:
    strb r1, [r0], #1   // Store byte in address pointed by r0, then increment r0
    subs r2, r2, #1     // Decrement n
    bne loop_memset
end_memset:
    bx lr

// my_strlen
my_strlen:
    mov r1, r0          // Copy string pointer to r1
    mov r0, #0          // Initialize length counter to 0
loop_strlen:
    ldrb r2, [r1], #1   // Load byte from string into r2 and increment r1
    cmp r2, #0          // Check if end of string (null-terminator)
    bne loop_strlen     // Continue if not null-terminator
end_strlen:
    bx lr

// my_strcmp
my_strcmp:
loop_strcmp:
    ldrb r2, [r0], #1   // Load byte from first string into r2 and increment r0
    ldrb r3, [r1], #1   // Load byte from second string into r3 and increment r1
    cmp r2, r3          // Compare bytes
    bne not_equal
    cmp r2, #0          // If both are \0, strings are equal
    beq equal
    b loop_strcmp
not_equal:
    sub r0, r2, r3      // Return difference of characters
    bx lr
equal:
    mov r0, #0          // Strings are equal, return 0
    bx lr


// multiples
multiples:
    mov r2, #0          // r2 = counter
loop_multiples:
    mul r3, r1, r2      // r3 = n * counter
    strh r3, [r0, r2, lsl #1] // Store r3 (multiple) into the array[r2]
    add r2, r2, #1      // Increment counter
    cmp r2, #10         // Check if we have stored 10 multiples
    blt loop_multiples  // If less than 10, continue
end_multiples:
    bx lr

// minimum
minimum:
    mov r3, r0          // Store count in r3
    mov r0, [r1]        // Initialize minimum value with the first element
    add r1, r1, #4      // Move to the next element
loop_minimum:
    cmp r3, #1          // If only one element left, exit loop
    ble end_minimum
    ldr r2, [r1]        // Load next element into r2
    cmp r0, r2          // Compare with current minimum
    bge no_update
update:
    mov r0, r2
no_update:
    add r1, r1, #4      // Move to the next element
    subs r3, r3, #1     // Decrement count
    b loop_minimum
end_minimum:
    bx lr
