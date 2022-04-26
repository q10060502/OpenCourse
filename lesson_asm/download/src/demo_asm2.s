.global _start
.data
	msg: .ascii "Hello ASM!\n"
	.equ msg_size,.-msg
.text
_start:
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
	mov $0, %rdi
	mov $60, %rax
	syscall
