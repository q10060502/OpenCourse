.macro disp
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
.endm
.global _start
.data
	b32: .long 0x676e6154		/*gnaT*/
	msg: .ascii "Hello, "
	name: 
		.rep 20
		.byte 0x20
		.endr
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
immtomem:
	movl $0x676e6154,name
	disp
immtoreg32:
	mov $0x676e6154,%eax
reg32tomem:
	mov %eax,name
	disp
memtoreg32:
	mov b32,%eax
	mov %eax,name
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
