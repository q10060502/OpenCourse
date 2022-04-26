#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "msg.h"

#define IP 		"127.0.0.1"
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
	socklen_t sockaddr_size;
	SOCKET sock = INVALID_SOCKET;
	char rep_buf[BUF_SIZE];
	int rep_size;
	char req_buf[BUF_SIZE];
	int req_size;
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

	preq_msg_head = (struct msg_head_t *)req_buf;
	preq_body = req_buf + sizeof(struct msg_head_t);
	prep_msg_head = (struct msg_head_t *)rep_buf;
	prep_body = rep_buf + sizeof(struct msg_head_t);
	while(1) {
		printf("Input: ");
		if(NULL==fgets(preq_body, sizeof(req_buf) - sizeof(struct msg_head_t), stdin)) {
			break;
		}
		preq_msg_head->type = htonl(MSG_TYPE_SYS_ECHO_REQ);
		preq_msg_head->size = htonl(strlen(preq_body) + 1);
		req_size = sendto(sock, req_buf, sizeof(struct msg_head_t) + ntohl(preq_msg_head->size), 0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
		if(req_size<0) {
			err_num = WSAGetLastError();
			printf("sendto err: %d\n", err_num);
			break;
		}
		printf("req_size: %d\n", req_size);

		sockaddr_size = sizeof(sockaddr);
		rep_size = recvfrom(sock, rep_buf, sizeof(rep_buf), 0, (struct sockaddr*)&sockaddr, &sockaddr_size);
		if(rep_size<0) {
			err_num = WSAGetLastError();
			printf("recvfrom err: %d\n", err_num);
			break;
		}
		printf("recvfrom %s:%u\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));
		printf("rep_size: %d\n", rep_size);
		for(int i=0;i<rep_size;i++) {
			printf("0x%x, ", rep_buf[i]);
		}
		printf("\n");

		prep_msg_head->type = ntohl(prep_msg_head->type);
		prep_msg_head->size = ntohl(prep_msg_head->size);
		
		if(rep_size < sizeof(struct msg_head_t)) {
			printf("data err: %d < msg_head_t(%u)\n", rep_size, (unsigned int)sizeof(struct msg_head_t));
			continue;
		}
		if(rep_size != sizeof(struct msg_head_t) + prep_msg_head->size) {
			printf("data err: %d != msg_head_t(%u) + %u\n", rep_size, (unsigned int)sizeof(struct msg_head_t), prep_msg_head->size);
			continue;
		}
		switch (prep_msg_head->type) {
			case MSG_TYPE_SYS_ECHO_REP:
				printf("SYS_ECHO: %s\n", prep_body);
				break;
			case MSG_TYPE_SYS_REP:
				printf("SYS: %s\n", prep_body);
				break;
			default:
				printf("err: msg type\n");
				break;
		}
	}
quit:
	closesocket(sock);
	WSACleanup();

	return 0;
}
