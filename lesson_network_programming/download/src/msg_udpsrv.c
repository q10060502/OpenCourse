#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "msg.h"

#define IP 		"0.0.0.0"
#define PORT 		1980
#define BUF_SIZE 	4096
#define IP_BUF_SIZE	64

int main(int argc, char *argv[])
{
	int err_num;
	WSADATA winsock_data;
	char ip[IP_BUF_SIZE] = IP;
	unsigned int port = PORT;
	struct sockaddr_in sockaddr;
	SOCKET sock = INVALID_SOCKET;
	char req_buf[BUF_SIZE];
	int req_size;
	char rep_buf[BUF_SIZE];
	int rep_size;
	struct msg_head_t *preq_msg_head, *prep_msg_head;
	char *preq_body, *prep_body;

	if(argc>1) {
		strncpy(ip, argv[1], sizeof(ip)-1);
	}
	if(argc>2) {
		port = atoi(argv[2]);
	}
	printf("ip: %s\nport: %u\n", ip, port);

	err_num = WSAStartup(MAKEWORD(2,2), &winsock_data);
	if(0!=err_num) {
		printf("WSAStartup err: %d\n", err_num);
		goto quit;
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(INVALID_SOCKET == sock) {
		err_num = WSAGetLastError();
		printf("socket err: %d\n", err_num);
		goto quit;
	}

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	sockaddr.sin_addr.s_addr = inet_addr(ip);
	if(SOCKET_ERROR == bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) {
		err_num = WSAGetLastError();
		printf("bind err: %d\n", err_num);
		goto quit;
	}

	preq_msg_head = (struct msg_head_t *)req_buf;
	preq_body = req_buf + sizeof(struct msg_head_t);
	prep_msg_head = (struct msg_head_t *)rep_buf;
	prep_body = rep_buf + sizeof(struct msg_head_t);
	while(1) {
		socklen_t sockaddr_size;
		sockaddr_size = sizeof(sockaddr);
		req_size = recvfrom(sock, req_buf, sizeof(req_buf), 0, (struct sockaddr*)&sockaddr, &sockaddr_size);
		if(req_size<0) {
			err_num = WSAGetLastError();
			printf("recvfrom err: %d\n", err_num);
			break;
		}
		printf("recvfrom %s:%u\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));
		printf("req_size: %d\n", req_size);
		for(int i=0;i<req_size;i++) {
			printf("0x%x, ", req_buf[i]);
		}
		printf("\n");

		preq_msg_head->type = ntohl(preq_msg_head->type);
		preq_msg_head->size = ntohl(preq_msg_head->size);

		if(req_size < sizeof(struct msg_head_t)) {
			printf("data err: %d < msg_head_t(%u)\n", req_size, (unsigned int)sizeof(struct msg_head_t));
			continue;
		}
		if(req_size != sizeof(struct msg_head_t) + preq_msg_head->size) {
			printf("data err: %d != msg_head_t(%u) + %u\n", req_size, (unsigned int)sizeof(struct msg_head_t), preq_msg_head->size);
			continue;
		}

		switch (preq_msg_head->type) {
			case MSG_TYPE_SYS_ECHO_REQ:
				memcpy(prep_body, preq_body, preq_msg_head->size);
				prep_msg_head->type = htonl(MSG_TYPE_SYS_ECHO_REP);
				prep_msg_head->size = htonl(preq_msg_head->size);
				rep_size = sendto(sock, rep_buf, sizeof(struct msg_head_t) + ntohl(prep_msg_head->size), 0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
				if(rep_size<0) {
					err_num = WSAGetLastError();
					printf("sendto err: %d\n", err_num);
					break;
				}
				printf("rep_size: %d\n", rep_size);
				break;
			default:
				strncpy(prep_body, "err: msg type\n", sizeof(rep_buf) - sizeof(struct msg_head_t));
				prep_msg_head->type = htonl(MSG_TYPE_SYS_REP);
				prep_msg_head->size = htonl(strlen(prep_body) + 1);
				rep_size = sendto(sock, rep_buf, sizeof(struct msg_head_t) + ntohl(prep_msg_head->size), 0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
				if(rep_size<0) {
					err_num = WSAGetLastError();
					printf("sendto err: %d\n", err_num);
					break;
				}
				printf("rep_size: %d\n", rep_size);
				break;
		}
	}
quit:
	closesocket(sock);
	WSACleanup();

	return 0;
}
