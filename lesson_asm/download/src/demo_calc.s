.global _start
.data
	INPUT:	.ascii "Input:"
			.equ INPUT_SIZE,.-INPUT
	num:		.fill 20,1,0x20
			.byte '\n'
			.equ NUM_SIZE,.-num
.text
_start:
	/*syscall: ssize_t write(int fd, void *buf, size_t count)*/
	mov $1, %rdi
	mov $INPUT, %rsi
	mov $INPUT_SIZE, %rdx
	mov $1, %rax
	syscall
	/*syscall: ssize_t read(int fd, void *buf, size_t count)*/
	mov $0, %rdi
	mov $num, %rsi
	mov $1, %rdx
	mov $0, %rax
	syscall
	add $0x30,num
	/*syscall: ssize_t write(int fd, void *buf, size_t count)*/
	mov $1, %rdi
	mov $num, %rsi
	mov $NUM_SIZE, %rdx
	mov $1, %rax
	syscall
	/*syscall: void exit(int status)*/
	mov $0, %rdi
	mov $60, %rax
	syscall
