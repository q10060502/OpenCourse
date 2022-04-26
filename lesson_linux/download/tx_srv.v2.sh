#!/bin/bash
read line
method=$(echo $line | cut -d ' ' -f 1)
uri=$(echo $line | cut -d ' ' -f 2)
ver=$(echo $line | cut -d ' ' -f 3)
msg="<div>method: $method; uri: $uri; ver: $ver</div>"
echo "$uri" | grep "/$" 2>&1 > /dev/null
if test $? -eq 0; then
	file=".${uri}index.htm"
else
	file=".${uri}"
fi
msg="$msg<div>file: $file </div>"
if test -f $file; then
	msg=$(cat $file)
else
	msg="404 Not Found"
fi
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo 
echo -n $msg
