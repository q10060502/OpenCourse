.include "tx.s"
.bss
.global _start
.data
	conn_sock:
		.quad -1
	
		.equ ADDR_IN_SIZE,16

	conn_sock_addr:
	conn_sock_addr.sin_family:
		.word 0x2		#AF_INET
	conn_sock_addr.sin_port:
		.word 0x1027
	conn_sock_addr.sin_addr:
		.byte 39,100,205,142
	conn_sock_addr.sin_zero:
		.fill 8,1,0
	conn_sock_addr_size: .long .-conn_sock_addr

		.equ BUF_SIZE,4096
	recv_buf:
		.fill BUF_SIZE,1,0
		.equ recv_buf_size,.-recv_buf
	recv_size:
		.quad 0

	DEFAULT_HDR:
		.ascii "GET / HTTP/1.1\r\n"
		.ascii "User-Agent: tx_http_cnt/0.1\r\n"
		.ascii "Connection: close\r\n"
		.ascii "\r\n"
		.equ DEFAULT_HDR_SIZE,.-DEFAULT_HDR
.text
_start:
Lconn_socket:
	#syscall: int socket(int domain, int type, int protocol)
	mov $2, %rdi		#domain: AF_INET
	mov $1, %rsi		#type: SOCK_STREAM	
	mov $6, %rdx		#protocol: IPPROTO_TCP 
	mov $41, %rax
	syscall
	mov %rax,(conn_sock)
Lconn_connect:
	#syscall: int connect(int sockfd, struct sockaddr *addr, socklen_t addr_len)
	mov (conn_sock), %rdi
	mov $conn_sock_addr, %rsi
	mov $ADDR_IN_SIZE, %rdx		
	mov $42, %rax
	syscall
Lconn_write_default_hdr:
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov (conn_sock), %rdi
	mov $DEFAULT_HDR, %rsi
	mov $DEFAULT_HDR_SIZE, %rdx
	mov $1, %rax
	syscall
Lconn_read:
	#syscall: ssize_t read(int fd, void *buf, size_t count)
	mov (conn_sock), %rdi
	mov $recv_buf, %rsi
	mov $BUF_SIZE, %rdx
	mov $0, %rax
	syscall
	mov %rax,(recv_size)
Lconn_write:
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov $1, %rdi
	mov $recv_buf, %rsi
	mov recv_size, %rdx
	mov $1, %rax
	syscall
Lconn_close:
	#syscall: int close(int fd)
	mov (conn_sock), %rdi
	mov $3, %rax
	syscall
Lexit:
	#syscall: void exit(int status)
	mov $0, %rdi
	mov $60, %rax
	syscall
