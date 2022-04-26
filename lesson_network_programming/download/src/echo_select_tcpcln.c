#include "tx.h"

#define PORT 1980

int main(void)
{
	tx_sock_t cln_sock = TX_SOCK_INVALID;
	fd_set read_fds, write_fds;

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	cln_sock = tx_sock_open(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(TX_SOCK_INVALID == cln_sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("cln_sock: %ld\n", (long)cln_sock);

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(PORT);
	sockaddr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(TX_SOCK_ERR == tx_sock_connect(cln_sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_connect err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	unsigned int sockaddr4_size = sizeof(sockaddr4);
	if(TX_SOCK_ERR == tx_sock_get_native_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_get_native_sockaddr err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("%s:%d\n", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

	if(TX_SOCK_ERR == tx_sock_get_remote_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_get_remote_sockaddr err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("%s:%d\n", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_SET(cln_sock, &read_fds);
	FD_SET(cln_sock, &write_fds);

	char buf[32] = "0123456789";
	while(1) {
		FD_SET(cln_sock, &read_fds);
		int fd_num = tx_io_select(cln_sock+1, &read_fds, &write_fds, NULL, NULL);
		if(TX_SOCK_ERR == fd_num) {
			int err_num = tx_sock_get_errnum();
			printf("select err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		printf("fd_num: %d\n",fd_num);

		if(FD_ISSET(cln_sock, &write_fds)) {
			if(NULL==fgets(buf, sizeof(buf), stdin)) {
				break;
			}
			int send_size = tx_sock_send(cln_sock, buf, strlen(buf), 0);
			if(send_size<0) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_send err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				break;
			}
			if(send_size==0) {
				printf("tx_sock_send closed\n");
				break;
			}
			FD_CLR(cln_sock, &write_fds);
			fd_num--;
			if(fd_num==0) continue;
		}

		int recv_size = tx_sock_recv(cln_sock, buf, sizeof(buf), 0);
		if(recv_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_recv err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(recv_size==0) {
			printf("tx_sock_recv closed\n");
			break;
		}
		for(int i=0;i<recv_size;i++) {
			printf("0x%x, ", buf[i]);
		}
		printf("\n");
		FD_SET(cln_sock, &write_fds);
	}
quit:
	tx_sock_close(cln_sock);
	tx_socklib_cleanup();

	return 0;
}
