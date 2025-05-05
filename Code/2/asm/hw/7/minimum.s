// int minimum(int count, int *values)


.global minimum
// r0 = int count
// r1 = int *values

minimum:
    cmp r0, #0
    beq exit_loop           // if count == 0


    bl some_function   // call to some_function
    bx lr


some_function:
    ldr r2, [r1]       // load the first value into r2
    add r1, r1, #4     // move to the next value
    sub r0, r0, #1     // decrement count
    mov r4, lr         // save return address of minimum

loop:
    cmp r0, #0         // check if count == 0
    beq exit_loop      // if count == 0

    ldr r3, [r1]       // load the next value into r3
    cmp r2, r3         // compare current minimum with the new value
    movlt r2, r3       // if new value is less than current minimum, update it

    add r1, r1, #4     // move to the next value
    sub r0, r0, #1     // decrement counter

    b loop             // repeat the loop

exit_loop:
    mov r0, r2         // move the minimum value to return register
    bx r4              // return from function

