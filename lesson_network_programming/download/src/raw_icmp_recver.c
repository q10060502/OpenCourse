#include "tx.h"

int main(void)
{
	tx_sock_t sock = TX_SOCK_INVALID;

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	sock = tx_sock_open(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(TX_SOCK_INVALID == sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("sock: %ld\n", (long)sock);

#if defined(win32)
	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	//sockaddr4.sin_port = htons(PORT);
	sockaddr4.sin_addr.s_addr = htonl(INADDR_ANY);
	if(TX_SOCK_ERR == tx_sock_bind(sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
#endif

	char buf[4096];
	while(1) {
		struct sockaddr_in sockaddr4;
		unsigned int sockaddr4_size;
		memset(&sockaddr4, 0, sizeof(sockaddr4));
		sockaddr4_size = sizeof(sockaddr4);
		int recv_size = tx_sock_recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size);
		if(recv_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_recvfrom err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(recv_size==0) {
			printf("tx_sock_recvfrom closed\n");
			break;
		}

		printf("%s:%d --> ", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));
		for(int i=0;i<recv_size;i++) {
			printf("0x%x, ", buf[i]);
		}
		printf("\n");
	}
quit:
	tx_sock_close(sock);
	tx_socklib_cleanup();

	return 0;
}
