#include "tx.h"

#define IP "0.0.0.0"
#define PORT 1980

int main(int argc, char *argv[])
{
	tx_sock_t srv_sock = TX_SOCK_INVALID;
	tx_sock_t cln_sock = TX_SOCK_INVALID;

	char ip[32] = IP;
	unsigned short port = PORT;

	if(argc>1) {
		strncpy(ip, argv[1], sizeof(ip)-1);
	}
	if(argc>2) {
		port = atoi(argv[2]);
	}
	printf("ip: %s\n", ip);
	printf("port: %u\n", port);


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

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(port);
	sockaddr4.sin_addr.s_addr = inet_addr(ip);
	if(TX_SOCK_ERR == tx_sock_bind(srv_sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	if(TX_SOCK_ERR == tx_sock_listen(srv_sock, SOMAXCONN)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_listen err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	while(1) {
		unsigned int sockaddr4_size = sizeof(sockaddr4);
		cln_sock = tx_sock_accept(srv_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size);
		if(TX_SOCK_INVALID == cln_sock) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_accept err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			goto quit;
		}
		printf("cln_sock: %ld, %s:%d\n", (long)cln_sock, inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

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

		char recv_buf[1024];
		char send_buf[4096];
		while(1) {
			int recv_size = tx_sock_recv(cln_sock, recv_buf, sizeof(recv_buf), 0);
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
				printf("0x%x, ", recv_buf[i]);
			}
			printf("\n");
			
			int send_size = sprintf(send_buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", recv_size);

			memcpy(send_buf + send_size, recv_buf, recv_size);

			send_size = tx_sock_send(cln_sock, send_buf, send_size + recv_size, 0);
			if(send_size<0) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_send err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				break;
			}
			if(send_size==0) {
				printf("tx_sock_send closed\n");
				break;
			}
		}
		tx_sock_close(cln_sock);
	}
quit:
	tx_sock_close(srv_sock);
	tx_socklib_cleanup();

	return 0;
}
