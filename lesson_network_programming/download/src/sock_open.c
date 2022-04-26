#include "tx.h"

int main(void)
{
	tx_socklib_startup();

	printf("sizeof(tx_sock_t): %lu\n", (unsigned long)sizeof(tx_sock_t));

	int n = 1;
	tx_sock_t sock;
	do {
		sock = tx_sock_open(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		printf("%d. sock: %ld\n", n, (long)sock);
		n++;
	} while(sock<0);

	tx_socklib_cleanup();

	return 0;
}
