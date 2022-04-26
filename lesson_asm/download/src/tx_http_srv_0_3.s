.macro _tx_num_b8toa /*%al,%ah,%bl,%rdi*/
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
.macro _tx_num_b16toa /*%ax,%bx,%rdi%/
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
.macro _tx_num_b32toa /*%eax,%ebx,%rdi*/
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
.macro _tx_num_b64toa /*%rax,%rbx,%rdi*/
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
		.word 0x1327			#sin_port
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

	so_reuseaddr_val:
		.long 0xffffffff
		.equ SO_REUSEADDR_VAL_SIZE,.-so_reuseaddr_val

	so_rcvtimeo_val:
		.quad 1,0
		.equ SO_RCVTIMEO_VAL_SIZE,.-so_rcvtimeo_val

		.equ BUF_SIZE,4096
	recv_buf:
		.fill BUF_SIZE,1,0
		.equ recv_buf_size,.-recv_buf
	recv_size:
		.quad 0
	
		.equ HTTP_REP_LINE_STATUS_SIZE,40
	HTTP_REP_LINE_STATUS_200:
		.ascii "200 OK"
		.equ HTTP_REP_LINE_STATUS_200_SIZE,.-HTTP_REP_LINE_STATUS_200
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_200_SIZE,1,0x20
	HTTP_REP_LINE_STATUS_400:
		.ascii "400 Bad Request"
		.equ HTTP_REP_LINE_STATUS_400_SIZE,.-HTTP_REP_LINE_STATUS_400
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_400_SIZE,1,0x20
	HTTP_REP_LINE_STATUS_404:
		.ascii "404 Not Found"
		.equ HTTP_REP_LINE_STATUS_404_SIZE,.-HTTP_REP_LINE_STATUS_404
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_404_SIZE,1,0x20
	HTTP_REP_LINE_STATUS_405:
		.ascii "405 Method Not Allowed"
		.equ HTTP_REP_LINE_STATUS_405_SIZE,.-HTTP_REP_LINE_STATUS_405
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_405_SIZE,1,0x20
	HTTP_REP_LINE_STATUS_414:
		.ascii "414 Request-URI Too Long"
		.equ HTTP_REP_LINE_STATUS_414_SIZE,.-HTTP_REP_LINE_STATUS_414
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_414_SIZE,1,0x20

		.equ HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,20

		.equ HTTP_REP_HEAD_CONTENT_TYPE_SIZE,40
	HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML:
		.ascii "text/html"
		.equ HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML_SIZE,.-HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML
		.fill HTTP_REP_HEAD_CONTENT_TYPE_SIZE-HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML_SIZE,1,0x20
	HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN:
		.ascii "text/plain"
		.equ HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN_SIZE,.-HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN
		.fill HTTP_REP_HEAD_CONTENT_TYPE_SIZE-HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN_SIZE,1,0x20

	send_buf:
	HTTP_REP_HEAD:
		.ascii "HTTP/1.1 "
	http_rep_line_status:
		.ascii "200 OK"
		.fill HTTP_REP_LINE_STATUS_SIZE-HTTP_REP_LINE_STATUS_200_SIZE,1,0x20
		.ascii "\r\n"
		.ascii "User-Agent: tx_http_srv/0.3\r\n"
		.ascii "Content-Length: "
	http_rep_head_content_length:
		.fill HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,1,0x20
		.ascii "\r\n"
		.ascii "Content-Type: "
	http_rep_head_content_type:
		.ascii "text/html"
		.fill HTTP_REP_HEAD_CONTENT_TYPE_SIZE-HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML_SIZE,1,0x20
		.ascii "\r\n"
		.ascii "Connection: close\r\n"
		.ascii "Pragma: no-cache\r\n"
		.ascii "Cache-Control: no-cache\r\n"
		.ascii "\r\n"
		.equ HTTP_REP_HEAD_SIZE,.-HTTP_REP_HEAD
	send_data_buf:
		.fill BUF_SIZE*2-HTTP_REP_HEAD_SIZE,1,0x58
		.equ SEND_DATA_BUF_SIZE,.-send_data_buf
		.equ SEND_BUF_SIZE,.-send_buf
	send_size:
		.quad 0 

	HTTP_REQ_DBG_ECHO:
		.ascii "/dbg/echo"
		.equ HTTP_REQ_DBG_ECHO_SIZE,.-HTTP_REQ_DBG_ECHO

	HTTP_REQ_DBG_HTTP:
		.ascii "/dbg/http"
		.equ HTTP_REQ_DBG_HTTP_SIZE,.-HTTP_REQ_DBG_HTTP

	HTTP_REP_DBG_HTTP_LINE_STR:
		.ascii "     LINE_SIZE: "
		.equ HTTP_REP_DBG_HTTP_LINE_STR_SIZE,.-HTTP_REP_DBG_HTTP_LINE_STR

	HTTP_REP_DBG_HTTP_HEAD_STR:
		.ascii "     HEAD_SIZE: "
		.equ HTTP_REP_DBG_HTTP_HEAD_STR_SIZE,.-HTTP_REP_DBG_HTTP_HEAD_STR

	HTTP_REP_DBG_HTTP_ALL_STR:
		.ascii "      ALL_SIZE: "
		.equ HTTP_REP_DBG_HTTP_ALL_STR_SIZE,.-HTTP_REP_DBG_HTTP_ALL_STR

	HTTP_REP_DBG_HTTP_MTHD_STR:
		.ascii "          MTHD: "
		.equ HTTP_REP_DBG_HTTP_MTHD_STR_SIZE,.-HTTP_REP_DBG_HTTP_MTHD_STR

	HTTP_REP_DBG_HTTP_URI_STR:
		.ascii "           URI: "
		.equ HTTP_REP_DBG_HTTP_URI_STR_SIZE,.-HTTP_REP_DBG_HTTP_URI_STR

	HTTP_REP_DBG_HTTP_VER_STR:
		.ascii "           VER: "
		.equ HTTP_REP_DBG_HTTP_VER_STR_SIZE,.-HTTP_REP_DBG_HTTP_VER_STR

	HTTP_REP_DBG_HTTP_HEAD_NUM_STR:
		.ascii "      HEAD_NUM: "
		.equ HTTP_REP_DBG_HTTP_HEAD_NUM_STR_SIZE,.-HTTP_REP_DBG_HTTP_HEAD_NUM_STR

	HTTP_REQ_CNT_IP:
		.ascii "/cnt/ip"
		.equ HTTP_REQ_CNT_IP_SIZE,.-HTTP_REQ_CNT_IP

	HTTP_REQ_CNTS_NUM:
		.ascii "/cnts/num"
		.equ HTTP_REQ_CNTS_NUM_SIZE,.-HTTP_REQ_CNTS_NUM
	cnts_num:
		.quad 10000000000

	HTTP_REQ_INDEX:
		.ascii "/"
		.equ HTTP_REQ_INDEX_SIZE,.-HTTP_REQ_INDEX

	index_file_name:
		.asciz "index_0_3.htm"
	index_file_fd:
		.quad -1
		.equ INDEX_FILE_BUF_SIZE,BUF_SIZE
	index_file_size:
		.quad -1
	index_file_buf:
		.fill INDEX_FILE_BUF_SIZE,1,0x58

	.equ HTTP_CHAR_CR,0x0d
	.equ HTTP_CHAR_LF,0x0a
	.equ HTTP_CHAR_SP,0x20
	.equ HTTP_CHAR_SLASH,'/
	.equ HTTP_CHAR_BACKSLASH,'\\
	.equ HTTP_CHAR_QUESTION,'?
	http_req_line_size:		.quad 0
	http_req_line_mthd_size:	.quad 0
	http_req_line_uri_ptr:		.quad 0
	http_req_line_uri_size:		.quad 0
	http_req_line_uri_abspath_size:	.quad 0
	http_req_line_uri_query_ptr:	.quad 0
	http_req_line_uri_query_size:	.quad 0
	http_req_line_ver_ptr:		.quad 0
	http_req_line_ver_size:		.quad 0
					.equ HTTP_REQ_HEAD_MAX_NUM,20
	http_req_head_num:		.quad 0
	http_req_head_line_ptr:		.quad 0
	http_req_head_line_size:	.quad 0
					.equ HTTP_REQ_HEAD_UNIT_SIZE,.-http_req_head_line_ptr
					.fill HTTP_REQ_HEAD_MAX_NUM*HTTP_REQ_HEAD_UNIT_SIZE,1,0
	http_req_head_size:		.quad 0
	http_req_head_host_ptr:		.quad 0
	http_req_head_host_size:		.quad 0
	http_req_head_length_ptr:	.quad 0
	http_req_head_length_size:	.quad 0
	http_req_body_ptr:		.quad 0
	http_req_body_size:		.quad 0

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
	cmp $0, %rax
	jle Lconn_close
	cmp $BUF_SIZE, %rax
	je Lhttp_rep_400_begin
	mov %rax,(recv_size)
