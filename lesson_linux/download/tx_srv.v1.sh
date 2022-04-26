#!/bin/bash
msg="hello world"
msg=$(cat index.htm)
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo 
echo -n $msg
