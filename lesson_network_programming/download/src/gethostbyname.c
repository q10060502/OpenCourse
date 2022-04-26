#include "tx.h"

int main(int argc, char *argv[])
{
	char name[32] = "localhost";

	if(argc>1) {
		strncpy(name, argv[1], sizeof(name)-1);
	}

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	printf("sizeof(struct hostent): %lu\n", (unsigned long)sizeof(struct hostent));

	struct hostent *phostent = gethostbyname(name);
	if(NULL==phostent) {
		err_num = tx_sock_get_herrnum();
		printf("gethostbyname err: %d, %s\n", err_num, tx_sock_get_herrstr(err_num));
		goto quit;
	}
	printf("phostent->h_name: %s\n", phostent->h_name);
	for(int i=0; phostent->h_aliases[i]!=NULL; i++) {
		printf("phostent->h_aliases[%d]: %s\n", i, phostent->h_aliases[i]);
	}
	switch(phostent->h_addrtype) {
		case AF_INET:
			printf("phostent->h_addrtype: %d(AF_INET)\n", phostent->h_addrtype);
			break;
		default:
			printf("phostent->h_addrtype: %d\n", phostent->h_addrtype);
	}
	printf("phostent->h_length: %d\n", phostent->h_length);
	for(int i=0; phostent->h_addr_list[i]!=NULL; i++) {
		printf("phostent->h_addr[%d]: %s\n", i, inet_ntoa(*((struct in_addr*)phostent->h_addr_list[i])));
	}

quit:
	tx_socklib_cleanup();

	return 0;
}
