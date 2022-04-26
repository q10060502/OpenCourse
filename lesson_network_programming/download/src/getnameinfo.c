#include "tx.h"

void getnameinfo_test(char *ip, short port)
{
	struct sockaddr_in sockaddr;
	char host[32];
	char service[32];

	unsigned int a, b, c, d;
	unsigned long ip_num;
	int n = sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
	if(n<4) {
		printf("sscanf err\n");
		return;
	}
	printf("a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
	ip_num = a<<24 | b<<16 | c<<8 | d;
	printf("ip_num: %#lx\n", ip_num);
	
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	sockaddr.sin_addr.s_addr = htonl(ip_num);

	if(0!=getnameinfo((struct sockaddr*)&sockaddr, sizeof(sockaddr), host, sizeof(host), service, sizeof(service), 0)) {
		int err_num = tx_sock_get_errnum();
		printf("getnameinfo err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		return;
	}

	printf("host: %s\nservice: %s\n", host, service);
	
}

int main(int argc, char *argv[])
{
	char ip[32] = "127.0.0.1";
	short port = 80;

	if(argc>1) {
		strncpy(ip, argv[1], sizeof(ip)-1);
	}

	if(argc>2) {
		port = (short)atoi(argv[2]);
	}

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	printf("sizeof(struct addrinfo): %lu\n", (unsigned long)sizeof(struct addrinfo));

	getnameinfo_test(ip, port);

quit:
	tx_socklib_cleanup();

	return 0;
}
