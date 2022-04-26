.macro disp
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
.endm
.global _start
.data
	b8: .byte 0x58
	msg: .ascii "Hello, "
	name: .ascii "12345678901234567890"
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
immtomem:
	movb $'X,name
	disp

immtoreg8:
	mov $'X,%al
reg8tomem:
	mov %al,name
	disp

memtoreg8:
	mov b8,%al
	mov %al,name
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
