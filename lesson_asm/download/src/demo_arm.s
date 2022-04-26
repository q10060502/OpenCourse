	.arch armv4t
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"demo.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d,%d\012\000"
	.align	2
.LC1:
	.ascii	"%d\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	mov	r2, #28
	mov	r1, #16
	ldr	r3, .L3
.LPIC0:
	add	r3, pc, r3
	mov	r0, r3
	bl	printf(PLT)
	mov	r1, #16
	ldr	r3, .L3+4
.LPIC1:
	add	r3, pc, r3
	mov	r0, r3
	bl	printf(PLT)
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L4:
	.align	2
.L3:
	.word	.LC0-(.LPIC0+8)
	.word	.LC1-(.LPIC1+8)
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18) 6.3.0 20170516"
	.section	.note.GNU-stack,"",%progbits
