.global _start
.data
	msg:	.ascii "Hello, "
	name:	.fill 20,1,0x20
		.equ name_size,.-name
		.byte '$,'\n
		.equ msg_size,.-msg
.text
_start:
	/*syscall: ssize_t read(int fd, void *buf, size_t count)*/
	mov $0, %rdi
	mov $name, %rsi
	mov $name_size, %rdx
	mov $0, %rax
	syscall
	/*syscall: ssize_t write(int fd, void *buf, size_t count)*/
	mov $1, %rdi
	mov $msg, %rsi
	mov $msg_size, %rdx
	mov $1, %rax
	syscall
	/*syscall: void exit(int status)*/
	mov $0, %rdi
	mov $60, %rax
	syscall
