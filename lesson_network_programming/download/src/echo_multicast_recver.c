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

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(PORT);
	sockaddr4.sin_addr.s_addr = htonl(INADDR_ANY);
	if(TX_SOCK_ERR == tx_sock_bind(sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	struct ip_mreq ip_mreq;
	memset(&ip_mreq, 0, sizeof(ip_mreq));
	ip_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	ip_mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
	if(TX_SOCK_ERR==tx_sock_set_opt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&ip_mreq, sizeof(ip_mreq))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_set_opt  IP_ADD_MEMBERSHIP err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	char buf[4];
	while(1) {
		unsigned int sockaddr4_size;
		sockaddr4_size = sizeof(sockaddr4);
		int recv_size = tx_sock_recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size);
		if(recv_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_recvfrom err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(recv_size==0) break;

		printf("%s:%d --> ", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));
		for(int i=0;i<recv_size;i++) {
			printf("0x%x, ", buf[i]);
		}
		printf("\n");

		int send_size = tx_sock_sendto(sock, buf, recv_size, 0, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4));
		if(send_size<0) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_sendto err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			break;
		}
		if(send_size==0) break;
	}

	if(TX_SOCK_ERR==tx_sock_set_opt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const void*)&ip_mreq, sizeof(ip_mreq))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_set_opt IP_DROP_MEMBERSHIP err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
quit:
	tx_sock_close(sock);
	tx_socklib_cleanup();

	return 0;
}
