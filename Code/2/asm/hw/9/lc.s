.section .bss
	.lcomm buffer, 4096 // allocate 4096 bytes for buffer
	.lcomm numbuf, 32   // allocate 32 bytes for numbuf

.section .rodata
newline:
	.ascii "\n" // define a newline character

.section .text

.global _start
_start:
	bl main
	b exit

exit:
	mov	r7, #1 // exit syscall
	mov	r0, #0 // exit code 0
	svc	#0    //  syscall

main:

	mov	r4, #0 // initialize line count to 0

read_loop:
	mov	r0, #0 				// file descriptor 0 (stdin)
	ldr	r1, =buffer 	// load address of buffer
	mov	r2, #4096 		// read up to 4096 bytes
	mov	r7, #3 				// read syscall
	svc	#0    				// syscall
	cmp	r0, #0 				// check if read returned 0 (eof)
	ble	print_count 	// if eof or error, print line count
	mov	r5, r0 				// store number of bytes read in r5
	ldr	r1, =buffer 	// reload buffer address

count_loop:
	cmp	r5, #0 				 // check if all bytes are processed
	beq	read_loop 		 // if yes, read more data
	ldrb	r6, [r1], #1 // load a byte from buffer and increment pointer
	subs	r5, r5, #1   // decrement remaining byte count
	cmp	r6, #10 			 // check if byte is a newline character
	addeq	r4, r4, #1 	 // increment line count if newline
	b	count_loop 			 // repeat for remaining bytes

print_count:
	mov	r0, r4 // move line count to r0
	bl	convert // convert line count to string

	mov	r7, #4 // syscall for write
	mov	r2, r1 // length of string
	mov	r1, r0 // address of string
	mov	r0, #1 // file descriptor 1 (stdout)
	svc	#0    // trigger syscall

	mov	r7, #4 // syscall for write
	mov	r0, #1 // file descriptor 1 (stdout)
	ldr	r1, =newline // address of newline character
	mov	r2, #1 // length of newline
	svc	#0    // trigger syscall

	mov	r7, #1 // exit syscall
	mov	r0, #0 // exit code 0
	svc	#0    // trigger syscall

convert:
	ldr	r1, =numbuf // load address of numbuf
	mov	r2, #0 // initialize string length to 0
	mov	r6, r0 // copy number to r6

conv_loop:
	cmp	r6, #0 // check if number is 0
	beq	conv_done // if yes, conversion is done
	mov	r3, #0 // initialize quotient to 0
	mov	r5, r6 // copy number to r5

div_sub:
	cmp	r5, #10 // check if number is less than 10
	blt	div_sub_done // if yes, division is done
	sub	r5, r5, #10 // subtract 10 from number
	add	r3, r3, #1 // increment quotient
	b	div_sub // repeat division

div_sub_done:
	add	r5, r5, #'0' // convert remainder to ascii
	sub	r1, r1, #1 // move pointer back in numbuf
	strb	r5, [r1] // store ascii character in numbuf
	add	r2, r2, #1 // increment string length
	mov	r6, r3 // update number with quotient
	b	conv_loop // repeat conversion

conv_done:
	cmp	r2, #0 // check if string length is 0
	bne	ret // if not, return
	sub	r1, r1, #1 // move pointer back in numbuf
	mov	r5, #'0' // ascii '0'
	strb	r5, [r1] // store '0' in numbuf
	mov	r2, #1 // set string length to 1

ret:
	mov	r0, r1 // return address of string
	mov	r1, r2 // return length of string
	bx	lr    // return from function
