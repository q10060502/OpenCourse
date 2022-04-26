#include "tx.h"

#define NATIVE_IP "0.0.0.0"
#define NATIVE_PORT 1980

int main(int argc, char *argv[])
{

	char native_ip[48] = NATIVE_IP;
	unsigned int native_port = NATIVE_PORT;

	if(argc>1) {
		strncpy(native_ip, argv[1], sizeof(native_ip)-1);
	}
	if(argc>2) {
		native_port = atoi(argv[2]);
	}

	printf("native_ip: %s\nnative port: %u\n", native_ip, native_port);

	tx_sock_t sock = TX_SOCK_INVALID;

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	sock = tx_sock_open(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(TX_SOCK_INVALID == sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	int is_reuseaddr = 1;
	if(TX_SOCK_ERR==tx_sock_set_opt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&is_reuseaddr, sizeof(int))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_set_opt err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(native_port);
	sockaddr4.sin_addr.s_addr = inet_addr(native_ip);

	if(TX_SOCK_ERR == tx_sock_bind(sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	char buf[32] = "0123456789";
	while(1) {
		struct sockaddr_in remote_sockaddr;
		socklen_t remote_sockaddr_size = sizeof(remote_sockaddr);
		int recv_size = tx_sock_recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote_sockaddr, &remote_sockaddr_size);
		if(recv_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_recvfrom err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(recv_size==0) {
			printf("tx_sock_recvfrom closed\n");
			break;
		}
		printf("[%s:%d] ", inet_ntoa(remote_sockaddr.sin_addr), ntohs(remote_sockaddr.sin_port));
		for(int i=0;i<recv_size;i++) {
			printf("%c", buf[i]);
		}
		printf("\n");
	}
quit:
	tx_sock_close(sock);
	tx_socklib_cleanup();

	return 0;
}
