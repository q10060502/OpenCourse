all: hello syntax_c socklib sock_err sock_open sock_close sockaddr byte_order inet_addr inet_ntoa gethostbyname gethostbyaddr getaddrinfo getnameinfo echo_tcpsrv echo_tcpcln echo_httpsrv httpsrv echo_udpsrv echo_udpcln echo_multithread_tcpsrv echo_select_tcpsrv echo_select_tcpcln echo_broadcast_sender echo_multicast_sender echo_multicast_recver raw_icmp_recver
hello: 
	i686-w64-mingw32-gcc -Wall -g -o bin/hello.i686.exe hello.c
	x86_64-w64-mingw32-gcc -Wall -g -o bin/hello.amd64.exe hello.c
	cc -Wall -g -o bin/hello.linux.i386.out -m32 hello.c 
	cc -Wall -g -o bin/hello.linux.amd64.out -m64 hello.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/hello.linux.arm.out hello.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/hello.linux.aarch64.out hello.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/hello.linux.mips.out hello.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/hello.linux.mips64.out hello.c 
syntax_c: 
	i686-w64-mingw32-gcc -Wall -g -o bin/syntax_c.i686.exe syntax_c.c
	x86_64-w64-mingw32-gcc -Wall -g -o bin/syntax_c.amd64.exe syntax_c.c
	cc -Wall -g -o bin/syntax_c.linux.i386.out -m32 syntax_c.c 
	cc -Wall -g -o bin/syntax_c.linux.amd64.out -m64 syntax_c.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/syntax_c.linux.arm.out syntax_c.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/syntax_c.linux.aarch64.out syntax_c.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/syntax_c.linux.mips.out syntax_c.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/syntax_c.linux.mips64.out syntax_c.c 
socklib: 
	i686-w64-mingw32-gcc -Wall -g -o bin/socklib.i686.exe socklib.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/socklib.amd64.exe socklib.c -lws2_32
	cc -Wall -g -o bin/socklib.linux.i386.out -m32 socklib.c 
	cc -Wall -g -o bin/socklib.linux.amd64.out -m64 socklib.c 
sock_err: 
	i686-w64-mingw32-gcc -Wall -g -o bin/sock_err.i686.exe sock_err.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/sock_err.amd64.exe sock_err.c -lws2_32
	cc -Wall -g -o bin/sock_err.linux.i386.out -m32 sock_err.c 
	cc -Wall -g -o bin/sock_err.linux.amd64.out -m64 sock_err.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/sock_err.linux.arm.out sock_err.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/sock_err.linux.aarch64.out sock_err.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/sock_err.linux.mips.out sock_err.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/sock_err.linux.mips64.out sock_err.c 
sock_open: 
	i686-w64-mingw32-gcc -Wall -g -o bin/sock_open.i686.exe sock_open.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/sock_open.amd64.exe sock_open.c -lws2_32
	cc -Wall -g -o bin/sock_open.linux.i386.out -m32 sock_open.c 
	cc -Wall -g -o bin/sock_open.linux.amd64.out -m64 sock_open.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/sock_open.linux.arm.out sock_open.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/sock_open.linux.aarch64.out sock_open.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/sock_open.linux.mips.out sock_open.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/sock_open.linux.mips64.out sock_open.c 
sock_close: 
	i686-w64-mingw32-gcc -Wall -g -o bin/sock_close.i686.exe sock_close.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/sock_close.amd64.exe sock_close.c -lws2_32
	cc -Wall -g -o bin/sock_close.linux.i386.out -m32 sock_close.c 
	cc -Wall -g -o bin/sock_close.linux.amd64.out -m64 sock_close.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/sock_close.linux.arm.out sock_close.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/sock_close.linux.aarch64.out sock_close.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/sock_close.linux.mips.out sock_close.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/sock_close.linux.mips64.out sock_close.c 
byte_order: 
	i686-w64-mingw32-gcc -Wall -g -o bin/byte_order.i686.exe byte_order.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/byte_order.amd64.exe byte_order.c -lws2_32
	cc -Wall -g -o bin/byte_order.linux.i386.out -m32 byte_order.c 
	cc -Wall -g -o bin/byte_order.linux.amd64.out -m64 byte_order.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/byte_order.linux.arm.out byte_order.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/byte_order.linux.aarch64.out byte_order.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/byte_order.linux.mips.out byte_order.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/byte_order.linux.mips64.out byte_order.c 
