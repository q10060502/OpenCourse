#!/bin/sh
while echo start $1; do
	if test ! -p pipe; then
		mkfifo pipe
	fi
	./tx_srv$1.sh < pipe | nc -l -p 8000 > pipe
done
