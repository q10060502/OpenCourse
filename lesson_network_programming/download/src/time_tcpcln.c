#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

#define REMOTE_IP 	"127.0.0.1"
#define REMOTE_PORT 	1980
#define BUF_SIZE 	4096
#define IP_BUF_SIZE 	64

#if BYTE_ORDER == BIG_ENDIAN
	uint64_t ntohll(uint64_t value)
	{
			return _byteswap_uint64(value);
	}
#else
	#define ntohll(value) (value)
#endif

int main(int argc, char *argv[])
{
	int err_num;
	WSADATA winsock_data;
	char remote_ip[IP_BUF_SIZE] = REMOTE_IP;
	unsigned short remote_port = REMOTE_PORT;
	SOCKET cln_sock = INVALID_SOCKET;
	struct sockaddr_in sockaddr;
	socklen_t sockaddr_size;
	uint64_t now64;
	time_t now;
	char *ptime;

	if(argc>1) {
		strncpy(remote_ip, argv[1], sizeof(remote_ip)-1);
	}
	if(argc>2) {
		remote_port = atoi(argv[2]);
	}
	printf("remote_ip: %s\nremote port: %u\n", remote_ip, remote_port);

	err_num = WSAStartup(MAKEWORD(2,2), &winsock_data);
	if(0!=err_num) {
		printf("WSAStartup err: %d\n", err_num);
		goto quit;
	}

	cln_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == cln_sock) {
		err_num = WSAGetLastError();
		printf("socket err: %d\n", err_num);
		goto quit;
	}
	printf("cln_sock: %ld\n", (long)cln_sock);

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(REMOTE_PORT);
	sockaddr.sin_addr.s_addr = inet_addr(REMOTE_IP);
	if(SOCKET_ERROR == connect(cln_sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) {
		err_num = WSAGetLastError();
		printf("connect err: %d\n", err_num);
		goto quit;
	}

	sockaddr_size = sizeof(sockaddr);
	if(SOCKET_ERROR == getsockname(cln_sock, (struct sockaddr*)&sockaddr, &sockaddr_size)) {
		err_num = WSAGetLastError();
		printf("getsockname err: %d\n", err_num);
		goto quit;
	}
	printf("getsockname: %s:%d\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

	if(SOCKET_ERROR == getpeername(cln_sock, (struct sockaddr*)&sockaddr, (void*)&sockaddr_size)) {
		err_num = WSAGetLastError();
		printf("getpeername err: %d\n", err_num);
		goto quit;
	}
	printf("getpeername: %s:%d\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

	int recv_size = 0;
	while(recv_size < sizeof(now64)) {
		int tmp_recv_size = recv(cln_sock, ((char*)&now64) + recv_size, sizeof(now64) - recv_size, 0);
		if(tmp_recv_size<0) {
			err_num = WSAGetLastError();
			printf("recv err: %d\n", err_num);
			break;
		}
		if(tmp_recv_size==0) {
			printf("recv closed\n");
			break;
		}
		printf("tmp_recv_size: %d\n", tmp_recv_size);
		recv_size += tmp_recv_size;
	}
	printf("now64: %16"PRIx64"\n", now64);
	now = (time_t)ntohll(now64);
	printf("  now: %16"PRIx64"\n", (uint64_t)now);
	ptime = ctime(&now);
	if(NULL == ptime) {
		err_num = errno;
		printf("ctime err: %d\n", err_num);
		goto quit;
	}
	printf("recv: %s\n", ptime);
quit:
	closesocket(cln_sock);
	WSACleanup();

	return 0;
}
