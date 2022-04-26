#ifndef _TX_H_
#define _TX_H_

#if defined(WIN32)
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <direct.h> //getcwd
	#include <process.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <stddef.h>
	#include <pthread.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined(WIN32)
	#define TX_SOCK_INVALID INVALID_SOCKET
	#define TX_SOCK_ERR SOCKET_ERROR
	#define TX_SOCK_SHUT_RD SD_RECEIVE
	#define TX_SOCK_SHUT_WR SD_SEND
	#define TX_SOCK_SHUT_RDWR SD_BOTH
#else
	#define TX_SOCK_INVALID -1
	#define TX_SOCK_ERR -1
	#define TX_SOCK_SHUT_RD SHUT_RD
	#define TX_SOCK_SHUT_WR SHUT_WR
	#define TX_SOCK_SHUT_RDWR SHUT_RDWR
#endif

#if defined(WIN32)
	typedef SOCKET tx_sock_t;
#else
	typedef int tx_sock_t;
#endif

int tx_socklib_startup()
{
#if defined(WIN32)
	WSADATA wsa_data;
	return WSAStartup(0x0202, &wsa_data);
#else
	return 0;
#endif
}

int tx_socklib_cleanup()
{
#if defined(WIN32)
	return WSACleanup();
#else
	return 0;
#endif
}

#if defined(WIN32)
	#define tx_sock_open(domain, type, protocol) WSASocket((domain), (type), (protocol), NULL, 0, WSA_FLAG_OVERLAPPED)
#else
	#define tx_sock_open socket
#endif

int tx_sock_close(int _sock)
{
#if defined(WIN32)
	return closesocket(_sock);
#else
	return close(_sock);
#endif
}

#if defined(WIN32)
#define tx_sock_is_errtimeo(num) (WSAETIMEDOUT==num)
#else
#define tx_sock_is_errtimeo(num) (EAGAIN==num||EWOULDBLOCK==num)
#endif

#if defined(WIN32)
	#define tx_err_get_num() GetLastError()
#else
	#define tx_err_get_num() errno
#endif

#if defined(WIN32)
	#define tx_err_set_num(_num) SetLastError(_num)
#else
	#define tx_err_set_num(_num) (errno = (_num))
#endif

#if defined(WIN32)
	char *tx_err_get_str(int num)
	{
		char *buf = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, num, 0, (LPSTR)&buf, 256, NULL);
		return buf;
	}
#else
	#define tx_err_get_str(_num) strerror(_num)
#endif

#if defined(WIN32)
	void tx_err_free_str(char *_str)
	{
		LocalFree(_str);
	}
#else
	#define tx_err_free_str(_str)
#endif

#if defined(WIN32)
	#define tx_sock_get_errnum() WSAGetLastError()
	#define tx_sock_get_herrnum() WSAGetLastError()
#else
	#define tx_sock_get_errnum() errno
	#define tx_sock_get_herrnum() h_errno
#endif

#if defined(WIN32)
	#define tx_sock_set_err_num(_num) WSASetLastError(_num)
#else
	#define tx_sock_set_err_num(_num) (errno = (_num))
#endif

#if defined(WIN32)
	char *tx_sock_get_errstr(int num)
	{
		char *pbuf = NULL;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, num, 0, (LPSTR)&pbuf, 256, NULL);
		return pbuf;
	}
	#define tx_sock_get_herrstr(_num) tx_sock_get_errstr(_num)
#else
	#define tx_sock_get_errstr(_num) strerror(_num)
	#define tx_sock_get_herrstr(_num) hstrerror(_num)
#endif

#if defined(WIN32)
	void tx_sock_free_errstr(char *_str)
	{
		LocalFree(_str);
	}
#else
	#define tx_sock_free_errstr(_str)
#endif

#define tx_sock_bind bind

#define tx_sock_listen listen

#if defined(WIN32)
	#define tx_sock_accept(sock, psockaddr, psockaddr_size) WSAAccept((sock),(psockaddr),(psockaddr_size), NULL, 0)
#else
	#define tx_sock_accept(sock, psockaddr, psockaddr_size) accept((sock),(psockaddr),(psockaddr_size))
#endif

#define tx_sock_connect connect 

#define tx_sock_get_native_sockaddr getsockname
#define tx_sock_get_remote_sockaddr getpeername

#define tx_sock_recv recv
#define tx_sock_send send
#define tx_sock_shutdown shutdown

#define tx_sock_recvfrom recvfrom
#define tx_sock_sendto sendto

#define tx_sock_get_opt getsockopt
#define tx_sock_set_opt setsockopt

int tx_sock_set_reuseaddr(tx_sock_t sock, int reuseaddr)
{
	return tx_sock_set_opt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseaddr, sizeof(reuseaddr));
}

int tx_sock_set_rcvtimeopt(tx_sock_t sock, int ms)
{
#if defined(WIN32)
	//SO_RCVTIMEO <-- WSASocket(..., WSA_FLAG_OVERLAPPED)
	DWORD rcvtimeo = ms;
#else
	struct timeval rcvtimeo = {ms/1000,(ms/1000)*1000};
#endif
	return tx_sock_set_opt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&rcvtimeo, sizeof(rcvtimeo));
}

ssize_t tx_sock_recv_all(tx_sock_t sock, void *buf, size_t buf_size, int flags)
{
	size_t recvd_size = 0;
	do {
		size_t tmp_size = tx_sock_recv(sock, buf + recvd_size, buf_size - recvd_size, 0);
		if(tmp_size==-1||tmp_size==0) return tmp_size;
		recvd_size += tmp_size;
	} while(recvd_size<buf_size);
	return recvd_size;
}

ssize_t tx_sock_send_all(tx_sock_t sock, void *buf, size_t buf_size, int flags)
{
	size_t sent_size = 0;
	do {
		size_t tmp_size = tx_sock_send(sock, buf + sent_size, buf_size - sent_size, 0);
		if(tmp_size==-1||tmp_size==0) return tmp_size;
		sent_size += tmp_size;
	} while(sent_size<buf_size);
	return sent_size;
}

#define tx_io_select select

#define IPV4_LEN 16
#define IPV6_LEN 64
#define IP_LEN IPV6_LEN

void tx_mem_dump(void *_buf, size_t _buf_size) 
{
	for(int i=0;i<(_buf_size); i++) {
		printf("%#x, ", ((unsigned char*)(_buf))[i]);
	}
	printf("\n");
}

#endif

