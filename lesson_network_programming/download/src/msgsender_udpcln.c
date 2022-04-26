#include "tx.h"

#define REMOTE_IP "127.0.0.1"
#define REMOTE_PORT 1980

int main(int argc, char *argv[])
{

	char remote_ip[48] = REMOTE_IP;
	unsigned int remote_port = REMOTE_PORT;

	if(argc>1) {
		strncpy(remote_ip, argv[1], sizeof(remote_ip)-1);
	}
	if(argc>2) {
		remote_port = atoi(argv[2]);
	}

	printf("remote_ip: %s\nremote port: %u\n", remote_ip, remote_port);

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

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(remote_port);
	sockaddr4.sin_addr.s_addr = inet_addr(remote_ip);

	char buf[32] = "HELO";
	while(1) {
		int send_size = tx_sock_sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4));
		if(send_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_sendto err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(send_size==0) {
			printf("tx_sock_sendto closed\n");
			break;
		}
		printf("Input: ");
		if(NULL==fgets(buf, sizeof(buf), stdin)) {
			break;
		}
	}
quit:
	tx_sock_close(sock);
	tx_socklib_cleanup();

	return 0;
}
