.global _start
.text
_start:
	mov $255, %rdi
	mov $60, %rax
	syscall