Lconn_parse:
Lhttp_req_scan_begin:
Lhttp_req_scan_line_begin:
	mov %rax, %rdx
	mov %rax, %rcx
	movb $HTTP_CHAR_LF, %al
	mov $recv_buf, %rdi
	repne scasb
	jne Lhttp_rep_400_begin
	sub %rcx, %rdx
	mov %rdx, http_req_line_size
Lhttp_req_scan_line_end:
Lhttp_req_scan_hdr_begin:
	mov %rdi, http_req_head_line_ptr
	mov $http_req_head_line_ptr, %rbx
	mov $0, %rsi
	push %rcx
	movb $HTTP_CHAR_LF, %al
	/*mov %rdi, %rdi */
	/*mov %rcx, %rcx*/
0:
	mov %rcx, %rdx
	repne scasb
	jne Lhttp_rep_400_begin
	cmp $2, %rcx
	jl Lhttp_rep_400_begin
	sub %rcx, %rdx
	mov %rdx, 8(%rbx)
	inc %rsi
	lea 16(%rbx), %rbx
	mov %rdi, (%rbx)
	cmpb $HTTP_CHAR_CR, (%rdi)
	jne 0b
	cmpb $HTTP_CHAR_LF, 1(%rdi)
	jne 0b
	mov %rsi, http_req_head_num
	pop %rax
	sub %rcx, %rax
	mov %rax, http_req_head_size
	inc %rdi
	mov %rdi, http_req_body_ptr
