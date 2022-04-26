#include "tx.h"

#if defined(WIN32)
	//struct in_addr ipv4_num = {{S_addr:0x0100007f}};
	struct in_addr ipv4_num = {{{0x7f, 0x00, 0x00, 0x01}}};
	char ipv6_str[48] = "[0000:0000:0000:0000:0000:0000:0000:0001]:1980";
#else
	struct in_addr ipv4_num = {0x0100007f};
	char ipv6_str[48] = "0000:0000:0000:0000:0000:0000:0000:0001";
#endif

	char ipv4_str[16] = "127.0.0.1";
	struct in6_addr ipv6_num = IN6ADDR_LOOPBACK_INIT;

void in_addr_str_to_num()
{
	printf("\n--str_to_num: inet_addr--\n");
	printf("ipv4_str: %s", ipv4_str);
	printf("\t--> ");
	printf("ipv4_num: 0x%08lx", (unsigned long)inet_addr(ipv4_str));
	printf("\n");

#if defined(WIN32)
	struct sockaddr_in addr;
	int addr_size = sizeof(addr);
	printf("\n--str_to_num: WSAStringToAddress--\n");
	printf("ipv4_str: %s", ipv4_str);
	printf("\t--> ");
	if(0!=WSAStringToAddress(ipv4_str, AF_INET, NULL, (struct sockaddr*)&addr, &addr_size)) {
		printf("WSAStringToAddress error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else { 
		printf("ipv4_num: 0x%08lx", (unsigned long)addr.sin_addr.s_addr);
	}
	printf("\n");
#else
	struct in_addr tmp_num;

	printf("\n--str_to_num: inet_pton--\n");
	printf("ipv4_str: %s", ipv4_str);
	printf("\t--> ");
	if(0>=inet_pton(AF_INET, ipv4_str, &tmp_num)) {
		printf("inet_pton error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		printf("ipv4_num: 0x%08lx", (unsigned long)tmp_num.s_addr);
	}
	printf("\n");
#endif
}

void in_addr_num_to_str()
{
	printf("\n--num_to_str: inet_ntoa--\n");
	printf("ipv4_num: 0x%08lx", (unsigned long)ipv4_num.s_addr);
	printf("\t--> ");
	printf("ipv4_str: %s", inet_ntoa(ipv4_num));
	printf("\n");

	char tmp_str[4096];
#if defined(WIN32)
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr = ipv4_num;
	unsigned long tmp_str_size = sizeof(tmp_str);
	printf("\n--num_to_str: WSAAddressToString--\n");
	printf("ipv4_num: 0x%08lx", (unsigned long)ipv4_num.s_addr);
	printf("\t--> ");
	if(0!=WSAAddressToString((struct sockaddr*)&addr, sizeof(addr), NULL, tmp_str, &tmp_str_size)) {
		printf("WSAAddressToString error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		printf("ipv4_str: %s", tmp_str);
	}
	printf("\n");
#else
	printf("\n--num_to_str: inet_ntop--\n");
	printf("ipv4_num: 0x%08lx", (unsigned long)ipv4_num.s_addr);
	printf("\t--> ");
	if(0>=inet_ntop(AF_INET, &ipv4_num, tmp_str, sizeof(tmp_str))) {
		printf("inet_ntop error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		printf("ipv4_str: %s", tmp_str);
	}
	printf("\n");
#endif
}

void in6_addr_printf(struct in6_addr *pin6_addr)
{
	printf("ipv6_num: ");
	for(int i=0;i<16;i++) {
		if(i%8==0) printf("\n");
		printf("0x%02x, ", pin6_addr->s6_addr[i]);
	}
}

void in6_addr_str_to_num()
{
#if defined(WIN32)
	struct sockaddr_in6 addr;
	int addr_size = sizeof(addr);
	printf("\n--str_to_num: WSAStringToAddress--\n");
	printf("ipv6_str: %s", ipv6_str);
	printf("\n--> ");
	if(0!=WSAStringToAddress(ipv6_str, AF_INET6, NULL, (struct sockaddr*)&addr, &addr_size)) {
		printf("WSAStringToAddress error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else { 
		in6_addr_printf(&addr.sin6_addr);
		printf("\nport: %u", ntohs(addr.sin6_port));
	}
	printf("\n");
#else
	struct in6_addr tmp_num;
	printf("\n--str_to_num: inet_pton--\n");
	printf("ipv6_str: %s", ipv6_str);
	printf("\n--> ");
	if(0>=inet_pton(AF_INET6, ipv6_str, &tmp_num)) {
		printf("inet_pton error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		in6_addr_printf(&tmp_num);
	}
	printf("\n");
#endif
}

void in6_addr_num_to_str()
{
	char tmp_str[4096];
#if defined(WIN32)
	struct sockaddr_in6 addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(1980);
	addr.sin6_addr = ipv6_num;
	unsigned long tmp_str_size = sizeof(tmp_str);
	printf("\n--num_to_str: WSAAddressToString--\n");
	in6_addr_printf(&ipv6_num);
	printf("\n--> ");
	if(0!=WSAAddressToString((struct sockaddr*)&addr, sizeof(addr), NULL, tmp_str, &tmp_str_size)) {
		printf("WSAAddressToString error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		printf("ipv6_str: %s", tmp_str);
	}
	printf("\n");
#else
	printf("\n--num_to_str: inet_ntop--\n");
	in6_addr_printf(&ipv6_num);
	printf("\n--> ");
	if(0>=inet_ntop(AF_INET6, &ipv6_num, tmp_str, sizeof(tmp_str))) {
		printf("inet_ntop error: %s\n", tx_sock_get_errstr(tx_sock_get_errnum()));
	} else {
		printf("ipv6_str: %s", tmp_str);
	}
	printf("\n");
#endif
}

int main(void)
{
	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	printf("sizeof(struct in_addr): %lu\n", (unsigned long)sizeof(struct in_addr));
	printf("sizeof(struct in6_addr): %lu\n", (unsigned long)sizeof(struct in6_addr));

	in_addr_str_to_num();
	in_addr_num_to_str();
	in6_addr_str_to_num();
	in6_addr_num_to_str();
	tx_socklib_cleanup();
quit:
	return 0;
}
