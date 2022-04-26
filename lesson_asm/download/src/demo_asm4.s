.global _start
.data
	hello:		.ascii "Hello, "
			.equ hello_size,.-hello
	name:		.fill 20,1,0x20
			.equ name_max_size,.-name
	name_size:	.quad 0
.text
_start:
	/*syscall: ssize_t read(int fd, void *buf, size_t count)*/
	mov $0, %rdi
	mov $name, %rsi
	mov $name_max_size, %rdx
	mov $0, %rax
	syscall
	mov %rax,name_size
	/*syscall: ssize_t write(int fd, void *buf, size_t count)*/
	mov $1, %rdi
	mov $hello, %rsi
	mov $hello_size, %rdx
	mov $1, %rax
	syscall
	/*syscall: ssize_t write(int fd, void *buf, size_t count)*/
	mov $1, %rdi
	mov $name, %rsi
	mov name_size, %rdx
	mov $1, %rax
	syscall
	/*syscall: void exit(int status)*/
	mov name_size, %rdi
	mov $60, %rax
	syscall