Lhttp_req_scan_hdr_end:
Lhttp_req_scan_end:
Lhttp_req_scan_line_mthd_begin:
	movb $HTTP_CHAR_SP, %al
	mov $recv_buf, %rdi
	mov http_req_line_size, %rcx
	mov %rcx, %rdx
	repne scasb
	jnz Lhttp_rep_400_begin
	sub %rcx, %rdx
	dec %rdx
	mov %rdx, http_req_line_mthd_size
Lhttp_req_scan_line_mthd_end:
Lhttp_req_scan_line_uri_begin:
	mov %rdi, http_req_line_uri_ptr
	mov %rcx, %rdx
	movb $HTTP_CHAR_SP, %al
	/*mov http_req_line_uri_ptr, %rdi*/
	/*mov %rcx, %rcx*/
	repne scasb
	jnz Lhttp_rep_400_begin
	sub %rcx, %rdx
	dec %rdx
	mov %rdx, http_req_line_uri_size
Lhttp_req_scan_line_uri_end:
Lhttp_req_scan_line_ver_begin:
	mov %rdi, http_req_line_ver_ptr
	sub $2,%rcx
	mov %rcx, http_req_line_ver_size
Lhttp_req_scan_line_ver_end:
Lhttp_req_dbg_echo_begin:
	cmp $HTTP_REQ_DBG_ECHO_SIZE,http_req_line_uri_size
	jl Lhttp_req_dbg_echo_end
	mov http_req_line_uri_ptr,%rdi
	mov $HTTP_REQ_DBG_ECHO,%rsi
	mov $HTTP_REQ_DBG_ECHO_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_dbg_echo_end
	mov $0x20,%al
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN, %rsi
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN_SIZE, %rcx
	rep movsb
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov recv_size, %rax
	_tx_num_b64toa
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $HTTP_REP_HEAD, %rsi
	mov $HTTP_REP_HEAD_SIZE, %rdx
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
	cmp $HTTP_REQ_CNT_IP_SIZE,http_req_line_uri_size
	jl Lhttp_req_cnt_ip_end
	mov http_req_line_uri_ptr,%rdi
	mov $HTTP_REQ_CNT_IP,%rsi
	mov $HTTP_REQ_CNT_IP_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_cnt_ip_end
	mov conn_sock_addr.sin_addr,%eax
	mov $send_data_buf,%rdi
	_tx_inet_ntoa
	movb $':,(%rdi)
	inc %rdi
	mov conn_sock_addr.sin_port,%ax
	_tx_port_ntoa
	sub $send_data_buf, %rdi
	mov %rdi, send_size
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov send_size, %rax
	_tx_num_b64toa
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	mov send_size, %rdx
	add $HTTP_REP_HEAD_SIZE, %rdx
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_cnt_ip_end:
Lhttp_req_cnts_num_begin:
	cmp $HTTP_REQ_CNTS_NUM_SIZE,http_req_line_uri_size
	jl Lhttp_req_cnts_num_end
	mov http_req_line_uri_ptr,%rdi
	mov $HTTP_REQ_CNTS_NUM,%rsi
	mov $HTTP_REQ_CNTS_NUM_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_cnts_num_end
	mov cnts_num,%rax
	mov $send_data_buf, %rdi
	_tx_num_b64toa
	sub $send_data_buf, %rdi
	mov %rdi, send_size
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov send_size, %rax
	_tx_num_b64toa
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	mov send_size, %rdx
	add $HTTP_REP_HEAD_SIZE, %rdx
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_cnts_num_end:
Lhttp_req_dbg_http_begin:
	cmp $HTTP_REQ_DBG_HTTP_SIZE,http_req_line_uri_size
	jl Lhttp_req_dbg_http_end
	mov http_req_line_uri_ptr,%rdi
	mov $HTTP_REQ_DBG_HTTP,%rsi
	mov $HTTP_REQ_DBG_HTTP_SIZE,%rcx
	repe cmpsb
	jnz Lhttp_req_dbg_http_end

	mov $send_data_buf, %rdi
	mov $HTTP_REP_DBG_HTTP_LINE_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_LINE_STR_SIZE, %rcx
	rep movsb
	mov http_req_line_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_HEAD_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_HEAD_STR_SIZE, %rcx
	/*mov %rdi, %rdi*/
	rep movsb
	mov http_req_head_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_ALL_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_ALL_STR_SIZE, %rcx
	rep movsb
	mov recv_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_MTHD_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_MTHD_STR_SIZE, %rcx
	rep movsb
	mov http_req_line_mthd_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa
	movb $',,(%rdi)
	inc %rdi
	mov $recv_buf, %rsi
	mov http_req_line_mthd_size, %rcx
	/*mov %rdi, %rdi*/
	rep movsb

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_URI_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_URI_STR_SIZE, %rcx
	rep movsb
	mov http_req_line_uri_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa
	movb $',,(%rdi)
	inc %rdi
	mov http_req_line_uri_ptr, %rsi
	mov http_req_line_uri_size, %rcx
	/*mov %rdi, %rdi*/
	rep movsb

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_VER_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_VER_STR_SIZE, %rcx
	rep movsb
	mov http_req_line_ver_size, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa
	movb $',,(%rdi)
	inc %rdi
	mov http_req_line_ver_ptr, %rsi
	mov http_req_line_ver_size, %rcx
	/*mov %rdi, %rdi*/
	rep movsb

	movb $'\n,(%rdi)
	inc %rdi

	mov $HTTP_REP_DBG_HTTP_HEAD_NUM_STR, %rsi
	mov $HTTP_REP_DBG_HTTP_HEAD_NUM_STR_SIZE, %rcx
	rep movsb
	mov http_req_head_num, %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa

	movb $'\n,(%rdi)
	inc %rdi

	mov http_req_head_num, %rcx
	mov $http_req_head_line_ptr, %rbx
