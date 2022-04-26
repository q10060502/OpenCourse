.macro disp
	mov $msg_size, %rdx
	mov $msg, %rsi
	mov $1, %rdi
	mov $1, %rax
	syscall
.endm
.global _start
.data
	b16: .word 0x5854
	msg: .ascii "Hello, "
	name: .ascii "                    "
	.byte '$,'\n
	.equ msg_size,.-msg
.text
_start:
immtomem:
	movw $0x5854,name
	disp
immtoreg16:
	mov $0x5854,%ax
reg16tomem:
	mov %ax,name
	disp
memtoreg16:
	mov b16,%ax
	mov %ax,name
	disp
exit:
	mov $0, %rdi
	mov $60, %rax
	syscall
