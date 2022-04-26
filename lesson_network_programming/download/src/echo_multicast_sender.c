#include "tx.h"

#define PORT 1980
#define MULTICAST_IP "239.0.0.1"
//#define MULTICAST_IP "224.0.0.1"

int main(void)
{
	tx_sock_t sock = TX_SOCK_INVALID;

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	sock = tx_sock_open(AF_INET, SOCK_DGRAM, 0);
	if(TX_SOCK_INVALID == sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("sock: %ld\n", (long)sock);

	
	int ms = 2000;
	if(TX_SOCK_ERR==tx_sock_set_rcvtimeopt(sock, ms)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_set_opt SO_RCVTIMEO err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(PORT);
	sockaddr4.sin_addr.s_addr = inet_addr(MULTICAST_IP);

	char buf[32] = "0123456789";
	while(1) {
		printf("Input: ");
		if(NULL==fgets(buf, sizeof(buf), stdin)) {
			break;
		}
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

		while(1) {
			int recv_size = tx_sock_recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
			if(recv_size<0) {
				int err_num = tx_sock_get_errnum();
				if(tx_sock_is_errtimeo(err_num)) {
					printf("tx_sock_recvfrom timeout\n");
					break;
				}
				printf("tx_sock_sendto err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				goto quit;
			}
			if(recv_size==0) {
				printf("tx_sock_recvfrom closed\n");
				goto quit;
			}
			for(int i=0;i<recv_size;i++) {
				printf("0x%x, ", buf[i]);
			}
			printf("\n");
		}
	}
quit:
	tx_sock_close(sock);
	tx_socklib_cleanup();

	return 0;
}
