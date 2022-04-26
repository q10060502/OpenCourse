.bss
.global _start
.data
	lisn_sock:
		.quad -1 
	conn_sock:
		.quad -1
	
		.equ ADDR_IN_SIZE,16

	lisn_sock_addr:
	lisn_sock_addr.sin_family:
		.word 0x0002			#sin_family
	lisn_sock_addr.sin_port:
		.word 0x1127			#sin_port
	lisn_sock_addr.sin_addr:
		.byte 0x00,0x00,0x00,0x00	#sin_addr
	lisn_sock_addr.sin_zero:
		.fill 8,1,0
	lisn_sock_addr_size:
		.long .-conn_sock_addr

	conn_sock_addr:
	conn_sock_addr.sin_family:
		.word 0x0
	conn_sock_addr.sin_port:
		.word 0x0
	conn_sock_addr.sin_addr:
		.byte 0x00,0x00,0x00,0x00
	conn_sock_addr.sin_zero:
		.fill 8,1,0
	conn_sock_addr_size:
		.long .-conn_sock_addr

		.equ SO_REUSEADDR_VAL_SIZE,4
	so_reuseaddr_val:
		.long 0xffffffff

		.equ SO_RCVTIMEO_VAL_SIZE,16
	so_rcvtimeo_val:
		.quad 2,0

		.equ BUF_SIZE,4096
	recv_buf:
		.fill BUF_SIZE,1,0
		.equ recv_buf_size,.-recv_buf
	recv_size:
		.quad 0
	
	DEFAULT_HDR:
		.ascii "HTTP/1.1 200 OK\r\n"
		.ascii "User-Agent: tx_http_srv/0.1\r\n"
		.ascii "Context-Type: text/plain\r\n"
		.ascii "Connection: close\r\n"
		.ascii "Pragma: no-cache\r\n"
		.ascii "Cache-Control: no-cache;\r\n"
		.ascii "\r\n"
		.equ DEFAULT_HDR_SIZE,.-DEFAULT_HDR
.text
_start:
Llisn_socket:
	#syscall: int socket(int domain, int type, int protocol)
	mov $2, %rdi		#domain: AF_INET
	mov $1, %rsi		#type: SOCK_STREAM	
	mov $6, %rdx		#protocol: IPPROTO_TCP 
	mov $41, %rax
	syscall
	cmp $0,%rax
	jl Lexit
	mov %rax,(lisn_sock)
Llisn_setsockopt_reuseaddr:
	#syscall: int setsockopt(int sockfd, int level, int name, void *val, socklen_t len)
	mov (lisn_sock), %rdi
	mov $1, %rsi		#SOL_SOCKET
	mov $2, %rdx		#SO_REUSEADDR
	mov $so_reuseaddr_val,%r10
	mov $SO_REUSEADDR_VAL_SIZE,%r8
	mov $54, %rax
	syscall
	cmp $0,%rax
	jl Llisn_close
Llisn_bind:
	#syscall: int bind(int sockfd, struct sockaddr *addr, socklen_t addr_len)
	mov (lisn_sock), %rdi
	mov $lisn_sock_addr, %rsi
	mov $ADDR_IN_SIZE, %rdx		
	mov $49, %rax
	syscall
	cmp $0,%rax
	jl Llisn_close
Llisn_listen:
	#syscall: int listen(int sockfd, int backlog)
	mov (lisn_sock), %rdi
	mov $128, %rsi		
	mov $50, %rax
	syscall
	cmp $0,%rax
	jl Llisn_close
Llisn_accept:
	#syscall: int accept(int sockfd, struct sockaddr *addr, socklen_t *addr_len)
	mov (lisn_sock), %rdi
	mov $conn_sock_addr, %rsi
	mov $conn_sock_addr_size, %rdx
	mov $43, %rax
	syscall
	cmp $0,%rax
	jl Llisn_close
	mov %rax,(conn_sock)
Lconn_setsockopt_rcvtimeo:
	#syscall: int setsockopt(int sockfd, int level, int name, void *val, socklen_t len)
	mov (conn_sock), %rdi
	mov $1, %rsi		#SOL_SOCKET
	mov $20, %rdx		#SO_RCVTIMEO
	mov $so_rcvtimeo_val,%r10
	mov $SO_RCVTIMEO_VAL_SIZE,%r8
	mov $54, %rax
	syscall
	cmp $0,%rax
	jl Lconn_close
Lconn_read:
	#syscall: ssize_t read(int fd, void *buf, size_t count)
	mov (conn_sock), %rdi
	mov $recv_buf, %rsi
	mov $BUF_SIZE, %rdx
	mov $0, %rax
	syscall
	cmp $0,%rax
	jle Lconn_close
	mov %rax,(recv_size)
Lconn_write:
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov (conn_sock), %rdi
	mov $DEFAULT_HDR, %rsi
	mov $DEFAULT_HDR_SIZE, %rdx
	mov $1, %rax
	syscall
	cmp $0,%rax
	jle Lconn_close
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov (conn_sock), %rdi
	mov $recv_buf, %rsi
	mov recv_size, %rdx
	mov $1, %rax
	syscall
Lconn_close:
	#syscall: int close(int fd)
	mov (conn_sock), %rdi
	mov $3, %rax
	syscall
	jmp Llisn_accept
Llisn_close:
	#syscall: int close(int fd)
	mov (lisn_sock), %rdi
	mov $3, %rax
	syscall
Lexit:
	#syscall: void exit(int status)
	mov $0, %rdi
	mov $60, %rax
	syscall
