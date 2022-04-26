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

	cln_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == cln_sock) {
		err_num = WSAGetLastError();
		printf("socket err: %d\n", err_num);
		goto quit;
	}
	printf("cln_sock: %ld\n", (long)cln_sock);

	struct sockaddr_in remote_sockaddr;
	memset(&remote_sockaddr, 0, sizeof(remote_sockaddr));
	remote_sockaddr.sin_family = AF_INET;
	remote_sockaddr.sin_port = htons(REMOTE_PORT);
	remote_sockaddr.sin_addr.s_addr = inet_addr(REMOTE_IP);

	int send_size = sendto(cln_sock, NULL, 0, 0, (struct sockaddr*)&remote_sockaddr, sizeof(remote_sockaddr));
	if(send_size<0) {
		err_num = WSAGetLastError();
		printf("sendto err: %d\n", err_num);
		goto quit;
	}
	printf("send_size: %d\n", send_size);

	now64 = 0;
	sockaddr_size = sizeof(sockaddr);
	int recv_size = recvfrom(cln_sock, (char*)&now64, sizeof(now64), 0, (struct sockaddr*)&sockaddr, &sockaddr_size);
	if(recv_size<0) {
		err_num = WSAGetLastError();
		printf("recvfrom err: %d\n", err_num);
		goto quit;
	}
	printf("recvfrom %s:%d\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));
	printf("recv_size: %d\n", recv_size);
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