Lhttp_req_dbg_http_fill_head_begin:
	push %rcx
	movb $'*,(%rdi)
	inc %rdi
	movb $',,(%rdi)
	inc %rdi

	push %rbx
	lea 8(%rbx), %rax
	mov (%rax), %rax
	/*mov %rdi, %rdi*/
	_tx_num_b64toa
	pop %rbx
	movb $',,(%rdi)
	inc %rdi
	mov (%rbx), %rsi
	mov 8(%rbx), %rcx
	/*mov %rdi, %rdi*/
	rep movsb
	lea 16(%rbx), %rbx

	pop %rcx
	loopnz Lhttp_req_dbg_http_fill_head_begin
Lhttp_req_dbg_http_fill_head_end:
	sub $send_data_buf, %rdi
	mov %rdi, send_size
	mov $0x20,%al
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN, %rsi
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN_SIZE, %rcx
	rep movsb
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov send_size, %rax
	_tx_num_b64toa
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $send_buf, %rsi
	mov send_size, %rdx
	add $HTTP_REP_HEAD_SIZE,%rdx
	mov $1, %rax
	syscall
	jmp Lconn_close
Lhttp_req_dbg_http_end:
Lhttp_req_index_begin:
	cmp $HTTP_REQ_INDEX_SIZE,http_req_line_uri_size
	jne Lhttp_req_index_end

	cmp $0, index_file_size
	jg Lhttp_req_index_write_begin

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
	mov $index_file_buf, %rsi
	mov $INDEX_FILE_BUF_SIZE, %rdx
	mov $0, %rax
	syscall
	mov %rax, index_file_size
	#syscall: int close(int fd)
	mov index_file_fd, %rdi
	mov $3, %rax
	syscall
