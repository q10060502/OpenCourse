#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define IP 		"0.0.0.0"
#define PORT 		1980
#define BUF_SIZE	4096

int main(int argc, char *argv[])
{
	int err_num;
	WSADATA winsock_data;
	SOCKET sock = INVALID_SOCKET;
	struct sockaddr_in sockaddr;
	char buf[BUF_SIZE];


	err_num = WSAStartup(MAKEWORD(2,2), &winsock_data);
	if(0 != err_num) {
		printf("WSAStartup err: %d\n", err_num);
		goto quit;
	}

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == sock) {
		err_num = WSAGetLastError();
		printf("socket err: %d\n", err_num);
		goto quit;
	}
	printf("sock: %ld\n", (long)sock);

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = inet_addr(IP);
	if(SOCKET_ERROR == bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) {
		err_num = WSAGetLastError();
		printf("bind err: %d\n", err_num);
		goto quit;
	}

	while(1) {
		socklen_t sockaddr_size = sizeof(sockaddr);
		int recv_size = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr, &sockaddr_size);
		if(recv_size<0) {
			err_num = WSAGetLastError();
			printf("recvfrom err: %d\n", err_num);
			break;
		}
		printf("recvfrom %s:%u\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

		printf("recv_size: %d\n", recv_size);
		for(int i=0;i<recv_size;i++) {
			printf("0x%x, ", buf[i]);
		}
		printf("\n");

		int send_size = sendto(sock, buf, recv_size, 0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
		if(send_size<0) {
			err_num = WSAGetLastError();
			printf("sendto err: %d\n", err_num);
			break;
		}
		printf("send_size: %d\n", send_size);
	}

	err_num = 0;
quit:
	closesocket(sock);
	WSACleanup();

	return err_num;
}
