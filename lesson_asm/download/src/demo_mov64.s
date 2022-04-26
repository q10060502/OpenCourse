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
immtoreg64:
	mov $'X,%rax
	mov %rax,name
	disp
	mov $0x31323334,%rax
	mov %rax,name
	disp
imm64toreg64:
	movabsq $0x6275702e6e61756a,%rax
reg64tomem:
	mov %rax,name
	disp
memtoreg64:
	mov b64,%rax
	mov %rax,name
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