Lhttp_req_index_write_begin:
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov index_file_size, %rax
	_tx_num_b64toa
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $HTTP_REP_HEAD, %rsi
	mov $HTTP_REP_HEAD_SIZE, %rdx
	mov $1, %rax
	syscall
	cmp $0,%rax
	jle Lconn_close
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock, %rdi
	mov $index_file_buf, %rsi
	mov index_file_size,%rdx
	mov $1, %rax
	syscall
Lhttp_req_index_write_end:
	jmp Lconn_close
Lhttp_req_index_end:
Lhttp_rep_404_begin:
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_LINE_STATUS_404_SIZE, %rax
	_tx_num_b64toa
	mov $HTTP_REP_LINE_STATUS_404,%rsi
	mov $http_rep_line_status,%rdi
	mov $HTTP_REP_LINE_STATUS_404_SIZE,%rcx
	mov %rcx,%rdx
	add $HTTP_REP_HEAD_SIZE,%rdx
	rep movsb
	mov $HTTP_REP_LINE_STATUS_404,%rsi
	mov $send_data_buf,%rdi
	mov $HTTP_REP_LINE_STATUS_404_SIZE,%rcx
	rep movsb
	jmp Lhttp_rep_xxx_begin
Lhttp_rep_404_end:
Lhttp_rep_400_begin:
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_LINE_STATUS_400_SIZE, %rax
	_tx_num_b64toa
	mov $HTTP_REP_LINE_STATUS_400,%rsi
	mov $http_rep_line_status,%rdi
	mov $HTTP_REP_LINE_STATUS_400_SIZE,%rcx
	mov %rcx,%rdx
	add $HTTP_REP_HEAD_SIZE,%rdx
	rep movsb
	mov $HTTP_REP_LINE_STATUS_400,%rsi
	mov $send_data_buf,%rdi
	mov $HTTP_REP_LINE_STATUS_400_SIZE,%rcx
	rep movsb
	jmp Lhttp_rep_xxx_begin
Lhttp_rep_400_end:
Lhttp_rep_414_begin:
	mov $0x20,%al
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_HEAD_CONTENT_LENGTH_SIZE,%rcx
	rep stosb
	mov $http_rep_head_content_length, %rdi
	mov $HTTP_REP_LINE_STATUS_414_SIZE, %rax
	_tx_num_b64toa
	mov $HTTP_REP_LINE_STATUS_414,%rsi
	mov $http_rep_line_status,%rdi
	mov $HTTP_REP_LINE_STATUS_414_SIZE,%rcx
	mov %rcx,%rdx
	add $HTTP_REP_HEAD_SIZE,%rdx
	rep movsb
	mov $HTTP_REP_LINE_STATUS_414,%rsi
	mov $send_data_buf,%rdi
	mov $HTTP_REP_LINE_STATUS_414_SIZE,%rcx
	rep movsb
	jmp Lhttp_rep_xxx_begin
Lhttp_rep_414_end:
Lhttp_rep_xxx_begin:
	mov $0x20,%al
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN, %rsi
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_PLAIN_SIZE, %rcx
	rep movsb
	#syscall: ssize_t write(int fd, void *buf, size_t count)
	mov conn_sock,%rdi
	mov $send_buf,%rsi
	/*mov %rdx,%rdx*/
	mov $1,%rax
	syscall
Lhttp_rep_xxx_end:
	mov $0x20,%al
	mov $http_rep_line_status,%rdi
	mov $HTTP_REP_LINE_STATUS_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_LINE_STATUS_200,%rsi
	mov $http_rep_line_status,%rdi
	mov $HTTP_REP_LINE_STATUS_200_SIZE,%rcx
	rep movsb
/*
Lconn_shutdown:
	#syscall: int shutdown(int fd, int how)
	mov conn_sock, %rdi
	mov $0, %rsi
	mov $48, %rax
	syscall
	jmp Lconn_read
*/
Lconn_close:
	mov $0x20,%al
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_SIZE,%rcx
	rep stosb
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML, %rsi
	mov $http_rep_head_content_type, %rdi
	mov $HTTP_REP_HEAD_CONTENT_TYPE_TEXT_HTML_SIZE, %rcx
	rep movsb
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
