.macro _tx_num_b8toa /*%al,%rdi*/
	push $0
	mov $10,%bl
0:
	xor %ah,%ah
	div %bl
	cmp $0,%al
	je 0f
	add $0x30,%ah
	push %rax
	jmp 0b
0:
	add $0x30,%ah
	mov %ah,(%rdi)
	inc %rdi
1:
	pop %rax
	cmp $0,%ah
	je 1f
	mov %ah,(%rdi)
	inc %rdi
	jmp 1b
1:
.endm
.macro _tx_num_b16toa /*%ax,%rdi%/
	push $0
	mov $10,%bx
0:
	xor %dx,%dx
	div %bx
	cmp $0,%ax
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
.macro _tx_num_b64toa /*%rax,%rdi*/
	push $0
	mov $10,%rbx
0:
	xor %rdx,%rdx
	div %rbx
	cmp $0,%rax
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
.macro _tx_port_ntoa /*%ax,%rdi*/
	xchg %al,%ah
	_tx_num_b16toa
.endm
.macro _tx_inet_ntoa /*%eax,%rdi*/
	push %rax
	_tx_num_b8toa
	movb $'.,(%rdi)
	inc %rdi
	pop %rax
	shr $8,%rax
	push %rax
	_tx_num_b8toa
	movb $'.,(%rdi)
	inc %rdi
	pop %rax
	shr $8,%rax
	push %rax
	_tx_num_b8toa
	movb $'.,(%rdi)
	inc %rdi
	pop %rax
	shr $8,%rax
	_tx_num_b8toa
.endm
.bss
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
		.word 0x1227			#sin_port
	lisn_sock_addr.sin_addr:
		.byte 0x00,0x00,0x00,0x00	#sin_addr
	lisn_sock_addr.sin_zero:
		.fill 8,1,0
	lisn_sock_addr_size:
		.long .-lisn_sock_addr

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
	
		.equ HTTP_REP_HDR_STATUS_SIZE,40
	HTTP_REP_HDR_STATUS_200:
		.ascii "200 OK"
		.equ HTTP_REP_HDR_STATUS_200_SIZE,.-HTTP_REP_HDR_STATUS_200
		.fill HTTP_REP_HDR_STATUS_SIZE-HTTP_REP_HDR_STATUS_200_SIZE,1,0x20
	HTTP_REP_HDR_STATUS_404:
		.ascii "404 Not Found"
		.equ HTTP_REP_HDR_STATUS_404_SIZE,.-HTTP_REP_HDR_STATUS_404
		.fill HTTP_REP_HDR_STATUS_SIZE-HTTP_REP_HDR_STATUS_404_SIZE,1,0x20

		.equ HTTP_REP_HDR_CTYPE_SIZE,40
	HTTP_REP_HDR_CTYPE_TEXT_HTML:
		.ascii "text/html"
		.equ HTTP_REP_HDR_CTYPE_TEXT_HTML_SIZE,.-HTTP_REP_HDR_CTYPE_TEXT_HTML
		.fill HTTP_REP_HDR_CTYPE_SIZE-HTTP_REP_HDR_CTYPE_TEXT_HTML_SIZE,1,0x20
	send_buf:
	HTTP_REP_HDR:
		.ascii "HTTP/1.1 "
	HTTP_REP_HDR_STATUS:
		.ascii "200 OK"
		.fill HTTP_REP_HDR_STATUS_SIZE-HTTP_REP_HDR_STATUS_200_SIZE,1,0x20
		.ascii "\r\n"
		.ascii "User-Agent: tx_http_srv/0.2\r\n"
		.ascii "Context-Type: "
	HTTP_REP_HDR_CTYPE:
		.ascii "text/html"
		.fill HTTP_REP_HDR_CTYPE_SIZE-HTTP_REP_HDR_CTYPE_TEXT_HTML_SIZE,1,0x20
		.ascii "\r\n"
		.ascii "Connection: close\r\n"
		.ascii "Pragma: no-cache\r\n"
		.ascii "Cache-Control: no-cache\r\n"
		.ascii "\r\n"
		.equ HTTP_REP_HDR_SIZE,.-HTTP_REP_HDR
	send_data_buf:
		.fill BUF_SIZE-HTTP_REP_HDR_SIZE,1,0x58
		.equ SEND_DATA_BUF_SIZE,.-send_data_buf
		.equ SEND_BUF_SIZE,.-send_buf
	send_size:
		.quad 0 

	HTTP_REQ_DBG_ECHO:
		.ascii "GET /dbg/echo "
		.equ HTTP_REQ_DBG_ECHO_SIZE,.-HTTP_REQ_DBG_ECHO

	HTTP_REQ_CNT_IP:
		.ascii "GET /cnt/ip "
		.equ HTTP_REQ_CNT_IP_SIZE,.-HTTP_REQ_CNT_IP

	HTTP_REQ_CNTS_NUM:
		.ascii "GET /cnts/num "
		.equ HTTP_REQ_CNTS_NUM_SIZE,.-HTTP_REQ_CNTS_NUM
	cnts_num:
		.quad 10000000000

	HTTP_REQ_INDEX:
		.ascii "GET / "
		.equ HTTP_REQ_INDEX_SIZE,.-HTTP_REQ_INDEX

	index_file_name:
		.asciz "index_0_2.htm"
	index_file_fd:
		.quad -1
.text
.global _start
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
	mov %rax,conn_sock
	incq cnts_num
