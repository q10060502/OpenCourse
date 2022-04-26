.global _start
.data
	msg: .ascii "Hello ASM!\n"
	.equ msg_size,.-msg
.text
_start:
	ldr r2,=msg_size
	ldr r1,=msg
	mov r0,#1
	mov r7,#4
	swi #0
	mov r0,#0
	mov r7,#1
	swi #0
