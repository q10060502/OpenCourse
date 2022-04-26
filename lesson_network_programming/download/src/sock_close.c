#include "tx.h"

int main(void)
{
	tx_socklib_startup();

	tx_sock_t sock;
	sock = tx_sock_open(AF_INET, SOCK_STREAM, 0);
	printf("sock: %ld\n", (long)sock);

	tx_sock_close(sock);

	tx_socklib_cleanup();

	return 0;
}
