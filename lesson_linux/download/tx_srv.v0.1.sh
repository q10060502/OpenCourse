#!/bin/sh
msg="hello world"
msg=$(cat index.htm)
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo "Server: TXS/0.1"
echo 
echo -n $msg
