#include "tx.h"

#define PORT 1980

void sockaddr_in_printf(struct sockaddr_in *paddr)
{
	printf("----------\n");
	printf("sockaddr_in size: %lu\n", (unsigned long)sizeof(struct sockaddr_in));
	printf("sin_family: 0x%04x\n", paddr->sin_family);
	printf("sin_port: 0x%04x\n", paddr->sin_port);
	printf("sin_addr: 0x%08lx\n", (unsigned long)paddr->sin_addr.s_addr);
	printf("sin_zero: ");
	for(int i=0;i<8;i++) {
		printf("0x%02x, ", paddr->sin_zero[i]);
	}
	printf("\n");
}

void sockaddr_in6_printf(struct sockaddr_in6 *paddr)
{
	printf("----------\n");
	printf("sockaddr_in6 size: %lu\n", (unsigned long)sizeof(struct sockaddr_in6));
	printf("sin6_family: 0x%04x\n", paddr->sin6_family);
	printf("sin6_port: 0x%04x\n", paddr->sin6_port);
	printf("sin6_flowinfo: 0x%08lx\n", (unsigned long)paddr->sin6_flowinfo);
	printf("sin6_addr: ");
	for(int i=0;i<16;i++) {
		printf("0x%02x, ", paddr->sin6_addr.s6_addr[i]);
	}
	printf("\n");
	printf("sin6_scope_id: 0x%08lx\n", (unsigned long)paddr->sin6_scope_id);
}

void sockaddr_in_init()
{
	struct sockaddr_in addr;

	sockaddr_in_printf(&addr);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	sockaddr_in_printf(&addr);
}

void sockaddr_in6_init()
{
	struct sockaddr_in6 addr6;

	sockaddr_in6_printf(&addr6);

	memset(&addr6, 0, sizeof(addr6));
	addr6.sin6_family = AF_INET6;
	addr6.sin6_port = htons(PORT);
	addr6.sin6_addr = in6addr_loopback;
	sockaddr_in6_printf(&addr6);
}

int main(void)
{
	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	printf("sizeof(struct sockaddr): %lu\n", (unsigned long)sizeof(struct sockaddr));
	printf("sizeof(struct sockaddr_in): %lu\n", (unsigned long)sizeof(struct sockaddr_in));
	printf("sizeof(struct sockaddr_in6): %lu\n", (unsigned long)sizeof(struct sockaddr_in6));
	printf("sizeof(struct sockaddr_storage): %lu\n", (unsigned long)sizeof(struct sockaddr_storage));

	sockaddr_in_init();
	sockaddr_in6_init();

quit:
	tx_socklib_cleanup();

	return 0;
}
