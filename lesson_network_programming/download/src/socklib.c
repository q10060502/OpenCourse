#if defined(WIN32)
	#include <winsock2.h>
#endif

#include <stdio.h>

int main(void)
{
	int r = 0;
#if defined(WIN32)
	WSADATA wsa_data;
	r = WSAStartup(0x0202, &wsa_data);
	if(0!=r) {
		printf("WSAStartup err: %d\n", r);
	}
#endif

#if defined(WIN32)
	r = WSACleanup();
	if(0!=r) {
		printf("WSACleanup err: %d\n", r);
	}
#endif

	return r;
}
