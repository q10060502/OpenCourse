.macro _tx_msg_show msg,msg_size
	mov $1, %rdi
	mov \msg, %rsi
	mov \msg_size, %rdx
	mov $1, %rax
	syscall
.endm
.macro _tx_num_b32toa /*%eax,%rdi*/
	push $0
	mov $10,%ebx
0:
	xor %edx,%edx
	div %ebx
	cmp $0,%eax
	je 0f
	add $0x30,%dl
	push %rdx
	jmp 0b
0:
	add $0x30,%dl
	mov %dl,(%rdi)
	inc %rdi
1:
	pop %rax
	cmp $0,%al
	je 1f
	mov %al,(%rdi)
	inc %rdi
	jmp 1b
1:
.endm
.global _start
.data
	UID_MSG:
		.ascii "uid:"
	uid_msg_data:	
		.fill 20,1,0x20
		.byte '$,'\n
		.equ UID_MSG_SIZE,.-UID_MSG
.text
_start:
Lgetuid:
	mov $102,%rax
	syscall
	/*mov %rax,%rax*/
	mov $uid_msg_data,%rdi
	_tx_num_b32toa
Lmsg_show:
	_tx_msg_show $UID_MSG,$UID_MSG_SIZE
Lexit:
	/*syscall: void exit(int status)*/
	mov $0, %rdi
	mov $60, %rax
	syscall
