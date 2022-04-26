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
	mov $name,%rbx
get_addr:
	mov $0,%rsi
	movb $'#,(%rbx,%rsi,4)
	disp
	mov $1,%rsi
	movb $'#,(%rbx,%rsi,4)
	disp
	mov $1,%rsi
	lea (%rbx,%rsi,4),%rbx
	movb $'^,(%rbx)
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