inet_addr: 
	i686-w64-mingw32-gcc -Wall -g -o bin/inet_addr.i686.exe inet_addr.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/inet_addr.amd64.exe inet_addr.c -lws2_32
	cc -Wall -g -o bin/inet_addr.linux.i386.out -m32 inet_addr.c 
	cc -Wall -g -o bin/inet_addr.linux.amd64.out -m64 inet_addr.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/inet_addr.linux.arm.out inet_addr.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/inet_addr.linux.aarch64.out inet_addr.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/inet_addr.linux.mips.out inet_addr.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/inet_addr.linux.mips64.out inet_addr.c 
inet_ntoa: 
	i686-w64-mingw32-gcc -Wall -g -o bin/inet_ntoa.i686.exe inet_ntoa.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/inet_ntoa.amd64.exe inet_ntoa.c -lws2_32
	cc -Wall -g -o bin/inet_ntoa.linux.i386.out -m32 inet_ntoa.c 
	cc -Wall -g -o bin/inet_ntoa.linux.amd64.out -m64 inet_ntoa.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/inet_ntoa.linux.arm.out inet_ntoa.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/inet_ntoa.linux.aarch64.out inet_ntoa.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/inet_ntoa.linux.mips.out inet_ntoa.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/inet_ntoa.linux.mips64.out inet_ntoa.c 
sockaddr: 
	i686-w64-mingw32-gcc -Wall -g -o bin/sockaddr.i686.exe sockaddr.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/sockaddr.amd64.exe sockaddr.c -lws2_32
	cc -Wall -g -o bin/sockaddr.linux.i386.out -m32 sockaddr.c 
	cc -Wall -g -o bin/sockaddr.linux.amd64.out -m64 sockaddr.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/sockaddr.linux.arm.out sockaddr.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/sockaddr.linux.aarch64.out sockaddr.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/sockaddr.linux.mips.out sockaddr.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/sockaddr.linux.mips64.out sockaddr.c 
gethostbyname: 
	i686-w64-mingw32-gcc -Wall -g -o bin/gethostbyname.i686.exe gethostbyname.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/gethostbyname.amd64.exe gethostbyname.c -lws2_32
	cc -Wall -g -o bin/gethostbyname.linux.i386.out -m32 gethostbyname.c 
	cc -Wall -g -o bin/gethostbyname.linux.amd64.out -m64 gethostbyname.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/gethostbyname.linux.arm.out gethostbyname.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/gethostbyname.linux.aarch64.out gethostbyname.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/gethostbyname.linux.mips.out gethostbyname.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/gethostbyname.linux.mips64.out gethostbyname.c 
gethostbyaddr: 
	i686-w64-mingw32-gcc -Wall -g -o bin/gethostbyaddr.i686.exe gethostbyaddr.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/gethostbyaddr.amd64.exe gethostbyaddr.c -lws2_32
	cc -Wall -g -o bin/gethostbyaddr.linux.i386.out -m32 gethostbyaddr.c 
	cc -Wall -g -o bin/gethostbyaddr.linux.amd64.out -m64 gethostbyaddr.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/gethostbyaddr.linux.arm.out gethostbyaddr.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/gethostbyaddr.linux.aarch64.out gethostbyaddr.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/gethostbyaddr.linux.mips.out gethostbyaddr.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/gethostbyaddr.linux.mips64.out gethostbyaddr.c 
getaddrinfo: 
	i686-w64-mingw32-gcc -Wall -g -o bin/getaddrinfo.i686.exe getaddrinfo.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/getaddrinfo.amd64.exe getaddrinfo.c -lws2_32
	cc -Wall -g -o bin/getaddrinfo.linux.i386.out -m32 getaddrinfo.c 
	cc -Wall -g -o bin/getaddrinfo.linux.amd64.out -m64 getaddrinfo.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/getaddrinfo.linux.arm.out getaddrinfo.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/getaddrinfo.linux.aarch64.out getaddrinfo.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/getaddrinfo.linux.mips.out getaddrinfo.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/getaddrinfo.linux.mips64.out getaddrinfo.c 
getnameinfo: 
	i686-w64-mingw32-gcc -Wall -g -o bin/getnameinfo.i686.exe getnameinfo.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/getnameinfo.amd64.exe getnameinfo.c -lws2_32
	cc -Wall -g -o bin/getnameinfo.linux.i386.out -m32 getnameinfo.c 
	cc -Wall -g -o bin/getnameinfo.linux.amd64.out -m64 getnameinfo.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/getnameinfo.linux.arm.out getnameinfo.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/getnameinfo.linux.aarch64.out getnameinfo.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/getnameinfo.linux.mips.out getnameinfo.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/getnameinfo.linux.mips64.out getnameinfo.c 
