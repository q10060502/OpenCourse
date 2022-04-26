#include "tx.h"

void getaddrinfo_test(char *node, char *service)
{
	struct addrinfo *ai;

	if(0!=getaddrinfo(node, service, NULL, &ai)) {
		int err_num = tx_sock_get_errnum();
		printf("getaddrinfo err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
	}
	
	struct addrinfo *p = ai;
	while(p) {
		printf("------\n");
		switch(p->ai_family) {
			case AF_INET:
				printf("family: %d, AF_INET\n", p->ai_family);
				unsigned long ip4_num = ((struct sockaddr_in*)p->ai_addr)->sin_addr.s_addr;
				unsigned char *ip4_str = (unsigned char*)&ip4_num;
				printf("addr: ");
				for(int i=0;i<4;i++) {
					printf("%d", ip4_str[i]);
					if(i<3) {
						printf(".");
					} else {
						printf("\n");
					}
				}
				break;
			case AF_INET6:
				printf("family: %d, AF_INET6\n", p->ai_family);
				unsigned char *ip6_str = ((struct sockaddr_in6*)p->ai_addr)->sin6_addr.s6_addr;
				printf("addr: ");
				for(int i=0;i<16;i++) {
					printf("%02x", ip6_str[i]);
					if(i<15) {
						printf(":");
					} else {
						printf("\n");
					}
				}
				break;
			default:
				printf("family: %d\n", p->ai_family);
		}

		switch(p->ai_protocol) {
			case IPPROTO_TCP:
				printf("protocol: %d, IPPROTO_TCP\n", p->ai_protocol);
				break;
			case IPPROTO_UDP:
				printf("protocol: %d, IPPROTO_UDP\n", p->ai_protocol);
				break;
			case IPPROTO_IP:
				printf("protocol: %d, IPPROTO_IP\n", p->ai_protocol);
				break;
			default:
				printf("protocol: %d\n", p->ai_protocol);
		}

		switch(p->ai_socktype) {
			case SOCK_STREAM:
				printf("socktype: %d, SOCK_STREAM\n", p->ai_socktype);
				break;
			case SOCK_DGRAM:
				printf("socktype: %d, SOCK_DGRAM\n", p->ai_socktype);
				break;
			case SOCK_RAW:
				printf("socktype: %d, SOCK_RAW\n", p->ai_socktype);
				break;
			default:
				printf("socktype: %d\n", p->ai_socktype);
		}

		printf("canonname: %s\n", p->ai_canonname);

		p = p->ai_next;
	}

	freeaddrinfo(ai);
}

int main(int argc, char *argv[])
{
	char node[32] = "localhost";
	char service[32] = "";

	if(argc>1) {
		strncpy(node, argv[1], sizeof(node)-1);
	}

	if(argc>2) {
		strncpy(service, argv[2], sizeof(service)-1);
	}

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	printf("sizeof(struct addrinfo): %lu\n", (unsigned long)sizeof(struct addrinfo));

	getaddrinfo_test(node, service);

quit:
	tx_socklib_cleanup();

	return 0;
}
