#include "tx.h"

#define PORT		1980
#define BUF_SIZE	4096
#define MAX_CLIENT_COUNT	2

struct cln_t {
	#if defined(WIN32)
		uintptr_t thread;
	#else
		pthread_t thread;
	#endif
	int sock;
};

int srv_sock = -1;
struct cln_t clns[MAX_CLIENT_COUNT];
int is_quit = 0;

#if defined(WIN32)
unsigned int WINAPI cln_thread_func(void *pparam)
#else
void *cln_thread_func(void *pparam)
#endif
{
	int index = *(int*)pparam;
	struct cln_t *pclns = &clns[index];
	int cln_sock = pclns->sock;
	int r = 0;
	while(1) 
	{
		char recv_buf[BUF_SIZE];
		int recv_size;
		printf("recv...\n");
		recv_size = tx_sock_recv(cln_sock, recv_buf, sizeof(recv_buf), 0);
		if(recv_size < 0) 
		{
			printf("recv error\n");
			break;
		}
		if(recv_size == 0) 
		{
			printf("recv: 0\n");
			break;
		}
		printf("cln[%d](%d) recv_size: %d\n", index, cln_sock, recv_size);
		for(int i=0;i<recv_size;i++) {
			printf("0x%x, ", recv_buf[i]);
		}
		printf("\n");

		if(strncmp(recv_buf, "x", 1) == 0) {
			printf("quit\n");
			printf("shutdown srv_sock...\n");
			tx_sock_shutdown(srv_sock, TX_SOCK_SHUT_WR);
			is_quit = -1;
			break;
		}

		int send_size;
		printf("send...\n");
		send_size = tx_sock_send_all(cln_sock, recv_buf, recv_size, 0);
		if(send_size < 0) 
		{
			printf("send error\n");
			break;
		}
		if(send_size == 0) 
		{
			printf("send: 0\n");
			break;
		}
		printf("cln[%d](%d) send_size: %d\n", index, cln_sock, send_size);
	}
	#if defined(WIN32)
	return r;
	#else
	return (void*)(intptr_t)r;
	#endif
}

int main(int argc, char *argv[]) 
{
	int r = 0;

	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		r = 1;
		goto quit;
	}

	for(int index = 0; index<MAX_CLIENT_COUNT; index++) {
		clns[index].sock = -1;
	}

	printf("socket...\n");
	srv_sock = tx_sock_open(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(srv_sock<0) 
	{
		r = 2;
		goto quit;
	}

	struct sockaddr_in srv_sockaddr;

	printf("bind...\n");
	memset(&srv_sockaddr, 0, sizeof(srv_sockaddr));
	srv_sockaddr.sin_family = AF_INET;
	srv_sockaddr.sin_port = htons(PORT);
	srv_sockaddr.sin_addr.s_addr = INADDR_ANY;
	r = tx_sock_bind(srv_sock, (struct sockaddr *)&srv_sockaddr, sizeof(srv_sockaddr));
	if(r<0) 
	{
		r = 3;
		goto quit;
	}

	printf("listen...\n");
	r = tx_sock_listen(srv_sock, SOMAXCONN);
	if(r<0) 
	{
		r = 4;
		goto quit;
	}

	while(!is_quit)
	{
		int cln_sock = -1;
		struct sockaddr_in cln_sockaddr;
		socklen_t cln_sockaddr_size;
		cln_sockaddr_size = sizeof(cln_sockaddr);
		printf("accept...\n");
		cln_sock = tx_sock_accept(srv_sock, (struct sockaddr *)&cln_sockaddr, &cln_sockaddr_size);
		if(cln_sock < 0)
		{
			r = 5;
			goto quit;
		}
		int index = 0;
		for(index = 0; index<MAX_CLIENT_COUNT; index++) {
			if(clns[index].sock==-1) {
				break;
			}
		}
		if(index >= MAX_CLIENT_COUNT) {
			printf("full\n");
			tx_sock_close(cln_sock);
			continue;
		}
		clns[index].sock = cln_sock;
		#if defined(WIN32)
			unsigned int tid;
			clns[index].thread = _beginthreadex(NULL, 0, cln_thread_func, &index, 0, &tid);
			if(((HANDLE)clns[index].thread)==INVALID_HANDLE_VALUE) {
				printf("closesocket during creating thread\n");
				tx_sock_close(cln_sock);
				continue;
			}
		#else
			r = pthread_create(&clns[index].thread, NULL, cln_thread_func, &index);
			if(r<0) {
				printf("close during creating thread\n");
				tx_sock_close(cln_sock);
				continue;
			}
		#endif
	}
quit:
	tx_sock_close(srv_sock);
	tx_socklib_cleanup();
	return r;
}
