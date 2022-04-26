#include "tx.h"

#define IP "127.0.0.1"
#define PORT 1980

int main(int argc, char *argv[])
{
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
	sockaddr4.sin_port = htons(port);
	sockaddr4.sin_addr.s_addr = inet_addr(ip);
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

	char buf[4096] = "GET / HTTP/1.1\r\n\r\n";
	int send_size = tx_sock_send(cln_sock, buf, strlen(buf), 0);
	if(send_size<0) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_send err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	if(send_size==0) {
		printf("tx_sock_send closed\n");
		goto quit;
	}

	int recv_size = tx_sock_recv(cln_sock, buf, sizeof(buf)-1, 0);
	if(recv_size<0) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_recv err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	if(recv_size==0) {
		printf("tx_sock_recv closed\n");
		goto quit;
	}
	buf[recv_size] = 0;
	printf("%s", buf);
quit:
	tx_sock_close(cln_sock);
	tx_socklib_cleanup();

	return 0;
}
