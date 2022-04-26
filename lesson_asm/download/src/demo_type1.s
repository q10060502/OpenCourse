.macro msg_show msg,msg_size
	mov $1, %rdi
	mov \msg, %rsi
	mov \msg_size, %rdx
	mov $1, %rax
	syscall
.endm
.macro msg_read msg,msg_size
	mov $0, %rdi
	mov \msg, %rsi
	mov \msg_size, %rdx
	mov $0, %rax
	syscall
.endm
.global _start
.data
	MENU:		.ascii "-------\n1.start\n2.exit\nChoice:"
			.equ MENU_SIZE,.-MENU
	choice:		.byte 0
	START_MSG:	.ascii "-------\nStart!\n"
			.equ START_MSG_SIZE,.-START_MSG
	ERR_MSG:	.ascii "-------\nSelect error!\n"
			.equ ERR_MSG_SIZE,.-ERR_MSG
.text
_start:
Ltype_menu:
	msg_show $MENU,$MENU_SIZE
Ltype_choice:
	msg_read $choice,$1
	cmpb $'1,(choice)
	je Ltype_start
	cmpb $'2,(choice)
	je Lexit
	jmp Ltype_choice_err
Ltype_start:
	msg_show $START_MSG,$START_MSG_SIZE
	jmp Lexit
Ltype_choice_err:
	msg_show $ERR_MSG,$ERR_MSG_SIZE
Lexit:
	/*syscall: void exit(int status)*/
	mov $0, %rdi
	mov $60, %rax
	syscall
