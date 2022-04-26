#include "tx.h"

int main(int argc, char *argv[])
{
	char *ip = "127.0.0.1"; //255.255.255.255?

	if(argc>1) {
		ip = argv[1];
	}

	int r = tx_socklib_startup();
	if(0!=r) {
		printf("tx_socklib_startup err: %d, %s\n", r, tx_sock_get_errstr(r));
		goto quit;
	}
	
	struct in_addr addr;
	addr.s_addr = inet_addr(ip);
	tx_mem_dump(&addr, sizeof(addr));
quit:
	tx_socklib_cleanup();
	return r;
}
