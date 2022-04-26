.macro disp
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
.endm
.global _start
.data
	msg: .ascii "Hello, "
	name: .fill 20,1,0x20
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
base_mem:
	mov $name,%rbx
	movb $'!,(%rbx)
	disp
	movb $'!,1(%rbx)
	disp
	movb $'!,2(%rbx)
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