echo_tcpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_tcpsrv.i686.exe echo_tcpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_tcpsrv.amd64.exe echo_tcpsrv.c -lws2_32
	cc -Wall -g -o bin/echo_tcpsrv.linux.i386.out -m32 echo_tcpsrv.c 
	cc -Wall -g -o bin/echo_tcpsrv.linux.amd64.out -m64 echo_tcpsrv.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_tcpsrv.linux.arm.out echo_tcpsrv.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_tcpsrv.linux.aarch64.out echo_tcpsrv.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_tcpsrv.linux.mips.out echo_tcpsrv.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_tcpsrv.linux.mips64.out echo_tcpsrv.c 
echo_tcpcln: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_tcpcln.i686.exe echo_tcpcln.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_tcpcln.amd64.exe echo_tcpcln.c -lws2_32
	cc -Wall -g -o bin/echo_tcpcln.linux.i386.out -m32 echo_tcpcln.c 
	cc -Wall -g -o bin/echo_tcpcln.linux.amd64.out -m64 echo_tcpcln.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_tcpcln.linux.arm.out echo_tcpcln.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_tcpcln.linux.aarch64.out echo_tcpcln.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_tcpcln.linux.mips.out echo_tcpcln.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_tcpcln.linux.mips64.out echo_tcpcln.c 
echo_httpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_httpsrv.i686.exe echo_httpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_httpsrv.amd64.exe echo_httpsrv.c -lws2_32
	cc -Wall -g -o bin/echo_httpsrv.linux.i386.out -m32 echo_httpsrv.c 
	cc -Wall -g -o bin/echo_httpsrv.linux.amd64.out -m64 echo_httpsrv.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_httpsrv.linux.arm.out echo_httpsrv.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_httpsrv.linux.aarch64.out echo_httpsrv.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_httpsrv.linux.mips.out echo_httpsrv.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_httpsrv.linux.mips64.out echo_httpsrv.c 
httpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/httpsrv.i686.exe httpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/httpsrv.amd64.exe httpsrv.c -lws2_32
	cc -Wall -g -o bin/httpsrv.linux.i386.out -m32 httpsrv.c 
	cc -Wall -g -o bin/httpsrv.linux.amd64.out -m64 httpsrv.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/httpsrv.linux.arm.out httpsrv.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/httpsrv.linux.aarch64.out httpsrv.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/httpsrv.linux.mips.out httpsrv.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/httpsrv.linux.mips64.out httpsrv.c 
echo_multithread_tcpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_multithread_tcpsrv.i686.exe echo_multithread_tcpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_multithread_tcpsrv.amd64.exe echo_multithread_tcpsrv.c -lws2_32
	cc -Wall -g -o bin/echo_multithread_tcpsrv.linux.i386.out -m32 echo_multithread_tcpsrv.c -lpthread
	cc -Wall -g -o bin/echo_multithread_tcpsrv.linux.amd64.out -m64 echo_multithread_tcpsrv.c  -lpthread
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_multithread_tcpsrv.linux.arm.out echo_multithread_tcpsrv.c  -lpthread
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_multithread_tcpsrv.linux.aarch64.out echo_multithread_tcpsrv.c  -lpthread
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_multithread_tcpsrv.linux.mips.out echo_multithread_tcpsrv.c  -lpthread
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_multithread_tcpsrv.linux.mips64.out echo_multithread_tcpsrv.c  -lpthread
echo_select_tcpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_select_tcpsrv.i686.exe echo_select_tcpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_select_tcpsrv.amd64.exe echo_select_tcpsrv.c -lws2_32
	cc -Wall -g -o bin/echo_select_tcpsrv.linux.i386.out -m32 echo_select_tcpsrv.c 
	cc -Wall -g -o bin/echo_select_tcpsrv.linux.amd64.out -m64 echo_select_tcpsrv.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_select_tcpsrv.linux.arm.out echo_select_tcpsrv.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_select_tcpsrv.linux.aarch64.out echo_select_tcpsrv.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_select_tcpsrv.linux.mips.out echo_select_tcpsrv.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_select_tcpsrv.linux.mips64.out echo_select_tcpsrv.c 
echo_udpsrv: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_udpsrv.i686.exe echo_udpsrv.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_udpsrv.amd64.exe echo_udpsrv.c -lws2_32
	cc -Wall -g -o bin/echo_udpsrv.linux.i386.out -m32 echo_udpsrv.c 
	cc -Wall -g -o bin/echo_udpsrv.linux.amd64.out -m64 echo_udpsrv.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_udpsrv.linux.arm.out echo_udpsrv.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_udpsrv.linux.aarch64.out echo_udpsrv.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_udpsrv.linux.mips.out echo_udpsrv.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_udpsrv.linux.mips64.out echo_udpsrv.c 
