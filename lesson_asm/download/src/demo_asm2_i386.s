.global _start
.data
	msg: .ascii "Hello ASM!\n"
	.equ msg_size,.-msg
.text
_start:
	mov $msg_size, %edx
	mov $msg, %ecx
	mov $1, %ebx
	mov $4, %eax
	int $0x80
	mov $0, %ebx
	mov $1, %eax
	int $0x80
