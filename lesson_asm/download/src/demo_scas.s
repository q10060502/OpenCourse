.macro disp
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
.endm
.global _start
.data
	b64: .quad 0x6275702e6e61756a 	/*bup.nauJ*/
	msg: .ascii "Hello, "
	name: .fill 20,1,0x20
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
	disp
scans:
	mov $msg,%rdi
	mov $msg_size,%rcx
	mov $',,%al
	repne scasb
	movb $'!,-1(%rdi)
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