echo_udpcln: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_udpcln.i686.exe echo_udpcln.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_udpcln.amd64.exe echo_udpcln.c -lws2_32
	cc -Wall -g -o bin/echo_udpcln.linux.i386.out -m32 echo_udpcln.c 
	cc -Wall -g -o bin/echo_udpcln.linux.amd64.out -m64 echo_udpcln.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_udpcln.linux.arm.out echo_udpcln.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_udpcln.linux.aarch64.out echo_udpcln.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_udpcln.linux.mips.out echo_udpcln.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_udpcln.linux.mips64.out echo_udpcln.c 
echo_broadcast_sender: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_broadcast_sender.i686.exe echo_broadcast_sender.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_broadcast_sender.amd64.exe echo_broadcast_sender.c -lws2_32
	cc -Wall -g -o bin/echo_broadcast_sender.linux.i386.out -m32 echo_broadcast_sender.c 
	cc -Wall -g -o bin/echo_broadcast_sender.linux.amd64.out -m64 echo_broadcast_sender.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_broadcast_sender.linux.arm.out echo_broadcast_sender.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_broadcast_sender.linux.aarch64.out echo_broadcast_sender.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_broadcast_sender.linux.mips.out echo_broadcast_sender.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_broadcast_sender.linux.mips64.out echo_broadcast_sender.c 
echo_multicast_recver: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_multicast_recver.i686.exe echo_multicast_recver.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_multicast_recver.amd64.exe echo_multicast_recver.c -lws2_32
	cc -Wall -g -o bin/echo_multicast_recver.linux.i386.out -m32 echo_multicast_recver.c 
	cc -Wall -g -o bin/echo_multicast_recver.linux.amd64.out -m64 echo_multicast_recver.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_multicast_recver.linux.arm.out echo_multicast_recver.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_multicast_recver.linux.aarch64.out echo_multicast_recver.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_multicast_recver.linux.mips.out echo_multicast_recver.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_multicast_recver.linux.mips64.out echo_multicast_recver.c 
echo_multicast_sender: 
	i686-w64-mingw32-gcc -Wall -g -o bin/echo_multicast_sender.i686.exe echo_multicast_sender.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/echo_multicast_sender.amd64.exe echo_multicast_sender.c -lws2_32
	cc -Wall -g -o bin/echo_multicast_sender.linux.i386.out -m32 echo_multicast_sender.c 
	cc -Wall -g -o bin/echo_multicast_sender.linux.amd64.out -m64 echo_multicast_sender.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/echo_multicast_sender.linux.arm.out echo_multicast_sender.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/echo_multicast_sender.linux.aarch64.out echo_multicast_sender.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/echo_multicast_sender.linux.mips.out echo_multicast_sender.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/echo_multicast_sender.linux.mips64.out echo_multicast_sender.c 
raw_icmp_recver: 
	i686-w64-mingw32-gcc -Wall -g -o bin/raw_icmp_recver.i686.exe raw_icmp_recver.c -lws2_32
	x86_64-w64-mingw32-gcc -Wall -g -o bin/raw_icmp_recver.amd64.exe raw_icmp_recver.c -lws2_32
	cc -Wall -g -o bin/raw_icmp_recver.linux.i386.out -m32 raw_icmp_recver.c 
	cc -Wall -g -o bin/raw_icmp_recver.linux.amd64.out -m64 raw_icmp_recver.c 
	arm-linux-gnueabi-gcc -Wall -g -o bin/raw_icmp_recver.linux.arm.out raw_icmp_recver.c 
	aarch64-linux-gnu-gcc -Wall -g -o bin/raw_icmp_recver.linux.aarch64.out raw_icmp_recver.c 
	mips-linux-gnu-gcc -static -Wall -g -o bin/raw_icmp_recver.linux.mips.out raw_icmp_recver.c 
	mips64-linux-gnuabi64-gcc -static -Wall -g -o bin/raw_icmp_recver.linux.mips64.out raw_icmp_recver.c 
cc:
	apt-get install build-essential mingw-w64 gcc-arm-linux-gnueabi gcc-aarch64-linux-gnu gcc-mips-linux-gnu gcc-mips64-linux-gnuabi64-gcc qemu
cc_fix:
	cd /usr/include/ && sudo ln -s asm-generic asm
