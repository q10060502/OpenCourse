#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define IP "0.0.0.0"
#define PORT 1980
#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
	int err_num;
	WSADATA wsa_data;
	SOCKET lisn_sock = INVALID_SOCKET;
	SOCKET conn_sock = INVALID_SOCKET;
	struct sockaddr_in sockaddr;
	char buf[BUF_SIZE];

	err_num = WSAStartup(MAKEWORD(2,2), &wsa_data);
	if(0 != err_num) {
		printf("WSAStartup err: %d\n", err_num);
		goto quit;
	}

	lisn_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == lisn_sock) {
		err_num = WSAGetLastError();
		printf("socket err: %d\n", err_num);
		goto quit;
	}
	printf("lisn_sock: %ld\n", (long)lisn_sock);

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = inet_addr(IP);
	if(SOCKET_ERROR == bind(lisn_sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) {
		err_num = WSAGetLastError();
		printf("bind err: %d\n", err_num);
		goto quit;
	}

	if(SOCKET_ERROR == listen(lisn_sock, SOMAXCONN)) {
		err_num = WSAGetLastError();
		printf("listen err: %d\n", err_num);
		goto quit;
	}

	while(1) {
		socklen_t sockaddr_size = sizeof(sockaddr);
		conn_sock = accept(lisn_sock, (struct sockaddr*)&sockaddr, &sockaddr_size);
		if(INVALID_SOCKET == conn_sock) {
			err_num = WSAGetLastError();
			printf("accept err: %d\n", err_num);
			goto quit;
		}
		printf("conn_sock: %ld, %s:%u\n", (long)conn_sock, inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

		if(SOCKET_ERROR == getsockname(conn_sock, (struct sockaddr*)&sockaddr, (void*)&sockaddr_size)) {
			err_num = WSAGetLastError();
			printf("getsockname err: %d\n", err_num);
			goto quit;
		}
		printf("getsockname: %s:%d\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

		if(SOCKET_ERROR == getpeername(conn_sock, (struct sockaddr*)&sockaddr, (void*)&sockaddr_size)) {
			err_num = WSAGetLastError();
			printf("getpeername err: %d\n", err_num);
			goto quit;
		}
		printf("getpeername: %s:%d\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

		while(1) {
			int recv_size = recv(conn_sock, buf, sizeof(buf), 0);
			if(recv_size<0) {
				err_num = WSAGetLastError();
				printf("recv err: %d\n", err_num);
				break;
			}
			if(recv_size==0) {
				printf("recv closed\n");
				break;
			}

			printf("recv_size: %d\n", recv_size);
			for(int i=0;i<recv_size;i++) {
				printf("0x%x, ", buf[i]);
			}
			printf("\n");

			int send_size = send(conn_sock, buf, recv_size, 0);
			if(send_size<0) {
				err_num = WSAGetLastError();
				printf("send err: %d\n", err_num);
				break;
			}
			if(send_size==0) {
				printf("send closed\n");
				break;
			}
			printf("send_size: %d\n", send_size);
		}
		closesocket(conn_sock);
	}

	err_num = 0;
quit:
	closesocket(lisn_sock);
	WSACleanup();

	return err_num;
}
