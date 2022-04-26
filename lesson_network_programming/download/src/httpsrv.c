#include "tx.h"

#define IP "0.0.0.0"
#define PORT 1980

#define _STR(x) #x
#define STR(x) _STR(x)

#define LINE_SIZE	255
#define METHOD_SIZE	15
#define VER_SIZE	15
#define URI_SIZE	223

#define HDR_LINE_SIZE	255
#define HDR_KEY_SIZE	31
#define HDR_VAL_SIZE	223

#define BODY_SIZE	4095

#define BUF_SIZE	4096*100

#define PATHNAME_SIZE	255

#define HTTP_ERR_403	"Forbidden"
#define HTTP_ERR_404	"Not Found"
#define HTTP_ERR_408	"Request Timeout"
#define HTTP_ERR_411	"Length Required"
#define HTTP_ERR_500 	"Internal Server Error"

int main(int argc, char *argv[])
{
	tx_sock_t srv_sock = TX_SOCK_INVALID;
	tx_sock_t cln_sock = TX_SOCK_INVALID;

	char ip[32] = IP;
	unsigned short port = PORT;

	if(argc>1) {
		strncpy(ip, argv[1], sizeof(ip)-1);
	}
	if(argc>2) {
		port = atoi(argv[2]);
	}
	printf("ip: %s\n", ip);
	printf("port: %u\n", port);


	int err_num = tx_socklib_startup();
	if(0!=err_num) {
		printf("tx_socklib_startup err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	srv_sock = tx_sock_open(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(TX_SOCK_INVALID == srv_sock) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_open err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}
	printf("srv_sock: %ld\n", (long)srv_sock);

	int reuseaddr = 1;
	if(TX_SOCK_ERR == tx_sock_set_reuseaddr(srv_sock, reuseaddr)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_setsockopt reuseaddr err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	struct sockaddr_in sockaddr4;
	memset(&sockaddr4, 0, sizeof(sockaddr4));
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_port = htons(port);
	sockaddr4.sin_addr.s_addr = inet_addr(ip);
	if(TX_SOCK_ERR == tx_sock_bind(srv_sock, (struct sockaddr*)&sockaddr4, sizeof(sockaddr4))) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_bind err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	if(TX_SOCK_ERR == tx_sock_listen(srv_sock, SOMAXCONN)) {
		int err_num = tx_sock_get_errnum();
		printf("tx_sock_listen err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
		goto quit;
	}

	while(1) {
		unsigned int sockaddr4_size = sizeof(sockaddr4);
		cln_sock = tx_sock_accept(srv_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size);
		if(TX_SOCK_INVALID == cln_sock) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_accept err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			goto quit;
		}
		printf("cln_sock: %ld, %s:%d\n", (long)cln_sock, inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

		if(TX_SOCK_ERR == tx_sock_get_native_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_get_native_sockaddr err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			goto quit;
		}
		printf("%s:%d\n", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

		if(TX_SOCK_ERR == tx_sock_get_remote_sockaddr(cln_sock, (struct sockaddr*)&sockaddr4, (void*)&sockaddr4_size)) {
			int err_num = tx_sock_get_errnum();
			printf("tx_sock_get_remote_sockaddr err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
			goto quit;
		}
		printf("%s:%d\n", inet_ntoa(sockaddr4.sin_addr), ntohs(sockaddr4.sin_port));

		char recv_buf[BUF_SIZE];
		char send_buf[BUF_SIZE];
		while(1) {
			long recv_size = tx_sock_recv(cln_sock, recv_buf, sizeof(recv_buf)-1, 0);
			if(recv_size<0) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_recv err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				break;
			}
			if(recv_size==0) {
				printf("tx_sock_recv closed\n");
				break;
			}

			recv_buf[recv_size] = 0;
			printf("recv_buf: %ld, {\n%s}\n", recv_size, recv_buf);

			long send_size = 0;

			char *pbuf = recv_buf;

			char line[LINE_SIZE+1] = "";
			sscanf(pbuf, "%"STR(LINE_SIZE)"[^\r\n]", line);
			printf("line: {%s}\n", line);
			
			char method[METHOD_SIZE+1] = "";
			char uri[URI_SIZE+1] = "";
			char ver[VER_SIZE+1] = "";
			sscanf(pbuf, "%"STR(METHOD_SIZE)"s %"STR(URI_SIZE)"s %"STR(VER_SIZE)"s", method, uri, ver);
			printf("method: [%s]\n", method);
			printf("uri: [%s]\n", uri);
			printf("ver: [%s]\n", ver);

			pbuf = pbuf + strlen(line) + 2;
			if(pbuf - recv_buf >= recv_size) {
				snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 408 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n408 %s", HTTP_ERR_408, (unsigned long)(4+strlen(HTTP_ERR_408)), HTTP_ERR_408);
				send_size = strlen(send_buf);
				goto send;
			}
			
			long content_length = 0;
			while(1) {
				char hdr_line[HDR_LINE_SIZE+1] = "";
				sscanf(pbuf, "%"STR(HDR_LINE_SIZE)"[^\r\n]", hdr_line);
				printf("hdr_line: {%s}\n", hdr_line);
				if(strlen(hdr_line)==0) {
					pbuf = pbuf + 2;
					break;
				}
				char hdr_key[HDR_KEY_SIZE+1] = "";
				char hdr_val[HDR_VAL_SIZE+1] = "";
				sscanf(pbuf, "%"STR(HDR_KEY_SIZE)"[^:]: %"STR(HDR_VAL_SIZE)"[^\r\n]", hdr_key, hdr_val);
				printf("hdr_key: {%s}\n", hdr_key);
				printf("hdr_val: {%s}\n", hdr_val);
				if(0==strcmp(hdr_key, "Content-Length")) {
					content_length = atoi(hdr_val);
					printf("content_length: %ld\n", content_length);
				}
				pbuf = pbuf + strlen(hdr_line) + 2;
				if(pbuf - recv_buf >= recv_size) {
					snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 408 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n408 %s", HTTP_ERR_408, (unsigned long)(4+strlen(HTTP_ERR_408)), HTTP_ERR_408);
					send_size = strlen(send_buf);
					goto send;
				}
			}

			if(pbuf - recv_buf + content_length > recv_size) {
				snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 408 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n408 %s", HTTP_ERR_408, (unsigned long)(4+strlen(HTTP_ERR_408)), HTTP_ERR_408);
				send_size = strlen(send_buf);
				goto send;
			}
			char body[BODY_SIZE] = "";
			if(content_length>0) {
				memcpy(body, pbuf, content_length);
			}
			printf("body: {%s}\n", body);

			char root_pathname[PATHNAME_SIZE+1] = "";
			getcwd(root_pathname, sizeof(root_pathname));
			printf("root_pathname: %s\n", root_pathname);
	
			char index_name[] = "index.htm";

			char script_filename[256] = "";
			if(uri[strlen(uri)-1] == '/') {
				snprintf(script_filename, sizeof(script_filename), "%s%s", uri, index_name);
			} else {
				strcpy(script_filename, uri);
			}
#if defined(WIN32)
			for(int i=0;i<strlen(script_filename);i++) {
				if(script_filename[i]=='/') script_filename[i]='\\';
			}
#endif
			printf("script_filename: %s\n", script_filename);

			char script_pathname[PATHNAME_SIZE+1] = "";
			snprintf(script_pathname, sizeof(script_pathname), "%s%s", root_pathname, script_filename);
			printf("script_pathname: %s\n", script_pathname);
			//backdoor

			FILE *fp;
			fp = fopen(script_pathname, "rb");
			if(NULL==fp){
				snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 404 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n404 %s", HTTP_ERR_404, (unsigned long)(4+strlen(HTTP_ERR_404)), HTTP_ERR_404);
				send_size = strlen(send_buf);
			} else {
				fseek(fp, 0, SEEK_END);
				long ftell_size = ftell(fp);
				printf("ftell_size: %ld\n", ftell_size);
				if(ftell_size<0||ftell_size>sizeof(send_buf)/2) {
					snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 403 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n403 %s", HTTP_ERR_403, (unsigned long)(4+strlen(HTTP_ERR_403)), HTTP_ERR_403);
					send_size = strlen(send_buf);
				} else {
					sprintf(send_buf, "HTTP/1.1 200 OK\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n", ftell_size);

					long head_size = strlen(send_buf);
					rewind(fp);
					long fread_size = fread(send_buf+head_size, 1, ftell_size, fp);
					if(fread_size<ftell_size) {
						printf("fread_size: %ld\n", fread_size);
						snprintf(send_buf, sizeof(send_buf), "HTTP/1.1 500 %s\r\nConnection: Close\r\nContent-Length: %lu\r\n\r\n500 %s", HTTP_ERR_500, (unsigned long)(4+strlen(HTTP_ERR_500)), HTTP_ERR_500);
						send_size = strlen(send_buf);
					} else {
						send_size = head_size+fread_size;
						send_buf[head_size+ftell_size] = 0;
					}
				}
				fclose(fp);
			}

		send:
			printf("tx_sock_send begin: %ld, {\n%s}\n", send_size, send_buf);
			send_size = tx_sock_send_all(cln_sock, send_buf, send_size, 0);
			if(send_size<0) {
				int err_num = tx_sock_get_errnum();
				printf("tx_sock_send err: %d, %s\n", err_num, tx_sock_get_errstr(err_num));
				break;
			}
			if(send_size==0) {
				printf("tx_sock_send closed\n");
				break;
			}
			printf("tx_sock_send end: %ld\n", send_size);
			//tx_sock_shutdown(cln_sock, TX_SOCK_SHUT_RDWR);
		}
		tx_sock_close(cln_sock);
	}
quit:
	tx_sock_close(srv_sock);
	tx_socklib_cleanup();

	return 0;
}
