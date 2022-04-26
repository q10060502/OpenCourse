#include "tx.h"

#define PORT 1980

int main(void)
{
	tx_sock_t srv_sock = TX_SOCK_INVALID;
	tx_sock_t cln_sock = TX_SOCK_INVALID;

	tx_sock_t cln_socks[FD_SETSIZE];
	int cln_socks_max_num;
	int cln_socks_num;
	int cln_socks_pos;
	fd_set all_fds, read_fds;
	int max_fd;

	cln_socks_max_num = sizeof(cln_socks)/sizeof(tx_sock_t);
	cln_socks_num = 0;
	cln_socks_pos = 0;
	for(int i=0;i<cln_socks_max_num;i++) {
		cln_socks[i] = TX_SOCK_INVALID;
	}

	FD_ZERO(&all_fds);
	FD_ZERO(&read_fds);

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	srv_sock = tx_sock_open(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(TX_SOCK_INVALID == srv_sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("srv_sock: %ld\n", (long)srv_sock);

	int is_reuseaddr = 1;
	if(TX_SOCK_ERR==tx_sock_set_opt(srv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&is_reuseaddr, sizeof(int))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_set_opt err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(PORT);
	sockaddr4.sin_addr.s_addr = htonl(INADDR_ANY);
	if(TX_SOCK_ERR == tx_sock_bind(srv_sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("port: %d\n", PORT);

	if(TX_SOCK_ERR == tx_sock_listen(srv_sock, SOMAXCONN)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_listen err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	FD_SET(srv_sock, &all_fds);
	cln_socks[cln_socks_pos++] = srv_sock;
	cln_socks_num++;
	max_fd = srv_sock;

	while(1) {
		read_fds = all_fds;
		int fd_num = tx_io_select(max_fd+1, &read_fds, NULL, NULL, NULL);
		if(TX_SOCK_ERR == fd_num) {
			int err_num = tx_sock_get_errnum();
			printf("select err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			goto quit;
		}
		printf("fd_num: %d\n",fd_num);

		if(FD_ISSET(srv_sock, &read_fds)) {
			unsigned int sockaddr4_size = sizeof(sockaddr4);
			cln_sock = tx_sock_accept(srv_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size);
			if(TX_SOCK_INVALID == cln_sock) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_accept err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				goto accept_quit;
			}
			printf("tx_sock_accept cln_sock(%ld) %s:%d\n", (long)cln_sock, inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

			if(TX_SOCK_ERR == tx_sock_get_native_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_get_native_sockaddr cln_sock(%ld) err: %d, %s\n", (long)cln_sock, err_num, tx_sock_get_errstr(err_num));
			} else {
				printf("tx_sock_get_native_sockaddr cln_sock(%ld) %s:%d\n", (long)cln_sock, inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));
			}

			if(TX_SOCK_ERR == tx_sock_get_remote_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_get_remote_sockaddr cln_sock(%ld) err: %d, %s\n", (long)cln_sock, err_num, tx_sock_get_errstr(err_num));
			} else {
				printf("tx_sock_get_remote_sockaddr cln_sock(%ld) %s:%d\n", (long)cln_sock, inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));
			}

			printf("cln_sock(%ld) check cln_socks_num/cln_socks_max_num: %d/%lu\n", (long)cln_sock, cln_socks_num, (unsigned long)cln_socks_max_num);
			if(cln_socks_num>=cln_socks_max_num) {
				printf("srv_sock(%ld) is full while accepting cln_sock(%ld)\n", (long)srv_sock, (long)cln_sock);
				tx_sock_close(cln_sock);
				goto accept_quit;
			}

			while(cln_socks[cln_socks_pos]!=TX_SOCK_INVALID) cln_socks_pos++; 
			cln_socks[cln_socks_pos++] = cln_sock;
			if(max_fd<cln_sock) max_fd = cln_sock;
			FD_SET(cln_sock, &all_fds);
			cln_socks_num++;
			printf("srv_sock(%ld) cln_socks[%d](%ld) opened\n", (long)srv_sock, cln_socks_pos-1, (long)cln_sock);
		accept_quit:
			fd_num--;
			if(fd_num==0) continue;

		}

		char buf[4];
		for(int i=0;i<cln_socks_max_num;i++) {

			if(cln_socks[i]==TX_SOCK_INVALID) continue;

			if(FD_ISSET(cln_socks[i], &read_fds)) {
			printf("cln_socks[%d](%ld) read_fds\n", i, (long)cln_socks[i]);
				int recv_size = tx_sock_recv(cln_socks[i], buf, sizeof(buf), 0);
				if(recv_size<0) {
					int err_num = tx_sock_get_errnum();
					printf("cln_socks[%d](%ld) tx_sock_recv err: %d, %s\n", i, (long)cln_socks[i], err_num, tx_sock_get_errstr(err_num));
					goto read_fds_close;
				}
				if(recv_size==0) {
					printf("cln_socks[%d](%ld) tx_sock_recv closed\n", i, (long)cln_socks[i]);
					goto read_fds_close;
				}

				printf("cln_socks[%d](%ld) tx_sock_recv recv_size: %d\n", i, (long)cln_socks[i], recv_size);
				for(int i=0;i<recv_size;i++) {
					printf("0x%x, ", buf[i]);
				}
				printf("\n");

				int send_size = tx_sock_send(cln_socks[i], buf, recv_size, 0);
				if(send_size<0) {
					int err_num = tx_sock_get_errnum();
					printf("cln_socks[%d](%ld) tx_sock_send err: %d, %s\n", i, (long)cln_socks[i], err_num, tx_sock_get_errstr(err_num));
					goto read_fds_close;
				}
				if(send_size==0) {
					printf("cln_socks[%d](%ld) tx_sock_send closed\n", i, (long)cln_socks[i]);
					goto read_fds_close;
				}
				printf("cln_socks[%d](%ld) tx_sock_send send_size: %d\n", i, (long)cln_socks[i], send_size);
				goto read_fds_quit;
			read_fds_close:
				FD_CLR(cln_socks[i], &all_fds);
				tx_sock_close(cln_socks[i]);
				if(cln_socks_pos>i) cln_socks_pos=i;
				if(max_fd==cln_socks[i]) max_fd--;
				cln_socks[i] = TX_SOCK_INVALID;
				cln_socks_num--;
			read_fds_quit:
				fd_num--;
				if(fd_num==0) break;
			}
		}
	}
quit:
	tx_sock_close(cln_sock);
	tx_sock_close(srv_sock);
	tx_socklib_cleanup();

	return 0;
}