Lconn_setsockopt_rcvtimeo:
	#syscall: int setsockopt(int sockfd, int level, int name, void *val, socklen_t len)
	mov conn_sock, %rdi
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
	mov conn_sock, %rdi
	mov $recv_buf, %rsi
	mov $BUF_SIZE, %rdx
	mov $0, %rax
	syscall
	cmp $0,%rax
	jle Lconn_close
	mov %rax,(recv_size)
Lconn_parse:
Lhttp_req_dbg_echo_begin:
	cmp $HTTP_REQ_DBG_ECHO_SIZE,(recv_size)
	jl Lhttp_req_dbg_echo_end
	mov $recv_buf,%rdi
	mov $HTTP_REQ_DBG_ECHO,%rsi
	mov $HTTP_REQ_DBG_ECHO_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_dbg_echo_end
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $HTTP_REP_HDR, %rsi
	mov $HTTP_REP_HDR_SIZE, %rdx
	mov $1, %rax
	syscall
	cmp $0,%rax
	jle Lconn_close
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $recv_buf, %rsi
	mov recv_size, %rdx
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_dbg_echo_end:
Lhttp_req_cnt_ip_begin:
	cmp $HTTP_REQ_CNT_IP_SIZE,(recv_size)
	jl Lhttp_req_cnt_ip_end
	mov $recv_buf,%rdi
	mov $HTTP_REQ_CNT_IP,%rsi
	mov $HTTP_REQ_CNT_IP_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_cnt_ip_end
	mov conn_sock_addr.sin_addr,%eax
	mov $send_data_buf,%rdi
	mov %rdi,%rsi
	_tx_inet_ntoa
	movb $':,(%rdi)
	inc %rdi
	mov conn_sock_addr.sin_port,%ax
	_tx_port_ntoa
	sub %rsi,%rdi
	add $HTTP_REP_HDR_SIZE,%rdi
	mov %rdi,send_size
	mov %rdi,%rdx
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	/*mov %rdx, %rdx*/
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_cnt_ip_end:
Lhttp_req_cnts_num_begin:
	cmp $HTTP_REQ_CNTS_NUM_SIZE,(recv_size)
	jl Lhttp_req_cnts_num_end
	mov $recv_buf,%rdi
	mov $HTTP_REQ_CNTS_NUM,%rsi
	mov $HTTP_REQ_CNTS_NUM_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_cnts_num_end
	mov cnts_num,%rax
	mov $send_data_buf,%rdi
	mov %rdi,%rsi
	_tx_num_b64toa
	sub %rsi,%rdi
	add $HTTP_REP_HDR_SIZE,%rdi
	mov %rdi,send_size
	mov %rdi,%rdx
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	/*mov %rdx, %rdx*/
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_cnts_num_end:
Lhttp_req_index_begin:
	cmp $HTTP_REQ_INDEX_SIZE,(recv_size)
	jl Lhttp_req_index_end
	mov $recv_buf,%rdi
	mov $HTTP_REQ_INDEX,%rsi
	mov $HTTP_REQ_INDEX_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_index_end
	#syscall: int open(const  char *pathname, int flags, mode_t mode)
	mov $index_file_name, %rdi
	mov $0, %rsi				#O_RDONLY
	mov $2, %rax
	syscall
	cmp $0,%rax
	jl Lhttp_rep_404_begin
	mov %rax,index_file_fd

	#syscall: ssize_t read(int fd, void *buf, size_t count)
	mov %rax, %rdi
	mov $send_data_buf, %rsi
	mov $SEND_DATA_BUF_SIZE, %rdx
	mov $0, %rax
	syscall
	add $HTTP_REP_HDR_SIZE,%rax
	mov %rax,send_size
	mov %rax,%rdx

	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	/*mov send_size,%rdx*/
	mov $1, %rax
	syscall

	#syscall: int close(int fd)
	mov index_file_fd, %rdi
	mov $3, %rax
	syscall
	jmp Lconn_close
Lhttp_req_index_end:
Lhttp_rep_404_begin:
	mov $HTTP_REP_HDR_STATUS_404,%rsi
	mov $HTTP_REP_HDR_STATUS,%rdi
	mov $HTTP_REP_HDR_STATUS_404_SIZE,%rcx
	mov %rcx,%rdx
	add $HTTP_REP_HDR_SIZE,%rdx
	rep movsb
	mov $HTTP_REP_HDR_STATUS_404,%rsi
	mov $send_data_buf,%rdi
	mov $HTTP_REP_HDR_STATUS_404_SIZE,%rcx
	rep movsb
	mov conn_sock,%rdi
	mov $send_buf,%rsi
	/*mov %rdx,%rdx*/
	mov $1,%rax
	syscall
Lhttp_rep_404_end:
	mov $0x20,%al
	mov $HTTP_REP_HDR_STATUS,%rdi
	mov $HTTP_REP_HDR_STATUS_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_HDR_STATUS_200,%rsi
	mov $HTTP_REP_HDR_STATUS,%rdi
	mov $HTTP_REP_HDR_STATUS_200_SIZE,%rcx
	rep movsb
Lconn_close:
	#syscall: int close(int fd)
	mov conn_sock, %rdi
	mov $3, %rax
	syscall
	jmp Llisn_accept
Llisn_close:
	#syscall: int close(int fd)
	mov lisn_sock, %rdi
	mov $3, %rax
	syscall
Lexit:
	#syscall: void exit(int numus)
	mov $0, %rdi
	mov $60, %rax
	syscall
