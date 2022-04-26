#include "tx.h"

int main(int argc, char *argv[])
{
	int r = tx_socklib_startup();
	if(0!=r) {
		printf("tx_socklib_startup err: %d, %s\n", r, tx_sock_get_errstr(r));
		goto quit;
	}
	
	struct in_addr addr;
	addr.s_addr = ntohl(INADDR_LOOPBACK);
	tx_mem_dump(&addr, sizeof(addr));

	char *p = inet_ntoa(addr);
	printf("%s\n", p);
quit:
	tx_socklib_cleanup();
	return r;
}
