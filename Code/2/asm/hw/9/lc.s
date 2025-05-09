.section .bss
	.lcomm buffer, 4096
	.lcomm numbuf, 32

.section .rodata
newline:
	.ascii "\n"

.section .text

.global _start
_start:
  bl main
  b exit

exit:
  mov	r7, #1
  mov	r0, #0
  svc	#0

main:

	mov	r4, #0

read_loop:
	mov	r0, #0
	ldr	r1, =buffer
	mov	r2, #4096
	mov	r7, #3
	svc	#0
	cmp	r0, #0
	ble	print_count
	mov	r5, r0
	ldr	r1, =buffer

count_loop:
	cmp	r5, #0
	beq	read_loop
	ldrb	r6, [r1], #1
	subs	r5, r5, #1
	cmp	r6, #10
	addeq	r4, r4, #1
	b	count_loop

print_count:
	mov	r0, r4
	bl	convert

	mov	r7, #4
	mov	r2, r1
	mov	r1, r0
	mov	r0, #1
	svc	#0

	mov	r7, #4
	mov	r0, #1
	ldr	r1, =newline
	mov	r2, #1
	svc	#0

	mov	r7, #1
	mov	r0, #0
	svc	#0

convert:
	ldr	r1, =numbuf
	mov	r2, #0
	mov	r6, r0

conv_loop:
	cmp	r6, #0
	beq	conv_done
	mov	r3, #0
	mov	r5, r6

div_sub:
	cmp	r5, #10
	blt	div_sub_done
	sub	r5, r5, #10
	add	r3, r3, #1
	b	div_sub

div_sub_done:
	add	r5, r5, #'0'
	sub	r1, r1, #1
	strb	r5, [r1]
	add	r2, r2, #1
	mov	r6, r3
	b	conv_loop

conv_done:
	cmp	r2, #0
	bne	ret
	sub	r1, r1, #1
	mov	r5, #'0'
	strb	r5, [r1]
	mov	r2, #1

ret:
	mov	r0, r1
	mov	r1, r2
	bx	lr
