#include "tx.h"

int main(void)
{
	int r = 0;
	r = tx_socklib_startup();
	if(0!=r) {
		char *p = tx_sock_get_errstr(r);
		printf("tx_sock_open err: %d, %s\n", r, p);
	}

	r = tx_socklib_cleanup();
	if(0!=r) {
		int r = tx_sock_get_errnum();
		char *p = tx_sock_get_errstr(r);
		printf("tx_sock_open err: %d, %s\n", r, p);
		tx_sock_free_errstr(p);
	}

	return r;
}
